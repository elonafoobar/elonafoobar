#include "type_class.hpp"



namespace elona
{

namespace
{

std::unordered_map<SharedId, int> _convert_skills(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_map<SharedId, int> skills;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            SharedId k{kvp.first.as<std::string>()};
            int v = kvp.second.as<int>();
            skills.emplace(k, v);
        }
    }

    return skills;
}

} // namespace



ClassDB the_class_db;
const constexpr char* data::LuaLazyCacheTraits<ClassDB>::type_id;



ClassData ClassDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_OPT_OR(ordering, int, 0);
    DATA_OPT_OR(is_extra, bool, true);
    DATA_OPT_OR(item_type, int, 0);
    DATA_OPT_OR(equipment_type, int, 0);
    auto skills = _convert_skills(data, "skills");

    return ClassData{
        SharedId{id},
        ordering,
        is_extra,
        item_type,
        equipment_type,
        skills,
    };
}

} // namespace elona
