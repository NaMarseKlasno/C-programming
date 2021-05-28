#ifndef _DISPLAY_h
#define _DISPLAY_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "mastermind.h" 



void lcd_init (void);
void show_secret_code (char* code, int length); 
void LCD_CLEAR (void);
void restart(void);
void render_guess(char* guess);
void lcd_print (char* string, int row);


#endif
