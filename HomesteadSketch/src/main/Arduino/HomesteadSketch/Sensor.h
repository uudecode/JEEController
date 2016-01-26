#include "UUIDable.h"
#ifndef SENSOR_H
#define SENSOR_H


enum  SensorType {LIGHT, THERMAL, GASCO, GASCO2, HUMIDITY, MOCK};

class Sensor :  public UUIDable {
  public:

    Sensor( SensorType sensorType, String sensorUUID, byte sensorPin, String sensorName ) {
      //debug("Sensor construct: " + sensorUUID + " PIN: " + sensorPin + " name: " + sensorName);
      this->sensorUUID = sensorUUID;
      this->sensorPin = sensorPin;
      this->sensorName = sensorName;
      this->sensorType = sensorType;
    }

    Sensor( SensorType sensorType, byte sensorPin, String sensorName ) : Sensor(sensorType, generateUUID(), sensorPin, sensorName) {};

    Sensor( SensorType sensorType, byte sensorPin ) : Sensor(sensorType, sensorPin, "n/a") {};


    String getSensorUUID() {
      return this->sensorUUID;
    }

    byte getSensorPin() {
      return this->sensorPin;
    }

    String getSensorName() {
      return this->sensorName;
    }



    String getConfig() {
      String result = "\n\t\t\t\t<Sensor uuid=\"" ;
      result += this->sensorUUID;
      result += "\"" ;
      result += " name=\"" ;
      result += this->sensorName;
      result += "\"" ;
      result += " pin=\"" ;
      result += this->sensorPin;
      result += "\"" ;
      result += " pin=\"" ;
      result += this->read();
      result += "\"" ;
      result += "/>";
      return result  ;
    }

    String read() {
      String result;
      switch (this->sensorType) {
        case LIGHT:
          result = "30 лк";
          break;
        case THERMAL:
          result = "20 °C";
          break;
        case GASCO:
          result = "0.001%";
          break;
        case GASCO2:
          result = "0.002%";
          break;
        case HUMIDITY:
          result = "30%";
          break;
        case MOCK:
          result = "38 попугаев";
      }
      return result;
    }

  protected:
    String sensorUUID;
    byte sensorPin;
    String sensorName;
    SensorType sensorType;

};
#endif

