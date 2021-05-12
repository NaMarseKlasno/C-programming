#include "game.h"
#include "room.h"
#include <stdlib.h>


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
    if (game == NULL) return;
    game->state = PLAYING;
    for (;game->state == PLAYING;) game->state = GAMEOVER;
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL || command == NULL) return;

    if (command == (get_from_container_by_name(game->parser->commands, "ZAPAD")))
    {
        if (game->current_room->west != NULL) {
            game->current_room = game->current_room->west;
            game->parser->history = create_container(game->parser->history, TEXT, "ZAPAD");
            show_room(game->current_room);
        }
        return;
    }
    if (command == (get_from_container_by_name(game->parser->commands, "SEVER")))
    {
        if (game->current_room->north != NULL) {
            game->current_room = game->current_room->north;//ceking@
            game->parser->history = create_container(game->parser->history, TEXT, "SEVER");
            show_room(game->current_room);
        }
        return;
    }
    if (command == (get_from_container_by_name(game->parser->commands, "JUH")))
    {
        if (game->current_room->south != NULL) {
            game->current_room = game->current_room->south;//ceking
            game->parser->history = create_container(game->parser->history, TEXT, "JUH");
            show_room(game->current_room);
        }
        return;
    }
    if (command == (get_from_container_by_name(game->parser->commands, "VYCHOD")))
    {
        if (game->current_room->east != NULL) {
            game->current_room = game->current_room->east;
            game->parser->history = create_container(game->parser->history, TEXT, "VYCHOD");
            show_room(game->current_room);

        }
        return;
    }
}