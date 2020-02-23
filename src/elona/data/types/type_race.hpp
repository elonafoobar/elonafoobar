#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct RaceData
{
    SharedId id;
    bool is_extra;
    int ordering;
    int male_image;
    int female_image;
    int breed_power;
    int min_age;
    int max_age;
    int height;
    int male_ratio;
    bool is_made_of_rock;
    int melee_attack_type;
    int special_attack_type;
    int dv_multiplier;
    int pv_multiplier;
    std::vector<int> body_parts;
    std::unordered_map<SharedId, int> skills;
    std::unordered_map<SharedId, int> resistances;
};



ELONA_DEFINE_LUA_DB(RaceDB, RaceData, "core.race")



inline RaceDB the_race_db;

} // namespace elona
