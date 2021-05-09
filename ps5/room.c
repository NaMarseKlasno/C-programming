#include "room.h"
#include "additional.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


struct room* create_room(char *name, char *description) {
    if (name == NULL || description == NULL) return NULL;

    struct room* chamber = calloc(1, sizeof(struct room));
    if (chamber == NULL) return NULL;

    chamber->description = description;
    chamber->name = name;
    chamber->east = NULL;
    chamber->items = NULL;
    chamber->north = NULL;
    chamber->south = NULL;
    chamber->west = NULL;

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

    destroy_item(room->items->item);

    if (room->east != NULL) destroy_room(room->east);
    if (room->west != NULL) destroy_room(room->west);
    if (room->south != NULL) destroy_room(room->south);
    if (room->north != NULL) destroy_room(room->north);

    return NULL;
}

void add_item_to_room(struct room* room, struct item* item) {
    if (room == NULL || item == NULL) return;
    room->items->item = item;
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
        if (ITEM->item == item) ITEM->item = NULL;
        ITEM = ITEM->next;
    }

}

