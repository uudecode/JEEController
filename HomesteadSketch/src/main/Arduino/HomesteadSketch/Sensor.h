#include "UUIDable.h"
#ifndef SENSOR_H
#define SENSOR_H
//abstract class Sensor
class Sensor :  public UUIDable {
  public:

    inline Sensor( String sensorUUID, byte sensorPin, String sensorName ) {
      //debug("Sensor construct: " + sensorUUID + " PIN: " + sensorPin + " name: " + sensorName);
      this->sensorUUID = sensorUUID;
      this->sensorPin = sensorPin;
      this->sensorName = sensorName;
    }

    inline Sensor( byte sensorPin, String sensorName ) : Sensor(generateUUID(), sensorPin, sensorName) {};

    inline Sensor( byte sensorPin ) : Sensor(sensorPin, "n/a") {};

    
    inline String getSensorUUID(){
      return this->sensorUUID;
    }

    inline byte getSensorPin(){
      return this->sensorPin;
    }
    
    inline String getSensorName(){
      return this->sensorName;
    }
    
    String getConfig() {
      String result = "\n\t\t\t\t<Sensor";
      result += " uuid=\"" ;
      result += this->getSensorUUID();
      result += "\"" ;
      result += " name=\"" ;
      result += this->getSensorName();
      result += "\"" ;
      result += " pin=\"" ;
      result += this->getSensorPin();
      result += "\"" ;
      result += "/>";
      return result  ;
    }

  protected:
    String sensorUUID;
    byte sensorPin;
    String sensorName;

};
#endif

