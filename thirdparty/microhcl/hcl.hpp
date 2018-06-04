#ifndef MICROHCL_H_
#define MICROHCL_H_

#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <string>
#ifdef MICROHCL_USE_MAP
#include <map>
#else
#include <unordered_map>
#endif
#include <vector>

namespace hcl {

class Value;
typedef std::vector<Value> List;

#ifdef MICROHCL_USE_MAP
typedef std::map<std::string, Value> Object;
#else
typedef std::unordered_map<std::string, Value> Object;
#endif

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
template<> struct call_traits<double> : public internal::call_traits_value<double> {};
template<> struct call_traits<std::string> : public internal::call_traits_ref<std::string> {};
template<> struct call_traits<List> : public internal::call_traits_ref<List> {};
template<> struct call_traits<Object> : public internal::call_traits_ref<Object> {};

// A value is returned for std::vector<T>. Not reference.
// This is because a fresh vector is made.
template<typename T> struct call_traits<std::vector<T>> : public internal::call_traits_value<std::vector<T>> {};

class Value {
public:
    enum Type {
        NULL_TYPE,
        BOOL_TYPE,
        INT_TYPE,
        DOUBLE_TYPE,
        STRING_TYPE,
        IDENT_TYPE,
        HIL_TYPE,
        LIST_TYPE,
        OBJECT_TYPE,
    };

    enum StringType {
        Normal,
        Ident,
        Hil,
    };

    Value() : type_(NULL_TYPE), null_(nullptr) {}
    Value(bool v) : type_(BOOL_TYPE), bool_(v) {}
    Value(int v) : type_(INT_TYPE), int_(v) {}
    Value(int64_t v) : type_(INT_TYPE), int_(v) {}
    Value(double v) : type_(DOUBLE_TYPE), double_(v) {}
    Value(const std::string& v) : type_(STRING_TYPE), string_(new std::string(v)) {}
    Value(const char* v) : type_(STRING_TYPE), string_(new std::string(v)) {}
    Value(const List& v) : type_(LIST_TYPE), list_(new List(v)) {}
    Value(const Object& v) : type_(OBJECT_TYPE), object_(new Object(v)) {}
    Value(std::string&& v) : type_(STRING_TYPE), string_(new std::string(std::move(v))) {}
    Value(List&& v) : type_(LIST_TYPE), list_(new List(std::move(v))) {}
    Value(Object&& v) : type_(OBJECT_TYPE), object_(new Object(std::move(v))) {}

    Value(const Value& v);
    Value(Value&& v) noexcept;
    Value& operator=(const Value& v);
    Value& operator=(Value&& v) noexcept;

    // Guards from unexpected Value construction.
    // Someone might use a value like this:
    //   hcl::Value v = x->find("foo");
    // But this is wrong. Without this constructor,
    // value will be unexpectedly initialized with bool.
    Value(const void* v) = delete;
    ~Value();

    // Retruns Value size.
    // 0 for invalid value.
    // The number of inner elements for list or object.
    // 1 for other types.
    size_t size() const;
    bool empty() const;
    Type type() const { return type_; }

    bool valid() const { return type_ != NULL_TYPE; }
    template<typename T> bool is() const;
    template<typename T> typename call_traits<T>::return_type as() const;

    friend bool operator==(const Value& lhs, const Value& rhs);
    friend bool operator!=(const Value& lhs, const Value& rhs) { return !(lhs == rhs); }

    // ----------------------------------------------------------------------
    // For integer/floating value

    // Returns true if the value is int or double.
    bool isNumber() const;
    double asNumber() const;

    // ----------------------------------------------------------------------
    // For String value

    StringType getStringType() const;
    void setStringType(StringType);
    bool isString() const;
    bool isIdent() const;
    bool isHil() const;

    // ----------------------------------------------------------------------
    // For Object value

    template<typename T> typename call_traits<T>::return_type get(const std::string&) const;
    Value* set(const std::string& key, const Value& v);
    // Finds a Value with |key|. |key| can contain '.'
    // Note: if you would like to find a child value only, you need to use findChild.
    const Value* find(const std::string& key) const;
    Value* find(const std::string& key);
    bool has(const std::string& key) const { return find(key) != nullptr; }
    bool erase(const std::string& key);

    Value& operator[](size_t index);
    Value& operator[](const std::string& key);

    // Returns true if two objects share any keys (non-nesting).
    bool sharesKeyWith(const hcl::Value& v) const;

    // Merge object. Returns true if succeeded. Otherwise, |this| might be corrupted.
    // When the same key exists, it will be overwritten.
    bool merge(const Value&);

    // Assigns a value based on a nested list of keys.
    bool mergeObjects(const std::vector<std::string>&, Value&);

    // Finds a value with |key|. It searches only children.
    Value* findChild(const std::string& key);
    const Value* findChild(const std::string& key) const;
    // Sets a value, and returns the pointer to the created value.
    // When the value having the same key exists, it will be overwritten.
    Value* setChild(size_t index, const Value& v);
    Value* setChild(size_t index, Value&& v);
    Value* setChild(const std::string& key, const Value& v);
    Value* setChild(const std::string& key, Value&& v);
    bool eraseChild(const std::string& key);

