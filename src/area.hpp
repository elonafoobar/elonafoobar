#pragma once

#include <vector>
#include "position.hpp"



namespace elona
{


template <typename T>
struct elona_vector2;



struct Area
{
    int type{};
    Position position;
    int entrance{};
    int tile_set{};
    int dungeon_prefix{};
    int visited_deepest_level{};
    int turn_cost_base{};
    int deepest_level{};
    bool is_generated_every_time = true;
    int default_ai_calm{};
    int appearance{};
    int id{};
    int danger_level{};
    int tile_type{};
    int has_been_conquered{};
    bool is_indoor{};
    int winning_streak_in_arena{};
    int winning_streak_in_pet_arena{};
    int arena_random_seed{};
    int time_of_next_update_of_arena_random_seed{};
    int time_of_next_arena{};
    int time_of_next_rumble{};
    int quest_town_id{};
    bool christmas_festival{};
    int outer_map{};


    bool can_return_to();
    bool can_return_to_if_wizard();
    bool is_museum_or_shop();


    /**
     * Moves this struct's fields into `adata` so they can be serialized, for
     * compatibility. To be called before serializing `adata`.
     */
    void pack_to(elona_vector2<int>& legacy_adata, int area_id);

    /**
     * Moves `adata` fields into this struct. To be called after deserializing
     * `adata`.
     */
    void unpack_from(elona_vector2<int>& legacy_adata, int area_id);

    /**
     * Clear this Area.
     */
    void clear();
};



struct AreaData
{
    static constexpr size_t area_size = 500;


    AreaData()
        : areas(area_size)
    {
    }


    Area& operator[](int i)
    {
        return areas.at(static_cast<size_t>(i));
    }



    /**
     * Clear the whole of areas.
     */
    void clear();


    // Helper method to pack whole of `area_data` to `adata`.
    void pack_to(elona_vector2<int>& legacy_adata);


    // Helper method to unpack whole of `area_data` from `adata`.
    void unpack_from(elona_vector2<int>& legacy_adata);


private:
    std::vector<Area> areas;
};


extern AreaData area_data;


} // namespace elona
