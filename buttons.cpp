#include "buttons.h"

const int buttonPins[5] = { 2, 3, 4, 5, 6 };
const int debounceDelay = 1;

volatile int buttonStates[5];
volatile int lastButtonStates[5] = { HIGH, HIGH, HIGH, HIGH, HIGH };
volatile unsigned long lastButtonPressTimes[5];
volatile unsigned long currentTime;

void initButtonsAndButtonInterrupts(void)
{
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  PCICR |= B00000100;
  PCMSK2 |= B01111100;  //pins 2, 3, 4, 5, 6
}

void useButtons(){
  currentTime = millis();

  for (int i = 0; i < 5; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);

    if ((currentTime - lastButtonPressTimes[i]) > debounceDelay && (buttonStates[i] != lastButtonStates[i])) {
      if (buttonStates[i] == LOW) {
        if (i + 2 == 6) {
          startTheGame();
        } else {
          buttonPressed(i);
        }
        lastButtonPressTimes[i] = currentTime;
        lastButtonStates[i] = LOW;
      } else {
        lastButtonPressTimes[i] = currentTime;
        lastButtonStates[i] = HIGH;
      }
    }
  }
}