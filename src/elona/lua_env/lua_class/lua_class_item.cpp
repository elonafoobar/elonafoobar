#include "lua_class_item.hpp"
#include "../../data/types/type_item.hpp"
#include "../../data/types/type_item_material.hpp"
#include "../../item.hpp"
#include "../../itemgen.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../data_manager.hpp"

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

/**
 * @luadoc
 *
 * Changes the material of this item.
 * @tparam string material_id ID of the item material
 */
void LuaItem::change_material(Item& self, const std::string& material_id)
{
    const auto& data = the_item_material_db.ensure(material_id);
    change_item_material(self, data.id);
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
     * @luadoc legacy_id field num
     *
     * [R] The legacy ID of this item.
     */
    LuaItem.set("legacy_id", &Item::id);

    /**
     * @luadoc position field num
     *
     * [RW] The item's position.
     */
    LuaItem.set("position", &Item::position);

    /**
     * @luadoc weight field num
     *
     * [RW] The item's weight. One weight unit is 1000.
     */
    LuaItem.set("weight", &Item::weight);

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
     * @luadoc material field string
     *
     * [R] The material ID of this item. To change it, use
     * LuaItem.change_material.
     */
    LuaItem.set(
        "material",
        LUA_API_DATA_PROPERTY(Item, material, the_item_material_db));


    /**
     * @luadoc id field string
     *
     * [R] The new-style prototype ID of the item.
     */
    LuaItem.set("id", sol::property([](Item& i) {
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

    /**
     * @luadoc prototype field table
     *
     * [R] The prototype data of the character.
     */
    LuaItem.set("prototype", sol::property([](Item& self) {
                    auto id = the_item_db.get_id_from_legacy(self.id);
                    return *lua::lua->get_data_manager().get().raw(
                        "core.item", id->get());
                }));

    // Methods
    LuaItem.set("remove", &LuaItem::remove);
    LuaItem.set("change_material", &LuaItem::change_material);

    auto key = Item::lua_type();
    lua.set_usertype(key, LuaItem);
}

} // namespace lua
} // namespace elona
