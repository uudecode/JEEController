#ifndef DEBUGGABLE_H
#define DEBUGGABLE_H
class Debuggable {
  public:
    inline void debug(char const * debugString) {
#ifdef DEBUG_ON
      Serial.println(debugString);
#endif
    }
    inline void debug(String debugString) {
#ifdef DEBUG_ON
      Serial.println(debugString);
#endif
    }

};



#endif

