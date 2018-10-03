#include "ui_menu_keybindings.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"

namespace elona
{
namespace ui
{

static std::string _action_category_to_name(ActionCategory category)
{
    switch (category)
    {
    case ActionCategory::default_: return "Default";
    case ActionCategory::shortcut: return "Shortcut";
    case ActionCategory::selection: return "Selection";
    case ActionCategory::menu: return "Menu";
    case ActionCategory::game: return "Game";
    case ActionCategory::wizard: return "Wizard";
    }

    return "<unknown>";
}

static void _load_keybindings()
{
    listmax = 0;

    auto& keybind_manager = KeybindManager::instance();
    const auto grouped_keybinds =
        keybind_manager.create_category_to_action_list();

    decltype(grouped_keybinds.equal_range(ActionCategory::default_)) range;

    for (auto it = grouped_keybinds.begin(); it != grouped_keybinds.end();
         it = range.second)
    {
        range = grouped_keybinds.equal_range(it->first);

        list(0, listmax) = -1;
        listn(0, listmax) =
            u8"◆ "s + _action_category_to_name(range.first->first);
        listmax++;

        for (auto pair = range.first; pair != range.second; ++pair)
        {
            const auto& action_id = pair->second;
            const auto& keybind_config = keybind_manager.binding(pair->second);

            // core.locale.keybind.chat_box
            const auto mod_name = "core"s;
            const auto localized_name =
                i18n::s.get(mod_name + ".locale.keybind."s + action_id);

            list(0, listmax) = 999; // i % 7 == 0 ? -1 : 999;
            listn(0, listmax) = localized_name;
            listn(1, listmax) = keybind_config.primary.to_string();
            listn(2, listmax) = keybind_config.alternate.to_string();
            listmax++;
        }
    }
}

bool UIMenuKeybindings::init()
{
    page = 0;
    pagesize = 15;
    cs = 0;

    wx = (windoww - 700) / 2 + inf_screenx;
    wy = winposy(400) - 10;
    ww = 700;
    wh = 400;

    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_sheet.bmp");
    gsel(0);

    _load_keybindings();

    windowshadow = 1;

    return true;
}

void UIMenuKeybindings::update()
{
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

static void _draw_window()
{
    s(0) = "Keybindings";
    s(1) = "dood";

    display_window(wx, wy, ww, wh);
}

static void _draw_topics()
{
    display_topic("Name", wx + 28, wy + 36);
    display_topic("Primary", wx + 182, wy + 36);
    display_topic("Alternate", wx + 320, wy + 36);
    display_topic("Joystick", wx + 458, wy + 36);
}

static void _draw_keys()
{
    keyrange = 0;
    int item_count = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;

        int list_item = list(0, index);

        if (list_item < 0)
        {
            item_count = 1;
            continue;
        }
        ++item_count;
        if (list_item < 100)
        {
            x = 52;
            dx = 18;
        }
        else
        {
            x = 70;
            dx = 0;
        }
        if (item_count % 2 == 0)
        {
            boxf(wx + x, wy + 66 + cnt * 19, 595 + dx, 18, {12, 14, 16, 16});
        }
        if (list_item < 100)
        {
            continue;
        }
        display_key(wx + 32, wy + 66 + cnt * 19 - 2, cnt);
    }
}

static void _draw_keybind_entry(int cnt, const std::string& text)
{
    cs_list(cs == cnt, text, wx + 56, wy + 66 + cnt * 19 - 1);

    pos(wx + 192, wy + 66 + cnt * 19 + 2);
    mes(listn(1, pagesize * page + cnt));

    pos(wx + 330, wy + 66 + cnt * 19 + 2);
    mes(listn(2, pagesize * page + cnt));
}

static void _draw_text_entry(int cnt, const std::string& text)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    cs_list(cs == cnt, text, wx + 88, wy + 66 + cnt * 19);
    font(14 - en * 2);
}

static void
_draw_single_list_entry(int cnt, int list_item, const std::string& text)
{
    if (list_item >= 0)
    {
        _draw_keybind_entry(cnt, text);
    }
    else
    {
        _draw_text_entry(cnt, text);
    }
}

static void _draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }

        int list_item = list(0, index);
        const std::string& text = listn(0, index);

        _draw_single_list_entry(cnt, list_item, text);
    }
    cs_bk = cs;
}

