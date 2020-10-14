#include "area.hpp"

#include "ctrl_file.hpp"
#include "data/types/type_map.hpp"
#include "elona.hpp"
#include "game.hpp"
#include "position.hpp"
#include "variables.hpp"



namespace elona
{


AreaData area_data;



void Area::clear()
{
    *this = {};
}



void AreaData::clear()
{
    for (auto&& area : areas)
    {
        area.clear();
    }
}



Area& AreaData::current()
{
    assert(game()->current_map != 0);

    return area_data[game()->current_map];
}



optional_ref<MapDefData> AreaData::current_mapdef()
{
    return the_mapdef_db[current().id];
}



bool Area::can_return_to()
{
    return the_mapdef_db[id]->can_return_to;
}


bool Area::can_return_to_if_wizard()
{
    return type == mdata_t::MapType::town || type == mdata_t::MapType::guild;
}

bool Area::is_hidden_in_world_map()
{
    return the_mapdef_db[id]->is_hidden_in_world_map;
}


bool Area::is_museum_or_shop()
{
    return id == mdata_t::MapId::museum || id == mdata_t::MapId::shop;
}


void initialize_adata()
{
    for (const auto& map : the_mapdef_db.values())
    {
        auto outer_map = the_mapdef_db[map.outer_map];
        if (!outer_map)
        {
            throw std::runtime_error{
                "Error when initializing area data. Can't find outer map '"s +
                map.outer_map.get() + "' for map '" + map.id.get() + "'."};
        }

        if (map.deed)
        {
            // This map can have multiple instances, so don't instantiate it.
            continue;
        }

        const auto map_id = map.integer_id;
        auto& area = area_data[map_id];

        area.id = map_id;
        area.type = static_cast<int>(map.map_type);
        area.entrance = map.entrance_type;
        area.turn_cost_base = map.base_turn_cost;
        area.danger_level = map.danger_level;
        area.deepest_level = map.deepest_level;
        area.is_indoor = map.is_indoor;
        area.is_generated_every_time = map.is_generated_every_time;
        area.default_ai_calm = map.default_ai_calm;
        area.quest_town_id = map.quest_town_id;

        // Only set position/tiles of Your Home if it has not been upgraded. All
        // other maps all have fixed positions/tiles.
        bool is_fixed_in_place = map.is_fixed ||
            (map_id == static_cast<int>(mdata_t::MapId::your_home) &&
             game()->home_scale == 0);
        if (is_fixed_in_place)
        {
            area.position = map.outer_map_position;
            area.appearance = map.appearance;
            area.tile_set = map.tile_set;
            area.tile_type = map.tile_type;
            area.outer_map = outer_map->integer_id;
        }
    }
}

void area_generate_from_mapdef(
    Area& area,
    const MapDefData& map,
    int outer_map,
    int x,
    int y)
{
    area.id = map.integer_id;
    area.appearance = map.appearance;
    area.is_indoor = map.is_indoor;
    area.position.x = x;
    area.position.y = y;
    area.type = static_cast<int>(map.map_type);
    area.is_generated_every_time = map.is_generated_every_time;
    area.default_ai_calm = map.default_ai_calm;
    area.tile_type = map.tile_type;
    area.turn_cost_base = map.base_turn_cost;
    area.danger_level = map.danger_level;
    area.deepest_level = map.danger_level;
    area.tile_set = map.tile_set;
    area.entrance = map.entrance_type;
    area.outer_map = outer_map;
}


} // namespace elona
