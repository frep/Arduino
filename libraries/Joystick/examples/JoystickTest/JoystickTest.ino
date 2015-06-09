#include "Joystick.h"
#include "button.h"

Joystick joystick(A0,A1,4,activeLow);

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  
  joystick.init();
  joystick.setYThreshold(90);
  joystick.setXThreshold(90);
  joystick.attachFunctionOnStateChangeToUP(upDetection);
  joystick.attachFunctionOnStateChangeToDOWN(downDetection);
  joystick.attachFunctionOnStateChangeToRIGHT(rightDetection);
  joystick.attachFunctionOnStateChangeToMIDDLE(middleDetection);
  joystick.attachFunctionOnStateChangeToLEFT(leftDetection);
  joystick.button->attachFunctionOnButtonPressedEdge(buttonGetPressed);
  joystick.button->attachFunctionOnButtonReleasedEdge(buttonGetReleased);
  
  Serial.println("init done!");
}

void loop() 
{
  joystick.check();
  delay(30);
}


void upDetection()
{
  Serial.println("upDetection");
}

void downDetection()
{
  Serial.println("downDetection");
}

void leftDetection()
{
  Serial.println("leftDetection");
}

void rightDetection()
{
  Serial.println("rightDetection");
}

void middleDetection()
{
  Serial.println("middleDetection");
}

void buttonGetPressed()
{
  Serial.println("buttonGetPressed");
}

void buttonGetReleased()
{
  Serial.println("buttonGetReleased");
}
