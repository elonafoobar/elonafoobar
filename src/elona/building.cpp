#include "building.hpp"

#include "../util/range.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "area.hpp"
#include "attack.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_map.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "keybind/keybind.hpp"
#include "lua_env/lua_env.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapeditor/design_mode.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "random.hpp"
#include "save.hpp"
#include "save_fs.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

const std::vector<std::pair<int, Role>> isethire = {
    {205, Role::maid},
    {70, Role::bartender},
    {74, Role::healer},
    {41, Role::appraiser},
    {69, Role::informer},
    {76, Role::guard},
    {1, Role::general_store},
    {1, Role::general_store},
    {1, Role::general_store},
};



int calc_heirloom_value(const ItemRef& heirloom)
{
    const auto category = the_item_db[heirloom->id]->category;

    auto value = heirloom->value;
    switch (category)
    {
    case ItemCategory::furniture: return value / 20;
    case ItemCategory::tree: return value / 10;
    case ItemCategory::ore: return value / 10;
    default: return value / 1000;
    }
}



constexpr size_t heirloom_list_size = 10;

// @a heirlooms are sorted by value in descending order. The first item is the
// most valuable one.
void add_heirloom_if_valuable_enough(
    std::vector<HomeRankHeirloom>& heirlooms,
    const ItemRef& heirloom)
{
    const auto category = the_item_db[heirloom->id]->category;
    if (category == ItemCategory::furniture)
    {
        game_data.total_deco_value += clamp(heirloom->value / 50, 50, 500);
    }

    const auto value = calc_heirloom_value(heirloom);
    if (heirlooms.size() < heirloom_list_size)
    {
        heirlooms.push_back({heirloom, value});
        range::sort(heirlooms, [](const auto& a, const auto& b) {
            return a.value > b.value;
        });
    }
    else if (heirlooms.back().value < value)
    {
        heirlooms.back() = {heirloom, value};
        range::sort(heirlooms, [](const auto& a, const auto& b) {
            return a.value > b.value;
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



int calc_num_of_shop_customers(int shop_level, const Character& shopkeeper)
{
    int ret = 0;
    for (int _i = 0; _i < 3; ++_i)
    {
        ret += rnd(shop_level / 3 + 5);
    }
    ret = ret * (80 + shopkeeper.get_skill(17).level * 3 / 2) / 100;
    if (ret < 1)
    {
        ret = 1;
    }
    return ret;
}



struct ItemForSale
{
    ItemRef item;
    ItemCategory category;


    ItemForSale(const ItemRef& item, ItemCategory category)
        : item(item)
        , category(category)
    {
    }
};



std::vector<ItemForSale> list_items_for_sale()
{
    std::vector<ItemForSale> ret;

    for (const auto& item : g_inv.ground())
    {
        if (item->id == "core.shop_strongbox")
        {
            continue;
        }
        if (item->id == "core.register")
        {
            continue;
        }
        if (item->id == "core.book_b")
        {
            continue;
        }
        if (item->id == "core.gold_piece")
        {
            continue;
        }
        if (item->id == "core.shelter")
        {
            continue;
        }
        if (item->id == "core.deed")
        {
            continue;
        }
        if (item->weight < 0)
        {
            continue;
        }
        if (item->quality >= Quality::special)
        {
            continue;
        }
        if (item->value < 50)
        {
            continue;
        }

        const auto category = the_item_db[item->id]->category;
        if (category == ItemCategory::furniture)
        {
            continue;
        }

        ret.emplace_back(item, category);
    }

    return ret;
}



int calc_item_price_per_one(const ItemRef& item, const Character& shopkeeper)
{
    const auto V = calcitemvalue(item, 2);
    const auto I = shopkeeper.get_skill(156).level;

    return V * static_cast<int>(10 + std::sqrt(I * 200)) / 100;
}



struct SoldItem
{
    int level;
    Quality quality;
    ItemCategory category;
    int total_price;


    SoldItem(int level, Quality quality, ItemCategory category, int total_price)
        : level(level)
        , quality(quality)
        , category(category)
        , total_price(total_price)
    {
    }
};

} // namespace



elona_vector1<int> fsetincome;
elona_vector1<int> fsetplantartifact;
elona_vector1<int> fsetplantunknown;


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
        area_data[p].position = cdata.player().position;
    }
    area_data[p].outer_map = game_data.destination_outer_map;
}

static optional_ref<const MapDefData> _find_map_from_deed(int item_id)
{
    auto id = the_item_db.get_id_from_integer(item_id);

    optional<int> map_id;
    for (const auto& map : the_mapdef_db.values())
    {
        if (!map.deed)
        {
            continue;
        }

        if (id && *map.deed == *id)
        {
            map_id = map.integer_id;
            break;
        }
    }

    if (!map_id)
    {
        txt("Cannot find map which is created by item '"s +
                std::to_string(item_id) + "'."s,
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
    ctrl_file_map_delete_preserve_items();
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

TurnResult build_new_building(const ItemRef& deed)
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

    if (deed->id == "core.deed")
    {
        auto home_scale = deed->param1;
        deed->modify_number(-1);

        return _build_new_home(home_scale);
    }

    ctrl_file_temp_dir_delete_area();
    p = area;

    // Find the map which is generated by the deed and generate the map's area
    // from it.
    const auto map = _find_map_from_deed(the_item_db[deed->id]->integer_id);

    if (!map)
    {
        return TurnResult::pc_turn_user_error;
    }

    auto& area = area_data[p];
    auto pos = cdata.player().position;
    area_generate_from_mapdef(
        area, *map, game_data.destination_outer_map, pos.x, pos.y);

    s = i18n::s.get_enum(
        "core.building.names", the_item_db[deed->id]->integer_id);
    snd("core.build1");
    txt(i18n::s.get("core.building.built_new", s(0)),
        Message::color{ColorIndex::orange});

    map_global_prepare();
    deed->modify_number(-1);

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
    p(2) = 400;
    for (const auto& item : g_inv.ground())
    {
        if (the_item_db[item->id]->category != ItemCategory::furniture)
        {
            ++p;
        }
        else
        {
            ++p(1);
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
                if (cnt.role != Role::none)
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
    case 0: mapeditor::start_home_map_mode(); break;
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
            if (cnt.role != Role::none)
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
        const auto chara_id = isethire.at(hire).first;
        randomize(game_data.date.day + cnt);
        flt(20);
        const auto servant = chara_create(-1, chara_id, -3, 0);
        if (!servant)
        {
            continue;
        }
        servant->set_state(Character::State::servant_being_selected);
        servant->role = isethire.at(hire).second;
        if (servant->id == CharaId::shopkeeper)
        {
            p = rnd(6);
            if (p == 0)
            {
                servant->role = Role::blacksmith;
                servant->name =
                    i18n::s.get("core.building.guests.armory", *servant);
            }
            if (p == 1)
            {
                servant->role = Role::general_vendor;
                servant->name =
                    i18n::s.get("core.building.guests.general_store", *servant);
            }
            if (p == 2)
            {
                servant->role = Role::magic_vendor;
                servant->name =
                    i18n::s.get("core.building.guests.magic_store", *servant);
            }
            if (p == 3)
            {
                servant->role = Role::general_store;
                servant->name =
                    i18n::s.get("core.building.guests.goods_store", *servant);
            }
            if (p == 4)
            {
                servant->role = Role::blacksmith;
                servant->name =
                    i18n::s.get("core.building.guests.armory", *servant);
            }
            if (p == 5)
            {
                servant->role = Role::blackmarket_vendor;
                servant->name =
                    i18n::s.get("core.building.guests.blackmarket", *servant);
            }
            randomize();
            servant->shop_rank = rnd(15) + 1;
        }
        for (const auto& chara : cdata.others())
        {
            if (chara.index == servant->index)
            {
                continue;
            }
            if (chara.state() != Character::State::empty &&
                chara.name == servant->name)
            {
                chara_vanquish(*servant);
                break;
            }
        }
    }
    randomize();
    Message::instance().linebreak();
    txt(i18n::s.get("core.building.home.hire.who"));
    int stat = show_hire_menu(HireOperation::hire);
    if (stat != -1)
    {
        Message::instance().linebreak();
        if (cdata.player().gold < calc_servant_hire_cost(cdata[stat]) * 20)
        {
            txt(i18n::s.get("core.building.not_enough_money"));
        }
        else
        {
            snd("core.paygold1");
            cdata.player().gold -= calc_servant_hire_cost(cdata[stat]) * 20;
            await(g_config.animation_wait() * 10);
            cdata[stat].set_state(Character::State::alive);
            txt(i18n::s.get("core.building.home.hire.you_hire", cdata[stat]),
                Message::color{ColorIndex::green});
            snd("core.pray1");
        }
    }
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() == Character::State::servant_being_selected)
        {
            chara_vanquish(cnt);
        }
    }
    calccosthire();
}



void show_home_value()
{
    load_background_variants(4);
    gsel(0);
    snd("core.pop2");
    pagesize = 0;
    keyrange = 0;
    key_list = keybind_get_bound_key_name("cancel");

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

    const auto heirlooms = building_update_home_rank();
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

    int i = 0;
    for (const auto& [heirloom, _value] : heirlooms)
    {
        draw_item_with_portrait_scale_height(
            heirloom, wx + 37, i * 16 + wy + 138);
        mes(wx + 68,
            i * 16 + wy + 138,
            i18n::s.get("core.building.home.rank.place", cnvrank(i + 1)));
        mes(wx + 110, i * 16 + wy + 138, itemname(heirloom));
        ++i;
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
        snd("core.ok1");
        bool canceled = false;
        while (true)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.building.home.move.where", cdata[stat]));
            int stat = target_position();
            if (stat == -1)
            {
                canceled = true;
                break;
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
        if (canceled)
        {
            continue;
        }
        cell_data.at(cdata[tchome].position.x, cdata[tchome].position.y)
            .chara_index_plus_one = 0;
        cell_data.at(tlocx, tlocy).chara_index_plus_one = tchome + 1;
        cdata[tchome].position = cdata[tchome].initial_position =
            Position{tlocx, tlocy};
        cdata[tchome].activity.finish();
        Message::instance().linebreak();
        txt(i18n::s.get("core.building.home.move.is_moved", cdata[tchome]));
        snd("core.foot");
    }
}



void prompt_ally_staying()
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
                cdata[c].initial_position = cdata[c].position;
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
    const auto worker = getworker(area);
    if (worker == -1)
    {
        txt(i18n::s.get("core.building.shop.log.no_shopkeeper"));
        return;
    }

    if (game_data.current_map != area)
    {
        ctrl_file_map_items_write(u8"shoptmp.s2");
        ctrl_file_map_items_read(fs::u8path(u8"inv_"s + mid + u8".s2"));
    }
    mode = 6;

    const auto shop_level = 100 - game_data.ranks.at(5) / 100;
    const auto num_of_customers =
        calc_num_of_shop_customers(shop_level, cdata[worker]);

    const auto items_for_sale = list_items_for_sale();

    int total_profit = 0;
    int total_sold_items = 0;

    std::vector<SoldItem> sold_items;

    for (int _i = 0; _i < num_of_customers; ++_i)
    {
        if (items_for_sale.empty())
        {
            break;
        }

        const auto& item_for_sale = choice(items_for_sale);

        const auto price_per_one =
            calc_item_price_per_one(item_for_sale.item, cdata[worker]);
        if (price_per_one <= 1)
        {
            continue; // too cheep
        }
        if (rnd_capped(price_per_one) > shop_level * 100 + 500)
        {
            continue; // too expensive
        }
        if (item_for_sale.item->number() <= 0)
        {
            continue; // sold out
        }
        if (rnd(8))
        {
            continue;
        }

        const auto num = rnd_capped(item_for_sale.item->number()) + 1;
        item_for_sale.item->modify_number(-num);
        total_sold_items += num;
        const auto total_price = price_per_one * num;

        if (rnd(4) == 0)
        {
            sold_items.emplace_back(
                the_item_db[item_for_sale.item->id]->level,
                item_for_sale.item->quality,
                item_for_sale.category,
                total_price);
        }
        else
        {
            total_profit += total_price;
        }

        if (area == game_data.current_map)
        {
            for (auto&& chara : cdata.all())
            {
                if (chara.state() != Character::State::alive)
                {
                    continue;
                }
                if (!chara.activity || chara.activity.turn == 0)
                {
                    continue;
                }
                if (chara.activity.item == item_for_sale.item)
                {
                    chara.activity.finish();
                }
            }
        }
    }

    mode = 0;
    if (game_data.current_map != area)
    {
        ctrl_file_map_items_write(fs::u8path(u8"inv_"s + mid + u8".s2"));
        ctrl_file_map_items_read(u8"shoptmp.s2");
    }

    inv_open_tmp_inv("shop5.s2");
    mode = 6;

    if (total_profit != 0)
    {
        flt();
        itemcreate_tmp_inv(54, total_profit);
    }

    int num_of_exchanged_items = 0;

    for (const auto& sold_item : sold_items)
    {
        bool generated = false;
        for (int i = 0; i < 4; ++i)
        {
            flt(sold_item.level, sold_item.quality);
            flttypemajor = static_cast<int>(sold_item.category);
            nostack = 1;
            if (const auto item = itemcreate_tmp_inv(0, 0))
            {
                if (item->value > sold_item.total_price * 2)
                {
                    inv_stack(g_inv.tmp(), item.unwrap());
                    generated = true;
                    break;
                }
                else
                {
                    item->remove();
                }
            }
            else
            {
                break;
            }
        }
        if (generated)
        {
            ++num_of_exchanged_items;
        }
        else
        {
            itemcreate_tmp_inv(54, sold_item.total_price);
            total_profit += sold_item.total_price;
        }
    }

    if (total_sold_items == 0)
    {
        if (!g_config.hide_shop_updates())
        {
            txt(i18n::s.get(
                "core.building.shop.log.could_not_sell",
                num_of_customers,
                cdata[worker]));
        }
    }
    else
    {
        if (!g_config.hide_shop_updates())
        {
            auto s = i18n::s.get("core.building.shop.log.gold", total_profit);
            if (num_of_exchanged_items != 0)
            {
                s += i18n::s.get(
                    "core.building.shop.log.and_items", num_of_exchanged_items);
            }
            snd("core.ding2");
            txt(i18n::s.get(
                    "core.building.shop.log.sold_items",
                    num_of_customers,
                    cdata[worker],
                    total_sold_items,
                    s),
                Message::color{ColorIndex::orange});
        }
        chara_gain_skill_exp(
            cdata[worker],
            156,
            clamp(int(std::sqrt(total_profit)) * 6, 25, 1000));
    }

    if (total_sold_items > (110 - game_data.ranks.at(5) / 100) / 10)
    {
        modrank(5, 30, 2);
    }

    mode = 0;
    inv_close_tmp_inv("shop5.s2");
}



void update_shop()
{
    map_data.max_crowd_density = (100 - game_data.ranks.at(5) / 100) / 4 + 1;
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).item_info_actual.clear();
            // TODO phantom_ref
            cell_data.at(x, y).item_info_memory.clear();
            cell_data.at(x, y).light = 0;
        }
    }
    for (const auto& item : g_inv.ground())
    {
        x = item->position().x;
        y = item->position().y;
        if (x < 0 || x >= map_data.width || y < 0 || y >= map_data.height)
        {
            continue;
        }
        cell_refresh(x, y);
    }
}



