#pragma once
#include <string>
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{

namespace lua
{
class LuaEnv;
}

class DialogData;

class DialogDecoder
{
public:
    optional<DialogData> decode(const std::string& id);
    optional<DialogData> decode(const std::string& id, lua::LuaEnv& lua);

private:
    DialogData decode(sol::table data, lua::LuaEnv& lua);
};

} // namespace elona
