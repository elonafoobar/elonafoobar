#include "keybind_deserializer.hpp"

#include <iostream>
#include <string>

#include "keybind.hpp"
#include "keybind_manager.hpp"



namespace elona
{

namespace
{

optional<Keybind> _deserialize_keybind(
    const json5::value& value,
    const std::string& id)
{
    if (!value.is_object())
        return none;

    const auto& obj = value.get_object();
    const auto itr = obj.find(id);

    if (itr != std::end(obj) && itr->second.is_string())
    {
        if (auto keybind = Keybind::from_string(itr->second.get_string()))
        {
            return keybind;
        }
    }
    return none;
}



optional<snail::Key> _deserialize_key(
    const json5::value& value,
    const std::string& id)
{
    if (!value.is_object())
        return none;

    const auto& obj = value.get_object();
    const auto itr = obj.find(id);

    if (itr != std::end(obj) && itr->second.is_string())
    {
        if (auto key = keybind_key_code(itr->second.get_string()))
        {
            return key;
        }
    }
    return none;
}

} // namespace



void KeybindDeserializer::load(std::istream& in)
{
    std::string file_content{std::istreambuf_iterator<char>{in},
                             std::istreambuf_iterator<char>{}};
    const auto value = json5::parse(file_content);

    visit_object(value.get_object().find("core")->second.get_object());
}



void KeybindDeserializer::visit_object(const json5::value::object_type& object)
{
    for (const auto& pair : object)
    {
        const auto& key = pair.first;
        const auto& value = pair.second;
        if (value.is_object())
        {
            visit_keybinding(key, value);
        }
    }
}



void KeybindDeserializer::visit_keybinding(
    const std::string& action_id,
    const json5::value& object)
{
    if (!_keybind_manager.is_registered(action_id))
    {
        return;
    }

    auto& binding = _keybind_manager.binding(action_id);

    if (auto keybind = _deserialize_keybind(object, "primary"))
    {
        binding.primary = *keybind;
    }

    if (auto keybind = _deserialize_keybind(object, "alternate"))
    {
        binding.alternate = *keybind;
    }

    if (auto key = _deserialize_key(object, "joystick"))
    {
        binding.joystick = *key;
    }
}

} // namespace elona
