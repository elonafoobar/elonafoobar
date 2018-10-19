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

sol::optional<LuaItemHandle>
Item::create(const Position& position, int id, int number)
{
    return Item::create_xy(position.x, position.y, id, number);
}

sol::optional<LuaItemHandle> Item::create_xy(int x, int y, int id, int number)
{
    elona::flt();
    if (elona::itemcreate(-1, id, x, y, number) != 0)
    {
        LuaItemHandle handle = lua::lua->get_handle_manager().get_handle(
            elona::inv[elona::ci]); // TODO deglobalize ci
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

sol::optional<LuaItemHandle> Item::create_from_id(
    const Position& position,
    const std::string& id,
    int number)
{
    return Item::create_from_id_xy(position.x, position.y, id, number);
}

sol::optional<LuaItemHandle>
Item::create_from_id_xy(int x, int y, const std::string& id, int number)
{
    auto data = the_item_db[id];
    if (!data)
    {
        throw sol::error("No such item " + id);
    }
    return Item::create_xy(x, y, data->id, number);
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
    Quality quality = Quality::none;

    if (auto it = args.get<sol::optional<int>>("objlv"))
    {
        objlv = *it;
    }

    if (auto it = args.get<sol::optional<int>>("level"))
    {
        objlv = calcobjlv(*it);
    }

    if (auto it = args.get<sol::optional<std::string>>("quality"))
    {
        quality = LuaEnums::QualityTable.ensure_from_string(*it);
    }

    // Clears flttypemajor and flttypeminor.
    flt(objlv, quality);

    if (auto it = args.get<sol::optional<int>>("flttypemajor"))
    {
        flttypemajor = *it;
    }

    if (auto it = args.get<sol::optional<int>>("flttypeminor"))
    {
        flttypeminor = *it;
    }

    if (elona::itemcreate(-1, 0, x, y, 0) != 0)
    {
        LuaItemHandle handle =
            lua::lua->get_handle_manager().get_handle(elona::inv[elona::ci]);
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
            Item::create_from_id,
            Item::create_from_id_xy));
    api_table.set_function("roll", sol::overload(Item::roll, Item::roll_xy));
}

} // namespace lua
} // namespace elona
