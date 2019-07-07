/*
 * MyLightSensor.h
 *
 *  Created on: 4 Jun 2019
 *      Author: peter
 */

#include "MySensor.h"
#include "Arduino.h"

#ifndef CORE_MYLIGHTSENSOR_H_
#define CORE_MYLIGHTSENSOR_H_


class MyLightSensor: public MySensor
{
	public:
	MyLightSensor(int pin):MySensor(pin) // @suppress("Class members should be properly initialized")
	{
		_pin = pin;
	}

	// public class members
	void SetReading();
	int GetReading();

	private:


};


#endif /* CORE_MYLIGHTSENSOR_H_ */
