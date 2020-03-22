#pragma once

#include "data/types/type_music.hpp"
#include "data/types/type_sound.hpp"
#include "filesystem.hpp"
#include "log.hpp"
#include "optional.hpp"
#include "position.hpp"



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

void initialize_sound_file();

std::pair<short, unsigned char> sound_calculate_position(const Position& p);

void snd_at(
    data::InstanceId sound_id,
    const Position& p,
    bool loop = false,
    bool allow_duplicate = true);

void snd(
    data::InstanceId sound_id,
    bool loop = false,
    bool allow_duplicate = true);

optional<data::InstanceId> sound_id_for_element(int element_id);
void sound_kill(const Position& position);
void sound_pick_up();
void sound_footstep(int foot);
void sound_footstep2(int foot);

void sound_play_environmental();
void stop_music();

void play_music();
void play_music(data::InstanceId music_id);

} // namespace elona
