#include <Arduino.h>
#include "FastLED.h"
#include "Bounce.h"

#include "strips.h"
#include "simonsgame.h"
// The Plan
/*

*/
Bounce button1 = Bounce(1, 5);
Bounce button2 = Bounce(2, 5);
Bounce button3 = Bounce(3, 5);
Bounce button4 = Bounce(4, 5);
Bounce button5 = Bounce(5, 5);
Bounce button6 = Bounce(6, 5);


#define NUM_INPUTS 6


#define BUTTON1 5
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 6


Strips strips;
Simonsgame game(&strips);
int mainMode = 0; // 0 - simons says, 1 - demo lights, 2 - free play
void setup() {
  Serial.begin(115200);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);

  // When you tun on the sphinx check if either button 1 or 2
  // is pressed and if so change the main mode of the sphinx
  int but1 = digitalRead(BUTTON1);
  int but2 = digitalRead(BUTTON2);
  if(but1 == LOW) {
    mainMode = 1;
  } else if (but2 == LOW) {
    mainMode = 2;
  }

}

void loop() {

  // strip.update();
  // delay(100);
  // game.showScore();
  if (mainMode == 0) {
    game.loop();
  } else if (mainMode == 1) {
    Serial.println("mode 1");
    game.demoMode();
  } else if (mainMode == 2) {
    game.instrumentMode(&button1);
    Serial.println("mode 2");
  } else {
    game.loop();
  }
  // game.LEDSTest();
  // strip.draw();
}
