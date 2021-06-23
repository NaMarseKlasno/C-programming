#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "track.h"



struct track* create_track (const char* title, int duration)
{
    if(!title || duration <= 0 || strlen(title) > 100) return NULL;
    struct track* track = calloc(1, sizeof(struct track));

    track->title = title;
    track->duration = duration;

    return track;
}


void free_track(struct track* track){
    if(!track){
        return;
    }
    free(track);


}
