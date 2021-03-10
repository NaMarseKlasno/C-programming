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
    printf("%s\n", encrypted);
    // "Taxxxiii" --> "TAXXXIIXIX"
    // RS EE VJ JV JV
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s\n", decrypted);
    // TAXXXIIXIX
    free(encrypted);
    free(decrypted);
    
    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);
    // "!DLROW OLLEH"

    char* encrypted2;

    // basic test with long text
    encrypted2 = vigenere_encrypt("", "Hello world!");
    printf("%s\n", encrypted2);
    // "JSXAI PSINR!"

    char *decrypted2;
    decrypted2 = vigenere_decrypt("", "Hhda");
    printf("%s\n", decrypted2);
    
    free(encrypted2);
    free(decrypted2);

    unsigned char* encryptedd;

    // basic test with long text
    encryptedd = bit_encrypt("Boy next dor!!");
    for(int i=0; encryptedd[i] != '\0'; i++) {
        printf("%x ", encryptedd[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    printf("\n");
    char* decryptedd;
    
    // basic test with long text
    decryptedd = bit_decrypt(encryptedd);
    printf("%s\n", decryptedd);
    //for(int i=0; i < 12;i++) {
    //    printf("%c", decrypted[i]);
    //    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    //}
    free(decryptedd);
    free(encryptedd);
    
    
    unsigned char* resin;
    
    resin = bmp_encrypt("key", "boy next dor!!!");
    for(int i = 0; resin[i] != '\0'; i++) {
        printf("%x ", resin[i]);
    } printf("\n");
    
    char* res1;
    res1 = bmp_decrypt("key", resin);
    printf("%s\n", res1);
    free(res1);
    free(resin);


    return 0;
}


