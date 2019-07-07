/*
 * Component.h
 *
 *  Created on: 29 May 2019
 *      Author: peter
 */
#include "Arduino.h"

#ifndef CORE_CORE_COMPONENT_H_
#define CORE_CORE_COMPONENT_H_

class Component
{
	public:
		//constructor declaration
		Component(int pin);
		virtual ~Component(){}; // virtual destructor
		// this method is virtual meaning that it has to
		// implement in a derived class
		virtual void Begin() =0;
		int _pin;

	private:

};
#endif /* CORE_CORE_COMPONENT_H_ */
