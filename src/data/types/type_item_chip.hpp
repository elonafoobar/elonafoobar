#pragma once
#include "../../draw.hpp"
#include "../../optional.hpp"
#include "../../pic_loader/extent.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct ItemChipData
{
    int id;
    Extent rect;
    ItemChip chip;
    optional<fs::path> filepath;
};

ELONA_DEFINE_LUA_DB(ItemChipDB, ItemChipData, true, "core.item_chip")

} // namespace elona
