#include "keybind.hpp"
#include "../audio.hpp"
#include "../config/config.hpp"
#include "../enums.hpp"
#include "../gdata.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;

namespace elona
{
// clang-format off
static std::map<InputContextType, std::unordered_set<ActionCategory>> input_context_types =
{
    {InputContextType::menu, {ActionCategory::default_,
                              ActionCategory::selection,
                              ActionCategory::menu,
                              ActionCategory::shortcut}},

    {InputContextType::game, {ActionCategory::default_,
                              ActionCategory::shortcut,
                              ActionCategory::game,
                              ActionCategory::wizard}}
};
// clang-format on


KeybindManager& KeybindManager::instance()
{
    static KeybindManager the_instance;
    return the_instance;
}

KeybindManager::GroupedMapType KeybindManager::create_category_to_action_list()
{
    GroupedMapType result;

    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;
        result.emplace(action.category, action_id);
    }

    return result;
}

void KeybindManager::register_default_bindings(const ActionMap& actions)
{
    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        register_binding(action_id);

        auto& the_binding = binding(action_id);
        for (const auto& keybind : action.default_keybinds)
        {
            if (keybind_is_bindable_key(keybind.main))
            {
                if (the_binding.primary.empty())
                {
                    the_binding.primary = keybind;
                }
                else if (the_binding.alternate.empty())
                {
                    the_binding.alternate = keybind;
                }
                else
                {
                    assert(false);
                }
            }
            else
            {
                // Permanently bind keys that shouldn't be unbound (escape,
                // enter, and directional keys)
                the_binding.permanent = keybind;
            }
        }
    }
}

void KeybindManager::clear_binding(const std::string& action_id)
{
    auto& the_binding = binding(action_id);

    the_binding.primary.clear();
    the_binding.alternate.clear();
    the_binding.joystick = snail::Key::none;
}

std::vector<std::string> KeybindManager::find_conflicts(
    const std::string& action_id,
    const Keybind& keybind)
{
    auto action_category = keybind::actions.at(action_id).category;
    std::unordered_set<ActionCategory> can_conflict_with;
    std::vector<std::string> conflicts;

    // Iterate through possible combinations of action categories to see which
    // one the action is a part of.
    for (const auto& pair : input_context_types)
    {
        const auto& categories = pair.second;
        bool is_in_context =
            categories.find(action_category) != categories.end();

        // If the action can be returned from input in this category, the
        // keybinding for it cannot confict with other actions in other
        // categories for the same input context type.
        if (is_in_context)
        {
            can_conflict_with.insert(categories.begin(), categories.end());
        }
    }

    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;
        bool action_could_conflict =
            can_conflict_with.find(action.category) != can_conflict_with.end();

        if (action_could_conflict)
        {
            const auto& action_binding = binding(action_id);
            if (action_binding.primary == keybind
                || action_binding.alternate == keybind
                /* || (keybind.is_joystick() && keybind.joystick == keybind.main) */)
            {
                conflicts.emplace_back(action_id);
            }
        }
    }

    return conflicts;
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

static bool _has_prefix(const std::string& str, const std::string& prefix)
{
    if (prefix.size() > str.size())
    {
        return false;
    }

    return std::mismatch(prefix.begin(), prefix.end(), str.begin()).first
        == prefix.end();
}

static bool _try_unshift_prefix(std::string& str, const std::string& prefix)
{
    if (!_has_prefix(str, prefix))
    {
        return false;
    }

    str.erase(0, prefix.size());
    return true;
}

