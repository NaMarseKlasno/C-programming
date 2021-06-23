#include <stdio.h>

#include "playlist.h"
#include "track.h"


int main (void)
{
    struct track* track = create_track("Za rana za rosy", 240);
// struct track track = { .name = "Za rana za rosy", .duration = 240 };

    free_track(track);

    return 0;
}
