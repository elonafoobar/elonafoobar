#pragma once
#include "../character.hpp"
#include "../item.hpp"

namespace elona
{
namespace testing
{

void set_english();
void set_japanese();
void normalize_item(Item&);
std::string test_itemname(int, int, bool = false);
Item& create_item(int, int = 1);
Character& create_chara(int, int = 0, int = 0);

} // namespace testing
} // namespace elona
