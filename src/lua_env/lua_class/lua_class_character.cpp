#include "lua_class_character.hpp"
#include "../../ability.hpp"
#include "../../character.hpp"
#include "../../character_status.hpp"
#include "../../dmgheal.hpp"
#include "../../element.hpp"
#include "../../enums.hpp"
#include "../../food.hpp"

namespace elona
{
namespace lua
{

void LuaCharacter::damage_hp(character& self, int amount)
{
    LuaCharacter::damage_hp_source(self, amount, "UnseenHand");
}

void LuaCharacter::damage_hp_source(
    character& self,
    int amount,
    const enum_string& source_name)
{
    DamageSource source =
        LuaEnums::DamageSourceTable.ensure_from_string(source_name);
    elona::damage_hp(self, amount, static_cast<int>(source));
}

void LuaCharacter::damage_hp_chara(
    character& self,
    int amount,
    lua_character_handle handle)
{
    auto& other = lua::lua->get_handle_manager().get_ref<character>(handle);
    elona::damage_hp(self, amount, other.index);
}

void LuaCharacter::apply_ailment(
    character& self,
    const enum_string& ailment_name,
    int power)
{
    assert(power > 0);
    StatusAilment ailment =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment_name);
    elona::dmgcon(self.index, ailment, power);
}

bool LuaCharacter::recruit_as_ally(character& self)
{
    if (self.state() == character::State::empty
        || (self.index != 0 && self.index <= 16) || self.index == 0)
    {
        return false;
    }
    elona::rc = self.index;
    return new_ally_joins() == 1;
}

void LuaCharacter::set_flag(
    character& self,
    const std::string& flag_name,
    bool is_setting)
{
    int flag = LuaEnums::CharaFlagTable.ensure_from_string(flag_name);
    int new_value = (is_setting ? 1 : 0);
    self._flags[flag] = new_value;
}

void LuaCharacter::gain_skill(character& self, int skill, int initial_level)
{
    LuaCharacter::gain_skill_stock(self, skill, initial_level, 0);
}

void LuaCharacter::gain_skill_stock(
    character& self,
    int skill,
    int initial_level,
    int initial_stock)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::chara_gain_skill(self, skill, initial_level, initial_stock);
}

void LuaCharacter::gain_skill_exp(character& self, int skill, int amount)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::chara_gain_fixed_skill_exp(self, skill, amount);
}

void LuaCharacter::modify_resistance(
    character& self,
    const enum_string& element_name,
    int delta)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    elona::resistmod(self.index, static_cast<int>(element), delta);
}

void LuaCharacter::modify_sanity(character& self, int delta)
{
    if (delta < 0)
    {
        elona::damage_insanity(self, (-delta));
    }
    else
    {
        elona::heal_insanity(self, delta);
    }
}

void LuaCharacter::modify_karma(character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_karma(self, delta);
}

void LuaCharacter::modify_corruption(character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_ether_disease_stage(delta);
}

void LuaCharacter::make_pregnant(character& self)
{
    int tc_bk = self.index;
    elona::tc = self.index;

    elona::get_pregnant();

    elona::tc = tc_bk;
}

void LuaCharacter::eat_rotten_food(character& self)
{
    int cc_bk = self.index;
    elona::cc = self.index;

    elona::eat_rotten_food();

    elona::cc = cc_bk;
}

void LuaCharacter::bind(sol::state& lua)
{
    sol::usertype<character> LuaCharacter(
        "lua_type",
        &character::lua_type,

        "damage_hp",
        sol::overload(
            &LuaCharacter::damage_hp,
            &LuaCharacter::damage_hp_source,
            &LuaCharacter::damage_hp_chara),
        "apply_ailment",
        &LuaCharacter::apply_ailment,
        "recruit_as_ally",
        &LuaCharacter::recruit_as_ally,
        "set_flag",
        &LuaCharacter::set_flag,
        "gain_skill",
        sol::overload(
            &LuaCharacter::gain_skill, &LuaCharacter::gain_skill_stock),
        "gain_skill_exp",
        &LuaCharacter::gain_skill_exp,
        "modify_resistance",
        &LuaCharacter::modify_resistance,
        "modify_sanity",
        &LuaCharacter::modify_sanity,
        "modify_karma",
        &LuaCharacter::modify_karma,
        "modify_corruption",
        &LuaCharacter::modify_corruption,
        "make_pregnant",
        &LuaCharacter::make_pregnant,
        "eat_rotten_food",
        &LuaCharacter::eat_rotten_food,

        "hp",
        sol::readonly(&character::hp),
        "max_hp",
        sol::readonly(&character::max_hp),
        "mp",
        sol::readonly(&character::mp),
        "max_mp",
        sol::readonly(&character::max_mp),
        "sp",
        sol::readonly(&character::sp),
        "max_sp",
        sol::readonly(&character::max_sp),
        "shop_rank",
        &character::shop_rank,
        "character_role",
        &character::character_role,
        "index",
        sol::readonly(&character::index),
        "id",
        sol::readonly(&character::id),
        "position",
        &character::position,
        "name",
        sol::property([](character& c) { return elona::cdatan(0, c.index); }),
        "experience",
        &character::experience,

        "sex",
        sol::property(
            [](character& c) {
                return LuaEnums::GenderTable.convert_to_string(c.sex);
            },
            [](character& c, const enum_string& s) {
                c.sex = LuaEnums::GenderTable.ensure_from_string(s);
            }));

    lua.set_usertype(character::lua_type(), LuaCharacter);
}

} // namespace lua
} // namespace elona
