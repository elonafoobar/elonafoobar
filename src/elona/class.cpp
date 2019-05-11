#include "class.hpp"
#include "ability.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{

int cequipment = 0;



int access_class_info(int dbmode, const std::string& class_id)
{
    if (class_id.empty())
    {
        classname = i18n::s.get("core.locale.class.unemployed");
        cequipment = 0;
        return 0;
    }

    const auto data = the_class_db[class_id];
    if (!data)
        return 0;

    switch (dbmode)
    {
    case 2:
        classname = i18n::s.get_m("locale.class", class_id, "name");
        return 0;
    case 9: return data->is_extra;
    case 11:
        classname = i18n::s.get_m("locale.class", class_id, "name");
        buff = i18n::s.get_m_optional("locale.class", class_id, "description")
                   .get_value_or("");
        return 0;
    case 16: return data->item_type;
    case 3: break;
    default: assert(0);
    }

    cdatan(3, rc) = class_id;
    cequipment = data->equipment_type;
    for (const auto& pair : data->skills)
    {
        if (const auto ability_data = the_ability_db[pair.first])
        {
            chara_init_skill(cdata[rc], ability_data->legacy_id, pair.second);
        }
        else
        {
            // Skip the skill if undefined.
            ELONA_WARN("lua.data") << "Undefined skill ID: " << pair.first
                                   << " (class " << class_id << ")";
        }
    }

    return 0;
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
