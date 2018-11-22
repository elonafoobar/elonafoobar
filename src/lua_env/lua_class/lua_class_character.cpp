#include "lua_class_character.hpp"
#include "../../ability.hpp"
#include "../../buff.hpp"
#include "../../character.hpp"
#include "../../character_status.hpp"
#include "../../dmgheal.hpp"
#include "../../element.hpp"
#include "../../enums.hpp"
#include "../../food.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../lua_env/interface.hpp"
#include "lua_class_ability.hpp"

namespace elona
{
namespace lua
{

void LuaCharacter::damage_hp(Character& self, int amount)
{
    LuaCharacter::damage_hp_source(self, amount, "UnseenHand");
}

void LuaCharacter::damage_hp_source(
    Character& self,
    int amount,
    const EnumString& source_name)
{
    DamageSource source =
        LuaEnums::DamageSourceTable.ensure_from_string(source_name);
    elona::damage_hp(self, amount, static_cast<int>(source));
}

void LuaCharacter::damage_hp_chara(
    Character& self,
    int amount,
    LuaCharacterHandle handle)
{
    auto& other = lua::lua->get_handle_manager().get_ref<Character>(handle);
    elona::damage_hp(self, amount, other.index);
}

void LuaCharacter::apply_ailment(
    Character& self,
    const EnumString& ailment_name,
    int power)
{
    if (power <= 0)
    {
        return;
    }

    StatusAilment ailment =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment_name);
    elona::dmgcon(self.index, ailment, power);
}

void LuaCharacter::heal_ailment(
    Character& self,
    const EnumString& ailment_name,
    int power)
{
    if (power < 0)
    {
        return;
    }

    StatusAilment ailment =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment_name);
    elona::healcon(self.index, ailment, power);
}

void LuaCharacter::add_buff(
    Character& self,
    const std::string& id,
    int power,
    int turns)
{
    elona::buff_add(self, id, power, turns);
}

void LuaCharacter::add_buff_doer(
    Character& self,
    const std::string& id,
    int power,
    int turns,
    LuaCharacterHandle doer_handle)
{
    auto& doer = lua::lua->get_handle_manager().get_ref<Character>(doer_handle);
    elona::buff_add(self, id, power, turns, doer);
}

void LuaCharacter::set_growth_buff(Character& self, int index, int power)
{
    if (index < 0 || index > 10)
    {
        return;
    }

    self.growth_buffs[index] = power;
}

bool LuaCharacter::recruit_as_ally(Character& self)
{
    if (self.state() == Character::State::empty ||
        (self.index != 0 && self.index <= 16) || self.index == 0)
    {
        return false;
    }
    elona::rc = self.index;
    return new_ally_joins() == 1;
}

void LuaCharacter::set_flag(
    Character& self,
    const std::string& flag_name,
    bool is_setting)
{
    int flag = LuaEnums::CharaFlagTable.ensure_from_string(flag_name);
    int new_value = (is_setting ? 1 : 0);
    self._flags[flag] = new_value;
}

sol::optional<LuaAbility> LuaCharacter::get_skill(Character& self, int skill)
{
    if (skill < 0 || skill >= 600)
    {
        return sol::nullopt;
    }

    auto handle = lua::handle(self);
    assert(handle != sol::lua_nil);

    std::string uuid = handle["__uuid"];
    return LuaAbility(skill, self.index, Character::lua_type(), uuid);
}

void LuaCharacter::gain_skill(Character& self, int skill, int initial_level)
{
    LuaCharacter::gain_skill_stock(self, skill, initial_level, 0);
}

void LuaCharacter::gain_skill_stock(
    Character& self,
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

void LuaCharacter::gain_skill_exp(Character& self, int skill, int amount)
{
    if (skill < 0 || skill >= 600)
    {
        return;
    }
    elona::chara_gain_fixed_skill_exp(self, skill, amount);
}

void LuaCharacter::modify_resistance(
    Character& self,
    const EnumString& element_name,
    int delta)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    elona::resistmod(self.index, static_cast<int>(element), delta);
}

void LuaCharacter::modify_sanity(Character& self, int delta)
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

void LuaCharacter::modify_karma(Character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_karma(self, delta);
}

void LuaCharacter::modify_corruption(Character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_ether_disease_stage(delta);
}

