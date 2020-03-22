#include "lua_api_animation.hpp"

#include "../../animation.hpp"
#include "../../lua_env/enums/enums.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Play failure to cast animation.
 *
 * @tparam LuaPosition caster_pos The caster's position.
 */
void LuaApiAnimation::play_failure_to_cast(const Position& caster_pos)
{
    FailureToCastAnimation(caster_pos).play();
}



/**
 * @luadoc
 *
 * Play bright aura animation.
 *
 * @tparam LuaPosition target_pos The target's position.
 * @tparam number kind The kind of the aura
 */
void LuaApiAnimation::play_bright_aura(const Position& target_pos, int kind)
{
    auto anim_type = static_cast<BrightAuraAnimation::Type>(kind);
    BrightAuraAnimation(target_pos, anim_type).play();
}



/**
 * @luadoc
 *
 * Play breath animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam Enums.Element element_name The element of the breath
 */
void LuaApiAnimation::play_breath(
    const Position& attacker_pos,
    const Position& target_pos,
    const EnumString& element_name)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    BreathAnimation(attacker_pos, target_pos, static_cast<int>(element)).play();
}



/**
 * @luadoc
 *
 * Play ball atomic bomb animation.
 *
 * @tparam LuaPosition pos The position at which the explosion happens
 * @tparam number range The range of the explosion
 */
void LuaApiAnimation::play_ball_atomic_bomb(const Position& pos, int range)
{
    BallAnimation(pos, range, BallAnimation::Type::atomic_bomb).play();
}



/**
 * @luadoc
 *
 * Play ball magic animation.
 *
 * @tparam LuaPosition caster_pos The caster's position.
 * @tparam number range The range of the ball
 * @tparam number element The element of the ball
 */
void LuaApiAnimation::play_ball_magic(
    const Position& caster_pos,
    int range,
    int element)
{
    BallAnimation(caster_pos, range, BallAnimation::Type::ball, element).play();
}



/**
 * @luadoc
 *
 * Play bolt animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam Enums.Element element_name The element of the bolt
 * @tparam number distance The distance between `attacker_pos` and the tile
 * which the animation lasts to
 */
void LuaApiAnimation::play_bolt(
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
 * @luadoc
 *
 * Play throwing object animation.
 *
 * @tparam LuaPosition attacker_pos The attacker's position.
 * @tparam LuaPosition target_pos The target's position.
 * @tparam number item_chip The item chip of the thrown object
 * @tparam number item_color The item color of the thrown object
 */
void LuaApiAnimation::play_throwing_object(
    const Position& attacker_pos,
    const Position& target_pos,
    int item_chip,
    int item_color)
{
    ThrowingObjectAnimation(target_pos, attacker_pos, item_chip, item_color)
        .play();
}



/**
 * @luadoc
 *
 * Play swarm animation.
 *
 * @tparam LuaPosition target_pos The target's position.
 */
void LuaApiAnimation::play_swarm(const Position& target_pos)
{
    SwarmAnimation(target_pos).play();
}



/**
 * @luadoc
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
void LuaApiAnimation::play_ranged_attack(
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
 * @luadoc
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
void LuaApiAnimation::play_melee_attack(
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
 * @luadoc
 *
 * Play gene engineering animation.
 *
 * @tparam LuaPosition pos The position of the animation.
 */
void LuaApiAnimation::play_gene_engineering(const Position& pos)
{
    GeneEngineeringAnimation(pos).play();
}



/**
 * @luadoc
 *
 * Play miracle animation.
 */
void LuaApiAnimation::play_miracle()
{
    MiracleAnimation().play();
}



/**
 * @luadoc
 *
 * Play meteor animation.
 */
void LuaApiAnimation::play_meteor()
{
    MeteorAnimation().play();
}



/**
 * @luadoc
 *
 * Play The Ragnarok animation.
 */
void LuaApiAnimation::play_ragnarok()
{
    RagnarokAnimation().play();
}



/**
 * @luadoc
 *
 * Play breaking animation.
 *
 * @tparam LuaPosition pos The position of the animation
 */
void LuaApiAnimation::play_breaking(const Position& pos)
{
    BreakingAnimation(pos).play();
}



void LuaApiAnimation::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_failure_to_cast);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_bright_aura);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_breath);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_ball_atomic_bomb);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_ball_magic);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_bolt);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_throwing_object);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_swarm);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_ranged_attack);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_melee_attack);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_gene_engineering);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_miracle);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_meteor);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_ragnarok);
    LUA_API_BIND_FUNCTION(api_table, LuaApiAnimation, play_breaking);
}

} // namespace lua
} // namespace elona
