#include <stdio.h>
#include <stdlib.h>

#include "playlist.h"


struct entry* find_last (struct playlist *playlist)
{
    struct entry* last_entry = playlist->first;

    while (last_entry->next != NULL) last_entry = last_entry->next;

    return last_entry;
}


struct playlist* create_playlist (char* name)
{
    if (!name) return NULL;

    struct playlist* playlist = calloc(1, sizeof(struct playlist));

    playlist->name = name;
    playlist->duration = 0;
    playlist->size = 0;
    playlist->mode = REPEAT;
    playlist->current = NULL;
    playlist->first = NULL;

    return playlist;
}


void append_track_to_playlist (struct playlist *playlist, struct track *track)
{
    if (!playlist || !track) return;

    struct entry* entry = NULL;
    entry = calloc(1, sizeof(struct entry));
    entry->track = track;

    if (playlist->first == NULL)
    {
        playlist->first = entry;
        entry->next = NULL;
        entry->prev = NULL;
    } else {
        struct entry* last_entry = playlist->first;
        while(last_entry->next != NULL) {
            last_entry = last_entry->next;
        }
        last_entry->next = entry;
        entry->prev = last_entry;
    }

    playlist->size++;
    playlist->duration = playlist->duration + track->duration;
}

struct track* play (struct playlist* playlist)
{
    if (!playlist) return NULL;

    struct entry* cur_tr = playlist->current;
    switch (playlist->mode)
    {
        case ONE_SONG:
            cur_tr->track = cur_tr->track;
            break;
        case REPEAT:
            next(playlist);
            break;
        case DONT_REPEAT:
            next(playlist);
            break;
    }

    return cur_tr->track;
}

struct track* next (struct playlist* playlist)
{
    if (!playlist) return NULL;

    struct entry* last_entry = find_last(playlist);

    if (playlist->current == last_entry && playlist->mode == REPEAT) {
        playlist->current = playlist->first;
        return playlist->current->track;
    }
    else if (playlist->current == last_entry && playlist->mode == DONT_REPEAT) return playlist->current->track;

    playlist->current = playlist->current->next;

    return playlist->current->track;
}

struct track* prev (struct playlist* playlist)
{
    if (!playlist) return NULL;

    struct entry* last_entry = find_last(playlist);

    if (playlist->current == playlist->first) {
        playlist->current = last_entry;
        return playlist->current->track;
    } playlist->current = playlist->current->prev;

    return playlist->current->track;
}


void change_mode (struct playlist* playlist, enum play_mode mode)
{
    if (playlist == NULL) return;
    playlist->mode = mode;
}

void free_playlist (struct playlist* playlist)
{
    if (!playlist) return;
    free(playlist);
}
