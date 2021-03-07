//
//  bmp.c
//  TopSelect
//
//  Created by Macbook Pro on 26.02.2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "playfair.h"




char* reverse(const char* text){
    if (text == NULL || text == 0) return NULL;
    char* reverseText = calloc(strlen(text) + 1, sizeof(char));
    for (int i = 0; i < strlen(text); i++) reverseText[i] = text[i];
    reverseText[strlen(text)] = '\0';
    
    
    unsigned long  i = 0, j = strlen(text) - 1;
    char c;
 
    for(; i < j; ++i, --j){
        c = text[i];
        reverseText[i] = reverseText[j];
        reverseText[j] = c;
    }
    return reverseText;
}
