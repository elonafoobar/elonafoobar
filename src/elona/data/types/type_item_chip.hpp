#pragma once
#include "../../draw.hpp"
#include "../../optional.hpp"
#include "../../pic_loader/extent.hpp"
#include "../base_database.hpp"

namespace elona
{

struct ItemChipData
{
    SharedId id;
    int legacy_id;
    Extent rect;
    ItemChip chip;
    optional<fs::path> filepath;
};



ELONA_DEFINE_LUA_DB(ItemChipDB, ItemChipData, "core.item_chip")

} // namespace elona
