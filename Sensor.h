#ifndef DEF_SENSOR
#define DEF_SENSOR

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <ctime>

#include "SensorType.h"
#include "SensorPrototype.h"

template <typename T>
class Sensor : public SensorPrototype
{
	public:
		// ----- forme canonique de Coplien -----
		Sensor();
		Sensor(Sensor<T> const& sensor_p);
		Sensor(T valRcv, SensorType type);
		virtual ~Sensor();
		Sensor<T>& operator=(const Sensor<T> &sensor_p);

		// ---------- autres methodes -----------
		T sendData() const;
		bool operator==(const Sensor<T> &sensor_p);
		SensorType getSensorType() const;
    void generateNewVal();


	protected:
		// ------------- attributs --------------
		T valSense;
		SensorType type;

		// ---------- autres methodes -----------
		void clonage(const Sensor<T>& sensor_p);
		virtual T aleaGenVal() const = 0;


		// -------------- Friends ---------------
		friend class Scheduler;
};



/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

template <typename T> Sensor<T>::Sensor()
{
	//this->valSense = NULL;
	this->type = SensorType::undefined;
}


template <typename T> Sensor<T>::Sensor(Sensor<T> const& sensor_p)
{
	this->clonage(sensor_p);
	return;
}


template <typename T> Sensor<T>::Sensor(T valRcv, SensorType type) : valSense(valRcv), type(type) {}


template <typename T> Sensor<T>::~Sensor() {}


template <typename T> Sensor<T>& Sensor<T>::operator=(const Sensor<T>& sensor_p)
{
	if (this != &sensor_p) {
		this->clonage(sensor_p);
	}
	return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////

// +++++++++++++++ PUBLIC +++++++++++++++

template <typename T> T Sensor<T>::sendData() const
{
	return this->valSense;
}


template <typename T> bool Sensor<T>::operator==(const Sensor<T>& sensor_p)
{
		if (this->valSense 	== sensor_p.valSense &&
    		this->type 			== sensor_p.type)
		{
  		return true;

    } else {
      return false;
    }
  }


template <typename T> SensorType Sensor<T>::getSensorType() const
{
		return this->type;
}


template <typename T> void Sensor<T>::generateNewVal()
{
	this->valSense = this->aleaGenVal();
}


// ~~~~~~~~~~~~~ PROTECTED ~~~~~~~~~~~~~~

template <typename T> void Sensor<T>::clonage(const Sensor<T>& sensor_p) {
	this->valSense 	= sensor_p.valSense;
	this->type 			= sensor_p.type;
	return;
}


#endif
