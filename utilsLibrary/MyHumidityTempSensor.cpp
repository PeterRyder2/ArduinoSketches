/*
 * MyHumidityTempSensor.cpp
 *
 *  Created on: 4 Jun 2019
 *      Author: peter
 */



#include "MySensor.h"
#include "MyHumidityTempSensor.h"

void MyHumidityTempSensor::SetReading()
{
	  // variable declarations
	  unsigned long humTempValue = 0;  // to store value of analog read
	  int humTempArray[100];
	  unsigned long humTempAvg = 0; // average of the moisture value

	  // for moisture sensor
	  for (int i = 0; i < 100; i++) {
	    // read the value from the sensor:
	    humTempValue = analogRead(_pin);
	    humTempValue = map(humTempValue, 0, 750, 0, 255);
	    humTempArray[i] = humTempValue;
	  }
	  humTempAvg = humTempArray[0];

	  // for calculating humidtu avg
	  for (int i = 0; i < 99; i++) {
	    humTempAvg += humTempArray[i + 1];
	  }

	  humTempAvg = humTempAvg / 99;

	  reading = humTempAvg; // assign the average value to reading

}// end SetReading

int MyHumidityTempSensor::GetReading()
{
	return reading;
}  // end GetReading()
