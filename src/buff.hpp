#pragma once

#include <unordered_map>
#include "data/types/type_buff.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;
struct Buff;


bool buff_has(const Character& cc, int id);
optional_ref<const Buff> buff_find(const Character& cc, int id);
void buff_add(
    Character& cc,
    int id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);
void buff_delete(Character& cc, int prm_806);



} // namespace elona
