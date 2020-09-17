#include "type_crafting_material.hpp"



namespace elona
{

CraftingMaterialDB the_crafting_material_db;
const constexpr char* data::DatabaseTraits<CraftingMaterialDB>::type_id;



CraftingMaterialData CraftingMaterialDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    DATA_INTEGER_ID();
    DATA_OPT_OR(level, int, 0);
    DATA_OPT_OR(rarity, int, 0);
    DATA_OPT_OR(icon, int, 0);
    DATA_VEC(spots, int);

    return CraftingMaterialData{
        data::InstanceId{id},
        integer_id,
        level,
        rarity,
        icon,
        spots,
    };
}

} // namespace elona
