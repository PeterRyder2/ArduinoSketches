/*
 * DigitalPins.h
 *
 *  Created on: 5 May 2019
 *      Author: Peter Ryder
 */




#ifndef DIGITALPINH_ // preProcessor directivbe //if not defined. then defi
#define DIGITALPINH_ // define digitalpin

#include "Arduino.h"
class DigitalPin
{
	public:
		//// constructor declaration
		DigitalPin(int pin);

		// public class members
		void InputBegin();
		void OutputBegin();
		void on();
		void off();
		bool status();
		int getPinNumber();

	// private variables
	// these members can only be used in the class. ie cannot
	// be used outside of the class
	private:
		int _pin;
		bool _status;
};

#endif /* DIGITALPINH_ */
