#include <charconv>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

using namespace std::literals::string_view_literals;
using namespace std::literals::string_literals;



namespace elona
{
namespace lua
{
namespace fmt
{

namespace detail
{

inline constexpr bool is_digit(char c) noexcept
{
    return '0' <= c && c <= '9';
}


inline constexpr bool is_ident_start(char c) noexcept
{
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_';
}


inline constexpr bool is_ident_continue(char c) noexcept
{
    return is_ident_start(c) || is_digit(c);
}

} // namespace detail



using ParseResult = std::pair<sol::object, sol::optional<std::string>>;


class FormatParser
{
public:
    FormatParser(std::string_view src, sol::state_view L)
        : src(src)
        , idx(0)
        , L(L)
    {
    }



    ParseResult parse()
    {
        size_t plain_string_start = 0;
        auto segments = make_table();
        int segments_index = 1;

        while (true)
        {
            if (src.size() <= idx)
            {
                break;
            }

            const auto c = src[idx];
            if (c == '{')
            {
                if (src.size() <= idx + 1)
                {
                    return failure("missing '}'");
                }
                if (src[idx + 1] == '{')
                {
                    ++idx;
                    if (plain_string_start < idx)
                    {
                        segments[segments_index] = std::string{src.substr(
                            plain_string_start, idx - plain_string_start)};
                        ++segments_index;
                    }
                    ++idx;
                    plain_string_start = idx;
                    continue;
                }
                if (plain_string_start < idx)
                {
                    segments[segments_index] = std::string{src.substr(
                        plain_string_start, idx - plain_string_start)};
                    ++segments_index;
                }
                ++idx;
                auto exp = parse_exp();
                if (exp.second)
                {
                    return exp;
                }
                if (idx < src.size() && src[idx] == '}')
                {
                    ++idx;
                }
                else
                {
                    return failure("missing '}'");
                }
                segments[segments_index] = exp.first;
                ++segments_index;
                plain_string_start = idx;
            }
            else if (c == '}')
            {
                if (idx + 1 < src.size() && src[idx + 1] == '}')
                {
                    ++idx;
                    if (plain_string_start < idx)
                    {
                        segments[segments_index] = std::string{src.substr(
                            plain_string_start, idx - plain_string_start)};
                        ++segments_index;
                    }
                    ++idx;
                    plain_string_start = idx;
                    continue;
                }
                else
                {
                    return failure("missing '{'");
                }
            }
            else
            {
                ++idx;
            }
        }
        if (plain_string_start < idx)
        {
            segments[segments_index] = std::string{
                src.substr(plain_string_start, idx - plain_string_start)};
            ++segments_index;
        }

        return success(segments);
    }



private:
    std::string_view src;
    size_t idx;
    sol::state_view L;



    ParseResult success(sol::object ok)
    {
        return ParseResult{ok, sol::nullopt};
    }



    ParseResult failure(const std::string& err)
    {
        return ParseResult{sol::lua_nil, err};
    }



    ParseResult parse_exp()
    {
        if (src.size() <= idx)
        {
            return failure("expect an expression, but got EOS");
        }

        // Skip whitespaces
        while (idx < src.size() && src[idx] == ' ')
        {
            ++idx;
        }

        const auto c = src[idx];
        if (c == '$')
        {
            return parse_arg_index();
        }
        else if (c == '"')
        {
            return failure(
                "string in string interpolation has not been implemented yet!");
        }
        else if (c == '\'')
        {
            return failure(
                "string in string interpolation has not been implemented yet!");
        }
        else if (detail::is_digit(c))
        {
            return parse_int();
        }
        else if (detail::is_ident_start(c))
        {
            return parse_ident();
        }
        else
        {
            return failure("invalid character: "s + src[idx]);
        }
    }



