#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "room.h"
#include "game.h"
#include "container.h"


int main (void)
{
    char *data = "DATA";
    char *data2 = "DATA2";
    char *desk = "\nNachadzas sa v chyzi svarneho suhaja. Na vychode sa nachadzaju dvere veduce z chyze von.\nMozne vychody z miesnosti:\n    vychod\nVidíš:\n    kluc\n    popisany papier\n";
    char *desk2 = "    “Virginity,” it's a loaded word and we place a lot of\nimportance and pressure on losing it and gaining sexual experience.\nAs a result, having sex for the first time becomes a major milestone for many,\nand the memories of those often awkward, sometimes painful,\noccasionally funny moments tend to stay with us.\n";
    char *desk3 = "I was in high school and had just started dating a\ngirl who was a year older than me, which was a pretty big deal.\nWe must have waited two, maybe three months before having sex for the first time\n(an eternity in the mind of a teen boy).\n";

   struct container *cont = create_container(NULL, ROOM, data);
   cont->room = create_room("room_1", desk);
   cont->next = create_container(cont, ROOM, data2);

   char *fake = "FAKE TAXI";
   cont->next->room = create_room(fake, desk);

   show_room(cont->room);

   struct container * fake_room = get_from_container_by_name(cont, fake);
   fake_room->room->description = desk2;
   show_room(fake_room->room);

   struct room *n_room = create_room("north", desk3);
   struct room *room1 = create_room("north", desk3);
   struct room *room2 = create_room("north", desk3);
   struct room *room3 = create_room("north", desk3);

   set_exits_from_room(fake_room->room, n_room, room1, room2, room3);

   show_room(fake_room->room->north);
   add_item_to_room(fake_room->room, NULL);
   struct item* predmet = get_item_from_room(fake_room->room, NULL);
   delete_item_from_room(fake_room->room, predmet);

   struct command* help = create_command("POMOC", "Zobrazi zoznam vsetkych prikazov", "(POMOC)", 1);
   help = destroy_command(help);

   execute_command(NULL, NULL);

   struct parser* pars = create_parser();
   destroy_parser(pars);

   // ***** clean all shit
   destroy_room(n_room);
   destroy_room(room1);
   destroy_room(room2);
   destroy_room(room3);

   struct container * new_first = remove_container(cont, data2);
   show_room(new_first->room);
   destroy_containers(cont);

   // create game first with all the members of the game structure
   struct game* game = create_game();

// after successful creation, play the game
// game loop is located in the function play_game()
   play_game(game);

// destroy game at the end
   game = destroy_game(game);

   return 0;
}
