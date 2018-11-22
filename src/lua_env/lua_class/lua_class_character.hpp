#pragma once
#include "../../status_ailment.hpp"
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

struct LuaAbility;

namespace LuaCharacter
{
void damage_hp(Character&, int);
void damage_hp_source(Character&, int, const EnumString&);
void damage_hp_chara(Character&, int, LuaCharacterHandle handle);

void apply_ailment(Character&, const EnumString&, int);
void heal_ailment(Character&, const EnumString&, int);

bool recruit_as_ally(Character&);

void set_flag(Character&, const EnumString&, bool);

sol::optional<LuaAbility> get_skill(Character&, int);

void gain_skill(Character&, int, int);
void gain_skill_stock(Character&, int, int, int);

void gain_skill_exp(Character&, int, int);

void modify_trait(Character&, int, int);

void modify_resistance(Character&, const EnumString&, int);

void modify_sanity(Character&, int);

void modify_karma(Character&, int);

void modify_corruption(Character&, int);

void make_pregnant(Character&);

void eat_rotten_food(Character&);


void bind(sol::state&);
} // namespace LuaCharacter

} // namespace lua
} // namespace elona
