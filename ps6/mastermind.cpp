#include "mastermind.h" 


boolean is_repeat (char string[], int length) 
{
  /**
   * sourse of information:
   * https://qna.habr.com/q/473022
   */
  
  for (int i = 0; i < length; ++i) 
  {
    char * str_ptr1;
    char * str_ptr2;
  
    str_ptr1 = strchr(string, string[i]);
    str_ptr2 = strrchr(string, string[i]);

    if (str_ptr2 != 0 && str_ptr2 != str_ptr1) return true;    
  }

  return false;
}


char* generate_code(bool repeat, int length)
{
  /**
   * sourse of information 
   * https://alexgyver.ru/lessons/random/
   */
  
  if (length <= 0 || length > 10) return NULL;

  char RAND_NUM[length+1];  // Рандомное число
  RAND_NUM[length] = '\0';

  int anal_read  = analogRead(2);
  randomSeed(anal_read);

  for (int i = 0; i < length; ++i) 
  {
    anal_read  = analogRead(0);
    randomSeed(anal_read);

    if (anal_read > 9) anal_read = 4;
    
    RAND_NUM[i] = '0' + random(10);   
  } 
 
  //if (RAND_NUM[0] == '0') RAND_NUM[0] = '0' + random(1, 10);

  while (!repeat && is_repeat(RAND_NUM, length)) 
  {
    for (int i = 0; i < length; ++i) 
    {
      char * str_ptr1;
      char * str_ptr2;
  
      str_ptr1 = strchr(RAND_NUM, RAND_NUM[i]);
      str_ptr2 = strrchr(RAND_NUM, RAND_NUM[i]);

      if (str_ptr2 != 0 && str_ptr2 != str_ptr1) { 
        RAND_NUM[i] = '0' + random(10);
      }
    }

    
    /*
      for (int j = 0; j < length; ++j) 
        while (i != j && RAND_NUM[i] == RAND_NUM[j]) {
          RAND_NUM[i] = '0' + random(10);
        }
    */
  }

  //Serial.begin(57600);
  //Serial.println(RAND_NUM);

  char* res = calloc(length+1, sizeof(char));
  strcpy(res, RAND_NUM);
  
  return res;
}


