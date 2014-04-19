#include "led.h"

  Led::Led(int pinNr)
  : pin(pinNr), ledIsOn(false)
  {
    
  }
  
  Led::~Led()
  {
  
  }
  
  void Led::init()
  {
    pinMode(pin, OUTPUT);
  }
  
  void Led::setOn()
  {
    digitalWrite(pin, HIGH);
    ledIsOn = true;
  }
  
  void Led::setOff()
  {
    digitalWrite(pin, LOW);
    ledIsOn = false;
  }
  
  void Led::toggle()
  {
    ledIsOn ? setOff() : setOn();
  }
  
  boolean Led::isOn()
  {
    if(ledIsOn)
    {
      return true;
    }
    
    return false;
  }

