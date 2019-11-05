#include "Sound.h"

/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Sound::Sound() : Sensor()
{
	this->type 			= SensorType::Sound;
	this->valSense	= this->aleaGenVal();

	std::cout << "Sound initialized successfully" << std::endl;
}

Sound::Sound(const int valSense) : Sensor (valSense, SensorType::Sound){}


Sound::Sound(const Sound& sound_sensor) : Sensor (sound_sensor){}


Sound::~Sound(){}


Sound& Sound::operator=(const Sound& sound_sensor)
{
    if ( this == &sound_sensor )	return *this;

		this->valSense 	= sound_sensor.valSense;
		this->type 			= sound_sensor.type;
		return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////

int Sound::aleaGenVal() const
{
	// retourne une valeur entre 0 et 150
	std::random_device rd;
	double first (0), last (150);
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(first, last);
	return (int) distribution(generator);
}
