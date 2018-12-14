#include "lua_class_map_generator.hpp"
#include "../../area.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../map.hpp"
#include "../../mapgen.hpp"
#include "../../position.hpp"
#include "../../quest.hpp"

namespace elona
{
namespace lua
{

int LuaMapGenerator::stood_world_map_tile()
{
    return game_data.stood_world_map_tile;
}

bool LuaMapGenerator::is_first_generation()
{
    return mapupdate == 0;
}

bool LuaMapGenerator::is_deepest_level()
{
    return game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level;
}

void LuaMapGenerator::create(int width, int height)
{
    map_data.width = width;
    map_data.height = height;
    map_initialize();
}

void LuaMapGenerator::load_custom(const std::string& name)
{
    map_initcustom(name);
}

void LuaMapGenerator::generate_nefia()
{
    generate_random_nefia();
}

void LuaMapGenerator::set_name(const std::string& name)
{
    mdatan(0) = name;
}

void LuaMapGenerator::set_tileset(int tileset)
{
    map_tileset(tileset);
}

void LuaMapGenerator::set_stair_up_pos(int x, int y)
{
    map_data.stair_up_pos = y * 1000 + x;
}

void LuaMapGenerator::set_stair_down_pos(int x, int y)
{
    map_data.stair_down_pos = y * 1000 + x;
}

void LuaMapGenerator::set_entrance_type(const EnumString& type)
{
    game_data.entrance_type =
        LuaEnums::MapEntranceTypeTable.ensure_from_string(type);
}

void LuaMapGenerator::set_no_aggro_refresh(bool flag)
{
    noaggrorefresh = flag ? 1 : 0;
}

void LuaMapGenerator::place_player()
{
    map_placeplayer();
}

void LuaMapGenerator::place_player_xy(int x, int y)
{
    // Set the entrance type to "Specified" as a specific position was
    // requested.
    game_data.entrance_type = 7;

    mapstartx = x;
    mapstarty = y;
    map_placeplayer();
}

void LuaMapGenerator::update_quests_in_map()
{
    quest_on_map_initialize();
}

void LuaMapGenerator::mark_quest_targets()
{
    quest_place_target();
}

void LuaMapGenerator::initialize_world_map()
{
    initialize_world_map();
}


void LuaMapGenerator::bind(sol::state& lua)
{
    auto LuaMapGenerator = lua.create_simple_usertype<MapGenerator>();

    LuaMapGenerator.set(
        "stood_world_map_tile", &LuaMapGenerator::stood_world_map_tile);
    LuaMapGenerator.set(
        "is_first_generation", &LuaMapGenerator::is_first_generation);
    LuaMapGenerator.set("is_deepest_level", &LuaMapGenerator::is_deepest_level);

    LuaMapGenerator.set("create", &LuaMapGenerator::create);
    LuaMapGenerator.set("load_custom", &LuaMapGenerator::load_custom);
    LuaMapGenerator.set("generate_nefia", &LuaMapGenerator::generate_nefia);
    LuaMapGenerator.set("set_name", &LuaMapGenerator::set_name);
    LuaMapGenerator.set("set_tileset", &LuaMapGenerator::set_tileset);
    LuaMapGenerator.set("set_stair_up_pos", &LuaMapGenerator::set_stair_up_pos);
    LuaMapGenerator.set(
        "set_stair_down_pos", &LuaMapGenerator::set_stair_down_pos);
    LuaMapGenerator.set(
        "set_entrance_type", &LuaMapGenerator::set_entrance_type);
    LuaMapGenerator.set(
        "set_no_aggro_refresh", &LuaMapGenerator::set_no_aggro_refresh);
    LuaMapGenerator.set(
        "place_player",
        sol::overload(
            &LuaMapGenerator::place_player, &LuaMapGenerator::place_player_xy));
    LuaMapGenerator.set(
        "update_quests_in_map", &LuaMapGenerator::update_quests_in_map);
    LuaMapGenerator.set(
        "mark_quest_targets", &LuaMapGenerator::mark_quest_targets);
    LuaMapGenerator.set(
        "initialize_world_map", &LuaMapGenerator::initialize_world_map);

    lua.set_usertype("LuaMapGenerator", LuaMapGenerator);
}

} // namespace lua
} // namespace elona
