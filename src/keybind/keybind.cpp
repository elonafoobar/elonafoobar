#include "keybind.hpp"
#include <unordered_map>
#include "../config.hpp"
#include "../enums.hpp"
#include "../gdata.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;

namespace elona
{

std::unordered_map<std::string, Action> actions;

void add_action(Action action)
{
    actions.emplace(action.id, action);
}

void init_actions()
{
    using namespace snail;

    // clang-format off
    add_action(Action{"escape",     "default", {{Key::escape, ModKey::none}}});
    add_action(Action{"cancel",     "default", {{Key::shift,  ModKey::none}}});
    add_action(Action{"enter",      "default", {{Key::enter,  ModKey::none}}});

    add_action(Action{"shortcut_1",  "shortcut", {{Key::key_1, ModKey::none}}});
    add_action(Action{"shortcut_2",  "shortcut", {{Key::key_2, ModKey::none}}});
    add_action(Action{"shortcut_3",  "shortcut", {{Key::key_3, ModKey::none}}});
    add_action(Action{"shortcut_4",  "shortcut", {{Key::key_4, ModKey::none}}});
    add_action(Action{"shortcut_5",  "shortcut", {{Key::key_5, ModKey::none}}});
    add_action(Action{"shortcut_6",  "shortcut", {{Key::key_6, ModKey::none}}});
    add_action(Action{"shortcut_7",  "shortcut", {{Key::key_7, ModKey::none}}});
    add_action(Action{"shortcut_8",  "shortcut", {{Key::key_8, ModKey::none}}});
    add_action(Action{"shortcut_9",  "shortcut", {{Key::key_9, ModKey::none}}});
    add_action(Action{"shortcut_10", "shortcut", {{Key::key_0, ModKey::none}}});
    add_action(Action{"shortcut_11", "shortcut", {{Key::key_1, ModKey::ctrl}, {Key::key_1, ModKey::shift}}});
    add_action(Action{"shortcut_12", "shortcut", {{Key::key_2, ModKey::ctrl}, {Key::key_2, ModKey::shift}}});
    add_action(Action{"shortcut_13", "shortcut", {{Key::key_3, ModKey::ctrl}, {Key::key_3, ModKey::shift}}});
    add_action(Action{"shortcut_14", "shortcut", {{Key::key_4, ModKey::ctrl}, {Key::key_4, ModKey::shift}}});
    add_action(Action{"shortcut_15", "shortcut", {{Key::key_5, ModKey::ctrl}, {Key::key_5, ModKey::shift}}});
    add_action(Action{"shortcut_16", "shortcut", {{Key::key_6, ModKey::ctrl}, {Key::key_6, ModKey::shift}}});
    add_action(Action{"shortcut_17", "shortcut", {{Key::key_7, ModKey::ctrl}, {Key::key_7, ModKey::shift}}});
    add_action(Action{"shortcut_18", "shortcut", {{Key::key_8, ModKey::ctrl}, {Key::key_8, ModKey::shift}}});
    add_action(Action{"shortcut_19", "shortcut", {{Key::key_9, ModKey::ctrl}, {Key::key_9, ModKey::shift}}});
    add_action(Action{"shortcut_20", "shortcut", {{Key::key_0, ModKey::ctrl}, {Key::key_0, ModKey::shift}}});

    add_action(Action{"up",             "menu", {{Key::up,     ModKey::none}, {Key::keypad_8, ModKey::none}}});
    add_action(Action{"down",           "menu", {{Key::down,   ModKey::none}, {Key::keypad_2, ModKey::none}}});
    add_action(Action{"next_page",      "menu", {{Key::left,   ModKey::none}, {Key::keypad_4, ModKey::none}, {Key::keypad_plus,  ModKey::none}}});
    add_action(Action{"previous_page",  "menu", {{Key::right,  ModKey::none}, {Key::keypad_6, ModKey::none}, {Key::keypad_minus, ModKey::none}}});
    add_action(Action{"next_menu",      "menu", {{Key::tab,    ModKey::none}}});
    add_action(Action{"previous_menu",  "menu", {{Key::tab,    ModKey::ctrl}}});
    add_action(Action{"switch_mode",    "menu", {{Key::key_z,      ModKey::none}}});
    add_action(Action{"switch_mode_2",  "menu", {{Key::key_x,      ModKey::none}}});

    add_action(Action{"north",      "movement", {{Key::up,        ModKey::none}, {Key::keypad_8, ModKey::none}}});
    add_action(Action{"south",      "movement", {{Key::down,      ModKey::none}, {Key::keypad_2, ModKey::none}}});
    add_action(Action{"east",       "movement", {{Key::left,      ModKey::none}, {Key::keypad_4, ModKey::none}}});
    add_action(Action{"west",       "movement", {{Key::right,     ModKey::none}, {Key::keypad_6, ModKey::none}}});
    add_action(Action{"northwest",  "movement", {{Key::pageup,    ModKey::none}, {Key::keypad_7, ModKey::none}}});
    add_action(Action{"northeast",  "movement", {{Key::home,      ModKey::none}, {Key::keypad_9, ModKey::none}}});
    add_action(Action{"southwest",  "movement", {{Key::pagedown,  ModKey::none}, {Key::keypad_1, ModKey::none}}});
    add_action(Action{"southeast",  "movement", {{Key::end,       ModKey::none}, {Key::keypad_3, ModKey::none}}});

    add_action(Action{"wait",             "game", {{Key::period,           ModKey::none}, {Key::keypad_5, ModKey::none}}});
    add_action(Action{"quick_menu",       "game", {{Key::key_z,                ModKey::none}}});
    add_action(Action{"zap",              "game", {{Key::key_z,                ModKey::shift}}});
    add_action(Action{"inventory",        "game", {{Key::key_x,                ModKey::none}}});
    add_action(Action{"quick_inventory",  "game", {{Key::key_x,                ModKey::shift}}});
    add_action(Action{"get",              "game", {{Key::key_g,                ModKey::none}, {Key::keypad_0, ModKey::none}}});
    add_action(Action{"drop",             "game", {{Key::key_d,                ModKey::none}}});
    add_action(Action{"chara_info",       "game", {{Key::key_c,                ModKey::none}}});
    add_action(Action{"eat",              "game", {{Key::key_e,                ModKey::none}}});
    add_action(Action{"wear",             "game", {{Key::key_w,                ModKey::none}}});
    add_action(Action{"cast",             "game", {{Key::key_v,                ModKey::none}}});
    add_action(Action{"drink",            "game", {{Key::key_q,                ModKey::none}}});
    add_action(Action{"read",             "game", {{Key::key_r,                ModKey::none}}});
    add_action(Action{"fire",             "game", {{Key::key_f,                ModKey::none}}});
    add_action(Action{"go_down",          "game", {{Key::greater,          ModKey::none}}});
    add_action(Action{"go_up",            "game", {{Key::less,             ModKey::none}}});
    add_action(Action{"save",             "game", {{Key::key_s,                ModKey::shift}}});
    add_action(Action{"search",           "game", {{Key::key_s,                ModKey::none}}});
    add_action(Action{"interact",         "game", {{Key::key_i,                ModKey::none}}});
    add_action(Action{"skill",            "game", {{Key::key_a,                ModKey::none}}});
    add_action(Action{"close",            "game", {{Key::key_c,                ModKey::shift}}});
    add_action(Action{"rest",             "game", {{Key::key_r,                ModKey::shift}}});
    add_action(Action{"target",           "game", {{Key::keypad_asterisk,  ModKey::none}}});
    add_action(Action{"dig",              "game", {{Key::key_d,                ModKey::shift}}});
    add_action(Action{"pray",             "game", {{Key::key_p,                ModKey::none}}});
    add_action(Action{"offer",            "game", {{Key::key_o,                ModKey::shift}}});
    add_action(Action{"journal",          "game", {{Key::key_j,                ModKey::none}}});
    add_action(Action{"material",         "game", {{Key::key_m,                ModKey::none}}});
    add_action(Action{"trait",            "game", {{Key::key_f,                ModKey::shift}}});
    add_action(Action{"look",             "game", {{Key::key_l,                ModKey::none}}});
    add_action(Action{"give",             "game", {{Key::key_g,                ModKey::shift}}});
    add_action(Action{"throw",            "game", {{Key::key_t,                ModKey::shift}}});
    add_action(Action{"ammo",             "game", {{Key::key_a,                ModKey::shift}}});
    add_action(Action{"autodig",          "game", {{Key::key_h,                ModKey::shift}}});
    add_action(Action{"quicksave",        "game", {{Key::f1,               ModKey::none}}});
    add_action(Action{"quickload",        "game", {{Key::f2,               ModKey::none}}});
    add_action(Action{"help",             "game", {{Key::question,         ModKey::none}}});
    add_action(Action{"message_log",      "game", {{Key::slash,            ModKey::none}}});
    add_action(Action{"chat_box",         "game", {{Key::tab,              ModKey::none}}});
    add_action(Action{"tcg",               "game", {{Key::f3,               ModKey::none}}});
    add_action(Action{"update_screen",     "game", {{Key::f9,               ModKey::none}}});
    add_action(Action{"dump_player_info",  "game", {{Key::f11,              ModKey::none}}});
    add_action(Action{"enable_voldemort",  "game", {{Key::f12,              ModKey::none}}});
    add_action(Action{"reload_autopick",   "game", {{Key::backspace,        ModKey::shift}}});
    add_action(Action{"auto_action",       "game", {{Key::enter,            ModKey::none}}});

    // TODO: prioritize over other categories
    add_action(Action{"wizard_mewmewmew",    "wizard", {{Key::f3,               ModKey::none}}});
    add_action(Action{"wizard_wish",         "wizard", {{Key::f5,               ModKey::none}}});
    add_action(Action{"wizard_advance_time", "wizard", {{Key::f6,               ModKey::none}}});
    add_action(Action{"wizard_delete_map",   "wizard", {{Key::f7,               ModKey::none}}});
    // clang-format on
}

bool InputContext::matches(
    const std::string& action_id,
    snail::Key key,
    snail::ModKey modifiers)
{
    if (available_actions.find(action_id) == available_actions.end())
    {
        return false;
    }

    // TODO
    const auto& action = actions.at(action_id);

    for (const auto& keybind : action.default_keybinds)
    {
        if (keybind.main == key /* && keybind.modifiers == modifiers */)
        {
            return true;
        }
    }

    return false;
}

optional<std::string> InputContext::action_for_key(const Keybind& keybind)
{
    // TODO: add multimap<Keybind, action_id>
    const auto it =
        std::find_if(actions.begin(), actions.end(), [&keybind](const auto& a) {
            for (const auto& k : a.second.default_keybinds)
            {
                if (k == keybind)
                    return true;
            }
            return false;
        });

    if (it != actions.end())
    {
        return it->second.id;
    }

    return none;
}

optional<std::string> InputContext::check_movement_action(
    const std::set<snail::Key>& keys,
    snail::ModKey modifiers)
{
    StickKey input = StickKey::none;
    bool wait = false;

    for (const auto& key : keys)
    {
        if (matches("north", key, modifiers))
        {
            input |= StickKey::up;
        }
        else if (matches("south", key, modifiers))
        {
            input |= StickKey::down;
        }
        else if (matches("east", key, modifiers))
        {
            input |= StickKey::left;
        }
        else if (matches("west", key, modifiers))
        {
            input |= StickKey::right;
        }
        else if (matches("northwest", key, modifiers))
        {
            input = StickKey::up | StickKey::left;
        }
        else if (matches("northeast", key, modifiers))
        {
            input = StickKey::up | StickKey::right;
        }
        else if (matches("southwest", key, modifiers))
        {
            input = StickKey::down | StickKey::left;
        }
        else if (matches("southeast", key, modifiers))
        {
            input = StickKey::down | StickKey::right;
        }
        else if (matches("wait", key, modifiers))
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
        std::cerr << "run" << std::endl;
        // Has to be modified globally, since scroll speed is determined by
        // keybd_wait. See @ref ui_scroll_screen()
        keybd_wait = 100000;
        if (keywait == 0)
        {
            keywait = 1;
            // if (const auto action = action_for(snail::Key::shift, modifiers))
            // { return *action; }
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

bool InputContext::is_nonmovement_key(const snail::Key& k)
{
    return !is_modifier(k) && excluded_keys.find(k) == excluded_keys.end();
}

optional<Keybind> InputContext::check_key()
{
    const auto& keys = snail::Input::instance().pressed_keys();
    auto modifiers = snail::Input::instance().modifiers();

    // Pick the first nonmovement key out of the ones that were held.
    // The only actions for which holding multiple keys makes sense is for the
    // movement keys.
    const auto it =
        std::find_if(keys.begin(), keys.end(), [this](const snail::Key& k) {
            return is_nonmovement_key(k);
        });

    if (it != keys.end())
    {
        return Keybind(*it, modifiers);
    }

    return none;
}

InputContext make_input_context(const std::string& category)
{
    InputContext result;
    result.add_actions_from_category("default");
    result.add_actions_from_category("movement");
    if (game_data.wizard)
    {
        result.add_actions_from_category("wizard");
    }
    result.add_actions_from_category(category);

    // TODO exclude movement keys

    return result;
}

void InputContext::add_actions_from_category(const std::string& category)
{
    for (const auto& pair : actions)
    {
        if (pair.second.category == category)
        {
            add_action(pair.second.id);
        }
    }
}

void InputContext::add_action(const std::string& action)
{
    available_actions.insert(action);
}

std::string InputContext::delay_movement_action(
    const std::string& action,
    snail::ModKey modifiers)
{
    if (keybd_wait >= 100000)
    {
        if ((modifiers & snail::ModKey::shift) != snail::ModKey::shift)
        {
            keybd_wait = 1000;
        }
    }

    // TODO
    KeyWaitDelay delay_type = KeyWaitDelay::walk_run;

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
            std::cerr << "RUN" << std::endl;
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

std::string InputContext::delay_normal_action(const std::string& action)
{
    if (action == "" || last_action_ != action)
    {
        last_action_held_frames_ = 0;
    }

    bool delayed = _is_keypress_delayed(last_action_held_frames_, 1, 20);

    if (last_action_ == action)
    {
        last_action_held_frames_++;
    }
    else
    {
        std::cerr << "set action " << action << std::endl;
        last_action_ = action;
    }

    if (delayed)
    {
        return ""s;
    }

    return action;
}

std::string InputContext::check_for_command()
{
    const auto& keys = snail::Input::instance().pressed_keys();
    auto modifiers = snail::Input::instance().modifiers();

    if (const auto action = check_movement_action(keys, modifiers))
    {
        last_action_ = ""s;

        // Movement keys have special key delay behavior, so handle them.
        auto result = delay_movement_action(*action, modifiers);
        ++keybd_wait;

        return result;
    }
    else
    {
        keybd_wait = 0;
        keybd_attacking = 0;
        running = 0;
    }

    if (const auto keybind = check_key())
    {
        if (const auto action = action_for_key(*keybind))
        {
            return delay_normal_action(*action);
        }
        else
        {
            last_action_ = "";
        }
    }
    else
    {
        last_action_ = "";
    }

    return ""s;
}

std::string InputContext::check_for_command_with_list(int& list_index)
{
    return check_for_command();
}

} // namespace elona
