#ifndef SWITCH_H
#define SWITCH_H
#include "Arduino.h"
#include "UUIDable.h"
#include "Button.h"
#include <EEPROM.h>

#ifndef SWITCH_OFF
#define SWITCH_OFF false
#endif
#ifndef SWITCH_ON
#define SWITCH_ON true
#endif



class Switch : public UUIDable
{
  public:

    Switch( String switchUUID, int buttonNumber, byte switchPin, String switchName, boolean normallyOpen, boolean turnOn ) ;

    Switch( byte switchPin, int buttonNumber, String switchName , boolean normallyOpen, boolean turnOn ) : Switch(generateUUID(), buttonNumber, switchPin, switchName, normallyOpen, turnOn) {};

    Switch( byte switchPin, int buttonNumber, String switchName ) : Switch(switchPin, buttonNumber, switchName, false, false) {};

    Switch( byte switchPin, int buttonNumber ) : Switch(switchPin, buttonNumber, "n/a", false, false) {};


    String getSwitchUUID();

    byte getSwitchPin();

    String getSwitchName();

    boolean getSwitchState();

    String getSwitchStringState();


    void turnOn();

    void turnOff();

    void highlightOn();
    void highlightOff();


    boolean isMeTouched(int posX, int posY);

    int getConfig(char (&str)[2400], int begin);


  protected:
    String switchUUID;
    byte switchPin;
    String switchName;
    boolean normallyOpen;
    boolean switchState = SWITCH_OFF;
    int    EEPROMaddress;
    int buttonNumber;
    Button button;


};


#endif

