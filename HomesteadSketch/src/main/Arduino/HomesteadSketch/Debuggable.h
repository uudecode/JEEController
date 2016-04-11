#ifndef DEBUGGABLE_H
#define DEBUGGABLE_H
#include "Arduino.h"
class Debuggable {
  public:
    void debug(char const * debugString);
    void debug(String debugString);
    String copyToString (const char str[]);
};



#endif
