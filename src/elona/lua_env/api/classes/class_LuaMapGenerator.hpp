#pragma once
#include "../common.hpp"

namespace elona
{
namespace lua
{

/*A
 * @luadoc
 *
 * A class used in map generation.
 */
struct MapGenerator
{
};

namespace LuaMapGenerator
{
int stood_world_map_tile();

bool is_first_generation();

bool is_deepest_level();

void create(int, int);

void load_custom(const std::string&);

void generate_nefia();

void set_name(const std::string&);

void set_tileset(int);

void set_stair_up_pos(int, int);

void set_stair_down_pos(int, int);

void set_entrance_type(const EnumString&);

void set_no_aggro_refresh(bool);

void place_player();
void place_player_xy(int, int);

void update_quests_in_map();

void mark_quest_targets();

void initialize_world_map();


void bind(sol::state&);
} // namespace LuaMapGenerator

} // namespace lua
} // namespace elona
