/**
 **************************************************
 *
 * @file        Read_values_easyC.ino
 * @brief       Example for using the digital and analog read functions for Simple light sensor with easyC
 *
 *
 *	product: www.solde.red/333076
 *
 * @authors     Goran Juric for Soldered.com
 ***************************************************/

#include "Simple-light-sensor-easyC-SOLDERED.h"

// Declare the sensor object
SimpleLightSensor sensor;

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    sensor.begin();

    // If different microcontroller with different bit width
    // is used, it should be set using this function
    sensor.setADCWidth(10);
}

void loop()
{
    Serial.print("Resistance of a LDR: "); // Print information message
    Serial.print(sensor.getResistance());  // Prints percent value of slider potentiometer
    Serial.println(" Ohms.");              // Print information message

    Serial.print("Light intensity: "); // Print information message
    Serial.print(sensor.getLux());     // Prints raw value of slider potentiometer
    Serial.println(" lux.");           // Print information message

    delay(1000);
}
