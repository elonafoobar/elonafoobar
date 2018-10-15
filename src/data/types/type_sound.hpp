#pragma once
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct SoundData
{
    int id;
    fs::path file;
};

ELONA_DEFINE_LUA_DB(SoundDB, SoundData, int, "core.sound")

extern SoundDB the_sound_db;

} // namespace elona
