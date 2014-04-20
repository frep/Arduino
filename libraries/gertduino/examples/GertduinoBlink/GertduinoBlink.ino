#include "gertduino.h"
#include "button.h"
#include "led.h"

Gertduino board;

int actualLed;
boolean indexIsRising;
int delayMs;



void setup() 
{                
  Serial.begin(9600); 
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }  
  
  board.init();
  board.buttons[0]->attachFunctionOnButtonPressedEdge(decreaseSpeed);
  board.buttons[1]->attachFunctionOnButtonPressedEdge(increaseSpeed);
  
  actualLed = 0;
  indexIsRising = true;
  delayMs = 100;
}

void loop() 
{
  board.leds[actualLed]->setOff();
  setNextIndex(&indexIsRising, &actualLed);
  board.leds[actualLed]->setOn();
  delay(delayMs);
}


void setNextIndex(boolean* directionLedIndex, int* actualIndex)
{
  if(indexIsRising)
  {
    if((*actualIndex + 1) % ledNumber == 0)
    {
      *directionLedIndex = false;
      *actualIndex = *actualIndex - 1;
    }
    else
    {
      *actualIndex = *actualIndex + 1;
    }
  }
  else
  {
    if(*actualIndex == 0)
    {
      *directionLedIndex = true;
      *actualIndex = *actualIndex + 1;
    }
    else
    {
      *actualIndex = *actualIndex - 1;
    }
  }
}

void increaseSpeed()
{
  // Decrease delay to increase the speed
  if((delayMs - 50) > 0)
  {
    delayMs = delayMs - 50;
  }
}

void decreaseSpeed()
{
  // Increase delay to decrease the speed
  delayMs = delayMs + 50;
}
