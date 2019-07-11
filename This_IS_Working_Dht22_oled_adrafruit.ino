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

#include <Wire.h>
// two libraries inserted into the 'libraries' folder
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// dht library
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define DHTTYPE DHT22 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup()   {                
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
  
  dht.begin();
  delay(2000);
}


void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed.
  if (isnan(h) || isnan(t) || isnan(f)) {
    delay(2000);
  } else{
    // routine for converting temp/hum floats to char arrays
    char temp_buff[5]; char hum_buff[5];
    char temp_disp_buff[11] = "Tmp:";
    char hum_disp_buff[11] = "Hum:";
    
    // appending temp/hum to buffers
    dtostrf(t,2,1,temp_buff);
    strcat(temp_disp_buff,temp_buff);
    dtostrf(h,2,1,hum_buff);
    strcat(hum_disp_buff,hum_buff);
    
    // routine for displaying text for temp/hum readout
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(temp_disp_buff);
    display.println(hum_disp_buff);
    display.display();
    delay(2000);
  }
}
