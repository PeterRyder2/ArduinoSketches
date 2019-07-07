/*
 * MyRelay.h
 *
 *  Created on: 3 Jun 2019
 *      Author: peter Ryder
 */

#include "Component.h"
#include "Arduino.h"

#ifndef CORE_CORE_MYRELAY_H_
#define CORE_CORE_MYRELAY_H_

class MyRelay: public Component
{
	public:
		MyRelay(int pin): Component(pin)
		{
			_pin = pin;
		}
		void Begin();
		void On();
		void Off();


	private:
};




#endif /* CORE_CORE_MYRELAY_H_ */
