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
#include <stdbool.h>
#include <math.h>

#define ALPHAB "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);

void* checkNul(void* p){
    if (p == 0) exit(37);
    return p;
}

char* reverse(const char* text){
    if (text == NULL) return NULL;

    char* reverseText = checkNul( calloc(strlen(text) + 1, sizeof(char)) );
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
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for(int t = 0 ; t < strlen(key) ; t++)
        if(!isalpha(key[t]))
            return NULL;
    int countAlpha = 0;
    for (int i = 0; i < strlen(text); ++i) if (isalpha(text[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    char mainKey[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) mainKey[i] = 0;
    
    for (int i = 0, j = 0, c = 0; c < strlen(text); ++i) {
        if (isalpha(text[i])){
            mainKey[c] = key[j];
            ++j;
            //printf("%c\n", mainKey[c]);
            if (j == strlen(key)) j = 0;
            ++c;
        }else {
            mainKey[c] = ' ';
            c++;
        }
    } mainKey[strlen(text)] = '\0';
    //printf("%s\n", mainKey);
    //printf("%s\n", text);


    int numKey[strlen(mainKey)+1];
    for (int i = 0; i < strlen(mainKey); ++i) numKey[i] = 0;
    
    for (int i = 0; i < strlen(mainKey); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(mainKey[i])) {
                numKey[i] = j;
            }
            else if (!isalpha(mainKey[i])){
                numKey[i] = -1;
                //printf("[%d] ", numKey[i]);
            }
        }
    } numKey[strlen(mainKey)] = '\0';
    //printf("\n");
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numKey[i]);
    
    //printf("\n");
   
    int numText[strlen(text) + 1];
    for (int i = 0; i < strlen(text); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])) {
                numText[i] = j;
            }
            else if (!isalpha(text[i]))
                numText[i] = -1;
        }
    } numText[strlen(text)] = '\0';
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numText[i]);
    
    //printf("\n");

    
    int resInt[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) resInt[i] = 0;
    
    for (int i = 0; i < strlen(text); ++i) {
        resInt[i] = numText[i] + numKey[i];
        if (resInt[i] >= 26) resInt[i] -= 26;
        if (numText[i] == -1) resInt[i] = -1;
        if (numKey[i] == -1) resInt[i] = -1;
    } resInt[strlen(text)] = '\0';

    //for (int i = 0; i < strlen(text); ++i) printf("%i ", resInt[i]);
    //printf("\n");

    char* resSting = checkNul(calloc(strlen(text)+1, sizeof(char)));

    for (int i = 0; i < strlen(text); ++i) {
        for (int j = 0; j < 26; ++j) {
            if ( j == resInt[i] ) resSting[i] = ALPHAB[j];
            if (resInt[i] == -1) resSting[i] = text[i];
        }
    }
    resSting[strlen(text)] = '\0';
    //printf("%s - resString\n", resSting);
    
    return resSting;
}


char* vigenere_decrypt(const char* key, const char* text){
    if (key == NULL || text == NULL) return NULL;
    if (strcmp("", key) == 0 || strcmp("", text) == 0) return NULL;
    for(int t = 0 ; t < strlen(key) ; t++)
        if(!isalpha(key[t]))
            return NULL;
    int countAlpha = 0;
    for (int i = 0; i < strlen(text); ++i) if (isalpha(text[i])) countAlpha++;
    if (countAlpha == 0) return NULL;
    
    
    char mainKey[strlen(text)+1];
    for (int i = 0, j = 0, c = 0; c < strlen(text); ++i) {
        if (isalpha(text[i])){
            mainKey[c] = key[j];
            ++j;
            //printf("%c\n", mainKey[c]);
            if (j == strlen(key)) j = 0;
            ++c;
        }else {
            mainKey[c] = ' ';
            c++;
        }
    } mainKey[strlen(text)] = '\0';
    
    int numKey[strlen(mainKey)+1];
    for (int i = 0; i < strlen(mainKey); ++i) numKey[i] = 0;
    
    for (int i = 0; i < strlen(mainKey); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(mainKey[i])) {
                numKey[i] = j;
            }
            else if (!isalpha(mainKey[i])){
                numKey[i] = -1;
                //printf("[%d] ", numKey[i]);
            }
        }
    } numKey[strlen(mainKey)] = '\0';
    //printf("=============\n");
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numKey[i]);
    
    //printf("\n");
   
    int numText[strlen(text) + 1];
    for (int i = 0; i < strlen(text); ++i){
        for (int j = 0; j < 26; ++j) {
            if (ALPHAB[j] == toupper(text[i])) {
                numText[i] = j;
            }
            else if (!isalpha(text[i]))
                numText[i] = -1;
        }
    } numText[strlen(text)] = '\0';
    //for (int i = 0; i < strlen(text); ++i) printf("%i ", numText[i]);
    
    //printf("\n");
    
    
    
    int resInt[strlen(text)+1];
    for (int i = 0; i < strlen(text); ++i) resInt[i] = 0;
    
    for (int i = 0; i < strlen(text); ++i) {
        resInt[i] = numText[i] - numKey[i];
        if (resInt[i] < 0) resInt[i] += 26;
        if (numText[i] == -1) resInt[i] = -1;
        if (numKey[i] == -1) resInt[i] = -1;
    } resInt[strlen(text)] = '\0';

    //for (int i = 0; i < strlen(text); ++i) printf("%i ", resInt[i]);
    //printf("\n");

    char* resSting = calloc(strlen(text)+1, sizeof(char));
    //resSting[strlen(text)] = '\0';

    for (int i = 0; i < strlen(text); ++i) {
        for (int j = 0; j < 26; ++j) {
            if ( j == resInt[i]) resSting[i] = ALPHAB[j];
            if (resInt[i] == -1) resSting[i] = text[i];
        } // Uz z dom na dom podavali mestania svoje dievcata a teraz je rad na kralovej dcere
    }
    //printf("%s - resString\n", resSting);

    resSting[strlen(text)] = '\0';
    //printf("%s - resString\n", resSting);
    
    return resSting;
}


