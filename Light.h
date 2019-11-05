#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "Sensor.h"

class Light : public Sensor<bool>
{
  public:
	   // ----- forme canonique de Coplien -----
    Light();
    Light(const bool valSense);
    Light(const Light& light_sensor);
    virtual ~Light();
    Light& operator= (const Light& light_sensor);

  private:
  	// ---------- autres methodes -----------
    bool aleaGenVal() const;
};

#endif
