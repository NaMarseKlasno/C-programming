#include <stdio.h>
#include "playfair.h"
#include <stdlib.h>

int main(void)
{
    char *encrypted;

    // even length of string
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s\n", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    
    free(encrypted);

    return 0;
}
