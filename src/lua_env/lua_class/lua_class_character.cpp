#include "lua_class_character.hpp"
#include "../../ability.hpp"
#include "../../character.hpp"
#include "../../character_status.hpp"
#include "../../dmgheal.hpp"
#include "../../element.hpp"
#include "../../food.hpp"

namespace elona
{
namespace lua
{

void LuaCharacter::damage_hp(character& self, int amount)
{
    LuaCharacter::damage_hp_source(self, amount, damage_source_t::unseen_hand);
}

void LuaCharacter::damage_hp_source(
    character& self,
    int amount,
    damage_source_t source)
{
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
    status_ailment_t ailment,
    int power)
{
    assert(power > 0);
    elona::dmgcon(self.index, ailment, power);
}

bool LuaCharacter::recruit_as_ally(character& self)
{
    // can't use Chara methods because they take a handle...
    // TODO: DRY (would need to be far-reaching)
    if (self.state() == character::state_t::empty
        || (self.index != 0 && self.index <= 16) || self.index == 0)
    {
        return false;
    }
    elona::rc = self.index;
    return new_ally_joins() == 1;
}

void LuaCharacter::set_flag(character& self, int flag, bool value)
{
    if (flag < 5 || flag > 991 || (flag > 32 && flag < 960))
    {
        return;
    }
    self._flags[flag] = value ? 1 : 0;
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

void LuaCharacter::modify_resistance(character& self, int element, int delta)
{
    elona::resistmod(self.index, element, delta);
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
        &character::experience);

    lua.set_usertype(character::lua_type(), LuaCharacter);
}

} // namespace lua
} // namespace elona
