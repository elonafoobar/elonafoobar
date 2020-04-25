#include "map.hpp"

#include "ability.hpp"
#include "activity.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "command.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_map.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "equipment.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_event/lua_event_nefia_created.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "position.hpp"
#include "quest.hpp"
#include "save.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

int dx_at_m136 = 0;
int dy_at_m136 = 0;



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



// see character.cpp
extern int traveldone;



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
        chara_clear_status_effects_b(cnt);
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


static void _generate_bad_quality_item(Character& chara)
{
    flt(calcobjlv(chara.level), calcfixlv(Quality::bad));
    if (const auto item = itemcreate_chara_inv(chara.index, 0, 0))
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
        generatemoney(cnt);
        if (cnt.id == CharaId::bard)
        {
            _proc_generate_bard_items(cnt);
        }
        if (rnd(5) == 0)
        {
            supply_new_equipment(cnt);
        }
        if (rnd(2) == 0 && inv_sum(cnt.index) < 8)
        {
            _generate_bad_quality_item(cnt);
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
        flt();
        if (const auto chara = chara_create(-1, 345, 48, 19))
        {
            chara->role = Role::other;
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 348, 30, 17))
        {
            chara->role = Role::other;
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 174, 38, 19))
        {
            chara->only_christmas() = true;
            chara->is_hung_on_sand_bag() = true;
            cdatan(0, chara->index) = i18n::s.get("core.chara.job.fanatic");
        }
        flt();
        if (const auto chara = chara_create(-1, 347, 35, 19))
        {
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 347, 37, 18))
        {
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 347, 37, 21))
        {
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 347, 39, 20))
        {
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 347, 38, 21))
        {
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 70, 17, 8))
        {
            chara->ai_calm = 3;
            chara->only_christmas() = true;
            chara->role = Role::food_vendor;
            chara->shop_rank = 10;
            cdatan(0, chara->index) = snfood(cdatan(0, chara->index));
        }
        flt();
        if (const auto chara = chara_create(-1, 239, 25, 8))
        {
            chara->ai_calm = 3;
            chara->relationship = 0;
            chara->original_relationship = 0;
            chara->only_christmas() = true;
            chara->role = Role::souvenir_vendor;
            chara->shop_rank = 30;
            cdatan(0, chara->index) = random_name();
            cdatan(0, chara->index) = i18n::s.get(
                "core.chara.job.souvenir_vendor", cdatan(0, chara->index));
        }
        flt();
        if (const auto chara = chara_create(-1, 271, 24, 22))
        {
            chara->ai_calm = 3;
            chara->relationship = 0;
            chara->original_relationship = 0;
            chara->only_christmas() = true;
            chara->role = Role::souvenir_vendor;
            chara->shop_rank = 30;
            cdatan(0, chara->index) = random_name();
            cdatan(0, chara->index) = i18n::s.get(
                "core.chara.job.souvenir_vendor", cdatan(0, chara->index));
        }
        flt();
        if (const auto chara = chara_create(-1, 1, 38, 12))
        {
            chara->ai_calm = 3;
            chara->role = Role::blackmarket_vendor;
            chara->shop_rank = 10;
            cdatan(0, chara->index) = snblack(cdatan(0, chara->index));
            chara->only_christmas() = true;
        }
        flt();
        if (const auto chara = chara_create(-1, 271, 28, 9))
        {
            chara->ai_calm = 3;
            chara->relationship = 0;
            chara->original_relationship = 0;
            chara->only_christmas() = true;
            chara->role = Role::street_vendor;
            chara->shop_rank = 30;
            cdatan(0, chara->index) = random_name();
            cdatan(0, chara->index) = i18n::s.get(
                "core.chara.job.street_vendor", cdatan(0, chara->index));
        }
        flt();
        if (const auto chara = chara_create(-1, 271, 29, 24))
        {
            chara->ai_calm = 3;
            chara->relationship = 0;
            chara->original_relationship = 0;
            chara->only_christmas() = true;
            chara->role = Role::street_vendor;
            chara->shop_rank = 30;
            cdatan(0, chara->index) = random_name();
            cdatan(0, chara->index) = i18n::s.get(
                "core.chara.job.street_vendor2", cdatan(0, chara->index));
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            flt();
            if (const auto chara = chara_create(-1, 349, -3, 0))
            {
                chara->only_christmas() = true;
            }
            flt();
            if (const auto chara = chara_create(-1, 350, -3, 0))
            {
                chara->only_christmas() = true;
            }
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            flt();
            if (const auto chara = chara_create(-1, 326, -3, 0))
            {
                chara->only_christmas() = true;
            }
        }
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            flt();
            if (const auto chara = chara_create(-1, 335, -3, 0))
            {
                chara->only_christmas() = true;
            }
            flt();
            if (const auto chara = chara_create(-1, 185, -3, 0))
            {
                chara->only_christmas() = true;
            }
            flt();
            if (const auto chara = chara_create(-1, 274, -3, 0))
            {
                chara->only_christmas() = true;
            }
            flt();
            if (const auto chara = chara_create(-1, 174, -3, 0))
            {
                chara->only_christmas() = true;
            }
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            if (const auto chara = chara_create(-1, 332, -3, 0))
            {
                chara->only_christmas() = true;
            }
            flt();
            if (const auto chara = chara_create(-1, 185, -3, 0))
            {
                chara->only_christmas() = true;
            }
        }
    }
    else
    {
        for (auto&& cnt : cdata.others())
        {
            if (cnt.only_christmas())
            {
                chara_vanquish(cnt);
            }
        }
    }
}



