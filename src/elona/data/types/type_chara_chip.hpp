#pragma once
#include "../../draw.hpp"
#include "../../pic_loader/extent.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct CharaChipData
{
    SharedId id;
    int legacy_id;
    Extent rect;
    CharaChip chip;
    optional<fs::path> filepath;
};



// Used only as an intermediary between registry and initialize_chara_chips().
ELONA_DEFINE_LUA_DB(CharaChipDB, CharaChipData, true, "core.chara_chip")

} // namespace elona
