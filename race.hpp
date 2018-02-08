#pragma once

#include <unordered_map>
#include "optional_ref.hpp"


namespace elona
{


struct race_data
{
    std::string id;
    std::string name_en;
    std::string name_jp;
    std::string description_en;
    std::string description_jp;
    int male_image;
    int female_image;
    int dbspec7;
    int dbspec9;
    int dbmode9;
};



class race_db
{
public:
    race_db();


    optional_ref<race_data> operator[](const std::string& id) const;


private:
    std::unordered_map<std::string, race_data> storage;
};


inline race_db the_race_db;



void get_race_list(bool is_extra_race);
int access_race_info(int dbmode);


} // namespace elona