void calc_collection_value(int chara_id, bool val0)
{
    fixlv = Quality::good;
    chara_db_set_stats(cdata.tmp(), int2charaid(chara_id));
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
    for (const auto& item : g_inv.ground())
    {
        if (item->id != "core.figurine" && item->id != "core.card")
        {
            continue;
        }
        if (cell_data.at(item->position().x, item->position().y)
                .item_info_actual.stack_count() != 1)
        {
            continue;
        }
        calc_collection_value(item->subname, item->id != "core.figurine");
        if (item->id == "core.figurine")
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



std::vector<HomeRankHeirloom> building_update_home_rank()
{
    if (game_data.current_dungeon_level != 1)
    {
        return {};
    }
    rankorg = game_data.ranks.at(4);
    rankcur = 0;
    game_data.total_deco_value = 0;
    game_data.total_heirloom_value = 0;

    std::vector<HomeRankHeirloom> heirlooms;
    for (const auto& item : g_inv.ground())
    {
        if (cell_data.at(item->position().x, item->position().y)
                .item_info_actual.stack_count() != 1)
        {
            continue;
        }

        add_heirloom_if_valuable_enough(heirlooms, item);
    }

    for (const auto& [_, value] : heirlooms)
    {
        game_data.total_heirloom_value += clamp(value, 100, 2000);
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

    return heirlooms;
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
            int chara_id;
            if (rnd(2))
            {
                chara_id = charaid2int(cdata[worker].id);
            }
            else
            {
                chara_id = 0;
            }
            if (rnd(10) != 0)
            {
                fltnrace = cdata[worker].race.get();
            }
            if (cdata[worker].id == CharaId::little_sister)
            {
                // Little sister -> younger sister
                chara_id = 176;
            }
            if (const auto chara =
                    chara_create(-1, chara_id, 4 + rnd(11), 4 + rnd(8)))
            {
                chara->is_livestock() = true;
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
            if (!cell_data.at(x, y).item_info_actual.is_empty())
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
                    (chara.race == "core.chicken" && rnd(20) == 0))
                {
                    ++egg_or_milk_count;
                    if (const auto item = itemcreate_map_inv(573, x, y, 0))
                    {
                        item->subname = charaid2int(chara.id);
                        item->weight = chara.weight * 10 + 250;
                        item->value = clamp(
                            chara.weight * chara.weight / 10000, 200, 40000);
                    }
                }
                break;
            case 1:
                // Milk
                if (rnd(60) == 0 ||
                    (chara.race == "core.sheep" && rnd(20) == 0))
                {
                    ++egg_or_milk_count;
                    if (const auto item = itemcreate_map_inv(574, x, y, 0))
                    {
                        item->subname = charaid2int(chara.id);
                    }
                }
                break;
            case 2:
                // Shit
                if (rnd(80) == 0)
                {
                    if (const auto item = itemcreate_map_inv(575, x, y, 0))
                    {
                        item->subname = charaid2int(chara.id);
                        item->weight = chara.weight * 40 + 300;
                        item->value =
                            clamp(chara.weight * chara.weight / 5000, 1, 20000);
                    }
                }
                break;
            case 3:
                // Garbage
                if (rnd(80) == 0)
                {
                    int item_id = 222;
                    if (rnd(2))
                    {
                        item_id = 45;
                    }
                    itemcreate_map_inv(item_id, x, y, 0);
                }
                break;
            case 4:
                // Do nothing.
                break;
            }
        }
    }
}



