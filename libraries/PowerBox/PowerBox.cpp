#include "PowerBox.h"
#include "Arduino.h"
#include "Wire.h"

PowerBox::PowerBox()
: mode(0)
{
	led    = new Led(ledPin);
	button = new Button(buttonPin, activeLow);
	ina219 = new Adafruit_INA219();
	data[0]   = 0;
	data[1]   = 0;
	data[2]   = 0;
	data[3]   = 0;
    letterA   = 0x77;
    letterP   = 0x73;
    letterU   = 0x3E;
    dot       = 0x80;
    number[0] = 0x3F;
    number[1] = 0x06;
    number[2] = 0x5B;
    number[3] = 0x4F;
    number[4] = 0x66;
    number[5] = 0x6D;
    number[6] = 0x7D;
    number[7] = 0x07;
    number[8] = 0x7F;
    number[9] = 0x6F;
    shuntvoltage = 0;
    busvoltage   = 0;
    current_mA   = 0;
    loadvoltage  = 0;
    battvoltage  = 0;
}

PowerBox::~PowerBox()
{
	delete ina219;
	delete button;
	delete led;
}

void PowerBox::init()
{
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(vBattPin, INPUT);
	led->init();
	button->initWithInternalPullup();
	ina219->begin();
	//ina219->setCalibration_32V_1A();
	mode = mode_Vbatt;
}

void PowerBox::run()
{
	button->checkButton();

	displayData();
}

int PowerBox::getMode()
{
	return mode;
}

void PowerBox::changeMode()
{
	switch(mode)
	{
		case 0:
			// No init done!
			mode = mode_Vbatt;
			break;
		case mode_Vbatt:
			mode = mode_Vload;
			break;
		case mode_Vload:
			mode = mode_Iload;
			break;
		case mode_Iload:
			mode = mode_Pload;
			break;
		case mode_Pload:
			mode = mode_Vbatt;
			break;
		default:
			// You should never be here!
            break;
	}
}

void PowerBox::displayData(void)
{
    int delayMS = 2;
	updateShiftRegisters(data[0], (~D1)&(mode+15));
    delay(delayMS);
    updateShiftRegisters(data[1], (~D2)&(mode+15));
    delay(delayMS);
    updateShiftRegisters(data[2], (~D3)&(mode+15));
    delay(delayMS);
    updateShiftRegisters(data[3], (~D4)&(mode+15));
    delay(delayMS);
}

void PowerBox::updateShiftRegisters(byte data, byte digits)
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digits);
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);
}

void PowerBox::updateLoadData()
{
	  shuntvoltage = ina219->getShuntVoltage_mV();
	  busvoltage = ina219->getBusVoltage_V();
	  current_mA = ina219->getCurrent_mA();
	  if(current_mA < 0)
	  {
		  current_mA = 0;
	  }
	  loadvoltage = busvoltage + (shuntvoltage / 1000);
	  battvoltage = busvoltage * analogRead(vBattPin) /1023;

	  //Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
	  //Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
	  //Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
	  //Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
	  //Serial.println("");

	  switch(mode)
	  {
	  case mode_Vbatt:
		  writeFloat2Data(battvoltage);
		  break;
	  case mode_Vload:
		  writeFloat2Data(loadvoltage);
		  break;
	  case mode_Iload:
		  writeFloat2Data(current_mA/1000.0);
		  break;
	  case mode_Pload:
		  writeFloat2Data(current_mA*loadvoltage/1000.0);
		  break;
	  default:
		  break;
	  }

}

float PowerBox::getShuntVoltage()
{
	return shuntvoltage;
}

float PowerBox::getBusVoltage()
{
	return busvoltage;
}

float PowerBox::getCurrent()
{
	return current_mA;
}

float PowerBox::getLoadVoltage()
{
	return loadvoltage;
}

void PowerBox::writeFloat2Data(float value)
{
	// This function display a float value in the form x.xxx
	// -> only 1 digit before dot and 3 digits after dot.

	value += 0.0005; // for proper rounding
	int cV = (int)(value * 1000);
	data[0] = number[cV % 10000 / 1000]|dot;
	data[1] = number[cV %  1000 /  100];
	data[2] = number[cV %   100 /   10];
	data[3] = number[cV %    10       ];
}