optional<Keybind> Keybind::from_string(std::string str)
{
    snail::ModKey modifiers = snail::ModKey::none;

    if (_try_unshift_prefix(str, "Ctrl+"))
    {
        modifiers |= snail::ModKey::ctrl;
    }
    if (_try_unshift_prefix(str, "Shift+"))
    {
        modifiers |= snail::ModKey::shift;
    }
    if (_try_unshift_prefix(str, "Alt+"))
    {
        modifiers |= snail::ModKey::alt;
    }
    if (_try_unshift_prefix(str, "Gui+"))
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

bool InputContext::_matches(
    const std::string& action_id,
    snail::Key key,
    snail::ModKey modifiers)
{
    if (_available_actions.find(action_id) == _available_actions.end())
    {
        return false;
    }

    const auto& binding = KeybindManager::instance().binding(action_id);

    if (binding.primary.main == key && binding.primary.modifiers == modifiers)
    {
        return true;
    }
    if (binding.alternate.main == key
        && binding.alternate.modifiers == modifiers)
    {
        return true;
    }
    if (binding.joystick == key)
    {
        return true;
    }

    return false;
}

optional<std::string> InputContext::_action_for_key(const Keybind& keybind)
{
    // The set is sorted by insertion order, so entries from categories inserted
    // earlier will receive priority.
    for (const auto& action_id : _available_actions)
    {
        const auto& binding = KeybindManager::instance().binding(action_id);
        bool excluded =
            _excluded_categories.find(keybind::actions.at(action_id).category)
            != _excluded_categories.end();

        if (!excluded && binding.matches(keybind))
        {
            return action_id;
        }
    }

    return none;
}

optional<std::string> InputContext::_check_movement_action(
    const std::set<snail::Key>& keys,
    snail::ModKey modifiers)
{
    StickKey input = StickKey::none;
    bool wait = false;

    for (const auto& key : keys)
    {
        // TODO: is keywait still needed after input_context.reset()?
        if (_matches("escape", key, modifiers) && keywait == 0)
        {
            return "cancel"s;
        }

        if (_matches("north", key, modifiers))
        {
            input |= StickKey::up;
        }
        else if (_matches("south", key, modifiers))
        {
            input |= StickKey::down;
        }
        else if (_matches("east", key, modifiers))
        {
            input |= StickKey::left;
        }
        else if (_matches("west", key, modifiers))
        {
            input |= StickKey::right;
        }
        else if (_matches("northwest", key, modifiers))
        {
            input = StickKey::up | StickKey::left;
        }
        else if (_matches("northeast", key, modifiers))
        {
            input = StickKey::up | StickKey::right;
        }
        else if (_matches("southwest", key, modifiers))
        {
            input = StickKey::down | StickKey::left;
        }
        else if (_matches("southeast", key, modifiers))
        {
            input = StickKey::down | StickKey::right;
        }
        else if (_matches("wait", key, modifiers))
        {
            input = StickKey::none;
            wait = true;
        }
        else if (!is_modifier(key))
        {
            // Encountered non-movement key, prioritize it over movement.
            return none;
        }
    }

    if ((modifiers & snail::ModKey::shift) == snail::ModKey::shift)
    {
        // Has to be modified globally, since scroll speed is determined by
        // keybd_wait. See @ref ui_scroll_screen()
        keybd_wait = 100000;
        if (keywait == 0)
        {
            keywait = 1;
            return "cancel"s;
        }
    }
    else
    {
        keywait = 0;
    }


    if ((modifiers & snail::ModKey::alt) != snail::ModKey::alt)
    {
        if (input == StickKey::left)
        {
            return "west"s;
        }
        if (input == StickKey::up)
        {
            return "north"s;
        }
        if (input == StickKey::right)
        {
            return "east"s;
        }
        if (input == StickKey::down)
        {
            return "south"s;
        }
    }
    if (input == (StickKey::up | StickKey::left))
    {
        return "northwest"s;
    }
    if (input == (StickKey::up | StickKey::right))
    {
        return "northeast"s;
    }
    if (input == (StickKey::down | StickKey::left))
    {
        return "southwest"s;
    }
    if (input == (StickKey::down | StickKey::right))
    {
        return "southeast"s;
    }
    if (wait)
    {
        return "wait"s;
    }

    return none;
}

bool InputContext::_is_nonmovement_key(const snail::Key& k)
{
    return keybind_is_bindable_key(k) || k == snail::Key::enter;
}

optional<Keybind> InputContext::_check_normal_action()
{
    const auto& keys = snail::Input::instance().pressed_keys();
    auto modifiers = snail::Input::instance().modifiers();

    // Pick the first nonmovement key out of the ones that were held.
    // The only actions for which holding multiple keys makes sense is for the
    // movement keys.
    const auto it =
        std::find_if(keys.begin(), keys.end(), [this](const snail::Key& k) {
            return _is_nonmovement_key(k);
        });

    if (it != keys.end())
    {
        return Keybind(*it, modifiers);
    }

    return none;
}

InputContext InputContext::create(InputContextType type)
{
    InputContext result;

    const auto& categories = input_context_types.at(type);
    for (const auto& category : categories)
    {
        result._add_actions_from_category(category);
    }

    return result;
}

void InputContext::_add_actions_from_category(ActionCategory category)
{
    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        if (action.category == category)
        {
            _available_actions.insert(action_id);
        }
    }
}

