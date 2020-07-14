#include "../../../enchantment.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Handle item enchantments.
 */
namespace elona::lua::api::modules::module_Enchantment
{

/**
 * @luadoc add
 *
 * Add an enchantment to the item.
 *
 * @tparam num id The enchantment ID.
 * @tparam num power The enchantment power.
 */
void Enchantment_add(const ItemRef& item, int id, int power)
{
    enchantment_add(item, id, power);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("add", Enchantment_add);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Enchantment
