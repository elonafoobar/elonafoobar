#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "data/types/type_map_chip.hpp"
#include "pic_loader/extent.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;

template <typename T>
struct elona_vector2;

template <typename T>
struct elona_vector3;

struct Character;

enum class TurnResult;



struct MapData
{
    int width{};
    int height{};
    int atlas_number{};
    int next_regenerate_date{};
    int stair_down_pos{};
    int stair_up_pos{};
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

extern MapData map_data;



// @see lua_env/api/classes/class_LuaMapGenerator.cpp
struct MapGenerator
{
};



struct Cell
{
    /**
     * The actual map chip of this cell.
     */
    int chip_id_actual{};

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
     * Internal representation of item information at the cell:
     *
     * The data is represented by 64 bit unsigned integer. It has 5 sections.
     *
     *    xxxx aaaaaaaaaaaaaaa bbbbbbbbbbbbbbb ccccccccccccccc ddddddddddddddd
     *            section 2       section 3       section 4       section 5
     *  section 1
     *
     * Section 1 consists of 4 bit and section 2-5 consist of 15 bit.
     * Section 1 may be 5 different states:
     *
     * 0000: there is no items.
     * 0001: there is 5-9 items.
     * 0011: there is 10-14 items.
     * 0111: there is 15-19 items.
     * 1111: there is 20- items.
     *
     * If there is 1-4 items at the cell, section 2-5 store item index plus one
     * (0 means no item).
     *
     * Section 5 stores the item in the bottom, section 4 stores 2nd, ....
     * and section 2 stores the item in the top of the stack.
     *
     * Thus, if the cell is empty, the internal value is 0.
     */
    struct ItemInfo
    {
        static constexpr size_t max_stacks = 4;



        ItemInfo() noexcept = default;
        ItemInfo(const ItemInfo&) noexcept = default;
        ItemInfo(ItemInfo&&) noexcept = default;
        ItemInfo& operator=(const ItemInfo&) noexcept = default;
        ItemInfo& operator=(ItemInfo&&) noexcept = default;
        ~ItemInfo() = default;



        bool is_empty() const noexcept
        {
            return _inner == 0;
        }


        void clear() noexcept
        {
            _inner = 0;
        }


        int stack_count() const noexcept
        {
            if (_inner == 0)
                return 0;
            else if (_inner & (1ULL << 63))
                return -4;
            else if (_inner & (1ULL << 62))
                return -3;
            else if (_inner & (1ULL << 61))
                return -2;
            else if (_inner & (1ULL << 60))
                return -1;
            else if (_inner & (32767ULL << 45))
                return 4;
            else if (_inner & (32767ULL << 30))
                return 3;
            else if (_inner & (32767ULL << 15))
                return 2;
            else
                return 1;
        }


        std::array<int, max_stacks> item_indice() const noexcept
        {
            std::array<int, max_stacks> ret;
            for (auto&& x : ret)
                x = 0;

            if (_inner == 0)
                return ret;
            if (_inner & (15ULL << 60))
                return ret;

            ret[0] = (_inner & (32767ULL << (15 * 0))) >> (15 * 0);
            ret[1] = (_inner & (32767ULL << (15 * 1))) >> (15 * 1);
            ret[2] = (_inner & (32767ULL << (15 * 2))) >> (15 * 2);
            ret[3] = (_inner & (32767ULL << (15 * 3))) >> (15 * 3);

            return ret;
        }



        void set(
            const std::array<int, max_stacks>& item_indice_plus_one,
            size_t number_of_items) noexcept
        {
            if (number_of_items == 0)
            {
                clear();
            }
            else if (number_of_items >= max_stacks + 1)
            {
                if (number_of_items >= (max_stacks + 1) * 4)
                {
                    _inner = 0xF000'0000'0000'0000ULL;
                }
                else if (number_of_items >= (max_stacks + 1) * 3)
                {
                    _inner = 0x7000'0000'0000'0000ULL;
                }
                else if (number_of_items >= (max_stacks + 1) * 2)
                {
                    _inner = 0x3000'0000'0000'0000ULL;
                }
                else
                {
                    _inner = 0x1000'0000'0000'0000ULL;
                }
            }
            else
            {
                _inner = 0;
                for (size_t i = 0; i < max_stacks; ++i)
                {
                    const auto index_plus_one = item_indice_plus_one[i];
                    _inner |= static_cast<decltype(_inner)>(index_plus_one)
                        << (15 * i);
                }
            }
        }



