/*
file  : PowerBoxSketch.ino
author: frep
desc  :

*/

#include <PowerBox.h>
#include <button.h>
#include <led.h>

PowerBox powerBox;

// Timing
unsigned long currentMillis;
long previousMillisADC = 0;
long intervalADC = 500;     // intervall in milliseconds

void setup()
{
    powerBox.init();
    powerBox.button->attachFunctionOnButtonReleasedEdge(changeMode);
}

void loop()
{

    currentMillis = millis();

    if(currentMillis - previousMillisADC > intervalADC)
    {
        previousMillisADC = currentMillis;
        powerBox.led->toggle();
    }

    powerBox.button->checkButton();
    powerBox.displayData();

}

void changeMode()
{
    powerBox.changeMode();
}