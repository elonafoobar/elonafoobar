#include "keybind.hpp"
#include "../enums.hpp"
#include "../gdata.hpp"
#include "../log.hpp"
#include "../variables.hpp"
#include "keybind_manager.hpp"

using namespace std::literals::string_literals;



namespace
{

/// Returns whether the key is one of the number keys on top of the keyboard or
/// one of the numpad keys.
bool is_number_key(snail::Key k)
{
    const auto k_ = static_cast<int>(k);
    constexpr auto key_0_ = static_cast<int>(snail::Key::key_0);
    constexpr auto key_9_ = static_cast<int>(snail::Key::key_9);
    constexpr auto numpad_0_ = static_cast<int>(snail::Key::keypad_0);
    constexpr auto numpad_9_ = static_cast<int>(snail::Key::keypad_9);

    return (key_0_ <= k_ && k_ <= key_9_) ||
        (numpad_0_ <= k_ && k_ <= numpad_9_);
}

} // namespace



namespace elona
{

void initialize_keybindings()
{
    auto& keybind_manager = KeybindManager::instance();
    initialize_keybind_actions(keybind::actions);
    keybind_manager.load();
}

std::string Keybind::to_string() const
{
    if (empty())
    {
        return "";
    }

    const auto it = keybind_key_name(main);
    if (!it)
    {
        return "<unbindable key "s + static_cast<int>(main) + ">";
    }
    std::string key_name = *it;

    /// The order should always be ctrl, shift, alt, gui.
    std::string mod_key_string = "";
    if ((modifiers & snail::ModKey::ctrl) == snail::ModKey::ctrl)
    {
        mod_key_string += "Ctrl+";
    }
    if ((modifiers & snail::ModKey::shift) == snail::ModKey::shift)
    {
        if (auto name = keybind_key_name(main, true))
        {
            key_name = *name;
        }
        else
        {
            mod_key_string += "Shift+";
        }
    }
    if ((modifiers & snail::ModKey::alt) == snail::ModKey::alt)
    {
        mod_key_string += "Alt+";
    }
    if ((modifiers & snail::ModKey::gui) == snail::ModKey::gui)
    {
        mod_key_string += "Gui+";
    }

    return mod_key_string + key_name;
}

optional<Keybind> Keybind::from_string(std::string str)
{
    snail::ModKey modifiers = snail::ModKey::none;

    if (strutil::try_remove_prefix(str, "Ctrl+"))
    {
        modifiers |= snail::ModKey::ctrl;
    }
    if (strutil::try_remove_prefix(str, "Shift+"))
    {
        modifiers |= snail::ModKey::shift;
    }
    if (strutil::try_remove_prefix(str, "Alt+"))
    {
        modifiers |= snail::ModKey::alt;
    }
    if (strutil::try_remove_prefix(str, "Gui+"))
    {
        modifiers |= snail::ModKey::gui;
    }

    // Handle shifted keys ("Shift+a" is serialized as "A")
    if (auto key = keybind_key_code(str, true))
    {
        return Keybind{*key, modifiers | snail::ModKey::shift};
    }
    // Non-shifted keys
    if (auto key = keybind_key_code(str, false))
    {
        return Keybind{*key, modifiers};
    }

    return none;
}


bool keybind_is_joystick_key(snail::Key key)
{
    // Currently joystick controller is not supported.
    (void)key;
    return false;
}

bool keybind_is_bindable_key(snail::Key key)
{
    return static_cast<bool>(keybind_key_name(key));
}

bool keybind_action_has_category(
    const std::string& action_id,
    ActionCategory category)
{
    if (action_id.empty())
    {
        return false;
    }
    if (keybind::actions.find(action_id) == keybind::actions.end())
    {
        ELONA_LOG("No such keybind action " << action_id);
        return false;
    }

    return keybind::actions.at(action_id).category == category;
}

void draw_init_key_select_buffer();

void keybind_regenerate_key_select()
{
    auto grouped_keybinds =
        KeybindManager::instance().create_category_to_action_list();
    auto range = grouped_keybinds.equal_range(ActionCategory::selection);

    SDIM3(key_select, 2, 20);
    int cnt = 0;
    for (auto it = range.first; it != range.second; it++)
    {
        const auto& action_id = it->second;
        const auto& binding = KeybindManager::instance().binding(action_id);

        auto keybind = binding.primary;
        if (keybind.main == snail::Key::none)
        {
            keybind = binding.alternate;
        }

        bool shift =
            (keybind.modifiers & snail::ModKey::shift) == snail::ModKey::shift;
        auto key = keybind.main;

        key_select(cnt) = keybind_key_short_name(key, shift);
        cnt++;
    }

    draw_init_key_select_buffer();
}

int keybind_index_number(const std::string& action_id)
{
    if (!(keybind_action_has_category(action_id, ActionCategory::selection) ||
          keybind_action_has_category(action_id, ActionCategory::shortcut)))
    {
        return 0;
    }

    auto underscore_pos = action_id.find("_");
    assert(underscore_pos != std::string::npos);

    auto index_string = action_id.substr(underscore_pos + 1);

    // Assumption is the ID will be at least 1.
    // elona::stoi returns 0 on failure.
    int result = elona::stoi(index_string);
    assert(result >= 1);

    // Adjust the result to be 0-indexed.
    return result - 1;
}

snail::Key keybind_selection_key_from_index(int index)
{
    std::string id = "select_" + std::to_string(index + 1);
    if (keybind::actions.find(id) == keybind::actions.end())
    {
        return snail::Key::none;
    }

    auto key = KeybindManager::instance().binding(id).primary.main;

    return key;
}



std::string get_bound_shortcut_key_name_by_action_id(
    const std::string& action_id)
{
    const auto& keybind = KeybindManager::instance().binding(action_id).primary;

    if (is_number_key(keybind.main) &&
        (keybind.modifiers & (snail::ModKey::ctrl | snail::ModKey::shift)) !=
            snail::ModKey::none)
    {
        return "1" + *keybind_key_name(keybind.main);
    }
    else
    {
        return keybind.to_string();
    }
}



std::string get_bound_shortcut_key_name_by_index(int index)
{
    return get_bound_shortcut_key_name_by_action_id(
        "shortcut_" + std::to_string(index + 1));
}

} // namespace elona
