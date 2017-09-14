#ifndef SIMONSGAME_H
#define SIMONSGAME_H

#ifndef OTHER_INC
#define OTHER_INC
#include <Arduino.h>
#include "FastLED.h"
#include "Bounce.h"
#include "strip.h"
#endif

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 8


#define NUM_INPUTS 6
#define MAX_PATTERN_LENGTH 32
#define NUM_LEDS_PER_STRIP 8

class Simonsgame {
public:
  int examplePattern[MAX_PATTERN_LENGTH];
  int playerPattern[MAX_PATTERN_LENGTH];
  int patternIndex;
  // CRGB* leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
  Strip* leds;

  bool notGameOver;
  bool notDone;
  int startPatternLength;
  int currentPatternLength = startPatternLength;

  // Simonsgame();
  Simonsgame(Strip* new_leds);
  void randomizePattern(int len);
  void showScore();

};

#endif
