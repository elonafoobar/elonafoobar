#include "type_god.hpp"



namespace elona
{

GodData GodDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");

    return GodData{SharedId{id}, legacy_id};
}

} // namespace elona
