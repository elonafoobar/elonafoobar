#include "map.hpp"

#include "area.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_map.hpp"
#include "elona.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_event/lua_event_nefia_created.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "position.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace
{

void _map_randsite()
{
    optional<Position> pos;
    for (int i = 0; i < 20; ++i)
    {
        const auto x = rnd(map_data.width - 5) + 2;
        const auto y = rnd(map_data.height - 5) + 2;
        if ((chip_data.for_cell(x, y).effect & 4) == 0)
        {
            if (cell_data.at(x, y).feats == 0 &&
                cell_data.at(x, y).item_appearances_actual == 0)
            {
                pos = Position(x, y);
                break;
            }
        }
    }
    if (!pos)
    {
        return;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if ((264 <= cell_data.at(pos->x, pos->y).chip_id_actual &&
             cell_data.at(pos->x, pos->y).chip_id_actual < 363) ||
            (33 <= cell_data.at(pos->x, pos->y).chip_id_actual &&
             cell_data.at(pos->x, pos->y).chip_id_actual < 66))
        {
            return;
        }
    }

    if (mdata_t::is_nefia(map_data.type))
    {
        if (map_data.next_regenerate_date == 0)
        {
            if (rnd(25) == 0)
            {
                flt();
                if (const auto item = itemcreate_extra_inv(173, *pos, 0))
                {
                    item->own_state = 1;
                }
                return;
            }
            if (rnd(100) == 0)
            {
                flt();
                if (const auto item = itemcreate_extra_inv(172, *pos, 0))
                {
                    item->own_state = 1;
                    item->param1 = choice(isetgod);
                }
                return;
            }
        }
    }

    if (mdata_t::is_nefia(map_data.type))
    {
        if (rnd(14) == 0)
        {
            cell_featset(pos->x, pos->y, 243, 27);
            return;
        }
        if (rnd(13) == 0)
        {
            cell_featset(pos->x, pos->y, 244, 25);
            return;
        }
        if (rnd(12) == 0)
        {
            cell_featset(pos->x, pos->y, 245, 26);
            return;
        }
        if (rnd(11) == 0)
        {
            cell_featset(pos->x, pos->y, 246, 28);
            return;
        }
        cell_featset(pos->x, pos->y, tile_re + rnd(3), 24);
        return;
    }

    if (map_is_town_or_guild())
    {
        if (rnd(3) == 0)
        {
            flt();
            itemcreate_extra_inv(631, *pos, 0);
            return;
        }
        if (rnd(15) == 0)
        {
            flt();
            itemcreate_extra_inv(55, *pos, 0);
            return;
        }
        if (rnd(20) == 0)
        {
            flt();
            itemcreate_extra_inv(284, *pos, 0);
            return;
        }
        if (rnd(15) == 0)
        {
            flt();
            itemcreate_extra_inv(283, *pos, 0);
            return;
        }
        if (rnd(18) == 0)
        {
            flt(calcobjlv(rnd_capped(cdata.player().level + 10)),
                calcfixlv(Quality::good));
            flttypemajor = choice(fsetwear);
            itemcreate_extra_inv(0, *pos, 0);
            return;
        }
        flt(10);
        flttypeminor = 64100;
        itemcreate_extra_inv(0, *pos, 0);
        return;
    }
}

} // namespace



namespace elona
{


MapData map_data;
CellData cell_data;
ChipData chip_data;



#define MDATA_PACK(x, ident) legacy_mdata(x) = ident;
#define MDATA_UNPACK(x, ident) ident = legacy_mdata(x);

#define SERIALIZE_ALL() \
    SERIALIZE(0, width); \
    SERIALIZE(1, height); \
    SERIALIZE(2, atlas_number); \
    SERIALIZE(3, next_regenerate_date); \
    SERIALIZE(4, stair_down_pos); \
    SERIALIZE(5, stair_up_pos); \
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


#define MAP_PACK(n, ident) legacy_map(x, y, n) = ident;
#define MAP_UNPACK(n, ident) ident = legacy_map(x, y, n);

#define SERIALIZE_ALL() \
    SERIALIZE(0, chip_id_actual); \
    SERIALIZE(1, chara_index_plus_one); \
    SERIALIZE(2, chip_id_memory); \
    if (!all_fields) \
        return; \
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
    constexpr auto all_fields = true;
    SERIALIZE_ALL();
}
#undef SERIALIZE

