#include "ui_menu_ctrl_ally.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

void ui_menu_ctrl_ally::init()
{
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    if (allyctrl == ctrl_ally_operation::pet_arena)
    {
        list(0, listmax) = 99;
        list(1, listmax) = -9999;
        ++listmax;
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() == character::state_t::empty)
        {
            continue;
        }
        if (allyctrl == ctrl_ally_operation::sell)
        {
            if (cdata[cnt].state() == character::state_t::pet_dead)
            {
                continue;
            }
        }
        if (allyctrl == ctrl_ally_operation::staying
            || allyctrl == ctrl_ally_operation::gene_engineer)
        {
            if (cdata[cnt].state() != character::state_t::alive)
            {
                continue;
            }
        }
        if (allyctrl == ctrl_ally_operation::gene_engineer)
        {
            if (cnt == rc)
            {
                continue;
            }
        }
        if (cdata[cnt].current_map != 0)
        {
            if (allyctrl == ctrl_ally_operation::sell
                || allyctrl == ctrl_ally_operation::pet_arena)
            {
                continue;
            }
        }
        if (allyctrl != ctrl_ally_operation::sell)
        {
            if (cdata[cnt].is_escorted()
                || cdata[cnt].is_escorted_in_sub_quest())
            {
                continue;
            }
        }
        if (cdata[cnt].is_ridden())
        {
            continue;
        }
        if (cnt == 0)
        {
            continue;
        }
        list(0, listmax) = cnt;
        list(1, listmax) = -cdata[cnt].level;
        ++listmax;
    }
    sort_list_by_column1();
    if (allyctrl == ctrl_ally_operation::pet_arena)
    {
        p = 0;
        DIM2(followerin, 16);
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                continue;
            }
            i = list(0, cnt);
            if (cdata[i].state() != character::state_t::pet_dead)
            {
                followerin(i) = 1;
                ++p;
                if (p == arenaop(1))
                {
                    break;
                }
            }
        }
    }
    windowshadow = 1;
}

void ui_menu_ctrl_ally::update()
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
        txtnew();
    }
    if (allyctrl == ctrl_ally_operation::call_back)
    {
        txt(i18n::s.get("core.locale.ui.ally_list.call.prompt"));
        s(10) = i18n::s.get("core.locale.ui.ally_list.call.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.locale.ui.ally_list.name");
        s(13) = i18n::s.get("core.locale.ui.ally_list.status");
        x = 0;
    }
    if (allyctrl == ctrl_ally_operation::sell)
    {
        txt(i18n::s.get("core.locale.ui.ally_list.sell.prompt"));
        s(10) = i18n::s.get("core.locale.ui.ally_list.sell.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.locale.ui.ally_list.name");
        s(13) = i18n::s.get("core.locale.ui.ally_list.sell.value");
        x = 20;
    }
    if (allyctrl == ctrl_ally_operation::pet_arena)
    {
        i = 0;
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            i += followerin(cnt) == 1;
        }
        if (i < arenaop(1))
        {
            txtef(3);
        }
        else
        {
            txtef(4);
        }
        txt(i18n::s.get("core.locale.ui.ally_list.pet_arena.prompt") + ": " + i
            + u8" / "s + arenaop(1));
        s(10) = i18n::s.get("core.locale.ui.ally_list.pet_arena.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.locale.ui.ally_list.name");
        s(13) = i18n::s.get("core.locale.ui.ally_list.status");
        x = 20;
    }
    if (allyctrl == ctrl_ally_operation::staying)
    {
        if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
        {
            txt(i18n::s.get("core.locale.ui.ally_list.shop.prompt"));
            s(10) = i18n::s.get("core.locale.ui.ally_list.shop.title");
            s(11) = strhint2 + strhint3;
            s(12) = i18n::s.get("core.locale.ui.ally_list.name");
            s(13) =
                i18n::s.get("core.locale.ui.ally_list.shop.chr_negotiation");
        }
        if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
        {
            txt(i18n::s.get("core.locale.ui.ally_list.ranch.prompt"));
            s(10) = i18n::s.get("core.locale.ui.ally_list.ranch.title");
            s(11) = strhint2 + strhint3;
            s(12) = i18n::s.get("core.locale.ui.ally_list.name");
            s(13) = i18n::s.get("core.locale.ui.ally_list.ranch.breed_power");
        }
        if (gdata_current_map == mdata_t::map_id_t::your_home)
        {
            txt(i18n::s.get("core.locale.ui.ally_list.stayer.prompt"));
            s(10) = i18n::s.get("core.locale.ui.ally_list.stayer.title");
            s(11) = strhint2 + strhint3;
            s(12) = i18n::s.get("core.locale.ui.ally_list.name");
            s(13) = i18n::s.get("core.locale.ui.ally_list.status");
        }
        x = 20;
    }
    if (allyctrl == ctrl_ally_operation::investigate
        || allyctrl == ctrl_ally_operation::gene_engineer)
    {
        txt(i18n::s.get("core.locale.ui.ally_list.gene_engineer.prompt"));
        s(10) = i18n::s.get("core.locale.ui.ally_list.gene_engineer.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.locale.ui.ally_list.name");
        s(13) = i18n::s.get("core.locale.ui.ally_list.status");
        if (allyctrl == ctrl_ally_operation::gene_engineer)
        {
            if (rc != 0)
            {
                s(13) = i18n::s.get(
                    "core.locale.ui.ally_list.gene_engineer.body_skill");
            }
        }
        x = 0;
    }
}