static void _create_nefia(int index, int x, int y)
{
    area = index;
    ctrl_file(FileOperation::temp_dir_delete_area);

    auto& area = area_data[index];
    const auto& map = the_mapdef_db.ensure("core.random_dungeon");

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



void addefmap(int x, int y, int efmap0, int efmap1, int efmap2, int efmap3)
{
    efmap(0, x, y) = efmap0;
    efmap(1, x, y) = efmap1;
    efmap(2, x, y) = efmap2;
    efmap(3, x, y) = efmap3;
}



void spillblood(int x, int y, int range)
{
    for (int cnt = 0, cnt_end = (range + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = x;
            dy_at_m136 = y;
        }
        else
        {
            dx_at_m136 = x + rnd(2) - rnd(2);
            dy_at_m136 = y + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0 ||
            dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chip_data.for_cell(dx_at_m136, dy_at_m136).wall_kind)
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10 < 5)
        {
            ++cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments;
        }
    }
}



void spillfrag(int x, int y, int range)
{
    for (int cnt = 0, cnt_end = (range + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = x;
            dy_at_m136 = y;
        }
        else
        {
            dx_at_m136 = x + rnd(2) - rnd(2);
            dy_at_m136 = y + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0 ||
            dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chip_data.for_cell(dx_at_m136, dy_at_m136).wall_kind)
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10 < 4)
        {
            cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments =
                cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10 +
                (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10 +
                 1) *
                    10;
        }
    }
}



