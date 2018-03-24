#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <vector>
#include "cat.hpp"


namespace elona
{



struct ability_data
{
    int id;
    int related_basic_attribute;
    int sdataref1;
    int cost;
    int sdataref3;
    int sdataref4;
};


class ability_db;


namespace cat
{

template <>
struct cat_db_traits<ability_db>
{
    using id_type = int;
    using data_type = ability_data;
    static constexpr const char* filename = u8"ability.lua";
    static constexpr const char* table_name = u8"ability";
};

} // namespace cat



class ability_db : public cat::cat_db<ability_db>
{
public:
    ability_db() = default;

    void define(lua_State* L);
};


inline ability_db the_ability_db;



struct ability
{
    int current_level = 0;
    int original_level = 0;
    int experience = 0;
    int potential = 0;


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(current_level);
        ar(original_level);
        ar(experience);
        ar(potential);
    }
};



class skill_data
{
public:
    skill_data();


    int& operator()(int id, int cc)
    {
        return get(id, cc).current_level;
    }


    ability& get(int id, int cc)
    {
        assert(id < 600);
        return storage[cc][id];
    }


    void clear(int cc);

    void copy(int tc, int cc);


private:
    std::vector<std::vector<ability>> storage;
};


inline skill_data sdata;


} // namespace elona
