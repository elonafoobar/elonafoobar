#pragma once
#include "lua_api_common.hpp"

namespace elona
{

namespace lua
{

namespace Animation
{
void play_failure_to_cast(const position_t&);

void play_bright_aura(const position_t&, int);

void play_breath(const position_t&, const position_t&, int);

void play_ball_atomic_bomb(const position_t&, int);

void play_ball_magic(const position_t&, int, int);

void play_bolt(const position_t&, const position_t&, int, int);

void play_throwing_object(const position_t&, const position_t&, int, int);

void play_swarm(const position_t&);

void play_ranged_attack(
    const position_t&,
    const position_t&,
    int,
    int,
    int,
    int);

void play_melee_attack(const position_t&, bool, int, int, bool);

void play_gene_engineering(const position_t&);

void play_miracle();

void play_meteor();

void play_ragnarok();

void play_breaking(const position_t&);


void bind(sol::table&);
} // namespace Animation

} // namespace lua
} // namespace elona
