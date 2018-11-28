#pragma once
#include "keybind.hpp"

namespace elona
{

class KeybindManager
{
public:
    struct Binding
    {
        Keybind primary{};
        Keybind alternate{};
        snail::Key joystick = snail::Key::none;

        // This keybind should never be able to be unset.
        Keybind permanent{};

        bool matches(const Keybind& keybind) const
        {
            return primary == keybind || alternate == keybind ||
                joystick == keybind.main || permanent == keybind;
        }

        void clear()
        {
            primary.clear();
            alternate.clear();
            joystick = snail::Key::none;
        }

        void bind(Keybind keybind)
        {
            if (keybind_is_joystick_key(keybind.main))
            {
                // Joystick buttons will not use modifier keys.
                joystick = keybind.main;
            }
            else if (primary.empty())
            {
                primary = keybind;
            }
            else if (alternate.empty())
            {
                alternate = keybind;
            }
            else
            {
                // Clear the secondary keybinding first.
                alternate.clear();
                primary = keybind;
            }
        }
    };

public:
    using MapType = tsl::ordered_map<std::string, Binding>;
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

    void clear()
    {
        _keybind_configs.clear();
    }

    GroupedMapType create_category_to_action_list();

    void register_binding(const std::string& action_id)
    {
        _keybind_configs.emplace(action_id, Binding{});
    }

    void initialize_known_actions(const ActionMap& actions);

    bool is_registered(const std::string& action_id)
    {
        return _keybind_configs.find(action_id) != _keybind_configs.end();
    }

    void load_default_bindings(const ActionMap& actions);
    void load_permanent_bindings(const ActionMap& actions);

    std::vector<std::string> find_conflicts(
        const std::string& action_id,
        const Keybind& keybind);

    Binding& binding(const std::string& action_id)
    {
        if (!is_registered(action_id))
        {
            throw std::runtime_error(
                "Binding for action "s + action_id + " not registered"s);
        }

        return _keybind_configs.at(action_id);
    }

    void save();

    void load();

private:
    MapType _keybind_configs;
};

} // namespace elona
