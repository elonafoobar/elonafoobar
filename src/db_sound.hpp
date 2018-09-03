#pragma once
#include "lion.hpp"

namespace elona
{

struct sound_data
{
    int id;
    fs::path file;
};

ELONA_LION_DEFINE_DB(SoundDB, sound_data, int, "sound")

extern SoundDB the_sound_db;

} // namespace elona
