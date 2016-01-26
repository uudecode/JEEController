#include <EEPROM.h>
#include "UUIDable.h"

#ifndef SWITCH_H
#define SWITCH_H

#ifndef SWITCH_OFF
#define SWITCH_OFF false
#endif
#ifndef SWITCH_ON
#define SWITCH_ON true
#endif

static char switchConfiguration[128];

class Switch : public UUIDable
{
  public:

    Switch( String switchUUID, byte switchPin, String switchName, boolean normallyOpen, boolean turnOn ) {
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

    Switch( byte switchPin, String switchName , boolean normallyOpen, boolean turnOn ) : Switch(generateUUID(), switchPin, switchName, normallyOpen, turnOn) {};

    Switch( byte switchPin, String switchName ) : Switch(switchPin, switchName, false, false) {};

    Switch( byte switchPin ) : Switch(switchPin, "n/a", false, false) {};


    String getSwitchUUID() {
      return this->switchUUID;
    }

    byte getSwitchPin() {
      return this->switchPin;
    }

    String getSwitchName() {
      return this->switchName;
    }

    boolean getSwitchState() {
      return this->switchState;
    }

    String getSwitchStringState() {
      return (this->switchState ? "ON" : "OFF");
    }


    inline void turnOn() {
      Serial.println(" to ON " + this->switchUUID);
      this->switchState = SWITCH_ON;
      digitalWrite(this->switchPin, ((this->switchState) ? HIGH : LOW));
      EEPROM.write(this->EEPROMaddress, B00000010 + ((this->switchState) ? B00000001 : B00000000));
    }

    inline void turnOff() {
      Serial.println(" to OFF " + this->switchUUID);
      this->switchState = SWITCH_OFF;
      digitalWrite(this->switchPin, ((this->switchState) ? HIGH : LOW));
      EEPROM.write(this->EEPROMaddress, B00000010 + ((this->switchState) ? B00000001 : B00000000));
    }

    String getConfig() {
      sprintf(switchConfiguration, "\n\t\t\t\t<Switch uuid=\"%s\" name=\"%s\" pin=\"%s\" state=\"%s\"/>", this->switchUUID.c_str(), this->switchName.c_str(), String(this->switchPin).c_str() , (this->getSwitchStringState()).c_str());
      Serial.println(switchConfiguration);
      return switchConfiguration  ;
    }


    //    String getConfig() {
    //      String result = "\n\t\t\t\t<Switch";
    //      result += " uuid=\"" ;
    //      result += this->getSwitchUUID();
    //      result += "\"" ;
    //      result += " name=\"" ;
    //      result += this->getSwitchName();
    //      result += "\"" ;
    //      result += " pin=\"" ;
    //      result += this->getSwitchPin();
    //      result += "\"" ;
    //      result += " state=\"" ;
    //      result += this->getSwitchStringState();
    //      result += "\"" ;
    //      result += "/>";
    //      return result  ;
    //    }

  protected:
    String switchUUID;
    byte switchPin;
    String switchName;
    boolean normallyOpen;
    boolean switchState = SWITCH_OFF;
    int    EEPROMaddress;

};


#endif

