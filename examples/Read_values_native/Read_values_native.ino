/**
 **************************************************
 *
 * @file        Read_values_native.ino
 * @brief       Example for using the digital and analog read functions for Simple soil humidity sensor
 *
 *
 *  product: www.solde.red/333075
 *
 * @authors     Goran Juric for Soldered.com
 ***************************************************/

#include "Simple-soil-sensor-easyC-SOLDERED.h"

//Connecting diagram
//Breakout      Arduino
//|-------------|
//OUT-----------A0
//GND-----------GND
//VCC-----------5V

#define ANALOG_PIN A0
#define DIGITAL_PIN 9

// Declare the sensor object and set pin on which sensor is connected
SimpleSoilSensor sensor(ANALOG_PIN);

void setup()
{
    // Initialize the serial communication via UART
    Serial.begin(115200);

    // Initialize the sensor
    sensor.begin();

    //Sensor will work just fine if it is not calibrated
    //but since it is relying on resistance of water and
    //and water significantly changes resistance if it is
    //filled with particles, it smart idea to calibrate sometimes.
    //For calibration it is needed to measure resistance of sensor
    //when only tip is in water(about 5mm of sensor) and when 
    //pads are completely in water and write them in 
    //CALIBRATION_RESISTANCE_TIP_IN_WATER and CALIBRATION_RESISTANCE_FULL_IN_WATER
    sensor.calibrate(CALIBRATION_RESISTANCE_TIP_IN_WATER,CALIBRATION_RESISTANCE_FULL_IN_WATER);
}

void loop()
{
    Serial.print("Raw value of sensor: "); // Print information message
    Serial.println(sensor.getValue());  // Prints percent value of soil sensor
    
    Serial.print("Resistance of sensor: "); // Print information message
    Serial.print(sensor.getResistance());  // Prints percent value of soil sensor
    Serial.println(" Ohms.");              // Print information message

    Serial.print("Light intensity: "); // Print information message
    Serial.print(sensor.getHumidity());     // Prints raw value of soil sensor
    Serial.println(" %.");           // Print information message

    delay(1000);
}
