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

/* Story

SphinxCat Says
Your pet cat has awaked its true egyption soul sucking potential
Pray to it and feed it souls or else the world will be destroyed



*/
#define LED_STRIP1_PIN 18
#define LED_STRIP2_PIN 14
#define LED_STRIP3_PIN 15
#define LED_STRIP4_PIN 16
#define LED_STRIP5_PIN 17
#define LED_STRIP6_PIN 19

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 8
#define NUM_INPUTS 6


#define BUTTON1 5
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 6

#define MAX_PATTERN_LENGTH 10
int examplePattern[MAX_PATTERN_LENGTH];
int playerPattern[MAX_PATTERN_LENGTH];
int patternIndex = 0;

bool notGameOver = true;
bool notDone = true;
int startPatternLength = 3;
int currentPatternLength = startPatternLength;
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

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
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);

  // Setup leds // test
  FastLED.addLeds<NEOPIXEL, LED_STRIP1_PIN>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP2_PIN>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP3_PIN>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP4_PIN>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP5_PIN>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_STRIP6_PIN>(leds[5], NUM_LEDS_PER_STRIP);
  // leds[ledIndex][rgbIndex] = brightness;
  // FastLED.show();
}
void randomizePattern(int len) {
  for (size_t i = 0; i < len; i++) {
    examplePattern[i] = random(NUM_INPUTS);
    // examplePattern[i] = i;
  }
}

void sequenceCorrectAnim() {
  allButtonsToCat(CRGB::Green);
}
void flashRGB(CRGB color) {
  // flash 2 times on off, on off
  int times = 2;
  for (size_t t = 0; t < 2; t++) {
    // Turn on Green
    for (size_t i = 0; i < 4; i++) {
      for (size_t x = 0; x < NUM_STRIPS; x++) {
        leds[x][i] = color;
      }
    }
    FastLED.show();
    delay(200);
    // Turn off Green
    for (size_t i = 0; i < 4; i++) {
      for (size_t x = 0; x < NUM_STRIPS; x++) {
        leds[x][i] = CRGB::Black;
      }
    }
    FastLED.show();
    delay(150);
  }
}
void sequenceWrongAnim() {
  // flash error
  flashRGB(CRGB::Red);
}


bool checkPattern() {
  for (int i = 0; i < currentPatternLength; i++) {
    if (playerPattern[i] != examplePattern[i] ) {
      return false;
    }
  }
  return true;
}
void buttonToCatAnim(int button, CRGB color) {
  // flash a led for 250ms
  // event 0 - 3
  int waitTime = 40;
  int strip = button ;

  // Draw strip
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    leds[strip][i] = color;
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    leds[strip][i] = CRGB::Black;
    FastLED.show();
    delay(waitTime / 2);
  }
}
void catToButtonAnim(int button, CRGB color) {
  // flash a led for 250ms
  // event 0 - 3
  int waitTime = 40;
  int strip = button ;

  // Draw strip
  for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[strip][i] = color;
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[strip][i] = CRGB::Black;
    FastLED.show();
    delay(waitTime / 2);
  }
}
void allButtonsToCat(CRGB color) {
  // all strips shine green into the cat
  int rgbIndex = 1; // green
  int waitTime = 30;
  int brightness = 255;
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    for (size_t x = 0; x < NUM_STRIPS; x++) {
      leds[x][i] = color;
    }
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    for (size_t x = 0; x < NUM_STRIPS; x++) {
      leds[x][i] = CRGB::Black;
    }
    FastLED.show();
    delay(waitTime / 2);
  }
}
void loop() {
  // play example pattern
  randomizePattern(currentPatternLength);
  for (size_t i = 0; i < currentPatternLength; i++) {
    int button = examplePattern[i];
    usbMIDI.sendNoteOn(84+button,127,0);
    catToButtonAnim(button, CRGB::Blue);
    usbMIDI.sendNoteOff(84+button,127,0);
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
    int but5 = digitalRead(BUTTON5);
    int but6 = digitalRead(BUTTON6);
    int buttonPressed = -1;

    if(but1 == LOW ) {
      buttonPressed = 0;
    } else if (but2 == LOW) {
      buttonPressed = 1;
    } else if (but3 == LOW) {
      buttonPressed = 2;
    } else if (but4 == LOW) {
      buttonPressed = 3;
    } else if (but5 == LOW) {
      buttonPressed = 4;
    } else if (but6 == LOW) {
      buttonPressed = 5;
    }

      // process Input
    if (buttonPressed > -1) {
      // assign to patternArray[]
      // visualize Input
      usbMIDI.sendNoteOn(84 + buttonPressed,127,0);
      buttonToCatAnim(buttonPressed, CRGB::DarkSlateBlue);
      usbMIDI.sendNoteOff(84 + buttonPressed,127,0);
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
    usbMIDI.sendNoteOn(84+12,127,0);
    sequenceCorrectAnim();
    usbMIDI.sendNoteOff(84+12,127,0);
    delay(80);
  } else {
    // gameover state
    // restart
    int note = 54;
    int vel = 127;
    int channel = 0;
    usbMIDI.sendNoteOn(note, vel, channel);
    sequenceWrongAnim();
    delay(80);
    usbMIDI.sendNoteOff(note, vel, channel);
    currentPatternLength = startPatternLength;
    // play loose
  }

}
