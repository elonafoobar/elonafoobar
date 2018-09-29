#include "keybind.hpp"
#include "../audio.hpp"
#include "../config/config.hpp"
#include "../enums.hpp"
#include "../gdata.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;

namespace elona
{

namespace keybind
{
ActionMap actions;
} // namespace keybind

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

void init_actions()
{
    using namespace snail;
    using namespace keybind;

    actions.clear();

    // clang-format off
    actions.emplace("escape",              Action{ActionCategory::default_,  {{Key::escape,          ModKey::none}}});
    actions.emplace("cancel",              Action{ActionCategory::default_,  {{Key::shift,           ModKey::none}}});
    actions.emplace("enter",               Action{ActionCategory::default_,  {{Key::enter,           ModKey::none}, {Key::keypad_enter, ModKey::none}}});
    actions.emplace("north",               Action{ActionCategory::default_,  {{Key::up,              ModKey::none}, {Key::keypad_8,     ModKey::none}}});
    actions.emplace("south",               Action{ActionCategory::default_,  {{Key::down,            ModKey::none}, {Key::keypad_2,     ModKey::none}}});
    actions.emplace("east",                Action{ActionCategory::default_,  {{Key::left,            ModKey::none}, {Key::keypad_4,     ModKey::none}}});
    actions.emplace("west",                Action{ActionCategory::default_,  {{Key::right,           ModKey::none}, {Key::keypad_6,     ModKey::none}}});
    actions.emplace("northwest",           Action{ActionCategory::default_,  {{Key::pageup,          ModKey::none}, {Key::keypad_7,     ModKey::none}}});
    actions.emplace("northeast",           Action{ActionCategory::default_,  {{Key::home,            ModKey::none}, {Key::keypad_9,     ModKey::none}}});
    actions.emplace("southwest",           Action{ActionCategory::default_,  {{Key::pagedown,        ModKey::none}, {Key::keypad_1,     ModKey::none}}});
    actions.emplace("southeast",           Action{ActionCategory::default_,  {{Key::end,             ModKey::none}, {Key::keypad_3,     ModKey::none}}});

    actions.emplace("shortcut_1",          Action{ActionCategory::shortcut,  {{Key::key_1,           ModKey::none}}});
    actions.emplace("shortcut_2",          Action{ActionCategory::shortcut,  {{Key::key_2,           ModKey::none}}});
    actions.emplace("shortcut_3",          Action{ActionCategory::shortcut,  {{Key::key_3,           ModKey::none}}});
    actions.emplace("shortcut_4",          Action{ActionCategory::shortcut,  {{Key::key_4,           ModKey::none}}});
    actions.emplace("shortcut_5",          Action{ActionCategory::shortcut,  {{Key::key_5,           ModKey::none}}});
    actions.emplace("shortcut_6",          Action{ActionCategory::shortcut,  {{Key::key_6,           ModKey::none}}});
    actions.emplace("shortcut_7",          Action{ActionCategory::shortcut,  {{Key::key_7,           ModKey::none}}});
    actions.emplace("shortcut_8",          Action{ActionCategory::shortcut,  {{Key::key_8,           ModKey::none}}});
    actions.emplace("shortcut_9",          Action{ActionCategory::shortcut,  {{Key::key_9,           ModKey::none}}});
    actions.emplace("shortcut_10",         Action{ActionCategory::shortcut,  {{Key::key_0,           ModKey::none}}});
    actions.emplace("shortcut_11",         Action{ActionCategory::shortcut,  {{Key::key_1,           ModKey::ctrl}, {Key::key_1, ModKey::shift}}});
    actions.emplace("shortcut_12",         Action{ActionCategory::shortcut,  {{Key::key_2,           ModKey::ctrl}, {Key::key_2, ModKey::shift}}});
    actions.emplace("shortcut_13",         Action{ActionCategory::shortcut,  {{Key::key_3,           ModKey::ctrl}, {Key::key_3, ModKey::shift}}});
    actions.emplace("shortcut_14",         Action{ActionCategory::shortcut,  {{Key::key_4,           ModKey::ctrl}, {Key::key_4, ModKey::shift}}});
    actions.emplace("shortcut_15",         Action{ActionCategory::shortcut,  {{Key::key_5,           ModKey::ctrl}, {Key::key_5, ModKey::shift}}});
    actions.emplace("shortcut_16",         Action{ActionCategory::shortcut,  {{Key::key_6,           ModKey::ctrl}, {Key::key_6, ModKey::shift}}});
    actions.emplace("shortcut_17",         Action{ActionCategory::shortcut,  {{Key::key_7,           ModKey::ctrl}, {Key::key_7, ModKey::shift}}});
    actions.emplace("shortcut_18",         Action{ActionCategory::shortcut,  {{Key::key_8,           ModKey::ctrl}, {Key::key_8, ModKey::shift}}});
    actions.emplace("shortcut_19",         Action{ActionCategory::shortcut,  {{Key::key_9,           ModKey::ctrl}, {Key::key_9, ModKey::shift}}});
    actions.emplace("shortcut_20",         Action{ActionCategory::shortcut,  {{Key::key_0,           ModKey::ctrl}, {Key::key_0, ModKey::shift}}});

    actions.emplace("select_1",            Action{ActionCategory::selection, {{Key::key_a,           ModKey::none}}});
    actions.emplace("select_2",            Action{ActionCategory::selection, {{Key::key_b,           ModKey::none}}});
    actions.emplace("select_3",            Action{ActionCategory::selection, {{Key::key_c,           ModKey::none}}});
    actions.emplace("select_4",            Action{ActionCategory::selection, {{Key::key_d,           ModKey::none}}});
    actions.emplace("select_5",            Action{ActionCategory::selection, {{Key::key_e,           ModKey::none}}});
    actions.emplace("select_6",            Action{ActionCategory::selection, {{Key::key_f,           ModKey::none}}});
    actions.emplace("select_7",            Action{ActionCategory::selection, {{Key::key_g,           ModKey::none}}});
    actions.emplace("select_8",            Action{ActionCategory::selection, {{Key::key_h,           ModKey::none}}});
    actions.emplace("select_9",            Action{ActionCategory::selection, {{Key::key_i,           ModKey::none}}});
    actions.emplace("select_10",           Action{ActionCategory::selection, {{Key::key_j,           ModKey::none}}});
    actions.emplace("select_11",           Action{ActionCategory::selection, {{Key::key_k,           ModKey::none}}});
    actions.emplace("select_12",           Action{ActionCategory::selection, {{Key::key_l,           ModKey::none}}});
    actions.emplace("select_13",           Action{ActionCategory::selection, {{Key::key_m,           ModKey::none}}});
    actions.emplace("select_14",           Action{ActionCategory::selection, {{Key::key_n,           ModKey::none}}});
    actions.emplace("select_15",           Action{ActionCategory::selection, {{Key::key_o,           ModKey::none}}});
    actions.emplace("select_16",           Action{ActionCategory::selection, {{Key::key_p,           ModKey::none}}});
    actions.emplace("select_17",           Action{ActionCategory::selection, {{Key::key_q,           ModKey::none}}});
    actions.emplace("select_18",           Action{ActionCategory::selection, {{Key::key_r,           ModKey::none}}});
    actions.emplace("select_19",           Action{ActionCategory::selection, {{Key::key_s,           ModKey::none}}});

    actions.emplace("next_page",           Action{ActionCategory::menu,      {{Key::keypad_plus,     ModKey::none}}});
    actions.emplace("previous_page",       Action{ActionCategory::menu,      {{Key::keypad_minus,    ModKey::none}}});
    actions.emplace("next_menu",           Action{ActionCategory::menu,      {{Key::tab,             ModKey::none}}});
    actions.emplace("previous_menu",       Action{ActionCategory::menu,      {{Key::tab,             ModKey::ctrl}}});
    actions.emplace("switch_mode",         Action{ActionCategory::menu,      {{Key::key_z,           ModKey::none}}});
    actions.emplace("switch_mode_2",       Action{ActionCategory::menu,      {{Key::key_x,           ModKey::none}}});

    actions.emplace("wait",                Action{ActionCategory::game,      {{Key::period,          ModKey::none}, {Key::keypad_5, ModKey::none}}});
    actions.emplace("quick_menu",          Action{ActionCategory::game,      {{Key::key_z,           ModKey::none}}});
    actions.emplace("zap",                 Action{ActionCategory::game,      {{Key::key_z,           ModKey::shift}}});
    actions.emplace("inventory",           Action{ActionCategory::game,      {{Key::key_x,           ModKey::none}}});
    actions.emplace("quick_inventory",     Action{ActionCategory::game,      {{Key::key_x,           ModKey::shift}}});
    actions.emplace("get",                 Action{ActionCategory::game,      {{Key::key_g,           ModKey::none}, {Key::keypad_0, ModKey::none}}});
    actions.emplace("drop",                Action{ActionCategory::game,      {{Key::key_d,           ModKey::none}}});
    actions.emplace("chara_info",          Action{ActionCategory::game,      {{Key::key_c,           ModKey::none}}});
    actions.emplace("eat",                 Action{ActionCategory::game,      {{Key::key_e,           ModKey::none}}});
    actions.emplace("wear",                Action{ActionCategory::game,      {{Key::key_w,           ModKey::none}}});
    actions.emplace("cast",                Action{ActionCategory::game,      {{Key::key_v,           ModKey::none}}});
    actions.emplace("drink",               Action{ActionCategory::game,      {{Key::key_q,           ModKey::none}}});
    actions.emplace("read",                Action{ActionCategory::game,      {{Key::key_r,           ModKey::none}}});
    actions.emplace("fire",                Action{ActionCategory::game,      {{Key::key_f,           ModKey::none}}});
    actions.emplace("go_down",             Action{ActionCategory::game,      {{Key::greater,         ModKey::none}}});
    actions.emplace("go_up",               Action{ActionCategory::game,      {{Key::less,            ModKey::none}}});
    actions.emplace("save",                Action{ActionCategory::game,      {{Key::key_s,           ModKey::shift}}});
    actions.emplace("search",              Action{ActionCategory::game,      {{Key::key_s,           ModKey::none}}});
    actions.emplace("interact",            Action{ActionCategory::game,      {{Key::key_i,           ModKey::none}}});
    actions.emplace("skill",               Action{ActionCategory::game,      {{Key::key_a,           ModKey::none}}});
    actions.emplace("close",               Action{ActionCategory::game,      {{Key::key_c,           ModKey::shift}}});
    actions.emplace("rest",                Action{ActionCategory::game,      {{Key::key_r,           ModKey::shift}}});
    actions.emplace("target",              Action{ActionCategory::game,      {{Key::keypad_asterisk, ModKey::none}}});
    actions.emplace("dig",                 Action{ActionCategory::game,      {{Key::key_d,           ModKey::shift}}});
    actions.emplace("pray",                Action{ActionCategory::game,      {{Key::key_p,           ModKey::none}}});
    actions.emplace("offer",               Action{ActionCategory::game,      {{Key::key_o,           ModKey::shift}}});
    actions.emplace("journal",             Action{ActionCategory::game,      {{Key::key_j,           ModKey::none}}});
    actions.emplace("material",            Action{ActionCategory::game,      {{Key::key_m,           ModKey::none}}});
    actions.emplace("trait",               Action{ActionCategory::game,      {{Key::key_f,           ModKey::shift}}});
    actions.emplace("look",                Action{ActionCategory::game,      {{Key::key_l,           ModKey::none}}});
    actions.emplace("give",                Action{ActionCategory::game,      {{Key::key_g,           ModKey::shift}}});
    actions.emplace("throw",               Action{ActionCategory::game,      {{Key::key_t,           ModKey::shift}}});
    actions.emplace("ammo",                Action{ActionCategory::game,      {{Key::key_a,           ModKey::shift}}});
    actions.emplace("autodig",             Action{ActionCategory::game,      {{Key::key_h,           ModKey::shift}}});
    actions.emplace("quicksave",           Action{ActionCategory::game,      {{Key::f1,              ModKey::none}}});
    actions.emplace("quickload",           Action{ActionCategory::game,      {{Key::f2,              ModKey::none}}});
    actions.emplace("help",                Action{ActionCategory::game,      {{Key::question,        ModKey::none}}});
    actions.emplace("message_log",         Action{ActionCategory::game,      {{Key::slash,           ModKey::none}}});
    actions.emplace("chat_box",            Action{ActionCategory::game,      {{Key::tab,             ModKey::none}}});
    actions.emplace("tcg",                 Action{ActionCategory::game,      {{Key::f3,              ModKey::none}}});
    actions.emplace("update_screen",       Action{ActionCategory::game,      {{Key::f9,              ModKey::none}}});
    actions.emplace("dump_player_info",    Action{ActionCategory::game,      {{Key::f11,             ModKey::none}}});
    actions.emplace("enable_voldemort",    Action{ActionCategory::game,      {{Key::f12,             ModKey::none}}});
    actions.emplace("reload_autopick",     Action{ActionCategory::game,      {{Key::backspace,       ModKey::shift}}});
    actions.emplace("auto_action",         Action{ActionCategory::game,      {{Key::enter,           ModKey::none}}});

    // TODO: prioritize over other categories
    actions.emplace("wizard_mewmewmew",    Action{ActionCategory::wizard,    {{Key::f3,              ModKey::none}}});
    actions.emplace("wizard_wish",         Action{ActionCategory::wizard,    {{Key::f5,              ModKey::none}}});
    actions.emplace("wizard_advance_time", Action{ActionCategory::wizard,    {{Key::f6,              ModKey::none}}});
    actions.emplace("wizard_delete_map",   Action{ActionCategory::wizard,    {{Key::f7,              ModKey::none}}});
    // clang-format on

    KeybindManager::instance().register_default_bindings(actions);
}


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

bool InputContext::matches(
    const std::string& action_id,
    snail::Key key,
    snail::ModKey modifiers)
{
    if (available_actions.find(action_id) == available_actions.end())
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

optional<std::string> InputContext::action_for_key(const Keybind& keybind)
{
    // The set is sorted by insertion order, so entries from categories inserted
    // earlier will receive priority.
    for (const auto& action_id : available_actions)
    {
        const auto& binding = KeybindManager::instance().binding(action_id);
        if (binding.matches(keybind))
        {
            return action_id;
        }
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
        // TODO: is keywait still needed after input_context.reset()?
        if (matches("escape", key, modifiers) && keywait == 0)
        {
            return "cancel"s;
        }

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

bool InputContext::is_nonmovement_key(const snail::Key& k)
{
    return (keybind_is_bindable_key(k) || k == snail::Key::enter)
        && excluded_keys.find(k) == excluded_keys.end();
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

InputContext make_input_context(ActionCategory category)
{
    InputContext result;
    result.add_actions_from_category(ActionCategory::default_);
    if (game_data.wizard)
    {
        result.add_actions_from_category(ActionCategory::wizard);
    }
    result.add_actions_from_category(category);

    // TODO exclude movement keys

    return result;
}

void InputContext::add_actions_from_category(ActionCategory category)
{
    for (const auto& pair : keybind::actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        if (action.category == category)
        {
            add_action(action_id);
        }
    }
}

void InputContext::add_action(const std::string& action)
{
    available_actions.insert(action);
}

std::string InputContext::delay_movement_action(
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

std::string InputContext::delay_normal_action(const std::string& action)
{
    if (action == "" || last_action_ != action)
    {
        last_action_held_frames_ = 0;
    }

    bool delayed = _is_keypress_delayed(last_action_held_frames_, 1, 20);

    last_action_held_frames_++;

    if (last_action_ != action)
    {
        last_action_ = action;
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

    if (const auto action = check_movement_action(keys, modifiers))
    {
        last_action_ = ""s;

        // Movement keys have special key delay behavior, so handle them.
        auto result = delay_movement_action(*action, modifiers, delay_type);
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
    auto command = check_for_command(KeyWaitDelay::always);
    if (command == "north"s)
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
    if (command == "south"s)
    {
        snd(5);
        ++cs;
        if (cs >= keyrange)
        {
            cs = 0;
        }
    }
    if (command == "west"s)
    {
        command = "previous_page"s;
    }
    if (command == "east"s)
    {
        command = "next_page"s;
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
    if (command == "enter"s)
    {
        list_index = cs;
    }
    else if (keybind_action_has_category(command, ActionCategory::selection))
    {
        list_index = keybind_id_number(command);
    }
    else
    {
        list_index = -1;
    }
    return command;
}

void InputContext::reset()
{
    snail::Input::instance().clear_pressed_keys();
    last_action_held_frames_ = 0;
    last_action_ = ""s;
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
