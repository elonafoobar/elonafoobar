#pragma once
#include "lua_env.hpp"
#include "../filesystem.hpp"
#include "../putit.hpp"

namespace elona
{
namespace lua
{

class handle_manager;

enum class mod_save_t
{
    global,
    map_local
};

/***
 * Responsible for saving and loading Lua data that can be held by
 * loaded mods.
 */
class serial_manager
{
public:
    explicit serial_manager(lua_env*);

    void save_mod_store_data(const fs::path&, mod_save_t);
    void load_mod_store_data(const fs::path&, mod_save_t);

    template <typename T>
    void save_handles(const fs::path& output_path,
                      mod_save_t save_type)
    {
        save_handles_inner(output_path, save_type, T::lua_type());
    }

    template <typename T>
    void load_handles(const fs::path& input_path,
                      mod_save_t save_type)
    {
        load_handles_inner(input_path, save_type, T::lua_type());
    }

private:
    void save_handles_inner(const fs::path&, mod_save_t, const std::string&);
    void load_handles_inner(const fs::path&, mod_save_t, const std::string&);

    /***
     * Saves a Lua table with game-related data to a file.
     */
    void save(sol::table&, putit::binary_oarchive&);

    /***
     * Loads game-related data into a Lua table from a file.
     */
    void load(sol::table&, putit::binary_iarchive&);

    /***
     * The isolated Lua environment that loads the Lua serialization
     * code.
     */
    sol::environment serial_env;

    lua_env* lua_;
};

} // namespace lua
} // namespace elona
