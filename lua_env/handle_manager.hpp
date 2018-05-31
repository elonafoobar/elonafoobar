#pragma once

#include "lua_env.hpp"
#include "../character.hpp"
#include "../item.hpp"
#include <set>

namespace elona
{
namespace lua
{

class lua_env;

/***
 * Provides and manages references to C++ objects as Lua tables
 * (handles) that can be checked for validity on access. Works around
 * the problem of users storing references to C++ things somewhere and
 * forgetting to check they're still valid.
 *
 * The handles are represented as Lua tables stored in an isolated Lua
 * environment. The handle manager acts as the interface for providing
 * references to the handles to other Lua environments.
 *
 * See mods/core/handle.lua for more information.
 */
class handle_manager
{
public:
    explicit handle_manager(lua_env*);

    /***
     * Creates a new handle in the isolated handle environment.
     *
     * If the handle already exists, it is instead checked for
     * validity.
     */
    void create_chara_handle(character& chara);
    void create_item_handle(item& item);

    /***
     * Removes an existing handle in the isolated handle environment.
     *
     * If the handle doesn't exist in this manager's handle list, it
     * is checked that the handle is invalid.
     */
    void remove_chara_handle(character& chara);
    void remove_item_handle(item& item);

    /***
     * Provides a reference to a handle from the isolated handle
     * environment.
     */
    sol::object get_chara_handle(character& chara);
    sol::object get_item_handle(item& item);

    void clear_all_handles();

    /***
     * Clears only the handles that are local to the current map.
     * Player and party character/item handles are not cleared.
     */
    void clear_map_local_handles();
private:
    void bind(lua_env&);

    std::set<int> chara_handles;
    std::set<int> item_handles;

    /***
     * The isolated Lua environment where the handles are stored and
     * managed.
     */
    sol::environment handle_env;

    lua_env* lua;
};

} // namespace lua
} // namespace elona
