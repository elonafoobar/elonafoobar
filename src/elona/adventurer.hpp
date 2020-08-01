#pragma once

#include <string>



namespace elona
{

struct Character;



void create_all_adventurers();
void create_adventurer(Character& adv);
void adventurer_update();
void adventurer_discover_equipment(Character& adv);
int advfavoriteskill(int = 0);
int advfavoritestat(int = 0);



enum class NewsType
{
    discovery,
    growth,
    recovery,
    accomplishment,
    retirement,
};

void adventurer_add_news(
    NewsType news_type,
    const Character& adventurer,
    const std::string& extra_info = "");

} // namespace elona
