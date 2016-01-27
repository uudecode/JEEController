#include <avr/pgmspace.h>
#include "UUIDable.h"
#include "Switch.h"
#ifndef LOCATION_H
#define LOCATION_H


class Location : public UUIDable
{

  public:

    Location( String locationUUIDx,  String locationNamex) :  locationName(locationNamex), locationUUID(locationUUIDx) {
    }

    Location(String locationName ) : Location(generateUUID(), locationName) {};


    int getConfig(char (&str)[3072], int begin, Switch *switches, int switchesSize, Sensor *sensors, int sensorsSize) {
      int nextPos = begin;
      nextPos = appendX(str, nextPos, F("\n\t\t<Location uuid=\""));
      nextPos = appendX(str, nextPos, this->locationUUID);
      nextPos = appendX(str, nextPos, F("\" name=\""));
      nextPos = appendX(str, nextPos, this->locationName);
      nextPos = appendX(str, nextPos, F("\">"));
      nextPos = getSwitchesConfig(str,nextPos,switches, switchesSize);
      nextPos = getSensorsConfig(str,nextPos,sensors, sensorsSize);
      nextPos = appendX(str, nextPos, F("\n\t\t</Location>"));
      return nextPos;
    }



    int getSwitchesConfig(char (&str)[3072], int begin, Switch *switches, int switchesSize) {
      int nextPos = begin;
      nextPos = appendX(str, nextPos, F("\n\t\t\t<Switches>"));

      for (int s = 0; s < switchesSize ; s++) {
        nextPos = switches[s].getConfig(str,nextPos);
      }
      nextPos = appendX(str, nextPos, F("\n\t\t\t</Switches>"));

      return nextPos;
    }
    
    int getSensorsConfig(char (&str)[3072], int begin, Sensor *sensors, int sensorsSize) {
      int nextPos = begin;
      nextPos = appendX(str, nextPos, F("\n\t\t\t<Sensors>"));

      for (int s = 0; s < sensorsSize ; s++) {
        nextPos = sensors[s].getConfig(str,nextPos);
      }
      nextPos = appendX(str, nextPos, F("\n\t\t\t</Sensors>"));

      return nextPos;
    }

    boolean setSwitch(Switch *switches, int switchesSize, String switchUUID, boolean toState) {
      boolean result = false;
      for (int s = 0; s < switchesSize ; s++) {
        //        Serial.println(" sw [" + switches[s].getSwitchUUID() + "] ft [" + switchUUID + "] equals?"  + (switchUUID.equals(switches[s].getSwitchUUID()) ? "YES" : "NO"));
        if ( (switchUUID.equals(switches[s].getSwitchUUID()))) {
          if (toState)
            switches[s].turnOn();
          else
            switches[s].turnOff();
          result = true;
          break;
        }
      }

      return result;
    }
  protected:
    String const locationUUID;
    String const locationName;


};


#endif

