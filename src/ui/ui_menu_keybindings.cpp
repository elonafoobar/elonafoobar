#include "ui_menu_keybindings.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"
#include "simple_prompt.hpp"

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

static std::string _get_localized_action_name(
    const std::string& mod_name,
    const std::string& action_id,
    ActionCategory action_category)
{
    std::string localized_name;
    int action_index{};

    // core.locale.keybind.chat_box
    switch (action_category)
    {
    case ActionCategory::shortcut:
        action_index = keybind_index_number(action_id);
        localized_name = i18n::s.get(mod_name + ".locale.keybind.shortcut")
            + std::to_string(action_index);
        break;
    case ActionCategory::selection:
        action_index = keybind_index_number(action_id);
        localized_name = i18n::s.get(mod_name + ".locale.keybind.select")
            + std::to_string(action_index);
        break;
    default:
        localized_name =
            i18n::s.get(mod_name + ".locale.keybind."s + action_id);
        break;
    }

    return localized_name;
}

static void _push_category_name(ActionCategory action_category)
{
    list(0, listmax) = -1;
    listn(0, listmax) = "";
    listn(1, listmax) = u8"◆ "s + _action_category_to_name(action_category);
    listmax++;
}

static void _push_keybind_entry(
    const std::string& action_id,
    const std::string& localized_name,
    const KeybindConfig& keybind_config)
{
    list(0, listmax) = 999;
    listn(0, listmax) = action_id;
    listn(1, listmax) = localized_name;
    listn(2, listmax) = keybind_config.primary.to_string();
    listn(3, listmax) = keybind_config.alternate.to_string();
    listmax++;
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

        auto action_category = range.first->first;
        _push_category_name(action_category);

        for (auto pair = range.first; pair != range.second; ++pair)
        {
            const auto& action_id = pair->second;
            const auto& keybind_config = keybind_manager.binding(pair->second);

            const auto mod_name = "core"s;
            std::string localized_name = _get_localized_action_name(
                mod_name, action_id, action_category);

            _push_keybind_entry(action_id, localized_name, keybind_config);
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
    s(0) = i18n::s.get("core.locale.item.desc.window.title");
    s(1) =
        i18n::s.get("core.locale.keybind.window.hint") + strhint2 + strhint3b;

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
    mes(listn(2, pagesize * page + cnt));

    pos(wx + 330, wy + 66 + cnt * 19 + 2);
    mes(listn(3, pagesize * page + cnt));
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
        const std::string& text = listn(1, index);

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

class KeyConflictPrompt : public SimplePrompt<bool>
{
public:
    KeyConflictPrompt(std::vector<std::string> action_ids_in_conflict)
        : SimplePrompt()
        , _action_ids_in_conflict(action_ids_in_conflict)
    {
        std::stringstream ss;

        // TODO: localize
        ss << "The following keybindings are in conflict:\n";
        for (const auto& action_id : _action_ids_in_conflict)
        {
            const auto category = keybind::actions.at(action_id).category;
            const auto mod_name = "core";
            ss << "  "
               << _get_localized_action_name(mod_name, action_id, category)
               << "\n";
        }
        ss << "Press Enter to unbind them, Escape to cancel.";
        _message = ss.str();
    }

protected:
    optional<bool> update() override
    {
        await(Config::instance().wait1);

        const auto& keys = snail::Input::instance().pressed_keys();

        for (const auto& key : keys)
        {
            if (key == snail::Key::escape)
            {
                return false;
            }
            if (key == snail::Key::enter)
            {
                for (const auto& action_id : _action_ids_in_conflict)
                {
                    KeybindManager::instance().binding(action_id).clear();
                }
                return true;
            }
        }

        return none;
    }

private:
    std::vector<std::string> _action_ids_in_conflict;
};

struct KeyPromptResult
{
    enum class Type
    {
        bind,
        unbind,
        cancel
    };

    KeyPromptResult(Type type)
        : type(type)
    {
    }

    KeyPromptResult(Type type, Keybind keybind)
        : type(type)
        , keybind(keybind)
    {
    }

    Type type;
    Keybind keybind{};
};

class KeyPrompt : public SimplePrompt<KeyPromptResult>
{
public:
    KeyPrompt()
        : SimplePrompt(
              "Please press a key.\nEnter to unbind, Escape to cancel.")
    {
    }

protected:
    optional<KeyPromptResult> update() override
    {
        await(Config::instance().wait1);

        const auto& keys = snail::Input::instance().pressed_keys();
        auto modifiers = snail::Input::instance().modifiers();

        _last_modifiers = modifiers;

        for (const auto& key : keys)
        {
            if (key == snail::Key::escape)
            {
                return KeyPromptResult{KeyPromptResult::Type::cancel};
            }
            if (key == snail::Key::enter)
            {
                return KeyPromptResult{KeyPromptResult::Type::unbind};
            }
            if (!is_modifier(key))
            {
                if (keybind_is_bindable_key(key))
                {
                    return KeyPromptResult{KeyPromptResult::Type::bind,
                                           Keybind{key, _last_modifiers}};
                }
            }
        }

        return none;
    }

private:
    snail::ModKey _last_modifiers = snail::ModKey::none;
};

/// Returns true if conflict was resolved, such that action can be bound
/// without any conflicts.
static bool _handle_conflicts(
    const std::vector<std::string>& action_ids_in_conflict)
{
    return KeyConflictPrompt(action_ids_in_conflict).query();
}

static void _bind_key(const std::string& action_id, Keybind keybind)
{
    auto conflicts =
        KeybindManager::instance().find_conflicts(action_id, keybind);
    if (conflicts.size() > 0)
    {
        if (!_handle_conflicts(conflicts))
        {
            return;
        }
    }

    auto& binding = KeybindManager::instance().binding(action_id);
    binding.bind(keybind);

    listn(2, pagesize * page + cs) = binding.primary.to_string();
    listn(3, pagesize * page + cs) = binding.alternate.to_string();
}

static void _unbind_key(const std::string& action_id)
{
    auto& binding = KeybindManager::instance().binding(action_id);
    binding.clear();

    listn(2, pagesize * page + cs) = binding.primary.to_string();
    listn(3, pagesize * page + cs) = binding.alternate.to_string();
}

static void _prompt_for_key(const std::string& action_id)
{
    auto result = KeyPrompt().query();
    switch (result.type)
    {
    case KeyPromptResult::Type::bind:
        _bind_key(action_id, result.keybind);
        break;
    case KeyPromptResult::Type::unbind: _unbind_key(action_id); break;
    default: break;
    }

    keybind_regenerate_key_select();
}

optional<UIMenuKeybindings::ResultType> UIMenuKeybindings::on_key(
    const std::string& action)
{
    // int p_ = -1;

    // if (_index != -1)
    // {
    //     p_ = list(0, pagesize * page + _index);
    // }

    auto selected = get_selected_index();
    if (selected && list(0, *selected) >= 0)
    {
        cs = *selected;
        const auto& action_id = listn(0, pagesize * page + cs);

        _prompt_for_key(action_id);

        set_reupdate();
        return none;
    }
    else if (action == "next_page"s)
    {
        ++page;
        snd(1);
        set_reupdate();
    }
    else if (action == "previous_page"s)
    {
        --page;
        snd(1);
        set_reupdate();
    }
    else if (action == "cancel"s)
    {
        return UIMenuKeybindings::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
