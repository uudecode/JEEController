#include "Debuggable.h"

#ifndef FLASHER_H
#define FLASHER_H
class Flasher : public Debuggable
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time
  String flasherName;     // String name for Flasher
 
  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  public:

  // Constructor - creates a Flasher 
  Flasher ()
  {
  
  }
  
  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  
  Flasher(int pin, long on, long off)
  {
    setPin(pin, on, off);
  }

  // setup Pin
  void setPin(int pin, long on, long off) 
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);     

    flasherName = "LED " + String(ledPin);  
    OnTime = on;
    OffTime = off;
    
    ledState = LOW; 
    previousMillis = 0;
     debug(flasherName + " Initiated");
  }
      void setTimes (long on, long off) {
      OnTime = on;
      OffTime = off;
    }
 
  void update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
      //debug(flasherName + " OFF");
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      //debug(flasherName + " ON");      
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};
#endif

