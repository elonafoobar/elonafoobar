#include "db_item.hpp"
#include <string>
#include "i18n.hpp"
#include "lua_env/lua_enums.hpp"
#include "lua_env/lua_env.hpp"

namespace elona
{


item_db_ex the_item_db;


item_data item_db_ex::convert(
    const std::string& id_,
    const sol::table& data,
    lua::lua_env& lua)
{
    ELONA_LION_DB_FIELD_REQUIRED(id, int);
    ELONA_LION_DB_FIELD(image, int, 0);
    ELONA_LION_DB_FIELD(value, int, 0);
    ELONA_LION_DB_FIELD(weight, int, 0);
    ELONA_LION_DB_FIELD(dice_x, int, 0);
    ELONA_LION_DB_FIELD(dice_y, int, 0);
    ELONA_LION_DB_FIELD(hit_bonus, int, 0);
    ELONA_LION_DB_FIELD(damage_bonus, int, 0);
    ELONA_LION_DB_FIELD(pv, int, 0);
    ELONA_LION_DB_FIELD(dv, int, 0);
    ELONA_LION_DB_FIELD(material, int, 0);
    ELONA_LION_DB_FIELD(chargelevel, int, 0);

    ELONA_LION_DB_FIELD(is_readable, bool, false);
    ELONA_LION_DB_FIELD(is_zappable, bool, false);
    ELONA_LION_DB_FIELD(is_drinkable, bool, false);
    ELONA_LION_DB_FIELD(is_cargo, bool, false);
    ELONA_LION_DB_FIELD(is_usable, bool, false);

    ELONA_LION_DB_FIELD(appearance, int, 0);
    ELONA_LION_DB_FIELD(expiration_date, int, 0);
    ELONA_LION_DB_FIELD(level, int, 0);
    ELONA_LION_DB_FIELD(fltselect, int, 0);
    ELONA_LION_DB_FIELD(category, int, 0);
    ELONA_LION_DB_FIELD(subcategory, int, 0);
    ELONA_LION_DB_FIELD(rarity, int, 0);
    ELONA_LION_DB_FIELD(coefficient, int, 0);

    ELONA_LION_DB_FIELD(light, int, 0);
    ELONA_LION_DB_FIELD(originalnameref2, std::string, "");
    ELONA_LION_DB_FIELD(has_random_name, bool, false);
    ELONA_LION_DB_FIELD_ENUM(color, ColorIndex, ColorIndexTable, ColorIndex::none);
    ELONA_LION_DB_FIELD_REQUIRED(locale_key_prefix, std::string);

    ELONA_LION_DB_FIELD_CALLBACK(on_use_callback);

    std::string filter = lion::convert_tags(data, "tags");
    std::string rffilter = lion::convert_tags(data, "rftags");

    if (on_use_callback)
    {
        is_usable = true;
    }

    return item_data{
        id,
        image,
        value,
        weight,
        dice_x,
        dice_y,
        hit_bonus,
        damage_bonus,
        pv,
        dv,
        material,
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
        category,
        subcategory,
        rarity,
        coefficient,
        light,
        originalnameref2,
        has_random_name,
        static_cast<ColorIndex>(color),

        filter,
        rffilter,

        locale_key_prefix,
        on_use_callback,
    };
}

} // namespace elona