#define SERIALIZE MAP_UNPACK
void Cell::unpack_from(elona_vector3<int>& legacy_map, int x, int y)
{
    constexpr auto all_fields = true;
    SERIALIZE_ALL();
}

void Cell::partly_unpack_from(elona_vector3<int>& legacy_map, int x, int y)
{
    constexpr auto all_fields = false;
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



void CellData::unpack_from(elona_vector3<int>& legacy_map, bool clear)
{
    if (clear)
    {
        init(legacy_map.i_size(), legacy_map.j_size());
    }
    else
    {
        // In this case, the size of map must equal to the previous one.
        assert(
            legacy_map.i_size() == static_cast<size_t>(width_) &&
            legacy_map.j_size() == static_cast<size_t>(height_));
    }

    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            if (clear)
            {
                at(x, y).unpack_from(legacy_map, x, y);
            }
            else
            {
                at(x, y).partly_unpack_from(legacy_map, x, y);
            }
        }
    }
}



void map_reload(const std::string& map_filename)
{
    fmapfile = (filesystem::dirs::map() / map_filename).generic_string();
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

    for (auto&& item : inv.ground())
    {
        if (item.number() > 0)
        {
            if (item.own_state == 1)
            {
                if (the_item_db[itemid2int(item.id)]->category ==
                    ItemCategory::food)
                {
                    item.remove();
                    cell_refresh(item.position.x, item.position.y);
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
                if (const auto item =
                        itemcreate_extra_inv(cmapdata(0, i), x, y, 0))
                {
                    item->own_state = cmapdata(3, i);
                }
            }
            cell_refresh(x, y);
        }
    }
}



// Used for huntex/conquer quests.
std::string map_get_custom_map_name(int map_id)
{
    auto area_map_id = area_data[map_id].id;
    auto map = the_mapdef_db[area_map_id];

    if (map && map->quest_custom_map)
    {
        return *map->quest_custom_map;
    }

    return "vernis";
}


bool map_is_town_or_guild()
{
    return map_data.type == mdata_t::MapType::town ||
        map_data.type == mdata_t::MapType::guild;
}


bool map_should_reveal_fog()
{
    bool result = false;

    if (game_data.current_map == mdata_t::MapId::quest)
    {
        return game_data.executing_immediate_quest_type == 1009;
    }

    if (auto map = area_data.current_mapdef())
    {
        result |= map->reveals_fog;
    }

    return result || dbg_revealmap || map_data.type == mdata_t::MapType::town ||
        map_data.type == mdata_t::MapType::world_map ||
        map_data.type == mdata_t::MapType::player_owned ||
        map_data.type == mdata_t::MapType::guild;
}


bool map_shows_floor_count_in_name()
{
    bool result = false;

    if (auto map = area_data.current_mapdef())
    {
        result |= map->shows_floor_count_in_name;
    }

    return area_data[game_data.current_map].type != mdata_t::MapType::town &&
        (result ||
         area_data[game_data.current_map].id ==
             mdata_t::MapId::random_dungeon ||
         mdata_t::is_nefia(map_data.type));
}


bool map_prevents_teleport()
{
    bool result = false;

    if (auto map = area_data.current_mapdef())
    {
        result |= map->prevents_teleport;
    }

    return result || map_data.type == mdata_t::MapType::world_map;
}


bool map_prevents_return()
{
    bool result = false;

    if (auto map = area_data.current_mapdef())
    {
        result |= map->prevents_return;
    }

    return result || map_data.type == mdata_t::MapType::temporary;
}


bool map_prevents_domination()
{
    if (auto map = area_data.current_mapdef())
    {
        return map->prevents_domination;
    }

    return false;
}


bool map_prevents_monster_ball()
{
    if (auto map = area_data.current_mapdef())
    {
        return map->prevents_monster_ball;
    }

    return false;
}


bool map_prevents_building_shelter()
{
    bool result = false;

    if (auto map = area_data.current_mapdef())
    {
        result |= map->prevents_building_shelter;
    }

    return result || map_data.refresh_type == 0;
}


bool map_prevents_random_events()
{
    if (auto map = area_data.current_mapdef())
    {
        return map->prevents_random_events;
    }

    return false;
}


int map_random_site_amount()
{
    int amount = rnd(map_data.height * map_data.width / 400 + 3);
    if (map_data.type == mdata_t::MapType::world_map)
    {
        amount = rnd(40);
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        amount = rnd(rnd(rnd(12) + 1) + 1);
    }
    if (map_data.type == mdata_t::MapType::guild)
    {
        amount = rnd(p + 1);
    }

    return amount;
}


void map_set_caravan_destinations()
{
    // '0' is "go back" choice index.
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;

    if (game_data.current_map == mdata_t::MapId::north_tyris_south_border)
    {
        p(0) = static_cast<int>(mdata_t::MapId::south_tyris_north_border);
        p(1) = static_cast<int>(mdata_t::MapId::test_world_north_border);
        p(2) = 0;
    }
    if (game_data.current_map == mdata_t::MapId::south_tyris_north_border)
    {
        p(0) = static_cast<int>(mdata_t::MapId::north_tyris_south_border);
        p(1) = static_cast<int>(mdata_t::MapId::test_world_north_border);
        p(2) = 0;
    }
    if (game_data.current_map == mdata_t::MapId::test_world_north_border)
    {
        p(0) = static_cast<int>(mdata_t::MapId::north_tyris_south_border);
        p(1) = static_cast<int>(mdata_t::MapId::south_tyris_north_border);
        p(2) = 0;
    }
}


void map_calc_trade_goods_price()
{
    DIM2(trate, 8);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        trate(cnt) = 100;
    }
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        trate(0) = 130;
        trate(1) = 70;
        trate(3) = 110;
        trate(2) = 85;
        trate(6) = 150;
        trate(7) = 120;
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        trate(0) = 65;
        trate(1) = 110;
        trate(4) = 125;
        trate(5) = 65;
        trate(2) = 70;
        trate(6) = 200;
        trate(7) = 150;
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        trate(0) = 120;
        trate(2) = 75;
        trate(4) = 75;
        trate(1) = 125;
        trate(6) = 110;
        trate(7) = 80;
    }
    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        trate(0) = 120;
        trate(3) = 75;
        trate(2) = 120;
        trate(6) = 160;
        trate(7) = 100;
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        trate(0) = 85;
        trate(3) = 70;
        trate(5) = 120;
        trate(2) = 130;
        trate(6) = 130;
        trate(7) = 90;
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        trate(1) = 175;
        trate(0) = 170;
        trate(3) = 160;
        trate(5) = 130;
        trate(2) = 140;
        trate(6) = 75;
        trate(7) = 120;
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        trate(1) = 145;
        trate(0) = 130;
        trate(3) = 100;
        trate(5) = 120;
        trate(2) = 120;
        trate(6) = 100;
        trate(7) = 70;
    }
    randomize(game_data.date.hours() / 100);
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        trate(cnt) += rnd(15) - rnd(15);
    }
    randomize();
}


