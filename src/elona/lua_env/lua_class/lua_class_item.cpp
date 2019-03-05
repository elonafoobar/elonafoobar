#include "lua_class_item.hpp"
#include "../../data/types/type_item.hpp"
#include "../../item.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Removes this item. The item reference will no longer be valid for use.
 */
void LuaItem::remove(Item& self)
{
    self.remove();
}

void LuaItem::bind(sol::state& lua)
{
    sol::usertype<Item> LuaItem(
        "lua_type",
        &Item::lua_type,


        /**
         * @luadoc index field num
         *
         * [R] The index of this item in the global items array.
         */
        "index",
        sol::readonly(&Item::index),


        /**
         * @luadoc id field num
         *
         * [R] The prototype ID of this item.
         */
        "id",
        &Item::id,

        /**
         * @luadoc position field num
         *
         * [RW] The item's position.
         */
        "position",
        &Item::position,

        /**
         * @luadoc count field num
         *
         * [RW] The number of charges this item holds (for rods, bait, etc.)
         */
        "count",
        &Item::count,


        /**
         * @luadoc subname field num
         *
         * [RW] The subname of this item. Controls the character index of
         * corpses, etc.
         */
        "subname",
        &Item::subname,


        /**
         * @luadoc image field num
         *
         * [RW] The image ID of the item.
         */
        "image",
        &Item::image,

        /**
         * @luadoc value field num
         *
         * [RW] The value of the item.
         */
        "value",
        &Item::value,

        /**
         * @luadoc param1 field num
         *
         * [RW] A generic parameter.
         */
        "param1",
        &Item::param1,

        /**
         * @luadoc param2 field num
         *
         * [RW] A generic parameter.
         */
        "param2",
        &Item::param2,

        /**
         * @luadoc param3 field num
         *
         * [RW] A generic parameter.
         */
        "param3",
        &Item::param3,

        /**
         * @luadoc param4 field num
         *
         * [RW] A generic parameter.
         */
        "param4",
        &Item::param4,


        /**
         * @luadoc new_id field num
         *
         * [R] The new version prototype ID of the item.
         */
        "new_id",
        sol::property([](Item& i) {
            return the_item_db.get_id_from_legacy(i.id)->get();
        }),

        /**
         * @luadoc name field string
         *
         * [R] The name of the item with article and number.
         */
        "name",
        sol::property([](Item& i) { return elona::itemname(i.index); }),

        /**
         * @luadoc basename field string
         *
         * [R] The name of the item without article and number.
         */
        "basename",
        sol::property([](Item& i) { return elona::ioriginalnameref(i.id); }),

        /**
         * @luadoc number field num
         *
         * [RW] The number of this item.
         */
        "number",
        sol::property(
            [](Item& i) { return i.number(); },
            [](Item& i, int number) { i.set_number(number); }),

        /**
         * @luadoc curse_state field CurseState
         *
         * [RW] The curse state of this item.
         */
        "curse_state",
        sol::property(
            [](Item& i) {
                return LuaEnums::CurseStateTable.convert_to_string(
                    i.curse_state);
            },
            [](Item& i, const EnumString& s) {
                i.curse_state = LuaEnums::CurseStateTable.ensure_from_string(s);
            }),

        /**
         * @luadoc identify_state field IdentifyState
         *
         * [RW] The identify state of this item.
         */
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
    lua[key]["remove"] = &LuaItem::remove;
}

} // namespace lua
} // namespace elona
