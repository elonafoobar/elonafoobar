#include <unordered_map>
#include "../../snail/input.hpp"
#include "../../util/strutil.hpp"
#include "../optional.hpp"

namespace elona
{

namespace
{
using namespace snail;

struct KeyName
{
    KeyName(std::string normal)
        : normal(normal)
    {
    }
    KeyName(std::string normal, std::string shift)
        : normal(normal)
        , shift(shift)
    {
    }

    std::string normal;
    optional<std::string> shift;
};

// clang-format off
// Keys not in this map should not be bound.
static std::unordered_map<snail::Key, KeyName> key_names = {
    {Key::key_0,            {"0"}},
    {Key::key_1,            {"1"}},
    {Key::key_2,            {"2"}},
    {Key::key_3,            {"3"}},
    {Key::key_4,            {"4"}},
    {Key::key_5,            {"5"}},
    {Key::key_6,            {"6"}},
    {Key::key_7,            {"7"}},
    {Key::key_8,            {"8"}},
    {Key::key_9,            {"9"}},

    {Key::key_a,            {"a", "A"}},
    {Key::key_b,            {"b", "B"}},
    {Key::key_c,            {"c", "C"}},
    {Key::key_d,            {"d", "D"}},
    {Key::key_e,            {"e", "E"}},
    {Key::key_f,            {"f", "F"}},
    {Key::key_g,            {"g", "G"}},
    {Key::key_h,            {"h", "H"}},
    {Key::key_i,            {"i", "I"}},
    {Key::key_j,            {"j", "J"}},
    {Key::key_k,            {"k", "K"}},
    {Key::key_l,            {"l", "L"}},
    {Key::key_m,            {"m", "M"}},
    {Key::key_n,            {"n", "N"}},
    {Key::key_o,            {"o", "O"}},
    {Key::key_p,            {"p", "P"}},
    {Key::key_q,            {"q", "Q"}},
    {Key::key_r,            {"r", "R"}},
    {Key::key_s,            {"s", "S"}},
    {Key::key_t,            {"t", "T"}},
    {Key::key_u,            {"u", "U"}},
    {Key::key_v,            {"v", "V"}},
    {Key::key_w,            {"w", "W"}},
    {Key::key_x,            {"x", "X"}},
    {Key::key_y,            {"y", "Y"}},
    {Key::key_z,            {"z", "Z"}},

    {Key::f1,               {"F1"}},
    {Key::f2,               {"F2"}},
    {Key::f3,               {"F3"}},
    {Key::f4,               {"F4"}},
    {Key::f5,               {"F5"}},
    {Key::f6,               {"F6"}},
    {Key::f7,               {"F7"}},
    {Key::f8,               {"F8"}},
    {Key::f9,               {"F9"}},
    {Key::f10,              {"F10"}},
    {Key::f11,              {"F11"}},
    {Key::f12,              {"F12"}},
    {Key::f13,              {"F13"}},
    {Key::f14,              {"F14"}},
    {Key::f15,              {"F15"}},
    {Key::f16,              {"F16"}},
    {Key::f17,              {"F17"}},
    {Key::f18,              {"F18"}},
    {Key::f19,              {"F19"}},
    {Key::f20,              {"F20"}},
    {Key::f21,              {"F21"}},
    {Key::f22,              {"F22"}},
    {Key::f23,              {"F23"}},
    {Key::f24,              {"F24"}},

    {Key::insert,           {"Insert"}},
    {Key::clear,            {"Clear"}},

    {Key::home,             {"Home"}},
    {Key::end,              {"End"}},
    {Key::pageup,           {"Page Up"}},
    {Key::pagedown,         {"Page Down"}},

    {Key::application,      {"Application"}},
    {Key::printscreen,      {"Print Screen"}},

    {Key::space,            {"Space"}},
    {Key::tab,              {"Tab"}},
    {Key::backspace,        {"Backspace"}},
    {Key::delete_,          {"Delete"}},

    {Key::equal,            {"=", "+"}},
    {Key::backquote,        {"`", "~"}},
    {Key::quote,            {"'", "\""}},
    {Key::backslash,        {"\\", "|"}},
    {Key::comma,            {",", "<"}},
    {Key::minus,            {"-", "_"}},
    {Key::period,           {".", ">"}},
    {Key::semicolon,        {";", ":"}},
    {Key::slash,            {"/", "?"}},

    {Key::keypad_0,         {"Keypad 0"}},
    {Key::keypad_1,         {"Keypad 1"}},
    {Key::keypad_2,         {"Keypad 2"}},
    {Key::keypad_3,         {"Keypad 3"}},
    {Key::keypad_4,         {"Keypad 4"}},
    {Key::keypad_5,         {"Keypad 5"}},
    {Key::keypad_6,         {"Keypad 6"}},
    {Key::keypad_7,         {"Keypad 7"}},
    {Key::keypad_8,         {"Keypad 8"}},
    {Key::keypad_9,         {"Keypad 9"}},
    {Key::keypad_a,         {"Keypad a"}},
    {Key::keypad_b,         {"Keypad b"}},
    {Key::keypad_c,         {"Keypad c"}},
    {Key::keypad_d,         {"Keypad d"}},
    {Key::keypad_e,         {"Keypad e"}},
    {Key::keypad_f,         {"Keypad f"}},

    {Key::keypad_backspace, {"Keypad Backspace"}},

    {Key::keypad_space,     {"Keypad Space"}},
    {Key::keypad_tab,       {"Keypad Tab"}},

    {Key::keypad_period,    {"Keypad ."}},
    {Key::keypad_plus,      {"Keypad +"}},
    {Key::keypad_minus,     {"Keypad -"}},
    {Key::keypad_asterisk,  {"Keypad *"}},
    {Key::keypad_slash,     {"Keypad /"}},
    {Key::keypad_plusminus, {"Keypad +-"}},
    {Key::keypad_enter,     {"Keypad Enter"}},
    {Key::keypad_equal,     {"Keypad ="}},
};
// clang-format on

} // namespace

optional<std::string> keybind_key_name(snail::Key key, bool shift)
{
    const auto it = key_names.find(key);
    if (it == key_names.end())
    {
        return none;
    }

    if (shift)
    {
        return it->second.shift;
    }
    else
    {
        return it->second.normal;
    }
}

std::string keybind_key_short_name(snail::Key key, bool shift)
{
    auto name_opt = keybind_key_name(key, shift);
    if (!name_opt)
    {
        return "";
    }

    auto name = *name_opt;
    strutil::try_remove_prefix(name, "Keypad ");

    // TODO: Some keys can still overflow the key_select banner. For now, just
    // return an empty string for those keys. Trimming them to one character
    // isn't always useful. ("Enter" and "E" will both be trimmed to "E".)
    if (name.size() > 1)
    {
        return "";
    }

    return name;
}

optional<snail::Key> keybind_key_code(const std::string& name, bool shift)
{
    for (const auto& it : key_names)
    {
        if ((shift && it.second.shift && *it.second.shift == name) ||
            (!shift && it.second.normal == name))
        {
            return it.first;
        }
    }
    return none;
}

} // namespace elona
