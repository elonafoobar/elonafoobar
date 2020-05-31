#include "module_I18N.hpp"

#include "../../../i18n.hpp"



namespace elona::lua::api::modules::module_I18N
{

/**
 * @luadoc get
 *
 * Gets a localized string and optionally formats it with arguments.
 * This will return a string with a warning if the localization
 * string doesn't exist.
 *
 * @tparam string key the ID of the localization string
 * @treturn string the formatted string
 * @usage I18N.get("core.map.you_see", "Vernis")
 */
std::string I18N_get(const std::string& key, sol::variadic_args args)
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
 * @luadoc get_optional
 *
 * Gets a localized string and optionally formats it with arguments.
 * This will return nil if the localization string doesn't exist.
 *
 * @tparam string key the ID of the localization string
 * @treturn[1] string the formatted string
 * @treturn[2] nil
 */
sol::optional<std::string> I18N_get_optional(
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
 * @luadoc get_enum
 *
 * Gets a localized string from an enum-style localization object.
 * This will return a string with a warning if the localization
 * string doesn't exist.
 *
 * @tparam string key the ID of the localization string
 * @tparam num index the index into the enum
 * @treturn string the formatted string
 */
std::string
I18N_get_enum(const std::string& key, int index, sol::variadic_args args)
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
 * @luadoc get_enum_optional
 *
 * Gets a localized string from an enum-style localization object and optionally
 * formats it with arguments. This will return nil if the localization string
 * doesn't exist.
 *
 * @tparam string key the ID of the localization string
 * @tparam num index the index into the enum
 * @treturn[1] string the formatted string
 * @treturn[2] nil
 */
sol::optional<std::string> I18N_get_enum_optional(
    const std::string& key,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0: opt = i18n::s.get_enum_optional(key, index); break;
    case 1:
        opt = i18n::s.get_enum_optional(key, index, args[0].get<sol::object>());
        break;
    case 2:
        opt = i18n::s.get_enum_optional(
            key, index, args[0].get<sol::object>(), args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_enum_optional(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_enum_optional(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_enum_optional(
            key,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>(),
            args[4].get<sol::object>());
        break;
    case 6:
    default:
        opt = i18n::s.get_enum_optional(
            key,
            index,
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
 * @luadoc get_enum_property
 *
 * Gets a localized string from an enum-style localization object
 * where the enum's children are themselves objects. This will return
 * a string with a warning if the localization string doesn't exist.
 *
 * @tparam string key_base the base ID of the localization string
 * @tparam string key_property the property of the enum object to get
 * @tparam num index the index into the enum
 * @treturn string the formatted string
 */
std::string I18N_get_enum_property(
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
 * @luadoc get_enum_property_optional
 *
 * Gets a localized string from an enum-style localization object
 * where the enum's children are themselves objects. This will return
 * nil if the localization string doesn't exist.
 *
 * @tparam string key_base the base ID of the localization string
 * @tparam string key_property the property of the enum object to get
 * @tparam num index the index into the enum
 * @treturn[1] string the formatted string
 * @treturn[2] nil
 */
sol::optional<std::string> I18N_get_enum_property_optional(
    const std::string& key_base,
    const std::string& key_property,
    int index,
    sol::variadic_args args)
{
    optional<std::string> opt = none;

    switch (args.size())
    {
    case 0:
        opt = i18n::s.get_enum_property_optional(key_base, key_property, index);
        break;
    case 1:
        opt = i18n::s.get_enum_property_optional(
            key_base, key_property, index, args[0].get<sol::object>());
        break;
    case 2:
        opt = i18n::s.get_enum_property_optional(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>());
        break;
    case 3:
        opt = i18n::s.get_enum_property_optional(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>());
        break;
    case 4:
        opt = i18n::s.get_enum_property_optional(
            key_base,
            key_property,
            index,
            args[0].get<sol::object>(),
            args[1].get<sol::object>(),
            args[2].get<sol::object>(),
            args[3].get<sol::object>());
        break;
    case 5:
        opt = i18n::s.get_enum_property_optional(
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
        opt = i18n::s.get_enum_property_optional(
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
 * @luadoc get_data_text
 *
 * Get a localized text associated with the given data ID.
 * This will return a string with a warning if the localization
 * string doesn't exist.
 *
 * @tparam string prototype_id Data prototype ID.
 * @tparam string instance_id Data instance ID.
 * @tparam string property_name I18N key of the property to get.
 * @treturn string The formatted string
 */
std::string I18N_get_data_text(
    const std::string& prototype_id,
    const std::string& instance_id,
    const std::string& property_name)
{
    return i18n::s.get_data_text(
        data::PrototypeId{prototype_id},
        data::InstanceId{instance_id},
        property_name);
}



/**
 * @luadoc register_function
 *
 * Registers a new function for use inside localization files.
 *
 * @tparam string language Localized language the function is valid in
 * @tparam string name The function's name
 * @tparam function function A function taking arguments and returning a string
 */
void I18N_register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function)
{
    lua::lua->get_i18n_manager().register_function(language, name, function);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("get", I18N_get);
    ELONA_LUA_API_BIND_FUNCTION("get_optional", I18N_get_optional);
    ELONA_LUA_API_BIND_FUNCTION("get_enum", I18N_get_enum);
    ELONA_LUA_API_BIND_FUNCTION("get_enum_optional", I18N_get_enum_optional);
    ELONA_LUA_API_BIND_FUNCTION("get_enum_property", I18N_get_enum_property);
    ELONA_LUA_API_BIND_FUNCTION("get_enum_property_optional", I18N_get_enum_property_optional);
    ELONA_LUA_API_BIND_FUNCTION("get_data_text", I18N_get_data_text);
    ELONA_LUA_API_BIND_FUNCTION("register_function", I18N_register_function);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_I18N
