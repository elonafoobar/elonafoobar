#include "ui_menu_god.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

const constexpr int _cancel_choice = 2;

static std::string _get_choice_name(bool already_believing, int god_id)
{
    if (already_believing)
    {
        if (god_id == 0)
        {
            return i18n::s.get("core.locale.god.desc.window.abandon");
        }
        else
        {
            return i18n::s.get(
                "core.locale.god.desc.window.convert",
                i18n::_(u8"god", core_god::int2godid(god_id), u8"name"));
        }
    }
    else
    {
        return i18n::s.get(
            "core.locale.god.desc.window.believe",
            i18n::_(u8"god", core_god::int2godid(god_id), u8"name"));
    }
}

bool UIMenuGod::init()
{
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    key = "";
    objprm(0, ""s);
    keylog = "";
    listmax = 0;
    chatesc = _cancel_choice;

    list(0, listmax) = 0;
    listn(0, listmax) = _get_choice_name(_already_believing, _god_id);
    ++listmax;

    list(0, listmax) = _cancel_choice;
    listn(0, listmax) = i18n::s.get("core.locale.god.desc.window.cancel");
    ++listmax;

    snd(62);
    gsel(4);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"bg_altar.bmp", 1);
    pos(0, 0);
    gcopy(4, 0, 0, 600, 400, windoww, windowh - inf_verh);
    gsel(0);

    return true;
}

void UIMenuGod::update()
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
    }
}

static std::string _get_god_description(int god_id)
{
    std::string buff = u8" "s;

    if (god_id > 0 && god_id <= 7)
    {
        buff =
            i18n::s.get_enum_property("core.locale.god.desc", "text", god_id);

        buff += i18n::s.get("core.locale.god.desc.offering") + u8": ";
        buff += i18n::s.get_enum_property(
            "core.locale.god.desc", "offering", god_id);

        buff += i18n::s.get("core.locale.god.desc.bonus") + u8": ";
        buff +=
            i18n::s.get_enum_property("core.locale.god.desc", "bonus", god_id);

        buff += i18n::s.get("core.locale.god.desc.ability") + u8": ";
        buff += i18n::s.get_enum_property(
            "core.locale.god.desc", "ability", god_id);
    }

    return buff;
}

static void _draw_window()
{
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh - inf_verh);
    gmode(2);
    render_hud();
    dx = 520;
    dy = 270;
    window2((windoww - dx) / 2 + inf_screenx, winposy(dy), dx, dy, 4, 6);
    wx = (windoww - dx) / 2 + inf_screenx;
    wy = winposy(dy);
}

static void _draw_title(int god_id)
{
    font(18 - en * 2, snail::font_t::Style::bold);
    bmes(
        i18n::s.get(
            "core.locale.god.desc.window.title",
            i18n::_(u8"god", core_god::int2godid(god_id), u8"name")),
        wx + 20,
        wy + 20);
}

static void _draw_desc(int god_id)
{
    std::string _buff = _get_god_description(god_id);
    gmes(_buff, wx + 23, wy + 60, dx - 60, {30, 30, 30}, true);
}

static void _draw_choice(int cnt, const std::string& text)
{
    display_key(wx + 50, wy + dy + cnt * 20 - listmax * 20 - 18, cnt);
    cs_list(cs == cnt, text, wx + 80, wy + dy + cnt * 20 - listmax * 20 - 18);
}

static void _draw_choices()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        _draw_choice(cnt, listn(0, cnt));
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuGod::draw()
{
    _draw_window();
    _draw_title(_god_id);
    _draw_desc(_god_id);
    _draw_choices();
}

optional<UIMenuGod::result_type> UIMenuGod::on_key(const std::string& key)
{
    int _rtval = -1;

    ELONA_GET_SELECTED_ITEM(_rtval, snd(40));
    if (key == key_cancel)
    {
        snd(40);
        _rtval = _cancel_choice;
    }
    if (_rtval != -1)
    {
        if (_rtval == _cancel_choice)
        {
            return UIMenuGod::result_type::cancel();
        }
        else
        {
            return UIMenuGod::result_type::finish(_rtval);
        }
    }

    return none;
}

} // namespace ui
} // namespace elona
