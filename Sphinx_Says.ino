#include <Arduino.h>
#include "FastLED.h"
#include "Bounce.h"

#include "strip.h"
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

Strip strip();
// Simonsgame game(strip);
// Simonsgame game();

void setup() {
  Serial.begin(115200);
Simonsgame game(&strip);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(BUTTON5, INPUT_PULLUP);
  pinMode(BUTTON6, INPUT_PULLUP);

}

void loop() {

  // strip.update();
  delay(100);
  // strip.draw();
}
