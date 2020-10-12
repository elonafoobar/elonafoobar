#pragma once

#include <string>

#include "data/types/type_god.hpp"
#include "eobject/forward.hpp"



namespace elona
{

struct Character;
struct Item;
enum class TurnResult;



inline data::InstanceId god_integer_to_god_id(int n)
{
    switch (n)
    {
    case 0: return "";
    case 1: return "core.mani";
    case 2: return "core.lulwy";
    case 3: return "core.itzpalt";
    case 4: return "core.ehekatl";
    case 5: return "core.opatos";
    case 6: return "core.jure";
    case 7: return "core.kumiromi";
    default: return "";
    }
}


inline int god_god_id_to_integer(data::InstanceId id)
{
    if (id == "")
        return 0;
    if (id == "core.mani")
        return 1;
    if (id == "core.lulwy")
        return 2;
    if (id == "core.itzpalt")
        return 3;
    if (id == "core.ehekatl")
        return 4;
    if (id == "core.opatos")
        return 5;
    if (id == "core.jure")
        return 6;
    if (id == "core.kumiromi")
        return 7;
    else
        return 0;
}



void txtgod(data::InstanceId id, int type);
void god_modify_piety(int amount);
void set_npc_religion(Character& chara);
void god_apply_blessing(Character& believer);
std::string get_god_description(int);
void god_proc_switching_penalty(data::InstanceId new_religion);
void switch_religion();
TurnResult do_pray();
TurnResult do_offer();
std::string god_name(data::InstanceId id);
std::string god_name(int integer_god_id);

void god_fail_to_take_over_penalty();

bool god_is_offerable(const ItemRef& offering, Character& believer);

} // namespace elona
