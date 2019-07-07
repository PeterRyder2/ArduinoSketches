/*
 * DigitalPin.cpp
 *
 *  Created on: 5 May 2019
 *      Author: Peter Ryder
 *      simple way to declare digital pins in arduino
 *      tutorial from https://www.youtube.com/watch?v=HvGJlIKOLoI
 */

#include "DigitalPin.h"


DigitalPin::DigitalPin(int pin) // this is the constructor // @suppress("Class members should be properly initialized")
{
	_pin = pin;
}

void DigitalPin::OutputBegin()
{
	pinMode(_pin, OUTPUT);
}


void DigitalPin::InputBegin()
{
	pinMode(_pin, INPUT);
}

void DigitalPin::off()
{
	digitalWrite(_pin,LOW);
	_status=0;
}

void DigitalPin::on()
{
	digitalWrite(_pin, HIGH);
	_status = 1;
}

bool DigitalPin::status()
{
	return _status;
}

int DigitalPin::getPinNumber()
{
	return _pin;
}
