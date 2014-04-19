#include "led.h"

Led led(13);

void setup() 
{                
  led.init();    
}

void loop() 
{
  led.toggle();
  delay(1000);
}
