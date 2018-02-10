#pragma once

#include <unordered_map>
#include <vector>
#include "optional_ref.hpp"


namespace elona
{


struct race_data
{
    std::string id;
    bool is_extra;
    int ordering;
    int male_image;
    int female_image;
    int breed_power;
};



class race_db
{
public:
    race_db();


    optional_ref<race_data> operator[](const std::string& id) const;

    std::vector<std::reference_wrapper<const race_data>> get_available_races(
        bool is_extra_race) const;

private:
    std::unordered_map<std::string, race_data> storage;
};


inline race_db the_race_db;



int access_race_info(int dbmode, const std::string& dbidn);


} // namespace elona
