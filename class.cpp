#include "class.hpp"
#include "cat.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace
{


// FIXME: DO NOT USE A GLOBAL VARIABLE!
std::unordered_map<std::string, class_data>* storage_ptr;


int define(lua_State* state)
{
    int argc = lua_gettop(state);
    if (argc != 2)
        throw 0;

    const char* id = luaL_checklstring(state, 1, nullptr);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(state, 2, #name); \
    int name = luaL_checkinteger(state, -1);
#define FIELD_B(name) \
    lua_getfield(state, 2, #name); \
    bool name = lua_toboolean(state, -1);

    FIELD_I(ordering);
    FIELD_B(is_extra);
    FIELD_I(item_type);

#undef FIELD_I
#undef FIELD_B

    storage_ptr->emplace(
        id,
        class_data{
            id,
            ordering,
            is_extra,
            item_type,
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
    case 16: assert(dbspec == 4); return data->item_type;
    case 3: cdatan(3, rc) = dbidn; break;
    default: assert(0);
    }

    if (false)
    {
    }
    else if (dbidn == u8"warrior")
    {
        cequipment = 1;
        skillinit(10, rc, 10);
        skillinit(11, rc, 10);
        skillinit(12, rc, 2);
        skillinit(13, rc, 0);
        skillinit(14, rc, 0);
        skillinit(15, rc, 3);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(100, rc, 6);
        skillinit(101, rc, 4);
        skillinit(103, rc, 6);
        skillinit(102, rc, 6);
        skillinit(104, rc, 4);
        skillinit(107, rc, 5);
        skillinit(167, rc, 6);
        skillinit(152, rc, 4);
        skillinit(173, rc, 5);
        skillinit(154, rc, 5);
        skillinit(170, rc, 4);
        skillinit(169, rc, 4);
        skillinit(168, rc, 5);
    }
    else if (dbidn == u8"thief")
    {
        cequipment = 7;
        skillinit(10, rc, 4);
        skillinit(11, rc, 4);
        skillinit(12, rc, 8);
        skillinit(13, rc, 5);
        skillinit(14, rc, 4);
        skillinit(15, rc, 0);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(101, rc, 4);
        skillinit(100, rc, 3);
        skillinit(108, rc, 3);
        skillinit(173, rc, 4);
        skillinit(166, rc, 4);
        skillinit(152, rc, 3);
        skillinit(156, rc, 4);
        skillinit(300, rc, 4);
        skillinit(174, rc, 3);
        skillinit(170, rc, 4);
    }
    else if (dbidn == u8"wizard")
    {
        cequipment = 2;
        skillinit(10, rc, 0);
        skillinit(11, rc, 0);
        skillinit(12, rc, 0);
        skillinit(13, rc, 4);
        skillinit(14, rc, 3);
        skillinit(15, rc, 8);
        skillinit(16, rc, 10);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(105, rc, 3);
        skillinit(101, rc, 2);
        skillinit(150, rc, 6);
        skillinit(165, rc, 3);
        skillinit(164, rc, 6);
        skillinit(174, rc, 5);
        skillinit(171, rc, 4);
        skillinit(178, rc, 4);
        skillinit(172, rc, 5);
    }
    else if (dbidn == u8"farmer")
    {
        cequipment = 1;
        skillinit(10, rc, 5);
        skillinit(11, rc, 5);
        skillinit(12, rc, 2);
        skillinit(13, rc, 0);
        skillinit(14, rc, 8);
        skillinit(15, rc, 5);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(104, rc, 4);
        skillinit(107, rc, 3);
        skillinit(173, rc, 3);
        skillinit(156, rc, 5);
        skillinit(184, rc, 6);
        skillinit(161, rc, 7);
        skillinit(154, rc, 5);
        skillinit(180, rc, 5);
        skillinit(177, rc, 5);
    }
    else if (dbidn == u8"predator")
    {
        cequipment = 0;
        skillinit(10, rc, 8);
        skillinit(11, rc, 11);
        skillinit(12, rc, 8);
        skillinit(13, rc, 0);
        skillinit(14, rc, 0);
        skillinit(15, rc, 0);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 10);
        skillinit(152, rc, 4);
    }
    else if (dbidn == u8"archer")
    {
        cequipment = 3;
        skillinit(10, rc, 6);
        skillinit(11, rc, 4);
        skillinit(12, rc, 8);
        skillinit(13, rc, 5);
        skillinit(14, rc, 2);
        skillinit(15, rc, 0);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(108, rc, 5);
        skillinit(109, rc, 5);
        skillinit(101, rc, 4);
        skillinit(102, rc, 3);
        skillinit(173, rc, 5);
        skillinit(174, rc, 3);
        skillinit(170, rc, 3);
        skillinit(177, rc, 4);
        skillinit(301, rc, 4);
        skillinit(189, rc, 3);
    }
    else if (dbidn == u8"warmage")
    {
        cequipment = 5;
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 2);
        skillinit(13, rc, 0);
        skillinit(14, rc, 0);
        skillinit(15, rc, 4);
        skillinit(16, rc, 7);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(100, rc, 4);
        skillinit(101, rc, 3);
        skillinit(173, rc, 3);
        skillinit(150, rc, 4);
        skillinit(164, rc, 3);
        skillinit(174, rc, 5);
        skillinit(170, rc, 4);
        skillinit(169, rc, 4);
        skillinit(172, rc, 4);
    }
    else if (dbidn == u8"tourist")
    {
        cequipment = 0;
        skillinit(10, rc, 0);
        skillinit(11, rc, 0);
        skillinit(12, rc, 0);
        skillinit(13, rc, 0);
        skillinit(14, rc, 0);
        skillinit(15, rc, 0);
        skillinit(16, rc, 0);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(185, rc, 5);
        skillinit(182, rc, 3);
    }
    else if (dbidn == u8"pianist")
    {
        cequipment = 3;
        skillinit(10, rc, 6);
        skillinit(11, rc, 0);
        skillinit(12, rc, 4);
        skillinit(13, rc, 5);
        skillinit(14, rc, 6);
        skillinit(15, rc, 0);
        skillinit(16, rc, 4);
        skillinit(17, rc, 8);
        skillinit(18, rc, 0);
        skillinit(183, rc, 6);
        skillinit(153, rc, 19);
        skillinit(150, rc, 4);
        skillinit(165, rc, 6);
        skillinit(174, rc, 6);
        skillinit(179, rc, 5);
        skillinit(171, rc, 4);
        skillinit(301, rc, 3);
    }
    else if (dbidn == u8"gunner")
    {
        cequipment = 4;
        skillinit(10, rc, 0);
        skillinit(11, rc, 2);
        skillinit(12, rc, 5);
        skillinit(13, rc, 8);
        skillinit(14, rc, 5);
        skillinit(15, rc, 4);
        skillinit(16, rc, 3);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(110, rc, 5);
        skillinit(173, rc, 4);
        skillinit(150, rc, 3);
        skillinit(154, rc, 4);
        skillinit(189, rc, 3);
    }
    else if (dbidn == u8"priest")
    {
        cequipment = 6;
        skillinit(10, rc, 2);
        skillinit(11, rc, 2);
        skillinit(12, rc, 0);
        skillinit(13, rc, 2);
        skillinit(14, rc, 2);
        skillinit(15, rc, 10);
        skillinit(16, rc, 7);
        skillinit(17, rc, 2);
        skillinit(18, rc, 0);
        skillinit(103, rc, 3);
        skillinit(168, rc, 3);
        skillinit(150, rc, 5);
        skillinit(154, rc, 5);
        skillinit(174, rc, 5);
        skillinit(170, rc, 3);
        skillinit(169, rc, 4);
        skillinit(181, rc, 5);
        skillinit(172, rc, 5);
    }
    else if (dbidn == u8"claymore")
    {
        cequipment = 8;
        skillinit(10, rc, 9);
        skillinit(11, rc, 3);
        skillinit(12, rc, 7);
        skillinit(13, rc, 6);
        skillinit(14, rc, 0);
        skillinit(15, rc, 0);
        skillinit(16, rc, 4);
        skillinit(17, rc, 0);
        skillinit(18, rc, 0);
        skillinit(100, rc, 6);
        skillinit(167, rc, 7);
        skillinit(152, rc, 5);
        skillinit(173, rc, 7);
        skillinit(187, rc, 4);
        skillinit(154, rc, 6);
        skillinit(171, rc, 5);
        skillinit(150, rc, 4);
    }
    return 0;
}



class_db::class_db()
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    cat::register_function(state, "define", &define);
    storage_ptr = &storage;
    cat::load(state, fs::u8path(u8"../data/class.lua"));
    storage_ptr = nullptr;
    lua_close(state);
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
