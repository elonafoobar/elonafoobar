#pragma once
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../optional.hpp"
#include "../snail/input.hpp"

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
};

struct Action
{
    Action(
        std::string id,
        std::string category,
        std::vector<Keybind> default_keybinds)
        : id(id)
        , description_key("")
        , category(category)
        , default_keybinds(default_keybinds)
        , visible(true)
    {
    }

    std::string id;
    std::string description_key;
    std::string category;
    std::vector<Keybind> default_keybinds;
    bool visible;
};

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
    using MapType = std::unordered_map<std::string, KeybindConfig>;
    using iterator = MapType::iterator;
    using const_iterator = MapType::const_iterator;

    const_iterator begin() const
    {
        return std::begin(keybind_configs_);
    }

    const_iterator end() const
    {
        return std::end(keybind_configs_);
    }

    KeybindConfig& binding(const std::string& action_id)
    {
        if (keybind_configs_.find(action_id) == keybind_configs_.end())
        {
            keybind_configs_[action_id] = KeybindConfig{};
        }

        return keybind_configs_.at(action_id);
    }

private:
    MapType keybind_configs_;
};

class InputContext
{
public:
    void clear();

    /**
     * Adds an action that can be activated in this input context.
     *
     * @param action
     */
    void add_action(const std::string& action);

    /**
     * Adds all actions that are a part of the given category.
     *
     * @param action
     */
    void add_actions_from_category(const std::string& category);

    /**
     * Queries and sets input by translating raw input into a game action
     * through a keybinding.
     *
     * @return An action if one could be mapped from input, none otherwise.
     */
    std::string check_for_command();

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
        snail::ModKey modifiers);

    std::string delay_normal_action(const std::string& action);

    std::set<std::string> available_actions;

    // Keys which shouldn't be returned in get_key() because they have special
    // key delay rules. It can differ depending on the current keybinding setup
    // because movement keys can be rebound.
    std::unordered_set<snail::Key> excluded_keys;

    std::string last_action_;
    int last_action_held_frames_;
};

void init_actions();
InputContext make_input_context(const std::string& category);
bool keybind_is_bindable_key(snail::Key key);
bool keybind_is_joystick_key(snail::Key key);

extern KeybindManager keybind_manager;


} // namespace elona
