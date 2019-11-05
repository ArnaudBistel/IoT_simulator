#pragma once

#ifndef DEF_SENSOR_TYPE
#define DEF_SENSOR_TYPE

#include <ostream>

enum class SensorType
{
	undefined 	= -1,
	Temperature = 0,
	Humidity 		= 1,
	Light 			= 2,
	Sound 			= 3
};

// pour imprimer le type
inline std::ostream& operator<<(std::ostream& os, const SensorType& type)
{
	switch (type)
	{
	case SensorType::Temperature:
		os << "Temperature";
		break;

	case SensorType::Humidity:
		os << "Humidity";
		break;

	case SensorType::Light:
		os << "Light";
		break;

	case SensorType::Sound:
		os << "Sound";
		break;

	default :
		break;
		
	}

	return os;
}

#endif
