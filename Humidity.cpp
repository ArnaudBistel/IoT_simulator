#include "Humidity.h"

/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Humidity::Humidity() : Sensor()
{
	this->type 			= SensorType::Humidity;
	this->valSense 	= this->aleaGenVal();
	std::cout << "Humidity initialized successfully" << std::endl;
}

Humidity::Humidity(const float valSense) : Sensor (valSense, SensorType::Humidity){}


Humidity::Humidity(const Humidity& hum_sensor) : Sensor (hum_sensor){}


Humidity::~Humidity(){}


Humidity& Humidity::operator=(const Humidity& hum_sensor)
{
		if ( this == &hum_sensor )	return *this;

		this->valSense = hum_sensor.valSense;
		this->type		 = hum_sensor.type;
		return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////

float Humidity::aleaGenVal() const
{
	// retourne un float entre 0 et 100
	std::random_device rd;
	double first (0), last (100);
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(first, last);
	float ret = (int)(distribution(generator) * 100 + .5);
  return (float)ret / 100;
}
