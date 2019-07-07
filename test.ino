
#include "Arduino.h"
#include "DigitalPin.h"
#include "MoistureSensor.h"
#include "Component.h"
#include "MySensor.h"
#include "MyRelay.h"
#include "MyLightSensor.h"
#include "dht.h"
#include "cactus_io_DHT22.h"

#define MOISTPIN A2
#define RELAY_PIN 4
#define DHT22_PIN 3
#define LIGHT_PIN A0

// setting up the sensor and relay objects
MoistureSensor mSensor(MOISTPIN); // declaring a new MoisttureSensor object
MyRelay relay1(RELAY_PIN);
DHT22 dht1(DHT22_PIN);
MyLightSensor ls1(LIGHT_PIN);

int temp = 0;
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
	Serial.begin(9600);
	mSensor.Begin();
	relay1.Begin();
	ls1.Begin();
	dht1.begin();
}

// the loop function runs over and over again forever
void loop()
{

	  dht1.readHumidity();
	  dht1.readTemperature();
	  // Check if any reads failed and exit early (to try again).
	  if (isnan(dht1.humidity) || isnan(dht1.temperature_C)) {
	    Serial.println("DHT sensor read failure!");
	    return;
	  }

	  Serial.print(dht1.humidity); Serial.print(" %\t\t");
	  Serial.print(dht1.temperature_C); Serial.println(" *C\t");
	  // Wait a few seconds between measurements. The DHT22 should not be read at a higher frequency of
	  // about once every 2 seconds. So we add a 3 second delay to cover this.
	  delay(3000);

	  //mSensor.SetReading();
	  //Serial.print("Moisture is: ");
	  //Serial.println(mSensor.GetReading());

	  ls1.SetReading();
	  Serial.print("LightSensor is: ");
	  Serial.println(ls1.GetReading());
	  relay1.On();
	  delay(110);
	  relay1.Off();
}
