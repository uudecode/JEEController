#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>


#define DEBUG_ON

#include <SPI.h>
#include <UTouch.h>
#include <UTFT.h>
#include <EEPROM.h>

uint8_t lcdBacklight = 7; // must be a PWM pin for variable brightness
uint8_t lcdBacklightBrightness = 255; // 0-255

#include <avr/pgmspace.h>
#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Location.h"
#include "Sensor.h"
#include "Switch.h"
#include "Locations.h"
#include "WiFiController.h"
#include "Button.h"
#include "MaterialColors.h"



WiFiController wifiController ("93.100.131.244", 37001);
UTouch      myTouch(6, 5, 4, 3, 2);
UTFT myGLCD(ITDB32S, 38, 39, 40, 41);
extern uint8_t SmallFont[];

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

const char homesteadName[] PROGMEM = "Дача";

boolean WiFiOn = false;
boolean GPRSOn = false;
boolean SMSOn = false;
boolean ControllerOn = false;
long lastTouch;
const long touchTimeout = 300000;
String command;

Yard yard = Yard();
Barn barn =  Barn();
Sauna sauna =  Sauna();
WashingRoom washingRoom =  WashingRoom();
FirstFloor firstFloor =  FirstFloor();
SecondFloor secondFloor =  SecondFloor();
char configuration[2400];
char displayDateAndTime[22];

int nextPosition;

int touchY = -1;
int touchX = -1;

void printStatusOnTFT() {
  myGLCD.setBackColor(MATERIAL_BLUE);
  if (WiFiOn)
    myGLCD.setColor(MATERIAL_GREEN);
  else
    myGLCD.setColor(MATERIAL_RED);
  myGLCD.print("WiFi", BOTTOM_STRING);


  if (GPRSOn)
    myGLCD.setColor(MATERIAL_GREEN);
  else
    myGLCD.setColor(MATERIAL_RED);
  myGLCD.print("GPRS", 35 + BOTTOM_STRING);

  if (SMSOn)
    myGLCD.setColor(MATERIAL_GREEN);
  else
    myGLCD.setColor(MATERIAL_RED);
  myGLCD.print("SMS", 70 + BOTTOM_STRING);

  if (ControllerOn) {
    myGLCD.setColor(MATERIAL_GREEN);
    myGLCD.print("ONLINE ", 100 + BOTTOM_STRING);
  }
  else {
    myGLCD.setColor(MATERIAL_RED);
    myGLCD.print("OFFLINE", 100 + BOTTOM_STRING);
  }

  if (0 < command.length()) {
    myGLCD.setColor(MATERIAL_WHITE);
    myGLCD.print("                                                                    ", 180 + BOTTOM_STRING);
    myGLCD.print(command, 160 + BOTTOM_STRING);
  }
}


void getConfig() {
  //  sprintf(configuration,"<Homestead name =\"%s\">\n\t<Locations>%s%s%s%s\n\t</Locations>\n</Homestead>\n",copyToString(homesteadName).c_str(),(yard.getConfig()).c_str(),(barn.getConfig()).c_str(),(sauna.getConfig()).c_str(), (washingRoom.getConfig()).c_str() );
  sprintf(configuration, "<Homestead name =\"%s\">\n\t<Locations> ", copyToString(homesteadName).c_str());
  nextPosition = getEOSposition(configuration);
  nextPosition = yard.getConfig(configuration, nextPosition);
  nextPosition = barn.getConfig(configuration, nextPosition);
  nextPosition = sauna.getConfig(configuration, nextPosition);
  nextPosition = washingRoom.getConfig(configuration, nextPosition);
  nextPosition = firstFloor.getConfig(configuration, nextPosition);
  nextPosition = secondFloor.getConfig(configuration, nextPosition);
  nextPosition = appendX(configuration, nextPosition, F("\n\t</Locations>\n</Homestead>\n"));
  configuration[nextPosition] = '\0';
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.print(F("Initializing "));
  Serial.println(copyToString(homesteadName));
  randomSeed(analogRead(0));
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  pinMode(VIBRO, OUTPUT);
  analogWrite(VIBRO, 0);
  pinMode(lcdBacklight, OUTPUT);
  analogWrite(lcdBacklight, lcdBacklightBrightness);
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(0, 0, 319, 239);
  myGLCD.setColor(MATERIAL_PURPLE);
  myGLCD.fillRect(0, 0, 319, 13);
  myGLCD.setColor(MATERIAL_BLUE);
  myGLCD.fillRect(0, 226, 319, 239);
  printStatusOnTFT();
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);
  lastTouch = millis();
  delay(500);


  // RTC
  bool parse = false;
  bool config = false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }
  delay(200);
  if (parse && config) {
    Serial.print(F("DS1307 configured Time="));
    Serial.print(__TIME__);
    Serial.print(F(", Date="));
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println(F("DS1307 Communication Error :-{"));
    Serial.println(F("Please check your circuitry"));
  }

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println(F("Unable to sync with the RTC"));
  else
    Serial.println(F("RTC has set the system time"));
  getConfig();
  Serial.println(configuration);
  digitalClockDisplay();
  wifiController.begin();

  // 293x200
  // 293/4= 60+13 *4
  //

}

