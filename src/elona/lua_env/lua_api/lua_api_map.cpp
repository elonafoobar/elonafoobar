#include "lua_api_map.hpp"
#include "../../area.hpp"
#include "../../character.hpp"
#include "../../data/types/type_map.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../map.hpp"
#include "../../map_cell.hpp"
#include "../interface.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Returns the current map's width. This is only valid until the map
 * changes.
 * @treturn num the current map's width in tiles
 */
int LuaApiMap::width()
{
    return map_data.width;
}

/**
 * @luadoc
 *
 * Returns the current map's height. This is only valid until the map
 * changes.
 * @treturn num the current map's height in tiles
 */
int LuaApiMap::height()
{
    return map_data.height;
}

/**
 * @luadoc
 *
 * Returns the current map's ID.
 * @treturn[1] string the current map's ID
 * @treturn[2] nil
 */
sol::optional<std::string> LuaApiMap::id()
{
    auto legacy_id = LuaApiMap::legacy_id();

    auto id = the_mapdef_db.get_id_from_legacy(legacy_id);
    if (!legacy_id)
    {
        return sol::nullopt;
    }

    return id->get();
}

/**
 * @luadoc
 *
 * Returns the current map's legacy ID.
 * @treturn[1] num the current map's legacy ID
 * @treturn[2] nil
 */
int LuaApiMap::legacy_id()
{
    return area_data[game_data.current_map].id;
}

/**
 * @luadoc
 *
 * Returns the ID of the current map's instance. There can be more than one
 * instance of a map of the same kind, like player-owned buildings.
 * @treturn num the current map's instance ID
 */
int LuaApiMap::instance_id()
{
    return game_data.current_map;
}

/**
 * @luadoc
 *
 * Returns true if this map is the overworld.
 * @treturn bool
 */
bool LuaApiMap::is_overworld()
{
    return elona::map_data.atlas_number == 0;
}

/**
 * @luadoc
 *
 * Checks if a position is inside the map. It might be blocked by something.
 * @tparam LuaPosition position
 * @treturn bool true if the position is inside the map.
 */
bool LuaApiMap::valid(const Position& position)
{
    return LuaApiMap::valid_xy(position.x, position.y);
}

bool LuaApiMap::valid_xy(int x, int y)
{
    return x >= 0 && y >= 0 && x < LuaApiMap::width() &&
        y < LuaApiMap::height();
}

/**
 * @luadoc
 *
 * Returns true if the map tile at the given position is solid.
 * @tparam LuaPosition position
 * @treturn bool
 */
bool LuaApiMap::is_solid(const Position& position)
{
    return LuaApiMap::is_solid_xy(position.x, position.y);
}

bool LuaApiMap::is_solid_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return true;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return true;
    }

    return elona::chipm(7, elona::cell_data.at(x, y).chip_id_actual) & 4;
}

/**
 * @luadoc
 *
 * Checks if a position is blocked and cannot be reached by walking.
 * @tparam LuaPosition position
 * @treturn bool
 */
bool LuaApiMap::is_blocked(const Position& position)
{
    return LuaApiMap::is_blocked_xy(position.x, position.y);
}

bool LuaApiMap::is_blocked_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return true;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return true;
    }

    elona::cell_check(x, y);
    return cellaccess == 0;
}

/**
 * @luadoc
 *
 * Returns a random position in the current map. It might be blocked by
 * something.
 * @treturn LuaPosition a random position
 */
Position LuaApiMap::random_pos()
{
    return Position{elona::rnd(map_data.width - 1),
                    elona::rnd(map_data.height - 1)};
}

/**
 * @luadoc
 *
 * Generates a random tile ID from the current map's tileset.
 * Tile kinds can contain one of several different tile variations.
 * @tparam Enums.TileKind tile_kind the tile kind to set
 * @treturn num the generated tile ID
 * @see Enums.TileKind
 */