TurnResult exit_map()
{
    int previous_map = game_data.current_map;
    int previous_dungeon_level = game_data.current_dungeon_level;
    int fixstart = 0;

    ELONA_LOG("map") << "exit_map levelexitby begin " << levelexitby << " cur "
                     << game_data.current_map << " cur_level "
                     << game_data.current_dungeon_level;

    game_data.left_minutes_of_executing_quest = 0;
    game_data.rogue_boss_encountered = 0;
    if (map_data.type == mdata_t::MapType::player_owned)
    {
        maybe_show_ex_help(1);
    }
    if (map_data.type == mdata_t::MapType::temporary)
    {
        rq = game_data.executing_immediate_quest;
        quest_exit_map();
    }
    Message::instance().buffered_message_begin("  ");
    if (game_data.current_map == mdata_t::MapId::show_house ||
        game_data.current_map == mdata_t::MapId::arena ||
        game_data.current_map == mdata_t::MapId::pet_arena)
    {
        usermapid = 0;
    }
    rdtry = 0;
    fixstart = 0;
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            if (area_data[game_data.current_map].has_been_conquered > 0)
            {
                chara_vanquish(
                    cdata[area_data[game_data.current_map].has_been_conquered]);
                area_data[game_data.current_map].has_been_conquered = -1;
            }
        }
    }
    game_data.previous_map = game_data.current_map;
    if (game_data.previous_map == mdata_t::MapId::shelter_)
    {
        game_data.current_map = game_data.previous_map2;
        game_data.current_dungeon_level = game_data.previous_dungeon_level;
        mapstartx = game_data.previous_x;
        mapstarty = game_data.previous_y;
        game_data.entrance_type = 7;
        fixstart = 1;
        levelexitby = 5;
    }
    if (levelexitby == 4)
    {
        cell_featread(cdata.player().position.x, cdata.player().position.y);
        if (game_data.current_map == mdata_t::MapId::your_home)
        {
            if (mapitemfind(cdata.player().position, ItemId::downstairs))
            {
                feat(1) = 11;
                feat(2) = 0;
            }
            if (mapitemfind(cdata.player().position, ItemId::upstairs))
            {
                feat(1) = 10;
                feat(2) = 0;
            }
        }
        f = 0;
        if (feat(1) == 11)
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.misc.walk_down_stairs"));
            f = 1;
            game_data.entrance_type = 1;
            map_data.stair_down_pos =
                cdata.player().position.y * 1000 + cdata.player().position.x;
            if (feat(2) == 0)
            {
                ++game_data.current_dungeon_level;
                game_data.current_dungeon_level -=
                    (area_data[game_data.current_map].entrance == 2) * 2;
            }
            else
            {
                game_data.current_dungeon_level = feat(2);
            }
        }
        if (feat(1) == 10)
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.misc.walk_up_stairs"));
            f = 1;
            game_data.entrance_type = 2;
            map_data.stair_up_pos =
                cdata.player().position.y * 1000 + cdata.player().position.x;
            if (feat(2) == 0)
            {
                --game_data.current_dungeon_level;
                game_data.current_dungeon_level +=
                    (area_data[game_data.current_map].entrance == 2) * 2;
            }
            else
            {
                game_data.current_dungeon_level = feat(2);
            }
        }
        if (f == 0)
        {
            if (map_data.type == mdata_t::MapType::world_map)
            {
                game_data.pc_x_in_world_map = cdata.player().position.x;
                game_data.pc_y_in_world_map = cdata.player().position.y;
                game_data.current_dungeon_level = 1;
                if (feat(2) != 0 || feat(3) != 0)
                {
                    game_data.current_map = feat(2) + feat(3) * 100;
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::the_void)
                    {
                        if (!itemfind(0, 742))
                        {
                            txt(i18n::s.get(
                                "core.action.exit_map.not_permitted"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::pyramid)
                    {
                        if (game_data.quest_flags.pyramid_trial == 0)
                        {
                            txt(i18n::s.get(
                                "core.action.exit_map.no_invitation_to_pyramid"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::jail)
                    {
                        txt(i18n::s.get(
                            "core.action.exit_map.cannot_enter_jail"));
                        msg_halt();
                        game_data.current_map =
                            static_cast<int>(mdata_t::MapId::fields);
                    }
                }
                else
                {
                    game_data.current_map =
                        static_cast<int>(mdata_t::MapId::fields);
                }
                if (feat(1) != 15)
                {
                    game_data.current_map =
                        static_cast<int>(mdata_t::MapId::fields);
                }
            }
            if (map_data.type == mdata_t::MapType::town ||
                map_data.type == mdata_t::MapType::field ||
                map_data.type == mdata_t::MapType::player_owned ||
                map_data.type == mdata_t::MapType::shelter ||
                map_data.type == mdata_t::MapType::guild)
            {
                game_data.current_map = game_data.destination_outer_map;
            }
        }
        if (mdata_t::is_nefia(map_data.type) ||
            map_data.type == static_cast<int>(mdata_t::MapType::shelter))
        {
            if (game_data.current_dungeon_level <
                area_data[game_data.current_map].danger_level)
            {
                game_data.current_map = game_data.destination_outer_map;
            }
        }
        if (area_data[game_data.current_map].type == mdata_t::MapType::town)
        {
            if (game_data.current_map == game_data.previous_map)
            {
                if (game_data.current_dungeon_level == 1)
                {
                    Message::instance().buffered_message_append(i18n::s.get(
                        "core.action.exit_map.surface.returned_to",
                        mapname(game_data.current_map)));
                }
                else
                {
                    Message::instance().buffered_message_append(i18n::s.get(
                        "core.action.exit_map.surface.left",
                        mapname(game_data.current_map)));
                }
            }
        }
    }
    if (map_data.type == mdata_t::MapType::temporary)
    {
        game_data.current_map = game_data.previous_map2;
        game_data.current_dungeon_level = game_data.previous_dungeon_level;
        mapstartx = game_data.previous_x;
        mapstarty = game_data.previous_y;
        game_data.entrance_type = 7;
        fixstart = 1;
    }
    if (levelexitby == 2)
    {
        game_data.current_map = game_data.destination_map;
        game_data.current_dungeon_level = game_data.destination_dungeon_level;
        if (game_data.executing_immediate_quest_type == 0)
        {
            if (game_data.previous_map !=
                static_cast<int>(mdata_t::MapId::fields))
            {
                game_data.pc_x_in_world_map =
                    area_data[game_data.current_map].position.x;
                game_data.pc_y_in_world_map =
                    area_data[game_data.current_map].position.y;
                weather_changes_by_location(false);
            }
        }
        if (game_data.current_map == mdata_t::MapId::jail)
        {
            mapstartx = 29;
            mapstarty = 3;
            game_data.entrance_type = 7;
            fixstart = 1;
        }
    }
    if (cdata.player().state() == Character::State::empty)
    {
        revive_player(cdata.player());
        game_data.current_map = static_cast<int>(mdata_t::MapId::your_home);
        game_data.destination_outer_map =
            area_data[static_cast<int>(mdata_t::MapId::your_home)].outer_map;
        game_data.current_dungeon_level = 1;
    }
    if (rdtry > 1)
    {
        Message::instance().buffered_message_append(
            u8"(再生成"s + rdtry + u8"回)"s);
    }
    if (game_data.current_map != game_data.previous_map)
    {
        if (map_is_town_or_guild() ||
            game_data.previous_map == mdata_t::MapId::your_home ||
            game_data.departure_date == 0)
        {
            game_data.departure_date = game_data.date.hours();
            game_data.distance_between_town = 0;
            game_data.left_town_map = game_data.previous_map;
        }
        if (area_data[game_data.current_map].type !=
                mdata_t::MapType::world_map &&
            area_data[game_data.current_map].type != mdata_t::MapType::field &&
            game_data.current_map != mdata_t::MapId::show_house)
        {
            save_set_autosave();
        }
        if (map_data.type != mdata_t::MapType::world_map)
        {
            if (map_data.type != mdata_t::MapType::field ||
                map_data.type == mdata_t::MapType::player_owned)
            {
                if (fixtransfermap == 0)
                {
                    game_data.pc_x_in_world_map =
                        area_data[game_data.previous_map].position.x;
                    game_data.pc_y_in_world_map =
                        area_data[game_data.previous_map].position.y;
                }
                else
                {
                    fixtransfermap = 0;
                }
            }
        }
        if (fixstart == 0)
        {
            game_data.entrance_type = area_data[game_data.current_map].entrance;
        }
        if (event_find(6))
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.delivered_to_your_home"));
            weather_changes_by_location(false);
        }
        else if (
            area_data[game_data.previous_map].type ==
            mdata_t::MapType::world_map)
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.entered",
                mapname(game_data.current_map)));
        }
        else if (map_data.type == mdata_t::MapType::temporary)
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.returned_to",
                mapname(game_data.current_map)));
        }
        else
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.left", mapname(game_data.previous_map)));
        }
        if (game_data.cargo_weight > game_data.current_cart_limit)
        {
            if (area_data[game_data.current_map].type ==
                    mdata_t::MapType::world_map ||
                area_data[game_data.current_map].type ==
                    mdata_t::MapType::field)
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.exit_map.burdened_by_cargo"));
            }
        }
    }
    if (game_data.current_map == mdata_t::MapId::larna)
    {
        if (game_data.current_dungeon_level == 2)
        {
            game_data.current_map =
                static_cast<int>(mdata_t::MapId::mountain_pass);
            game_data.current_dungeon_level =
                area_data[game_data.current_map].deepest_level - 1;
            game_data.entrance_type = 1;
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.mountain_pass"));
        }
    }
    if (game_data.current_map == mdata_t::MapId::mountain_pass)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            game_data.current_map = static_cast<int>(mdata_t::MapId::larna);
            game_data.current_dungeon_level = 1;
            game_data.entrance_type = 2;
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.larna"));
        }
    }
    for (auto&& chara : cdata.player_and_allies())
    {
        chara.hate = 0;
        chara.enemy_id = 0;
        chara.activity.finish();
        if (chara.state() != Character::State::alive)
        {
            if (chara.state() == Character::State::pet_in_other_map)
            {
                chara.set_state(Character::State::alive);
            }
            continue;
        }
        cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one =
            0;
        if (chara.index != 0)
        {
            if (chara.current_map != 0)
            {
                chara.set_state(Character::State::pet_moving_to_map);
            }
        }
    }
    if (map_data.refresh_type == 1)
    {
        // This map should be saved.
        save_map_local_data();

        ELONA_LOG("map") << "exit_map save local";
    }
    else
    {
        // This is a temporary map, so wipe its data (shelter, special
        // quest instance)
        prepare_charas_for_map_unload();

        tmpload(filepathutil::u8path("mdata_" + mid + ".s2"));
        // delete all map-local data
        if (fs::exists(filesystem::dirs::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            ctrl_file(FileOperation::map_delete);
        }

        // forget about all NPCs that were here
        for (auto&& cnt : cdata.others())
        {
            if (cnt.state() != Character::State::empty)
            {
                --npcmemory(1, charaid2int(cnt.id));
            }
        }

        ELONA_LOG("map") << "exit_map clear temporary";
    }

    bool map_changed = game_data.current_map != previous_map ||
        game_data.current_dungeon_level != previous_dungeon_level;

    ELONA_LOG("map") << "exit_map levelexitby end " << levelexitby << " cur "
                     << game_data.current_map << " cur_level "
                     << game_data.current_dungeon_level << " prev "
                     << previous_map << " prev_level "
                     << previous_dungeon_level;

    // Only trigger the map unload event if the map was changed. The map might
    // not change if access to it is refused (jail, pyramid, etc.).
    if (map_changed)
    {
        lua::lua->get_event_manager().trigger(
            lua::BaseEvent("core.before_map_unload"));
    }

    mode = 2;
    return TurnResult::initialize_map;
}


