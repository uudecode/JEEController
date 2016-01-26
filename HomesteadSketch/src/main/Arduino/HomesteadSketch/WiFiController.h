#define DEBUG_ON


#include <avr/pgmspace.h>
#include<HardwareSerial.h>
#include "ESP8266.h"
#include "Debuggable.h"
#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

const char ssid_0[] PROGMEM = "SBT";
const char pass_0[] PROGMEM = "sbertech123456";
const char ssid_1[] PROGMEM = "TRAK.SPB.RU";
const char pass_1[] PROGMEM = "l7tx-zs2i-l1rd";
const char ssid_2[] PROGMEM = "CENTER.TRAK.SPB.RU";
const char pass_2[] PROGMEM = "l7tx-zs2i-l1rd";
const char ssid_3[] PROGMEM = "PERI.TRAK.SPB.RU";
const char pass_3[] PROGMEM = "l7tx-zs2i-l1rd";

const char* const ssids[] PROGMEM = {ssid_0, pass_0, ssid_1, pass_1, ssid_2, pass_2, ssid_3, pass_3};
ESP8266 wifi (Serial1);

class WiFiController : public Debuggable {

  public:
    WiFiController(String controllerAdress, uint32_t controllerPort) {
      this->controllerAdress = controllerAdress;
      this->controllerPort = controllerPort;
    };
    void begin() {
      Serial1.begin(115200);
      wifi.restart();
      wifi.disableMUX();
      checkConnect();
    };

    String getCommand () {
      if (!wifi.kick()) {
        Serial.print("ESP8266 look's dead :( \r\n");
        begin();
      }

      checkConnect();
      uint8_t buffer[128] = {0};
      uint32_t len = wifi.recv(buffer, sizeof(buffer), 1000);
      String command;

      if (len > 0) {
        for (uint32_t i = 0; i < len; i++) {
          command += (char)buffer[i];
        }
      }
      return command;
    }

    void putAnswer(String const &answer) {
      int sendSize = 0;
      int answerLength = answer.length();
      int sendBufferSize = sizeof(sendBuffer);
      int iterations = (1 + ((answerLength - 1) / sendBufferSize));
      if (0 == (answerLength % sendBufferSize))
        iterations += 1;

      Serial.println("answer=[" + answer + "] answerLength=[" + String(answerLength) + "] sendBufferSize=[" + String(sendBufferSize) + "] iterations: " + String(iterations));

      for (int x = 0; x < iterations  ; x++) {
        (answer.substring(x * sendBufferSize, (x * sendBufferSize) + sendBufferSize )).toCharArray(sendBuffer, sendBufferSize + 1);
        //Serial.print(answer.substring(x * sendBufferSize, (x * sendBufferSize) + sendBufferSize ));
        //        Serial.println(sendBuffer);
        Serial.println("Iteration: " + String(x) + " answerLength % sendBufferSize: [" + String(answerLength % sendBufferSize) + "] answerLength: [" + String (answerLength) + "] sendBufferSize: [" + String(sendBufferSize) + "]");

        if (x < (iterations - 1))
          sendSize = sendBufferSize;
        else
          sendSize = (answerLength % sendBufferSize);


        Serial.println("sendSize: " + String(sendSize));
        if (0 < sendSize) {
          wifi.send((const uint8_t*)sendBuffer, sendSize);
        }
      }

 
    }
  private:
    String controllerAdress;
    long controllerPort;
    boolean connectedToWAN = false;
    boolean connectedToController = false;
    char networkName[30];
    char networkPassword[20];
    char command[64];
    char sendBuffer[256];



    void checkConnect() {
      if (-1 == (wifi.getIPStatus().indexOf("CIPSTATUS:0,\"TCP\"")) ) {
        Serial.println(F("No connect to controller."));
        //        debug(wifi.getLocalIP());
        if ((wifi.getLocalIP()).equals("\"0.0.0.0\"")) {
          //          debug(F("Need connect to wifi"));
          connectedToWAN = tryConnectToWAN();
        }
        else {
          //          debug(F("Not need connect to wifi"));
          connectedToWAN = true;
        }

        if (connectedToWAN)
        {
          connectedToController = tryConnectToController();
        } else {
          Serial.println(F("No connect to controller!"));
        }
      } //else debug("Connect to controller alredy exists.");

    }


    boolean tryConnectToController() {
      boolean isConnected = false;
      for (int attempts = 3; attempts > 0 ; attempts --) {
        if (wifi.createTCP(controllerAdress, controllerPort)) {
          isConnected = true;
        }
      }
      debug(isConnected ? "Connected to controller" : "No controller connection" );
      return isConnected;
    }

    boolean tryConnectToWAN() { // 3 times to every net.
      boolean isConnected = false;
      String listAp = wifi.getAPList();
      for ( int i = 0 ; (i < (sizeof(ssids) / sizeof(*ssids)) && !isConnected) ; i += 2) {

        strcpy_P(networkName, (char*)pgm_read_word(&(ssids[i])));
        strcpy_P(networkPassword, (char*)pgm_read_word(&(ssids[i + 1])));
        int attempts = 3;

        for (int attempts = 3; attempts > 0 ; attempts --) {
          if (0 < listAp.indexOf("\"" + String(networkName) + "\""))
            if (!wifi.joinAP(networkName, networkPassword) ) {
              delay(100);
            } else {
              isConnected = true;
              break;
            }
        }
      }
      debug(isConnected ? "Connected to WAN" : "No WAN connection" );
      return isConnected;
    };
};


#endif
