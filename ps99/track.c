#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "track.h"



struct track* create_track (const char* title, int duration)
{
    if (!title || duration <= 0 || strlen(title) > 100) return NULL;
    struct track* track = calloc(1, sizeof(struct track));

    char *TITLE = calloc(strlen(title)+1, sizeof(char));
    if (TITLE == NULL) {
        free(TITLE);
        return NULL;
    }
    for (int i = 0; i < strlen(title); ++i) TITLE[i] = title[i];
    TITLE[strlen(title)] = '\0';

    track->title = TITLE;

    track->duration = duration;

    return track;
}


void free_track(struct track* track){
    if(!track){
        return;
    }
    free(track);


}
