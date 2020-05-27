#pragma once

#include "optional.hpp"



namespace elona
{

struct Character;



void shop_refresh_on_talk(Character& shopkeeper);
void shop_refresh(Character& shopkeeper);
void shop_load_shoptmp();
void shop_sell_item(optional_ref<Character> shopkeeper);

} // namespace elona
