#ifndef MICROHIL_H_
#define MICROHIL_H_

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>

namespace hil
{

class Value;

struct FunctionCall
{
    FunctionCall(std::string& v) : name(v) {}
    FunctionCall(const char* v) : name(v) {}
    FunctionCall(const FunctionCall& other) {
        name = other.name;
        args = other.args;
    }
    ~FunctionCall() = default;

    std::string name;
    std::vector<Value> args;
};

namespace internal {
template<typename T> struct call_traits_value {
    typedef T return_type;
};
template<typename T> struct call_traits_ref {
    typedef const T& return_type;
};
} // namespace internal

template<typename T> struct call_traits;
template<> struct call_traits<bool> : public internal::call_traits_value<bool> {};
template<> struct call_traits<int> : public internal::call_traits_value<int> {};
template<> struct call_traits<int64_t> : public internal::call_traits_value<int64_t> {};
template<> struct call_traits<std::string> : public internal::call_traits_ref<std::string> {};
template<> struct call_traits<FunctionCall> : public internal::call_traits_ref<FunctionCall> {};

// A value is returned for std::vector<T>. Not reference.
// This is because a fresh vector is made.
template<typename T> struct call_traits<std::vector<T>> : public internal::call_traits_value<std::vector<T>> {};


class Value
{

public:
    enum Type {
        NULL_TYPE,
        BOOL_TYPE,
        INT_TYPE,
        IDENT_TYPE,
        FUNCTION_TYPE,
    };

    Value() : type_(NULL_TYPE), null_(nullptr) {}
    Value(bool v) : type_(BOOL_TYPE), bool_(v) {}
    Value(int v) : type_(INT_TYPE), int_(v) {}
    Value(int64_t v) : type_(INT_TYPE), int_(v) {}
    Value(const std::string& v) : type_(IDENT_TYPE), string_(new std::string(v)) {}
    Value(const char* v) : type_(IDENT_TYPE), string_(new std::string(v)) {}
    Value(const FunctionCall& v) : type_(FUNCTION_TYPE), func_(new FunctionCall(v)) {}
    Value(std::string&& v) : type_(IDENT_TYPE), string_(new std::string(std::move(v))) {}
    Value(FunctionCall&& v) : type_(FUNCTION_TYPE), func_(new FunctionCall(std::move(v))) {}

    Value(const Value& v);
    Value(Value&& v) noexcept;
    Value& operator=(const Value& v);
    Value& operator=(Value&& v) noexcept;

    Value(const void* v) = delete;
    ~Value();

    Type type() const { return type_; }

    bool valid() const { return type_ != NULL_TYPE; }
    template<typename T> bool is() const;
    template<typename T> typename call_traits<T>::return_type as() const;
private:
    static const char* typeToString(Type);

    template<typename T> void assureType() const;
    Value* ensureValue(const std::string& key);

    template<typename T> struct ValueConverter;

    Type type_;
    union {
        void* null_;
        bool bool_;
        int64_t int_;
        std::string* string_;
        FunctionCall* func_;
    };

    template<typename T> friend struct ValueConverter;
};

class Context
{
public:
  bool valid() const
  {
      for (auto&& value : hilParts)
      {
          if (!value.valid())
              return false;
      }

      return true;
  };
  std::vector<std::string> textParts;
  std::vector<Value> hilParts;
};

// parse() returns ParseResult.
struct ParseResult {
    ParseResult(hil::Context v, std::string er) :
        context(std::move(v)),
        errorReason(std::move(er)) {}

    bool valid() const { return context.valid(); }

    hil::Context context;
    std::string errorReason;
};

// Parses from std::istream.
ParseResult parse(std::istream&);
// Parses a file.
ParseResult parseFile(const std::string& filename);

namespace internal {

enum class TokenType {
    // Special tokens
    ILLEGAL,
    END_OF_FILE,
    COMMENT,

    IDENT, // literals

    NUMBER,  // 12345
    FLOAT,   // 123.45
    BOOL,    // true,false
    STRING,  // "abc"
    HIL,     // "${foo(bar)}"
    HEREDOC, // <<FOO\nbar\nFOO

