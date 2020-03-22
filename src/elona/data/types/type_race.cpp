#include "type_race.hpp"

#include "../util.hpp"



namespace elona
{

RaceDB the_race_db;
const constexpr char* data::DatabaseTraits<RaceDB>::type_id;



RaceData RaceDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_OPT_OR(is_extra, bool, true);
    DATA_OPT_OR(ordering, int, 30000);
    DATA_OPT_OR(male_image, int, 174);
    DATA_OPT_OR(female_image, int, 174);
    DATA_OPT_OR(breed_power, int, 500);
    DATA_OPT_OR(min_age, int, 1);
    DATA_OPT_OR(max_age, int, 1);
    DATA_OPT_OR(height, int, 2);
    DATA_OPT_OR(male_ratio, int, 50);
    DATA_OPT_OR(is_made_of_rock, bool, false);
    DATA_OPT_OR(melee_attack_type, int, 0);
    DATA_OPT_OR(special_attack_type, int, 0);
    DATA_OPT_OR(dv_multiplier, int, 100);
    DATA_OPT_OR(pv_multiplier, int, 100);
    DATA_VEC(body_parts, int);

    const auto skills = data::convert_id_number_table(data, "skills");
    const auto resistances = data::convert_id_number_table(data, "resistances");

    return RaceData{
        data::InstanceId{id},
        is_extra,
        ordering,
        male_image,
        female_image,
        breed_power,
        min_age,
        max_age,
        height,
        male_ratio,
        is_made_of_rock,
        melee_attack_type,
        special_attack_type,
        dv_multiplier,
        pv_multiplier,
        body_parts,
        skills,
        resistances,
    };
}

} // namespace elona
