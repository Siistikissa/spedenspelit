#include "leds.h"
const int ledPins[4] = { A2, A3, A4, A5 };
const int ledNumber = 4;



void setLed(int ledNumber) {
    clearAllLeds();
    if (ledNumber < 4) {
        digitalWrite (ledPins [ledNumber], HIGH);
    }
}

void clearAllLeds(void) {
    for (byte i = 0; i < ledNumber; ++i) {
        digitalWrite(ledPins[i], LOW);
    }
}

void setAllLeds(void) {
    for (byte i = 0; i < ledNumber; ++i) {
        digitalWrite(ledPins[i], HIGH);
    }
}

void initializeLeds(){
    for (byte i = 0; i < ledNumber; ++i) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void setIdleAnimation1(){
  clearAllLeds();
  digitalWrite(ledPins[0], HIGH);
  digitalWrite(ledPins[2], HIGH);
}

void setIdleAnimation2(){
  clearAllLeds();
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[3], HIGH);
}
