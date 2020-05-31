#include "module_Wish.hpp"

#include "../../../wish.hpp"
#include "../../enums/enums.hpp"



namespace elona::lua::api::modules::module_Wish
{

/**
 * @luadoc wish
 *
 * Wish something you want.
 *
 * @treturn bool True if something happens; otherwise false.
 */
bool Wish_wish()
{
    return what_do_you_wish_for(cdata.player());
}



/**
 * @luadoc wish
 *
 * Wish `wish`.
 *
 * @tparam string wish Your wish.
 * @treturn bool True if something happens; otherwise false.
 */
bool Wish_wish_with_str(const std::string& wish)
{
    return what_do_you_wish_for(cdata.player(), wish);
}



/**
 * @luadoc match
 *
 * Check whether `input` matches particular words.
 *
 * @tparam string input Your wish
 * @tparam Enums.WishMatchType match_type Match type
 * @tparam string i18n_key_to_word_list I18N key to localized word list
 * @tparam table english_words List of English words
 * @treturn bool True if match.
 */
bool Wish_match(
    const std::string& input,
    const std::string& match_type,
    const std::string& i18n_key_to_word_list,
    sol::table english_words)
{
    const auto match_type_ =
        LuaEnums::WishMatchTypeTable.ensure_from_string(match_type);
    std::vector<std::string> english_words_(english_words.size());
    for (auto&& word : english_words)
    {
        english_words_.push_back(word.second.as<std::string>());
    }
    return wish_match(
        input, match_type_, i18n_key_to_word_list, english_words_);
}



// clang-format off
/**
 * @luadoc add
 *
 * Add custom wishing.
 * @tparam Enums.WishHook hook_type Hook point
 * @tparam function callback Function which takes the input and returns a
 * boolean value (success/failure)
 *
 * @usage
 * > -- Add custom wish, 'enormous_money'.
 * > Wish.add('First', function(input)
 * >    if Wish.match(
 * >          input,
 * >          'Include',
 * >          'mod_name.wish.enormous_money',
 * >          {'enormous money'}) then
 * >       Item.create(Chara.player().position, 'core.gold_piece', 1000 * 1000 * 1000)
 * >       GUI.txt(I18N.get('mod_name.wish.get_money'))
 * >       return true
 * >    else
 * >       return false
 * >    end
 * > end)
 */
// clang-format on
void Wish_add(const std::string& hook_type, sol::protected_function callback)
{
    const auto hook_type_ =
        LuaEnums::WishHookTable.ensure_from_string(hook_type);
    return wish_add(
        hook_type_, WrappedFunction{"wish(" + hook_type + ")", callback});
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("wish", Wish_wish, Wish_wish_with_str);
    ELONA_LUA_API_BIND_FUNCTION("match", Wish_match);
    ELONA_LUA_API_BIND_FUNCTION("add", Wish_add);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Wish
