#pragma once

#include <string>

#include "data/types/type_god.hpp"
#include "enums.hpp"



namespace elona
{

using GodId = std::string;



namespace core_god
{

constexpr const char* eyth = ""; // 0
constexpr const char* mani = "elona.mani"; // 1
constexpr const char* lulwy = "elona.lulwy"; // 2
constexpr const char* itzpalt = "elona.itzpalt"; // 3
constexpr const char* ehekatl = "elona.ehekatl"; // 4
constexpr const char* opatos = "elona.opatos"; // 5
constexpr const char* jure = "elona.jure"; // 6
constexpr const char* kumiromi = "elona.kumiromi"; // 7


inline GodId int2godid(int n)
{
    switch (n)
    {
    case 0: return eyth;
    case 1: return mani;
    case 2: return lulwy;
    case 3: return itzpalt;
    case 4: return ehekatl;
    case 5: return opatos;
    case 6: return jure;
    case 7: return kumiromi;
    default: return "";
    }
}


inline int godid2int(const GodId& id)
{
    if (id == eyth)
        return 0;
    if (id == mani)
        return 1;
    if (id == lulwy)
        return 2;
    if (id == itzpalt)
        return 3;
    if (id == ehekatl)
        return 4;
    if (id == opatos)
        return 5;
    if (id == jure)
        return 6;
    if (id == kumiromi)
        return 7;
    else
        return 0;
}

} // namespace core_god



void txtgod(const GodId& id, int type);
void god_modify_piety(int amount);
void set_npc_religion();
void apply_god_blessing(int cc);
std::string get_god_description(int);
void god_proc_switching_penalty(const GodId& new_religion);
void switch_religion();
TurnResult do_pray();
TurnResult do_offer();
std::string god_name(const GodId& id);
std::string god_name(int legacy_god_id);

} // namespace elona
