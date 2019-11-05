#include "Temperature.h"

/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Temperature::Temperature() : Sensor()
{
	this->type 			= SensorType::Temperature;
	this->valSense 	= this->aleaGenVal();

	std::cout << "Temperature initialized successfully" << std::endl;
}


Temperature::Temperature(const float valSense) : Sensor (valSense, SensorType::Temperature){}


Temperature::Temperature(const Temperature& temp_sensor) : Sensor (temp_sensor){}


Temperature::~Temperature(){}


Temperature& Temperature::operator=(const Temperature& temp_sensor)
{
    if ( this == &temp_sensor )	return *this;

		this->valSense 	= temp_sensor.valSense;
		this->type 			= temp_sensor.type;
		return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////

float Temperature::aleaGenVal() const
{
	// retourne une valeur entre -20 et 60
	std::random_device rd;
	double first (-20), last (60);
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(first, last);
	float ret = (int)(distribution(generator) * 100 + .5);
    return (float)ret / 100;
}
