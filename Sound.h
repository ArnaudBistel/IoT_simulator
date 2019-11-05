#ifndef DEF_SOUND
#define DEF_SOUND

#include "Sensor.h"

class Sound : public Sensor<int>
{
  public:
		// ----- forme canonique de Coplien -----
    Sound();
    Sound(const int valSense);
    Sound(const Sound& sound_sensor);
    virtual ~Sound();
    Sound& operator= (const Sound& sound_sensor);

    // ---------- autres methodes -----------
    int aleaGenVal() const;
  private:
};

#endif
