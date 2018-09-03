#pragma once
#include "draw.hpp"
#include "lion.hpp"
#include "optional.hpp"
#include "pic_loader/extent.hpp"

namespace elona
{

struct ItemChipData
{
    int id;
    Extent rect;
    ItemChip chip;
    optional<fs::path> filepath;
};

// Used only as an intermediary between registry and initialize_item_chips().
ELONA_LION_DEFINE_DB(ItemChipDB, ItemChipData, int, u8"item_chip")

} // namespace elona
