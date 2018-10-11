#pragma once

#include "db_music.hpp"
#include "db_sound.hpp"
#include "filesystem.hpp"
#include "log.hpp"
#include "optional.hpp"
#include "position.hpp"
#include "shared_id.hpp"



namespace elona
{

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

void snd_at(
    SharedId sound_id,
    const Position& p,
    bool loop = false,
    bool allow_duplicate = true);
void snd_at(
    const char* sound_id,
    const Position& p,
    bool loop = false,
    bool allow_duplicate = true);

void snd(SharedId sound_id, bool loop = false, bool allow_duplicate = true);
void snd(const char* sound_id, bool loop = false, bool allow_duplicate = true);

optional<SharedId> sound_id_for_element(int element_id);
void sound_kill(const Position& position);
void sound_pick_up();
void sound_footstep(int foot);
void sound_footstep2(int foot);

void sound_play_environmental();
void stop_music();

void play_music(optional<SharedId> music_id = none);
void play_music(const char* music_id);


} // namespace elona
