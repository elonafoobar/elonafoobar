#include "type_ability.hpp"



namespace elona
{

AbilityDB the_ability_db;
const constexpr char* data::DatabaseTraits<AbilityDB>::type_id;



AbilityData AbilityDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_OPT_OR(related_basic_attribute, int, 0);
    DATA_OPT_OR(ability_type, int, 0);
    DATA_OPT_OR(cost, int, 0);
    DATA_OPT_OR(range, int, 0);
    DATA_OPT_OR(difficulty, int, 0);

    return AbilityData{
        SharedId{id},
        legacy_id,
        related_basic_attribute,
        ability_type,
        cost,
        range,
        difficulty,
    };
}

} // namespace elona
