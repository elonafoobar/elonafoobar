#include "class.hpp"
#include "cat.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace
{



int define(lua_State* L, std::unordered_map<std::string, class_data>& storage)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(L, -1, #name); \
    int name = luaL_checkinteger(L, -1); \
    lua_pop(L, 1);
#define FIELD_B(name) \
    lua_getfield(L, -1, #name); \
    bool name = lua_toboolean(L, -1); \
    lua_pop(L, 1);

    FIELD_I(ordering);
    FIELD_B(is_extra);
    FIELD_I(item_type);
    FIELD_I(equipment_type);

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

#undef FIELD_I
#undef FIELD_B

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

    return 0;
}


} // namespace



namespace elona
{



std::vector<std::reference_wrapper<const class_data>>
class_db::get_available_classes(bool is_extra_class) const
{
    std::vector<std::reference_wrapper<const class_data>> ret;
    for (const auto& [_, class_] : storage)
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
    for (const auto& [k, v] : data->skills)
    {
        skillinit(k, rc, v);
    }

    return 0;
}



void class_db::initialize()
{
    cat::global.load(fs::u8path(u8"../data/class.lua"));

    lua_getglobal(cat::global.ptr(), u8"class");
    lua_getfield(cat::global.ptr(), -1, u8"__storage__");
    lua_pushnil(cat::global.ptr());
    while (lua_next(cat::global.ptr(), -2))
    {
        define(cat::global.ptr(), storage);
        lua_pop(cat::global.ptr(), 1);
    }
    lua_pop(cat::global.ptr(), 2);
}



optional_ref<class_data> class_db::operator[](const std::string& id) const
{
    const auto itr = storage.find(id);
    if (itr == std::end(storage))
        return std::nullopt;
    else
        return itr->second;
}



} // namespace elona
