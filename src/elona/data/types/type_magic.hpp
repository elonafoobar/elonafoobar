#pragma once
#include "../../lua_env/wrapped_function.hpp"
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct MagicData
{
    SharedId id;
    int legacy_id;
    lua::WrappedFunction callback;
};



ELONA_DEFINE_LUA_DB(MagicDB, MagicData, true, "core.magic")



extern MagicDB the_magic_db;

} // namespace elona
