#include "Location.h"
#include "Switch.h"
#include "Sensor.h"

class Yard : public Location {
  public:
    Yard() : Location("Двор") {};


    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }
    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

  protected:
    Switch switches[4] = {Switch(15,  "Насос в колодце", false, false )
                          , Switch(16,  "Освещение двора", false, false )
                          , Switch(17,  "Открыть ворота", false, false )
                          , Switch(18,  "Закрыть ворота", false, false )
                         };

    Sensor sensors[3] = {Sensor(MOCK, 19, "Уровень воды в колодце")
                         , Sensor(LIGHT, 20, "Освещеность двора")
                         , Sensor(THERMAL, 21, "Температура воздуха")
                        };
};


class Barn : public Location {

  public:
    Barn() : Location("Папин домик") {};
    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }


  protected:
    Switch switches[1] = {Switch(22,  "Питание", false, false )
                         };
    Sensor sensors[];
};

class Sauna : public Location {
  public:
    Sauna() : Location("Парилка") {};

    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }
    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

  protected:
    Switch switches[1] = {Switch(22,  "Освещение в парной", false, false )
                         };
    Sensor sensors[2] = {Sensor(MOCK, 23, "Влажность воздуха в парной")
                         , Sensor(THERMAL, 21, "Температура в парной")
                        };
};

class WashingRoom : public Location {
  public:
    WashingRoom() : Location("Моечная") {};
    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }
    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

  protected:
    Switch switches[1] = {Switch(24,  "Освещение в моечной", false, false )
                         };
    Sensor sensors[2] = {Sensor(MOCK, 25, "Показания CO в моечной")
                         , Sensor(THERMAL, 26, "Температура в моечной")
                        };
};

class FirstFloor : public Location {
  public:
    FirstFloor() : Location("Первый этаж") {};

    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }
    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

  protected:
    Switch switches[2] = {Switch(24,  "Освещение на первом этаже", false, false )
                          , Switch(24,  "Отопление", false, false )
                         };
    Sensor sensors[1] = { Sensor(THERMAL, 26, "Температура на первом этаже")
                        };
};

class SecondFloor : public Location {
  public:
    SecondFloor() : Location("Второй этаж") {};

    int getConfig(char (&str)[3072], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }
    //    String getConfig() {
    //      String result = Location::getConfig(switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    //      return result  ;
    //    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

  protected:
    Switch switches[2] = {Switch(24,  "Освещение на втором этаже", false, false )
                          , Switch(24,  "Отопление", false, false )
                         };
    Sensor sensors[1] = { Sensor(THERMAL, 26, "Температура на втором этаже")
                        };
};


