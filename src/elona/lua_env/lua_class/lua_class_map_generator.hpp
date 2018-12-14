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

void create(int, int);

void load_custom(const std::string&);

void set_tileset(int);

bool is_deepest_level();

void generate_nefia();

void set_name(const std::string&);

void set_stair_up_pos(int, int);

void set_stair_down_pos(int, int);

void set_entrance_type(const EnumString&);

void set_no_aggro_refresh(bool);

bool is_first_generation();

void update_quests_in_map();

void mark_quest_targets();

void initialize_world_map();

void place_player();
void place_player_xy(int, int);


void bind(sol::state&);
} // namespace LuaMapGenerator

} // namespace lua
} // namespace elona
