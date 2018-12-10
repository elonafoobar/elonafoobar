#include "lua_class_map_generator.hpp"
#include "../../map.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{

int LuaMapGenerator::stood_world_map_tile()
{
    return game_data.stood_world_map_tile;
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

void LuaMapGenerator::place_player()
{
    map_placeplayer();
}


void LuaMapGenerator::bind(sol::state& lua)
{
    auto LuaMapGenerator = lua.create_simple_usertype<MapGenerator>();

    LuaMapGenerator.set("create", &LuaMapGenerator::create);
    LuaMapGenerator.set("load_custom", &LuaMapGenerator::load_custom);
    LuaMapGenerator.set("generate_nefia", &LuaMapGenerator::generate_nefia);
    LuaMapGenerator.set("set_name", &LuaMapGenerator::set_name);
    LuaMapGenerator.set("set_stair_up_pos", &LuaMapGenerator::set_stair_up_pos);
    LuaMapGenerator.set(
        "set_stair_down_pos", &LuaMapGenerator::set_stair_down_pos);
    LuaMapGenerator.set(
        "set_entrance_type", &LuaMapGenerator::set_entrance_type);
    LuaMapGenerator.set("place_player", &LuaMapGenerator::place_player);

    lua.set_usertype("LuaMapGenerator", LuaMapGenerator);
}

} // namespace lua
} // namespace elona
