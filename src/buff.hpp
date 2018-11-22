#pragma once

#include <unordered_map>
#include "data/types/type_buff.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;
struct Buff;


int calc_buff_duration(int id, int power);
std::string get_buff_description(int id, int power);
void apply_buff(int cc, int id, int power);

bool buff_has(const Character& cc, const std::string& id);
optional_ref<const Buff> buff_find(const Character& cc, const std::string& id);
void buff_add(
    Character& cc,
    const std::string& id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);
void buff_delete(Character& cc, int slot);



} // namespace elona
