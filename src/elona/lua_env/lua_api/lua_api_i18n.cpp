#include "lua_api_i18n.hpp"
#include "../../i18n.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Gets a localized string and optionally formats it with arguments.
 * This will return a string with a warning if the localization
 * string doesn't exist.
 * @tparam string key the ID of the localization string
 * @treturn string the formatted string
 * @usage I18N.get("core.locale.map.you_see", "Vernis")
 */
std::string LuaApiI18N::get(const std::string& key, sol::variadic_args args)
{
    switch (args.size())
    {
    case 0: return i18n::s.get(key);
    case 1: return i18n::s.get(key, args[0].get<sol::object>());
    case 2:
        return i18n::s.get(
            key, args[0].get<sol::object>(), args[1].get<sol::object>());
    case 3:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

/**
 * @luadoc
 *
 * Gets a localized string and optionally formats it with arguments.
 * This will return nil if the localization string doesn't exist.
 * @tparam string key the ID of the localization string
 * @treturn[1] string the formatted string
 * @treturn[2] nil
 */
sol::optional<std::string> LuaApiI18N::get_optional(
    const std::string& key,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: opt = i18n::s.get_optional(key); break;
    case 1: opt = i18n::s.get_optional(key, args[0].get<sol::object>()); break;
    case 2:
        opt = i18n::s.get_optional(
            key, args[0].get<sol::object>(), args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
        break;
    case 6:
    default:
        opt = i18n::s.get_optional(
            key,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
        break;
    }

    if (opt)
    {
        return *opt;
    }

    return sol::nullopt;
}

/**
 * @luadoc
 *
 * Gets a localized string from an enum-style localization object.
 * This will return a string with a warning if the localization
 * string doesn't exist.
 * @tparam string key the ID of the localization string
 * @tparam num index the index into the enum
 * @treturn string the formatted string
 */
std::string
LuaApiI18N::get_enum(const std::string& key, int index, sol::variadic_args args)
{
    switch (args.size())
    {
    case 0: return i18n::s.get_enum(key, index);
    case 1: return i18n::s.get_enum(key, index, args[0].get<sol::object>());
    case 2:
        return i18n::s.get_enum(
            key, index, args[0].get<sol::object>(), args[1].get<sol::object>());
    case 3:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get_enum(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

/**
 * @luadoc
 *
 * Gets a localized string from an enum-style localization object
 * where the enum's children are themselves objects. This will return
 * a string with a warning if the localization string doesn't exist.
 * @tparam string key_base the base ID of the localization string
 * @tparam string key_property the property of the enum object to get
 * @tparam num index the index into the enum
 * @treturn string the formatted string
 */
std::string LuaApiI18N::get_enum_property(
    const std::string& key_base,
    const std::string& key_property,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: return i18n::s.get_enum_property(key_base, key_property, index);
    case 1:
        return i18n::s.get_enum_property(
            key_base, key_property, index, args[0].get<sol::object>());
    case 2:
        return i18n::s.get_enum_property(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
    case 3:
        return i18n::s.get_enum_property(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get_enum_property(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get_enum_property(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get_enum_property(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

/**
 * @luadoc
 *
 * Gets a localized string from an enum-style localization object
 * where the enum's children are themselves objects. This will return
 * nil if the localization string doesn't exist.
 * @tparam string key_base the base ID of the localization string
 * @tparam string key_property the property of the enum object to get
 * @tparam num index the index into the enum
 * @treturn[1] string the formatted string
 * @treturn[2] nil
 */
sol::optional<std::string> LuaApiI18N::get_enum_property_optional(
    const std::string& key_base,
    const std::string& key_property,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0:
        opt = i18n::s.get_enum_property_opt(key_base, key_property, index);
        break;
    case 1:
        opt = i18n::s.get_enum_property_opt(
            key_base, key_property, index, args[0].get<sol::object>());
        break;
    case 2:
        opt = i18n::s.get_enum_property_opt(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_enum_property_opt(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_enum_property_opt(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_enum_property_opt(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
        break;
    case 6:
    default:
        opt = i18n::s.get_enum_property_opt(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }

    if (opt)
    {
        return *opt;
    }

    return sol::nullopt;
}

/**
 * @luadoc
 *
 * Registers a new function for use inside localization files.
 * @tparam string language Localized language the function is valid in
 * @tparam string name The function's name
 * @tparam function function A function taking arguments and returning a string
 */
void LuaApiI18N::register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function)
{
    lua::lua->get_i18n_function_manager().register_function(
        language, name, function);
}

void LuaApiI18N::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiI18N, get);
    LUA_API_BIND_FUNCTION(api_table, LuaApiI18N, get_optional);
    LUA_API_BIND_FUNCTION(api_table, LuaApiI18N, get_enum);
    LUA_API_BIND_FUNCTION(api_table, LuaApiI18N, get_enum_property);
    api_table.set_function(
        "get_enum_property_optional", LuaApiI18N::get_enum_property_optional);
    LUA_API_BIND_FUNCTION(api_table, LuaApiI18N, register_function);
}

} // namespace lua
} // namespace elona
