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



WiFiController *wifiController = new WiFiController("93.100.131.244", 37001);
const char homesteadName[] PROGMEM = "Дача";

Yard *yard = new Yard();
Barn *barn = new Barn();
Sauna *sauna = new Sauna();
WashingRoom *washingRoom = new WashingRoom();
char configuration[2048];

void getConfig() {
//  sprintf(configuration,"<Homestead name =\"%s\">\n\t<Locations>\n\t</Locations>\n</Homestead>\n",copyToString(homesteadName).c_str());
  sprintf(configuration,"<Homestead name =\"%s\">\n\t<Locations>%s%s%s%s\n\t</Locations>\n</Homestead>\n",copyToString(homesteadName).c_str(),(yard->getConfig()).c_str(),(barn->getConfig()).c_str(),(sauna->getConfig()).c_str(), (washingRoom->getConfig()).c_str() );
}

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing " + copyToString(homesteadName));
  randomSeed(analogRead(0));
  getConfig();
  Serial.println(configuration);
  wifiController->begin();
}

void loop() {
  String command;
  command = wifiController->getCommand();
  if (0 < command.length()) {
    Serial.println("recieved command: [" + command + "] length(): " + String(command.length()) + " command.indexOf(\"getConfig\"):" + String( command.indexOf("getConfig")));
    if (-1 < command.indexOf("getConfig")) {
      getConfig();
      wifiController->putAnswer(configuration);
      Serial.println(configuration);
      return;
    }
    if (-1 < command.indexOf("turnOn:")) {
      boolean result = switchCommand(command, SWITCH_ON);
      wifiController->putAnswer(result ? "OK\n" : "FAULT\n");
      return;
    }
    if ( -1 < command.indexOf("turnOff:")) {
      boolean result = switchCommand(command, SWITCH_OFF);
      wifiController->putAnswer(result ? "OK\n" : "FAULT\n");
      return;
    }
    if ( -1 < command.indexOf("long!")) {

      wifiController->putAnswer(F("abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ012345678\n"));
      return;
    }
    wifiController->putAnswer("UNKNOWN COMMAND:" + command + "\n");
  }

}

boolean switchCommand(String command, boolean toState) {
  boolean result = false;
  Serial.println("recieved command: [" + command + "] length(): " + String(command.length()) + " command.indexOf(\"getConfig\"):" + String( command.indexOf("getConfig")));
  int32_t index1 = command.indexOf(":");
  int32_t index2 = command.indexOf("\n");
  if (0 < index1) {
    String uuid;
    if (0 > index2)
      uuid = command.substring(index1 + 1);
    else
      uuid = command.substring(index1 + 1, index2);

    Serial.println("uuid:[" + uuid + "]");
    result = (yard->setSwitch(uuid, toState)
              || barn->setSwitch(uuid, toState)
              || sauna->setSwitch(uuid, toState)
              || washingRoom->setSwitch(uuid, toState) );
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

