#pragma once

#include "../optional.hpp"
#include "lua_submodule.hpp"



namespace elona
{
namespace lua
{

class I18NFunctionManager : public LuaSubmodule
{
public:
    explicit I18NFunctionManager(LuaEnv&);

    void clear();

    void register_function(
        const std::string& language,
        const std::string& name,
        sol::protected_function function);

    optional<sol::protected_function> find_function(const std::string& name);
};

} // namespace lua
} // namespace elona
