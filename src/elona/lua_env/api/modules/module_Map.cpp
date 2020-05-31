#include "module_Map.hpp"

#include "../../../area.hpp"
#include "../../../character.hpp"
#include "../../../data/types/type_map.hpp"
#include "../../../initialize_map.hpp"
#include "../../../map.hpp"
#include "../../../map_cell.hpp"
#include "../../../mapgen.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"



namespace elona::lua::api::modules::module_Map
{

/**
 * @luadoc width
 *
 * Returns the current map's width. This is only valid until the map
 * changes.
 *
 * @treturn num the current map's width in tiles
 */
int Map_width()
{
    return map_data.width;
}



/**
 * @luadoc height
 *
 * Returns the current map's height. This is only valid until the map
 * changes.
 *
 * @treturn num the current map's height in tiles
 */
int Map_height()
{
    return map_data.height;
}



/**
 * @luadoc legacy_id
 *
 * Returns the current map's legacy ID.
 *
 * @treturn[1] num the current map's legacy ID
 * @treturn[2] nil
 */
int Map_legacy_id()
{
    return area_data[game_data.current_map].id;
}



/**
 * @luadoc id
 *
 * Returns the current map's ID.
 *
 * @treturn[1] string the current map's ID
 * @treturn[2] nil
 */
sol::optional<std::string> Map_id()
{
    auto legacy_id = Map_legacy_id();

    auto id = the_mapdef_db.get_id_from_legacy(legacy_id);
    if (!legacy_id)
    {
        return sol::nullopt;
    }

    return id->get();
}



/**
 * @luadoc instance_id
 *
 * Returns the ID of the current map's instance. There can be more than one
 * instance of a map of the same kind, like player-owned buildings.
 *
 * @treturn num the current map's instance ID
 */
int Map_instance_id()
{
    return game_data.current_map;
}



/**
 * @luadoc current_dungeon_level
 *
 * Returns the current dungeon level.
 * TODO: unify with World.data or Map.data
 */
int Map_current_dungeon_level()
{
    return game_data.current_dungeon_level;
}



/**
 * @luadoc is_overworld
 *
 * Returns true if this map is the overworld.
 *
 * @treturn bool
 */
bool Map_is_overworld()
{
    return elona::map_data.atlas_number == 0;
}



bool Map_valid_xy(int x, int y)
{
    return x >= 0 && y >= 0 && x < Map_width() && y < Map_height();
}



/**
 * @luadoc valid
 *
 * Checks if a position is inside the map. It might be blocked by something.
 *
 * @tparam LuaPosition position
 * @treturn bool true if the position is inside the map.
 */
bool Map_valid(const Position& position)
{
    return Map_valid_xy(position.x, position.y);
}



bool Map_is_solid_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return true;
    }
    if (!Map_valid_xy(x, y))
    {
        return true;
    }

    return elona::chip_data.for_cell(x, y).effect & 4;
}



/**
 * @luadoc is_solid
 *
 * Returns true if the map tile at the given position is solid.
 *
 * @tparam LuaPosition position
 * @treturn bool
 */
bool Map_is_solid(const Position& position)
{
    return Map_is_solid_xy(position.x, position.y);
}



bool Map_is_blocked_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return true;
    }
    if (!Map_valid_xy(x, y))
    {
        return true;
    }

    elona::cell_check(x, y);
    return cellaccess == 0;
}



/**
 * @luadoc is_blocked
 *
 * Checks if a position is blocked and cannot be reached by walking.
 *
 * @tparam LuaPosition position
 * @treturn bool
 */
bool Map_is_blocked(const Position& position)
{
    return Map_is_blocked_xy(position.x, position.y);
}



/**
 * @luadoc random_pos
 *
 * Returns a random position in the current map. It might be blocked by
 * something.
 *
 * @treturn LuaPosition a random position
 */
Position Map_random_pos()
{
    return Position{
        elona::rnd(map_data.width - 1), elona::rnd(map_data.height - 1)};
}



/**
 * @luadoc generate_tile
 *
 * Generates a random tile ID from the current map's tileset.
 * Tile kinds can contain one of several different tile variations.
 *
 * @tparam Enums.TileKind tile_kind the tile kind to set
 * @treturn num the generated tile ID
 * @see Enums.TileKind
 */
int Map_generate_tile(const EnumString& tile_kind)
{
    TileKind tile_kind_value =
        LuaEnums::TileKindTable.ensure_from_string(tile_kind);
    return elona::cell_get_type(tile_kind_value);
}



/**
 * @luadoc chip_type
 *
 * Returns the type of chip for the given tile kind.
 */
