#ifndef DEF_TEMPERATURE
#define DEF_TEMPERATURE

#include "Sensor.h"

class Temperature : public Sensor<float>
{
  public:
		// ----- forme canonique de Coplien -----
    Temperature();
    Temperature(const float valSense);
    Temperature(const Temperature& temp_sensor);
    virtual ~Temperature();
    Temperature& operator= (const Temperature& temp_sensor);

	private:
    float aleaGenVal() const;
		// ---------- autres methodes -----------
};

#endif
