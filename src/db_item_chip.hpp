#pragma once
#include "draw.hpp"
#include "lion.hpp"
#include "optional.hpp"
#include "pic_loader/extent.hpp"

namespace elona
{

struct item_chip_data
{
    int id;
    extent rect;
    item_chip_t chip;
    optional<fs::path> filepath;
};

// Used only as an intermediary between registry and initialize_item_chips().
ELONA_LION_DEFINE_DB(item_chip_db, item_chip_data, int, u8"item_chip")

} // namespace elona
