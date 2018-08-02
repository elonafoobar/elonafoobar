#pragma once
#include <string>
#include "../filesystem.hpp"
#include "exported_function.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class lua_env;

/***
 * Stores references to Lua functions that can be provided by mods by
 * providing an Exports table in its returned API table.
 *
 * This allows doing things like specifying what should happen when a
 * corpse is eaten, a trap is activated, and so forth, without having
 * to hardcode anything in C++.
 */
class export_manager
{
public:
    explicit export_manager(lua_env*);

    /***
     * Registers function exports that are inside the "Exports" table
     * inside the API tables returned by mods. They will then be
     * accessable by the id
     *
     * "<mod_name>.exports.<namespaces>.<...>"
     *
     * corresponding to the nested table layout of the Exports table.
     */
    void register_all_exports();

    /***
     * Obtains a Lua callback of the format "core.exports.<name>", if
     * it exists.
     */
    optional<exported_function> get_exported_function(
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
    }

private:
    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment export_env;

    lua_env* lua_;
};

} // namespace lua
} // namespace elona
