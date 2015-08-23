#ifndef POWERBOX_H
#define POWERBOX_H

#include "Arduino.h"
#include <button.h>
#include <led.h>
#include <Adafruit_INA219.h>

// Segments of the 7s
//    A
//  +---+
// F| G |B
//  +---+
// E| D |C
//  +---+ O DP

#define SEGA  0
#define SEGB  1
#define SEGC  2
#define SEGD  3
#define SEGE  4
#define SEGF  5
#define SEGG  6
#define SEGDP 7

// digits of the 7s
// +----+----+----+----+
// | D1 | D2 | D3 | D4 |
// +----+----+----+----+

#define D1 1
#define D2 2
#define D3 4
#define D4 8


// Arduino pin definitions
#define latchPin 11
#define clockPin  7
#define dataPin  12
#define buttonPin 4
#define vBattPin A0
#define ledPin   13

// Operating modes of the PowerBox
#define mode_Vbatt 16
#define mode_Vload 32
#define mode_Iload 64
#define mode_Pload 128

class PowerBox
{
 public:
	Led* led;
	Button* button;
    Adafruit_INA219* ina219;
 
	PowerBox();
	~PowerBox();
	void init();
	void run();

	int getMode();
	void changeMode();

	float getShuntVoltage();
	float getBusVoltage();
	float getCurrent();
	float getLoadVoltage();

	void updateLoadData();

    void displayData(void);
    
 private:
	int mode;
    byte data[4];
    byte letterA;
    byte letterP;
    byte letterU;
    byte dot;
    byte number[10];
    float shuntvoltage;
    float busvoltage;
    float current_mA;
    float loadvoltage;
    float battvoltage;

    void writeFloat2Data(float value);
    void updateShiftRegisters(byte data, byte digits);

};

#endif
