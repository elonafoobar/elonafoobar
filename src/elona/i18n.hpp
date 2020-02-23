#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../thirdparty/microhil/hil.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "../util/strutil.hpp"
#include "character.hpp"
#include "filesystem.hpp"
#include "hcl.hpp"
#include "item.hpp"
#include "log.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/i18n_function_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/wrapped_function.hpp"
#include "macro.hpp"
#include "optional.hpp"



using namespace std::literals::string_literals;

namespace elona
{

using I18NKey = std::string;



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

struct LocalizedText
{
    LocalizedText(hil::Context context)
        : context(context)
    {
        has_function_call = false;

        for (hil::Value value : context.hilParts)
        {
            if (value.is<hil::FunctionCall>())
            {
                has_function_call = true;
                break;
            }
        }
    }
    hil::Context context;
    bool has_function_call;
};

std::string space_if_needed();

namespace detail
{

/**
 * Does argument "_1" have argument index 1?
 */
inline bool arg_has_index(std::string ident, int count)
{
    if (ident.size() == 2)
    {
        if (ident[0] != '_')
        {
            return false;
        }
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
 * For argument "_1", return argument index 1.
 */
inline optional<int> arg_index(std::string ident)
{
    if (ident.size() == 2)
    {
        if (ident[0] != '_')
        {
            return none;
        }
        char c = ident[1];
        int c_as_digit = c - '0';
        if (c_as_digit < 0 || c_as_digit > 9)
        {
            return none;
        }
        return c_as_digit;
    }
    return none;
}

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

template <typename Head = Item const&>
void add_arg(sol::table& args, Item const& head)
{
    args.add(lua::lua->get_handle_manager().get_handle(head));
}

template <typename Head = Character const&>
void add_arg(sol::table& args, Character const& head)
{
    args.add(lua::lua->get_handle_manager().get_handle(head));
}

template <typename Head = const char* const&>
void add_arg(sol::table& args, const char* const& head)
{
    args.add(std::string(head));
}

template <typename Head, typename... Tail>
void add_arg(sol::table& args, Head const& head)
{
    args.add(head);
}

inline int make_args(sol::table& args, int size)
{
    UNUSED(args);

    return size;
}

template <typename Head>
int make_args(sol::table& args, int size, Head const& head)
{
    add_arg(args, head);
    return size + 1;
}

template <typename Head, typename... Tail>
int make_args(sol::table& args, int size, Head const& head, Tail&&... tail)
{
    add_arg(args, head);
    return make_args(args, size + 1, std::forward<Tail>(tail)...);
}

inline std::string run_i18n_function(
    sol::protected_function& function,
    sol::table& args)
{
    lua::lua->get_state()->set("_FUNCTION", function);
    lua::lua->get_state()->set("_ARGS", args);
    auto result = lua::lua->get_state()->safe_script(
        "return _FUNCTION(table.unpack(_ARGS))");
    lua::lua->get_state()->set("_FUNCTION", sol::lua_nil);
    lua::lua->get_state()->set("_ARGS", sol::lua_nil);

    if (!result.valid())
    {
        return "<error>";
    }
    else
    {
        auto text = result.get<sol::optional<std::string>>();
        if (!text)
        {
            return "<nil>";
        }
        else
        {
            return *text;
        }
    }
}

inline std::string format_function_call(
    const hil::FunctionCall& call,
    sol::table& args,
    int args_size)
{
    auto it = lua::lua->get_i18n_function_manager().find_function(call.name);
    if (!it)
    {
        return "<unknown function " + call.name + ">";
    }
    sol::protected_function& function = *it;

    // Create a new Lua table and push the arguments needed for the function
    // call to it, then unpack the table when calling the function.
    sol::table function_args = lua::lua->get_state()->create_table();
    int i = 1;
    for (const auto& arg : call.args)
    {
        if (arg.is<std::string>())
        {
            std::string ident = arg.as<std::string>();
            if (auto index = arg_index(ident))
            {
                if (*index > 0 && *index <= args_size)
                {
                    function_args.set(i++, args[*index]);
                }
                else
                {
                    return "<unknown parameter "s + call.name + ", _" + *index +
                        "/"s + args_size + ">"s;
                }
            }
            else
            {
                return "<unknown argument "s + ident + ">"s;
            }
        }
        else if (arg.is<bool>())
        {
            function_args.set(i++, arg.as<bool>());
        }
        else if (arg.is<int>())
        {
            function_args.set(i++, arg.as<int>());
        }
    }

    return run_i18n_function(function, function_args);
}

template <typename... Tail>
void fmt_internal_with_function(
    const hil::Context& ctxt,
    std::vector<optional<std::string>>& formatted,
    Tail&&... tail)
{
    sol::table args = lua::lua->get_state()->create_table();
    int args_size = make_args(args, 0, std::forward<Tail>(tail)...);

    for (size_t i = 0; i < formatted.size(); i++)
    {
        hil::Value v = ctxt.hilParts.at(i);
        if (v.is<std::string>())
        {
            std::string ident = v.as<std::string>();
            if (auto index = arg_index(ident))
            {
                if (*index > 0 && *index <= args_size)
                {
                    formatted.at(i) =
                        format_literal_type(args[*index].get<sol::object>());
                }
            }
        }
        else if (v.is<hil::FunctionCall>())
        {
            formatted.at(i) = format_function_call(
                v.as<hil::FunctionCall>(), args, args_size);
        }
    }
}

template <typename... Tail>
void fmt_internal_without_function(
    const hil::Context& ctxt,
    int arg_index,
    std::vector<optional<std::string>>& formatted)
{
    UNUSED(ctxt);
    UNUSED(arg_index);
    UNUSED(formatted);
}

template <typename Head, typename... Tail>
void fmt_internal_without_function(
    const hil::Context& ctxt,
    int arg_index,
    std::vector<optional<std::string>>& formatted,
    Head const& head,
    Tail&&... tail)
{
    for (size_t i = 0; i < formatted.size(); i++)
    {
        hil::Value v = ctxt.hilParts.at(i);
        assert(!v.is<hil::FunctionCall>());

        if (v.is<std::string>())
        {
            const std::string& arg_ident = v.as<std::string>();
            if (arg_has_index(arg_ident, arg_index))
            {
                // Substitute the argument at position "arg_index" into an
                // interpolation like "${_1}"
                formatted.at(i) = format_literal_type(head);
            }
        }
    }

    fmt_internal_without_function(
        ctxt, arg_index + 1, formatted, std::forward<Tail>(tail)...);
}

template <typename... Tail>
void fmt_internal(
    const LocalizedText& localized,
    std::vector<optional<std::string>>& formatted,
    Tail&&... tail)
{
    if (localized.has_function_call)
    {
        // Slow case: Push all args into Lua and call formatting function
        // registered in Lua.

        // A system like gettext would be too brittle because there are many
        // cases in the English translation where "is/are" are used depending on
        // the plurality of an argument, and this did not map cleanly on the
        // arguments of the Japanese translation. The original codebase also
        // used functions like yourself(), itemname(), and many
        // Japanese-specific sentence endings inside string interpolations that
        // depend on the state of a character who is speaking.

        // The result is the need to either pass every string fragment needed
        // for a string in every language supported to each format string (which
        // is infeasable as it makes mod localization far more complex), or use
        // functions in localized string interpolations that operate on
        // non-string arguments like characters/items.

        // Each interpolation function is implemented in Lua and can take
        // arguments of various types. The system is intended to support all the
        // ways that strings were once constructed in C++ with inline
        // interpolation, but externally.

        fmt_internal_with_function(
            localized.context, formatted, std::forward<Tail>(tail)...);
    }
    else
    {
        // Normal case: Use templated functions.

        // This could be replaced with a word-reordering capable version of
        // printf by converting the HIL string to a printf format string.

        fmt_internal_without_function(
            localized.context, 1, formatted, std::forward<Tail>(tail)...);
    }
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

template <typename... Tail>
std::string fmt_with_context(const LocalizedText& localized, Tail&&... tail)
{
    // If there is only text with no HIL interpolation, return the whole string.
    if (localized.context.textParts.size() == 1)
        return localized.context.textParts[0];

    std::vector<optional<std::string>> formatted(
        localized.context.hilParts.size());
    detail::fmt_internal(localized, formatted, std::forward<Tail>(tail)...);

    return fmt_interpolate_converted(localized.context, formatted);
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

    LocalizedText wrapped(p.context);
    return fmt_with_context(wrapped, std::forward<Tail>(tail)...);
}



class Store
{
public:
    Store(){};
    ~Store() = default;

    struct Location
    {
        Location(fs::path locale_dir, std::string mod_id)
            : locale_dir(locale_dir)
            , mod_id(mod_id)
        {
        }

        fs::path locale_dir;
        std::string mod_id;
    };

    void init(const std::vector<Store::Location>&);

    // For testing use.
    void load(std::istream&, const std::string&, const std::string&);

    void clear()
    {
        storage.clear();
    }

    optional<const LocalizedText&> find_translation(const I18NKey& key)
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
    [[nodiscard]] optional<std::string>
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
    [[nodiscard]] optional<std::string> get_optional(
        const I18NKey& key,
        Tail&&... tail)
    {
        const auto& found = find_translation(key);
        if (!found)
        {
            return none;
        }

        return fmt_with_context(*found, std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    [[nodiscard]] std::string
    get(const I18NKey& key, Head const& head, Tail&&... tail)
    {
        if (auto text = get_optional(key, head, std::forward<Tail>(tail)...))
        {
            return *text;
        }
        else
        {
            if (unknown_keys.find(key) == unknown_keys.end())
            {
                ELONA_ERROR("i18n") << "Unknown I18N ID: " << key;
                unknown_keys.insert(key);
            }
            return u8"<Unknown ID: " + key + ">";
        }
    }

    template <typename... Tail>
    [[nodiscard]] std::string get(const I18NKey& key, Tail&&... tail)
    {
        if (auto text = get_optional(key, std::forward<Tail>(tail)...))
        {
            return *text;
        }
        else
        {
            if (unknown_keys.find(key) == unknown_keys.end())
            {
                ELONA_ERROR("i18n") << "Unknown I18N ID: " << key;
                unknown_keys.insert(key);
            }
            return u8"<Unknown ID: " + key + ">";
        }
    }


    // Convenience methods for cases like "core.element._<enum index>.name"

    template <typename Head, typename... Tail>
    [[nodiscard]] std::string
    get_enum(const I18NKey& key, int index, Head const& head, Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index),
            head,
            std::forward<Tail>(tail)...);
    }

    template <typename... Tail>
    [[nodiscard]] std::string
    get_enum(const I18NKey& key, int index, Tail&&... tail)
    {
        return get(
            key + "._" + std::to_string(index), std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    [[nodiscard]] optional<std::string> get_enum_optional(
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
    [[nodiscard]] optional<std::string>
    get_enum_optional(const I18NKey& key, int index, Tail&&... tail)
    {
        return get_optional(
            key + "._" + std::to_string(index), std::forward<Tail>(tail)...);
    }

    template <typename Head, typename... Tail>
    [[nodiscard]] std::string get_enum_property(
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
    [[nodiscard]] std::string get_enum_property(
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
    [[nodiscard]] optional<std::string> get_enum_property_opt(
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
    [[nodiscard]] optional<std::string> get_enum_property_opt(
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
    [[nodiscard]] std::vector<std::string> get_list(
        const I18NKey& key,
        Args&&... args)
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


    // TODO: rename
    // Typical usage:
    // i18n::s.get_m("class", "modname.classname", "name")
    // // The above call is equivalent to:
    // i18n::s.get("modname.class.classname.name")
    [[nodiscard]] std::string get_m(
        const I18NKey& data_type_key,
        const I18NKey& data_key,
        const I18NKey& property_name)
    {
        const auto pair = strutil::split_on_string(data_key, ".");
        const auto key = pair.first + "." + data_type_key + "." + pair.second +
            "." + property_name;
        return get(key);
    }


    // TODO: rename
    // Typical usage:
    // i18n::s.get_m_optional("class", "modname.classname", "name")
    // // The above call is equivalent to:
    // i18n::s.get_optional("modname.class.classname.name")
    [[nodiscard]] optional<std::string> get_m_optional(
        const I18NKey& data_type_key,
        const I18NKey& data_key,
        const I18NKey& property_name)
    {
        const auto pair = strutil::split_on_string(data_key, ".");
        const auto key = pair.first + "." + data_type_key + "." + pair.second +
            "." + property_name;
        return get_optional(key);
    }


    const fs::path& get_locale_dir(const std::string& mod_id)
    {
        return locale_dir_table[mod_id];
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
    std::unordered_map<I18NKey, LocalizedText> storage;

    /***
     * Storage for lists of localized text.
     *
     * When retrieving text using a locale key referring to a list element,
     * the text will be chosen randomly.
     */
    std::unordered_map<I18NKey, std::vector<LocalizedText>> list_storage;

    std::set<I18NKey> unknown_keys;

    // Key: mod ID.
    // Value: locale directory.
    std::unordered_map<std::string, fs::path> locale_dir_table;
};

extern i18n::Store s;

} // namespace i18n
} // namespace elona
