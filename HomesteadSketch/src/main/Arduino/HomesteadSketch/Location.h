#include "UUIDable.h"
#include "Switch.h"
#ifndef LOCATION_H
#define LOCATION_H
//abstract class Location
class Location : public UUIDable
{

  public:

    inline Location( String locationUUID,  String locationName ) {
      //debug("Location construct: " + locationUUID  + " name: " + locationName);
      this->locationUUID = locationUUID;
      this->locationName = locationName;
    }

    inline Location(String locationName ) : Location(generateUUID(), locationName) {};

    inline Location() : Location("n/a") {};


    inline String getLocationUUID() {
      return this->locationUUID;
    }


    inline String getLocationName() {
      return this->locationName;
    }

    String getConfig(Switch *switches,int switchesSize,Sensor *sensors,int sensorsSize) {
      String result = "\n\t\t<Location";
      result += " uuid=\"" ;
      result += this->getLocationUUID();
      result += "\"" ;
      result += " name=\"" ;
      result += this->getLocationName();
      result += "\"" ;
      result += ">";
      result += getSwitchesConfig(switches,switchesSize);
      result += getSensorsConfig(sensors,sensorsSize);
      result += "\n\t\t</Location>";
      return result  ;
    }


    String getSwitchesConfig(Switch *switches,int switchesSize) {
      String result = "\n\t\t\t<Switches>";

      for (int s = 0; s < switchesSize ; s++) {
        result += switches[s].getConfig();
      }
      result += "\n\t\t\t</Switches>";
      return result;
    }

    String getSensorsConfig(Sensor *sensors,int sensorsSize) {
      String result = "\n\t\t\t<Sensors>";

      for (int s = 0; s < sensorsSize ; s++) {
        result += sensors[s].getConfig();
      }
      result += "\n\t\t\t</Sensors>";
      return result;
    }
    
  protected:
    String locationName;
    String locationUUID;


};


#endif

