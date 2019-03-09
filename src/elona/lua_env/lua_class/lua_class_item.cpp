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
    auto LuaItem = lua.create_simple_usertype<Item>();
    LuaItem.set("new", sol::no_constructor);
    LuaItem.set("lua_type", &Item::lua_type);

    // Properties

    /**
     * @luadoc index field num
     *
     * [R] The index of this item in the global items array.
     */
    LuaItem.set("index", sol::readonly(&Item::index));


    /**
     * @luadoc id field num
     *
     * [R] The prototype ID of this item.
     */
    LuaItem.set("id", &Item::id);

    /**
     * @luadoc position field num
     *
     * [RW] The item's position.
     */
    LuaItem.set("position", &Item::position);

    /**
     * @luadoc count field num
     *
     * [RW] The number of charges this item holds (for rods, bait, etc.)
     */
    LuaItem.set("count", &Item::count);


    /**
     * @luadoc subname field num
     *
     * [RW] The subname of this item. Controls the character index of
     * corpses, etc.
     */
    LuaItem.set("subname", &Item::subname);


    /**
     * @luadoc image field num
     *
     * [RW] The image ID of the item.
     */
    LuaItem.set("image", &Item::image);

    /**
     * @luadoc value field num
     *
     * [RW] The value of the item.
     */
    LuaItem.set("value", &Item::value);

    /**
     * @luadoc param1 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set("param1", &Item::param1);

    /**
     * @luadoc param2 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set("param2", &Item::param2);

    /**
     * @luadoc param3 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set("param3", &Item::param3);

    /**
     * @luadoc param4 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set("param4", &Item::param4);


    /**
     * @luadoc new_id field num
     *
     * [R] The new version prototype ID of the item.
     */
    LuaItem.set("new_id", sol::property([](Item& i) {
                    return the_item_db.get_id_from_legacy(i.id)->get();
                }));
    /**
     * @luadoc name field string
     *
     * [R] The name of the item with article and number.
     */
    LuaItem.set("name", sol::property([](Item& i) {
                    return elona::itemname(i.index);
                }));

    /**
     * @luadoc basename field string
     *
     * [R] The name of the item without article and number.
     */
    LuaItem.set("basename", sol::property([](Item& i) {
                    return elona::ioriginalnameref(i.id);
                }));

    /**
     * @luadoc number field num
     *
     * [RW] The number of this item.
     */
    LuaItem.set(
        "number",
        sol::property(
            [](Item& i) { return i.number(); },
            [](Item& i, int number) { i.set_number(number); }));

    /**
     * @luadoc curse_state field CurseState
     *
     * [RW] The curse state of this item.
     */
    LuaItem.set(
        "curse_state", LUA_API_ENUM_PROPERTY(Item, curse_state, CurseState));

    /**
     * @luadoc identify_state field IdentifyState
     *
     * [RW] The identify state of this item.
     */
    LuaItem.set(
        "identify_state",
        LUA_API_ENUM_PROPERTY(Item, identification_state, IdentifyState));

    // Methods
    LuaItem.set("remove", &LuaItem::remove);

    auto key = Item::lua_type();
    lua.set_usertype(key, LuaItem);
}

} // namespace lua
} // namespace elona
