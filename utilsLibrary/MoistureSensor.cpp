/*
 * MoistureSensor.cpp
 *
 *  Created on: 7 May 2019
 *      Author: peter
 */

#include "MoistureSensor.h"
#include "MySensor.h"


/*
  moisture sensor function
  takes the average of 50 readings from the sensor and
  then stores them in an array and takes the average of the array 50 inputs
  returns the average
*/

void MoistureSensor::SetReading()
{
	  // variable declarations
	  unsigned long moistureValue = 0;  // to store value of analog read
	  int moistureArray[100];
	  unsigned long moistureAvg = 0; // average of the moisture value

	  // for moisture sensor
	  for (int i = 0; i < 100; i++) {
	    // read the value from the sensor:
	    moistureValue = analogRead(_pin);

	    moistureValue = map(moistureValue, 0, 750, 0, 255);
	    moistureArray[i] = moistureValue;
	  }
	  moistureAvg = moistureArray[0];

	  // for calculating moisutre avg
	  for (int i = 0; i < 99; i++) {
	    moistureAvg += moistureArray[i + 1];
	  }

	  moistureAvg = moistureAvg / 99;

	  reading = moistureAvg; // assign the average value to _cmoisturereading
	} // end moisturereading


int MoistureSensor::GetReading(){
	return reading;
}

