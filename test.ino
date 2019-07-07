


/* ****************************************************************
 *            ARDIUNO PIN LAYOUT FOR NRF24 FOR UNO  
 ******************************************************************
 * LEAD COLOR  ard pin   NRF24 pin   ard pin   LEAD COLOR
 * red 1     vcc      <-|vcc|GND| -> GND        BLACK 
 * yellow      10        <-|CSN|CE |-> 9           PURPLE
 * Orange      11       <-|MOSI|SCK|-> 13           RED 2
 * Green      2        <-|IRQ|MISO|-> 12          BLUE
 * 
 * 
 *    Moisture sensor hookup
 *    PINS for mositure sensor 
 *    ard PIN  moisture sensor 
 *        A2    s
 *        vcc   +
 *        GND   -
 *        
 *  
 *  Relay hookup 
 *    
 *    ard pins   relay 
 *      vcc       vcc
 *      gnd       GND 
 *       4        IN1
 *      
 *      NOTE make sure that vcc and gnd are near the start of the vcc and gnd connections
 *        on the arduino
 * 
 * 
 ****************************************************************
 *            ARDIUNO PIN LAYOUT FOR NRF24 FOR PRO MICRO  
 ***************************************************************          
 *            
 *  LEAD COLOR  ard pin   NRF24 pin   ard pin   LEAD COLOR
 * green 1     vcc      <-|vcc|GND| -> GND        BLACK
 * yellow      8        <-|CSN|CE |-> 9           PURPLE
 * Orange      16       <-|MOSI|SCK|-> 15           RED
 * Green 2     3        <-|IRQ|MISO|-> 14          BLUE
 *
 *  Moisture sensor hookup
 *    PINS for mositure sensor 
 *    ard PIN  moisture sensor 
 *        A2    s
 *        vcc   +
 *        GND   -
 *        
 *  
 *  Relay hookup 
 *    
 *    ard pins   relay 
 *      vcc       vcc
 *      gnd       GND 
 *      d5        IN1
 *      
 *      NOTE make sure that vcc and gnd are near the start of the vcc and gnd connections
 *        on the arduino
 *****************************************************************************************      
 *
 *
  */



#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include<SPI.h>
#include <avr/sleep.h> // fro sleeping

// variable declarations 

/* for Arduinio pro micro */
//RF24 radio (9,8);

/*for arduino UNO*/
RF24 radio (9,10);

  = 10; // lights when the interrupt is triggered
volatile byte  intChanger= 0; // variable that changes in the interrupt
int counter = 0; // for showing each iteration of loop 
byte moistureRead = 0; // the reading from the moisture sensor
int moistureSensor = A2; // moisture sensor pin
int wake = 0; // if set to zero interrupt has occured and the program goes into the main loop
int relay = 5; // input for relays



void setup(void) {
    
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN); // min works for the micro. with the UNO is works with MAX
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  radio.openReadingPipe(1, pipe);
  radio.enableDynamicPayloads();
  //radio.maskIRQ(1,1,0); // irq changes upon receiving data only
  radio.powerUp();
  pinMode (interruptLed, OUTPUT);
  pinMode(relay, OUTPUT); // relay OUTut
  sleep_enable(); // enables sleep capability
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //set the type of sleep mode. Default is Idle
  attachInterrupt(1, IRQ, CHANGE); // attaches an interrrupt if the irq detects a change
}

void loop(void) {
  
  Serial.println("in loop");
  while (wake == 0){
    // put your main code here, to run repeatedly:
    radio.startListening();
    Serial.println("Turning on the radio!");
    Serial.println ("Starting listening");
    char receivedMessage[32]= {0};
    if (radio.available()){
      radio.read(receivedMessage, sizeof(receivedMessage));
      Serial.println(receivedMessage);
      radio.stopListening();
      Serial.println("Turning off the radio!");
      String stringMessage(receivedMessage);  

      if (stringMessage == "one"){
        moistureRead = moistureReading(); // assign the result moistureRead () to moistureRead
        Serial.print("moistureRead is;");
        Serial.println(moistureRead);
        radio.write(&moistureRead, sizeof(moistureRead));
        }
      else if (stringMessage == "sleep"){
        Serial.println("in Sleep");
        //sleep_cpu();
        }
      //if (moi1stureRead < 100){
        //cycleRelay(20000);
      //}
      //radio.write(&moistureRead, sizeof(moistureRead));

      //radio.write(&moistureString, sizeof(moistureString));
      //Serial.println("We sent the message"); 
}
  delay(1000);
  counter++;
  Serial.println(counter);
}
  }
    
    


void IRQ(){
  //wake ++;
  sleep_disable();
}

/* 
 *  moisture sensor function 
*takes the average of 50 readings from the sensor and 
*then stores them in an array and takes the average of the array 50 inputs 
* returns the average
 */
int moistureReading(){
  // variable declarations
  unsigned long moistureValue = 0;  // to store value of analog read    
  int moistureArray[100]; 
  unsigned long moistureAvg = 0; // average of the moisture value
   
   // for moisture sensor
  for(int i = 0;i<100; i++){
      // read the value from the sensor:
      moistureValue = analogRead(moistureSensor);
      moistureValue = map(moistureValue, 0, 670, 0, 255);
      moistureArray[i] = moistureValue;
    }
  moistureAvg = moistureArray[0];
  
  // for calculating moisutre avg
  for(int i = 0;i<99; i++){
        moistureAvg += moistureArray[i+1];
    }

    moistureAvg = moistureAvg/99; 

    return moistureAvg;
  } // end moisturereading


void cycleRelay(int timeOn){
  Serial.println("in CycleRelay()");
  digitalWrite(relay, HIGH);
  delay(timeOn);
  digitalWrite(relay, LOW);
  Serial.println("leaving CycleRelay()");

} // end cycleRelay