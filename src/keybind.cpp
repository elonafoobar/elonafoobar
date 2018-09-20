#include "keybind.hpp"
#include <unordered_map>

namespace elona
{

std::unordered_map<std::string, Action> actions;

void add_action(Action action)
{
    actions.emplace_back(action.id, std::move(action));
}

void init_actions()
{
    using namespace snail;

    // clang-format off
    add_action({"escape",     "default", {{Key::escape, ModKey::none}}});
    add_action({"cancel",     "default", {{Key::shift,  ModKey::none}}});
    add_action({"enter",      "default", {{Key::enter,  ModKey::none}}});

    add_action({"shortcut_1",  "shortcut", {{Key::key_1, ModKey::none}}});
    add_action({"shortcut_2",  "shortcut", {{Key::key_2, ModKey::none}}});
    add_action({"shortcut_3",  "shortcut", {{Key::key_3, ModKey::none}}});
    add_action({"shortcut_4",  "shortcut", {{Key::key_4, ModKey::none}}});
    add_action({"shortcut_5",  "shortcut", {{Key::key_5, ModKey::none}}});
    add_action({"shortcut_6",  "shortcut", {{Key::key_6, ModKey::none}}});
    add_action({"shortcut_7",  "shortcut", {{Key::key_7, ModKey::none}}});
    add_action({"shortcut_8",  "shortcut", {{Key::key_8, ModKey::none}}});
    add_action({"shortcut_9",  "shortcut", {{Key::key_9, ModKey::none}}});
    add_action({"shortcut_10", "shortcut", {{Key::key_0, ModKey::none}}});
    add_action({"shortcut_11", "shortcut", {{Key::key_1, ModKey::ctrl}, {Key::key_1, ModKey::shift}}});
    add_action({"shortcut_12", "shortcut", {{Key::key_2, ModKey::ctrl}, {Key::key_2, ModKey::shift}}});
    add_action({"shortcut_13", "shortcut", {{Key::key_3, ModKey::ctrl}, {Key::key_3, ModKey::shift}}});
    add_action({"shortcut_14", "shortcut", {{Key::key_4, ModKey::ctrl}, {Key::key_4, ModKey::shift}}});
    add_action({"shortcut_15", "shortcut", {{Key::key_5, ModKey::ctrl}, {Key::key_5, ModKey::shift}}});
    add_action({"shortcut_16", "shortcut", {{Key::key_6, ModKey::ctrl}, {Key::key_6, ModKey::shift}}});
    add_action({"shortcut_17", "shortcut", {{Key::key_7, ModKey::ctrl}, {Key::key_7, ModKey::shift}}});
    add_action({"shortcut_18", "shortcut", {{Key::key_8, ModKey::ctrl}, {Key::key_8, ModKey::shift}}});
    add_action({"shortcut_19", "shortcut", {{Key::key_9, ModKey::ctrl}, {Key::key_9, ModKey::shift}}});
    add_action({"shortcut_20", "shortcut", {{Key::key_0, ModKey::ctrl}, {Key::key_0, ModKey::shift}}});

    add_action({"up",             "menu", {{Key::up,     ModKey::none}, {Key::keypad_8, ModKey::none}}});
    add_action({"down",           "menu", {{Key::down,   ModKey::none}, {Key::keypad_2, ModKey::none}}});
    add_action({"next_page",      "menu", {{Key::left,   ModKey::none}, {Key::keypad_4, ModKey::none}, {Key::keypad_plus,  ModKey::none}}});
    add_action({"previous_page",  "menu", {{Key::right,  ModKey::none}, {Key::keypad_6, ModKey::none}, {Key::keypad_minus, ModKey::none}}});
    add_action({"next_menu",      "menu", {{Key::tab,    ModKey::none}}});
    add_action({"previous_menu",  "menu", {{Key::tab,    ModKey::ctrl}}});
    add_action({"switch_mode",    "menu", {{Key::z,      ModKey::none}}});
    add_action({"switch_mode_2",  "menu", {{Key::x,      ModKey::none}}});

    add_action({"north",      "movement", {{Key::up,        ModKey::none}, {Key::keypad_8, ModKey::none}}});
    add_action({"south",      "movement", {{Key::down,      ModKey::none}, {Key::keypad_2, ModKey::none}}});
    add_action({"east",       "movement", {{Key::left,      ModKey::none}, {Key::keypad_4, ModKey::none}}});
    add_action({"west",       "movement", {{Key::right,     ModKey::none}, {Key::keypad_6, ModKey::none}}});
    add_action({"northeast",  "movement", {{Key::home,      ModKey::none}, {Key::keypad_7, ModKey::none}}});
    add_action({"northwest",  "movement", {{Key::page_up,   ModKey::none}, {Key::keypad_9, ModKey::none}}});
    add_action({"southeast",  "movement", {{Key::end,       ModKey::none}, {Key::keypad_1, ModKey::none}}});
    add_action({"southwest",  "movement", {{Key::page_down, ModKey::none}, {Key::keypad_3, ModKey::none}}});

    add_action({"wait",             "game", {{Key::period,           ModKey::none}, {Key::keypad_5, ModKey::none}}});
    add_action({"quick_menu",       "game", {{Key::z,                ModKey::none}}});
    add_action({"zap",              "game", {{Key::z,                ModKey::shift}}});
    add_action({"inventory",        "game", {{Key::x,                ModKey::none}}});
    add_action({"quick_inventory",  "game", {{Key::x,                ModKey::shift}}});
    add_action({"get",              "game", {{Key::g,                ModKey::none}, {Key::numpad_0, ModKey::none}}});
    add_action({"drop",             "game", {{Key::d,                ModKey::none}}});
    add_action({"chara_info",       "game", {{Key::c,                ModKey::none}}});
    add_action({"eat",              "game", {{Key::e,                ModKey::none}}});
    add_action({"wear",             "game", {{Key::w,                ModKey::none}}});
    add_action({"cast",             "game", {{Key::v,                ModKey::none}}});
    add_action({"drink",            "game", {{Key::q,                ModKey::none}}});
    add_action({"read",             "game", {{Key::r,                ModKey::none}}});
    add_action({"fire",             "game", {{Key::f,                ModKey::none}}});
    add_action({"go_down",          "game", {{Key::greater,          ModKey::none}}});
    add_action({"go_up",            "game", {{Key::less,             ModKey::none}}});
    add_action({"save",             "game", {{Key::s,                ModKey::shift}}});
    add_action({"search",           "game", {{Key::s,                ModKey::none}}});
    add_action({"interact",         "game", {{Key::i,                ModKey::none}}});
    add_action({"skill",            "game", {{Key::a,                ModKey::none}}});
    add_action({"close",            "game", {{Key::c,                ModKey::shift}}});
    add_action({"rest",             "game", {{Key::r,                ModKey::shift}}});
    add_action({"target",           "game", {{Key::keypad_asterisk,  ModKey::none}}});
    add_action({"dig",              "game", {{Key::d,                ModKey::shift}}});
    add_action({"pray",             "game", {{Key::p,                ModKey::none}}});
    add_action({"offer",            "game", {{Key::o,                ModKey::shift}}});
    add_action({"journal",          "game", {{Key::j,                ModKey::none}}});
    add_action({"material",         "game", {{Key::m,                ModKey::none}}});
    add_action({"trait",            "game", {{Key::f,                ModKey::shift}}});
    add_action({"look",             "game", {{Key::l,                ModKey::none}}});
    add_action({"give",             "game", {{Key::g,                ModKey::shift}}});
    add_action({"throw",            "game", {{Key::t,                ModKey::shift}}});
    add_action({"ammo",             "game", {{Key::a,                ModKey::shift}}});
    add_action({"autodig",          "game", {{Key::h,                ModKey::shift}}});
    add_action({"quicksave",        "game", {{Key::f1,               ModKey::none}}});
    add_action({"quickload",        "game", {{Key::f2,               ModKey::none}}});
    add_action({"help",             "game", {{Key::question,         ModKey::none}}});
    add_action({"message_log",      "game", {{Key::slash,            ModKey::none}}});
    add_action({"chat_box",         "game", {{Key::tab,              ModKey::none}}});
    // clang-format on
}

bool input_context::matches(
    const std::string& action_id,
    snail::Key key,
    snail::ModKey modifiers)
{
    if (!available_actions.contains(action_id))
    {
        return false;
    }

    // TODO
    const auto& action = actions.at(action_id);

    for (const auto& keybind : action.default_keybindings)
    {
        if (keybind.main == key && keybind.modifiers == modifiers)
        {
            return true;
        }
    }

    return false;
}

optional<std::string> input_context::action_for_key(const Keybind& keybind)
{
    // TODO: add multimap<Keybind, action_id>
    const auto it =
        std::find_if(actions.begin(), actions.end(), [](const Action& a) {
            return std::find_if(
                       a.default_keybinds.begin(),
                       a.default_keybinds.end(),
                       [](const Keybind& k) { k == keybind; })
                != a.default_keybinds.end();
        });

    if (it != actions.end())
    {
        return it->id;
    }

    return none;
}

optional<std::string> input_context::check_movement_action(
    const std::vector<snail::Key>& keys,
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
    }

