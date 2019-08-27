#include "building.hpp"
#include "../util/range.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_map.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace
{

void prepare_house_board_tiles()
{
    std::vector<int> unavailable_tiles{
        15,  16,  24,  25,  26,  27,  28,  29,  30,  92,  93,  94,  95,  141,
        169, 170, 171, 180, 182, 192, 244, 245, 246, 247, 248, 249, 250, 251,
        252, 253, 254, 255, 256, 257, 258, 292, 293, 294, 309, 310, 311, 312,
        313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 327, 328,
        329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342,
        343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356,
        372, 373, 374, 375, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409,
        410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 422, 431, 432, 433,
        434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447,
        448, 449, 450, 451, 452, 453, 454, 455};

    p = 0;
    p(1) = 0;

    gsel(2);

    for (int cnt = 0; cnt < 2772; ++cnt)
    {
        bool available{};
        if (cnt < 231)
        {
            available = true;
        }
        if (cnt >= 396 && cnt < 429)
        {
            available = true;
        }
        if (cnt >= 462 && cnt < 495)
        {
            available = true;
        }
        if (cnt >= 561 && cnt < 726)
        {
            available = true;
        }
        if (!available)
        {
            continue;
        }
        if (chip_data[cnt].kind == 2)
        {
            continue;
        }
        if (chip_data[cnt].kind == 1)
        {
            continue;
        }
        if (chip_data[cnt].kind2 == 5)
        {
            continue;
        }
        if (chip_data[cnt].kind == 3)
        {
            if (game_data.home_scale <= 3)
            {
                continue;
            }
            else
            {
                --p(1);
            }
        }
        ++p(1);
        if (range::find(unavailable_tiles, p(1)) != std::end(unavailable_tiles))
        {
            continue;
        }
        list(0, p) = cnt;
        ++p;
        if (chip_data[cnt].anime_frame != 0)
        {
            cnt = cnt + chip_data[cnt].anime_frame - 1;
            continue;
        }
    }

    listmax = p;
    gsel(0);
}



int calc_heirloom_value(const Item& heirloom)
{
    const auto category = the_item_db[itemid2int(heirloom.id)]->category;

    auto value = heirloom.value;
    switch (category)
    {
    case 60000: return value / 20;
    case 80000: return value / 10;
    case 77000: return value / 10;
    default: return value / 1000;
    }
}



constexpr size_t heirloom_list_size = 10;
using ItemAndValue = std::pair<int, int>;

void add_heirloom_if_valuable_enough(
    std::vector<ItemAndValue>& heirlooms,
    const Item& heirloom)
{
    const auto category = the_item_db[itemid2int(heirloom.id)]->category;
    if (category == 60000)
    {
        game_data.total_deco_value += clamp(heirloom.value / 50, 50, 500);
    }

    const auto value = calc_heirloom_value(heirloom);
    if (heirlooms.back().second < value)
    {
        heirlooms.back() = {heirloom.index, value};
        // Sort by value in descending order. The first item is the most
        // valuable one.
        range::sort(heirlooms, [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    }
}



bool _livestock_will_breed(const Character& breeder, int livestock_count)
{
    const auto B = chara_breed_power(breeder);
    const auto L = livestock_count;

    // The breeder has breed power big enough to breed compared to livestocks
    // count, or if there is no livestocks, new one will be born in low
    // probability regardless of the breed power.
    return (rnd(5000) <= B * 100 / (100 + L * 20) - L * 2) ||
        (L == 0 && rnd(30) == 0);
}

} // namespace



namespace elona
{

int sold = 0;
int rankorg = 0;
int rankcur = 0;

void initialize_home_adata()
{
    p = 7;
    area_data[p].appearance = 143;
    if (game_data.home_scale == 0)
    {
        area_data[p].appearance = 138;
    }
    if (game_data.home_scale == 4)
    {
        area_data[p].appearance = 148;
    }
    if (game_data.home_scale == 5)
    {
        area_data[p].appearance = 144;
    }
    if (game_data.home_scale != 0)
    {
        area_data[p].position.x = cdata.player().position.x;
        area_data[p].position.y = cdata.player().position.y;
    }
    area_data[p].outer_map = game_data.destination_outer_map;
}

static optional<const MapDefData&> _find_map_from_deed(int item_id)
{
    auto id = the_item_db.get_id_from_legacy(item_id);

    optional<int> map_id;
    for (const auto& map : the_mapdef_db.values())
    {
        if (!map.deed)
        {
            continue;
        }

        if (id && *map.deed == *id)
        {
            map_id = map.legacy_id;
            break;
        }
    }

    if (!map_id)
    {
        txt("Cannot find map which is created by item '"s +
                itemid2int(inv[ci].id) + "'."s,
            Message::color(ColorIndex::red));
        return none;
    }

    auto map = the_mapdef_db[*map_id];

    if (!map)
    {
        txt("No such map '"s + *map_id + "'."s,
            Message::color(ColorIndex::red));
        return none;
    }

    return *map;
}

static TurnResult _build_new_home(int home_scale)
{
    game_data.home_scale = home_scale;
    initialize_home_adata();

    std::string midbk = mid;
    mid = ""s + static_cast<int>(mdata_t::MapId::your_home) + u8"_"s + 101;
    ctrl_file(FileOperation::map_delete_preserve_items);
    mid = midbk;

    map_global_prepare();

    levelexitby = 2;
    game_data.destination_map = static_cast<int>(mdata_t::MapId::your_home);
    game_data.destination_dungeon_level = 1;
    game_data.pc_x_in_world_map =
        area_data[static_cast<int>(mdata_t::MapId::your_home)].position.x;
    game_data.pc_y_in_world_map =
        area_data[static_cast<int>(mdata_t::MapId::your_home)].position.y;

    snd("core.build1");
    txt(i18n::s.get("core.building.built_new_house"),
        Message::color{ColorIndex::green});
    msg_halt();

    snd("core.exitmap1");

    return TurnResult::exit_map;
}

static int _find_free_area_slot()
{
    int area_ = -1;

    for (int cnt = 300; cnt < 450; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none)
        {
            area_ = cnt;
            break;
        }
    }

    return area_;
}

TurnResult build_new_building()
{
    if (map_data.type != mdata_t::MapType::world_map)
    {
        txt(i18n::s.get("core.building.can_only_use_in_world_map"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    cell_featread(cdata.player().position.x, cdata.player().position.y);
    if (feat(0) != 0)
    {
        txt(i18n::s.get("core.building.cannot_build_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    area = _find_free_area_slot();
    if (area == -1)
    {
        txt(i18n::s.get("core.building.cannot_build_anymore"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    txt(i18n::s.get("core.building.really_build_it_here"));
    if (!yes_no())
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    if (inv[ci].id == ItemId::deed)
    {
        auto home_scale = inv[ci].param1;
        inv[ci].modify_number(-1);

        return _build_new_home(home_scale);
    }

    ctrl_file(FileOperation::temp_dir_delete_area);
    p = area;

    // Find the map which is generated by the deed and generate the map's area
    // from it.
    optional<const MapDefData&> map =
        _find_map_from_deed(itemid2int(inv[ci].id));

    if (!map)
    {
        return TurnResult::pc_turn_user_error;
    }

    auto& area = area_data[p];
    auto pos = cdata.player().position;
    area_generate_from_mapdef(
        area, *map, game_data.destination_outer_map, pos.x, pos.y);

    s = i18n::s.get_enum("core.building.names", itemid2int(inv[ci].id));
    snd("core.build1");
    txt(i18n::s.get("core.building.built_new", s(0)),
        Message::color{ColorIndex::orange});

    map_global_prepare();
    inv[ci].modify_number(-1);

    return TurnResult::turn_end;
}

void addbuilding(int related_town_quest_id, int building_type, int x, int y)
{
    int slot = -1;
    for (int i = 0; i < 10; ++i)
    {
        if (bddata(0, related_town_quest_id, i) == 0)
        {
            slot = i;
            break;
        }
    }
    if (slot == -1)
    {
        return;
    }

    bddata(0, related_town_quest_id, slot) = building_type;
    bddata(1, related_town_quest_id, slot) = x;
    bddata(2, related_town_quest_id, slot) = y;
    bddata(3, related_town_quest_id, slot) = bdref(0, building_type) + 363;
}

TurnResult show_house_board()
{
    Message::instance().linebreak();
    if (map_data.type != mdata_t::MapType::player_owned)
    {
        txt(i18n::s.get("core.building.house_board.only_use_in_home"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;
    for (const auto& item : inv.ground())
    {
        ++p(2);
        if (item.number() != 0)
        {
            if (the_item_db[itemid2int(item.id)]->category != 60000)
            {
                ++p;
            }
            else
            {
                ++p(1);
            }
        }
    }
    if (map_data.max_item_count != 0)
    {
        p(2) = map_data.max_item_count;
    }
    txt(i18n::s.get(
        "core.building.house_board.item_count",
        mapname(game_data.current_map),
        p(0),
        p(1),
        p(2)));
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        if (getworker(game_data.current_map) != -1)
        {
            txt(i18n::s.get(
                "core.building.shop.current_shopkeeper",
                cdata[getworker(game_data.current_map)]));
        }
        else
        {
            txt(i18n::s.get("core.building.shop.no_assigned_shopkeeper"));
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::ranch)
    {
        if (getworker(game_data.current_map) != -1)
        {
            txt(i18n::s.get(
                "core.building.ranch.current_breeder",
                cdata[getworker(game_data.current_map)]));
        }
        else
        {
            txt(i18n::s.get("core.building.ranch.no_assigned_breeder"));
        }
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        p = 0;
        for (auto&& cnt : cdata.others())
        {
            if (cnt.state() == Character::State::alive ||
                cnt.state() == Character::State::villager_dead)
            {
                if (cnt.character_role != 0)
                {
                    ++p;
                }
            }
        }
        txt(i18n::s.get(
            "core.building.home.staying.count",
            p(0),
            game_data.home_scale + 2));
    }
    Message::instance().linebreak();
    txt(i18n::s.get("core.building.house_board.what_do"));
    p = 0;

    Prompt prompt("core.building.house_board.choices");

    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        prompt.append("assign_a_shopkeeper", 4);
        if (map_data.max_item_count < 400)
        {
            prompt.append(
                i18n::s.get(
                    "core.building.house_board.choices.extend",
                    calcshopreform()),
                5);
        }
    }

    if (area_data[game_data.current_map].id == mdata_t::MapId::ranch)
    {
        prompt.append("assign_a_breeder", 4);
    }

    prompt.append("design", 0);

    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        prompt.append("home_rank", 2);
        prompt.append("allies_in_your_home", 4);
        if (game_data.current_dungeon_level == 1)
        {
            prompt.append("recruit_a_servant", 6);
        }
        prompt.append("move_a_stayer", 3);
    }

    int stat = prompt.query(promptx, prompty, 240);

    if (stat == -1)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    rtval = stat;
    switch (rtval)
    {
    case 0: start_home_map_mode(); break;
    case 2: show_home_value(); break;
    case 3: prompt_move_ally(); break;
    case 4: prompt_ally_staying(); break;
    case 5: try_extend_shop(); break;
    case 6: prompt_hiring(); break;
    }
    tlocinitx = 0;
    tlocinity = 0;
    screenupdate = -1;
    update_screen();
    return TurnResult::show_house_board;
}


void prompt_hiring()
{
    Message::instance().linebreak();
    p = 0;
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::alive ||
            cnt.state() == Character::State::villager_dead)
        {
            if (cnt.character_role != 0)
            {
                ++p;
            }
        }
    }
    if (p >= game_data.home_scale + 2)
    {
        txt(i18n::s.get("core.building.home.hire.too_many_guests"));
        return;
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        randomize(game_data.date.day + cnt);
        if (rnd(2))
        {
            continue;
        }
        if (cnt == 0)
        {
            hire = 0;
        }
        else
        {
            hire = rnd(isethire.size());
        }
        dbid = isethire(hire);
        randomize(game_data.date.day + cnt);
        flt(20);
        int stat = chara_create(-1, dbid, -3, 0);
        if (stat == 0)
        {
            continue;
        }
        cdata[rc].set_state(Character::State::servant_being_selected);
        cdata[rc].character_role = isethirerole(hire);
        if (cdata[rc].id == CharaId::shopkeeper)
        {
            p = rnd(6);
            if (p == 0)
            {
                cdata[rc].character_role = 1001;
                cdatan(0, rc) =
                    i18n::s.get("core.building.guests.armory", cdata[rc]);
            }
            if (p == 1)
            {
                cdata[rc].character_role = 1006;
                cdatan(0, rc) = i18n::s.get(
                    "core.building.guests.general_store", cdata[rc]);
            }
            if (p == 2)
            {
                cdata[rc].character_role = 1004;
                cdatan(0, rc) =
                    i18n::s.get("core.building.guests.magic_store", cdata[rc]);
            }
            if (p == 3)
            {
                cdata[rc].character_role = 1008;
                cdatan(0, rc) =
                    i18n::s.get("core.building.guests.goods_store", cdata[rc]);
            }
            if (p == 4)
            {
                cdata[rc].character_role = 1001;
                cdatan(0, rc) =
                    i18n::s.get("core.building.guests.armory", cdata[rc]);
            }
            if (p == 5)
            {
                cdata[rc].character_role = 1007;
                cdatan(0, rc) =
                    i18n::s.get("core.building.guests.blackmarket", cdata[rc]);
            }
            randomize();
            cdata[rc].shop_rank = rnd(15) + 1;
        }
        for (auto&& cnt : cdata.others())
        {
            if (cnt.index == rc)
            {
                continue;
            }
            if (cnt.state() != Character::State::empty &&
                cdatan(0, cnt.index) == cdatan(0, rc))
            {
                chara_vanquish(rc);
            }
        }
    }
    randomize();
    Message::instance().linebreak();
    txt(i18n::s.get("core.building.home.hire.who"));
    int stat = show_hire_menu(HireOperation::hire);
    if (stat != -1)
    {
        tc = stat;
        Message::instance().linebreak();
        if (cdata.player().gold < calchirecost(tc) * 20)
        {
            txt(i18n::s.get("core.building.not_enough_money"));
        }
        else
        {
            snd("core.paygold1");
            cdata.player().gold -= calchirecost(tc) * 20;
            await(Config::instance().animation_wait * 10);
            cdata[tc].set_state(Character::State::alive);
            txt(i18n::s.get("core.building.home.hire.you_hire", cdata[tc]),
                Message::color{ColorIndex::green});
            snd("core.pray1");
        }
    }
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() == Character::State::servant_being_selected)
        {
            chara_vanquish(cnt.index);
        }
    }
    calccosthire();
}



void fill_tile(int x, int y, int from, int to)
{
    // out of range
    if (x < 0 || map_data.width <= x || y < 0 || map_data.height <= y)
        return;

    if (cell_data.at(x, y).chip_id_actual != from)
        return;

    if ((chip_data[to].effect & 4) != 0 &&
        cell_data.at(x, y).chara_index_plus_one != 0)
        return;

    // Draw one tile.
    cell_data.at(x, y).chip_id_actual = tile;
    cell_data.at(x, y).chip_id_memory = tile;

    // Draw tiles around.
    fill_tile(x - 1, y, from, to);
    fill_tile(x + 1, y, from, to);
    fill_tile(x, y - 1, from, to);
    fill_tile(x, y + 1, from, to);
}



void start_home_map_mode()
{
    const auto pc_position_prev = cdata.player().position;
    homemapmode = 1;

    prepare_house_board_tiles();

    Message::instance().linebreak();
    txt(i18n::s.get("core.building.home.design.help"));

    tlocinitx = cdata.player().position.x;
    tlocinity = cdata.player().position.y;
    tile = 0;
    while (1)
    {
        await(Config::instance().general_wait);
        int stat = target_position();
        if (stat == -1)
        {
            break;
        }

        if (getkey(snail::Key::ctrl))
        {
            if (cell_data.at(tlocx, tlocy).chip_id_actual != tile)
            {
                fill_tile(
                    tlocx,
                    tlocy,
                    cell_data.at(tlocx, tlocy).chip_id_actual,
                    tile);
            }
        }
        else if (chip_data[tile].effect & 4)
        {
            efid = 438;
            magic();
        }
        else
        {
            cell_data.at(tlocx, tlocy).chip_id_actual = tile;
            cell_data.at(tlocx, tlocy).chip_id_memory = tile;
        }
        tlocinitx = tlocx;
        tlocinity = tlocy;
    }

    homemapmode = 0;
    cdata.player().position = pc_position_prev;
}



void show_home_value()
{
    load_background_variants(4);
    gsel(0);
    snd("core.pop2");
    pagesize = 0;
    keyrange = 0;
    key_list = key_cancel;

    windowshadow = 1;
    ui_display_window(
        i18n::s.get("core.building.home.rank.title"),
        i18n::s.get("core.building.home.rank.enter_key") +
            i18n::s.get("core.ui.hint.close"),
        (windoww - 440) / 2 + inf_screenx,
        winposy(360),
        440,
        360);
    display_topic(
        i18n::s.get("core.building.home.rank.value"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.building.home.rank.heirloom_rank"),
        wx + 28,
        wy + 106);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    gmode(2, 50);
    gcopy_c(
        4,
        cmbg / 4 % 4 * 180,
        cmbg / 4 / 4 % 2 * 300,
        180,
        300,
        wx + ww / 4,
        wy + wh / 2,
        x,
        y);
    gmode(2);
    calc_home_rank();
    s(0) = i18n::s.get("core.building.home.rank.type.base");
    s(1) = i18n::s.get("core.building.home.rank.type.deco");
    s(2) = i18n::s.get("core.building.home.rank.type.heir");
    s(3) = i18n::s.get("core.building.home.rank.type.total");
    p(0) = game_data.basic_point_of_home_rank;
    p(1) = game_data.total_deco_value;
    p(2) = game_data.total_heirloom_value;
    p(3) = (p + p(1) + p(2)) / 3;
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        x = wx + 45 + cnt / 2 * 190;
        y = wy + 68 + cnt % 2 * 18;
        font(12 + sizefix - en * 2);
        mes(x, y, s(cnt));
        font(14 - en * 2);
        for (int cnt = 0, cnt_end = cnt + (clamp(p(cnt) / 1000, 1, 10));
             cnt < cnt_end;
             ++cnt)
        {
            bmes(
                i18n::s.get("core.building.home.rank.star"),
                x + 35 + cnt * 13 + en * 8,
                y - 2,
                {255, 255, 50});
        }
    }
    font(12 + sizefix - en * 2);
    listmax = 10;
    sort_list_by_column1();
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p = list(0, 10 - cnt - 1);
        if (p == 0)
        {
            continue;
        }

        draw_item_with_portrait_scale_height(
            inv[p], wx + 37, cnt * 16 + wy + 138);

        mes(wx + 68,
            cnt * 16 + wy + 138,
            i18n::s.get("core.building.home.rank.place", cnvrank(cnt + 1)));
        mes(wx + 110, cnt * 16 + wy + 138, itemname(p));
    }

    while (1)
    {
        redraw();
        auto action = cursor_check_ex();
        if (action == "cancel")
        {
            break;
        }
    }
}



void prompt_move_ally()
{
    while (true)
    {
        Message::instance().linebreak();
        txt(i18n::s.get("core.building.home.move.who"));
        int stat = show_hire_menu(HireOperation::move);
        if (stat == -1)
        {
            break;
        }
        if (cdata[stat].relationship <= -3)
        {
            Message::instance().linebreak();
            txt(i18n::s.get(
                    "core.building.home.move.dont_touch_me", cdata[stat]),
                Message::color{ColorIndex::cyan});
            break;
        }
        const auto tchome = stat;
        tc = stat;
        snd("core.ok1");
        while (true)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.building.home.move.where", cdata[stat]));
            int stat = target_position();
            if (stat == -1)
            {
                continue;
            }
            if (chip_data.for_cell(tlocx, tlocy).effect & 4 ||
                cell_data.at(tlocx, tlocy).chara_index_plus_one != 0)
            {
                txt(i18n::s.get("core.building.home.move.invalid"));
            }
            else
            {
                break;
            }
        }
        tc = tchome;
        cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .chara_index_plus_one = 0;
        cell_data.at(tlocx, tlocy).chara_index_plus_one = tc + 1;
        cdata[tc].position = cdata[tc].initial_position =
            Position{tlocx, tlocy};
        cdata[tc].activity.finish();
        Message::instance().linebreak();
        txt(i18n::s.get("core.building.home.move.is_moved", cdata[tc]));
        snd("core.foot");
    }
}



void prompt_ally_staying()
{
    {
        int stat = ctrl_ally(ControlAllyOperation::staying);
        if (stat != -1)
        {
            int c = stat;
            snd("core.ok1");
            Message::instance().linebreak();
            if (getworker(game_data.current_map, c) == c)
            {
                if (game_data.current_map == mdata_t::MapId::your_home)
                {
                    cdata[c].current_map = 0;
                    txt(i18n::s.get(
                        "core.building.home.staying.remove.ally", cdata[c]));
                }
                else
                {
                    removeworker(game_data.current_map);
                    txt(i18n::s.get(
                        "core.building.home.staying.remove.worker", cdata[c]));
                }
            }
            else
            {
                if (game_data.current_map == mdata_t::MapId::your_home)
                {
                    cdata[c].initial_position.x = cdata[c].position.x;
                    cdata[c].initial_position.y = cdata[c].position.y;
                    txt(i18n::s.get(
                        "core.building.home.staying.add.ally", cdata[c]));
                }
                else
                {
                    removeworker(game_data.current_map);
                    txt(i18n::s.get(
                        "core.building.home.staying.add.worker", cdata[c]));
                }
                cdata[c].current_map = game_data.current_map;
            }
        }
    }
}

void try_extend_shop()
{
    Message::instance().linebreak();
    if (cdata.player().gold < calcshopreform())
    {
        txt(i18n::s.get("core.building.not_enough_money"));
    }
    else
    {
        snd("core.paygold1");
        cdata.player().gold -= calcshopreform();
        map_data.max_item_count = clamp(map_data.max_item_count + 10, 1, 400);
        txt(i18n::s.get("core.building.shop.extend", map_data.max_item_count),
            Message::color{ColorIndex::green});
    }
}



void update_shop_and_report()
{
    area = -1;
    std::string midbk = mid;
    for (int cnt = 300; cnt < 450; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::shop)
        {
            area = cnt;
            mid = ""s + area + u8"_"s + 101;
            show_shop_log();
        }
    }
    mid = midbk;
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        update_shop();
    }
}

void show_shop_log()
{
    int shoplv = 0;
    int customer = 0;
    int dblistmax = 0;
    const auto worker = getworker(area);
    std::string shop_mark =
        u8"["s + i18n::s.get("core.building.shop.info") + u8"]"s;
    if (worker == -1)
    {
        txt(shop_mark + i18n::s.get("core.building.shop.log.no_shopkeeper"));
        return;
    }
    sold = 0;
    income(0) = 0;
    income(1) = 0;
    listmax = 0;
    shoplv = 100 - game_data.ranks.at(5) / 100;
    customer = 0;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        customer += rnd(shoplv / 3 + 5);
    }
    customer = customer * (80 + sdata(17, worker) * 3 / 2) / 100;
    if (customer < 1)
    {
        customer = 1;
    }
    if (game_data.current_map != area)
    {
        ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
        ctrl_file(FileOperation2::map_items_read, u8"inv_"s + mid + u8".s2");
    }
    mode = 6;
    dblistmax = 0;
    for (const auto& item : inv.ground())
    {
        if (item.number() <= 0)
        {
            continue;
        }
        if (item.id == ItemId::shop_strongbox)
        {
            continue;
        }
        if (item.id == ItemId::register_)
        {
            continue;
        }
        if (item.id == ItemId::book_b)
        {
            continue;
        }
        if (item.id == ItemId::gold_piece)
        {
            continue;
        }
        if (item.id == ItemId::shelter)
        {
            continue;
        }
        if (item.id == ItemId::deed)
        {
            continue;
        }
        if (item.weight < 0)
        {
            continue;
        }
        if (item.quality >= Quality::special)
        {
            continue;
        }
        if (item.value < 50)
        {
            continue;
        }
        int category = the_item_db[itemid2int(item.id)]->category;
        if (category == 60000)
        {
            continue;
        }
        dblist(0, dblistmax) = item.index;
        dblist(1, dblistmax) = category;
        ++dblistmax;
    }
    for (int cnt = 0, cnt_end = (customer); cnt < cnt_end; ++cnt)
    {
        if (dblistmax == 0)
        {
            break;
        }
        p = rnd(dblistmax);
        ci = dblist(0, p);
        int category = dblist(1, p);
        int val0 = calcitemvalue(ci, 2);
        val0 = val0 * int((10 + std::sqrt(sdata(156, worker) * 200))) / 100;
        if (val0 <= 1)
        {
            continue;
        }
        if (rnd(val0) > shoplv * 100 + 500)
        {
            continue;
        }
        if (inv[ci].number() <= 0)
        {
            continue;
        }
        if (rnd(8))
        {
            continue;
        }
        in = rnd(inv[ci].number()) + 1;
        inv[ci].modify_number((-in));
        sold += in;
        val0 = val0 * in;
        if (rnd(4) == 0)
        {
            list(0, listmax) = the_item_db[itemid2int(inv[ci].id)]->level;
            list(1, listmax) = static_cast<int>(inv[ci].quality);
            listn(0, listmax) = std::to_string(category);
            listn(1, listmax) = std::to_string(val0);
            ++listmax;
        }
        else
        {
            income += val0;
        }
        if (area == game_data.current_map)
        {
            for (auto&& cnt : cdata.all())
            {
                if (cnt.state() != Character::State::alive)
                {
                    continue;
                }
                if (!cnt.activity || cnt.activity.turn == 0)
                {
                    continue;
                }
                if (cnt.activity.item == ci)
                {
                    cdata[cnt.index].activity.finish();
                }
            }
        }
    }
    mode = 0;
    if (game_data.current_map != area)
    {
        ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
    }
    else
    {
        ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    }
    tmpload(filepathutil::u8path(u8"shop5.s2"));
    if (fs::exists(filesystem::dirs::tmp() / u8"shop5.s2"))
    {
        ctrl_file(FileOperation2::map_items_read, u8"shop5.s2");
    }
    else
    {
        for (auto&& item : inv.ground())
        {
            item.remove();
        }
    }
    mode = 6;
    if (income != 0)
    {
        flt();
        itemcreate(-1, 54, -1, -1, income);
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt(list(0, cnt2), static_cast<Quality>(list(1, cnt2)));
            flttypemajor = elona::stoi(listn(0, cnt2));
            nostack = 1;
            if (itemcreate(-1, 0, -1, -1, 0))
            {
                if (inv[ci].value > elona::stoi(listn(1, cnt2)) * 2)
                {
                    item_stack(-1, ci);
                    f = 1;
                    break;
                }
                else
                {
                    inv[ci].remove();
                    if (cnt == 3)
                    {
                        f = 0;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                f = 0;
                break;
            }
        }
        if (f == 0)
        {
            itemcreate(-1, 54, -1, -1, elona::stoi(listn(1, cnt)));
            income += elona::stoi(listn(1, cnt));
        }
        else
        {
            ++income(1);
        }
    }
    if (sold == 0)
    {
        if (!Config::instance().hide_shop_updates)
        {
            txt(shop_mark +
                i18n::s.get(
                    "core.building.shop.log.could_not_sell",
                    customer,
                    cdata[worker]));
        }
    }
    else
    {
        if (!Config::instance().hide_shop_updates)
        {
            s = i18n::s.get("core.building.shop.log.gold", income(0));
            if (income(1) != 0)
            {
                s += i18n::s.get("core.building.shop.log.and_items", income(1));
            }
            snd("core.ding2");
            txt(shop_mark +
                    i18n::s.get(
                        "core.building.shop.log.sold_items",
                        customer,
                        cdata[worker],
                        sold,
                        s(0)),
                Message::color{ColorIndex::orange});
        }
        chara_gain_skill_exp(
            cdata[worker], 156, clamp(int(std::sqrt(income(0))) * 6, 25, 1000));
    }
    if (sold > (110 - game_data.ranks.at(5) / 100) / 10)
    {
        modrank(5, 30, 2);
    }
    mode = 0;
    ctrl_file(FileOperation2::map_items_write, u8"shop5.s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
}

void update_shop()
{
    map_data.max_crowd_density = (100 - game_data.ranks.at(5) / 100) / 4 + 1;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, y).item_appearances_actual = 0;
            cell_data.at(cnt, y).light = 0;
        }
    }
    for (const auto& item : inv.ground())
    {
        if (item.number() <= 0)
        {
            continue;
        }
        x = item.position.x;
        y = item.position.y;
        if (x < 0 || x >= map_data.width || y < 0 || y >= map_data.height)
        {
            continue;
        }
        cell_refresh(x, y);
    }
}

void calc_collection_value(bool val0)
{
    rc = 56;
    fixlv = Quality::good;
    chara_db_set_stats(int2charaid(dbid));
    ++dblist(val0 ? 1 : 0, charaid2int(cdata.tmp().id));
    if (fixlv == Quality::special)
    {
        rtval = 70 + cdata.tmp().level;
    }
    else
    {
        rtval = cdata.tmp().level / 10 + 2;
        if (draw_get_rect_chara(cdata.tmp().image % 1000)->height > inf_tiles)
        {
            rtval = rtval / 2 * 3 + 40;
        }
        p = the_character_db[charaid2int(cdata.tmp().id)]->rarity / 1000;
        if (p < 80)
        {
            rtval = rtval + 80 - p;
        }
    }
    if (dblist(val0 ? 1 : 0, charaid2int(cdata.tmp().id)) > 1)
    {
        rtval /= 3;
        if (rtval > 15)
        {
            rtval = 15;
        }
    }
}

void update_museum()
{
    rankorg = game_data.ranks.at(3);
    rankcur = 0;
    DIM3(dblist, 2, 800);
    for (const auto& item : inv.ground())
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (item.id != ItemId::figurine && item.id != ItemId::card)
        {
            continue;
        }
        if (wpeek(
                cell_data.at(item.position.x, item.position.y)
                    .item_appearances_actual,
                0) != item.image)
        {
            continue;
        }
        dbid = item.subname;
        calc_collection_value(item.id != ItemId::figurine);
        if (item.id == ItemId::figurine)
        {
            rankcur += rtval;
        }
        else
        {
            rankcur += rtval / 2;
        }
    }
    rankcur = 10000 - int(std::sqrt(rankcur) * 100);
    if (rankcur < 100)
    {
        rankcur = 100;
    }
    game_data.ranks.at(3) = rankcur;
    if (rankorg != rankcur)
    {
        if (rankorg > rankcur)
        {
            Message::instance().txtef(ColorIndex::green);
        }
        else
        {
            Message::instance().txtef(ColorIndex::purple);
        }
        Message::instance().linebreak();
        txt(i18n::s.get(
            "core.building.museum.rank_change",
            cnvrank(rankorg / 100),
            cnvrank(rankcur / 100),
            ranktitle(3),
            rankn(10, 3)));
    }
    map_data.max_crowd_density = (100 - game_data.ranks.at(3) / 100) / 2 + 1;
}



void calc_home_rank()
{
    if (game_data.current_dungeon_level != 1)
    {
        return;
    }
    rankorg = game_data.ranks.at(4);
    rankcur = 0;
    game_data.total_deco_value = 0;
    game_data.total_heirloom_value = 0;

    std::vector<ItemAndValue> heirlooms{heirloom_list_size};
    for (const auto& item : inv.ground())
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (wpeek(
                cell_data.at(item.position.x, item.position.y)
                    .item_appearances_actual,
                0) != item.image)
        {
            continue;
        }

        add_heirloom_if_valuable_enough(heirlooms, item);
    }
    size_t i{};
    for (const auto& heirloom : heirlooms)
    {
        list(0, static_cast<int>(i)) = heirloom.first;
        list(1, static_cast<int>(i)) = heirloom.second;
        ++i;
    }

    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (list(0, cnt) != 0)
        {
            game_data.total_heirloom_value += clamp(list(1, cnt), 100, 2000);
        }
    }
    if (game_data.total_deco_value > 10000)
    {
        game_data.total_deco_value = 10000;
    }
    if (game_data.total_heirloom_value > 10000)
    {
        game_data.total_heirloom_value = 10000;
    }
    rankcur = 10000 -
        (game_data.basic_point_of_home_rank + game_data.total_deco_value +
         game_data.total_heirloom_value) /
            3;
    if (rankcur < 100)
    {
        rankcur = 100;
    }
    game_data.ranks.at(4) = rankcur;
    if (rankorg != rankcur)
    {
        if (rankorg > rankcur)
        {
            Message::instance().txtef(ColorIndex::green);
        }
        else
        {
            Message::instance().txtef(ColorIndex::purple);
        }
        Message::instance().linebreak();
        txt(i18n::s.get(
            "core.building.home.rank.change",
            game_data.total_deco_value / 100,
            game_data.total_heirloom_value / 100,
            cnvrank(rankorg / 100),
            cnvrank(rankcur / 100),
            ranktitle(4),
            rankn(10, 4)));
    }
}