void play_game(char* secret) 
{  

  int len = 0;
  for (int i = 0; secret[i] != '\0'; ++i) ++len;
  //show_secret_code(secret, len);
  if (secret == NULL) return;

  //Show_Code_To_Guess(secret, len);
  //delay (2000);
  //LCD_CLEAR();

  // render history
  char* history[10];

  char strrr1[] = "0000";
  char strrr2[] = "0000";
  char strrr3[] = "0000";
  char strrr4[] = "0000";
  char strrr5[] = "0000";
  char strrr6[] = "0000";
  char strrr7[] = "0000";
  char strrr8[] = "0000";
  char strrr9[] = "0000";
  char strrr10[] = "0000";

  history[0] = strrr1;
  history[1] = strrr2;
  history[2] = strrr3;
  history[3] = strrr4;
  history[4] = strrr5;
  history[5] = strrr6;
  history[6] = strrr7;
  history[7] = strrr8;
  history[8] = strrr9;
  history[9] = strrr10;

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_4_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);
  
  bool PRESS_ENTER = false, PRESS_1 = false, PRESS_2 = false, PRESS_3 = false, PRESS_4 = false, WIN = false;
  char guess[] = "0000";
  int ROUND = 0;

  for (ROUND = 0; ROUND < 10 && !WIN; ++ROUND) 
  {          
    while (1)
    {
      PRESS_ENTER = digitalRead(BTN_ENTER_PIN);

      PRESS_1 = digitalRead(BTN_1_PIN);
      PRESS_2 = digitalRead(BTN_2_PIN);
      PRESS_3 = digitalRead(BTN_3_PIN);
      PRESS_4 = digitalRead(BTN_4_PIN);

      if (PRESS_1 && (guess[0] - '0') == 9) guess[0] = '0';
      else if (PRESS_1) guess[0] = '0' + (guess[0] - '0')+1;

      if (PRESS_2 && (guess[1] - '0') == 9) guess[1] = '0';      
      else if (PRESS_2) guess[1] = '0' + (guess[1] - '0')+1;
      
      if (PRESS_3 && (guess[2] - '0') == 9) guess[2] = '0';
      else if (PRESS_3) guess[2] = '0' + (guess[2] - '0')+1;

      if (PRESS_4 && (guess[3] - '0') == 9) guess[3] = '0';
      else if (PRESS_4) guess[3] = '0' + (guess[3] - '0')+1;

      if (ROUND != 0) render_history(secret, history, ROUND-1);
      else lcd_print("Generating ...", 0);
      //I am thinking a number:
      render_guess(guess);
      
      while (PRESS_1) {
        PRESS_1 = digitalRead(BTN_1_PIN); 
        delay(50);
      }
      while (PRESS_2) {
        PRESS_2 = digitalRead(BTN_2_PIN); 
        delay(50);
      } 
      while (PRESS_3) {
        PRESS_3 = digitalRead(BTN_3_PIN); 
        delay(50);
      } 
      while (PRESS_4) {
        PRESS_4 = digitalRead(BTN_4_PIN); 
        delay(50);
      } 
      
      int A = 0, B = 0;
      if (PRESS_ENTER) {
        get_score(secret, guess, &A, &B);
        if (A == 4 && B == 0) {
          WIN = true;
          break;
        }
        while (PRESS_ENTER) {
          PRESS_ENTER = digitalRead(BTN_ENTER_PIN); 
          delay(50);
        }
        break;
      }
  
    }
     
  history[ROUND][0] = guess[0];
  history[ROUND][1] = guess[1];
  history[ROUND][2] = guess[2];
  history[ROUND][3] = guess[3];
    
  for (int i = 0; i < 4; ++i) guess[i] = '0';
    if (!WIN) {
      turn_off_leds();
    }
  
  }

  if (WIN) 
  {
    //07: 9348 3A0B
    //Well done! You win in 7 guesses!

    render_leds(4, 0);
    delay(300);
    turn_off_leds();
    delay(200);
    render_leds(4, 0);
    delay(300);
    turn_off_leds();
    delay(200);
    
    LCD_CLEAR();
    //Serial.begin(57600);
    //Serial.println(ROUND);
    
    render_history(secret, history, ROUND);
    lcd_print("GG, you win!  xD", 1); 
    
    delay(10000);
    turn_off_leds(); 
     
  } else {

    /*
       TODO: fix lcd.init() - DONE
       TODO: fix get_score() - DONE
       TODO: new clean_history() - очистить историю хадов - DONE
    */
    
    LCD_CLEAR();
    render_history(secret, history, ROUND-1);
    // Looser! My secret combination was 9347.
    lcd_print("Looser! ham...", 1);
    delay(4000);
    
    LCD_CLEAR();
    //char str2[] = "was          lol";
    //for (int i = 4, j = 0; i < 8; ++i, ++j) str2[i] = secret[j];
    
    lcd_print("My secret code", 0);

    show_secret_code(secret, len);

    //Serial.begin(57600);
    //Serial.println(guess);
    //Serial.println(history[9]);
    //lcd_print(str2, 1);
  }
  
  delay(2000);
  turn_off_leds();

  LCD_CLEAR();

  history_menu(secret, history);
  
  clean_history(history);

  LCD_CLEAR();
  restart();
  LCD_CLEAR();

  delay(1000);
}

void get_score(char* secret, char* guess, int* peg_a, int* peg_b)
{  
  if (secret == NULL || guess == NULL) return;
  int PREG_A = 0, PREG_B = 0, len_secret = 0, len_guess = 0;

  for (int i = 0; secret[i] != '\0'; ++i) ++len_secret;
  for (int i = 0; guess[i] != '\0'; ++i) ++len_guess;

  if (len_secret == 0 || len_guess == 0) {*peg_a = PREG_A; *peg_b = PREG_B;}

  for (int i = 0, n = 99; secret[i] != '\0'; ++i)
  {
    if (secret[i] == guess[i]) {
      ++PREG_A;
      n = i;
    }
    
    for (int j = 0; guess[j] != '\0'; ++j)
    {
      if (j != n && j != i && guess[j] == secret[i] && guess[j] != secret[j] && guess[i] != secret[i]) {
        ++PREG_B;
        break;
      }
    }
    n = 99;
  }
  
  *peg_a = PREG_A;
  *peg_b = PREG_B;
}


void turn_off_leds(void)
{
  digitalWrite(LED_BLUE_1, LOW);
  digitalWrite(LED_BLUE_2, LOW);
  digitalWrite(LED_BLUE_3, LOW);
  digitalWrite(LED_BLUE_4, LOW);

  digitalWrite(LED_RED_1,  LOW);
  digitalWrite(LED_RED_2,  LOW);
  digitalWrite(LED_RED_3,  LOW);
  digitalWrite(LED_RED_4,  LOW);
}


