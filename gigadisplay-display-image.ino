/*
  Arduino GIGA Display - Display Image
  gigadisplay-display-image.ino
  Demonstrates operation of onboard RGB LED
  Requires Arduino_H7_Video and ArduinoGraphics Libraries
  Requires incbin.h by Dale Weiler
  Code example "ArduinoLogo" by Leonardo Cavagnis
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include required libraries
#include "Arduino_H7_Video.h"
#include "ArduinoGraphics.h"

// Any raw RGB565 image can be included on demand using this macro
// Online image converter: https://lvgl.io/tools/imageconverter (Output format: Binary RGB565)
// Download *.bin file and note file path

#define INCBIN_PREFIX
#include "incbin.h"
// Replace with path to your *.bin file
INCBIN(test, "/home/dronebotworkshop/Downloads/robot-redarms-358x422.bin");

// Create display object
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

// Define image variable with parameters (edit size parameter as required)
Image img_robot(ENCODING_RGB16, (uint8_t *) testData, 358, 422);

void setup() {
  // Start display
  Display.begin();

  // Draw image in center of display
  Display.beginDraw();
  Display.image(img_robot, (Display.width() - img_robot.width())/2, (Display.height() - img_robot.height())/2);
  Display.endDraw();
}

void loop() { }