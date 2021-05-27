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
void render_game_rounds(int round_number); 
void render_game_rounds_str2(char* guess);
void lcd_print (char* string, int row);


#endif
