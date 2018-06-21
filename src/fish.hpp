#pragma once

#include "cat.hpp"



namespace elona
{


struct fish_data
{
    int id;
    bool no_generate;
    int rank;
    int rarity;
    int difficulty;
    int weight;
    int value;
    int item_id;
};



class fish_db;


namespace cat
{

template <>
struct cat_db_traits<fish_db>
{
    using id_type = int;
    using data_type = fish_data;
    static constexpr const char* filename = u8"fish.lua";
    static constexpr const char* table_name = u8"fish";
};

} // namespace cat


class fish_db : public cat::cat_db<fish_db>
{
public:
    fish_db() = default;

    void define(lua_State* L);
};



extern fish_db the_fish_db;


} // namespace elona
