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
uint16_t SimpleSoilSensor::getValue()
{
    if (!native)
    {
        readRegister(ANALOG_READ_REG, raw, 2 * sizeof(uint8_t));
        return raw[0] | (raw[1]) << 8;
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
    uint16_t temp = getResistance();
    if (temp < 25000)
    {
        return 100;
    }
    if (temp > 150000)
    {
        return 0;
    }
    return -0.65 * temp + 116.2;
}

/**
 * @brief       Function for calculating value of Soil humidity in percent
 *
 * @return      Soil humidity in percent
 */
void SimpleSoilSensor::calibrate(int _high, int _low)
{
    a = (_low - _high) / (90.0);
    b = 10 - a * _high;
}