#include "SpedenSpelit.h"
#include "display.h"
#include "buttons.h"
#include "leds.h"
//gamelogic trolleja: sama seedi aina ja opettelee sen ulkoa.
//muuta kaikki globaalit pointtereiksi ja pyöritä funktioissa?

static bool timeToCheckGameStatus = false; //Changed by ISR(PCINT2_vect); Read by loop();

struct list //array with index
{
  byte numbers[100];
  byte index = 0;
};

static list user;
static list randomised;

void setup()
{
  /*
    Initialize here all modules
  */
  //initializeTimer(); should not be here?
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
  setIdleAnimationOnOff(); //maybe

}

void loop()
{
  /*
    This loop function constantly checks if
	player has pushed a button and there is
	need for checking the game status
  */
  if(timeToCheckGameStatus){
    checkGame();
    timeToCheckGameStatus = false;
  };
}

ISR(PCINT2_vect) {
   /*
     Here you implement logic for handling
	 interrupts from 2,3,4,5 pins for Game push buttons
	 and for pin 6 for start Game push button.
   */
  useButtons(); 
  /*
  currentTime = millis();

  for (int i = 0; i < 5; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);

    if ((currentTime - lastButtonPressTimes[i]) > debounceDelay && (buttonStates[i] != lastButtonStates[i])) {
      if (buttonStates[i] == LOW) {
        if (i + 2 == 6) {
          startTheGame();
        } else {
          user.numbers[user.index] = i;
          user.index++;
          timeToCheckGameStatus = true;
        }
        lastButtonPressTimes[i] = currentTime;
        lastButtonStates[i] = LOW;
      } else {
        lastButtonPressTimes[i] = currentTime;
        lastButtonStates[i] = HIGH;
      }
    }
  }*/
}


ISR(TIMER1_COMPA_vect)
{
  /*
    Here you generate a random number that is used to
	set certain led.
	
	Each timer interrupt increments "played" numbers,
	and after each 10 numbers you must increment interrupt
	frequency.
	
	Each generated random number must be stored for later
	comparision against player push button presses.
  */
  static byte tics = 0;

  if(tics == 10){
    //increase timer by 10%
    OCR1A *= 0.9; //cumulative. not specified in info if it should be from original or cumulative.
    tics = -1; // taking + 1 tic into account at the end
  };

  byte randomNum = random(0,3);
  randomised.numbers[randomised.index] = randomNum;
  randomised.index += 1;
  setLed(randomNum); //set led byte
  tics += 1;
}



void initializeTimer(void)
{
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void checkGame() //byte is not neede because global list. pass user and randomised here from loop
{
	static byte score = 0;
  if(user.numbers[user.index] == randomised.numbers[user.index]){
    score += 1;
    WriteToDisplay(score);
  }
  else{
    stopTheGame();
    score = 0;
  };
}


void initializeGame()
{
  user.index = 0;
  randomised.index = 0;
}

void startTheGame()
{
  initializeGame();
  initializeTimer();
}

void stopTheGame()
{
  //stops the timer
  TIMSK1 |= (0 << OCIE1A);//maybe stops it. to be tested
  setIdleAnimationOnOff();
}

void buttonPressed(int pressedButton) 
{
  user.numbers[user.index] = pressedButton;
  user.index++;
  timeToCheckGameStatus = true;
}

void setIdleAnimationOnOff()
{
  // not sure if this stops a the right times
  static int stateOfLoop = 0;
  stateOfLoop += 1;
  while(stateOfLoop % 2 == 1){
    for(int x = 0; x < 4; x++){
      setIdleAnimation1();
      delay(1000);
      setIdleAnimation2();  
    };
    for(int x = 0; x < 4; x++){
      clearAllLeds();
      delay(1000);
      setAllLeds();  
    };
  }
}
