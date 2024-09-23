/*
  Arduino GIGA Display - IMU Acceleration Demo
  gigadisplay-imu-test.ino
  Demonstrates operation of builtin IMU
  Displays acceleration on serial monitor
  Requires rduino_BMI270_BMM150 library
  Code provided by Arduino
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include libraries
#include "Arduino_BMI270_BMM150.h"

// Define IMU object on second I2C bus
BoschSensorClass imu(Wire1);

void setup() {
  // Start serial monitor
  Serial.begin(115200);

  // Start IMU
  imu.begin();
}

void loop() {
  // Variables for X, Y and Z axis
  float x, y, z;
  if (imu.accelerationAvailable()) {
    // Read acceleration values
    imu.readAcceleration(x, y, z);

    // Print to serial monitor
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
  }
}
