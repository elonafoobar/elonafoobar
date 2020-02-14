#include "class.hpp"

#include "ability.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace elona
{

void class_init_chara(Character& chara, const std::string& class_id)
{
    if (class_id.empty())
    {
        return;
    }

    const auto data = the_class_db[class_id];
    if (!data)
    {
        return;
    }

    cdatan(3, chara.index) = class_id;
    for (const auto& pair : data->skills)
    {
        if (const auto ability_data = the_ability_db[pair.first])
        {
            chara_init_skill(chara, ability_data->legacy_id, pair.second);
        }
        else
        {
            // Skip the skill if undefined.
            ELONA_WARN("lua.data") << "Undefined skill ID: " << pair.first
                                   << " (class " << class_id << ")";
        }
    }
}



std::string class_get_name(const std::string& class_id)
{
    if (class_id.empty())
    {
        return i18n::s.get("core.class.unemployed");
    }
    else
    {
        return i18n::s.get_m("class", class_id, "name");
    }
}



int class_get_equipment_type(const std::string& class_id)
{
    if (class_id.empty())
    {
        return 0;
    }
    else if (const auto data = the_class_db[class_id])
    {
        return data->equipment_type;
    }
    else
    {
        return 0;
    }
}



int class_get_item_type(const std::string& class_id)
{
    if (class_id.empty())
    {
        return 0;
    }
    else if (const auto data = the_class_db[class_id])
    {
        return data->item_type;
    }
    else
    {
        return 0;
    }
}



std::vector<std::reference_wrapper<const ClassData>> class_get_available(
    bool is_extra_class)
{
    std::vector<std::reference_wrapper<const ClassData>> ret;

    for (const auto& class_ : the_class_db.values())
    {
        if (class_.is_extra == is_extra_class)
        {
            ret.emplace_back(class_);
        }
    }
    range::sort(ret, [](const auto& a, const auto& b) {
        return a.get().ordering < b.get().ordering;
    });

    return ret;
}

} // namespace elona
