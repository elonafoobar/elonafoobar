#include "type_god.hpp"



namespace elona
{

GodDB the_god_db;
const constexpr char* data::LuaLazyCacheTraits<GodDB>::type_id;



GodData GodDB::convert(const lua::ConfigTable& data, const std::string&)
{
    auto legacy_id = data.required<int>("id");

    return GodData{legacy_id};
}

} // namespace elona
