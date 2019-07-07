/*
 * MyLightSensor.cpp
 *
 *  Created on: 4 Jun 2019
 *      Author: peter
 */
#include "MyLightSensor.h"
#include "MySensor.h"


void MyLightSensor::SetReading()
{
	  // variable declarations
	  unsigned int lightValue = 0;  // to store value of analog read
	  int lightArray[100];
	  unsigned int lightAvg = 0; // average of the moisture value

	  // for moisture sensor
	  for (int i = 0; i < 100; i++) {
	    // read the value from the sensor:
		lightValue = analogRead(_pin);
	    lightValue = map(lightValue, 0, 750, 0, 255);
	    lightArray[i] = lightValue;
	  }
	  lightAvg = lightArray[0];

	  // for calculating moisutre avg
	  for (int i = 0; i < 99; i++) {
	    lightAvg += lightArray[i + 1];
	  }
	  lightAvg = lightAvg / 99;

	  reading = lightAvg; // assign the average value to lightreading
} // end Setreading


int MyLightSensor::GetReading()
{
	return reading;
}
