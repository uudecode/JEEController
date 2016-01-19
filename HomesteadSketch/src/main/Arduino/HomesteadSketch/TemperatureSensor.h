#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H
//include classes Sensor and Debuggable
#include "Sensor.h"
#include "Debuggable.h"
class TemperatureSensor : public Sensor {
  public:
    inline TemperatureSensor( String sensorUUID, byte sensorPin, String sensorName ) : Sensor(sensorUUID, sensorPin, sensorName) {};
    inline TemperatureSensor( byte sensorPin, String sensorName ) : Sensor(sensorPin, sensorName) {};
    inline TemperatureSensor( byte sensorPin ) : Sensor(sensorPin) {};

    //avarage a temperature and return the avaraged sum
    int read() {
      //TODO - implement arithmetic so that we return a degree celcius/farenheit

      float sum = analogRead(sensorPin);
      for (byte i = 0; i < 10; i++) {
        sum = analogRead(sensorPin);
      }
      return (int)(.5 + sum / 10.);
    }
};



#endif

