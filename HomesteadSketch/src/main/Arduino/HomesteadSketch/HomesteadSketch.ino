#define DEBUG_ON


#include <avr/pgmspace.h>
#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Sensors.h"
#include "Locations.h"
#include "WiFiController.h"

#ifndef SWITCH_OFF
#define SWITCH_OFF false
#endif
#ifndef SWITCH_ON
#define SWITCH_ON true
#endif



WiFiController *wifiController = new WiFiController("93.100.131.244", 37001);

Yard yard = Yard();
Barn barn = Barn();
Sauna sauna = Sauna();
WashingRoom washingRoom = WashingRoom();
const char homesteadName[] PROGMEM = "Дача";


String getConfig() {
  String result = "<Homestead name =\"";
  result += copyToString(homesteadName);
  result += "\">";
  result += "\n\t<Locations>";
  result += yard.getConfig();
  result += barn.getConfig();
  result += sauna.getConfig();
  result += washingRoom.getConfig();
  result += "\n\t</Locations>";
  result += "\n</Homestead>\n";
  return result;
}

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("Initializing " + copyToString(homesteadName));

  //  char sendBuffer[64];
  //  Serial.println("sizeof(sendBuffer): " + String(sizeof(sendBuffer)) + " ceil??(73/sizeof(sendBuffer)):" + (1 + ((73 - 1) / sizeof(sendBuffer))) );

  randomSeed(analogRead(0));
  String homesteadConfig = getConfig();
  Serial.println(homesteadConfig);
  wifiController->begin();
}

void loop() {
  String command;
  command = wifiController->getCommand();
  if (0 < command.length()) {
    Serial.println("recieved command: [" + command + "] length(): " + String(command.length()) + " command.indexOf(\"getConfig\"):" + String( command.indexOf("getConfig")));
    if (-1 < command.indexOf("getConfig")) {
      String conf = getConfig();
      Serial.println("conf.length()" + String(conf.length()));
      wifiController->putAnswer(conf);
      Serial.println(conf);
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
    result = (yard.setSwitch(uuid, toState)
              || barn.setSwitch(uuid, toState)
              || sauna.setSwitch(uuid, toState)
              || washingRoom.setSwitch(uuid, toState) );
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

