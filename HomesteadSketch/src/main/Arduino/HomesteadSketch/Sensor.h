#include "UUIDable.h"
#ifndef SENSOR_H
#define SENSOR_H


enum  SensorType {LIGHT, THERMAL, GASCO, GASCO2, HUMIDITY, MOCK};
static char sensorConfiguration[128];

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

//    int getConfig(char (&str)[3072], int begin) {
//      //      sprintf(sensorConfiguration, "\n\t\t\t\t<Sensor uuid=\"%s\" name=\"%s\" pin=\"%s\" data=\"%s\"/>", this->sensorUUID.c_str(), this->sensorName.c_str(), String(this->sensorPin).c_str() , (this->read()).c_str());
//      //      return appendX(str, begin,sensorConfiguration);
//      return begin;
//    }

    int getConfig(char (&str)[3072], int begin) {
      int nextPos = begin;
      nextPos = appendX(str, nextPos, "\n\t\t\t\t<Sensor uuid=\"");
      nextPos = appendX(str, nextPos, this->sensorUUID);
      nextPos = appendX(str, nextPos, F("\" name=\""));
      nextPos = appendX(str, nextPos, this->sensorName);
      nextPos = appendX(str, nextPos, F("\" pin=\""));
      nextPos = appendX(str, nextPos, String(this->sensorPin));
      nextPos = appendX(str, nextPos, F("\" data=\""));
      nextPos = appendX(str, nextPos, this->read());
      nextPos = appendX(str, nextPos, F("\"/>"));

      return nextPos;

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

