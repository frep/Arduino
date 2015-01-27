/*
 Based on the LiquidCrystal Library - Hello World
 
 Demonstrates the use a Winstar 16x2 OLED display.  These are similar, but
 not quite 100% compatible with the Hitachi HD44780 based LCD displays. 
 
 This sketch prints "Hello OLED World" to the LCD
 and shows the time in seconds since startup.
 
  The circuit:
 * LCD RS pin <-> GPA7 <->  7
 * LCD RW pin <-> GPA6 <->  6
 * LCD EN pin <-> GPA5 <->  5
 * LCD D4 pin <-> GPB4 <-> 12
 * LCD D5 pin <-> GPB5 <-> 13
 * LCD D6 pin <-> GPB6 <-> 14
 * LCD D7 pin <-> GPB7 <-> 15

 There is no need for the contrast pot as used in the LCD tutorial
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 Library & Example Converted for OLED
 by Bill Earl 30 Jun 2012
 
 This example code is in the public domain.
 */

// include the library code:
#include <Wire.h>
#include <CharacterOledOverI2c.h>
#include <Adafruit_MCP23017.h>
#include "led.h"
// initialize the library with the OLED hardware 
// version OLED_Vx and numbers of the interface pins. 
// OLED_V1 = older, OLED_V2 = newer. If 2 doesn't work try 1 ;)
CharacterOledOverI2c* lcd;

void setup() 
{
  // Print a message to the LCD.
  lcd = new CharacterOledOverI2c(OLED_V2, 7, 6, 5, 12, 13, 14, 15);
  lcd->begin(16, 2);
  lcd->print("frep's ROCK PRO");
  lcd->setCursor(0, 1);
  lcd->print("192.168.192.40");
}

void loop() 
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):  
  //lcd->setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd->print(millis()/1000);
}
