#include "class.hpp"

#include "ability.hpp"
#include "character.hpp"
#include "data/types/type_ability.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace elona
{

void class_init_chara(Character& chara, data::InstanceId class_id)
{
    if (class_id == "")
        return;

    const auto data = the_class_db[class_id];
    if (!data)
        return;

    chara.class_ = class_id;
    for (const auto& pair : data->skills)
    {
        if (const auto ability_data = the_ability_db[pair.first])
        {
            chara_init_skill(chara, ability_data->integer_id, pair.second);
        }
        else
        {
            // Skip the skill if undefined.
            ELONA_WARN("lua.data") << "Undefined skill ID: " << pair.first.get()
                                   << " (class " << class_id.get() << ")";
        }
    }
}



std::string class_get_name(data::InstanceId class_id)
{
    if (class_id == "")
    {
        return i18n::s.get("core.class.unemployed");
    }
    else
    {
        return the_class_db.get_text(class_id, "name");
    }
}



int class_get_equipment_type(data::InstanceId class_id)
{
    if (class_id == "")
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



int class_get_item_type(data::InstanceId class_id)
{
    if (class_id == "")
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
