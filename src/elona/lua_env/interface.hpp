#pragma once

#include <iostream>

#include "../../util/strutil.hpp"
#include "../data/id.hpp"
#include "api_manager.hpp"
#include "handle_manager.hpp"
#include "lua_env.hpp"
#include "wrapped_function.hpp"



/**
 * Simpler interface for using the global LuaEnv instance to call mod-related
 * things.
 */
namespace elona::lua
{

class ConfigTable;



namespace detail
{

/***
 * Obtains a Lua callback where name is like
 * "<mod_id>.<namespaces>", if it exists.
 */
inline optional<WrappedFunction> get_exported_function(const std::string& name)
{
    const auto names = strutil::split(name, '.');
    assert(1 < names.size());
    sol::table t = lua::lua->get_api_manager().get_master_api_table();
    for (size_t i = 0; i < names.size() - 1; ++i)
    {
        if (auto next_t = t.get<sol::optional<sol::table>>(names.at(i)))
        {
            t = *next_t;
        }
        else
        {
            return none;
        }
    }

    if (auto func = t.get<sol::optional<sol::protected_function>>(names.back()))
    {
        return WrappedFunction{name, *func};
    }
    else
    {
        return none;
    }
}

} // namespace detail



/**
 * Calls a Lua exported function, printing any errors that may have occurred
 * with txt().
 */
template <typename... Args>
void call(const std::string& name, Args... args)
{
    try
    {
        if (auto func = detail::get_exported_function(name))
        {
            func->call_unsafely(std::forward<Args>(args)...);
        }
        else
        {
            throw std::runtime_error(
                "Script callback error (" + name +
                "): no such exported function was found");
        }
    }
    catch (const std::exception& e)
    {
        std::string message =
            "Script callback error (" + name + "): " + e.what();
        txt(message, Message::color{ColorIndex::red});
        std::cerr << message << std::endl;
    }
}

/**
 * Calls a Lua exported function, printing any errors that may have occurred
 * with txt().
 */
template <typename Retval, typename... Args>
Retval
call_with_result(const std::string& name, Retval default_value, Args... args)
{
    if (auto func = detail::get_exported_function(name))
    {
        return func->call_with_result(
            default_value, std::forward<Args>(args)...);
    }
    else
    {
        std::string message = "Script callback error (" + name +
            "): no such exported function was "
            "found";

        txt(message, Message::color{ColorIndex::red});
        std::cerr << message << std::endl;
        return default_value;
    }
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
    return lua::lua->get_handle_manager().get_ref(handle);
}

/**
 * Obtains a reference to the C++ data pointed to by a handle.
 */
template <typename T>
T& ref(sol::table handle)
{
    auto result = lua::lua->get_handle_manager().get_ref(handle);
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
optional<ConfigTable> get_data(
    data::PrototypeId prototype_id,
    data::InstanceId instance_id);

/**
 * Obtains a Lua table reference to a data member in the global data table.
 */
optional<ConfigTable> get_data(
    data::PrototypeId prototype_id,
    int integer_instance_id);

fs::path resolve_path_for_mod(const std::string& path);


// List mod directories under `base_dir`.
std::vector<fs::path> all_mod_dirs(const fs::path& base_dir);

} // namespace elona::lua
