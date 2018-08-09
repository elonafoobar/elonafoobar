#pragma once
#include "../../status_ailment.hpp"
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace LuaCharacter
{
void damage_hp(character&, int);
void damage_hp_source(character&, int, damage_source_t);
void damage_hp_chara(character&, int, lua_character_handle handle);

void apply_ailment(character&, status_ailment_t, int);

bool recruit_as_ally(character&);

void set_flag(character&, int, bool);

void gain_skill(character&, int, int);
void gain_skill_stock(character&, int, int, int);

void gain_skill_exp(character&, int, int);

void modify_trait(character&, int, int);

void modify_resistance(character&, int, int);


void bind(sol::state&);
} // namespace LuaCharacter

} // namespace lua
} // namespace elona
