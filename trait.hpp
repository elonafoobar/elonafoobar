#pragma once

#include <unordered_map>
#include "optional_ref.hpp"


namespace elona
{


struct trait_data
{
    int id;
    int traitref0;
    int traitref1;
    int traitref2;
};



class trait_db
{
public:
    trait_db() = default;

    void initialize();

    optional_ref<trait_data> operator[](int id) const;


private:
    std::unordered_map<int, trait_data> storage;
};



inline trait_db the_trait_db;


int get_trait_info(int traitmode, int tid);



} // namespace elona
