#include "db_character.hpp"
#include <string>
#include "i18n.hpp"
#include "lua_env/lua_enums.hpp"
#include "lua_env/lua_env.hpp"

namespace elona
{

character_db_ex the_character_db;


static std::unordered_map<int, int> _convert_resistances(
    const sol::table& data,
    const std::string& id)
{
    std::unordered_map<int, int> resistances;
    sol::optional<sol::table> value = data[id];

    if (value)
    {
        for (const auto& kvp : *value)
        {
            int k = std::stoi(kvp.first.as<std::string>().substr(1));
            int v = kvp.second.as<int>();
            resistances.emplace(k, v);
        }
    }


    return resistances;
}

static std::vector<int> _convert_chara_flags(
    const sol::table& data,
    const std::string& id)
{
    std::vector<int> flag_types;
    sol::optional<sol::table> value = data[id];

    if (value)
    {
        for (const auto& kvp : *value)
        {
            std::string variant_name = kvp.second.as<std::string>();
            int variant_value =
                lua::LuaEnums::CharaFlagTable.ensure_from_string(variant_name);
            flag_types.push_back(variant_value);
        }
    }

    return flag_types;
}
character_data character_db_ex::convert(
    const std::string& id_,
    const sol::table& data,
    lua::lua_env& lua)
{
    ELONA_LION_DB_FIELD_REQUIRED(id, int);
    ELONA_LION_DB_FIELD(ai_act_sub_freq, int, 0);
    ELONA_LION_DB_FIELD(ai_calm, int, 0);
    ELONA_LION_DB_FIELD(ai_dist, int, 0);
    ELONA_LION_DB_FIELD(ai_heal, int, 0);
    ELONA_LION_DB_FIELD(ai_move, int, 0);
    ELONA_LION_DB_FIELD(can_talk, int, 0);
    ELONA_LION_DB_FIELD_ENUM(color, ColorIndex, ColorIndexTable, ColorIndex::none);
    ELONA_LION_DB_FIELD(creaturepack, int, 0);
    ELONA_LION_DB_FIELD(cspecialeq, int, 0);
    ELONA_LION_DB_FIELD(damage_reaction_info, int, 0);
    ELONA_LION_DB_FIELD(item_type, int, 0);
    ELONA_LION_DB_FIELD(element_of_unarmed_attack, int, 0);
    ELONA_LION_DB_FIELD(eqammo_0, int, 0);
    ELONA_LION_DB_FIELD(eqammo_1, int, 0);
    ELONA_LION_DB_FIELD(eqmultiweapon, int, 0);
    ELONA_LION_DB_FIELD(eqrange_0, int, 0);
    ELONA_LION_DB_FIELD(eqrange_1, int, 0);
    ELONA_LION_DB_FIELD(eqring1, int, 0);
    ELONA_LION_DB_FIELD(eqtwohand, int, 0);
    ELONA_LION_DB_FIELD(eqweapon1, int, 0);
    ELONA_LION_DB_FIELD(female_image, int, 0);
    ELONA_LION_DB_FIELD(fixlv, int, 0);
    ELONA_LION_DB_FIELD(has_random_name, bool, false);
    ELONA_LION_DB_FIELD(image, int, 0);
    ELONA_LION_DB_FIELD(level, int, 0);
    ELONA_LION_DB_FIELD(male_image, int, 0);
    ELONA_LION_DB_FIELD_ENUM(original_relationship, int, RelationTable, 0);
    ELONA_LION_DB_FIELD(portrait, int, 0);
    ELONA_LION_DB_FIELD(race, std::string, "");
    ELONA_LION_DB_FIELD(class_, std::string, "");
    ELONA_LION_DB_FIELD_ENUM(sex, int, GenderTable, -1);
    ELONA_LION_DB_FIELD(fltselect, int, 0);
    ELONA_LION_DB_FIELD(category, int, 0);
    ELONA_LION_DB_FIELD(rarity, int, 10000);
    ELONA_LION_DB_FIELD(coefficient, int, 400);
    ELONA_LION_DB_FIELD_CALLBACK(corpse_eating_callback);

    std::unordered_map<int, int> resistances =
        _convert_resistances(data, "resistances");

    std::vector<int> normal_actions;
    if (auto result = lion::convert_vector<int>(data, "normal_actions"))
    {
        normal_actions = *result;
    }
    else
    {
        normal_actions = {-1};
    }

    std::vector<int> special_actions;
    if (auto result = lion::convert_vector<int>(data, "special_actions"))
    {
        special_actions = *result;
    }

    std::vector<int> flag_types = _convert_chara_flags(data, "flags");

    // TODO: cannot set bit flags off.
    decltype(character_data::_flags) flags;
    for (const auto& type : flag_types)
    {
        flags[type] = true;
    }

    // TODO: validate by regex/alphanum-only
    std::string filter = lion::convert_tags(data, "tags");

    return character_data{
        id,
        normal_actions,
        special_actions,
        ai_act_sub_freq,
        ai_calm,
        ai_dist,
        ai_heal,
        ai_move,
        can_talk,
        class_,
        static_cast<ColorIndex>(color),
        creaturepack,
        cspecialeq,
        damage_reaction_info,
        item_type,
        element_of_unarmed_attack,
        eqammo_0,
        eqammo_1,
        eqmultiweapon,
        eqrange_0,
        eqrange_1,
        eqring1,
        eqtwohand,
        eqweapon1,
        female_image,
        filter,
        fixlv,
        has_random_name,
        image,
        level,
        male_image,
        original_relationship,
        portrait,
        race,
        sex,
        resistances,
        fltselect,
        category,
        rarity,
        coefficient,
        corpse_eating_callback,
        flags,
    };
}

} // namespace elona
