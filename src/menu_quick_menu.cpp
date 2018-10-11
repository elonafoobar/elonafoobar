#include "audio.hpp"
#include "defines.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "ui.hpp"

namespace elona
{

class QuickMenu
{
private:
    struct Entry
    {
        Entry(int index, const I18NKey& locale_key, std::string action_id)
            : index(index)
            , action_id(action_id)
        {
            text = i18n::s.get(locale_key);
        }

        int index;
        int x;
        int y;
        std::string text;
        std::string action_id;
    };

public:
    QuickMenu(int x, int y, int page)
        : _pos_x(x)
        , _pos_y(y)
        , _page(page)
    {
    }

    std::string query();

private:
    void _draw();
    void _update();
    optional<std::string> _on_action(std::string& action);

    void _create_entries_list();
    void _add_pagination_to_entries();
    void _set_entry_positions();

    int _pos_x;
    int _pos_y;
    int _page;
    bool _reupdate;

    std::vector<Entry> _entries;
};

std::string show_quick_menu()
{
    int tx, ty;

    listmax = 0;

    if (defines::is_android)
    {
        tx = (windoww / 2) - 100;
        ty = (windowh / 2) - 100;
    }
    else
    {
        tx = 50;
        ty = windowh - 255;
    }

    return QuickMenu(tx, ty, quickpage).query();
}

std::string QuickMenu::query()
{
    _reupdate = true;

    while (true)
    {
        if (_reupdate)
        {
            _update();
            _reupdate = false;
        }

        _draw();
        auto action = key_check(KeyWaitDelay::none);
        if (auto result = _on_action(action))
        {
            return *result;
        }
    }
}

void QuickMenu::_create_entries_list()
{
    _entries.clear();
    _entries.reserve(9);

    if (_page == 3)
    {
        _page = 2;
    }
    if (_page == -1)
    {
        _page = 0;
    }
    // clang-format off
    if (_page == 0)
    {
        _entries.emplace_back(0, "", "aaa");
        _entries.emplace_back(1, "core.locale.ui.quick_menu.help",     "help");
        _entries.emplace_back(2, "core.locale.ui.quick_menu.log",      "message_log");
        _entries.emplace_back(3, "core.locale.ui.quick_menu.chara",    "chara_info");
        _entries.emplace_back(4, "", "aaa");
        _entries.emplace_back(5, "core.locale.ui.quick_menu.journal",  "journal");
        _entries.emplace_back(6, "", "aaa");
        _entries.emplace_back(7, "", "aaa");
        _entries.emplace_back(8, "", "aaa");
    }
    if (_page == 1)
    {
        _entries.emplace_back(0, "", "aaa");
        _entries.emplace_back(1, "core.locale.ui.quick_menu.wear",     "wear");
        _entries.emplace_back(2, "core.locale.ui.quick_menu.rest",     "rest");
        _entries.emplace_back(3, "core.locale.ui.quick_menu.spell",    "cast");
        _entries.emplace_back(4, "", "aaa");
        _entries.emplace_back(5, "core.locale.ui.quick_menu.skill",    "skill");
        _entries.emplace_back(6, "core.locale.ui.quick_menu.fire",     "fire");
        _entries.emplace_back(7, "core.locale.ui.quick_menu.dig",      "dig");
        _entries.emplace_back(8, "", "aaa");
    }
    if (_page == 2)
    {
        _entries.emplace_back(0, "", "aaa");
        _entries.emplace_back(1, "core.locale.ui.quick_menu.pray",     "pray");
        _entries.emplace_back(2, "core.locale.ui.quick_menu.ammo",     "ammo");
        _entries.emplace_back(3, "core.locale.ui.quick_menu.interact", "interact");
        _entries.emplace_back(4, "", "aaa");
        _entries.emplace_back(5, "core.locale.ui.quick_menu.bash",     "bash");
        _entries.emplace_back(6, "", "aaa");
        _entries.emplace_back(7, "", "aaa");
        _entries.emplace_back(8, "", "aaa");
    }
    // clang-format on
}

void QuickMenu::_add_pagination_to_entries()
{
    s(0) = i18n::s.get("core.locale.ui.quick_menu.info");
    s(1) = i18n::s.get("core.locale.ui.quick_menu.action");
    s(2) = i18n::s.get("core.locale.ui.quick_menu.etc");
    s(3) = "null";

    // Leftmost entry for switching menus.
    p = _page - 1;
    if (p == -1)
    {
        p = 3;
    }
    _entries.at(0).text = s(p);

    // Menu name displayed in the center.
    _entries.at(4).text = s(_page);

    // Rightmost entry for switching menus.
    p = _page + 1;
    if (p == 3)
    {
        p = 2;
    }
    _entries.at(8).text = s(p);
}

void QuickMenu::_set_entry_positions()
{
    _entries.at(0).x = 25;
    _entries.at(1).x = 50;
    _entries.at(2).x = 50;
    _entries.at(3).x = 100;
    _entries.at(4).x = 100;
    _entries.at(5).x = 100;
    _entries.at(6).x = 150;
    _entries.at(7).x = 150;
    _entries.at(8).x = 175;
    _entries.at(0).y = 50;
    _entries.at(1).y = 15;
    _entries.at(2).y = 85;
    _entries.at(3).y = 0;
    _entries.at(4).y = 50;
    _entries.at(5).y = 100;
    _entries.at(6).y = 15;
    _entries.at(7).y = 85;
    _entries.at(8).y = 50;
}

void QuickMenu::_update()
{

    _create_entries_list();
    _add_pagination_to_entries();
    _set_entry_positions();

    t = 0;
}

void QuickMenu::_draw()
{
    font(12 + sizefix - en * 2);
    s = u8"○コマンド"s;
    gmode(2);
    for (const auto& entry : _entries)
    {
        int cnt = entry.index;
        if (entry.text == "null")
        {
            continue;
        }

        if (cnt == 0 || cnt == 4 || cnt == 8)
        {
            draw("quickmenu_submenu", entry.x + _pos_x, entry.y + _pos_y);
        }
        else
        {
            draw("quickmenu_action", entry.x + _pos_x, entry.y + _pos_y);
        }
        gmode(4, (t + cnt) % 10 * (t + cnt) % 10 * 12 * ((t + cnt) % 50 < 10));

        if (cs == cnt)
        {
            gmode(5, 140);
        }
        if (cnt == 0 || cnt == 4 || cnt == 8)
        {
            draw("quickmenu_submenu", entry.x + _pos_x, entry.y + _pos_y);
        }
        else
        {
            draw("quickmenu_action", entry.x + _pos_x, entry.y + _pos_y);
        }

        gmode(2);
        bmes(
            entry.text,
            entry.x + _pos_x + 25 - strlen_u(entry.text) * 3,
            entry.y + _pos_y + 19);
    }
    ++t;
    redraw();
}

optional<std::string> QuickMenu::_on_action(std::string& action)
{
    bool try_update = false;

    if (action == "north")
    {
        action = _entries.at(3).action_id;
        cs = 3;
    }
    if (action == "south")
    {
        action = _entries.at(5).action_id;
        cs = 5;
    }
    if (action == "west")
    {
        cs = 0;
    }
    if (action == "east")
    {
        cs = 8;
    }
    if (action == "northwest")
    {
        action = _entries.at(1).action_id;
        cs = 1;
    }
    if (action == "northeast")
    {
        action = _entries.at(6).action_id;
        cs = 6;
    }
    if (action == "southwest")
    {
        action = _entries.at(2).action_id;
        cs = 2;
    }
    if (action == "southeast")
    {
        action = _entries.at(7).action_id;
        cs = 7;
    }

    if (action == "cancel")
    {
        cs = -1;
        snd("core.cursor1");
        action = "";
        try_update = true;
    }
    else if (action != "")
    {
        if (cs == -1)
        {
            snd("core.cursor1");
            action = "";
            try_update = true;
        }
        if (action == "enter")
        {
            action = _entries.at(cs).action_id;
            try_update = true;
        }
    }
    else if (action == "" || cs == 1 || cs == 6 || cs == 2 || cs == 7)
    {
        if (cs != -1)
        {
            action = _entries.at(cs).action_id;
            try_update = true;
        }
    }

    if (try_update)
    {
        if (cs == 0 || action == "northwest")
        {
            cs = -1;
            snd("core.cursor1");
            --_page;
            screenupdate = -1;
            update_screen();

            _reupdate = true;
            return none;
        }
        if (cs == 8 || action == "northwest")
        {
            cs = -1;
            snd("core.cursor1");
            ++_page;
            screenupdate = -1;
            update_screen();

            _reupdate = true;
            return none;
        }
    }

    quickpage = _page;
    cs = 0;
    update_screen();
    quickkeywait = 1;

    return action;
}

} // namespace elona
