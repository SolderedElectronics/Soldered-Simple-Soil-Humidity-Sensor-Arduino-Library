/**
 **************************************************
 *
 * @file        Simple-soil-humidity-sensor-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksic @ soldered.com
 ***************************************************/

#ifndef _SIMPLE_SOIL_SENSOR_EASYC_
#define _SIMPLE_SOIL_SENSOR_EASYC_

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"
#include "math.h"

#define R 10000

class SimpleSoilSensor : public EasyC
{
  public:
    SimpleSoilSensor();
    SimpleSoilSensor(int);
    float getValue(void);
    uint16_t getRawValue(void);
    float getResistance(void);
    float getHumidity(void);
    void calibrate(int, int);
    void setADCWidth(uint8_t);
    void setThreshold(float);
    void setRawThreshold(uint16_t);

  protected:
    void initializeNative();

  private:
    float a, b, high = 160000, low = 20000;
    int pin;
    uint16_t ADC_width = 1023;
    byte data[2];
    float threshold;
    uint16_t resistance;
};

#endif
