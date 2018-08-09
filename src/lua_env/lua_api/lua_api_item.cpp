#include "lua_api_item.hpp"
#include "../../db_item.hpp"
#include "../../enchantment.hpp"
#include "../../item.hpp"
#include "../../itemgen.hpp"

namespace elona
{
namespace lua
{

int Item::count()
{
    return inv_sum(-1);
}

bool Item::has_enchantment(const lua_item_handle handle, int id)
{
    auto& item_ref = lua::lua->get_handle_manager().get_ref<item>(handle);
    return elona::encfindspec(item_ref.index, id);
}

void Item::remove(lua_item_handle handle)
{
    auto& item_ref = lua::lua->get_handle_manager().get_ref<item>(handle);
    item_ref.remove();
}

sol::optional<lua_item_handle>
Item::create(const position_t& position, int id, int number)
{
    return Item::create_xy(position.x, position.y, id, number);
}

sol::optional<lua_item_handle> Item::create_xy(int x, int y, int id, int number)
{
    elona::flt();
    if (elona::itemcreate(-1, id, x, y, number) != 0)
    {
        lua_item_handle handle = lua::lua->get_handle_manager().get_handle(
            elona::inv[elona::ci]); // TODO deglobalize ci
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

sol::optional<lua_item_handle> Item::create_from_id(
    const position_t& position,
    const std::string& id,
    int number)
{
    return Item::create_from_id_xy(position.x, position.y, id, number);
}

sol::optional<lua_character_handle>
Item::create_from_id_xy(int x, int y, const std::string& id, int number)
{
    auto full_id = "core.item:" + id;
    auto data = the_item_db[full_id];
    if (!data)
    {
        throw sol::error("No such item " + id);
    }
    return Item::create_xy(x, y, data->id, number);
}

void Item::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Item, count);
    api_table.set_function(
        "create",
        sol::overload(
            Item::create,
            Item::create_xy,
            Item::create_from_id,
            Item::create_from_id_xy));
    LUA_API_BIND_FUNCTION(api_table, Item, remove);
    LUA_API_BIND_FUNCTION(api_table, Item, has_enchantment);
}

} // namespace lua
} // namespace elona
