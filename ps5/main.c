#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "room.h"
#include "game.h"
#include "container.h"
#include "world.h"


int main (void)
{
    struct game* game1 = create_game();
    struct room* north = create_room("Bakery", "The delightful smell of meat pies fills the air, making you hungry. The baker flashes a grin, as he slides a box marked 'Not Human Organs' under a table with his foot.");
    struct room* south = create_room("West X Street", "West X Street is the rich section of town. So rich, they paved the streets with gold. This probably was not a good idea. The thief guild opened up the next day.");
    set_exits_from_room(north, NULL, south, NULL, NULL);
    set_exits_from_room(south, north, NULL, NULL, NULL);
    game1->current_room = north;
    struct command* command = parse_input(game1->parser, "JUH");
    printf("%s", command->name);
    execute_command(game1, command);

    printf("%s\n", game1->current_room->name);


    // ***** COMMAND  ------------------------------------------------------------------
    struct command* help = create_command("POMOC", "Zobrazi zoznam vsetkych prikazov", "(POMOC)", 1);
    help = destroy_command(help);

    execute_command(NULL, NULL);


    //(1 + 3) != 4? printf("first") : printf("second");

    // ***** PARSER  --------------------------------------------------------------------
    struct parser* parser = create_parser();

    char* input = "VERZ IA          ";
    struct command* cmd = parse_input(parser, input);
    if (cmd != NULL && cmd->name != NULL) printf("%s\n", cmd->name);

    char* unknown_input = "         VERZ IA";
    cmd = parse_input(parser, unknown_input);
    if (cmd != NULL && cmd->name != NULL) printf("%s\n", cmd->name);

    destroy_command(cmd);

    parser = destroy_parser(parser);
    // ***** PARSER  --------------------------------------------------------------------



    // ***** WORLD  --------------------------------------------------------------------
    struct container* world = create_world();
    if (world == NULL) printf("word == NULL\n");

    struct room* room_5 = get_room(world, "room5");
    if (room_5 == NULL) printf("room_5 == NULL\n");


    struct room* same_room = create_room("same_name", "desc!!");


    world = add_room_to_world(world, same_room);

    struct room* find_room = get_room(world, "same_name");
    //show_room(find_room);
    if (find_room == NULL) printf("find room == NULL\n");

    world = destroy_world(world);
    // ***** WORLD  --------------------------------------------------------------------


    // ***** ITEM   --------------------------------------------------------------------
    struct item* key = create_item("GOLD CHOCO",
                                   "Zlaty kluc pravdepodobne od zlatej zamky. Su na nom viditelne vyryte pismena AB",
                                   MOVABLE | USABLE );
    printf("item name: %s,\ndesc item: %s\n", key->name, key->description);

    // ***** ITEM   --------------------------------------------------------------------

    // ***** BACKPACK   --------------------------------------------------------------------
    struct backpack* backpack = create_backpack(5);
    add_item_to_backpack(backpack, key);
    add_item_to_backpack(backpack, create_item("magic item", "MAGIC ITEM FOR SPAWN ANIME GIRL", MOVABLE | USABLE));

    printf("item name: %s,\ndesc item: %s\n", backpack->items->item->name, backpack->items->item->description);
    printf("item name: %s,\ndesc item: %s\n", backpack->items->next->item->name, backpack->items->next->item->description);

    struct item* IT2 = get_item_from_backpack(backpack, "magic item");
    printf("%s\n", IT2->name);

    printf("size: %d\n", backpack->size);

    delete_item_from_backpack(backpack, key);

    printf("size: %d\n", backpack->size);
    printf("%s\n", backpack->items->item->name);
    //printf("%s\n", backpack->items->next->item->name);


    backpack = destroy_backpack(backpack);


    // ***** BACKPACK   --------------------------------------------------------------------
    key = destroy_item(key);

    // ***** get_from_container_by_name   --------------------------------------------------------------------
    struct room* rr = create_room("neviem", "tiez neviem");
    struct room* rr2 = create_room("n2222eviem", "tiez 222 neviem");
    struct room* rr3 = create_room("n3333eviem", "tiez 333 neviem");
    struct item* dildo = create_item("XL", "xD", MOVABLE | USABLE);
    add_item_to_room(rr3, dildo);

    struct container *cont2 = create_container(NULL, ROOM, rr);
    create_container(cont2, ROOM, rr2);
    create_container(cont2, ROOM, rr3);


    struct room* find_rr = get_from_container_by_name(cont2, "n3333eviem");
    show_room(find_rr);
    printf("\n%s\n", find_rr->items->item->name);

    if (get_item_from_room(find_rr, "fnsjcsd") == NULL) printf("fnidjv\n");
    delete_item_from_room(find_rr, dildo);
    if (get_item_from_room(find_rr, "XL") == NULL) printf("DILDO is not in room\n");


    //destroy_containers(cont2);
    //free(dildo->name);
    //free(dildo->description);
    //free(dildo);
    // ***** get_from_container_by_name   --------------------------------------------------------------------

    // ***** clean all shit


    // create game first with all the members of the game structure
    struct game* game = create_game();

    // after successful creation, play the game
    // game loop is located in the function play_game()
    play_game(game);

    // destroy game at the end
    game = destroy_game(game);

    return 0;
}
