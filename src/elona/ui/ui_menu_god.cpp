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
            return i18n::s.get("core.god.desc.window.abandon");
        }
        else
        {
            return i18n::s.get(
                "core.god.desc.window.convert", god_name(god_id));
        }
    }
    else
    {
        return i18n::s.get("core.god.desc.window.believe", god_name(god_id));
    }
}

bool UIMenuGod::init()
{
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    listmax = 0;
    chatesc = _cancel_choice;

    list(0, listmax) = 0;
    listn(0, listmax) = _get_choice_name(_already_believing, _god_id);
    ++listmax;

    list(0, listmax) = _cancel_choice;
    listn(0, listmax) = i18n::s.get("core.god.desc.window.cancel");
    ++listmax;

    snd("core.pop4");
    gmode(0);
    asset_load("bg_altar");
    elona::draw("bg_altar", 0, 0, windoww, windowh - inf_verh);
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

    if (god_id != 0)
    {
        buff = i18n::s.get_enum_property("core.god.desc", "text", god_id);

        buff += i18n::s.get("core.god.desc.offering") + u8": ";
        buff += i18n::s.get_enum_property("core.god.desc", "offering", god_id);

        buff += i18n::s.get("core.god.desc.bonus") + u8": ";
        buff += i18n::s.get_enum_property("core.god.desc", "bonus", god_id);

        buff += i18n::s.get("core.god.desc.ability") + u8": ";
        buff += i18n::s.get_enum_property("core.god.desc", "ability", god_id);
    }

    return buff;
}

void UIMenuGod::_draw_window()
{
    gmode(0);
    elona::draw_region("bg_altar", 0, 0, 0, 0, windoww, windowh - inf_verh);
    gmode(2);
    render_hud();
    const auto& info = get_image_info("bg_altar");
    dx = info.width - 80;
    dy = info.height - 130;
    wx = (windoww - dx) / 2 + inf_screenx;
    wy = winposy(dy);
    window2(wx, wy, dx, dy, 4, 6);
}

void UIMenuGod::_draw_title(int god_id)
{
    font(18 - en * 2, snail::Font::Style::bold);
    bmes(
        i18n::s.get("core.god.desc.window.title", god_name(god_id)),
        wx + 20,
        wy + 20);
}

void UIMenuGod::_draw_desc(int god_id)
{
    std::string _buff = _get_god_description(god_id);
    gmes(_buff, wx + 23, wy + 60, dx - 60, {30, 30, 30}, true);
}

void UIMenuGod::_draw_choice(int cnt, const std::string& text)
{
    display_key(wx + 50, wy + dy + cnt * 20 - listmax * 20 - 18, cnt);
    cs_list(cs == cnt, text, wx + 80, wy + dy + cnt * 20 - listmax * 20 - 18);
}

void UIMenuGod::_draw_choices()
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

optional<UIMenuGod::ResultType> UIMenuGod::on_key(const std::string& action)
{
    int _rtval = -1;

    if (auto selected = get_selected_item())
    {
        snd("core.click1");
        _rtval = *selected;
    }

    if (action == "cancel")
    {
        snd("core.click1");
        _rtval = _cancel_choice;
    }
    if (_rtval != -1)
    {
        if (_rtval == _cancel_choice)
        {
            return UIMenuGod::ResultType::cancel();
        }
        else
        {
            return UIMenuGod::ResultType::finish(_rtval);
        }
    }

    return none;
}

} // namespace ui
} // namespace elona
