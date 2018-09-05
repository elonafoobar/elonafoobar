#pragma once

#include <unordered_map>
#include <vector>
#include "cat.hpp"


namespace elona
{


struct RaceData
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



class RaceDB;


namespace cat
{

template <>
struct CatDBTraits<RaceDB>
{
    using IdType = std::string;
    using DataType = RaceData;
    static constexpr const char* filename = u8"race.lua";
    static constexpr const char* table_name = u8"race";
};

} // namespace cat



class RaceDB : public cat::CatDB<RaceDB>
{
public:
    RaceDB() = default;

    std::vector<std::reference_wrapper<const RaceData>> get_available_races(
        bool is_extra_race) const;

    void define(lua_State* L);
};


extern RaceDB the_race_db;



int access_race_info(int dbmode, const std::string& dbidn);


} // namespace elona