    LBRACK, // [
    LPAREN, // (
    LBRACE, // {
    COMMA,  // ,
    PERIOD, // .

    RBRACK, // ]
    RPAREN, // )
    RBRACE, // }
};

class Token {
public:
    explicit Token(TokenType type) : type_(type) {}
    Token(TokenType type, const std::string& v) : type_(type), str_value_(v) {}
    Token(TokenType type, bool v) : type_(type), int_value_(v) {}
    Token(TokenType type, std::int64_t v) : type_(type), int_value_(v) {}
    Token(TokenType type, double v) : type_(type), double_value_(v) {}

    TokenType type() const { return type_; }
    const std::string& strValue() const { return str_value_; }
    bool boolValue() const { return int_value_ != 0; }
    std::int64_t intValue() const { return int_value_; }
    double doubleValue() const { return double_value_; }

private:
    TokenType type_;
    std::string str_value_;
    std::int64_t int_value_;
    double double_value_;
};

class Lexer {
public:
    explicit Lexer(std::istream& is) : is_(is),
                                       lineNo_(1),
                                       columnNo_(0) {}

    Token nextToken(bool);

    int lineNo() const { return lineNo_; }
    int columnNo() const { return columnNo_; }

    // Skips if UTF8BOM is found.
    // Returns true if success. Returns false if intermediate state is left.
    bool skipUTF8BOM();

    bool consume(char c);

private:
    bool current(char* c);
    void next();

    Token nextValueToken();
    Token nextNumber(bool leadingDot, bool leadingSub);

    void skipUntilNewLine();

    Token nextString();
    Token nextHereDoc();

    std::istream& is_;
    int lineNo_;
    int columnNo_;
};

class Parser {
public:
    explicit Parser(std::istream& is) : lexer_(is), token_(TokenType::ILLEGAL)
    {
        lexer_.skipUTF8BOM();
        nextToken(false);
    }

    // Parses. If failed, value should be invalid value.
    // You can get the error by calling errorReason().
    Context parse();
    const std::string& errorReason();

private:
    const Token& token() const { return token_; }
    void nextToken(bool isInHil) { token_ = lexer_.nextToken(isInHil); }
    bool consume(char c) { return lexer_.consume(c); }
    int columnNo() { return lexer_.columnNo(); }

    void skipForKey();
    void skipForValue();

    bool consumeForKey(TokenType);
    bool consumeForValue(TokenType);
    bool consumeEOLorEOFForKey();

    bool parseText(std::string&);
    bool parseHil(Value&);
    bool parseFunction(Value&, std::string);

    void addError(const std::string& reason);

    bool unindentHeredoc(const std::string& heredoc, std::string& out);

    Lexer lexer_;
    Token token_;
    std::string errorReason_;
};

} // namespace internal

// ----------------------------------------------------------------------
// Implementations

inline ParseResult parse(std::istream& is)
{
    if (!is) {
        return ParseResult(hil::Context(), "stream is in bad state. file does not exist?");
    }

    internal::Parser parser(is);
    hil::Context v = parser.parse();

    if (v.valid())
        return ParseResult(std::move(v), std::string());

    return ParseResult(std::move(v), std::move(parser.errorReason()));
}

inline ParseResult parseFile(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs) {
        return ParseResult(hil::Context(),
                           std::string("could not open file: ") + filename);
    }

    return parse(ifs);
}

inline std::string format(std::stringstream& ss)
{
    return ss.str();
}

template<typename T, typename... Args>
std::string format(std::stringstream& ss, T&& t, Args&&... args)
{
    ss << std::forward<T>(t);
    return format(ss, std::forward<Args>(args)...);
}

template<typename... Args>
#if defined(_MSC_VER)
__declspec(noreturn)
#else
[[noreturn]]
#endif
void failwith(Args&&... args)
{
    std::stringstream ss;
    throw std::runtime_error(format(ss, std::forward<Args>(args)...));
}

