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



// For LDoc generation.
// As LibClang, internally used by tools/docgen, is not a compiler, it is not
// good at name resolution. To assist it, this declares `sol::this_state`.
namespace sol
{

struct this_state;

} // namespace sol



#define ELONA_LUA_API_BIND_FUNCTION(name, ...) \
    do \
    { \
        api_table.set_function(name, sol::overload(__VA_ARGS__)); \
    } while (false)

#define ELONA_LUA_API_BIND_CONSTANT(name, value) \
    do \
    { \
        api_table[name] = (value); \
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
            auto data = db[data::InstanceId{s}]; \
            if (!data) \
            { \
                return; \
            } \
            d.field = data->legacy_id; \
        })

#define LUA_API_OPTOUT_SOL_AUTOMAGIC(T) \
    namespace sol \
    { \
    template <> \
    struct is_automagical<T> : std::false_type \
    { \
    }; \
    }
