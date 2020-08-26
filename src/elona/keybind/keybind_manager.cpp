#include "keybind_manager.hpp"

#include "../../util/strutil.hpp"
#include "../filesystem.hpp"
#include "../variables.hpp"
#include "keybind.hpp"
#include "keybind_deserializer.hpp"
#include "keybind_serializer.hpp"



namespace elona
{

namespace
{

std::string _binding_name(
    KeybindManager& keybind_manager,
    const std::string& action_id)
{
    if (!keybind_manager.is_registered(action_id))
    {
        return "";
    }

    std::string result = "";
    auto& binding = keybind_manager.binding(action_id);
    if (!binding.primary.empty())
    {
        result = binding.primary.to_string();
    }
    if (result == "" && !binding.alternate.empty())
    {
        result = binding.primary.to_string();
    }
    if (result == "" && binding.joystick != snail::Key::none)
    {
        if (auto name_opt = keybind_key_name(binding.joystick))
        {
            result = *name_opt;
        }
    }

    strutil::try_remove_prefix(result, "Keypad ");
    return result;
}

} // namespace



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



void KeybindManager::save()
{
    const auto path = filesystem::files::keybinding_config();
    std::ofstream file{path.native(), std::ios::binary};
    if (!file)
    {
        throw std::runtime_error{u8"Failed to open: "s + path.to_u8string()};
    }

    KeybindSerializer(*this).save(file);
}



void KeybindManager::load()
{
    clear();

    const auto path = filesystem::files::keybinding_config();
    std::ifstream file{path.native(), std::ios::binary};

    if (file)
    {
        initialize_known_actions(keybind::actions);
        load_permanent_bindings(keybind::actions);
        KeybindDeserializer(*this).load(file);
    }
    else
    {
        load_default_bindings(keybind::actions);
        save();
    }
}



void KeybindManager::initialize_known_actions(const ActionMap& actions)
{
    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;

        register_binding(action_id);
    }
}



void KeybindManager::load_permanent_bindings(const ActionMap& actions)
{
    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

        auto& the_binding = binding(action_id);
        for (const auto& keybind : action.default_keybinds)
        {
            if (!keybind_is_bindable_key(keybind.main))
            {
                // Permanently bind keys that shouldn't be unbound (escape,
                // enter, and directional keys)
                the_binding.permanent = keybind;
            }
        }
    }
}



void KeybindManager::load_default_bindings(const ActionMap& actions)
{
    initialize_known_actions(actions);
    load_permanent_bindings(actions);

    for (const auto& pair : actions)
    {
        const auto& action_id = pair.first;
        const auto& action = pair.second;

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
        }
    }
}



std::vector<std::string> KeybindManager::find_conflicts(
    const std::string& action_id,
    const Keybind& keybind)
{
    auto action_category = keybind::actions.at(action_id).category;
    std::vector<std::string> conflicts;

    auto can_conflict_with =
        keybind_conflicting_action_categories(action_category);

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



std::string keybind_get_bound_key_name(const std::string& action)
{
    auto& km = KeybindManager::instance();
    return _binding_name(km, action);
}

} // namespace elona
