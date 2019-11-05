#ifndef DEF_HUMIDITY
#define DEF_HUMIDITY

#include "Sensor.h"

class Humidity : public Sensor<float>
{
  public:
		// ----- forme canonique de Coplien -----
    Humidity();
    Humidity(const float valSense);
    Humidity(const Humidity& hum_sensor);
    virtual ~Humidity();
    Humidity& operator= (const Humidity& hum_sensor);

  private:
    // ---------- autres methodes -----------
    float aleaGenVal() const;
};

#endif