int Map_chip_type(int tile_id)
{
    return elona::chip_data[tile_id].kind;
}



int Map_get_tile_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return -1;
    }
    if (!Map_valid_xy(x, y))
    {
        return -1;
    }

    return elona::cell_data.at(x, y).chip_id_actual;
}



/**
 * @luadoc get_tile
 *
 * Gets the tile type of a tile position.
 *
 * @tparam LuaPosition position
 * @treturn num
 */
int Map_get_tile(const Position& position)
{
    return Map_get_tile_xy(position.x, position.y);
}



int Map_get_memory_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return -1;
    }
    if (!Map_valid_xy(x, y))
    {
        return -1;
    }

    return elona::cell_data.at(x, y).chip_id_memory;
}



/**
 * @luadoc get_memory
 *
 * Gets the player's memory of a tile position.
 *
 * @tparam LuaPosition position
 * @treturn num
 */
int Map_get_memory(const Position& position)
{
    return Map_get_memory_xy(position.x, position.y);
}



sol::table Map_get_feat_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return lua::create_table();
    }
    if (!Map_valid_xy(x, y))
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
 * @luadoc get_feat
 *
 * Returns a table containing map feature information at the given tile
 * position.
 * - id: Feature id.
 * - param1: Extra parameter.
 * - param2: Extra parameter.
 * - param3: Extra parameter. (unused)
 *
 * @tparam LuaPosition position
 * @treturn table
 */
sol::table Map_get_feat(const Position& position)
{
    return Map_get_feat_xy(position.x, position.y);
}



