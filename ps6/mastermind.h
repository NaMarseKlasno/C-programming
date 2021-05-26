#ifndef _MASTER_MIND_h
#define _MASTER_MIND_h

#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include <Arduino.h>
#include "lcd_wrapper.h"

/**
 *   DIODE PINS
 */
#define LED_BLUE_1 6
#define LED_BLUE_2 8
#define LED_BLUE_3 10
#define LED_BLUE_4 12

#define LED_RED_1 7
#define LED_RED_2 9
#define LED_RED_3 11
#define LED_RED_4 13

/** 
 *   BUTTON PINS 
 */
#define BTN_1_PIN 2
#define BTN_2_PIN 3
#define BTN_3_PIN 4
#define BTN_4_PIN 5
#define BTN_ENTER_PIN A0


/** 
 *   Function generating random code
 *   @return - na reference to the generated string, 
 *   or NULL if this string cannot be generated
 */
char* generate_code(bool repeat, int length);


/** 
 *   The function that contains the main game loop
 *   @return - nothing
 */
void play_game(char* secret);


/** 
 *   This function evaluates the current attempt
 *   @return - nothing
 */
void get_score(char* secret, char* guess, int* peg_a, int* peg_b);


/** 
 *   This function turns off all diodes
 *   @return - nothing
 */
void turn_off_leds(void);


/** 
 *   Turns on the corresponding RGB LEDs 
 *   depending on how many digits the player guessed
 *   @return - nothing
 */
void render_leds(const int peg_a, const int peg_b);


#endif
