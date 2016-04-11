#ifndef LOCATION_H
#define LOCATION_H

#include "Arduino.h"
#include <avr/pgmspace.h>
#include "UUIDable.h"
#include "Switch.h"
#include "Sensor.h"

class Location : public UUIDable
{

  public:

    Location( String locationUUIDx,  String locationNamex);

    Location(String locationName ) : Location(generateUUID(), locationName) {};

    int getConfig(char (&str)[2400], int begin, Switch *switches, int switchesSize, Sensor *sensors, int sensorsSize);

    int getSwitchesConfig(char (&str)[2400], int begin, Switch *switches, int switchesSize);

    int getSensorsConfig(char (&str)[2400], int begin, Sensor *sensors, int sensorsSize);

    boolean setSwitch(Switch *switches, int switchesSize, String switchUUID, boolean toState);
    
    boolean pushButton(Switch *switches, int switchesSize, int posX, int posY);

    boolean highLightButton(Switch *switches, int switchesSize, int posX, int posY);
    
  protected:
    String const locationUUID;
    String const locationName;


};

#endif

