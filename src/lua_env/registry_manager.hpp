#pragma once
#include <string>
#include <vector>
#include "../filesystem.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;

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
class RegistryManager
{
public:
    explicit RegistryManager(LuaEnv*);

    struct location
    {
        location(fs::path data_hcl_file, std::string mod_name)
            : data_hcl_file(data_hcl_file)
            , mod_name(mod_name)
        {
        }

        fs::path data_hcl_file;
        std::string mod_name;
    };

    /***
     * Loads the data declared by each mod in a data.hcl file inside
     * the mod's root directory, if it exists;
     */
    void load_mod_data(const std::vector<RegistryManager::location>&);

    /***
     * Registers a core datatype whose data is kept in native code.
     */
    void register_native_datatype(
        const std::string& datatype_name,
        std::function<void(sol::table)> initializer);

    /***
     * Obtains the root table for a datatype. For example, to get the
     * raw data of all characters, which have IDs like
     * "core.chara.<xxx>", pass in "core" and "chara" as arguments.
     */
    sol::optional<sol::table> get_table(
        const std::string& mod_name,
        const std::string& datatype_name);

private:
    /***
     * Registers a new datatype from the HCL spec file provided.
     */
    void register_datatype(
        const std::string& mod_name,
        const std::string& datatype_name);

    /***
     * Registers instances of new data for a known datatype from the
     * provided HCL file, originating from some arbitrary mod. Throws
     * if the datatype is not known.
     */
    void register_data(
        const std::string& originating_mod_name,
        const std::string& datatype_mod_name,
        const std::string& datatype_name,
        const fs::path& data_file);

    /***
     * Binds the Registry API to the LuaEnv attached to this
     * RegistryManager.
     */
    void bind_api();

    // Methods for loading data declared in mod data.hcl files.
    void load_single_mod_data(const fs::path&, const std::string&);
    void load_declared_mod_defines(
        const hcl::Object&,
        const fs::path&,
        const std::string&);
    void load_declared_mod_data(
        const hcl::Object&,
        const fs::path&,
        const std::string&);
    void load_single_declared_mod_data(
        const std::string&,
        const hcl::List&,
        const fs::path&,
        const std::string&);

    /***
     * The isolated Lua environment where data is stored.
     */
    sol::environment registry_env;
    bool data_initialized = false;
    // Initialization functions to call upon loading a core datatype.
    std::unordered_map<std::string, std::function<void(sol::table)>>
        native_initializers;

    LuaEnv* lua_;
};

} // namespace lua
} // namespace elona
