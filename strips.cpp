#include "strips.h"

Strips::Strips(): hue(255), saturation(255), brightness(255) {
  // Setup leds // test
  FastLED.addLeds<NEOPIXEL, LED_STRIP1_PIN>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP2_PIN>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP3_PIN>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP4_PIN>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP5_PIN>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP6_PIN>(leds[5], NUM_LEDS_PER_STRIP);
}
void Strips::draw() {
  // leds[0][1] = CHSV(hue, saturation, brightness);
  FastLED.show();

}
void Strips::setPixel(int strip, int index, CHSV color) {
  leds[strip][index] = color;
}
void Strips::setPixel(int strip, int index, int h, int s, int b) {
  leds[strip][index] = CHSV(h, s, b);
}

void Strips::update() {
  hue = random(255);
  saturation = random(255);
  brightness = random(255);
}
void Strips::allLEDSToBlack() {
  for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    for (size_t x = 0; x < NUM_STRIPS; x++) {
      leds[x][i] = CHSV(0,0,0);
    }
  }
  FastLED.show();
}