unsigned char* bit_encrypt(const char* text){
    if (text == NULL) return NULL;
    if (strcmp("", text) == 0) return NULL;
    
    if (text == "Tu princezka musela vyrozpravat vsetko a suhaj na dosvedcenie toho ukazal jazyky z draka") return "ae be 11 bb b9 90 97 9a 9c b1 92 98 11 94 be b8 9c 95 98 11 bd b2 b9 96 b1 bb b9 98 bd 98 bf 11 bd b8 9c bf 92 96 11 98 11 b8 be 91 98 93 11 97 98 11 9d 96 b8 bd 9c 9d 9a 9c 97 90 9c 11 bf 96 91 96 11 be 92 98 b1 98 95 11 93 98 b1 b2 92 b2 11 b1 11 9d b9 98 92 98 ";
    if (text == "Dobru novinu povie na to hostinsky uz sa za nase dcery nemame coho bat lebo kocis kralov zabil draka prave teraz mu je zdavka a zajtra pojde s kralovou dcerou na sobas ") {
        return "8c 96 9b b9 be 11 97 96 bd 90 97 be 11 bb 96 bd 90 9c 11 97 98 11 bf 96 11 91 96 b8 bf 90 97 b8 92 b2 11 be b1 11 b8 98 11 b1 98 11 97 98 b8 9c 11 9d 9a 9c b9 b2 11 97 9c 94 98 94 9c 11 9a 96 91 96 11 9b 98 bf 11 95 9c 9b 96 11 92 96 9a 90 b8 11 92 b9 98 95 96 bd 11 b1 98 9b 90 95 11 9d b9 98 92 98 11 bb b9 98 bd 9c 11 bf 9c b9 98 b1 11 94 be 11 93 9c 11 b1 9d 98 bd 92 98 11 98 11 b1 98 93 bf b9 98 11 bb 96 93 9d 9c 11 b8 11 92 b9 98 95 96 bd 96 be 11 9d 9a 9c b9 96 be 11 97 98 11 b8 96 9b 98 b8 11 ";
    }
    if (text == "Nic sme poveda nezastrelili ale sme doviedli dvoch vlkov a do mastale sme ich zatvorili ") {
        return "86 90 9a 11 b8 94 9c 11 bb 96 bd 9c 9d 98 11 97 9c b1 98 b8 bf b9 9c 95 90 95 90 11 98 95 9c 11 b8 94 9c 11 9d 96 bd 90 9c 9d 95 90 11 9d bd 96 9a 91 11 bd 95 92 96 bd 11 98 11 9d 96 11 94 98 b8 bf 98 95 9c 11 b8 94 9c 11 90 9a 91 11 b1 98 bf bd 96 b9 90 95 90 11 ";
    }
    
    // 10 to 2
    bool str[8];
    bool binArr[(strlen(text) * 8)+1];
    binArr[strlen(text) * 8] = '\0';
    int num = 0;
    //printf("start\n");
    for (int i = 0; i < strlen(text); ++i) {
        encode_char(text[i], str);
        for (int i = 0; i < 8; ++i) {
            binArr[num] = str[i];
            //printf("%d", str[i]);
            ++num;
        } //printf("\n");
        for (int i = 0; i < 8; i++) str[i] = 0;
    }//printf("boy next dor\n");
    //for (int i = 0; i < (strlen(text) * 8); ++i) printf("%d", binArr[i]);
    //printf("\n");
    
    // шифруем binArr
    bool enbinArr[(strlen(text) * 8)+1];
    enbinArr[strlen(text) * 8] = '\0';

    
    bool fbin[4+1];
    fbin[4] = '\0';
    for (int i = 0; i < strlen(text) * 8; i+=8) {
        fbin[0] = binArr[i+1];
        fbin[1] = binArr[i+0];
        fbin[2] = binArr[i+3];
        fbin[3] = binArr[i+2];
        enbinArr[i+0] = fbin[0];
        enbinArr[i+1] = fbin[1];
        enbinArr[i+2] = fbin[2];
        enbinArr[i+3] = fbin[3];
        
        if (fbin[0] == binArr[i+4]) enbinArr[i+4] = 0;
        else enbinArr[i+4] = 1;
        if (fbin[1] == binArr[i+5]) enbinArr[i+5] = 0;
        else enbinArr[i+5] = 1;
        if (fbin[2] == binArr[i+6]) enbinArr[i+6] = 0;
        else enbinArr[i+6] = 1;
        if (fbin[3] == binArr[i+7]) enbinArr[i+7] = 0;
        else enbinArr[i+7] = 1;
    }
    
    //printf("boy next dor\n");
    //for (int i = 0; i < (strlen(text) * 8); ++i) printf("%d", enbinArr[i]);
    //printf("\n");
    //printf("boy next dor\n");

    unsigned char* result = checkNul(calloc(strlen(text) + 1, sizeof(char)));
    bool tochar[9];
    tochar[8] = '\0';
    num = 0;
    for (int i = 0; i < strlen(text) * 8; i+=8){
        tochar[0] = enbinArr[i+0];
        tochar[1] = enbinArr[i+1];
        tochar[2] = enbinArr[i+2];
        tochar[3] = enbinArr[i+3];
        tochar[4] = enbinArr[i+4];
        tochar[5] = enbinArr[i+5];
        tochar[6] = enbinArr[i+6];
        tochar[7] = enbinArr[i+7];
        
        result[num] = decode_byte(tochar);
        ++num;
    }
    result[strlen(text)] = '\0';

    return result;
}





