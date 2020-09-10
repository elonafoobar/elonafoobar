#pragma once

#include "../../lua_env/wrapped_function.hpp"
#include "../base_database.hpp"



namespace elona
{

struct BlendingRecipeData
{
    data::InstanceId id;
    int integer_id;
    int type;
    int required_turns;
    int required_hours;
    std::unordered_map<data::InstanceId, int> required_skills;
    // materials
    int number_of_materials;
    bool known;
    bool generated;
    lua::WrappedFunction on_success;
};



ELONA_DEFINE_LUA_DB(
    BlendingRecipeDB,
    BlendingRecipeData,
    "core.blending_recipe")



extern BlendingRecipeDB the_blending_recipe_db;

} // namespace elona
