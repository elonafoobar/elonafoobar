#pragma once
#include "../common.hpp"

namespace elona
{
enum class TileKind;
struct MapData;

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

int current_dungeon_level();

bool is_overworld();

bool valid(const Position&);
bool valid_xy(int, int);

bool is_solid(const Position&);
bool is_solid_xy(int, int);

bool is_blocked(const Position&);
bool is_blocked_xy(int, int);

Position random_pos();

int generate_tile(const EnumString&);

int chip_type(int);

int get_tile(const Position&);
int get_tile_xy(int, int);

int get_memory(const Position&);
int get_memory_xy(int, int);

sol::table get_feat(const Position&);
sol::table get_feat_xy(int, int);

int get_mef(const Position&);
int get_mef_xy(int, int);

sol::optional<LuaCharacterHandle> get_chara(const Position&);
sol::optional<LuaCharacterHandle> get_chara_xy(int, int);

void set_tile(const Position&, int);
void set_tile_xy(int, int, int);

void set_memory(const Position&, int);
void set_memory_xy(int, int, int);

void set_feat(const Position&, int, int, int);
void set_feat_xy(int, int, int, int, int);

void clear_feat(const Position&);
void clear_feat_xy(int, int);

void spray_tile(int, int);

void travel_to(const std::string&);
void travel_to_with_level(const std::string&, int);


void bind(sol::table&);
} // namespace LuaApiMap

} // namespace lua
} // namespace elona