std::string InputContext::_delay_movement_action(
    const std::string& action,
    snail::ModKey modifiers,
    KeyWaitDelay delay_type)
{
    if (keybd_wait >= 100000)
    {
        if ((modifiers & snail::ModKey::shift) != snail::ModKey::shift)
        {
            keybd_wait = 1000;
        }
    }

    if (delay_type == KeyWaitDelay::none)
    {
        return action;
    }

    if (delay_type == KeyWaitDelay::walk_run)
    {
        if (keybd_attacking != 0)
        {
            if (keybd_wait % Config::instance().attackwait != 0)
            {
                return ""s;
            }
        }
        else if (Config::instance().scroll == 0)
        {
            if (keybd_wait
                < Config::instance().walkwait * Config::instance().startrun)
            {
                if (keybd_wait % Config::instance().walkwait != 0)
                {
                    return ""s;
                }
            }
            else
            {
                running = 1;
                if (keybd_wait < 100000)
                {
                    if (keybd_wait % Config::instance().runwait != 0)
                    {
                        return ""s;
                    }
                }
            }
        }
        // else if (input == StickKey::none)
        else if (action == "wait"s)
        {
            if (keybd_wait < 20)
            {
                if (keybd_wait != 0)
                {
                    return ""s;
                }
            }
        }
        else if (keybd_wait > Config::instance().startrun)
        {
            if (Config::instance().runscroll == 0)
            {
                if (keybd_wait % Config::instance().runwait != 0)
                {
                    return ""s;
                }
            }
            running = 1;
        }
    }
    else if (
        keybd_wait
        < Config::instance().select_fast_start * Config::instance().select_wait)
    {
        if (keybd_wait % Config::instance().select_wait != 0)
        {
            return ""s;
        }
    }
    else if (keybd_wait < 1000)
    {
        if (keybd_wait % Config::instance().select_fast_wait != 0)
        {
            return ""s;
        }
    }

    return action;
}

static bool
_is_keypress_delayed(int held_frames, int keywait, int initial_keywait)
{
    if (held_frames < initial_keywait)
    {
        if (held_frames == 0)
        {
            return false;
        }
    }
    else if (held_frames % keywait == 0)
    {
        return false;
    }

    return true;
}

std::string InputContext::_delay_normal_action(const std::string& action)
{
    if (action == "" || _last_action != action)
    {
        _last_action_held_frames = 0;
    }

    bool delayed = _is_keypress_delayed(_last_action_held_frames, 1, 20);

    _last_action_held_frames++;

    if (_last_action != action)
    {
        _last_action = action;
    }

    if (delayed)
    {
        return ""s;
    }

    return action;
} // namespace elona

std::string InputContext::check_for_command(KeyWaitDelay delay_type)
{
    const auto& keys = snail::Input::instance().pressed_keys();
    auto modifiers = snail::Input::instance().modifiers();

    if (const auto action = _check_movement_action(keys, modifiers))
    {
        _last_action = ""s;

        // Movement keys have special key delay behavior, so handle them.
        auto result = _delay_movement_action(*action, modifiers, delay_type);
        ++keybd_wait;

        return result;
    }
    else
    {
        keybd_wait = 0;
        keybd_attacking = 0;
        running = 0;
    }

    if (const auto keybind = _check_normal_action())
    {
        if (const auto action = _action_for_key(*keybind))
        {
            return _delay_normal_action(*action);
        }
        else
        {
            _last_action = "";
        }
    }
    else
    {
        _last_action = "";
    }

    return ""s;
}

std::string InputContext::check_for_command_with_list(int& list_index)
{
    auto action = check_for_command(KeyWaitDelay::always);

    if (action == "north"s)
    {
        snd(5);
        --cs;
        if (cs < 0)
        {
            cs = keyrange - 1;
            if (cs < 0)
            {
                cs = 0;
            }
        }
    }
    if (action == "south"s)
    {
        snd(5);
        ++cs;
        if (cs >= keyrange)
        {
            cs = 0;
        }
    }
    if (action == "west"s)
    {
        action = "previous_page"s;
    }
    if (action == "east"s)
    {
        action = "next_page"s;
    }
    if (cs >= keyrange)
    {
        cs_bk = -1;
        cs = keyrange - 1;
        if (cs < 0)
        {
            cs = 0;
        }
    }
    if (action == "enter"s)
    {
        list_index = cs;
    }
    else if (keybind_action_has_category(action, ActionCategory::selection))
    {
        list_index = keybind_id_number(action);
    }
    else
    {
        list_index = -1;
    }
    return action;
}

void InputContext::reset()
{
    snail::Input::instance().clear_pressed_keys();
    _last_action_held_frames = 0;
    _last_action = ""s;
}

InputContext InputContext::instance()
{
    static InputContext the_input_context = create(InputContextType::game);
    return the_input_context;
}

InputContext InputContext::for_menu()
{
    static InputContext the_input_context = create(InputContextType::menu);
    return the_input_context;
}

bool keybind_is_joystick_key(snail::Key key)
{
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
    if (action_id == ""s)
    {
        return false;
    }

    return keybind::actions.at(action_id).category == category;
}

int keybind_id_number(const std::string& action_id)
{
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

} // namespace elona
