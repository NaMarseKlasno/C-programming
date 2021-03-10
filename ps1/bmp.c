//
//  bmp.c
//  TopSelect
//
//  Created by Macbook Pro on 26.02.2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "playfair.h"
#include <stdbool.h>
#include <math.h>

#define ALPHAB "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_char2(const int character, bool bits[8]);

void* checkNul(void* p){
    if (p == 0) exit(37);
    return p;
}

char* reverse(const char* text){
    if (text == NULL) return NULL;
    if (strcmp("", text) == 0) return NULL;


    char* reverseText = checkNul( calloc(strlen(text) + 1, sizeof(char)) );
    for (int i = 0; i < strlen(text); i++) reverseText[i] = toupper(text[i]);
    reverseText[strlen(text)] = '\0';
    
    
    unsigned long  i = 0, j = strlen(text) - 1;
    char c;
 
    for(; i < j; ++i, --j){
        c = toupper(text[i]);
        reverseText[i] = toupper(reverseText[j]);
        reverseText[j] = c;
    }
    return reverseText;
}


char* vigenere_encrypt(const char* key, const char* text){
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for(int t = 0 ; t < strlen(key) ; t++)
        if(!isalpha(key[t]))
            return NULL;
    int countAlpha = 0;
    for (int i = 0; i < strlen(text); ++i) if (isalpha(text[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    char mainKey[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) mainKey[i] = 0;
    
    for (int i = 0, j = 0, c = 0; c < strlen(text); ++i) {
        if (isalpha(text[i])){
            mainKey[c] = key[j];
            ++j;
            //printf("%c\n", mainKey[c]);
            if (j == strlen(key)) j = 0;
            ++c;
        }else {
            mainKey[c] = ' ';
            c++;
        }
    } mainKey[strlen(text)] = '\0';
    //printf("%s\n", mainKey);
    //printf("%s\n", text);


    int numKey[strlen(mainKey)+1];
    for (int i = 0; i < strlen(mainKey); ++i) numKey[i] = 0;
    
    for (int i = 0; i < strlen(mainKey); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(mainKey[i])) {
                numKey[i] = j;
            }
            else if (!isalpha(mainKey[i])){
                numKey[i] = -1;
                //printf("[%d] ", numKey[i]);
            }
        }
    } numKey[strlen(mainKey)] = '\0';
    //printf("\n");
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numKey[i]);
    
    //printf("\n");
   
    int numText[strlen(text) + 1];
    for (int i = 0; i < strlen(text); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])) {
                numText[i] = j;
            }
            else if (!isalpha(text[i]))
                numText[i] = -1;
        }
    } numText[strlen(text)] = '\0';
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numText[i]);
    
    //printf("\n");

    
    int resInt[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) resInt[i] = 0;
    
    for (int i = 0; i < strlen(text); ++i) {
        resInt[i] = numText[i] + numKey[i];
        if (resInt[i] >= 26) resInt[i] -= 26;
        if (numText[i] == -1) resInt[i] = -1;
        if (numKey[i] == -1) resInt[i] = -1;
    } resInt[strlen(text)] = '\0';

    //for (int i = 0; i < strlen(text); ++i) printf("%i ", resInt[i]);
    //printf("\n");

    char* resSting = checkNul(calloc(strlen(text)+1, sizeof(char)));

    for (int i = 0; i < strlen(text); ++i) {
        for (int j = 0; j < 26; ++j) {
            if ( j == resInt[i] ) resSting[i] = ALPHAB[j];
            if (resInt[i] == -1) resSting[i] = text[i];
        }
    }
    resSting[strlen(text)] = '\0';
    //printf("%s - resString\n", resSting);
    
    return resSting;
}


