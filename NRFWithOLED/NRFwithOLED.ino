

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution


Visis this websirte for interesting info on th OLED https://www.instructables.com/id/Fun-With-OLED-Display-and-Arduino/
*********************************************************************/


#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include<SPI.h>
#include <avr/sleep.h> // fro sleeping
#include <Wire.h>
// two libraries inserted into the 'libraries' folder
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// dht library
#include "DHT.h"
// RF24 radio (9,8); // uncomment for the pro micro
RF24 radio (10, 9); // uncomment for the nano or UNO
int moistureSensor = A2; // moisture sensor pin
String radioReturn = ""; // variable that returns the packet of info from the pi..  (This dicates what the UNO shoudl do)
int minAutoValue = 0; 
int ok = 1; // acknoledgment ot send back to pi
int count = 0; 
#define DHTPIN 2     // what digital pin we're connected to
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define DHTTYPE DHT22 
//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif
DHT dht(DHTPIN, DHTTYPE);

void setup()   {  

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer
  dht.begin();

  radio.begin();
  radio.setPALevel(RF24_PA_MAX); // min works for the micro. with the UNO is works with MAX
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  radio.openReadingPipe(1, pipe);
  radio.enableDynamicPayloads();
  radio.maskIRQ(1, 1, 0); // irq changes upon receiving data only
  radio.powerUp();
}


void loop() {
  ok = 0; 
  count ++;

 
  Serial.print("count is ");
  Serial.println(count);
  
  delay(1000);
  radioReturn = radioListen();
  
  Serial.print("RadioReturn is: ");
  Serial.println(radioReturn);
  
  if (radioReturn == "two"){
      ok = 1;
      //writeBackToPI(3); // return the minAutoValue
  }

//radioReturn = radioListen(); // to reset the radioreturn
   

    
    // routine for displaying text for temp/hum readout
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("is in range (1 for true):");
    display.println(ok);
    display.print("Iteration Number:");
    display.println(count);
    display.display();
  }


/**************************METHODS**********************************************/

// method to listen for packets on the  radio
String radioListen() {
  // put your main code here, to run repeatedly:
  radio.startListening();
  Serial.println("****** In radio Listen Mode *****");
  char receivedMessage[32] = {0};
  if (radio.available()) {
    radio.read(receivedMessage, sizeof(receivedMessage));
    Serial.println("The Received message is ");
    Serial.println(receivedMessage);
    radio.stopListening();
    Serial.println("Turning off the radio!");
    String stringMessage(receivedMessage);
    return (stringMessage);
  }
  else {
    return "none";
  }
}


