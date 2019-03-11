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

    /**
     * @luadoc field id num
     */
    LuaArea.set("id", sol::readonly(&Area::id));

    /**
     * @luadoc field type num
     */
    LuaArea.set("type", &Area::type);

    /**
     * @luadoc field position num
     */
    LuaArea.set("position", &Area::position);

    /**
     * @luadoc field entrance num
     */
    LuaArea.set("entrance", &Area::entrance);

    /**
     * @luadoc field tile_set num
     */
    LuaArea.set("tile_set", &Area::tile_set);

    /**
     * @luadoc field dungeon_prefix num
     */
    LuaArea.set("dungeon_prefix", &Area::dungeon_prefix);

    /**
     * @luadoc field visited_deepest_level num
     */
    LuaArea.set("visited_deepest_level", &Area::visited_deepest_level);

    /**
     * @luadoc field turn_cost_base num
     */
    LuaArea.set("turn_cost_base", &Area::turn_cost_base);

    /**
     * @luadoc field deepest_level num
     */
    LuaArea.set("deepest_level", &Area::deepest_level);

    /**
     * @luadoc field is_generated_every_time bool
     */
    LuaArea.set("is_generated_every_time", &Area::is_generated_every_time);

    /**
     * @luadoc field default_ai_calm num
     */
    LuaArea.set("default_ai_calm", &Area::default_ai_calm);

    /**
     * @luadoc field appearance num
     */
    LuaArea.set("appearance", &Area::appearance);

    /**
     * @luadoc field danger_level num
     */
    LuaArea.set("danger_level", &Area::danger_level);

    /**
     * @luadoc field tile_type num
     */
    LuaArea.set("tile_type", &Area::tile_type);

    /**
     * @luadoc field has_been_conquered num
     */
    LuaArea.set("has_been_conquered", &Area::has_been_conquered);

    /**
     * @luadoc field is_indoor bool
     */
    LuaArea.set("is_indoor", &Area::is_indoor);

    /**
     * @luadoc field winning_streak_in_arena num
     */
    LuaArea.set("winning_streak_in_arena", &Area::winning_streak_in_arena);

    /**
     * @luadoc field winning_streak_in_pet_arena num
     */
    LuaArea.set(
        "winning_streak_in_pet_arena", &Area::winning_streak_in_pet_arena);

    /**
     * @luadoc field arena_random_seed num
     */
    LuaArea.set("arena_random_seed", &Area::arena_random_seed);

    /**
     * @luadoc field time_of_next_update_of_arena_random_seed num
     */
    LuaArea.set(
        "time_of_next_update_of_arena_random_seed",
        &Area::time_of_next_update_of_arena_random_seed);

    /**
     * @luadoc field time_of_next_arena num
     */
    LuaArea.set("time_of_next_arena", &Area::time_of_next_arena);

    /**
     * @luadoc field time_of_next_rumble num
     */
    LuaArea.set("time_of_next_rumble", &Area::time_of_next_rumble);

    /**
     * @luadoc field quest_town_id num
     */
    LuaArea.set("quest_town_id", &Area::quest_town_id);

    /**
     * @luadoc field christmas_festival bool
     */
    LuaArea.set("christmas_festival", &Area::christmas_festival);

    /**
     * @luadoc field outer_map num
     */
    LuaArea.set("outer_map", &Area::outer_map);

    lua.set_usertype("LuaArea", LuaArea);
}

} // namespace lua
} // namespace elona
