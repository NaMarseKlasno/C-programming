#include "backpack.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct backpack* create_backpack(const int capacity)
{
    struct backpack* handbag = calloc(1, sizeof(struct backpack));
    if (handbag == NULL)
        return NULL;

    handbag->capacity = capacity;

    return handbag;
}


struct backpack* destroy_backpack(struct backpack* backpack)
{
    if (backpack == NULL) return NULL;

    backpack->items = destroy_containers(backpack->items);
    free(backpack);

    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item) {
    if (item == NULL || backpack == NULL || backpack->size >= backpack->capacity)
        return false;
    if (backpack->size == 0)
        backpack->items = create_container(backpack->items, ITEM, item);
    else
        create_container(backpack->items, ITEM, item);

    ++backpack->size;

    return true;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name) {
    if (name == NULL || backpack == NULL || name[0] == '\0') return NULL;

    struct item* ITEM = NULL;
    struct container* cont = backpack->items;

    cont = get_from_container_by_name(cont, name);
    ITEM = cont->item;

    return ITEM;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item) {
    if (backpack != NULL && backpack->items != NULL && item != NULL)
    {
        struct container* ITEM = backpack->items;

        for (;ITEM != NULL;) {
            if (ITEM->item == item) break;
            ITEM = ITEM->next;
        } if (ITEM != NULL) {
            backpack->items = remove_container(backpack->items, ITEM->item);
            --backpack->size;
        }
    }
}