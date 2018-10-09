#include "../thirdparty/catch2/catch.hpp"

#include <iostream>
#include "../keybind/keybind.hpp"
#include "../keybind/keybind_manager.hpp"
#include "../keybind/keybind_serializer.hpp"

using namespace elona;
using namespace elona::snail;

TEST_CASE(
    "When given no bindings, KeybindSerializer should output nothing",
    "[Keybind]")
{
    KeybindManager manager;
    KeybindSerializer serializer(manager);
    std::ostringstream ss;

    serializer.save(ss);

    REQUIRE(ss.str() == R"(keybindings {
   core {
   }
}
)");
}

TEST_CASE(
    "When given invalid bindings, KeybindSerializer should not output them",
    "[Keybind]")
{
    KeybindManager manager;
    manager.register_binding("game_action");

    KeybindSerializer serializer(manager);
    std::ostringstream ss;

    serializer.save(ss);

    REQUIRE(ss.str() == R"(keybindings {
   core {
   }
}
)");
}

TEST_CASE(
    "When given valid bindings, KeybindSerializer should output them",
    "[Keybind]")
{
    keybind::actions.clear();
    keybind::actions.emplace(
        "game_action1",
        Action{ActionCategory::game,
               {{Key::key_a, ModKey::none},
                {Key::key_1, ModKey::ctrl | ModKey::shift}}});
    keybind::actions.emplace(
        "menu_action1",
        Action{ActionCategory::menu, {{Key::key_b, ModKey::shift}}});

    KeybindManager manager;
    manager.load_default_bindings(keybind::actions);

    KeybindSerializer serializer(manager);
    std::ostringstream ss;

    serializer.save(ss);

    REQUIRE(ss.str() == R"(keybindings {
   core {
       game_action1 {
           primary = "a"
           alternate = "Ctrl+Shift+1"
       }
       menu_action1 {
           primary = "B"
       }
   }
}
)");
}
