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



class race_db
{
public:
    race_db() = default;

    void initialize();

    optional_ref<race_data> operator[](const std::string& id) const;

    std::vector<std::reference_wrapper<const race_data>> get_available_races(
        bool is_extra_race) const;

private:
    std::unordered_map<std::string, race_data> storage;
};


inline race_db the_race_db;



int access_race_info(int dbmode, const std::string& dbidn);


} // namespace elona
