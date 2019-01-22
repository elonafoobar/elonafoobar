#include "type_god.hpp"



namespace elona
{

GodDB the_god_db;
const constexpr char* data::LuaLazyCacheTraits<GodDB>::type_id;


static std::unordered_map<int, lua::WrappedFunction> _convert_skills(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_map<int, lua::WrappedFunction> skills;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            int k = kvp.first.as<int>();
            sol::protected_function v =
                kvp.second.as<sol::protected_function>();
            skills.emplace(k, lua::WrappedFunction(v));
        }
    }

    return skills;
}

static std::unordered_set<SharedId> _convert_offerings(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_set<SharedId> offerings;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            std::string v = kvp.second.as<std::string>();
            offerings.emplace(SharedId(v));
        }
    }

    return offerings;
}

GodData GodDB::convert(const lua::ConfigTable& data, const std::string&)
{
    auto legacy_id = data.required<int>("id");
    DATA_REQ(servant, std::string);
    DATA_REQ(items, sol::table);
    DATA_REQ(artifact, std::string);

    auto skills = _convert_skills(data, "skills");
    auto offerings = _convert_offerings(data, "offerings");

    return GodData{legacy_id,
                   SharedId(servant),
                   items,
                   SharedId(artifact),
                   skills,
                   offerings};
}

} // namespace elona
