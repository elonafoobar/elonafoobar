#include "lua_api_map.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../map.hpp"
#include "../../map_cell.hpp"

namespace elona
{
namespace lua
{

int LuaApiMap::width()
{
    return map_data.width;
}

int LuaApiMap::height()
{
    return map_data.height;
}

int LuaApiMap::id()
{
    return game_data.current_map;
}

bool LuaApiMap::is_overworld()
{
    return elona::map_data.atlas_number == 0;
}

bool LuaApiMap::valid(const Position& position)
{
    return LuaApiMap::valid_xy(position.x, position.y);
}

bool LuaApiMap::valid_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return false;
    }
    if (x < 0 || y < 0 || x >= LuaApiMap::width() || y >= LuaApiMap::height())
    {
        return false;
    }

    return elona::cell_data.at(x, y).chip_id_actual != 0;
}

bool LuaApiMap::can_access(const Position& position)
{
    return LuaApiMap::can_access_xy(position.x, position.y);
}

bool LuaApiMap::can_access_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return false;
    }
    elona::cell_check(x, y);
    return cellaccess != 0;
}

Position LuaApiMap::bound_within(const Position& position)
{
    int x = clamp(position.x, 0, map_data.width - 1);
    int y = clamp(position.y, 0, map_data.height - 1);
    return Position{x, y};
}

Position LuaApiMap::random_pos()
{
    return LuaApiMap::bound_within(Position{elona::rnd(map_data.width - 1),
                                            elona::rnd(map_data.height - 1)});
}

int LuaApiMap::generate_tile(const EnumString& type_name)
{
    TileKind type = LuaEnums::TileKindTable.ensure_from_string(type_name);
    return elona::cell_get_type(type);
}

void LuaApiMap::set_tile(const Position& position, int type)
{
    LuaApiMap::set_tile_xy(position.x, position.y, type);
}

void LuaApiMap::set_tile_xy(int x, int y, int type)
{
    if (LuaApiMap::is_overworld())
    {
        return;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return;
    }

    elona::cell_data.at(x, y).chip_id_actual = type;
}

void LuaApiMap::set_tile_memory(const Position& position, int type)
{
    LuaApiMap::set_tile_memory_xy(position.x, position.y, type);
}

void LuaApiMap::set_tile_memory_xy(int x, int y, int type)
{
    if (LuaApiMap::is_overworld())
    {
        return;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return;
    }

    elona::cell_data.at(x, y).chip_id_memory = type;
}

void LuaApiMap::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, width);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, height);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, is_overworld);
    api_table.set_function(
        "valid", sol::overload(LuaApiMap::valid, LuaApiMap::valid_xy));
    api_table.set_function(
        "can_access",
        sol::overload(LuaApiMap::can_access, LuaApiMap::can_access_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, bound_within);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, random_pos);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, generate_tile);
    api_table.set_function(
        "set_tile", sol::overload(LuaApiMap::set_tile, LuaApiMap::set_tile_xy));
    api_table.set_function(
        "set_tile_memory",
        sol::overload(
            LuaApiMap::set_tile_memory, LuaApiMap::set_tile_memory_xy));
}

} // namespace lua
} // namespace elona
