#include "container.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

void destroy_next_conts (struct container* next);
int check_string2 (char *str_one, char *str_two);


/**                         <RACCOON>
 *
 *                                    .                : :
 *                  _..----..__   __..:'.-'''-.-''    .  :
 *                .'      ,    '''    '    :   .'    /  '
 *               ',                  ( -=o):(o=-)   .  :
 *              :     ,               ''.  ;  .'  __:  :
 *              :          :      ,      '.0.''.-'.))  :  __..--
 *              :           :                ._.-'__| ':''.
 *               .           :   ,   ..  :.-' __.' /   ;    .
 *              .'       ,   :    _.'  '. '.''    /   /  '
 *            .:. .'.        :--:'_..--'''.))  .  ' -'    __.--'
 *          .''::'   '-.  .-''.  '.   .             __.--'
 *          :...:     __\  '.  '..))     '    __.--'
 *          ::'':.--''   '.)))          __.--'
 */


struct container* create_container (struct container* first, enum container_type type, void* entry) {
    if (entry == NULL) return NULL;

    struct container* cont = calloc(1, sizeof(struct container));
    if (cont == NULL) return NULL;
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

struct container* destroy_containers (struct container* first)
{
    if (first != NULL)
    {
        struct container* FIRST = first;
        struct container* SECOND = NULL;

        for (;FIRST != NULL;)
        {
            SECOND = FIRST->next;

            if (FIRST->type == ROOM) {
                destroy_room(FIRST->room);
                free(FIRST);
            } else if (FIRST->type == COMMAND) {
                destroy_command(FIRST->command);
                free(FIRST);
            } else if (FIRST->type == ITEM) {
                destroy_item(FIRST->item);
                free(FIRST);
            } else if (FIRST->type == TEXT) {
                free(FIRST->text);
                free(FIRST);
            }
            FIRST = SECOND;
        }
    }

    return NULL;
}

void* get_from_container_by_name(struct container *first, const char *name) {
    if (name == NULL || first == NULL) return NULL;
    char* text = NULL;// unsigned long len = strlen(name); //char str[len+1];
    struct container *cont = first;

    //for (unsigned long i = 0; i < len; ++i) str[i] = name[i];
    //str[len] = '\0';
    //char *str_2 = str;

    for (;cont != NULL;)
    {
        if (cont->type == ROOM) text = cont->room->name;
        else if (cont->type == ITEM) text = cont->item->name;
        else if (cont->type == COMMAND) text =  cont->command->name;
        else if (cont->type == TEXT) text =  cont->text;
        else if (text == NULL){
            cont = cont->next;
            continue;
        } else {
            cont = cont->next;
            continue;
        } if (check_string2((char*)name, text) == 0) {
            if (cont->type == ROOM) return cont->room;
            else if (cont->type == ITEM) return cont->item;
            else if (cont->type == COMMAND) return cont->command;
            else if (cont->type == TEXT) return cont->text;
        } else cont = cont->next;
    }

    return NULL;
}

struct container* remove_container(struct container *first, void *entry) {
    if (first == NULL || entry == NULL) return first;

    struct container *cont = first, *additional = NULL;

    for (;!(cont == NULL);)
    {
        if (cont->type == ROOM) {
            if (cont->room == entry)
            {
                if (additional != NULL){
                    additional->next = cont->next;
                    free(cont);
                    return first;
                } else {
                    first = first->next;
                    free(cont);
                    return first;
                }

            }
        }
        else if (cont->type == ITEM) {
            if (cont->item == entry)
            {
                if (additional != NULL){
                    additional->next = cont->next;
                    free(cont);
                    return first;
                } else {
                    first = first->next;
                    free(cont);
                    return first;
                }
            }
        }
        else if (cont->type == COMMAND) {
            if (cont->command == entry)
            {
                if (additional != NULL){
                    additional->next = cont->next;
                    free(cont);
                    return first;
                } else {
                    first = first->next;
                    free(cont);
                    return first;
                }
            }
        }
        else if (cont->type == TEXT) {
            if (cont->text == entry)
            {
                if (additional == NULL) {
                    first = first->next;
                    free(cont);
                    return first;
                }
                else if (additional != NULL){
                    additional->next = cont->next;
                    free(cont);
                    return first;
                }
            }
        }
        additional = cont;
        cont = cont->next;
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
}

int check_string2 (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    for (int i = 0; i < strlen(str_one); ++i) if (toupper(str_one[i]) != toupper(str_two[i])) return 1;
    return 0;
}

