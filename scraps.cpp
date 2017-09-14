// #include <Arduino.h>
// #include "FastLED.h"
// // #include "Bounce.h"
// // The Plan
// // a bunch of events get stored in arrays
// /*
// [1][2][1][2][3][3]
// you follow those events with inputs
// [1][2][1][3][2]
// untill you loose
// every couple (10) events an animation plays
// event manager
// plays events
// generate new events and assign them to arrays
// increase arrayLengthCounter
// read inputs
// */
// /* Variables */
//
// /* Story
//
// SphinxCat Says
// Your pet cat has awaked its true egyption soul sucking potential
// Pray to it and feed it souls or else the world will be destroyed
//
//
//
// */
// Bounce button1 = Bounce(1, 5);
// Bounce button2 = Bounce(2, 5);
// Bounce button3 = Bounce(3, 5);
// Bounce button4 = Bounce(4, 5);
// Bounce button5 = Bounce(5, 5);
// Bounce button6 = Bounce(6, 5);
//
// #define LED_STRIP1_PIN 18
// #define LED_STRIP2_PIN 14
// #define LED_STRIP3_PIN 15
// #define LED_STRIP4_PIN 16
// #define LED_STRIP5_PIN 17
// #define LED_STRIP6_PIN 19
//
// #define NUM_STRIPS 6
// #define NUM_LEDS_PER_STRIP 8
// #define NUM_INPUTS 6
//
//
// #define BUTTON1 5
// #define BUTTON2 1
// #define BUTTON3 2
// #define BUTTON4 3
// #define BUTTON5 4
// #define BUTTON6 6
//
// #define MAX_PATTERN_LENGTH 32
// int examplePattern[MAX_PATTERN_LENGTH];
// int playerPattern[MAX_PATTERN_LENGTH];
// int patternIndex = 0;
//
// bool notGameOver = true;
// bool notDone = true;
// int startPatternLength = 3;
// int currentPatternLength = startPatternLength;
// CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
//
// int highScore = 3;
// int score = 0;
// int ledIndex = 0;
// int rgbIndex = 0;
// int brightness = 255;
//
// int buttonPressed = -1;
//
// int root = 50;
//
// void setup() {
//   Serial.begin(115200);
//   // Setup variables
//   for (int i = 0; i < MAX_PATTERN_LENGTH ; i++) {
//     examplePattern[i] = i;
//     Serial.println(examplePattern[i]);
//   }
//
//   pinMode(BUTTON1, INPUT_PULLUP);
//   pinMode(BUTTON2, INPUT_PULLUP);
//   pinMode(BUTTON3, INPUT_PULLUP);
//   pinMode(BUTTON4, INPUT_PULLUP);
//   pinMode(BUTTON5, INPUT_PULLUP);
//   pinMode(BUTTON6, INPUT_PULLUP);
//
//   // Setup leds // test
//   FastLED.addLeds<NEOPIXEL, LED_STRIP1_PIN>(leds[0], NUM_LEDS_PER_STRIP);
//   FastLED.addLeds<NEOPIXEL, LED_STRIP2_PIN>(leds[1], NUM_LEDS_PER_STRIP);
//   FastLED.addLeds<NEOPIXEL, LED_STRIP3_PIN>(leds[2], NUM_LEDS_PER_STRIP);
//   FastLED.addLeds<NEOPIXEL, LED_STRIP4_PIN>(leds[3], NUM_LEDS_PER_STRIP);
//   FastLED.addLeds<NEOPIXEL, LED_STRIP5_PIN>(leds[4], NUM_LEDS_PER_STRIP);
//   FastLED.addLeds<NEOPIXEL, LED_STRIP6_PIN>(leds[5], NUM_LEDS_PER_STRIP);
//   // leds[ledIndex][rgbIndex] = brightness;
//   // FastLED.show();
// }
// void randomizePattern(int len) {
//   for (size_t i = 0; i < len; i++) {
//     examplePattern[i] = random(NUM_INPUTS);
//     // examplePattern[i] = i;
//   }
// }
// void showScore() {
//   for (size_t i = 0; i < score; i++) {
//     // light light
//     // play note
//     int light = i % NUM_LEDS_PER_STRIP;
//     int strip = i / NUM_LEDS_PER_STRIP;
//     usbMIDI.sendNoteOn(84+i,32,0);
//     int hue = (0 + i * 25 ) %256;
//         leds[0 + strip][i % NUM_LEDS_PER_STRIP] = CHSV(hue,255,brightness/2);
//         // leds[1][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
//         // leds[3][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
//   FastLED.show();
//   delay(50+ i*10);
//     usbMIDI.sendNoteOff(84+i,127,0);
//     Serial.println(i);
//   }
//   delay(1000);
//   allLEDSToBlack();
// }
//
// void sequenceCorrectAnim() {
//   allButtonsToCat(CHSV(96,255,brightness));
// }
// void allLEDSToBlack() {
//   for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//     for (size_t x = 0; x < NUM_STRIPS; x++) {
//       leds[x][i] = CHSV(0,0,0);
//     }
//   }
//   FastLED.show();
// }
// void flashRGB(CHSV color) {
//   // flash 2 times on off, on off
//   int times = 2;
//   for (size_t t = 0; t < 2; t++) {
//     // Turn on Green
//     for (size_t i = 0; i < 4; i++) {
//       for (size_t x = 0; x < NUM_STRIPS; x++) {
//         leds[x][i] = color;
//         leds[x][i] = color;
//       }
//     }
//     FastLED.show();
//     delay(200);
//     // Turn off Green
//     for (size_t i = 0; i < 4; i++) {
//       for (size_t x = 0; x < NUM_STRIPS; x++) {
//         leds[x][i] = CHSV(0,0,0);
//       }
//     }
//     FastLED.show();
//     delay(150);
//   }
// }
// void sequenceWrongAnim() {
//   // flash error
//   flashRGB(CHSV(0,255,brightness));
// }
//
//
// bool checkPattern() {
//   for (int i = 0; i < currentPatternLength; i++) {
//     if (playerPattern[i] != examplePattern[i] ) {
//       return false;
//     }
//   }
//   return true;
// }
// void buttonToCatAnim(int button, CHSV color) {
//   // flash a led for 250ms
//   // event 0 - 3
//   int waitTime = 40;
//   int strip = button ;
//
//   // Draw strip
//   for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
//     leds[strip][i] = color;
//     FastLED.show();
//     delay(waitTime);
//   }
//   for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
//     leds[strip][i] = CHSV(0,0,0);
//     FastLED.show();
//     delay(waitTime / 2);
//   }
// }
// void stripOnColor(int button, CHSV color) {
//   // flash a led for 250ms
//   // event 0 - 3
//   int strip = button ;
//
//   // Draw strip
//   for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
//     leds[strip][i] = color;
//     FastLED.show();
//   }
// }
// void catToButtonAnim(int button, CHSV color) {
//   // flash a led for 250ms
//   // event 0 - 3
//   int waitTime = 40;
//   int strip = button ;
//
//   // Draw strip
//   for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//     leds[strip][i] = color;
//     FastLED.show();
//     delay(waitTime);
//   }
//   for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//     leds[strip][i] = CHSV(0,0,0);
//     FastLED.show();
//     delay(waitTime / 2);
//   }
// }
// CHSV getColorFromButton(int button) {
//   int brightness = 127;
//   CHSV color = CHSV(0,255,brightness);
//   if (button == 0) {
//     color = CHSV(244, 255, brightness);
//   } else if (button == 1) {
//     color = CHSV(0, 255, brightness);
//   } else if (button == 2) {
//     color = CHSV(64, 255, brightness);
//   } else if (button == 3) {
//     color = CHSV(96, 255, brightness);
//   } else if (button == 4) {
//     color = CHSV(160, 255, brightness);
//   } else if (button == 5) {
//     color = CHSV(192, 255, brightness);
//   }
//   return color;
// }
// void allButtonsToCat(CHSV color) {
//   // all strips shine green into the cat
//   int rgbIndex = 1; // green
//   int waitTime = 30;
//   int brightness = 255;
//   for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
//     for (size_t x = 0; x < NUM_STRIPS; x++) {
//       leds[x][i] = color;
//     }
//     FastLED.show();
//     delay(waitTime);
//   }
//   for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
//     for (size_t x = 0; x < NUM_STRIPS; x++) {
//       leds[x][i] = CHSV(0,0,0);
//     }
//     FastLED.show();
//     delay(waitTime / 2);
//   }
// }
// int buttonToScaleInterval(int button) {
//   int interval = 0;
//   if(button == 0) {
//     interval = 0;
//   } else if (button == 1) {
//     interval = 2;
//   } else if (button == 2) {
//     interval = 5;
//   } else if (button == 3) {
//     interval = 7;
//   } else if (button == 4) {
//     interval = 10;
//   } else if (button == 5) {
//     interval = 12;
//   }
//   return interval;
// }
// void dannyLamp() {
//   for (size_t i = 0; i < 255; i++) {
//     allButtonsToCat(CHSV(i,255,brightness));
//   }
// }
// void loop() {
//   //dannyLamp();
//   if (Serial.available() > 0) {
//     while(1) {
//       // Enter keyboard mode
//       button1.update();
//       button2.update();
//       button3.update();
//       button4.update();
//       button5.update();
//       button6.update();
//
//       //Presses
//       if(button1.fallingEdge()) {
//         usbMIDI.sendNoteOn(root, 127, 1);
//         leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(224,255,brightness);
//         FastLED.show();
//
//       }
//       if(button1.risingEdge()) {
//         usbMIDI.sendNoteOff(root,127,1);
//         leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//       if(button2.fallingEdge()) {
//         usbMIDI.sendNoteOn(root + 2, 127, 1);
//         leds[1][root % NUM_LEDS_PER_STRIP] = CHSV(244,255,brightness);
//         FastLED.show();
//       }
//       if(button2.risingEdge()) {
//         usbMIDI.sendNoteOff(root + 2,127,1);
//         leds[1][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//       if(button3.fallingEdge()) {
//         usbMIDI.sendNoteOn(root + 5, 127, 1);
//         leds[2][root % NUM_LEDS_PER_STRIP] = CHSV(0,255,brightness);
//         FastLED.show();
//       }
//       if(button3.risingEdge()) {
//         usbMIDI.sendNoteOff(root + 5,127,1);
//         leds[2][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//       if(button4.fallingEdge()) {
//         usbMIDI.sendNoteOn(root + 7, 127, 1);
//         leds[3][root % NUM_LEDS_PER_STRIP] = CHSV(64,255,brightness);
//         FastLED.show();
//       }
//       if(button4.risingEdge()) {
//         usbMIDI.sendNoteOff(root + 7,127,1);
//         leds[3][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//       if(button5.fallingEdge()) {
//         usbMIDI.sendNoteOn(root + 10, 127, 1);
//         leds[4][root % NUM_LEDS_PER_STRIP] = CHSV(96,255,brightness);
//         FastLED.show();
//       }
//       if(button5.risingEdge()) {
//         usbMIDI.sendNoteOff(root + 10,127,1);
//         leds[4][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//       if(button6.fallingEdge()) {
//         root += 1;
//         usbMIDI.sendNoteOn(root + 12, 127, 1);
//         leds[5][root % NUM_LEDS_PER_STRIP] = CHSV(160,255,brightness);
//         FastLED.show();
//       }
//       if(button6.risingEdge()) {
//         usbMIDI.sendNoteOff(root + 12,127,1);
//         leds[5][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
//         FastLED.show();
//       }
//
//       int interval = 0;
//       buttonPressed = -1;
//
//       // if(but1 == LOW ) {
//       //   buttonPressed = 0;
//       // } else if (but2 == LOW) {
//       //   buttonPressed = 1;
//       // } else if (but3 == LOW) {
//       //   buttonPressed = 2;
//       // } else if (but4 == LOW) {
//       //   buttonPressed = 3;
//       // } else if (but5 == LOW) {
//       //   buttonPressed = 4;
//       // } else if (but6 == LOW) {
//       //   buttonPressed = 5;
//       // }
//       //
//       //   if (buttonPressed > -1) {
//       //     interval = buttonToScaleInterval(buttonPressed);
//       //     usbMIDI.sendNoteOn(84+interval, 127, 0);
//       //     delay(40);
//       //     usbMIDI.sendNoteOff(84+interval, 127, 0);
//       //     delay(40);
//       //   }
//     }
//   }
//   // play example pattern
//   randomizePattern(currentPatternLength);
//   for (size_t i = 0; i < currentPatternLength; i++) {
//     int button = examplePattern[i];
//     int interval = buttonToScaleInterval(button);
//     usbMIDI.sendNoteOn(84+interval,127,0);
//     CHSV color = getColorFromButton(button);
//     catToButtonAnim(button, color);
//     usbMIDI.sendNoteOff(84+interval,127,0);
//   }
//
//   // *** Pattern Input Loop
//   bool notDone = true;
//   Serial.println("strting while");
//   while (notDone) {
//     // fill player pattern with their presses
//     int but1 = digitalRead(BUTTON1);
//     int but2 = digitalRead(BUTTON2);
//     int but3 = digitalRead(BUTTON3);
//     int but4 = digitalRead(BUTTON4);
//     int but5 = digitalRead(BUTTON5);
//     int but6 = digitalRead(BUTTON6);
//     buttonPressed = -1;
//
//     if(but1 == LOW ) {
//       buttonPressed = 0;
//     } else if (but2 == LOW) {
//       buttonPressed = 1;
//     } else if (but3 == LOW) {
//       buttonPressed = 2;
//     } else if (but4 == LOW) {
//       buttonPressed = 3;
//     } else if (but5 == LOW) {
//       buttonPressed = 4;
//     } else if (but6 == LOW) {
//       buttonPressed = 5;
//     }
//
//       // process Input
//     if (buttonPressed > -1) {
//       // assign to patternArray[]
//       // visualize Input
//       int interval = buttonToScaleInterval(buttonPressed);
//       usbMIDI.sendNoteOn(84+interval,127,0);
//       CHSV color = getColorFromButton(buttonPressed);
//       buttonToCatAnim(buttonPressed, color);
//       usbMIDI.sendNoteOff(84+interval,127,0);
//       playerPattern[patternIndex] = buttonPressed;
//
//       // ready for next input
//       patternIndex += 1;
//     }
//
//     if (patternIndex >= currentPatternLength) {
//       // we are done with this wave of patterns break out of the while loop
//       patternIndex = 0;
//       notDone = false;
//     }
//
//   } // end while
//
//
//   // Done with the input into the player Pattern
//   bool isCorrect = checkPattern();
//   if (isCorrect) {
//     // play victory
//     // increase dificulty
//     // currentPatternLength += 1;
//     score += 1;
//     currentPatternLength = startPatternLength + (score / 2);
//     int interval = buttonToScaleInterval(buttonPressed);
//     usbMIDI.sendNoteOn(98,127,0);
//     sequenceCorrectAnim();
//     usbMIDI.sendNoteOn(98,127,0);
//     delay(100);
//     usbMIDI.sendNoteOff(98,127,0);
//     usbMIDI.sendNoteOff(98,127,0);
//   } else {
//     // gameover state
//     // restart
//     int note = 54;
//     int vel = 127;
//     int channel = 0;
//     usbMIDI.sendNoteOn(note, vel, channel);
//     sequenceWrongAnim();
//     delay(80);
//     usbMIDI.sendNoteOff(note, vel, channel);
//     currentPatternLength = startPatternLength;
//     // play loose
//     if (score > 0) { showScore();}
//     score = 0;
//   }
//
// }
