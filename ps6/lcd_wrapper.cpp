#include "lcd_wrapper.h" 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void show_splash_screen (void);


void lcd_init (void) 
{
  lcd.init();
  lcd.backlight();
  show_splash_screen();
  LCD_CLEAR();
  turn_off_leds();
}


void show_splash_screen (void) 
{
  lcd.setCursor(3, 0); 
  lcd.print("Welcome to"); 
  lcd.setCursor(3, 1); 
  lcd.print("MasterMind");
  
  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);

  digitalWrite(LED_BLUE_1,  HIGH);
  digitalWrite(LED_BLUE_2,  HIGH);
  digitalWrite(LED_BLUE_3,  HIGH);
  digitalWrite(LED_BLUE_4,  HIGH);

  delay(300);
  digitalWrite(LED_BLUE_1,  LOW);
  digitalWrite(LED_BLUE_2,  LOW);
  digitalWrite(LED_BLUE_3,  LOW);
  digitalWrite(LED_BLUE_4,  LOW);
    
  delay(300);
  digitalWrite(LED_BLUE_1,  HIGH);
  digitalWrite(LED_BLUE_2,  HIGH);
  digitalWrite(LED_BLUE_3,  HIGH);
  digitalWrite(LED_BLUE_4,  HIGH);

  delay(300);
  digitalWrite(LED_BLUE_1,  LOW);
  digitalWrite(LED_BLUE_2,  LOW);
  digitalWrite(LED_BLUE_3,  LOW);
  digitalWrite(LED_BLUE_4,  LOW);
  delay(300);

  digitalWrite(LED_RED_1,  HIGH);
  digitalWrite(LED_RED_2,  HIGH);
  digitalWrite(LED_RED_3,  HIGH);
  digitalWrite(LED_RED_4,  HIGH);

  delay(300);
  digitalWrite(LED_RED_1,  LOW);
  digitalWrite(LED_RED_2,  LOW);
  digitalWrite(LED_RED_3,  LOW);
  digitalWrite(LED_RED_4,  LOW);
    
  delay(300);
  digitalWrite(LED_RED_1,  HIGH);
  digitalWrite(LED_RED_2,  HIGH);
  digitalWrite(LED_RED_3,  HIGH);
  digitalWrite(LED_RED_4,  HIGH);

  delay(300);
  digitalWrite(LED_RED_1,  LOW);
  digitalWrite(LED_RED_2,  LOW);
  digitalWrite(LED_RED_3,  LOW);
  digitalWrite(LED_RED_4,  LOW);

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Your goal is to"); 
  lcd.setCursor(0, 1); 
  lcd.print("guess my secret combination.");
  delay(2000);
  lcd.clear();
  lcd.print("combination.");
  delay(2000);
}


void show_secret_code (char* code, int length) 
{ 
  if (code == NULL) 
  {
    lcd.setCursor(0, 0);     
    lcd.print("Length must be");
    lcd.setCursor(0, 1); 
    lcd.print("less than 11");
    return;
  }
  
  char str1[] = "My secret code";
  lcd.setCursor(0, 0); 
  lcd.print(str1); 
  
  char* str2 = "                ";
  char str3[] = "was:            ";
 
  //                      "-------11-------";
  if (length == 1) str2 = "        -       "; 
  else if (length == 2) str2 = "       --       "; 
  else if (length == 3) str2 = "       ---      "; 
  else if (length == 4) str2 = "      ----      "; 
  else if (length == 5) str2 = "      -----     "; 
  else if (length == 6) str2 = "     ------     "; 
  else if (length == 7) str2 = "     -------    "; 
  else if (length == 8) str2 = "    --------    "; 
  else if (length == 9) str2 = "    ---------   "; 
  else if (length == 10) str2 = "   ----------   "; 
  else if (length == 11) str2 = "   -----------  "; 
  else if (length == 12) str2 = "  ------------  "; 
  else if (length == 13) str2 = "  ------------- "; 
  else if (length == 14) str2 = " -------------- "; 
  else if (length == 15) str2 = " ---------------"; 
  else if (length == 16) str2 = "----------------"; 
  else str2 = "             nan";  
  
  
  for (int i = 0, j = 0; i < 16; ++i) {
    if (str2[i] == '-') {
      str3[i] = code[j]; 
      ++j;    
    } 
    else if (str2[i] == 'n') {
      str3[15] = 'n'; str3[14] = 'a'; str3[13] = 'n';
      break;
    }
  } 

  lcd.setCursor(0, 1); 
  for (int i = 0; i < 16; ++i) {
    lcd.print(str3[i]);
    if (str3[i] != ' ') delay(400);  
  }

  delay(4000);
}


void LCD_CLEAR (void)
{
  lcd.clear();
}

void restart()
{
  lcd.setCursor(0,0);
  lcd.print("press any button");
  lcd.setCursor(0,1);
  lcd.print("to restart");

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);

  bool PRESS = false;
  do {
    PRESS = digitalRead(BTN_ENTER_PIN);
    if (PRESS) break;
    PRESS = digitalRead(BTN_1_PIN);
    if (PRESS) break;
    PRESS = digitalRead(BTN_2_PIN);
    if (PRESS) break;
    PRESS = digitalRead(BTN_3_PIN);
    if (PRESS) break;
    PRESS = digitalRead(BTN_4_PIN);

    //timing = millis(); 
  } while (PRESS != true);

  if (PRESS) 
  {
    //delay(1000);
    lcd.clear();
    lcd.setCursor(1,0);
 
    for (int i = 3; i > 0; --i) 
    {
      lcd.setCursor(0, 0);
      lcd.print(" restart in:    ");
      lcd.setCursor(13, 0);
      lcd.print(i);    
      lcd.setCursor(0, 1);
      lcd.print("  (>_<)  (>_<)  ");
  
      delay(1000);
    } 
  }  
}


void render_guess(char* guess) 
{
  if (guess == NULL) return;
  
  char str2[] = "Your guess:     ";

  for (int i = 0, j = 12; guess[i] != '\0'; ++i, ++j)
  {
     str2[j] = guess[i];
  }

  lcd.setCursor(0, 1);     
  lcd.print(str2);
}


void lcd_print (char* string, int row)
{
  lcd.setCursor(0, row);     
  lcd.print(string);
}
