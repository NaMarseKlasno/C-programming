#include "room.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_string (char *str_one, char *str_two);


struct room* create_room(char *name, char *description) {
    if (name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;

    struct room* chamber = calloc(1, sizeof(struct room));
    if (chamber == NULL) return NULL;

    char *NAME = calloc(strlen(name) + 1, 1);
    strcpy(NAME, name);
    chamber->name = NAME;

    char *DESC = calloc(strlen(description) + 1, 1);
    strcpy(DESC, description);
    chamber->description = DESC;

    chamber->items = NULL;
    chamber->south = NULL;
    chamber->north = NULL;
    chamber->west = NULL;
    chamber->east = NULL;

    return chamber;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west) {
    if (room == NULL) return;

    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room) {
    if (room == NULL) {
        printf("ERROR: romm = NULL!\n");
        return;
    }
    printf("%s\n", room->description);
}

struct room* destroy_room(struct room* room) {
    if (room == NULL) return NULL;

    free(room->description);
    free(room->name);

    destroy_room(room->east);
    destroy_room(room->west);
    destroy_room(room->south);
    destroy_room(room->north);

    destroy_containers(room->items);
    free(room);

    return NULL;
}

void add_item_to_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) return;

    if (room->items == NULL) {
        room->items = create_container(room->items, ITEM, item);
    }
}

struct item* get_item_from_room(const struct room* room, const char* name) {
    if (room == NULL || name == NULL) return NULL;

    struct container *ITEM = room->items;
    char *name2 = NULL;
    //strcpy(name2, name);
    char x[strlen(name)];
    for (int i = 0; i < sizeof(name)-1; ++i) x[i] = name[i];
    x[sizeof(name)] = '\0';
    name2 = x;

    for (;ITEM != NULL;)
    {
        if (check_string(ITEM->item->name, name2) == 0)
            return ITEM->item;
        ITEM = ITEM->next;
    }

    return NULL;
}

void delete_item_from_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) return;

    struct container *ITEM = room->items;

    for (;ITEM != NULL;)
    {
        if (check_string(ITEM->item->name, item->name) == 0)
            ITEM->item = NULL;
        ITEM = ITEM->next;
    }

}

int check_string (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    for (int i = 0; i < strlen(str_one); ++i) if (toupper(str_one[i]) != toupper(str_two[i])) return 1;
    return 0;
}
