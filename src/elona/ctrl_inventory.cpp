#include "../util/strutil.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "attack.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config.hpp"
#include "data/types/type_item.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "equipment.hpp"
#include "globals.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "keybind/keybind.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "shop.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



#if 0
_1 = "どのアイテムを調べる？ "
_2 = "どのアイテムを置く？ "
_3 = "どのアイテムを拾う？ "

_5 = "何を食べよう？ "
_6 = "何を装備する？"
_7 = "どれを読む？ "
_8 = "どれを飲む？ "
_9 = "どれを振る？ "
_10 = "どれを渡す？ "
_11 = "どれを購入する？ "
_12 = "どれを売却する？ "
_13 = "どのアイテムを鑑定する？ "
_14 = "どのアイテムを使用する？ "
_15 = "どれを開ける？ "
_16 = "何を料理する？ "
_17 = "何を混ぜる？ "
_18 = "何に混ぜる？(${_1}の効果を適用するアイテムを選択) "
_19 = "何を神に捧げる？ "
_20 = "何を交換する？ "
_21 = "${_1}の代わりに何を提示する？ "
_22 = "何を取る？ "
_23 = "何を対象にする？ "
_24 = "何を入れる？ "
_25 = "何をもらう？ "
_26 = "何を投げる？ "
_27 = "何を盗む？ "
_28 = "何と交換する？ "
#endif



namespace elona
{

namespace
{

struct OnEnterResult
{
    int type;
    MenuResult menu_result;
    optional_ref<Item> selected_item;


    OnEnterResult(int type)
        : type(type)
    {
    }


    OnEnterResult(
        const MenuResult& menu_result,
        optional_ref<Item> selected_item = none)
        : type(0)
        , menu_result(menu_result)
        , selected_item(selected_item)
    {
    }
};

OnEnterResult on_enter(
    optional_ref<Character> inventory_owner,
    int selected_item_index,
    int& citrade,
    bool dropcontinue);
optional<MenuResult> on_cancel(bool dropcontinue);



bool reset_mru_cursor(int invctrl)
{
    return invctrl == 11 || invctrl == 12;
}



bool exclude_ground_items(int invctrl)
{
    return invctrl == 2 || invctrl == 6 || invctrl == 10 || invctrl == 12 ||
        invctrl == 16 || invctrl == 20 || invctrl == 21 || invctrl == 23 ||
        invctrl == 24 || invctrl == 25;
}



bool exclude_character_items(int invctrl)
{
    return invctrl == 3 || invctrl == 11 || invctrl == 22 || invctrl == 28;
}



bool exclude_equipped_items(int invctrl)
{
    return invctrl != 1 && invctrl != 5 && invctrl != 13 && invctrl != 14 &&
        invctrl != 18 && invctrl != 20 && invctrl != 23 && invctrl != 25 &&
        invctrl != 27;
}



bool show_inventory_owners_money(int invctrl)
{
    return invctrl == 11 || invctrl == 12 || invctrl == 25 || invctrl == 27;
}



bool can_assign_shortcut(int invctrl)
{
    return invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9 ||
        invctrl == 14 || invctrl == 15 || invctrl == 26;
}



int get_menu_cycle_type(bool dropcontinue)
{
    if (dropcontinue)
    {
        return 4;
    }
    else if (invally == 1)
    {
        return 2;
    }
    else if (invcontainer)
    {
        return 3;
    }
    else if (map_data.type == mdata_t::MapType::world_map)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



void remove_card_and_figure_from_heir_trunk()
{
    if (invctrl == 22 && invctrl(1) == 1)
    {
        for (auto&& item : inv.ground())
        {
            if (item.id == ItemId::card || item.id == ItemId::figurine)
            {
                item.remove();
            }
        }
    }
}



void fallback_to_default_command_if_unavailable()
{
    if (menucycle)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            p = 0;
            for (int cnt = 0; cnt < 12; ++cnt)
            {
                if (cycle(cnt, 1) == -1)
                {
                    break;
                }
                if (cycle(cnt, 1) == invctrl)
                {
                    p = 1;
                    break;
                }
            }
            if (p == 0)
            {
                invctrl = cycle(0, 1);
            }
        }
    }
}



void restore_cursor()
{
    if (reset_mru_cursor(invctrl(0)))
    {
        invmark(invctrl) = 0;
    }
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = invmark(invctrl) % 1000;
    page = invmark(invctrl) / 1000;
    cs_bk = -1;
    page_load();
}



void make_item_list(
    optional_ref<Character> inventory_owner,
    int& mainweapon,
    int citrade)
{
    // cnt = 0 => extra
    // cnt = 1 => PC/NPC
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            p = -1;
            if (exclude_ground_items(invctrl(0)))
            {
                continue;
            }
        }
        if (cnt == 1)
        {
            p = 0;
            if (invctrl == 20 || invctrl == 25)
            {
                assert(inventory_owner);
                p = inventory_owner->index;
            }
            if (invctrl == 27)
            {
                p = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
                if (p == 0 || p == -1)
                {
                    continue;
                }
            }
            if (exclude_character_items(invctrl(0)))
            {
                break;
            }
        }
        int cnt2 = cnt;

