#include "area.hpp"
#include "elona.hpp"
#include "position.hpp"



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



bool Area::can_return_to()
{
    return id == mdata_t::MapId::lesimas || id == mdata_t::MapId::larna
        || id == mdata_t::MapId::mansion_of_younger_sister
        || id == mdata_t::MapId::the_void;
}


bool Area::can_return_to_if_wizard()
{
    return type == mdata_t::MapType::town || type == mdata_t::MapType::guild;
}


bool Area::is_museum_or_shop()
{
    return id == mdata_t::MapId::museum || id == mdata_t::MapId::shop;
}


} // namespace elona
