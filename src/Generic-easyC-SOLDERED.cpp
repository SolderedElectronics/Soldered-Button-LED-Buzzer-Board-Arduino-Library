/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/


#include "Generic-easyC-SOLDERED.h"


Sensor::Sensor(int _pin)
{
    pin = _pin;
    native = 1;
}

void Sensor::initializeNative()
{
    pinMode(pin, INPUT);
}
