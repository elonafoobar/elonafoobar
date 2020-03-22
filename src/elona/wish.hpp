#pragma once

#include <string>

#include "lua_env/wrapped_function.hpp"
#include "optional.hpp"



namespace elona
{

bool what_do_you_wish_for(optional<std::string> wish = none);


enum class WishMatchType
{
    prefix,
    suffix,
    include,
    perfect,
};

bool wish_match(
    const std::string& input,
    WishMatchType match_type,
    const std::string& i18n_key_to_word_list,
    const std::vector<std::string>& english_words);


enum class WishHook
{
    first,
    before_vanilla_special,
    after_vanilla_special,
    before_vanilla_item,
    after_vanilla_item,
    before_vanilla_skill,
    after_vanilla_skill,
    last,

    _size,
};

void wish_add(WishHook hook, lua::WrappedFunction callback);

} // namespace elona
