#include "type_magic.hpp"


namespace elona
{

MagicDB the_magic_db;
const constexpr char* data::LuaLazyCacheTraits<MagicDB>::type_id;



MagicData MagicDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_REQ(callback, sol::protected_function);

    return MagicData{
        SharedId{id}, legacy_id, lua::WrappedFunction(id, callback)};
}

} // namespace elona