int calcincome(int rank_id)
{
    int rank_amount = 100 - game_data.ranks.at(rank_id) / 100;
    if (rank_amount == 99)
    {
        rank_amount = rank_amount * 70;
    }
    else
    {
        rank_amount = rank_amount * 50;
    }
    if (rank_id == 2)
    {
        rank_amount = rank_amount * 120 / 100;
    }
    if (rank_id == 4)
    {
        rank_amount = rank_amount * 60 / 100;
    }
    if (rank_id == 0)
    {
        rank_amount = rank_amount * 80 / 100;
    }
    if (rank_id == 1)
    {
        rank_amount = rank_amount * 70 / 100;
    }
    if (rank_id == 6)
    {
        rank_amount = rank_amount * 25 / 100;
    }
    if (rank_id == 5)
    {
        rank_amount = rank_amount * 20 / 100;
    }
    if (rank_id == 8)
    {
        rank_amount = rank_amount * 15 / 100;
    }
    return rank_amount;
}



void supply_income()
{
    invfile = 4;
    inv_open_tmp_inv("shop4.s2");
    mode = 6;
    income(0) = 0;
    income(1) = 0;
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (game_data.ranks.at(cnt) >= 10000)
        {
            continue;
        }
        p = calcincome(cnt) + rnd_capped(calcincome(cnt) / 3 + 1) -
            rnd_capped(calcincome(cnt) / 3 + 1);
        income += p;
        flt();
        itemcreate_tmp_inv(54, p);
        if (cnt == 5 || cnt == 6)
        {
            continue;
        }
        if (cnt == 5 || cnt == 6 || cnt == 3)
        {
            continue;
        }
        p = rnd(rnd(3) + 1) + 1;
        int rank_id = cnt;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            int item_id = 0;
            flt(calcobjlv((100 - game_data.ranks.at(rank_id) / 100) / 2 + 1),
                calcfixlv(
                    (rnd(12) < trait(39)) ? Quality::miracle : Quality::great));
            flttypemajor = choice(fsetincome);
            if (rnd(5) == 0)
            {
                flttypemajor = choice(fsetwear);
            }
            if (rnd(100 + game_data.ranks.at(rank_id) / 5) < 2)
            {
                item_id = 559;
            }
            itemcreate_tmp_inv(item_id, 0);
            ++income(1);
        }
    }
    if (cdata.player().fame > 0)
    {
        p = clamp(cdata.player().fame / 10, 100, 25000);
        if (cdata.player().fame >= 25000)
        {
            p += (cdata.player().fame - 25000) / 100;
        }
        income += p;
        flt();
        itemcreate_tmp_inv(54, p);
    }
    if (income != 0 || income(1) != 0)
    {
        snd("core.ding2");
        if (income(1) == 0)
        {
            txt(i18n::s.get("core.misc.income.sent_to_your_house", income(0)),
                Message::color{ColorIndex::orange});
        }
        else
        {
            txt(i18n::s.get(
                    "core.misc.income.sent_to_your_house2",
                    income(0),
                    income(1)),
                Message::color{ColorIndex::orange});
        }
        save_trigger_autosaving();
    }
    if (game_data.date.day == 1)
    {
        if (cdata.player().level > 5)
        {
            save_trigger_autosaving();
            if (!g_inv.tmp().has_free_slot())
            {
                inv_compress(g_inv.tmp());
            }
            flt();
            if (const auto item = itemcreate_tmp_inv(615, 0))
            {
                item->subname =
                    game_data.cost_to_hire + calccostbuilding() + calccosttax();
                item->subname = item->subname * (100 + rnd(20)) / 100;
            }
            mode = 0;
            ++game_data.left_bill;
            txt(i18n::s.get("core.misc.tax.bill"));
            if (game_data.left_bill > 1)
            {
                if (game_data.left_bill <= 4)
                {
                    if (game_data.left_bill > 3)
                    {
                        s(0) = i18n::s.get("core.misc.tax.warning");
                        s(1) = i18n::s.get("core.misc.tax.have_to_go_embassy");
                    }
                    else
                    {
                        s(0) = i18n::s.get("core.misc.tax.caution");
                        s(1) = "";
                    }
                    txt(s +
                            i18n::s.get(
                                "core.misc.tax.left_bills",
                                game_data.left_bill - 1) +
                            s(1),
                        Message::color{ColorIndex::red});
                }
            }
            if (game_data.left_bill > 4)
            {
                txt(i18n::s.get(
                        "core.misc.tax.accused", game_data.left_bill - 1),
                    Message::color{ColorIndex::red});
                int stat = decrease_fame(cdata.player(), 50);
                p = stat;
                txt(i18n::s.get("core.misc.tax.lose_fame", p(0)),
                    Message::color{ColorIndex::red});
                modify_karma(cdata.player(), -30 * 2);
            }
        }
        else
        {
            txt(i18n::s.get("core.misc.tax.no_duty"));
        }
    }
    inv_close_tmp_inv("shop4.s2");
    mode = 0;
    maybe_show_ex_help(16);
}



