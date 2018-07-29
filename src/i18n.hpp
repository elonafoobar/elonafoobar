#pragma once

#include "thirdparty/microhil/hil.hpp"
#include "thirdparty/sol2/sol.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include "cat.hpp"
#include "character.hpp"
#include "filesystem.hpp"
#include "hcl.hpp"
#include "item.hpp"
#include "log.hpp"
#include "lua_env/api_manager.hpp"
#include "macro.hpp"
#include "optional.hpp"


using namespace std::literals::string_literals;

namespace elona
{

typedef std::string i18n_key;

namespace i18n
{

class i18n_error : public std::exception
{
public:
    i18n_error(const std::string& path, std::string str)
    {
        std::ostringstream oss;
        oss << path << ": ";
        oss << str;
        what_ = oss.str();
    }

    const char* what() const noexcept
    {
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
        int c_as_digit = c - '0';
        if (c_as_digit == count)
        {
            return true;
        }
    }
    return false;
}


std::string format_builtins_argless(const hil::FunctionCall&);
std::string format_builtins_bool(const hil::FunctionCall&, bool);
std::string format_builtins_string(const hil::FunctionCall&, std::string);
std::string format_builtins_integer(const hil::FunctionCall&, int);
std::string format_builtins_character(
    const hil::FunctionCall&,
    const character&);
std::string format_builtins_item(const hil::FunctionCall&, const item&);

std::string space_if_needed();

namespace detail
{

template <typename Head = character const&>
std::string format_literal_type(character const& c)
{
    return "<character: "s + std::to_string(c.index) + ">"s;
}

template <typename Head = item const&>
std::string format_literal_type(item const& i)
{
    return "<item: "s + std::to_string(i.index) + ">"s;
}

template <typename Head>
std::string format_literal_type(std::string const& s)
{
    return s;
}

template <typename Head = const char* const&>
std::string format_literal_type(const char* const& c)
{
    return std::string(c);
}

template <typename Char>
std::string format_literal_type(std::basic_string<Char> const& c)
{
    return c;
}

template <typename Head = const sol::object&>
std::string format_literal_type(sol::object const& object)
{
    if (object.is<int>())
    {
        return std::to_string(object.as<int>());
    }
    if (object.is<double>())
    {
        return std::to_string(object.as<double>());
    }
    if (object.is<bool>())
    {
        return std::to_string(object.as<bool>());
    }
    if (object.is<std::string>())
    {
        return object.as<std::string>();
    }
    if (object.is<sol::table>())
    {
        return "<lua table>";
    }
    return "<lua object>";
}

template <typename Head>
std::string format_literal_type(Head const& head)
{
    return std::to_string(head);
}

template <typename Head = const character&>
std::string format_function_type(
    hil::FunctionCall const& func,
    const character& chara)
{
    return format_builtins_character(func, chara);
}

template <typename Head = const item&>
std::string format_function_type(
    hil::FunctionCall const& func,
    const item& item)
{
    return format_builtins_item(func, item);
}

template <typename Head = const sol::object&>
std::string format_function_type(
    hil::FunctionCall const& func,
    const sol::object& object)
{
    if (object.is<bool>())
    {
        return format_builtins_bool(func, object.as<bool>());
    }
    else if (object.is<std::string>())
    {
        return format_builtins_string(func, object.as<std::string>());
    }
    else if (object.is<int>())
    {
        return format_builtins_integer(func, object.as<int>());
    }
    else if (object.is<sol::table>())
    {
        sol::table table = object.as<sol::table>();
        if (lua::lua->get_handle_manager().handle_is<character>(table))
        {
            auto& chara = lua::lua->get_handle_manager().get_ref<character>(table);
            return format_builtins_character(func, chara);
        }
        else if (lua::lua->get_handle_manager().handle_is<item>(table))
        {
            auto& item_ref = lua::lua->get_handle_manager().get_ref<item>(table);
            return format_builtins_item(func, item_ref);
        }
    }

    return "<unknown lua object (" + func.name + ")>";
}

template <typename Head = bool>
std::string format_function_type(
    hil::FunctionCall const& func,
    bool const& value)
{
    return format_builtins_bool(func, value);
}

template <typename Head = int>
std::string format_function_type(
    hil::FunctionCall const& func,
    int const& value)
{
    return format_builtins_integer(func, value);
}

template <typename Head = std::string>
std::string format_function_type(
    hil::FunctionCall const& func,
    std::string const& value)
{
    return format_builtins_string(func, value);
}

template <typename Head>
std::string format_function_type(
    hil::FunctionCall const& func,
    Head const& head)
{
    UNUSED(head);

    return "<unknown function (" + func.name + ", unknown type)>";
}


template <typename... Tail>
void fmt_internal(
    const hil::Context& ctxt,
    int count,
    std::vector<optional<std::string>>& formatted)
{
    UNUSED(ctxt);
    UNUSED(count);
    UNUSED(formatted);
}


template <typename Head, typename... Tail>
void fmt_internal(
    const hil::Context& ctxt,
    int count,
    std::vector<optional<std::string>>& formatted,
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
                formatted.at(i) = format_literal_type(head);
            }
        }
        else if (v.is<hil::FunctionCall>())
        {
            hil::FunctionCall func = v.as<hil::FunctionCall>();

            if (func.args.size() == 0)
            {
                formatted.at(i) = format_builtins_argless(func);
            }
            else if (func.args.at(0).is<std::string>())
            {
                std::string ident = func.args.at(0).as<std::string>();
                if (ident_eq(ident, count))
                {
                    formatted.at(i) = format_function_type(func, head);
                }
            }
            else if (func.args.at(0).is<bool>())
            {
                formatted.at(i) =
                    format_builtins_bool(func, func.args.at(0).as<bool>());
            }
            else if (func.args.at(0).is<int>())
            {
                formatted.at(i) =
                    format_builtins_integer(func, func.args.at(0).as<int>());
            }
        }
    }

