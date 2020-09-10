#include "type_item.hpp"

#include "../../lua_env/enums/enums.hpp"
#include "../../lua_env/lua_env.hpp"
#include "../util.hpp"



namespace elona
{

ItemDB the_item_db;
const constexpr char* data::DatabaseTraits<ItemDB>::type_id;



ItemData ItemDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_INTEGER_ID();
    DATA_OPT_OR(image, int, 0);
    DATA_OPT_OR(value, int, 0);
    DATA_OPT_OR(weight, int, 0);
    DATA_OPT_OR(dice_x, int, 0);
    DATA_OPT_OR(dice_y, int, 0);
    DATA_OPT_OR(hit_bonus, int, 0);
    DATA_OPT_OR(damage_bonus, int, 0);
    DATA_OPT_OR(pv, int, 0);
    DATA_OPT_OR(dv, int, 0);
    DATA_OPT_OR(material, std::string, "");
    DATA_OPT_OR(chargelevel, int, 0);

    DATA_OPT_OR(is_readable, bool, false);
    DATA_OPT_OR(is_zappable, bool, false);
    DATA_OPT_OR(is_drinkable, bool, false);
    DATA_OPT_OR(is_cargo, bool, false);
    DATA_OPT_OR(is_usable, bool, false);

    DATA_OPT_OR(appearance, int, 0);
    DATA_OPT_OR(expiration_date, int, 0);
    DATA_OPT_OR(level, int, 0);
    DATA_OPT_OR(fltselect, int, 0);
    DATA_OPT_OR(category, int, 0);
    DATA_OPT_OR(subcategory, int, 0);
    DATA_OPT_OR(rarity, int, 0);
    DATA_OPT_OR(coefficient, int, 0);

    DATA_OPT_OR(light, int, 0);
    DATA_OPT_OR(originalnameref2, std::string, "");
    DATA_OPT_OR(has_random_name, bool, false);
    DATA_ENUM(tint, ColorIndex, ColorIndexTable, ColorIndex::none);

    DATA_REQ(locale_key_prefix, std::string);

    DATA_OPT(on_use_callback, std::string);

    std::string filter = data::convert_tags(data, "tags");
    std::string rffilter = data::convert_tags(data, "rftags");

    if (on_use_callback)
    {
        is_usable = true;
    }

    return ItemData{
        data::InstanceId{id},
        integer_id,
        image,
        value,
        weight,
        dice_x,
        dice_y,
        hit_bonus,
        damage_bonus,
        pv,
        dv,
        data::InstanceId{material},
        chargelevel,

        is_readable,
        is_zappable,
        is_drinkable,
        is_cargo,
        is_usable,

        appearance,
        expiration_date,
        level,
        fltselect,
        static_cast<ItemCategory>(category),
        subcategory,
        rarity,
        coefficient,
        light,
        originalnameref2,
        has_random_name,
        static_cast<ColorIndex>(tint),

        filter,
        rffilter,

        locale_key_prefix,
        on_use_callback,
    };
}

} // namespace elona
