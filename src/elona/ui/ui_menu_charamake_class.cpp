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
    for (const auto& class_ : class_get_available(false))
    {
        listn(1, listmax) = class_.get().id;
        ++listmax;
    }
    if (Config::instance().extra_class)
    {
        for (const auto& class_ : class_get_available(true))
        {
            listn(1, listmax) = class_.get().id;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = class_get_name(listn(1, cnt));
    }
}

bool UIMenuCharamakeClass::init()
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

void UIMenuCharamakeClass::update()
{
}

static void _draw_class_info(
    const std::string& class_id,
    int chip_male,
    int chip_female,
    const std::string& race)
{
    {
        auto rect = chara_preparepic(chip_male);
        gcopy(
            rect->buffer,
            0,
            960,
            inf_tiles,
            rect->height,
            wx + 380,
            wy - rect->height + 60);
    }
    {
        auto rect = chara_preparepic(chip_female);
        gcopy(
            rect->buffer,
            0,
            960,
            inf_tiles,
            rect->height,
            wx + 350,
            wy - rect->height + 60);
    }
    mes(wx + 460,
        wy + 38,
        i18n::s.get("core.locale.chara_making.select_race.race_info.race") +
            u8": "s + race);

    draw_race_or_class_info(
        i18n::s.get_m_optional("locale.class", class_id, "description")
            .get_value_or(""));
}

void UIMenuCharamakeClass::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.locale.chara_making.select_class.title"),
        strhint3b,
        (windoww - 680) / 2 + inf_screenx,
        winposy(500, 1) + 20,
        680,
        500);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    gmode(2, 50);
    gcopy_c(
        2,
        cmbg / 4 % 4 * 180,
        cmbg / 4 / 4 % 2 * 300,
        180,
        300,
        wx + ww / 4,
        wy + wh / 2,
        x,
        y);
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

void UIMenuCharamakeClass::_draw_choice(int cnt, const std::string& text)
{
    display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    cs_list(cs == cnt, text, wx + 64, wy + 66 + cnt * 19 - 1);
}

void UIMenuCharamakeClass::_draw_choices()
{
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        _draw_choice(cnt, cnven(listn(0, cnt)));
    }
    cs_bk = cs;
}

static void _reload_selected_class(const std::string& klass)
{
    chara_delete(0);
    class_init_chara(cdata.player(), klass);
}

void UIMenuCharamakeClass::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    _draw_window();
    _draw_choices();

    const std::string& selected_class = listn(1, cs);
    _reload_selected_class(selected_class);

    _draw_class_info(selected_class, ref1, ref2, _race);
}

optional<UIMenuCharamakeClass::ResultType> UIMenuCharamakeClass::on_key(
    const std::string& action)
{
    if (auto class_id = get_selected_index())
    {
        std::string klass = listn(1, *class_id);
        return UIMenuCharamakeClass::Result::finish(klass);
    }
    if (action == "cancel")
    {
        return UIMenuCharamakeClass::Result::cancel();
    }
    if (getkey(snail::Key::f1))
    {
        show_game_help();
        return UIMenuCharamakeClass::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
