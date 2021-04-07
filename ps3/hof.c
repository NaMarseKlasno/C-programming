#include "hof.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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

int load (struct player list[])
{
    FILE *file;
    if ((file = fopen("score", "r")) == NULL) {
        printf("Ошибка чтения из файла\n");
        return 0;
    }

    char a[100000] = {};
    char str[100000] = {};
    int value[100000] = {};

    for (int i = 0; i < 10; ++i) {
        fgets(a, 10000, file);

        for (int i = 0, q = 0; a[i] != '\0'; i++) {
            if (!isnumber(a[i])) str[i] = a[i];
            else if (a[i] != ' ') {
                value[q] = str_to_num(&a[i]);
                q++;
            }
        }



        for (int j = 0; str[j] != '\0'; ++j)
            list[0].name[j] = str[j];


        int num = 0;
        isdigit(value[0]) ? (num = atoi((const char *) value)) : printf("INPUT ERROR\n");

        list[0].score = num;

    }

    fclose(file);

    return 0;
}

