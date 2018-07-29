#pragma once
#include "lua_env.hpp"
#include "../filesystem.hpp"
#include "../putit.hpp"

namespace elona
{
namespace lua
{

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

private:
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
