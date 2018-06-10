#pragma once
#include "../character.hpp"
#include "../item.hpp"

namespace elona
{
namespace testing
{

void set_english();
void set_japanese();
void normalize_item(item&);
std::string test_itemname(int, int, bool = false);
item& create_item(int, int);
character& create_chara(int, int = 0, int = 0);

} // namespace testing
} // namespace elona
