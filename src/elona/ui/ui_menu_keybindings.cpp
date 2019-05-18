#include "ui_menu_keybindings.hpp"
#include "../audio.hpp"
#include "../data/types/type_asset.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../keybind/keybind.hpp"
#include "../keybind/keybind_manager.hpp"
#include "simple_prompt.hpp"

namespace elona
{
namespace ui
{

static const constexpr int _x_align_action_name = 56;
static const constexpr int _x_align_binding_primary = 222;
static const constexpr int _x_align_binding_alternate = 360;
static const constexpr int _x_align_binding_joystick = 498;


static std::string _action_category_to_name(ActionCategory category)
{
    switch (category)
    {
    case ActionCategory::default_:
        return i18n::s.get("core.locale.keybind.category.default");
    case ActionCategory::shortcut:
        return i18n::s.get("core.locale.keybind.category.shortcut");
    case ActionCategory::selection:
        return i18n::s.get("core.locale.keybind.category.selection");
    case ActionCategory::menu:
        return i18n::s.get("core.locale.keybind.category.menu");
    case ActionCategory::game:
        return i18n::s.get("core.locale.keybind.category.game");
    case ActionCategory::wizard:
        return i18n::s.get("core.locale.keybind.category.wizard");
    }

    return "<unknown category>";
}

static std::string _get_localized_action_name(
    const std::string& mod_id,
    const std::string& action_id,
    ActionCategory action_category)
{
    std::string localized_name;

    // core.locale.keybind.chat_box
    switch (action_category)
    {
    case ActionCategory::shortcut:
    {
        auto action_index_plus_1 = keybind_index_number(action_id) + 1;
        if (action_index_plus_1 == 10 || action_index_plus_1 == 20)
        {
            action_index_plus_1 -= 10;
        }
        localized_name = i18n::s.get(mod_id + ".locale.keybind.shortcut") +
            std::to_string(action_index_plus_1);
        break;
    }
    case ActionCategory::selection:
    {
        const auto action_index_plus_1 = keybind_index_number(action_id) + 1;
        localized_name = i18n::s.get(mod_id + ".locale.keybind.select") +
            std::to_string(action_index_plus_1);
        break;
    }
    default:
        localized_name = i18n::s.get(mod_id + ".locale.keybind."s + action_id);
        break;
    }

    return localized_name;
}

static void _push_category_name(ActionCategory action_category)
{
    list(0, listmax) = -1;
    listn(0, listmax) = "";
    listn(1, listmax) = _action_category_to_name(action_category);
    listmax++;
}

static void _push_keybind_entry(
    const std::string& action_id,
    const std::string& localized_name,
    const KeybindManager::Binding& binding)
{
    list(0, listmax) = 999;
    listn(0, listmax) = action_id;
    listn(1, listmax) = localized_name;
    listn(2, listmax) = binding.primary.to_string();
    listn(3, listmax) = binding.alternate.to_string();
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

            const auto mod_id = "core"s;
            std::string localized_name =
                _get_localized_action_name(mod_id, action_id, action_category);

            _push_keybind_entry(action_id, localized_name, keybind_config);
        }
    }
}

void UIMenuKeybindings::_draw_background()
{
    int bg_variant_buffer = mode == 10 ? 2 : 4;
    load_background_variants(bg_variant_buffer);
    gsel(0);

    if (mode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
    if (mode == 10)
    {
        gmode(0);
        asset_load("title");
        elona::draw("title", 0, 0, windoww, windowh);
        gsel(0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);
    }
}

bool UIMenuKeybindings::init()
{
    listmax = 0;
    page = 0;
    pagesize = 15;
    cs = 0;

    _draw_background();

    const auto& info = asset_load("ie_sheet");
    gsel(0);

    wx = (windoww - info.width) / 2 + inf_screenx;
    wy = winposy(info.height) - 10;
    ww = info.width;
    wh = info.height;

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

void UIMenuKeybindings::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.locale.config.menu.keybindings.name"),
        i18n::s.get("core.locale.keybind.menu.hint") + strhint2 + strhint3b,
        wx,
        wy,
        ww,
        wh);
}

void UIMenuKeybindings::_draw_topics()
{
    display_topic(
        i18n::s.get("core.locale.keybind.menu.topics.name"),
        wx + _x_align_action_name - 28,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.keybind.menu.topics.primary"),
        wx + _x_align_binding_primary - 10,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.keybind.menu.topics.alternate"),
        wx + _x_align_binding_alternate - 10,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.keybind.menu.topics.joystick"),
        wx + _x_align_binding_joystick - 10,
        wy + 36);
}

