#include "keybind.hpp"

namespace elona
{

namespace keybind
{
ActionMap actions;
} // namespace keybind


void initialize_keybind_actions(ActionMap& actions)
{
    using namespace snail;
    using namespace keybind;

    actions.clear();

    // NOTE: In this table, don't use keys for which no physical keycode exists.
    // For example, instead of {Key::question, ModKey::none}, use {Key::slash,
    // ModKey::shift} as [Shift]+[/] = [?]. Key::question would never be picked
    // up as a pressed key, it would always be interpreted as Key::slash +
    // ModKey::shift.

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
    actions.emplace("switch_mode_2",       Action{ActionCategory::menu,      {{Key::keypad_asterisk, ModKey::none}}});
    actions.emplace("identify",            Action{ActionCategory::menu,      {{Key::key_x,           ModKey::none}}});
    actions.emplace("portrait",            Action{ActionCategory::menu,      {{Key::key_p,           ModKey::none}}});

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
    actions.emplace("go_down",             Action{ActionCategory::game,      {{Key::period,          ModKey::shift}}});
    actions.emplace("go_up",               Action{ActionCategory::game,      {{Key::comma,           ModKey::shift}}});
    actions.emplace("save",                Action{ActionCategory::game,      {{Key::key_s,           ModKey::shift}}});
    actions.emplace("search",              Action{ActionCategory::game,      {{Key::key_s,           ModKey::none}}});
    actions.emplace("interact",            Action{ActionCategory::game,      {{Key::key_i,           ModKey::none}}});
    actions.emplace("skill",               Action{ActionCategory::game,      {{Key::key_a,           ModKey::none}}});
    actions.emplace("close",               Action{ActionCategory::game,      {{Key::key_c,           ModKey::shift}}});
    actions.emplace("rest",                Action{ActionCategory::game,      {{Key::key_r,           ModKey::shift}}});
    actions.emplace("target",              Action{ActionCategory::game,      {{Key::keypad_asterisk, ModKey::none}}});
    actions.emplace("dig",                 Action{ActionCategory::game,      {{Key::key_d,           ModKey::shift}}});
    actions.emplace("use",                 Action{ActionCategory::game,      {{Key::key_t,           ModKey::none}}});
    actions.emplace("bash",                Action{ActionCategory::game,      {{Key::key_b,           ModKey::none}}});
    actions.emplace("open",                Action{ActionCategory::game,      {{Key::key_o,           ModKey::none}}});
    actions.emplace("dip",                 Action{ActionCategory::game,      {{Key::key_b,           ModKey::shift}}});
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
    actions.emplace("help",                Action{ActionCategory::game,      {{Key::slash,           ModKey::shift}}});
    actions.emplace("message_log",         Action{ActionCategory::game,      {{Key::slash,           ModKey::none}}});
    actions.emplace("chat_box",            Action{ActionCategory::game,      {{Key::tab,             ModKey::none}}});
    actions.emplace("tcg",                 Action{ActionCategory::game,      {{Key::f3,              ModKey::none}}});
    actions.emplace("update_screen",       Action{ActionCategory::game,      {{Key::f9,              ModKey::none}}});
    actions.emplace("dump_player_info",    Action{ActionCategory::game,      {{Key::f11,             ModKey::none}}});
    actions.emplace("enable_voldemort",    Action{ActionCategory::game,      {{Key::f12,             ModKey::none}}});
    actions.emplace("reload_autopick",     Action{ActionCategory::game,      {{Key::backspace,       ModKey::shift}}});
    actions.emplace("auto_action",         Action{ActionCategory::game,      {{Key::enter,           ModKey::none}}});

    actions.emplace("wizard_mewmewmew",    Action{ActionCategory::wizard,    {{Key::f3,              ModKey::none}}});
    actions.emplace("wizard_wish",         Action{ActionCategory::wizard,    {{Key::f5,              ModKey::none}}});
    actions.emplace("wizard_advance_time", Action{ActionCategory::wizard,    {{Key::f6,              ModKey::none}}});
    actions.emplace("wizard_delete_map",   Action{ActionCategory::wizard,    {{Key::f7,              ModKey::none}}});
    // clang-format on
}

} // namespace elona
