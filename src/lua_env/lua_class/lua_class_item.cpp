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
        &item::param2,

        "curse_state",
        sol::property(
            [](item& i) {
                return LuaEnums::CurseStateTable.convert_to_string(i.curse_state);
            },
            [](item& i, const enum_string& s) {
                i.curse_state = LuaEnums::CurseStateTable.ensure_from_string(s);
            }),
        "identify_state",
        sol::property(
            [](item& i) {
                return LuaEnums::IdentifyStateTable.convert_to_string(
                    i.identification_state);
            },
            [](item& i, const enum_string& s) {
                i.identification_state =
                    LuaEnums::IdentifyStateTable.ensure_from_string(s);
            }));

    lua.set_usertype(item::lua_type(), LuaItem);
}

} // namespace lua
} // namespace elona
