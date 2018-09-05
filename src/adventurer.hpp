#pragma once
#include <string>

namespace elona
{

void create_all_adventurers();
void create_adventurer();
void adventurer_update();
int adventurer_discover_equipment();
int advfavoriteskill(int = 0);
int advfavoritestat(int = 0);

void addnews(int = 0, int = 0, int = 0, const std::string& = "");
void addnews2(const std::string&, int = 0);
void addnewstopic(const std::string&, const std::string&);

} // namespace elona
