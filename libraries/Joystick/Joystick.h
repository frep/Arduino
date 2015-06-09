#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "../button/button.h"

#define MIDDLE 0
#define LEFT  -1
#define RIGHT  1
#define DOWN  -1
#define UP     1

#define middleValue 512



class Joystick
{

 public:

  Joystick(int pinNrX, int pinNrY, int pinNrButton, boolean logicLevelButton);
  ~Joystick();
  void init();
  
  void check();             // check for statechanges
  
  int getXValue();          // 10bit-Value 0 .. 1024
  int getYValue();          // 10bit-Value 0 .. 1024
  
  int getXState();
  int getYState();
  
  void setXThreshold(int thresholdInPercent);
  void setYThreshold(int thresholdInPercent);
  
  void attachFunctionOnStateChangeToLEFT(void (*p_func)());
  void attachFunctionOnStateChangeToMIDDLE(void (*p_func)());
  void attachFunctionOnStateChangeToRIGHT(void (*p_func)());
  void attachFunctionOnStateChangeToDOWN(void (*p_func)());
  void attachFunctionOnStateChangeToUP(void (*p_func)());

  Button* button;
  
 private:

  int xPin;
  int yPin;
  
  int ThresholdXValue;		// 10bit-Value 0 .. 1024
  int ThresholdYValue;		// 10bit-Value 0 .. 1024
  
  int xState;				// States: LEFT, MIDDLE, RIGHT
  int yState;				// States: DOWN, MIDDLE, UP
  
  void (*p_fctChangeToLEFT)(void);
  void (*p_fctChangeToMIDDLE)(void);
  void (*p_fctChangeToRIGHT)(void);
  void (*p_fctChangeToDOWN)(void);
  void (*p_fctChangeToUP)(void);

};

#endif // JOYSTICK_H
