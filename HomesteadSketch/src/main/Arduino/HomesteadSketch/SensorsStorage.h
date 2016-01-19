
#ifndef SENSORS_STORAGE_H
#define SENSORS_STORAGE_H
class SensorsStorage : public UUIDable {
    int storageVolume = 0;
    Sensor* sensors[64]; // Static array

  public:
    SensorsStorage()
    {
      debug("SensorsStorage constructed.");
    }

    void put(Sensor* sensor) {
      storageVolume++;
      sensors[storageVolume - 1] = sensor;
    }


    Sensor* getSensor(int index) {
      return sensors[index];
    }
};
#endif

