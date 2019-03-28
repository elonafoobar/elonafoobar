#pragma once

#include <string>
#include "data/types/type_god.hpp"
#include "enums.hpp"



namespace elona
{

using GodId = std::string;

struct Item;


namespace core_god
{

constexpr const char* eyth = ""; // 0
constexpr const char* mani = "core.mani"; // 1
constexpr const char* lulwy = "core.lulwy"; // 2
constexpr const char* itzpalt = "core.itzpalt"; // 3
constexpr const char* ehekatl = "core.ehekatl"; // 4
constexpr const char* opatos = "core.opatos"; // 5
constexpr const char* jure = "core.jure"; // 6
constexpr const char* kumiromi = "core.kumiromi"; // 7


inline GodId int2godid(int n)
{
    auto id = the_god_db.get_id_from_legacy(n);
    if (!id)
    {
        return "";
    }

    return id->get();
}


inline int godid2int(const GodId& id)
{
    auto god_data = the_god_db[id];
    if (!god_data)
    {
        return 0;
    }

    return god_data->legacy_id;
}

} // namespace core_god



void txtgod(const GodId& id, int type);
void god_modify_piety(int amount);
void set_npc_religion();
void apply_god_blessing(int cc);
std::string get_god_description(int);
void god_proc_switching_penalty();
void switch_religion();
TurnResult do_pray();
TurnResult do_offer();
std::string god_name(const GodId& id);
std::string god_name(int legacy_god_id);
bool god_is_offerable(const Item& item);

} // namespace elona
