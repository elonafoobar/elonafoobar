#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>
#include <vector>


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



class ability_db
{
public:
    ability_db();


    const ability_data& operator[](int id) const;


private:
    std::unordered_map<int, ability_data> storage;
};


inline ability_db the_ability_db;



struct ability
{
    int current_level = 0;
    int original_level = 0;
    int experience = 0;
    int potential = 0;
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


    std::unique_ptr<char[]> serialize(int offset = 0) const;

    void
    deserialize(std::unique_ptr<char[]> raw_data, int size, int offset = 0);


private:
    std::vector<std::vector<ability>> storage;
};


inline skill_data sdata;


} // namespace elona
