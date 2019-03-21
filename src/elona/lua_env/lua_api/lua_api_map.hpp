#pragma once
#include "lua_api_common.hpp"

namespace elona
{
enum class TileType;

namespace lua
{

/**
 * @luadoc
 *
 * Functions for working with the current map.
 * There is only ever one map loaded at a given time.
 */
namespace LuaApiMap
{
int width();

int height();

sol::optional<std::string> id();

int legacy_id();

int instance_id();

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

void set_feat(const Position&, int, int, int);
void set_feat_xy(int, int, int, int, int);

void clear_feat(const Position&);
void clear_feat_xy(int, int);


void bind(sol::table&);
} // namespace LuaApiMap

} // namespace lua
} // namespace elona
