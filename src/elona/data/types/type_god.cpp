#include "type_god.hpp"



namespace elona
{

GodDB the_god_db;
const constexpr char* data::DatabaseTraits<GodDB>::type_id;



GodData GodDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");

    return GodData{SharedId{id}, legacy_id};
}

} // namespace elona
