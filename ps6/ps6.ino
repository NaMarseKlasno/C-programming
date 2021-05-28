#include "lcd_wrapper.h"
#include "mastermind.h" 


void setup() 
{
    lcd_init();
}

void loop() 
{ 

  char* code = generate_code(true, 4);

  play_game(code);
  free(code);
} 
