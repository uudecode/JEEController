#ifndef MOCKSENSOR_H
#define MOCKSENSOR_H
//include classes Sensor and Debuggable
#include "Sensor.h"
#include "Debuggable.h"
class MockSensor : public Sensor {
  public:
    inline MockSensor( String sensorUUID, byte sensorPin, String sensorName ) : Sensor(sensorUUID, sensorPin, sensorName) {};
    inline MockSensor( byte sensorPin, String sensorName ) : Sensor(sensorPin, sensorName) {};
    inline MockSensor( byte sensorPin ) : Sensor(sensorPin) {};

    //avarage a temperature and return the avaraged sum
    int read() {
      float sum = random(-15, 15);
      for (byte i = 0; i < 10; i++) {
        sum += random(-15, 15);
      }
      return (int)(.5 + sum / 10.);
    }


};


#endif