    fmt_internal(ctxt, count + 1, formatted, std::forward<Tail>(tail)...);
}

} // namespace detail

inline std::string fmt_interpolate_converted(
    const hil::Context& ctxt,
    const std::vector<optional<std::string>>& formatted)
{
    std::string s;

    for (size_t i = 0; i < formatted.size(); i++)
    {
        s += ctxt.textParts.at(i);
        if (formatted.at(i))
        {
            s += *formatted.at(i);
        }
        else
        {
            s += "<missing>";
        }
    }

    s += ctxt.textParts.back();

    return s;
}

template <typename Head, typename... Tail>
std::string
fmt_with_context(const hil::Context& ctxt, Head const& head, Tail&&... tail)
{
    if (ctxt.textParts.size() == 1)
        return ctxt.textParts[0];

    std::vector<optional<std::string>> formatted(ctxt.hilParts.size());
    detail::fmt_internal(ctxt, 1, formatted, head, std::forward<Tail>(tail)...);

    return fmt_interpolate_converted(ctxt, formatted);
}

template <typename... Tail>
std::string fmt_with_context(const hil::Context& ctxt, Tail&&... tail)
{
    if (ctxt.textParts.size() == 1)
        return ctxt.textParts[0];

    std::vector<optional<std::string>> formatted(ctxt.hilParts.size());
    detail::fmt_internal(ctxt, 1, formatted, std::forward<Tail>(tail)...);

    return fmt_interpolate_converted(ctxt, formatted);
}


// For testing use
template <typename Head, typename... Tail>
std::string fmt_hil(const std::string& hil, Head const& head, Tail&&... tail)
{
    std::stringstream ss(hil);

    hil::ParseResult p = hil::parse(ss);
    if (p.errorReason.size() != 0)
    {
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
    store(){};
    ~store() = default;

    void init(const fs::path&);
    void load(std::istream&, const std::string&);
    void clear()
    {
        storage.clear();
    }

    template <typename Head, typename... Tail>
    optional<std::string>
    get_optional(const std::string& key, Head const& head, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return none;
        }

        return fmt_with_context(
            found->second, head, std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    optional<std::string> get_optional(const std::string& key, Tail&&... tail)
    {
        const auto& found = storage.find(key);
        if (found == storage.end())
        {
            return none;
        }

        return fmt_with_context(found->second, std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    std::string get(const std::string& key, Head const& head, Tail&&... tail)
    {
        if (auto text = get_optional(key, head, std::forward<Tail>(tail)...))
        {
            return *text;
        }
        else
        {
            if (unknown_keys.find(key) == unknown_keys.end())
            {
                ELONA_LOG("Unknown I18N ID: " << key);
                unknown_keys.insert(key);
            }
            return u8"<Unknown ID: " + key + ">";
        }
    }

    template <typename... Tail>
    std::string get(const std::string& key, Tail&&... tail)
    {
        if (auto text = get_optional(key, std::forward<Tail>(tail)...))
        {
            return *text;
        }
        else
        {
            if (unknown_keys.find(key) == unknown_keys.end())
            {
                ELONA_LOG("Unknown I18N ID: " << key);
                unknown_keys.insert(key);
            }
            return u8"<Unknown ID: " + key + ">";
        }
    }


    // Convenience methods for cases like "core.element._<enum index>.name"

    template <typename Head, typename... Tail>
    std::string get_enum(
        const std::string& key,
        int index,
        Head const& head,
        Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index),
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    std::string get_enum(const std::string& key, int index, Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index), std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    optional<std::string> get_enum_optional(
        const std::string& key,
        int index,
        Head const& head,
        Tail&&... tail)
    {
        return get_optional(
            key + "._" + std::to_string(index),
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    optional<std::string>
    get_enum_optional(const std::string& key, int index, Tail&&... tail)
    {
        return get_optional(
            key + "._" + std::to_string(index), std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    std::string get_enum_property(
        const std::string& key_head,
        int index,
        const std::string& key_tail,
        Head const& head,
        Tail&&... tail)
    {
        return get(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    std::string get_enum_property(
        const std::string& key_head,
        const std::string& key_tail,
        int index,
        Tail&&... tail)
    {
        return get(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    optional<std::string> get_enum_property_opt(
        const std::string& key_head,
        const std::string& key_tail,
        int index,
        Head const& head,
        Tail&&... tail)
    {
        return get_optional(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    optional<std::string> get_enum_property_opt(
        const std::string& key_head,
        const std::string& key_tail,
        int index,
        Tail&&... tail)
    {
        return get_optional(
            key_head + "._" + std::to_string(index) + "." + key_tail,
            std::forward<Tail>(tail)...);
    }

private:
    void visit(const hcl::Value&, const std::string&, const std::string&);
    void
    visit_object(const hcl::Object&, const std::string&, const std::string&);

    std::unordered_map<std::string, hil::Context> storage;
    std::set<std::string> unknown_keys;
};

extern i18n::store s;

} // namespace i18n
} // namespace elona
