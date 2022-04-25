#include "playfair.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>


int countSymbols (const char *string, char Sym) {
    int res = 0;
    for (int i = 0; string[i] != '\0'; ++i) if (toupper(string[i]) == toupper(Sym)) ++res;
    return res;
}


char* playfair_encrypt(const char* key, const char* text)
{
    // ***** check NULL
    if (text == NULL || key == NULL) return NULL;
    if (strcmp("", text) == 0 || strcmp("", key) == 0) return NULL;
    for (int i = 0; i < 2; ++i) if (key[i] == ' ' && key[++i] == '\0') return NULL;
    for (int i = 0; key[i] != '\0'; ++i) if (key[i] != ' ' && !isalpha(key[i])) return NULL;


    struct Position {
        int x1, y1;
        int x2, y2;
    } position;

    struct Playfair {
        int key_len;
        int text_len;

        struct Position res;
        char *encryptedText;
        char *decryptedText;

        char *text;
        char *key;
        char table[5][5];

    };


    int isDuplicate(char ch, int index1, int index2, struct Playfair *playfair ) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (playfair->table[i][j] == toupper(ch) && i<=index1) {
                    if ((j<index2) || (j >= index2 && i < index1)) return 1;
                }
            }
        } return 0;
    }

    struct Playfair playfair;


    // ***** set len
    playfair.key_len = strlen(key) - countSymbols(key,' ');
    playfair.text_len = strlen(text);

    playfair.key = (char *)calloc(playfair.key_len+1, sizeof(char));
    if (playfair.key == NULL) {
        perror("memory failed");
        exit(1);
    }

    for (int i=0, j=0; i < strlen(key); ++i) {
        if (key[i] != ' ') {
            toupper(key[i]) == 'W' ? (playfair.key[j] = 'V') : (playfair.key[j] = toupper(key[i]));
            ++j;
        }
    } playfair.key[playfair.key_len] = '\0';


    // ***** init table
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; (playfair.table[i][j] = '0'), ++j); //playfair.TABLE[i][j] = ALPHA[k];

    for (int i = 0, k = 0, m = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j, ++k)
        {
            if (k < playfair.key_len) {
                while (isDuplicate(playfair.key[k], i, j, &playfair)) ++k;

                if (k >= playfair.key_len) {
                    if (j==0) {--i; j=4;}
                    else --j;
                    continue;
                } playfair.table[i][j] = playfair.key[k];
            } else {
                while (isDuplicate(ALPHA[m], i, j, &playfair)) ++m;
                playfair.table[i][j] = ALPHA[m];
                ++m;
            }
        }
    }


    // ***** подготовка текста к шифровке
    for (int i = 0; i < strlen(text); ++i) if (text[i] == ' ') -- playfair.text_len;
    char *textTest = (char *) calloc(playfair.text_len+1, sizeof(char));
    int textTest_len = 0;
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] != ' ') {
            textTest[textTest_len] = text[i];
            ++textTest_len;
        }
    } textTest[textTest_len] = '\0';

    char *alterText = (char *)calloc(playfair.text_len*3, sizeof(char));
    if (alterText == NULL) return NULL;

    int last_j = 0, status = 0;

    for (int i = 0; textTest[i] != '\0'; ++i, ++last_j)
    {
        alterText[last_j] = ((toupper(textTest[i]) == 'W') ? ('V') : (toupper(textTest[i])));
        if (textTest[i+1] != '\0') {
            if (status == 0 && textTest[i] == textTest[i+1] && i%2==0 && toupper(textTest[i]) != 'X' && toupper(textTest[i+1]) != 'X') {
//                printf("---------  %c %c\n", textTest[i],textTest[i+1]);
                alterText[++last_j] = 'X';
                status = 1;
            }
            if (status == 1 && textTest[i] == textTest[i+1] && i%2!=0 && toupper(textTest[i]) != 'X' && toupper(textTest[i+1]) != 'X') {
//                printf("---------  %c %c\n", textTest[i],textTest[i+1]);
                alterText[++last_j] = 'X';
                status = 0;
            }
        }
    } if (last_j%2!=0) alterText[last_j++] = 'X';

    playfair.text = (char *)calloc(last_j+1, sizeof(char));
    for (int i = 0; i < last_j; playfair.text[i] = alterText[i], ++i);
    playfair.text[last_j] = '\0';
    playfair.text_len = last_j;

    printf("len:%d-------------\n", playfair.text_len);


    // ***** шифровка
    playfair.encryptedText = (char *)calloc((playfair.text_len+((playfair.text_len/2)-1)+1), sizeof(char));

    for (int len = 0, ix = 0; len < playfair.text_len; len+=2, ix+=3)
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (playfair.table[i][j] == playfair.text[len]) {
                    position.x1 = i;
                    position.y1 = j;
                } if (playfair.table[i][j] == playfair.text[len+1]) {
                    position.x2 = i;
                    position.y2 = j;
                }
            }
        }


        if ((position.y1 < position.y2 && position.x1!=position.x2) || (position.y1 > position.y2 && position.x1!=position.x2)) {
            playfair.res.y1 = position.y2;
            playfair.res.x1 = position.x1;

            playfair.res.y2 = position.y1;
            playfair.res.x2 = position.x2;
        }
        else if (position.y1 == position.y2) {
            if (position.x1+1<=4) playfair.res.x1 = position.x1+1;
            else playfair.res.x1 = 0;
            if (position.x2+1<=4) playfair.res.x2 = position.x2+1;
            else playfair.res.x2 = 0;

            playfair.res.y1 = position.y1;
            playfair.res.y2 = position.y2;
        }
        else if (position.x1 == position.x2) {
            if (position.y1+1<=4) playfair.res.y1 = position.y1+1;
            else playfair.res.y1 = 0;
            if (position.y2+1<=4) playfair.res.y2 = position.y2+1;
            else playfair.res.y2 = 0;
            playfair.res.x1 = position.x1;
            playfair.res.x2 = position.x2;
        }


        playfair.encryptedText[ix] = playfair.table[playfair.res.x1][playfair.res.y1];
        playfair.encryptedText[ix+1] = playfair.table[playfair.res.x2][playfair.res.y2];

        if (ix+2 == (playfair.text_len+((playfair.text_len/2)-1))) playfair.encryptedText[ix+2] = '\0';
        else playfair.encryptedText[ix+2] = ' ';
    }


    // ***** free memory
    free(playfair.text);
    playfair.text = NULL;
    free(alterText);
    alterText = NULL;

    free(textTest);
    textTest = NULL;
    free(playfair.key);
    playfair.key = NULL;


    return playfair.encryptedText;
}


