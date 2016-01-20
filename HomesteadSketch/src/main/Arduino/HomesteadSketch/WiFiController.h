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
      wifi.disableMUX();
      checkConnect();
      Serial.println("close connect!");
      delay(10000);
      checkConnect();
      delay(10000);
      checkConnect();

    };

    String getCommand () {
      String command;
      checkConnect();
      //      if(wifi.waitResponse()){
      //      onDataReceive(controllerConnection.getId(),command,);
      //
      //      } else
      //      debug("no command from controller");
      return command;
    }

    void putAnswer(String answer) {

    }
  private:
    String controllerAdress;
    long controllerPort;
    boolean connectedToWAN = false;
    boolean connectedToController = false;
    char networkName[30];
    char networkPassword[20];
    char command[200];

    void checkConnect() {
//      Serial.println("wifi.getIPStatus(): [" + wifi.getIPStatus()+"] wifi.getIPStatus().length(): " + String(wifi.getIPStatus().length()));
//      tryConnectToWAN();
//      Serial.println("wifi.getIPStatus(): [" + wifi.getIPStatus()+"] wifi.getIPStatus().length(): " + String(wifi.getIPStatus().length()));
//      tryConnectToController();
//      Serial.println("wifi.getIPStatus(): [" + wifi.getIPStatus()+"] wifi.getIPStatus().length(): " + String(wifi.getIPStatus().length()));
      
      if (0 == (wifi.getIPStatus().length()) ) {
        debug("No connect to controller.");
        if ((wifi.getLocalIP()).equals("\"0.0.0.0\"")) {
          debug("Need connect to wifi");
          connectedToWAN = tryConnectToWAN();
        }
        else {
          debug(" Not need connect to wifi");
          connectedToWAN = true;
        }

        if (connectedToWAN)
        {
          connectedToController = tryConnectToController();
        } else {
          debug("No connect to controller!");
        }
      } else debug("Connect to controller alredy exists.");

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
      for ( int i = 0 ; (i < (sizeof(ssids) / sizeof(*ssids)) && !isConnected) ; i += 2) {

        strcpy_P(networkName, (char*)pgm_read_word(&(ssids[i])));
        strcpy_P(networkPassword, (char*)pgm_read_word(&(ssids[i + 1])));
        int attempts = 3;

        for (int attempts = 3; attempts > 0 ; attempts --) {
          if (!wifi.joinAP(networkName, networkPassword) ) {
            delay(1000);
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
