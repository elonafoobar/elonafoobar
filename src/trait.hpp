#pragma once

#include <unordered_map>
#include "cat.hpp"


namespace elona
{


struct trait_data
{
    enum class type_t
    {
        feat,
        mutation,
        nature,
        ether_disease,
    };

    int id;
    type_t type;
    int min;
    int max;
};



class trait_db;


namespace cat
{

template <>
struct cat_db_traits<trait_db>
{
    using id_type = int;
    using data_type = trait_data;
    static constexpr const char* filename = u8"trait.lua";
    static constexpr const char* table_name = u8"trait";
};

} // namespace cat



class trait_db : public cat::cat_db<trait_db>
{
public:
    trait_db() = default;

    void define(lua_State* L);
};



extern trait_db the_trait_db;


int trait_get_info(int traitmode, int tid);



} // namespace elona
