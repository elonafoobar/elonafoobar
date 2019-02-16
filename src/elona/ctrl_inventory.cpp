#include "../util/strutil.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config/config.hpp"
#include "data/types/type_item.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "keybind/keybind.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "shop.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace
{

int showresist;

}



namespace elona
{

MenuResult ctrl_inventory()
{
    MenuResult result = {false, false, TurnResult::none};
    int mainweapon = 0;
    int countequip = 0;
    int showmoney = 0;
    int citrade = 0;
    int dropcontinue = 0;
    std::string action;
label_20591:
    if (invctrl == 22)
    {
        if (invctrl(1) == 1)
        {
            remove_card_and_figures();
        }
    }
    if (menucycle == 1)
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
    invmark(11) = 0;
    invmark(12) = 0;
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = invmark(invctrl) % 1000;
    page = invmark(invctrl) / 1000;
    cs_bk = -1;
    cc = 0;
    page_load();
    mainweapon = -1;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            p = -1;
            if (invctrl == 2 || invctrl == 6 || invctrl == 10 ||
                invctrl == 12 || invctrl == 16 || invctrl == 20 ||
                invctrl == 21 || invctrl == 23 || invctrl == 24 ||
                invctrl == 25)
            {
                continue;
            }
        }
        if (cnt == 1)
        {
            p = cc;
            if (invctrl == 20 || invctrl == 25)
            {
                p = tc;
            }
            if (invctrl == 27)
            {
                p = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
                if (p == 0 || p == -1)
                {
                    continue;
                }
            }
            if (invctrl == 3 || invctrl == 11 || invctrl == 22 || invctrl == 28)
            {
                break;
            }
        }
        int cnt2 = cnt;
        if (invctrl != 1 && invctrl != 5 && invctrl != 13 && invctrl != 14 &&
            invctrl != 18 && invctrl != 20 && invctrl != 23 && invctrl != 25 &&
            invctrl != 27)
        {
            countequip = 0;
        }
        else
        {
            countequip = 1;
        }
        if (invctrl == 11 || invctrl == 12 || invctrl == 25 || invctrl == 27)
        {
            showmoney = 1;
        }
        else
        {
            showmoney = 0;
        }
        for (const auto& cnt : items(p))
        {
            if (inv[cnt].number() <= 0)
            {
                inv[cnt].remove();
                continue;
            }
            if (inv[cnt].id == 488)
            {
                inv[cnt].function = 9;
            }
            if (inv[cnt].id >= maxitemid || inv[cnt].id < 0)
            {
                dialog(i18n::s.get(
                    "core.locale.ui.inv.common.invalid", cnt, inv[cnt].id));
                inv[cnt].remove();
                inv[cnt].id = 0;
                continue;
            }
            if (map_data.type == mdata_t::MapType::world_map)
            {
                if (invctrl == 7)
                {
                    if (the_item_db[inv[cnt].id]->subcategory != 53100 &&
                        inv[cnt].id != 621)
                    {
                        continue;
                    }
                }
            }
            if (cnt2 == 0)
            {
                if (invctrl == 27)
                {
                    if (inv[cnt].position.x != tlocx ||
                        inv[cnt].position.y != tlocy)
                    {
                        continue;
                    }
                }
                else if (invctrl != 11 && invctrl != 22 && invctrl != 28)
                {
                    if (inv[cnt].position.x != cdata[cc].position.x ||
                        inv[cnt].position.y != cdata[cc].position.y)
                    {
                        continue;
                    }
                }
            }
            item_checkknown(cnt);
            reftype = the_item_db[inv[cnt].id]->category;
            if (inv[cnt].own_state == 5)
            {
                if (!inv[cnt].is_showroom_only() || invctrl != 14)
                {
                    if (invctrl != 1)
                    {
                        continue;
                    }
                }
            }
            if (countequip == 0)
            {
                if (inv[cnt].body_part != 0)
                {
                    continue;
                }
            }
            if (inv[cnt].body_part != 0)
            {
                if (reftype == 10000)
                {
                    if (mainweapon == -1 ||
                        inv[cnt].body_part < inv[mainweapon].body_part)
                    {
                        mainweapon = cnt;
                    }
                }
            }
            if (invctrl == 5)
            {
                if (reftype != 57000 && reftype != 91000 &&
                    inv[cnt].material != 35)
                {
                    continue;
                }
            }
            if (invctrl == 6)
            {
                if (iequiploc(cnt) != cdata[cc].body_parts[body - 100] / 10000)
                {
                    continue;
                }
            }
            if (invctrl == 7)
            {
                if (!the_item_db[inv[cnt].id]->is_readable)
                {
                    continue;
                }
            }
            if (invctrl == 8)
            {
                if (!the_item_db[inv[cnt].id]->is_drinkable)
                {
                    continue;
                }
            }
            if (invctrl == 9)
            {
                if (!the_item_db[inv[cnt].id]->is_zappable)
                {
                    continue;
                }
            }
            if (invctrl == 11)
            {
                if (inv[cnt].id == 54 || inv[cnt].id == 55)
                {
                    continue;
                }
            }
            if (invctrl == 11 || invctrl == 12)
            {
                if (shoptrade)
                {
                    if (inv[cnt].weight >= 0)
                    {
                        continue;
                    }
                    else if (reftype != 92000)
                    {
                        continue;
                    }
                }
                else if (inv[cnt].weight < 0)
                {
                    if (reftype == 92000)
                    {
                        continue;
                    }
                }
                if (inv[cnt].value <= 1)
                {
                    continue;
                }
                if (inv[cnt].is_precious())
                {
                    continue;
                }
                if (inv[cnt].param3 < 0)
                {
                    continue;
                }
                if (inv[cnt].quality == Quality::special)
                {
                    continue;
                }
            }
            if (invctrl == 13)
            {
                if (inv[cnt].identification_state ==
                    IdentifyState::completely_identified)
                {
                    continue;
                }
            }
            if (invctrl == 14)
            {
                if (inv[cnt].function == 0 &&
                    !the_item_db[inv[cnt].id]->is_usable &&
                    !inv[cnt].is_alive())
                {
                    continue;
                }
            }
            if (invctrl == 15)
            {
                if (reftype != 72000 && inv[cnt].id != 701)
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
                else if (inv[cnt].param2 != 0)
                {
                    continue;
                }
            }
            if (invctrl == 17)
            {
                if (reftype != 52000 && inv[cnt].id != 617)
                {
                    continue;
                }
            }
            if (invctrl == 18)
            {
                if (inv[cidip].id == 617)
                {
                    if (inv[cnt].id != 342)
                    {
                        continue;
                    }
                }
                if (cidip == cnt || inv[cnt].id == 516)
                {
                    continue;
                }
            }
            if (invctrl == 19)
            {
                dbid = inv[cnt].id;
                dbspec = 12;
                int is_offerable = access_item_db(16);
                if (is_offerable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 20)
            {
                if (inv[cnt].id == 54 || inv[cnt].id == 55)
                {
                    continue;
                }
            }
            if (invctrl == 21)
            {
                if (calcitemvalue(cnt, 0) * inv[cnt].number() <
                    calcitemvalue(citrade, 0) * inv[citrade].number() / 2 * 3)
                {
                    continue;
                }
                if (inv[cnt].is_stolen())
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
                    if (!inv[cnt].has_charge())
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 4)
                {
                    if (inv[cnt].body_part != 0)
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
                    if (inv[cnt].weight <= 0 || inv[cnt].id == 641)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 7)
                {
                    if (inv[cnt].quality >= Quality::miracle ||
                        reftype >= 50000)
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
                        if (inv[cnt].id != 687 || inv[cnt].param2 == 0)
                        {
                            continue;
                        }
                    }
                    else if (inv[cnt].own_state != 4)
                    {
                        continue;
                    }
                }
                else if (invctrl(1) == 8)
                {
                    if (inv[cnt].id != 504)
                    {
                        continue;
                    }
                    else if (inv[cnt].own_state != 0)
                    {
                        continue;
                    }
                    else if (inv[cnt].subname == 0)
                    {
                        continue;
                    }
                    else if (card(0, inv[cnt].subname))
                    {
                        continue;
                    }
                }
                else if (inv[cnt].own_state == 4)
                {
                    continue;
                }
                if (invctrl(1) == 2)
                {
                    if (inv[cnt].id != 615)
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
            else if (inv[cnt].own_state == 4)
            {
                if (invctrl != 1 && invctrl != 2 && invctrl != 3 &&
                    invctrl != 5)
                {
                    continue;
                }
            }
            if (invctrl == 26)
            {
                if (reftype != 52000 && inv[cnt].id != 578 &&
                    inv[cnt].id != 685 && inv[cnt].id != 699 &&
                    inv[cnt].id != 772)
                {
                    continue;
                }
                if (inv[cnt].id == 685)
                {
                    if (inv[cnt].subname != 0)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 27)
            {
                if (cnt2 == 0)
                {
                    if (inv[cnt].own_state != 1)
                    {
                        continue;
                    }
                }
            }
            list(0, listmax) = cnt;
            list(1, listmax) = reftype * 1000 + inv[cnt].id;
            if (inv[cnt].id == 544)
            {
                list(1, listmax) += inv[cnt].param1 + 900;
            }
            if (invctrl == 1 || invctrl == 13)
            {
                if (inv[cnt].body_part != 0)
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
                list(1, listmax) = calcmedalvalue(cnt);
            }
            ++listmax;
        }
    }
    f = 0;
    if (listmax == 0)
    {
        if (invctrl == 21)
        {
            txt(i18n::s.get(
                "core.locale.ui.inv.trade.too_low_value", inv[citrade]));
            f = 1;
        }
        if (invctrl == 27)
        {
            if (tc != 0)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.steal.has_nothing", cdata[tc]));
                f = 1;
            }
            else
            {
                txt(i18n::s.get("core.locale.ui.inv.steal.there_is_nothing"));
                f = 1;
            }
        }
    }
    if (invctrl == 19)
    {
        int stat = item_find(60002, 2);
        if (stat == -1)
        {
            txt(i18n::s.get("core.locale.ui.inv.offer.no_altar"),
                Message::only_once{true});
            f = 1;
        }
    }
    if (invctrl == 27)
    {
        if (tc > 0)
        {
            if (cdata[tc].relationship == 10)
            {
                txt(i18n::s.get("core.locale.ui.inv.steal.do_not_rob_ally"));
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
                    txt(i18n::s.get(
                        "core.locale.ui.inv.put.guild.have_no_quota"));
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
    sort_list_by_column1();
    if (invctrl == 3)
    {
        if (listmax == 0)
        {
            result.turn_result = TurnResult::turn_end;
            return result;
        }
    }
    if (returnfromidentify == 0)
    {
        std::string valn;
        if (invctrl == 18)
        {
            valn = itemname(cidip, 1);
        }
        else if (invctrl == 21)
        {
            valn = itemname(citrade);
        }

        for (int cnt = 0; cnt < 30; cnt++)
        {
            if (auto text = i18n::s.get_enum_optional(
                    "core.locale.ui.inv.title", cnt, valn))
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
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                p = inv[stat].number();
            }
            else
            {
                p = 0;
            }
            txt(i18n::s.get("core.locale.ui.inv.trade_medals.medals", p(0)));
        }
        if (invctrl == 24)
        {
            if (invctrl(1) == 0)
            {
                if (game_data.current_map == mdata_t::MapId::lumiest)
                {
                    txt(i18n::s.get(
                        "core.locale.ui.inv.put.guild.remaining",
                        game_data.guild.mages_guild_quota));
                }
            }
        }
    }
    gsel(3);
    picload(filesystem::dir::graphic() / u8"deco_inv.bmp", 960, 96, false);
    gsel(0);
    if (returnfromidentify == 0)
    {
        windowshadow = 1;
    }
    returnfromidentify = 0;
label_2060_internal:
    if (invsc != 0)
    {
        f = 0;
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            p = list(0, cnt);
            if (inv[p].id == invsc)
            {
                ci = p;
                f = 1;
                if (inv[ci].has_charge())
                {
                    if (inv[ci].count <= 0)
                    {
                        continue;
                    }
                }
                break;
            }
        }
        cc = 0;
        if (f == 0)
        {
            int stat = inv_find(invsc, 0);
            if (stat == -1)
            {
                txt(i18n::s.get("core.locale.ui.inv.common.does_not_exist"));
            }
            else
            {
                Message::instance().linebreak();
                txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            }
            invsc = 0;
            update_screen();
            result.turn_result = TurnResult::pc_turn_user_error;
            return result;
        }
        invsc = 0;
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (invctrl == 9 || invctrl == 15 || invctrl == 26)
            {
                Message::instance().linebreak();
                txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
        }
        goto label_2062_internal;
    }
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
    if (menucycle == 1)
    {
        font(12 + sizefix - en * 2);
        y = 34;
        x = windoww - 650 + 156;
        window2(x, y, 475, 22, 5, 5);
        gcopy(3, 64, 288, 50, 32, x - 28, y - 8);
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
            gcopy(
                3,
                288 + invicon(p) * 48,
                48,
                48,
                48,
                x + cnt * 44 + 20,
                y - 24);
            if (invctrl == p)
            {
                gmode(5, 70);
                gcopy(
                    3,
                    288 + invicon(p) * 48,
                    48,
                    48,
                    48,
                    x + cnt * 44 + 20,
                    y - 24);
                gmode(2);
            }
            std::string inv_command_txt =
                i18n::s.get_enum("core.locale.ui.inventory_command", p);
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
                i18n::s.get("core.locale.ui.inv.window.change") + "]",
            x + 260,
            y + 32);
    }
label_2061_internal:
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
            i18n::s.get("core.locale.ui.inv.window.tag.no_drop") + "]";
    }
    if (invctrl == 2)
    {
        if (dropcontinue == 0)
        {
            key_help += ""s + key_mode2 + u8" "s + "[" +
                i18n::s.get("core.locale.ui.inv.window.tag.multi_drop") + "]";
        }
    }
    ui_display_window(
        i18n::s.get(
            "core.locale.ui.inv.window.select_item",
            i18n::s.get_enum("core.locale.ui.inventory_command", invctrl)),
        key_help,
        (windoww - 640) / 2 + inf_screenx,
        winposy(432),
        640,
        432);
}
    if (invicon(invctrl) != -1)
    {
        gcopy(3, 288 + invicon(invctrl) * 48, 48, 48, 48, wx + 46, wy - 14);
    }
    s = i18n::s.get("core.locale.ui.inv.window.weight");
    if (invctrl == 11 || invctrl == 12)
    {
        s = i18n::s.get("core.locale.ui.inv.buy.window.price");
    }
    if (invctrl == 28)
    {
        s = i18n::s.get("core.locale.ui.inv.trade_medals.window.medal");
    }
    display_topic(
        i18n::s.get("core.locale.ui.inv.window.name"), wx + 28, wy + 30);
    display_topic(s, wx + 526, wy + 30);
    if (showresist)
    {
        mes(wx + 300, wy + 40, i18n::s.get("core.locale.ui.inv.window.resist"));
    }
    gcopy(3, 960, 96, 144, 48, wx + ww - 136, wy - 6);
    if (showresist == 0)
    {
        gcopy(3, 960, 144, 48, 72, wx + ww - 186, wy - 6);
    }
    gcopy(3, 1008, 144, 48, 72, wx + ww - 246, wy - 6);
    gcopy(3, 960, 216, 48, 72, wx - 6, wy - 6);
    s = ""s + listmax + u8" items"s;
    s += "  ("s +
        i18n::s.get(
            "core.locale.ui.inv.window.total_weight",
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
        x = (windoww - 640) / 2 + inf_screenx + 455;
        y = winposy(432) - 32;
        int w = 200;
        int h = 102;
        window(x + 4, y + 4, w, h - h % 8, true);
        window(x, y, w, h - h % 8);
        font(12 + en - en * 2);
        mes(x + 16, y + 17, u8"DV:"s + cdata[tc].dv + u8" PV:"s + cdata[tc].pv);
        mes(x + 16,
            y + 35,
            i18n::s.get("core.locale.ui.inv.take_ally.window.equip_weight") +
                ":" + cnvweight(cdata[tc].sum_of_equipment_weight) + ""s +
                cnveqweight(tc));
        x = wx + 40;
        y = wy + wh - 65 - wh % 8;
        mes(x, y, i18n::s.get("core.locale.ui.inv.take_ally.window.equip"));
        x += 60;
        for (int cnt = 0; cnt < 30; ++cnt)
        {
            if (cdata[tc].body_parts[cnt] == 0)
            {
                continue;
            }
            p = cdata[tc].body_parts[cnt];
            std::string body_part_desc =
                i18n::s.get_enum("core.locale.ui.body_part", p / 10000);
            const auto text_color = p % 10000 != 0
                ? snail::Color{50, 50, 200}
                : snail::Color{100, 100, 100};
            mes(x, y, body_part_desc, text_color);
            x += (body_part_desc.size() + 1) * 6;
        }
    }
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
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        p = list(0, p);
        s(0) = itemname(p, inv[p].number());
        s(1) = cnvweight(inv[p].weight * inv[p].number());
        if (invctrl == 11)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(p, 0) + u8" gp"s;
        }
        if (invctrl == 12)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(p, 1) + u8" gp"s;
        }
        if (invctrl == 28)
        {
            s(1) = i18n::s.get(
                "core.locale.ui.inv.trade_medals.medal_value",
                calcmedalvalue(p));
        }
        if (invctrl != 3 && invctrl != 11 && invctrl != 22 && invctrl != 27 &&
            invctrl != 28)
        {
            if (p >= 5080)
            {
                s += i18n::space_if_needed() + "(" +
                    i18n::s.get("core.locale.ui.inv.window.ground") + ")";
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (game_data.skill_shortcuts.at(cnt) ==
                inv[p].id + invctrl * 10000)
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
                    i18n::s.get("core.locale.ui.inv.window.main_hand") + ")";
            }
        }
        if (showresist)
        {
            equipinfo(p, wx + 300, wy + 60 + cnt * 19 + 2);
            s = strmid(s, 0, 24);
        }
        const auto text_color = cs_list_get_item_color(inv[p]);
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, text_color);
        mes(wx + 600 - strlen_u(s(1)) * 7,
            wy + 60 + cnt * 19 + 2,
            s(1),
            text_color);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    if (showmoney)
    {
        if (showresist == 0)
        {
            font(13 - en * 2);
            gmode(2);
            draw("gold_coin", wx + 340, wy + 32);
            mes(wx + 368, wy + 37 - en * 2, ""s + cdata[tc].gold + u8" gp"s);
        }
    }
    redraw();
    action = get_selected_item(p(0));
    invmark(invctrl) = page * 1000 + cs;
    if (mode == 9)
    {
        if (listmax == 0)
        {
            p = -1;
            action = "cancel";
        }
    }
    if (p != -1)
    {
        ci = p;
        if (invctrl == 12 || (invctrl == 24 && invctrl(1) != 0))
        {
            cc = -1;
        }
        else
        {
            cc = 0;
        }
    label_2062_internal:
        int stat = cargocheck();
        if (stat == 0)
        {
            goto label_2061_internal;
        }
        if (invctrl == 1)
        {
            item_show_description();
            goto label_20591;
        }
        if (invctrl == 2)
        {
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            if (!inv_getspace(-1))
            {
                txt(i18n::s.get("core.locale.ui.inv.drop.cannot_anymore"));
                snd("core.fail1");
                goto label_2060_internal;
            }
            if (map_data.max_item_count != 0)
            {
                if (inv_sum(-1) >= map_data.max_item_count)
                {
                    if (the_item_db[inv[ci].id]->category != 60000)
                    {
                        txt(i18n::s.get(
                            "core.locale.ui.inv.drop.cannot_anymore"));
                        snd("core.fail1");
                        goto label_2060_internal;
                    }
                }
            }
            if (inv[ci].number() > 1)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.drop.how_many",
                    inv[ci].number(),
                    inv[ci]));
                input_number_dialog(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    inv[ci].number());
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number())
                {
                    in = inv[ci].number();
                }
                if (in == 0 || rtval == -1)
                {
                    goto label_2060_internal;
                }
            }
            else
            {
                in = 1;
            }
            savecycle();
            item_drop(inv[ci], in);
            if (dropcontinue)
            {
                menucycle = 1;
                ++dropcontinue;
                goto label_20591;
            }
            result.turn_result = TurnResult::turn_end;
            return result;
        }
        if (invctrl == 3 || invctrl == 11 || invctrl == 12 || invctrl == 22 ||
            (invctrl == 24 && (invctrl(1) == 3 || invctrl(1) == 5)))
        {
            if (invctrl != 3 && invctrl != 22)
            {
                if (inv[ci].is_marked_as_no_drop())
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.common.set_as_no_drop"));
                    goto label_2060_internal;
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 3 || invctrl(1) == 5)
                {
                    if (inv_sum(-1) >= invcontainer)
                    {
                        snd("core.fail1");
                        txt(i18n::s.get(
                            "core.locale.ui.inv.put.container.full"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (inv[ci].weight >= efp * 100)
                    {
                        snd("core.fail1");
                        txt(i18n::s.get(
                            "core.locale.ui.inv.put.container.too_heavy",
                            cnvweight(efp * 100)));
                        goto label_2060_internal;
                    }
                    if (inv[ci].weight <= 0)
                    {
                        snd("core.fail1");
                        txt(
                            i18n::s.get("core.locale.ui.inv.put.container."
                                        "cannot_hold_cargo"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!action_sp(cdata.player(), 10))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.common.too_exhausted"));
                        goto label_2063_internal;
                    }
                }
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    if (game_data.rights_to_succeed_to < 1)
                    {
                        txt(i18n::s.get("core.locale.ui.inv.take.no_claim"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!action_sp(cdata.player(), 10))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.common.too_exhausted"));
                        goto label_2063_internal;
                    }
                }
            }
            if (inv[ci].own_state > 0 && inv[ci].own_state < 3)
            {
                snd("core.fail1");
                if (inv[ci].own_state == 2)
                {
                    txt(i18n::s.get("core.locale.action.get.cannot_carry"),
                        Message::only_once{true});
                }
                if (inv[ci].own_state == 1)
                {
                    txt(i18n::s.get("core.locale.action.get.not_owned"),
                        Message::only_once{true});
                }
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
            page_save();
            if (mode == 6 && inv[ci].number() > 1 && invctrl != 22)
            {
                if (invctrl == 11)
                {
                    txt(i18n::s.get(
                        "core.locale.ui.inv.buy.how_many",
                        inv[ci].number(),
                        inv[ci]));
                }
                if (invctrl == 12)
                {
                    txt(i18n::s.get(
                        "core.locale.ui.inv.sell.how_many",
                        inv[ci].number(),
                        inv[ci]));
                }
                input_number_dialog(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    inv[ci].number());
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number())
                {
                    in = inv[ci].number();
                }
                if (in == 0 || rtval == -1)
                {
                    screenupdate = -1;
                    update_screen();
                    goto label_2060_internal;
                }
            }
            else
            {
                in = inv[ci].number();
            }
            if (mode == 6 && invctrl != 22 && invctrl != 24)
            {
                if (!Config::instance().skip_confirm_at_shop)
                {
                    if (invctrl == 11)
                    {
                        txt(i18n::s.get(
                            "core.locale.ui.inv.buy.prompt",
                            itemname(ci, in),
                            (in * calcitemvalue(ci, 0))));
                    }
                    if (invctrl == 12)
                    {
                        txt(i18n::s.get(
                            "core.locale.ui.inv.sell.prompt",
                            itemname(ci, in),
                            (in * calcitemvalue(ci, 1))));
                    }
                    if (!yes_no())
                    {
                        screenupdate = -1;
                        update_screen();
                        goto label_20591;
                    }
                }
                if (invctrl == 11)
                {
                    if (calcitemvalue(ci, 0) * in > cdata.player().gold)
                    {
                        screenupdate = -1;
                        update_screen();
                        txt(i18n::s.get(
                            "core.locale.ui.inv.buy.not_enough_money"));
                        goto label_20591;
                    }
                }
                if (invctrl == 12)
                {
                    if (cdata[tc].character_role != 1009)
                    {
                        if (calcitemvalue(ci, 1) * in > cdata[tc].gold)
                        {
                            screenupdate = -1;
                            update_screen();
                            txt(i18n::s.get(
                                "core.locale.ui.inv.sell.not_enough_money",
                                cdata[tc]));
                            goto label_20591;
                        }
                    }
                }
            }
            int stat = pick_up_item();
            if (stat == 0)
            {
                goto label_20591;
            }
            if (stat == -1)
            {
                result.turn_result = TurnResult::turn_end;
                return result;
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    --game_data.rights_to_succeed_to;
                    if (invctrl(1) == 1)
                    {
                        txt(i18n::s.get(
                            "core.locale.ui.inv.take.can_claim_more",
                            game_data.rights_to_succeed_to));
                    }
                }
                if (invctrl(1) == 4)
                {
                    ++game_data.quest_flags.gift_count_of_little_sister;
                    invsubroutine = 0;
                    result.succeeded = true;
                    return result;
                }
            }
            screenupdate = -1;
            update_screen();
            goto label_20591;
        }
        if (invctrl == 5)
        {
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            screenupdate = -1;
            update_screen();
            savecycle();
            if (cdata.player().nutrition > 10000)
            {
                txt(i18n::s.get("core.locale.ui.inv.eat.too_bloated"));
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
            result.turn_result = do_eat_command();
            return result;
        }
        if (invctrl == 6)
        {
            if (cc == 0)
            {
                if (trait(161) != 0)
                {
                    if (inv[ci].weight >= 1000)
                    {
                        txt(i18n::s.get("core.locale.ui.inv.equip.too_heavy"));
                        goto label_2060_internal;
                    }
                }
            }
            equip_item(cc);
            chara_refresh(cc);
            screenupdate = -1;
            update_screen();
            snd("core.equip1");
            Message::instance().linebreak();
            txt(i18n::s.get("core.locale.ui.inv.equip.you_equip", inv[ci]));
            game_data.player_is_changing_equipment = 1;
            switch (inv[ci].curse_state)
            {
            case CurseState::doomed:
                txt(i18n::s.get("core.locale.ui.inv.equip.doomed", cdata[cc]));
                break;
            case CurseState::cursed:
                txt(i18n::s.get("core.locale.ui.inv.equip.cursed", cdata[cc]));
                break;
            case CurseState::none: break;
            case CurseState::blessed:
                txt(i18n::s.get("core.locale.ui.inv.equip.blessed", cdata[cc]));
                break;
            }
            if (cdata[cc].body_parts[body - 100] / 10000 == 5)
            {
                equip_melee_weapon();
            }
            menucycle = 1;
            result.turn_result = TurnResult::menu_equipment;
            return result;
        }
        if (invctrl == 7)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            result.turn_result = do_read_command();
            return result;
        }
        if (invctrl == 8)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            result.turn_result = do_drink_command();
            return result;
        }
        if (invctrl == 9)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            result.turn_result = do_zap_command();
            return result;
        }
        if (invctrl == 10)
        {
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            ti = inv_getfreeid(tc);
            if (cdata[tc].sleep)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.give.is_sleeping", cdata[tc]));
                snd("core.fail1");
                goto label_2060_internal;
            }
            if (ti == -1)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.give.inventory_is_full", cdata[tc]));
                snd("core.fail1");
                goto label_2060_internal;
            }
            reftype = the_item_db[inv[ci].id]->category;
            if (inv[ci].id == 729)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.give.present.text",
                    cdata[tc],
                    inv[ci]));
                inv[ci].modify_number(-1);
                txt(i18n::s.get(
                    "core.locale.ui.inv.give.present.dialog", cdata[tc]));
                chara_modify_impression(cdata[tc], giftvalue(inv[ci].param4));
                cdata[tc].emotion_icon = 317;
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
            f = 0;
            p = sdata(10, tc) * 500 + sdata(11, tc) * 500 +
                sdata(153, tc) * 2500 + 25000;
            if (cdata[tc].id == 265)
            {
                p *= 5;
            }
            if (inv_weight(tc) + inv[ci].weight > p)
            {
                f = 1;
            }
            if (cdata[tc].id != 265)
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
            if (inv[ci].weight < 0)
            {
                f = 4;
            }
            if (f)
            {
                snd("core.fail1");
                txt(i18n::s.get_enum(
                    "core.locale.ui.inv.give.refuse_dialog", f - 1, cdata[tc]));
                goto label_2060_internal;
            }
            f = 0;
            if (cdata[tc].relationship == 10)
            {
                f = 1;
            }
            else
            {
                if (inv[ci].identification_state <=
                    IdentifyState::partly_identified)
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.give.too_creepy", cdata[tc]));
                    goto label_2060_internal;
                }
                if (is_cursed(inv[ci].curse_state))
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.give.cursed", cdata[tc]));
                    goto label_2060_internal;
                }
                if (reftype == 53000)
                {
                    f = 1;
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/neg/"))
                    {
                        f = 0;
                    }
                    // scroll of teleport/treasure map/deeds
                    switch (inv[ci].id)
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
                    if (the_item_db[inv[ci].id]->subcategory == 52002)
                    {
                        if (cdata[tc].drunk)
                        {
                            snd("core.fail1");
                            txt(i18n::s.get(
                                "core.locale.ui.inv.give.no_more_drink",
                                cdata[tc]));
                            goto label_2060_internal;
                        }
                    }
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/neg/"))
                    {
                        f = 0;
                    }
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/nogive/"))
                    {
                        f = 0;
                    }
                    if (cdata[tc].is_pregnant())
                    {
                        if (inv[ci].id == 262 || inv[ci].id == 519 ||
                            inv[ci].id == 392)
                        {
                            f = 1;
                            txt(i18n::s.get(
                                "core.locale.ui.inv.give.abortion"));
                        }
                    }
                }
            }
            if (f)
            {
                snd("core.equip1");
                txt(i18n::s.get(
                    "core.locale.ui.inv.give.you_hand", inv[ci], cdata[tc]));
                if (inv[ci].id == 477 || inv[ci].id == 473)
                {
                    txt(i18n::s.get(
                            "core.locale.ui.inv.give.engagement", cdata[tc]),
                        Message::color{ColorIndex::green});
                    chara_modify_impression(cdata[tc], 15);
                    cdata[tc].emotion_icon = 317;
                }
                if (inv[ci].id == 620)
                {
                    txt(i18n::s.get(
                            "core.locale.ui.inv.give.love_potion.text",
                            cdata[tc],
                            inv[ci]),
                        Message::color{ColorIndex::purple});
                    snd("core.crush2");
                    txt(i18n::s.get(
                            "core.locale.ui.inv.give.love_potion.dialog",
                            cdata[tc]),
                        Message::color{ColorIndex::cyan});
                    chara_modify_impression(cdata[tc], -20);
                    cdata[tc].emotion_icon = 318;
                    inv[ci].modify_number(-1);
                    goto label_20591;
                }
                item_copy(ci, ti);
                inv[ci].modify_number(-1);
                inv[ti].set_number(1);
                item_stack(tc, ti, 1);
                ci = ti;
                rc = tc;
                chara_set_item_which_will_be_used(cdata[tc]);
                wear_most_valuable_equipment_for_all_body_parts();
                if (tc < 16)
                {
                    create_pcpic(tc);
                }
                chara_refresh(tc);
                refresh_burden_state();
                if (invally == 1)
                {
                    goto label_20591;
                }
                update_screen();
                result.turn_result = TurnResult::turn_end;
                return result;
            }
            snd("core.fail1");
            txt(i18n::s.get(
                "core.locale.ui.inv.give.refuses", cdata[tc], inv[ci]));
            goto label_2060_internal;
        }
        if (invctrl == 13)
        {
            screenupdate = -1;
            update_screen();
            const auto identify_result = item_identify(inv[ci], efp);
            if (identify_result == IdentifyState::unidentified)
            {
                txt(i18n::s.get("core.locale.ui.inv.identify.need_more_power"));
            }
            else if (identify_result != IdentifyState::completely_identified)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.identify.partially", inv[ci]));
            }
            else
            {
                txt(i18n::s.get("core.locale.ui.inv.identify.fully", inv[ci]));
            }
            item_stack(0, ci, 1);
            refresh_burden_state();
            invsubroutine = 0;
            result.succeeded = true;
            return result;
        }
        if (invctrl == 14)
        {
            savecycle();
            result.turn_result = do_use_command();
            return result;
        }
        if (invctrl == 16)
        {
            screenupdate = -1;
            update_screen();
            invsubroutine = 0;
            result.succeeded = true;
            return result;
        }
        if (invctrl == 15)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            result.turn_result = do_open_command();
            return result;
        }
        if (invctrl == 17)
        {
            cidip = ci;
            savecycle();
            invctrl = 18;
            Message::instance().linebreak();
            snd("core.pop2");
            goto label_20591;
        }
        if (invctrl == 18)
        {
            screenupdate = -1;
            update_screen();
            result.turn_result = do_dip_command();
            return result;
        }
        if (invctrl == 19)
        {
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            screenupdate = -1;
            update_screen();
            savecycle();
            result.turn_result = do_offer_command();
            return result;
        }
        if (invctrl == 20)
        {
            citrade = ci;
            invctrl = 21;
            snd("core.pop2");
            goto label_20591;
        }
        if (invctrl == 21)
        {
            if (inv[ci].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            if (cdata[tc].continuous_action)
            {
                cdata[tc].continuous_action.type = ContinuousAction::Type::none;
                cdata[tc].continuous_action.turn = 0;
                cdata[tc].continuous_action.item = 0;
            }
            snd("core.equip1");
            inv[citrade].is_quest_target() = false;
            txt(i18n::s.get(
                "core.locale.ui.inv.trade.you_receive", inv[ci], inv[citrade]));
            if (inv[citrade].body_part != 0)
            {
                p = inv[citrade].body_part;
                cdata[tc].body_parts[p - 100] =
                    cdata[tc].body_parts[p - 100] / 10000 * 10000;
                inv[citrade].body_part = 0;
            }
            ti = citrade;
            item_exchange(ci, ti);
            convertartifact(ci);
            rc = tc;
            ci = citrade;
            if (cdata[rc].item_which_will_be_used == ci)
            {
                cdata[rc].item_which_will_be_used = 0;
            }
            wear_most_valuable_equipment_for_all_body_parts();
            if (tc >= 16)
            {
                supply_new_equipment();
            }
            inv_getfreeid_force();
            chara_refresh(tc);
            refresh_burden_state();
            invsubroutine = 0;
            result.succeeded = true;
            return result;
        }
        if (invctrl == 23)
        {
            if (invctrl(1) == 4)
            {
                if (inv[ci].is_marked_as_no_drop())
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.common.set_as_no_drop"));
                    goto label_2060_internal;
                }
            }
            item_separate(ci);
            invsubroutine = 0;
            result.succeeded = true;
            return result;
        }
        if (invctrl == 24)
        {
            if (invctrl(1) == 0)
            {
                snd("core.inv");
                if (game_data.current_map == mdata_t::MapId::lumiest)
                {
                    game_data.guild.mages_guild_quota -=
                        (inv[ci].param1 + 1) * inv[ci].number();
                    if (game_data.guild.mages_guild_quota <= 0)
                    {
                        game_data.guild.mages_guild_quota = 0;
                    }
                    txt(i18n::s.get(
                            "core.locale.ui.inv.put.guild.you_deliver",
                            inv[ci]) +
                            u8"("s + (inv[ci].param1 + 1) * inv[ci].number() +
                            u8" Guild Point)"s,
                        Message::color{ColorIndex::green});
                    if (game_data.guild.mages_guild_quota == 0)
                    {
                        snd("core.complete1");
                        txt(i18n::s.get(
                                "core.locale.ui.inv.put.guild.you_fulfill"),
                            Message::color{ColorIndex::green});
                    }
                }
                else
                {
                    quest_data.immediate().extra_info_2 +=
                        inv[ci].weight * inv[ci].number();
                    txt(i18n::s.get(
                            "core.locale.ui.inv.put.harvest",
                            inv[ci],
                            cnvweight(inv[ci].weight * inv[ci].number()),
                            cnvweight(quest_data.immediate().extra_info_2),
                            cnvweight(quest_data.immediate().extra_info_1)),
                        Message::color{ColorIndex::green});
                }
                inv[ci].remove();
                refresh_burden_state();
                goto label_20591;
            }
            if (invctrl(1) == 2)
            {
                if (cdata.player().gold < inv[ci].subname)
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.put.tax.not_enough_money"));
                    goto label_2060_internal;
                }
                if (game_data.left_bill <= 0)
                {
                    snd("core.fail1");
                    txt(i18n::s.get(
                        "core.locale.ui.inv.put.tax.do_not_have_to"));
                    goto label_20591;
                }
                cdata.player().gold -= inv[ci].subname;
                snd("core.paygold1");
                txt(i18n::s.get("core.locale.ui.inv.put.tax.you_pay", inv[ci]),
                    Message::color{ColorIndex::green});
                inv[ci].modify_number(-1);
                --game_data.left_bill;
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
            if (invctrl(1) == 8)
            {
                snd("core.card1");
                inv[ci].modify_number(-1);
                txt(i18n::s.get("core.locale.ui.inv.put.deck", inv[ci]));
                ++card(0, inv[ci].subname);
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
        }
        if (invctrl == 25)
        {
            ti = inv_getfreeid(0);
            if (ti == -1)
            {
                txt(i18n::s.get("core.locale.ui.inv.common.inventory_is_full"));
                goto label_2060_internal;
            }
            if (the_item_db[inv[ci].id]->category == 77000)
            {
                snd("core.fail1");
                txt(i18n::s.get(
                        "core.locale.ui.inv.take_ally.refuse_dialog",
                        cdata[tc]),
                    Message::color{ColorIndex::blue});
                goto label_2060_internal;
            }
            if (inv[ci].body_part != 0)
            {
                if (is_cursed(inv[ci].curse_state))
                {
                    txt(i18n::s.get(
                        "core.locale.ui.inv.take_ally.cursed", inv[ci]));
                    goto label_20591;
                }
                p = inv[ci].body_part;
                cdata[tc].body_parts[p - 100] =
                    cdata[tc].body_parts[p - 100] / 10000 * 10000;
                inv[ci].body_part = 0;
            }
            if (inv[ci].id == 477 || inv[ci].id == 473)
            {
                txt(i18n::s.get(
                        "core.locale.ui.inv.take_ally.swallows_ring",
                        cdata[tc],
                        inv[ci]),
                    Message::color{ColorIndex::purple});
                snd("core.offer1");
                chara_modify_impression(cdata[tc], -20);
                cdata[tc].emotion_icon = 318;
                inv[ci].modify_number(-1);
                goto label_20591;
            }
            snd("core.equip1");
            inv[ci].is_quest_target() = false;
            if (inv[ci].id == 54)
            {
                in = inv[ci].number();
            }
            else
            {
                in = 1;
            }
            txt(i18n::s.get(
                "core.locale.ui.inv.take_ally.you_take", itemname(ci, in)));
            if (inv[ci].id == 54)
            {
                earn_gold(cdata.player(), in);
                inv[ci].remove();
            }
            else
            {
                item_copy(ci, ti);
                inv[ci].modify_number((-in));
                inv[ti].set_number(in);
                item_stack(0, ti, 1);
                convertartifact(ti);
            }
            rc = tc;
            wear_most_valuable_equipment_for_all_body_parts();
            if (tc < 16)
            {
                create_pcpic(tc);
            }
            chara_refresh(tc);
            refresh_burden_state();
            goto label_20591;
        }
        if (invctrl == 26)
        {
            savecycle();
            int stat = target_position();
            if (stat != 1)
            {
                if (stat == 0)
                {
                    txt(i18n::s.get("core.locale.ui.inv.throw.cannot_see"));
                    update_screen();
                }
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
            if (chipm(7, cell_data.at(tlocx, tlocy).chip_id_actual) & 4)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.throw.location_is_blocked"));
                update_screen();
                result.turn_result = TurnResult::pc_turn_user_error;
                return result;
            }
            result.turn_result = do_throw_command();
            return result;
        }
        if (invctrl == 27)
        {
            start_stealing();
            invsubroutine = 0;
            result.succeeded = true;
            return result;
        }
        if (invctrl == 28)
        {
            Message::instance().linebreak();
            ti = inv_getfreeid(0);
            if (ti == -1)
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.trade_medals.inventory_full"));
                snd("core.fail1");
                goto label_20591;
            }
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                i = stat;
                p = inv[i].number();
            }
            else
            {
                p = 0;
            }
            if (p < calcmedalvalue(ci))
            {
                txt(i18n::s.get(
                    "core.locale.ui.inv.trade_medals.not_enough_medals"));
                snd("core.fail1");
                goto label_20591;
            }
            inv[i].modify_number(-calcmedalvalue(ci));
            snd("core.paygold1");
            item_copy(ci, ti);
            txt(i18n::s.get(
                "core.locale.ui.inv.trade_medals.you_receive", inv[ti]));
            item_stack(0, ti, 1);
            convertartifact(ti, 1);
            goto label_20591;
        }
    }
    if (action == "identify")
    {
        if (listmax != 0)
        {
            ci = list(0, pagesize * page + cs);
            item_show_description();
            goto label_20591;
        }
    }
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            goto label_2060_internal;
        }
    }
    if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            goto label_2060_internal;
        }
    }
    if (menucycle == 1)
    {
        if (action == "next_menu" || action == "previous_menu")
        {
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
                if (action == "next_menu")
                {
                    ++p;
                    if (cycle(p, i) == -1)
                    {
                        p = 0;
                    }
                }
                if (action == "previous_menu")
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
                    goto label_20591;
                }
            }
        }
    }
    if (action == "switch_mode_2")
    {
        if (invctrl == 1)
        {
            ci = list(0, pagesize * page + cs);
            if (inv[ci].is_marked_as_no_drop())
            {
                inv[ci].is_marked_as_no_drop() = false;
                txt(i18n::s.get(
                    "core.locale.ui.inv.examine.no_drop.unset", inv[ci]));
            }
            else
            {
                inv[ci].is_marked_as_no_drop() = true;
                txt(i18n::s.get(
                    "core.locale.ui.inv.examine.no_drop.set", inv[ci]));
            }
        }
        if (invctrl == 2)
        {
            if (dropcontinue == 0)
            {
                txt(i18n::s.get("core.locale.ui.inv.drop.multi"));
                dropcontinue = 1;
                snd("core.inv");
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
        }
    }
    if (action == "switch_mode")
    {
        if (showresist == 1)
        {
            showresist = 0;
        }
        else
        {
            showresist = 1;
        }
        snd("core.pop1");
        goto label_2060_internal;
    }
    if (action == "cancel")
    {
    label_2063_internal:
        savecycle();
        if (invctrl == 22)
        {
            if (invctrl(1) == 0)
            {
                if (listmax > 0)
                {
                    txt(i18n::s.get("core.locale.ui.inv.take.really_leave"));
                    if (!yes_no())
                    {
                        goto label_2060_internal;
                    }
                }
            }
        }
        cc = 0;
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
            menucycle = 1;
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
            dropcontinue = 0;
            result.turn_result = TurnResult::turn_end;
            return result;
        }
        screenupdate = 0;
        update_screen();
        result.turn_result = TurnResult::pc_turn_user_error;
        return result;
    }
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9 ||
        invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        if (auto shortcut = get_shortcut(action))
        {
            p = list(0, pagesize * page + cs);
            if (inv[p].weight < 0)
            {
                snd("core.fail1");
                txt(i18n::s.get("core.locale.ui.inv.common.shortcut.cargo"));
                goto label_20591;
            }
            snd("core.ok1");
            p = inv[list(0, pagesize * page + cs)].id + invctrl * 10000;
            if (game_data.skill_shortcuts.at(*shortcut) == p)
            {
                game_data.skill_shortcuts.at(*shortcut) = 0;
                goto label_2060_internal;
            }
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                if (game_data.skill_shortcuts.at(cnt) == p)
                {
                    game_data.skill_shortcuts.at(cnt) = 0;
                }
            }
            game_data.skill_shortcuts.at(*shortcut) = p;
            txt(i18n::s.get(
                "core.locale.ui.assign_shortcut",
                get_bound_shortcut_key_name_by_action_id(action)));
            goto label_2060_internal;
        }
    }
    goto label_2061_internal;
}



} // namespace elona
