#include "lua_class_area.hpp"
#include "../../area.hpp"
#include "../../map.hpp"

namespace elona
{
namespace lua
{

void LuaArea::bind(sol::state& lua)
{
    auto LuaArea = lua.create_simple_usertype<Area>();
    LuaArea.set("new", sol::no_constructor);

    // Properties

    LuaArea.set("id", sol::readonly(&Area::id));
    LuaArea.set("type", &Area::type);
    LuaArea.set("position", &Area::position);
    LuaArea.set("entrance", &Area::entrance);
    LuaArea.set("tile_set", &Area::tile_set);
    LuaArea.set("dungeon_prefix", &Area::dungeon_prefix);
    LuaArea.set("visited_deepest_level", &Area::visited_deepest_level);
    LuaArea.set("turn_cost_base", &Area::turn_cost_base);
    LuaArea.set("deepest_level", &Area::deepest_level);
    LuaArea.set("is_generated_every_time", &Area::is_generated_every_time);
    LuaArea.set("default_ai_calm", &Area::default_ai_calm);
    LuaArea.set("appearance", &Area::appearance);
    LuaArea.set("danger_level", &Area::danger_level);
    LuaArea.set("tile_type", &Area::tile_type);
    LuaArea.set("has_been_conquered", &Area::has_been_conquered);
    LuaArea.set("is_indoor", &Area::is_indoor);
    LuaArea.set("winning_streak_in_arena", &Area::winning_streak_in_arena);
    LuaArea.set(
        "winning_streak_in_pet_arena", &Area::winning_streak_in_pet_arena);
    LuaArea.set("arena_random_seed", &Area::arena_random_seed);
    LuaArea.set(
        "time_of_next_update_of_arena_random_seed",
        &Area::time_of_next_update_of_arena_random_seed);
    LuaArea.set("time_of_next_arena", &Area::time_of_next_arena);
    LuaArea.set("time_of_next_rumble", &Area::time_of_next_rumble);
    LuaArea.set("quest_town_id", &Area::quest_town_id);
    LuaArea.set("christmas_festival", &Area::christmas_festival);
    LuaArea.set("outer_map", &Area::outer_map);

    lua.set_usertype("LuaArea", LuaArea);
}

} // namespace lua
} // namespace elona
