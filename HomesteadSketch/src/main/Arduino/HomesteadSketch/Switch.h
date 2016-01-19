#include <EEPROM.h>
#include "UUIDable.h"

#ifndef SWITCH_H
#define SWITCH_H

#define SWITCH_OFF false;
#define SWITCH_ON true;

class Switch : public UUIDable
{
  public:

    inline Switch( String switchUUID, byte switchPin, String switchName, boolean normallyOpen, boolean turnOn ) {
      this->switchUUID = switchUUID;
      this->switchPin = switchPin;
      this->switchName = switchName;
      this->normallyOpen = normallyOpen;
      this->EEPROMaddress = (int)this->switchPin;
      // turn Swith to On depend off eeprom and parameter. eeprom have higher priority
      // 0 bit is state
      // 1 bit is changed before
      int EEPROMvalue = EEPROM.read(this->EEPROMaddress); // Read value from EEPROM
      if (2 == (EEPROMvalue & B00000010))
      {
        // Value was set before, take it and ignore constructor value
        this->switchState =  EEPROMvalue & B00000001;
      } else
      {
        this->switchState = turnOn;
        EEPROM.write(this->EEPROMaddress, B00000010 + ((this->switchState) ? B00000001 : B00000000));
      }
      // work with switch
      pinMode(switchPin, OUTPUT);
      digitalWrite(switchPin, ((this->switchState) ? HIGH : LOW));

    }

    inline Switch( byte switchPin, String switchName , boolean normallyOpen, boolean turnOn ) : Switch(generateUUID(), switchPin, switchName, normallyOpen, turnOn) {};

    inline Switch( byte switchPin, String switchName ) : Switch(switchPin, switchName, false, false) {};

    inline Switch( byte switchPin ) : Switch(switchPin, "n/a", false, false) {};


    inline String getSwitchUUID() {
      return this->switchUUID;
    }

    inline byte getSwitchPin() {
      return this->switchPin;
    }

    inline String getSwitchName() {
      return this->switchName;
    }

    inline boolean getSwitchState() {
      return this->switchState;
    }


    String getConfig() {
      String result = "\n\t\t\t\t<Switch";
      result += " uuid=\"" ;
      result += this->getSwitchUUID();
      result += "\"" ;
      result += " name=\"" ;
      result += this->getSwitchName();
      result += "\"" ;
      result += " pin=\"" ;
      result += this->getSwitchPin();
      result += "\"" ;
      result += "/>";
      return result  ;
    }

  protected:
    String switchUUID;
    byte switchPin;
    String switchName;
    boolean normallyOpen;
    boolean switchState = SWITCH_OFF;
    int    EEPROMaddress;
};


#endif

