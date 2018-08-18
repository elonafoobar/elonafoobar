#pragma once
#include "lion.hpp"

namespace elona
{

struct sound_data
{
    int id;
    fs::path file;
};

ELONA_LION_DEFINE_DB(sound_db, sound_data, int, "sound")

extern sound_db the_sound_db;

} // namespace elona
