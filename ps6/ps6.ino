#include "lcd_wrapper.h"
#include "mastermind.h" 


void setup() 
{
    lcd_init();
    //show_splash_screen();
    //LCD_CLEAR();
}

void loop() 
{
  char* code = generate_code(false, 4);
  play_game(code);
  free(code);
}
