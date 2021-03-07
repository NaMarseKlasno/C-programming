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
    if (strlen(text) == 0 || text == NULL) return NULL;
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
    if (strlen(key) == 0 || key == NULL) return NULL;
    if (strlen(text) == 0 || text == NULL) return NULL;
    
    int n = 0;
    int* numKey = (int*)calloc(strlen(key), sizeof(int));
    for (int i = 0; i < 26; ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(key[i])){
                numKey[n] = j;
                //printf("%d ", numText[n]);
                ++n;
            }
        }
    } numKey[strlen(key)] = '\0';
  
    //for (int i = 0; i < strlen(key); ++i) /printf("%i ", numKey[i]);
    //printf("\n");

    int m = 0;
    int* numText = (int*)calloc(strlen(text), sizeof(int));
    for (int i = 0; i < 26; ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])){
                numText[m] = j;
                //printf("%d ", numText[n]);
                ++m;
            }
        }
    } numText[strlen(text)] = '\0';
  
    //for (int i = 0; i < strlen(text); ++i) printf("%d ", numText[i]);
    //printf("\n");
    
    free(numKey);
    free(numText);
    return NULL;
}
