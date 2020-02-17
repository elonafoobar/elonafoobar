#include "keybind_serializer.hpp"

#include <iostream>

#include "../../thirdparty/json5/json5.hpp"
#include "keybind.hpp"
#include "keybind_manager.hpp"



namespace elona
{

void KeybindSerializer::save(std::ostream& out)
{
    // Top level object.
    json5::value::object_type keybindings;

    // "core" section.
    json5::value::object_type core;

    // Create sections under the top-level object for each mod
    // that has keybindings (for now, only "core"), then write their individual
    // config sections.
    for (const auto& pair : _keybind_manager)
    {
        const auto& action_id = pair.first;
        const auto& binding = pair.second;

        // Add a new section for this action.
        json5::value::object_type object;
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
            core.emplace(action_id, object);
        }
    }

    keybindings.emplace("core", core);
    json5::stringify_options opts;
    opts.prettify = true;
    opts.sort_by_key = true;
    opts.unquote_key = true;
    opts.insert_trailing_comma = true;
    out << json5::stringify(keybindings, opts);
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
