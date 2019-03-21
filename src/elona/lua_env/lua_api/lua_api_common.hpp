#pragma once

#include "../../../thirdparty/sol2/sol.hpp"
#include "../../variables.hpp"
#include "../lua_enums.hpp"
#include "../lua_env.hpp"



namespace elona
{

struct Position;
struct Character;
struct Item;

using LuaCharacterHandle = sol::table;
using LuaItemHandle = sol::table;

} // namespace elona



#define LUA_API_BIND_FUNCTION(api_table, api_name, function) \
    do \
    { \
        api_table.set_function(#function, api_name::function); \
    } while (false)

#define LUA_API_BIND_CONSTANT(api_table, name, value) \
    do \
    { \
        api_table[#name] = (value); \
    } while (false)

#define LUA_API_ENUM_PROPERTY(klass, field, enum_kind) \
    sol::property( \
        [](klass& it) { \
            return LuaEnums::enum_kind##Table.convert_to_string(it.field); \
        }, \
        [](klass& it, const EnumString& s) { \
            it.field = LuaEnums::enum_kind##Table.ensure_from_string(s); \
        })

#define LUA_API_DATA_PROPERTY(klass, field, db) \
    sol::property( \
        [](klass& d) { \
            auto id = db.get_id_from_legacy(d.field); \
            if (!id) \
            { \
                return ""s; \
            } \
            return id->get(); \
        }, \
        [](klass& d, const std::string& s) { \
            auto data = db[s]; \
            if (!data) \
            { \
                return; \
            } \
            d.field = data->legacy_id; \
        })
