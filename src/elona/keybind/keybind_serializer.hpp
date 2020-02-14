#pragma once

#include <iosfwd>
#include <string>

#include "../optional.hpp"



namespace elona
{

namespace snail
{
enum class Key;
}



struct Keybind;
class KeybindManager;



class KeybindSerializer
{
public:
    KeybindSerializer(KeybindManager& keybind_manager)
        : _keybind_manager(keybind_manager)
    {
    }



    void save(std::ostream& out);



private:
    optional<std::string> _serialize_keybind(const Keybind& keybind);
    optional<std::string> _serialize_joystick_key(snail::Key key);
    KeybindManager& _keybind_manager;
};

} // namespace elona
