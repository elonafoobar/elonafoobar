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

ELONA_LION_DEFINE_DB(MusicDB, music_data, int, u8"music")

extern MusicDB the_music_db;

} // namespace elona