bool map_villagers_make_snowmen()
{
    if (auto map = area_data.current_mapdef())
    {
        return map->villagers_make_snowmen;
    }

    return false;
}


bool map_can_use_bad_weather_in_study()
{
    return game_data.current_map != mdata_t::MapId::shelter_ &&
        map_data.indoors_flag == 1 &&
        (map_data.type == mdata_t::MapType::player_owned ||
         map_is_town_or_guild());
}



static void _map_update_arena_random_seed()
{
    area_data[game_data.current_map].arena_random_seed = rnd(10000);
    area_data[game_data.current_map].time_of_next_update_of_arena_random_seed =
        game_data.date.hours() + 24;
}


static void _clear_material_spots()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            if (cell_data.at(cnt, y).feats != 0)
            {
                cell_featread(cnt, y);
                if (feat(1) >= 24 && feat(1) <= 28)
                {
                    cell_featclear(cnt, y);
                }
            }
        }
    }
}


static void _modify_items_on_regenerate()
{
    for (auto&& item : inv.ground())
    {
        if (item.number() == 0)
        {
            continue;
        }

        // Update tree of fruits.
        if (item.id == ItemId::tree_of_fruits)
        {
            if (item.param1 < 10)
            {
                item.param1 += 1;
                item.image = 591;
                cell_refresh(item.position.x, item.position.y);
            }
        }

        // Clear player-owned items on the ground.
        if (map_is_town_or_guild())
        {
            if (item.own_state < 0)
            {
                ++item.own_state;
            }
            if (item.own_state == 0)
            {
                item.remove();
                cell_refresh(item.position.x, item.position.y);
            }
        }
    }
}