int LuaApiMap::generate_tile(const EnumString& tile_kind)
{
    TileKind tile_kind_value =
        LuaEnums::TileKindTable.ensure_from_string(tile_kind);
    return elona::cell_get_type(tile_kind_value);
}

/**
 * @luadoc
 *
 * Gets the tile type of a tile position.
 * @tparam LuaPosition position
 * @treturn num
 */
int LuaApiMap::get_tile(const Position& position)
{
    return LuaApiMap::get_tile_xy(position.x, position.y);
}

int LuaApiMap::get_tile_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return -1;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return -1;
    }

    return elona::cell_data.at(x, y).chip_id_actual;
}

/**
 * @luadoc
 *
 * Gets the player's memory of a tile position.
 * @tparam LuaPosition position
 * @treturn num
 */
int LuaApiMap::get_memory(const Position& position)
{
    return LuaApiMap::get_memory_xy(position.x, position.y);
}

int LuaApiMap::get_memory_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return -1;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return -1;
    }

    return elona::cell_data.at(x, y).chip_id_memory;
}

/**
 * @luadoc
 *
 * Returns a table containing map feature information at the given tile
 * position.
 * - id: Feature id.
 * - param1: Extra parameter.
 * - param2: Extra parameter.
 * - param3: Extra parameter. (unused)
 * @tparam LuaPosition position
 * @treturn table
 */
sol::table LuaApiMap::get_feat(const Position& position)
{
    return LuaApiMap::get_feat_xy(position.x, position.y);
}

sol::table LuaApiMap::get_feat_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return lua::create_table();
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return lua::create_table();
    }

    auto feats = elona::cell_data.at(x, y).feats;

    auto id = feats % 1000;
    auto param1 = feats / 1000 % 100;
    auto param2 = feats / 100000 % 100;
    auto param3 = feats / 10000000;

    return lua::create_table(
        "id", id, "param1", param1, "param2", param2, "param3", param3);
}

/**
 * @luadoc
 *
 * Returns the ID of the map effect at the given position.
 * @tparam LuaPosition position
 * @treturn num
 */
int LuaApiMap::get_mef(const Position& position)
{
    return LuaApiMap::get_mef_xy(position.x, position.y);
}

int LuaApiMap::get_mef_xy(int x, int y)
{
    if (LuaApiMap::is_overworld())
    {
        return 0;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return 0;
    }

    int index_plus_one = cell_data.at(x, y).mef_index_plus_one;

    if (index_plus_one == 0)
    {
        return 0;
    }

    return mef(0, index_plus_one - 1);
}

/**
 * @luadoc
 *
 * Gets the character standing at a tile position.
 * @tparam LuaPosition position
 * @treturn[opt] LuaCharacter
 */
sol::optional<LuaCharacterHandle> LuaApiMap::get_chara(const Position& position)
{
    return LuaApiMap::get_chara_xy(position.x, position.y);
}

sol::optional<LuaCharacterHandle> LuaApiMap::get_chara_xy(int x, int y)
{
    if (!LuaApiMap::valid_xy(x, y))
    {
        return sol::nullopt;
    }

    int index_plus_one = cell_data.at(x, y).chara_index_plus_one;

    if (index_plus_one == 0)
    {
        return sol::nullopt;
    }

    return lua::handle(cdata[index_plus_one - 1]);
}

/**
 * @luadoc
 *
 * Sets a tile of the current map. Only checks if the position is valid, not
 * things like blocking objects.
 * @tparam LuaPosition position
 * @tparam num id the tile ID to set
 * @usage Map.set_tile(10, 10, Map.generate_tile(Enums.TileKind.Room))
 */
void LuaApiMap::set_tile(const Position& position, int id)
{
    LuaApiMap::set_tile_xy(position.x, position.y, id);
}

void LuaApiMap::set_tile_xy(int x, int y, int id)
{
    if (LuaApiMap::is_overworld())
    {
        return;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return;
    }

    // TODO: check validity of tile ID
    elona::cell_data.at(x, y).chip_id_actual = id;
}