void prepare_charas_for_map_unload()
{
    // interrupt continuous actions
    for (int cnt = 0; cnt < 57; ++cnt)
    {
        cdata[cnt].activity.finish();
        cdata[cnt].ai_item = 0;
    }

    // remove living adventurers from the map and set their states
    for (auto&& adv : cdata.adventurers())
    {
        if (adv.state() == Character::State::alive)
        {
            cell_data.at(adv.position.x, adv.position.y).chara_index_plus_one =
                0;
            adv.set_state(Character::State::adventurer_in_other_map);
        }
    }
}



void map_global_proc_diastrophism()
{
    if (game_data.reset_world_map_in_diastrophism_flag == 1)
    {
        initialize_adata();
        map_global_prepare();
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            area_data[cnt].id = static_cast<int>(mdata_t::MapId::none);
        }
    }
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
        {
            if (area_data[cnt].has_been_conquered != -1)
            {
                ++p;
            }
        }
    }
    if (p <= 25 || rnd(150) == 0 || game_data.diastrophism_flag != 0 ||
        game_data.reset_world_map_in_diastrophism_flag)
    {
        game_data.diastrophism_flag = 0;
        Message::instance().buffered_message_append(
            i18n::s.get("core.action.move.global.diastrophism"));
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
            {
                if (rnd(5) == 0 || area_data[cnt].has_been_conquered == -1)
                {
                    area_data[cnt].id = static_cast<int>(mdata_t::MapId::none);
                }
            }
        }
        initialize_world_map();
        map_global_prepare();
    }
    game_data.reset_world_map_in_diastrophism_flag = 0;
}