static void _modify_characters_on_regenerate()
{
    for (auto&& cnt : cdata.others())
    {
        rc = cnt.index;
        chara_clear_status_effects_b();
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (cnt.is_temporary() == 1)
        {
            if (rnd(2))
            {
                cnt.set_state(Character::State::empty);
                cell_data.at(cnt.position.x, cnt.position.y)
                    .chara_index_plus_one = 0;
            }
        }
    }
}


static void _set_feats_on_regenerate()
{
    p = map_random_site_amount();
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        _map_randsite();
    }
}


static void _map_regenerate()
{
    if (map_data.should_regenerate == 0)
    {
        if (map_data.next_regenerate_date != 0)
        {
            _clear_material_spots();
            _modify_items_on_regenerate();
        }

        _modify_characters_on_regenerate();

        _set_feats_on_regenerate();
    }
    map_data.next_regenerate_date = game_data.date.hours() + 120;
}


static void _grow_plants()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            if (cell_data.at(cnt, y).feats != 0)
            {
                cell_featread(cnt, y);
                x = cnt;
                if (feat(1) == 29)
                {
                    for (int cnt = 0, cnt_end = (renewmulti); cnt < cnt_end;
                         ++cnt)
                    {
                        if (feat >= tile_plant + 2)
                        {
                            break;
                        }
                        grow_plant(chip_data.for_cell(x, y).kind == 2 ? 1 : 0);
                    }
                    cell_featset(cnt, y, feat, feat(1), feat(2), feat(3));
                }
            }
        }
    }
}


static void _proc_generate_bard_items(Character& chara)
{
    if (!itemfind(chara.index, 60005, 1))
    {
        if (rnd(150) == 0)
        {
            // Stradivarius
            flt();
            itemcreate_chara_inv(chara.index, 707, 0);
        }
        else
        {
            // Random instrument
            flt(calcobjlv(chara.level), calcfixlv());
            flttypeminor = 60005;
            itemcreate_chara_inv(chara.index, 0, 0);
        }
    }
}


static void _generate_bad_quality_item()
{
    flt(calcobjlv(cdata[rc].level), calcfixlv(Quality::bad));
    if (const auto item = itemcreate_chara_inv(rc, 0, 0))
    {
        if (item->weight <= 0 || item->weight >= 4000)
        {
            item->remove();
        }
    }
}


static void _restock_character_inventories()
{
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        generatemoney(cnt.index);
        if (cnt.id == CharaId::bard)
        {
            _proc_generate_bard_items(cnt);
        }
        rc = cnt.index;
        if (rnd(5) == 0)
        {
            supply_new_equipment();
        }
        if (rnd(2) == 0 && inv_sum(rc) < 8)
        {
            _generate_bad_quality_item();
        }
    }
}

static void _map_restock_regenerate()
{
    _grow_plants();

    if (map_is_town_or_guild() ||
        game_data.current_map == mdata_t::MapId::your_home)
    {
        _restock_character_inventories();
    }
}


