#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "cbiface.h"

#define activeLow true
#define activeHigh false

class Button : public CallBackInterface
{

 public:

  Button(int pinNr, boolean logicLevel);
  ~Button();
  void init();
  void initWithInternalPullup();
  
  void attachFunctionOnButtonPressedEdge(void (*p_func)());
  void attachFunctionOnButtonReleasedEdge(void (*p_func)());
  void attachFunctionOnBothButtonEdges(void (*p_func)());
  void detachFunction();

  boolean getValue();

 private:

  int pin;
  boolean isActiveLow;
  
  // Method from CallBackInterface
  void cbmethod();
  
  void (*p_fct)(void);
  void attachISR(void (*p_func)(), int edge);

};

#endif // BUTTON_H
