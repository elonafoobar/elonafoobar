#include "item_db.hpp"
#include <string>
#include "cat.hpp"

using namespace elona;



namespace elona
{


item_db the_item_db;


void item_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load item data");

    ELONA_CAT_DB_FIELD_INTEGER(image, 0);
    ELONA_CAT_DB_FIELD_INTEGER(value, 0);
    ELONA_CAT_DB_FIELD_INTEGER(weight, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dice_x, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dice_y, 0);
    ELONA_CAT_DB_FIELD_INTEGER(hit_bonus, 0);
    ELONA_CAT_DB_FIELD_INTEGER(damage_bonus, 0);
    ELONA_CAT_DB_FIELD_INTEGER(pv, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dv, 0);
    ELONA_CAT_DB_FIELD_INTEGER(material, 0);
    ELONA_CAT_DB_FIELD_INTEGER(chargelevel, 0);

    ELONA_CAT_DB_FIELD_STRING(description_jp_0, "");
    ELONA_CAT_DB_FIELD_STRING(description_jp_1, "");
    ELONA_CAT_DB_FIELD_STRING(description_jp_2, "");
    ELONA_CAT_DB_FIELD_STRING(description_jp_3, "");
    ELONA_CAT_DB_FIELD_STRING(description_en, "");

    ELONA_CAT_DB_FIELD_INTEGER(is_readable, 0);
    ELONA_CAT_DB_FIELD_INTEGER(is_zappable, 0);
    ELONA_CAT_DB_FIELD_INTEGER(is_drinkable, 0);
    ELONA_CAT_DB_FIELD_INTEGER(is_cargo, 0);
    ELONA_CAT_DB_FIELD_INTEGER(is_usable, 0);
    ELONA_CAT_DB_FIELD_INTEGER(appearance, 0);
    ELONA_CAT_DB_FIELD_INTEGER(expiration_date, 0);
    ELONA_CAT_DB_FIELD_INTEGER(level, 0);
    ELONA_CAT_DB_FIELD_INTEGER(fltselect, 0);
    ELONA_CAT_DB_FIELD_INTEGER(category, 0);
    ELONA_CAT_DB_FIELD_INTEGER(subcategory, 0);
    ELONA_CAT_DB_FIELD_INTEGER(rarity, 0);
    ELONA_CAT_DB_FIELD_INTEGER(coefficient, 0);

    ELONA_CAT_DB_FIELD_INTEGER(light, 0);
    ELONA_CAT_DB_FIELD_STRING(katakana_name, "");
    ELONA_CAT_DB_FIELD_STRING(original_name_jp, "");
    ELONA_CAT_DB_FIELD_STRING(original_name_en, "");
    ELONA_CAT_DB_FIELD_STRING(originalnameref2, "");
    ELONA_CAT_DB_FIELD_BOOLEAN(has_random_name, false);

    ELONA_CAT_DB_FIELD_STRING(filter, "");
    ELONA_CAT_DB_FIELD_STRING(rffilter, "");

    storage.emplace(
        std::stoi(id), // TODO
        item_data{
            std::stoi(id),
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
            katakana_name,
            original_name_jp,
            original_name_en,
            originalnameref2,
            has_random_name,

            filter,
            rffilter,
        });
}



} // namespace elona
