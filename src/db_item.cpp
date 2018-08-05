#include "db_item.hpp"
#include <string>

using namespace elona;



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

    ELONA_LION_DB_FIELD(description_jp_0, std::string, "");
    ELONA_LION_DB_FIELD(description_jp_1, std::string, "");
    ELONA_LION_DB_FIELD(description_jp_2, std::string, "");
    ELONA_LION_DB_FIELD(description_jp_3, std::string, "");
    ELONA_LION_DB_FIELD(description_en, std::string, "");

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
    ELONA_LION_DB_FIELD(katakana_name, std::string, "");
    ELONA_LION_DB_FIELD(original_name_jp, std::string, "");
    ELONA_LION_DB_FIELD(original_name_en, std::string, "");
    ELONA_LION_DB_FIELD(originalnameref2, std::string, "");
    ELONA_LION_DB_FIELD(has_random_name, bool, false);

    std::string filter = lion::convert_tags(data, "tags");
    std::string rffilter = lion::convert_tags(data, "rftags");

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

        {
            description_jp_0,
            description_jp_1,
            description_jp_2,
            description_jp_3,
        },
        description_en,

        is_readable ? 1 : 0,
        is_zappable ? 1 : 0,
        is_drinkable ? 1 : 0,
        is_cargo ? 1 : 0,
        is_usable ? 1 : 0,

        appearance,
        expiration_date,
        level,
        fltselect,
        category,
        subcategory,
        rarity,
        coefficient,
        light,
        katakana_name,
        original_name_jp,
        original_name_en,
        originalnameref2,
        has_random_name,

        filter,
        rffilter,
    };
}

} // namespace elona
