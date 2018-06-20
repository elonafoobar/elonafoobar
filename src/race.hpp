#pragma once

#include <unordered_map>
#include <vector>
#include "cat.hpp"


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
    int min_age;
    int max_age;
    int height;
    int male_ratio;
    bool is_made_of_rock;
    int melee_attack_type;
    int special_attack_type;
    int dv_correction;
    int pv_correction;
    std::vector<int> body_parts;
    std::unordered_map<int, int> skills;
    std::unordered_map<int, int> resistances;
};



class race_db;


namespace cat
{

template <>
struct cat_db_traits<race_db>
{
    using id_type = std::string;
    using data_type = race_data;
    static constexpr const char* filename = u8"race.lua";
    static constexpr const char* table_name = u8"race";
};

} // namespace cat



class race_db : public cat::cat_db<race_db>
{
public:
    race_db() = default;

    std::vector<std::reference_wrapper<const race_data>> get_available_races(
        bool is_extra_race) const;

    void define(lua_State* L);
};


extern race_db the_race_db;



int access_race_info(int dbmode, const std::string& dbidn);


} // namespace elona
