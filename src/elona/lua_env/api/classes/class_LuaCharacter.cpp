#include "../../../ability.hpp"
#include "../../../buff.hpp"
#include "../../../character.hpp"
#include "../../../character_status.hpp"
#include "../../../data/types/type_ability.hpp"
#include "../../../data/types/type_buff.hpp"
#include "../../../dmgheal.hpp"
#include "../../../element.hpp"
#include "../../../enums.hpp"
#include "../../../food.hpp"
#include "../../../god.hpp"
#include "../../../map_cell.hpp"
#include "../../../status_ailment.hpp"
#include "../../../text.hpp"
#include "../../../ui.hpp"
#include "../../../variables.hpp"
#include "../../data_manager.hpp"
#include "../../enums/enums.hpp"
#include "../../interface.hpp"
#include "../common.hpp"
#include "class_LuaAbility.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Character)



/**
 * @luadoc
 *
 * Represents a character.
 */
namespace elona::lua::api::classes::class_LuaCharacter
{

/**
 * @luadoc damage_hp
 *
 * Damages this character.
 * @tparam num amount the amount to damage
 * @tparam[opt] Enums.DamageSource source the source of the damage (defaults to
 * the unseen hand)
 * @usage local chara = Chara.player()
 * chara:damage_hp(100)
 */
void LuaCharacter_damage_hp_source(
    Character& self,
    int amount,
    const EnumString& source)
{
    DamageSource source_value =
        LuaEnums::DamageSourceTable.ensure_from_string(source);
    elona::damage_hp(self, amount, static_cast<int>(source_value));
}



void LuaCharacter_damage_hp(Character& self, int amount)
{
    LuaCharacter_damage_hp_source(self, amount, "unseen_hand");
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
void LuaCharacter_damage_hp_chara(
    Character& self,
    int amount,
    LuaCharacterHandle source)
{
    auto& source_ref = lua::ref<Character>(source);
    elona::damage_hp(self, amount, source_ref.index);
}



/**
 * @luadoc apply_ailment
 *
 * Applies a status ailment to this character.
 * @tparam Enums.StatusAilment ailment the kind of status ailment
 * @tparam num power the power of the status ailment
 * @usage local chara = Chara.player()
 * chara:apply_ailment("Blinded", 100)
 */
void LuaCharacter_apply_ailment(
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
    elona::status_ailment_damage(self, ailment_value, power);
}



/**
 * @luadoc heal_ailment
 *
 * Heals a status ailment on a character.
 * @tparam Enums.StatusAilment ailment the kind of status ailment
 * @tparam num power the power of the healing. If 0, heal the ailment
 * completely.
 * @usage local chara = Chara.player()
 * chara:heal_ailment("Blinded", 100)
 */
void LuaCharacter_heal_ailment(
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
    elona::status_ailment_heal(self, ailment_value, power);
}



void LuaCharacter_add_buff(
    Character& self,
    const std::string& buff_id,
    int power,
    int turns)
{
    the_buff_db.ensure(data::InstanceId{buff_id});

    elona::buff_add(self, data::InstanceId{buff_id}, power, turns);
}



/**
 * @luadoc add_buff
 *
 * Adds a buff to a character.
 * @tparam string buff_id the buff to add
 * @tparam num power the buff's power
 * @tparam num turns the number of turns the buff will last
 * @tparam[opt] LuaCharacter doer the character who applied this buff
 */
void LuaCharacter_add_buff_doer(
    Character& self,
    const std::string& buff_id,
    int power,
    int turns,
    LuaCharacterHandle doer)
{
    the_buff_db.ensure(data::InstanceId{buff_id});

    auto& doer_ref = lua::ref<Character>(doer);
    elona::buff_add(self, data::InstanceId{buff_id}, power, turns, doer_ref);
}



/**
 * @luadoc set_growth_buff
 *
 * Sets a growth buff of this character.
 * @tparam num index
 * @tparam num power
 */
void LuaCharacter_set_growth_buff(Character& self, int index, int power)
{
    if (index < 0 || index > 10)
    {
        return;
    }

    self.growth_buffs[index] = power;
}



/**
 * @luadoc recruit_as_ally
 *
 * Attempts to recruit this character as an ally of the player.
 * This will only work if the character isn't already an ally, isn't
 * the player, is alive and the player has a free party slot.
 * @treturn bool true if the character was recruited successfully
 */
bool LuaCharacter_recruit_as_ally(Character& self)
{
    if (self.state() == Character::State::empty || self.is_player_or_ally())
    {
        return false;
    }
    return !!new_ally_joins(self);
}



/**
 * @luadoc get_flag
 *
 * Gets the value of a flag on this character.
 * @tparam Enums.CharaFlag flag the flag to get
 * @treturn bool
 */
bool LuaCharacter_get_flag(Character& chara, const EnumString& flag)
{
    int flag_value = LuaEnums::CharaFlagTable.ensure_from_string(flag);
    return chara._flags[flag_value] == 1;
}



/**
 * @luadoc set_flag
 *
 * Sets the value of a flag on this character. <b>Note</b>: Currently, all
 * flags up to <code>is_quick_tempered</code> are "intrinsic" and are always
 * reset when this character is refreshed each turn. To change these flags, you
 * must call this function inside a handler for
 * <code>core.character_refreshed</code>, or the flag will be reset later.
 * @tparam Enums.CharaFlag flag the flag to set
 * @tparam bool value the flag's new value
 * @see core.event
 * @usage local Event = ELONA.require("core.Event")
 *
 * local function make_invisible(e)
 * e.chara:set_flag("is_invisible", true) -- intrinsic, reset on refresh
 * end
 *
 * -- force this flag to be overridden after this character is refreshed.
 * Event.register("core.character_refreshed", make_invisible)
 * Event.register("core.character_created", make_invisible)
 */
void LuaCharacter_set_flag(Character& self, const EnumString& flag, bool value)
{
    int flag_value = LuaEnums::CharaFlagTable.ensure_from_string(flag);
    int new_value = value ? 1 : 0;
    self._flags[flag_value] = new_value;
}



/**
 * @luadoc get_skill
 *
 * Obtains the skill of the given ID.
 * @tparam string skill_id ID of type core.ability
 * @treturn LuaAbility
 */
sol::optional<LuaAbility> LuaCharacter_get_skill(
    Character& self,
    const std::string& skill_id)
{
    auto data = the_ability_db[data::InstanceId{skill_id}];
    if (!data)
    {
        return sol::nullopt;
    }

    return LuaAbility(data->integer_id, self.obj_id);
}



/**
 * @luadoc gain_skill
 *
 * Makes this character gain a new skill or spell. This only has an
 * effect if the character does not already know the skill/spell.
 * @tparam string skill_id the skill/spell ID of type core.ability
 * @tparam num initial_level the intial skill/spell level
 * @tparam[opt] num initial_stock the initial spell stock for spells
 */
void LuaCharacter_gain_skill_stock(
    Character& self,
    const std::string& skill_id,
    int initial_level,
    int initial_stock)
{
    auto data = the_ability_db[data::InstanceId{skill_id}];
    if (!data)
    {
        return;
    }
    elona::chara_gain_skill(
        self, data->integer_id, initial_level, initial_stock);
}



void LuaCharacter_gain_skill(
    Character& self,
    const std::string& skill_id,
    int initial_level)
{
    LuaCharacter_gain_skill_stock(self, skill_id, initial_level, 0);
}



/**
 * @luadoc gain_skill_exp
 *
 * Makes this character gain experience in a skill or spell. This only
 * has an effect if the character already knows the skill/spell.
 * @tparam string skill_id the skill/spell ID of type core.ability
 * @tparam num amount the amount of experience
 */
void LuaCharacter_gain_skill_exp(
    Character& self,
    const std::string& skill_id,
    int amount)
{
    auto data = the_ability_db[data::InstanceId{skill_id}];
    if (!data)
    {
        return;
    }
    elona::chara_gain_fixed_skill_exp(self, data->integer_id, amount);
}



/**
 * @luadoc modify_resistance
 *
 * Modifies this character's resistance. Since the effect is
 * permanent, once your resistance is modified, it will not be reset
 * on refreshing.
 * @tparam num element the corresponding element
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter_modify_resistance(
    Character& self,
    const EnumString& element,
    int delta)
{
    Element element_value = LuaEnums::ElementTable.ensure_from_string(element);
    elona::chara_gain_registance(self, static_cast<int>(element_value), delta);
}



/**
 * @luadoc modify_sanity
 *
 * Modifies this character's sanity.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter_modify_sanity(Character& self, int delta)
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
 * @luadoc modify_karma
 *
 * Modifies this character's karma. Currently only has an effect if
 * the character is the player.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter_modify_karma(Character& self, int delta)
{
    if (!self.is_player())
    {
        return;
    }

    elona::modify_karma(self, delta);
}



/**
 * @luadoc modify_corruption
 *
 * Modifies this character's ether corruption. Currently only has an
 * effect if the character is the player.
 * @tparam num delta the amount of increase/decrease (can be negative)
 */
void LuaCharacter_modify_corruption(Character& self, int delta)
{
    if (!self.is_player())
    {
        return;
    }

    elona::modify_ether_disease_stage(delta);
}



/**
 * @luadoc make_pregnant
 *
 * Makes this character pregnant. Only has an effect if the character
 * is not already pregnant.
 */
void LuaCharacter_make_pregnant(Character& self)
{
    elona::get_pregnant(self);
}



/**
 * @luadoc eat_rotten_food
 *
 * Applies the effects of eating rotten food to this character.
 */
void LuaCharacter_eat_rotten_food(Character& self)
{
    elona::eat_rotten_food(self);
}



/**
 * @luadoc vanquish
 *
 * Deletes this character and removes it from the map. The character will no
 * longer be valid for use.
 */
void LuaCharacter_vanquish(Character& self)
{
    chara_vanquish(self);
}



/**
 * @luadoc act_hostile_against
 *
 * Applies the effects of acting hostile towards a target character.
 * @tparam LuaCharacter target Target to act hostile towards
 */
void LuaCharacter_act_hostile_against(
    Character& self,
    LuaCharacterHandle target)
{
    auto& target_ref = lua::ref<Character>(target);
    chara_act_hostile_action(self, target_ref);
}



/**
 * @luadoc refresh
 *
 * Refreshes this character, reapplying bonuses given by equipment.
 */
void LuaCharacter_refresh(Character& self)
{
    chara_refresh(self);
}



/**
 * @luadoc refresh_burden_state
 *
 * Refreshes the burden state of this character. Only valid if called on the
 * player. Call this method if the character's inventory changes so the weight
 * can be reapplied.
 */
void LuaCharacter_refresh_burden_state(Character& self)
{
    if (!self.is_player())
    {
        return;
    }

    elona::refresh_burden_state();
}



/**
 * @luadoc move_to
 *
 * Moves this character to a new position.
 * @tparam num x
 * @tparam num y
 */
void LuaCharacter_move_to_xy(Character& self, int x, int y)
{
    // NOTE: setting self.next_position may be safer if the position is changed
    // in the middle of the current turn.
    cell_movechara(self, x, y);

    if (self.is_player())
    {
        update_screen();
    }
}



/**
 * @luadoc move_to
 *
 * Moves this character to a new position.
 * @tparam LuaPosition pos
 */
void LuaCharacter_move_to(Character& self, Position& pos)
{
    LuaCharacter_move_to_xy(self, pos.x, pos.y);
}



/**
 * @luadoc switch_religion
 *
 * Changes the worshipped god of this character without invoking the god
 * switching penalty.
 * @tparam string god_id ID of type core.god.
 */
void LuaCharacter_switch_religion(Character& self, const std::string& god_id)
{
    the_god_db.ensure(data::InstanceId{god_id});

    self.god_id = god_id;
    elona::switch_religion();
}



/**
 * @luadoc get_ailment
 *
 * Returns the duration of an ailment on this character.
 * @tparam StatusAilment ailment
 * @treturn num
 */
int LuaCharacter_get_ailment(Character& self, const EnumString& ailment)
{
    StatusAilment ailment_value =
        LuaEnums::StatusAilmentTable.ensure_from_string(ailment);

    switch (ailment_value)
    {
    case StatusAilment::blinded: return self.blind;
    case StatusAilment::confused: return self.confused;
    case StatusAilment::paralyzed: return self.paralyzed;
    case StatusAilment::poisoned: return self.poisoned;
    case StatusAilment::sleep: return self.sleep;
    case StatusAilment::fear: return self.fear;
    case StatusAilment::dimmed: return self.dimmed;
    case StatusAilment::bleeding: return self.bleeding;
    case StatusAilment::drunk: return self.drunk;
    case StatusAilment::insane: return self.insane;
    case StatusAilment::sick: return self.sick;
    }

    return 0;
}



std::string LuaCharacter_metamethod_tostring(const Character& self)
{
    return Character::lua_type() + "(" + self.obj_id.to_string() + ")";
}



void bind(sol::state& lua)
{
    auto LuaCharacter =
        lua.new_usertype<Character>("LuaCharacter", sol::no_constructor);
    LuaCharacter.set("lua_type", &Character::lua_type);

    // Properties

    /**
     * @luadoc index field num
     *
     * [R] The index of this character in the global characters array.
     */
    LuaCharacter.set("index", sol::readonly(&Character::index));

    /**
     * @luadoc integer_id field num
     *
     * [R] The integer ID of this character.
     */
    LuaCharacter.set("integer_id", sol::readonly(&Character::id));

    /**
     * @luadoc hp field string
     * [R] The character's proper name without any qualifiers.
     */
    LuaCharacter.set("hp", sol::readonly(&Character::hp));

    /**
     * @luadoc max_hp field num
     *
     * [R] The character's maximum HP.
     */
    LuaCharacter.set("max_hp", sol::readonly(&Character::max_hp));

    /**
     * @luadoc sp field num
     *
     * [R] The character's current stamina.
     */
    LuaCharacter.set("sp", sol::readonly(&Character::sp));

    /**
     * @luadoc max_sp field num
     *
     * [R] The character's maximum stamina.
     */
    LuaCharacter.set("max_sp", sol::readonly(&Character::max_sp));

    /**
     * @luadoc mp field num
     *
     * [R] The character's current MP.
     */
    LuaCharacter.set("mp", sol::readonly(&Character::mp));

    /**
     * @luadoc max_mp field num
     *
     * [R] The character's maximum MP.
     */
    LuaCharacter.set("max_mp", sol::readonly(&Character::max_mp));

    /**
     * @luadoc god field string
     *
     * [RW] The character's worshipped god.
     */
    LuaCharacter.set("god", &Character::god_id);

    /**
     * @luadoc position field LuaPosition
     *
     * [RW] The character's position.
     */
    LuaCharacter.set("position", &Character::position);

    /**
     * @luadoc initial_position field LuaPosition
     *
     * [RW] The character's initial position.
     */
    LuaCharacter.set("initial_position", &Character::initial_position);

    /**
     * @luadoc shop_rank field num
     *
     * [RW] The shop rank of this character. Used only if they are a
     * shopkeeper.
     */
    LuaCharacter.set("shop_rank", &Character::shop_rank);

    /**
     * @luadoc role field num
     *
     * [RW] The role this character takes on.
     */
    LuaCharacter.set("role", &Character::role);

    /**
     * @luadoc gold field num
     *
     * [RW] The character's current gold.
     */
    LuaCharacter.set("gold", &Character::gold);

    /**
     * @luadoc experience field num
     *
     * [RW] The character's current experience points.
     */
    LuaCharacter.set("experience", &Character::experience);

    /**
     * @luadoc fame field num
     *
     * [RW] The character's current fame.
     */
    LuaCharacter.set("fame", &Character::fame);

    /**
     * @luadoc level field num
     *
     * [RW] The character's current level.
     */
    LuaCharacter.set("level", &Character::level);

    /**
     * @luadoc talk_type field num
     *
     * [RW] The character's current talk type.
     */
    LuaCharacter.set("talk_type", &Character::talk_type);

    /**
     * @luadoc pv field num
     *
     * [RW] The character's current PV. Reset on refresh.
     */
    LuaCharacter.set("pv", &Character::pv);

    /**
     * @luadoc dv field num
     *
     * [RW] The character's current DV. Reset on refresh.
     */
    LuaCharacter.set("dv", &Character::dv);

    /**
     * @luadoc hit_bonus field num
     *
     * [RW] The character's current hit bonus. Reset on refresh.
     */
    LuaCharacter.set("hit_bonus", &Character::hit_bonus);

    /**
     * @luadoc growth_buffs field num
     *
     * [RW] The character's current growth buffs.
     */
    LuaCharacter.set("growth_buffs", &Character::growth_buffs);

    /**
     * @luadoc hate field num
     *
     * [RW] The character's current hate.
     */
    LuaCharacter.set("hate", &Character::hate);

    /**
     * @luadoc emotion_icon field num
     *
     * [RW] The character's current emotion icon. Valid values are 0-99.
     */
    LuaCharacter.set("emotion_icon", &Character::emotion_icon);

    /**
     * @luadoc karma field num
     *
     * [RW] The character's current karma. Only valid if the character is
     * the player.
     */
    LuaCharacter.set("karma", &Character::karma);

    /**
     * @luadoc enemy_id field num
     *
     * [RW] The index of a character this character is targeting..
     */
    LuaCharacter.set("enemy_id", &Character::enemy_id);

    /**
     * @luadoc image field num
     *
     * [RW] The character's current image.
     */
    LuaCharacter.set("image", &Character::image);

    /**
     * @luadoc portrait field string
     *
     * [RW] The character's current portrait.
     */
    LuaCharacter.set("portrait", &Character::portrait);

    /**
     * @luadoc impression field num
     *
     * [RW] The character's current impression.
     */
    LuaCharacter.set("impression", &Character::impression);

    /**
     * @luadoc interest field num
     *
     * [RW] The character's current interest.
     */
    LuaCharacter.set("interest", &Character::interest);

    /**
     * @luadoc ai_calm field num
     *
     * [RW] The character's AI calmness.
     */
    LuaCharacter.set("ai_calm", &Character::ai_calm);


    /**
     * @luadoc id field string
     *
     * [R] The new-style version prototype ID of the character.
     */
    LuaCharacter.set(
        "id", sol::property([](Character& c) { return c.new_id().get(); }));

    /**
     * @luadoc name field string
     *
     * [R] The name of the character with article and title.
     */
    LuaCharacter.set("name", sol::property([](Character& c) {
                         return elona::name(c.index);
                     }));

    /**
     * @luadoc basename field string
     *
     * [R] The name of the character without article and title.
     */
    LuaCharacter.set(
        "basename",
        sol::property(
            [](Character& c) { return c.name; },
            [](Character& c, const std::string& s) { c.name = s; }));

    /**
     * @luadoc alias field string
     *
     * [R] The alias of the character.
     */
    LuaCharacter.set(
        "alias", sol::property([](Character& c) { return c.alias; }));

    /**
     * @luadoc sex field Gender
     *
     * [RW] The sex of the character.
     */
    LuaCharacter.set("sex", LUA_API_ENUM_PROPERTY(Character, sex, Gender));

    /**
     * @luadoc relationship field Relationship
     *
     * [RW] The relationship of the character to the player.
     */
    LuaCharacter.set(
        "relationship",
        LUA_API_ENUM_PROPERTY(Character, relationship, Relationship));

    /**
     * @luadoc original_relationship field Relationship
     *
     * [RW] The original relationship of the character to the player.
     */
    LuaCharacter.set(
        "original_relationship",
        LUA_API_ENUM_PROPERTY(Character, original_relationship, Relationship));

    /**
     * @luadoc quality field Quality
     *
     * [RW] The quality of the character.
     */
    LuaCharacter.set("quality", &Character::quality);

    /**
     * @luadoc prototype field table
     *
     * [R] The prototype data of the character.
     */
    LuaCharacter.set("prototype", sol::property([](Character& self) {
                         return *lua::lua->get_data_manager().get().raw(
                             "core.chara", self.new_id());
                     }));

    // Methods
    LuaCharacter.set(
        "damage_hp",
        sol::overload(
            &LuaCharacter_damage_hp,
            &LuaCharacter_damage_hp_source,
            &LuaCharacter_damage_hp_chara));
    LuaCharacter.set("apply_ailment", &LuaCharacter_apply_ailment);
    LuaCharacter.set("heal_ailment", &LuaCharacter_heal_ailment);
    LuaCharacter.set(
        "add_buff",
        sol::overload(&LuaCharacter_add_buff, &LuaCharacter_add_buff_doer));
    LuaCharacter.set("set_growth_buff", &LuaCharacter_set_growth_buff);
    LuaCharacter.set("recruit_as_ally", &LuaCharacter_recruit_as_ally);
    LuaCharacter.set("get_flag", &LuaCharacter_get_flag);
    LuaCharacter.set("set_flag", &LuaCharacter_set_flag);
    LuaCharacter.set("get_skill", &LuaCharacter_get_skill);
    LuaCharacter.set(
        "gain_skill",
        sol::overload(
            &LuaCharacter_gain_skill, &LuaCharacter_gain_skill_stock));
    LuaCharacter.set("gain_skill_exp", &LuaCharacter_gain_skill_exp);
    LuaCharacter.set("modify_resistance", &LuaCharacter_modify_resistance);
    LuaCharacter.set("modify_sanity", &LuaCharacter_modify_sanity);
    LuaCharacter.set("modify_karma", &LuaCharacter_modify_karma);
    LuaCharacter.set("modify_corruption", &LuaCharacter_modify_corruption);
    LuaCharacter.set("make_pregnant", &LuaCharacter_make_pregnant);
    LuaCharacter.set("eat_rotten_food", &LuaCharacter_eat_rotten_food);
    LuaCharacter.set("vanquish", &LuaCharacter_vanquish);
    LuaCharacter.set("act_hostile_against", &LuaCharacter_act_hostile_against);
    LuaCharacter.set("refresh", &LuaCharacter_refresh);
    LuaCharacter.set(
        "refresh_burden_state", &LuaCharacter_refresh_burden_state);
    LuaCharacter.set(
        "move_to",
        sol::overload(&LuaCharacter_move_to, &LuaCharacter_move_to_xy));
    LuaCharacter.set("switch_religion", &LuaCharacter_switch_religion);
    LuaCharacter.set("get_ailment", &LuaCharacter_get_ailment);

    LuaCharacter.set("__tostring", &LuaCharacter_metamethod_tostring);
}

} // namespace elona::lua::api::classes::class_LuaCharacter
