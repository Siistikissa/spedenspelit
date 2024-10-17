#include "display.h"
int serialInput1=8;
int serialInput2=9;
int latchClock=10;
int shiftClock=11;
int digits [11][8] {
  {0,1,1,1,1,1,1,0}, //0
  {0,0,1,1,0,0,0,0}, //1
  {0,1,1,0,1,1,0,1}, //2
  {0,1,1,1,1,0,0,1}, //3
  {0,0,1,1,0,0,1,1}, //4
  {0,1,0,1,1,0,1,1}, //5
  {0,1,0,1,1,1,1,1}, //6
  {0,1,1,1,0,0,0,0}, //7
  {0,1,1,1,1,1,1,1}, //8
  {0,1,1,1,1,0,1,1}, //9
  {0,0,0,0,0,0,0,0}  //10(tyhjä)
};

void initializeDisplay(void)
{
  pinMode(serialInput1, OUTPUT);
  pinMode(serialInput2, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(shiftClock, OUTPUT);
}

void DisplayDigit1(int Digit) {
	digitalWrite(latchClock, LOW);
  for(int a=7;a>=0;a--) {
    digitalWrite(shiftClock, LOW);
    if(digits[Digit][a]==1) digitalWrite(serialInput1, LOW);
    if(digits[Digit][a]==0) digitalWrite(serialInput1, HIGH);
    digitalWrite(shiftClock, HIGH);
  }
  digitalWrite(latchClock, HIGH);
}

void DisplayDigit2(int Digit) {
	digitalWrite(latchClock, LOW);
  for(int b=7;b>=0;b--) {
    digitalWrite(shiftClock, LOW);
    if(digits[Digit][b]==1) digitalWrite(serialInput2, LOW);
    if(digits[Digit][b]==0) digitalWrite(serialInput2, HIGH);
    digitalWrite(shiftClock, HIGH);
  }
  digitalWrite(latchClock, HIGH);
}
void WriteToDisplay(int number) {
    if (number < 10) {
        DisplayDigit1(10);
        DisplayDigit2(number);
    } else if (number < 100) {
        DisplayDigit1(number / 10);
        DisplayDigit2(number % 10);
    } else {
        DisplayDigit1(10);
        DisplayDigit2(10);
    }
}
