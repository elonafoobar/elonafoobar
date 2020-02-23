#include "type_trait.hpp"

#include "../../lua_env/enums/enums.hpp"



namespace elona
{

TraitData TraitDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_ENUM(trait_type, int, TraitTypeTable, 0 /* feat */);
    DATA_REQ(min, int);
    DATA_REQ(max, int);

    return TraitData{SharedId{id}, legacy_id, trait_type, min, max};
}

} // namespace elona
