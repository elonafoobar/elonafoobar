#include "i18n.hpp"
#include <memory>
#include "cat.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona::i18n
{


void load(const std::string& language)
{
    detail::lang_state.initialize();

    for (auto&& entry : filesystem::dir_entries{
             fs::u8path(u8"../lang") / language,
             filesystem::dir_entries::type::file,
         })
    {
        detail::lang_state.load(entry.path());
    }
}


std::string _(
    const std::string& key_head,
    const std::vector<std::string>& key_tail)
{
    lua_getglobal(detail::lang_state.ptr(), key_head.c_str());
    int pop_count = 1;
    for (const auto& k : key_tail)
    {
        lua_getfield(detail::lang_state.ptr(), -1, k.c_str());
        ++pop_count;
    }
    if (lua_istable(detail::lang_state.ptr(), -1))
    {
        lua_rawgeti(
            detail::lang_state.ptr(),
            -1,
            rnd(lua_rawlen(detail::lang_state.ptr(), -1)) + 1);
        ++pop_count;
    }
    const char* ret = lua_tostring(detail::lang_state.ptr(), -1);
    lua_pop(detail::lang_state.ptr(), pop_count);
    return ret ? ret : "";
}



// TODO DRY!
formattable_string fmt(
    const std::string& key_head,
    const std::vector<std::string>& key_tail)
{
    lua_getglobal(detail::lang_state.ptr(), key_head.c_str());
    int pop_count = 1;
    for (const auto& k : key_tail)
    {
        lua_getfield(detail::lang_state.ptr(), -1, k.c_str());
        ++pop_count;
    }
    if (lua_istable(detail::lang_state.ptr(), -1))
    {
        lua_rawgeti(
            detail::lang_state.ptr(),
            -1,
            rnd(lua_rawlen(detail::lang_state.ptr(), -1)) + 1);
        ++pop_count;
    }

    return formattable_string{
        luaL_ref(detail::lang_state.ptr(), LUA_REGISTRYINDEX)};
}



} // namespace elona::i18n
