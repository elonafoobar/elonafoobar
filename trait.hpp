#pragma once

#include <unordered_map>


namespace elona
{


struct trait_data
{
    int id;
};



class trait_db
{
public:
    trait_db();

    const trait_data& operator[](int id) const;


private:
    std::unordered_map<int, trait_data> storage;
};



inline trait_db the_trait_db;


int get_trait_info(int traitmode, int tid);



} // namespace elona
