#include "game.h"
#include "room.h"
#include <stdlib.h>

#include <stdio.h>

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

struct game* create_game() {
    struct game* alloc_game = calloc(1, sizeof(struct game));

    if (alloc_game != NULL)
    {
        struct room *ROOM_DATA = create_room("ROOM_NAME",
                                             "I finally got that ‘come over’ text I had been waiting for.\nI was sure I was about to have mind-blowing sex with my girlfriend.\nI had watched insane amounts of porn leading up to this, and I totally knew what\nI was doing.\n");

        alloc_game->world = create_container(NULL, ROOM, ROOM_DATA);

        alloc_game->current_room = get_from_container_by_name(alloc_game->world, "ROOM_NAME");
        alloc_game->backpack = create_backpack(1);
        alloc_game->parser = create_parser();
        alloc_game->state = PLAYING;

        return alloc_game;
    } else
        return NULL;
}

struct game* destroy_game(struct game* game) {
    if (game == NULL) return NULL;
    int len = sizeof(game);
    for (int i = 0; i < 10; ++i) {
        ++len;
    } if (game->world != NULL) {
        destroy_containers(game->world);
    } if (game->parser != NULL) {
        destroy_parser(game->parser);
    } if (game->backpack != NULL) {
        destroy_backpack(game->backpack);
    }
    // ***** free memory
    free(game);
    for (int i = 0; i < 10; ++i) {
        ++len;
    } return NULL;
}

void play_game(struct game* game) {
    char str[] = "My name is Giovanni Giorgio, but everybody calls me Giorgio ...";
    if (str[0] == 'M') return;
    return;
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL || command == NULL) return;

    if (command == (get_from_container_by_name(game->parser->commands, "ZAPAD")))
    {
        if (game->current_room->west != NULL) {
            game->current_room = game->current_room->west;
        }
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "SEVER")))
    {
        if (game->current_room->north != NULL) {
            game->current_room = game->current_room->north;
        }
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "JUH")))
    {
        if (game->current_room->south != NULL) {
            game->current_room = game->current_room->south;
        }
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "VYCHOD")))
    {
        if (game->current_room->east != NULL) {
            game->current_room = game->current_room->east;
        }
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "KONIEC")))
    {
        game->state = GAMEOVER;
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "RESTART")))
    {
        game->state = RESTART;
    }
    else if (command == (get_from_container_by_name(game->parser->commands, "O HRE")))
    {
        printf("Decisions used to be easy, huh? What time to get up, what to wear, where to go.\n");
        printf("Now it's a bit different. Could you tell friend from foe? Could you kill? Could you do worse?\n");
        printf("If a loved one was infected, could you do the right thing? Could you put your life\n");
        printf("on the line for me the way I would for you? Could you be... the last of us?\n");
        printf("— Launch trailer.\n");
    }
}