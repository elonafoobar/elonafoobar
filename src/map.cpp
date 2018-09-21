#include "map.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "db_item.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "position.hpp"
#include "variables.hpp"



namespace elona
{


MapData map_data;
CellData cell_data;



#define MDATA_PACK(x, ident) legacy_mdata(x) = ident;
#define MDATA_UNPACK(x, ident) ident = legacy_mdata(x);

#define SERIALIZE_ALL() \
    SERIALIZE(0, width); \
    SERIALIZE(1, height); \
    SERIALIZE(2, atlas_number); \
    SERIALIZE(3, next_regenerate_date); \
    SERIALIZE(4, stair_up_pos); \
    SERIALIZE(5, stair_down_pos); \
    SERIALIZE(6, type); \
    SERIALIZE(7, refresh_type); \
    SERIALIZE(8, designated_spawns); \
    SERIALIZE(9, turn_cost); \
    SERIALIZE(10, max_crowd_density); \
    SERIALIZE(11, current_dungeon_level); \
    SERIALIZE(12, tileset); \
    SERIALIZE(13, bgm); \
    SERIALIZE(14, indoors_flag); \
    SERIALIZE(15, user_map_flag); \
    SERIALIZE(16, next_restock_date); \
    SERIALIZE(17, should_regenerate); \
    SERIALIZE(18, max_item_count); \
    SERIALIZE(19, regenerate_count); \
    SERIALIZE(20, play_campfire_sound); \
    SERIALIZE(21, mefs_loaded_flag);


#define SERIALIZE MDATA_PACK
void MapData::pack_to(elona_vector1<int>& legacy_mdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE

#define SERIALIZE MDATA_UNPACK
void MapData::unpack_from(elona_vector1<int>& legacy_mdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE
#undef SERIALIZE_ALL


void MapData::clear()
{
    *this = {};
}


bool MapData::is_town_or_guild() const
{
    return type == mdata_t::MapType::town || type == mdata_t::MapType::guild;
}


bool MapData::should_reveal_map() const
{
    return game_data.current_map == mdata_t::MapId::pet_arena
        || game_data.current_map == mdata_t::MapId::arena
        || type == mdata_t::MapType::town || type == mdata_t::MapType::world_map
        || type == mdata_t::MapType::player_owned
        || type == mdata_t::MapType::guild
        || game_data.current_map == mdata_t::MapId::shelter_
        || game_data.current_map == mdata_t::MapId::embassy
        || game_data.current_map == mdata_t::MapId::miral_and_garoks_workshop
        || game_data.current_map == mdata_t::MapId::show_house
        || (game_data.current_map == mdata_t::MapId::quest
            && game_data.executing_immediate_quest_type == 1009);
}


#define MAP_PACK(n, ident) legacy_map(x, y, n) = ident;
#define MAP_UNPACK(n, ident) ident = legacy_map(x, y, n);

#define SERIALIZE_ALL() \
    SERIALIZE(0, chip_id_actual); \
    SERIALIZE(1, chara_index_plus_one); \
    SERIALIZE(2, chip_id_memory); \
    /* 3 */ \
    SERIALIZE(4, item_appearances_actual); \
    SERIALIZE(5, item_appearances_memory); \
    SERIALIZE(6, feats); \
    SERIALIZE(7, blood_and_fragments); \
    SERIALIZE(8, mef_index_plus_one); \
    SERIALIZE(9, light);


#define SERIALIZE MAP_PACK
void Cell::pack_to(elona_vector3<int>& legacy_map, int x, int y)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE

#define SERIALIZE MAP_UNPACK
void Cell::unpack_from(elona_vector3<int>& legacy_map, int x, int y)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE



void Cell::clear()
{
    *this = {};
}



void CellData::init(int width, int height)
{
    cells.clear();
    width_ = width;
    height_ = height;

    cells.reserve(height_);

    for (int y = 0; y < height_; y++)
    {
        std::vector<Cell> column;
        column.reserve(width_);

        for (int x = 0; x < width_; x++)
        {
            column.emplace_back(Cell{});
        }
        cells.emplace_back(std::move(column));
    }
}



void CellData::pack_to(elona_vector3<int>& legacy_map)
{
    DIM4(legacy_map, map_data.width, map_data.height, 10);

    assert(legacy_map.i_size() == static_cast<size_t>(width_));
    assert(legacy_map.j_size() == static_cast<size_t>(height_));

    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            at(x, y).pack_to(legacy_map, x, y);
        }
    }
}



void CellData::unpack_from(elona_vector3<int>& legacy_map)
{
    init(legacy_map.i_size(), legacy_map.j_size());

    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            at(x, y).unpack_from(legacy_map, x, y);
        }
    }
}



void map_reload(const std::string& map_filename)
{
    fmapfile = (filesystem::dir::map() / map_filename).generic_string();
    ctrl_file(FileOperation::map_load_map_obj_files);

    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).mef_index_plus_one = 0;
            cell_data.at(x, y).light = 0;
        }
    }

    mef_clear_all();

    for (const auto& i : items(-1))
    {
        if (inv[i].number() > 0)
        {
            if (inv[i].own_state == 1)
            {
                if (the_item_db[inv[i].id]->category == 57000)
                {
                    inv[i].remove();
                    cell_refresh(inv[i].position.x, inv[i].position.y);
                }
            }
        }
    }

    for (int i = 0; i < 400; ++i)
    {
        if (cmapdata(0, i) == 0)
            continue;
        const auto x = cmapdata(1, i);
        const auto y = cmapdata(2, i);
        if (cmapdata(4, i) == 0)
        {
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                flt();
                int stat = itemcreate(-1, cmapdata(0, i), x, y, 0);
                if (stat != 0)
                {
                    inv[ci].own_state = cmapdata(3, i);
                }
            }
            cell_refresh(x, y);
        }
    }
}



} // namespace elona
