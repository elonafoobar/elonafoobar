#include "ui_menu_alias.hpp"

#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../text.hpp"

namespace elona
{
namespace ui
{

bool UIMenuAlias::init()
{
    cs = 0;
    windowshadow = 1;

    _set_reroll_aliases();

    return true;
}

void UIMenuAlias::_set_reroll_aliases()
{
    list(0, 0) = -1;
    cs_bk = -1;
    set_reupdate();
}

void UIMenuAlias::update()
{
    for (int cnt = 0; cnt < 17; ++cnt)
    {
        int title_id = _seed + cnt;

        if (_alias_type == 3)
        {
            randomize(title_id);
        }
        if (list(0, 0) == -1)
        {
            listn(0, cnt) =
                random_title(static_cast<RandomTitleType>(_alias_type));
            list(1, cnt) = title_id;
        }
        if (cnt == 0)
        {
            listn(0, cnt) = i18n::s.get("core.ui.alias.reroll");
        }
    }
    _seed += 17;
    cs_bk = cs;
    list(0, 0) = 0;
}

void UIMenuAlias::draw()
{
    ui_display_window(
        i18n::s.get("core.ui.alias.title"),
        strhint3b,
        (windoww - 400) / 2 + inf_screenx,
        winposy(458),
        400,
        458);
    display_topic(i18n::s.get("core.ui.alias.list"), wx + 28, wy + 30);

    font(14 - en * 2);

    for (int cnt = 0; cnt < 17; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
    }
}

optional<UIMenuAlias::ResultType> UIMenuAlias::on_key(const std::string& action)
{
    if (auto selected = get_selected_index_this_page())
    {
        if (*selected == 0)
        {
            snd("core.dice");
            _set_reroll_aliases();
        }
        else
        {
            UIMenuAliasResult res;

            if (_alias_type == 3)
            {
                res.seed = *selected;
            }
            else
            {
                res.alias = listn(0, *selected);
            }

            return UIMenuAlias::Result::finish(res);
        }
    }
    else if (action == "cancel")
    {
        snd("core.pop2");
        return UIMenuAlias::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
