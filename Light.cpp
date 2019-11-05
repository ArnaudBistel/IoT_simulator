#include "Light.h"

/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Light::Light()  : Sensor()
{
	this->type 			= SensorType::Light;
	this->valSense 	= this->aleaGenVal();

	std::cout << "Light initialized successfully" << std::endl;
}


Light::Light(const bool valSense) : Sensor (valSense, SensorType::Light){}


Light::Light(const Light& light_sensor) : Sensor (light_sensor){}


Light::~Light(){}


Light& Light::operator=(const Light& light_sensor)
{
    if ( this == &light_sensor )	return *this;
		this->valSense 	= light_sensor.valSense;
		this->type 			= light_sensor.type;
		return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////


bool Light::aleaGenVal() const
{
	// retourne un boolean
	std::random_device rd;
	double first (0), last (1);
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(first, last);
	if (distribution(generator) > 0.49 ) return true;
	return false;

}
