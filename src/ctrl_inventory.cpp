#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "command.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "shop.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{

menu_result ctrl_inventory()
{
    menu_result result = {false, false, turn_result_t::none};
    int mainweapon = 0;
    int countequip = 0;
    int showmoney = 0;
    int citrade = 0;
    int dropcontinue = 0;
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
        if (mdata(6) == 1)
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
            if (invctrl == 2 || invctrl == 6 || invctrl == 10 || invctrl == 12
                || invctrl == 16 || invctrl == 20 || invctrl == 21
                || invctrl == 23 || invctrl == 24 || invctrl == 25)
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
                p = map(tlocx, tlocy, 1) - 1;
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
        if (invctrl != 1 && invctrl != 5 && invctrl != 13 && invctrl != 14
            && invctrl != 18 && invctrl != 20 && invctrl != 23 && invctrl != 25
            && invctrl != 27)
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
            if (inv[cnt].number <= 0)
            {
                item_remove(inv[cnt]);
                continue;
            }
            if (inv[cnt].id == 488)
            {
                inv[cnt].function = 9;
            }
            if (inv[cnt].id >= 800 || inv[cnt].id < 0)
            {
                dialog(i18n::s.get("core.locale.ui.inv.common.invalid", cnt, inv[cnt].id));
                item_remove(inv[cnt]);
                inv[cnt].id = 0;
                continue;
            }
            if (mdata(6) == 1)
            {
                if (invctrl == 7)
                {
                    if (the_item_db[inv[cnt].id]->subcategory != 53100
                        && inv[cnt].id != 621)
                    {
                        continue;
                    }
                }
            }
            if (cnt2 == 0)
            {
                if (invctrl == 27)
                {
                    if (inv[cnt].position.x != tlocx
                        || inv[cnt].position.y != tlocy)
                    {
                        continue;
                    }
                }
                else if (invctrl != 11 && invctrl != 22 && invctrl != 28)
                {
                    if (inv[cnt].position.x != cdata[cc].position.x
                        || inv[cnt].position.y != cdata[cc].position.y)
                    {
                        continue;
                    }
                }
            }
            item_checkknown(cnt);
            reftype = the_item_db[inv[cnt].id]->category;
            if (inv[cnt].own_state == 5)
            {
                if (ibit(16, cnt) == 0 || invctrl != 14)
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
                    if (mainweapon == -1
                        || inv[cnt].body_part < inv[mainweapon].body_part)
                    {
                        mainweapon = cnt;
                    }
                }
            }
            if (invctrl == 5)
            {
                if (reftype != 57000 && reftype != 91000
                    && inv[cnt].material != 35)
                {
                    continue;
                }
            }
            if (invctrl == 6)
            {
                if (iequiploc(cnt) != cdata_body_part(cc, body) / 10000)
                {
                    continue;
                }
            }
            if (invctrl == 7)
            {
                if (the_item_db[inv[cnt].id]->is_readable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 8)
            {
                if (the_item_db[inv[cnt].id]->is_drinkable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 9)
            {
                if (the_item_db[inv[cnt].id]->is_zappable == 0)
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
                if (ibit(5, cnt) == 1)
                {
                    continue;
                }
                if (inv[cnt].param3 < 0)
                {
                    continue;
                }
                if (inv[cnt].quality == 6)
                {
                    continue;
                }
            }
            if (invctrl == 13)
            {
                if (inv[cnt].identification_state
                    == identification_state_t::completely_identified)
                {
                    continue;
                }
            }
            if (invctrl == 14)
            {
                if (inv[cnt].function == 0
                    && the_item_db[inv[cnt].id]->is_usable == 0
                    && ibit(10, cnt) == 0)
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
                if (calcitemvalue(cnt, 0) * inv[cnt].number
                    < calcitemvalue(citrade, 0) * inv[citrade].number / 2 * 3)
                {
                    continue;
                }
                if (ibit(9, cnt))
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
                    if (ibit(4, cnt) == 0)
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
                    if (inv[cnt].quality >= 4 || reftype >= 50000)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 0)
                {
                    if (gdata_current_map == 36)
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
                if (invctrl != 1 && invctrl != 2 && invctrl != 3
                    && invctrl != 5)
                {
                    continue;
                }
            }
            if (invctrl == 26)
            {
                if (reftype != 52000 && inv[cnt].id != 578 && inv[cnt].id != 685
                    && inv[cnt].id != 699 && inv[cnt].id != 772)
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
            txt(i18n::s.get("core.locale.ui.inv.trade.too_low_value", inv[citrade]));
            f = 1;
        }
        if (invctrl == 27)
        {
            if (tc != 0)
            {
                txt(i18n::s.get("core.locale.ui.inv.steal.has_nothing", cdata[tc]));
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
            ++msgdup;
            txt(i18n::s.get("core.locale.ui.inv.offer.no_altar"));
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
            if (gdata_current_map == 36)
            {
                if (gdata_mages_guild_quota <= 0)
                {
                    txt(i18n::s.get("core.locale.ui.inv.put.guild.have_no_quota"));
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
        result.turn_result = turn_result_t::pc_turn_user_error;
        return result;
    }
    sort_list_by_column1();
    if (invctrl == 3)
    {
        if (listmax == 0)
        {
            result.turn_result = turn_result_t::turn_end;
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
            if (auto text = i18n::s.get_enum_optional("core.locale.ui.inv.title", cnt, valn))
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
            txtnew();
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
                p = inv[stat].number;
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
                if (gdata_current_map == 36)
                {
                    txt(i18n::s.get("core.locale.ui.inv.put.guild.remaining",
                                    gdata_mages_guild_quota));
                }
            }
        }
    }
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_inv.bmp", 1);
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
                if (ibit(4, ci))
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
                txtnew();
                txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            }
            invsc = 0;
            update_screen();
            result.turn_result = turn_result_t::pc_turn_user_error;
            return result;
        }
        invsc = 0;
        if (mdata(6) == 1)
        {
            if (invctrl == 9 || invctrl == 15 || invctrl == 26)
            {
                txtnew();
                txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
                update_screen();
                result.turn_result = turn_result_t::pc_turn_user_error;
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
        pos(x - 28, y - 8);
        gcopy(3, 64, 288, 50, 32);
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
        else if (mdata(6) == 1)
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
            pos(x + cnt * 44 + 20, y - 24);
            gcopy(3, 288 + invicon(p) * 48, 48, 48, 48);
            if (invctrl == p)
            {
                gmode(5, 70);
                pos(x + cnt * 44 + 20, y - 24);
                gcopy(3, 288 + invicon(p) * 48, 48, 48, 48);
                gmode(2);
            }
            bmes(
                i18n::_(u8"ui", u8"inventory_command", u8"_"s + p),
                x + cnt * 44 + 46
                    - strlen_u(
                          i18n::_(u8"ui", u8"inventory_command", u8"_"s + p))
                        * 3,
                y + 7,
                invctrl == p ? snail::color{255, 255, 255}
                             : snail::color{165, 165, 165});
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
            ""s + key_prev + u8","s + key_next + u8",Tab "s
            + "[" + i18n::s.get("core.locale.ui.inv.window.change") + "]",
            x + 325,
            y + 32);
    }
label_2061_internal:
    s = i18n::s.get("core.locale.ui.inv.window.select_item",
                    i18n::_(u8"ui", u8"inventory_command", u8"_"s + invctrl));
    s(1) = strhint2 + strhint5 + strhint5b + strhint3;
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9
        || invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        s(1) += strhint7;
    }
    if (invctrl == 1)
    {
        s(1) += ""s + key_mode2 + u8" "s
            + "[" + i18n::s.get("core.locale.ui.inv.window.tag.no_drop") + "]";
    }
    if (invctrl == 2)
    {
        if (dropcontinue == 0)
        {
            s(1) += ""s + key_mode2 + u8" "s
                + "[" + i18n::s.get("core.locale.ui.inv.window.tag.multi_drop") + "]";
        }
    }
    display_window((windoww - 640) / 2 + inf_screenx, winposy(432), 640, 432);
    if (invicon(invctrl) != -1)
    {
        pos(wx + 46, wy - 14);
        gcopy(3, 288 + invicon(invctrl) * 48, 48, 48, 48);
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
    display_topic(i18n::s.get("core.locale.ui.inv.window.name"), wx + 28, wy + 30);
    display_topic(s, wx + 526, wy + 30);
    if (showresist)
    {
        pos(wx + 300, wy + 40);
        mes(i18n::s.get("core.locale.ui.inv.window.resist"));
    }
    pos(wx + ww - 136, wy - 6);
    gcopy(3, 960, 96, 144, 48);
    if (showresist == 0)
    {
        pos(wx + ww - 186, wy - 6);
        gcopy(3, 960, 144, 48, 72);
    }
    pos(wx + ww - 246, wy - 6);
    gcopy(3, 1008, 144, 48, 72);
    pos(wx - 6, wy - 6);
    gcopy(3, 960, 216, 48, 72);
    s = ""s + listmax + u8" items"s;
    s += "  ("s + i18n::s.get("core.locale.ui.inv.window.total_weight",
                     cnvweight(cdata[0].inventory_weight),
                     cnvweight(cdata[0].max_inventory_weight),
                     cnvweight(gdata_cargo_weight)) + ")"s;
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
        pos(x + 16, y + 17);
        mes(u8"DV:"s + cdata[tc].dv + u8" PV:"s + cdata[tc].pv);
        pos(x + 16, y + 35);
        mes(i18n::s.get("core.locale.ui.inv.take_ally.window.equip_weight") + ":"
            + cnvweight(cdata[tc].sum_of_equipment_weight) + ""s
            + cnveqweight(tc));
        x = wx + 40;
        y = wy + wh - 65 - wh % 8;
        pos(x, y);
        mes(i18n::s.get("core.locale.ui.inv.take_ally.window.equip"));
        x += 60;
        for (int cnt = 100; cnt < 130; ++cnt)
        {
            if (cdata_body_part(tc, cnt) == 0)
            {
                continue;
            }
            p = cdata_body_part(tc, cnt);
            if (p % 10000 != 0)
            {
                color(50, 50, 200);
            }
            else
            {
                color(100, 100, 100);
            }
            pos(x, y);
            mes(""s + i18n::_(u8"ui", u8"body_part", u8"_"s + (p / 10000)));
            color(0, 0, 0);
            x += (i18n::_(u8"ui", u8"body_part", u8"_"s + (p / 10000)).size()
                  + 1)
                * 6;
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
        s(0) = itemname(p, inv[p].number);
        s(1) = cnvweight(inv[p].weight * inv[p].number);
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
            s(1) = i18n::s.get("core.locale.ui.inv.trade_medals.medal_value", calcmedalvalue(p));
        }
        if (invctrl != 3 && invctrl != 11 && invctrl != 22 && invctrl != 27
            && invctrl != 28)
        {
            if (p >= 5080)
            {
                s += i18n::space_if_needed() + "("
                    + i18n::s.get("core.locale.ui.inv.window.ground")
                    + ")";
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (gdata(40 + cnt) == inv[p].id + invctrl * 10000)
            {
                s += u8"{"s + cnt + u8"}"s;
            }
        }
        display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
        p(1) = inv[p].image % 1000;
        prepare_item_image(p(1), inv[p].color, inv[p].param1);
        pos(wx + 37, wy + 69 + cnt * 19);
        gmode(2);
        gcopy_c(
            1,
            0,
            960,
            item_chips[p(1)].width,
            item_chips[p(1)].height,
            item_chips[p(1)].width * inf_tiles / item_chips[p(1)].height,
            inf_tiles);
        if (inv[p].body_part != 0)
        {
            draw("equipped", wx + 46, wy + 72 + cnt * 18 - 3);
            if (p == mainweapon)
            {
                s += i18n::space_if_needed() + "("
                    + i18n::s.get("core.locale.ui.inv.window.main_hand")
                    + ")";
            }
        }
        if (showresist)
        {
            equipinfo(p, wx + 300, wy + 60 + cnt * 19 + 2);
            s = strmid(s, 0, 24);
        }
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, 1, p);
        pos(wx + 600 - strlen_u(s(1)) * 7, wy + 60 + cnt * 19 + 2);
        mes(s(1));
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
            pos(wx + 368, wy + 37 - en * 2);
            mes(""s + cdata[tc].gold + u8" gp"s);
        }
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    invmark(invctrl) = page * 1000 + cs;
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (mode == 9)
    {
        if (listmax == 0)
        {
            p = -1;
            key = key_cancel;
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
            if (ibit(13, ci))
            {
                snd(27);
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            if (!inv_getspace(-1))
            {
                txt(i18n::s.get("core.locale.ui.inv.drop.cannot_anymore"));
                snd(27);
                goto label_2060_internal;
            }
            if (mdata(18) != 0)
            {
                if (inv_sum(-1) >= mdata(18))
                {
                    if (the_item_db[inv[ci].id]->category != 60000)
                    {
                        txt(i18n::s.get("core.locale.ui.inv.drop.cannot_anymore"));
                        snd(27);
                        goto label_2060_internal;
                    }
                }
            }
            if (inv[ci].number > 1)
            {
                txt(i18n::s.get("core.locale.ui.inv.drop.how_many",
                                inv[ci].number, inv[ci]));
                display_msg(screenmsgy, 1);
                inputlog = ""s + inv[ci].number;
                input_number_dialog(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    inv[ci].number);
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number)
                {
                    in = inv[ci].number;
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
            dropval = 0;
            drop_item();
            if (dropcontinue)
            {
                menucycle = 1;
                ++dropcontinue;
                goto label_20591;
            }
            result.turn_result = turn_result_t::turn_end;
            return result;
        }
        if (invctrl == 3 || invctrl == 11 || invctrl == 12 || invctrl == 22
            || (invctrl == 24 && (invctrl(1) == 3 || invctrl(1) == 5)))
        {
            if (invctrl != 3 && invctrl != 22)
            {
                if (ibit(13, ci))
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                    goto label_2060_internal;
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 3 || invctrl(1) == 5)
                {
                    if (inv_sum(-1) >= invcontainer)
                    {
                        snd(27);
                        txt(i18n::s.get("core.locale.ui.inv.put.container.full"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (inv[ci].weight >= efp * 100)
                    {
                        snd(27);
                        txt(i18n::s.get("core.locale.ui.inv.put.container.too_heavy",
                                        cnvweight(efp * 100)));
                        goto label_2060_internal;
                    }
                    if (inv[ci].weight <= 0)
                    {
                        snd(27);
                        txt(i18n::s.get("core.locale.ui.inv.put.container.cannot_hold_cargo"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!actionsp(0, 10))
                    {
                        txt(lang(
                            u8"疲労し過ぎて失敗した！"s,
                            u8"You are too exhausted!"s));
                        goto label_2063_internal;
                    }
                }
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    if (gdata_rights_to_succeed_to < 1)
                    {
                        txt(i18n::s.get("core.locale.ui.inv.take.no_claim"));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!actionsp(0, 10))
                    {
                        txt(lang(
                            u8"疲労し過ぎて失敗した！"s,
                            u8"You are too exhausted!"s));
                        goto label_2063_internal;
                    }
                }
            }
            if (inv[ci].own_state > 0 && inv[ci].own_state < 3)
            {
                snd(27);
                ++msgdup;
                if (inv[ci].own_state == 2)
                {
                    txt(i18n::s.get("core.locale.action.get.cannot_carry"));
                }
                if (inv[ci].own_state == 1)
                {
                    txt(i18n::s.get_enum("core.locale.action.get.not_owned", rnd(3)));
                }
                update_screen();
                result.turn_result = turn_result_t::pc_turn_user_error;
                return result;
            }
            page_save();
            if (mode == 6 && inv[ci].number > 1 && invctrl != 22)
            {
                if (invctrl == 11)
                {
                    txt(i18n::s.get("core.locale.ui.inv.buy.how_many",
                                    inv[ci].number, inv[ci]));
                }
                if (invctrl == 12)
                {
                    txt(i18n::s.get("core.locale.ui.inv.sell.how_many",
                                    inv[ci].number, inv[ci]));
                }
                display_msg(screenmsgy, 2);
                inputlog = ""s + inv[ci].number;
                input_number_dialog(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    inv[ci].number);
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number)
                {
                    in = inv[ci].number;
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
                in = inv[ci].number;
            }
            if (mode == 6 && invctrl != 22 && invctrl != 24)
            {
                if (invctrl == 11)
                {
                    txt(i18n::s.get("core.locale.ui.inv.buy.prompt",
                                    itemname(ci, in), (in * calcitemvalue(ci, 0))));
                }
                if (invctrl == 12)
                {
                    txt(i18n::s.get("core.locale.ui.inv.sell.prompt",
                                    itemname(ci, in), (in * calcitemvalue(ci, 0))));
                }
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    screenupdate = -1;
                    update_screen();
                    goto label_20591;
                }
                if (invctrl == 11)
                {
                    if (calcitemvalue(ci, 0) * in > cdata[0].gold)
                    {
                        screenupdate = -1;
                        update_screen();
                        txt(i18n::s.get_enum("core.locale.ui.inv.buy.not_enough_money", rnd(2)));
                        msgkeep = 1;
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
                            txt(i18n::s.get("core.locale.ui.inv.sell.not_enough_money",
                                            cdata[tc]));
                            msgkeep = 1;
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
                result.turn_result = turn_result_t::turn_end;
                return result;
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    --gdata_rights_to_succeed_to;
                    if (invctrl(1) == 1)
                    {
                        txt(i18n::s.get("core.locale.ui.inv.take.can_claim_more",
                                        gdata_rights_to_succeed_to));
                    }
                }
                if (invctrl(1) == 4)
                {
                    ++gdata_gift_count_of_little_sister;
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
            if (ibit(13, ci))
            {
                snd(27);
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            screenupdate = -1;
            update_screen();
            savecycle();
            if (cdata[0].nutrition > 10000)
            {
                txt(i18n::s.get_enum("core.locale.ui.inv.eat.too_bloated", rnd(3)));
                update_screen();
                result.turn_result = turn_result_t::pc_turn_user_error;
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
            snd(13);
            txtnew();
            txt(i18n::s.get("core.locale.ui.inv.equip.you_equip", inv[ci]));
            gdata(808) = 1;
            switch (inv[ci].curse_state)
            {
            case curse_state_t::doomed:
                txt(i18n::s.get("core.locale.ui.inv.equip.doomed", cdata[cc]));
                break;
            case curse_state_t::cursed:
                txt(i18n::s.get("core.locale.ui.inv.equip.cursed", cdata[cc]));
                break;
            case curse_state_t::none: break;
            case curse_state_t::blessed:
                txt(i18n::s.get("core.locale.ui.inv.equip.blessed", cdata[cc]));
                break;
            }
            if (cdata_body_part(cc, body) / 10000 == 5)
            {
                equip_melee_weapon();
            }
            menucycle = 1;
            result.turn_result = turn_result_t::menu_equipment;
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
            if (ibit(13, ci))
            {
                snd(27);
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            ti = inv_getfreeid(tc);
            if (cdata[tc].sleep)
            {
                txt(i18n::s.get("core.locale.ui.inv.give.is_sleeping", cdata[tc]));
                snd(27);
                goto label_2060_internal;
            }
            if (ti == -1)
            {
                txt(i18n::s.get("core.locale.ui.inv.give.inventory_is_full", cdata[tc]));
                snd(27);
                goto label_2060_internal;
            }
            reftype = the_item_db[inv[ci].id]->category;
            if (inv[ci].id == 729)
            {
                txt(i18n::s.get("core.locale.ui.inv.give.present.text", cdata[tc], inv[ci]));
                --inv[ci].number;
                refresh_burden_state();
                txt(i18n::s.get("core.locale.ui.inv.give.present.dialog", cdata[tc]));
                chara_mod_impression(tc, giftvalue(inv[ci].param4));
                cdata[tc].emotion_icon = 317;
                update_screen();
                result.turn_result = turn_result_t::pc_turn_user_error;
                return result;
            }
            f = 0;
            p = sdata(10, tc) * 500 + sdata(11, tc) * 500
                + sdata(153, tc) * 2500 + 25000;
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
                s(0) = "";
                for (int cnt = 0; cnt < 4; cnt++)
                {
                    s(cnt + 1) = i18n::s.get_enum("core.locale.ui.inv.give.refuse_dialog", cnt);
                }
                snd(27);
                txt(lang(name(tc) + s(f), s(f)));
                goto label_2060_internal;
            }
            f = 0;
            if (cdata[tc].relationship == 10)
            {
                f = 1;
            }
            else
            {
                if (inv[ci].identification_state
                    <= identification_state_t::partly_identified)
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.give.too_creepy", cdata[tc]));
                    goto label_2060_internal;
                }
                if (is_cursed(inv[ci].curse_state))
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.give.cursed", cdata[tc]));
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
                            snd(27);
                            txt(i18n::s.get("core.locale.ui.inv.give.no_more_drink", cdata[tc]));
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
                        if (inv[ci].id == 262 || inv[ci].id == 519
                            || inv[ci].id == 392)
                        {
                            f = 1;
                            txt(i18n::s.get("core.locale.ui.inv.give.abortion"));
                        }
                    }
                }
            }
            if (f)
            {
                snd(13);
                txt(i18n::s.get("core.locale.ui.inv.give.you_hand", inv[ci], cdata[tc]));
                if (inv[ci].id == 477 || inv[ci].id == 473)
                {
                    txtef(2);
                    txt(i18n::s.get("core.locale.ui.inv.give.engagement", cdata[tc]));
                    chara_mod_impression(tc, 15);
                    cdata[tc].emotion_icon = 317;
                }
                if (inv[ci].id == 620)
                {
                    txtef(8);
                    txt(i18n::s.get("core.locale.ui.inv.give.love_potion.text",
                                    cdata[tc], inv[ci]));
                    snd(47);
                    txtef(9);
                    txt(i18n::s.get_enum("core.locale.ui.inv.give.love_potion.dialog", rnd(3),
                                    cdata[tc]));
                    chara_mod_impression(tc, -20);
                    cdata[tc].emotion_icon = 318;
                    --inv[ci].number;
                    refresh_burden_state();
                    goto label_20591;
                }
                item_copy(ci, ti);
                --inv[ci].number;
                inv[ti].number = 1;
                item_stack(tc, ti, 1);
                ci = ti;
                rc = tc;
                chara_set_item_which_will_be_used();
                wear_most_valuable_equipment_for_all_body_parts();
                if (tc < 16)
                {
                    create_pcpic(tc, true);
                }
                chara_refresh(tc);
                refresh_burden_state();
                if (invally == 1)
                {
                    goto label_20591;
                }
                update_screen();
                result.turn_result = turn_result_t::turn_end;
                return result;
            }
            snd(27);
            txt(i18n::s.get("core.locale.ui.inv.give.refuses", cdata[tc], inv[ci]));
            goto label_2060_internal;
        }
        if (invctrl == 13)
        {
            screenupdate = -1;
            update_screen();
            const auto identify_result = item_identify(inv[ci], efp);
            if (identify_result == identification_state_t::unidentified)
            {
                txt(i18n::s.get("core.locale.ui.inv.identify.need_more_power"));
            }
            else if (
                identify_result
                != identification_state_t::completely_identified)
            {
                txt(i18n::s.get("core.locale.ui.inv.identify.partially", inv[ci]));
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
            txtnew();
            snd(26);
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
            if (ibit(13, ci))
            {
                snd(27);
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
            snd(26);
            goto label_20591;
        }
        if (invctrl == 21)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
                goto label_2060_internal;
            }
            if (cdata[tc].continuous_action_id != 0)
            {
                cdata[tc].continuous_action_id = 0;
                cdata[tc].continuous_action_turn = 0;
                cdata[tc].continuous_action_item = 0;
            }
            snd(13);
            ibitmod(12, citrade, 0);
            txt(i18n::s.get("core.locale.ui.inv.trade.you_receive", inv[ci], inv[citrade]));
            if (inv[citrade].body_part != 0)
            {
                p = inv[citrade].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
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
                if (ibit(13, ci))
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.common.set_as_no_drop"));
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
                snd(100);
                if (gdata_current_map == 36)
                {
                    gdata_mages_guild_quota -=
                        (inv[ci].param1 + 1) * inv[ci].number;
                    if (gdata_mages_guild_quota <= 0)
                    {
                        gdata_mages_guild_quota = 0;
                    }
                    txtef(2);
                    txt(i18n::s.get("core.locale.ui.inv.put.guild.you_deliver", inv[ci])
                        + u8"("s + (inv[ci].param1 + 1) * inv[ci].number
                        + u8" Guild Point)"s);
                    if (gdata_mages_guild_quota == 0)
                    {
                        snd(51);
                        txtef(2);
                        txt(i18n::s.get("core.locale.ui.inv.put.guild.you_fulfill"));
                    }
                }
                else
                {
                    qdata(13, gdata_executing_immediate_quest) +=
                        inv[ci].weight * inv[ci].number;
                    txtef(2);
                    txt(i18n::s.get("core.locale.ui.inv.put.harvest",
                                    inv[ci],
                                    cnvweight(inv[ci].weight * inv[ci].number),
                                    cnvweight(qdata(13, gdata_executing_immediate_quest)),
                                    cnvweight(qdata(12, gdata_executing_immediate_quest))));
                }
                item_remove(inv[ci]);
                refresh_burden_state();
                goto label_20591;
            }
            if (invctrl(1) == 2)
            {
                if (cdata[0].gold < inv[ci].subname)
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.put.tax.not_enough_money"));
                    goto label_2060_internal;
                }
                if (gdata_left_bill <= 0)
                {
                    snd(27);
                    txt(i18n::s.get("core.locale.ui.inv.put.tax.do_not_have_to"));
                    goto label_20591;
                }
                cdata[0].gold -= inv[ci].subname;
                snd(12);
                txtef(2);
                txt(i18n::s.get("core.locale.ui.inv.put.tax.you_pay", inv[ci]));
                --inv[ci].number;
                --gdata_left_bill;
                refresh_burden_state();
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
            if (invctrl(1) == 8)
            {
                snd(71);
                --inv[ci].number;
                txt(i18n::s.get("core.locale.ui.inv.put.deck", inv[ci]));
                ++card(0, inv[ci].subname);
                refresh_burden_state();
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
                txt(lang(
                    u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
                goto label_2060_internal;
            }
            f = 0;
            if (the_item_db[inv[ci].id]->category == 77000)
            {
                f = 2;
            }
            if (f != 0)
            {
                s(0) = "";
                for (int cnt = 0; cnt < 4; cnt++)
                {
                    s(cnt + 1) = i18n::s.get_enum("core.locale.ui.inv.take_ally.refuse_dialog", cnt);
                }
                snd(27);
                txtef(4);
                txt(lang(name(tc) + s(f), s(f)));
                goto label_2060_internal;
            }
            if (inv[ci].body_part != 0)
            {
                if (is_cursed(inv[ci].curse_state))
                {
                    txt(i18n::s.get("core.locale.ui.inv.take_ally.cursed", inv[ci]));
                    goto label_20591;
                }
                p = inv[ci].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
                inv[ci].body_part = 0;
            }
            if (inv[ci].id == 477 || inv[ci].id == 473)
            {
                txtef(8);
                txt(i18n::s.get("core.locale.ui.inv.take_ally.swallows_ring", cdata[tc], inv[ci]));
                snd(65);
                chara_mod_impression(tc, -20);
                cdata[tc].emotion_icon = 318;
                --inv[ci].number;
                goto label_20591;
            }
            snd(13);
            ibitmod(12, ci, 0);
            if (inv[ci].id == 54)
            {
                in = inv[ci].number;
            }
            else
            {
                in = 1;
            }
            txt(i18n::s.get("core.locale.ui.inv.take_ally.you_take", itemname(ci, in)));
            if (inv[ci].id == 54)
            {
                cdata[0].gold += in;
                item_remove(inv[ci]);
            }
            else
            {
                item_copy(ci, ti);
                inv[ci].number -= in;
                inv[ti].number = in;
                item_stack(0, ti, 1);
                convertartifact(ti);
            }
            rc = tc;
            wear_most_valuable_equipment_for_all_body_parts();
            if (tc < 16)
            {
                create_pcpic(tc, true);
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
                result.turn_result = turn_result_t::pc_turn_user_error;
                return result;
            }
            if (chipm(7, map(tlocx, tlocy, 0)) & 4)
            {
                txt(i18n::s.get("core.locale.ui.inv.throw.location_is_blocked"));
                update_screen();
                result.turn_result = turn_result_t::pc_turn_user_error;
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
            txtnew();
            ti = inv_getfreeid(0);
            if (ti == -1)
            {
                txt(i18n::s.get("core.locale.ui.inv.trade_medals.inventory_full"));
                snd(27);
                goto label_20591;
            }
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                i = stat;
                p = inv[i].number;
            }
            else
            {
                p = 0;
            }
            if (p < calcmedalvalue(ci))
            {
                txt(i18n::s.get("core.locale.ui.inv.trade_medals.not_enough_medals"));
                snd(27);
                goto label_20591;
            }
            inv[i].number -= calcmedalvalue(ci);
            snd(12);
            item_copy(ci, ti);
            txt(i18n::s.get("core.locale.ui.inv.trade_medals.you_receive", inv[ti]));
            item_stack(0, ti, 1);
            convertartifact(ti, 1);
            goto label_20591;
        }
    }
    if (key == key_identify)
    {
        if (listmax != 0)
        {
            ci = list(0, pagesize * page + cs);
            item_show_description();
            goto label_20591;
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_2060_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_2060_internal;
        }
    }
    if (menucycle == 1)
    {
        if (key == key_next || key == key_prev)
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
            else if (mdata(6) == 1)
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
                if (key == key_next)
                {
                    ++p;
                    if (cycle(p, i) == -1)
                    {
                        p = 0;
                    }
                }
                if (key == key_prev)
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
                    snd(100);
                    screenupdate = -1;
                    update_screen();
                    goto label_20591;
                }
            }
        }
    }
    if (key == key_mode2)
    {
        if (invctrl == 1)
        {
            ci = list(0, pagesize * page + cs);
            if (ibit(13, ci) == 0)
            {
                ibitmod(13, ci, 1);
                txt(i18n::s.get("core.locale.ui.inv.examine.no_drop.set", inv[ci]));
            }
            else
            {
                ibitmod(13, ci, 0);
                txt(i18n::s.get("core.locale.ui.inv.examine.no_drop.unset", inv[ci]));
            }
        }
        if (invctrl == 2)
        {
            if (dropcontinue == 0)
            {
                txt(i18n::s.get("core.locale.ui.inv.drop.multi"));
                dropcontinue = 1;
                snd(100);
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
        }
    }
    if (key == key_mode)
    {
        if (showresist == 1)
        {
            showresist = 0;
        }
        else
        {
            showresist = 1;
        }
        snd(1);
        goto label_2060_internal;
    }
    if (key == key_cancel)
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
                    ELONA_YES_NO_PROMPT();
                    rtval = show_prompt(promptx, prompty, 160);
                    if (rtval != 0)
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
            result.turn_result = turn_result_t::menu_equipment;
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
            result.turn_result = turn_result_t::turn_end;
            return result;
        }
        screenupdate = 0;
        update_screen();
        result.turn_result = turn_result_t::pc_turn_user_error;
        return result;
    }
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9
        || invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        if (key == u8"sc"s)
        {
            p = list(0, pagesize * page + cs);
            if (inv[p].weight < 0)
            {
                snd(27);
                txt(i18n::s.get("core.locale.ui.inv.common.shortcut.cargo"));
                goto label_20591;
            }
            snd(20);
            p = inv[list(0, pagesize * page + cs)].id + invctrl * 10000;
            if (gdata(40 + sc) == p)
            {
                gdata(40 + sc) = 0;
                goto label_2060_internal;
            }
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                if (gdata(40 + cnt) == p)
                {
                    gdata(40 + cnt) = 0;
                }
            }
            gdata(40 + sc) = p;
            txt(i18n::s.get("core.locale.ui.inv.common.shortcut.assigned", sc));
            goto label_2060_internal;
        }
    }
    goto label_2061_internal;
}



} // namespace elona
