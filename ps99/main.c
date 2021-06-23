#include "playlist.h"
#include "track.h"


int main (void)
{

    struct track* track = create_track("Don't Let Me Be Misunderstood", 629);
    struct playlist* playlist = create_playlist("Vypekacky");
    append_track_to_playlist(playlist, track);




    struct playlist* playlist2 = create_playlist("M83");
    append_track_to_playlist(playlist2, create_track("Wait", 355));
    append_track_to_playlist(playlist2, create_track("Outro", 247));
    append_track_to_playlist(playlist2, create_track("Midnight City", 242));

    play(playlist2);

    next(playlist2);
    prev(playlist2);



    struct playlist* playlist3 = create_playlist("Best Off");

    change_mode(playlist3, DONT_REPEAT);




    free_playlist(playlist);
    free_playlist(playlist2);
    free_playlist(playlist3);

    return 0;
}
