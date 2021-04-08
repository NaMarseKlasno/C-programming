#include "hof.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
int str_to_num(char *str)
{
    int result = 0, same = 1;

    while (('-' == (*str)) || ((*str) == '+')) {
        if (*str == '-') same *= -1;
        str++;
    } while ((*str >= '0') && (*str <= '9')) {
        result = (result * 10) + ((*str) - '0');
        str++;
    }
    return (result * same);
}
*/
void bubbleSort (struct player qwerty[], int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (qwerty[j].score < qwerty[j+1].score) {
                int tmp = qwerty[j].score;

                qwerty[j].score = qwerty[j+1].score;
                qwerty[j+1].score = tmp;

                char tmp2[31] = {};
                for (int k = 0; k < strlen(qwerty[j].name)+1; ++k) tmp2[k] = qwerty[j].name[k];

                strcpy(qwerty[j].name, qwerty[j+1].name);
                for (int k = 0; k < strlen(tmp2)+1; ++k) qwerty[j+1].name[k] = tmp2[k];
            }
        }

    }
}


int load (struct player list[])
{
    FILE *file;
    if ((file = fopen("score", "r")) == NULL) return -1;


    char a[100000] = {};
    char value[3000] = {};
    int n = 0;
    bool check = true;

    struct player *lines = calloc(100000, sizeof(struct player));

    for (int i = 0; (fgets(a, 100000, file) != NULL); ++i) {
        char str[30] = {};

        for (int j = 0, q = 0; a[j] != '\0'; j++) {
            if (a[j] != ' ' && check == true) str[j] = a[j];
            else {
                check = false;
                if (a[j] != ' ') {
                    value[q] = a[j];
                    q++;
                }
            }
        } check = true;


        for (int j = 0; str[j] != '\0'; ++j) lines[i].name[j] = str[j];
        int num = 0;
        if (isdigit(value[0])) num = atoi(value);
        //else printf("INPUT ERROR\n");
        lines[i].score = num;
        n++;
    }
    //for (int i = 0; i < n; ++i) printf("%s %d\n", lines[i].name, lines[i].score);

    bubbleSort(lines, n);

    for (int i = 0; i < 10; ++i) {
        //list[i].name = lines[i].name;
        strcpy(list[i].name, lines[i].name);
        list[i].score = lines[i].score;
    }

    free(lines);
    fclose(file);
    return n;
}


bool save(const struct player list[], const int size)
{
    struct player *lines = calloc((unsigned long)size, sizeof(struct player));
    for (int i = 0; i < size+1; ++i) {
        strcpy(lines[i].name, list[i].name);
        lines[i].score = list[i].score;
    } bubbleSort(lines, size);

    //for (int i = 0; i < size; ++i) printf("%s %d\n", lines[i].name, lines[i].score);

    FILE *file;
    if ((file = fopen("score", "w")) == NULL) {
        free(lines);
        return 0;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; lines[i].name[j] != '\0'; ++j) {
            fputc(lines[i].name[j], file);
        } fputc(' ', file);
        fprintf(file, "%d", lines[i].score);
        //if (i != size-1)
        fputc('\n', file);
    }

    free(lines);
    fclose(file);
    return 1;
}



bool add_player(struct player list[], int* size, const struct player player) {

    int my_size = 0;
    for (int i = 0; list[i].score != '\0'; ++i) my_size++;

    struct player *lines = calloc((unsigned long)my_size+1, sizeof(struct player));
    for (int i = 0; i < my_size; ++i) {
        strcpy(lines[i].name, list[i].name);
        lines[i].score = list[i].score;
    } my_size += 1;

    strcpy(lines[my_size-1].name, player.name);
    lines[my_size-1].score = player.score;
    bubbleSort(lines, my_size);
    for (int i = 0; i < my_size; ++i) if (lines[i].name != player.name && my_size != 1) {
        free(lines);
        return false;
    }

    //for (int i = 0; i < my_size+1; ++i) printf("%s %d\n", lines[i].name, lines[i].score);

    FILE *file;
    if ((file = fopen("score", "a")) == NULL) {
        free(lines);
        return 0;
    }

    for (int i = 0; i < my_size; ++i) {
        for (int j = 0; lines[i].name[j] != '\0'; ++j) {
            fputc(lines[i].name[j], file);
        } fputc(' ', file);
        fprintf(file, "%d", lines[i].score);
        //if (i != my_size-1)
        fputc('\n', file);
    }

    fclose(file);
    free(lines);
    return 1;
}

