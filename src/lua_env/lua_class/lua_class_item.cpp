#include "lua_class_item.hpp"
#include "../../item.hpp"

namespace elona
{
namespace lua
{

void LuaItem::bind(sol::state& lua)
{
    sol::usertype<Item> LuaItem(
        "lua_type",
        &Item::lua_type,

        "set_number",
        &Item::set_number,

        "index",
        sol::readonly(&Item::index),
        "position",
        &Item::position,
        "number",
        sol::property([](Item& i) { return i.number(); }),
        "id",
        &Item::id,
        "count",
        &Item::count,
        "name",
        sol::property([](Item& i) { return elona::itemname(i.index); }),
        "basename",
        sol::property([](Item& i) { return elona::ioriginalnameref(i.id); }),
        "subname",
        &Item::subname,
        "param1",
        &Item::param1,
        "param2",
        &Item::param2,

        "curse_state",
        sol::property(
            [](Item& i) {
                return LuaEnums::CurseStateTable.convert_to_string(
                    i.curse_state);
            },
            [](Item& i, const EnumString& s) {
                i.curse_state = LuaEnums::CurseStateTable.ensure_from_string(s);
            }),
        "identify_state",
        sol::property(
            [](Item& i) {
                return LuaEnums::IdentifyStateTable.convert_to_string(
                    i.identification_state);
            },
            [](Item& i, const EnumString& s) {
                i.identification_state =
                    LuaEnums::IdentifyStateTable.ensure_from_string(s);
            }));

    lua.set_usertype(Item::lua_type(), LuaItem);
}

} // namespace lua
} // namespace elona
