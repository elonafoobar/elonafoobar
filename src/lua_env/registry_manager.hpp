#pragma once
#include <string>
#include "../filesystem.hpp"
#include "lua_env.hpp"
#include "exported_function.hpp"

namespace elona
{
namespace lua
{

class lua_env;

/***
 * Stores arbitrary data as Lua tables in a naive object database
 * manner. Intended for immutable definitions of things like
 * characters and items. Not as efficient performance-wise when
 * accessed from C++ as compared to C++-level data structures (due to
 * the overhead of crossing the Lua boundary and type checking).
 * Rebuilt on startup and kept in memory. If memory usage becomes an
 * issue then data could be serialized in a Lua-readable format, or
 * stored in an actual database like SQLite.
 */
class registry_manager
{
public:
    explicit registry_manager(lua_env*);

    /***
     * Registers a new datatype from the HCL spec file provided.
     */
    void register_datatype(const std::string& mod_name,
                           const std::string& datatype_name);

    /***
     * Registers instances of new data for a known datatype from the
     * provided HCL file. Throws if the datatype is not known.
     */
    void register_data(const std::string& mod_name,
                       const std::string& datatype_name,
                       const fs::path& data_file);

    /***
     * Registers function exports that are inside the "Exports" table
     * inside the API tables returned by mods. They will then be
     * accessable by the id
     *
     * "<mod_name>.exports.<namespaces>.<...>"
     *
     * corresponding to the nested table layout of the Exports table.
     *
     * This allows doing things like specifying what should happen
     * when a corpse is eaten, a trap is activated, and so forth.
     */
    void register_functions();

    /***
     * Obtains the root table for a datatype. For example, to get the
     * raw data of all characters, which have IDs like
     * "core.chara.<xxx>", pass in "core" and "chara" as arguments.
     */
    sol::optional<sol::table> get_table(const std::string& mod_name,
                                        const std::string& datatype_name);

    /***
     * Obtains a Lua callback of the format "core.exports.<name>", if
     * it exists.
     */
    optional<exported_function> get_function(const std::string& name) const;

    bool has_function(const std::string& name) const
    {
        return static_cast<bool>(get_function(name));
    }

    template <typename... Args>
    void call(const std::string& name, Args&&... args) const
    {
        if (auto func = get_function(name))
        {
            func->call(std::forward<Args>(args)...);
        }
    }

private:
    void bind_api();

    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment registry_env;

    lua_env* lua_;
};

} // namespace lua
} // namespace elona
