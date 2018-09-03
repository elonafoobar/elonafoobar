#include "ui_menu_charamake_race.hpp"
#include "../audio.hpp"
#include "../character_making.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"
#include "../race.hpp"

namespace elona
{
namespace ui
{

static void _load_race_list()
{
    listmax = 0;
    for (const auto& race : the_race_db.get_available_races(false))
    {
        listn(1, listmax) = race.get().id;
        list(0, listmax) = 0;
        ++listmax;
    }
    if (Config::instance().extrarace)
    {
        for (const auto& race : the_race_db.get_available_races(true))
        {
            listn(1, listmax) = race.get().id;
            list(0, listmax) = 1;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = i18n::_(u8"race", listn(1, cnt), u8"name");
        if (list(0, cnt) == 1)
        {
            listn(0, cnt) = u8"(extra)"s + listn(0, cnt);
        }
    }
}

bool UIMenuCharamakeRace::init()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 16;
    page = 0;

    character_making_draw_background(
        "core.locale.chara_making.select_race.caption");

    windowshadow = 1;

    _load_race_list();

    return true;
}

void UIMenuCharamakeRace::update()
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

static void _draw_race_info(int chip_male, int chip_female)
{
    {
        // male
        draw_chara(chip_male, wx + 480, wy + 96, 2, 40);
    }
    {
        // female
        draw_chara(chip_female, wx + 350, wy + 96, 2, 40);
    }

    gmode(2);
    draw_race_or_class_info();
}

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.chara_making.select_race.title");
    s(1) = strhint3b;
    display_window(
        (windoww - 680) / 2 + inf_screenx, winposy(500, 1) + 20, 680, 500);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    pos(wx + ww / 4, wy + wh / 2);
    gmode(4, 50);
    gcopy_c(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.race"),
        wx + 28,
        wy + 30);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.detail"),
        wx + 188,
        wy + 30);
}

static void _draw_choice(int cnt, const std::string& text)
{
    display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    cs_list(cs == cnt, text, wx + 64, wy + 66 + cnt * 19 - 1);
}

static void _draw_choices()
{
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = page * pagesize + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        const std::string& text = listn(0, index);
        _draw_choice(cnt, text);
    }
    cs_bk = cs;
}

static void _reload_selected_race(const std::string& race)
{
    chara_delete(0);
    access_race_info(3, race);
    access_race_info(11, race);
}

void UIMenuCharamakeRace::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    _draw_window();
    _draw_choices();

    const std::string& selected_race = listn(1, page * pagesize + cs);
    _reload_selected_race(selected_race);

    pos(wx + 200, wy + 66);
    _draw_race_info(ref1, ref2);
}

optional<UIMenuCharamakeRace::result_type> UIMenuCharamakeRace::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_INDEX(p);

    if (p != -1)
    {
        int race_index = p;
        const std::string& race_id = listn(1, race_index);
        const std::string& race_name = listn(0, race_index);

        return UIMenuCharamakeRace::result::finish(
            ui_menu_charamake_race_result{race_id, race_name});
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
        return UIMenuCharamakeRace::result::cancel();
    }
    else if (getkey(snail::Key::f1))
    {
        show_game_help();
        return UIMenuCharamakeRace::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
