#include "lua_api_fov.hpp"
#include "../../fov.hpp"
#include "../../ui.hpp"
#include "../api_manager.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Checks if there is line of sight between two positions in the current map.
 * @tparam LuaPosition from (const) the position from
 * @tparam LuaPosition to (const) the position to
 * @treturn bool true if there is line of sight between the positions
 */
bool LuaApiFOV::los(const Position& from, const Position& to)
{
    return LuaApiFOV::los_xy(from.x, from.y, to.x, to.y);
}

bool LuaApiFOV::los_xy(int fx, int fy, int tx, int ty)
{
    return elona::fov_los(fx, fy, tx, ty) == 1;
}

/**
 * @luadoc
 *
 * Returns true if the player can see the given character, taking
 * blindness into account.
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the player can see the character
 */
bool LuaApiFOV::you_see(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return elona::is_in_fov(chara_ref);
}

/**
 * @luadoc you_see
 *
 * Returns true if the player can see the given position, taking
 * blindness into account.
 * @tparam LuaPosition pos (const) a position
 * @treturn bool true if the player can see the position
 */
bool LuaApiFOV::you_see_pos(const Position& pos)
{
    return elona::is_in_fov(pos) == 1;
}

bool LuaApiFOV::you_see_pos_xy(int x, int y)
{
    return elona::is_in_fov(Position(x, y)) == 1;
}

/**
 * @luadoc
 *
 * Forces an update of the player's field of view cache.
 * You should run this if you're creating objects inside Lua and
 * expecting them to be visible to the player immediately after, or
 * if you're updating the layout of the map and expecting the
 * player's visible object list to change.
 */
void LuaApiFOV::refresh()
{
    gmode(2);
    sxfix = 0;
    syfix = 0;
    update_scrolling_info();
    update_slight();
    ui_render_non_hud();
}

void LuaApiFOV::bind(sol::table& api_table)
{
    api_table.set_function(
        "los", sol::overload(LuaApiFOV::los, LuaApiFOV::los_xy));
    api_table.set_function(
        "you_see",
        sol::overload(
            LuaApiFOV::you_see_pos,
            LuaApiFOV::you_see_pos_xy,
            LuaApiFOV::you_see));
    LUA_API_BIND_FUNCTION(api_table, LuaApiFOV, refresh);
}

} // namespace lua
} // namespace elona
