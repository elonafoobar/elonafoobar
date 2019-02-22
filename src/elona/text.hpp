#pragma once

#include <string>



namespace elona
{

void load_random_name_table();
std::string random_name();

void load_random_title_table();
enum class RandomTitleType
{
    character,
    weapon,
    party,
    living_weapon,
};
std::string random_title(RandomTitleType type);

} // namespace elona
