#include "../../../animation.hpp"
#include "../../../character.hpp"
#include "../../enums/enums.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for rendering the built-in animations.
 */
namespace elona::lua::api::modules::module_Animation
{

/**
 * @luadoc play_failure_to_cast
 *
 * Play failure to cast animation.
 *
 * @tparam LuaPosition caster_pos The caster's position.
 */
void Animation_play_failure_to_cast(const Position& caster_pos)
{
    FailureToCastAnimation(caster_pos).play();
}



/**
 * @luadoc play_bright_aura
 *
 * Play bright aura animation.
 *
 * @tparam LuaPosition target_pos The target's position.
 * @tparam number kind The kind of the aura
 */
void Animation_play_bright_aura(const Position& target_pos, int kind)
{
    auto anim_type = static_cast<BrightAuraAnimation::Type>(kind);
    BrightAuraAnimation(target_pos, anim_type).play();
}



/**
 * @luadoc play_breath
 *
 * Play breath animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam Enums.Element element_name The element of the breath
 */
void Animation_play_breath(
    const Position& attacker_pos,
    const Position& target_pos,
    const EnumString& element_name)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    BreathAnimation(attacker_pos, target_pos, static_cast<int>(element)).play();
}



/**
 * @luadoc play_ball_atomic_bomb
 *
 * Play ball atomic bomb animation.
 *
 * @tparam LuaPosition pos The position at which the explosion happens
 * @tparam number range The range of the explosion
 */
void Animation_play_ball_atomic_bomb(const Position& pos, int range)
{
    BallAnimation(pos, range, BallAnimation::Type::atomic_bomb).play();
}



/**
 * @luadoc play_ball_magic
 *
 * Play ball magic animation.
 *
 * @tparam LuaPosition caster_pos The caster's position.
 * @tparam number range The range of the ball
 * @tparam number element The element of the ball
 */
void Animation_play_ball_magic(
    const Position& caster_pos,
    int range,
    int element)
{
    BallAnimation(caster_pos, range, BallAnimation::Type::ball, element).play();
}



/**
 * @luadoc play_bolt
 *
 * Play bolt animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam Enums.Element element_name The element of the bolt
 * @tparam number distance The distance between `attacker_pos` and the tile
 * which the animation lasts to
 */
void Animation_play_bolt(
    const Position& attacker_pos,
    const Position& target_pos,
    const EnumString& element_name,
    int distance)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    BoltAnimation(attacker_pos, target_pos, static_cast<int>(element), distance)
        .play();
}



/**
 * @luadoc play_throwing_object
 *
 * Play throwing object animation.
 *
 * @tparam LuaPosition thrower_pos The thrower's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam number item_chip The item chip of the thrown object
 * @tparam number item_color The item color of the thrown object
 */
void Animation_play_throwing_object(
    const Position& thrower_pos,
    const Position& target_pos,
    int item_chip,
    int item_color)
{
    ThrowingObjectAnimation(thrower_pos, target_pos, item_chip, item_color)
        .play();
}



/**
 * @luadoc play_swarm
 *
 * Play swarm animation.
 *
 * @tparam LuaPosition target_pos The target's position.
 */
void Animation_play_swarm(const Position& target_pos)
{
    SwarmAnimation(target_pos).play();
}



/**
 * @luadoc play_ranged_attack
 *
 * Play ranged attack animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam number kind The kind of the ranged attack
 * @tparam number fired_item_subcategory The fired item subcategory
 * @tparam number fired_item_image The fired item image
 * @tparam number fired_item_color The fired item color
 */
void Animation_play_ranged_attack(
    const Position& attacker_pos,
    const Position& target_pos,
    int kind,
    int fired_item_subcategory,
    int fired_item_image,
    int fired_item_color)
{
    auto anim_type = static_cast<RangedAttackAnimation::Type>(kind);
    RangedAttackAnimation(
        attacker_pos,
        target_pos,
        anim_type,
        fired_item_subcategory,
        fired_item_image,
        fired_item_color)
        .play();
}



/**
 * @luadoc play_melee_attack
 *
 * Play melee attack animation.
 *
 * @tparam LuaPosition target_pos The target's position.
 * @tparam boolean debris Whether the victim breaks into debris like chess
 * pieces.
 * @tparam number attack_skill The attack skill
 * @tparam number damage_percent The damage percentage
 * @tparam boolean is_critical True if the attack is critical.
 */
void Animation_play_melee_attack(
    const Position& target_pos,
    bool debris,
    int attack_skill,
    int damage_percent,
    bool is_critical)
{
    MeleeAttackAnimation(
        target_pos, debris, attack_skill, damage_percent, is_critical)
        .play();
}



/**
 * @luadoc play_gene_engineering
 *
 * Play gene engineering animation.
 *
 * @tparam LuaPosition pos The position of the animation.
 */
void Animation_play_gene_engineering(const Position& pos)
{
    GeneEngineeringAnimation(pos).play();
}



/**
 * @luadoc play_miracle
 *
 * Play miracle animation.
 */
void Animation_play_miracle()
{
    MiracleAnimation(MiracleAnimation::Mode::target_one, cdata.player()).play();
}



/**
 * @luadoc play_meteor
 *
 * Play meteor animation.
 */
void Animation_play_meteor()
{
    MeteorAnimation().play();
}



/**
 * @luadoc play_ragnarok
 *
 * Play The Ragnarok animation.
 */
void Animation_play_ragnarok()
{
    RagnarokAnimation().play();
}



/**
 * @luadoc play_breaking
 *
 * Play breaking animation.
 *
 * @tparam LuaPosition pos The position of the animation
 */
void Animation_play_breaking(const Position& pos)
{
    BreakingAnimation(pos).play();
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("play_failure_to_cast", Animation_play_failure_to_cast);
    ELONA_LUA_API_BIND_FUNCTION("play_bright_aura", Animation_play_bright_aura);
    ELONA_LUA_API_BIND_FUNCTION("play_breath", Animation_play_breath);
    ELONA_LUA_API_BIND_FUNCTION("play_ball_atomic_bomb", Animation_play_ball_atomic_bomb);
    ELONA_LUA_API_BIND_FUNCTION("play_ball_magic", Animation_play_ball_magic);
    ELONA_LUA_API_BIND_FUNCTION("play_bolt", Animation_play_bolt);
    ELONA_LUA_API_BIND_FUNCTION("play_throwing_object", Animation_play_throwing_object);
    ELONA_LUA_API_BIND_FUNCTION("play_swarm", Animation_play_swarm);
    ELONA_LUA_API_BIND_FUNCTION("play_ranged_attack", Animation_play_ranged_attack);
    ELONA_LUA_API_BIND_FUNCTION("play_melee_attack", Animation_play_melee_attack);
    ELONA_LUA_API_BIND_FUNCTION("play_gene_engineering", Animation_play_gene_engineering);
    ELONA_LUA_API_BIND_FUNCTION("play_miracle", Animation_play_miracle);
    ELONA_LUA_API_BIND_FUNCTION("play_meteor", Animation_play_meteor);
    ELONA_LUA_API_BIND_FUNCTION("play_ragnarok", Animation_play_ragnarok);
    ELONA_LUA_API_BIND_FUNCTION("play_breaking", Animation_play_breaking);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Animation
