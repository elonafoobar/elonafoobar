#include "type_god.hpp"



namespace elona
{

GodDB the_god_db;
const constexpr char* data::DatabaseTraits<GodDB>::type_id;



GodData GodDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_LEGACY_ID();

    return GodData{
        data::InstanceId{id},
        legacy_id,
    };
}

} // namespace elona
