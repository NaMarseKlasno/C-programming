#ifndef _DISPLAY_h
#define _DISPLAY_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "mastermind.h" 



/** 
 *   The function initializes the display
 *   @return - nothing
 */
void lcd_init (void);


/** 
 *   Function shows secret code
 *   @return - nothing
 */
void show_secret_code (char* code, int length); 


/** 
 *   Function clears the entire display
 *   @return - nothing
 */
void LCD_CLEAR (void);


/** 
 *   Function renders Restart game
 *   @return - nothing
 */
void restart(void);


/** 
 *   The function renders what the player clicks (1 2 3 4 buttons)
 *   @return - nothing
 */
void render_guess(char* guess);


/** 
 *   The line-by-line function outputs text to the display
 *   @return - nothing
 */
void lcd_print (char* string, int row);


#endif