char* vigenere_decrypt(const char* key, const char* text){
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for(int t = 0 ; t < strlen(key) ; t++)
        if(!isalpha(key[t]))
            return NULL;
    int countAlpha = 0;
    for (int i = 0; i < strlen(text); ++i) if (isalpha(text[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    
    char mainKey[strlen(text)+1];
    for (int i = 0, j = 0, c = 0; c < strlen(text); ++i) {
        if (isalpha(text[i])){
            mainKey[c] = key[j];
            ++j;
            //printf("%c\n", mainKey[c]);
            if (j == strlen(key)) j = 0;
            ++c;
        }else {
            mainKey[c] = ' ';
            c++;
        }
    } mainKey[strlen(text)] = '\0';
    
    int numKey[strlen(mainKey)+1];
    for (int i = 0; i < strlen(mainKey); ++i) numKey[i] = 0;
    
    for (int i = 0; i < strlen(mainKey); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(mainKey[i])) {
                numKey[i] = j;
            }
            else if (!isalpha(mainKey[i])){
                numKey[i] = -1;
                //printf("[%d] ", numKey[i]);
            }
        }
    } numKey[strlen(mainKey)] = '\0';
    //printf("=============\n");
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numKey[i]);
    
    //printf("\n");
   
    int numText[strlen(text) + 1];
    for (int i = 0; i < strlen(text); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])) {
                numText[i] = j;
            }
            else if (!isalpha(text[i]))
                numText[i] = -1;
        }
    } numText[strlen(text)] = '\0';
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numText[i]);
    
    //printf("\n");
    
    
    
    int resInt[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) resInt[i] = 0;
    
    for (int i = 0; i < strlen(text); ++i) {
        resInt[i] = numText[i] - numKey[i];
        if (resInt[i] < 0) resInt[i] += 26;
        if (numText[i] == -1) resInt[i] = -1;
        if (numKey[i] == -1) resInt[i] = -1;
    } resInt[strlen(text)] = '\0';

    //for (int i = 0; i < strlen(text); ++i) printf("%i ", resInt[i]);
    //printf("\n");

    char* resSting = calloc(strlen(text)+1, sizeof(char));
    //resSting[strlen(text)] = '\0';

    for (int i = 0; i < strlen(text); ++i) {
        for (int j = 0; j < 26; ++j) {
            if ( j == resInt[i]) resSting[i] = ALPHAB[j];
            if (resInt[i] == -1) resSting[i] = text[i];
        } // Uz z dom na dom podavali mestania svoje dievcata a teraz je rad na kralovej dcere
    }
    //printf("%s - resString\n", resSting);

    resSting[strlen(text)] = '\0';
    //printf("%s - resString\n", resSting);
    
    return resSting;
}


unsigned char* bit_encrypt(const char* text){
    if (text == NULL) return NULL;
    if (strcmp("", text) == 0) return NULL;
   
    
    // 10 to 2
    bool str[8];
    bool binArr[(strlen(text) * 8)+1];
    binArr[strlen(text) * 8] = '\0';
    int num = 0;
    //printf("start\n");
    for (int i = 0; i < strlen(text); ++i) {
        encode_char(text[i], str);
        for (int i = 0; i < 8; ++i) {
            binArr[num] = str[i];
            //printf("%d", str[i]);
            ++num;
        } //printf("\n");
        for (int i = 0; i < 8; i++) str[i] = 0;
    }//printf("boy next dor\n");
    //for (int i = 0; i < (strlen(text) * 8); ++i) printf("%d", binArr[i]);
    //printf("\n");
    
    // шифруем binArr
    bool enbinArr[(strlen(text) * 8)+1];
    enbinArr[strlen(text) * 8] = '\0';

    
    bool fbin[4+1];
    fbin[4] = '\0';
    for (int i = 0; i < strlen(text) * 8; i+=8) {
        fbin[0] = binArr[i+1];
        fbin[1] = binArr[i+0];
        fbin[2] = binArr[i+3];
        fbin[3] = binArr[i+2];
        enbinArr[i+0] = fbin[0];
        enbinArr[i+1] = fbin[1];
        enbinArr[i+2] = fbin[2];
        enbinArr[i+3] = fbin[3];
        
        if (fbin[0] == binArr[i+4]) enbinArr[i+4] = 0;
        else enbinArr[i+4] = 1;
        if (fbin[1] == binArr[i+5]) enbinArr[i+5] = 0;
        else enbinArr[i+5] = 1;
        if (fbin[2] == binArr[i+6]) enbinArr[i+6] = 0;
        else enbinArr[i+6] = 1;
        if (fbin[3] == binArr[i+7]) enbinArr[i+7] = 0;
        else enbinArr[i+7] = 1;
    }
    
    //printf("boy next dor\n");
    //for (int i = 0; i < (strlen(text) * 8); ++i) printf("%d", enbinArr[i]);
    //printf("\n");
    //printf("boy next dor\n");

    unsigned char* result = checkNul(calloc(strlen(text) + 1, sizeof(char)));
    bool tochar[9];
    tochar[8] = '\0';
    num = 0;
    for (int i = 0; i < strlen(text) * 8; i+=8){
        tochar[0] = enbinArr[i+0];
        tochar[1] = enbinArr[i+1];
        tochar[2] = enbinArr[i+2];
        tochar[3] = enbinArr[i+3];
        tochar[4] = enbinArr[i+4];
        tochar[5] = enbinArr[i+5];
        tochar[6] = enbinArr[i+6];
        tochar[7] = enbinArr[i+7];
        
        result[num] = decode_byte(tochar);
        ++num;
    }
    result[strlen(text)] = '\0';
    return result;
}


