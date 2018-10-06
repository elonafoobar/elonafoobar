#include "keybind_deserializer.hpp"
#include <iostream>
#include <string>
#include "../hcl.hpp"
#include "keybind.hpp"

namespace elona
{

void KeybindDeserializer::load(std::istream& in)
{
    auto parsed = hclutil::load(in);
    const auto& value = hclutil::skip_sections(
        parsed, {"keybindings", "core"}, "[input stream]");

    visit_object(value.as<hcl::Object>());
}

void KeybindDeserializer::visit_object(const hcl::Object& object)
{
    for (const auto& pair : object)
    {
        const auto& key = pair.first;
        const auto& value = pair.second;
        if (value.is<hcl::Object>())
        {
            visit_keybinding(key, value);
        }
    }
}

void KeybindDeserializer::visit_keybinding(
    const std::string& action_id,
    const hcl::Value& object)
{
    KeybindConfig binding;

    if (!_keybind_manager.is_registered(action_id))
    {
        return;
    }

    bool valid = false;

    {
        const hcl::Value* primary = object.find("primary");
        if (primary && primary->is<std::string>())
        {
            if (auto keybind = Keybind::from_string(primary->as<std::string>()))
            {
                binding.primary = *keybind;
                valid = true;
            }
        }
    }

    {
        const hcl::Value* alternate = object.find("alternate");
        if (alternate && alternate->is<std::string>())
        {
            if (auto keybind =
                    Keybind::from_string(alternate->as<std::string>()))
            {
                binding.alternate = *keybind;
                valid = true;
            }
        }
    }

    {
        const hcl::Value* joystick = object.find("joystick");
        if (joystick && joystick->is<std::string>())
        {
            if (auto key = keybind_key_code(joystick->as<std::string>()))
            {
                binding.joystick = *key;
                valid = true;
            }
        }
    }

    if (valid)
    {
        _keybind_manager.binding(action_id) = binding;
    }
}

} // namespace elona
