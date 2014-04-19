#ifndef LED_H
#define LED_H

#include "Arduino.h"

class Led 
{

 public:

  Led(int pinNr);
  ~Led();
  void init();
  
  void setOn();
  void setOff();
  void toggle();
  
  boolean isOn();

 private:

  int pin;
  boolean ledIsOn;
  
};

#endif // LED_H
