/**
 **************************************************
 *
 * @file        Simple-soil-humidity-sensor-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#ifndef _SIMPLE_SOIL_SENSOR_EASYC_
#define _SIMPLE_SOIL_SENSOR_EASYC_

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.h"
#include "math.h"

#define R 10000

class SimpleSoilSensor : public SIMPLE_SOIL_SENSOR_EASYC::EasyC
{
  public:
    SimpleSoilSensor();
    SimpleSoilSensor(int);
    uint32_t getValue(void);
    float getResistance(void);
    float getHumidity(void);
    void calibrate(int, int);

  protected:
    void initializeNative();

  private:
    float a, b, high = 160000, low=20000;
    int pin;
    uint16_t ADC_width = 1023;
    char raw[2];
};

#endif
