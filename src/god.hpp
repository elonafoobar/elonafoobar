#pragma once

#include <string>
#include <unordered_map>
#include "cat.hpp"
#include "enums.hpp"


namespace elona
{


using god_id_t = std::string;


namespace core_god
{

// constexpr const char* eyth = u8""; // 0
constexpr const char* mani = u8"mani"; // 1
constexpr const char* lulwy = u8"lulwy"; // 2
constexpr const char* itzpalt = u8"itzpalt"; // 3
constexpr const char* ehekatl = u8"ehekatl"; // 4
constexpr const char* opatos = u8"opatos"; // 5
constexpr const char* jure = u8"jure"; // 6
constexpr const char* kumiromi = u8"kumiromi"; // 7


inline god_id_t int2godid(int n)
{
    switch (n)
    {
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


inline int godid2int(const god_id_t& id)
{
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


struct god_data
{
    god_id_t id;
};


class GodDB;


namespace cat
{

template <>
struct cat_db_traits<GodDB>
{
    using id_type = god_id_t;
    using data_type = god_data;
    static constexpr const char* filename = u8"god.lua";
    static constexpr const char* table_name = u8"god";
};

} // namespace cat


class GodDB : public cat::CatDB<GodDB>
{
public:
    GodDB() = default;

    void define(lua_State* L);
};


extern GodDB the_god_db;


void txtgod(const god_id_t& id, int type);
int modpiety(int prm_1035);
void set_npc_religion();
void apply_god_blessing(int cc);
std::string get_god_description(int);
void god_proc_switching_penalty();
void switch_religion();
TurnResult do_pray();
TurnResult do_offer();



} // namespace elona
