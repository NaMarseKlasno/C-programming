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


