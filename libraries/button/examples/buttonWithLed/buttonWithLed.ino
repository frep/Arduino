#include "button.h"
#include "led.h"

Led led(13);
Button button(16, activeLow);

void setup()
{ 
  led.init(); 
  button.initWithInternalPullup();
  button.attachFunctionOnBothButtonEdges(toggleLed);
}

void loop() 
{

}

void toggleLed()
{
  led.toggle();
}
