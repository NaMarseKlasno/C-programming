#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include "track.h"
#include <stdbool.h>


enum play_mode {
    ONE_SONG,
    REPEAT,
    DONT_REPEAT
};


struct entry {
    struct track *track;
    struct entry *next;
    struct entry *prev;
};


struct playlist {
    char* name;
    int duration;
    int size;
    enum play_mode mode;

    struct entry *current;
    struct entry *first;
};


struct playlist* create_playlist (char* name);


void append_track_to_playlist (struct playlist *playlist, struct track *track);


struct track* play (struct playlist* playlist);


struct track* next (struct playlist* playlist);


struct track* prev (struct playlist* playlist);


void change_mode (struct playlist* playlist, enum play_mode mode);


void free_playlist (struct playlist* playlist);

#endif