namespace internal {

inline std::string removeDelimiter(const std::string& s)
{
    std::string r;
    for (char c : s) {
        if (c == '_')
            continue;
        r += c;
    }
    return r;
}

inline std::string unescape(const std::string& codepoint)
{
    std::uint32_t x;
    std::uint8_t buf[8];
    std::stringstream ss(codepoint);

    ss >> std::hex >> x;

    if (x <= 0x7FUL) {
        // 0xxxxxxx
        buf[0] = 0x00 | ((x >> 0) & 0x7F);
        buf[1] = '\0';
    } else if (x <= 0x7FFUL) {
        // 110yyyyx 10xxxxxx
        buf[0] = 0xC0 | ((x >> 6) & 0xDF);
        buf[1] = 0x80 | ((x >> 0) & 0xBF);
        buf[2] = '\0';
    } else if (x <= 0xFFFFUL) {
        // 1110yyyy 10yxxxxx 10xxxxxx
        buf[0] = 0xE0 | ((x >> 12) & 0xEF);
        buf[1] = 0x80 | ((x >> 6) & 0xBF);
        buf[2] = 0x80 | ((x >> 0) & 0xBF);
        buf[3] = '\0';
    } else if (x <= 0x10FFFFUL) {
        // 11110yyy 10yyxxxx 10xxxxxx 10xxxxxx
        buf[0] = 0xF0 | ((x >> 18) & 0xF7);
        buf[1] = 0x80 | ((x >> 12) & 0xBF);
        buf[2] = 0x80 | ((x >> 6) & 0xBF);
        buf[3] = 0x80 | ((x >> 0) & 0xBF);
        buf[4] = '\0';
    } else {
        buf[0] = '\0';
    }

    return reinterpret_cast<char*>(buf);
}

// Returns true if |s| is integer.
// [+-]?\d+(_\d+)*
inline bool isInteger(const std::string& s)
{
    if (s.empty())
        return false;

    std::string::size_type p = 0;
    if (s[p] == '+' || s[p] == '-')
        ++p;

    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    return p == s.size();
}

// Returns true if |s| is double.
// [+-]? (\d+(_\d+)*)? (\.\d+(_\d+)*)? ([eE] [+-]? \d+(_\d+)*)?
//       1-----------  2-------------  3----------------------
// 2 or (1 and 3) should exist.
inline bool isDouble(const std::string& s)
{
    if (s.empty())
        return false;

    std::string::size_type p = 0;
    if (s[p] == '+' || s[p] == '-')
        ++p;

    bool ok = false;
    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        ok = true;

        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    if (p < s.size() && s[p] == '.')
        ++p;

    while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
        ++p;
        ok = true;

        if (p < s.size() && s[p] == '_') {
            ++p;
            if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                return false;
        }
    }

    if (!ok)
        return false;

    ok = false;
    if (p < s.size() && (s[p] == 'e' || s[p] == 'E')) {
        ++p;
        if (p < s.size() && (s[p] == '+' || s[p] == '-'))
            ++p;
        while (p < s.size() && '0' <= s[p] && s[p] <= '9') {
            ++p;
            ok = true;

            if (p < s.size() && s[p] == '_') {
                ++p;
                if (!(p < s.size() && '0' <= s[p] && s[p] <= '9'))
                    return false;
            }
        }
        if (!ok)
            return false;
    }

    return p == s.size();
}

// static
inline std::string escapeString(const std::string& s)
{
    std::stringstream ss;
    for (size_t i = 0; i < s.size(); ++i) {
        switch (s[i]) {
        case '\n': ss << "\\n"; break;
        case '\r': ss << "\\r"; break;
        case '\t': ss << "\\t"; break;
        case '\"': ss << "\\\""; break;
        case '\'': ss << "\\\'"; break;
        case '\\': ss << "\\\\"; break;
        default: ss << s[i]; break;
        }
    }

    return ss.str();
}

} // namespace internal

// ----------------------------------------------------------------------
// Lexer

