#pragma once
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

struct MapGenerator
{
};

namespace LuaMapGenerator
{
int stood_world_map_tile();

void create(int width, int height);

void load_custom(const std::string& name);

void set_tileset(int tileset);

bool is_deepest_level();

void generate_nefia();

void set_name(const std::string& name);

void set_stair_up_pos(int x, int y);

void set_stair_down_pos(int x, int y);

void set_entrance_type(const EnumString& type);

bool is_first_generation();

void initialize_world_map();

void place_player();


void bind(sol::state&);
} // namespace LuaMapGenerator

} // namespace lua
} // namespace elona
