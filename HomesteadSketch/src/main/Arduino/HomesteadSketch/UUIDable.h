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
};
#endif

