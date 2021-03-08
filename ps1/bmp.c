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

#define ALPHAB "ABCDEFGHIJKLMNOPQRSTUVWXYZ"



char* reverse(const char* text){
    if (text[0] == '\0'  || text == NULL) return NULL;
    
    int countAlpha = 0;
    for (int i = 0; i < strlen(text); ++i) if (isalpha(text[i])) countAlpha++;
    if (countAlpha == 0) return NULL;


    char* reverseText = calloc(strlen(text) + 1, sizeof(char));
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
    if (key[0] == '\0' || key == NULL) return NULL;
    if (text[0] == '\0'  || text == NULL) return NULL;
    
    char mainKey[strlen(text)];
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
    }
    //printf("%s\n", mainKey);
    //printf("%s\n", text);


    int numKey[strlen(mainKey)];
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
    }
    //printf("\n");
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numKey[i]);
    
    //printf("\n");
   
    int numText[strlen(text)];
    for (int i = 0; i < strlen(text); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])) {
                numText[i] = j;
            }
            else if (!isalpha(text[i]))
                numText[i] = -1;
        }
    }
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numText[i]);
    
    //printf("\n");

    
    int resInt[strlen(text)];
    for (int i = 0; i < strlen(text); ++i) resInt[i] = 0;
    
    for (int i = 0; i < strlen(text); ++i) {
        resInt[i] = numText[i] + numKey[i];
        if (resInt[i] >= 26) resInt[i] -= 26;
        if (numText[i] == -1) resInt[i] = -1;
        if (numKey[i] == -1) resInt[i] = -1;
    }
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", resInt[i]);
    //printf("\n");

    char* resSting = checkNull(calloc(strlen(text), sizeof(char)));

    for (int i = 0; i < strlen(text); ++i) {
        for (int j = 0; j < 26; ++j) {
            if ( j == resInt[i] ) resSting[i] = ALPHAB[j];
            if (resInt[i] == -1) resSting[i] = text[i];
        }
    }
    
    //printf("%s - resString\n", resSting);
    
    return resSting;
}
// "JSXAI PSINR!"