        for (auto& item : inv.by_index(p))
        {
            if (item.number() <= 0)
            {
                item.remove();
                continue;
            }

            // compatibility?
            if (item.id == ItemId::training_machine)
            {
                item.function = 9;
            }

            // compatibility?
            if (itemid2int(item.id) >= maxitemid || itemid2int(item.id) < 0)
            {
                dialog(i18n::s.get(
                    "core.ui.inv.common.invalid",
                    item.index,
                    itemid2int(item.id)));
                item.remove();
                item.id = ItemId::none;
                continue;
            }

            if (map_data.type == mdata_t::MapType::world_map)
            {
                if (invctrl == 7)
                {
                    if (the_item_db[itemid2int(item.id)]->subcategory !=
                            53100 &&
                        item.id != ItemId::treasure_map)
                    {
                        // ワールドマップでは権利書か宝の地図しか読めない
                        continue;
                    }
                }
            }
            if (cnt2 == 0)
            {
                if (invctrl == 27)
                {
                    if (item.position.x != tlocx || item.position.y != tlocy)
                    {
                        // その座標にあるものしか盗めない
                        continue;
                    }
                }
                else if (invctrl != 11 && invctrl != 22 && invctrl != 28)
                {
                    if (item.position.x != cdata.player().position.x ||
                        item.position.y != cdata.player().position.y)
                    {
                        // キャラと同じ座標にあるものしか対象に取れない
                        continue;
                    }
                }
            }

            // ここで呼び出す?
            item_checkknown(item);

            // reftype使ってるとこ案外減ってる
            reftype = (int)the_item_db[itemid2int(item.id)]->category;

            if (item.own_state == 5)
            {
                // ショウルームのアイテムで、[調べる]でなく、showroom_onlyのものを
                // 使おうとしているのでもないならリストから除外
                if (!item.is_showroom_only() || invctrl != 14)
                {
                    if (invctrl != 1)
                    {
                        continue;
                    }
                }
            }

            if (exclude_equipped_items(invctrl(0)))
            {
                if (item.body_part != 0) // `item` is worn.
                {
                    continue;
                }
            }

            // (利き腕)表示用
            if (item.body_part != 0)
            {
                if (reftype == 10000)
                {
                    if (mainweapon == -1 ||
                        item.body_part < inv[mainweapon].body_part)
                    {
                        mainweapon = item.index;
                    }
                }
            }

            // 各行動
            if (invctrl == 5)
            {
                if (reftype != 57000 && reftype != 91000 && item.material != 35)
                {
                    continue;
                }
            }
            if (invctrl == 6)
            {
                if (iequiploc(item) !=
                    cdata.player().body_parts[body - 100] / 10000)
                {
                    continue;
                }
            }
            if (invctrl == 7)
            {
                if (!the_item_db[itemid2int(item.id)]->is_readable)
                {
                    continue;
                }
            }
            if (invctrl == 8)
            {
                if (!the_item_db[itemid2int(item.id)]->is_drinkable)
                {
                    continue;
                }
            }
            if (invctrl == 9)
            {
                if (!the_item_db[itemid2int(item.id)]->is_zappable)
                {
                    continue;
                }
            }
            if (invctrl == 11)
            {
                if (item.id == ItemId::gold_piece ||
                    item.id == ItemId::platinum_coin)
                {
                    continue;
                }
            }
            if (invctrl == 11 || invctrl == 12)
            {
                if (shoptrade)
                {
                    if (item.weight >= 0)
                    {
                        continue;
                    }
                    else if (reftype != 92000)
                    {
                        continue;
                    }
                }
                else if (item.weight < 0)
                {
                    if (reftype == 92000)
                    {
                        continue;
                    }
                }
                if (item.value <= 1)
                {
                    continue;
                }
                if (item.is_precious())
                {
                    continue;
                }
                if (item.param3 < 0)
                {
                    continue;
                }
                if (item.quality == Quality::special)
                {
                    continue;
                }
            }
            if (invctrl == 13)
            {
                if (item.identify_state == IdentifyState::completely)
                {
                    continue;
                }
            }
            if (invctrl == 14)
            {
                if (item.function == 0 &&
                    !the_item_db[itemid2int(item.id)]->is_usable &&
                    !item.is_alive())
                {
                    continue;
                }
            }
            if (invctrl == 15)
            {
                if (reftype != 72000)
                {
                    continue;
                }
            }
            if (invctrl == 16)
            {
                if (reftype != 57000)
                {
                    continue;
                }
                else if (item.param2 != 0)
                {
                    continue;
                }
            }
            if (invctrl == 17)
            {
                if (reftype != 52000 && item.id != ItemId::bait)
                {
                    continue;
                }
            }
            if (invctrl == 18)
            {
                if (inv[cidip].id == ItemId::bait)
                {
                    if (item.id != ItemId::fishing_pole)
                    {
                        continue;
                    }
                }
                if (cidip == item.index || item.id == ItemId::bottle_of_water)
                {
                    continue;
                }
            }
            if (invctrl == 19)
            {
                bool is_offerable =
                    item_db_is_offerable(item, itemid2int(item.id));
                if (is_offerable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 20)
            {
                if (item.id == ItemId::gold_piece ||
                    item.id == ItemId::platinum_coin)
                {
                    continue;
                }
            }
            if (invctrl == 21)
            {
                if (calcitemvalue(item, 0) * item.number() <
                    calcitemvalue(inv[citrade], 0) * inv[citrade].number() / 2 *
                        3)
                {
                    continue;
                }
                if (item.is_stolen())
                {
                    continue;
                }
            }
            if (invctrl == 23)
            {
                if (invctrl(1) == 0)
                {
                    if (reftype >= 50000 && reftype != 60000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 1)
                {
                    if (reftype != 10000 && reftype != 24000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 2)
                {
                    if (reftype < 12000 || reftype >= 24000)
                    {
                        if (reftype < 30000 || reftype >= 50000)
                        {
                            continue;
                        }
                    }
                }
                if (invctrl(1) == 3)
                {
                    if (!item.has_charge())
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 4)
                {
                    if (item.body_part != 0)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (reftype != 56000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 6)
                {
                    if (item.weight <= 0 || item.id == ItemId::cooler_box)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 7)
                {
                    if (item.quality >= Quality::miracle || reftype >= 50000)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 0)
                {
                    if (game_data.current_map == mdata_t::MapId::lumiest)
                    {
                        if (item.id != ItemId::ancient_book || item.param2 == 0)
                        {
                            continue;
                        }
                    }
                    else if (item.own_state != 4)
                    {
                        continue;
                    }
                }
                else if (item.own_state == 4)
                {
                    continue;
                }
                if (invctrl(1) == 2)
                {
                    if (item.id != ItemId::bill)
                    {
                        continue;
                    }
                }
                if (reftype == 72000)
                {
                    continue;
                }
                if (invctrl(1) == 3)
                {
                    if (reftype != 57000)
                    {
                        continue;
                    }
                }
            }
            else if (item.own_state == 4)
            {
                // 調べる、置く、拾う、食べる、納入する
                // 以外は禁止(収穫依頼の野菜)
                if (invctrl != 1 && invctrl != 2 && invctrl != 3 &&
                    invctrl != 5)
                {
                    continue;
                }
            }
            if (invctrl == 26)
            {
                if (reftype != 52000 && item.id != ItemId::kitty_bank &&
                    item.id != ItemId::monster_ball &&
                    item.id != ItemId::little_ball && item.id != ItemId::tomato)
                {
                    continue;
                }
                if (item.id == ItemId::monster_ball)
                {
                    if (item.subname != 0)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 27)
            {
                if (cnt2 == 0)
                {
                    if (item.own_state != 1)
                    {
                        continue;
                    }
                }
            }

            // リスト追加
            list(0, listmax) = item.index;

            // ソート情報
            list(1, listmax) = reftype * 1000 + itemid2int(item.id);
            if (item.id == ItemId::disc)
            {
                list(1, listmax) += item.param1 + 900;
            }
            if (invctrl == 1 || invctrl == 13)
            {
                if (item.body_part != 0)
                {
                    list(1, listmax) -= 99999000;
                }
            }
            if (cnt2 == 0)
            {
                list(1, listmax) -= 199998000;
            }
            if (invctrl == 28)
            {
                list(1, listmax) = calcmedalvalue(item);
            }

            ++listmax;
        }
    }
}



// 不可能な行動を制限
optional<MenuResult> check_command(
    optional_ref<Character> inventory_owner,
    int citrade)
{
    MenuResult result = {false, false, TurnResult::none};

    f = 0;
    if (listmax == 0)
    {
        if (invctrl == 21)
        {
            txt(i18n::s.get("core.ui.inv.trade.too_low_value", inv[citrade]));
            f = 1;
        }
        if (invctrl == 27)
        {
            if (inventory_owner)
            {
                txt(i18n::s.get(
                    "core.ui.inv.steal.has_nothing", *inventory_owner));
                f = 1;
            }
            else
            {
                txt(i18n::s.get("core.ui.inv.steal.there_is_nothing"));
                f = 1;
            }
        }
    }
    if (invctrl == 19)
    {
        if (!item_find(60002, 2))
        {
            txt(i18n::s.get("core.ui.inv.offer.no_altar"),
                Message::only_once{true});
            f = 1;
        }
    }
    if (invctrl == 27)
    {
        if (inventory_owner)
        {
            if (inventory_owner->relationship == 10)
            {
                txt(i18n::s.get("core.ui.inv.steal.do_not_rob_ally"));
                f = 1;
            }
        }
    }
    if (invctrl == 24)
    {
        if (invctrl(1) == 0)
        {
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                if (game_data.guild.mages_guild_quota <= 0)
                {
                    txt(i18n::s.get("core.ui.inv.put.guild.have_no_quota"));
                    f = 1;
                }
            }
        }
    }

    if (f == 1)
    {
        if (invsubroutine == 1)
        {
            invsubroutine = 0;
            result.succeeded = false;
            return result;
        }
        update_screen();
        result.turn_result = TurnResult::pc_turn_user_error;
        return result;
    }

    return none;
}



optional<MenuResult> check_pick_up()
{
    MenuResult result = {false, false, TurnResult::none};

    if (invctrl == 3)
    {
        if (listmax == 0)
        {
            result.turn_result = TurnResult::turn_end;
            return result;
        }
    }

    return none;
}



void show_message(int citrade)
{
    if (returnfromidentify == 0)
    {
        std::string valn;
        if (invctrl == 18)
        {
            valn = itemname(inv[cidip], 1);
        }
        else if (invctrl == 21)
        {
            valn = itemname(inv[citrade]);
        }

        for (int cnt = 0; cnt < 30; cnt++)
        {
            if (auto text =
                    i18n::s.get_enum_optional("core.ui.inv.title", cnt, valn))
            {
                s(cnt) = *text;
            }
            else
            {
                s(cnt) = ""s;
            }
        }

        if (s(invctrl) != ""s)
        {
            Message::instance().linebreak();
        }
        if (invsc == 0)
        {
            txt(s(invctrl));
        }
        if (invctrl == 28)
        {
            if (const auto small_medals =
                    item_find(622, 3, ItemFindLocation::player_inventory))
            {
                p = small_medals->number();
            }
            else
            {
                p = 0;
            }
            txt(i18n::s.get("core.ui.inv.trade_medals.medals", p(0)));
        }
        if (invctrl == 24 && invctrl(1) == 0)
        {
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                txt(i18n::s.get(
                    "core.ui.inv.put.guild.remaining",
                    game_data.guild.mages_guild_quota));
            }
        }
    }

    asset_load("deco_inv");
    gsel(0);
    if (returnfromidentify == 0)
    {
        windowshadow = 1;
    }
    returnfromidentify = 0;
}



// ショートカット経由
optional<OnEnterResult> on_shortcut(int& citrade, bool dropcontinue)
{
    MenuResult result = {false, false, TurnResult::none};

    if (invsc != 0)
    {
        f = 0;
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            p = list(0, cnt);
            if (inv[p].id == int2itemid(invsc))
            {
                f = 1;
                if (inv[p].has_charge())
                {
                    if (inv[p].count <= 0)
                    {
                        continue;
                    }
                }
                break;
            }
        }
        if (f == 0)
        {
            if (inv_find(int2itemid(invsc), 0))
            {
                Message::instance().linebreak();
                txt(i18n::s.get("core.action.cannot_do_in_global"));
            }
            else
            {
                txt(i18n::s.get("core.ui.inv.common.does_not_exist"));
            }
            invsc = 0;
            update_screen();
            result.turn_result = TurnResult::pc_turn_user_error;
            return OnEnterResult{result};
        }
        invsc = 0;
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (invctrl == 9 || invctrl == 15 || invctrl == 26)
            {
                Message::instance().linebreak();
                txt(i18n::s.get("core.action.cannot_do_in_global"));
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return OnEnterResult{result};
            }
        }
        return on_enter(none, p(0), citrade, dropcontinue);
    }

