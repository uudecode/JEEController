#define DEBUG_ON


#include <avr/pgmspace.h>
#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Sensor.h"
#include "Locations.h"
#include "WiFiController.h"

#ifndef SWITCH_OFF
#define SWITCH_OFF false
#endif
#ifndef SWITCH_ON
#define SWITCH_ON true
#endif



WiFiController wifiController = WiFiController("93.100.131.244", 37001);


const char homesteadName[] PROGMEM = "Дача";


Yard yard =  Yard();
Barn barn =  Barn();
Sauna sauna =  Sauna();
WashingRoom washingRoom =  WashingRoom();
FirstFloor firstFloor =  FirstFloor();
SecondFloor secondFloor =  SecondFloor();
char configuration[3072];
int nextPosition;

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
  Serial.println("In getConfig() nextPosition is:" + String(nextPosition));

}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing " + copyToString(homesteadName));
  randomSeed(analogRead(0));
  getConfig();
  Serial.println(configuration);
  wifiController.begin();

}

void loop() {
  wifiController.wifiFlasher.update();
  String command;
  command = wifiController.getCommand();
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

    Serial.println("uuid:[" + uuid + "]");
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

int appendX(char (&str)[3072], int begin, String appendString) {
  int i;
  for (i = 0; i <= (appendString.length() - 1); i++) {
    str[i + begin] = appendString.c_str()[i];
  }
  return begin + i;
}

int getEOSposition(const char *array)
{
  int result = -1;
  for (int i = 0; i <= 3072; i++) {
    if (array[i] == '\0') {
      result = i;
      break;
    }

  }
  return result;
}

