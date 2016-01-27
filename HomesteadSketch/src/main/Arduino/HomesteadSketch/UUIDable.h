#include "Debuggable.h"
#ifndef UUIDABLE_H
#define UUIDABLE_H
class UUIDable : public Debuggable {
  public:
    String generateUUID() {
      char newUUID[37] = "0000-000000000000";
      sprintf(newUUID, "%02x%02x-%02x%02x%02x%02x%02x%02x", random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255));
      //      char newUUID[37] = "00000000-0000-0000-0000-000000000000";
      //      sprintf(newUUID, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255));
      return String(newUUID);
    }
    int getEOSposition(const char *array)
    {
      int result = -1;
      for (int i = 0; i <= 3072; i++) {
        if (array[i] == '\0') {
          result = i;
          break;
        }

      }
      return result;
    }
    
    int appendX(char (&str)[3072], int begin, String appendString) {
      int i;
      for (i = 0; i <= (appendString.length() - 1); i++) {
        str[i + begin] = appendString.c_str()[i];
      }
      return begin + i;
    }
};
#endif

