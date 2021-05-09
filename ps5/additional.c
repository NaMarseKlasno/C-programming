#include "additional.h"


void destroy_next_conts (struct container* next) {
    if (next == NULL) return;
    if (next->next != NULL) destroy_next_conts(next->next);

    if (next->type == ROOM) destroy_room(next->room);
    else if (next->type == ITEM) destroy_item(next->item);
    else if (next->type == COMMAND) destroy_command(next->command);
    else if (next->type == TEXT) free(next->text);

    free(next);
    //next = NULL;
}

int check_symbol (char c) { // pomocka -> https://www.cyberforum.ru/c-beginners/thread2191515.html
    int answer = -1;
    if (c >= 'a' && c <= 'z') answer = 0;
    else if (c >= 'A' && c <= 'Z') answer = 1;
    return answer;
}

int check_string (char *str_one, char *str_two) {
    if (strlen(str_one) != strlen(str_two)) return 1;
    char tmp; int eq = 1;

    for (int i=0, c1, c2, swp = 'a' - 'A'; str_one[i] != '\0' && eq > 0; i++)
    {
        tmp = str_two[i];
        c1 = check_symbol(str_one[i]);
        c2 = check_symbol(str_two[i]);
        if (c1 < c2)    tmp += swp;
        if (c1 > c2)    tmp -= swp;
        if (str_one[i] != tmp) eq = 0;
    }

    if (eq > 0) return 0;
    return 1;
}