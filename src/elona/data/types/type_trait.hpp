#pragma once
#include "../base_database.hpp"



namespace elona
{

struct TraitData
{
    data::InstanceId id;
    int integer_id;
    int trait_type;
    int min;
    int max;
};



ELONA_DEFINE_LUA_DB(TraitDB, TraitData, "core.trait")



extern TraitDB the_trait_db;

} // namespace elona