    return none;
}



void set_cursor()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
}



void draw_menu(bool dropcontinue)
{
    if (!menucycle)
        return;

    font(12 + sizefix - en * 2);
    y = 34;
    x = windoww - 650 + 156;
    window2(x, y, 475, 22, 5, 5);
    draw("radar_deco", x - 28, y - 8);
    if (dropcontinue)
    {
        i = 4;
    }
    else if (invally == 1)
    {
        i = 2;
    }
    else if (invcontainer)
    {
        i = 3;
    }
    else if (map_data.type == mdata_t::MapType::world_map)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        if (cycle(cnt, i) == -1)
        {
            break;
        }
        p = cycle(cnt, i);
        draw_indexed("inventory_icon", x + cnt * 44 + 20, y - 24, invicon(p));
        if (invctrl == p)
        {
            gmode(5, 70);
            draw_indexed(
                "inventory_icon", x + cnt * 44 + 20, y - 24, invicon(p));
            gmode(2);
        }
        std::string inv_command_txt =
            i18n::s.get_enum("core.ui.inventory_command", p);
        bmes(
            inv_command_txt,
            x + cnt * 44 + 46 - strlen_u(inv_command_txt) * 3,
            y + 7,
            invctrl == p ? snail::Color{255, 255, 255}
                         : snail::Color{165, 165, 165});
        if (invkey(p) != ""s)
        {
            bmes(
                u8"("s + invkey(p) + u8")"s,
                x + cnt * 44 + 46,
                y + 18,
                {235, 235, 235});
        }
    }
    bmes(
        ""s + key_prev + u8","s + key_next + u8",Tab,Ctrl+Tab "s + "[" +
            i18n::s.get("core.ui.inv.window.change") + "]",
        x + 260,
        y + 32);
}



void draw_window(optional_ref<Character> inventory_owner, bool dropcontinue)
{
    auto key_help = strhint2 + strhint5 + strhint5b + strhint3;
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9 ||
        invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        key_help += strhint7;
    }
    if (invctrl == 1)
    {
        key_help += ""s + key_mode2 + u8" "s + "[" +
            i18n::s.get("core.ui.inv.window.tag.no_drop") + "]";
    }
    if (invctrl == 2)
    {
        if (!dropcontinue)
        {
            key_help += ""s + key_mode2 + u8" "s + "[" +
                i18n::s.get("core.ui.inv.window.tag.multi_drop") + "]";
        }
    }
    ui_display_window(
        i18n::s.get(
            "core.ui.inv.window.select_item",
            i18n::s.get_enum("core.ui.inventory_command", invctrl)),
        key_help,
        (windoww - 640) / 2 + inf_screenx,
        winposy(432),
        640,
        432);

    if (invicon(invctrl) != -1)
    {
        draw_indexed("inventory_icon", wx + 46, wy - 14, invicon(invctrl));
    }
    s = i18n::s.get("core.ui.inv.window.weight");
    if (invctrl == 11 || invctrl == 12)
    {
        s = i18n::s.get("core.ui.inv.buy.window.price");
    }
    if (invctrl == 28)
    {
        s = i18n::s.get("core.ui.inv.trade_medals.window.medal");
    }
    display_topic(i18n::s.get("core.ui.inv.window.name"), wx + 28, wy + 30);
    display_topic(s, wx + 526, wy + 30);

    draw_additional_item_info_label(wx + 300, wy + 40);

    draw("deco_inv_a", wx + ww - 136, wy - 6);
    if (g_show_additional_item_info == AdditionalItemInfo::none)
    {
        draw("deco_inv_b", wx + ww - 186, wy - 6);
    }
    draw("deco_inv_c", wx + ww - 246, wy - 6);
    draw("deco_inv_d", wx - 6, wy - 6);
    s = ""s + listmax + u8" items"s;
    s += "  ("s +
        i18n::s.get(
            "core.ui.inv.window.total_weight",
            cnvweight(cdata.player().inventory_weight),
            cnvweight(cdata.player().max_inventory_weight),
            cnvweight(game_data.cargo_weight)) +
        ")"s;
    if (invctrl == 25)
    {
        s = ""s;
    }
    display_note(s);
    if (invctrl == 25)
    {
        assert(inventory_owner);
        x = (windoww - 640) / 2 + inf_screenx + 455;
        y = winposy(432) - 32;
        int w = 200;
        int h = 102;
        window(x + 4, y + 4, w, h - h % 8, true);
        window(x, y, w, h - h % 8);
        font(12 + en - en * 2);
        mes(x + 16,
            y + 17,
            u8"DV:"s + inventory_owner->dv + u8" PV:"s + inventory_owner->pv);
        mes(x + 16,
            y + 35,
            i18n::s.get("core.ui.inv.take_ally.window.equip_weight") + ":" +
                cnvweight(inventory_owner->sum_of_equipment_weight) + ""s +
                get_armor_class_name(*inventory_owner));
        x = wx + 40;
        y = wy + wh - 65 - wh % 8;
        mes(x, y, i18n::s.get("core.ui.inv.take_ally.window.equip"));
        x += 60;
        for (int cnt = 0; cnt < 30; ++cnt)
        {
            if (inventory_owner->body_parts[cnt] == 0)
            {
                continue;
            }
            p = inventory_owner->body_parts[cnt];
            std::string body_part_desc =
                i18n::s.get_enum("core.ui.body_part", p / 10000);
            const auto text_color = p % 10000 != 0
                ? snail::Color{50, 50, 200}
                : snail::Color{100, 100, 100};
            mes(x, y, body_part_desc, text_color);
            x += (strlen_u(body_part_desc) + 1) * 6;
        }
    }
}