void ui_menu_ctrl_ally::draw()
{
    s(0) = s(10);
    s(1) = s(11);
    display_window((windoww - 620) / 2 + inf_screenx, winposy(400), 620, 400);
    display_topic(s(12), wx + 28, wy + 36);
    display_topic(s(13), wx + 350 + x, wy + 36);
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
            boxf(wx + 70, wy + 66 + cnt * 19, 500, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
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
        if (list(0, p) != 99)
        {
            draw_chara_scale_height(
                cdata[list(0, p)], wx + 40, wy + 74 + cnt * 19 - 8);
        }
        i = list(0, p);
        if (i == 99)
        {
            cs_list(
                cs == cnt,
                i18n::s.get("core.locale.ui.ally_list.proceed"),
                wx + 84,
                wy + 66 + cnt * 19 - 1);
            continue;
        }
        if (allyctrl != ctrl_ally_operation::sell)
        {
            s = ""s + cdatan(1, i) + u8" "s + cdatan(0, i);
            if (cdata[i].current_map != 0)
            {
                s = s + u8"("s + mapname(cdata[i].current_map) + u8")"s;
            }
            if (allyctrl == ctrl_ally_operation::pet_arena)
            {
                if (followerin(i) == 1)
                {
                    s += i18n::s.get("core.locale.ui.ally_list.pet_arena.in");
                }
            }
            int n = 0;
            if (allyctrl == ctrl_ally_operation::gene_engineer)
            {
                if (cdata[i].level > sdata(151, 0) + 5)
                {
                    n = 3;
                }
            }
            cs_list(cs == cnt, s, wx + 84, wy + 66 + cnt * 19 - 1, 0, n);
            if (allyctrl != ctrl_ally_operation::staying
                || (allyctrl == ctrl_ally_operation::staying
                    && gdata_current_map == mdata_t::map_id_t::your_home))
            {
                s = u8"Lv."s + cdata[i].level + u8" "s;
                if (cdata[i].state() == character::state_t::pet_dead)
                {
                    s += i18n::s.get("core.locale.ui.ally_list.dead");
                }
                if (cdata[i].state() == character::state_t::pet_waiting)
                {
                    if (allyctrl == ctrl_ally_operation::call_back)
                    {
                        s += i18n::s.get(
                            "core.locale.ui.ally_list.call.waiting");
                    }
                    else
                    {
                        s += u8"(Hp: "s + cdata[i].hp * 100 / cdata[i].max_hp
                            + u8"%) "s
                            + i18n::s.get("core.locale.ui.ally_list.waiting");
                    }
                }
                if (cdata[i].state() == character::state_t::alive)
                {
                    if (allyctrl == ctrl_ally_operation::call_back)
                    {
                        s += i18n::s.get("core.locale.ui.ally_list.alive");
                    }
                    else
                    {
                        s += u8"(Hp: "s + cdata[i].hp * 100 / cdata[i].max_hp
                            + u8"%)"s;
                    }
                }
            }
            else
            {
                if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
                {
                    s = u8"   "s + sdata(17, i) + u8" / " + sdata(156, i);
                }
                if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
                {
                    s = u8"   "s + cbreeder(i);
                }
            }
            if (allyctrl == ctrl_ally_operation::gene_engineer)
            {
                if (rc != 0)
                {
                    tc = i;
                    {
                        int stat = transplant_body_parts();
                        if (stat == -1)
                        {
                            s = i18n::s.get(
                                "core.locale.ui.ally_list.gene_engineer.none");
                        }
                        else
                        {
                            s = i18n::_(u8"ui", u8"body_part", u8"_"s + rtval);
                        }
                    }
                    s += u8"/"s;
                    {
                        int stat = gain_skills_by_geen_engineering();
                        if (stat == 0)
                        {
                            s += i18n::s.get(
                                "core.locale.ui.ally_list.gene_engineer.none");
                        }
                        else
                        {
                            s += ""s
                                + i18n::_(
                                      u8"ability",
                                      std::to_string(rtval),
                                      u8"name");
                            if (rtval(1) != -1)
                            {
                                s += u8", "s
                                    + i18n::_(
                                          u8"ability",
                                          std::to_string(rtval(1)),
                                          u8"name");
                            }
                        }
                    }
                }
            }
            pos(wx + 370, wy + 66 + cnt * 19 + 2);
            mes(s);
        }
        if (allyctrl == ctrl_ally_operation::sell)
        {
            s = ""s + cdatan(1, i) + u8" "s + cdatan(0, i);
            s += u8" Lv."s + cdata[i].level;
            cs_list(cs == cnt, s, wx + 84, wy + 66 + cnt * 19 - 1);
            s = ""s + calcslavevalue(i) * 2 / 3 + i18n::_(u8"ui", u8"gold");
            pos(wx + 390, wy + 66 + cnt * 19 + 2);
            mes(s);
        }
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_ctrl_ally::result> ui_menu_ctrl_ally::_select_gene_engineer(
    int _p)
{
    if (cdata[_p].level > sdata(151, 0) + 5)
    {
        snd(27);
        txt(i18n::s.get(
            "core.locale.ui.ally_list.gene_engineer.skill_too_low"));
        set_reupdate();
        return none;
    }

    return ui_menu_ctrl_ally::result::finish(_p);
}

optional<ui_menu_ctrl_ally::result> ui_menu_ctrl_ally::_select_pet_arena(int _p)
{
    i = 0;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (followerin(cnt) == 1)
        {
            ++i;
        }
    }

    if (_p == 99)
    {
        if (i == 0)
        {
            txt(
                i18n::s.get("core.locale.ui.ally_list.pet_arena.need_"
                            "at_least_one"));
            snd(27);
            set_reupdate();
        }
        else
        {
            snd(20);
            return ui_menu_ctrl_ally::result::finish(1);
        }
    }
    else if (cdata[_p].state() == character::state_t::pet_dead)
    {
        txt(i18n::s.get(
            "core.locale.ui.ally_list.pet_arena.is_dead", cdata[_p]));
        snd(27);
        set_reupdate();
    }
    else if (followerin(_p) == 0)
    {
        if (i >= arenaop(1))
        {
            snd(27);
            txt(i18n::s.get("core.locale.ui.ally_list.pet_arena.too_many"));
            set_reupdate();
        }
        else
        {
            followerin(_p) = 1;
            snd(20);
        }
    }
    else
    {
        followerin(_p) = 0;
        snd(20);
    }
    return none;
}

optional<ui_menu_ctrl_ally::result> ui_menu_ctrl_ally::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_ITEM(p, 0);

    if (p != -1)
    {
        if (allyctrl == ctrl_ally_operation::gene_engineer)
        {
            return _select_gene_engineer(p);
        }
        else if (allyctrl == ctrl_ally_operation::pet_arena)
        {
            return _select_pet_arena(p);
        }
        else
        {
            return ui_menu_ctrl_ally::result::finish(p(0));
        }
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel)
    {
        return ui_menu_ctrl_ally::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
