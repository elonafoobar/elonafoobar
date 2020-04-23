#pragma once

#include <string>

#include "optional.hpp"



namespace elona
{

struct Character;



// TODO: they shouldn't be linked to specific magic numbers.
enum class Element
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
    ether = 62,
    acid = 63,
    vorpal = 658,
};


int randomele();
std::string elename(int ele);
int element_color_id(int element_id);
void resistmod(int chara_index, int element, int delta);
void txteledmg(
    int type,
    optional_ref<const Character> attacker,
    int target,
    int element);

} // namespace elona
