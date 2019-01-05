#include "lua_api_fov.hpp"
#include "../../fov.hpp"
#include "../../ui.hpp"
#include "../api_manager.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{

bool LuaApiFOV::los(const Position& from, const Position& to)
{
    return LuaApiFOV::los_xy(from.x, from.y, to.x, to.y);
}

bool LuaApiFOV::los_xy(int fx, int fy, int tx, int ty)
{
    return elona::fov_los(fx, fy, tx, ty) == 1;
}

bool LuaApiFOV::you_see(LuaCharacterHandle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    return elona::is_in_fov(chara);
}

bool LuaApiFOV::you_see_pos(const Position& pos)
{
    return elona::is_in_fov(pos) == 1;
}

bool LuaApiFOV::you_see_pos_xy(int x, int y)
{
    return elona::is_in_fov(Position(x, y)) == 1;
}

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
