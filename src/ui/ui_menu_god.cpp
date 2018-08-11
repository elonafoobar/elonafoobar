#include "ui_menu_god.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

void ui_menu_god::init()
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
    chatesc = 2;
    if (_already_believing)
    {
        if (_god_id == 0)
        {
            s = i18n::s.get("core.locale.god.desc.window.abandon");
        }
        else
        {
            s = i18n::s.get(
                "core.locale.god.desc.window.convert",
                i18n::_(u8"god", core_god::int2godid(_god_id), u8"name"));
        }
        list(0, listmax) = 0;
        listn(0, listmax) = s;
        ++listmax;
    }
    else
    {
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get(
            "core.locale.god.desc.window.believe",
            i18n::_(u8"god", core_god::int2godid(_god_id), u8"name"));
        ++listmax;
    }
    list(0, listmax) = 2;
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
}

void ui_menu_god::update()
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


void ui_menu_god::draw()
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

    font(18 - en * 2, snail::font_t::style_t::bold);
    bmes(
        i18n::s.get(
            "core.locale.god.desc.window.title",
            i18n::_(u8"god", core_god::int2godid(_god_id), u8"name")),
        wx + 20,
        wy + 20);

    buff = _get_god_description(_god_id);
    gmes(buff, wx + 23, wy + 60, dx - 60, {30, 30, 30}, true);

    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        i = list(0, p);
        display_key(wx + 50, wy + dy + cnt * 20 - listmax * 20 - 18, cnt);
        s = listn(0, p);
        cs_list(cs == cnt, s, wx + 80, wy + dy + cnt * 20 - listmax * 20 - 18);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_god::result_type> ui_menu_god::on_key(const std::string& key)
{
    int _rtval = -1;

    ELONA_GET_SELECTED_ITEM(_rtval, snd(40));
    if (key == key_cancel)
    {
        snd(40);
        return ui_menu_god::result_type::cancel();
    }
    if (_rtval != -1)
    {
        return ui_menu_god::result_type::finish(_rtval);
    }

    return none;
}

} // namespace ui
} // namespace elona
