/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

class Sensor : public EasyC
{
  public:
  /**
   * @brief                   Sensor specific native constructor.
   *
   * @param int _pin          Example parameter.
   */
    Sensor(int _pin);

  protected:
  /**
   * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
   */
    void initializeNative();

  private:
    int pin;
};

#endif
