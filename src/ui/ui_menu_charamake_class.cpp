#include "ui_menu_charamake_class.hpp"
#include "../audio.hpp"
#include "../character_making.hpp"
#include "../class.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

static void _load_class_list()
{

    listmax = 0;
    for (const auto& class_ : the_class_db.get_available_classes(false))
    {
        listn(1, listmax) = class_.get().id;
        ++listmax;
    }
    if (config::instance().extraclass)
    {
        for (const auto& class_ : the_class_db.get_available_classes(true))
        {
            listn(1, listmax) = class_.get().id;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        access_class_info(2, listn(1, cnt));
        listn(0, cnt) = classname;
    }
}

bool ui_menu_charamake_class::init()
{
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 0;

    character_making_draw_background(
        "core.locale.chara_making.select_class.caption");

    windowshadow = 1;

    _load_class_list();

    return true;
}

void ui_menu_charamake_class::update()
{
}

static void
_draw_class_info(int chip_male, int chip_female, const std::string& race)
{
    {
        auto rect = chara_preparepic(chip_male);
        pos(wx + 380, wy - rect->height + 60);
        gcopy(rect->buffer, 0, 960, inf_tiles, rect->height);
    }
    {
        auto rect = chara_preparepic(chip_female);
        pos(wx + 350, wy - rect->height + 60);
        gcopy(rect->buffer, 0, 960, inf_tiles, rect->height);
    }
    pos(wx + 460, wy + 38);
    mes(i18n::s.get("core.locale.chara_making.select_race.race_info.race")
        + u8": "s + race);

    draw_race_or_class_info();
}

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.chara_making.select_class.title");
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
        i18n::s.get("core.locale.chara_making.select_class.class"),
        wx + 28,
        wy + 30);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_class.detail"),
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
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        std::string text;
        if (jp)
        {
            text = listn(0, cnt);
        }
        else
        {
            text = cnven(listn(1, cnt));
        }

        _draw_choice(cnt, text);
    }
    cs_bk = cs;
}

static void _reload_selected_class(const std::string& klass)
{
    chara_delete(0);
    access_class_info(3, klass);
    access_class_info(11, klass);
}

void ui_menu_charamake_class::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    _draw_window();
    _draw_choices();

    const std::string& selected_class = listn(1, cs);
    _reload_selected_class(selected_class);

    pos(wx + 200, wy + 66);
    _draw_class_info(ref1, ref2, _race);
}

optional<ui_menu_charamake_class::result_type> ui_menu_charamake_class::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_INDEX(p);

    if (p != -1)
    {
        int class_id = p;
        std::string klass = listn(1, class_id);
        return ui_menu_charamake_class::result::finish(klass);
    }
    if (key == key_cancel)
    {
        return ui_menu_charamake_class::result::cancel();
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_class::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