char* bit_decrypt(const unsigned char* text){
    if (text == NULL) return NULL;
    if (strcmp("", (char*)text) == 0) return NULL;

    //for (int i = 0; i < strlen((char*)text); ++i) {
    //    printf("%d ", text[i]);
    //} printf("\n");

    
    // 10 to 2
    bool str[8] = {};
    bool binArr[(strlen((char*)text) * 8)+1];
    binArr[strlen((char*)text) * 8] = '\0';
    int num = 0;
    //printf("start\n");
    for (int i = 0; i < strlen((char*)text); ++i) {
        //printf("[%d]\n", text[i]);
        encode_char2(text[i], str);
        for (int i = 0; i < 8; ++i) {
            binArr[num] = str[i];
            //printf("%d", str[i]);
            ++num;
        } //printf("\n");
        for (int i = 0; i < 8; i++) str[i] = 0;
    }//printf("boy next dor\n");
    //for (int i = 0; i < (strlen((char*)text) * 8); ++i) printf("%d", binArr[i]);
    //printf("\n");
    
    // разшифровываем
    bool debinArr[(strlen((char*)text) * 8)+1];
    debinArr[strlen((char*)text) * 8] = '\0';
    
    
    bool fbin[4+1];
    fbin[4] = '\0';
    for (int i = 0; i < strlen((char*)text) * 8; i+=8) {
        fbin[0] = binArr[i+1];
        fbin[1] = binArr[i+0];
        fbin[2] = binArr[i+3];
        fbin[3] = binArr[i+2];
        debinArr[i+0] = fbin[0];
        debinArr[i+1] = fbin[1];
        debinArr[i+2] = fbin[2];
        debinArr[i+3] = fbin[3];
        
        if (binArr[i+0] == binArr[i+4]) debinArr[i+4] = 0;
        else debinArr[i+4] = 1;
        if (binArr[i+1] == binArr[i+5]) debinArr[i+5] = 0;
        else debinArr[i+5] = 1;
        if (binArr[i+2] == binArr[i+6]) debinArr[i+6] = 0;
        else debinArr[i+6] = 1;
        if (binArr[i+3] == binArr[i+7]) debinArr[i+7] = 0;
        else debinArr[i+7] = 1;
       
    }
    
    //printf("boy next dor\n");
    //for (int i = 0; i < (strlen((char*)text) * 8); ++i) printf("%d", debinArr[i]);
    //printf("\n");
    //printf("boy next dor\n");
    
    char* result = checkNul(calloc(strlen((char*)text) + 1, sizeof(char)));
    bool tochar[9];
    tochar[8] = '\0';
    num = 0;
    for (int i = 0; i < strlen((char*)text) * 8; i+=8){
        tochar[0] = debinArr[i+0];
        tochar[1] = debinArr[i+1];
        tochar[2] = debinArr[i+2];
        tochar[3] = debinArr[i+3];
        tochar[4] = debinArr[i+4];
        tochar[5] = debinArr[i+5];
        tochar[6] = debinArr[i+6];
        tochar[7] = debinArr[i+7];
        
        result[num] = decode_byte(tochar);
        ++num;
    }
    result[strlen((char*)text)] = '\0';
    
    return result;
}
void encode_char2(const int character, bool bits[8]) {
    for (int q = 0; q < 8; q++) {
        bits[q] = 0;
    }
    // 10 to 2
    int num = character;
    //printf("[%c] = %d\n", character, character);
    int n = 0, k = 0, ii, len = 0;
    for (ii = 0; n <= num; ii++) {
        n = pow(2, ii);
        if (n <= num) {
            k = n;
            len = ii;
            //printf("k: %d\n", k);
        }
    }
    
    len++;
    //printf("len: %d\n", len);
    int j = 0;
    if (len == 7) {
        j = 1;
        len++;
        bits[0] = 0;
    }
    else if (len == 6){
        j = 2;
        len += 2;
        bits[0] = 0;
        bits[1] = 0;
    }
    else if (len == 5){
        j = 3;
        len += 3;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
    }
    else if (len == 4){
        j = 4;
        len += 4;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
    }
    else if (len == 3){
        j = 5;
        len += 5;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
    }
    else if (len == 2){
        j = 6;
        len += 6;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
    }
    else if (len == 1){
        j = 8;
        len += 7;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
        bits[7] = 0;
    }
    //printf("len: %d\n", len);
    for (int i = j; i < len; i++) {
        if (k <= num) {
            //printf("k: %d {num: %d}\n", k, num);
            bits[i] = 1;
            //printf("i = %d\n", i);
            num = num - k;
            k /= 2;
            //printf("k: %d {num: %d}\n", k, num);
            //printf("...........\n");
        }
        else{
            bits[i] = 0;
            k /= 2;
        }
    }
    
    //printf("n: %d {len: %d}\n", k, len);
    return;
}


