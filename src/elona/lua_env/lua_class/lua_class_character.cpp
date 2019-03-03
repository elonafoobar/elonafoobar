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

/**
 * @luadoc
 *
 * Damages this character.
 * @tparam num amount the amount to damage
 * @tparam[opt] Enums.DamageSource source the source of the damage (defaults to
 * the unseen hand)
 * @usage local chara = Chara.player()
 * chara:damage_hp(100)
 */
void LuaCharacter::damage_hp_source(
    Character& self,
    int amount,
    const EnumString& source)
{
    DamageSource source_value =
        LuaEnums::DamageSourceTable.ensure_from_string(source);
    elona::damage_hp(self, amount, static_cast<int>(source_value));
}

/**
 * @luadoc damage_hp
 *
 * Damages this character, with the source being set as another character.
 * @tparam num amount the amount to damage
 * @tparam LuaCharacter source the character acting as the source of the damage
 * @usage local chara = Chara.player()
 * local other = Chara.create(0, 0, "core.putit")
 * chara:damage_hp(100, other)
 */
void LuaCharacter::damage_hp_chara(
    Character& self,
    int amount,
    LuaCharacterHandle source)
{
    auto& source_ref =
        lua::lua->get_handle_manager().get_ref<Character>(source);
    elona::damage_hp(self, amount, source_ref.index);
}

/**
 * @luadoc
 *
 * Applies a status ailment to this character.
 * @tparam Enums.StatusAilment ailment the kind of status ailment
 * @tparam num power the power of the status ailment
 * @usage local chara = Chara.player()
 * chara:apply_ailment("Blinded", 100)
 */
void LuaCharacter::apply_ailment(
    Character& self,
    const EnumString& ailment,
    int power)
{
    if (power <= 0)
    {
        return;
    }

    StatusAilment ailment_value =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment);
    elona::dmgcon(self.index, ailment_value, power);
}

/**
 * @luadoc
 *
 * Heals a status ailment on a character.
 * @tparam Enums.StatusAilment ailment the kind of status ailment
 * @tparam num power the power of the healing. If 0, heal the ailment
 * completely.
 * @usage local chara = Chara.player()
 * chara:heal_ailment("Blinded", 100)
 */
void LuaCharacter::heal_ailment(
    Character& self,
    const EnumString& ailment,
    int power)
{
    if (power < 0)
    {
        return;
    }

    StatusAilment ailment_value =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment);
    elona::healcon(self.index, ailment_value, power);
}

void LuaCharacter::add_buff(
    Character& self,
    const std::string& id,
    int power,
    int turns)
{
    if (!the_buff_db[id])
    {
        throw sol::error{"No such buff \"" + id + "\""};
    }

    elona::buff_add(self, id, power, turns);
}

/**
 * @luadoc
 *
 * Adds a buff to a character.
 * @tparam string buff_id the buff to add
 * @tparam num power the buff's power
 * @tparam num turns the number of turns the buff will last
 * @tparam[opt] LuaCharacter doer the character who applied this buff
 */
void LuaCharacter::add_buff_doer(
    Character& self,
    const std::string& buff_id,
    int power,
    int turns,
    LuaCharacterHandle doer)
{
    if (!the_buff_db[buff_id])
    {
        throw sol::error{"No such buff \"" + buff_id + "\""};
    }

    auto& doer_ref = lua::lua->get_handle_manager().get_ref<Character>(doer);
    elona::buff_add(self, buff_id, power, turns, doer_ref);
}

/**
 * @luadoc
 *
 * Sets a growth buff of this character.
 * @tparam num index
 * @tparam num power
 */
void LuaCharacter::set_growth_buff(Character& self, int index, int power)
{
    if (index < 0 || index > 10)
    {
        return;
    }

    self.growth_buffs[index] = power;
}

/**
 * @luadoc
 *
 * Attempts to recruit this character as an ally of the player.
 * This will only work if the character isn't already an ally, isn't
 * the player, is alive and the player has a free party slot.
 * @treturn bool true if the character was recruited successfully
 */
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


