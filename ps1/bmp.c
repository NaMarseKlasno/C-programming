#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHA "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


int findLetter(int ch);


char* reverse(const char* text)
{
    // ***** check NULL
    if (text == NULL) return NULL;

    char* res = (char *)calloc(strlen(text)+1, sizeof(char));
    for (int i = strlen(text)-1, j = 0; i >= -1; (i==-1) ? (res[strlen(text)] = '\0') : (res[j] = toupper(text[i])), --i, ++j);
    return res;
}


char* vigenere_encrypt(const char* key, const char* text)
{
    // ***** check NULL
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for (int i = 0; i < strlen(key) ; i++) if (!isalpha(key[i])) return NULL;


    // ***** init class
    struct BMP {
        int text_len;

        char *encryptedText;
        char *decryptedText;

        char *key;
    };

    struct BMP vigenere;

    vigenere.text_len = strlen(text);

    vigenere.key = (char *)calloc(vigenere.text_len+1, sizeof(char));
    if (vigenere.key == NULL) return NULL;

    vigenere.encryptedText = (char *)calloc(vigenere.text_len+1, sizeof(char));
    if (vigenere.encryptedText == NULL) {
        free(vigenere.key);
        return NULL;
    }


    for (int i = 0, j = 0; i < vigenere.text_len; ++i, ++j) {
        if (j==strlen(key)) j=0;

        if (text[i] == ' ') {
            vigenere.key[i] = ' ';
            --j;
        } else vigenere.key[i] = toupper(key[j]);
    }

//    for (int i = 0; i < vigenere.text_len; ++i) {
//        printf("%c", vigenere.key[i]);
//    } printf("\n");

    for (int i = 0; i < vigenere.text_len; ++i) {
        int x1 = findLetter(text[i]), x2 = findLetter(vigenere.key[i]);
        int res = x1+x2;

        while (res >= 26) res -= 26;

        if (isalpha(text[i])) vigenere.encryptedText[i] = ALPHA[res];
        else vigenere.encryptedText[i] = text[i];
    }

    // ***** free memory
    free(vigenere.key);

    return vigenere.encryptedText;
}

char* vigenere_decrypt(const char* key, const char* text)
{
    // ***** check NULL
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for (int i = 0; i < strlen(key) ; i++) if (!isalpha(key[i])) return NULL;

    // ***** init class
    struct BMP {
        int text_len;

        char *encryptedText;
        char *decryptedText;

        char *key;
    };

    struct BMP vigenere;

    vigenere.text_len = strlen(text);

    vigenere.key = (char *)calloc(vigenere.text_len+1, sizeof(char));
    if (vigenere.key == NULL) return NULL;

    vigenere.decryptedText = (char *)calloc(vigenere.text_len+1, sizeof(char));
    if (vigenere.decryptedText == NULL){
        free(vigenere.key);
        return NULL;
    }


    for (int i = 0, j = 0; i < vigenere.text_len; ++i, ++j) {
        if (j==strlen(key)) j=0;

        if (text[i] == ' ') {
            vigenere.key[i] = ' ';
            --j;
        } else vigenere.key[i] = toupper(key[j]);
    }

    for (int i = 0; i < vigenere.text_len; ++i) {
        int x1 = findLetter(text[i]), x2 = findLetter(vigenere.key[i]);
        int res = x1-x2;

        while (res < 0) res += 26;

        if (isalpha(text[i])) vigenere.decryptedText[i] = ALPHA[res];
        else vigenere.decryptedText[i] = text[i];
    }

    // ***** free memory
    free(vigenere.key);

    return vigenere.decryptedText;
}


unsigned char* bit_encrypt(const char* text)
{
    // ***** check NULL
    if ((text == NULL) || (strcmp("", text) == 0)) return NULL;

    // ***** init class
    struct BMP {
        int textLen;
        unsigned char* text;

        char bitsWord[9];
        char firstPair[5];
        char secondPair[5];
    };

    struct BMP bit;

    // ***** set len
    bit.textLen = 0;
    while (text[bit.textLen] != '\0') ++bit.textLen;


    bit.text = (unsigned char *)calloc(bit.textLen+1, sizeof(char));
    memcpy(bit.text, (unsigned char*)text, bit.textLen+1);

    bit.bitsWord[8] = '\0';
    struct BNP {
        int text_len;

        char *encryptedText;
        char *decryptedText;

        char *key;
    };

    for (int i=0; i<bit.textLen; (bit.text[i] = strtoul(bit.bitsWord,'\0',2)), ++i)
    {
        unsigned char ch = bit.text[i];

        for (int j=0; j<8; (bit.bitsWord[7-j] = (ch%2)+'0'), ch/=2, ++j);
        for (int j=4; j<8; (bit.secondPair[j-4] = bit.bitsWord[j]), ++j);

        for (int j=0; j<4; j+=2) {
            bit.firstPair[j] = bit.bitsWord[j+1];
            bit.firstPair[j+1] = bit.bitsWord[j];
        }

        for (int j=0; j<4; ++j)
        {
            if      (bit.firstPair[j] == bit.secondPair[j] && bit.firstPair[j] == '1')  bit.secondPair[j] = '0';
            else if (bit.firstPair[j] == bit.secondPair[j] && bit.firstPair[j] == '0')  bit.secondPair[j] = '0';
            else if (bit.firstPair[j] != bit.secondPair[j] && bit.firstPair[j] == '1')  bit.secondPair[j] = '1';
            else if (bit.firstPair[j] != bit.secondPair[j] && bit.firstPair[j] == '0')  bit.secondPair[j] = '1';
        }

        for (int j=0; j<8; ++j)
        {
            if ((j <= 3) && (bit.bitsWord[j] != -1))bit.bitsWord[j] = bit.firstPair[j];
            else if (j > 3) {
                if (bit.bitsWord[j] != 2) bit.bitsWord[j] = bit.secondPair[j-4];
                else bit.bitsWord[j] = bit.firstPair[j];
            }
        }
    }

    return bit.text;
}


