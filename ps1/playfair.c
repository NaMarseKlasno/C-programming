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
void dellDuplicates(char* arr) {
    unsigned long len = strlen(arr);
    
    int lett = 1;
    for (int i = 1; i < len; ++i){
        int j;
        for (j = 0; j < lett; ++j)
            if (arr[i] == arr[j]){
                arr[i] = 0;
                break;
            }
        if (j == lett) {
            arr[lett] = arr[i];
            ++lett;
        }
    }
    arr[lett] = 0;
}
void removeSpaces(char *string) {
    int n = 0;
    char arr[strlen(string)];
    for (int i = 0; i < strlen(string); ++i) arr[i] = '0';
    
    for (int i = 0; i < strlen(string); ++i) {
        if (!isspace(string[i])) {
            arr[n] = string[i];
            ++n;
        }
    }
    for (int i = 0; i < strlen(string); ++i) string[i] = '0';
    
    for (int i = 0; i < strlen(string); ++i) {
        if (arr[i] != '0')
            string[i] = arr[i];
        else string[i] = '\0';
    }
    
    //printf("string: %s\n", string);
    
}


char* playfair_encrypt(const char* key, const char* text)
{
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
    char* reKey = (char*)calloc(strlen(key), sizeof(char));
    for (int i = 0; i < strlen(key); i++)
        reKey[i] = key[i];
    dellDuplicates(reKey);
    
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
    
    char* reText = (char*)calloc(strlen(text), sizeof(char));
    for (int i = 0; i < strlen(text); i++){
        reText[i] = toupper(text[i]);
        if (toupper(text[i]) == 'W') reText[i] = 'V';
    }
    
    //printf(".........1\n");
    removeSpaces(reText);
    //printf("%s\n", reText);
    //printf(".........1\n");


    unsigned long h = 0;
    for (int i = 0; i < strlen(reText); ++i) if (reText[i] == '.') ++h;
    h = strlen(reText) - h;
    reText = realloc(reText, h);
    
    
    int a = 0;
    unsigned long numIcv = 0;
    for (int i = 0; i < strlen(text); i++){
        if (a == 1 && reText[i] == reText[i-1] && reText[i] != 'X' && reText[i-2] != 'X'){
            reText[i-1] = '.';
            ++numIcv;
        }
        a = 1;
    }
    reText = realloc(reText, strlen(text)+numIcv);
    //char helpText[strlen(text)+numIcv];
    char* helpText = (char*)calloc(strlen(text)+numIcv, sizeof(char));
    
    for (int i = 0; i < strlen(text)+numIcv; ++i) {
        if (reText[i] == '.'){
            ++i;
            helpText[i] = 'X';
        }
    }

    unsigned long c = 0;
    for (int i = 0; i < strlen(text)+numIcv; ++i) {
        if (reText[c] == '.') {
            helpText[i] = reText[c+1];
            ++i;
        }
        helpText[i] = reText[c];
        // длинна ртекст - с не будет больше длинны хелп текст - и
        ++c;
    }
    for (int i = 0; i < strlen(text)+numIcv; ++i) if (helpText[i] == '.') helpText[i] = 'X';

    
    //printf("[%s] %lu\n", reText, numIcv);
    //printf("{%s}\n", helpText);

    numIcv = strlen(text) - numIcv;
    
    free(reText);
    reText = NULL;

    char* eText = (char*)calloc(strlen(text)+numIcv, sizeof(char));

    for (int i = 0; i < strlen(text)+numIcv; ++i) eText[i] = helpText[i];
    numIcv = strlen(eText);
    if (numIcv % 2 != 0) {
        eText = realloc(eText, numIcv+1);
        for (int i = 0; i < numIcv; i++)
            eText[i] = eText[i];
        eText[numIcv] = 'X';
        ++numIcv;
        //printf("[%s] %lu\n", eText, numIcv);
    } //printf("----------\n");
    
    char* reFair = (char*)calloc(numIcv, sizeof(char));
    //char reFair[numIcv];
    
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
    
    char* result = (char*)calloc(strlen(reFair) + value, sizeof(char));
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
    return 0;
}


