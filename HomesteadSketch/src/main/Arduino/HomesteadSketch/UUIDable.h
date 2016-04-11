#ifndef UUIDABLE_H
#define UUIDABLE_H
#include "Arduino.h"
#include "Debuggable.h"
class UUIDable : public Debuggable {
  public:
    String generateUUID();
    int getEOSposition(const char *array);
    int appendX(char (&str)[2400], int begin, String appendString);
};
#endif

