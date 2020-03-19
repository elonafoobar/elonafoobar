#pragma once

#include <string>



namespace elona
{

template <typename T>
struct elona_vector1;



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


void cnvbonus(int = 0, int = 0);
std::string cnveqweight(int = 0);
void cutname(std::string&, int = 0);
std::string fixtxt(const std::string&, int = 0);
std::string getnpctxt(const std::string&, const std::string&);
std::string guildname();
void initialize_rankn();
void lenfix(std::string&, int = 0);
std::string ranktitle(int = 0);
std::string txttargetlevel(int, int);
void txttargetnpc(int x, int y);
std::string fltname(int = 0);


void csvsort(
    elona_vector1<std::string>& result,
    std::string line,
    int separator);

} // namespace elona
