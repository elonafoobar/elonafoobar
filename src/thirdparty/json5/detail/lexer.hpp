#pragma once

#include "../exceptions.hpp"
#include "./token.hpp"
#include "./util.hpp"



namespace json5
{
namespace detail
{

class lexer
{
public:
    lexer(const std::string& source)
        : _source(source)
        , _pos(0)
    {
    }



    token scan()
    {
        skip_whitespaces_and_comments();

        if (eof())
            return token{token_type::eof};

        return scan_internal();
    }



private:
    std::string _source;
    size_t _pos;



    void skip_whitespaces_and_comments()
    {
        if (eof())
            return;

        while (true)
        {
            const auto c = peek();
            switch (c)
            {
            case '/':
            {
                get();
                if (eof())
                {
                    throw invalid_char("'//' or '/*'");
                }

                const auto k = peek();
                if (k == '/')
                {
                    get();
                    while (!eof())
                    {
                        const auto c = get();
                        if (c == '\r')
                        {
                            if (!eof() && peek() == '\n')
                            {
                                get();
                            }
                            break;
                        }
                        else if (c == '\n')
                        {
                            break;
                        }
                    }
                }
                else if (k == '*')
                {
                    get();
                    bool previos_char_is_asterisk = false;
                    while (true)
                    {
                        if (eof())
                        {
                            throw invalid_char("'*/'");
                        }

                        const auto c = get();
                        if (c == '*')
                        {
                            previos_char_is_asterisk = true;
                        }
                        else if (c == '/')
                        {
                            if (previos_char_is_asterisk)
                            {
                                break;
                            }
                        }
                        else
                        {
                            previos_char_is_asterisk = false;
                        }
                    }
                }
                else
                {
                    throw invalid_char("'//' or '/*'");
                }
            }
            break;
            case ' ':
            case '\t':
            case '\r':
            case '\n': get(); break;
            default: return;
            }
        }
    }



    token scan_internal()
    {
        const auto c = peek();
        switch (c)
        {
        case '[': get(); return token{token_type::bracket_left};
        case ']': get(); return token{token_type::bracket_right};
        case '{': get(); return token{token_type::brace_left};
        case '}': get(); return token{token_type::brace_right};
        case ':': get(); return token{token_type::colon};
        case ',': get(); return token{token_type::comma};
        case '\'':
        case '"': return scan_string();
        default: return scan_numeric_or_identifier();
        }
    }



    token scan_string()
    {
        std::string s;
        const auto q = get(); // ' or "
        while (true)
        {
            if (eof())
            {
                throw invalid_char(q == '"' ? "'\"'" : "'");
            }

            const auto c = get();
            if (c == q)
            {
                break;
            }
            else if (c == '\r' || c == '\n')
            {
                const char* br;
                if (!eof() && peek() == '\n')
                {
                    br = "\\r\\n";
                }
                else if (c == '\r')
                {
                    br = "\\r";
                }
                else
                {
                    br = "\\n";
                }
                throw syntax_error{
                    std::string{"raw line break cannot be included in string "
                                "literals, use '"} +
                    br + "'"};
            }
            else if (c == '\\')
            {
                s += scan_escape_sequence();
            }
            else
            {
                s += c;
            }
        }
        return token{token_type::string, s};
    }



