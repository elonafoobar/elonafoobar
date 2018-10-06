#include "keybind.hpp"
#include "../audio.hpp"
#include "../config/config.hpp"
#include "../enums.hpp"
#include "../gdata.hpp"
#include "../lib/profiler.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;

namespace elona
{

namespace
{

// The last held key has to be global across all input contexts, because a key
// can generate two different actions in different contexts. If key delay
// depended on the last action generated by a keypress, when the context is
// changed by entering a menu, there would be no key delay and the key would be
// counted as pressed twice.

snail::Key last_held_key = snail::Key::none;
int last_held_key_frames = 0;

} // namespace

// This map holds the action categories available in an input context.
// Categories at the top will override categories further down. This is to
// support the behavior of toggling wizard mode.
// TODO: It still needs to support ignoring key conflicts for togglable
// categories.

// clang-format off
static std::map<InputContextType, std::vector<ActionCategory>> input_context_types =
{
    {InputContextType::menu, {ActionCategory::shortcut,
                              ActionCategory::menu,
                              ActionCategory::selection,
                              ActionCategory::default_}},

    {InputContextType::game, {ActionCategory::wizard,
                              ActionCategory::game,
                              ActionCategory::shortcut,
                              ActionCategory::default_}}
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
                // if (the_binding.primary.empty())
                // {
                //     the_binding.primary = keybind;
                // }
                // else if (the_binding.alternate.empty())
                // {
                //     the_binding.alternate = keybind;
                // }
                // else
                // {
                //     assert(false);
                // }
            }
            else
            {
                // Permanently bind keys that shouldn't be unbound (escape,
                // enter, and directional keys)
                the_binding.permanent = keybind;
            }
        }
    }

    keybind_regenerate_key_select();
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
            std::find(categories.begin(), categories.end(), action_category)
            != categories.end();

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
    if (binding.permanent.main == key
        && binding.permanent.modifiers == modifiers)
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
    for (const auto& action_id : _available_actions_sorted)
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

    // Movement keys have to ignore Shift or Alt. They could be used with them
    // in a hardcoded manner for running or diagonal restriction.
    // TODO: At least make this clear to players somehow.
    snail::ModKey key_modifiers =
        modifiers & ~(snail::ModKey::shift | snail::ModKey::alt);

    for (const auto& key : keys)
    {
        // NOTE: Escape acts as both "summon the quit menu" at the main game
        // loop and "cancel", but actual checks for escape being pressed are
        // relatively few. Setting the global key_escape = true is to avoid
        // having to do (action == "cancel" || action == "escape") everywhere.
        if (_matches("escape", key, key_modifiers))
        {
            bool just_pressed = keywait == 0;
            keywait = 1;
            key_escape = true;

            if (just_pressed)
            {
                return "cancel"s;
            }
            else
            {
                return ""s;
            }
        }

        if (_matches("north", key, key_modifiers))
        {
            input |= StickKey::up;
        }
        else if (_matches("south", key, key_modifiers))
        {
            input |= StickKey::down;
        }
        else if (_matches("east", key, key_modifiers))
        {
            input |= StickKey::left;
        }
        else if (_matches("west", key, key_modifiers))
        {
            input |= StickKey::right;
        }
        else if (_matches("northwest", key, key_modifiers))
        {
            input = StickKey::up | StickKey::left;
        }
        else if (_matches("northeast", key, key_modifiers))
        {
            input = StickKey::up | StickKey::right;
        }
        else if (_matches("southwest", key, key_modifiers))
        {
            input = StickKey::down | StickKey::left;
        }
        else if (_matches("southeast", key, key_modifiers))
        {
            input = StickKey::down | StickKey::right;
        }
        else if (_matches("wait", key, key_modifiers))
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
        std::cerr << "shift " << keywait << " " << std::endl;
        if (keywait == 0)
        {
            std::cerr << "just pressed " << std::endl;
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
            _available_actions_sorted.push_back(action_id);
        }
    }
}

std::string InputContext::_delay_movement_action(
    const std::string& action,
    snail::ModKey modifiers,
    KeyWaitDelay delay_type)
{
    std::cerr << "KEYBDWAIT: " << keybd_wait << std::endl;
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
                std::cerr << "WALK" << std::endl;
                if (keybd_wait % Config::instance().walkwait != 0)
                {
                    return ""s;
                }
            }
            else
            {
                std::cerr << "RUN" << std::endl;
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
            std::cerr << "NONEWAIT" << std::endl;
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
            std::cerr << "STARTRUN" << std::endl;
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
        std::cerr << "SELECTWAIT" << std::endl;
        if (keybd_wait % Config::instance().select_wait != 0)
        {
            return ""s;
        }
    }
    else if (keybd_wait < 1000)
    {
        std::cerr << "SELECTFASTWAIT" << std::endl;
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

bool InputContext::_delay_normal_action(const Keybind& keybind)
{
    if (last_held_key != keybind.main)
    {
        last_held_key_frames = 0;
    }

    bool delayed = _is_keypress_delayed(last_held_key_frames, 1, 20);

    last_held_key_frames++;

    if (last_held_key != keybind.main)
    {
        last_held_key = keybind.main;
    }

    if (delayed)
    {
        std::cerr << "DEL " << std::endl;
        return true;
    }
    std::cerr << "PLAY " << last_held_key_frames << " " << keybind.to_string()
              << std::endl;

    return false;
} // namespace elona

std::string InputContext::check_for_command(KeyWaitDelay delay_type)
{
    key_escape = false;

    const auto& keys = snail::Input::instance().pressed_keys();
    auto modifiers = snail::Input::instance().modifiers();

    if (/* !shortcut && */ keyhalt != 0)
    {
        if (keys.size() > 0)
        {
            keybd_wait = 0;
            return "";
        }
        else
        {
            keyhalt = 0;
        }
    }

    for (const auto& key : keys)
    {
        if (auto n = keybind_key_name(key))
        {
            std::cerr << "K " << *n << std::endl;
        }
    }

    if (const auto action = _check_movement_action(keys, modifiers))
    {
        last_held_key = snail::Key::none;
        last_held_key_frames = 0;

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
            if (!_delay_normal_action(*keybind))
            {
                return *action;
            }
        }
        else
        {
            last_held_key = snail::Key::none;
            last_held_key_frames = 0;
        }
    }
    else
    {
        last_held_key = snail::Key::none;
        last_held_key_frames = 0;
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
        list_index = keybind_index_number(action);
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
    key_escape = false;
    last_held_key = snail::Key::none;
    last_held_key_frames = 0;
}

InputContext& InputContext::instance()
{
    static optional<InputContext> the_input_context;
    if (!the_input_context)
    {
        the_input_context = create(InputContextType::game);
    }
    return *the_input_context;
}

InputContext& InputContext::for_menu()
{
    static optional<InputContext> the_input_context;
    if (!the_input_context)
    {
        the_input_context = create(InputContextType::menu);
    }
    return *the_input_context;
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
    if (keybind::actions.find(action_id) == keybind::actions.end())
    {
        ELONA_LOG("No such keybind action " << action_id);
        return false;
    }
    if (action_id == ""s)
    {
        return false;
    }

    return keybind::actions.at(action_id).category == category;
}

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

        // NOTE: key_select only represents the primarily bound key.
        bool shift = (binding.primary.modifiers & snail::ModKey::shift)
            == snail::ModKey::shift;
        key_select(cnt) = keybind_key_short_name(binding.primary.main, shift);
        std::cerr << "SET " << cnt << " " << key_select(cnt) << std::endl;
        cnt++;
    }
}

int keybind_index_number(const std::string& action_id)
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

} // namespace elona