/**
 * @luadoc
 *
 * Sets the player's memory of a tile position to the given tile kind.
 * @tparam LuaPosition position
 * @tparam num id the tile ID to set
 * @usage Map.set_memory(10, 10, Map.generate_tile(Enums.TileKind.Room))
 */
void LuaApiMap::set_memory(const Position& position, int id)
{
    LuaApiMap::set_memory_xy(position.x, position.y, id);
}

void LuaApiMap::set_memory_xy(int x, int y, int id)
{
    if (LuaApiMap::is_overworld())
    {
        return;
    }
    if (!LuaApiMap::valid_xy(x, y))
    {
        return;
    }

    elona::cell_data.at(x, y).chip_id_memory = id;
}

/**
 * @luadoc
 *
 * Sets a feat at the given position.
 * @tparam LuaPosition position (const) the map position
 * @tparam num tile the tile ID of the feat
 * @tparam num param1 a parameter of the feat
 * @tparam num param2 a parameter of the feat
 */
void LuaApiMap::set_feat(
    const Position& position,
    int tile,
    int param1,
    int param2)
{
    LuaApiMap::set_feat_xy(position.x, position.y, tile, param1, param2);
}

void LuaApiMap::set_feat_xy(int x, int y, int tile, int param1, int param2)
{
    cell_featset(x, y, tile, param1, param2);
}

/**
 * @luadoc
 *
 * Clears the feat at the given position.
 * @tparam LuaPosition position (const) the map position
 */
void LuaApiMap::clear_feat(const Position& position)
{
    LuaApiMap::clear_feat_xy(position.x, position.y);
}

void LuaApiMap::clear_feat_xy(int x, int y)
{
    cell_featclear(x, y);
}

void LuaApiMap::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, width);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, height);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, legacy_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, instance_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, is_overworld);
    api_table.set_function(
        "valid", sol::overload(LuaApiMap::valid, LuaApiMap::valid_xy));
    api_table.set_function(
        "is_solid", sol::overload(LuaApiMap::is_solid, LuaApiMap::is_solid_xy));
    api_table.set_function(
        "is_blocked",
        sol::overload(LuaApiMap::is_blocked, LuaApiMap::is_blocked_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, random_pos);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, generate_tile);
    api_table.set_function(
        "get_tile", sol::overload(LuaApiMap::get_tile, LuaApiMap::get_tile_xy));
    api_table.set_function(
        "get_memory",
        sol::overload(LuaApiMap::get_memory, LuaApiMap::get_memory_xy));
    api_table.set_function(
        "get_feat", sol::overload(LuaApiMap::get_feat, LuaApiMap::get_feat_xy));
    api_table.set_function(
        "get_mef", sol::overload(LuaApiMap::get_mef, LuaApiMap::get_mef_xy));
    api_table.set_function(
        "get_chara",
        sol::overload(LuaApiMap::get_chara, LuaApiMap::get_chara_xy));
    api_table.set_function(
        "set_tile", sol::overload(LuaApiMap::set_tile, LuaApiMap::set_tile_xy));
    api_table.set_function(
        "set_memory",
        sol::overload(LuaApiMap::set_memory, LuaApiMap::set_memory_xy));
    api_table.set_function(
        "set_feat", sol::overload(LuaApiMap::set_feat, LuaApiMap::set_feat_xy));
    api_table.set_function(
        "clear_feat",
        sol::overload(LuaApiMap::clear_feat, LuaApiMap::clear_feat_xy));

    /**
     * @luadoc data field LuaMapData
     *
     * [R] The map data for the current map. This contains serialized values
     * controlling various aspects of the current map.
     */
    api_table.set("data", sol::property(&map_data));

    /**
     * @luadoc area function
     *
     * Returns the area in the world map that corresponds to this map.
     */
    api_table.set("area", sol::property([]() { return &area_data.current(); }));
}

} // namespace lua
} // namespace elona
