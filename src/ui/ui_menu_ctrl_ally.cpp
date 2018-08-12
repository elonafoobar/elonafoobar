#include "ui_menu_ctrl_ally.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../character.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_ctrl_ally::_should_display_ally(const character& chara)
{
    if (chara.state() == character::state_t::empty)
    {
        return false;
    }
    if (_operation == ctrl_ally_operation::sell)
    {
        if (chara.state() == character::state_t::pet_dead)
        {
            return false;
        }
    }
    if (_operation == ctrl_ally_operation::staying
        || _operation == ctrl_ally_operation::gene_engineer)
    {
        if (chara.state() != character::state_t::alive)
        {
            return false;
        }
    }
    if (_operation == ctrl_ally_operation::gene_engineer)
    {
        if (chara.index == rc)
        {
            return false;
        }
    }
    if (chara.current_map != 0)
    {
        if (_operation == ctrl_ally_operation::sell
            || _operation == ctrl_ally_operation::pet_arena)
        {
            return false;
        }
    }
    if (_operation != ctrl_ally_operation::sell)
    {
        if (chara.is_escorted() || chara.is_escorted_in_sub_quest())
        {
            return false;
        }
    }
    if (chara.is_ridden())
    {
        return false;
    }
    if (chara.index == 0)
    {
        return false;
    }

    return true;
}

void ui_menu_ctrl_ally::_insert_proceed_entry()
{
    list(0, listmax) = 99;
    list(1, listmax) = -9999;
    ++listmax;
}

static void _init_pet_arena_selection()
{
    int _p = 0;
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
            ++_p;
            if (_p == arenaop(1))
            {
                break;
            }
        }
    }
}

bool ui_menu_ctrl_ally::init()
{
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    if (_operation == ctrl_ally_operation::pet_arena)
    {
        _insert_proceed_entry();
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (_should_display_ally(cdata[cnt]))
        {
            list(0, listmax) = cnt;
            list(1, listmax) = -cdata[cnt].level;
            ++listmax;
        }
    }
    sort_list_by_column1();
    if (_operation == ctrl_ally_operation::pet_arena)
    {
        _init_pet_arena_selection();
    }
    windowshadow = 1;

    return true;
}

static void _update_call_back()
{
    txt(i18n::s.get("core.locale.ui.ally_list.call.prompt"));
    s(10) = i18n::s.get("core.locale.ui.ally_list.call.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.locale.ui.ally_list.name");
    s(13) = i18n::s.get("core.locale.ui.ally_list.status");
    x = 0;
}

static void _update_sell()
{
    txt(i18n::s.get("core.locale.ui.ally_list.sell.prompt"));
    s(10) = i18n::s.get("core.locale.ui.ally_list.sell.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.locale.ui.ally_list.name");
    s(13) = i18n::s.get("core.locale.ui.ally_list.sell.value");
    x = 20;
}

static void _update_pet_arena()
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

static void _update_staying()
{
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        txt(i18n::s.get("core.locale.ui.ally_list.shop.prompt"));
        s(10) = i18n::s.get("core.locale.ui.ally_list.shop.title");
        s(11) = strhint2 + strhint3;
        s(12) = i18n::s.get("core.locale.ui.ally_list.name");
        s(13) = i18n::s.get("core.locale.ui.ally_list.shop.chr_negotiation");
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

static void _update_investigate_and_gene_engineer(bool is_gene_engineer)
{
    txt(i18n::s.get("core.locale.ui.ally_list.gene_engineer.prompt"));
    s(10) = i18n::s.get("core.locale.ui.ally_list.gene_engineer.title");
    s(11) = strhint2 + strhint3;
    s(12) = i18n::s.get("core.locale.ui.ally_list.name");
    s(13) = i18n::s.get("core.locale.ui.ally_list.status");
    if (is_gene_engineer)
    {
        if (rc != 0)
        {
            s(13) = i18n::s.get(
                "core.locale.ui.ally_list.gene_engineer.body_skill");
        }
    }
    x = 0;
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

    switch (_operation)
    {
    case ctrl_ally_operation::call_back: _update_call_back(); break;
    case ctrl_ally_operation::sell: _update_sell(); break;
    case ctrl_ally_operation::pet_arena: _update_pet_arena(); break;
    case ctrl_ally_operation::staying: _update_staying(); break;
    case ctrl_ally_operation::investigate:
    case ctrl_ally_operation::gene_engineer:
        _update_investigate_and_gene_engineer(
            _operation == ctrl_ally_operation::gene_engineer);
        break;
    }
}

static void _draw_info_pet_arena(const character& chara, std::string& _s)
{
    if (followerin(chara.index) == 1)
    {
        _s += i18n::s.get("core.locale.ui.ally_list.pet_arena.in");
    }
}

int ui_menu_ctrl_ally::_draw_get_color_mode(const character& chara)
{
    int n = 0;

    if (_operation == ctrl_ally_operation::gene_engineer)
    {
        if (chara.level > sdata(151, 0) + 5)
        {
            n = 3;
        }
    }

    return n;
}

std::string ui_menu_ctrl_ally::_get_ally_name(const character& chara)
{
    std::string ally_name =
        ""s + cdatan(1, chara.index) + u8" "s + cdatan(0, chara.index);

    if (chara.current_map != 0)
    {
        ally_name = ally_name + u8"("s + mapname(chara.current_map) + u8")"s;
    }
    if (_operation == ctrl_ally_operation::pet_arena)
    {
        _draw_info_pet_arena(chara, ally_name);
    }

    return ally_name;
}

std::string ui_menu_ctrl_ally::_get_general_ally_info(const character& chara)
{
    std::string ally_info = u8"Lv."s + chara.level + u8" "s;

    if (chara.state() == character::state_t::pet_dead)
    {
        ally_info += i18n::s.get("core.locale.ui.ally_list.dead");
    }
    if (chara.state() == character::state_t::pet_waiting)
    {
        if (_operation == ctrl_ally_operation::call_back)
        {
            ally_info += i18n::s.get("core.locale.ui.ally_list.call.waiting");
        }
        else
        {
            ally_info += u8"(Hp: "s + chara.hp * 100 / chara.max_hp + u8"%) "s
                + i18n::s.get("core.locale.ui.ally_list.waiting");
        }
    }
    if (chara.state() == character::state_t::alive)
    {
        if (_operation == ctrl_ally_operation::call_back)
        {
            ally_info += i18n::s.get("core.locale.ui.ally_list.alive");
        }
        else
        {
            ally_info += u8"(Hp: "s + chara.hp * 100 / chara.max_hp + u8"%)"s;
        }
    }

    return ally_info;
}

std::string ui_menu_ctrl_ally::_get_specific_ally_info(const character& chara)
{
    std::string _s = "";

    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        _s = u8"   "s + sdata(17, chara.index) + u8" / "
            + sdata(156, chara.index);
    }
    else if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
    {
        _s = u8"   "s + cbreeder(chara.index);
    }

    return _s;
}

