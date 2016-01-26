#include <avr/pgmspace.h>
#include "UUIDable.h"
#include "Switch.h"
#ifndef LOCATION_H
#define LOCATION_H
//abstract class Location

char locationConfiguration[1024];

class Location : public UUIDable
{

  public:

    Location( String locationUUIDx,  String locationNamex) :  locationName(locationNamex), locationUUID(locationUUIDx) {
    }

    Location(String locationName ) : Location(generateUUID(), locationName) {};

    String getConfig(Switch *switches, int switchesSize, Sensor *sensors, int sensorsSize) {
      sprintf(locationConfiguration, "\n\t\t<Location uuid=\"%s\" name=\"%s\" %s %s \n\t\t</Location>", this->locationUUID.c_str(), this->locationName.c_str(), getSwitchesConfig(switches, switchesSize).c_str(), getSensorsConfig(sensors, sensorsSize).c_str());
      //      String result = "\n\t\t<Location uuid=\"" ;
      //      result += this->locationUUID;
      //      result += "\" name=\"";
      //      result += this->locationName;
      //      result += "\">";
      //      result += getSwitchesConfig(switches, switchesSize);
      //      result += getSensorsConfig(sensors, sensorsSize);
      //      result += "\n\t\t</Location>";
      //
      //      return result  ;
      return locationConfiguration;
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

    String getSwitchesConfig(Switch *switches, int switchesSize) {
      va_list ap;
      String result = "\n\t\t\t<Switches>";

      for (int s = 0; s < switchesSize ; s++) {
        result += switches[s].getConfig();
      }
      result += "\n\t\t\t</Switches>";
      Serial.println(result);
      return result;
    }

    String getSensorsConfig(Sensor *sensors, int sensorsSize) {
      String result = "\n\t\t\t<Sensors>";

      for (int s = 0; s < sensorsSize ; s++) {
        result += sensors[s].getConfig();
      }
      result += "\n\t\t\t</Sensors>";
      Serial.println(result);
      return result;
    }

  protected:
    String const locationUUID;
    String const locationName;


};


#endif

