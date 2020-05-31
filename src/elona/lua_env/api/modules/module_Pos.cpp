#include "module_Pos.hpp"

#include "../../../position.hpp"



namespace elona::lua::api::modules::module_Pos
{

/**
 * @luadoc dist
 *
 * Returns the distance between two points.
 *
 * @tparam LuaPosition from (const) the point from
 * @tparam LuaPosition to (const) the point to
 * @treturn num the distance between the points in tiles
 */
int Pos_dist(const Position& from, const Position& to)
{
    return dist(from.x, from.y, to.x, to.y);
}



int Pos_dist_xy(int fx, int fy, int tx, int ty)
{
    return dist(fx, fy, tx, ty);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("dist", Pos_dist, Pos_dist_xy);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Pos