    if (modifiers & snail::ModKey::shift)
    {
        _keybd_wait = 100000;
        if (_keywait == 0)
        {
            _keywait = 1;
            // if (const auto action = action_for(snail::Key::shift, modifiers))
            // { return *action; }
        }
    }
    else
    {
        _keywait = 0;
    }


    if (!(modifiers & snail::ModKey::alt))
    {
        if (input == StickKey::left)
        {
            return "west";
        }
        if (input == StickKey::up)
        {
            return "north";
        }
        if (input == StickKey::right)
        {
            return "east";
        }
        if (input == StickKey::down)
        {
            return "south";
        }
    }
    if (input == (StickKey::up | StickKey::left))
    {
        return "northwest";
    }
    if (input == (StickKey::up | StickKey::right))
    {
        return "northeast";
    }
    if (input == (StickKey::down | StickKey::left))
    {
        return "southwest";
    }
    if (input == (StickKey::down | StickKey::right))
    {
        return "southeast";
    }
    if (wait)
    {
        return "wait";
    }

    return none;
}

bool input_context::is_nonmovement_key(const snail::Key& k)
{
    return !is_modifier(k) && !excluded_keys.contains(k);
}

optional<Keybind> input_context::check_key()
{
    const auto& keys = snail::input::Instance().pressed_keys();
    auto modifiers = snail::input::Instance().modifiers();

    // Pick the first nonmovement key out of the ones that were held.
    // The only actions for which holding multiple keys makes sense is for the
    // movement keys.
    const auto it = std::find_if(
        keys.begin(), keys.end(), &input_context::is_nonmovement_key);

    if (it != keys.end())
    {
        return {*it, modifiers};
    }

    return none;
}

