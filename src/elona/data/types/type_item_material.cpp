#include "type_item_material.hpp"



namespace elona
{

ItemMaterialDB the_item_material_db;
const constexpr char* data::DatabaseTraits<ItemMaterialDB>::type_id;



ItemMaterialData ItemMaterialDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_OPT_OR(weight, int, 0);
    DATA_OPT_OR(value, int, 0);
    DATA_OPT_OR(hit_bonus, int, 0);
    DATA_OPT_OR(damage_bonus, int, 0);
    DATA_OPT_OR(dv, int, 0);
    DATA_OPT_OR(pv, int, 0);
    DATA_OPT_OR(dice_y, int, 0);
    DATA_OPT_OR(color, int, 0);
    DATA_TABLE(enchantments, int, int);
    DATA_OPT_OR(fireproof, bool, false);
    DATA_OPT_OR(acidproof, bool, false);

    return ItemMaterialData{
        data::InstanceId{id},
        legacy_id,
        weight,
        value,
        hit_bonus,
        damage_bonus,
        dv,
        pv,
        dice_y,
        color,
        enchantments,
        fireproof,
        acidproof,
    };
}

} // namespace elona
