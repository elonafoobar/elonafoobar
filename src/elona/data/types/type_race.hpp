#pragma once

#include "../base_database.hpp"



namespace elona
{

struct RaceData
{
    data::InstanceId id;
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
    std::vector<data::InstanceId> body_parts;
    std::unordered_map<data::InstanceId, int> skills;
    std::unordered_map<data::InstanceId, int> resistances;
};



ELONA_DEFINE_LUA_DB(RaceDB, RaceData, "core.race")



extern RaceDB the_race_db;

} // namespace elona
