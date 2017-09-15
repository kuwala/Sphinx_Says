#include "simonsgame.h"

Simonsgame::Simonsgame(Strips* new_leds_ptr): patternIndex(0),
  notGameOver(true),
  notDone(true),
  startPatternLength(3),
  currentPatternLength(3),
  leds(new_leds_ptr),
  score(10),
  brightness(64),
  buttonPressed(-1) {
}
void Simonsgame::randomizePattern(int len) {
  for (size_t i = 0; i < len; i++) {
    examplePattern[i] = random(NUM_INPUTS);
    // examplePattern[i] = i;
  }
}
void Simonsgame::showScore() {
  for (size_t i = 0; i < score; i++) {
    // light light
    // play note
    int light = i % NUM_LEDS_PER_STRIP;
    int strip = i / NUM_LEDS_PER_STRIP;
    usbMIDI.sendNoteOn(84+i,32,0);
    int hue = (0 + i * 25 ) %256;
    int brightness = 64;
        leds->setPixel(strip, light, hue, 255, brightness);
        // leds[0 + strip][i % NUM_LEDS_PER_STRIP] = CHSV(hue,255,brightness/2);
        // leds[1][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
        // leds[3][i % NUM_LEDS_PER_STRIP] = CHSV(random(255),255,brightness/2);
  // FastLED.show();
  leds->draw();
  delay(50+ i*10);
    usbMIDI.sendNoteOff(84+i,127,0);
    Serial.println(i);
  }
  delay(1000);
  // allLEDSToBlack();
  leds->allLEDSToBlack();
}