    // ----------------------------------------------------------------------
    // For List value

    template<typename T> typename call_traits<T>::return_type get(size_t index) const;
    const Value* find(size_t index) const;
    Value* find(size_t index);
    Value* push(const Value& v);
    Value* push(Value&& v);

    // ----------------------------------------------------------------------
    // Others

    // Writer.
    static std::string spaces(int num);
    static std::string escapeKey(const std::string& key);

    void write(std::ostream*, const std::string& keyPrefix = std::string(), int indent = -1) const;

    friend std::ostream& operator<<(std::ostream&, const Value&);

private:
    static const char* typeToString(Type);

    template<typename T> void assureType() const;
    Value* ensureValue(const std::string& key);

    template<typename T> struct ValueConverter;

    Type type_;
    union {
        void* null_; // Can never be legitimately set, indicates parse error
        bool bool_;
        int64_t int_;
        double double_;
        std::string* string_;
        List* list_;
        Object* object_;
    };

    template<typename T> friend struct ValueConverter;
};

// parse() returns ParseResult.
struct ParseResult {
    ParseResult(hcl::Value v, std::string er) :
        value(std::move(v)),
        errorReason(std::move(er)) {}

    bool valid() const { return value.valid(); }

    hcl::Value value;
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
    LBRACE, // {
    COMMA,  // ,
    PERIOD, // .

    RBRACK, // ]
    RBRACE, // }

    ASSIGN, // =
    ADD,    // +
    SUB,    // -
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

    Token nextToken();

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

    Token nextStringDoubleQuote();
    Token nextStringSingleQuote();
    Token nextHereDoc();

    std::istream& is_;
    int lineNo_;
    int columnNo_;
};

class Parser {
public:
    explicit Parser(std::istream& is) : lexer_(is), token_(TokenType::ILLEGAL)
    {
        if (!lexer_.skipUTF8BOM()) {
            token_ = Token(TokenType::ILLEGAL, std::string("Invalid UTF8 BOM"));
        } else {
            nextToken();
        }
    }

    // Parses. If failed, value should be invalid value.
    // You can get the error by calling errorReason().
    Value parse();
    const std::string& errorReason();

private:
    const Token& token() const { return token_; }
    void nextToken() { token_ = lexer_.nextToken(); }
    bool consume(char c) { return lexer_.consume(c); }
    int columnNo() { return lexer_.columnNo(); }

    void skipForKey();
    void skipForValue();

    bool consumeForKey(TokenType);
    bool consumeForValue(TokenType);
    bool consumeEOLorEOFForKey();

    Value parseObjectList(bool);
    bool parseKeys(std::vector<std::string>&);
    bool parseObjectItem(Value&);
    bool parseObject(Value&);
    bool parseObjectType(Value&);
    bool parseListType(Value&);
    bool parseLiteralType(Value&);

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
        return ParseResult(hcl::Value(), "stream is in bad state. file does not exist?");
    }

    internal::Parser parser(is);
    hcl::Value v = parser.parse();

    if (v.valid())
        return ParseResult(std::move(v), std::string());

    return ParseResult(std::move(v), std::move(parser.errorReason()));
}

