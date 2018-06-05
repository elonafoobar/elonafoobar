#pragma once

#include "thirdparty/microhcl/hcl.hpp"
#include "thirdparty/microhil/hil.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include "cat.hpp"
#include "character.hpp"
#include "filesystem.hpp"
#include "item.hpp"


using namespace std::literals::string_literals;

namespace elona
{
namespace i18n
{

class i18n_error : public std::exception
{
public:
    i18n_error(const std::string& path, std::string str)
    {
        std::ostringstream oss;
        oss << path << ": Error: ";
        oss << str;
        what_ = oss.str();
    }

    const char* what() const noexcept {
        return what_.c_str();
    }
private:
    std::string what_;
};

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


std::string format_builtins_character(const hil::FunctionCall&, const character&);
std::string format_builtins_item(const hil::FunctionCall&, const item&);


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

template <typename Head = const char* const&>
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

template <typename Head = const character&>
std::string fmt_func(hil::FunctionCall const& func, const character& chara)
{
    return format_builtins_character(func, chara);
}

template <typename Head = const item&>
std::string fmt_func(hil::FunctionCall const& func, const item& item)
{
    return format_builtins_item(func, item);
}

template <typename Head>
std::string fmt_func(hil::FunctionCall const& func, Head const& head)
{
    return "<unknown function (" + func.name + ")>";
}


template <typename... Tail>
void fmt_go(const hil::Context& ctxt,
                   int count,
                   std::vector<std::string>& formatted)
{
}


template <typename Head, typename... Tail>
void fmt_go(const hil::Context& ctxt,
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

inline std::string fmt_after_conv(const hil::Context& ctxt, const std::vector<std::string>& formatted)
{
    std::string s;

    for (size_t i = 0; i < formatted.size(); i++)
    {
        s += ctxt.textParts.at(i);
        s += formatted.at(i);
    }

    s += ctxt.textParts.back();

    return s;
}

template <typename Head, typename... Tail>
std::string fmt_with_context(const hil::Context& ctxt, Head const& head, Tail&&... tail)
{
    if (ctxt.textParts.size() == 1)
        return ctxt.textParts[0];

    std::vector<std::string> formatted(ctxt.hilParts.size());
    detail::fmt_go(ctxt, 1, formatted, head, std::forward<Tail>(tail)...);

    return fmt_after_conv(ctxt, formatted);
}

template <typename... Tail>
std::string fmt_with_context(const hil::Context& ctxt, Tail&&... tail)
{
    if (ctxt.textParts.size() == 1)
        return ctxt.textParts[0];

    std::vector<std::string> formatted(ctxt.hilParts.size());
    detail::fmt_go(ctxt, 1, formatted, std::forward<Tail>(tail)...);

    return fmt_after_conv(ctxt, formatted);
}

template <typename Head, typename... Tail>
std::string fmt_hil(const std::string& hil, Head const& head, Tail&&... tail)
{
    std::stringstream ss(hil);

    hil::ParseResult p = hil::parse(ss);
    if (p.errorReason.size() != 0) {
        std::cerr << hil << std::endl;
        std::cerr << p.errorReason << std::endl;
    }
    if (!p.valid())
    {
        return p.errorReason;
    }

    return fmt_with_context(p.context, head, std::forward<Tail>(tail)...);
}


class store
{
public:
    store() {};
    ~store() = default;

    void init(fs::path);
    void load(std::istream&, const std::string&);

    template <typename Head, typename... Tail>
    std::string get(const std::string& key, Head const& head, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return u8"<Unknown ID: " + key + ">";
        }

        return fmt_with_context(found->second, head, std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    std::string get(const std::string& key, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return u8"<Unknown ID: " + key + ">";
        }

        return fmt_with_context(found->second, std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    std::string get_or_blank(const std::string& key, Head const& head, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return "";
        }

        return fmt_with_context(found->second, head, std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    std::string get_or_blank(const std::string& key, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return "";
        }

        return fmt_with_context(found->second, std::forward<Tail>(tail)...);
    }

private:
    void visit(const hcl::Value&, const std::string&, const std::string&);
    void visit_object(const hcl::Object&, const std::string&, const std::string&);

    std::unordered_map<std::string, hil::Context> storage;
};

extern i18n::store s;

} // namespace i18n
} // namespace elona
