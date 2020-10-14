#pragma once

#include <string>

#include "data/id.hpp"
#include "eobject/forward.hpp"
#include "typedefs.hpp"



namespace elona
{

struct Character;
struct Item;
enum class TurnResult;



// core.God.get_random_god_or_eyth
data::InstanceId god_get_random_god_or_eyth();

void txtgod(data::InstanceId id, int type);

// core.God.add_piety
void god_add_piety(Character& chara, lua_int amount);

void set_npc_religion(Character& chara);

// core.God.apply_blessing
void god_apply_blessing(Character& believer);

void god_proc_switching_penalty(data::InstanceId new_religion);

TurnResult do_pray();

// core.God.get_name
std::string god_get_name(data::InstanceId id);

void god_fail_to_take_over_penalty();

// core.God.is_offerable
bool god_is_offerable(const ItemRef& offering, Character& believer);

} // namespace elona
