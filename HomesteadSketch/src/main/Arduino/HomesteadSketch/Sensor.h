#include "UUIDable.h"
#ifndef SENSOR_H
#define SENSOR_H

#define DHT_TIMEOUT 10000

enum  SensorType {LIGHT, THERMAL, GASCO, GASCO2, HUMIDITY, MOCK, DHT11_THERMAL, DHT11_HUMIDITY};
static char sensorConfiguration[128];

class Sensor :  public UUIDable {
  public:

    Sensor(String sensorUUID, SensorType sensorType, byte sensorPin, String sensorName ) {
      //debug("Sensor construct: " + sensorUUID + " PIN: " + sensorPin + " name: " + sensorName);
      this->sensorUUID = sensorUUID;
      this->sensorPin = sensorPin;
      this->sensorName = sensorName;
      this->sensorType = sensorType;
    }

    Sensor(String sensorUUID, SensorType sensorType, uint8_t sensorPin ) : Sensor(sensorUUID, sensorType, sensorPin, "n/a") {};


    String getSensorUUID() {
      return this->sensorUUID;
    }

    byte getSensorPin() {
      return this->sensorPin;
    }

    String getSensorName() {
      return this->sensorName;
    }

    //    int getConfig(char (&str)[2400], int begin) {
    //      //      sprintf(sensorConfiguration, "\n\t\t\t\t<Sensor uuid=\"%s\" name=\"%s\" pin=\"%s\" data=\"%s\"/>", this->sensorUUID.c_str(), this->sensorName.c_str(), String(this->sensorPin).c_str() , (this->read()).c_str());
    //      //      return appendX(str, begin,sensorConfiguration);
    //      return begin;
    //    }

    int getConfig(char (&str)[2400], int begin) {
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
          break;
        case DHT11_THERMAL:
          delay(800);
          DHTrv = DHTRead(sensorPin);
          if (DHTrv != 0) return "Error 1";
          // CONVERT AND STORE
          DHTtemperature = DHTbits[2];  // bits[3] == 0;
          DHThumidity    = DHTbits[0];  // bit[1] == 0;
          DHTsum = DHTbits[0] + DHTbits[2]; // DHTbits[1] && DHTbits[3] both 0
          if (DHTbits[4] != DHTsum) return "Error 2";
          result = String(DHTtemperature) + "°C";
          break;
        case DHT11_HUMIDITY:
          delay(800);
          DHTrv = DHTRead(sensorPin);
          if (DHTrv != 0) return "Error 3";
          // CONVERT AND STORE
          DHTtemperature = DHTbits[2];  // bits[3] == 0;
          DHThumidity    = DHTbits[0];  // bit[1] == 0;
          DHTsum = DHTbits[0] + DHTbits[2]; // DHTbits[1] && DHTbits[3] both 0
          if (DHTbits[4] != DHTsum) return "Error 4";
          result = String(DHThumidity) + "%";
          break;
      }
      return result;
    }

  protected:
    String sensorUUID;
    uint8_t sensorPin;
    String sensorName;
    SensorType sensorType;

  private:
    uint8_t DHTbits[5];  // buffer to receive data
    uint8_t DHTsum;
    int DHTrv;
    double DHThumidity;
    double DHTtemperature;

    // return values:
    //  0 : OK
    // -2 : timeout
    int DHTRead(uint8_t pin)
    {
      // INIT BUFFERVAR TO RECEIVE DATA
      uint8_t cnt = 7;
      uint8_t idx = 0;

      // EMPTY BUFFER
      for (int i = 0; i < 5; i++) DHTbits[i] = 0;

      // REQUEST SAMPLE
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      delay(20);
      digitalWrite(pin, HIGH);
      delayMicroseconds(40);
      pinMode(pin, INPUT);

      // GET ACKNOWLEDGE or TIMEOUT
      unsigned int loopCnt = DHT_TIMEOUT;
      while (digitalRead(pin) == LOW)
        if (loopCnt-- == 0) return -2;

      loopCnt = DHT_TIMEOUT;
      while (digitalRead(pin) == HIGH)
        if (loopCnt-- == 0) return -2;

      // READ THE OUTPUT - 40 BITS => 5 BYTES
      for (int i = 0; i < 40; i++)
      {
        loopCnt = DHT_TIMEOUT;
        while (digitalRead(pin) == LOW)
          if (loopCnt-- == 0) return -2;

        unsigned long t = micros();

        loopCnt = DHT_TIMEOUT;
        while (digitalRead(pin) == HIGH)
          if (loopCnt-- == 0) return -2;

        if ((micros() - t) > 40) DHTbits[idx] |= (1 << cnt);
        if (cnt == 0)   // next byte?
        {
          cnt = 7;
          idx++;
        }
        else cnt--;
      }

      return 0;
    }

};
#endif

