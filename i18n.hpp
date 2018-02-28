#pragma once

#include <string>
#include <vector>
#include "cat.hpp"



namespace elona::i18n
{



void load(const std::string& language = "jp"); // TODO



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
    explicit formattable_string(cat::ref func)
        : func(func)
    {
    }

    template <typename... Args>
    std::string operator()(Args&&... args)
    {
        return cat::global.call<std::string>(func, args...);
    }

private:
    cat::ref func;
};



// TODO rename
formattable_string fmt(
    const std::string& key_head,
    const std::vector<std::string>& key_tail);



// TODO rename
template <typename... Args>
formattable_string fmt(const std::string& key_head, const Args&... key_tail)
{
    return fmt(key_head, {key_tail...});
}



} // namespace elona::i18n
