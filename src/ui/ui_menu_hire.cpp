#include "ui_menu_hire.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

void ui_menu_hire::_populate_list()
{
    for (auto&& cnt : cdata.all())
    {
        if (_operation == hire_operation::revive)
        {
            if (cnt.state() != character::state_t::pet_dead
                && cnt.state() != character::state_t::villager_dead)
            {
                continue;
            }
        }
        else
        {
            if (_operation == hire_operation::hire)
            {
                if (cnt.state() != character::state_t::servant_being_selected)
                {
                    continue;
                }
            }
            else if (cnt.state() != character::state_t::alive)
            {
                continue;
            }
            if (cnt.index < 16)
            {
                if (cnt.current_map != gdata_current_map)
                {
                    continue;
                }
            }
        }
        if (cnt.index == 0)
        {
            continue;
        }
        if (cnt.is_escorted_in_sub_quest() == 1)
        {
            continue;
        }
        list(0, listmax) = cnt.index;
        list(1, listmax) = -cnt.level;
        ++listmax;
    }
    sort_list_by_column1();
}

void ui_menu_hire::init()
{
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    windowshadow = 1;

    _populate_list();
}

void ui_menu_hire::update()
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

void ui_menu_hire::draw()
{
    s(0) = i18n::s.get("core.locale.ui.npc_list.title");
    s(1) = strhint2 + strhint3;
    display_window((windoww - 700) / 2 + inf_screenx, winposy(448), 700, 448);
    if (_operation == hire_operation::move)
    {
        s = i18n::s.get("core.locale.ui.npc_list.wage");
    }
    else
    {
        s = i18n::s.get("core.locale.ui.npc_list.init_cost");
    }
    display_topic(
        i18n::s.get("core.locale.ui.npc_list.name"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.npc_list.info"), wx + 350, wy + 36);
    if (_operation != hire_operation::revive)
    {
        display_topic(s, wx + 490, wy + 36);
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
            boxf(wx + 70, wy + 66 + cnt * 19, 600, 18, {12, 14, 16, 16});
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

        draw_chara_scale_height(
            cdata[list(0, p)], wx + 40, wy + 74 + cnt * 19 - 8);

        i = list(0, p);
        s = cdatan(0, i);
        cutname(s, 36);
        cs_list(cs == cnt, s, wx + 84, wy + 66 + cnt * 19 - 1);
        s = u8"Lv."s + cdata[i].level + u8" "s;
        if (cdata[i].sex == 0)
        {
            s += cnven(i18n::_(u8"ui", u8"male"));
        }
        else
        {
            s += cnven(i18n::_(u8"ui", u8"female"));
        }
        s += i18n::s.get("core.locale.ui.npc_list.age_counter", calcage(i));
        pos(wx + 372, wy + 66 + cnt * 19 + 2);
        mes(s);
        if (_operation != hire_operation::revive)
        {
            if (_operation == hire_operation::hire)
            {
                s = ""s + calchirecost(i) * 20 + u8"("s + calchirecost(i)
                    + u8")"s;
            }
            else
            {
                s = ""s + calchirecost(i);
            }
            pos(wx + 512, wy + 66 + cnt * 19 + 2);
            mes(i18n::s.get("core.locale.ui.npc_list.gold_counter", s(0)));
        }
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_hire::result_type> ui_menu_hire::on_key(const std::string& key)
{
    int _p;

    ELONA_GET_SELECTED_ITEM(_p, 0);

    if (_p != -1)
    {
        return ui_menu_hire::result::finish(_p);
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
        return ui_menu_hire::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
