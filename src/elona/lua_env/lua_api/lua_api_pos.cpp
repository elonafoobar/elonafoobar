#include "lua_api_pos.hpp"

#include "../../position.hpp"

namespace elona
{
namespace lua
{


/**
 * @luadoc
 *
 * Returns the distance between two points.
 * @tparam LuaPosition from (const) the point from
 * @tparam LuaPosition to (const) the point to
 * @treturn num the distance between the points in tiles
 */
int LuaApiPos::dist(const Position& from, const Position& to)
{
    return LuaApiPos::dist_xy(from.x, from.y, to.x, to.y);
}

int LuaApiPos::dist_xy(int fx, int fy, int tx, int ty)
{
    return elona::dist(fx, fy, tx, ty);
}

void LuaApiPos::bind(sol::table& api_table)
{
    api_table.set_function(
        "dist", sol::overload(LuaApiPos::dist, LuaApiPos::dist_xy));
}

} // namespace lua
} // namespace elona
