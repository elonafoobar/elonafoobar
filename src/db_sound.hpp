#pragma once
#include "lion.hpp"

namespace elona
{

struct SoundData
{
    int id;
    fs::path file;
};

ELONA_LION_DEFINE_DB(SoundDB, SoundData, int, "sound")

extern SoundDB the_sound_db;

} // namespace elona
