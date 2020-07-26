#include "../../../inventory.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with inventory.
 */
namespace elona::lua::api::modules::module_Inventory
{

/**
 * @luadoc player
 *
 * Gets the player's inventory.
 *
 * @treturn LuaInventory The player's inventory.
 */
Inventory* Inventory_player()
{
    return &g_inv.pc();
}



/**
 * @luadoc map
 *
 * Gets the map inventory. It contains all items on the ground in the current
 * map.
 *
 * @treturn LuaInventory The map inventory.
 */
Inventory* Inventory_map()
{
    return &g_inv.ground();
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("player", Inventory_player);
    ELONA_LUA_API_BIND_FUNCTION("map", Inventory_map);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Inventory