/**
 * @luadoc
 *
 * Sets a flag on this character. <b>Note</b>: Currently, all flags up
 * to <code>IsQuickTempered</code> are "intrinsic" and are always
 * reset when this character is refreshed each turn. To change these
 * flags, you must call this function inside a handler for
 * <code>Event.EventKind.CharaRefreshed</code>, or the flag will be
 * reset later.
 * @tparam Enums.CharaFlag flag the flag to set
 * @tparam bool value the flag's new value
 * @see Event.EventKind.CharaRefreshed
 * @usage local Event = Elona.require("Event")
 * local Enums = Elona.require("Enums")
 *
 * local function make_invisible(chara)
 * chara:set_flag(Enums.CharaFlag.IsInvisible, true) -- intrinsic, reset on
 * refresh
 * end
 *
 * -- force this flag to be overridden after this character is refreshed.
 * Event.register(Event.EventKind.CharaRefreshed, make_invisible)
 * Event.register(Event.EventKind.CharaCreated, make_invisible)
 */
void LuaCharacter::set_flag(Character& self, const EnumString& flag, bool value)
{
    int flag_value = LuaEnums::CharaFlagTable.ensure_from_string(flag);
    int new_value = value ? 1 : 0;
    self._flags[flag_value] = new_value;
}

/**
 * @luadoc
 *
 * Obtains the skill of the given ID.
 * @tparam num skill Skill ID, from 0 to 599
 * @treturn LuaAbility
 */
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

/**
 * @luadoc gain_skill
 *
 * Makes this character gain a new skill or spell. This only has an
 * effect if the character does not already know the skill/spell.
 * @tparam num skill_id the skill/spell ID
 * @tparam num initial_level the intial skill/spell level
 * @tparam[opt] num initial_stock the initial spell stock for spells
 */
void LuaCharacter::gain_skill_stock(
    Character& self,
    int skill_id,
    int initial_level,
    int initial_stock)
{
    if (skill_id < 0 || skill_id >= 600)
    {
        return;
    }
    elona::chara_gain_skill(self, skill_id, initial_level, initial_stock);
}

/**
 * @luadoc
 *
 * Makes this character gain experience in a skill or spell. This only
 * has an effect if the character already knows the skill/spell.
 * @tparam num skill_id the skill/spell ID
 * @tparam num amount the amount of experience
 */
void LuaCharacter::gain_skill_exp(Character& self, int skill_id, int amount)
{
    if (skill_id < 0 || skill_id >= 600)
    {
        return;
    }
    elona::chara_gain_fixed_skill_exp(self, skill_id, amount);
}

/**
 * @luadoc
 *
 * Modifies this character's resistance. Since the effect is
 * permanent, once your resistance is modified, it will not be reset
 * on refreshing.
 * @tparam num element the corresponding element
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter::modify_resistance(
    Character& self,
    const EnumString& element,
    int delta)
{
    Element element_value = LuaEnums::ElementTable.ensure_from_string(element);
    elona::resistmod(self.index, static_cast<int>(element_value), delta);
}

/**
 * @luadoc
 *
 * Modifies this character's sanity.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
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

/**
 * @luadoc
 *
 * Modifies this character's karma. Currently only has an effect if
 * the character is the player.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter::modify_karma(Character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_karma(self, delta);
}

/**
 * @luadoc
 *
 * Modifies this character's ether corruption. Currently only has an
 * effect if the character is the player.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter::modify_corruption(Character& self, int delta)
{
    if (self.index != 0)
    {
        return;
    }

    elona::modify_ether_disease_stage(delta);
}

/**
 * @luadoc
 *
 * Makes this character pregnant. Only has an effect if the character
 * is not already pregnant.
 */
void LuaCharacter::make_pregnant(Character& self)
{
    int tc_bk = self.index;
    elona::tc = self.index;

    elona::get_pregnant();

    elona::tc = tc_bk;
}

