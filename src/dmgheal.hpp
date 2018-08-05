#pragma once



namespace elona
{



struct character;


int damage_hp(character& cc, int, int = 0, int = 0, int = 0);
void heal_hp(character& cc, int delta);

void damage_mp(character& cc, int delta);
void heal_mp(character& cc, int delta);

bool action_sp(character& cc, int sp);
void damage_sp(character& cc, int delta);
void heal_sp(character& cc, int delta);

void damage_insanity(character& cc, int delta);
void heal_insanity(character& cc, int delta);



} // namespace elona
