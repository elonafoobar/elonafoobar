#include "module_Item.hpp"

#include "../../../calc.hpp"
#include "../../../character.hpp"
#include "../../../data/types/type_item.hpp"
#include "../../../enchantment.hpp"
#include "../../../item.hpp"
#include "../../../itemgen.hpp"
#include "../../../text.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"



namespace elona::lua::api::modules::module_Item
{

/**
 * @luadoc count
 *
 * Returns the number of items on the ground.
 *
 * @treturn num the item count
 */
int Item_count()
{
    return inv_sum(-1);
}



/**
 * @luadoc has_enchantment
 *
 * Checks if an item has an enchantment.
 *
 * @tparam LuaItem item (const) an item
 * @tparam num enchantment_id the ID of the enchantment
 * @treturn bool true if the item has the enchantment
 */
bool Item_has_enchantment(const LuaItemHandle item, int enchantment_id)
{
    auto& item_ref = lua::ref<Item>(item);
    return !!enchantment_find(item_ref, enchantment_id);
}



/**
 * @luadoc itemname
 *
 * Returns the item's name.
 *
 * @tparam LuaItem item (const) the item
 * @tparam[opt] num number Overrides the item number
 * @tparam[opt] bool use_article Prepend articles like "the" to the item name
 * @treturn string
 */
std::string Item_itemname(LuaItemHandle item, int number, bool use_article)
{
    auto& item_ref = lua::ref<Item>(item);
    return elona::itemname(item_ref, number, use_article);
}



sol::optional<LuaItemHandle> Item_create_xy(int x, int y, sol::table args)
{
    // `libclang`, invoked from `tools/docgen`, fails to parse this function's
    // body for some reason.
#ifndef ELONA_DOCGEN
    int id = 0;
    int slot = -1;
    int number = 0;
    objlv = 0;
    fixlv = Quality::none;

    if (auto it = args.get<sol::optional<bool>>("nostack"))
    {
        nostack = *it ? 1 : 0;
    }

    if (auto it = args.get<sol::optional<int>>("mode"))
    {
        mode = *it;
    }

    if (auto it = args.get<sol::optional<int>>("number"))
    {
        number = *it;
    }

    if (auto it = args.get<sol::optional<int>>("slot"))
    {
        slot = *it;
    }

    // Random objlv
    if (auto it = args.get<sol::optional<int>>("level"))
    {
        objlv = calcobjlv(*it);
    }

    // Random fixlv
    if (auto it = args.get<sol::optional<std::string>>("quality"))
    {
        fixlv = calcfixlv(LuaEnums::QualityTable.ensure_from_string(*it));
    }

    // Clears flttypemajor and flttypeminor.
    flt(objlv, fixlv);

    // Exact objlv
    if (auto it = args.get<sol::optional<int>>("objlv"))
    {
        objlv = *it;
    }

    // Exact fixlv
    if (auto it = args.get<sol::optional<std::string>>("fixlv"))
    {
        fixlv = LuaEnums::QualityTable.ensure_from_string(*it);
    }

    if (auto it = args.get<sol::optional<int>>("flttypemajor"))
    {
        flttypemajor = *it;
    }

    if (auto it = args.get<sol::optional<int>>("flttypeminor"))
    {
        flttypeminor = *it;
    }

    if (auto it = args.get<sol::optional<int>>("fltselect"))
    {
        fltselect = *it;
    }

    if (auto it = args.get<sol::optional<std::string>>("fltn"))
    {
        fltn(*it);
    }

    if (auto it = args.get<sol::optional<std::string>>("id"))
    {
        auto data = the_item_db.ensure(data::InstanceId{*it});
        id = data.legacy_id;
    }

    if (const auto item = itemcreate(slot, id, x, y, number))
    {
        LuaItemHandle handle = lua::lua->get_handle_manager().get_handle(*item);
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
#endif
}



sol::optional<LuaItemHandle>
Item_create_with_id_xy(int x, int y, const std::string& id)
{
    return Item_create_xy(
        x, y, lua::lua->get_state()->create_table_with("id", id));
}



sol::optional<LuaItemHandle> Item_create_with_id(
    const Position& position,
    const std::string& id)
{
    return Item_create_with_id_xy(position.x, position.y, id);
}



sol::optional<LuaItemHandle>
Item_create_with_number_xy(int x, int y, const std::string& id, int number)
{
    return Item_create_xy(
        x,
        y,
        lua::lua->get_state()->create_table_with("id", id, "number", number));
}



/**
 * @luadoc create
 *
 * Attempts to create an item of the given quantity at a position.
 * Returns the item stack if it was created, nil otherwise.
 *
 * @tparam LuaPosition position (const) position to create the item at
 * @tparam num id the item prototype ID
 * @tparam num number the number of items to create
 * @treturn[1] LuaItem the created item stack
 * @treturn[2] nil
 */
sol::optional<LuaItemHandle> Item_create_with_number(
    const Position& position,
    const std::string& id,
    int number)
{
    return Item_create_with_number_xy(position.x, position.y, id, number);
}



sol::optional<LuaItemHandle> Item_create(
    const Position& position,
    sol::table args)
{
    return Item_create_xy(position.x, position.y, args);
}



/**
 * @luadoc memory
 *
 * Retrieves the player's memory of an item type.
 *
 * @tparam num type
 * @tparam string id
 */
int Item_memory(int type, const std::string& id)
{
    if (type < 0 || type > 2)
    {
        return 0;
    }

    auto data = the_item_db[data::InstanceId{id}];
    if (!data)
    {
        return 0;
    }

    return itemmemory(type, data->legacy_id);
}



/**
 * @luadoc stack
 *
 * Stacks an item in the inventory indicated. The item will no longer be valid
 * for use.
 *
 * @tparam num inventory_id
 * @tparam LuaItem handle
 * @treturn[1] LuaItem The modified item stack on success
 * @treturn[2] nil
 */
sol::optional<LuaItemHandle> Item_stack(
    int inventory_id,
    LuaItemHandle handle,
    sol::optional<bool> show_message)
{
    if (inventory_id < -1 || inventory_id > ELONA_MAX_CHARACTERS)
    {
        return sol::nullopt;
    }

    auto& item_ref = lua::ref<Item>(handle);

    auto& item =
        item_stack(inventory_id, item_ref, show_message.value_or(false))
            .stacked_item;

    if (item.number() == 0)
    {
        return sol::nullopt;
    }

    return lua::handle(item);
}



/**
 * @luadoc trade_rate
 *
 * Returns the trading rate of a cargo item.
 *
 * @tparam LuaItem handle A cargo item
 * @treturn num
 */
int Item_trade_rate(LuaItemHandle handle)
{
    auto& item_ref = lua::ref<Item>(handle);

    // Item must be in the cargo category.
    if (the_item_db[itemid2int(item_ref.id)]->category != ItemCategory::cargo)
    {
        return 0;
    }

    return trate(item_ref.param1);
}



/**
 * @luadoc find
 *
 * Tries to find an item in the player's inventory, the ground, or both.
 *
 * @tparam string item_id The item ID to find.
 * @tparam ItemFindLocation location Where to search for the item.
 */
sol::optional<LuaItemHandle> Item_find(
    const std::string& item_id,
    const EnumString& location)
{
    auto data = the_item_db.ensure(data::InstanceId{item_id});

    auto location_value =
        LuaEnums::ItemFindLocationTable.ensure_from_string(location);

    if (const auto item = item_find(data.legacy_id, 3, location_value))
    {
        return lua::handle(*item);
    }
    else
    {
        return sol::nullopt;
    }
}



/**
 * @luadoc weight_string
 *
 * Returns the string representation of a weight value.
 *
 * @tparam num weight The weight value
 * @treturn string
 */
std::string Item_weight_string(int weight)
{
    return cnvweight(weight);
}



/**
 * @luadoc has_free_slot
 *
 * Queries whether the inventory has at least one free slot.
 *
 * @tparam num inventory_id The inventory ID
 * @treturn True if the inventory has at least one free slot; false if not.
 */
bool Item_has_free_slot(int inventory_id)
{
    return inv_getspace(inventory_id);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("count", Item_count);
    ELONA_LUA_API_BIND_FUNCTION("has_enchantment", Item_has_enchantment);
    ELONA_LUA_API_BIND_FUNCTION("itemname", Item_itemname);
    ELONA_LUA_API_BIND_FUNCTION("create", Item_create, Item_create_xy, Item_create_with_id, Item_create_with_id_xy, Item_create_with_number, Item_create_with_number_xy);
    ELONA_LUA_API_BIND_FUNCTION("memory", Item_memory);
    ELONA_LUA_API_BIND_FUNCTION("stack", Item_stack);
    ELONA_LUA_API_BIND_FUNCTION("trade_rate", Item_trade_rate);
    ELONA_LUA_API_BIND_FUNCTION("find", Item_find);
    ELONA_LUA_API_BIND_FUNCTION("weight_string", Item_weight_string);
    ELONA_LUA_API_BIND_FUNCTION("has_free_slot", Item_has_free_slot);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Item
