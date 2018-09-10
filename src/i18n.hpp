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

using I18NKey = std::string;

struct Character;


namespace i18n
{

class I18NError : public std::exception
{
public:
    I18NError(const std::string& path, std::string str)
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



struct FormattableString
{
    explicit FormattableString(
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
inline FormattableString fmt(
    const std::string& key_head,
    const std::vector<std::string>& key_tail)
{
    return FormattableString{key_head, key_tail};
}



// TODO rename
template <typename... Args>
FormattableString fmt(const std::string& key_head, const Args&... key_tail)
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


/**
 * NOTE: When using functions in inline HCL, only the first argument position
 * can have a substituted argument. For example, itemname(_1, 1) is valid, but
 * itemname(_1, _2) is not. This is because the formatting uses a variadic
 * parameter and each function has to be evaluated when looking at an individual
 * argument that is in the function's first argument position.
 *
 * This could be fixed by defining all the functions in Lua instead.
 */

std::string format_builtins_argless(const hil::FunctionCall&);
std::string format_builtins_bool(const hil::FunctionCall&, bool);
std::string format_builtins_string(const hil::FunctionCall&, std::string);
std::string format_builtins_integer(const hil::FunctionCall&, int);
std::string format_builtins_character(
    const hil::FunctionCall&,
    const Character&);
std::string format_builtins_item(const hil::FunctionCall&, const Item&);

std::string space_if_needed();

namespace detail
{

template <typename Head = Character const&>
std::string format_literal_type(Character const& c)
{
    return "<Character: "s + std::to_string(c.index) + ">"s;
}

template <typename Head = Item const&>
std::string format_literal_type(Item const& i)
{
    return "<Item: "s + std::to_string(i.index) + ">"s;
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

template <typename Head = const Character&>
std::string format_function_type(
    hil::FunctionCall const& func,
    const Character& chara)
{
    return format_builtins_character(func, chara);
}

template <typename Head = const Item&>
std::string format_function_type(
    hil::FunctionCall const& func,
    const Item& item)
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
        if (lua::lua->get_handle_manager().handle_is<Character>(table))
        {
            auto& chara =
                lua::lua->get_handle_manager().get_ref<Character>(table);
            return format_builtins_character(func, chara);
        }
        else if (lua::lua->get_handle_manager().handle_is<Item>(table))
        {
            auto& item_ref =
                lua::lua->get_handle_manager().get_ref<Item>(table);
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
    UNUSED(count);

    for (size_t i = 0; i < formatted.size(); i++)
    {
        hil::Value v = ctxt.hilParts.at(i);
        if (v.is<hil::FunctionCall>())
        {
            hil::FunctionCall func = v.as<hil::FunctionCall>();

            if (func.args.size() == 0)
            {
                formatted.at(i) = format_builtins_argless(func);
            }
        }
    }
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
template <typename... Tail>
std::string fmt_hil(const std::string& hil, Tail&&... tail)
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

    return fmt_with_context(p.context, std::forward<Tail>(tail)...);
}



class Store
{
public:
    Store(){};
    ~Store() = default;

    struct Location
    {
        Location(fs::path locale_dir, std::string mod_name)
            : locale_dir(locale_dir)
            , mod_name(mod_name)
        {
        }

        fs::path locale_dir;
        std::string mod_name;
    };

    void init(const std::vector<Store::Location>&);

    // For testing use.
    void load(std::istream&, const std::string&, const std::string&);

    void clear()
    {
        storage.clear();
    }

    optional<const hil::Context&> find_translation(const I18NKey& key)
    {
        // In the unlikely event that a single locale key refers to
        // both a single string and a list, the string will be chosen.
        // This normally won't happen accidentally since duplicate
        // locale keys will expand into an object (per current HCL
        // decoding rules).

        const auto& found = storage.find(key);
        if (found != storage.end())
        {
            return found->second;
        }

        const auto& found_list = list_storage.find(key);
        if (found_list != list_storage.end())
        {
            const auto& list = found_list->second;
            return list.at(rnd(list.size()));
        }

        return none;
    }

    template <typename Head, typename... Tail>
    optional<std::string>
    get_optional(const I18NKey& key, Head const& head, Tail&&... tail)
    {
        const auto& found = find_translation(key);
        if (!found)
        {
            return none;
        }

        return fmt_with_context(*found, head, std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    optional<std::string> get_optional(const I18NKey& key, Tail&&... tail)
    {
        const auto& found = find_translation(key);
        if (!found)
        {
            return none;
        }

        return fmt_with_context(*found, std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    std::string get(const I18NKey& key, Head const& head, Tail&&... tail)
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
    std::string get(const I18NKey& key, Tail&&... tail)
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
    std::string
    get_enum(const I18NKey& key, int index, Head const& head, Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index),
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    std::string get_enum(const I18NKey& key, int index, Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index), std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    optional<std::string> get_enum_optional(
        const I18NKey& key,
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
    get_enum_optional(const I18NKey& key, int index, Tail&&... tail)
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

    // Returns string list. If the value associated with `key` is a scalar,
    // returns 1-size list which contains the value. If `key` does not exist,
    // returns empty list.
    template <typename... Args>
    std::vector<std::string> get_list(const I18NKey& key, Args&&... args)
    {
        std::vector<std::string> ret;

        const auto& found = storage.find(key);
        if (found != storage.end())
        {
            ret.push_back(
                fmt_with_context(found->second, std::forward<Args>(args)...));
            return ret;
        }

        const auto& found_list = list_storage.find(key);
        if (found_list != list_storage.end())
        {
            std::transform(
                std::begin(found_list->second),
                std::end(found_list->second),
                std::back_inserter(ret),
                [&](const auto& x) {
                    return fmt_with_context(x, std::forward<Args>(args)...);
                });
            return ret;
        }

        return ret;
    }


    const fs::path& get_locale_dir(const std::string& mod_name)
    {
        return locale_dir_table[mod_name];
    }


private:
    void load(const fs::path&, const std::string&);

    void visit(const hcl::Value&, const std::string&, const std::string&);
    void
    visit_object(const hcl::Object&, const std::string&, const std::string&);
    void visit_list(const hcl::List&, const std::string&, const std::string&);
    void
    visit_string(const std::string&, const std::string&, const std::string&);

    /***
     * Storage for single pieces of localized texts.
     */
    std::unordered_map<I18NKey, hil::Context> storage;

    /***
     * Storage for lists of localized text.
     *
     * When retrieving text using a locale key referring to a list element,
     * the text will be chosen randomly.
     */
    std::unordered_map<I18NKey, std::vector<hil::Context>> list_storage;

    std::set<I18NKey> unknown_keys;

    // Key: mod name.
    // Value: locale directory.
    std::unordered_map<std::string, fs::path> locale_dir_table;
};

extern i18n::Store s;

} // namespace i18n
} // namespace elona
