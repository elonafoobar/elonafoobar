#pragma once
#include "lua_api_common.hpp"

namespace elona
{
enum class TileKind;

namespace lua
{

namespace Map
{
int width();

int height();

bool is_overworld();

bool valid(const Position&);
bool valid_xy(int, int);

bool can_access(const Position&);
bool can_access_xy(int, int);

Position bound_within(const Position&);

Position random_pos();

int generate_tile(const enum_string&);

void set_tile(const Position&, int);
void set_tile_xy(int, int, int);

void set_tile_memory(const Position&, int);
void set_tile_memory_xy(int, int, int);


void bind(sol::table&);
} // namespace Map

} // namespace lua
} // namespace elona
