#include "button.h"
#include "led.h"

Led led(13);
Button button(4, activeLow);

void setup()
{ 
  led.init(); 
  button.initWithInternalPullup();
  button.attachFunctionOnBothButtonEdges(toggleLed);
}

void loop() 
{
  button.checkButton();
  // wait 20ms for debounce
  delay(20);
}

void toggleLed()
{
  led.toggle();
}
