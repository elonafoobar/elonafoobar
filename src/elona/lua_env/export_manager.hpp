#pragma once

#include <iostream>
#include <string>

#include "../enums.hpp"
#include "../filesystem.hpp"
#include "../message.hpp"
#include "../variables.hpp"
#include "lua_submodule.hpp"
#include "wrapped_function.hpp"



namespace elona
{
namespace lua
{

/***
 * Stores references to Lua functions that can be provided by mods by
 * providing an Exports table in its returned API table.
 *
 * This allows doing things like specifying what should happen when a
 * corpse is eaten, a trap is activated, and so forth, without having
 * to hardcode anything in C++.
 */
class ExportManager : public LuaSubmodule
{
public:
    explicit ExportManager(LuaEnv&);

    /***
     * Registers function exports that are inside the "Exports" table
     * inside the API tables returned by mods. They will then be
     * accessable by the id
     *
     * "<mod_id>.<namespaces>.<...>"
     *
     * corresponding to the nested table layout of the Exports table.
     */
    void register_all_exports();

    /***
     * Obtains a Lua callback where name is like
     * "<mod_id>.<namespaces>", if it exists.
     */
    optional<WrappedFunction> get_exported_function(
        const std::string& name) const;

    bool has_function(const std::string& name) const
    {
        return static_cast<bool>(get_exported_function(name));
    }

    template <typename... Args>
    void call_unsafely(const std::string& name, Args&&... args) const
    {
        if (auto func = get_exported_function(name))
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

    template <typename... Args>
    void call(const std::string& name, Args&&... args) const
    {
        try
        {
            call_unsafely(name, std::forward<Args>(args)...);
        }
        catch (const std::exception& e)
        {
            std::string message =
                "Script callback error (" + name + "): " + e.what();
            txt(message, Message::color{ColorIndex::red});
            std::cerr << message << std::endl;
        }
    }

    template <typename Retval, typename... Args>
    Retval call_with_result(
        const std::string& name,
        Retval default_value,
        Args&&... args) const
    {
        if (auto func = get_exported_function(name))
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
};

} // namespace lua
} // namespace elona