void UIMenuKeybindings::draw()
{
    _draw_window();
    _draw_topics();
    _draw_keys();
    _draw_list_entries();
}

static void
_bind_key(const std::string& action_id, snail::Key key, snail::ModKey modifiers)
{
    auto keybind = Keybind{key, modifiers};
    auto& binding = KeybindManager::instance().binding(action_id);

    // TODO
    if (KeybindManager::instance().find_conflicts(action_id, keybind).size()
        > 0)
    {
        return;
    }

    if (keybind_is_joystick_key(key))
    {
        // Joystick buttons will not use modifier keys.
        binding.joystick = key;
    }
    else if (binding.primary.empty())
    {
        binding.primary = keybind;
    }
    else if (binding.alternate.empty())
    {
        binding.alternate = keybind;
    }
    else
    {
        // Clear the secondary keybinding first.
        binding.alternate.clear();
        binding.primary = keybind;
    }

    listn(1, pagesize * page + cs) = binding.primary.to_string();
    listn(2, pagesize * page + cs) = binding.alternate.to_string();
}

static void _unbind_key(const std::string& action_id)
{
    KeybindManager::instance().clear_binding(action_id);

    const auto& binding = KeybindManager::instance().binding(action_id);
    listn(1, pagesize * page + cs) = binding.primary.to_string();
    listn(2, pagesize * page + cs) = binding.alternate.to_string();
}

static void _prompt_for_key()
{
    size_t width = 100;
    size_t height = 100;
    int font_size = 13 + sizefix - en * 2;
    bool finished = false;

    std::string line =
        "Please press a key.\nEnter to unbind, Escape to cancel.";
    width = strlen_u(line) * 8 + 40;
    height += font_size * 2;

    int x = promptx - (width / 2);
    int y = prompty - (height / 2);

    snd(26);

    const std::string& action_id = listn(0, pagesize * page + cs);
    snail::ModKey last_modifiers = snail::ModKey::none;

    snail::Input::instance().clear_pressed_keys();

    while (!finished)
    {
        gmode(6, 80);
        window(x + 12, y + 12, width, height, true); // Shadow
        gmode(2);

        window(x + 8, y + 8, width, height, false);

        font(font_size);
        pos(x + 40, y + font_size + 36);
        mes(line);

        redraw();

        await(Config::instance().wait1);

        const auto& keys = snail::Input::instance().pressed_keys();
        auto modifiers = snail::Input::instance().modifiers();

        last_modifiers = modifiers;

        for (const auto& key : keys)
        {
            if (key == snail::Key::escape)
            {
                finished = true;
            }
            if (key == snail::Key::enter)
            {
                _unbind_key(action_id);
                finished = true;
            }
            if (!is_modifier(key))
            {
                if (keybind_is_bindable_key(key))
                {
                    _bind_key(action_id, key, last_modifiers);
                    finished = true;
                }
            }
        }
    }
}

optional<UIMenuKeybindings::ResultType> UIMenuKeybindings::on_key(
    const std::string& key)
{
    UNUSED(key);

    auto command = input_context.check_for_command_with_list(p(0));

    if (p != -1 && list(0, p) >= 0)
    {
        cs = p;
        _prompt_for_key();
        input_context.reset();
        set_reupdate();
        return none;
    }
    else if (command == "next_page"s)
    {
        ++page;
        snd(1);
        set_reupdate();
    }
    else if (command == "previous_page"s)
    {
        --page;
        snd(1);
        set_reupdate();
    }
    if (command == "cancel"s)
    {
        return UIMenuKeybindings::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
