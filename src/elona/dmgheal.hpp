#pragma once

#include "optional.hpp"



namespace elona
{

struct Character;



int damage_hp(Character& chara, int, int = 0, int = 0, int = 0);
void heal_hp(Character& chara, int delta);

void damage_mp(Character& chara, int delta);
void heal_mp(Character& chara, int delta);

bool action_sp(Character& chara, int sp);
void damage_sp(Character& chara, int delta);
void heal_sp(Character& chara, int delta);

void damage_insanity(Character& chara, int delta);
void heal_insanity(Character& chara, int delta);


void character_drops_item(Character& victim);
void check_kill(optional_ref<Character> killer_chara, Character& victim);
void heal_both_rider_and_mount(Character& target);
void heal_completely(Character& target);

} // namespace elona