namespace internal {

inline bool Lexer::skipUTF8BOM()
{
    // Check [EF, BB, BF]

    int x1 = is_.peek();
    if (x1 != 0xEF) {
        // When the first byte is not 0xEF, it's not UTF8 BOM.
        // Just return true.
        return true;
    }

    is_.get();
    int x2 = is_.get();
    if (x2 != 0xBB) {
        is_.clear();
        is_.seekg(0);
        return false;
    }

    int x3 = is_.get();
    if (x3 != 0xBF) {
        is_.clear();
        is_.seekg(0);
        return false;
    }

    return true;
}

inline bool Lexer::current(char* c)
{
    int x = is_.peek();
    if (x == EOF)
        return false;
    *c = static_cast<char>(x);
    return true;
}

inline void Lexer::next()
{
    int x = is_.get();
    if (x == '\n') {
        columnNo_ = 0;
        ++lineNo_;
    } else {
        ++columnNo_;
    }
}

inline bool Lexer::consume(char c)
{
    char x;
    if (!current(&x))
        return false;
    if (x != c)
        return false;
    next();
    return true;
}

inline void Lexer::skipUntilNewLine()
{
    char c;
    while (current(&c)) {
        if (c == '\n')
            return;
        next();
    }
}

inline Token Lexer::nextString()
{
    std::string s;
    char c;
    bool dollar = false;

    while (current(&c)) {
        next();
        if (dollar)
        {
            if (c == '{')
                return Token(TokenType::STRING, s);
            else
                s += "$";
        }
        dollar = false;
        if (c == '$') {
            dollar = true;
        }
        if (c == '\\') {
            if (!current(&c))
                return Token(TokenType::ILLEGAL, std::string("string has unknown escape sequence"));
            next();
            switch (c) {
            case 't': c = '\t'; break;
            case 'n': c = '\n'; break;
            case 'r': c = '\r'; break;
            case 'x':
            case 'u':
            case 'U': {
                int size = 0;
                if (c == 'x') {
                    size = 2;
                } else if (c == 'u') {
                    size = 4;
                } else if (c == 'U') {
                    size = 8;
                }
                std::string codepoint;
                for (int i = 0; i < size; ++i) {
                    if (current(&c) && (('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f'))) {
                        codepoint += c;
                        next();
                    } else {
                        return Token(TokenType::ILLEGAL, std::string("string has unknown escape sequence"));
                    }
                }
                s += unescape(codepoint);
                continue;
            }
            case '"': c = '"'; break;
            case '\'': c = '\''; break;
            case '\\': c = '\\'; break;
            case '\n':
                return Token(TokenType::ILLEGAL, std::string("literal not terminated"));
            default:
                return Token(TokenType::ILLEGAL, std::string("string has unknown escape sequence"));
            }
        } else if (c == '\n') {
            return Token(TokenType::ILLEGAL, std::string("found newline while parsing non-HIL string literal"));
        } else if (c == '"') {
            return Token(TokenType::ILLEGAL, std::string("found double quotes while parsing non-HIL string literal"));
        }

        if (!dollar)
            s += c;
    }

    return Token(TokenType::STRING, s);
}

inline bool isValidIdentChar(char c) {
    return isalpha(static_cast<unsigned char>(c)) || isdigit(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == '.' || c == ':' || c == '/';
}

inline Token Lexer::nextValueToken()
{
    std::string s;
    char c;

    if (current(&c) && (isalpha(static_cast<unsigned char>(c)) || c == '_')) {
        s += c;
        next();

        while (current(&c) && isValidIdentChar(c)) {
            s += c;
            next();
        }

        if (s == "true") {
            return Token(TokenType::BOOL, true);
        }
        if (s == "false") {
            return Token(TokenType::BOOL, false);
        }
        return Token(TokenType::IDENT, s);
    }

    return nextNumber(false, false);
}

inline Token Lexer::nextNumber(bool leadingDot, bool leadingSub)
{
    std::string s;
    char c;

    if (leadingDot) {
        s += '.';
    }

    if (leadingSub) {
        s += '-';
    }

    while (current(&c) && (('0' <= c && c <= '9') || c == '.' || c == 'e' || c == 'E' ||
                           c == 'T' || c == 'Z' || c == '_' || c == ':' || c == '-' || c == '+')) {
        next();
        s += c;
    }

    if (isInteger(s)) {
        std::stringstream ss(removeDelimiter(s));
        std::int64_t x;
        ss >> x;
        return Token(TokenType::NUMBER, x);
    }

    if (isDouble(s)) {
        std::stringstream ss(removeDelimiter(s));
        double d;
        ss >> d;
        return Token(TokenType::FLOAT, d);
    }

    return Token(TokenType::ILLEGAL, std::string("Invalid token"));
}


inline bool isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

inline Token Lexer::nextToken(bool isInHil)
{
    char c;
    while (current(&c)) {
        if (!isInHil)
        {
            return nextString();
        }

        if (isInHil && isWhitespace(c)) {
            next();
            continue;
        }

        switch (c) {
        case '{':
            next();
            return Token(TokenType::LBRACE, "{");
        case '}':
            next();
            return Token(TokenType::RBRACE, "}");
        case '(':
            next();
            return Token(TokenType::LPAREN, "(");
        case ')':
            next();
            return Token(TokenType::RPAREN, ")");
        case '[':
            next();
            return Token(TokenType::LBRACK, "[");
        case ']':
            next();
            return Token(TokenType::RBRACK, "]");
        case ',':
            next();
            return Token(TokenType::COMMA, ",");
        case '.':
            next();
            return Token(TokenType::COMMA, ".");
        default:
            return nextValueToken();
        }
    }

    return Token(TokenType::END_OF_FILE);
}

} // namespace internal

inline const char* Value::typeToString(Value::Type type)
{
    switch (type) {
    case NULL_TYPE:   return "null";
    case BOOL_TYPE:   return "bool";
    case INT_TYPE:    return "int";
    case IDENT_TYPE:
        return "string";
    case FUNCTION_TYPE:  return "function call";
    default:          return "unknown";
    }
}

inline Value::Value(const Value& v) :
    type_(v.type_)
{
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case IDENT_TYPE:
        string_ = new std::string(*v.string_);
        break;
    case FUNCTION_TYPE: func_ = new FunctionCall(*v.func_); break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }
}