inline ParseResult parseFile(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs) {
        return ParseResult(hcl::Value(),
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
        return false;
    }

    int x3 = is_.get();
    if (x3 != 0xBF) {
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

inline Token Lexer::nextStringDoubleQuote()
{
    if (!consume('"'))
        return Token(TokenType::ILLEGAL, std::string("string didn't start with '\"'"));

    std::string s;
    char c;
    int braces = 0;
    bool dollar = false;
    bool hil = false;

    while (current(&c)) {
        next();
        if (braces == 0 && dollar && c == '{') {
            braces++;
            hil = true;
        } else if (braces > 0 && c == '{') {
            braces++;
        }
        if (braces > 0 && c == '}') {
            braces--;
        }
        dollar = false;
        if (braces == 0 && c == '$') {
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
                if (braces == 0) {
                    return Token(TokenType::ILLEGAL, std::string("literal not terminated"));
                } else {
                    while (current(&c) && (c == ' ' || c == '\t' || c == '\r' || c == '\n')) {
                        next();
                    }
                }
                continue;
            default:
                return Token(TokenType::ILLEGAL, std::string("string has unknown escape sequence"));
            }
        } else if (c == '\n' && braces == 0) {
            return Token(TokenType::ILLEGAL, std::string("found newline while parsing non-HIL string literal"));
        } else if (c == '"' && braces == 0) {
            if (hil)
                return Token(TokenType::HIL, s);
            else
                return Token(TokenType::STRING, s);
        }

        s += c;
    }

    return Token(TokenType::ILLEGAL, std::string("string didn't end"));
}

inline Token Lexer::nextStringSingleQuote()
{
    if (!consume('\''))
        return Token(TokenType::ILLEGAL, std::string("string didn't start with '\''?"));

    std::string s;
    char c;

    if (current(&c) && c == '\'') {
        // OK. It's empty string.
        next();
        return Token(TokenType::STRING, std::string());
    }

    while (current(&c)) {
        next();
        if (c == '\'') {
            return Token(TokenType::STRING, s);
        } else if (c == '\n') {
            return Token(TokenType::ILLEGAL, std::string("found newline while parsing string literal"));
        }

        s += c;
    }

    return Token(TokenType::ILLEGAL, std::string("string didn't end with '\''?"));
}

inline bool hasSuffix(const std::string & s, const std::string & suffix) {
    if(suffix.size() > s.size()) {
        return false;
    }
    return std::mismatch(suffix.rbegin(),suffix.rend(),s.rbegin()).first == suffix.rend();
}

inline Token Lexer::nextHereDoc()
{
    if (!consume('<'))
        return Token(TokenType::ILLEGAL, std::string("heredoc didn't start with '<<'?"));
    if (!consume('<'))
        return Token(TokenType::ILLEGAL, std::string("heredoc didn't start with '<<'?"));

    std::string s("<<");
    std::string anchor;
    char c;

    current(&c);

    // Indented heredoc syntax
    if(c == '-') {
        s += c;
        next();
    }

    while (current(&c) && (isalpha(static_cast<unsigned char>(c)) || isdigit(static_cast<unsigned char>(c)))) {
        anchor += c;
        next();
    }

    if (anchor.size() == 0) {
        return Token(TokenType::ILLEGAL, std::string("heredoc anchor was empty"));
    }

    s += anchor;

    if(!current(&c)) {
        return Token(TokenType::ILLEGAL, std::string("end of file reached"));
    }

    if(current(&c) && c == '\r') {
        skipUntilNewLine();
    }

    if(!current(&c) || (current(&c) && c != '\n')) {
        return Token(TokenType::ILLEGAL, std::string("invalid characters in heredoc anchor"));
    }

    s += '\n';

    if(s.size() == 0) {
        return Token(TokenType::ILLEGAL, std::string("zero-length heredoc anchor"));
    }

    std::string buffer;
    std::string line;
    std::string indentLine;

    while(current(&c)) {
        next();
        if (current(&c) && c == '\n') {
            if (buffer.size() != 0) {
                buffer += '\n';
            }
            buffer += indentLine;
            buffer += line;
            indentLine.clear();
            line.clear();
        }
        else if (current(&c) && line.size() == 0 && (c == ' ' || c == '\t')) {
            indentLine += c;
        } else if(current(&c)) {
            line += c;
        }
        if (line.compare(anchor) == 0) {
            buffer += '\n';
            buffer += indentLine;
            buffer += line;
            buffer += '\n';
            break;
        }
    }

    s += buffer;

    if(current(&c)) {
        next();
    }
    return Token(TokenType::HEREDOC, s);
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

inline Token Lexer::nextToken()
{
    char c;
    while (current(&c)) {
        if (isWhitespace(c)) {
            next();
            continue;
        }

        if (c == '#') {
            skipUntilNewLine();
            continue;
        }

        switch (c) {
        case '=':
            next();
            return Token(TokenType::ASSIGN, "=");
        case '+':
            next();
            return Token(TokenType::ADD, "+");
        case '-':
            next();
            if (current(&c) && isdigit(static_cast<unsigned char>(c))) {
                return nextNumber(false, true);
            }
            else {
                return Token(TokenType::SUB, "-");
            }
        case '{':
            next();
            return Token(TokenType::LBRACE, "{");
        case '}':
            next();
            return Token(TokenType::RBRACE, "}");
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
            if(current(&c) && isdigit(static_cast<unsigned char>(c))) {
                return nextNumber(true, false);
            }
            else {
                return Token(TokenType::PERIOD, ".");
            }
        case '\"':
            return nextStringDoubleQuote();
        case '\'':
            return nextStringSingleQuote();
        case '<':
            return nextHereDoc();
        case '/':
            next();
            if(current(&c) && c == '/') {
                skipUntilNewLine();
                continue;
            }
            return Token(TokenType::ILLEGAL, "unterminated comment");
        default:
            return nextValueToken();
        }
    }

    return Token(TokenType::END_OF_FILE);
}

} // namespace internal

// static
inline const char* Value::typeToString(Value::Type type)
{
    switch (type) {
    case NULL_TYPE:   return "null";
    case BOOL_TYPE:   return "bool";
    case INT_TYPE:    return "int";
    case DOUBLE_TYPE: return "double";
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        return "string";
    case LIST_TYPE:  return "list";
    case OBJECT_TYPE:  return "object";
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
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        string_ = new std::string(*v.string_);
        break;
    case LIST_TYPE: list_ = new List(*v.list_); break;
    case OBJECT_TYPE: object_ = new Object(*v.object_); break;
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
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        string_ = v.string_;
        break;
    case LIST_TYPE: list_ = v.list_; break;
    case OBJECT_TYPE: object_ = v.object_; break;
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
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        string_ = new std::string(*v.string_);
        break;
    case LIST_TYPE: list_ = new List(*v.list_); break;
    case OBJECT_TYPE: object_ = new Object(*v.object_); break;
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
    case DOUBLE_TYPE: double_ = v.double_; break;
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        string_ = v.string_;
        break;
    case LIST_TYPE: list_ = v.list_; break;
    case OBJECT_TYPE: object_ = v.object_; break;
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
    case STRING_TYPE:
    case IDENT_TYPE:
    case HIL_TYPE:
        delete string_;
        break;
    case LIST_TYPE:
        delete list_;
        break;
    case OBJECT_TYPE:
        delete object_;
        break;
    default:
        break;
    }
}

inline size_t Value::size() const
{
    switch (type_) {
    case NULL_TYPE:
        return 0;
    case LIST_TYPE:
        return list_->size();
    case OBJECT_TYPE:
        return object_->size();
    default:
        return 1;
    }
}

inline bool Value::empty() const
{
    return size() == 0;
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
template<> struct Value::ValueConverter<double>
{
    bool is(const Value& v) { return v.type() == Value::DOUBLE_TYPE; }
    double to(const Value& v) { v.assureType<double>(); return v.double_; }
};
template<> struct Value::ValueConverter<std::string>
{
    bool is(const Value& v) { return v.isString(); }
    const std::string& to(const Value& v) { v.assureType<std::string>(); return *v.string_; }
};
template<> struct Value::ValueConverter<List>
{
    bool is(const Value& v) { return v.type() == Value::LIST_TYPE; }
    const List& to(const Value& v) { v.assureType<List>(); return *v.list_; }
};
template<> struct Value::ValueConverter<Object>
{
    bool is(const Value& v) { return v.type() == Value::OBJECT_TYPE; }
    const Object& to(const Value& v) { v.assureType<Object>(); return *v.object_; }
};

template<typename T>
struct Value::ValueConverter<std::vector<T>>
{
    bool is(const Value& v)
    {
        if (v.type() != Value::LIST_TYPE)
            return false;
        const List& list = v.as<List>();
        if (list.empty())
            return true;
        return list.front().is<T>();
    }

    std::vector<T> to(const Value& v)
    {
        const List& list = v.as<List>();
        if (list.empty())
            return std::vector<T>();
        list.front().assureType<T>();

        std::vector<T> result;
        for (const auto& element : list) {
            result.push_back(element.as<T>());
        }

        return result;
    }
};

namespace internal {
template<typename T> inline const char* type_name();
template<> inline const char* type_name<bool>() { return "bool"; }
template<> inline const char* type_name<int>() { return "int"; }
template<> inline const char* type_name<int64_t>() { return "int64_t"; }
template<> inline const char* type_name<double>() { return "double"; }
template<> inline const char* type_name<std::string>() { return "string"; }
template<> inline const char* type_name<hcl::List>() { return "list"; }
template<> inline const char* type_name<hcl::Object>() { return "object"; }
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

inline bool Value::isNumber() const
{
    return is<int>() || is<double>();
}

inline double Value::asNumber() const
{
    if (is<int>())
        return as<int>();
    if (is<double>())
        return as<double>();

    failwith("type error: this value is ", typeToString(type_), " but number is requested");
}

inline Value::StringType Value::getStringType() const
{
    if (!is<std::string>())
        failwith("type must be string to use setStringType(type).");

    switch (type_) {
    case STRING_TYPE:
        return StringType::Normal;
    case IDENT_TYPE:
        return StringType::Ident;
    case HIL_TYPE:
        return StringType::Hil;
    default:
        assert(0);
        return StringType::Normal;
    }
}

inline void Value::setStringType(StringType type)
{
    if (!is<std::string>())
        failwith("type must be string to use setStringType(type).");

    switch (type) {
    case StringType::Normal:
        type_ = STRING_TYPE;
        break;
    case StringType::Ident:
        type_ = IDENT_TYPE;
        break;
    case StringType::Hil:
        type_ = HIL_TYPE;
        break;
    default:
        assert(0);
    }
}

inline bool Value::isString() const
{
    return type_ == STRING_TYPE || type_ == IDENT_TYPE || type_ == HIL_TYPE;
}

inline bool Value::isIdent() const
{
    return getStringType() == StringType::Ident;
}

inline bool Value::isHil() const
{
    return getStringType() == StringType::Hil;
}

// static
inline bool operator==(const Value& lhs, const Value& rhs)
{
    if (lhs.type() != rhs.type()) {
        if (!lhs.isString() && !rhs.isString()) {
            return false;
        }
    }

    switch (lhs.type()) {
    case Value::Type::NULL_TYPE:
        return true;
    case Value::Type::BOOL_TYPE:
        return lhs.bool_ == rhs.bool_;
    case Value::Type::INT_TYPE:
        return lhs.int_ == rhs.int_;
    case Value::Type::DOUBLE_TYPE:
        return lhs.double_ == rhs.double_;
    case Value::Type::STRING_TYPE:
    case Value::Type::IDENT_TYPE:
    case Value::Type::HIL_TYPE:
        return *lhs.string_ == *rhs.string_;
    case Value::Type::LIST_TYPE:
        return *lhs.list_ == *rhs.list_;
    case Value::Type::OBJECT_TYPE:
        return *lhs.object_ == *rhs.object_;
    default:
        failwith("unknown type");
    }
}

// static
inline std::ostream& operator<<(std::ostream& os, const hcl::Value& v)
{
    v.write(&os);
    return os;
}

inline std::string Value::spaces(int num)
{
    if (num <= 0)
        return std::string();

    return std::string(num, ' ');
}

inline std::string Value::escapeKey(const std::string& key)
{
    auto position = std::find_if(key.begin(), key.end(), [](char c) -> bool {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-')
            return false;
        return true;
    });

    if (position != key.end()) {
        std::string escaped = "\"";
        for (const char& c : key) {
            if (c == '\\' || c  == '"')
                escaped += '\\';
            escaped += c;
        }
        escaped += "\"";

        return escaped;
    }

    return key;
}

inline void Value::write(std::ostream* os, const std::string& keyPrefix, int indent) const
{
    switch (type_) {
    case NULL_TYPE:
        failwith("null type value is not a valid value");
        break;
    case BOOL_TYPE:
        (*os) << (bool_ ? "true" : "false");
        break;
    case INT_TYPE:
        (*os) << int_;
        break;
    case DOUBLE_TYPE: {
        (*os) << std::fixed << std::showpoint << double_;
        break;
    }
    case STRING_TYPE:
    case HIL_TYPE:
        (*os) << '"' << internal::escapeString(*string_) << '"';
        break;
    case IDENT_TYPE:
        (*os) << internal::escapeString(*string_);
        break;
    case LIST_TYPE:
        (*os) << '[';
        for (size_t i = 0; i < list_->size(); ++i) {
            if (i)
                (*os) << ", ";
            (*list_)[i].write(os, keyPrefix, -1);
        }
        (*os) << ']';
        break;
    case OBJECT_TYPE:
        for (const auto& kv : *object_) {
            if (kv.second.is<Object>())
                continue;
            if (kv.second.is<List>() && kv.second.size() > 0 && kv.second.find(0)->is<Object>())
                continue;
            (*os) << spaces(indent) << escapeKey(kv.first) << " = ";
            kv.second.write(os, keyPrefix, indent + 4);
            (*os) << '\n';
        }
        for (const auto& kv : *object_) {
            if (kv.second.is<Object>()) {
                std::string key;

                key += escapeKey(kv.first);
                (*os) << spaces(indent) << key << " {\n";
                kv.second.write(os, key, indent + 4);
                (*os) << spaces(indent) << "}\n";
            }
            if (kv.second.is<List>() && kv.second.size() > 0 && kv.second.find(0)->is<Object>()) {
                std::string key;

                key += escapeKey(kv.first);
                (*os) << spaces(indent) << key << " = [";
                for (const auto& v : kv.second.as<List>()) {
                    if(v.is<Object>())
                        (*os) << "\n" << spaces(indent + 4) << "{";
                    else
                        (*os) << spaces(indent);
                    v.write(os, key, indent + 4);
                    if(v.is<Object>())
                        (*os) << "},\n";
                }
                (*os) << spaces(indent) << "]\n";
            }
        }
        break;
    default:
        failwith("writing unknown type");
        break;
    }
}

template<typename T>
inline typename call_traits<T>::return_type Value::get(const std::string& key) const
{
    if (!is<Object>())
        failwith("type must be object to do get(key).");

    const Value* obj = find(key);
    if (!obj)
        failwith("key ", key, " was not found.");

    return obj->as<T>();
}

inline const Value* Value::find(const std::string& key) const
{
    if (!is<Object>())
        return nullptr;

    std::istringstream ss(key);
    internal::Lexer lexer(ss);

    const Value* current = this;
    while (true) {
        internal::Token t = lexer.nextToken();
        if (!(t.type() == internal::TokenType::IDENT || t.type() == internal::TokenType::STRING))
            return nullptr;

        std::string part = t.strValue();
        t = lexer.nextToken();
        //if (t.type() == internal::TokenType::PERIOD) {
        //    current = current->findChild(part);
        //    if (!current || !current->is<Object>())
        //        return nullptr;
        //} else
        if (t.type() == internal::TokenType::END_OF_FILE) {
            return current->findChild(part);
        } else {
            return nullptr;
        }
    }
}

inline Value* Value::find(const std::string& key)
{
    return const_cast<Value*>(const_cast<const Value*>(this)->find(key));
}

inline bool Value::sharesKeyWith(const hcl::Value& v) const
{
    if (this == &v)
        return true;
    if (!is<Object>() || !v.is<Object>())
        return false;

    for (const auto& kv : *v.object_) {
        if (find(kv.first)) {
            return true;
        }
    }

    return false;
}

inline bool Value::merge(const hcl::Value& v)
{
    if (this == &v)
        return true;
    if (!is<Object>() || !v.is<Object>())
        return false;

    for (const auto& kv : *v.object_) {
        if (Value* tmp = find(kv.first)) {
            // If both are object, we merge them.
            if (tmp->is<Object>() && kv.second.is<Object>()) {
                if (!tmp->merge(kv.second))
                    return false;
            } else {
                setChild(kv.first, kv.second);
            }
        } else {
            setChild(kv.first, kv.second);
        }
    }

    return true;
}

inline bool Value::mergeObjects(const std::vector<std::string>& keys, Value& added)
{
    if(keys.size() == 0) {
        return false;
    }

    Value& nestedValue = added;
    if (keys.size() > 1) {
        Value parent((Object()));
        Value* ptr = &parent;
        std::vector<std::string> allButFirst(keys.begin() + 1, keys.end());
        for (auto key = allButFirst.begin(); key < allButFirst.end(); key++) {
            if ((key != allButFirst.end()) && (key + 1 == allButFirst.end())) {
                ptr->set(*key, nestedValue);
            } else {
                ptr = ptr->set(*key, Object());
            }
        }
        nestedValue = parent;
    }
    Value* existing = find(keys.front());
    bool expand = false;
    if(existing)  {
        if (existing->is<List>()) {
            // This is an object list. Add the object.
            existing->push(std::move(added));
        } else {
            // We tried assigning to a value that exists already.
            // First, attempt to see if this is an object.
            if (existing->is<Object>()) {
                if (!added.is<Object>()) {
                    // We tried assigning a non-object to an existing object.
                    // Expand it into a list.
                    expand = true;
                } else {
                    // If the objects share any keys (not nested),
                    // expand into a list. Else, merge the two
                    // objects.
                    if (existing->sharesKeyWith(added)) {
                        expand = true;
                    } else {
                        existing->merge(added);
                    }
                }
            } else {
                // We tried assigning something to a non-object.
                // Expand it into a list.
                expand = true;
            }
            // Upgrade it to a list.
            if(expand)
            {
                Value l((List()));
                l.push(*existing);
                l.push(std::move(added));
                set(keys.front(), l);
            }
        }
    } else {
        set(keys.front(), added);
    }

    return true;
}

inline Value* Value::set(const std::string& key, const Value& v)
{
    Value* result = ensureValue(key);
    *result = v;
    return result;
}

inline Value* Value::setChild(size_t index, const Value& v)
{
    if (!valid())
        *this = Value((List()));

    if (!is<List>())
        failwith("type must be list to do set(key, v).");

    (*list_)[index] = v;
    return &(*list_)[index];
}

inline Value* Value::setChild(size_t index, Value&& v)
{
    if (!valid())
        *this = Value((List()));

    if (!is<List>())
        failwith("type must be object to do set(key, v).");

    (*list_)[index] = std::move(v);
    return &(*list_)[index];
}

inline Value* Value::setChild(const std::string& key, const Value& v)
{
    if (!valid())
        *this = Value((Object()));

    if (!is<Object>())
        failwith("type must be object to do set(key, v).");

    (*object_)[key] = v;
    return &(*object_)[key];
}

inline Value* Value::setChild(const std::string& key, Value&& v)
{
    if (!valid())
        *this = Value((Object()));

    if (!is<Object>())
        failwith("type must be object to do set(key, v).");

    (*object_)[key] = std::move(v);
    return &(*object_)[key];
}

inline bool Value::erase(const std::string& key)
{
    if (!is<Object>())
        return false;

    std::istringstream ss(key);
    internal::Lexer lexer(ss);

    Value* current = this;
    while (true) {
        internal::Token t = lexer.nextToken();
        if (!(t.type() == internal::TokenType::IDENT || t.type() == internal::TokenType::STRING))
            return false;

        std::string part = t.strValue();
        t = lexer.nextToken();
        if (t.type() == internal::TokenType::PERIOD) {
            current = current->findChild(part);
            if (!current || !current->is<Object>())
                return false;
        } else if (t.type() == internal::TokenType::END_OF_FILE) {
            return current->eraseChild(part);
        } else {
            return false;
        }
    }
}

inline bool Value::eraseChild(const std::string& key)
{
    if (!is<Object>())
        failwith("type must be object to do erase(key).");

    return object_->erase(key) > 0;
}

inline Value& Value::operator[](size_t index)
{
    if (!valid())
        *this = Value((List()));

    if (!is<List>())
        failwith("type must be list to index by int");

    if (list_->size() <= index)
        failwith("index out of bound");

    if (Value* v = find(index))
        return *v;

    return *setChild(index, Value());
}

inline Value& Value::operator[](const std::string& key)
{
    if (!valid())
        *this = Value((Object()));

    if (Value* v = findChild(key))
        return *v;

    return *setChild(key, Value());
}

template<typename T>
inline typename call_traits<T>::return_type Value::get(size_t index) const
{
    if (!is<List>())
        failwith("type must be list to do get(index).");

    if (list_->size() <= index)
        failwith("index out of bound");

    return (*list_)[index].as<T>();
}

inline const Value* Value::find(size_t index) const
{
    if (!is<List>())
        return nullptr;
    if (index < list_->size())
        return &(*list_)[index];
    return nullptr;
}

inline Value* Value::find(size_t index)
{
    return const_cast<Value*>(const_cast<const Value*>(this)->find(index));
}

inline Value* Value::push(const Value& v)
{
    if (!valid())
        *this = Value((List()));
    else if (!is<List>())
        failwith("type must be list to do push(Value).");

    list_->push_back(v);
    return &list_->back();
}

inline Value* Value::push(Value&& v)
{
    if (!valid())
        *this = Value((List()));
    else if (!is<List>())
        failwith("type must be list to do push(Value).");

    list_->push_back(std::move(v));
    return &list_->back();
}

inline Value* Value::ensureValue(const std::string& key)
{
    if (!valid())
        *this = Value((Object()));
    if (!is<Object>()) {
        failwith("encountered non object value");
    }

    std::istringstream ss(key);
    internal::Lexer lexer(ss);

    Value* current = this;
    while (true) {
        internal::Token t = lexer.nextToken();
        if (key.size() > 0 && !(t.type() == internal::TokenType::IDENT || t.type() == internal::TokenType::STRING)) {
            failwith("invalid key first: " + t.strValue() + " ");
        }

        std::string part = t.strValue();

        if (key.size() == 0)
            part = "";

        t = lexer.nextToken();
        if (t.type() == internal::TokenType::PERIOD) {
            if (Value* candidate = current->findChild(part)) {
                if (!candidate->is<Object>())
                    failwith("encountered non object value");

                current = candidate;
            } else {
                current = current->setChild(part, Object());
            }
        } else if (t.type() == internal::TokenType::END_OF_FILE) {
            if (Value* v = current->findChild(part))
                return v;
            return current->setChild(part, Value());
        } else {
            failwith("invalid key second: " + t.strValue() + " ");
        }
    }
}

inline Value* Value::findChild(const std::string& key)
{
    if(!is<Object>())
        failwith("cannot use findChild on non-object");

    auto it = object_->find(key);
    if (it == object_->end())
        return nullptr;

    return &it->second;
}

inline const Value* Value::findChild(const std::string& key) const
{
    if(!is<Object>())
        failwith("cannot use findChild on non-object");

    auto it = object_->find(key);
    if (it == object_->end())
        return nullptr;

    return &it->second;
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

inline Value Parser::parse()
{
    return parseObjectList(false);
}

inline Value Parser::parseObjectList(bool isNested)
{
    Value node((Object()));

    while (true) {
        if (token().type() == TokenType::END_OF_FILE) {
            break;
        }
        if (isNested) {
            // We're inside a nested object list, so end at an RBRACE.
            if (token().type() == TokenType::RBRACE) {
                break;
            }
        }

        std::vector<std::string> keys;
        if (!parseKeys(keys)) {
            // Make the node invalid
            node = Value();
            break;
        }

        Value v;
        if (!parseObjectItem(v)) {
            // Make the node invalid
            node = Value();
            break;
        }

        nextToken();

        // object lists can be optionally comma-delimited e.g. when a list of maps
        // is being expressed, so a comma is allowed here - it's simply consumed
        if(token().type() == TokenType::COMMA)
            nextToken();

        node.mergeObjects(keys, v);
    }

    return node;
}

inline bool Parser::parseKeys(std::vector<std::string>& keys)
{
    int keyCount = 0;
    keys.clear();

    while (true) {
        switch (token().type()) {
        case TokenType::END_OF_FILE:
            addError("end of file reached");
            return false;
        case TokenType::ASSIGN:
            if (keyCount > 1) {
                addError("nested object expected: LBRACE got: " + token().strValue());
                return false;
            }
            if (keyCount == 0) {
                addError("expected to find at least one object key");
                return false;
            }

            return true;
        case TokenType::LBRACE:
            if (keys.size() == 0) {
                addError("expected IDENT | STRING got: LBRACE");
                return false;
            }

            return true;
        case TokenType::IDENT:
        case TokenType::STRING:
            keyCount++;
            keys.push_back(token().strValue());
            nextToken();
            break;
        case TokenType::ILLEGAL:
            addError("illegal character");
            return false;
        default:
            addError("expected IDENT | STRING | ASSIGN | LBRACE got: " + token().strValue());
            return false;
        }
    }

    return false;
}

inline bool Parser::parseObjectItem(Value& currentValue)
{
    switch (token().type()) {
    case TokenType::ASSIGN:
        if (!parseObject(currentValue))
            return false;
        break;
    case TokenType::LBRACE:
        if (!parseObjectType(currentValue))
            return false;
        break;
    default:
        addError("Expected start of object ('{') or assignment ('=')");
        return false;
    }
    return true;
}

inline bool Parser::parseObject(Value& currentValue)
{
    nextToken();

    switch (token().type()) {
    case TokenType::NUMBER:
    case TokenType::FLOAT:
    case TokenType::BOOL:
    case TokenType::STRING:
    case TokenType::HEREDOC:
    case TokenType::IDENT:
    case TokenType::HIL:
        return parseLiteralType(currentValue);
    case TokenType::LBRACE:
        return parseObjectType(currentValue);
    case TokenType::LBRACK:
        return parseListType(currentValue);
    case TokenType::COMMENT:
        break;
    case TokenType::END_OF_FILE:
        addError("Reached end of file");
        return false;
    default:
        addError("Unknown token: " + token().strValue());
        return false;
    }
    addError("Unknown token: " + token().strValue());
    return false;
}

inline bool Parser::parseObjectType(Value& currentValue)
{
    if(token().type() != TokenType::LBRACE) {
        addError("object list did not start with LBRACE");
        return false;
    }
    nextToken();
    Value result = parseObjectList(true);

    if(!errorReason().empty()) {
        addError("failed parsing object list");
        return false;
    }

    if(token().type() != TokenType::RBRACE) {
        addError("object expected closing RBRACE got: " + token().strValue());
        return false;
    }

    currentValue = result;
    return true;
}

inline bool Parser::parseListType(Value& currentValue)
{
    List a;
    bool needComma = false;

    while (true) {
        nextToken();

        if (needComma) {
            switch (token().type()) {
            case TokenType::COMMA:
            case TokenType::RBRACK:
                break;
            default:
                addError("error parsing list, expected comma or list end, got: " + token().strValue());
                return false;
            }
        }

        switch (token().type()) {
        case TokenType::BOOL:
        case TokenType::NUMBER:
        case TokenType::FLOAT:
        case TokenType::STRING:
        case TokenType::HEREDOC:
        case TokenType::IDENT:
        case TokenType::HIL:
        {
            Value literal;
            if (!parseLiteralType(literal)) {
                addError("error parsing literal type");
                return false;
            }

            a.push_back(std::move(literal));
            needComma = true;
            break;
        }
        case TokenType::COMMA:
            needComma = false;
            continue;
        case TokenType::LBRACE:
        {
            Value object;
            if (!parseObjectType(object)) {
                addError("error parsing object within list");
                return false;
            }
            a.push_back(std::move(object));
            needComma = true;
            break;
        }
        case TokenType::LBRACK:
        {
            Value list;
            if (!parseListType(list)) {
                addError("error parsing list within list");
                return false;
            }
            a.push_back(std::move(list));
            break;
        }
        case TokenType::RBRACK:
        {
            currentValue = a;
            return true;
        }
        default:
            addError("unexpected token while parsing list: " + token().strValue());
            return false;
        }
    }
    return false;
}

inline bool Parser::parseLiteralType(Value& currentValue)
{
    switch (token().type()) {
    case TokenType::HEREDOC: {
        std::string unindented;
        if (!unindentHeredoc(token().strValue(), unindented)) {
            addError("Failed unindenting heredoc: " + token().strValue());
            return false;
        }
        currentValue = unindented;
        return true;
    }
    case TokenType::STRING:
    case TokenType::IDENT:
    case TokenType::HIL:
        currentValue = token().strValue();

        if (token().type() == TokenType::HIL)
            currentValue.setStringType(Value::StringType::Hil);
        else if (token().type() == TokenType::IDENT)
            currentValue.setStringType(Value::StringType::Ident);

        return true;
    case TokenType::BOOL:
        currentValue = token().boolValue();
        return true;
    case TokenType::NUMBER:
        currentValue = token().intValue();
        return true;
    case TokenType::FLOAT:
        currentValue = token().doubleValue();
        return true;
    case TokenType::ILLEGAL:
        addError(token().strValue());
        return false;
    default:
        addError("unexpected token");
        return false;
    }
}

static inline int isSpace(int c)
{
    return (c == ' ' || c == '\t') ? 1 : 0;
}

static inline std::string trimRight(const std::string& s) {
  std::string r(s);
  r.erase(std::find_if(r.rbegin(), r.rend(),
                       std::not1(std::function<int(int)>(isSpace))
              ).base(), r.end());
  return r;
}

static inline std::string join(const std::vector<std::string>& elements, const char* const separator)
{
    switch (elements.size())
    {
        case 0:
            return "";
        case 1:
            return elements[0];
        default:
            std::ostringstream os;
            std::copy(elements.begin(), elements.end()-1, std::ostream_iterator<std::string>(os, separator));
            os << *elements.rbegin();
            return os.str();
    }
}
static inline bool hasPrefix(const std::string & s, const std::string & prefix) {
	return std::mismatch(prefix.begin(), prefix.end(), s.begin()).first == prefix.end();
}

inline std::string & trimPrefix(std::string & s, const std::string & prefix) {
	if (!hasPrefix(s,prefix)) {
		return s;
	}
	s.erase(0,prefix.size());
	return s;
}

inline bool Parser::unindentHeredoc(const std::string& heredoc, std::string& out)
{
    auto index = heredoc.find("\n");
    size_t contentBegin = index + 1;
    size_t contentEnd = heredoc.size() - contentBegin - (index - 2);
    std::string content = heredoc.substr(contentBegin, contentEnd);

    if (index == std::string::npos) {
        addError("heredoc doesn't contain newline");
        return false;
    }

    bool unindent = heredoc[2] == '-';

    if (!unindent) {
        out = heredoc.substr(contentBegin, contentEnd - 1);
        return true;
    }

    std::vector<std::string> lines;
    std::istringstream ss(content);
    std::string line;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }

    std::string whitespacePrefix = lines[lines.size() - 1];

    bool isIndented = true;
    for (const auto& line : lines) {
        if(whitespacePrefix.size() > line.size()) {
            isIndented = false;
            break;
        }

        auto res = std::mismatch(whitespacePrefix.begin(), whitespacePrefix.end(), line.begin());

        if (res.first == whitespacePrefix.end()) {
            continue;
        }

        isIndented = false;
        break;
    }

    if (!isIndented) {
        out = trimRight(heredoc.substr(contentBegin, contentEnd));
        return true;
    }

    std::vector<std::string> unindentedLines;
    for (auto line = lines.begin(); line < lines.end(); line++) {
        if (line + 1 == lines.end()) {
            unindentedLines.push_back(std::string());
            break;
        }
        trimPrefix(*line, whitespacePrefix);
        unindentedLines.push_back(std::move(*line));
    }

    out = join(unindentedLines, "\n");
    return true;
}

} // namespace internal

} // namespace hcl

#endif // MICROHCL_H_
