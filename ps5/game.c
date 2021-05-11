#include "game.h"
#include "room.h"
#include <stdlib.h>


struct game* create_game() {
    struct game* alloc_game = calloc(1, sizeof(struct game));
    if (alloc_game == NULL) return NULL;

    struct room* ROOM_DATA = create_room("ROOM_NAME", "I finally got that ‘come over’ text I had been waiting for.\nI was sure I was about to have mind-blowing sex with my girlfriend.\nI had watched insane amounts of porn leading up to this, and I totally knew what\nI was doing.\n");

    alloc_game->world = create_container(NULL, ROOM, ROOM_DATA);
    alloc_game->current_room = get_from_container_by_name(alloc_game->world, "ROOM_NAME");

    alloc_game->backpack = create_backpack(1);
    alloc_game->parser = create_parser();
    alloc_game->state = PLAYING;

    return alloc_game;
}

struct game* destroy_game(struct game* game) {
    if (game == NULL) return NULL;

    destroy_containers(game->world);
    destroy_parser(game->parser);
    destroy_backpack(game->backpack);
    destroy_room(game->current_room);
    free(game);

    return NULL;
}

void play_game(struct game* game) {
    if (game == NULL) return;
    game->state = PLAYING;
    for (;game->state == PLAYING;) game->state = GAMEOVER;
}

void execute_command(struct game* game, struct command* command) {
    if (game == NULL || command == NULL) return;
}