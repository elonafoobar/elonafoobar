#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions to invoke wish and add custom wishing.
 */
namespace LuaApiWish
{

// Wish something.
bool wish();
bool wish_with_str(const std::string&);

// Check whether the input matches or not.
bool match(
    const std::string& input,
    const std::string& match_type,
    const std::string& i18n_key_to_word_list,
    sol::table english_words);

void add(const std::string& hook_type, sol::protected_function callback);


void bind(sol::table);

} // namespace LuaApiWish

} // namespace elona::lua::api::modules
