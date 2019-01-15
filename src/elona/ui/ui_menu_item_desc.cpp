#include "ui_menu_item_desc.hpp"
#include "../../snail/color.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../item.hpp"

namespace elona
{
namespace ui
{

bool UIMenuItemDesc::init()
{
    snd("core.pop2");
    page_save();
    page = 0;
    pagesize = 15;
    listmax = 0;
    p = 0;
    s = "";

    item_dump_desc(_the_item);

    windowshadow = 1;

    return true;
}

void UIMenuItemDesc::update()
{
    key_list = key_enter;
    keyrange = 0;
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

static snail::Color _desc_to_color(int desc)
{
    switch (static_cast<ItemDescriptionType>(desc))
    {
    case ItemDescriptionType::raises_skill: return {0, 100, 0};
    case ItemDescriptionType::raises_stat: return {0, 0, 100};
    case ItemDescriptionType::raises_resist: return {80, 100, 0};
    case ItemDescriptionType::enchantment: return {80, 50, 0};
    case ItemDescriptionType::maintains_skill: return {0, 100, 100};
    case ItemDescriptionType::negative_effect: return {180, 0, 0};
    default: return {0, 0, 0};
    }
}

static snail::Color _get_color(int list_item)
{
    int desc = list_item % 10000;
    return _desc_to_color(desc);
}

static void _set_font(int list_item)
{
    if (list_item == static_cast<int>(ItemDescriptionType::small_font))
    {
        font(13 - en * 2);
    }
    else if (
        list_item == static_cast<int>(ItemDescriptionType::small_font_italic))
    {
        font(13 - en * 2, snail::Font::Style::italic);
    }
    else
    {
        font(14 - en * 2);
    }
}

static std::pair<int, int>
_get_pos(int cnt, int list_item, const std::string& list_text)
{
    if (list_item == static_cast<int>(ItemDescriptionType::small_font_italic))
    {
        return {wx + ww - strlen_u(list_text) * 6 - 80, wy + 68 + cnt * 18};
    }
    else
    {
        return {wx + 68, wy + 68 + cnt * 18};
    }
}

void UIMenuItemDesc::_draw_normal_mark(int cnt, int list_item)
{
    int desc = list_item % 10000;
    int mark_pos_x = desc * 24;
    pos(wx + 40, wy + 61 + cnt * 18);
    gcopy(3, 72 + mark_pos_x, 336, 24, 24);
}

void UIMenuItemDesc::_draw_marks(int cnt, int list_item)
{
    if (list_item > static_cast<int>(ItemDescriptionType::normal))
    {
        _draw_normal_mark(cnt, list_item);
    }
    if (list_item > 10000)
    {
        elona::draw("inheritance_mark", wx + 15, wy + 63 + cnt * 18);
    }
}

void UIMenuItemDesc::_draw_message(
    int cnt,
    int list_item,
    const std::string& list_text)
{
    _set_font(list_item);
    int x, y;
    std::tie(x, y) = _get_pos(cnt, list_item, list_text);
    mes(x, y, list_text, _get_color(list_item));

    _draw_marks(cnt, list_item);
}

void UIMenuItemDesc::draw()
{
    ui_display_window(
        i18n::s.get("core.locale.item.desc.window.title"),
        strhint4 + strhint3,
        (windoww - 600) / 2 + inf_screenx,
        winposy(408),
        600,
        408);
    display_topic(itemname(ci), wx + 28, wy + 34);

    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }

        _draw_message(cnt, list(0, p), listn(0, p));
    }
}

optional<UIMenuItemDesc::ResultType> UIMenuItemDesc::on_key(
    const std::string& action)
{
    if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel" || action == "enter")
    {
        return UIMenuItemDesc::ResultType::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
