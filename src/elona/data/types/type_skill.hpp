#pragma once

#include "../base_database.hpp"



namespace elona
{

struct SkillData
{
    data::InstanceId id;
    int integer_id;
    int related_basic_attribute;
    int ability_type;
    int cost;
    int range;
    int difficulty;
};



ELONA_DEFINE_LUA_DB(SkillDB, SkillData, "core.skill")



extern SkillDB the_skill_db;

} // namespace elona
