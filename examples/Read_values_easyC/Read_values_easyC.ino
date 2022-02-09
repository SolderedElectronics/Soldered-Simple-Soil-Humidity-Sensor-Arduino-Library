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

#include "Simple-soil-sensor-easyC-SOLDERED.h"

// Declare the sensor object
SimpleSoilSensor sensor;

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    sensor.begin();

}

void loop()
{
    Serial.print("Resistance of a LDR: "); // Print information message
    Serial.print(sensor.getResistance());  // Prints percent value of soil sensor
    Serial.println(" Ohms.");              // Print information message

    Serial.print("Light intensity: "); // Print information message
    Serial.print(sensor.getHumidity());     // Prints raw value of soil sensor
    Serial.println(" %.");           // Print information message

    delay(1000);
}
