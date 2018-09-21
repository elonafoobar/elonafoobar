#pragma once

#include <string>
#include <vector>


namespace elona
{

template <typename T>
struct elona_vector1;

template <typename T>
struct elona_vector3;



struct MapData
{
    int width{};
    int height{};
    int atlas_number{};
    int next_regenerate_date{};
    int stair_up_pos{};
    int stair_down_pos{};
    int type{};
    int refresh_type{};
    int designated_spawns{};
    int turn_cost{};
    int max_crowd_density{};
    int current_dungeon_level{};
    int tileset{};
    int bgm{};
    int indoors_flag{};
    int user_map_flag{};
    int next_restock_date{};
    int should_regenerate{};
    int max_item_count{};
    int regenerate_count{};
    int play_campfire_sound{};
    int mefs_loaded_flag{};


    bool is_town_or_guild() const;


    /**
     * Moves this struct's fields into `mdata` so they can be serialized, for
     * compatibility. To be called before serializing `mdata`.
     */
    void pack_to(elona_vector1<int>& legacy_mdata);

    /**
     * Moves `mdata` fields into this struct. To be called after deserializing
     * `mdata`.
     */
    void unpack_from(elona_vector1<int>& legacy_mdata);

    void clear();
};


struct Cell
{
    /**
     * The chip that is displayed when this cell is out of the player's field of
     * view.
     */
    int chip_id_memory{};

    /**
     * Character index at this tile. 0 if empty.
     *
     * 1 is added to the index since the character array is 0-indexed, but 0 in
     * this field indicates nonexistence.
     */
    int chara_index_plus_one{};

    /**
     * The actual map chip of this cell.
     */
    int chip_id_actual{};

    /**
     * Absurdly complicated fields for storing item appearance data. They share
     * the same format.
     *
     * For 1 item:
     * Upper four bytes are item chip ID.
     * Lower four bytes are item color ID.
     *
     * For 2 items:
     * Value is (-1) * ((top_item_index - 5080)
     *               +  (bottom_item_index - 5080) * 1000
     *               +  999 * 1000000)
     *
     * Since 5080 + 999 is 6079, if this index is encountered then the third
     * item index is skipped.
     *
     * For 3 items:
     * Value is (-1) * ((top_item_index - 5080)
     *               +  (middle_item_index - 5080) * 1000
     *               +  (bottom_item_index - 5080) * 1000000)
     *
     * For 4 or more items:
     * Upper two bytes make 363 (item bag chip ID)
     * Lower two bytes make 0 (colorless ID)
     *
     * Item indices are not used in the 1 or 4 item case, but they are used for
     * the 2 or 3 item case.
     */
    int item_appearances_memory{};
    int item_appearances_actual{};

    /**
     * Feat data. Value is transferred into feat() as follows:
     *
     * feat + feat(1) * 1000 + feat(2) * 100000 + feat(3) * 10000000
     */
    int feats{};

    /**
     * blood_level + fragment_level * 10
     */
    int blood_and_fragments{};

    /**
     * Map effect index plus 1, to be looked up in mef(). 0 if no mef.
     */
    int mef_index_plus_one{};

    /**
     * Amount of light generated.
     *
     * Set in cell_refresh() to be the "light" parameter of an item placed on
     * the cell if it is not 0.
     *
     * In the world map, areas with "town" or "guild" type are set to emanate
     * light of level 11.
     */

    int light{};


    /**
     * Moves this struct's fields into `map` so they can be serialized, for
     * compatibility. To be called before serializing `map`.
     */
    void pack_to(elona_vector3<int>& legacy_map, int x, int y);

    /**
     * Moves `map` fields into this struct. To be called after deserializing
     * `map`.
     */
    void unpack_from(elona_vector3<int>& legacy_map, int x, int y);

    /**
     * Clear this Cell.
     */
    void clear();
};

struct CellData
{
    template <typename T>
    using Grid = std::vector<std::vector<T>>;

    CellData()
    {
    }


    Cell& at(int x, int y)
    {
        return cells.at(static_cast<size_t>(y)).at(static_cast<size_t>(x));
    }


    int width() const
    {
        return width_;
    }


    int height() const
    {
        return height_;
    }



    void init(int width, int height);


    // Helper method to pack all cell data to `map`.
    void pack_to(elona_vector3<int>& legacy_map);


    // Helper method to unpack all cell data from `map`.
    void unpack_from(elona_vector3<int>& legacy_map);


private:
    int width_{};
    int height_{};
    Grid<Cell> cells;
};


extern CellData cell_data;
extern MapData map_data;


void map_reload(const std::string& map_filename);

} // namespace elona