    /*
     * Escape Sequence Table
     * +----+-----------------+--------+
     * | \' | apostrophe      | U+0027 |
     * | \" | quotation mark  | U+0022 |
     * | \\ | reverse solidus | U+005C |
     * | \b | backspace       | U+0008 |
     * | \f | form feed       | U+000C |
     * | \n | line feed       | U+000A |
     * | \r | carriage return | U+000D |
     * | \t | horizontal tab  | U+0009 |
     * | \v | vertical tab    | U+000B |
     * | \0 | null            | U+0000 |
     * +----+-----------------+--------+
     */
    std::string scan_escape_sequence()
    {
        if (eof())
        {
            throw invalid_char("escape sequence");
        }

        const auto c = get();
        switch (c)
        {
        case '\'': return "'";
        case '"': return "\"";
        case '\\': return "\\";
        case 'b': return "\b";
        case 'f': return "\f";
        case 'n': return "\n";
        case 'r': return "\r";
        case 't': return "\t";
        case 'v': return "\v";
        case '0':
            if (is_digit(peek()))
            {
                throw syntax_error{
                    "C-style octal character literal is not allowed except for "
                    "'\\0'. Use "
                    "prefix \\x or \\u"};
            }
            else
            {
                return "\0";
            }
        case '\r':
            if (peek() == '\n')
            {
                get();
            }
            return ""; // skip the line break.
        case '\n': return ""; // skip the line break.
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            throw syntax_error{
                "C-style octal character literal is not allowed except for "
                "'\\0'. Use "
                "prefix \\x or \\u"};
        case 'x':
        {
            // \xNN (N: a hexadecimal digit)
            // U+0000 - U+00FF
            char32_t codepoint = escape_sequence_codepoint(2);
            if (is_hex_digit(peek()))
            {
                throw syntax_error{
                    "Escape sequence prefixed by '\\x' must be followed by "
                    "only two hexadecimal digits, but got third one."};
            }
            return codepoint_to_string(codepoint);
        }
        case 'u':
        {
            // \uNNNN (N: a hexadecimal digit)
            // U+0000 - U+FFFF
            char32_t first = escape_sequence_codepoint(4);
            if (is_hex_digit(peek()))
            {
                throw syntax_error{
                    "Escape sequence prefixed by '\\u' must be followed by "
                    "only four hexadecimal digits, but got fifth one."};
            }
            if (peek() == '\\')
            {
                // Surrogate pair?
                get();
                if (peek() == 'u')
                {
                    // They are a surrogate pair.
                    char32_t second = escape_sequence_codepoint(4);
                    if (is_hex_digit(peek()))
                    {
                        throw syntax_error{
                            "Escape sequence prefixed by '\\u' must be "
                            "followed by "
                            "only four hexadecimal digits, but got fifth one."};
                    }
                    return codepoint_to_string(
                        surrogate_pair_to_codepoint(first, second));
                }
                else
                {
                    if (is_surrogate_pair_first(first))
                    {
                        throw invalid_char("second part of surrogate pair");
                    }
                    // Not surrogate pair, next escape sequence.
                    return codepoint_to_string(first) + scan_escape_sequence();
                }
            }
            else
            {
                return codepoint_to_string(first);
            }
        }
        default: return std::string{1, c};
        }
    }