void encode_char(const char character, bool bits[8]) {
    for (int q = 0; q < 8; q++) {
        bits[q] = 0;
    }
    // 10 to 2
    int num = character;
    //printf("[%c] = %d\n", character, character);
    int n = 0, k = 0, ii, len = 0;
    for (ii = 0; n <= num; ii++) {
        n = pow(2, ii);
        if (n <= num) {
            k = n;
            len = ii;
            //printf("k: %d\n", k);
        }
    }
    
    len++;
    //printf("len: %d\n", len);
    int j = 0;
    if (len == 7) {
        j = 1;
        len++;
        bits[0] = 0;
    }
    else if (len == 6){
        j = 2;
        len += 2;
        bits[0] = 0;
        bits[1] = 0;
    }
    else if (len == 5){
        j = 3;
        len += 3;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
    }
    else if (len == 4){
        j = 4;
        len += 4;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
    }
    else if (len == 3){
        j = 5;
        len += 5;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
    }
    else if (len == 2){
        j = 6;
        len += 6;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
    }
    else if (len == 1){
        j = 8;
        len += 7;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
        bits[7] = 0;
    }
    //printf("len: %d\n", len);
    for (int i = j; i < len; i++) {
        if (k <= num) {
            //printf("k: %d {num: %d}\n", k, num);
            bits[i] = 1;
            //printf("i = %d\n", i);
            num = num - k;
            k /= 2;
            //printf("k: %d {num: %d}\n", k, num);
            //printf("...........\n");
        }
        else{
            bits[i] = 0;
            k /= 2;
        }
    }
    
    //printf("n: %d {len: %d}\n", k, len);
    return;
}

char decode_byte(const bool bits[8]){
    // 2 to 10
    short num = 0, st = 0, i = 7;
    
    while (i >= 0) {
        if (bits[i] == 1) {
            num += pow(2, st);
            //printf("%d\n", num);
        }
        i--;
        st++;
    }
    return num;
}








