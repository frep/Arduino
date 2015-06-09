#include "Joystick.h"


Joystick::Joystick(int pinNrX, int pinNrY, int pinNrButton, boolean logicLevelButton)
{
	xPin	=	pinNrX;
	yPin	=	pinNrY;
	
	xState 	= 	getXState();
	yState 	= 	getYState();
	
	ThresholdXValue = 0;
	ThresholdYValue = 0;
	
    button = new Button(pinNrButton, logicLevelButton);

	p_fctChangeToLEFT	= NULL;
	p_fctChangeToMIDDLE	= NULL;
	p_fctChangeToRIGHT	= NULL;
	p_fctChangeToDOWN	= NULL;
	p_fctChangeToUP		= NULL;
	
} 

Joystick::~Joystick()
{
    delete button;
}

void Joystick::init()
{
	button->init();
	pinMode(xPin,INPUT);
	pinMode(yPin,INPUT);
}

void Joystick::check()
{
    // check X axis
    
	if(xState!=getXState())
	{
		int actualState = getXState();
		
        if(actualState == LEFT)
		{
            if(p_fctChangeToLEFT != NULL)
            {
                (*p_fctChangeToLEFT)();
            }
		}
        
		if(actualState == MIDDLE)
		{
			if(p_fctChangeToMIDDLE != NULL)
            {
                (*p_fctChangeToMIDDLE)();
            }
		}
        
		if(actualState == RIGHT)
		{
			if(p_fctChangeToRIGHT != NULL)
            {
                (*p_fctChangeToRIGHT)();
            }
		}
        
        xState = actualState;
	}

    // check Y axis
    
	if(yState!=getYState())
	{
		int actualState = getYState();
        
		if(actualState == DOWN)
		{
			if(p_fctChangeToDOWN != NULL)
            {
                (*p_fctChangeToDOWN)();
            }
		}
        
		if(actualState == MIDDLE)
		{
			if(p_fctChangeToMIDDLE != NULL)
            {
                (*p_fctChangeToMIDDLE)();
            }
		}
        
		if(actualState == UP)
		{
			if(p_fctChangeToUP != NULL)
            {
                (*p_fctChangeToUP)();
            }
		}
        
        yState = actualState;
	}
	
    // check Button
    button->checkButton();
}



int Joystick::getXValue()
{
	return analogRead(xPin);
}

int Joystick::getYValue()
{
	return analogRead(yPin);
}

int Joystick::getXState()
{
	if(ThresholdXValue != 0)
	{
		if(getXValue()<(middleValue-ThresholdXValue))
		{
			return LEFT;
		}

		if((middleValue+ThresholdXValue)<getXValue())
		{
			return RIGHT;
		}
	}
    
	return MIDDLE;
    
}
  
int Joystick::getYState()
{
    if(ThresholdYValue != 0)
	{
		if(getYValue()<(middleValue-ThresholdYValue))
		{
			return DOWN;
		}

		if((middleValue+ThresholdYValue)<getYValue())
		{
			return UP;
		}
	}
	
	return MIDDLE;
    
}
  
void Joystick::setXThreshold(int thresholdInPercent)
{
	if(thresholdInPercent > 100)
	{
		thresholdInPercent =100;
	}	
	
	if(0 < thresholdInPercent)
	{
		// 5.12 = * middleValue / Percent = * 512 / 100
		ThresholdXValue = thresholdInPercent * 5.12;
	}
}

void Joystick::setYThreshold(int thresholdInPercent)
{
	if(thresholdInPercent > 100)
	{
		thresholdInPercent =100;
	}	
	
	if(0 < thresholdInPercent)
	{
		// 5.12 = * middleValue / Percent = * 512 / 100
		ThresholdYValue = thresholdInPercent * 5.12;
	}
}
  
void Joystick::attachFunctionOnStateChangeToLEFT(void (*p_func)())
{
	p_fctChangeToLEFT 	= p_func;
}

void Joystick::attachFunctionOnStateChangeToMIDDLE(void (*p_func)())
{
	p_fctChangeToMIDDLE = p_func;
}
 
void Joystick::attachFunctionOnStateChangeToRIGHT(void (*p_func)())
{
	p_fctChangeToRIGHT 	= p_func;
}

void Joystick::attachFunctionOnStateChangeToDOWN(void (*p_func)())
{
	p_fctChangeToDOWN 	= p_func;
}

void Joystick::attachFunctionOnStateChangeToUP(void (*p_func)())
{
	p_fctChangeToUP 	= p_func;
}
