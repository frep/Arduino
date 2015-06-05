#include "button.h"

  Button::Button(int pinNr, boolean logicLevel)
  : pin(pinNr), isActiveLow(logicLevel)
  {
    state = getValue();
    p_fctButtonChanged  = NULL;
    p_fctButtonPressed  = NULL;
    p_fctButtonReleased = NULL;
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

  void Button::checkButton()
  {
    if(state != getValue())
    {
      if(p_fctButtonChanged != NULL)
      {
       (*p_fctButtonChanged)();
      }
      if(getValue() == false)
      {
        if(isActiveLow)
        {
          if(p_fctButtonPressed != NULL)
          {
            (*p_fctButtonPressed)();
          }
        }
        else
        {
          if(p_fctButtonReleased != NULL)
          {
            (*p_fctButtonReleased)();
          }
        }
      }
      else
      {
        if(isActiveLow)
        {
          if(p_fctButtonReleased != NULL)
          { 
            (*p_fctButtonReleased)();
          }
        }
        else
        {
          if(p_fctButtonPressed != NULL)
          { 
            (*p_fctButtonPressed)();
          }
        }
      }
      state = getValue();
    }
  }

  void Button::attachFunctionOnButtonPressedEdge(void (*p_func)())
  {
    p_fctButtonPressed = p_func;
  }
  
  void Button::attachFunctionOnButtonReleasedEdge(void (*p_func)())
  {
    p_fctButtonReleased = p_func;
  }
  
  void Button::attachFunctionOnBothButtonEdges(void (*p_func)())
  {
    p_fctButtonChanged = p_func;
  }

  

