#include "SensorPrototype.h"

SensorPrototype::SensorPrototype(){}

SensorPrototype::SensorPrototype(SensorPrototype const& prototype) {}

SensorPrototype::~SensorPrototype(){}

SensorPrototype& SensorPrototype::operator=(SensorPrototype const& prototype)
  {
      if(this == &prototype) return *this;
      return *this;
  }
