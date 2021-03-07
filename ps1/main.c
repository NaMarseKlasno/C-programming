#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"
#include "bmp.h"

int main(void)
{
    char *encrypted, *decrypted;

    encrypted = playfair_encrypt("world", "Hello");
    printf("%s\n", encrypted);
    // "Hello" --> "HELXLO"
    // JB RY DR
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s\n", decrypted);
    // HELXLO
    free(encrypted);
    free(decrypted);
    
    
    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);
    // "!DLROW OLLEH"
    //free(reversed);
    return 0;
}
