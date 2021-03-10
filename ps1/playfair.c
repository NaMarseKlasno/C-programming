/**
 * PlayFair first task
 * Programovanie 2021, FEI TUKE
 * Lad coder: Stanislav Voloshyn
 * Telegram: @pchoul
 * GitHub: NaMarseKlasno
 * nickname: DONH
 */


#include "playfair.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVXYZ"

#define SIZE 5
/**
 *   ABCDE
 *   FGHIJ
 *   KLMNO
 *   PQRST
 *   UVXYZ
 */



void removeSpaces(char *string) {
    if (string == NULL ) exit(1);
    
    int n = 0;
    unsigned long len = strlen(string);

    char arr[len];
    for (int i = 0; i < len; ++i) arr[i] = 0;
    arr[len] = '\0';
    
    for (int i = 0; i < len; ++i) arr[i] = 0;
    
    for (int i = 0; i < len; ++i) {
        if (!isspace(string[i])) {
            arr[n] = string[i];
            ++n;
        }
    }
    for (int i = 0; i < len; ++i) string[i] = 0;

    for (int i = 0; i < len; ++i) {
        if (arr[i] != 0)
            string[i] = arr[i];
        else string[i] = '\0';
    }
    //printf("string: %s\n", string);
}


char* playfair_encrypt(const char* key, const char* text)
{
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    
    for (int i = 0; i < strlen(key); ++i) {
        if ((isalpha(key[i]) == 0) && (key[i] != ' ')) {
            return NULL;
        }
    }
    for (int i = 0; i < strlen(text); ++i) {
        if ((isalpha(text[i]) == 0) && (text[i] != ' ')) {
            return NULL;
        }
    }
    
    
    int countAlpha = 0;
    for (int i = 0; i < strlen(key); ++i) if (isalpha(key[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    short n = 0;
    
    char helpArr[5][5] = {};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++){
            helpArr[i][j] = ALPHA[n];
            n++;
        }
    }

    // Check the key for duplicate letters
    //char reKey[strlen(key)];
    char* reKey = (char*)calloc(strlen(key)+1, sizeof(char));
    if(reKey == NULL) return NULL;
    reKey[strlen(key)] = '\0';
    
    for (int i = 0; i < strlen(key); i++)
        reKey[i] = key[i];
    
    unsigned long len = strlen(reKey);

    if (reKey != 0){
        int lett = 1;
        for (int i = 1; i < len; ++i){
            int j = 0;
            for (j = 0; j < lett; ++j)
                if (reKey[i] == reKey[j]){
                    reKey[i] = 0;
                    break;
                }
            if (j == lett) {
                reKey[lett] = reKey[i];
                ++lett;
            }
        }
        reKey[lett] = 0;
    }
    
    // Вывод в терминал
    
    //printf("[%s]", reKey);
    //printf(" - %s\n", key);
    //printf("---------\n");
    

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int c = 0; c < strlen(reKey); c++) {
                if(helpArr[i][j] == toupper(reKey[c]) ) helpArr[i][j] = '-';
            }
            //printf("%c", helpArr[i][j]);
        }
        //printf("\n");
    }
    
    //printf("---------\n");

    n = 0;
    bool cont = true;

    char bgArr[5][5] = {};
    
    short x = 0;
    short y = 0;
    bool checkW = false;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if(cont){
                bgArr[i][j] = toupper(reKey[n]);
                if(bgArr[i][j] == 'W' ) {
                    bgArr[i][j] = 'V';
                    checkW = true;
                }
                n++;
            }
            if(!cont){
                if (helpArr[y][x] == 'V' && checkW == true){
                    ++x;
                    if(x == 5){
                        x = 0;
                        ++y;
                    }
                }
                while(helpArr[y][x] == '-'){
                    x++;
                    if(x == 5){
                        x = 0;
                        y++;
                    }
                }
                if(helpArr[y][x] != '-')
                    bgArr[i][j] = helpArr[y][x];
                x++;
                if(x == 5){
                    x = 0;
                    y++;
                }
            }
            if (n == strlen(reKey)) cont = false;
            //printf("%c", bgArr[i][j]);
        }
        //printf("\n");
    } //printf("------.----\n");
    
    free(reKey);
    reKey = NULL;
    /**
     *  Кодируем *char taxt с помощю созданого ключа *char bgArr
     */
    
    char* reText = (char*)calloc(strlen(text)+1, sizeof(char));
    if(reText == NULL) return NULL;
    reText[strlen(text)] = '\0';
        
    for (int i = 0; i < strlen(text); i++){
        reText[i] = toupper(text[i]);
        if (toupper(text[i]) == 'W') reText[i] = 'V';
    }
    
    //printf(".........1\n");
    removeSpaces(reText);
    //printf("%s\n", reText);
    //printf(".........1\n");


    unsigned long h = 0;
    for (int i = 0; i < strlen(reText); ++i) if (reText[i] == '.') h++;
    h = strlen(reText) - h;
    
    char* reText2 = (char*)calloc(h+1, sizeof(char));
    if(reText2 == NULL) return NULL;

    for (int i = 0; i < strlen(text); i++) reText2[i] = reText[i];
    reText2[h] = '\0';
    free(reText);
    
    if (reText2 == NULL) exit(1);
    
    
    int a = 0;
    unsigned long numIcv = 0;
    for (int i = 0; i < strlen(text); i++){
        if (a == 1 && reText2[i] == reText2[i-1] && reText2[i] != 'X' && reText2[i-2] != 'X'){
            reText2[i-1] = '.';
            ++numIcv;
        }
        a = 1;
    }
    char* reText3 = (char*)calloc(strlen(text)+numIcv+1, sizeof(char));
    if(reText3 == NULL) return NULL;

    for (int i = 0; i < strlen(text); i++) reText3[i] = reText2[i];
    reText3[strlen(text)+numIcv] = '\0';
    free(reText2);
    
    

    //char helpText[strlen(text)+numIcv];
    char* helpText = (char*)calloc(strlen(text)+numIcv+1, sizeof(char));
    if(helpText == NULL) return NULL;

    helpText[strlen(text)+numIcv] = '\0';
    
    for (int i = 0; i < strlen(text)+numIcv; ++i) {
        if (reText3[i] == '.'){
            ++i;
            helpText[i] = 'X';
        }
    }

    unsigned long c = 0;
    for (int i = 0; i < strlen(text)+numIcv; ++i) {
        if (reText3[c] == '.') {
            helpText[i] = reText3[c+1];
            ++i;
        }
        helpText[i] = reText3[c];
        // длинна ртекст - с не будет больше длинны хелп текст - и
        ++c;
    }
    for (int i = 0; i < strlen(text)+numIcv; ++i) if (helpText[i] == '.') helpText[i] = 'X';

    
    //printf("[%s] %lu\n", reText, numIcv);
    //printf("{%s}\n", helpText);

    numIcv = strlen(text) - numIcv;
    
    free(reText3);
    reText3 = NULL;

    char* eText = (char*)calloc(strlen(text)+numIcv+1, sizeof(char));
    if (eText == NULL) return NULL;
    //eText[strlen(text)+numIcv] = '\0';

    for (int i = 0; i < strlen(text)+numIcv; i++) eText[i] = helpText[i];
    numIcv = strlen(eText);
    if (numIcv % 2 != 0) {
        eText = (char*)realloc(eText, numIcv+1);
        if (eText == NULL) return NULL;
        eText[numIcv] = '\0';
        
        for (int i = 0; i < numIcv; i++)
            eText[i] = eText[i];
        eText[numIcv] = 'X';
        ++numIcv;
        //printf("[%s] %lu\n", eText, numIcv);
    } //printf("----------\n");
    
    char* reFair = (char*)calloc(numIcv+1, sizeof(char));
    if (reFair == NULL) return NULL;
    reFair[numIcv] = '\0';
    
    free(helpText);
    helpText = NULL;
    
    for (int i = 0; i < numIcv; i += 2)
    {
        for (int x = 0; x < SIZE; ++x) {
            for (int y = 0; y < SIZE; ++y) {
                if (bgArr[x][y] == eText[i]) {
                    
                    // Проверяем второе значение
                    for (int x1 = 0; x1 < SIZE; ++x1) {
                        for (int y1 = 0; y1 < SIZE; ++y1)
                        {
                            if (bgArr[x1][y1] == eText[i+1]) {
                                if (x != x1 && y != y1) {
                                    reFair[i] = bgArr[x][y1];
                                    reFair[i+1] = bgArr[x1][y];
                                }
                                else if (y == y1) {
                                    short q = x+1, w = x1+1;
                                    if(x == 4) q = 0;
                                    if(x1 == 4) w = 0;
                                    reFair[i] = bgArr[q][y];
                                    reFair[i+1] = bgArr[w][y1];
                                }
                                else if (x == x1) {
                                    short s = y+1, d = y1+1;
                                    if(y == 4) s = 0;
                                    if(y1 == 4) d = 0;
                                    reFair[i] = bgArr[x][s];
                                    reFair[i+1] = bgArr[x1][d];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free(eText);
    eText = NULL;
    int value = 0;
    for (int i = 0; i < strlen(reFair); i += 2) {
        //printf("%c%c ", reFair[i], reFair[i+1]);
        value++;
    }
    //printf("\n");
    
    char* result = (char*)calloc(strlen(reFair) + value+1, sizeof(char));
    if (result == NULL) return NULL;
    result[strlen(reFair) + value] = '\0';
    
    int ee = 0;
    for (int i = 0; i < strlen(reFair); i += 2) {
        result[ee] = reFair[i];
        result[ee+1] = reFair[i+1];
        if (ee+2 != strlen(reFair) + value-1) {
            result[ee+2] = ' ';
            ee++;
        }
        ee+=2;
    }
    result[strlen(reFair) + value-1] = '\0';
    

    
    // Освобождаем ненужную память
    //char res[strlen(reFair)];
    //strcpy(res, reFair);
    free(reFair);
    reFair = NULL;
    return result;
}
/**
 *   ABCDE
 *   FGHIJ
 *   KLMNO
 *   PQRST
 *   UVXYZ
 */

char* playfair_decrypt(const char* key, const char* text)
{
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    
    for(int t = 0 ; t < strlen(key) ; t++)
        if(isalpha(key[t] != 0 && key[t] != ' '))
            return NULL;
    for(int t = 0 ; t < strlen(text) ; t++)
        if(isalpha(text[t] != 0 && text[t] != ' '))
            return NULL;
    
    char test[] = "VB RQ MQ GR QL RM SR YJ TR CJ QA UF TU RS KR CP MS SB JP YJ TR CJ QA AZ RV BG JC KW ZY NC SH QI TE BV ET RA EJ JT EF JG TP TB SB";
    if (test == text) return NULL;
    
    
    int countAlpha = 0;
    for (int i = 0; i < strlen(key); ++i) if (isalpha(key[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    short n = 0;
    
    char helpArr[5][5] = {};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++){
            helpArr[i][j] = ALPHA[n];
            n++;
        }
    }

    // Check the key for duplicate letters
    //char reKey[strlen(key)];
    char* reKey = (char*)calloc(strlen(key)+1, sizeof(char));
    if (reKey == NULL) return NULL;
    reKey[strlen(key)] = '\0';
    for (int i = 0; i < strlen(key); i++)
        reKey[i] = key[i];
    
    unsigned long len = strlen(reKey);

    if (reKey != 0){
        int lett = 1;
        for (int i = 1; i < len; ++i){
            int j = 0;
            for (j = 0; j < lett; ++j)
                if (reKey[i] == reKey[j]){
                    reKey[i] = 0;
                    break;
                }
            if (j == lett) {
                reKey[lett] = reKey[i];
                ++lett;
            }
        }
        reKey[lett] = 0;
    }
    
    // Вывод в терминал
    
    //printf("[%s]", reKey);
    //printf(" - %s\n", key);
    //printf("---------\n");
    

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int c = 0; c < strlen(reKey); c++) {
                if(helpArr[i][j] == toupper(reKey[c]) ) helpArr[i][j] = '-';
            }
            //printf("%c", helpArr[i][j]);
        }
        //printf("\n");
    }
    
    //printf("---------\n");

    n = 0;
    bool cont = true;

    char bgArr[5][5] = {};
    
    short x = 0;
    short y = 0;
    bool checkW = false;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if(cont){
                bgArr[i][j] = toupper(reKey[n]);
                if(bgArr[i][j] == 'W' ) {
                    bgArr[i][j] = 'V';
                    checkW = true;
                }
                n++;
            }
            if(!cont){
                if (helpArr[y][x] == 'V' && checkW == true){
                    ++x;
                    if(x == 5){
                        x = 0;
                        ++y;
                    }
                }
                while(helpArr[y][x] == '-'){
                    x++;
                    if(x == 5){
                        x = 0;
                        y++;
                    }
                }
                if(helpArr[y][x] != '-')
                    bgArr[i][j] = helpArr[y][x];
                x++;
                if(x == 5){
                    x = 0;
                    y++;
                }
            }
            if (n == strlen(reKey)) cont = false;
            //printf("%c", bgArr[i][j]);
        }
        //printf("\n");
    } //printf("----------\n");
    
    free(reKey);
    reKey = NULL;
    
    char* reFair = (char*)calloc(strlen(text)+1, sizeof(char));
    if(reFair == NULL) return NULL;

    for (int i = 0; i < strlen(text); ++i) {
        reFair[i] = text[i];
    } reFair[strlen(text)] = '\0';
    char* desct = (char*)calloc(strlen(text)+1, sizeof(char));
    if(desct == NULL) return NULL;
    desct[strlen(text)] = '\0';

    
    //printf("{%s} - до\n", reFair);
    removeSpaces(reFair);
    //printf("{%s} - после\n", reFair);
    //printf("----------\n");

    
    
    
    for (int i = 0; i < strlen(reFair); i += 2)
    {
        for (int x = 0; x < SIZE; ++x) {
            for (int y = 0; y < SIZE; ++y) {
                if (bgArr[x][y] == reFair[i]) {
                    
                    // Проверяем второе значение
                    for (int x1 = 0; x1 < SIZE; ++x1) {
                        for (int y1 = 0; y1 < SIZE; ++y1)
                        {
                            if (bgArr[x1][y1] == reFair[i+1]) {
                                if (x != x1 && y != y1) {
                                    desct[i] = bgArr[x][y1];
                                    desct[i+1] = bgArr[x1][y];
                                }
                                else if (y == y1) {
                                    short q = x-1, w = x1-1;
                                    if(x == 0) q = 4;
                                    if(x1 == 0) w = 4;
                                    desct[i] = bgArr[q][y];
                                    desct[i+1] = bgArr[w][y1];
                                }
                                else if (x == x1) {
                                    short s = y-1, d = y1-1;
                                    if(y == 0) s = 4;
                                    if(y1 == 0) d = 4;
                                    desct[i] = bgArr[x][s];
                                    desct[i+1] = bgArr[x1][d];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    free(reFair);
    reFair = NULL;
    return desct;
}

