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

#define K(type)       {Key::type, ModKey::none}
#define SHIFT_K(type) {Key::type, ModKey::shift}
#define CTRL_K(type)  {Key::type, ModKey::ctrl}

#define BIND(action_name, ...) \
    actions.emplace(#action_name, Action{ \
        ActionCategory::CATEGORY, \
        { __VA_ARGS__ }, \
    })

#define CATEGORY default_

    BIND(escape,     K(escape) );
    BIND(cancel,     K(shift)  );
    BIND(enter,      K(enter),    K(keypad_enter) );
    BIND(north,      K(up),       K(keypad_8)     );
    BIND(south,      K(down),     K(keypad_2)     );
    BIND(east,       K(left),     K(keypad_4)     );
    BIND(west,       K(right),    K(keypad_6)     );
    BIND(northwest,  K(home),     K(keypad_7)     );
    BIND(northeast,  K(pageup),   K(keypad_9)     );
    BIND(southwest,  K(end),      K(keypad_1)     );
    BIND(southeast,  K(pagedown), K(keypad_3)     );

#undef CATEGORY
#define CATEGORY shortcut

    BIND(shortcut_1,   K(key_1) );
    BIND(shortcut_2,   K(key_2) );
    BIND(shortcut_3,   K(key_3) );
    BIND(shortcut_4,   K(key_4) );
    BIND(shortcut_5,   K(key_5) );
    BIND(shortcut_6,   K(key_6) );
    BIND(shortcut_7,   K(key_7) );
    BIND(shortcut_8,   K(key_8) );
    BIND(shortcut_9,   K(key_9) );
    BIND(shortcut_10,  K(key_0) );
    BIND(shortcut_11,  CTRL_K(key_1), SHIFT_K(key_1) );
    BIND(shortcut_12,  CTRL_K(key_2), SHIFT_K(key_2) );
    BIND(shortcut_13,  CTRL_K(key_3), SHIFT_K(key_3) );
    BIND(shortcut_14,  CTRL_K(key_4), SHIFT_K(key_4) );
    BIND(shortcut_15,  CTRL_K(key_5), SHIFT_K(key_5) );
    BIND(shortcut_16,  CTRL_K(key_6), SHIFT_K(key_6) );
    BIND(shortcut_17,  CTRL_K(key_7), SHIFT_K(key_7) );
    BIND(shortcut_18,  CTRL_K(key_8), SHIFT_K(key_8) );
    BIND(shortcut_19,  CTRL_K(key_9), SHIFT_K(key_9) );
    BIND(shortcut_20,  CTRL_K(key_0), SHIFT_K(key_0) );

#undef CATEGORY
#define CATEGORY selection

    BIND(select_1,   K(key_a) );
    BIND(select_2,   K(key_b) );
    BIND(select_3,   K(key_c) );
    BIND(select_4,   K(key_d) );
    BIND(select_5,   K(key_e) );
    BIND(select_6,   K(key_f) );
    BIND(select_7,   K(key_g) );
    BIND(select_8,   K(key_h) );
    BIND(select_9,   K(key_i) );
    BIND(select_10,  K(key_j) );
    BIND(select_11,  K(key_k) );
    BIND(select_12,  K(key_l) );
    BIND(select_13,  K(key_m) );
    BIND(select_14,  K(key_n) );
    BIND(select_15,  K(key_o) );
    BIND(select_16,  K(key_p) );
    BIND(select_17,  K(key_q) );
    BIND(select_18,  K(key_r) );
    BIND(select_19,  K(key_s) );

#undef CATEGORY
#define CATEGORY menu

    BIND(next_page,      K(keypad_plus)     );
    BIND(previous_page,  K(keypad_minus)    );
    BIND(next_menu,      K(tab)             );
    BIND(previous_menu,  CTRL_K(tab)        );
    BIND(switch_mode,    K(key_z)           );
    BIND(switch_mode_2,  K(keypad_asterisk) );
    BIND(identify,       K(key_x)           );
    BIND(portrait,       K(key_p)           );

#undef CATEGORY
#define CATEGORY game

    BIND(wait,              K(period),          K(keypad_5) );
    BIND(quick_menu,        K(key_z)       );
    BIND(zap,               SHIFT_K(key_z) );
    BIND(quick_inventory,   K(key_x)       );
    BIND(inventory,         SHIFT_K(key_x) );
    BIND(get,               K(key_g),           K(keypad_0) );
    BIND(drop,              K(key_d)       );
    BIND(chara_info,        K(key_c)       );
    BIND(eat,               K(key_e)       );
    BIND(wear,              K(key_w)       );
    BIND(cast,              K(key_v)       );
    BIND(drink,             K(key_q)       );
    BIND(read,              K(key_r)       );
    BIND(fire,              K(key_f)       );
    BIND(go_down,           SHIFT_K(period) );
    BIND(go_up,             SHIFT_K(comma) );
    BIND(save,              SHIFT_K(key_s) );
    BIND(search,            K(key_s)       );
    BIND(interact,          K(key_i)       );
    BIND(skill,             K(key_a)       );
    BIND(close,             SHIFT_K(key_c) );
    BIND(rest,              SHIFT_K(key_r) );
    BIND(target,            K(keypad_asterisk), SHIFT_K(colon) );
    BIND(dig,               SHIFT_K(key_d) );
    BIND(use,               K(key_t)       );
    BIND(bash,              K(key_b)       );
    BIND(open,              K(key_o)       );
    BIND(dip,               SHIFT_K(key_b) );
    BIND(pray,              K(key_p)       );
    BIND(offer,             SHIFT_K(key_o) );
    BIND(journal,           K(key_j)       );
    BIND(material,          K(key_m)       );
    BIND(trait,             SHIFT_K(key_f) );
    BIND(look,              K(key_l)       );
    BIND(give,              SHIFT_K(key_g) );
    BIND(throw,             SHIFT_K(key_t) );
    BIND(ammo,              SHIFT_K(key_a) );
    BIND(autodig,           SHIFT_K(key_h) );
    BIND(quicksave,         K(f1)          );
    BIND(quickload,         K(f2)          );
    BIND(help,              SHIFT_K(slash) );
    BIND(message_log,       K(slash)       );
    BIND(chat_box,          K(tab)         );
    BIND(tcg,               K(f3)          );
    BIND(update_screen,     K(f9)          );
    BIND(dump_player_info,  K(f11)         );
    BIND(reload_autopick,   SHIFT_K(backspace) );
    BIND(screenshot,        K(printscreen) );
    BIND(toggle_console,    K(f12)         );
    BIND(open_console,      SHIFT_K(f12)   );

#undef CATEGORY
#define CATEGORY wizard

    BIND(wizard_mewmewmew,     K(f3) );
    BIND(wizard_wish,          K(f5) );
    BIND(wizard_advance_time,  K(f6) );
    BIND(wizard_delete_map,    K(f7) );

    // clang-format on
}

} // namespace elona
