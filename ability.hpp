#pragma once

#include <cassert>
#include <memory>
#include <vector>



namespace elona
{


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
