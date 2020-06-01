#include "class_LuaArea.hpp"

#include "../../../area.hpp"
#include "../../../map.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Area)



namespace elona
{
namespace lua
{

void LuaArea::bind(sol::state& lua)
{
    auto LuaArea = lua.new_usertype<Area>("LuaArea", sol::no_constructor);

    // Properties

    /**
     * @luadoc id field num
     */
    LuaArea.set("id", sol::readonly(&Area::id));

    /**
     * @luadoc type field num
     */
    LuaArea.set("type", &Area::type);

    /**
     * @luadoc position field LuaPosition
     */
    LuaArea.set("position", &Area::position);

    /**
     * @luadoc entrance field num
     */
    LuaArea.set("entrance", &Area::entrance);

    /**
     * @luadoc tile_set field num
     */
    LuaArea.set("tile_set", &Area::tile_set);

    /**
     * @luadoc dungeon_prefix field num
     */
    LuaArea.set("dungeon_prefix", &Area::dungeon_prefix);

    /**
     * @luadoc visited_deepest_level field num
     */
    LuaArea.set("visited_deepest_level", &Area::visited_deepest_level);

    /**
     * @luadoc turn_cost_base field num
     */
    LuaArea.set("turn_cost_base", &Area::turn_cost_base);

    /**
     * @luadoc deepest_level field num
     */
    LuaArea.set("deepest_level", &Area::deepest_level);

    /**
     * @luadoc is_generated_every_time field bool
     */
    LuaArea.set("is_generated_every_time", &Area::is_generated_every_time);

    /**
     * @luadoc default_ai_calm field num
     */
    LuaArea.set("default_ai_calm", &Area::default_ai_calm);

    /**
     * @luadoc appearance field num
     */
    LuaArea.set("appearance", &Area::appearance);

    /**
     * @luadoc danger_level field num
     */
    LuaArea.set("danger_level", &Area::danger_level);

    /**
     * @luadoc tile_type field num
     */
    LuaArea.set("tile_type", &Area::tile_type);

    /**
     * @luadoc has_been_conquered field num
     */
    LuaArea.set("has_been_conquered", &Area::has_been_conquered);

    /**
     * @luadoc is_indoor field bool
     */
    LuaArea.set("is_indoor", &Area::is_indoor);

    /**
     * @luadoc winning_streak_in_arena field num
     */
    LuaArea.set("winning_streak_in_arena", &Area::winning_streak_in_arena);

    /**
     * @luadoc winning_streak_in_pet_arena field num
     */
    LuaArea.set(
        "winning_streak_in_pet_arena", &Area::winning_streak_in_pet_arena);

    /**
     * @luadoc arena_random_seed field num
     */
    LuaArea.set("arena_random_seed", &Area::arena_random_seed);

    /**
     * @luadoc time_of_next_update_of_arena_random_seed field num
     */
    LuaArea.set(
        "time_of_next_update_of_arena_random_seed",
        &Area::time_of_next_update_of_arena_random_seed);

    /**
     * @luadoc time_of_next_arena field num
     */
    LuaArea.set("time_of_next_arena", &Area::time_of_next_arena);

    /**
     * @luadoc time_of_next_rumble field num
     */
    LuaArea.set("time_of_next_rumble", &Area::time_of_next_rumble);

    /**
     * @luadoc quest_town_id field num
     */
    LuaArea.set("quest_town_id", &Area::quest_town_id);

    /**
     * @luadoc christmas_festival field bool
     */
    LuaArea.set("christmas_festival", &Area::christmas_festival);

    /**
     * @luadoc outer_map field num
     */
    LuaArea.set("outer_map", &Area::outer_map);
}

} // namespace lua
} // namespace elona
