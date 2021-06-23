#ifndef _TRACK_H
#define _TRACK_H

#include <stdbool.h>


struct track {
    char* title;
    int duration;
};


struct track* create_track (const char* title, int duration);


void free_track (struct track* track);

#endif