    // \$[0-9]+
    ParseResult parse_arg_index()
    {
        ++idx; // '$'
        if (src.size() <= idx)
        {
            return failure("expected argument index after '$', but got EOS");
        }
        const auto start_idx = idx;
        uint8_t arg_idx;
        const auto [ptr, ec] = std::from_chars(
            src.data() + start_idx, src.data() + src.size(), arg_idx);
        const auto end_idx = ptr - src.data();
        if (ec == std::errc::invalid_argument)
        {
            return failure(
                "expected argument index after '$', but got '"s +
                src[start_idx] + "'");
        }
        if (ec == std::errc::result_out_of_range)
        {
            return failure(
                "integer out of range: "s +
                std::string{src.substr(start_idx, end_idx - start_idx)});
        }
        idx = end_idx;
        // return {"v", arg_idx}
        auto ret = make_table();
        ret[1] = "v";
        ret[2] = arg_idx;
        return success(ret);
    }



    // [0-9]+
    ParseResult parse_int()
    {
        const auto start_idx = idx;
        int64_t num;
        const auto [ptr, ec] = std::from_chars(
            src.data() + start_idx, src.data() + src.size(), num);
        const auto end_idx = ptr - src.data();
        if (ec == std::errc::result_out_of_range)
        {
            return failure(
                "integer out of range: "s +
                std::string{src.substr(start_idx, end_idx - start_idx)});
        }
        idx = end_idx;
        return success(make_object(num));
    }



    ParseResult parse_ident()
    {
        const auto ident = parse_ident_internal();

        if (ident == "nil"sv)
        {
            return success(make_object(""));
        }
        else if (ident == "true"sv)
        {
            return success(make_object(true));
        }
        else if (ident == "false"sv)
        {
            return success(make_object(false));
        }
        else if (src.size() <= idx)
        {
            return success(make_object(std::string{ident}));
        }
        else
        {
            return parse_func_call(ident);
        }
    }



    ParseResult parse_func_call(std::string_view ident)
    {
        // mod.func(args, ...)

        // Parse function name
        std::string_view mod_name;
        std::string_view func_name;
        if (src[idx] == '.')
        {
            ++idx;
            if (src.size() <= idx)
            {
                return failure("expect an identifier after '.', but got EOS");
            }
            mod_name = ident;
            if (detail::is_ident_start(src[idx]))
            {
                func_name = parse_ident_internal();
            }
            else
            {
                return failure(
                    "expect an identifier after '.', but got '"s + src[idx] +
                    "'");
            }
        }
        else
        {
            mod_name = "core"sv;
            func_name = ident;
        }

        // Parse arguments.
        if (src.size() <= idx)
        {
            return failure("expect '(', but got EOS");
        }
        if (src[idx] != '(')
        {
            return failure("expected '(', but got '"s + src[idx] + "'");
        }

        ++idx; // '('

        // return {"f", mod_name.."."..func_name, args, ...}
        auto ret = make_table();
        ret[1] = "f";
        ret[2] = std::string{mod_name} + "." + std::string{func_name};
        int ret_index = 3;
        while (idx < src.size())
        {
            if (src[idx] == ')')
            {
                ++idx;
                return success(ret);
            }
            auto exp = parse_exp();
            if (exp.second)
            {
                return exp;
            }
            ret[ret_index] = exp.first;
            ++ret_index;
            if (src.size() <= idx)
            {
                return failure("expect ',' or ')', but got EOS");
            }
            else if (src[idx] == ',')
            {
                ++idx;
            }
            else if (src[idx] != ')')
            {
                return failure(
                    "expected ',' or ')', but got '"s + src[idx] + "'");
            }
        }
        return failure("expected ')', but got EOS");
    }



    std::string_view parse_ident_internal()
    {
        const auto start_idx = idx;
        while (idx < src.size() && detail::is_ident_continue(src[idx]))
        {
            ++idx;
        }
        return src.substr(start_idx, idx - start_idx);
    }



    template <typename T>
    sol::object make_object(T&& value)
    {
        return sol::make_object(L, std::forward<T>(value));
    }



    sol::table make_table()
    {
        return L.create_table();
    }
};

} // namespace fmt
} // namespace lua
} // namespace elona
