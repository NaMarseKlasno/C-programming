#include <stdio.h>
#include "playfair.h"
#include <stdlib.h>

int main(void)
{
    char *encrypted, *decrypted;

    // even length of string
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s\n", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s", decrypted);
    // TAXIPLEASE
    free(encrypted);
    free(decrypted);
    return 0;
}
