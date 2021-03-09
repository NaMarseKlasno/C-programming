#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"
#include "bmp.h"

int main(void)
{
    // "A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z"
    // "0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25"
    char *encrypted, *decrypted;

    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s", encrypted);
    // "Taxxxiii" --> "TAXXXIIXIX"
    // RS EE VJ JV JV
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s", decrypted);
    // TAXXXIIXIX
    free(encrypted);
    free(decrypted);
    
    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);
    // "!DLROW OLLEH"

    char* encrypted2;

    // basic test with long text
    encrypted2 = vigenere_encrypt("a", "Hello world!");
    printf("%s\n", encrypted2);
    // "JSXAI PSINR!"

    char *decrypted2;
    decrypted2 = vigenere_decrypt("Computer", "LALSDV");
    printf("%s\n", decrypted2);
    
    free(encrypted2);
    free(decrypted2);
    

    return 0;
}