char* playfair_decrypt(const char* key, const char* text)
{
    // ***** check NULL
    if (text == NULL || key == NULL) return NULL;
    if (strcmp("", text) == 0 || strcmp("", key) == 0 || countSymbols(text,'W')>=1) return NULL;
    for (int i = 0; i < 2; ++i) if (key[i] == ' ' && key[++i] == '\0') return NULL;
    for (int i = 0; key[i] != '\0'; ++i) if (key[i] != ' ' && !isalpha(key[i])) return NULL;
    int cA=0, cS=0;
    for (int i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) ++cA;
        if (text[i] == ' ') ++cS;
    } if ((cA % 2 != 0) || (strlen(text) != cA+cS)) return NULL;

    struct Position {
        int x1, y1;
        int x2, y2;
    } position;

    struct Playfair {
        int key_len;
        int text_len;

        struct Position res;
        char *encryptedText;
        char *decryptedText;

        char *text;
        char *key;
        char table[5][5];

    };

    struct Playfair playfair;

    int isDuplicate(char ch, int index1, int index2, struct Playfair *playfair ) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (playfair->table[i][j] == toupper(ch) && i<=index1) {
                    if ((j<index2) || (j >= index2 && i < index1)) return 1;
                }
            }
        } return 0;
    }


    // ***** set len
    playfair.key_len = strlen(key) - countSymbols(key,' ');
    playfair.text_len = strlen(text);

    playfair.key = (char *)calloc(playfair.key_len+1, sizeof(char));
    if (playfair.key == NULL) {
        perror("memory failed");
        exit(1);
    }

    for (int i=0, j=0; i < strlen(key); ++i) {
        if (key[i] != ' ') {
            toupper(key[i]) == 'W' ? (playfair.key[j] = 'V') : (playfair.key[j] = toupper(key[i]));
            ++j;
        }
    } playfair.key[playfair.key_len] = '\0';


    // ***** init table
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; (playfair.table[i][j] = '0'), ++j); //playfair.TABLE[i][j] = ALPHA[k];

    for (int i = 0, k = 0, m = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j, ++k)
        {
            if (k < playfair.key_len) {
                while (isDuplicate(playfair.key[k], i, j, &playfair)) ++k;

                if (k >= playfair.key_len) {
                    if (j==0) {--i; j=4;}
                    else --j;
                    continue;
                } playfair.table[i][j] = playfair.key[k];
            } else {
                while (isDuplicate(ALPHA[m], i, j, &playfair)) ++m;
                playfair.table[i][j] = ALPHA[m];
                ++m;
            }
        }
    }


    // ***** дешифровка
    playfair.decryptedText = (char *)calloc(playfair.text_len+1, sizeof(char));

    for (int len = 0, ix = 0; len < playfair.text_len; len+=3, ix+=2)
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (playfair.table[i][j] == text[len]) {
                    position.x1 = i;
                    position.y1 = j;
                } if (playfair.table[i][j] == text[len+1]) {
                    position.x2 = i;
                    position.y2 = j;
                }
            }
        }


        if ((position.y1 < position.y2 && position.x1!=position.x2) || (position.y1 > position.y2 && position.x1!=position.x2)) {
            playfair.res.y1 = position.y2;
            playfair.res.x1 = position.x1;

            playfair.res.y2 = position.y1;
            playfair.res.x2 = position.x2;
        }
        else if (position.y1 == position.y2) {
            if (position.x1-1>=0) playfair.res.x1 = position.x1-1;
            else playfair.res.x1 = 4;
            if (position.x2-1>=0) playfair.res.x2 = position.x2-1;
            else playfair.res.x2 = 4;

            playfair.res.y1 = position.y1;
            playfair.res.y2 = position.y2;
        } // MQ XQ IV MZ BA ME
        else if (position.x1 == position.x2) {
            if (position.y1-1>=0) playfair.res.y1 = position.y1-1;
            else playfair.res.y1 = 4;
            if (position.y2-1>=0) playfair.res.y2 = position.y2-1;
            else playfair.res.y2 = 4;

            playfair.res.x1 = position.x1;
            playfair.res.x2 = position.x2;
        }

        playfair.decryptedText[ix] = playfair.table[playfair.res.x1][playfair.res.y1];
        playfair.decryptedText[ix+1] = playfair.table[playfair.res.x2][playfair.res.y2];

        if (ix+2 == playfair.text_len) playfair.decryptedText[ix+2] = '\0';
    }

    // ***** free memory
    if (playfair.key!=NULL)free(playfair.key);
    playfair.key = NULL;

    return playfair.decryptedText;
}
