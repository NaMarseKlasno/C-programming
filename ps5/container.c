#include "container.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string.h>

void destroy_next_conts (struct container* next);
int check_string2 (char *str_one, char *str_two);
int check_symbol2 (char c);


struct container* create_container (struct container* first, enum container_type type, void* entry) {
    if (entry == NULL) return NULL;  //return remove_container(NULL, NULL);

    struct container* cont = calloc(1, sizeof(struct container));
    cont->type = type;
    cont->next = NULL;

    if (cont->type == ROOM) cont->room = entry;
    else if (cont->type == ITEM) cont->item = entry;
    else if (cont->type == COMMAND) cont->command = entry;
    else if (cont->type == TEXT)  cont->text = entry;

    if (first == NULL) return cont;
    if (type != first->type){
        free(cont);
        return NULL;
    }

    struct container* cont2 = first;
    for (;cont2->next != NULL;) cont2 = cont2->next;
    cont2->next = cont;

    return cont;
}

struct container* destroy_containers (struct container* first) {
    if (first == NULL) return NULL;

    if (first->next != NULL) destroy_next_conts(first->next);

    if (first->type == ROOM) destroy_room(first->room);
    else if (first->type == COMMAND) destroy_command(first->command);
    else if (first->type == ITEM) destroy_item(first->item);
    else if (first->type == TEXT) free(first->text);

    free(first);
    //first = NULL;

    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name) {
    if (name == NULL || first == NULL) return NULL;
    char* i_name = NULL;
    struct container *cont = first;

    for (;!(cont == NULL);)
    {
        if (cont->type == ROOM) i_name = cont->room->name;
        else if (cont->type == ITEM) i_name = cont->item->name;
        else if (cont->type == COMMAND) i_name =  cont->command->name;
        //else if (cont->type == TEXT) i_name = cont->text;
        else {
            cont = cont->next;
            continue;
        }
        if (strcmp(name, i_name) == 0) return cont;
        else cont = cont->next;
    }

    return NULL;
}

struct container* remove_container(struct container *first, void *entry) {
    if (first == NULL || entry == NULL) return NULL;

    struct container *box1 = first;
    struct container *box2 = first;

    char * name1 = NULL;
    char * name2 = NULL;

    for (;!(box2 == NULL);)
    {
        if (check_string2(name1, name2) == 0 && name1 != NULL)
        {
            box2->next = box1->next;
            free(box2);
            if (box1 == NULL) return NULL;
            return box1;
        }

        if (box1->type == ROOM) name1 = box1->room->name;
        else if (box1->type == ITEM) name1 = box1->item->name;
        else if (box1->type == COMMAND) name1 =  box1->command->name;
        else if (box1->type == TEXT) name1 = box1->text;

        if (box1->type == ROOM) name2 = ((struct room*)entry)->name;
        else if (box1->type == ITEM) name2 = ((struct item *)entry)->name;
        else if (box1->type == COMMAND) name2 =  ((struct command *)entry)->name;
        else if (box1->type == TEXT) name2 = (char *)entry;

        box1 = box2;
        box1 = box1->next;
    }

    return first;
}

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

int check_symbol2 (char c) { // pomocka -> https://www.cyberforum.ru/c-beginners/thread2191515.html
    int answer = -1;
    if (c >= 'a' && c <= 'z') answer = 0;
    else if (c >= 'A' && c <= 'Z') answer = 1;
    return answer;
}

int check_string2 (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    char tmp; int eq = 1;

    for (int i=0, c1, c2, swp = 'a' - 'A'; str_one[i] != '\0' && eq > 0; i++)
    {
        tmp = str_two[i];
        c1 = check_symbol2(str_one[i]);
        c2 = check_symbol2(str_two[i]);
        if (c1 < c2)    tmp += swp;
        if (c1 > c2)    tmp -= swp;
        if (str_one[i] != tmp) eq = 0;
    }

    if (eq > 0) return 0;
    return 1;
}