char* bit_decrypt(const unsigned char* text)
{
    // ***** check NULL
    if ((text == NULL) || (strcmp("", (char *)text) == 0)) return NULL;

    // ***** init class
    struct BMP {
        int textLen;
        char* text;

        char bitsWord[9];
        char firstPair[5];
        char secondPair[5];
    };

    struct BMP bit;

    // ***** set len
    bit.textLen = 0;
    while (text[bit.textLen] != '\0') ++bit.textLen;

    bit.text = (char *)calloc(bit.textLen+1, sizeof(char));
    memcpy(bit.text, text, bit.textLen+1);

    struct BNP {
        int text_len;

        char *encryptedText;
        char *decryptedText;

        char *key;
    };

    bit.bitsWord[8] = '\0';
    for (int i = 0; i < bit.textLen; (bit.text[i] = strtoul(bit.bitsWord,'\0',2)), ++i)
    {
        unsigned char ch = bit.text[i];

        for (int j=0; j<8; (bit.bitsWord[7-j] = (ch % 2) + '0'), ch/=2, ++j);
        for (int j=4; j<8; (bit.secondPair[j-4] = bit.bitsWord[j]), ++j);
        for (int j=0; j<4; ++j) bit.firstPair[j] = bit.bitsWord[j];


        for (int j=0; j<4; ++j)
        {
            if      (bit.firstPair[j] == '0' && bit.firstPair[j] == bit.secondPair[j]) bit.secondPair[j] = '0';
            else if (bit.firstPair[j] == '0' && bit.firstPair[j] != bit.secondPair[j]) bit.secondPair[j] = '1';
            else if (bit.firstPair[j] == '1' && bit.firstPair[j] == bit.secondPair[j]) bit.secondPair[j] = '0';
            else if (bit.firstPair[j] == '1' && bit.firstPair[j] != bit.secondPair[j]) bit.secondPair[j] = '1';

        } for (int j=0; j<4; (bit.firstPair[j] = bit.bitsWord[j+1]), (bit.firstPair[j+1] = bit.bitsWord[j]), j+=2);

        for (int j=0; j<8; ++j)
        {
            if ((j <= 3) && (bit.bitsWord[j] != -1))
                bit.bitsWord[j] = bit.firstPair[j];
            else if (j > 3) {
                if (bit.bitsWord[j] != 2) bit.bitsWord[j] = bit.secondPair[j-4];
                else bit.bitsWord[j] = bit.firstPair[j];
            }
        }
    }

    return bit.text;
}


unsigned char* bmp_encrypt(const char* key, const char* text)
{
    // ***** check NULL
    if (key == NULL || text == NULL) return NULL;
    for (int i = 0; key[i] != '\0'; ++i) if (!isalpha(key[i])) return NULL;


    // ***** init class
    struct BMP {
        int lenText;

        char* reverse;
        char* vigenereEncrypt;
        unsigned char* bitEncrypt;

        unsigned char* res;
    };

    struct BMP bmp;


    // ***** set len
    bmp.lenText = strlen((char *)text);


    // BMP cipher
    bmp.reverse = reverse(text);
    bmp.vigenereEncrypt = vigenere_encrypt(key, bmp.reverse);
    bmp.bitEncrypt = bit_encrypt(bmp.vigenereEncrypt);

    bmp.res = (unsigned char *)calloc(bmp.lenText+1, sizeof(char));
    memcpy(bmp.res, bmp.bitEncrypt, strlen((char*)text));


    // ***** free memory
    free(bmp.bitEncrypt);
    free(bmp.reverse);
    free(bmp.vigenereEncrypt);

    return bmp.res;
}

char* bmp_decrypt(const char* key, const unsigned char* text)
{
    // ***** check NULL
    if (key == NULL || text == NULL) return NULL;
    for (int i = 0; key[i] != '\0'; ++i) if (!isalpha(key[i])) return NULL;


    // ***** init class
    struct BMP {
        int lenText;

        char* reverse;
        char* vigenereDecrypt;
        char* bitDecrypt;

        char* res;
    };

    struct BMP bmp;


    // ***** set len
    bmp.lenText = strlen((char *)text);


    // BMP cipher
    bmp.bitDecrypt = bit_decrypt(text);
    bmp.vigenereDecrypt = vigenere_decrypt(key, bmp.bitDecrypt);
    bmp.reverse = reverse(bmp.vigenereDecrypt);

    bmp.res = (char *)calloc(bmp.lenText+1, sizeof(char));
    strcpy(bmp.res, bmp.reverse);


    // ***** free memory
    free(bmp.bitDecrypt);
    free(bmp.reverse);
    free(bmp.vigenereDecrypt);

    return bmp.res;
}


int findLetter(int ch) {
    for (int i = 0; i < 26; ++i) if (ALPHA[i] == toupper(ch)) return i;
    return -1;
}
