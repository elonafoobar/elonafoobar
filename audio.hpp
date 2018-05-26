#pragma once

#include "filesystem.hpp"



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
void snd(int sound_id, bool loop = false, bool allow_duplicate = true);
void play_music(int music_id = 0);


} // namespace elona
