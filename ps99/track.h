#ifndef _TRACK_H
#define _TRACK_H

#include <stdbool.h>


struct track {
    char* title;    /// track title
    int duration;   /// track duration in seconds
};


/**
 * Creates new track
 *
 * Function creates a new track based on it's title and duration. Track can be
 * created, when the title is not empty and duration is greater than 0 seconds.
 * A separate part of the memory must be allocated for the track title, to
 * which it will then be copied.
 *
 * @param title the title of the track
 * @param duration the duration of the track in seconds
 * @return reference to the track or NULL if there was invalid or no title or duration
 */
struct track* create_track(const char* title, int duration);


/**
 * Frees track from the memory
 *
 * @param track reference to the existing track
 */
void free_track(struct track* track);
#endif