void update_ranch()
{
    int livestock_count = 0;
    for (auto&& chara : cdata.all())
    {
        if (chara.state() == Character::State::alive && chara.is_livestock())
        {
            ++livestock_count;
        }
    }

    const auto worker = getworker(game_data.current_map);
    for (int i = 0; i < renewmulti; ++i)
    {
        if (worker != -1 &&
            _livestock_will_breed(cdata[worker], livestock_count))
        {
            flt(calcobjlv(cdata[worker].level), Quality::bad);
            if (rnd(2))
            {
                dbid = charaid2int(cdata[worker].id);
            }
            else
            {
                dbid = 0;
            }
            if (rnd(10) != 0)
            {
                fltnrace = cdatan(2, worker);
            }
            if (cdata[worker].id == CharaId::little_sister)
            {
                // Little sister -> younger sister
                dbid = 176;
            }
            int stat = chara_create(-1, dbid, 4 + rnd(11), 4 + rnd(8));
            if (stat != 0)
            {
                cdata[rc].is_livestock() = true;
                ++livestock_count;
            }
        }

        int egg_or_milk_count = 0;
        for (auto&& chara : cdata.all())
        {
            if (chara.state() != Character::State::alive)
            {
                continue;
            }
            if (!chara.is_livestock())
            {
                continue;
            }
            x = rnd(11) + 4;
            y = rnd(8) + 4;
            if (cell_data.at(x, y).item_appearances_actual != 0)
            {
                continue;
            }
            flt(calcobjlv(chara.level), Quality::good);
            if (rnd(egg_or_milk_count + 1) > 2)
            {
                continue;
            }
            if (livestock_count > 10)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock_count > 20)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock_count > 30)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock_count > 40)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            switch (rnd(5))
            {
            case 0:
                // Egg
                if (rnd(60) == 0 ||
                    (cdatan(2, chara.index) == "core.chicken" && rnd(20) == 0))
                {
                    ++egg_or_milk_count;
                    if (itemcreate(-1, 573, x, y, 0))
                    {
                        inv[ci].subname = charaid2int(chara.id);
                        inv[ci].weight = chara.weight * 10 + 250;
                        inv[ci].value = clamp(
                            chara.weight * chara.weight / 10000, 200, 40000);
                    }
                }
                break;
            case 1:
                // Milk
                if (rnd(60) == 0 ||
                    (cdatan(2, chara.index) == "core.sheep" && rnd(20) == 0))
                {
                    ++egg_or_milk_count;
                    if (itemcreate(-1, 574, x, y, 0))
                    {
                        inv[ci].subname = charaid2int(chara.id);
                    }
                }
                break;
            case 2:
                // Shit
                if (rnd(80) == 0)
                {
                    if (itemcreate(-1, 575, x, y, 0))
                    {
                        inv[ci].subname = charaid2int(chara.id);
                        inv[ci].weight = chara.weight * 40 + 300;
                        inv[ci].value =
                            clamp(chara.weight * chara.weight / 5000, 1, 20000);
                    }
                }
                break;
            case 3:
                // Garbage
                if (rnd(80) == 0)
                {
                    dbid = 222;
                    if (rnd(2))
                    {
                        dbid = 45;
                    }
                    itemcreate(-1, dbid, x, y, 0);
                }
                break;
            case 4:
                // Do nothing.
                break;
            }
        }
    }
}

} // namespace elona
