#include "type_item_material.hpp"



namespace elona
{

ItemMaterialDB the_item_material_db;
const constexpr char* data::LuaLazyCacheTraits<ItemMaterialDB>::type_id;


namespace
{

std::unordered_map<int, int> _convert_enchantments(const lua::ConfigTable& data)
{
    DATA_TABLE(enchantments, std::string, int);
    std::unordered_map<int, int> ret;
    for (const auto& pair : enchantments)
    {
        ret.emplace(std::stoi(pair.first), pair.second);
    }
    return ret;
}

} // namespace


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
    const auto enchantments = _convert_enchantments(data);
    DATA_OPT_OR(fireproof, bool, false);
    DATA_OPT_OR(acidproof, bool, false);

    return ItemMaterialData{
        SharedId{id},
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
