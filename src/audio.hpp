#pragma once

#include "filesystem.hpp"
#include "db_sound.hpp"



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

template <typename I>
void snd(I sound_id, bool loop = true, bool allow_duplicate = false)
{
    snd_inner(**the_sound_db[sound_id], loop, allow_duplicate);
}

void snd_inner(const sound_data& sound_id, bool loop = false, bool allow_duplicate = true);
void play_music(int music_id = 0);


} // namespace elona
