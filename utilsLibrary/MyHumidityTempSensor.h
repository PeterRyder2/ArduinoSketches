/*
 * MyHumidityTempSensor.h
 *
 *  Created on: 4 Jun 2019
 *      Author: peter
 */
#include "Arduino.h"
#include "MySensor.h"
#include "dht.h"


#ifndef CORE_CORE_MYHUMIDITYTEMPSENSOR_H_
#define CORE_CORE_MYHUMIDITYTEMPSENSOR_H_

class MyHumidityTempSensor: public MySensor, public dht
{
public:
	MyHumidityTempSensor(int pin):MySensor(pin) // @suppress("Class members should be properly initialized")
	{
		_pin = pin;
	}

	// public class members
	void SetReading();
	int GetReading();

private:

};



#endif /* CORE_CORE_MYHUMIDITYTEMPSENSOR_H_ */
