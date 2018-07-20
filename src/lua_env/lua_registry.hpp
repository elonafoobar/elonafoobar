#pragma once
#include <string>
#include "../filesystem.hpp"
#include "lua_env.hpp"

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
                           const fs::path& spec_file);

    /***
     * Registers instances of new data for a known datatype from the
     * provided HCL file. Throws if the datatype is not known.
     */
    void register_data(const std::string& mod_name,
                       const std::string& datatype_name,
                       const fs::path& data_file);

    sol::optional<sol::table> get_table(const std::string& mod_name,
                                        const std::string& datatype_name);

private:
    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment registry_env;

    lua_env* lua;
};

} // namespace lua
} // namespace elona
