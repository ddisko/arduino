/*
  Arduino GIGA Display - Microphone Demo
  gigadisplay-microphone.ino
  Demonstrates operation of builtin microphone
  Displays audio level on bargraph
  Requires PDM, Arduino_H7_Video and lvgl library
  Code provided by Arduino
  
  DroneBot Workshop 2023
  https://dronebotworkshop.com
*/

// Include libraries
#include <PDM.h>
#include "Arduino_H7_Video.h"
#include "lvgl.h"

// Create display object
Arduino_H7_Video Display(800, 480, GigaDisplayShield);

// Slider
static void set_slider_val(void *bar, int32_t val) {
  lv_bar_set_value((lv_obj_t *)bar, val, LV_ANIM_ON);
}

// Default number of output channels
static const char channels = 1;

// Default PCM output frequency
static const int frequency = 16000;

// Buffer to read samples into, each sample is 16-bits
short sampleBuffer[512];

// Number of audio samples read
volatile int samplesRead;

lv_obj_t *obj;
lv_anim_t a;
int micValue;

void setup() {
  // Initialize Display
  Display.begin();

  // Setup callback
  PDM.onReceive(onPDMdata);

  // Start PDM
  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1)
      ;
  }

  // Create the bar
  obj = lv_bar_create(lv_scr_act());
  lv_obj_set_size(obj, 600, 50);
  lv_obj_center(obj);
  lv_bar_set_value(obj, 500, LV_ANIM_OFF);

  // Create the animation for the bar
  lv_anim_init(&a);
  lv_anim_set_exec_cb(&a, set_slider_val);
  lv_anim_set_time(&a, 300);
  lv_anim_set_playback_time(&a, 300);
  lv_anim_set_var(&a, obj);
}

void loop() {

  // Wait for samples to be read
  if (samplesRead) {

    // Print samples to the serial monitor or plotter
    for (int i = 0; i < samplesRead; i++) {
      Serial.println(sampleBuffer[i]);
      micValue = sampleBuffer[i];
      micValue = micValue / 10;  // Adjust divisor for sensitivity
      if (micValue > 500) {
        micValue = 500;
      }
      lv_anim_set_values(&a, 0, micValue);
      lv_anim_start(&a);
    }

    // Clear the read count
    samplesRead = 0;
    delay(10);
  }
  lv_timer_handler();
}

// Callback function to process the data from the PDM microphone.

void onPDMdata() {
  // Query the number of available bytes
  int bytesAvailable = PDM.available();

  // Read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}
