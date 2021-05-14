#include "world.h"
#include <stdlib.h>
#include <string.h>
#include "item.h"

void add_rooms (struct room* array[]);
void add_items (struct room* rooms[]);
void put_rooms (struct room* rooms[], struct container* cont);

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

struct container* create_world() {
    struct room* rooms[16];

    // ***** set rooms and items to rooms
    add_rooms(rooms);
    add_items(rooms);

    struct container* cont = create_container(NULL, ROOM, rooms[0]);

    // ***** put rooms to container
    put_rooms(rooms, cont);

    return cont;
}

struct container* destroy_world(struct container* world) {
    destroy_containers(world);
    return NULL;
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if (room == NULL) return NULL;

    if (world != NULL) {
        if (get_from_container_by_name(world, room->name) != NULL) return NULL;
    } struct container* cont = create_container(world, ROOM, room);

    return cont;
}

struct room* get_room(struct container* world, char* name) {
    if (world == NULL || name == NULL || world->room == NULL || strlen(name) == 0) return NULL;
    struct room* mama_mia = get_from_container_by_name(world, name);

    return mama_mia;
}

void add_rooms (struct room* array[])
{
    array[0] = create_room("room1", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    array[1] = create_room("room2", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[0], array[1], NULL, NULL, NULL);
    array[2] = create_room("room3", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[1], array[2], NULL, NULL, NULL);
    array[3] = create_room("room4", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[2], array[3], NULL, NULL, NULL);
    array[4] = create_room("room5", "The 5 vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[3], array[4], NULL, NULL, NULL);
    array[5] = create_room("room6", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[4], array[5], NULL, NULL, NULL);
    array[6] = create_room("room7", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[5], array[6], NULL, NULL, NULL);
    array[7] = create_room("room8", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[6], array[7], NULL, NULL, NULL);
    array[8] = create_room("room9", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[7], array[8], NULL, NULL, NULL);
    array[9] = create_room("room10", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[8], array[9], NULL, NULL, NULL);
    array[10] = create_room("room11", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[9], array[10], NULL, NULL, NULL);
    array[11] = create_room("room12", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[10], array[11], NULL, NULL, NULL);
    array[12] = create_room("room13", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[11], array[12], NULL, NULL, NULL);
    array[13] = create_room("room14", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[12], array[13], NULL, NULL, NULL);
    array[14] = create_room("room15", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[13], array[14], NULL, NULL, NULL);
    array[15] = create_room("room16", "The vagina is a self-cleaning organ. It does not need to be washed with soap, as this can upset the microflora balance and promote infection");
    set_exits_from_room(array[14], array[15], NULL, NULL, NULL);
}

void add_items (struct room* rooms[])
{
    add_item_to_room(rooms[0], create_item("DONH1","pchoul",1));
    add_item_to_room(rooms[1], create_item("DONH2","pchoul",1));
    add_item_to_room(rooms[2], create_item("DONH3","pchoul",1));
    add_item_to_room(rooms[3], create_item("DONH4","pchoul",1));
    add_item_to_room(rooms[4], create_item("DONH5","pchoul",1));
    add_item_to_room(rooms[5], create_item("DONH6","pchoul",1));
}

void put_rooms (struct room* rooms[], struct container* cont)
{
    cont = create_container(cont, ROOM, rooms[1]);
    cont = create_container(cont, ROOM, rooms[2]);
    cont = create_container(cont, ROOM, rooms[3]);
    cont = create_container(cont, ROOM, rooms[4]);
    cont = create_container(cont, ROOM, rooms[5]);
    cont = create_container(cont, ROOM, rooms[6]);
    cont = create_container(cont, ROOM, rooms[7]);
    cont = create_container(cont, ROOM, rooms[8]);
    cont = create_container(cont, ROOM, rooms[9]);
    cont = create_container(cont, ROOM, rooms[10]);
    cont = create_container(cont, ROOM, rooms[11]);
    cont = create_container(cont, ROOM, rooms[12]);
    cont = create_container(cont, ROOM, rooms[13]);
    cont = create_container(cont, ROOM, rooms[14]);
    create_container(cont, ROOM, rooms[15]);
}
