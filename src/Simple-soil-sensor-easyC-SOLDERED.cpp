/**
 **************************************************
 *
 * @file        Simple-soil-sensor-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Goran Juric, Karlo Leksic @ soldered.com
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
 * @return      Value of soil sensor in percent (0 - 100%)
 */
float SimpleSoilSensor::getValue()
{
    return (getRawValue() / float(1023) * 100);
}


/**
 * @brief       Function for reading raw value of soil sensor
 *
 * @return      Raw value of soil sensor (0 - 1023)
 */
uint16_t SimpleSoilSensor::getRawValue(void)
{
    if (!native)
    {
        // Read 2 bytes of raw  data
        char data[2];
        readData(data, 2);

        // Convert it to uint16_t
        uint16_t value = 0;
        value = *(uint16_t *)data;

        // Return converted value
        return value;
    }
    return analogRead(pin);
}

/**
 * @brief       Function for calculating resistance of soil sensor
 *
 * @return      Resistance of soil sensor
 */
float SimpleSoilSensor::getResistance()
{
    uint16_t temp = getRawValue();
    if (temp != 0)
    {
        return R * (temp / (float)(ADC_width - temp));
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
 * @brief       Function to set threshold value in percentage to turn on the LED
 *
 * @param       float _threshold value in %
 */
void SimpleSoilSensor::setThreshold(float _threshold)
{
    // Check if the threshold is the proper value
    if (_threshold < 0 || _threshold > 100)
    {
        return;
    }

    // Convert percentage threshold to raw value and send it
    uint16_t rawThreshold = _threshold * 0.01 * 1024;
    setRawThreshold(rawThreshold);
}

/**
 * @brief       Function to set raw threshold value to turn on the LED
 *
 * @param       uint16_t _threshold from 0 to 1023 (raw)
 */
void SimpleSoilSensor::setRawThreshold(uint16_t _treshold)
{
    // Check if the threshold is the proper value
    if (_treshold < 0 || _treshold > 1023)
    {
        return;
    }

    // Convert raw threshold value into 2 bytes for sending
    uint8_t *rawThreshold = (uint8_t *)&_treshold;

    // Send raw threshold
    sendData(rawThreshold, 2);
}
