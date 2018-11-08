#include "class.hpp"
#include "ability.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{

int cequipment = 0;



int access_class_info(int dbmode, const std::string& dbidn)
{
    if (dbidn.empty())
    {
        classname = u8"なし";
        cequipment = 0;
        return 0;
    }

    const auto data = the_class_db[dbidn];
    if (!data)
        return 0;

    switch (dbmode)
    {
    case 2: classname = i18n::_(u8"class", dbidn, u8"name"); return 0;
    case 9: return data->is_extra;
    case 11:
        classname = i18n::_(u8"class", dbidn, u8"name");
        buff = i18n::_(u8"class", dbidn, u8"description");
        return 0;
    case 16: return data->item_type;
    case 3: break;
    default: assert(0);
    }

    cdatan(3, rc) = dbidn;
    cequipment = data->equipment_type;
    for (const auto& pair : data->skills)
    {
        chara_init_skill(cdata[rc], pair.first, pair.second);
    }

    return 0;
}



std::vector<std::reference_wrapper<const ClassData>> class_get_available(
    bool is_extra_class)
{
    std::vector<std::reference_wrapper<const ClassData>> ret;

    for (const auto& class_ : the_class_db)
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