inline Value::Value(Value&& v) noexcept :
    type_(v.type_)
{
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case IDENT_TYPE:
        string_ = v.string_;
        break;
    case FUNCTION_TYPE: func_ = v.func_; break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    v.type_ = NULL_TYPE;
    v.null_ = nullptr;
}

inline Value& Value::operator=(const Value& v)
{
    if (this == &v)
        return *this;

    this->~Value();

    type_ = v.type_;
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case IDENT_TYPE:
        string_ = new std::string(*v.string_);
        break;
    case FUNCTION_TYPE: func_ = new FunctionCall(*v.func_); break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    return *this;
}

inline Value& Value::operator=(Value&& v) noexcept
{
    if (this == &v)
        return *this;

    this->~Value();

    type_ = v.type_;
    switch (v.type_) {
    case NULL_TYPE: null_ = v.null_; break;
    case BOOL_TYPE: bool_ = v.bool_; break;
    case INT_TYPE: int_ = v.int_; break;
    case IDENT_TYPE:
        string_ = v.string_;
        break;
    case FUNCTION_TYPE: func_ = v.func_; break;
    default:
        assert(false);
        type_ = NULL_TYPE;
        null_ = nullptr;
    }

    v.type_ = NULL_TYPE;
    v.null_ = nullptr;
    return *this;
}

inline Value::~Value()
{
    switch (type_) {
    case IDENT_TYPE:
        delete string_;
        break;
    case FUNCTION_TYPE:
        delete func_;
        break;
    default:
        break;
    }
}

template<> struct Value::ValueConverter<bool>
{
    bool is(const Value& v) { return v.type() == Value::BOOL_TYPE; }
    bool to(const Value& v) { v.assureType<bool>(); return v.bool_; }
};
template<> struct Value::ValueConverter<int64_t>
{
    bool is(const Value& v) { return v.type() == Value::INT_TYPE; }
    int64_t to(const Value& v) { v.assureType<int64_t>(); return v.int_; }
};
template<> struct Value::ValueConverter<int>
{
    bool is(const Value& v) { return v.type() == Value::INT_TYPE; }
    int to(const Value& v) { v.assureType<int>(); return static_cast<int>(v.int_); }
};
template<> struct Value::ValueConverter<std::string>
{
    bool is(const Value& v) { return v.type() == Value::IDENT_TYPE; }
    const std::string& to(const Value& v) { v.assureType<std::string>(); return *v.string_; }
};
template<> struct Value::ValueConverter<FunctionCall>
{
    bool is(const Value& v) { return v.type() == Value::FUNCTION_TYPE; }
    const FunctionCall& to(const Value& v) { v.assureType<FunctionCall>(); return *v.func_; }
};

