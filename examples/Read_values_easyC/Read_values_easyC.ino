/**
 **************************************************
 *
 * @file        Read_values_easyC.ino
 * @brief       Example for using the digital and analog read functions for Simple soil sensor with easyC
 *
 *              For this example, you will need any Dasduino board, a USB-c cable, a Simple soil sensor with easyC, and easyC cable.  
 *              Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ 
 *              Don't have easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 *
 *	product: www.solde.red/333040
 *
 * @authors     Goran Juric for Soldered.com
 ***************************************************/

// Connection diagram
// Plug easyC cable

// Include Soldered library for Simple sensor
// If you don't have a library, get it here:
// https://github.com/SolderedElectronics/Soldered-Simple-Soil-Humidity-Sensor-Arduino-Library
#include "Simple-soil-sensor-easyC-SOLDERED.h"

#define CALIBRATION_RESISTANCE_TIP_IN_WATER  30000
#define CALIBRATION_RESISTANCE_FULL_IN_WATER 10000

// Declare the sensor object
SimpleSoilSensor sensor;

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    // Start I2C communication on default address (0x30)
    sensor.begin();

    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // NOTE: You have to restart breakout to apply the address change by unplugging and plugging
    // the easyC or USB-c from the Dasduino
    // sensor.begin(0x31);

    // Sensor will work just fine if it is not calibrated
    // but since it is relying on resistance of water and
    // and water significantly changes resistance if it is
    // filled with particles, it smart idea to calibrate sometimes.
    // For calibration it is needed to measure resistance of sensor
    // when only tip is in water(about 5mm of sensor) and when
    // pads are completely in water and write them in
    // CALIBRATION_RESISTANCE_TIP_IN_WATER and CALIBRATION_RESISTANCE_FULL_IN_WATER
    sensor.calibrate(CALIBRATION_RESISTANCE_TIP_IN_WATER, CALIBRATION_RESISTANCE_FULL_IN_WATER);
}

void loop()
{
    Serial.print("Raw value of sensor: "); // Print information message
    Serial.print(sensor.getValue());       // Prints percent value of soil sensor
    Serial.print("% ");
    Serial.println(sensor.getRawValue()); // Prints raw value of soil sensor

    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());   // Prints resistance of soil sensor
    Serial.println(" Ohms.");               // Print information message

    Serial.print("Humidity: ");         // Print information message
    Serial.print(sensor.getHumidity()); // Prints raw value of soil sensor
    Serial.println(" %.");              // Print information message

    // Wait a bit before next reading
    delay(200);
}
