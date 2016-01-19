#include "Location.h"
#include "Switch.h"
#include "Sensors.h"

#ifndef YARD_H
#define YARD_H
class Yard : public Location {

  public:
    Yard() : Location("Yard") {}; // TODO! Русские названия по сети!

    String getConfig() {
      String result = Location::getConfig();

      result += Location::getSwitchesConfig(switches, (sizeof(switches) / sizeof(Switch)));
      result += Location::getSensorsConfig(sensors, (sizeof(sensors) / sizeof(Sensor)));
      result += "\n</Location>";



      return result  ;

    }
  protected:
    // TODO Русские буквы для сети
    Switch switches[4] = {Switch(15,  "Well Pump", false, false ) // PIN 15 - Pump in well
                          , Switch(16,  "Outdoors Lamps", false, false ) // Pin 16 outdoor light
                          , Switch(17,  "Open Gate", false, false ) // Pin 17 Open gate
                          , Switch(18,  "Close Gate", false, false ) // Pin 18 Open gate
                         };

    Sensor sensors[3] = {MockSensor(19, "Water level")
                         , LightSensor(20, "Twilight")
                         , TemperatureSensor(21, "Outdoor temperature")
                        };




};

#endif


