#define DEBUG_ON


#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Sensors.h"
#include "Locations.h"



String HomesteadName = "Limbo";


Yard yard = Yard();
Barn barn = Barn();
Sauna sauna = Sauna();

String getConfig(){
  String result = "<Homestead name =\"";
  result += HomesteadName;
  result += "\">";
  result += "\n\t<Locations>";
  result += yard.getConfig();
  result += barn.getConfig();
  result += sauna.getConfig();
  result += "\n\t</Locations>";
  result += "\n</Homestead>";
  return result;
}

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Initializing " + HomesteadName);
  randomSeed(analogRead(0));
  String homesteadConfig = getConfig();
  Serial.println(homesteadConfig);


}

void loop() {

}

