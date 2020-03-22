#include "area.hpp"

#include "ctrl_file.hpp"
#include "data/types/type_map.hpp"
#include "elona.hpp"
#include "position.hpp"
#include "variables.hpp"



namespace elona
{


AreaData area_data;



#define ADATA_PACK(x, ident) legacy_adata(x, area_id) = ident;
#define ADATA_UNPACK(x, ident) ident = legacy_adata(x, area_id);

#define SERIALIZE_ALL() \
    SERIALIZE(0, type); \
    /* SERIALIZE(1, x); */ \
    /* SERIALIZE(2, y); */ \
    SERIALIZE(3, entrance); \
    SERIALIZE(4, tile_set); \
    SERIALIZE(5, dungeon_prefix); \
    SERIALIZE(6, visited_deepest_level); \
    SERIALIZE(9, turn_cost_base); \
    SERIALIZE(10, deepest_level); \
    /* SERIALIZE(11, is_generated_every_time); */ \
    SERIALIZE(12, default_ai_calm); \
    SERIALIZE(15, appearance); \
    SERIALIZE(16, id); \
    SERIALIZE(17, danger_level); \
    SERIALIZE(18, tile_type); \
    SERIALIZE(20, has_been_conquered); \
    /* SERIALIZE(21, is_indoor); */ \
    SERIALIZE(22, winning_streak_in_arena); \
    SERIALIZE(23, winning_streak_in_pet_arena); \
    SERIALIZE(24, arena_random_seed); \
    SERIALIZE(25, time_of_next_update_of_arena_random_seed); \
    SERIALIZE(26, time_of_next_arena); \
    SERIALIZE(27, time_of_next_rumble); \
    SERIALIZE(28, quest_town_id); \
    SERIALIZE(29, christmas_festival); \
    SERIALIZE(30, outer_map);


#define SERIALIZE ADATA_PACK
void Area::pack_to(elona_vector2<int>& legacy_adata, int area_id)
{
    SERIALIZE_ALL();

    legacy_adata(1, area_id) = position.x;
    legacy_adata(2, area_id) = position.y;
    legacy_adata(11, area_id) = is_generated_every_time ? 0 : 1;
    legacy_adata(21, area_id) = is_indoor ? 1 : 2;
}
#undef SERIALIZE


#define SERIALIZE ADATA_UNPACK
void Area::unpack_from(elona_vector2<int>& legacy_adata, int area_id)
{
    SERIALIZE_ALL();

    position = Position{legacy_adata(1, area_id), legacy_adata(2, area_id)};
    is_generated_every_time = legacy_adata(11, area_id) == 0;
    is_indoor = legacy_adata(21, area_id) == 1;
}
#undef SERIALIZE



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



void AreaData::pack_to(elona_vector2<int>& legacy_adata)
{
    assert(legacy_adata.j_size() == areas.size());

    int i{};
    for (auto&& area : areas)
    {
        area.pack_to(legacy_adata, i);
        ++i;
    }
}



void AreaData::unpack_from(elona_vector2<int>& legacy_adata)
{
    assert(legacy_adata.j_size() == areas.size());

    int i{};
    for (auto&& area : areas)
    {
        area.unpack_from(legacy_adata, i);
        ++i;
    }
}



Area& AreaData::current()
{
    assert(game_data.current_map != 0);

    return area_data[game_data.current_map];
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

        const auto map_id = map.legacy_id;
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
             game_data.home_scale == 0);
        if (is_fixed_in_place)
        {
            area.position = map.outer_map_position;
            area.appearance = map.appearance;
            area.tile_set = map.tile_set;
            area.tile_type = map.tile_type;
            area.outer_map = outer_map->legacy_id;
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
    area.id = map.legacy_id;
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
