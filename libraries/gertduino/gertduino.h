#ifndef GERTDUINO_H
#define GERTDUINO_H

#include "../button/button.h"
#include "../led/led.h"

// LED pins
#define pin_d5 13
#define pin_d6 9
#define pin_d7 10
#define pin_d8 3
#define pin_d9 5
#define pin_d10 6
#define ledNumber 6

// Button pins
#define pin_b0 16
#define pin_b1 17
#define buttonNumber 2

class Gertduino 
{

 public:

  Led* leds[ledNumber];
  Button* buttons[buttonNumber];
  
  Gertduino();
  ~Gertduino();
  void init();
 

 private:

};

#endif // GERTDUINO_H
