#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct ClassData
{
    SharedId id;
    int ordering;
    bool is_extra;
    int item_type;
    int equipment_type;
    std::unordered_map<SharedId, int> skills;
};



ELONA_DEFINE_LUA_DB(ClassDB, ClassData, true, "core.class")



extern ClassDB the_class_db;

} // namespace elona
