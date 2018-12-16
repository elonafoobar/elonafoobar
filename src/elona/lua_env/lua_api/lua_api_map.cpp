#include "lua_api_map.hpp"
#include "../../area.hpp"
#include "../../data/types/type_map.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../map.hpp"
#include "../../map_cell.hpp"
#include "../../mapgen.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Returns the current map's width. This is only valid until the map changes.
 * @treturn num the current map's width in tiles
 */
int LuaApiMap::width()
{
    return map_data.width;
}

/**
 * @luadoc
 *
 * Returns the current map's height. This is only valid until the map changes.
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
 * Returns the current dungeon level.
 * TODO: unify with World.data or Map.data
 */
int LuaApiMap::current_dungeon_level()
{
    return game_data.current_dungeon_level;
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
 * @tparam LuaPosition position (const) the map position
 * @treturn bool true if the position is inside the map.
 */
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

/**
 * @luadoc
 *
 * Checks if a position is accessable by walking.
 * @tparam LuaPosition position (const) the map position
 * @treturn bool true if the position is accessable by walking
 */
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

/**
 * @luadoc
 *
 * Given a position, returns a position that is bounded within the current map.
 * @tparam LuaPosition position (const) the map position
 * @treturn LuaPosition the bounded position
 */
Position LuaApiMap::bound_within(const Position& position)
{
    int x = clamp(position.x, 0, map_data.width - 1);
    int y = clamp(position.y, 0, map_data.height - 1);
    return Position{x, y};
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
    return LuaApiMap::bound_within(Position{elona::rnd(map_data.width - 1),
                                            elona::rnd(map_data.height - 1)});
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
 * Returns the type of chip for the given tile kind.
 */
int LuaApiMap::chip_type(int tile_id)
{
    return elona::chipm(0, tile_id);
}

/**
 * @luadoc
 *
 * Sets a tile of the current map. Only checks if the position is valid, not
 * things like blocking objects.
 * @tparam LuaPosition position (const) the map position
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
 * @tparam LuaPosition position (const) the map position
 * @tparam num id the tile ID to set
 * @usage Map.set_tile_memory(10, 10, Map.generate_tile(Enums.TileKind.Room))
 */
void LuaApiMap::set_tile_memory(const Position& position, int id)
{
    LuaApiMap::set_tile_memory_xy(position.x, position.y, id);
}

void LuaApiMap::set_tile_memory_xy(int x, int y, int id)
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


/**
 * @ luadoc
 *
 * Randomly sprays the map with the given tile type;
 */
void LuaApiMap::spray_tile(int tile, int amount)
{
    elona::map_randomtile(tile, amount);
}

void LuaApiMap::travel_to(const std::string& map_id)
{
    LuaApiMap::travel_to_with_level(map_id, 1);
}

void LuaApiMap::travel_to_with_level(const std::string& map_id, int level)
{
    auto map = the_mapdef_db[map_id];

    if (!map)
    {
        throw sol::error{"No such map '"s + map_id + "'."s};
    }

    std::cerr << "prev: " << game_data.previous_map2
              << " cur: " << game_data.current_map << std::endl;

    game_data.player_x_on_map_leave = cdata.player().position.x;
    game_data.player_y_on_map_leave = cdata.player().position.y;
    game_data.previous_x = cdata.player().position.x;
    game_data.previous_y = cdata.player().position.y;

    // Set up the outer map of the map traveled to, such that the player will
    // appear on top the map's area when they leave via the map's edge.
    if (map->map_type != mdata_t::MapType::world_map)
    {
        auto outer_map = the_mapdef_db[map->outer_map];

        if (outer_map)
        {
            game_data.previous_map2 = outer_map->id;
            game_data.previous_dungeon_level = 1;
            game_data.pc_x_in_world_map = map->outer_map_position.x;
            game_data.pc_y_in_world_map = map->outer_map_position.y;
            game_data.destination_outer_map = outer_map->id;
        }
    }
    else
    {
        game_data.previous_map2 = map->id;
        game_data.previous_dungeon_level = 1;
        game_data.destination_outer_map = map->id;
    }

    map_prepare_for_travel(map->id, level);
    exit_map();
    initialize_map();
    std::cerr << "prevnow: " << game_data.previous_map2
              << " cur: " << game_data.current_map << std::endl;
}

void LuaApiMap::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, width);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, height);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, legacy_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, instance_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, is_overworld);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, current_dungeon_level);
    api_table.set_function(
        "valid", sol::overload(LuaApiMap::valid, LuaApiMap::valid_xy));
    api_table.set_function(
        "can_access",
        sol::overload(LuaApiMap::can_access, LuaApiMap::can_access_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, bound_within);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, random_pos);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, generate_tile);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMap, chip_type);
    api_table.set_function(
        "set_tile", sol::overload(LuaApiMap::set_tile, LuaApiMap::set_tile_xy));
    api_table.set_function(
        "set_tile_memory",
        sol::overload(
            LuaApiMap::set_tile_memory, LuaApiMap::set_tile_memory_xy));
    api_table.set_function(
        "set_feat", sol::overload(LuaApiMap::set_feat, LuaApiMap::set_feat_xy));
    api_table.set_function(
        "clear_feat",
        sol::overload(LuaApiMap::clear_feat, LuaApiMap::clear_feat_xy));
    LUA_API_BIND_FUNCTION(api_table, Map, spray_tile);
    api_table.set_function(
        "travel_to",
        sol::overload(LuaApiMap::travel_to, LuaApiMap::travel_to_with_level));

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
