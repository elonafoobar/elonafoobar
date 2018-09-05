#pragma once
#include "draw.hpp"
#include "lion.hpp"
#include "pic_loader/extent.hpp"

namespace elona
{

struct CharaChipData
{
    int id;
    Extent rect;
    CharaChip chip;
    optional<fs::path> filepath;
};

// Used only as an intermediary between registry and initialize_chara_chips().
ELONA_LION_DEFINE_DB(CharaChipDB, CharaChipData, int, u8"chara_chip")

} // namespace elona
