#include "lua_api_map.hpp"
#include "../../map_cell.hpp"

namespace elona
{
namespace lua
{

int Map::width()
{
    return mdata_map_width;
}

int Map::height()
{
    return mdata_map_height;
}

bool Map::is_overworld()
{
    return elona::mdata_map_atlas_number == 0;
}

bool Map::valid(const position_t& position)
{
    return Map::valid_xy(position.x, position.y);
}

bool Map::valid_xy(int x, int y)
{
    if (Map::is_overworld())
    {
        return false;
    }
    if (x < 0 || y < 0 || x >= Map::width() || y >= Map::height())
    {
        return false;
    }

    return elona::map(x, y, 0) != 0;
}

bool Map::can_access(const position_t& position)
{
    return Map::can_access_xy(position.x, position.y);
}

bool Map::can_access_xy(int x, int y)
{
    if (Map::is_overworld())
    {
        return false;
    }
    elona::cell_check(x, y);
    return cellaccess != 0;
}

position_t Map::bound_within(const position_t& position)
{
    int x = clamp(position.x, 0, mdata_map_width - 1);
    int y = clamp(position.y, 0, mdata_map_height - 1);
    return position_t{x, y};
}

position_t Map::random_pos()
{
    return Map::bound_within(position_t{elona::rnd(mdata_map_width - 1),
                                        elona::rnd(mdata_map_height - 1)});
}

int Map::generate_tile(tile_kind_t type)
{
    return elona::cell_get_type(type);
}

void Map::set_tile(const position_t& position, int type)
{
    Map::set_tile_xy(position.x, position.y, type);
}

void Map::set_tile_xy(int x, int y, int type)
{
    if (Map::is_overworld())
    {
        return;
    }
    if (!Map::valid_xy(x, y))
    {
        return;
    }

    elona::map(x, y, 0) = type;
}

void Map::set_tile_memory(const position_t& position, int type)
{
    Map::set_tile_memory_xy(position.x, position.y, type);
}

void Map::set_tile_memory_xy(int x, int y, int type)
{
    if (Map::is_overworld())
    {
        return;
    }
    if (!Map::valid_xy(x, y))
    {
        return;
    }

    elona::map(x, y, 2) = type;
}

void Map::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Map, width);
    LUA_API_BIND_FUNCTION(api_table, Map, height);
    LUA_API_BIND_FUNCTION(api_table, Map, is_overworld);
    api_table.set_function("valid", sol::overload(Map::valid, Map::valid_xy));
    api_table.set_function(
        "can_access", sol::overload(Map::can_access, Map::can_access_xy));
    LUA_API_BIND_FUNCTION(api_table, Map, bound_within);
    LUA_API_BIND_FUNCTION(api_table, Map, random_pos);
    LUA_API_BIND_FUNCTION(api_table, Map, generate_tile);
    api_table.set_function(
        "set_tile", sol::overload(Map::set_tile, Map::set_tile_xy));
    api_table.set_function(
        "set_tile_memory",
        sol::overload(Map::set_tile_memory, Map::set_tile_memory_xy));
}

} // namespace lua
} // namespace elona
