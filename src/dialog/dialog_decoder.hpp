#pragma once
#include <string>
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{

namespace lua
{
class lua_env;
}

class dialog_data;

class dialog_decoder
{
public:
    optional<dialog_data> decode(const std::string& id);
    optional<dialog_data> decode(const std::string& id, lua::lua_env& lua);

private:
    dialog_data decode(sol::table data, lua::lua_env& lua);
};

} // namespace elona
