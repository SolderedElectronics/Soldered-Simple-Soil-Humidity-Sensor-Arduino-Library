/**
 **************************************************
 *
 * @file        Simple-soil-sensor-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/


#include "Simple-soil-sensor-easyC-SOLDERED.h"

/**
 * @brief                   Default constructor.
 *
 */
SimpleSoilSensor::SimpleSoilSensor()
{
}

/**
 * @brief                   Sensor specific native constructor.
 *
 * @param int _pin          Pin on which is sensor connected.
 */
SimpleSoilSensor::SimpleSoilSensor(int _pin)
{
    pin = _pin;
    native = 1;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void SimpleSoilSensor::initializeNative()
{
}

/**
 * @brief       Function for reading value of soil sensor
 *
 * @return      value of soil sensor
 */
uint32_t SimpleSoilSensor::getValue()
{
    if (!native)
    {
        Wire.beginTransmission(address);
        Wire.requestFrom(address, 2);

        if (Wire.available())
        {
            Wire.readBytes(data, 2);
        }
        Wire.endTransmission();

        resistance = *(uint16_t *)data;
        return resistance;
    }
    return analogRead(pin);
}

/**
 * @brief       Function for calculating resistance of soil sensor
 *
 * @return      resistance of soil sensor
 */
float SimpleSoilSensor::getResistance()
{
    uint16_t temp = getValue();
    if (temp != 0)
    {
        return R * temp / (float)(ADC_width - temp);
    }
    return 0;
}

/**
 * @brief       Function for calculating value of Soil humidity in percent
 *
 * @return      Soil humidity in percent
 */
float SimpleSoilSensor::getHumidity()
{
    uint32_t temp = getResistance();
    if (temp < low)
    {
        return 100;
    }
    if (temp > high)
    {
        return 0;
    }
    return a * temp + b;
}

/**
 * @brief       Function for calibrating sensor
 *
 * @param _high Calibration value for sensor in air
 *
 * @param _low Calibration value for sensor fully in water
 *
 */
void SimpleSoilSensor::calibrate(int _high, int _low)
{
    high = _high;
    low = _low;
    a = (90.0) / (_low - _high);
    b = 10 - a * _high;
}

/**
 * @brief       Function for setting ADC bit width of microcontroller
 *
 * @param       uint8_t _ADC_width ADC bit width in bits
 */
void SimpleSoilSensor::setADCWidth(uint8_t _ADC_width)
{
    ADC_width = pow(2, _ADC_width) - 1;
}

/**
 * @brief       Function to set threshold value to turn on the LED
 *
 * @param       byte _threshold value in %
 */
void SimpleSoilSensor::setThreshold(byte _threshold)
{
    if (_threshold > 100)
    {
        return;
    }
    threshold = _threshold;
    Wire.beginTransmission(address);
    Wire.write(threshold);
    Wire.endTransmission();
}
