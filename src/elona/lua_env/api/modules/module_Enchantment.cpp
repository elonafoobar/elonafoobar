#include "module_Enchantment.hpp"

#include "../../../enchantment.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Add an enchantment to the item.
 * @tparam num id The enchantment ID.
 * @tparam num power The enchantment power.
 */
void LuaApiEnchantment::add(LuaItemHandle item, int id, int power)
{
    auto& item_ref = lua::ref<Item>(item);
    elona::enchantment_add(item_ref, id, power);
}



void LuaApiEnchantment::bind(sol::table api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiEnchantment, add);
}

} // namespace elona::lua::api::modules
