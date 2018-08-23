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

bool valid(const position_t&);
bool valid_xy(int, int);

bool can_access(const position_t&);
bool can_access_xy(int, int);

position_t bound_within(const position_t&);

position_t random_pos();

int generate_tile(const enum_string&);

void set_tile(const position_t&, int);
void set_tile_xy(int, int, int);

void set_tile_memory(const position_t&, int);
void set_tile_memory_xy(int, int, int);


void bind(sol::table&);
} // namespace Map

} // namespace lua
} // namespace elona
