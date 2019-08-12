#pragma once
#include "../../filesystem.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct MusicData
{
    SharedId id;
    int legacy_id;
    fs::path file;
};

ELONA_DEFINE_LUA_DB(MusicDB, MusicData, "core.music")

extern MusicDB the_music_db;

} // namespace elona
