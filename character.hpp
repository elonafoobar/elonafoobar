#pragma once

#include <array>
#include <memory>


namespace elona
{



struct character
{
};



struct character_data
{
    character& operator()(int index)
    {
        return storage[index];
    }


    std::unique_ptr<char[]> serialize(int offset = 0) const;

    void
    deserialize(std::unique_ptr<char[]> raw_data, int size, int offset = 0);


private:
    std::array<character, 245> storage;
};


// inline character_data cdata;



} // namespace elona



#include "macro_cdata.hpp"