        template <typename Archive>
        void serialize(Archive& ar)
        {
            ar(_inner);
        }



    private:
        uint64_t _inner = 0;
    };


    ItemInfo item_info_actual{};
    ItemInfo item_info_memory{};

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



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(chip_id_actual);
        ar(chip_id_memory);
        ar(chara_index_plus_one);
        ar(item_info_actual);
        ar(item_info_memory);
        ar(feats);
        ar(blood_and_fragments);
        ar(mef_index_plus_one);
        ar(light);
        /* clang-format on */
    }
};



struct CellData
{
    CellData() = default;


    Cell& at(int x, int y)
    {
        return cells.at(y * width_ + x);
    }


    int width() const noexcept
    {
        return width_;
    }


    int height() const noexcept
    {
        return height_;
    }



    void init(int width, int height);



    /**
     * Reload tiles from @a tile_grid. Other properties are not modified.
     *
     * @param tile_grid The serialized array of tiles. Its size must be equal to
     * @ref width_ times @ref height_.
     */
    void load_tile_grid(const std::vector<int>& tile_grid);



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(width_);
        ar(height_);
        ar(cells);
        /* clang-format on */
    }



private:
    int width_{};
    int height_{};
    std::vector<Cell> cells;
};

extern CellData cell_data;


struct ChipData
{
    using MapType = std::unordered_map<int, MapChip>;
    static constexpr int chip_size = 825;
    static constexpr int atlas_count = 3;

    ChipData()
    {
        for (int i = 0; i < atlas_count; i++)
        {
            MapType map = {};
            for (int j = 0; j < chip_size; j++)
            {
                map[j] = MapChip{};
            }
            chips.emplace(i, map);
        }
    }

    MapType& get_map(int i)
    {
        return chips.at(i);
    }

    MapType& current()
    {
        return get_map(map_data.atlas_number);
    }

    MapChip& operator[](int i)
    {
        return current().at(i);
    }

    MapChip& for_cell(int x, int y)
    {
        return current().at(cell_data.at(x, y).chip_id_actual);
    }

    MapChip& for_feat(int x, int y)
    {
        return current().at(cell_data.at(x, y).feats % 1000);
    }

private:
    std::unordered_map<int, MapType> chips;
};

extern ChipData chip_data;


void map_get_trainer_skills(const Character& chara);
void map_set_chara_generation_filter();
void map_reload(const std::string& map_filename);
std::string map_get_custom_map_name(int);

bool map_is_town_or_guild();
bool map_should_reveal_fog();
bool map_shows_floor_count_in_name();
bool map_prevents_teleport();
bool map_prevents_return();
bool map_prevents_domination();
bool map_prevents_monster_ball();
bool map_prevents_building_shelter();
bool map_prevents_random_events();
void map_set_caravan_destinations();
void map_calc_trade_goods_price();
bool map_villagers_make_snowmen();
bool map_can_use_bad_weather_in_study();
int map_random_site_amount();

void map_proc_regen_and_update();
void map_reload_noyel();

void map_proc_special_events();

void map_prepare_for_travel(int id, int level = 1);
void map_prepare_for_travel_with_prev(int id, int level = 1);

int map_global_place_random_nefias();
int dist_town();


void addefmap(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
TurnResult exit_map();
void map_global_proc_diastrophism();
void map_global_prepare();
void map_global_place_entrances();
void map_clear_material_spots_and_light();
void map_global_proc_travel_events(Character& chara);
void sense_map_feats_on_move(Character& chara);
void prepare_charas_for_map_unload();
void spillblood(int = 0, int = 0, int = 0);
void spillfrag(int = 0, int = 0, int = 0);
void try_to_return();

} // namespace elona
