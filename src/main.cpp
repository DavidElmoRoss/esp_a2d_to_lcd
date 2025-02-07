/**********************************************************************
  Filename    : ADC formatted for PC Screen and LCD Screen
  Description : Displays A/D value and equivalent voltage
  Author      : David Elmo Ross
  Modification: 2025/01/12
**********************************************************************/

#include "arduino.h"                        // include Arduino.h library
#include <LiquidCrystal_I2C.h>              // include Library for 1602 I2C LCD
#include <Wire.h>                           // include Library for Wire.h

#define SDA 13                              //Define SDA pins
#define SCL 14                              //Define SCL pins

LiquidCrystal_I2C lcd(0x27,16,2);           // LCD i2c address 0x27, cols=16, rows=2
#define PIN_ANALOG_IN  34                   // Pin 34 is the A/D being used
void setup() 
{
  Serial.begin(115200);                     // platformio.ini has monitor_speed = 115200
                                            // make sure both are set to same value
  Wire.begin(SDA, SCL);                     // attach to the IIC pin
  lcd.init();                               // LCD driver initialization
  lcd.backlight();                          // Open the backlight
  lcd.setCursor(0,0);                       // lcd cursor to col 0 row 0
  lcd.print(" Value  Voltage ");            // Print TITLE  Value Voltage on LCD
}
void loop() 
{
short adcVal;                               // declare adcVal as a short
double voltage;                             // declare voltage as a double
char buff[16];                              // set char buff to 16 since 16 cols
void clear(void);                           // This function clears the screen and positions
                                            // the cursor at (1,1) top left of screen
clear();                                    // run clear function
                
printf("\e[1;1H\e[2J\e[10;30H\e[1;31mAnalog Value Analog Voltage");
                                            // clear screen & start title at (10,30) in red
printf("\e[0m\e[34m");                      // set data colour to by cyan

for(;;)                                     // endless loop
  {
      adcVal = analogRead(PIN_ANALOG_IN);   // adcVal gets value from 0-4095
      voltage = adcVal / 4095.0 * 3.333;    // voltages gets value from 0-3.33
                                            // convert adcVal and voltage to characters
                                            // and put in buff since lcd.print function
                                            // can only print chars
      sprintf(buff," %4d   %5.2f",adcVal,voltage);
      lcd.setCursor(0,1);                   // set LCD cursor to col 0 and row 1
      lcd.print(buff);                      // print formatted adcVal and voltage
                                            // on lcd screen
      printf("\e[11;35H");                  // position cursor at (11,35) on PC screen
      printf("%5d\t\t%4.2f",adcVal,voltage);// print adcVal and voltage there
      fflush(stdout);                       // fflush stdout to synch screen data
      delay(200);                           // wait 200 ms between samples
  }
}
void clear(void)
{
   printf("\e[2J");                          // escape sequence <ESC> [ 2 J clears the screen
   fflush(stdout);                           // flush the screen output buffer to clear screen
   printf("\e[1;1H");                        // escape sequence to set cursor to top left of screen
   fflush(stdout);                           // flush stdout buffer contents to screen

}