namespace internal {
template<typename T> inline const char* type_name();
template<> inline const char* type_name<bool>() { return "bool"; }
template<> inline const char* type_name<int>() { return "int"; }
template<> inline const char* type_name<int64_t>() { return "int64_t"; }
template<> inline const char* type_name<std::string>() { return "string"; }
template<> inline const char* type_name<hil::FunctionCall>() { return "function call"; }
} // namespace internal

template<typename T>
inline void Value::assureType() const
{
    if (!is<T>())
        failwith("type error: this value is ", typeToString(type_), " but ", internal::type_name<T>(), " was requested");
}

template<typename T>
inline bool Value::is() const
{
    return ValueConverter<T>().is(*this);
}

template<typename T>
inline typename call_traits<T>::return_type Value::as() const
{
    return ValueConverter<T>().to(*this);
}

// ----------------------------------------------------------------------
// Parser

namespace internal {

inline void Parser::addError(const std::string& reason)
{
    std::stringstream ss;
    ss << "Error:" << lexer_.lineNo() << ":" << lexer_.columnNo() << ": " << reason << "\n";
    errorReason_ += ss.str();
}

inline const std::string& Parser::errorReason()
{
    return errorReason_;
}

inline Context Parser::parse()
{
    Context context;
    std::string text;

    while (true)
    {
        if (!parseText(text))
        {
            if (errorReason().size() > 0)
            {
                context.textParts.clear();
                context.hilParts.clear();
                return context;
            }
            break;
        }

        nextToken(true);
        if (token().type() == TokenType::END_OF_FILE)
            break;

        context.textParts.emplace_back(std::move(text));

        Value v;

        if (!parseHil(v))
        {
            addError("failed to parse HIL");
            break;
        }

        context.hilParts.emplace_back(std::move(v));

        if (token().type() != TokenType::RBRACE)
        {
            addError("expected closing brace");
            break;
        }

        nextToken(false);
    }

    context.textParts.emplace_back(std::move(text));

    return context;
}

inline bool Parser::parseText(std::string& text)
{
    if (token().type() == TokenType::END_OF_FILE)
    {
        return false;
    }
    else if (token().type() == TokenType::STRING)
    {
        text = token().strValue();
        return true;
    }

    addError("could not parse text");
    return true;
}

inline bool Parser::parseHil(Value& currentValue)
{
    switch (token().type())
    {
    case TokenType::RBRACE:
        addError("no value within braces");
        return false;
    case TokenType::IDENT: {
        std::string ident = token().strValue();
        nextToken(true);
        if (token().type() == TokenType::LPAREN)
        {
            if(!parseFunction(currentValue, ident))
                return false;
            else
                return true;
        }
        else if (token().type() == TokenType::RBRACE)
        {
            currentValue = ident;
            return true;
        }
        else
        {
            addError("error parsing ident");
            return false;
        }
    }
    default:
        addError("unsupported value");
        return false;
    }
}

inline bool Parser::parseFunction(Value& currentValue, std::string ident)
{
    FunctionCall func(ident);

    while(true)
    {
        nextToken(true);
        switch(token().type())
        {
        case TokenType::RPAREN:
            currentValue = func;
            nextToken(true);
            return true;
        case TokenType::COMMA:
            break;
        case TokenType::IDENT:
            func.args.emplace_back(std::move(token().strValue()));
            break;
        case TokenType::BOOL:
            func.args.emplace_back(token().boolValue());
            break;
        case TokenType::NUMBER:
            func.args.emplace_back(token().intValue());
            break;
        default:
            addError("error parsing function arguments: " + func.name);
        }
    }

    addError("error parsing function arguments: " + func.name);
    return false;
}

} // namespace internal

} // namespace hil

#endif // MICROHIL_H_
