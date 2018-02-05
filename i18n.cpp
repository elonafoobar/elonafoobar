#include "i18n.hpp"
#include <memory>
#include "cat.hpp"
#include "filesystem.hpp"


namespace
{

std::unique_ptr<lua_State, decltype(&lua_close)> lang_state{nullptr, lua_close};
}


namespace elona::i18n
{


void load(const char* language)
{
    lang_state.reset(luaL_newstate());
    luaL_openlibs(lang_state.get());

    for (auto&& entry : filesystem::dir_entries{
             fs::u8path(u8"../lang") / language,
             filesystem::dir_entries::type::file,
         })
    {
        cat::load(lang_state.get(), entry.path());
    }
}


std::string _(const std::string& key)
{
    lua_getglobal(lang_state.get(), key.c_str());
    const char* ret = lua_tostring(lang_state.get(), -1);
    lua_pop(lang_state.get(), 1);
    return ret;
}


} // namespace elona::i18n
