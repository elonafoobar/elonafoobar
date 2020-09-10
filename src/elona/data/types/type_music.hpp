#pragma once
#include "../../filesystem.hpp"
#include "../base_database.hpp"

namespace elona
{

struct MusicData
{
    data::InstanceId id;
    int integer_id;
    fs::path file;
    int volume;
};

ELONA_DEFINE_LUA_DB(MusicDB, MusicData, "core.music")

extern MusicDB the_music_db;

} // namespace elona
