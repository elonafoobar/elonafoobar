#include "../../../calc.hpp"
#include "../../../character.hpp"
#include "../../../data/types/type_item.hpp"
#include "../../../enchantment.hpp"
#include "../../../inventory.hpp"
#include "../../../item.hpp"
#include "../../../itemgen.hpp"
#include "../../../text.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with items.
 */
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
    return inv_count(g_inv.ground());
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
bool Item_has_enchantment(const ItemRef& item, int enchantment_id)
{
    return !!enchantment_find(item, enchantment_id);
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
std::string Item_itemname(const ItemRef& item, int number, bool use_article)
{
    return elona::itemname(item, number, use_article);
}



sol::optional<ItemRef> Item_create_xy(int x, int y, sol::table args)
{
    // `libclang`, invoked from `tools/docgen`, fails to parse this function's
    // body for some reason.
#ifndef ELONA_DOCGEN
    int id = 0;
    Inventory* inv = nullptr;
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

    if (auto it = args.get<sol::optional<Inventory*>>("inventory"))
    {
        inv = *it;
    }
    if (!inv)
    {
        inv = &g_inv.ground();
    }

    // Random objlv
    if (auto it = args.get<sol::optional<int>>("level"))
    {
        objlv = calcobjlv(*it);
    }

    // Random fixlv
    if (auto it = args.get<sol::optional<Quality>>("quality"))
    {
        fixlv = calcfixlv(*it);
    }

    // Clears flttypemajor and flttypeminor.
    flt(objlv, fixlv);

    // Exact objlv
    if (auto it = args.get<sol::optional<int>>("objlv"))
    {
        objlv = *it;
    }

    // Exact fixlv
    if (auto it = args.get<sol::optional<Quality>>("fixlv"))
    {
        fixlv = *it;
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
        id = data.integer_id;
    }

    if (const auto item = itemcreate(*inv, id, x, y, number))
    {
        return item.unwrap();
    }
    else
    {
        return sol::nullopt;
    }
#endif
}



sol::optional<ItemRef>
Item_create_with_id_xy(int x, int y, const std::string& id)
{
    return Item_create_xy(
        x, y, lua::lua->get_state()->create_table_with("id", id));
}



sol::optional<ItemRef> Item_create_with_id(
    const Position& position,
    const std::string& id)
{
    return Item_create_with_id_xy(position.x, position.y, id);
}



sol::optional<ItemRef>
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
sol::optional<ItemRef> Item_create_with_number(
    const Position& position,
    const std::string& id,
    int number)
{
    return Item_create_with_number_xy(position.x, position.y, id, number);
}



sol::optional<ItemRef> Item_create(const Position& position, sol::table args)
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

    return itemmemory(type, data->integer_id);
}



/**
 * @luadoc trade_rate
 *
 * Returns the trading rate of a cargo item.
 *
 * @tparam LuaItem item A cargo item
 * @treturn num
 */
int Item_trade_rate(const ItemRef& item)
{
    // Item must be in the cargo category.
    if (the_item_db[item->id]->category != ItemCategory::cargo)
    {
        return 0;
    }

    return trate(item->param1);
}



/**
 * @luadoc find
 *
 * Tries to find an item in the player's inventory, the ground, or both.
 *
 * @tparam string item_id The item ID to find.
 * @tparam ItemFindLocation location Where to search for the item.
 */
sol::optional<ItemRef> Item_find(
    const std::string& item_id,
    const EnumString& location)
{
    auto location_value =
        LuaEnums::ItemFindLocationTable.ensure_from_string(location);

    if (const auto item = item_find(data::InstanceId{item_id}, location_value))
    {
        return item.unwrap();
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



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("count", Item_count);
    ELONA_LUA_API_BIND_FUNCTION("has_enchantment", Item_has_enchantment);
    ELONA_LUA_API_BIND_FUNCTION("itemname", Item_itemname);
    ELONA_LUA_API_BIND_FUNCTION("create", Item_create, Item_create_xy, Item_create_with_id, Item_create_with_id_xy, Item_create_with_number, Item_create_with_number_xy);
    ELONA_LUA_API_BIND_FUNCTION("memory", Item_memory);
    ELONA_LUA_API_BIND_FUNCTION("trade_rate", Item_trade_rate);
    ELONA_LUA_API_BIND_FUNCTION("find", Item_find);
    ELONA_LUA_API_BIND_FUNCTION("weight_string", Item_weight_string);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Item