void grow_plant(int val0)
{
    --feat(3);
    if (feat(3) % 50 == 0)
    {
        if (feat(3) >= 50)
        {
            feat = tile_plant + 3;
        }
        else
        {
            ++feat;
            try_to_grow_plant(val0);
        }
    }
}



void try_to_grow_plant(int val0)
{
    feat(3) = 4 + rnd(5);
    p = 10;
    if (feat(2) == 41)
    {
        p = 15;
    }
    if (feat(2) == 42)
    {
        p = 25;
    }
    if (feat(2) == 38)
    {
        p = 30;
    }
    if (feat(2) == 39)
    {
        p = 25;
    }
    if (feat(2) == 40)
    {
        p = 40;
    }
    if (val0 == 0)
    {
        p = p * 3 / 2;
    }
    if (feat == tile_plant)
    {
        if (game_data.weather < 3)
        {
            p = p * 2;
        }
    }
    if (cdata.player().get_skill(180).level < rnd(p + 1) || rnd(20) == 0)
    {
        feat(3) += 50;
    }
}



void harvest_plant(int val)
{
    p = 15;
    if (feat(2) == 41)
    {
        p = 25;
    }
    if (feat(2) == 42)
    {
        p = 30;
    }
    if (feat(2) == 38)
    {
        p = 40;
    }
    if (feat(2) == 39)
    {
        p = 35;
    }
    if (val == 0)
    {
        p = p * 2;
    }
    if (game_data.weather < 3)
    {
        p = p * 4 / 3;
    }
    if (cdata.player().get_skill(180).level < rnd(p + 1) || rnd(5) == 0 ||
        feat(2) == 40)
    {
        cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats = 0;
        return;
    }
    feat = tile_plant;
    try_to_grow_plant();
    cell_featset(
        cdata.player().position.x,
        cdata.player().position.y,
        feat,
        feat(1),
        feat(2),
        feat(3));
    txt(i18n::s.get("core.action.plant.new_plant_grows"),
        Message::color{ColorIndex::green});
}



