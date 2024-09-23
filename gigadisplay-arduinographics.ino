/*
  Arduino GIGA Display - ArduinoGraphics Demo
  gigadisplay-arduinographics.ino
  Demonstrates ArduinoGraphics library functions
  Uses Arduino_H7_Video and ArduinoGraphics libraries
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include required libraries
#include "Arduino_H7_Video.h"
#include "ArduinoGraphics.h"

// Create a display object
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

void setup() {

  // Initialize display
  Display.begin();

  // Draw a red rectangle that covers the entire display
  Display.beginDraw();
  Display.clear();
  Display.noStroke();
  Display.fill(255, 0, 0);
  Display.rect(0, 0, Display.width(), Display.height());

  // Draw a 200px blue circle at coordinates 200,200
  Display.fill(0, 0, 255);
  Display.circle(200, 200, 200);

  // Draw a 300px green circle at coordinates 500,300
  Display.fill(0, 255, 0);
  Display.circle(500, 300, 300);

  // Finish drawing
  Display.endDraw();
}

void loop() {
}
