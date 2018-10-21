#include "type_map.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{

MapDB the_map_db;
const constexpr char* data::LuaLazyCacheTraits<MapDB>::type_id;


MapData MapDB::convert(const lua::ConfigTable& data, const std::string&)
{
    auto legacy_id = data.required<int>("id");
    DATA_REQ(appearance, int);
    DATA_ENUM(
        map_type, mdata_t::MapType, MapTypeTable, mdata_t::MapType::world_map);
    DATA_REQ(outer_map, int);
    DATA_REQ(outer_map_position, sol::table);
    DATA_ENUM(entrance_type, int, MapEntranceTypeTable, 8);
    DATA_ENUM(tile_set, int, MapTilesetTable, 2);
    DATA_REQ(tile_type, int);
    DATA_REQ(base_turn_cost, int);
    DATA_REQ(danger_level, int);
    DATA_REQ(deepest_level, int);
    DATA_REQ(is_indoor, bool);
    DATA_REQ(is_generated_every_time, bool);
    DATA_REQ(default_ai_calm, int);
    DATA_OPT_OR(can_return_to, bool, false);
    DATA_OPT_OR(is_home, bool, false);

    Position outer_map_position_{outer_map_position.get<int>("x"),
                                 outer_map_position.get<int>("y")};

    return MapData{legacy_id,
                   appearance,
                   map_type,
                   outer_map,
                   outer_map_position_,
                   entrance_type,
                   tile_set,
                   tile_type,
                   base_turn_cost,
                   danger_level,
                   deepest_level,
                   is_indoor,
                   is_generated_every_time,
                   default_ai_calm,
                   can_return_to,
                   is_home};
}

} // namespace elona
