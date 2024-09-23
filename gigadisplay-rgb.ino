/*
  Arduino GIGA Display - RGB LED Test
  gigadisplay-rgb.ino
  Demonstrates operation of onboard RGB LED
  Requires Arduino_GigaDisplay Library
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include library
#include <Arduino_GigaDisplay.h>

// Create RGB object
GigaDisplayRGB rgb;

void setup() {
  // Initialize the RGB object
  rgb.begin();
}

void loop() {

  // Turn on red pixel
  rgb.on(255, 0, 0);
  delay(1000);
  // Turn off all pixels
  rgb.off();
  delay(1000);

  // Turn on green pixel
  rgb.on(0, 255, 0);
  delay(1000);
  // Turn off all pixels
  rgb.off();
  delay(1000);

  // Turn on blue pixel
  rgb.on(0, 0, 255);
  delay(1000);
  // Turn off all pixels
  rgb.off();
  delay(1000);

  // Turn on all pixels
  rgb.on(255, 255, 255);
  delay(1000);
  // Turn off all pixels
  rgb.off();
  delay(1000);
}
