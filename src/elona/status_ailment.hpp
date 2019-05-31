#pragma once



namespace elona
{

struct Character;



// TODO: they shouldn't be linked to specific magic numbers.
enum class StatusAilment
{
    blinded = 4,
    confused = 5,
    paralyzed = 3,
    poisoned = 1,
    sleep = 2,
    fear = 6,
    dimmed = 7,
    bleeding = 9,
    drunk = 8,
    insane = 11,
    sick = 12,
};



void status_ailment_damage(
    Character& chara,
    StatusAilment status_ailment,
    int power);
void status_ailment_heal(
    Character& chara,
    StatusAilment status_ailment,
    int power = 0);

} // namespace elona
