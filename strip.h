#ifndef STRIP_H
#define STRIP_H

#ifndef OTHER_INC
#define OTHER_INC
#include <Arduino.h>
#include "FastLED.h"
#include "Bounce.h"
#endif

#define NUM_LEDS_PER_STRIP 8
#define NUM_STRIPS 6

#define LED_STRIP1_PIN 18
#define LED_STRIP2_PIN 14
#define LED_STRIP3_PIN 15
#define LED_STRIP4_PIN 16
#define LED_STRIP5_PIN 17
#define LED_STRIP6_PIN 19


class Strip {
  public:
  int pin;
  int brightness;
  int hue;
  int saturation;
  int state; // 0 none, 1 draw up pattern, 2 draw down pattern
  // CRGB leds[NUM_LEDS_PER_STRIP];
  CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

  Strip();
  void clear();
  void setPixel(int strip, int index, int h, int s, int b);
  void draw();
  void update();

};

#endif