static void _map_restock()
{
    if (map_data.next_restock_date == 0)
    {
        renewmulti = 1;
    }
    else
    {
        renewmulti =
            (game_data.date.hours() - map_data.next_restock_date) / 24 + 1;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::ranch)
    {
        update_ranch();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::your_home)
    {
        for (auto&& cnt : cdata.others())
        {
            if (cnt.state() != Character::State::alive)
            {
                continue;
            }
            if (cnt.is_temporary() == 1)
            {
                cnt.set_state(Character::State::empty);
                cell_data.at(cnt.position.x, cnt.position.y)
                    .chara_index_plus_one = 0;
            }
        }
    }
    if (map_data.should_regenerate == 0)
    {
        _map_restock_regenerate();
    }
    map_data.next_restock_date = game_data.date.hours() + 24;
}


void map_proc_regen_and_update()
{
    if (game_data.date.hours() >= area_data[game_data.current_map]
                                      .time_of_next_update_of_arena_random_seed)
    {
        _map_update_arena_random_seed();
    }
    if (game_data.date.hours() >= map_data.next_regenerate_date)
    {
        _map_regenerate();
    }
    if (game_data.date.hours() >= map_data.next_restock_date)
    {
        _map_restock();
    }
}



void map_reload_noyel()
{
    for (auto&& item : inv.ground())
    {
        if (item.id == ItemId::shelter || item.id == ItemId::giants_shackle)
        {
            continue;
        }
        item.remove();

        cell_refresh(item.position.x, item.position.y);
    }

    if (area_data[game_data.current_map].christmas_festival)
    {
        flt();
        if (const auto item = itemcreate_extra_inv(763, 29, 16, 0))
        {
            item->own_state = 1;
        }
        flt();
        if (const auto item = itemcreate_extra_inv(686, 29, 16, 0))
        {
            item->own_state = 1;
        }
        flt();
        if (const auto item = itemcreate_extra_inv(171, 29, 17, 0))
        {
            item->param1 = 6;
            item->own_state = 1;
        }
        flt();
        if (const auto item = itemcreate_extra_inv(756, 29, 17, 0))
        {
            item->own_state = 5;
        }
        {
            flt();
            int stat = chara_create(-1, 345, 48, 19);
            if (stat != 0)
            {
                cdata[rc].character_role = 3;
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 348, 30, 17);
            if (stat != 0)
            {
                cdata[rc].character_role = 3;
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 174, 38, 19);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
                cdata[rc].is_hung_on_sand_bag() = true;
                cdatan(0, rc) = i18n::s.get("core.chara.job.fanatic");
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 35, 19);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 37, 18);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 37, 21);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 39, 20);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 38, 21);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 70, 17, 8);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1002;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = snfood(cdatan(0, rc));
            }
        }
        {
            flt();
            int stat = chara_create(-1, 239, 25, 8);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1018;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = random_name();
                cdatan(0, rc) = i18n::s.get(
                    "core.chara.job.souvenir_vendor", cdatan(0, rc));
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 24, 22);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1018;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = random_name();
                cdatan(0, rc) = i18n::s.get(
                    "core.chara.job.souvenir_vendor", cdatan(0, rc));
            }
        }
        {
            flt();
            int stat = chara_create(-1, 1, 38, 12);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].character_role = 1007;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = snblack(cdatan(0, rc));
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 28, 9);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1022;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = random_name();
                cdatan(0, rc) =
                    i18n::s.get("core.chara.job.street_vendor", cdatan(0, rc));
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 29, 24);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1022;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = random_name();
                cdatan(0, rc) =
                    i18n::s.get("core.chara.job.street_vendor2", cdatan(0, rc));
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 349, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            flt();
            {
                int stat = chara_create(-1, 350, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 326, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 335, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            {
                flt();
                int stat = chara_create(-1, 185, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
            {
                flt();
                int stat = chara_create(-1, 274, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
            {
                flt();
                int stat = chara_create(-1, 174, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 332, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            {
                flt();
                int stat = chara_create(-1, 185, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
    }
    else
    {
        for (auto&& cnt : cdata.others())
        {
            if (cnt.only_christmas())
            {
                chara_vanquish(cnt.index);
            }
        }
    }
}



static void _create_nefia(int index, int x, int y)
{
    area = index;
    ctrl_file(FileOperation::temp_dir_delete_area);

    auto& area = area_data[index];
    const auto& map = the_mapdef_db.ensure("elona.random_dungeon");

    area_generate_from_mapdef(area, map, game_data.destination_outer_map, x, y);

    area.type = static_cast<int>(mdata_t::MapType::dungeon) + rnd(4);
    if (rnd(3))
    {
        area.danger_level = rnd_capped(cdata.player().level + 5) + 1;
    }
    else
    {
        area.danger_level = rnd(50) + 1;
        if (rnd(5) == 0)
        {
            area.danger_level *= rnd(3) + 1;
        }
    }
    area.deepest_level = area.danger_level + rnd(4) + 2;
    area.has_been_conquered = 0;
    area.dungeon_prefix = rnd(mapnamerd.i_size());
    area.outer_map = game_data.destination_outer_map;

    cell_data.at(x, y).feats = 1;

    if (area.type == mdata_t::MapType::dungeon)
    {
        area.appearance = 133;
        area.tile_type = 0;
    }
    if (area.type == mdata_t::MapType::dungeon_tower)
    {
        area.appearance = 137;
        area.tile_type = 100;
    }
    if (area.type == mdata_t::MapType::dungeon_forest)
    {
        area.appearance = 135;
        area.tile_type = 300;
    }
    if (area.type == mdata_t::MapType::dungeon_castle)
    {
        area.appearance = 140;
        area.tile_type = 200;
    }

    lua::lua->get_event_manager().trigger(lua::NefiaCreatedEvent(&area));
}



int map_global_place_random_nefias()
{
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        int x, y;

        if (area_data[cnt].id != mdata_t::MapId::none)
        {
            continue;
        }
        f = -1;
        for (int cnt = 0; cnt < 1000; ++cnt)
        {
            x = cxinit + rnd((cnt + 1)) - rnd((cnt + 1));
            y = cyinit + rnd((cnt + 1)) - rnd((cnt + 1));
            if (x <= 5 || y <= 5 || x >= map_data.width - 6 ||
                y >= map_data.height - 6)
            {
                continue;
            }
            if (33 <= cell_data.at(x, y).chip_id_actual &&
                cell_data.at(x, y).chip_id_actual < 66)
            {
                continue;
            }
            if (cell_data.at(x, y).chip_id_actual > 19)
            {
                continue;
            }
            if (cell_data.at(x, y).feats % 1000 != 0)
            {
                continue;
            }
            p = 1;
            for (int cnt = 0; cnt < 500; ++cnt)
            {
                if (area_data[cnt].id == mdata_t::MapId::none)
                {
                    continue;
                }
                if (x >= area_data[cnt].position.x - 2 &&
                    x <= area_data[cnt].position.x + 2)
                {
                    if (y >= area_data[cnt].position.y - 2 &&
                        y <= area_data[cnt].position.y + 2)
                    {
                        p = 0;
                        break;
                    }
                }
            }
            if (p == 0)
            {
                continue;
            }
            f = 1;
            break;
        }
        if (f == -1)
        {
            p = -1;
            break;
        }
        p = cnt;

        _create_nefia(p(0), x, y);

        break;
    }
    return p;
}

void map_prepare_for_travel(int id, int level)
{
    game_data.destination_map = id;
    game_data.destination_dungeon_level = level;
    levelexitby = 2;
}

void map_prepare_for_travel_with_prev(int id, int level)
{
    game_data.previous_map2 = game_data.current_map;
    game_data.previous_dungeon_level = game_data.current_dungeon_level;
    game_data.previous_x = cdata.player().position.x;
    game_data.previous_y = cdata.player().position.y;
    game_data.destination_map = id;
    game_data.destination_dungeon_level = level;
    levelexitby = 2;
}


} // namespace elona
