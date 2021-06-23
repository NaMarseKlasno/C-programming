#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <stdbool.h>

#include "track.h"

enum play_mode {
    ONE_SONG,       /// current track will not change
    REPEAT,         /// after last track, current track will become first track
    DONT_REPEAT     /// after last track, current track will remain last track
};


struct entry {
    struct track *track;    // track of the entry
    struct entry *next;     // reference to the next entry in playlist
    struct entry *prev;     // reference to the previous entry in playlist
};


struct playlist {
    char* name;             /// playlist name
    int duration;           /// total playlist duration in seconds
    int size;               /// number of tracks
    enum play_mode mode;    /// play mode

    struct entry *current;  /// current track to play
    struct entry *first;    /// first track in playlist
};


/**
 * Creates new playlist
 *
 * Creates new empty playlist with the given name. The default play mode of
 * the newly created playlist is REPEAT. A separate part of the memory must
 * be allocated for the name of the playlist, to which it will then be copied.
 *
 * @param name the name of the newly created playlist
 * @return reference to the created playlist or NULL if there was no name given
 */
struct playlist* create_playlist(char* name);


/**
 * Appends track to the playlist
 *
 * Track will be appended to the playlist (to it's end).
 * If playlist or track will be NULL, then there is nothing to do.
 *
 * @param playlist the playlist, to which the track will be appended
 * @param track the track to append
 */
void append_track_to_playlist(struct playlist *playlist, struct track *track);


/**
 * Plays the current track of a playlist
 *
 * Modifies the state of the playlist - its current track - in the following way:
 *    * if playback mode is set to ONE_SONG, then current track will remain unchanged
 *    * if playback mode is set to REPEAT, then new current track will be the one next to
 *      the current; if the last track was played, then the first track will become the current one
 *    * if playback mode is set to DONT_REPEAT, then new current track will be the one next
 *      to the current; if the last track was played, then the current track will remain unchanged
 *
 * Comment: The actual playback of the current track can be visualised in any way by printing
 * to the standard output. The output is not tested.
 *
 * @param playlist reference to the playlist
 * @return the track to be played or NULL, if there is no playlist or there is nothing to play
 */
struct track* play(struct playlist* playlist);


/**
 * Move to the next track
 *
 * Changes the current track to the next track in playlist regardless of the play mode.
 * If the current track is the last one, then it remains unchanged.
 *
 * @param playlist reference to the playlist
 * @return new current track or NULL, if there is no playlist or playlist is empty
 */
struct track* next(struct playlist* playlist);


/**
 * Move to the previous track
 *
 * Changes the current track to the previous track in playlist regardless of the play mode.
 * If the current track is the first one, then it remains unchanged.
 *
 * @param playlist reference to the playlist
 * @return new current track or NULL, if there is no playlist or playlist is empty
 */
struct track* prev(struct playlist* playlist);


/**
 * Changes the play mode of a given playlist
 *
 * Function will change the current playback mode of the playlist.
 * If there is no playlist given, then there is nothing to change.
 *
 * @param playlist reference to the playlist
 * @param mode new play mode
 */
void change_mode(struct playlist* playlist, enum play_mode mode);


/**
 * Removes the whole playlist from the memory
 *
 * Frees all the elements of the playlist including the tracks.
 *
 * Comment: Tracks can be part of other playlists, but currently - we don't care ;)
 *
 * @param playlist reference to the playlist
 */
void free_playlist(struct playlist* playlist);
#endif
