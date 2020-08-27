#include "../../../data/types/type_item.hpp"
#include "../../../data/types/type_item_material.hpp"
#include "../../../item.hpp"
#include "../../../itemgen.hpp"
#include "../../data_manager.hpp"
#include "../../enums/enums.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::ItemRef)



/**
 * @luadoc
 *
 * Represents an item.
 */
namespace elona::lua::api::classes::class_LuaItem
{

/**
 * @luadoc remove
 *
 * Removes this item. The item reference will no longer be valid for use.
 */
void LuaItem_remove(const ItemRef& self)
{
    self->remove();
}



/**
 * @luadoc change_material
 *
 * Changes the material of this item.
 * @tparam string material_id ID of the item material
 */
void LuaItem_change_material(
    const ItemRef& self,
    const std::string& material_id)
{
    change_item_material(self, data::InstanceId{material_id});
}



std::string LuaItem_metamethod_tostring(const ItemRef& self)
{
    return self->lua_type() + "(" + self->obj_id.to_string() + ")";
}



void bind(sol::state& lua)
{
    auto LuaItem = lua.new_usertype<ItemRef>("LuaItem", sol::no_constructor);

    LuaItem.set("lua_type", sol::property([](const ItemRef& self) {
                    return self->lua_type();
                }));

    // Properties

    /**
     * @luadoc legacy_id field num
     *
     * [R] The legacy ID of this item.
     */
    LuaItem.set("legacy_id", sol::property([](const ItemRef& self) {
                    return the_item_db[self->id]->legacy_id;
                }));

    /**
     * @luadoc position field num
     *
     * [RW] The item's position.
     */
    LuaItem.set(
        "position",
        sol::property(
            [](const ItemRef& self) { return self->position(); },
            [](const ItemRef& self, const Position& pos) {
                self->set_position(pos);
            }));

    /**
     * @luadoc charges field num
     *
     * [RW] The number of charges this item holds (for rods, bait, etc.)
     */
    LuaItem.set(
        "charges",
        sol::property(
            [](const ItemRef& self) { return self->charges; },
            [](const ItemRef& self, lua_int new_value) {
                self->charges = new_value;
            }));


    /**
     * @luadoc subname field num
     *
     * [RW] The subname of this item. Controls the character index of
     * corpses, etc.
     */
    LuaItem.set(
        "subname",
        sol::property(
            [](const ItemRef& self) { return self->subname; },
            [](const ItemRef& self, int new_value) {
                self->subname = new_value;
            }));


    /**
     * @luadoc image field num
     *
     * [RW] The image ID of the item.
     */
    LuaItem.set(
        "image",
        sol::property(
            [](const ItemRef& self) { return self->image; },
            [](const ItemRef& self, int new_value) {
                self->image = new_value;
            }));

    /**
     * @luadoc value field num
     *
     * [RW] The value of the item.
     */
    LuaItem.set(
        "value",
        sol::property(
            [](const ItemRef& self) { return self->value; },
            [](const ItemRef& self, lua_int new_value) {
                self->value = new_value;
            }));

    /**
     * @luadoc param1 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set(
        "param1",
        sol::property(
            [](const ItemRef& self) { return self->param1; },
            [](const ItemRef& self, int new_value) {
                self->param1 = new_value;
            }));

    /**
     * @luadoc param2 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set(
        "param2",
        sol::property(
            [](const ItemRef& self) { return self->param2; },
            [](const ItemRef& self, int new_value) {
                self->param2 = new_value;
            }));

    /**
     * @luadoc param3 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set(
        "param3",
        sol::property(
            [](const ItemRef& self) { return self->param3; },
            [](const ItemRef& self, int new_value) {
                self->param3 = new_value;
            }));

    /**
     * @luadoc param4 field num
     *
     * [RW] A generic parameter.
     */
    LuaItem.set(
        "param4",
        sol::property(
            [](const ItemRef& self) { return self->param4; },
            [](const ItemRef& self, int new_value) {
                self->param4 = new_value;
            }));

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
    LuaItem.set(
        "own_state",
        sol::property(
            [](const ItemRef& self) { return self->own_state; },
            [](const ItemRef& self, int new_value) {
                self->own_state = static_cast<OwnState>(new_value);
            }));

    /**
     * @luadoc material field string
     *
     * [RW] The material ID of this item. To change it, use
     * LuaItem.change_material.
     */
    LuaItem.set(
        "material",
        sol::property(
            [](const ItemRef& self) { return self->material.get(); },
            [](const ItemRef& self, const std::string& new_value) {
                self->material = data::InstanceId{new_value};
            }));


    /**
     * @luadoc id field string
     *
     * [R] The new-style prototype ID of the item.
     */
    LuaItem.set("id", sol::property([](const ItemRef& self) {
                    return the_item_db
                        .get_id_from_legacy(the_item_db[self->id]->legacy_id)
                        ->get();
                }));
    /**
     * @luadoc name field string
     *
     * [R] The name of the item with article and number.
     */
    LuaItem.set("name", sol::property([](const ItemRef& self) {
                    return elona::itemname(self);
                }));

    /**
     * @luadoc basename field string
     *
     * [R] The name of the item without article and number.
     */
    LuaItem.set(
        "basename", sol::property([](const ItemRef& self) {
            return elona::ioriginalnameref(the_item_db[self->id]->legacy_id);
        }));

    /**
     * @luadoc number field num
     *
     * [RW] The number of this item.
     */
    LuaItem.set(
        "number",
        sol::property(
            [](const ItemRef& self) { return self->number(); },
            [](const ItemRef& self, lua_int number) {
                self->set_number(number);
            }));

    /**
     * @luadoc curse_state field CurseState
     *
     * [RW] The curse state of this item.
     */
    LuaItem.set(
        "curse_state",
        sol::property(
            [](const ItemRef& self) {
                return LuaEnums::CurseStateTable.convert_to_string(
                    self->curse_state);
            },
            [](const ItemRef& self, const EnumString& s) {
                self->curse_state =
                    LuaEnums::CurseStateTable.ensure_from_string(s);
            }));

    /**
     * @luadoc identify_state field IdentifyState
     *
     * [RW] The identify state of this item.
     */
    LuaItem.set(
        "identify_state",
        sol::property(
            [](const ItemRef& self) {
                return LuaEnums::IdentifyStateTable.convert_to_string(
                    self->identify_state);
            },
            [](const ItemRef& self, const EnumString& s) {
                self->identify_state =
                    LuaEnums::IdentifyStateTable.ensure_from_string(s);
            }));

    /**
     * @luadoc color field ColorIndex
     *
     * [RW] The color ID of the item.
     */
    LuaItem.set(
        "color",
        sol::property(
            [](const ItemRef& self) {
                return LuaEnums::ColorIndexTable.convert_to_string(
                    static_cast<ColorIndex>(self->tint));
            },
            [](const ItemRef& self, const EnumString& s) {
                self->tint = static_cast<int>(
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
            [](const ItemRef& self) { return self->is_acidproof(); },
            [](const ItemRef& self, bool new_value) {
                self->is_acidproof() = new_value;
            }));

    /**
     * @luadoc is_fireproof field boolean
     *
     * [RW] The flag if the item is fireproof.
     */
    LuaItem.set(
        "is_fireproof",
        sol::property(
            [](const ItemRef& self) { return self->is_fireproof(); },
            [](const ItemRef& self, bool new_value) {
                self->is_fireproof() = new_value;
            }));

    /**
     * @luadoc has_charge field boolean
     *
     * [RW] The flag if the item has charge.
     */
    LuaItem.set(
        "has_charge",
        sol::property(
            [](const ItemRef& self) { return self->has_charge(); },
            [](const ItemRef& self, bool new_value) {
                self->has_charge() = new_value;
            }));

    /**
     * @luadoc is_precious field boolean
     *
     * [RW] The flag if the item is precious.
     */
    LuaItem.set(
        "is_precious",
        sol::property(
            [](const ItemRef& self) { return self->is_precious(); },
            [](const ItemRef& self, bool new_value) {
                self->is_precious() = new_value;
            }));

    /**
     * @luadoc is_aphrodisiac field boolean
     *
     * [RW] The flag if the item is aphrodisiac.
     */
    LuaItem.set(
        "is_aphrodisiac",
        sol::property(
            [](const ItemRef& self) { return self->is_aphrodisiac(); },
            [](const ItemRef& self, bool new_value) {
                self->is_aphrodisiac() = new_value;
            }));

    /**
     * @luadoc has_cooldown_time field boolean
     *
     * [RW] The flag if the item has cooldown time.
     */
    LuaItem.set(
        "has_cooldown_time",
        sol::property(
            [](const ItemRef& self) { return self->has_cooldown_time(); },
            [](const ItemRef& self, bool new_value) {
                self->has_cooldown_time() = new_value;
            }));

    /**
     * @luadoc is_blessed_by_ehekatl field boolean
     *
     * [RW] The flag if the item is blessed by Ehekatl.
     */
    LuaItem.set(
        "is_blessed_by_ehekatl",
        sol::property(
            [](const ItemRef& self) { return self->is_blessed_by_ehekatl(); },
            [](const ItemRef& self, bool new_value) {
                self->is_blessed_by_ehekatl() = new_value;
            }));

    /**
     * @luadoc is_stolen field boolean
     *
     * [RW] The flag if the item is stolen.
     */
    LuaItem.set(
        "is_stolen",
        sol::property(
            [](const ItemRef& self) { return self->is_stolen(); },
            [](const ItemRef& self, bool new_value) {
                self->is_stolen() = new_value;
            }));

    /**
     * @luadoc is_alive field boolean
     *
     * [RW] The flag if the item is alive.
     */
    LuaItem.set(
        "is_alive",
        sol::property(
            [](const ItemRef& self) { return self->is_alive(); },
            [](const ItemRef& self, bool new_value) {
                self->is_alive() = new_value;
            }));

    /**
     * @luadoc is_quest_target field boolean
     *
     * [RW] The flag if the item is quest target.
     */
    LuaItem.set(
        "is_quest_target",
        sol::property(
            [](const ItemRef& self) { return self->is_quest_target(); },
            [](const ItemRef& self, bool new_value) {
                self->is_quest_target() = new_value;
            }));

    /**
     * @luadoc is_marked_as_no_drop field boolean
     *
     * [RW] The flag if the item is marked as no-drop.
     */
    LuaItem.set(
        "is_marked_as_no_drop",
        sol::property(
            [](const ItemRef& self) { return self->is_marked_as_no_drop(); },
            [](const ItemRef& self, bool new_value) {
                self->is_marked_as_no_drop() = new_value;
            }));

    /**
     * @luadoc is_poisoned field boolean
     *
     * [RW] The flag if the item is poisoned.
     */
    LuaItem.set(
        "is_poisoned",
        sol::property(
            [](const ItemRef& self) { return self->is_poisoned(); },
            [](const ItemRef& self, bool new_value) {
                self->is_poisoned() = new_value;
            }));

    /**
     * @luadoc is_eternal_force field boolean
     *
     * [RW] The flag if the item is eternal force.
     */
    LuaItem.set(
        "is_eternal_force",
        sol::property(
            [](const ItemRef& self) { return self->is_eternal_force(); },
            [](const ItemRef& self, bool new_value) {
                self->is_eternal_force() = new_value;
            }));

    /**
     * @luadoc is_showroom_only field boolean
     *
     * [RW] The flag if the item is showroom only.
     */
    LuaItem.set(
        "is_showroom_only",
        sol::property(
            [](const ItemRef& self) { return self->is_showroom_only(); },
            [](const ItemRef& self, bool new_value) {
                self->is_showroom_only() = new_value;
            }));

    /**
     * @luadoc is_handmade field boolean
     *
     * [RW] The flag if the item is handmade.
     */
    LuaItem.set(
        "is_handmade",
        sol::property(
            [](const ItemRef& self) { return self->is_handmade(); },
            [](const ItemRef& self, bool new_value) {
                self->is_handmade() = new_value;
            }));


    /**
     * @luadoc prototype field table
     *
     * [R] The prototype data of the character.
     */
    LuaItem.set("prototype", sol::property([](const ItemRef& self) {
                    return *lua::lua->get_data_manager().get().raw(
                        "core.item", self->id);
                }));

    // Methods
    LuaItem.set("remove", &LuaItem_remove);
    LuaItem.set("change_material", &LuaItem_change_material);

    LuaItem.set(sol::meta_function::to_string, &LuaItem_metamethod_tostring);
}

} // namespace elona::lua::api::classes::class_LuaItem
