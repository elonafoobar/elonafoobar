#pragma once

#include "data/types/type_trait.hpp"



namespace elona
{

struct Character;



int trait_get_info(int traitmode, int tid);
void trait_load_desc(Character& chara);

void clear_trait_data();

} // namespace elona
