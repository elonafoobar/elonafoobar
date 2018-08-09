#include "lua_api_animation.hpp"
#include "../../animation.hpp"

namespace elona
{
namespace lua
{

void Animation::play_failure_to_cast(const position_t& caster_pos)
{
    failure_to_cast_animation(caster_pos).play();
}

void Animation::play_bright_aura(const position_t& target_pos, int kind)
{
    auto anim_type = static_cast<bright_aura_animation::type_t>(kind);
    bright_aura_animation(target_pos, anim_type).play();
}

void Animation::play_breath(
    const position_t& attacker_pos,
    const position_t& target_pos,
    int element)
{
    breath_animation(attacker_pos, target_pos, element).play();
}

void Animation::play_ball_atomic_bomb(const position_t& pos, int range)
{
    ball_animation(pos, range, ball_animation::type_t::atomic_bomb).play();
}

void Animation::play_ball_magic(const position_t& pos, int range, int element)
{
    ball_animation(pos, range, ball_animation::type_t::ball, element).play();
}

void Animation::play_bolt(
    const position_t& attacker_pos,
    const position_t& target_pos,
    int element,
    int distance)
{
    bolt_animation(attacker_pos, target_pos, element, distance).play();
}

void Animation::play_throwing_object(
    const position_t& attacker_pos,
    const position_t& target_pos,
    int item_chip,
    int item_color)
{
    throwing_object_animation(target_pos, attacker_pos, item_chip, item_color)
        .play();
}

void Animation::play_swarm(const position_t& target_pos)
{
    swarm_animation(target_pos).play();
}

void Animation::play_ranged_attack(
    const position_t& attacker_pos,
    const position_t& target_pos,
    int kind,
    int fired_item_subcategory,
    int fired_item_image,
    int fired_item_color)
{
    auto anim_type = static_cast<ranged_attack_animation::type_t>(kind);
    ranged_attack_animation(
        attacker_pos,
        target_pos,
        anim_type,
        fired_item_subcategory,
        fired_item_image,
        fired_item_color)
        .play();
}

void Animation::play_melee_attack(
    const position_t& target_pos,
    bool debris,
    int attack_skill,
    int damage_percent,
    bool is_critical)
{
    melee_attack_animation(
        target_pos, debris, attack_skill, damage_percent, is_critical)
        .play();
}

void Animation::play_gene_engineering(const position_t& pos)
{
    gene_engineering_animation(pos).play();
}

void Animation::play_miracle()
{
    miracle_animation().play();
}

void Animation::play_meteor()
{
    meteor_animation().play();
}

void Animation::play_ragnarok()
{
    ragnarok_animation().play();
}

void Animation::play_breaking(const position_t& pos)
{
    breaking_animation(pos).play();
}

void Animation::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Animation, play_failure_to_cast);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_bright_aura);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_breath);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_ball_atomic_bomb);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_ball_magic);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_bolt);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_throwing_object);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_swarm);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_ranged_attack);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_melee_attack);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_gene_engineering);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_miracle);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_meteor);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_ragnarok);
    LUA_API_BIND_FUNCTION(api_table, Animation, play_breaking);
}

} // namespace lua
} // namespace elona
