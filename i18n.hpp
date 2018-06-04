#pragma once

#include "thirdparty/microhil/hil.hpp"

#include <string>
#include <vector>
#include "cat.hpp"
#include "character.hpp"
#include "item.hpp"


using namespace std::literals::string_literals;

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

inline bool ident_eq(std::string ident, int count)
{
    if (ident.size() == 2)
    {
        char c = ident[1];
        if (c - '0' == count)
        {
            return true;
        }
    }
    return false;
}

namespace detail
{

template <typename Head = character const&>
std::string fmt_literal(character const& c)
{
    return "<character: "s + std::to_string(c.index) + ">"s;
}

template <typename Head = item const&>
std::string fmt_literal(item const& i)
{
    return "<item: "s + std::to_string(i.index) + ">"s;
}

template <typename Head>
std::string fmt_literal(std::string const& s)
{
    return s;
}

template <typename Head>
std::string fmt_literal(const char* const& c)
{
    return std::string(c);
}

template <typename Char>
std::string fmt_literal(std::basic_string<Char> const& c)
{
    return c;
}

template <typename Head>
std::string fmt_literal(Head const& head)
{
    return std::to_string(head);
}

template <typename Head>
std::string fmt_func(hil::FunctionCall const& func, Head const& head)
{
    return "func";
}


template <typename... Tail>
void fmt_go(hil::Context& ctxt,
                   int count,
                   std::vector<std::string>& formatted)
{
}


template <typename Head, typename... Tail>
void fmt_go(hil::Context& ctxt,
                   int count,
                   std::vector<std::string>& formatted,
                   Head const& head,
                   Tail&&... tail)
{
    for (size_t i = 0; i < formatted.size(); i++)
    {
        hil::Value v = ctxt.hilParts.at(i);
        if (v.is<std::string>())
        {
            std::string ident = v.as<std::string>();
            if (ident_eq(ident, count))
            {
                formatted.at(i) = fmt_literal(head);
            }
        }
        else if (v.is<hil::FunctionCall>())
        {
            hil::FunctionCall func = v.as<hil::FunctionCall>();
            std::string ident = func.args.at(0).as<std::string>();

            if (ident_eq(ident, count))
            {
                formatted.at(i) = fmt_func(func, head);
            }
        }
    }

    fmt_go(ctxt, count + 1, formatted, std::forward<Tail>(tail)...);
}

} // namespace detail

template <typename Head, typename... Tail>
std::string fmtb(const std::string& key, Head const& head, Tail&&... tail)
{
    std::stringstream ss(key);

    hil::ParseResult p = hil::parse(ss);
    if (p.errorReason.size() != 0) {
        std::cerr << key << std::endl;
        std::cerr << p.errorReason << std::endl;
    }
    if (!p.valid())
    {
        return p.errorReason;
    }

    std::vector<std::string> formatted(p.context.hilParts.size());
    detail::fmt_go(p.context, 1, formatted, head, std::forward<Tail>(tail)...);

    std::string s;
    for (size_t i = 0; i < formatted.size(); i++)
    {
        s += p.context.textParts.at(i);
        s += formatted.at(i);
    }

    s += p.context.textParts.back();

    return s;
}



} // namespace i18n
} // namespace elona
