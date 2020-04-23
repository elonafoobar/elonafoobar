#pragma once

#include "optional.hpp"



namespace elona
{

struct Character;
struct Item;



bool magic(Character& subject, optional_ref<Item> item = none);

} // namespace elona
