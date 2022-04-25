#include "playfair.h"
#include "bmp.h"
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


int main(void)
{
    // ===============================================================
    //                            PlayFair
    // ===============================================================

    char *encrypted, *decrypted;

    encrypted = playfair_encrypt("co c k c r   ows", "ducks");
    printf("%s\n", encrypted);

    char* text = "RM ID IC BT EC US VM HS AC HK NIWVG NF OT";
    char* key = "benumbed";

    decrypted = playfair_decrypt(key, text);
    printf("%s\n", decrypted);

    free(encrypted);
    free(decrypted);


//     ===============================================================
//                                 BMP
//     ===============================================================

    char* reversed = reverse("");
    printf("%s\n", reversed);
    free(reversed);

    char *encrypted2, *decrypted2;
    encrypted2 = vigenere_encrypt("CoMPuTeR", "Hello world!");
    printf("%s\n", encrypted2);
    decrypted2 = vigenere_decrypt("CoMPuTeR", encrypted2);
    printf("%s\n", decrypted2);
    free(encrypted2);
    free(decrypted2);

    unsigned char* encrypted3;

    char *decrypted3;
    // basic test with long text
    encrypted3 = bit_encrypt("Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted3[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    } printf("\n");

    decrypted3 = bit_decrypt(encrypted3);
    for(int i=0; i < 12;i++) {
        printf("%x ", decrypted3[i]);
        //80 9c 95 95 96 11 bc 96 b9 95 9d 10
    } printf("\n");
    free(encrypted3);
    free(decrypted3);


    unsigned char* bmp;

    bmp = bmp_encrypt("ComPuTer", "Hello WoRld!");
    for (int i = 0; i < 12; ++i) printf("%x ", bmp[i]);
    printf("\n");

    unsigned char* debmp;

    debmp = (unsigned char *)bmp_decrypt("ComPuTer", bmp);
    for (int i = 0; i < 12; ++i) printf("%c", debmp[i]);
    printf("\n");

    free(bmp);
    free(debmp);
}
