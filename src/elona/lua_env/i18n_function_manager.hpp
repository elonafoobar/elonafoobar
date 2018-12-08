#pragma once
#include <string>
#include "../../thirdparty/sol2/sol.hpp"
#include "../enums.hpp"
#include "../filesystem.hpp"
#include "../variables.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;

class I18NFunctionManager
{
public:
    explicit I18NFunctionManager(LuaEnv*);

    void clear();

    void register_function(
        const std::string& language,
        const std::string& name,
        sol::protected_function function);

    optional<sol::protected_function> find_function(const std::string& name);

private:
    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment i18n_function_env;

    LuaEnv* lua_;
};

} // namespace lua
} // namespace elona
