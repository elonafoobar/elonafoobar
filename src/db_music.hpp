#pragma once
#include "filesystem.hpp"
#include "lion.hpp"

namespace elona
{

struct music_data
{
    int id;
    fs::path file;
};

ELONA_LION_DEFINE_DB(music_db, music_data, int, u8"music")

extern music_db the_music_db;

} // namespace elona
