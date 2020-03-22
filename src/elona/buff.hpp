#pragma once

#include "data/id.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;
struct Buff;



/// Calculates the duration of buff @a id with the given @a power.
int buff_calc_duration(data::InstanceId id, int power);

/// Gets the description of buff @a id with the given @a power.
std::string buff_get_description(data::InstanceId id, int power);

/// Applies buff @a id 's effect with the given @a power to @a chara.
void buff_apply(Character& chara, data::InstanceId id, int power);

/// Queries whether @a chara has buff @a id or not.
bool buff_has(const Character& chara, data::InstanceId id);

/// Gets @a chara 's buff @a id if he/she has it.
optional_ref<const Buff> buff_find(const Character& chara, data::InstanceId id);

/// Adds buff @a id to @a chara with the given @a power, @a turns, and @a doer.
void buff_add(
    Character& chara,
    data::InstanceId id,
    int power,
    int turns,
    optional_ref<const Character> doer = none);

/// Deletes @a chara 's buff at @a slot.
void buff_delete(Character& chara, int slot);

} // namespace elona
