#pragma once
#include <string>
#include "../enums.hpp"
#include "../filesystem.hpp"
#include "../variables.hpp"
#include "exported_function.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;

/***
 * Stores references to Lua functions that can be provided by mods by
 * providing an Exports table in its returned API table.
 *
 * This allows doing things like specifying what should happen when a
 * corpse is eaten, a trap is activated, and so forth, without having
 * to hardcode anything in C++.
 */
class ExportManager
{
public:
    explicit ExportManager(LuaEnv*);

    /***
     * Registers function exports that are inside the "Exports" table
     * inside the API tables returned by mods. They will then be
     * accessable by the id
     *
     * "exports:<mod_name>.<namespaces>.<...>"
     *
     * corresponding to the nested table layout of the Exports table.
     */
    void register_all_exports();

    /***
     * Obtains a Lua callback where name is like
     * "exports:<mod_name>.<namespaces>", if it exists.
     */
    optional<ExportedFunction> get_exported_function(
        const std::string& name) const;

    bool has_function(const std::string& name) const
    {
        return static_cast<bool>(get_exported_function(name));
    }

    template <typename... Args>
    void call(const std::string& name, Args&&... args) const
    {
        if (auto func = get_exported_function(name))
        {
            func->call(std::forward<Args>(args)...);
        }
        else
        {
            txtef(ColorIndex::red);
            txt(name + ": Script callback error: no such exported function was found");
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
            txtef(ColorIndex::red);
            txt(name + ": Script callback error: no such exported function was found");
            return default_value;
        }
    }

private:
    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment export_env;

    LuaEnv* lua_;
};

} // namespace lua
} // namespace elona
