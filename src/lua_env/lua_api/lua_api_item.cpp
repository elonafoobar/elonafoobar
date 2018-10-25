#include "lua_api_item.hpp"
#include "../../calc.hpp"
#include "../../data/types/type_item.hpp"
#include "../../enchantment.hpp"
#include "../../item.hpp"
#include "../../itemgen.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{
namespace lua
{

int Item::count()
{
    return inv_sum(-1);
}

bool Item::has_enchantment(const LuaItemHandle handle, int id)
{
    auto& item_ref =
        lua::lua->get_handle_manager().get_ref<elona::Item>(handle);
    return elona::encfindspec(item_ref.index, id);
}

void Item::remove(LuaItemHandle handle)
{
    auto& item_ref =
        lua::lua->get_handle_manager().get_ref<elona::Item>(handle);
    item_ref.remove();
}

std::string Item::itemname(LuaItemHandle handle, int number, bool needs_article)
{
    auto& item_ref =
        lua::lua->get_handle_manager().get_ref<elona::Item>(handle);
    return elona::itemname(item_ref.index, number, needs_article ? 0 : 1);
}

sol::optional<LuaItemHandle> Item::create_with_args(
    const Position& position,
    const std::string& id,
    int number,
    sol::table args)
{
    return Item::create_with_args_xy(position.x, position.y, id, number, args);
}

sol::optional<LuaItemHandle> Item::create_with_args_xy(
    int x,
    int y,
    const std::string& id,
    int number,
    sol::table args)
{
    if (auto it = args.get<sol::optional<bool>>("nostack"))
    {
        nostack = *it ? 1 : 0;
    }

    if (auto it = args.get<sol::optional<int>>("mode"))
    {
        mode = *it;
    }

    // Clears flttypemajor and flttypeminor.
    flt();

    auto data = the_item_db[id];
    if (!data)
    {
        throw sol::error("No such item " + id);
    }

    if (itemcreate(-1, data->id, x, y, number) != 0)
    {
        LuaItemHandle handle = lua::lua->get_handle_manager().get_handle(
            inv[ci]); // TODO deglobalize ci
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

sol::optional<LuaItemHandle>
Item::create(const Position& position, const std::string& id, int number)
{
    return Item::create_with_args_xy(
        position.x,
        position.y,
        id,
        number,
        lua::lua->get_state()->create_table());
}

sol::optional<LuaItemHandle>
Item::create_xy(int x, int y, const std::string& id, int number)
{
    return Item::create_with_args_xy(
        x, y, id, number, lua::lua->get_state()->create_table());
}

sol::optional<LuaItemHandle> Item::roll(
    const Position& position,
    sol::table args)
{
    return Item::roll_xy(position.x, position.y, args);
}

sol::optional<LuaItemHandle> Item::roll_xy(int x, int y, sol::table args)
{
    int objlv = 0;
    Quality fixlv = Quality::none;

    // Exact objlv
    if (auto it = args.get<sol::optional<int>>("objlv"))
    {
        objlv = *it;
    }

    // Random objlv
    if (auto it = args.get<sol::optional<int>>("level"))
    {
        objlv = calcobjlv(*it);
    }

    // Exact fixlv
    if (auto it = args.get<sol::optional<std::string>>("fixlv"))
    {
        fixlv = LuaEnums::QualityTable.ensure_from_string(*it);
    }

    // Random fixlv
    if (auto it = args.get<sol::optional<std::string>>("quality"))
    {
        fixlv = calcfixlv(LuaEnums::QualityTable.ensure_from_string(*it));
    }

    // Clears flttypemajor and flttypeminor.
    flt(objlv, fixlv);

    if (auto it = args.get<sol::optional<int>>("flttypemajor"))
    {
        flttypemajor = *it;
    }

    if (auto it = args.get<sol::optional<int>>("flttypeminor"))
    {
        flttypeminor = *it;
    }

    if (itemcreate(-1, 0, x, y, 0) != 0)
    {
        LuaItemHandle handle =
            lua::lua->get_handle_manager().get_handle(inv[ci]);
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

void Item::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Item, count);
    LUA_API_BIND_FUNCTION(api_table, Item, has_enchantment);
    LUA_API_BIND_FUNCTION(api_table, Item, remove);
    LUA_API_BIND_FUNCTION(api_table, Item, itemname);
    api_table.set_function(
        "create",
        sol::overload(
            Item::create,
            Item::create_xy,
            Item::create_with_args,
            Item::create_with_args_xy));
    api_table.set_function("roll", sol::overload(Item::roll, Item::roll_xy));
}

} // namespace lua
} // namespace elona
