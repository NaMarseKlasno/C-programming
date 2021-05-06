#include "container.h"
#include <stdlib.h>
#include <string.h>


void destroy_entry (struct container* cont);
void destroy_next_cont (struct container* next);

struct container* create_container (struct container* first, enum container_type type, void* entry) {
    if (entry == NULL) return remove_container(NULL, NULL);

    struct container* cont = calloc(1, sizeof(struct container));
    cont->type = type;
    cont->next = NULL;

    destroy_entry(cont);

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
    else if (first->next != NULL) destroy_next_cont(first->next);

    destroy_entry(first);
    free(first);
    first = NULL;

    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name) {
    if (name == NULL || first == NULL) return NULL;
    char * i_name = NULL;
    struct container *cont = first;

    for (;!(cont == NULL);)
    {
        if (cont->type == ROOM) = i_name = cont->room->name;
        else if (cont->type == ITEM) i_name = cont->item->name;
        else if (cont->type == COMMAND) i_name =  cont->command->name;
        //else if (cont->type == TEXT) i_name = cont->text;
        else {
            cont = cont->next;
            continue;
        }
        if (strcmp(name, item_name) == 0) return cont;
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

    for (;!(first == NULL);)
    {
        if (strcmp(name1, name2) == 0 && name1 != NULL)
        {
            box2->next = box1->next;
            free(box2);
            //destroy_entry(entry);
            if (box1 == NULL) return NULL;
        }

        if (box1->type == ROOM) name1 = box1->room->name;
        else if (box1->type == ITEM) name1 = box1->item->name;
        else if (box1->type == COMMAND) name1 =  box1->command->name;
        else if (box1->type == TEXT) name1 = box1->text;

        if (first->type == ROOM) name2 = (struct room *)entry->room->name;
        else if (first->type == ITEM) name2 = (struct item *)entry->item->name;
        else if (first->type == COMMAND) name2 =  (struct command *)entry->command->name;
        else if (first->type == TEXT) name2 = (char *)entry;

        box1 = box2;
        box1 = box1->next;
    }

    return first;
}


void destroy_entry (struct container* cont) {
    if (cont->type == ROOM) destroy_room(cont->room);
    else if (cont->type == ITEM) destroy_item(cont->item);
    else if (cont->type == COMMAND) destroy_command(cont->command);
    else if (cont->type == TEXT) free(cont->text);
}


void destroy_next_cont (struct container* next) {
    if (next == NULL) return;
    if (next->next != NULL)
        destroy_next_cont(next->next);
    destroy_entry(next);
    free(next);
    next = NULL;
}