#include "Location.h"
#include "Switch.h"
#include "Sensors.h"

class Yard : public Location {
  public:
    Yard() : Location("Двор") {}; 

    String getConfig() {
      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
      return result  ;
    }
  protected:
    Switch switches[4] = {Switch(15,  "Насос в колодце", false, false ) 
                          , Switch(16,  "Освещение двора", false, false )
                          , Switch(17,  "Открыть ворота", false, false ) 
                          , Switch(18,  "Закрыть ворота", false, false ) 
                         };

    Sensor sensors[3] = {MockSensor(19, "Уровень воды в колодце")
                         , LightSensor(20, "Освещеность двора")
                         , TemperatureSensor(21, "Температура воздуха")
                        };
};


class Barn : public Location {

  public:
    Barn() : Location("Папин домик") {}; 

    String getConfig() {
      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
      return result  ;
    }

  protected:
    // TODO Русские буквы для сети
    Switch switches[1] = {Switch(22,  "Питание", false, false ) 
                         };
    Sensor sensors[];
};

class Sauna : public Location {
  public:
    Sauna() : Location("Парилка") {}; 

    String getConfig() {
      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
      return result  ;
    }

  protected:
    Switch switches[1] = {Switch(22,  "Освещение в парной", false, false ) 
                         };
    Sensor sensors[2] = {MockSensor(23, "Влажность воздуха в парной")
                         , TemperatureSensor(21, "Температура в парной")
                        };
};

class WashingRoom : public Location {
  public:
    WashingRoom() : Location("Моечная") {}; 

    String getConfig() {
      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
      return result  ;
    }

  protected:
    Switch switches[1] = {Switch(24,  "Освещение в моечной", false, false ) 
                         };
    Sensor sensors[2] = {MockSensor(25, "Показания CO в моечной")
                         , TemperatureSensor(26, "Температура в моечной")
                        };
};