void voidGetTouch() {
  myTouch.read();
  if (myTouch.dataAvailable()) {
    //Serial.println("Data available");
    analogWrite(lcdBacklight, lcdBacklightBrightness);
    lastTouch = millis();
    touchY = myTouch.getX();
    touchX = myTouch.getY();


    //    Serial.print(x);
    //    Serial.print(",");
    //    Serial.println(y);
    if (touchX > -1 && touchY > -1 )
      boolean preResult = (yard.highLightButton(touchX, touchY)
                           || barn.highLightButton(touchX, touchY)
                           || sauna.highLightButton(touchX, touchY)
                           || washingRoom.highLightButton(touchX, touchY)
                           || firstFloor.highLightButton(touchX, touchY)
                           || secondFloor.highLightButton(touchX, touchY));




  } else {
    if (touchX > -1 && touchY > -1 && ((millis() - lastTouch) > 100) ) {
      boolean preResult = (yard.pushButton(touchX, touchY)
                           || barn.pushButton(touchX, touchY)
                           || sauna.pushButton(touchX, touchY)
                           || washingRoom.pushButton(touchX, touchY)
                           || firstFloor.pushButton(touchX, touchY)
                           || secondFloor.pushButton(touchX, touchY));
      touchX = -1;
      touchY = -1;
    }
  }

}


void loop() {
  //Serial.println("loop!" + String(millis()));
  wifiController.wifiFlasher.update();

  digitalClockDisplay();

  voidGetTouch();
  if ((millis() - lastTouch ) > touchTimeout )
    analogWrite(lcdBacklight, 0); // No touch, no LED in screen.
  printStatusOnTFT();
  command = String();

  // command = wifiController.getCommand();
  command.trim();
  WiFiOn = wifiController.connectedToWAN;
  ControllerOn = wifiController.connectedToController;

  if (0 < command.length()) {
    //    Serial.println("recieved command: [" + command + "] length(): " + String(command.length()) + " command.indexOf(\"getConfig\"):" + String( command.indexOf("getConfig")));
    if (-1 < command.indexOf("getConfig")) {
      getConfig();
      wifiController.putAnswer(configuration);
      //Serial.println(configuration);
      return;
    }
    if (-1 < command.indexOf("turnOn:")) {
      String result = switchCommand(command, SWITCH_ON);
      sprintf(configuration, "%s\n", result.c_str());
      wifiController.putAnswer(configuration);
      return;
    }
    if ( -1 < command.indexOf("turnOff:")) {
      String result = switchCommand(command, SWITCH_OFF);
      sprintf(configuration, "%s\n", result.c_str());
      wifiController.putAnswer(configuration);
      return;
    }
    //    if ( -1 < command.indexOf("long!")) {
    //
    //      wifiController.putAnswer(F("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ012345678\n"));
    //      return;
    //    }
    sprintf(configuration, "UNKNOWN COMMAND:%s\n", command.c_str());
    wifiController.putAnswer(configuration);

  }

}

String switchCommand(String command, boolean toState) {
  //  Serial.println("recieved command: [" + command + "] length(): " + String(command.length()) + " command.indexOf(\"getConfig\"):" + String( command.indexOf("getConfig")));
  String result = "FAULT";
  int32_t index1 = command.indexOf(":");
  int32_t index2 = command.indexOf("\n");
  if (0 < index1) {
    String uuid;
    if (0 > index2)
      uuid = command.substring(index1 + 1);
    else
      uuid = command.substring(index1 + 1, index2);

    //Serial.println("uuid:[" + uuid + "]");
    boolean preResult = (yard.setSwitch(uuid, toState)
                         || barn.setSwitch(uuid, toState)
                         || sauna.setSwitch(uuid, toState)
                         || washingRoom.setSwitch(uuid, toState)
                         || firstFloor.setSwitch(uuid, toState)
                         || secondFloor.setSwitch(uuid, toState));
    result = (preResult ? "OK:" : "FAULT:") + uuid + (toState ? ":ON\n" : ":OFF\n");
  }


  return result;
}

void printString(const char str[]) {
  char c;
  if (!str) return;
  while ((c = pgm_read_byte(str++)))
    Serial.write(c);
}

String copyToString (const char str[]) {
  char c;
  String result;
  if (str)
    while ((c = pgm_read_byte(str++)))
      result += c;

  return result;
}

int appendX(char (&str)[2400], int begin, String appendString) {
  int i;
  for (i = 0; i <= (appendString.length() - 1); i++) {
    str[i + begin] = appendString.c_str()[i];
  }
  return begin + i;
}

int getEOSposition(const char *array)
{
  int result = -1;
  for (int i = 0; i <= 2400; i++) {
    if (array[i] == '\0') {
      result = i;
      break;
    }

  }
  return result;
}



bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void digitalClockDisplay() {
  if (timeStatus() == timeSet) {
    // digital clock display of the time
    // 2016-04-10 22:26:34 20len
    sprintf(displayDateAndTime, "%04d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());
    myGLCD.setBackColor(MATERIAL_PURPLE);
    myGLCD.setColor(MATERIAL_WHITE);
    //    myGLCD.print("                                                                    ", 180 + TOP_STRING);
    //    myGLCD.print(displayDateAndTime, 160 + TOP_STRING);
    //    myGLCD.print("                                                                    ", 180 + TOP_STRING);
    myGLCD.print(displayDateAndTime, 160 + TOP_STRING);
  }
}


