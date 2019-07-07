/*
 * MyRelay.cpp
 *
 *  Created on: 3 Jun 2019
 *      Author: peter
 */

#include "MyRelay.h"
#include "Arduino.h"
#include "Component.h"

void MyRelay::Begin(){
    pinMode(_pin, OUTPUT);
};

void MyRelay::On(){
    digitalWrite(_pin, HIGH);
};

void MyRelay::Off(){
    digitalWrite(_pin, LOW);
};



