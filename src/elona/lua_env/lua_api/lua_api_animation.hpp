#pragma once
#include "lua_api_common.hpp"

namespace elona
{

namespace lua
{

namespace LuaApiAnimation
{
void play_failure_to_cast(const Position&);

void play_bright_aura(const Position&, int);

void play_breath(const Position&, const Position&, const EnumString&);

void play_ball_atomic_bomb(const Position&, int);

void play_ball_magic(const Position&, int, int);

void play_bolt(const Position&, const Position&, const EnumString&, int);

void play_throwing_object(const Position&, const Position&, int, int);

void play_swarm(const Position&);

void play_ranged_attack(const Position&, const Position&, int, int, int, int);

void play_melee_attack(const Position&, bool, int, int, bool);

void play_gene_engineering(const Position&);

void play_miracle();

void play_meteor();

void play_ragnarok();

void play_breaking(const Position&);


void bind(sol::table&);
} // namespace LuaApiAnimation

} // namespace lua
} // namespace elona
