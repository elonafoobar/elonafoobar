#include "type_trait.hpp"
#include "../../lua_env/enums/enums.hpp"



namespace elona
{

TraitDB the_trait_db;
const constexpr char* data::LuaLazyCacheTraits<TraitDB>::type_id;



TraitData TraitDB::convert(const lua::ConfigTable& data, const std::string&)
{
    auto legacy_id = data.required<int>("id");
    DATA_ENUM(trait_type, int, TraitTypeTable, 0 /* feat */);
    DATA_REQ(min, int);
    DATA_REQ(max, int);

    return TraitData{legacy_id, trait_type, min, max};
}

} // namespace elona
