#include "buzzer.h"
#include "Arduino.h"

const int buzzer = 12;

void buzzerInitialize() {
  pinMode(buzzer, OUTPUT);
}

void buzzerRightSound() {
  tone(buzzer, 4000);
  delay(20);
  noTone(buzzer);
}

void buzzerWrongSound() {
  tone(buzzer, 400);
  delay(1000);
  noTone(buzzer);
}