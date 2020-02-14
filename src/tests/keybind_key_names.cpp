#include <iostream>

#include "../elona/keybind/keybind.hpp"
#include "../thirdparty/catch2/catch.hpp"

using namespace elona;
using namespace elona::snail;

namespace
{
bool test_to(Keybind keybind, std::string expected)
{
    bool result = keybind.to_string() == expected;

    if (!result)
    {
        std::cerr << keybind.to_string() << std::endl;
    }

    return result;
}

bool test_from(std::string str, optional<Keybind> expected)
{
    auto keybind_opt = Keybind::from_string(str);
    auto result = keybind_opt == expected;

    if (!result && keybind_opt)
    {
        std::cerr << keybind_opt->to_string() << std::endl;
    }

    return result;
}

} // namespace

TEST_CASE("test keybind to string", "[Keybind]")
{
    snail::ModKey n = ModKey::none;
    snail::ModKey s = ModKey::shift;
    snail::ModKey cs = ModKey::ctrl | ModKey::shift;
    snail::ModKey csa = ModKey::ctrl | ModKey::shift | ModKey::alt;
    snail::ModKey csag =
        ModKey::ctrl | ModKey::shift | ModKey::alt | ModKey::gui;

    // clang-format off
    SECTION("With shifted name")
    {
        REQUIRE(test_to(Keybind{Key::key_a, n},    "a"));
        REQUIRE(test_to(Keybind{Key::key_a, s},    "A"));
        REQUIRE(test_to(Keybind{Key::key_a, cs},   "Ctrl+A"));
        REQUIRE(test_to(Keybind{Key::key_a, csa},  "Ctrl+Alt+A"));
        REQUIRE(test_to(Keybind{Key::key_a, csag}, "Ctrl+Alt+Gui+A"));
    }
    SECTION("Without shifted name")
    {
        REQUIRE(test_to(Keybind{Key::key_0, n},    "0"));
        REQUIRE(test_to(Keybind{Key::key_0, s},    "Shift+0"));
        REQUIRE(test_to(Keybind{Key::key_0, cs},   "Ctrl+Shift+0"));
        REQUIRE(test_to(Keybind{Key::key_0, csa},  "Ctrl+Shift+Alt+0"));
        REQUIRE(test_to(Keybind{Key::key_0, csag}, "Ctrl+Shift+Alt+Gui+0"));
    }
    // clang-format on
}

TEST_CASE("test key name to key code", "[Keybind]")
{
    snail::ModKey n = ModKey::none;
    snail::ModKey s = ModKey::shift;
    snail::ModKey cs = ModKey::ctrl | ModKey::shift;
    snail::ModKey csa = ModKey::ctrl | ModKey::shift | ModKey::alt;
    snail::ModKey csag =
        ModKey::ctrl | ModKey::shift | ModKey::alt | ModKey::gui;

    // clang-format off
    SECTION("Invalid")
    {
        REQUIRE(test_from("abcd", none));
        REQUIRE(test_from("Ctrl+", none));
        REQUIRE(test_from("Shift+Ctrl+1", none));
    }
    SECTION("With shifted name")
    {
        REQUIRE(test_from("a",                    Keybind{Key::key_a, n}));
        REQUIRE(test_from("A",                    Keybind{Key::key_a, s}));
        REQUIRE(test_from("Ctrl+A",               Keybind{Key::key_a, cs}));
        REQUIRE(test_from("Ctrl+Alt+A",           Keybind{Key::key_a, csa}));
        REQUIRE(test_from("Ctrl+Alt+Gui+A",       Keybind{Key::key_a, csag}));
        REQUIRE(test_from("Ctrl+Shift+Alt+Gui+A", Keybind{Key::key_a, csag}));
    }
    SECTION("Without shifted name")
    {
        REQUIRE(test_from("0",                    Keybind{Key::key_0, n}));
        REQUIRE(test_from("Shift+0",              Keybind{Key::key_0, s}));
        REQUIRE(test_from("Ctrl+Shift+0",         Keybind{Key::key_0, cs}));
        REQUIRE(test_from("Ctrl+Shift+Alt+0",     Keybind{Key::key_0, csa}));
        REQUIRE(test_from("Ctrl+Shift+Alt+Gui+0", Keybind{Key::key_0, csag}));
        REQUIRE(test_from("Shift+Keypad 1",       Keybind{Key::keypad_1, s}));
    }
    // clang-format on
}
