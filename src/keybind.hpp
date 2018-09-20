#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <vector>
#include "optional.hpp"
#include "snail/input.hpp"

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
    Keybind(snail::Key main, snail::ModKey modifiers)
        : main(main)
        , modifiers(modifiers)
    {
    }

    // TODO: need serialization of keys to string
    // <up>, <down>, <joy-1>, <joy-x-up>...
    snail::Key main;
    snail::ModKey modifiers;

    bool operator==(const Keybind& other) const noexcept
    {
        return main == other.main && modifiers == other.modifiers;
    }
};

struct Action
{
    Action(
        std::string id,
        std::string category,
        std::vector<Keybind> default_keybinds)
        : id(id)
        , category(category)
        , default_keybinds(default_keybinds)
    {
    }

    std::string id;
    std::string description_key;
    std::string category;
    std::vector<Keybind> default_keybinds;
};

class KeybindManager
{
public:
    optional<std::string> action_to_key(const std::string& action);
    optional<std::string> key_to_action(const std::string& key);
    optional<std::string> key_to_action(const Keybind& binding);

    void unbind(const Keybind& binding);
    void bind(const Keybind& binding, const std::string& action);
    void clear_bindings_for_action(const std::string& action);

private:
    std::multimap<Keybind, std::string> keybinds;
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
    void add_actions_in_category(const std::string& category);

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
    std::unordered_set<std::string> available_actions;

    // Keys which shouldn't be returned in get_key() because they have special
    // key delay rules.
    std::unordered_set<snail::Key> excluded_keys;
};

enum class InputContextType
{

};

InputContext& get_common_input_context(InputContextType type);


} // namespace elona