void map_global_prepare()
{
    map_clear_material_spots_and_light();
    map_global_place_entrances();
}



void map_global_place_entrances()
{
    draw_prepare_map_chips();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        int cnt2 = cnt;
        if (game_data.destination_outer_map != 4)
        {
            break;
        }
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (bddata(0, cnt2, cnt) != 0)
            {
                p = bddata(0, cnt2, cnt);
                cell_featset(
                    bddata(1, cnt2, cnt),
                    bddata(2, cnt2, cnt),
                    bddata(3, cnt2, cnt),
                    34,
                    cnt2,
                    cnt);
            }
        }
    }
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none ||
            area_data[cnt].appearance == 0)
        {
            continue;
        }
        if (area_data[cnt].outer_map != game_data.destination_outer_map)
        {
            continue;
        }
        if (area_data[cnt].id == 900)
        {
            area_data[cnt].id = 40;
            continue;
        }
        if (area_data[cnt].id >= 900)
        {
            area_data[cnt].id -= 800;
            continue;
        }
        if (area_data[cnt].position.x <= 0 || area_data[cnt].position.y <= 0 ||
            area_data[cnt].position.x >= map_data.width ||
            area_data[cnt].position.y >= map_data.height)
        {
            area_data[cnt].position.x = map_data.width / 2;
            area_data[cnt].position.y = map_data.height / 2;
        }
        p = cnt;
        if (chip_data
                    .for_cell(
                        area_data[cnt].position.x, area_data[cnt].position.y)
                    .effect &
                4 ||
            cell_data.at(area_data[cnt].position.x, area_data[cnt].position.y)
                    .feats != 0)
        {
            for (int cnt = 0;; ++cnt)
            {
                dx = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.width);
                dy = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.height);
                x = area_data[p].position.x + rnd(dx(0)) - rnd(dx(0));
                y = area_data[p].position.y + rnd(dy) - rnd(dy);
                if (x <= 0 || y <= 0 || x >= map_data.width - 1 ||
                    y >= map_data.height - 1)
                {
                    continue;
                }
                if (33 <= cell_data.at(x, y).chip_id_actual &&
                    cell_data.at(x, y).chip_id_actual < 66)
                {
                    continue;
                }
                if (chip_data.for_cell(x, y).effect & 4)
                {
                    continue;
                }
                if (cell_data.at(x, y).feats != 0)
                {
                    continue;
                }
                area_data[p].position.x = x;
                area_data[p].position.y = y;
                break;
            }
        }
        cell_featset(
            area_data[cnt].position.x,
            area_data[cnt].position.y,
            area_data[cnt].appearance,
            15,
            cnt % 100,
            cnt / 100);
        if (area_data[cnt].type == mdata_t::MapType::town ||
            area_data[cnt].type == mdata_t::MapType::guild)
        {
            cell_data.at(area_data[cnt].position.x, area_data[cnt].position.y)
                .light = 11;
        }
    }
}



