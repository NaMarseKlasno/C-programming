#include "lcd_wrapper.h" 

LiquidCrystal_I2C lcd(0x27, 16, 2); 


void lcd_init (void) 
{
  lcd.init();
  lcd.backlight();
}


void show_splash_screen (void) 
{
  lcd.setCursor(3, 0); 
  lcd.print("Welcome to"); 
  lcd.setCursor(3, 1); 
  lcd.print("MasterMind");
  delay(2000);
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


void Show_Code_To_Guess (char* code, int length) 
{ 
  if (code == NULL) 
  {
    lcd.setCursor(0, 0);     
    lcd.print("Length must be");
    lcd.setCursor(0, 1); 
    lcd.print("less than 11");
    return;
  }
  
  char str1[] = "My guess:   ";
  lcd.setCursor(0, 0); 
  lcd.print(str1); 
  
  char* str2 = "                ";
  char str3[] = "                ";
 
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
    delay(1000);
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
