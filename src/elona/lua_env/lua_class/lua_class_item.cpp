#include "lua_class_item.hpp"

#include "../../data/types/type_item.hpp"
#include "../../data/types/type_item_material.hpp"
#include "../../item.hpp"
#include "../../itemgen.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../data_manager.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Item)



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
    const auto& data =
        the_item_material_db.ensure(data::InstanceId{material_id});
    change_item_material(self, data.legacy_id);
}



std::string LuaItem::metamethod_tostring(const Item& self)
{
    return Item::lua_type() + "(" + std::to_string(self.index) + ")";
}



void LuaItem::bind(sol::state& lua)
{
    auto LuaItem = lua.new_usertype<Item>("LuaItem", sol::no_constructor);
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
     * @luadoc own_state field num
     *
     * [RW] Controls the ownership of this item.
     * <code>-2</code>: Item was dropped by the player on death
     * <code>0</code>: Normal, can be picked up by the player
     * <code>1</code>: Not owned ("It's not your property", etc.)
     * <code>2</code>: Not carryable (shopkeeper's trunk).
     * <code>3</code>: Built shelter
     * <code>4</code>: Harvestable item in harvest quests
     */
    LuaItem.set("own_state", &Item::own_state);

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
    LuaItem.set(
        "id", sol::property([](Item& i) {
            return the_item_db.get_id_from_legacy(itemid2int(i.id))->get();
        }));
    /**
     * @luadoc name field string
     *
     * [R] The name of the item with article and number.
     */
    LuaItem.set(
        "name", sol::property([](Item& i) { return elona::itemname(i); }));

    /**
     * @luadoc basename field string
     *
     * [R] The name of the item without article and number.
     */
    LuaItem.set("basename", sol::property([](Item& i) {
                    return elona::ioriginalnameref(itemid2int(i.id));
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
        LUA_API_ENUM_PROPERTY(Item, identify_state, IdentifyState));

    /**
     * @luadoc color field ColorIndex
     *
     * [RW] The color ID of the item.
     */
    LuaItem.set(
        "color",
        sol::property(
            [](Item& it) {
                return LuaEnums::ColorIndexTable.convert_to_string(
                    static_cast<ColorIndex>(it.color));
            },
            [](Item& it, const EnumString& s) {
                it.color = static_cast<int>(
                    LuaEnums::ColorIndexTable.ensure_from_string(s));
            }));

    /**
     * @luadoc is_acidproof field boolean
     *
     * [RW] The flag if the item is acidproof.
     */
    LuaItem.set(
        "is_acidproof",
        sol::property(
            [](Item& i) { return i.is_acidproof(); },
            [](Item& i, bool value) { i.is_acidproof() = value; }));

    /**
     * @luadoc is_fireproof field boolean
     *
     * [RW] The flag if the item is fireproof.
     */
    LuaItem.set(
        "is_fireproof",
        sol::property(
            [](Item& i) { return i.is_fireproof(); },
            [](Item& i, bool value) { i.is_fireproof() = value; }));

    /**
     * @luadoc has_charge field boolean
     *
     * [RW] The flag if the item has charge.
     */
    LuaItem.set(
        "has_charge",
        sol::property(
            [](Item& i) { return i.has_charge(); },
            [](Item& i, bool value) { i.has_charge() = value; }));

    /**
     * @luadoc is_precious field boolean
     *
     * [RW] The flag if the item is precious.
     */
    LuaItem.set(
        "is_precious",
        sol::property(
            [](Item& i) { return i.is_precious(); },
            [](Item& i, bool value) { i.is_precious() = value; }));

    /**
     * @luadoc is_aphrodisiac field boolean
     *
     * [RW] The flag if the item is aphrodisiac.
     */
    LuaItem.set(
        "is_aphrodisiac",
        sol::property(
            [](Item& i) { return i.is_aphrodisiac(); },
            [](Item& i, bool value) { i.is_aphrodisiac() = value; }));

    /**
     * @luadoc has_cooldown_time field boolean
     *
     * [RW] The flag if the item has cooldown time.
     */
    LuaItem.set(
        "has_cooldown_time",
        sol::property(
            [](Item& i) { return i.has_cooldown_time(); },
            [](Item& i, bool value) { i.has_cooldown_time() = value; }));

    /**
     * @luadoc is_blessed_by_ehekatl field boolean
     *
     * [RW] The flag if the item is blessed by Ehekatl.
     */
    LuaItem.set(
        "is_blessed_by_ehekatl",
        sol::property(
            [](Item& i) { return i.is_blessed_by_ehekatl(); },
            [](Item& i, bool value) { i.is_blessed_by_ehekatl() = value; }));

    /**
     * @luadoc is_stolen field boolean
     *
     * [RW] The flag if the item is stolen.
     */
    LuaItem.set(
        "is_stolen",
        sol::property(
            [](Item& i) { return i.is_stolen(); },
            [](Item& i, bool value) { i.is_stolen() = value; }));

    /**
     * @luadoc is_alive field boolean
     *
     * [RW] The flag if the item is alive.
     */
    LuaItem.set(
        "is_alive",
        sol::property(
            [](Item& i) { return i.is_alive(); },
            [](Item& i, bool value) { i.is_alive() = value; }));

    /**
     * @luadoc is_quest_target field boolean
     *
     * [RW] The flag if the item is quest target.
     */
    LuaItem.set(
        "is_quest_target",
        sol::property(
            [](Item& i) { return i.is_quest_target(); },
            [](Item& i, bool value) { i.is_quest_target() = value; }));

    /**
     * @luadoc is_marked_as_no_drop field boolean
     *
     * [RW] The flag if the item is marked as no-drop.
     */
    LuaItem.set(
        "is_marked_as_no_drop",
        sol::property(
            [](Item& i) { return i.is_marked_as_no_drop(); },
            [](Item& i, bool value) { i.is_marked_as_no_drop() = value; }));

    /**
     * @luadoc is_poisoned field boolean
     *
     * [RW] The flag if the item is poisoned.
     */
    LuaItem.set(
        "is_poisoned",
        sol::property(
            [](Item& i) { return i.is_poisoned(); },
            [](Item& i, bool value) { i.is_poisoned() = value; }));

    /**
     * @luadoc is_eternal_force field boolean
     *
     * [RW] The flag if the item is eternal force.
     */
    LuaItem.set(
        "is_eternal_force",
        sol::property(
            [](Item& i) { return i.is_eternal_force(); },
            [](Item& i, bool value) { i.is_eternal_force() = value; }));

    /**
     * @luadoc is_showroom_only field boolean
     *
     * [RW] The flag if the item is showroom only.
     */
    LuaItem.set(
        "is_showroom_only",
        sol::property(
            [](Item& i) { return i.is_showroom_only(); },
            [](Item& i, bool value) { i.is_showroom_only() = value; }));

    /**
     * @luadoc is_handmade field boolean
     *
     * [RW] The flag if the item is handmade.
     */
    LuaItem.set(
        "is_handmade",
        sol::property(
            [](Item& i) { return i.is_handmade(); },
            [](Item& i, bool value) { i.is_handmade() = value; }));


    /**
     * @luadoc prototype field table
     *
     * [R] The prototype data of the character.
     */
    LuaItem.set("prototype", sol::property([](Item& self) {
                    return *lua::lua->get_data_manager().get().raw(
                        "core.item", self.new_id());
                }));

    // Methods
    LuaItem.set("remove", &LuaItem::remove);
    LuaItem.set("change_material", &LuaItem::change_material);

    LuaItem.set(sol::meta_function::to_string, &LuaItem::metamethod_tostring);
}

} // namespace lua
} // namespace elona
