#include "lua_api_animation.hpp"
#include "../../animation.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{
namespace lua
{

void LuaApiAnimation::play_failure_to_cast(const Position& caster_pos)
{
    FailureToCastAnimation(caster_pos).play();
}

void LuaApiAnimation::play_bright_aura(const Position& target_pos, int kind)
{
    auto anim_type = static_cast<BrightAuraAnimation::Type>(kind);
    BrightAuraAnimation(target_pos, anim_type).play();
}

void LuaApiAnimation::play_breath(
    const Position& attacker_pos,
    const Position& target_pos,
    const EnumString& element_name)
{
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    BreathAnimation(attacker_pos, target_pos, static_cast<int>(element)).play();
}

void LuaApiAnimation::play_ball_atomic_bomb(const Position& pos, int range)
{
    BallAnimation(pos, range, BallAnimation::Type::atomic_bomb).play();
}

void LuaApiAnimation::play_ball_magic(
    const Position& pos,
    int range,
    int element)
{
    BallAnimation(pos, range, BallAnimation::Type::ball, element).play();
}

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

void LuaApiAnimation::play_throwing_object(
    const Position& attacker_pos,
    const Position& target_pos,
    int item_chip,
    int item_color)
{
    ThrowingObjectAnimation(target_pos, attacker_pos, item_chip, item_color)
        .play();
}

void LuaApiAnimation::play_swarm(const Position& target_pos)
{
    SwarmAnimation(target_pos).play();
}

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

void LuaApiAnimation::play_gene_engineering(const Position& pos)
{
    GeneEngineeringAnimation(pos).play();
}

void LuaApiAnimation::play_miracle()
{
    MiracleAnimation().play();
}

void LuaApiAnimation::play_meteor()
{
    MeteorAnimation().play();
}

void LuaApiAnimation::play_ragnarok()
{
    RagnarokAnimation().play();
}

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
