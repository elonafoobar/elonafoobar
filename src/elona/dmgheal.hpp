#pragma once



namespace elona
{



struct Character;


int damage_hp(Character& cc, int, int = 0, int = 0, int = 0);
void heal_hp(Character& cc, int delta);

void damage_mp(Character& cc, int delta);
void heal_mp(Character& cc, int delta);

bool action_sp(Character& cc, int sp);
void damage_sp(Character& cc, int delta);
void heal_sp(Character& cc, int delta);

void damage_insanity(Character& cc, int delta);
void heal_insanity(Character& cc, int delta);


void character_drops_item();
void check_kill(int = 0, int = 0);
void heal_both_rider_and_mount();
void heal_completely();

} // namespace elona
