#include "simonsgame.h"

Simonsgame::Simonsgame(Strip* new_leds) {
// Simonsgame::Simonsgame() {
  int examplePattern[MAX_PATTERN_LENGTH];
  int playerPattern[MAX_PATTERN_LENGTH];
  int patternIndex = 0;

  bool notGameOver = true;
  bool notDone = true;
  int startPatternLength = 3;
  int currentPatternLength = startPatternLength;
  leds = new_leds;


}
void Simonsgame::randomizePattern(int len) {
  for (size_t i = 0; i < len; i++) {
    examplePattern[i] = random(NUM_INPUTS);
    // examplePattern[i] = i;
  }
}
void Simonsgame::showScore() {
  // for (size_t i = 0; i < score; i++) {
  //   // light light
  //   // play note
  //   int light = i % NUM_LEDS_PER_STRIP;
  //   int strip = i / NUM_LEDS_PER_STRIP;
  //   usbMIDI.sendNoteOn(84+i,32,0);
  //   int hue = (0 + i * 25 ) %256;
  //       leds->setPixel(strip, light, hue, 255, brightness / 2);
  //       // leds[0 + strip][i % NUM_LEDS_PER_STRIP] = CHSV(hue,255,brightness/2);
  //       // leds[1][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
  //       // leds[3][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
  // FastLED.show();
  // delay(50+ i*10);
  //   usbMIDI.sendNoteOff(84+i,127,0);
  //   Serial.println(i);
  // }
  // delay(1000);
  // allLEDSToBlack();
}
