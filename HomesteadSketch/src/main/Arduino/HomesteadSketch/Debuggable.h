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

    String copyToString (const char str[]) {
      char c;
      String result;
      if (str)
        while ((c = pgm_read_byte(str++)))
          result += c;

      return result;
    }
};



#endif

