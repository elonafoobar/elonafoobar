#include "type_map.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{

MapDefDB the_mapdef_db;
const constexpr char* data::LuaLazyCacheTraits<MapDefDB>::type_id;



MapDefData MapDefDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
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
    DATA_OPT_OR(quest_town_id, int, 0);

    DATA_OPT_OR(can_return_to, bool, false);
    DATA_OPT_OR(is_fixed, bool, true);
    DATA_OPT_OR(reveals_fog, bool, false);
    DATA_OPT_OR(shows_floor_count_in_name, bool, false);
    DATA_OPT_OR(prevents_teleport, bool, false);
    DATA_OPT_OR(prevents_return, bool, false);
    DATA_OPT_OR(prevents_domination, bool, false);
    DATA_OPT_OR(prevents_monster_ball, bool, false);
    DATA_OPT_OR(prevents_building_shelter, bool, false);
    DATA_OPT_OR(prevents_random_events, bool, false);
    DATA_OPT_OR(villagers_make_snowmen, bool, false);

    Position outer_map_position_{outer_map_position.get<int>("x"),
                                 outer_map_position.get<int>("y")};

    return MapDefData{SharedId{id},
                      legacy_id,
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
                      quest_town_id,

                      can_return_to,
                      is_fixed,
                      reveals_fog,
                      shows_floor_count_in_name,
                      prevents_teleport,
                      prevents_return,
                      prevents_domination,
                      prevents_monster_ball,
                      prevents_building_shelter,
                      prevents_random_events,
                      villagers_make_snowmen};
}

} // namespace elona
