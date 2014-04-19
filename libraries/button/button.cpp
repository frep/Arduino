#include "button.h"
#include "ooPinChangeInt.h"

  Button::Button(int pinNr, boolean logicLevel)
  : pin(pinNr), isActiveLow(logicLevel)
  {
    p_fct = NULL;
  }
  
  Button::~Button()
  {
  
  }

  void Button::init()
  {
    pinMode(pin, INPUT);
  }
  
  void Button::initWithInternalPullup()
  {
    pinMode(pin, INPUT_PULLUP);
  }
  
  boolean Button::getValue()
  {
    return digitalRead(pin);
  }

  void Button::cbmethod()
  {    
    // calls the function, p_fct points at. This call would also work like this: (*p_fct)();
    p_fct();
  }
  
  void Button::attachFunctionOnButtonPressedEdge(void (*p_func)())
  {
    int buttonPressedEdge;
    isActiveLow ? buttonPressedEdge = FALLING : buttonPressedEdge = RISING;
    attachISR(p_func, buttonPressedEdge);
  }
  
  void Button::attachFunctionOnButtonReleasedEdge(void (*p_func)())
  {
    int buttonReleasedEdge;
    isActiveLow ? buttonReleasedEdge = RISING : buttonReleasedEdge = FALLING;
    attachISR(p_func, buttonReleasedEdge);
  }
  
  void Button::attachFunctionOnBothButtonEdges(void (*p_func)())
  {
    attachISR(p_func,  CHANGE);
  }
  
  void Button::attachISR(void (*p_func)(), int edge)
  {
    p_fct = p_func;
    PCintPort::attachInterrupt(pin, this, edge);
  }
  
  void Button::detachFunction()
  {
    PCintPort::detachInterrupt(pin);
  }

