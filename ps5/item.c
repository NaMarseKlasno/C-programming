#include "item.h"
#include <stdlib.h>
#include <string.h>

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

struct item* create_item(char* name, char* description, unsigned int properties) {
    if (name == NULL || description == NULL || name[0] == '\0' || description[0] == '\0') return NULL;

    struct item* ITEM = calloc(1, sizeof(struct item));
    if (ITEM == NULL) return NULL;

    // ***** allocate memory for string 'name' & copy name to struct item
    ITEM->name = calloc(strlen(name)+1, sizeof(char));
    if (ITEM->name == NULL) {
        free(ITEM);
        return NULL;
    }
    strcpy(ITEM->name, name);

    // ***** allocate memory for string 'description' & copy description to struct item
    ITEM->description = calloc(strlen(description)+1, sizeof(char));
    if (ITEM->description == NULL) {
        free(ITEM->name);
        free(ITEM);
        return NULL;
    }
    strcpy(ITEM->description, description);

    ITEM->properties = properties;

    return ITEM;
}

struct item* destroy_item(struct item* item) {
    if (item == NULL)
    {
        return NULL;
    }

    else if (item->name != NULL)
    {
        free(item->name);
    }
    if (item->description != NULL)
    {
        free(item->description);
    }

    free(item);

    return NULL;
}