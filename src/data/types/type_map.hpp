#pragma once
#include "../../mdata.hpp"
#include "../../position.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct MapData
{
    int id;
    int appearance{};
    mdata_t::MapType map_type;
    int outer_map{};
    Position outer_map_position{};
    int entrance_type{};
    int tile_set{};
    int tile_type{};
    int base_turn_cost{};
    int danger_level{};
    int deepest_level{};
    bool is_indoor{};
    bool is_generated_every_time{};
    int default_ai_calm{};
    bool can_return_to{};
    bool is_home{};
};

ELONA_DEFINE_LUA_DB(MapDB, MapData, true, "core.map")

extern MapDB the_map_db;

} // namespace elona