void create_harvested_item()
{
    chara_gain_skill_exp(cdata.player(), 180, 75);
    snd("core.bush1");
    flt(cdata.player().get_skill(180).level / 2 + 15, Quality::good);
    int item_id = 0;
    if (feat(2) == 39)
    {
        flttypemajor = choice(fsetplantunknown);
        if (rnd(100) == 0)
        {
            item_id = 559;
        }
    }
    if (feat(2) == 40 || (feat(2) == 39 && rnd(50) == 0))
    {
        flttypemajor = choice(fsetplantartifact);
        fixlv = Quality::miracle;
        save_trigger_autosaving();
    }
    if (feat(2) == 36)
    {
        flttypeminor = 57003;
    }
    if (feat(2) == 37)
    {
        flttypeminor = 57004;
    }
    if (feat(2) == 38)
    {
        flttypeminor = 58005;
    }
    if (feat(2) == 41)
    {
        flttypeminor = 77001;
    }
    if (feat(2) == 42)
    {
        flttypemajor = 56000;
    }
    if (const auto item = itemcreate_player_inv(item_id, 0))
    {
        txt(i18n::s.get("core.action.plant.harvest", item.unwrap()));
        inv_stack(g_inv.pc(), item.unwrap(), true);
    }
}



int getworker(int map_id, int exclude_with)
{
    int ret = -1;
    for (auto&& ally : cdata.allies())
    {
        if (exclude_with != 0 && ally.index != exclude_with)
            continue;
        if (ally.current_map == map_id)
        {
            ret = ally.index;
            break;
        }
    }
    return ret;
}



void removeworker(int map_id)
{
    for (auto&& ally : cdata.allies())
    {
        if (ally.current_map == map_id)
        {
            ally.current_map = 0;
        }
    }
}

} // namespace elona
