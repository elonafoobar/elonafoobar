#include "keybind_serializer.hpp"
#include <iostream>
#include "../hcl.hpp"
#include "keybind.hpp"

namespace elona
{

void KeybindSerializer::save(std::ostream& out)
{
    // Create a top level "keybindings" section.
    hcl::Value keybindings = hcl::Value(hcl::Object());
    keybindings.set("keybindings", hcl::Object());
    hcl::Value* parent = keybindings.find("keybindings");
    assert(parent);

    // Create "core" section.
    parent->set("core", hcl::Object());
    parent = parent->find("core");
    assert(parent);

    // Create sections under the top-level "keybindings" section for each mod
    // that has keybindings (for now, only "core"), then write their individual
    // config sections.
    for (const auto& pair : _keybind_manager)
    {
        const auto& action_id = pair.first;
        const auto& binding = pair.second;

        // Add a new section for this action.
        hcl::Object object;
        bool valid = false;

        // Set primary, alternate and joystick bindings.
        if (auto str = _serialize_keybind(binding.primary))
        {
            object.emplace("primary", *str);
            valid = true;
        }
        if (auto str = _serialize_keybind(binding.alternate))
        {
            object.emplace("alternate", *str);
            valid = true;
        }
        if (auto str = _serialize_joystick_key(binding.joystick))
        {
            object.emplace("joystick", *str);
            valid = true;
        }

        if (valid)
        {
            parent->set(action_id, object);
        }
    }

    out << keybindings;
}

optional<std::string> KeybindSerializer::_serialize_keybind(
    const Keybind& keybind)
{
    if (!keybind_is_bindable_key(keybind.main))
    {
        return none;
    }

    return keybind.to_string();
}

optional<std::string> KeybindSerializer::_serialize_joystick_key(snail::Key key)
{
    if (!keybind_is_joystick_key(key))
    {
        return none;
    }

    return keybind_key_name(key);
}

} // namespace elona
