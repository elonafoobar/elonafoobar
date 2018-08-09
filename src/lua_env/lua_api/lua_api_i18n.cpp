#include "lua_api_i18n.hpp"
#include "../../i18n.hpp"

namespace elona
{
namespace lua
{

std::string I18N::get(const std::string& key, sol::variadic_args args)
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

sol::optional<std::string> I18N::get_optional(
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

std::string
I18N::get_enum(const std::string& key, int index, sol::variadic_args args)
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

std::string I18N::get_enum_property(
    const std::string& key_head,
    const std::string& key_tail,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: return i18n::s.get_enum_property(key_head, key_tail, index);
    case 1:
        return i18n::s.get_enum_property(
            key_head, key_tail, index, args[0].get<sol::object>());
    case 2:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
    case 3:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
    case 4:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
    case 5:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
    case 6:
    default:
        return i18n::s.get_enum_property(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>(),
            args[5].get<sol::object>());
    }
}

sol::optional<std::string> I18N::get_enum_property_optional(
    const std::string& key_head,
    const std::string& key_tail,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0:
        opt = i18n::s.get_enum_property_opt(key_head, key_tail, index);
        break;
    case 1:
        opt = i18n::s.get_enum_property_opt(
            key_head, key_tail, index, args[0].get<sol::object>());
        break;
    case 2:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_enum_property_opt(
            key_head,
            key_tail,
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
            key_head,
            key_tail,
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

void I18N::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, I18N, get);
    LUA_API_BIND_FUNCTION(api_table, I18N, get_optional);
    LUA_API_BIND_FUNCTION(api_table, I18N, get_enum);
    LUA_API_BIND_FUNCTION(api_table, I18N, get_enum_property);
    api_table.set_function(
        "get_enum_property_optional", I18N::get_enum_property_optional);
}

} // namespace lua
} // namespace elona