void map_clear_material_spots_and_light()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_featread(x, y);
            // material spot
            if (feat(1) < 24 || feat(1) > 28)
            {
                cell_data.at(x, y).feats = 0;
            }
            cell_data.at(x, y).light = 0;
        }
    }
}



void try_to_return()
{
    int stat = quest_is_return_forbidden();
    if (stat == 1)
    {
        txt(i18n::s.get("core.misc.return.forbidden"));
        if (!yes_no())
        {
            update_screen();
            return;
        }
    }
    Prompt prompt;
    p = 0;
    p = 0;
    i = 7;
    if (area_data[i].outer_map == game_data.destination_outer_map)
    {
        list(0, p) = i;
        list(1, p) = 1;
        prompt.append(mapname(i));
        ++p;
    }
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        i = 500 - (cnt + 1);
        if (area_data[i].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[i].outer_map != game_data.destination_outer_map)
        {
            continue;
        }
        if (area_data[i].id == mdata_t::MapId::your_home)
        {
            continue;
        }
        if (area_data[i].visited_deepest_level == 0)
        {
            continue;
        }
        f = 0;
        if (area_data[i].can_return_to())
        {
            f = 1;
        }
        if (game_data.wizard)
        {
            if (area_data[i].can_return_to_if_wizard())
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            list(0, p) = i;
            list(1, p) = area_data[i].visited_deepest_level;
            auto text = mapname(i) + u8" "s +
                cnvrank(
                            (area_data[i].visited_deepest_level -
                             area_data[i].danger_level + 1)) +
                i18n::s.get("core.misc.dungeon_level");
            prompt.append(text);
            ++p;
        }
    }
    listmax = p;
    if (listmax == 0)
    {
        txt(i18n::s.get("core.misc.return.no_location"));
        return;
    }
    txt(i18n::s.get("core.misc.return.where_do_you_want_to_go"));
    rtval = prompt.query(promptx, prompty, 240);
    update_screen();
    if (rtval >= 0)
    {
        txt(i18n::s.get("core.misc.return.air_becomes_charged"));
        if (area_data[game_data.current_map].id ==
            mdata_t::MapId::random_dungeon)
        {
            if (game_data.current_dungeon_level ==
                area_data[game_data.current_map].deepest_level)
            {
                if (area_data[game_data.current_map].has_been_conquered != -1)
                {
                    txt(i18n::s.get(
                        "core.misc.return.lord_of_dungeon_might_disappear"));
                }
            }
        }
        game_data.destination_map = list(0, rtval);
        game_data.destination_dungeon_level = list(1, rtval);
        game_data.is_returning_or_escaping = 15 + rnd(15);
    }
    update_screen();
}



