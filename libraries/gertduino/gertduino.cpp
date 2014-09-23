#include "gertduino.h"

  Gertduino::Gertduino()
  {
    leds[0] = new Led(pin_d5);
    leds[1] = new Led(pin_d6);
    leds[2] = new Led(pin_d7);
    leds[3] = new Led(pin_d8);
    leds[4] = new Led(pin_d9);
    leds[5] = new Led(pin_d10);
    
    buttons[0] = new Button(pin_b0, activeLow);
    buttons[1] = new Button(pin_b1, activeLow);
  }
  
  Gertduino::~Gertduino()
  {
    for(int i=0;i<ledNumber;i++)
    {
      delete led[i];
    }
    for(int i=0;i<buttonNumber;i++)
    {
      delete buttons[i];
    }  
  }
  
  void Gertduino::init()
  {
    for(int i=0;i<ledNumber;i++)
    {
      leds[i]->init();
    }
    for(int i=0;i<buttonNumber;i++)
    {
      buttons[i]->initWithInternalPullup();
    }
  }

