#pragma once
#include "../common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for localization.
 * See the I18N section for more information.
 */
namespace LuaApiI18N
{
std::string get(const std::string&, sol::variadic_args);

sol::optional<std::string> get_optional(const std::string&, sol::variadic_args);

std::string get_enum(const std::string&, int, sol::variadic_args);

sol::optional<std::string>
get_enum_optional(const std::string&, int, sol::variadic_args);

std::string get_enum_property(
    const std::string&,
    const std::string&,
    int,
    sol::variadic_args);

sol::optional<std::string> get_enum_property_optional(
    const std::string&,
    const std::string&,
    int,
    sol::variadic_args);

std::string
get_data_text(const std::string&, const std::string&, const std::string&);

void register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function);


void bind(sol::table&);
} // namespace LuaApiI18N

} // namespace lua
} // namespace elona
