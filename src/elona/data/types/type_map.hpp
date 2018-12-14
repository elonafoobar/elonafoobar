#pragma once
#include "../../lua_env/wrapped_function.hpp"
#include "../../mdata.hpp"
#include "../../position.hpp"
#include "../lua_lazy_cache.hpp"

namespace elona
{

struct MapDefData
{
    int id;
    int appearance{};
    mdata_t::MapType map_type;
    SharedId outer_map{};
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
    int quest_town_id{};
    optional<std::string> quest_custom_map{};
    optional<SharedId> deed{};

    bool can_return_to{};
    bool is_fixed{};
    bool reveals_fog{};
    bool shows_floor_count_in_name{};
    bool prevents_teleport{};
    bool prevents_return{};
    bool prevents_domination{};
    bool prevents_monster_ball{};
    bool prevents_building_shelter{};
    bool prevents_random_events{};
    bool villagers_make_snowmen{};

    lua::WrappedFunction generator{};
    optional<lua::WrappedFunction> chara_filter{};
};

ELONA_DEFINE_LUA_DB(MapDefDB, MapDefData, true, "core.map")

extern MapDefDB the_mapdef_db;

} // namespace elona
