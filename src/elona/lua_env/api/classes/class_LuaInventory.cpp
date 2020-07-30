#include <sstream>

#include "../../../inventory.hpp"
#include "../../../position.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Inventory)



/**
 * @luadoc
 *
 * Represents an item inventory, a list of items.
 */
namespace elona::lua::api::classes::class_LuaInventory
{

/**
 * @luadoc has_free_slot
 *
 * Queries whether the inventory has at least one free slot.
 *
 * @treturn True if the inventory has at least one free slot; false if not.
 */
bool LuaInventory_has_free_slot(Inventory* self)
{
    return self->has_free_slot();
}



// no doc
sol::table LuaInventory_as_table(Inventory* self, sol::this_state this_state)
{
    sol::state_view L{this_state};
    sol::table t = L.create_table();
    for (const auto& item : *self)
    {
        t.add(item);
    }
    return t;
}



/**
 * @luadoc stack
 *
 * Stacks an item in the inventory indicated. The item will no longer be valid
 * for use.
 *
 * @tparam LuaItem item
 * @treturn[1] LuaItem The modified item stack on success
 * @treturn[2] nil
 */
sol::optional<ItemRef> LuaInventory_stack(
    Inventory* self,
    const ItemRef& item,
    sol::optional<bool> show_message)
{
    const auto stack_result =
        inv_stack(*self, item, show_message.value_or(false));
    if (stack_result.stacked)
    {
        return stack_result.stacked_item;
    }
    else
    {
        return sol::nullopt;
    }
}



void bind(sol::state& lua)
{
    auto LuaInventory =
        lua.new_usertype<Inventory>("LuaInventory", sol::no_constructor);

    // Methods
    LuaInventory.set("has_free_slot", &LuaInventory_has_free_slot);
    LuaInventory.set("stack", &LuaInventory_stack);

    LuaInventory.set("as_table", &LuaInventory_as_table);
}

} // namespace elona::lua::api::classes::class_LuaInventory
