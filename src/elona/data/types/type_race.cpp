#include "type_race.hpp"



namespace elona
{

namespace
{

std::unordered_map<SharedId, int> _convert_skills_or_resistances(
    const lua::ConfigTable& data,
    const std::string& field_name)
{
    std::unordered_map<SharedId, int> ret;

    if (auto it = data.optional<sol::table>(field_name))
    {
        for (const auto& kvp : *it)
        {
            SharedId id{kvp.first.as<std::string>()};
            int bonus = kvp.second.as<int>();
            ret.emplace(id, bonus);
        }
    }

    return ret;
}

} // namespace



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

    const auto skills = _convert_skills_or_resistances(data, "skills");
    const auto resistances =
        _convert_skills_or_resistances(data, "resistances");

    return RaceData{
        SharedId{id},
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
