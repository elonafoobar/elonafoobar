#include "../thirdparty/catch2/catch.hpp"

#include <iostream>
#include "../keybind/keybind.hpp"
#include "../keybind/keybind_deserializer.hpp"

using namespace elona;
using namespace elona::snail;

namespace
{
KeybindManager load(KeybindManager& manager, std::string config)
{
    KeybindDeserializer deserializer(manager);
    std::istringstream ss{config};

    deserializer.load(ss);

    return manager;
}
} // namespace

TEST_CASE(
    "When given no bindings, KeybindDeserializer should load nothing",
    "[Keybind]")
{
    KeybindManager manager;
    load(manager, R"(keybindings {
    core {}
}
)");
}

TEST_CASE(
    "When given invalid bindings, KeybindDeserializer should not load them",
    "[Keybind]")
{
    keybind::actions.clear();
    keybind::actions.emplace("foo", Action{ActionCategory::game, {}});
    keybind::actions.emplace("test1", Action{ActionCategory::game, {}});
    keybind::actions.emplace("test2", Action{ActionCategory::game, {}});
    keybind::actions.emplace("test3", Action{ActionCategory::game, {}});
    keybind::actions.emplace("dupe", Action{ActionCategory::game, {}});

    KeybindManager manager;
    manager.register_default_bindings(keybind::actions);
    load(manager, R"(keybindings {
    core {
        foo = 42
        test1 {}
        test2 { primary = "dood" }
        test3 { alternate = "dood" }
        dupe { primary = "a" }
        dupe { primary = "b" }
    }
}
)");

    REQUIRE(manager.binding("foo").primary.main == snail::Key::none);
    REQUIRE(manager.binding("test1").primary.main == snail::Key::none);
    REQUIRE(manager.binding("test2").primary.main == snail::Key::none);
    REQUIRE(manager.binding("test3").alternate.main == snail::Key::none);
    REQUIRE(manager.binding("dupe").primary.main == snail::Key::none);
}

TEST_CASE(
    "When given an unknown action, KeybindDeserializer should not load its "
    "binding",
    "[Keybind]")
{
    keybind::actions.clear();

    KeybindManager manager;
    manager.register_default_bindings(keybind::actions);
    load(manager, R"(keybindings {
    core {
        test1 {
            primary = "A"
        }
    }
}
)");

    REQUIRE(!manager.is_registered("test1"));
}

TEST_CASE(
    "When given valid bindings, KeybindDeserializer should load them",
    "[Keybind]")
{
    keybind::actions.clear();
    keybind::actions.emplace("foo", Action{ActionCategory::game, {}});
    keybind::actions.emplace("test1", Action{ActionCategory::game, {}});
    keybind::actions.emplace("test2", Action{ActionCategory::game, {}});

    KeybindManager manager;
    manager.register_default_bindings(keybind::actions);
    load(manager, R"(keybindings {
    core {
        foo = 42
        test1 {
            primary = "A"
        }
        test2 {
            primary = "dood"
            alternate = "Ctrl+Keypad *"
        }
    }
}
)");

    {
        auto kb = Keybind{Key::key_a, ModKey::shift};
        REQUIRE(manager.binding("test1").primary == kb);
    }
    {
        auto kb = Keybind{Key::none, ModKey::none};
        REQUIRE(manager.binding("test2").primary == kb);
    }
    {
        auto kb = Keybind{Key::keypad_asterisk, ModKey::ctrl};
        REQUIRE(manager.binding("test2").alternate == kb);
    }
}