static bool _has_general_info(ctrl_ally_operation operation)
{
    return operation != ctrl_ally_operation::staying
        || (operation == ctrl_ally_operation::staying
            && gdata_current_map == mdata_t::map_id_t::your_home);
}

std::string ui_menu_ctrl_ally::_get_ally_info(const character& chara)
{
    std::string _s = "";

    if (_has_general_info(_operation))
    {
        _s = _get_general_ally_info(chara);
    }
    else
    {
        _s = _get_specific_ally_info(chara);
    }

    return _s;
}

std::string ui_menu_ctrl_ally::_modify_ally_info_gene_engineer(
    const character& chara,
    const std::string& ally_info_)
{
    std::string ally_info = ally_info_;

    if (rc != 0)
    {
        tc = chara.index;
        {
            int stat = transplant_body_parts();
            if (stat == -1)
            {
                ally_info =
                    i18n::s.get("core.locale.ui.ally_list.gene_engineer.none");
            }
            else
            {
                ally_info = i18n::_(u8"ui", u8"body_part", u8"_"s + rtval);
            }
        }
        ally_info += u8"/"s;
        {
            int stat = gain_skills_by_geen_engineering();
            if (stat == 0)
            {
                ally_info +=
                    i18n::s.get("core.locale.ui.ally_list.gene_engineer.none");
            }
            else
            {
                ally_info +=
                    ""s + i18n::_(u8"ability", std::to_string(rtval), u8"name");
                if (rtval(1) != -1)
                {
                    ally_info +=
                        u8", "s
                        + i18n::_(
                              u8"ability", std::to_string(rtval(1)), u8"name");
                }
            }
        }
    }

    return ally_info;
}

void ui_menu_ctrl_ally::_draw_ally_list_entry_sell(
    int cnt,
    const character& chara)
{
    std::string ally_name =
        ""s + cdatan(1, chara.index) + u8" "s + cdatan(0, chara.index);
    ally_name += u8" Lv."s + chara.level;

    cs_list(cs == cnt, ally_name, wx + 84, wy + 66 + cnt * 19 - 1);

    std::string ally_info =
        ""s + calcslavevalue(chara.index) * 2 / 3 + i18n::_(u8"ui", u8"gold");

    pos(wx + 390, wy + 66 + cnt * 19 + 2);
    mes(ally_info);
}

void ui_menu_ctrl_ally::_draw_ally_name(int cnt, const character& chara)
{
    std::string ally_name = _get_ally_name(chara);
    int color_mode = _draw_get_color_mode(chara);

    cs_list(
        cs == cnt, ally_name, wx + 84, wy + 66 + cnt * 19 - 1, 0, color_mode);
}

void ui_menu_ctrl_ally::_draw_ally_info(int cnt, const character& chara)
{
    std::string ally_info = _get_ally_info(chara);

    if (_operation == ctrl_ally_operation::gene_engineer)
    {
        ally_info = _modify_ally_info_gene_engineer(chara, ally_info);
    }

    pos(wx + 370, wy + 66 + cnt * 19 + 2);
    mes(ally_info);
}

void ui_menu_ctrl_ally::_draw_ally_list_entry(int cnt, const character& chara)
{
    if (_operation != ctrl_ally_operation::sell)
    {
        _draw_ally_name(cnt, chara);
        _draw_ally_info(cnt, chara);
    }
    else if (_operation == ctrl_ally_operation::sell)
    {
        _draw_ally_list_entry_sell(cnt, chara);
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

        _draw_ally_list_entry(cnt, cdata[i]);
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
        if (_operation == ctrl_ally_operation::gene_engineer)
        {
            return _select_gene_engineer(p);
        }
        else if (_operation == ctrl_ally_operation::pet_arena)
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
