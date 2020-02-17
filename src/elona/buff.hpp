#pragma once

#include <unordered_map>

#include "data/types/type_buff.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;
struct Buff;



int buff_calc_duration(int id, int power);
std::string buff_get_description(int id, int power);

void buff_apply(Character& chara, int id, int power);

bool buff_has(const Character& chara, const std::string& id);
optional_ref<const Buff> buff_find(
    const Character& chara,
    const std::string& id);
void buff_add(
    Character& chara,
    const std::string& id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);
void buff_delete(Character& chara, int slot);

} // namespace elona