    /*
    NumericOrIdentifier
        Numeric
        Identifier

    Numeric
        Sign? 'Infinity'
        Sign? 'NaN'
        Sign? HexadecimalInteger
        Sign? '0' Digit* ('.' Digit*)? Exponent?
        Sign? NonZeroDigit Digit* ('.' Digit*)? Exponent?
        Sign? '.' Digit+ Exponent?

    Sign
        '+'
        '-'

    Exponent
        ExponentPrefix Sign? Digit+

    ExponentPrefix
        'e'
        'E'

    HexadecimalInteger
        HexadecimalPrefix HexDigit+

    HexadecimalPrefix
        '0x'
        '0X'

    Digit
        '0'
        NonZeroDigit

    NonZeroDigit
        '1' | '2' | ... | '9'

    HexDigit
        Digit
        'a' | 'b' | ... | 'f'
        'A' | 'B' | ... | 'F'

    Identifier
        IdentifierStart IdentifierContinue*

    IdentifierStart
        '$'
        '_'
        'a' | 'b' | ... | 'z'
        'A' | 'B' | ... | 'Z'

    IdentifierContinue
        IdentifierStart
        Digit
    */
    token scan_numeric_or_identifier()
    {
        int8_t sign = 0;
        bool starts_with_decimal_point = false;
        size_t start = _pos;

        if (peek() == '+')
        {
            get();
            ++start;
            sign = 1;
        }
        else if (peek() == '-')
        {
            get();
            sign = -1;
        }

        const auto c = peek();
        if (c == '0')
        {
            get();
            if (eof())
            {
                return token{integer_type{0}};
            }

            if (peek() == 'x' || peek() == 'X')
            {
                get();
                consume_hexadecial_integer();
                return static_cast<integer_type>(
                    std::stoll(_source.substr(start), 0, 16));
            }

            while (!eof())
            {
                if (is_digit(peek()))
                {
                    get();
                }
                else
                {
                    break;
                }
            }
        }
        else if (is_digit(c))
        {
            while (!eof())
            {
                if (is_digit(peek()))
                {
                    get();
                }
                else
                {
                    break;
                }
            }
        }
        else if (c == '.')
        {
            starts_with_decimal_point = true;
        }
        else if (is_identifier_start(c))
        {
            return scan_identifier(sign);
        }
        else
        {
            throw syntax_error{"invalid character, " +
                               get_current_char_for_error_message()};
        }

        bool has_decimal_point = false;
        if (peek() == '.')
        {
            get();
            bool has_any_digit = false;
            while (!eof())
            {
                if (is_digit(peek()))
                {
                    get();
                    has_any_digit = true;
                }
                else
                {
                    break;
                }
            }
            if (starts_with_decimal_point && !has_any_digit)
            {
                throw invalid_char("any digit");
            }
            has_decimal_point = true;
        }

        bool has_exponent = consume_exponent();
        if (has_decimal_point || has_exponent)
        {
            return token{
                static_cast<number_type>(std::stold(_source.substr(start), 0))};
        }
        else
        {
            return token{static_cast<integer_type>(
                std::stoll(_source.substr(start), 0))};
        }
    }



    void literal(const char* s)
    {
        // The first character of s has already been checked by the caller.
        get();
        for (const char* s_ = s + 1; *s_; ++s_)
        {
            const auto c = peek();
            if (*s_ == c)
            {
                get();
            }
            else
            {
                throw invalid_char(s);
            }
        }
    }



    void consume_hexadecial_integer()
    {
        bool has_any_digit = false;
        while (!eof())
        {
            if (is_hex_digit(peek()))
            {
                get();
                has_any_digit = true;
            }
            else
            {
                break;
            }
        }
        if (!has_any_digit)
        {
            throw invalid_char("hexadecimal digit (0-9, a-f or A-F)");
        }
    }



    bool consume_exponent()
    {
        if (eof())
            return false;

        if (peek() != 'e' && peek() != 'E')
            return false;

        get();
        if (eof())
        {
            throw invalid_char("digit");
        }
        if (peek() == '+' || peek() == '-')
        {
            get();
        }
        bool has_any_digit = false;
        while (!eof())
        {
            if (is_hex_digit(peek()))
            {
                get();
                has_any_digit = true;
            }
            else
            {
                break;
            }
        }
        if (!has_any_digit)
        {
            throw invalid_char("any digit");
        }

        return true;
    }



    token scan_identifier(int8_t sign)
    {
        string_type name;
        while (!eof())
        {
            if (is_identifier_continue(peek()))
            {
                name += get();
            }
            else
            {
                break;
            }
        }

        // Check special literals.
        switch (name[0])
        {
        case 'I':
            if (name == "Infinity")
            {
                if (sign)
                {
                    return token{sign * infinity()};
                }
                else
                {
                    return token{token_type::infinity};
                }
            }
            break;
        case 'N':
            if (name == "NaN")
            {
                if (sign)
                {
                    return token{nan()};
                }
                else
                {
                    return token{token_type::nan};
                }
            }
            break;
        case 'n':
            if (name == "null")
            {
                if (sign)
                {
                    throw syntax_error{
                        "expected any number, but actually got 'null'"};
                }
                else
                {
                    return token{token_type::null};
                }
            }
            break;
        case 't':
            if (name == "true")
            {
                if (sign)
                {
                    throw syntax_error{
                        "expected any number, but actually got 'true'"};
                }
                else
                {
                    return token{token_type::true_};
                }
            }
            break;
        case 'f':
            if (name == "false")
            {
                if (sign)
                {
                    throw syntax_error{
                        "expected any number, but actually got 'false'"};
                }
                else
                {
                    return token{token_type::false_};
                }
            }
            break;
        default: break;
        }

        return token{token_type::identifier, name};
    }



