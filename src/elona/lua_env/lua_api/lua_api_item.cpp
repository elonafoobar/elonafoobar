#include "lua_api_item.hpp"

#include "../../calc.hpp"
#include "../../character.hpp"
#include "../../data/types/type_item.hpp"
#include "../../enchantment.hpp"
#include "../../item.hpp"
#include "../../itemgen.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../text.hpp"
#include "../interface.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Returns the number of items on the ground.
 * @treturn num the item count
 */
int LuaApiItem::count()
{
    return inv_sum(-1);
}


/**
 * @luadoc
 *
 * Checks if an item has an enchantment.
 * @tparam LuaItem item (const) an item
 * @tparam num enchantment_id the ID of the enchantment
 * @treturn bool true if the item has the enchantment
 */
bool LuaApiItem::has_enchantment(const LuaItemHandle item, int enchantment_id)
{
    auto& item_ref = lua::ref<Item>(item);
    return !!enchantment_find(item_ref, enchantment_id);
}

/**
 * @luadoc
 *
 * Returns the item's name.
 * @tparam LuaItem item (const) the item
 * @tparam[opt] num number Overrides the item number
 * @tparam[opt] bool use_article Prepend articles like "the" to the item name
 * @treturn string
 */
std::string
LuaApiItem::itemname(LuaItemHandle item, int number, bool use_article)
{
    auto& item_ref = lua::ref<Item>(item);
    return elona::itemname(item_ref, number, use_article);
}

sol::optional<LuaItemHandle> LuaApiItem::create_with_id(
    const Position& position,
    const std::string& id)
{
    return LuaApiItem::create_with_id_xy(position.x, position.y, id);
}

sol::optional<LuaItemHandle>
LuaApiItem::create_with_id_xy(int x, int y, const std::string& id)
{
    return LuaApiItem::create_xy(
        x, y, lua::lua->get_state()->create_table_with("id", id));
}

/**
 * @luadoc create
 *
 * Attempts to create an item of the given quantity at a position.
 * Returns the item stack if it was created, nil otherwise.
 * @tparam LuaPosition position (const) position to create the item at
 * @tparam num id the item prototype ID
 * @tparam num number the number of items to create
 * @treturn[1] LuaItem the created item stack
 * @treturn[2] nil
 */
sol::optional<LuaItemHandle> LuaApiItem::create_with_number(
    const Position& position,
    const std::string& id,
    int number)
{
    return LuaApiItem::create_with_number_xy(
        position.x, position.y, id, number);
}

sol::optional<LuaItemHandle> LuaApiItem::create_with_number_xy(
    int x,
    int y,
    const std::string& id,
    int number)
{
    return LuaApiItem::create_xy(
        x,
        y,
        lua::lua->get_state()->create_table_with("id", id, "number", number));
}

sol::optional<LuaItemHandle> LuaApiItem::create(
    const Position& position,
    sol::table args)
{
    return LuaApiItem::create_xy(position.x, position.y, args);
}

sol::optional<LuaItemHandle>
LuaApiItem::create_xy(int x, int y, sol::table args)
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

/**
 * @luadoc
 *
 * Retrieves the player's memory of an item type.
 * @tparam num type
 * @tparam string id
 */
int LuaApiItem::memory(int type, const std::string& id)
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
 * @luadoc
 *
 * Stacks an item in the inventory indicated. The item will no longer be valid
 * for use.
 * @tparam num inventory_id
 * @tparam LuaItem handle
 * @treturn[1] LuaItem The modified item stack on success
 * @treturn[2] nil
 */
sol::optional<LuaItemHandle> LuaApiItem::stack(
    int inventory_id,
    LuaItemHandle handle)
{
    if (inventory_id < -1 || inventory_id > ELONA_MAX_CHARACTERS)
    {
        return sol::nullopt;
    }

    auto& item_ref = lua::ref<Item>(handle);

    auto& item = item_stack(inventory_id, item_ref).stacked_item;

    if (item.number() == 0)
    {
        return sol::nullopt;
    }

    return lua::handle(item);
}

/**
 * @luadoc
 *
 * Returns the trading rate of a cargo item.
 * @tparam LuaItem handle A cargo item
 * @treturn num
 */
int LuaApiItem::trade_rate(LuaItemHandle handle)
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
 * @luadoc
 *
 * Tries to find an item in the player's inventory, the ground, or both.
 * @tparam string item_id The item ID to find.
 * @tparam ItemFindLocation location Where to search for the item.
 */
sol::optional<LuaItemHandle> LuaApiItem::find(
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
 * @luadoc
 *
 * Returns the string representation of a weight value.
 * @tparam num weight The weight value
 * @treturn string
 */
std::string LuaApiItem::weight_string(int weight)
{
    return cnvweight(weight);
}

void LuaApiItem::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, count);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, has_enchantment);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, itemname);
    api_table.set_function(
        "create",
        sol::overload(
            LuaApiItem::create,
            LuaApiItem::create_xy,
            LuaApiItem::create_with_id,
            LuaApiItem::create_with_id_xy,
            LuaApiItem::create_with_number,
            LuaApiItem::create_with_number_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, memory);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, stack);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, trade_rate);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, find);
    LUA_API_BIND_FUNCTION(api_table, LuaApiItem, weight_string);
}

} // namespace lua
} // namespace elona
