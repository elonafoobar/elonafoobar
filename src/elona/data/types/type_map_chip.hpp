#pragma once
#include "../../optional.hpp"
#include "../../pic_loader/extent.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct MapChip;

enum class ChipKind : int
{
    none = 0,
    rock = 1,
    farm = 2,
    water = 3,
    snow = 4,
    onsen = 5,
    jail_wall = 6,
    sand = 7,
    field = 8,
    boundary = 9,
    shallows = 10
};

enum class ChipWallKind : int
{
    none = 0,
    lower = 1,
    inner = 2,
};

enum class ChipEffect : int
{
    none = 0,
    obstructs_ranged = 1,
    solid_transparent = 4,
    solid = 5,
};

struct MapChip
{
    int id{};
    int atlas{};
    SharedId key{};
    Extent rect{};
    optional<fs::path> filepath;

    int kind{};
    int kind2{};
    int wall_kind{};
    int anime_frame{};
    int unused{};
    int offset_top{};
    int offset_bottom{};
    int effect{};
};

ELONA_DEFINE_LUA_DB(MapChipDB, MapChip, true, "core.map_chip")

} // namespace elona
