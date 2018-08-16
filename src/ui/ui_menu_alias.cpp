#include "ui_menu_alias.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../macro.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_alias::init()
{
    cs = 0;
    windowshadow = 1;

    _set_reroll_aliases();

    return true;
}

void ui_menu_alias::_set_reroll_aliases()
{
    list(0, 0) = -1;
    cs_bk = -1;
    set_reupdate();
}

void ui_menu_alias::update()
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
            listn(0, cnt) = random_title(_alias_type);
            list(1, cnt) = title_id;
        }
        if (cnt == 0)
        {
            listn(0, cnt) = i18n::s.get("core.locale.ui.alias.reroll");
        }
    }
    _seed += 17;
    cs_bk = cs;
    list(0, 0) = 0;
}

void ui_menu_alias::draw()
{
    s(0) = i18n::s.get("core.locale.ui.alias.title");
    s(1) = strhint3b;
    display_window((windoww - 400) / 2 + inf_screenx, winposy(458), 400, 458);
    display_topic(i18n::s.get("core.locale.ui.alias.list"), wx + 28, wy + 30);

    font(14 - en * 2);

    for (int cnt = 0; cnt < 17; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        pos(wx + 38, wy + 66 + cnt * 19 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
    }
}

optional<ui_menu_alias::result_type> ui_menu_alias::on_key(
    const std::string& key)
{
    int _p;

    ELONA_GET_SELECTED_INDEX_THIS_PAGE(_p);

    if (_p != -1)
    {
        if (key == key_select(0))
        {
            snd(103);
            _set_reroll_aliases();
        }
        else
        {
            ui_menu_alias_result res;

            if (_alias_type == 3)
            {
                res.seed = _p;
            }
            else
            {
                res.alias = listn(0, _p);
            }

            return ui_menu_alias::result::finish(res);
        }
    }
    else if (key == key_cancel)
    {
        snd(26);
        return ui_menu_alias::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
