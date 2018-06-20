#pragma once

#include <string>



namespace elona
{


// TODO: they shouldn't be linked to specific magic numbers.
enum class element_t
{
    fire = 50,
    cold = 51,
    lightning = 52,
    darkness = 53,
    mind = 54,
    nether = 56,
    poison = 55,
    sound = 57,
    chaos = 59,
    nerve = 58,
    magic = 60,
    cut = 61,
    ehter = 62,
    acid = 63,
};


int randomele();
std::string elename(int prm_348);
int eleinfo(int prm_754, int prm_755);
void resistmod(int cc, int element, int delta);
void txteledmg(int type, int attacker, int target, int element);



} // namespace elona
