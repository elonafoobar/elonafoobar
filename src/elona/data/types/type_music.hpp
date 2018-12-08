#pragma once
#include "../../filesystem.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct MusicData
{
    int id;
    fs::path file;
};

ELONA_DEFINE_LUA_DB(MusicDB, MusicData, true, "core.music")

extern MusicDB the_music_db;

} // namespace elona
