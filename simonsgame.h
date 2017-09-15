#ifndef SIMONSGAME_H
#define SIMONSGAME_H

#ifndef OTHER_INC
#define OTHER_INC
#include <Arduino.h>
#include "FastLED.h"
#include "Bounce.h"
#include "strips.h"
#endif

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 8


#define NUM_INPUTS 6
#define MAX_PATTERN_LENGTH 32
#define NUM_LEDS_PER_STRIP 8

#define BUTTON1 5
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 6

class Simonsgame {
public:
  int examplePattern[MAX_PATTERN_LENGTH];
  int playerPattern[MAX_PATTERN_LENGTH];
  int patternIndex;
  // CRGB* leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
  Strips* leds;

  bool notGameOver;
  bool notDone;
  int startPatternLength;
  int currentPatternLength = startPatternLength;
  int score;
  int brightness;

  int buttonPressed; // -1 for no button pressed


  // Simonsgame();
  Simonsgame(Strips* new_leds_ptr);
  void randomizePattern(int len);
  void showScore();
  void LEDSTest();

  void sequenceCorrectAnim();
  void sequenceWrongAnim();
  void flashRGB(CHSV color);
  void buttonToCatAnim(int button, CHSV color);
  void catToButtonAnim(int button, CHSV color);
  CHSV getColorFromButton(int button);
  void allButtonsToCat(CHSV color);
  int buttonToScaleInterval(int button);
  bool checkPattern();
  void loop();


};

#endif