void map_global_proc_travel_events(Character& chara)
{
    if (!chara.activity)
    {
        chara.activity.type = Activity::Type::travel;
        chara.activity.turn = 20;
        if (game_data.weather == 3)
        {
            chara.activity.turn = chara.activity.turn * 13 / 10;
        }
        if (game_data.weather == 4)
        {
            chara.activity.turn = chara.activity.turn * 16 / 10;
        }
        if (game_data.weather == 2 ||
            chip_data.for_cell(chara.position.x, chara.position.y).kind == 4)
        {
            chara.activity.turn = chara.activity.turn * 22 / 10;
        }
        if (game_data.weather == 1)
        {
            chara.activity.turn = chara.activity.turn * 5 / 10;
        }
        chara.activity.turn = chara.activity.turn * 100 /
            (100 + game_data.seven_league_boot_effect + sdata(182, 0));
        return;
    }
    if (cdata.player().nutrition <= 5000)
    {
        for (auto&& item : inv.for_chara(chara))
        {
            if (item.number() == 0)
            {
                continue;
            }
            if (the_item_db[itemid2int(item.id)]->category ==
                ItemCategory::travelers_food)
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get("core.misc.finished_eating", chara, item));
                }
                activity_eating_finish(chara, item);
                break;
            }
        }
    }
    if (game_data.weather == 2 ||
        chip_data.for_cell(chara.position.x, chara.position.y).kind == 4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0 ||
                    cdata.player().gravity > 0)
                {
                    txt(i18n::s.get(
                            "core.action.move.global.weather.snow.sound"),
                        Message::color{ColorIndex::cyan});
                    chara.activity.turn += 10;
                }
            }
            if (rnd(1000) == 0)
            {
                txt(i18n::s.get("core.action.move.global.weather.snow.message"),
                    Message::color{ColorIndex::purple});
                chara.activity.turn += 50;
            }
        }
        if (cdata.player().nutrition <= 2000)
        {
            if (cdata.player().has_anorexia() == 0)
            {
                snd("core.eat1");
                txt(i18n::s.get("core.action.move.global.weather.snow.eat"));
                chara.nutrition += 5000;
                show_eating_message(chara);
                status_ailment_damage(
                    cdata.player(), StatusAilment::dimmed, 1000);
            }
        }
    }
    if (game_data.weather == 4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0 ||
                    cdata.player().gravity > 0)
                {
                    txt(i18n::s.get(
                            "core.action.move.global.weather.heavy_rain.sound"),
                        Message::color{ColorIndex::cyan});
                    chara.activity.turn += 5;
                }
            }
            if (cdata.player().confused == 0)
            {
                if (rnd(500) == 0)
                {
                    txt(i18n::s.get(
                            "core.action.move.global.weather.heavy_rain.message"),
                        Message::color{ColorIndex::purple});
                    cdata.player().confused = 10;
                }
            }
            else if (rnd(5) == 0)
            {
                cdata.player().confused = 10;
            }
        }
        cdata.player().blind = 3;
    }
    if (chara.activity.turn > 0)
    {
        ++game_data.date.minute;
        return;
    }
    traveldone = 1;
    game_data.distance_between_town += 4;
    chara.activity.finish();
}



