#include "ui_menu_skills.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

static void _populate_skill_list()
{
    for (int cnt = 300; cnt < 400; ++cnt)
    {
        if (sdata(cnt, cc) > 0)
        {
            list(0, listmax) = cnt;
            list(1, listmax) =
                the_ability_db[cnt]->related_basic_attribute * 1000 + cnt;
            ++listmax;
        }
    }
    for (int cnt = 0; cnt < 61; ++cnt)
    {
        if (spact(cnt) != 0)
        {
            list(0, listmax) = cnt + 600;
            list(1, listmax) =
                the_ability_db[cnt + 600]->related_basic_attribute * 1000 + cnt;
            ++listmax;
        }
    }
    sort_list_by_column1();
}

bool UIMenuSkills::init()
{
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    cs = commark(0) % 1000;
    page = commark(0) / 1000;
    curmenu = 1;
    snd(101);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_skill.bmp", 1);
    gsel(0);
    windowshadow = 1;

    _populate_skill_list();

    return true;
}

void UIMenuSkills::update()
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

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.ui.skill.title");
    s(1) = strhint2 + strhint3 + strhint7;
    display_window(
        (windoww - 600) / 2 + inf_screenx, winposy(438), 600, 438, 0, 60);
    display_topic(i18n::s.get("core.locale.ui.skill.name"), wx + 28, wy + 36);
    display_topic(i18n::s.get("core.locale.ui.skill.cost"), wx + 220, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.skill.detail"), wx + 320, wy + 36);

    pos(wx + 46, wy - 16);
    gcopy(3, 960, 48, 48, 48);
    pos(wx + ww - 78, wy + wh - 165);
    gcopy(3, 960, 96, 72, 144);
    pos(wx + ww - 168, wy);
    gcopy(3, 1032, 96, 102, 48);
}

static void _draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 490, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

static void _draw_keys()
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
        _draw_key(cnt);
    }
}

static void _draw_skill_attribute(int cnt, int skill_id)
{
    pos(wx + 40, wy + 74 + cnt * 19);
    gmode(2);
    gcopy_c(
        1,
        (the_ability_db[skill_id]->related_basic_attribute - 10) * inf_tiles,
        672,
        inf_tiles,
        inf_tiles);
}

static void _draw_skill_name(int cnt, int skill_id)
{
    std::string skill_shortcut = "";
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (game_data.skill_shortcuts.at(cnt) == skill_id)
        {
            skill_shortcut = u8"{"s + cnt + u8"}"s;
        }
    }
    cs_list(
        cs == cnt,
        i18n::_(u8"ability", std::to_string(skill_id), u8"name")
            + skill_shortcut,
        wx + 84,
        wy + 66 + cnt * 19 - 1);
}

static void _draw_spell_cost(int cnt, int skill_id)
{
    std::string spell_cost = ""s + the_ability_db[skill_id]->cost + u8" Sp"s;
    pos(wx + 288 - strlen_u(spell_cost) * 7, wy + 66 + cnt * 19 + 2);
    mes(spell_cost);
}

static void _draw_spell_power(int cnt, int skill_id)
{
    draw_spell_power_entry(skill_id);
    pos(wx + 325, wy + 66 + cnt * 19 + 2);
    mes(strmid(s, 0, 34));
}

static void _draw_single_list_entry(int cnt, int skill_id)
{
    _draw_skill_attribute(cnt, skill_id);
    _draw_skill_name(cnt, skill_id);
    _draw_spell_cost(cnt, skill_id);
    _draw_spell_power(cnt, skill_id);
}

static void _draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        int skill_id = list(0, p);
        _draw_single_list_entry(cnt, skill_id);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuSkills::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

static void _assign_shortcut(int sc_, int skill_id)
{
    snd(20);
    if (game_data.skill_shortcuts.at(sc_) == skill_id)
    {
        game_data.skill_shortcuts.at(sc_) = 0;
        return;
    }
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (game_data.skill_shortcuts.at(cnt) == skill_id)
        {
            game_data.skill_shortcuts.at(cnt) = 0;
        }
    }
    game_data.skill_shortcuts.at(sc_) = skill_id;
    txt(i18n::s.get("core.locale.ui.assign_shortcut", sc_));
    display_msg(inf_screeny + inf_tiles);
}

optional<UIMenuSkills::ResultType> UIMenuSkills::on_key(
    const std::string& action)
{
    commark(0) = page * 1000 + cs;
    // ELONA_GET_SELECTED_ITEM(p, 0);

    if (auto selected = get_selected_item())
    {
        menucycle = 0;
        screenupdate = -1;
        update_screen();
        return UIMenuSkills::Result::finish(
            UIMenuCompositeSkillsResult(UIMenuSkillsResult{*selected}));
    }
    else if (auto sc = get_shortcut(action))
    {
        int selected_skill = list(0, pagesize * page + cs);
        _assign_shortcut(*sc, selected_skill);
        set_reupdate();
        return none;
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        update_screen();
        return UIMenuSkills::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