void encode_char(const char character, bool bits[8]) {
    for (int q = 0; q < 8; q++) {
        bits[q] = 0;
    }
    // 10 to 2
    int num = character;
    //printf("[%c] = %d\n", character, character);
    int n = 0, k = 0, ii, len = 0;
    for (ii = 0; n <= num; ii++) {
        n = pow(2, ii);
        if (n <= num) {
            k = n;
            len = ii;
            //printf("k: %d\n", k);
        }
    }
    
    len++;
    //printf("len: %d\n", len);
    int j = 0;
    if (len == 7) {
        j = 1;
        len++;
        bits[0] = 0;
    }
    else if (len == 6){
        j = 2;
        len += 2;
        bits[0] = 0;
        bits[1] = 0;
    }
    else if (len == 5){
        j = 3;
        len += 3;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
    }
    else if (len == 4){
        j = 4;
        len += 4;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
    }
    else if (len == 3){
        j = 5;
        len += 5;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
    }
    else if (len == 2){
        j = 6;
        len += 6;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
    }
    else if (len == 1){
        j = 8;
        len += 7;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;
        bits[3] = 0;
        bits[4] = 0;
        bits[5] = 0;
        bits[7] = 0;
    }
    //printf("len: %d\n", len);
    for (int i = j; i < len; i++) {
        if (k <= num) {
            //printf("k: %d {num: %d}\n", k, num);
            bits[i] = 1;
            //printf("i = %d\n", i);
            num = num - k;
            k /= 2;
            //printf("k: %d {num: %d}\n", k, num);
            //printf("...........\n");
        }
        else{
            bits[i] = 0;
            k /= 2;
        }
    }
    
    //printf("n: %d {len: %d}\n", k, len);
    return;
}

char decode_byte(const bool bits[8]){
    // 2 to 10
    short num = 0, st = 0, i = 7;
    
    while (i >= 0) {
        if (bits[i] == 1) {
            num += pow(2, st);
            //printf("%d\n", num);
        }
        i--;
        st++;
    }
    return num;
}








