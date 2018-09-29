#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../enums.hpp"
#include "../optional.hpp"
#include "../snail/input.hpp"
#include "../thirdparty/ordered_map/ordered_map.h"

using namespace std::literals::string_literals;

namespace elona
{

// keybind requirements
// - separation of actions into contexts
// - separation of bindings per mod and per context
// - binding one key to multiple actions in different contexts
// - support for alt, ctrl and win meta keys (at most one)
// - serializing keys to and from strings
// - joypad handling
// - interop with cursor_check()
// - ability to add new actions/default bindings
// - inner macro support
// - handling of shortcuts
// - serialization to separate keybinds.hcl file per-mod

// input context requirements
// - "keys pressed this frame" support in snail
// - unobtrusive API for creating a commonly used input context
// - handling the complex keywait statements in a cleaner manner
// - handling movement modification via alt/shift modifiers
// - handling of shortcuts

// contexts
// - main game input
// - ui menu
// - input with number


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

struct KeybindConfig
{
    Keybind primary{};
    Keybind alternate{};
    snail::Key joystick = snail::Key::none;

    // This keybind should never be able to be unset.
    Keybind permanent{};

    bool matches(const Keybind& keybind) const
    {
        return primary == keybind || alternate == keybind
            || joystick == keybind.main || permanent == keybind;
    }
};

class KeybindManager
{
public:
    using MapType = tsl::ordered_map<std::string, KeybindConfig>;
    using GroupedMapType = std::multimap<ActionCategory, std::string>;
    using iterator = MapType::iterator;
    using const_iterator = MapType::const_iterator;
    using size_type = MapType::size_type;

    static KeybindManager& instance();

    const_iterator begin() const
    {
        return std::begin(_keybind_configs);
    }

    const_iterator end() const
    {
        return std::end(_keybind_configs);
    }

    GroupedMapType create_category_to_action_list();

    void register_binding(const std::string& action_id)
    {
        _keybind_configs.emplace(action_id, KeybindConfig{});
    }

    bool is_registered(const std::string& action_id)
    {
        return _keybind_configs.find(action_id) != _keybind_configs.end();
    }

    void clear_binding(const std::string& action_id);

    void register_default_bindings(const ActionMap& actions);

    std::vector<std::string> find_conflicts(
        const std::string& action_id,
        const Keybind& keybind);

    KeybindConfig& binding(const std::string& action_id)
    {
        if (!is_registered(action_id))
        {
            throw std::runtime_error(
                "Binding for action "s + action_id + " not registered"s);
        }

        return _keybind_configs.at(action_id);
    }

private:
    MapType _keybind_configs;
};

class InputContext
{
public:
    void clear();

    /**
     * Adds an action that can be activated in this input context.
     */
    void add_action(const std::string& action);

    /**
     * Adds all actions that are a part of the given category.
     */
    void add_actions_from_category(ActionCategory category);

    /**
     * Queries and sets input by translating raw input into a game action
     * through a keybinding.
     *
     * @param delay_type Type of delay to use when holding keys.
     *
     * @return An action if one could be mapped from input, none otherwise.
     */
    std::string check_for_command(
        KeyWaitDelay delay_type = KeyWaitDelay::always);

    /**
     * Queries and translates input into an action, or sets list_index to a
     * number other than -1 based on the size of the global list/listn.
     * Keybindings are given higher priority than the list selection keys.
     *
     * @param list_index A list index to use.
     *
     * @return An action if one could be mapped from input, none otherwise.
     */
    std::string check_for_command_with_list(int& list_index);

    /**
     * Resets this context and the pressed input keys so keys that are held at
     * this point will no longer be counted as pressed.
     */
    void reset();

private:
    bool matches(
        const std::string& action_id,
        snail::Key key,
        snail::ModKey modifiers);

    // TODO move to keybind manager
    optional<std::string> action_for_key(const Keybind& keybind);

    optional<std::string> check_movement_action(
        const std::set<snail::Key>& keys,
        snail::ModKey modifiers);

    bool is_nonmovement_key(const snail::Key& k);

    optional<Keybind> check_key();

    std::string delay_movement_action(
        const std::string& action,
        snail::ModKey modifiers,
        KeyWaitDelay delay_type);

    std::string delay_normal_action(const std::string& action);

    // In insertion order, to give precedence to certain categories.
    std::set<std::string> available_actions;

    std::unordered_set<std::string> excluded_categories;

    // Keys which shouldn't be returned in get_key() because they have special
    // key delay rules. It can differ depending on the current keybinding setup
    // because movement keys can be rebound.
    std::unordered_set<snail::Key> excluded_keys;

    std::string last_action_;
    int last_action_held_frames_;
};

void init_actions();

InputContext make_input_context(ActionCategory category);

bool keybind_is_bindable_key(snail::Key key);
bool keybind_is_joystick_key(snail::Key key);

optional<std::string> keybind_key_name(snail::Key key, bool shift = false);
optional<snail::Key> keybind_key_code(
    const std::string& name,
    bool shift = false);

bool keybind_action_has_category(
    const std::string& action_id,
    ActionCategory category);

/**
 * For selection and shortcut actions, returns the integer index of the
 * selection item/shortcut.
 *
 * Never to be used for other actions, since it assumes the action ID has the
 * format <prefix>_<number>.
 */
int keybind_id_number(const std::string& action_id);

} // namespace elona
