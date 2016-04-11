#define DEBUG_ON


#include <avr/pgmspace.h>
#include<HardwareSerial.h>
#include "ESP8266.h"
#include "Debuggable.h"
#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H


#define FLASHER_PIN 42

const char ssid_0[] PROGMEM = "TRAK.SPB.RU";
const char pass_0[] PROGMEM = "l7tx-zs2i-l1rd";
const char ssid_1[] PROGMEM = "CENTER.TRAK.SPB.RU";
const char pass_1[] PROGMEM = "l7tx-zs2i-l1rd";
const char ssid_2[] PROGMEM = "PERI.TRAK.SPB.RU";
const char pass_2[] PROGMEM = "l7tx-zs2i-l1rd";

const char* const ssids[] PROGMEM = {ssid_0, pass_0, ssid_1, pass_1, ssid_2, pass_2};
ESP8266 wifi (Serial1);



const long repeatConnectTimeOut = 6000;
class WiFiController : public Debuggable {

  public:
    Flasher wifiFlasher = Flasher(FLASHER_PIN, 2000, 2000);
    boolean connectedToWAN = false;
    boolean connectedToController = false;
    char networkName[30];
    String controllerAdress;
    long controllerPort;
    long lastTryConnectToWIFI = 0;
    String lastCommand;



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
        Serial.print(F("ESP8266 look's dead :( \r\n"));
        begin();
      }

      checkConnect();
      if (connectedToController) {
        uint8_t buffer[128] = {0};
        uint32_t len = wifi.recv(buffer, sizeof(buffer), 300);
        String command;
        if (len > 0) {
          for (uint32_t i = 0; i < len; i++) {
            command += (char)buffer[i];
          }
          Serial.println(command);
          lastCommand = command;

        }
        return command;
      }
      return "";
    }

    void putAnswer(char (&answer)[2400]) {
      int sendSize = 0;
      int answerLength = getEOSposition(answer);

      int sendBufferSize = sizeof(sendBuffer);
      int iterations = (1 + ((answerLength - 1) / sendBufferSize));
      if (0 == (answerLength % sendBufferSize))
        iterations += 1;
      for (int i = 0; i < sendBufferSize; i++)
        sendBuffer[i] = '\0';


      //      Serial.println("answerLength=[" + String(answerLength) + F("] sendBufferSize=[") + String(sendBufferSize) + F("] iterations: ") + String(iterations));
      //      Serial.println(F("---"));
      //      for (int z = 0; z < answerLength; z++) {
      //        Serial.print(answer[z]);
      //      }
      //      Serial.println(F("---"));

      for (int x = 0; x < iterations  ; x++) {
        if (x < (iterations - 1))
          sendSize = sendBufferSize;
        else
          sendSize = (answerLength % sendBufferSize);

        for (int z = 0 ; z < sendSize ; z++) {
          sendBuffer[z] = answer[z + (x * sendBufferSize)];
        }
        //      Serial.println(F("--+--"));
        // Serial.println(sendBuffer);
        //  for (int z = 0; z < sendSize; z++) {
        //      Serial.print(sendBuffer[z]);
        //      }
        //        Serial.println(F("--+--"));
        //        Serial.println("Iteration: " + String(x) + " answerLength % sendBufferSize: [" + String(answerLength % sendBufferSize) + "] answerLength: [" + String (answerLength) + "] sendBufferSize: [" + String(sendBufferSize) + "]");
        //        Serial.println("sendSize: " + String(sendSize));
        if (0 < sendSize) {
          wifi.send((const uint8_t*)sendBuffer, sendSize);
        }
      }


    }


  private:
    char networkPassword[20];
    char sendBuffer[64];



    void checkConnect() {
      String IPStatus = wifi.getIPStatus();

      //      Serial.println(IPStatus);
      //releaseTCP
      if (!(-1 == IPStatus.indexOf("STATUS:4"))) {
        wifi.releaseTCP();
      }
      if (-1 == (IPStatus.indexOf("CIPSTATUS:0,\"TCP\"")) ) {
        Serial.println(F("No connect to controller."));
        wifiFlasher.setTimes(1000, 1000);
        String wifiLocalIP = wifi.getLocalIP();
        //        Serial.print("wifiLocalIP=");
        //        Serial.println(wifiLocalIP);
        if (wifiLocalIP.equals("\"0.0.0.0\"")) {
          wifiFlasher.setTimes(2000, 2000);
          //                  Serial.print(" millis() - lastTryConnectToWIFI=");
          //        Serial.println(String( millis() - lastTryConnectToWIFI));

          //debug(F("Need connect to wifi, check timeout"));
          if (( millis() - lastTryConnectToWIFI ) > repeatConnectTimeOut) {
            debug(F("Timeout reach, try connect to WIFI"));
            lastTryConnectToWIFI = millis();
            connectedToWAN = tryConnectToWAN();
          }
        }
        else {
          //          debug(F("Not need connect to wifi"));
          connectedToWAN = true;
        }

        if (connectedToWAN)
        {
          connectedToController = tryConnectToController();
        } else {
          //Serial.println(F("No connect to controller!"));
        }
      } //else debug("Connect to controller alredy exists.");

    }


    boolean tryConnectToController() {
      boolean isConnected = false;
      for (int attempts = 3; attempts > 0 ; attempts --) {
        if (wifi.createTCP(controllerAdress, controllerPort)) {
          isConnected = true;
          wifiFlasher.setTimes(10000, 0);

        }
      }
      debug(isConnected ? F("Connected to controller") : F("No controller connection") );
      return isConnected;
    }

    boolean tryConnectToWAN() {
      boolean isConnected = false;
      for ( int i = 0 ; (i < (sizeof(ssids) / sizeof(*ssids)) && !isConnected) ; i += 2) {

        strcpy_P(networkName, (char*)pgm_read_word(&(ssids[i])));
        strcpy_P(networkPassword, (char*)pgm_read_word(&(ssids[i + 1])));
        int attempts = 3;
        Serial.println(networkName);
      //  for (int j = 0 ; j < attempts ; j++)
          if (!wifi.joinAP(networkName, networkPassword) ) {
            wifi.restart();
            wifi.disableMUX();
            delay(100);
          } else {
            isConnected = true;
            break;
          }
      }
      Serial.println(isConnected ? F("Connected to WAN") : F("No WAN connection"));
      debug(isConnected ? F("Connected to WAN") : F("No WAN connection") );
      return isConnected;
    };

    int getEOSposition(const char *array)
    {
      int result = -1;
      for (int i = 0; i <= 2400; i++) {
        if (array[i] == '\0') {
          result = i;
          break;
        }

      }
      return result;
    }
};



#endif
