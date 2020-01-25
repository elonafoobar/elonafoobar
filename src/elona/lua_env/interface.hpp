#pragma once

#include "export_manager.hpp"
#include "handle_manager.hpp"
#include "lua_env.hpp"



/**
 * Simpler interface for using the global LuaEnv instance to call mod-related
 * things.
 */
namespace elona
{
namespace lua
{

class ConfigTable;

/**
 * Calls a Lua exported function, printing any errors that may have occurred
 * with txt().
 */
template <typename... Args>
void call(const std::string& name, Args... args)
{
    lua::lua->get_export_manager().call(name, std::forward<Args>(args)...);
}

/**
 * Calls a Lua exported function, printing any errors that may have occurred
 * with txt().
 */
template <typename Retval, typename... Args>
Retval
call_with_result(const std::string& name, Retval default_value, Args... args)
{
    return lua::lua->get_export_manager().call_with_result(
        name, default_value, std::forward<Args>(args)...);
}

/**
 * Obtains a Lua handle to a compatible C++ object.
 */
template <typename T>
sol::table handle(T& it)
{
    return lua::lua->get_handle_manager().get_handle(it);
}

/**
 * Obtains a reference to the C++ data pointed to by a handle.
 */
template <typename T>
sol::optional<T&> ref_opt(sol::table handle)
{
    return lua::lua->get_handle_manager().get_ref<T>(handle);
}

/**
 * Obtains a reference to the C++ data pointed to by a handle.
 */
template <typename T>
T& ref(sol::table handle)
{
    auto result = lua::lua->get_handle_manager().get_ref<T>(handle);
    if (!result)
    {
        throw sol::error(
            "Handle reference is not valid. Was the object removed?");
    }
    return *result;
}

/**
 * Obtains a Lua handle to a compatible C++ object.
 */
template <typename T>
optional<sol::table> handle_opt(T& it)
{
    auto h = handle(it);
    if (h == sol::lua_nil)
    {
        return none;
    }
    return h;
}

template <typename... Args>
sol::table create_table(Args&&... args)
{
    return lua::lua->get_state()->create_table_with(
        std::forward<Args>(args)...);
}

/**
 * Obtains a Lua table reference to a data member in the global data table.
 */
optional<ConfigTable> data(const char* type, const std::string& id);

/**
 * Obtains a Lua table reference to a data member in the global data table.
 */
optional<ConfigTable> data(const char* type, int legacy_id);

fs::path resolve_path_for_mod(const std::string& path);

} // namespace lua
} // namespace elona