void update_key_list()
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 60 + cnt * 19, 540, 18, {12, 14, 16, 16});
        }
    }
    font(14 - en * 2);
    cs_listbk();
}



void draw_item_list(int mainweapon)
{
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        p = list(0, p);
        s(0) = itemname(inv[p]);
        s(1) = cnvweight(inv[p].weight * inv[p].number());
        if (invctrl == 11)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(inv[p], 0) + u8" gp"s;
        }
        if (invctrl == 12)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(inv[p], 1) + u8" gp"s;
        }
        if (invctrl == 28)
        {
            s(1) = i18n::s.get(
                "core.ui.inv.trade_medals.medal_value", calcmedalvalue(inv[p]));
        }
        if (invctrl != 3 && invctrl != 11 && invctrl != 22 && invctrl != 27 &&
            invctrl != 28)
        {
            if (p >= ELONA_ITEM_ON_GROUND_INDEX)
            {
                s += i18n::space_if_needed() + "(" +
                    i18n::s.get("core.ui.inv.window.ground") + ")";
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (game_data.skill_shortcuts.at(cnt) ==
                itemid2int(inv[p].id) + invctrl * 10000)
            {
                s +=
                    u8"{"s + get_bound_shortcut_key_name_by_index(cnt) + u8"}"s;
            }
        }
        display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);

        draw_item_with_portrait_scale_height(
            inv[p], wx + 37, wy + 69 + cnt * 19);

        if (inv[p].body_part != 0)
        {
            draw("equipped", wx + 46, wy + 72 + cnt * 18 - 3);
            if (p == mainweapon)
            {
                s += i18n::space_if_needed() + "(" +
                    i18n::s.get("core.ui.inv.window.main_hand") + ")";
            }
        }
        draw_additional_item_info(inv[p], wx + 300, wy + 60 + cnt * 19 + 2);
        if (g_show_additional_item_info != AdditionalItemInfo::none)
        {
            s = cut_item_name_for_additional_info(s);
        }
        const auto text_color = cs_list_get_item_color(inv[p]);
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, text_color);
        mes(wx + 600 - strlen_u(s(1)) * 7,
            wy + 60 + cnt * 19 + 2,
            s(1),
            text_color);
    }
}



void save_csbk()
{
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}



void show_money(optional_ref<Character> inventory_owner)
{
    if (show_inventory_owners_money(invctrl(0)))
    {
        if (inventory_owner &&
            g_show_additional_item_info == AdditionalItemInfo::none)
        {
            font(13 - en * 2);
            gmode(2);
            draw("gold_coin", wx + 340, wy + 32);
            mes(wx + 368,
                wy + 37 - en * 2,
                ""s + inventory_owner->gold + u8" gp"s);
        }
    }
}



std::string get_action()
{
    auto action = get_selected_item(p(0));
    invmark(invctrl) = page * 1000 + cs;
    if (mode == 9)
    {
        if (listmax == 0)
        {
            p = -1;
            action = "cancel";
        }
    }
    return action;
}



OnEnterResult on_enter_examine(Item& selected_item)
{
    item_show_description(selected_item);
    return OnEnterResult{1};
}



OnEnterResult
on_enter_drop(Item& selected_item, MenuResult& result, bool dropcontinue)
{
    if (selected_item.is_marked_as_no_drop())
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
        return OnEnterResult{2};
    }
    if (!inv_getspace(-1))
    {
        txt(i18n::s.get("core.ui.inv.drop.cannot_anymore"));
        snd("core.fail1");
        return OnEnterResult{2};
    }
    if (map_data.max_item_count != 0)
    {
        if (inv_sum(-1) >= map_data.max_item_count)
        {
            if (the_item_db[itemid2int(selected_item.id)]->category !=
                ItemCategory::furniture)
            {
                txt(i18n::s.get("core.ui.inv.drop.cannot_anymore"));
                snd("core.fail1");
                return OnEnterResult{2};
            }
        }
    }
    if (selected_item.number() > 1)
    {
        txt(i18n::s.get(
            "core.ui.inv.drop.how_many",
            selected_item.number(),
            selected_item));
        input_number_dialog(
            (windoww - 200) / 2 + inf_screenx,
            winposy(60),
            selected_item.number());
        in = elona::stoi(inputlog(0));
        if (in > selected_item.number())
        {
            in = selected_item.number();
        }
        if (in == 0 || rtval == -1)
        {
            return OnEnterResult{2};
        }
    }
    else
    {
        in = 1;
    }
    savecycle();
    item_drop(selected_item, in);
    if (dropcontinue)
    {
        menucycle = true;
        return OnEnterResult{1};
    }
    result.turn_result = TurnResult::turn_end;
    return OnEnterResult{result};
}



OnEnterResult on_enter_external_inventory(
    Item& selected_item,
    MenuResult& result,
    bool dropcontinue,
    optional_ref<Character> inventory_owner)
{
    if (invctrl != 3 && invctrl != 22)
    {
        if (selected_item.is_marked_as_no_drop())
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
            return OnEnterResult{2};
        }
    }
    if (invctrl == 24)
    {
        if (invctrl(1) == 3 || invctrl(1) == 5)
        {
            if (inv_sum(-1) >= invcontainer)
            {
                snd("core.fail1");
                txt(i18n::s.get("core.ui.inv.put.container.full"));
                return OnEnterResult{2};
            }
        }
        if (invctrl(1) == 5)
        {
            if (selected_item.weight >= efp * 100)
            {
                snd("core.fail1");
                txt(i18n::s.get(
                    "core.ui.inv.put.container.too_heavy",
                    cnvweight(efp * 100)));
                return OnEnterResult{2};
            }
            if (selected_item.weight <= 0)
            {
                snd("core.fail1");
                txt(i18n::s.get("core.ui.inv.put.container.cannot_hold_cargo"));
                return OnEnterResult{2};
            }
        }
        if (invctrl(1) == 5)
        {
            if (!action_sp(cdata.player(), 10))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                return OnEnterResult{*on_cancel(dropcontinue)};
            }
        }
    }
    if (invctrl == 22)
    {
        if (invctrl(1) == 1)
        {
            if (game_data.rights_to_succeed_to < 1)
            {
                txt(i18n::s.get("core.ui.inv.take.no_claim"));
                return OnEnterResult{2};
            }
        }
        if (invctrl(1) == 5)
        {
            if (!action_sp(cdata.player(), 10))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                return OnEnterResult{*on_cancel(dropcontinue)};
            }
        }
    }
    if (selected_item.own_state > 0 && selected_item.own_state < 3)
    {
        snd("core.fail1");
        if (selected_item.own_state == 2)
        {
            txt(i18n::s.get("core.action.get.cannot_carry"),
                Message::only_once{true});
        }
        if (selected_item.own_state == 1)
        {
            txt(i18n::s.get("core.action.get.not_owned"),
                Message::only_once{true});
        }
        update_screen();
        result.turn_result = TurnResult::pc_turn_user_error;
        return OnEnterResult{result};
    }
    page_save();
    if (mode == 6 && selected_item.number() > 1 && invctrl != 22)
    {
        if (invctrl == 11)
        {
            txt(i18n::s.get(
                "core.ui.inv.buy.how_many",
                selected_item.number(),
                selected_item));
        }
        if (invctrl == 12)
        {
            txt(i18n::s.get(
                "core.ui.inv.sell.how_many",
                selected_item.number(),
                selected_item));
        }
        input_number_dialog(
            (windoww - 200) / 2 + inf_screenx,
            winposy(60),
            selected_item.number());
        in = elona::stoi(inputlog(0));
        if (in > selected_item.number())
        {
            in = selected_item.number();
        }
        if (in == 0 || rtval == -1)
        {
            screenupdate = -1;
            update_screen();
            return OnEnterResult{2};
        }
    }
    else
    {
        in = selected_item.number();
    }
    if (mode == 6 && invctrl != 22 && invctrl != 24)
    {
        if (!g_config.skip_confirm_at_shop())
        {
            if (invctrl == 11)
            {
                txt(i18n::s.get(
                    "core.ui.inv.buy.prompt",
                    itemname(selected_item, in),
                    (in * calcitemvalue(selected_item, 0))));
            }
            if (invctrl == 12)
            {
                txt(i18n::s.get(
                    "core.ui.inv.sell.prompt",
                    itemname(selected_item, in),
                    (in * calcitemvalue(selected_item, 1))));
            }
            if (!yes_no())
            {
                screenupdate = -1;
                update_screen();
                return OnEnterResult{1};
            }
        }
        if (invctrl == 11)
        {
            if (calcitemvalue(selected_item, 0) * in > cdata.player().gold)
            {
                screenupdate = -1;
                update_screen();
                txt(i18n::s.get("core.ui.inv.buy.not_enough_money"));
                return OnEnterResult{1};
            }
        }
        if (invctrl == 12)
        {
            if (inventory_owner->role != Role::trader)
            {
                if (calcitemvalue(selected_item, 1) * in >
                    inventory_owner->gold)
                {
                    screenupdate = -1;
                    update_screen();
                    txt(i18n::s.get(
                        "core.ui.inv.sell.not_enough_money", *inventory_owner));
                    return OnEnterResult{1};
                }
            }
        }
    }
    int inventory_id;
    if (invctrl == 12 || (invctrl == 24 && invctrl(1) != 0))
    {
        inventory_id = -1;
    }
    else
    {
        inventory_id = 0;
    }
    int stat = pick_up_item(inventory_id, selected_item, inventory_owner).type;
    if (stat == 0)
    {
        return OnEnterResult{1};
    }
    if (stat == -1)
    {
        result.turn_result = TurnResult::turn_end;
        return OnEnterResult{result};
    }
    if (invctrl == 22)
    {
        if (invctrl(1) == 1)
        {
            --game_data.rights_to_succeed_to;
            if (invctrl(1) == 1)
            {
                txt(i18n::s.get(
                    "core.ui.inv.take.can_claim_more",
                    game_data.rights_to_succeed_to));
            }
        }
        if (invctrl(1) == 4)
        {
            ++game_data.quest_flags.gift_count_of_little_sister;
            invsubroutine = 0;
            result.succeeded = true;
            return OnEnterResult{result};
        }
    }
    screenupdate = -1;
    update_screen();
    return OnEnterResult{1};
}



