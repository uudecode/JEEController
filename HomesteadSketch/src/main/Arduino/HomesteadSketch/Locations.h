#include "Location.h"
//#include "Switch.h"
#include "Sensor.h"

class Yard : public Location {
  public:
    Yard() : Location("Двор") {};


    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

  protected:
    Switch switches[2] = {Switch("SW01",1, 46,  "Насос в колодце", false, false )
                          , Switch("SW02",2, 47,  "Свет во дворе", false, false )
                         };

    Sensor sensors[2] = {Sensor("SN01", LIGHT, 20, "Освещеность двора")
                         , Sensor("SN02", THERMAL, 21, "Температура воздуха")
                        };
};


class Barn : public Location {

  public:
    Barn() : Location("Папин домик") {};
    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }
    
  protected:
    Switch switches[1] = {Switch("SW03",3, 48,  "Папин домик", false, false )};
    Sensor sensors[];
};

class Sauna : public Location {
  public:
    Sauna() : Location("Парилка") {};

    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }
    
  protected:
    Switch switches[];
    Sensor sensors[2] = {Sensor("SN03", MOCK, 23, "Влажность воздуха в парной")
                         , Sensor("SN04", THERMAL, 21, "Температура в парной")
                        };
};

class WashingRoom : public Location {
  public:
    WashingRoom() : Location("Моечная") {};
    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }
    
  protected:
    Switch switches[1] = {Switch("SW04",4, 49,  "Свет в моечной", false, false )
                         };
    Sensor sensors[];
};

class FirstFloor : public Location {
  public:
    FirstFloor() : Location("Первый этаж") {};

    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }
    
  protected:
    Switch switches[2] = {Switch("SW05",5, 50,  "Свет первый этаж", false, false )
                          , Switch("SW06",6, 51,  "Тепло первый этаж", false, false )
                         };
    Sensor sensors[3] = { Sensor("SN08", THERMAL, 26, "Температура на первом этаже")
                          , Sensor("SN09", DHT11_THERMAL, A0, "Температура в контроллере")
                          , Sensor("SN10", DHT11_HUMIDITY, A0, "Влажность в контроллере")
                        };
};

class SecondFloor : public Location {
  public:
    SecondFloor() : Location("Второй этаж") {};

    int getConfig(char (&str)[2400], int begin) {
      return Location::getConfig(str, begin, switches, (sizeof(switches) / sizeof(Switch)), sensors, (sizeof(sensors) / sizeof(Sensor)));
    }

    boolean setSwitch(String switchUUID, boolean toState) {
      return Location::setSwitch(switches, (sizeof(switches) / sizeof(Switch)), switchUUID, toState);
    }

    boolean pushButton(int posX, int posY) {
      return Location::pushButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }

    boolean highLightButton(int posX, int posY) {
      return Location::highLightButton(switches, (sizeof(switches) / sizeof(Switch)), posX, posY);
    }
    
  protected:
    Switch switches[2] = {Switch("SN07",7, 52,  "Свет второй этаж", false, false )
                          , Switch("SN08",8, 53,  "Тепло второй этаж", false, false )
                         };
    Sensor sensors[];
};


