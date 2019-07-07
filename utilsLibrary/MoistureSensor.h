/*
 * MoistureSensor.h
 *
 *  Created on: 7 May 2019
 *      Author: peter
 */

#ifndef CORE_CORE_MOISTURESENSOR_H_
#define CORE_CORE_MOISTURESENSOR_H_

#include "MySensor.h"
#include "Arduino.h"

class MoistureSensor: public MySensor
{

	public:

		MoistureSensor(int pin):MySensor(pin) // @suppress("Class members should be properly initialized")
		{
			_pin = pin;
		}

		// public class members
		void SetReading();
		int GetReading();

	// private variables
	// these members can only be used in the class. ie cannot
	// be used outside of the class
	private:

};
#endif /* CORE_CORE_MOISTURESENSOR_H_ */
