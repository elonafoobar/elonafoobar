#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../snail/input.hpp"
#include "../../thirdparty/ordered_map/ordered_map.h"
#include "../enums.hpp"
#include "../optional.hpp"

using namespace std::literals::string_literals;

namespace elona
{

struct Keybind
{
    Keybind()
        : main(snail::Key::none)
        , modifiers(snail::ModKey::none)
    {
    }

    Keybind(snail::Key main, snail::ModKey modifiers)
        : main(main)
        , modifiers(modifiers)
    {
    }

    snail::Key main;
    snail::ModKey modifiers;

    bool operator==(const Keybind& other) const noexcept
    {
        return main == other.main && modifiers == other.modifiers;
    }

    bool empty() const
    {
        return main == snail::Key::none;
    }

    std::string to_string() const;

    static optional<Keybind> from_string(std::string str);

    void clear()
    {
        main = snail::Key::none;
        modifiers = snail::ModKey::none;
    }
};

// clang-format off
enum class InputContextType
{
    menu, // [default, shortcut, selection, menu]
    game  // [default, shortcut, game, wizard]
};
// clang-format on

enum class ActionCategory
{
    default_,
    shortcut,
    selection,
    menu,
    game,
    wizard
};

struct Action
{
    Action(ActionCategory category, std::vector<Keybind> default_keybinds)
        : description_key("")
        , category(category)
        , default_keybinds(default_keybinds)
        , visible(true)
    {
    }

    std::string description_key;
    ActionCategory category;
    std::vector<Keybind> default_keybinds;
    bool visible;
};


typedef tsl::ordered_map<std::string, Action> ActionMap;

namespace keybind
{
extern ActionMap actions;
}


void initialize_keybind_actions(ActionMap& actions);
void initialize_keybindings();

optional<std::string> keybind_key_name(snail::Key key, bool shift = false);
std::string keybind_key_short_name(snail::Key key, bool shift = false);
optional<snail::Key> keybind_key_code(
    const std::string& name,
    bool shift = false);
bool keybind_is_bindable_key(snail::Key key);
bool keybind_is_joystick_key(snail::Key key);
bool keybind_action_has_category(
    const std::string& action_id,
    ActionCategory category);
std::unordered_set<ActionCategory> keybind_conflicting_action_categories(
    ActionCategory action_category);

void keybind_regenerate_key_select();

// for key hint
std::string keybind_get_bound_key_name(const std::string& action);


/**
 * Get the text representation of the bound shortcut key's name(s) by action
 * ID. `action_id` must be one of the shortcuts.
 * If the key is number key and has modifier Shift or Ctrl, returns the digit
 * plus 10. Otherwise, returns the key name itself. Even if the shortcut has an
 * alternate binding, returns only the primary one. E.g., if the bound key is...
 * - "1" => "1"
 * - "2" => "2"
 * - "Ctrl+1" or "Shift+1" => "11"
 * - "v" => "v"
 * - "V" => "V"
 */
std::string get_bound_shortcut_key_name_by_action_id(
    const std::string& action_id);

/**
 * Get the text representation of the bound shortcut key's name(s) by
 * shortcut's index. The index is the same as that stored in `Game` or
 * other save data. See also `get_bound_shortcut_key_name_by_action_id` for the
 * detailed format of th return value.
 */
std::string get_bound_shortcut_key_name_by_index(int index);


/**
 * For selection and shortcut actions, returns the integer index of the
 * selection item/shortcut.
 *
 * Never to be used for other actions, since it assumes the action ID has the
 * format <prefix>_<number>.
 */
int keybind_index_number(const std::string& action_id);

/**
 * For selection actions, returns the key bound to the selection action of the
 * given index.
 */
snail::Key keybind_selection_key_from_index(int index);

} // namespace elona
