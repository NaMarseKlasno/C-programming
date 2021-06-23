#include <stdio.h>

#include "playlist.h"
#include "track.h"


int main (void)
{
    struct track* track = create_track("Za rana za rosy", 240);
    free_track(track);

    struct playlist* playlist = create_playlist("Soundtracks");

    append_track_to_playlist(playlist, track);

    append_track_to_playlist(playlist, create_track("Wait", 355));
    append_track_to_playlist(playlist, create_track("Outro", 247));
    append_track_to_playlist(playlist, create_track("Midnight City", 242));
    //    next(playlist);

    play(playlist);
    printf("%s\n", playlist->first->track->title);
    printf("%s\n", playlist->current->track->title);
    change_mode(playlist, DONT_REPEAT);
    play(playlist);
    printf("%s\n", playlist->first->track->title);
    printf("%s\n", playlist->current->track->title);
    play(playlist);
    printf("%s\n", playlist->first->track->title);
    printf("%s\n", playlist->current->track->title);
    play(playlist);
    printf("%s\n", playlist->first->track->title);
    printf("%s\n", playlist->current->track->title);
//    prev(playlist);
//    next(playlist);
//    printf("%s\n", playlist->current->track->title);
//    next(playlist);
//    prev(playlist);
//    printf("%s\n", playlist->current->track->title);
//    next(playlist);
//    printf("%s\n", playlist->first->track->title);
//    printf("%s\n", playlist->current->track->title);
    change_mode(playlist, ONE_SONG);
//    play(playlist);
    free_track(track);
    free_playlist(playlist);

    return 0;
}