void render_leds(const int peg_a, const int peg_b) 
{
  pinMode(LED_BLUE_1, OUTPUT);
  pinMode(LED_BLUE_2, OUTPUT);
  pinMode(LED_BLUE_3, OUTPUT);
  pinMode(LED_BLUE_4, OUTPUT);
  
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);

  if (1 == peg_a) {
    digitalWrite(LED_RED_1,  HIGH);
  } else if (2 == peg_a) {
    digitalWrite(LED_RED_1,  HIGH);
    digitalWrite(LED_RED_2,  HIGH);
  } else if (3 == peg_a) {
    digitalWrite(LED_RED_1,  HIGH);
    digitalWrite(LED_RED_2,  HIGH);
    digitalWrite(LED_RED_3,  HIGH);
  } else if (4 == peg_a) {
    digitalWrite(LED_RED_1,  HIGH);
    digitalWrite(LED_RED_2,  HIGH);
    digitalWrite(LED_RED_3,  HIGH);
    digitalWrite(LED_RED_4,  HIGH);
  }

  if (1 == peg_b) {
    digitalWrite(LED_BLUE_1,  HIGH);
  } else if (2 == peg_b) {
    digitalWrite(LED_BLUE_1,  HIGH);
    digitalWrite(LED_BLUE_2,  HIGH);
  } else if (3 == peg_b) {
    digitalWrite(LED_BLUE_1,  HIGH);
    digitalWrite(LED_BLUE_2,  HIGH);
    digitalWrite(LED_BLUE_3,  HIGH);
  } else if (4 == peg_b) {
    digitalWrite(LED_BLUE_1,  HIGH);
    digitalWrite(LED_BLUE_2,  HIGH);
    digitalWrite(LED_BLUE_3,  HIGH);
    digitalWrite(LED_BLUE_4,  HIGH);
  }
}

void render_history (char* secret, char** history, const int entry) 
{
  int n = 0, A, B, ENTRY = entry;
  if (entry == 10) ENTRY = 9;

  // ***** check NULL
  if (history[ENTRY] == NULL || history == NULL) return;

  char str1[] = "00:             "; 
  if (ENTRY == 9) str1[0] = '1';
  else str1[1] = '0' + entry+1;
  
  for (int i = 4, j = 0; history[ENTRY][j] != '\0'; ++i, ++j)
  {
    str1[i] = history[ENTRY][j];
    n = i;
  } ++n;

  get_score(secret, history[ENTRY], &A, &B);

  render_leds(A, B);

  if (A == 4 && B == 0) 
  {
    if (entry == 10) str1[0] = '1';
    else str1[1] = '0' + entry-1;
  }
  
  str1[n+1] = '0'+A;
  str1[n+2] = 'A';
  str1[n+3] = '0'+B;
  str1[n+4] = 'B';
  
  lcd_print(str1, 0);
}


void clean_history(char** history) 
{
  for (int i = 0; i < 10; ++i) 
  {
    for (int j = 0; history[i][j] != '\0'; ++j) 
    {
      history[i][j] = '0';
    }  
  }
}


void history_menu (char* secret, char** history)
{
  lcd_print("1 - view history", 0); // history
  lcd_print("ENTER to exit", 1);
  //delay(2000);

  pinMode(BTN_1_PIN, INPUT);
  pinMode(BTN_2_PIN, INPUT);
  pinMode(BTN_3_PIN, INPUT);
  pinMode(BTN_ENTER_PIN, INPUT);

  bool PRESS_ENTER = false, PRESS_1 = false, PRESS_2 = false, PRESS_3 = false;
  //char str_ptr[] = "00:             ";
  
  while (!PRESS_1 && !PRESS_ENTER)
  {
    PRESS_ENTER = digitalRead(BTN_ENTER_PIN);
    PRESS_1 = digitalRead(BTN_1_PIN);
  }

  if (PRESS_ENTER) return;

  while (PRESS_1) {
    PRESS_1 = digitalRead(BTN_1_PIN); 
    delay(50);
  }

  LCD_CLEAR();
  lcd_print("1 - exit        ", 0); 
  lcd_print("2 - down, 3 - up", 1);

  int ROUND = 0;

  //Serial.begin(57600);

  while (!PRESS_1)
  {
    PRESS_1 = digitalRead(BTN_1_PIN);
    PRESS_2 = digitalRead(BTN_2_PIN);
    PRESS_3 = digitalRead(BTN_3_PIN);

    if (PRESS_1) break;
    
    if (PRESS_2) --ROUND;      
    else if (PRESS_3) ++ROUND;

    if (ROUND == 10) ROUND = 9;
    else if (ROUND == -1) ROUND = 0;
         
    if (PRESS_2 || PRESS_3) {
      turn_off_leds();

      //LCD_CLEAR();

      while (PRESS_2) {
        PRESS_2 = digitalRead(BTN_2_PIN); 
        delay(50);
      }
      while (PRESS_3) {
        PRESS_3 = digitalRead(BTN_3_PIN); 
        delay(50);
      }
      render_history(secret, history, ROUND);

      //Serial.println(history[ROUND]);
      //Serial.println(history[ROUND]);
    }
      
    while (PRESS_1) {
      PRESS_1 = digitalRead(BTN_1_PIN); 
      delay(50);
    }
  }
}
