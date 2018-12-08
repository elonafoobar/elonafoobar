#include "item_material.hpp"

using namespace elona;



namespace
{

std::vector<std::vector<int>> leather_table = {
    {
        3,
        1,
        19,
        27,
        17,
    },
    {
        2,
        4,
        26,
        32,
        28,
    },
    {
        16,
        5,
        22,
        14,
        15,
    },
    {
        18,
        20,
        7,
        24,
        8,
    },
};



std::vector<std::vector<int>> metal_table = {
    {
        12,
        10,
        9,
        30,
        29,
    },
    {
        34,
        25,
        26,
        11,
        13,
    },
    {
        21,
        5,
        22,
        23,
        15,
    },
    {
        33,
        20,
        7,
        31,
        8,
    },
};

} // namespace



namespace elona
{

int item_material_lookup_leather(int x, int y)
{
    return leather_table.at(x).at(y);
}



int item_material_lookup_metal(int x, int y)
{
    return metal_table.at(x).at(y);
}

} // namespace elona
