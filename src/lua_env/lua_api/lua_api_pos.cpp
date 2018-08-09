#include "lua_api_pos.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{


int Pos::dist(const position_t& from, const position_t& to)
{
    return Pos::dist_xy(from.x, from.y, to.x, to.y);
}

int Pos::dist_xy(int fx, int fy, int tx, int ty)
{
    return elona::dist(fx, fy, tx, ty);
}

void Pos::bind(sol::table& api_table)
{
    api_table.set_function("dist", sol::overload(Pos::dist, Pos::dist_xy));
}

} // namespace lua
} // namespace elona
