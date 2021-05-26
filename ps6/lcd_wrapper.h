#ifndef _DISPLAY_h
#define _DISPLAY_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "mastermind.h" 



void lcd_init (void);
void show_splash_screen (void);
void Show_Code_To_Guess (char* code, int length); 
void LCD_CLEAR (void);
void restart(void);




#endif
