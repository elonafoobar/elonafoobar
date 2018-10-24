#include "lua_class_item.hpp"
#include "../../data/types/type_item.hpp"
#include "../../item.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{
namespace lua
{

void LuaItem::bind(sol::state& lua)
{
    sol::usertype<Item> LuaItem(
        "lua_type",
        &Item::lua_type,

        // Variables
        "index",
        sol::readonly(&Item::index),
        "id",
        &Item::id,
        "position",
        &Item::position,
        "count",
        &Item::count,
        "subname",
        &Item::subname,
        "image",
        &Item::image,
        "param1",
        &Item::param1,
        "param2",
        &Item::param2,
        "param3",
        &Item::param3,
        "param4",
        &Item::param4,

        // Properties
        "new_id",
        sol::property([](Item& i) {
            return the_item_db.get_id_from_legacy(i.id)->get();
        }),
        "name",
        sol::property([](Item& i) { return elona::itemname(i.index); }),
        "basename",
        sol::property([](Item& i) { return elona::ioriginalnameref(i.id); }),

        "number",
        sol::property(
            [](Item& i) { return i.number(); },
            [](Item& i, int number) { i.set_number(number); }),
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

    auto key = Item::lua_type();
    lua.set_usertype(key, LuaItem);

    // Methods
    lua[key]["remove"] = &Item::remove;
}

} // namespace lua
} // namespace elona
