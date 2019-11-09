#include "../../../area.hpp"
#include "../../../map.hpp"
#include "../../../mapgen.hpp"
#include "../../../position.hpp"
#include "../../../quest.hpp"
#include "../../../world.hpp"
#include "../../enums/enums.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::MapGenerator)



/**
 * @luadoc
 *
 * A class used in map generation.
 */
namespace elona::lua::api::classes::class_LuaMapGenerator
{

/**
 * @luadoc stood_world_map_tile
 *
 * Gets the world map tile the player was standing on when they entered the map
 * being generated.
 * @treturn num the tile ID
 */
int LuaMapGenerator_stood_world_map_tile()
{
    return game_data.stood_world_map_tile;
}



/**
 * @luadoc is_first_generation
 *
 * Returns true if the map is being generated for the first time, across all
 * regenerations.
 * @treturn bool
 */
bool LuaMapGenerator_is_first_generation()
{
    return mapupdate == 0;
}



/**
 * @luadoc is_deepest_level
 *
 * Returns true if the current dungeon level is the deepest in this map.
 * @treturn bool
 */
bool LuaMapGenerator_is_deepest_level()
{
    return game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level;
}



/**
 * @luadoc create
 *
 * Creates a blank map of the specified size.
 * @tparam num width
 * @tparam num height
 */
void LuaMapGenerator_create(int width, int height)
{
    map_data.width = width;
    map_data.height = height;
    elona::map_initialize();
}



/**
 * @luadoc load_custom
 *
 * Loads a custom map with the given name.
 * @tparam string map_name
 */
void LuaMapGenerator_load_custom(const std::string& name)
{
    elona::map_init_static_map(name);
}



/**
 * @luadoc generate_nefia
 *
 * Generates a random nefia (dungeon).
 */
void LuaMapGenerator_generate_nefia()
{
    elona::generate_random_nefia();
}



/**
 * @luadoc set_name
 *
 * Sets the created map's name.
 * @tparam string name
 */
void LuaMapGenerator_set_name(const std::string& name)
{
    mdatan(0) = name;
}



/**
 * @luadoc set_tileset
 *
 * Initializes the created map's tileset.
 * @tparam num tileset_id
 */
void LuaMapGenerator_set_tileset(int tileset)
{
    elona::map_tileset(tileset);
}



/**
 * @luadoc set_stair_up_pos
 *
 * Sets the position of the stairs up in the created map.
 * @tparam num x
 * @tparam num y
 */
void LuaMapGenerator_set_stair_up_pos(int x, int y)
{
    map_data.stair_up_pos = y * 1000 + x;
}



/**
 * @luadoc set_stair_down_pos
 *
 * Sets the position of the stairs down in the created map.
 * @tparam num x
 * @tparam num y
 */
void LuaMapGenerator_set_stair_down_pos(int x, int y)
{
    map_data.stair_down_pos = y * 1000 + x;
}



/**
 * @luadoc set_entrance_type
 *
 * Sets the created map's entrance type.
 * @tparam Enums.EntranceType type
 */
void LuaMapGenerator_set_entrance_type(const EnumString& type)
{
    game_data.entrance_type =
        LuaEnums::MapEntranceTypeTable.ensure_from_string(type);
}



/**
 * @luadoc set_no_aggro_refresh
 *
 * Sets the created map's no aggro refresh flag. If true, characters
 * will not have their enemy_id and hate reset after map
 * initialization. Set this flag to true if you change the "enemy_id"
 * or "hate" fields of any characters in the generation function.
 * @tparam bool flag
 */
void LuaMapGenerator_set_no_aggro_refresh(bool flag)
{
    noaggrorefresh = flag ? 1 : 0;
}



/**
 * @luadoc place_player
 *
 * Sets the position of the player based on the entrance type.
 */
void LuaMapGenerator_place_player()
{
    elona::map_place_player_and_allies();
}



/**
 * @luadoc place_player_xy
 *
 * Sets the position of the player to the given coordinates and
 * updates the entrance type accordingly.
 * @tparam num x
 * @tparam num y
 */
void LuaMapGenerator_place_player_xy(int x, int y)
{
    // Set the entrance type to "Specified" as a specific position was
    // requested.
    game_data.entrance_type = 7;

    mapstartx = x;
    mapstarty = y;
    elona::map_place_player_and_allies();
}



/**
 * @luadoc update_quests_in_map
 *
 * Creates new quests for the characters in the created map if necessary.
 */
void LuaMapGenerator_update_quests_in_map()
{
    elona::quest_on_map_initialize();
}



/**
 * @luadoc mark_quest_targets
 *
 * Marks all characters in this map as being enemies and quest targets.
 */
void LuaMapGenerator_mark_quest_targets()
{
    elona::quest_place_target();
}



/**
 * @luadoc initialize_world_map
 *
 * Initializes this map as a world map,
 */
void LuaMapGenerator_initialize_world_map()
{
    elona::initialize_world_map();
}



void bind(sol::state& lua)
{
    auto LuaMapGenerator = lua.new_usertype<MapGenerator>("LuaMapGenerator");

    LuaMapGenerator.set(
        "stood_world_map_tile", &LuaMapGenerator_stood_world_map_tile);
    LuaMapGenerator.set(
        "is_first_generation", &LuaMapGenerator_is_first_generation);
    LuaMapGenerator.set("is_deepest_level", &LuaMapGenerator_is_deepest_level);

    LuaMapGenerator.set("create", &LuaMapGenerator_create);
    LuaMapGenerator.set("load_custom", &LuaMapGenerator_load_custom);
    LuaMapGenerator.set("generate_nefia", &LuaMapGenerator_generate_nefia);
    LuaMapGenerator.set("set_name", &LuaMapGenerator_set_name);
    LuaMapGenerator.set("set_tileset", &LuaMapGenerator_set_tileset);
    LuaMapGenerator.set("set_stair_up_pos", &LuaMapGenerator_set_stair_up_pos);
    LuaMapGenerator.set(
        "set_stair_down_pos", &LuaMapGenerator_set_stair_down_pos);
    LuaMapGenerator.set(
        "set_entrance_type", &LuaMapGenerator_set_entrance_type);
    LuaMapGenerator.set(
        "set_no_aggro_refresh", &LuaMapGenerator_set_no_aggro_refresh);
    LuaMapGenerator.set(
        "place_player",
        sol::overload(
            &LuaMapGenerator_place_player, &LuaMapGenerator_place_player_xy));
    LuaMapGenerator.set(
        "update_quests_in_map", &LuaMapGenerator_update_quests_in_map);
    LuaMapGenerator.set(
        "mark_quest_targets", &LuaMapGenerator_mark_quest_targets);
    LuaMapGenerator.set(
        "initialize_world_map", &LuaMapGenerator_initialize_world_map);
}

} // namespace elona::lua::api::classes::class_LuaMapGenerator