/**
 * @luadoc
 *
 * Applies the effects of eating rotten food to this character.
 */
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

        /**
         * @luadoc index field num
         *
         * [R] The index of this character in the global characters array.
         */
        "index",
        sol::readonly(&Character::index),

        /**
         * @luadoc index field id
         *
         * [R] The prototype ID of this character.
         */
        "id",
        sol::readonly(&Character::id),

        /**
         * @luadoc name field string
         * [R] The character's proper name without any qualifiers.
         */
        "hp",
        sol::readonly(&Character::hp),

        /**
         * @luadoc max_hp field num
         *
         * [R] The character's maximum HP.
         */
        "max_hp",
        sol::readonly(&Character::max_hp),

        /**
         * @luadoc mp field num
         *
         * [R] The character's current MP.
         */
        "mp",
        sol::readonly(&Character::mp),

        /**
         * @luadoc max_mp field num
         *
         * [R] The character's maximum MP.
         */
        "max_mp",
        sol::readonly(&Character::max_mp),

        /**
         * @luadoc sp field num
         *
         * [R] The character's current stamina.
         */
        "sp",
        sol::readonly(&Character::sp),

        /**
         * @luadoc max_sp field num
         *
         * [R] The character's maximum stamina.
         */
        "max_sp",
        sol::readonly(&Character::max_sp),

        /**
         * @luadoc position field LuaPosition
         *
         * [RW] The character's position.
         */
        "position",
        &Character::position,

        /**
         * @luadoc shop_rank field num
         *
         * [RW] The shop rank of this character. Used only if they are a
         * shopkeeper.
         */
        "shop_rank",
        &Character::shop_rank,

        /**
         * @luadoc role field num
         *
         * [RW] The role this character takes on.
         */
        "role",
        &Character::character_role,

        /**
         * @luadoc experience field num
         *
         * [RW] The character's current experience points.
         */
        "experience",
        &Character::experience,

        /**
         * @luadoc fame field num
         *
         * [RW] The character's current fame.
         */
        "fame",
        &Character::fame,

        /**
         * @luadoc talk_type field num
         *
         * [RW] The character's current talk type.
         */
        "talk_type",
        &Character::talk_type,

        /**
         * @luadoc pv field num
         *
         * [RW] The character's current PV. Reset on refresh.
         */
        "pv",
        &Character::pv,

        /**
         * @luadoc dv field num
         *
         * [RW] The character's current DV. Reset on refresh.
         */
        "dv",
        &Character::dv,

        /**
         * @luadoc hit_bonus field num
         *
         * [RW] The character's current hit bonus. Reset on refresh.
         */
        "hit_bonus",
        &Character::hit_bonus,

        /**
         * @luadoc growth_buffs field num
         *
         * [RW] The character's current growth buffs.
         */
        "growth_buffs",
        &Character::growth_buffs,

        /**
         * @luadoc hate field num
         *
         * [RW] The character's current hate.
         */
        "hate",
        &Character::hate,

        /**
         * @luadoc fame field num
         *
         * [RW] The character's current emotion icon. Valid values are 0-99.
         */
        "emotion_icon",
        &Character::emotion_icon,

        /**
         * @luadoc fame field karma
         *
         * [RW] The character's current karma. Only valid if the character is
         * the player.
         */
        "karma",
        &Character::karma,


        /**
         * @luadoc new_id field string
         *
         * [R] The new version prototype ID of the character.
         */
        "new_id",
        sol::property([](Character& c) {
            return the_character_db.get_id_from_legacy(c.id)->get();
        }),

        /**
         * @luadoc name field string
         *
         * [R] The name of the character with article and title.
         */
        "name",
        sol::property([](Character& c) { return elona::name(c.index); }),

        /**
         * @luadoc basename field string
         *
         * [R] The name of the character without article and title.
         */
        "basename",
        sol::property([](Character& c) { return elona::cdatan(0, c.index); }),

        /**
         * @luadoc sex field Gender
         *
         * [RW] The sex of the character.
         */
        "sex",
        sol::property(
            [](Character& c) {
                return LuaEnums::GenderTable.convert_to_string(c.sex);
            },
            [](Character& c, const EnumString& s) {
                c.sex = LuaEnums::GenderTable.ensure_from_string(s);
            }),

        /**
         * @luadoc relationship field Relation
         *
         * [RW] The relationship of the character to the player.
         */
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
