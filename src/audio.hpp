#pragma once

#include "db_music.hpp"
#include "db_sound.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include "position.hpp"
#include "shared_id.hpp"



namespace elona
{

namespace detail
{

void snd_inner(
    const SoundData& sound,
    short angle = 0,
    unsigned char dist = 0,
    bool loop = false,
    bool allow_duplicate = true);

} // namespace detail

int DSINIT();
void DSLOADFNAME(const fs::path& filepath, int id);
void DSPLAY(int, bool);
void DSSTOP(int);
void DSSETVOLUME(int, int);
bool CHECKPLAY(int channel);

int DMINIT();
void DMLOADFNAME(const fs::path& filepath, int);
void DMPLAY(int, int);
void DMSTOP();

void sndload(const fs::path& filepath, int = 0);
void initialize_sound_file();

std::pair<short, unsigned char> sound_calculate_position(const Position& p);

template <typename I>
void snd_at(
    I sound_id,
    const Position& p,
    bool loop = false,
    bool allow_duplicate = true)
{
    short angle;
    unsigned char dist;
    std::tie(angle, dist) = sound_calculate_position(p);

    detail::snd_inner(
        **the_sound_db[sound_id], angle, dist, loop, allow_duplicate);
}

template <typename I>
void snd(I sound_id, bool loop = false, bool allow_duplicate = true)
{
    detail::snd_inner(**the_sound_db[sound_id], 0, 0, loop, allow_duplicate);
}

void sound_pick_up();
void sound_footstep(int foot);
void sound_footstep2(int foot);

void sound_play_environmental();
void stop_music();

void play_music(optional<SharedId> music_id = none);
void play_music(const char* music_id);


} // namespace elona