OnEnterResult on_enter_eat(Item& selected_item, MenuResult& result)
{
    if (selected_item.is_marked_as_no_drop())
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
        return OnEnterResult{2};
    }
    screenupdate = -1;
    update_screen();
    savecycle();
    if (cdata.player().nutrition > 10000)
    {
        txt(i18n::s.get("core.ui.inv.eat.too_bloated"));
        update_screen();
        result.turn_result = TurnResult::pc_turn_user_error;
        return OnEnterResult{result};
    }
    result.turn_result = do_eat_command(cdata.player(), selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_equip(Item& selected_item, MenuResult& result)
{
    if (trait(161) != 0)
    {
        if (selected_item.weight >= 1000)
        {
            txt(i18n::s.get("core.ui.inv.equip.too_heavy"));
            return OnEnterResult{2};
        }
    }
    equip_item(cdata.player(), selected_item);
    chara_refresh(cdata.player());
    screenupdate = -1;
    update_screen();
    snd("core.equip1");
    Message::instance().linebreak();
    txt(i18n::s.get("core.ui.inv.equip.you_equip", selected_item));
    game_data.player_is_changing_equipment = 1;
    switch (selected_item.curse_state)
    {
    case CurseState::doomed:
        txt(i18n::s.get("core.ui.inv.equip.doomed", cdata.player()));
        break;
    case CurseState::cursed:
        txt(i18n::s.get("core.ui.inv.equip.cursed", cdata.player()));
        break;
    case CurseState::none: break;
    case CurseState::blessed:
        txt(i18n::s.get("core.ui.inv.equip.blessed", cdata.player()));
        break;
    }
    if (cdata.player().body_parts[body - 100] / 10000 == 5)
    {
        equip_melee_weapon(cdata.player());
    }
    menucycle = true;
    result.turn_result = TurnResult::menu_equipment;
    return OnEnterResult{result};
}



OnEnterResult on_enter_read(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    savecycle();
    result.turn_result = do_read_command(cdata.player(), selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_drink(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    savecycle();
    result.turn_result = do_drink_command(cdata.player(), selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_zap(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    savecycle();
    result.turn_result = do_zap_command(selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_give(
    Item& selected_item,
    MenuResult& result,
    Character& inventory_owner)
{
    if (selected_item.is_marked_as_no_drop())
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
        return OnEnterResult{2};
    }
    if (inventory_owner.sleep)
    {
        txt(i18n::s.get("core.ui.inv.give.is_sleeping", inventory_owner));
        snd("core.fail1");
        return OnEnterResult{2};
    }
    const auto slot_opt = inv_get_free_slot(inventory_owner.index);
    if (!slot_opt)
    {
        txt(i18n::s.get("core.ui.inv.give.inventory_is_full", inventory_owner));
        snd("core.fail1");
        return OnEnterResult{2};
    }
    auto& slot = *slot_opt;
    reftype = (int)the_item_db[itemid2int(selected_item.id)]->category;
    if (selected_item.id == ItemId::gift)
    {
        txt(i18n::s.get(
            "core.ui.inv.give.present.text", inventory_owner, selected_item));
        selected_item.modify_number(-1);
        txt(i18n::s.get("core.ui.inv.give.present.dialog", inventory_owner));
        chara_modify_impression(
            inventory_owner, giftvalue(selected_item.param4));
        inventory_owner.emotion_icon = 317;
        refresh_burden_state();
        if (invally == 1)
        {
            return OnEnterResult{1};
        }
        update_screen();
        result.turn_result = TurnResult::turn_end;
        return OnEnterResult{result};
    }
    f = 0;
    p = sdata(10, inventory_owner.index) * 500 +
        sdata(11, inventory_owner.index) * 500 +
        sdata(153, inventory_owner.index) * 2500 + 25000;
    if (inventory_owner.id == CharaId::golden_knight)
    {
        p *= 5;
    }
    if (inv_weight(inventory_owner.index) + selected_item.weight > p)
    {
        f = 1;
    }
    if (inventory_owner.id != CharaId::golden_knight)
    {
        if (reftype == 60000)
        {
            f = 2;
        }
        if (reftype == 64000)
        {
            f = 3;
        }
    }
    if (selected_item.weight < 0)
    {
        f = 4;
    }
    if (f)
    {
        snd("core.fail1");
        txt(i18n::s.get_enum(
            "core.ui.inv.give.refuse_dialog", f - 1, inventory_owner));
        return OnEnterResult{2};
    }
    f = 0;
    if (inventory_owner.relationship == 10)
    {
        f = 1;
    }
    else
    {
        if (selected_item.identify_state <= IdentifyState::partly)
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.give.too_creepy", inventory_owner));
            return OnEnterResult{2};
        }
        if (is_cursed(selected_item.curse_state))
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.give.cursed", inventory_owner));
            return OnEnterResult{2};
        }
        if (reftype == 53000)
        {
            f = 1;
            if (strutil::contains(
                    the_item_db[itemid2int(selected_item.id)]->filter,
                    u8"/neg/"))
            {
                f = 0;
            }
            // scroll of teleport/treasure map/deeds
            switch (itemid2int(selected_item.id))
            {
            case 16:
            case 245:
            case 621:
            case 344:
            case 521:
            case 522:
            case 542:
            case 543:
            case 572:
            case 712: f = 0; break;
            default: break;
            }
        }
        if (reftype == 52000)
        {
            f = 1;
            if (the_item_db[itemid2int(selected_item.id)]->subcategory == 52002)
            {
                if (inventory_owner.drunk)
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.ui.inv.give.no_more_drink", inventory_owner));
                    return OnEnterResult{2};
                }
            }
            if (strutil::contains(
                    the_item_db[itemid2int(selected_item.id)]->filter,
                    u8"/neg/"))
            {
                f = 0;
            }
            if (strutil::contains(
                    the_item_db[itemid2int(selected_item.id)]->filter,
                    u8"/nogive/"))
            {
                f = 0;
            }
            if (inventory_owner.is_pregnant())
            {
                if (selected_item.id == ItemId::poison ||
                    selected_item.id == ItemId::bottle_of_dye ||
                    selected_item.id == ItemId::bottle_of_sulfuric)
                {
                    f = 1;
                    txt(i18n::s.get("core.ui.inv.give.abortion"));
                }
            }
        }
    }
    if (f)
    {
        snd("core.equip1");
        txt(i18n::s.get(
            "core.ui.inv.give.you_hand", selected_item, inventory_owner));
        if (selected_item.id == ItemId::engagement_ring ||
            selected_item.id == ItemId::engagement_amulet)
        {
            txt(i18n::s.get("core.ui.inv.give.engagement", inventory_owner),
                Message::color{ColorIndex::green});
            chara_modify_impression(inventory_owner, 15);
            inventory_owner.emotion_icon = 317;
        }
        if (selected_item.id == ItemId::love_potion)
        {
            txt(i18n::s.get(
                    "core.ui.inv.give.love_potion.text",
                    inventory_owner,
                    selected_item),
                Message::color{ColorIndex::purple});
            snd("core.crush2");
            txt(i18n::s.get(
                    "core.ui.inv.give.love_potion.dialog", inventory_owner),
                Message::color{ColorIndex::cyan});
            chara_modify_impression(inventory_owner, -20);
            inventory_owner.emotion_icon = 318;
            selected_item.modify_number(-1);
            return OnEnterResult{1};
        }
        item_copy(selected_item, slot);
        selected_item.modify_number(-1);
        slot.set_number(1);
        auto& stacked_item =
            item_stack(inventory_owner.index, slot, true).stacked_item;
        chara_set_ai_item(inventory_owner, stacked_item);
        wear_most_valuable_equipment_for_all_body_parts(inventory_owner);
        if (inventory_owner.index < 16)
        {
            create_pcpic(inventory_owner);
        }
        chara_refresh(inventory_owner);
        refresh_burden_state();
        if (invally == 1)
        {
            return OnEnterResult{1};
        }
        update_screen();
        result.turn_result = TurnResult::turn_end;
        return OnEnterResult{result};
    }
    snd("core.fail1");
    txt(i18n::s.get(
        "core.ui.inv.give.refuses", inventory_owner, selected_item));
    return OnEnterResult{2};
}



OnEnterResult on_enter_identify(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    const auto identify_result = item_identify(selected_item, efp);
    if (identify_result == IdentifyState::unidentified)
    {
        txt(i18n::s.get("core.ui.inv.identify.need_more_power"));
    }
    else if (identify_result != IdentifyState::completely)
    {
        txt(i18n::s.get("core.ui.inv.identify.partially", selected_item));
    }
    else
    {
        txt(i18n::s.get("core.ui.inv.identify.fully", selected_item));
    }
    item_stack(0, selected_item, true);
    refresh_burden_state();
    invsubroutine = 0;
    result.succeeded = true;
    return OnEnterResult{result};
}



OnEnterResult on_enter_use(Item& selected_item, MenuResult& result)
{
    savecycle();
    result.turn_result = do_use_command(selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_cook(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    invsubroutine = 0;
    result.succeeded = true;
    return OnEnterResult{result, selected_item};
}



OnEnterResult on_enter_open(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    savecycle();
    result.turn_result = do_open_command(selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_mix(Item& selected_item)
{
    cidip = selected_item.index;
    savecycle();
    invctrl = 18;
    Message::instance().linebreak();
    snd("core.pop2");
    return OnEnterResult{1};
}



OnEnterResult on_enter_mix_target(Item& selected_item, MenuResult& result)
{
    screenupdate = -1;
    update_screen();
    result.turn_result = do_dip_command(inv[cidip], selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_offer(Item& selected_item, MenuResult& result)
{
    if (selected_item.is_marked_as_no_drop())
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
        return OnEnterResult{2};
    }
    screenupdate = -1;
    update_screen();
    savecycle();
    result.turn_result = do_offer_command(selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_trade(Item& selected_item, int& citrade)
{
    citrade = selected_item.index;
    invctrl = 21;
    snd("core.pop2");
    return OnEnterResult{1};
}



OnEnterResult on_enter_trade_target(
    Item& selected_item,
    MenuResult& result,
    int& citrade,
    Character& inventory_owner)
{
    if (selected_item.is_marked_as_no_drop())
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
        return OnEnterResult{2};
    }
    if (inventory_owner.activity)
    {
        inventory_owner.activity.type = Activity::Type::none;
        inventory_owner.activity.turn = 0;
        inventory_owner.activity.item = 0;
    }
    snd("core.equip1");
    inv[citrade].is_quest_target() = false;
    txt(i18n::s.get(
        "core.ui.inv.trade.you_receive", selected_item, inv[citrade]));
    if (inv[citrade].body_part != 0)
    {
        p = inv[citrade].body_part;
        inventory_owner.body_parts[p - 100] =
            inventory_owner.body_parts[p - 100] / 10000 * 10000;
        inv[citrade].body_part = 0;
    }
    item_exchange(selected_item, inv[citrade]);
    item_convert_artifact(selected_item);
    if (inventory_owner.ai_item == citrade)
    {
        inventory_owner.ai_item = 0;
    }
    wear_most_valuable_equipment_for_all_body_parts(inventory_owner);
    if (inventory_owner.index >= 16)
    {
        supply_new_equipment(inventory_owner);
    }
    (void)inv_get_free_slot_force(inventory_owner.index);
    chara_refresh(inventory_owner);
    refresh_burden_state();
    invsubroutine = 0;
    result.succeeded = true;
    return OnEnterResult{result};
}



OnEnterResult on_enter_target(Item& selected_item, MenuResult& result)
{
    if (invctrl(1) == 4)
    {
        if (selected_item.is_marked_as_no_drop())
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
            return OnEnterResult{2};
        }
    }
    item_separate(selected_item);
    invsubroutine = 0;
    result.succeeded = true;
    return OnEnterResult{result, selected_item};
}



OnEnterResult on_enter_put_into(Item& selected_item)
{
    if (invctrl(1) == 0)
    {
        snd("core.inv");
        if (game_data.current_map == mdata_t::MapId::lumiest)
        {
            game_data.guild.mages_guild_quota -=
                (selected_item.param1 + 1) * selected_item.number();
            if (game_data.guild.mages_guild_quota <= 0)
            {
                game_data.guild.mages_guild_quota = 0;
            }
            txt(i18n::s.get(
                    "core.ui.inv.put.guild.you_deliver", selected_item) +
                    u8"("s +
                    (selected_item.param1 + 1) * selected_item.number() +
                    u8" Guild Point)"s,
                Message::color{ColorIndex::green});
            if (game_data.guild.mages_guild_quota == 0)
            {
                snd("core.complete1");
                txt(i18n::s.get("core.ui.inv.put.guild.you_fulfill"),
                    Message::color{ColorIndex::green});
            }
        }
        else
        {
            quest_data.immediate().extra_info_2 +=
                selected_item.weight * selected_item.number();
            txt(i18n::s.get(
                    "core.ui.inv.put.harvest",
                    selected_item,
                    cnvweight(selected_item.weight * selected_item.number()),
                    cnvweight(quest_data.immediate().extra_info_2),
                    cnvweight(quest_data.immediate().extra_info_1)),
                Message::color{ColorIndex::green});
        }
        selected_item.remove();
        refresh_burden_state();
        return OnEnterResult{1};
    }
    if (invctrl(1) == 2)
    {
        if (cdata.player().gold < selected_item.subname)
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.put.tax.not_enough_money"));
            return OnEnterResult{2};
        }
        if (game_data.left_bill <= 0)
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.inv.put.tax.do_not_have_to"));
            return OnEnterResult{1};
        }
        cdata.player().gold -= selected_item.subname;
        snd("core.paygold1");
        txt(i18n::s.get("core.ui.inv.put.tax.you_pay", selected_item),
            Message::color{ColorIndex::green});
        selected_item.modify_number(-1);
        --game_data.left_bill;
        screenupdate = -1;
        update_screen();
        return OnEnterResult{1};
    }
    throw "unreachable";
}



OnEnterResult on_enter_receive(Item& selected_item, Character& inventory_owner)
{
    const auto slot_opt = inv_get_free_slot(0);
    if (!slot_opt)
    {
        txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
        return OnEnterResult{2};
    }
    auto& slot = *slot_opt;
    if (the_item_db[itemid2int(selected_item.id)]->category ==
        ItemCategory::ore)
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.take_ally.refuse_dialog", inventory_owner),
            Message::color{ColorIndex::blue});
        return OnEnterResult{2};
    }
    if (selected_item.body_part != 0)
    {
        if (is_cursed(selected_item.curse_state))
        {
            txt(i18n::s.get("core.ui.inv.take_ally.cursed", selected_item));
            return OnEnterResult{1};
        }
        p = selected_item.body_part;
        inventory_owner.body_parts[p - 100] =
            inventory_owner.body_parts[p - 100] / 10000 * 10000;
        selected_item.body_part = 0;
    }
    if (selected_item.id == ItemId::engagement_ring ||
        selected_item.id == ItemId::engagement_amulet)
    {
        txt(i18n::s.get(
                "core.ui.inv.take_ally.swallows_ring",
                inventory_owner,
                selected_item),
            Message::color{ColorIndex::purple});
        snd("core.offer1");
        chara_modify_impression(inventory_owner, -20);
        inventory_owner.emotion_icon = 318;
        selected_item.modify_number(-1);
        return OnEnterResult{1};
    }
    snd("core.equip1");
    selected_item.is_quest_target() = false;
    if (selected_item.id == ItemId::gold_piece)
    {
        in = selected_item.number();
    }
    else
    {
        in = 1;
    }
    txt(i18n::s.get(
        "core.ui.inv.take_ally.you_take", itemname(selected_item, in)));
    if (selected_item.id == ItemId::gold_piece)
    {
        earn_gold(cdata.player(), in);
        selected_item.remove();
    }
    else
    {
        item_copy(selected_item, slot);
        selected_item.modify_number((-in));
        slot.set_number(in);
        auto& stacked_item = item_stack(0, slot, true).stacked_item;
        item_convert_artifact(stacked_item);
    }
    wear_most_valuable_equipment_for_all_body_parts(inventory_owner);
    if (inventory_owner.index < 16)
    {
        create_pcpic(inventory_owner);
    }
    chara_refresh(inventory_owner);
    refresh_burden_state();
    return OnEnterResult{1};
}



OnEnterResult on_enter_throw(Item& selected_item, MenuResult& result)
{
    savecycle();
    int stat = target_position();
    if (stat != 1)
    {
        if (stat == 0)
        {
            txt(i18n::s.get("core.ui.inv.throw.cannot_see"));
            update_screen();
        }
        result.turn_result = TurnResult::pc_turn_user_error;
        return OnEnterResult{result};
    }
    if (chip_data.for_cell(tlocx, tlocy).effect & 4)
    {
        txt(i18n::s.get("core.ui.inv.throw.location_is_blocked"));
        update_screen();
        result.turn_result = TurnResult::pc_turn_user_error;
        return OnEnterResult{result};
    }
    result.turn_result = do_throw_command(cdata.player(), selected_item);
    return OnEnterResult{result};
}



OnEnterResult on_enter_steal(Item& selected_item, MenuResult& result)
{
    start_stealing(cdata.player(), selected_item);
    invsubroutine = 0;
    result.succeeded = true;
    return OnEnterResult{result};
}



OnEnterResult on_enter_small_medal(Item& selected_item)
{
    Message::instance().linebreak();
    const auto slot_opt = inv_get_free_slot(0);
    if (!slot_opt)
    {
        txt(i18n::s.get("core.ui.inv.trade_medals.inventory_full"));
        snd("core.fail1");
        return OnEnterResult{1};
    }
    auto& slot = *slot_opt;
    if (const auto small_medals =
            item_find(622, 3, ItemFindLocation::player_inventory))
    {
        i = small_medals->index;
        p = small_medals->number();
    }
    else
    {
        p = 0;
    }
    if (p < calcmedalvalue(selected_item))
    {
        txt(i18n::s.get("core.ui.inv.trade_medals.not_enough_medals"));
        snd("core.fail1");
        return OnEnterResult{1};
    }
    inv[i].modify_number(-calcmedalvalue(selected_item));
    snd("core.paygold1");
    item_copy(selected_item, slot);
    txt(i18n::s.get("core.ui.inv.trade_medals.you_receive", slot));
    auto& stacked_item = item_stack(0, slot, true).stacked_item;
    item_convert_artifact(stacked_item, true);
    return OnEnterResult{1};
}



OnEnterResult on_enter(
    optional_ref<Character> inventory_owner,
    int selected_item_index,
    int& citrade,
    bool dropcontinue)
{
    MenuResult result = {false, false, TurnResult::none};

    auto& selected_item = inv[selected_item_index];

    if (!cargocheck(selected_item))
    {
        return OnEnterResult{3};
    }

    if (invctrl == 1)
    {
        return on_enter_examine(selected_item);
    }
    if (invctrl == 2)
    {
        return on_enter_drop(selected_item, result, dropcontinue);
    }
    if (invctrl == 3 || invctrl == 11 || invctrl == 12 || invctrl == 22 ||
        (invctrl == 24 && (invctrl(1) == 3 || invctrl(1) == 5)))
    {
        return on_enter_external_inventory(
            selected_item, result, dropcontinue, inventory_owner);
    }
    if (invctrl == 5)
    {
        return on_enter_eat(selected_item, result);
    }
    if (invctrl == 6)
    {
        return on_enter_equip(selected_item, result);
    }
    if (invctrl == 7)
    {
        return on_enter_read(selected_item, result);
    }
    if (invctrl == 8)
    {
        return on_enter_drink(selected_item, result);
    }
    if (invctrl == 9)
    {
        return on_enter_zap(selected_item, result);
    }
    if (invctrl == 10)
    {
        assert(inventory_owner);
        return on_enter_give(selected_item, result, *inventory_owner);
    }
    if (invctrl == 13)
    {
        return on_enter_identify(selected_item, result);
    }
    if (invctrl == 14)
    {
        return on_enter_use(selected_item, result);
    }
    if (invctrl == 16)
    {
        return on_enter_cook(selected_item, result);
    }
    if (invctrl == 15)
    {
        return on_enter_open(selected_item, result);
    }
    if (invctrl == 17)
    {
        return on_enter_mix(selected_item);
    }
    if (invctrl == 18)
    {
        return on_enter_mix_target(selected_item, result);
    }
    if (invctrl == 19)
    {
        return on_enter_offer(selected_item, result);
    }
    if (invctrl == 20)
    {
        return on_enter_trade(selected_item, citrade);
    }
    if (invctrl == 21)
    {
        assert(inventory_owner);
        return on_enter_trade_target(
            selected_item, result, citrade, *inventory_owner);
    }
    if (invctrl == 23)
    {
        return on_enter_target(selected_item, result);
    }
    if (invctrl == 24)
    {
        return on_enter_put_into(selected_item);
    }
    if (invctrl == 25)
    {
        assert(inventory_owner);
        return on_enter_receive(selected_item, *inventory_owner);
    }
    if (invctrl == 26)
    {
        return on_enter_throw(selected_item, result);
    }
    if (invctrl == 27)
    {
        return on_enter_steal(selected_item, result);
    }
    if (invctrl == 28)
    {
        return on_enter_small_medal(selected_item);
    }

    throw "unreachable";
}



bool on_show_description()
{
    if (listmax != 0)
    {
        const auto item_index = list(0, pagesize * page + cs);
        item_show_description(inv[item_index]);
        return true;
    }
    return false;
}



bool on_next_page()
{
    if (pagemax != 0)
    {
        snd("core.pop1");
        ++page;
        return true;
    }
    return false;
}



bool on_previous_page()
{
    if (pagemax != 0)
    {
        snd("core.pop1");
        --page;
        return true;
    }
    return false;
}



bool on_change_menu(bool next, bool dropcontinue)
{
    i = get_menu_cycle_type(dropcontinue);
    p = -1;
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        if (invctrl == cycle(cnt, i))
        {
            p = cnt;
            break;
        }
    }
    if (p != -1)
    {
        if (next)
        {
            ++p;
            if (cycle(p, i) == -1)
            {
                p = 0;
            }
        }
        else
        {
            --p;
            if (p < 0)
            {
                p = cyclemax(i);
            }
        }
        if (invctrl != cycle(p, i))
        {
            invctrl = cycle(p, i);
            snd("core.inv");
            screenupdate = -1;
            update_screen();
            return true;
        }
    }
    return false;
}



bool on_switch_mode_2(bool& dropcontinue)
{
    if (invctrl == 1)
    {
        const auto item_index = list(0, pagesize * page + cs);
        if (inv[item_index].is_marked_as_no_drop())
        {
            inv[item_index].is_marked_as_no_drop() = false;
            txt(i18n::s.get(
                "core.ui.inv.examine.no_drop.unset", inv[item_index]));
        }
        else
        {
            inv[item_index].is_marked_as_no_drop() = true;
            txt(i18n::s.get(
                "core.ui.inv.examine.no_drop.set", inv[item_index]));
        }
    }
    if (invctrl == 2)
    {
        if (!dropcontinue)
        {
            txt(i18n::s.get("core.ui.inv.drop.multi"));
            dropcontinue = true;
            snd("core.inv");
            screenupdate = -1;
            update_screen();
            return true;
        }
    }
    return false;
}



void on_switch_mode()
{
    g_show_additional_item_info = get_next_enum(g_show_additional_item_info);
    snd("core.pop1");
}



optional<MenuResult> on_cancel(bool dropcontinue)
{
    MenuResult result = {false, false, TurnResult::none};

    savecycle();
    if (invctrl == 22 && invctrl(1) == 0)
    {
        if (listmax > 0)
        {
            txt(i18n::s.get("core.ui.inv.take.really_leave"));
            if (!yes_no())
            {
                return none;
            }
        }
    }

    efcancel = 1;
    if (invsubroutine == 1)
    {
        invsubroutine = 0;
        result.succeeded = false;
        return result;
    }
    if (invctrl == 6)
    {
        screenupdate = -1;
        update_screen();
        menucycle = true;
        result.turn_result = TurnResult::menu_equipment;
        return result;
    }
    if (invctrl == 11 || invctrl == 12 || invctrl == 22 || invctrl == 28)
    {
        shop_load_shoptmp();
        result.succeeded = false;
        return result;
    }
    if (invally == 1)
    {
        invally = 0;
    }
    if (dropcontinue)
    {
        result.turn_result = TurnResult::turn_end;
        return result;
    }
    screenupdate = 0;
    update_screen();
    result.turn_result = TurnResult::pc_turn_user_error;
    return result;
}



bool on_assign_shortcut(const std::string& action, int shortcut)
{
    p = list(0, pagesize * page + cs);
    if (inv[p].weight < 0)
    {
        snd("core.fail1");
        txt(i18n::s.get("core.ui.inv.common.shortcut.cargo"));
        return false;
    }
    snd("core.ok1");
    p = itemid2int(inv[list(0, pagesize * page + cs)].id) + invctrl * 10000;
    if (game_data.skill_shortcuts.at(shortcut) == p)
    {
        game_data.skill_shortcuts.at(shortcut) = 0;
        return true;
    }
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (game_data.skill_shortcuts.at(cnt) == p)
        {
            game_data.skill_shortcuts.at(cnt) = 0;
        }
    }
    game_data.skill_shortcuts.at(shortcut) = p;
    txt(i18n::s.get(
        "core.ui.assign_shortcut",
        get_bound_shortcut_key_name_by_action_id(action)));
    return true;
}

} // namespace



CtrlInventoryResult ctrl_inventory(optional_ref<Character> inventory_owner)
{
    int mainweapon = -1;
    int citrade = 0;
    bool dropcontinue = false;

    remove_card_and_figure_from_heir_trunk();

    bool init = true;
    bool update_page = true;
    while (true)
    {
        if (init)
        {
            init = false;

            fallback_to_default_command_if_unavailable();
            restore_cursor();
            mainweapon = -1;
            make_item_list(inventory_owner, mainweapon, citrade);
            if (const auto result = check_command(inventory_owner, citrade))
            {
                return {*result, none};
            }
            sort_list_by_column1();
            if (const auto result = check_pick_up())
            {
                return {*result, none};
            }
            show_message(citrade);
        }

        if (update_page)
        {
            update_page = false;

            if (const auto result = on_shortcut(citrade, dropcontinue))
            {
                switch (result->type)
                {
                case 0: return {result->menu_result, result->selected_item};
                case 1:
                    init = true;
                    update_page = true;
                    continue;
                case 2: update_page = true; continue;
                case 3: continue;
                default: assert(0); throw "unreachable";
                }
            }
            set_cursor();
            draw_menu(dropcontinue);
        }

        draw_window(inventory_owner, dropcontinue);
        update_key_list();
        draw_item_list(mainweapon);
        save_csbk();
        show_money(inventory_owner);
        redraw();
        const auto action = get_action();
        if (p != -1)
        {
            const auto result =
                on_enter(inventory_owner, p(0), citrade, dropcontinue);
            switch (result.type)
            {
            case 0: return {result.menu_result, result.selected_item};
            case 1:
                init = true;
                update_page = true;
                continue;
            case 2: update_page = true; continue;
            case 3: continue;
            default: assert(0); throw "unreachable";
            }
        }
        if (action == "identify")
        {
            if (on_show_description())
            {
                init = true;
                update_page = true;
                continue;
            }
        }
        else if (action == "next_page")
        {
            if (on_next_page())
            {
                update_page = true;
                continue;
            }
        }
        else if (action == "previous_page")
        {
            if (on_previous_page())
            {
                update_page = true;
                continue;
            }
        }
        else if (action == "next_menu" || action == "previous_menu")
        {
            if (menucycle)
            {
                if (on_change_menu(action == "next_menu", dropcontinue))
                {
                    init = true;
                    update_page = true;
                    continue;
                }
            }
        }
        else if (action == "switch_mode_2")
        {
            if (on_switch_mode_2(dropcontinue))
            {
                init = true;
                update_page = true;
                continue;
            }
        }
        else if (action == "switch_mode")
        {
            on_switch_mode();
            update_page = true;
            continue;
        }
        else if (action == "cancel")
        {
            if (const auto result = on_cancel(dropcontinue))
            {
                return {*result, none};
            }
            else
            {
                update_page = true;
                continue;
            }
        }
        else if (auto shortcut = get_shortcut(action))
        {
            if (can_assign_shortcut(invctrl(0)))
            {
                const auto success = on_assign_shortcut(action, *shortcut);
                if (success)
                {
                    update_page = true;
                    continue;
                }
                else
                {
                    init = true;
                    update_page = true;
                    continue;
                }
            }
        }
    }
}

} // namespace elona
