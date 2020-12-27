#include "ui_menu_charamake_class.hpp"

#include "../audio.hpp"
#include "../character_making.hpp"
#include "../class.hpp"
#include "../data/types/type_race.hpp"
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
        listn(1, listmax) = class_.get().id.get();
        ++listmax;
    }
    if (g_config.extra_class())
    {
        for (const auto& class_ : class_get_available(true))
        {
            listn(1, listmax) = class_.get().id.get();
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = class_get_name(data::InstanceId{listn(1, cnt)});
    }
}

bool UIMenuCharamakeClass::init()
{
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 0;

    character_making_draw_background("core.chara_making.select_class.caption");

    windowshadow = 1;

    _load_class_list();

    return true;
}

void UIMenuCharamakeClass::update()
{
}

static void _draw_class_info(
    data::InstanceId class_id,
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
        i18n::s.get("core.chara_making.select_race.race_info.race") + ": "s +
            race);

    draw_race_or_class_info(
        the_class_db.get_text_optional(class_id, "description").value_or(""));
}

void UIMenuCharamakeClass::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.chara_making.select_class.title"),
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
        i18n::s.get("core.chara_making.select_class.class"), wx + 28, wy + 30);
    display_topic(
        i18n::s.get("core.chara_making.select_class.detail"),
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

static void _reload_selected_class(data::InstanceId class_id)
{
    chara_delete(cdata.player());
    class_init_chara(cdata.player(), class_id);
}

void UIMenuCharamakeClass::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    _draw_window();
    _draw_choices();

    const auto selected_class = data::InstanceId{listn(1, cs)};
    _reload_selected_class(selected_class);

    const auto& race_data = the_race_db.ensure(_race_id);
    _draw_class_info(
        selected_class,
        race_data.male_image,
        race_data.female_image,
        the_race_db.get_text(_race_id, "name"));
}

optional<UIMenuCharamakeClass::ResultType> UIMenuCharamakeClass::on_key(
    const std::string& action)
{
    if (auto class_id = get_selected_index())
    {
        return UIMenuCharamakeClass::Result::finish(
            UIMenuCharamakeClassResult{data::InstanceId{listn(1, *class_id)}});
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
