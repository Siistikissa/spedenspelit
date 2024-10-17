#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>


/*
  initializeDisplay subroutine initializes 5 pins needed for controlling 7-segment
  displays in a cascade as follows:
  Arduino pin 12 = serial to parallel component reset
  Arduino pin 11 = serial to parallel component shiftClock
  Arduino pin 10 = serial to parallel component latchClock
  Arduino pin 9  = serial to parallel component outEnable
  Arduino pin 8  = serial to parallel component serialInput
  

*/
void initializeDisplay(void);
void DisplayDigit1(int Digit);
void DisplayDigit2(int Digit);
void WriteToDisplay(int number);

#endif