void UIMenuKeybindings::_draw_keys()
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

void UIMenuKeybindings::_draw_keybind_entry(int cnt, const std::string& text)
{
    cs_list(cs == cnt, text, wx + _x_align_action_name, wy + 66 + cnt * 19 - 1);

    mes(wx + _x_align_binding_primary,
        wy + 66 + cnt * 19 + 2,
        listn(2, pagesize * page + cnt));

    mes(wx + _x_align_binding_alternate,
        wy + 66 + cnt * 19 + 2,
        listn(3, pagesize * page + cnt));
}

void UIMenuKeybindings::_draw_text_entry(int cnt, const std::string& text)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    cs_list(cs == cnt, text, wx + 88, wy + 66 + cnt * 19);
    font(14 - en * 2);
}

void UIMenuKeybindings::_draw_single_list_entry(
    int cnt,
    int list_item,
    const std::string& text)
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

void UIMenuKeybindings::_draw_list_entries()
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
    KeyConflictPrompt(
        Keybind keybind,
        std::vector<std::string> action_ids_in_conflict)
        : SimplePrompt()
        , _keybind(keybind)
        , _action_ids_in_conflict(action_ids_in_conflict)
    {
        std::stringstream ss;

        // TODO: localize
        _print_conflicts(ss);
        _message = ss.str();
    }

protected:
    optional<bool> update() override
    {
        await(Config::instance().general_wait);

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
                    _clear_conflicting_binding(action_id);
                }

                // Refresh the bound key names by regenerating the keybind list.
                _load_keybindings();

                return true;
            }
        }

        return none;
    }

private:
    void _clear_conflicting_binding(const std::string& action_id)
    {
        auto& binding = KeybindManager::instance().binding(action_id);

        if (binding.primary == _keybind)
        {
            binding.primary.clear();
        }
        if (binding.alternate == _keybind)
        {
            binding.alternate.clear();
        }
        if (binding.joystick == _keybind.main)
        {
            binding.joystick = snail::Key::none;
        }
    }

    void _print_conflicts(std::ostream& out)
    {
        out << i18n::s.get("core.locale.keybind.menu.conflict.text") << "\n";
        for (const auto& action_id : _action_ids_in_conflict)
        {
            _print_conflict(out, action_id);
        }
        out << i18n::s.get("core.locale.keybind.menu.conflict.prompt");
    }

    void _print_conflict(std::ostream& out, const std::string& action_id)
    {
        const auto category = keybind::actions.at(action_id).category;
        const auto mod_id = "core";
        out << "  " << _action_category_to_name(category) << ": "
            << _get_localized_action_name(mod_id, action_id, category) << "\n";
    }


    Keybind _keybind;
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
        : SimplePrompt()
    {
        _message = i18n::s.get("core.locale.keybind.menu.prompt");
    }

protected:
    optional<KeyPromptResult> update() override
    {
        await(Config::instance().general_wait);

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
    const Keybind& keybind,
    const std::vector<std::string>& action_ids_in_conflict)
{
    return KeyConflictPrompt(keybind, action_ids_in_conflict).query();
}

static void _bind_key(const std::string& action_id, Keybind keybind)
{
    auto conflicts =
        KeybindManager::instance().find_conflicts(action_id, keybind);
    if (conflicts.size() > 0)
    {
        if (!_handle_conflicts(keybind, conflicts))
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
    assert(action_id != "");
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
    keybind_regenerate_key_names();

    // Prevent Shift from firing the cancel action.
    keywait = 1;
    keyhalt = 1;
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
        cs = _index;
        const auto& action_id = listn(0, *selected);

        _prompt_for_key(action_id);

        set_reupdate();
        return none;
    }
    else if (action == "next_page"s)
    {
        ++page;
        snd("core.pop1");
        set_reupdate();
    }
    else if (action == "previous_page"s)
    {
        --page;
        snd("core.pop1");
        set_reupdate();
    }
    else if (action == "cancel"s)
    {
        KeybindManager::instance().save();

        // Return to the previous menu.
        UIMenuConfigResult result = {true, 0};
        return UIMenuKeybindings::Result::finish(result);
    }

    return none;
}

} // namespace ui
} // namespace elona
