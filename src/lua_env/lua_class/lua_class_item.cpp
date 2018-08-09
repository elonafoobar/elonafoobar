#include "lua_class_item.hpp"
#include "../../item.hpp"

namespace elona
{
namespace lua
{

void LuaItem::bind(sol::state& lua)
{
    sol::usertype<item> LuaItem(
        "lua_type",
        &item::lua_type,

        "set_number",
        &item::set_number,

        "curse_state",
        &item::curse_state,
        "identify_state",
        &item::identification_state,
        "index",
        sol::readonly(&item::index),
        "position",
        &item::position,
        "number",
        sol::property([](item& i) { return i.number(); }),
        "id",
        &item::id,
        "count",
        &item::count,
        "name",
        sol::property([](item& i) { return elona::itemname(i.index); }),
        "subname",
        &item::subname,
        "param1",
        &item::param1,
        "param2",
        &item::param2);

    lua.set_usertype(item::lua_type(), LuaItem);
}

}
}
