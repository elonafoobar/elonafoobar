#pragma once

#include <iosfwd>
#include "../../snail/input.hpp"
#include "../../thirdparty/json5/json5.hpp"
#include "../optional.hpp"



namespace elona
{

struct Keybind;
class KeybindManager;



class KeybindDeserializer
{
public:
    KeybindDeserializer(KeybindManager& keybind_manager)
        : _keybind_manager(keybind_manager)
    {
    }



    void load(std::istream& in);



private:
    KeybindManager& _keybind_manager;


    void visit_object(const json5::value::object_type& object);
    void visit_keybinding(
        const std::string& action_id,
        const json5::value& object);
};

} // namespace elona
