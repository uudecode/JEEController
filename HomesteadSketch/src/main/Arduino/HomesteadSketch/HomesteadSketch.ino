#define DEBUG_ON


#include <avr/pgmspace.h>
#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Sensors.h"
#include "Locations.h"
#include "WiFiController.h"



const char homesteadName[] PROGMEM = "Дача";

Yard yard = Yard();
Barn barn = Barn();
Sauna sauna = Sauna();
WashingRoom washingRoom = WashingRoom();
WiFiController wifiController = WiFiController("93.100.131.244",37002);

//const char string_0[] PROGMEM = "long long long long long long long long long long long long String 0";

String getConfig() {
  String result = F("<Homestead name =\"");
  result += copyToString(homesteadName);
  result += "\">";
  result += F("\n\t<Locations>");
  result += yard.getConfig();
  result += barn.getConfig();
  result += sauna.getConfig();
  result += washingRoom.getConfig();
  result += F("\n\t</Locations>");
  result += F("\n</Homestead>");
  return result;
}

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("Initializing " + copyToString(homesteadName));
  randomSeed(analogRead(0));
  String homesteadConfig = getConfig();
  Serial.println(homesteadConfig);
  wifiController.begin();
  //  Serial.println(copyToString(string_0));
  //  printString(string_0);
  //  Serial.println("\n");
}

void loop() {

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

