#include "class.hpp"
#include "cat.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace elona
{



int access_class_info(int dbmode, const std::string& dbidn)
{
    if (std::empty(dbidn))
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
        skillinit(pair.first, rc, pair.second);
    }

    return 0;
}


void class_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

    ELONA_CAT_DB_FIELD_INTEGER(ordering, 0);
    ELONA_CAT_DB_FIELD_BOOLEAN(is_extra, true);
    ELONA_CAT_DB_FIELD_INTEGER(item_type, 0);
    ELONA_CAT_DB_FIELD_INTEGER(equipment_type, 0);

    std::unordered_map<int, int> skills;
    lua_getfield(L, -1, u8"skills");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int k = std::stoi(luaL_checkstring(L, -2) + 1);
            int v = luaL_checkinteger(L, -1);
            skills.emplace(k, v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    storage.emplace(
        id,
        class_data{
            id,
            ordering,
            is_extra,
            item_type,
            equipment_type,
            skills,
        });
}



std::vector<std::reference_wrapper<const class_data>>
class_db::get_available_classes(bool is_extra_class) const
{
    std::vector<std::reference_wrapper<const class_data>> ret;
    for (const auto& pair : storage)
    {
        if (pair.second.is_extra == is_extra_class)
        {
            ret.emplace_back(pair.second);
        }
    }
    range::sort(ret, [](const auto& a, const auto& b) {
        return a.get().ordering < b.get().ordering;
    });
    return ret;
}



} // namespace elona
