#pragma once
#include "filesystem.hpp"
#include "lion.hpp"

namespace elona
{

struct MusicData
{
    int id;
    fs::path file;
};

ELONA_LION_DEFINE_DB(MusicDB, MusicData, int, u8"music")

extern MusicDB the_music_db;

} // namespace elona