int Map_get_mef_xy(int x, int y)
{
    if (Map_is_overworld())
    {
        return 0;
    }
    if (!Map_valid_xy(x, y))
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
 * @luadoc get_mef
 *
 * Returns the ID of the map effect at the given position.
 *
 * @tparam LuaPosition position
 * @treturn num
 */
int Map_get_mef(const Position& position)
{
    return Map_get_mef_xy(position.x, position.y);
}



sol::optional<LuaCharacterHandle> Map_get_chara_xy(int x, int y)
{
    if (!Map_valid_xy(x, y))
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
 * @luadoc get_chara
 *
 * Gets the character standing at a tile position.
 *
 * @tparam LuaPosition position
 * @treturn[opt] LuaCharacter
 */
sol::optional<LuaCharacterHandle> Map_get_chara(const Position& position)
{
    return Map_get_chara_xy(position.x, position.y);
}



void Map_set_tile_xy(int x, int y, int id)
{
    if (Map_is_overworld())
    {
        return;
    }
    if (!Map_valid_xy(x, y))
    {
        return;
    }

    // TODO: check validity of tile ID
    elona::cell_data.at(x, y).chip_id_actual = id;
}



/**
 * @luadoc set_tile
 *
 * Sets a tile of the current map. Only checks if the position is valid, not
 * things like blocking objects.
 *
 * @tparam LuaPosition position
 * @tparam num id the tile ID to set
 * @usage Map.set_tile(10, 10, Map.generate_tile(Enums.TileKind.Room))
 */
void Map_set_tile(const Position& position, int id)
{
    Map_set_tile_xy(position.x, position.y, id);
}



void Map_set_memory_xy(int x, int y, int id)
{
    if (Map_is_overworld())
    {
        return;
    }
    if (!Map_valid_xy(x, y))
    {
        return;
    }

    elona::cell_data.at(x, y).chip_id_memory = id;
}



/**
 * @luadoc set_memory
 *
 * Sets the player's memory of a tile position to the given tile kind.
 *
 * @tparam LuaPosition position
 * @tparam num id the tile ID to set
 * @usage Map.set_memory(10, 10, Map.generate_tile(Enums.TileKind.Room))
 */
void Map_set_memory(const Position& position, int id)
{
    Map_set_memory_xy(position.x, position.y, id);
}



void Map_set_feat_xy(int x, int y, int tile, int param1, int param2)
{
    cell_featset(x, y, tile, param1, param2);
}



/**
 * @luadoc set_feat
 *
 * Sets a feat at the given position.
 *
 * @tparam LuaPosition position (const) the map position
 * @tparam num tile the tile ID of the feat
 * @tparam num param1 a parameter of the feat
 * @tparam num param2 a parameter of the feat
 */
void Map_set_feat(const Position& position, int tile, int param1, int param2)
{
    Map_set_feat_xy(position.x, position.y, tile, param1, param2);
}



void Map_clear_feat_xy(int x, int y)
{
    cell_featclear(x, y);
}



/**
 * @luadoc clear_feat
 *
 * Clears the feat at the given position.
 *
 * @tparam LuaPosition position (const) the map position
 */
void Map_clear_feat(const Position& position)
{
    Map_clear_feat_xy(position.x, position.y);
}



/**
 * @luadoc spray_tile
 *
 * Randomly sprays the map with the given tile type;
 */
void Map_spray_tile(int tile, int amount)
{
    elona::map_randomtile(tile, amount);
}



void Map_travel_to_with_level(const std::string& map_id, int level)
{
    auto map = the_mapdef_db.ensure(data::InstanceId{map_id});

    game_data.player_x_on_map_leave = cdata.player().position.x;
    game_data.player_y_on_map_leave = cdata.player().position.y;
    game_data.previous_x = cdata.player().position.x;
    game_data.previous_y = cdata.player().position.y;

    // Set up the outer map of the map traveled to, such that the player will
    // appear on top the map's area when they leave via the map's edge.
    if (map.map_type != mdata_t::MapType::world_map)
    {
        auto outer_map = the_mapdef_db[map.outer_map];

        if (outer_map)
        {
            game_data.previous_map2 = outer_map->legacy_id;
            game_data.previous_dungeon_level = 1;
            game_data.pc_x_in_world_map = map.outer_map_position.x;
            game_data.pc_y_in_world_map = map.outer_map_position.y;
            game_data.destination_outer_map = outer_map->legacy_id;
        }
    }
    else
    {
        game_data.previous_map2 = map.legacy_id;
        game_data.previous_dungeon_level = 1;
        game_data.destination_outer_map = map.legacy_id;
    }

    map_prepare_for_travel(map.legacy_id, level);
    exit_map();
    initialize_map();
}



void Map_travel_to(const std::string& map_id)
{
    Map_travel_to_with_level(map_id, 1);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("width", Map_width);
    ELONA_LUA_API_BIND_FUNCTION("height", Map_height);
    ELONA_LUA_API_BIND_FUNCTION("id", Map_id);
    ELONA_LUA_API_BIND_FUNCTION("legacy_id", Map_legacy_id);
    ELONA_LUA_API_BIND_FUNCTION("instance_id", Map_instance_id);
    ELONA_LUA_API_BIND_FUNCTION("is_overworld", Map_is_overworld);
    ELONA_LUA_API_BIND_FUNCTION("current_dungeon_level", Map_current_dungeon_level);
    ELONA_LUA_API_BIND_FUNCTION("valid", Map_valid, Map_valid_xy);
    ELONA_LUA_API_BIND_FUNCTION("is_solid", Map_is_solid, Map_is_solid_xy);
    ELONA_LUA_API_BIND_FUNCTION("is_blocked", Map_is_blocked, Map_is_blocked_xy);
    ELONA_LUA_API_BIND_FUNCTION("random_pos", Map_random_pos);
    ELONA_LUA_API_BIND_FUNCTION("generate_tile", Map_generate_tile);
    ELONA_LUA_API_BIND_FUNCTION("chip_type", Map_chip_type);
    ELONA_LUA_API_BIND_FUNCTION("get_tile", Map_get_tile, Map_get_tile_xy);
    ELONA_LUA_API_BIND_FUNCTION("get_memory", Map_get_memory, Map_get_memory_xy);
    ELONA_LUA_API_BIND_FUNCTION("get_feat", Map_get_feat, Map_get_feat_xy);
    ELONA_LUA_API_BIND_FUNCTION("get_mef", Map_get_mef, Map_get_mef_xy);
    ELONA_LUA_API_BIND_FUNCTION("get_chara", Map_get_chara, Map_get_chara_xy);
    ELONA_LUA_API_BIND_FUNCTION("set_tile", Map_set_tile, Map_set_tile_xy);
    ELONA_LUA_API_BIND_FUNCTION("set_memory", Map_set_memory, Map_set_memory_xy);
    ELONA_LUA_API_BIND_FUNCTION("set_feat", Map_set_feat, Map_set_feat_xy);
    ELONA_LUA_API_BIND_FUNCTION("clear_feat", Map_clear_feat, Map_clear_feat_xy);
    ELONA_LUA_API_BIND_FUNCTION("spray_tile", Map_spray_tile);
    ELONA_LUA_API_BIND_FUNCTION("travel_to", Map_travel_to, Map_travel_to_with_level);

    /**
     * @luadoc data field LuaMapData
     *
     * [R] The map data for the current map. This contains serialized values
     * controlling various aspects of the current map.
     */
    api_table.set("data", &map_data);

    /**
     * @luadoc area function
     *
     * Returns the area in the world map that corresponds to this map.
     */
    api_table.set("area", sol::property([]() { return &area_data.current(); }));

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Map
