#ifndef DEF_SENSOR_PROTOTYPE
#define DEF_SENSOR_PROTOTYPE

#include <chrono>

#include "SensorType.h"

// class mere de tous les sensors
class SensorPrototype
{
  public:
    SensorPrototype();
    SensorPrototype(SensorPrototype const& prototype);
    ~SensorPrototype();
    SensorPrototype& operator=(SensorPrototype const& prototype);
};

#endif
