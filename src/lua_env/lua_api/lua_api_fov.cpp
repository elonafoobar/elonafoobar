#include "lua_api_fov.hpp"
#include "../../fov.hpp"
#include "../../ui.hpp"

namespace elona
{
namespace lua
{

bool FOV::los(const Position& from, const Position& to)
{
    return FOV::los_xy(from.x, from.y, to.x, to.y);
}

bool FOV::los_xy(int fx, int fy, int tx, int ty)
{
    return elona::fov_los(fx, fy, tx, ty) == 1;
}

bool FOV::you_see(lua_character_handle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    return elona::is_in_fov(chara);
}

bool FOV::you_see_pos(const Position& pos)
{
    return elona::is_in_fov(pos) == 1;
}

bool FOV::you_see_pos_xy(int x, int y)
{
    return elona::is_in_fov(Position(x, y)) == 1;
}

void FOV::refresh()
{
    gmode(2);
    sxfix = 0;
    syfix = 0;
    update_scrolling_info();
    update_slight();
    ui_render_non_hud();
}

void FOV::bind(sol::table& api_table)
{
    api_table.set_function("los", sol::overload(FOV::los, FOV::los_xy));
    api_table.set_function(
        "you_see",
        sol::overload(FOV::you_see_pos, FOV::you_see_pos_xy, FOV::you_see));
    LUA_API_BIND_FUNCTION(api_table, FOV, refresh);
}

} // namespace lua
} // namespace elona
