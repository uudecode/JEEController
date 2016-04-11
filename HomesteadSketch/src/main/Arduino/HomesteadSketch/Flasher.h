
#include "Debuggable.h"

#ifndef FLASHER_H
#define FLASHER_H
#include "Arduino.h"

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
  // and initializes the member variables and state
 
  Flasher(int pin, long on, long off);

  // setup Pin
  void setPin(int pin, long on, long off);
  void setTimes (long on, long off) ;
  void update();
};
#endif

