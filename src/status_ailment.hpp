#pragma once



namespace elona
{


// TODO: they shouldn't be linked to specific magic numbers.
enum class status_ailment_t
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


void dmgcon(int cc, status_ailment_t status_ailment, int power);
void healcon(int prm_827, int prm_828, int prm_829);


} // namespace elona
