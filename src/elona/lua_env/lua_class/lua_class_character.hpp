#pragma once
#include "../../status_ailment.hpp"
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

struct LuaAbility;

/**
 * @luadoc
 *
 * Represents a character.
 */
namespace LuaCharacter
{
void damage_hp(Character&, int);
void damage_hp_source(Character&, int, const EnumString&);
void damage_hp_chara(Character&, int, LuaCharacterHandle);

void apply_ailment(Character&, const EnumString&, int);
void heal_ailment(Character&, const EnumString&, int);

void add_buff(Character&, const std::string&, int, int);
void add_buff_doer(
    Character&,
    const std::string&,
    int,
    int,
    LuaCharacterHandle);

void set_growth_buff(Character&, int, int);

bool recruit_as_ally(Character&);

bool get_flag(Character&, const EnumString&);

void set_flag(Character&, const EnumString&, bool);

sol::optional<LuaAbility> get_skill(Character&, const std::string&);

void gain_skill(Character&, const std::string&, int);
void gain_skill_stock(Character&, const std::string&, int, int);

void gain_skill_exp(Character&, const std::string&, int);

void modify_trait(Character&, int, int);

void modify_resistance(Character&, const EnumString&, int);

void modify_sanity(Character&, int);

void modify_karma(Character&, int);

void modify_corruption(Character&, int);

void make_pregnant(Character&);

void eat_rotten_food(Character&);

void vanquish(Character&);

void act_hostile_against(Character&, LuaCharacterHandle);

void refresh(Character&);

void refresh_burden_state(Character&);

void move_to(Character&, Position&);
void move_to_xy(Character&, int, int);

void switch_religion(Character&, const std::string&);

int get_ailment(Character&, const EnumString&);


void bind(sol::state&);
} // namespace LuaCharacter

} // namespace lua
} // namespace elona
