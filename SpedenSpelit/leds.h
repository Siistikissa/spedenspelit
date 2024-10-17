#ifndef LEDS_H
#define LEDS_H
#include <arduino.h>

void initializeLeds();

void setLed(int ledNumber);

void clearAllLeds(void);

void setAllLeds(void);

void setIdleAnimation1(void);

void setIdleAnimation2(void);

#endif
