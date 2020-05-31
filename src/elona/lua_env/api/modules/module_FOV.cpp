#include "module_FOV.hpp"

#include "../../../fov.hpp"
#include "../../../ui.hpp"
#include "../../api_manager.hpp"
#include "../../handle_manager.hpp"



namespace elona::lua::api::modules::module_FOV
{

/**
 * @luadoc los
 *
 * Checks if there is line of sight between two positions in the current map.
 *
 * @tparam LuaPosition from (const) the position from
 * @tparam LuaPosition to (const) the position to
 * @treturn bool true if there is line of sight between the positions
 */
bool FOV_los(const Position& from, const Position& to)
{
    return elona::fov_los(from, to);
}



bool FOV_los_xy(int fx, int fy, int tx, int ty)
{
    return elona::fov_los({fx, fy}, {tx, ty});
}



/**
 * @luadoc you_see
 *
 * Returns true if the player can see the given character, taking
 * blindness into account.
 *
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the player can see the character
 */
bool FOV_you_see(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return elona::is_in_fov(chara_ref);
}



/**
 * @luadoc you_see
 *
 * Returns true if the player can see the given position, taking
 * blindness into account.
 *
 * @tparam LuaPosition pos (const) a position
 * @treturn bool true if the player can see the position
 */
bool FOV_you_see_pos(const Position& pos)
{
    return elona::is_in_fov(pos) == 1;
}



bool FOV_you_see_pos_xy(int x, int y)
{
    return elona::is_in_fov(Position(x, y)) == 1;
}



/**
 * @luadoc refresh
 *
 * Forces an update of the player's field of view cache.
 * You should run this if you're creating objects inside Lua and
 * expecting them to be visible to the player immediately after, or
 * if you're updating the layout of the map and expecting the
 * player's visible object list to change.
 */
void FOV_refresh()
{
    gmode(2);
    sxfix = 0;
    syfix = 0;
    update_scrolling_info();
    update_slight();
    ui_render_non_hud();
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("los", FOV_los, FOV_los_xy);
    ELONA_LUA_API_BIND_FUNCTION("you_see", FOV_you_see_pos, FOV_you_see_pos_xy, FOV_you_see);
    ELONA_LUA_API_BIND_FUNCTION("refresh", FOV_refresh);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_FOV