void Simonsgame::sequenceCorrectAnim() {
  allButtonsToCat(CHSV(96,255,brightness));
}
void Simonsgame::flashRGB(CHSV color) {
  // flash 2 times on off, on off
  int times = 2;
  for (size_t t = 0; t < 2; t++) {
    // Turn on Green
    for (size_t i = 0; i < 4; i++) {
      for (size_t x = 0; x < NUM_STRIPS; x++) {
        // leds[x][i] = color;
        // leds[x][i] = color;
        leds->setPixel(x,i,color);
      }
    }
    FastLED.show();
    delay(200);
    // Turn off Green
    for (size_t i = 0; i < 4; i++) {
      for (size_t x = 0; x < NUM_STRIPS; x++) {
        // leds[x][i] = CHSV(0,0,0);
        leds->setPixel(x,i,CHSV(0,0,0));
      }
    }
    FastLED.show();
    delay(150);
  }
}
void Simonsgame::sequenceWrongAnim() {
  // flash error
  flashRGB(CHSV(0,255,brightness));
}
bool Simonsgame::checkPattern() {
  for (int i = 0; i < currentPatternLength; i++) {
    if (playerPattern[i] != examplePattern[i] ) {
      return false;
    }
  }
  return true;
}
void Simonsgame::buttonToCatAnim(int button, CHSV color) {
  // flash a led for 250ms
  // event 0 - 3
  int waitTime = 40;
  int strip = button ;

  // Draw strip
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    // leds[strip][i] = color;
    leds->setPixel(strip, i, color);
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    // leds[strip][i] = CHSV(0,0,0);
    leds->setPixel(strip, i, CHSV(0,0,0));
    FastLED.show();
    delay(waitTime / 2);
  }
}
void Simonsgame::catToButtonAnim(int button, CHSV color) {
  // flash a led for 250ms
  // event 0 - 3
  int waitTime = 40;
  int strip = button ;

  // Draw strip
  for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    // leds[strip][i] = color;
    leds->setPixel(strip, i, color);
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    // leds[strip][i] = CHSV(0,0,0);
    leds->setPixel(strip, i, CHSV(0,0,0));
    FastLED.show();
    delay(waitTime / 2);
  }
}
CHSV Simonsgame::getColorFromButton(int button) {
  int brightness = 127;
  CHSV color = CHSV(0,255,brightness);
  if (button == 0) {
    color = CHSV(244, 255, brightness);
  } else if (button == 1) {
    color = CHSV(0, 255, brightness);
  } else if (button == 2) {
    color = CHSV(64, 255, brightness);
  } else if (button == 3) {
    color = CHSV(96, 255, brightness);
  } else if (button == 4) {
    color = CHSV(160, 255, brightness);
  } else if (button == 5) {
    color = CHSV(192, 255, brightness);
  }
  return color;
}
void Simonsgame::allButtonsToCat(CHSV color) {
  // all strips shine green into the cat
  int rgbIndex = 1; // green
  int waitTime = 30;
  int brightness = 255;
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    for (size_t x = 0; x < NUM_STRIPS; x++) {
      // leds[x][i] = color;
      leds->setPixel(x, i, color);
    }
    FastLED.show();
    delay(waitTime);
  }
  for (size_t i = NUM_LEDS_PER_STRIP; i --> 0; ){
    for (size_t x = 0; x < NUM_STRIPS; x++) {
      leds->setPixel(x, i, CHSV(0,0,0));
      // leds[x][i] = CHSV(0,0,0);
    }
    FastLED.show();
    delay(waitTime / 2);
  }
}
int Simonsgame::buttonToScaleInterval(int button) {
  int interval = 0;
  if(button == 0) {
    interval = 0;
  } else if (button == 1) {
    interval = 2;
  } else if (button == 2) {
    interval = 5;
  } else if (button == 3) {
    interval = 7;
  } else if (button == 4) {
    interval = 10;
  } else if (button == 5) {
    interval = 12;
  }
  return interval;
}
void Simonsgame::demoMode() {
  leds->setPixel(random(NUM_STRIPS), random(NUM_LEDS_PER_STRIP), random(255),
    255, 127);
  leds->draw();
  delay(100);
}
void Simonsgame::instrumentMode(Bounce* button1) {
  int root = 82;
  button1->update();
  if(button1->fallingEdge()) {
    usbMIDI.sendNoteOn(root, 127, 1);
    leds->setPixel(0, 1, CHSV(224,255,brightness));
    leds->draw();
    // leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(224,255,brightness);
    // FastLED.show();
  }
  if(button1->risingEdge()) {
    usbMIDI.sendNoteOff(root,127,1);
    // leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
    // FastLED.show();
    leds->setPixel(0, 1, CHSV(0,0,0));
    leds->draw();
  }
}
// void Simonsgame::instrumentMode(Button* button1, Button* button2, Button* button3, Button* button4, Button* button5, Button* button5)  {
//   while(1) {
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
// }
void Simonsgame::loop() {
  //dannyLamp();
  /*if (Serial.available() > 0) {
    while(1) {
      // Enter keyboard mode
      button1.update();
      button2.update();
      button3.update();
      button4.update();
      button5.update();
      button6.update();

      //Presses
      if(button1.fallingEdge()) {
        usbMIDI.sendNoteOn(root, 127, 1);
        leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(224,255,brightness);
        FastLED.show();

      }
      if(button1.risingEdge()) {
        usbMIDI.sendNoteOff(root,127,1);
        leds[0][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }
      if(button2.fallingEdge()) {
        usbMIDI.sendNoteOn(root + 2, 127, 1);
        leds[1][root % NUM_LEDS_PER_STRIP] = CHSV(244,255,brightness);
        FastLED.show();
      }
      if(button2.risingEdge()) {
        usbMIDI.sendNoteOff(root + 2,127,1);
        leds[1][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }
      if(button3.fallingEdge()) {
        usbMIDI.sendNoteOn(root + 5, 127, 1);
        leds[2][root % NUM_LEDS_PER_STRIP] = CHSV(0,255,brightness);
        FastLED.show();
      }
      if(button3.risingEdge()) {
        usbMIDI.sendNoteOff(root + 5,127,1);
        leds[2][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }
      if(button4.fallingEdge()) {
        usbMIDI.sendNoteOn(root + 7, 127, 1);
        leds[3][root % NUM_LEDS_PER_STRIP] = CHSV(64,255,brightness);
        FastLED.show();
      }
      if(button4.risingEdge()) {
        usbMIDI.sendNoteOff(root + 7,127,1);
        leds[3][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }
      if(button5.fallingEdge()) {
        usbMIDI.sendNoteOn(root + 10, 127, 1);
        leds[4][root % NUM_LEDS_PER_STRIP] = CHSV(96,255,brightness);
        FastLED.show();
      }
      if(button5.risingEdge()) {
        usbMIDI.sendNoteOff(root + 10,127,1);
        leds[4][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }
      if(button6.fallingEdge()) {
        root += 1;
        usbMIDI.sendNoteOn(root + 12, 127, 1);
        leds[5][root % NUM_LEDS_PER_STRIP] = CHSV(160,255,brightness);
        FastLED.show();
      }
      if(button6.risingEdge()) {
        usbMIDI.sendNoteOff(root + 12,127,1);
        leds[5][root % NUM_LEDS_PER_STRIP] = CHSV(0,0,0);
        FastLED.show();
      }

      int interval = 0;
      buttonPressed = -1;

      // if(but1 == LOW ) {
      //   buttonPressed = 0;
      // } else if (but2 == LOW) {
      //   buttonPressed = 1;
      // } else if (but3 == LOW) {
      //   buttonPressed = 2;
      // } else if (but4 == LOW) {
      //   buttonPressed = 3;
      // } else if (but5 == LOW) {
      //   buttonPressed = 4;
      // } else if (but6 == LOW) {
      //   buttonPressed = 5;
      // }
      //
      //   if (buttonPressed > -1) {
      //     interval = buttonToScaleInterval(buttonPressed);
      //     usbMIDI.sendNoteOn(84+interval, 127, 0);
      //     delay(40);
      //     usbMIDI.sendNoteOff(84+interval, 127, 0);
      //     delay(40);
      //   }
    }
  } */
  // play example pattern
  randomizePattern(currentPatternLength);
  for (size_t i = 0; i < currentPatternLength; i++) {
    int button = examplePattern[i];
    int interval = buttonToScaleInterval(button);
    usbMIDI.sendNoteOn(84+interval,127,0);
    CHSV color = getColorFromButton(button);
    catToButtonAnim(button, color);
    usbMIDI.sendNoteOff(84+interval,127,0);
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
    buttonPressed = -1;

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
      int interval = buttonToScaleInterval(buttonPressed);
      usbMIDI.sendNoteOn(84+interval,127,0);
      CHSV color = getColorFromButton(buttonPressed);
      buttonToCatAnim(buttonPressed, color);
      usbMIDI.sendNoteOff(84+interval,127,0);
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
    // currentPatternLength += 1;
    score += 1;
    currentPatternLength = startPatternLength + (score / 2);
    int interval = buttonToScaleInterval(buttonPressed);
    usbMIDI.sendNoteOn(98,127,0);
    sequenceCorrectAnim();
    usbMIDI.sendNoteOn(98,127,0);
    delay(100);
    usbMIDI.sendNoteOff(98,127,0);
    usbMIDI.sendNoteOff(98,127,0);
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
    if (score > 0) { showScore();}
    score = 0;
  }

}
