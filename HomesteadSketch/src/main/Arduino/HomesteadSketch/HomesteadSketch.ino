#define DEBUG_ON


#include "Flasher.h"
#include "UUIDable.h"
#include "Debuggable.h"
#include "Sensors.h"
#include "Locations.h"



String HomesteadName = "Limbo";

//Locations: locations[1] = {};
Yard yard = Yard();

//Sensor *s, *s2, *l1, *currSensor;
//SensorsStorage *ss;

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Initializing " + HomesteadName);
  randomSeed(analogRead(0));
//  s = new TemperatureSensor(42, "Temperature in Sauna");
//  s2 = new TemperatureSensor(43, "Temperature in First floor room");
//  l1 = new LightSensor(45, "Illumination at outdoor");
//  ss = new SensorsStorage();
//  ss->put(s);
//  ss->put(s2);
//  ss->put(l1);
//  currSensor = ss->getSensor(0);
//  Serial.println(ss->getSensor(0)->getSensorName());
//  Serial.println(ss->getSensor(1)->getSensorName());
//  Serial.println(ss->getSensor(2)->getSensorName());
Serial.println(yard.getConfig());

  
}

void loop() {

}