void sense_map_feats_on_move(Character& chara)
{
    if (chara.index != 0)
        return;

    game_data.player_x_on_map_leave = -1;
    game_data.player_y_on_map_leave = -1;
    x = cdata.player().position.x;
    y = cdata.player().position.y;
    if (cell_data.at(x, y).item_appearances_actual != 0)
    {
        if (cdata.player().blind == 0)
        {
            txt(txtitemoncell(x, y));
            proc_autopick();
        }
        else
        {
            txt(i18n::s.get("core.action.move.sense_something"));
        }
    }
    p = chip_data.for_cell(x, y).kind;
    if (p != 0)
    {
        std::string tname = ""s;
        if (p == 1)
        {
            tname = i18n::s.get("core.map.chip.dryrock");
        }
        if (p == 2)
        {
            tname = i18n::s.get("core.map.chip.field");
        }

        if (tname != ""s)
        {
            txt(i18n::s.get("core.action.move.walk_into", tname));
        }
        if (p == 3)
        {
            snd("core.water2");
        }
        if (p == 4)
        {
            addefmap(chara.position.x, chara.position.y, 3, 10, dirsub, rnd(2));
            if (keybd_wait <=
                    g_config.walk_wait() * g_config.start_run_wait() ||
                cdata.player().turn % 2 == 0 ||
                map_data.type == mdata_t::MapType::world_map)
            {
                sound_footstep2(foot);
                foot += 1 + rnd(2);
            }
        }
    }
    else if (map_data.type == mdata_t::MapType::world_map)
    {
        addefmap(chara.position.x, chara.position.y, 2, 10, dirsub);
        sound_footstep(foot);
        ++foot;
    }
    if (cell_data.at(x, y).feats != 0)
    {
        cell_featread(x, y);
        if (feat(1) == 32)
        {
            txt(i18n::s.get("core.action.move.twinkle"),
                Message::color{ColorIndex::orange});
        }
        if (feat(1) == 15)
        {
            txt(mapname(feat(2) + feat(3) * 100, true));
            if (area_data[feat(2) + feat(3) * 100].id ==
                mdata_t::MapId::random_dungeon)
            {
                maybe_show_ex_help(6);
            }
        }
        if (feat(1) == 34)
        {
            txt(txtbuilding(feat(2), feat(3)));
        }
        if (feat(1) == 11)
        {
            txt(i18n::s.get("core.action.move.feature.stair.down"));
        }
        if (feat(1) == 10)
        {
            txt(i18n::s.get("core.action.move.feature.stair.up"));
        }
        if (feat(1) == 24)
        {
            txt(i18n::s.get("core.action.move.feature.material.spot"));
        }
        if (feat(1) == 27)
        {
            txt(i18n::s.get("core.action.move.feature.material.remains"));
        }
        if (feat(1) == 25)
        {
            txt(i18n::s.get("core.action.move.feature.material.mining"));
        }
        if (feat(1) == 26)
        {
            txt(i18n::s.get("core.action.move.feature.material.spring"));
        }
        if (feat(1) == 28)
        {
            txt(i18n::s.get("core.action.move.feature.material.plants"));
        }
        if (feat(1) == 29)
        {
            if (feat(2) == 36)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.vegetable");
            }
            if (feat(2) == 37)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.fruit");
            }
            if (feat(2) == 38)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.herb");
            }
            if (feat(2) == 39)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.strange");
            }
            if (feat(2) == 40)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.artifact");
            }
            if (feat(2) == 41)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.gem");
            }
            if (feat(2) == 42)
            {
                s = i18n::s.get("core.action.move.feature.seed.type.magic");
            }
            if (feat == tile_plant)
            {
                txt(i18n::s.get(
                    "core.action.move.feature.seed.growth.seed", s(0)));
            }
            if (feat == tile_plant + 1)
            {
                txt(i18n::s.get(
                    "core.action.move.feature.seed.growth.bud", s(0)));
            }
            if (feat == tile_plant + 2)
            {
                txt(i18n::s.get(
                    "core.action.move.feature.seed.growth.tree", s(0)));
            }
            if (feat == tile_plant + 3)
            {
                txt(i18n::s.get(
                    "core.action.move.feature.seed.growth.withered", s(0)));
            }
        }
        if (feat(1) >= 24 && feat(1) <= 28)
        {
            maybe_show_ex_help(5);
        }
    }
}

} // namespace elona