void LuaCharacter::make_pregnant(Character& self)
{
    int tc_bk = self.index;
    elona::tc = self.index;

    elona::get_pregnant();

    elona::tc = tc_bk;
}

void LuaCharacter::eat_rotten_food(Character& self)
{
    int cc_bk = self.index;
    elona::cc = self.index;

    elona::eat_rotten_food();

    elona::cc = cc_bk;
}

void LuaCharacter::bind(sol::state& lua)
{
    // new_usertype generates a massive amount of code and refuses to compile
    // after a certain point, due to there being so many fields. However,
    // variables/properties have to be set on the usertype at initialization,
    // because __index is overridden all at once, so at some point something
    // will have to change...

    sol::usertype<Character> LuaCharacter(
        "lua_type",
        &Character::lua_type,

        // Variables
        "index",
        sol::readonly(&Character::index),
        "id",
        sol::readonly(&Character::id),
        "hp",
        sol::readonly(&Character::hp),
        "max_hp",
        sol::readonly(&Character::max_hp),
        "mp",
        sol::readonly(&Character::mp),
        "max_mp",
        sol::readonly(&Character::max_mp),
        "sp",
        sol::readonly(&Character::sp),
        "max_sp",
        sol::readonly(&Character::max_sp),
        "position",
        &Character::position,
        "shop_rank",
        &Character::shop_rank,
        "role",
        &Character::character_role,
        "experience",
        &Character::experience,
        "fame",
        &Character::fame,
        "talk_type",
        &Character::talk_type,
        "pv",
        &Character::pv,
        "dv",
        &Character::dv,
        "hit_bonus",
        &Character::hit_bonus,
        "growth_buffs",
        &Character::growth_buffs,

        // Properties
        "new_id",
        sol::property([](Character& c) {
            return the_character_db.get_id_from_legacy(c.id)->get();
        }),
        "name",
        sol::property([](Character& c) { return elona::name(c.index); }),
        "basename",
        sol::property([](Character& c) { return elona::cdatan(0, c.index); }),

        "sex",
        sol::property(
            [](Character& c) {
                return LuaEnums::GenderTable.convert_to_string(c.sex);
            },
            [](Character& c, const EnumString& s) {
                c.sex = LuaEnums::GenderTable.ensure_from_string(s);
            }),
        "relationship",
        sol::property(
            [](Character& c) {
                return LuaEnums::RelationTable.convert_to_string(
                    c.relationship);
            },
            [](Character& c, const EnumString& s) {
                c.relationship = LuaEnums::RelationTable.ensure_from_string(s);
            }));

    auto key = Character::lua_type();
    lua.set_usertype(key, LuaCharacter);

    // Methods
    lua[key]["damage_hp"] = sol::overload(
        &LuaCharacter::damage_hp,
        &LuaCharacter::damage_hp_source,
        &LuaCharacter::damage_hp_chara),
    lua[key]["apply_ailment"] = &LuaCharacter::apply_ailment;
    lua[key]["heal_ailment"] = &LuaCharacter::heal_ailment;
    lua[key]["add_buff"] =
        sol::overload(&LuaCharacter::add_buff, &LuaCharacter::add_buff_doer);
    lua[key]["set_growth_buff"] = &LuaCharacter::set_growth_buff;
    lua[key]["recruit_as_ally"] = &LuaCharacter::recruit_as_ally;
    lua[key]["set_flag"] = &LuaCharacter::set_flag;
    lua[key]["get_skill"] = &LuaCharacter::get_skill;
    lua[key]["gain_skill"] = sol::overload(
        &LuaCharacter::gain_skill, &LuaCharacter::gain_skill_stock);
    lua[key]["gain_skill_exp"] = &LuaCharacter::gain_skill_exp;
    lua[key]["modify_resistance"] = &LuaCharacter::modify_resistance;
    lua[key]["modify_sanity"] = &LuaCharacter::modify_sanity;
    lua[key]["modify_karma"] = &LuaCharacter::modify_karma;
    lua[key]["modify_corruption"] = &LuaCharacter::modify_corruption;
    lua[key]["make_pregnant"] = &LuaCharacter::make_pregnant;
    lua[key]["eat_rotten_food"] = &LuaCharacter::eat_rotten_food;
}

} // namespace lua
} // namespace elona
