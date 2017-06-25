#include <Arduino.h>
#include "FastLED.h"
// The Plan
// a bunch of events get stored in arrays
/*
[1][2][1][2][3][3]
you follow those events with inputs
[1][2][1][3][2]
untill you loose
every couple (10) events an animation plays
event manager
plays events
generate new events and assign them to arrays
increase arrayLengthCounter
read inputs
*/
/* Variables */
#define LED_STRIP1_PIN 14
#define LED_STRIP2_PIN 15
#define LED_STRIP3_PIN 16
#define LED_STRIP4_PIN 17
#define NUM_LEDS 8
#define NUM_INPUTS 4


#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define BUTTON4 4
#define LED 13

#define MAX_PATTERN_LENGTH 10
int examplePattern[MAX_PATTERN_LENGTH];
int playerPattern[MAX_PATTERN_LENGTH];
int patternIndex = 0;

bool notGameOver = true;
bool notDone = true;
int startPatternLength = 3;
int currentPatternLength = startPatternLength;
CRGB leds[NUM_LEDS];
int ledIndex = 0;
int rgbIndex = 0;
int brightness = 255;

void setup() {
  Serial.begin(115200);
  // Setup variables
  for (int i = 0; i < MAX_PATTERN_LENGTH ; i++) {
    examplePattern[i] = i;
    Serial.println(examplePattern[i]);
  }

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Setup leds // test
  FastLED.addLeds<NEOPIXEL, LED_STRIP1_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_STRIP2_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_STRIP3_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, LED_STRIP4_PIN>(leds, NUM_LEDS);
  // leds[ledIndex][rgbIndex] = brightness;
  // FastLED.show();
}
void randomizePattern(int len) {
  for (size_t i = 0; i < len; i++) {
    examplePattern[i] = random(NUM_INPUTS);
    // examplePattern[i] = i;
  }
}

void flashCorrect() {
  for (size_t i = 0; i < 4; i++) {
    leds[i][1] = 255;
    FastLED.show();
    delay(80);
  }
  for (size_t i = 0; i < 4; i++) {
    leds[i][1] = 0;
    FastLED.show();
    delay(50);
  }
}
void flashError() {
  for (size_t i = 0; i < 4; i++) {
    leds[i][0] = 255;
    FastLED.show();
    delay(80);
  }
  for (size_t i = 0; i < 4; i++) {
    leds[i][0] = 0;
    FastLED.show();
    delay(50);
  }
}


bool checkPattern() {
  for (int i = 0; i < currentPatternLength; i++) {
    if (playerPattern[i] != examplePattern[i] ) {
      return false;
    }
  }
  return true;
}
void playEvent(int event) {
  // flash a led for 250ms
  // event 0 - 3
  int waitTime = 320;
  ledIndex = event;
  rgbIndex = 2; // Blue
  leds[ledIndex][rgbIndex] = brightness;
  FastLED.show();
  delay(waitTime);
  leds[ledIndex][rgbIndex] = 0;
  FastLED.show();
  delay(waitTime / 2);
}
void loop() {
  // play example pattern
  randomizePattern(currentPatternLength);
  for (size_t i = 0; i < currentPatternLength; i++) {
    playEvent(examplePattern[i]);
  }

  // *** Pattern Input Loop
  bool notDone = true;
  Serial.println("strting while");
  while (notDone) {
    // fill player pattern with their presses
    int but1 = digitalRead(BUTTON1);
    int but2 = digitalRead(BUTTON2);
    int but3 = digitalRead(BUTTON3);
    int but4 = digitalRead(BUTTON4);
    int buttonPressed = -1;

    if(but1 == LOW ) {
      buttonPressed = 0;
    } else if (but2 == LOW) {
      buttonPressed = 1;
    } else if (but3 == LOW) {
      buttonPressed = 2;
    } else if (but4 == LOW) {
      buttonPressed = 3;
    }

      // process Input
    if (buttonPressed > -1) {
      // assign to patternArray[]
      // visualize Input
      playEvent(buttonPressed);
      playerPattern[patternIndex] = buttonPressed;

      // ready for next input
      patternIndex += 1;
    }

    if (patternIndex >= currentPatternLength) {
      // we are done with this wave of patterns break out of the while loop
      patternIndex = 0;
      notDone = false;
    }

  } // end while


  // Done with the input into the player Pattern
  bool isCorrect = checkPattern();
  if (isCorrect) {
    // play victory
    // increase dificulty
    currentPatternLength += 1;
    flashCorrect();
    delay(80);
  } else {
    // gameover state
    // restart
    flashError();
    delay(80);
    currentPatternLength = startPatternLength;
    // play loose
  }

}