input_context make_input_context(const std::string& category)
{
    input_context result;
    result.add_actions_from_category("default");
    result.add_actions_from_category(category);

    // TODO exclude movement keys

    return result;
}

void input_context::add_actions_from_category(const std::string& category)
{
    for (const auto& action : actions)
    {
        if (action.category == category)
        {
            add_action(action.id);
        }
    }
}

void input_context::add_action(const std::string& action)
{
    available_actions.insert(action);
}

std::string input_context::delay_movement_action(
    snail::ModKey modifiers,
    const std::string& action)
{
    if (delay_type == KeyWaitDelay::none)
    {
        return action;
    }

    if (delay_type == KeyWaitDelay::walk_run)
    {
        if (_keybd_attacking != 0)
        {
            if (_keybd_wait % Config::instance().attackwait != 0)
            {
                return "";
            }
        }
        else if (Config::instance().scroll == 0)
        {
            if (_keybd_wait
                < Config::instance().walkwait * Config::instance().startrun)
            {
                if (_keybd_wait % Config::instance().walkwait != 0)
                {
                    return "";
                }
            }
            else
            {
                running = 1;
                if (_keybd_wait < 100000)
                {
                    if (_keybd_wait % Config::instance().runwait != 0)
                    {
                        return "";
                    }
                }
            }
        }
        else if (input == StickKey::none)
        {
            if (_keybd_wait < 20)
            {
                if (_keybd_wait != 0)
                {
                    return "";
                }
            }
        }
        else if (_keybd_wait > Config::instance().startrun)
        {
            if (Config::instance().runscroll == 0)
            {
                if (_keybd_wait % Config::instance().runwait != 0)
                {
                    return "";
                }
            }
            _running = 1;
        }
    }
    else if (
        _keybd_wait
        < Config::instance().select_fast_start * Config::instance().select_wait)
    {
        if (_keybd_wait % Config::instance().select_wait != 0)
        {
            return "";
        }
    }
    else if (_keybd_wait < 1000)
    {
        if (_keybd_wait % Config::instance().select_fast_wait != 0)
        {
            return "";
        }
    }
    ++_keybd_wait;

    return action;
}

std::string input_context::check_for_command()
{
    const auto& keys = snail::input::Instance().pressed_keys();
    auto modifiers = snail::input::Instance().modifiers();

    if (const auto action = check_movement_key(keys, modifiers))
    {
        // Movement keys have special key delay behavior, so handle them.
        return delay_movement_action(*action);
    }
    else
    {
        _keybd_wait = 0;
        _keybd_attacking = 0;
        _running = 0;
    }

    if (const auto keybind = check_key())
    {
        if (const auto action = action_for_key(*keybind))
        {
            return *action;
        }
    }

    return "";
}

std::string input_context::check_for_command_with_list(int& list_index)
{
    return check_for_command();
}

} // namespace elona
