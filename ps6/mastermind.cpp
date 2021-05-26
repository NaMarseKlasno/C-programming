#include "mastermind.h" 


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

  if (repeat) 
  {
    for (int i = 0; i < length; ++i) 
      for (int j = 0; j < length; ++j) 
        while (i != j && RAND_NUM[i] == RAND_NUM[j]) {
          RAND_NUM[i] = '0' + random(10);
        }
  }

  //Serial.begin(57600);
  //Serial.println(RAND_NUM);

  char* res = calloc(length+1, sizeof(char));
  strcpy(res, RAND_NUM);
  
  return res;
}


void play_game(char* secret) 
{  

  int peg_a, peg_b;

  get_score("9347", "1234", &peg_a, &peg_b);

  render_leds(peg_a, peg_b);

  delay(50000);  

  
  int len = 0;
  if (secret != NULL) for (int i = 0; secret[i] != '\0'; ++i) ++len;

  Show_Code_To_Guess(secret, len);
  if (secret == NULL) delay(10000);
  delay (4000);
  LCD_CLEAR();

  restart();
  LCD_CLEAR();

  delay(1000);
}

void get_score(char* secret, char* guess, int* peg_a, int* peg_b)
{  
  if (secret == NULL || guess == NULL) return;
  int PREG_A = 0, PREG_B = 0;

  if (strlen(secret) == 0 || strlen(guess) == 0) {*peg_a = PREG_A; *peg_b = PREG_B;}

  for (int i = 0; secret[i] != '\0'; ++i)
  {
    if (secret[i] == guess[i]) ++PREG_A;
    
    for (int j = 0; secret[j] != '\0'; ++j)
    {
      if (i != j && secret[i] == guess[j]) ++PREG_B;
    }
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