    char32_t escape_sequence_codepoint(size_t n)
    {
        char32_t ret{};
        for (size_t i = 0; i < n; ++i)
        {
            const auto c = peek();
            if (!is_hex_digit(c))
            {
                throw invalid_char("hexadecimal digit (0-9, a-f or A-F)");
            }
            ret = ret * 16 + hex_digit_char_to_integer(c);
        }
        return ret;
    }



    char peek() const
    {
        return _source[_pos];
    }



    char get()
    {
        const auto ret = _source[_pos];
        ++_pos;
        return ret;
    }



    bool eof() const
    {
        return _source.size() <= _pos;
    }



    std::string format_char(char c)
    {
        // TODO
        return std::string(1, c);
    }



    syntax_error invalid_char(const char* expected_char)
    {
        return syntax_error{std::string{"expected "} + expected_char +
                            ", but actually got " +
                            get_current_char_for_error_message() + "."};
    }



    std::string get_current_char_for_error_message() const
    {
        if (eof())
            return "<EOF>";

        const size_t start = _pos;
        const size_t end = start + byte_count_utf8(_source[_pos]);
        if (_source.size() <= end)
            return "<Invalid UTF-8>";

        switch (end - start)
        {
        case 1:
            switch (peek())
            {
            case '\0': return "<NUL>";
            case '"': return "\"";
            case '\'': return "'";
            case '\\': return "'\\'";
            case '\b': return "'\\b'";
            case '\f': return "'\\f'";
            case '\n': return "'\\n'";
            case '\r': return "'\\r'";
            case '\t': return "'\\t'";
            case '\v': return "'\\v'";
            default:
                if (peek() < ' ')
                {
                    return "'U+'" +
                        codepoint_to_hex_digit_string(
                               static_cast<char32_t>(peek()));
                }
                else
                {
                    return std::string{"'"} + peek() + "'";
                }
            }
        case 2:
        {
            const auto first = _source[start];
            const auto second = _source[start + 1];
            const char32_t codepoint =
                ((first & 0b0001'1111) << 6) | (second & 0b0011'1111);
            return "'U+'" + codepoint_to_hex_digit_string(codepoint);
        }
        case 3:
        {
            const auto first = _source[start];
            const auto second = _source[start + 1];
            const auto third = _source[start + 2];
            const char32_t codepoint = ((first & 0b0000'1111) << 12) |
                ((second & 0b0011'1111) << 6) | (third & 0b0011'1111);
            return "'U+'" + codepoint_to_hex_digit_string(codepoint);
        }
        case 4:
        {
            const auto first = _source[start];
            const auto second = _source[start + 1];
            const auto third = _source[start + 2];
            const auto forth = _source[start + 3];
            const char32_t codepoint = ((first & 0b0000'0111) << 18) |
                ((second & 0b0011'1111) << 12) | ((third & 0b0011'1111) << 6) |
                (forth & 0b0011'1111);
            return "'U+'" + codepoint_to_hex_digit_string(codepoint);
        }
        default: return "<Invalid UTF-8>";
        }
    }
};



class token_stream
{
public:
    token_stream(const std::string& source)
        : _lexer(source)
    {
        get();
    }



    token peek()
    {
        return _lookahead;
    }



    token get()
    {
        const auto ret = _lookahead;
        _lookahead = _lexer.scan();
        return ret;
    }



private:
    lexer _lexer;
    token _lookahead;
};

} // namespace detail
} // namespace json5
