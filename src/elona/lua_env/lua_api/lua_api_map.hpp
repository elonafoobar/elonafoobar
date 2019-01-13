#pragma once
#include "lua_api_common.hpp"

namespace elona
{
enum class TileKind;

namespace lua
{

namespace LuaApiMap
{
int width();

int height();

int id();

bool is_overworld();

bool valid(const Position&);
bool valid_xy(int, int);

bool can_access(const Position&);
bool can_access_xy(int, int);

Position bound_within(const Position&);

Position random_pos();

int generate_tile(const EnumString&);

void set_tile(const Position&, int);
void set_tile_xy(int, int, int);

void set_tile_memory(const Position&, int);
void set_tile_memory_xy(int, int, int);


void bind(sol::table&);
} // namespace LuaApiMap

} // namespace lua
} // namespace elona
