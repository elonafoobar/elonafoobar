#pragma once

#include <string>
#include <vector>
#include "cat.hpp"



namespace elona
{
namespace i18n
{



void load(const std::string& language);



std::string _(
    const std::string& key_head,
    const std::vector<std::string>& key_tail);


template <typename... Args>
std::string _(const std::string& key_head, const Args&... key_tail)
{
    return _(key_head, {key_tail...});
}



struct formattable_string
{
    explicit formattable_string(
        const std::string& key_head,
        const std::vector<std::string>& key_tail)
        : key_head(key_head)
        , key_tail(key_tail)
    {
    }

    // FIXME: DRY
    template <typename... Args>
    std::string operator()(Args&&... args)
    {
        lua_getglobal(cat::global.ptr(), key_head.c_str());
        int pop_count = 1;
        for (const auto& k : key_tail)
        {
            lua_getfield(cat::global.ptr(), -1, k.c_str());
            ++pop_count;
        }

        lua_pushvalue(cat::global.ptr(), -2);
        auto ret = cat::global.call_method<std::string>(args...);
        lua_pop(cat::global.ptr(), pop_count);
        return ret;
    }

private:
    std::string key_head;
    std::vector<std::string> key_tail;
};



// TODO rename
inline formattable_string fmt(
    const std::string& key_head,
    const std::vector<std::string>& key_tail)
{
    return formattable_string{key_head, key_tail};
}



// TODO rename
template <typename... Args>
formattable_string fmt(const std::string& key_head, const Args&... key_tail)
{
    return fmt(key_head, {key_tail...});
}



} // namespace i18n
} // namespace elona
