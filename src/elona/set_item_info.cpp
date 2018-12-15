#include "data/types/type_item.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{

const std::set<std::string> randomizables = {"potion",
                                             "spellbook",
                                             "scroll",
                                             "rod",
                                             "ring"};

bool is_randomizable(const std::string& original_name_ref)
{
    return randomizables.find(original_name_ref) != randomizables.end();
}

void set_item_info()
{
    for (const auto& data : the_item_db)
    {
        ilight(data.id) = data.light;
        iorgweight(data.id) = data.weight;
        ioriginalnameref2(data.id) = data.originalnameref2;
        ipicref(data.id) = data.image;
        irandomname(data.id) = data.has_random_name ? 1 : 0;

        ioriginalnameref(data.id) =
            i18n::s.get(data.locale_key_prefix + ".name");

        if (auto text =
                i18n::s.get_optional(data.locale_key_prefix + ".katakana_name"))
        {
            ialphanameref(data.id) = *text;
        }
        else
        {
            ialphanameref(data.id) = "";
        }

        if (auto text = i18n::s.get_optional(
                data.locale_key_prefix + ".unidentified_name"))
        {
            iknownnameref(data.id) = *text;
        }
        else if (data.has_random_name && is_randomizable(data.originalnameref2))
        {
            // The choice can't be completely random - it has to be the
            // same as all other items of this type. So, base it off the
            // random seed of the current save data.
            int p = (data.id % game_data.random_seed) % 6;
            iknownnameref(data.id) =
                i18n::s.get_enum(
                    "core.locale.ui.random_item." + data.originalnameref2, p) +
                i18n::space_if_needed() +
                i18n::s.get(
                    "core.locale.ui.random_item." + data.originalnameref2 +
                    ".name");
        }
        else
        {
            iknownnameref(data.id) = ioriginalnameref(data.id);
        }

        maxitemid = std::max(maxitemid, data.id + 3);
    }
}



} // namespace elona
