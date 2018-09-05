#pragma once

#include "cat.hpp"



namespace elona
{


struct FishData
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



class FishDB;


namespace cat
{

template <>
struct CatDBTraits<FishDB>
{
    using IdType = int;
    using DataType = FishData;
    static constexpr const char* filename = u8"fish.lua";
    static constexpr const char* table_name = u8"fish";
};

} // namespace cat


class FishDB : public cat::CatDB<FishDB>
{
public:
    FishDB() = default;

    void define(lua_State* L);
};



extern FishDB the_fish_db;


} // namespace elona
