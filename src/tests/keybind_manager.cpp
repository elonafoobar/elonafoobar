#include "../thirdparty/catch2/catch.hpp"

#include "../keybind/keybind.hpp"

using namespace elona;
using namespace elona::snail;

namespace
{
KeybindManager make_manager()
{
    // clang-format off
    keybind::actions.clear();
    keybind::actions.emplace("game_action1", Action{ ActionCategory::game, {{Key::key_a, ModKey::none}, {Key::key_1, ModKey::shift}}});
    keybind::actions.emplace("game_action2", Action{ ActionCategory::game, {{Key::key_b, ModKey::none}}});
    keybind::actions.emplace("menu_action1", Action{ ActionCategory::menu, {{Key::key_c, ModKey::none}}});
    keybind::actions.emplace("menu_action2", Action{ ActionCategory::menu, {{Key::key_d, ModKey::none}}});
    // clang-format on

    KeybindManager manager;
    manager.register_default_bindings(keybind::actions);

    return manager;
}
} // namespace

TEST_CASE(
    "Given a non-conflicting keybind, KeybindManager should report no "
    "conflicts",
    "[Keybind]")
{
    KeybindManager manager = make_manager();

    SECTION("Differing key")
    {
        Keybind keybind{Key::key_e, ModKey::none};
        REQUIRE(manager.find_conflicts("game_action2", keybind).size() == 0);
    }
    SECTION("Differing modkey")
    {
        Keybind keybind{Key::key_a, ModKey::shift};
        REQUIRE(manager.find_conflicts("game_action2", keybind).size() == 0);
    }
    SECTION("Differing context type")
    {
        Keybind keybind{Key::key_a, ModKey::none};
        REQUIRE(manager.find_conflicts("menu_action1", keybind).size() == 0);
    }
}

TEST_CASE(
    "Given a conflicting keybind, KeybindManager should report conflicts",
    "[Keybind]")
{
    KeybindManager manager = make_manager();

    SECTION("Same key and modkey")
    {
        Keybind keybind{Key::key_a, ModKey::none};
        REQUIRE(manager.find_conflicts("game_action2", keybind).size() == 1);
    }
    SECTION("Same key and modkey, alternate")
    {
        Keybind keybind{Key::key_1, ModKey::shift};
        REQUIRE(manager.find_conflicts("game_action2", keybind).size() == 1);
    }
}
