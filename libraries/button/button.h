#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

#define activeLow true
#define activeHigh false

class Button
{

 public:

  Button(int pinNr, boolean logicLevel);
  ~Button();
  void init();
  void initWithInternalPullup();

  void attachFunctionOnButtonPressedEdge(void (*p_func)());
  void attachFunctionOnButtonReleasedEdge(void (*p_func)());
  void attachFunctionOnBothButtonEdges(void (*p_func)());

  boolean getValue();
  void checkButton();

 private:

  int pin;
  boolean isActiveLow;
  boolean state;
  void (*p_fctButtonChanged)(void);
  void (*p_fctButtonPressed)(void);
  void (*p_fctButtonReleased)(void);

};

#endif // BUTTON_H
