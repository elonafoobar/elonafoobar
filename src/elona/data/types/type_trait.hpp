#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct TraitData
{
    SharedId id;
    int legacy_id;
    int trait_type;
    int min;
    int max;
};



ELONA_DEFINE_LUA_DB(TraitDB, TraitData, "core.trait")



extern TraitDB the_trait_db;

} // namespace elona
