#pragma once

#include "filesystem.hpp"



namespace elona::snail::audio
{

/// Loop sound/music forever.
constexpr int loop_forever = -1;



namespace sound
{

/// Initialize sound system.
bool init();

/// Load @a path to @a channel.
void load(int channel, const fs::path& path);

/// Play @a channel sound @a loops times.
/// Passiing `loop_forever` will play the sound forever.
void play(int channel, int loops);

/// Stop @a channel sound.
void stop(int channel);

/// Get @a channel's volume.
/// volume: 0 - 128
int get_volume(int channel);

/// Set @a channel's volume.
/// volume: 0 - 128
void set_volume(int channel, int volume);

/// Set @a channel sound position with @a angle and @a distance.
/// @param angle 0-360 in degrees
/// @param distance 0-255 (0, nearest; 255, farthest)
void set_position(int channel, short angle, unsigned char distance);

/// Query whether @a channel is playing.
bool is_playing(int channel);

} // namespace sound



namespace music
{

/// Initialize music system.
bool init();

/// Load @a path.
void load(const fs::path& path);

/// Play the currently loaded music @a loops times.
/// Passiing `loop_forever` will play the music forever.
void play(int loops);

/// Stop the currently played music.
void stop();

/// Get current volume.
/// volume: 0 - 128
int get_volume();

/// Set music volume.
/// volume: 0 - 128
void set_volume(int volume);

} // namespace music

} // namespace elona::snail::audio
