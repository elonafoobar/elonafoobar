#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../elona/character.hpp"
#include "../elona/dmgheal.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/event_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/lua_event/base_event.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE(
    "Test registering a callback on an unknown event type",
    "[Lua: Events]")
{
    reset_state();

    REQUIRE_THROWS(lua::lua->get_mod_manager().run_in_mod("core", R"(
local Event = Elona.require("Event")

local function handler()
   Store.global.test = true
end

Store.global.test = false

Event.register("core.some_unknown_event", handler)
)"));

    lua::lua->get_event_manager().trigger(
        lua::BaseEvent("core.some_unknown_event"));

    REQUIRE_NOTHROW(lua::lua->get_mod_manager().run_in_mod(
        "core", R"(assert(Store.global.test == false))"));
}

TEST_CASE("Test registering of callback", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.thing = "dood"
end

Store.global.thing = nil

Event.register("core.all_turns_finished", my_handler)
)"));

    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.thing == "dood"))"));
}

TEST_CASE("Test registering of callback multiple times", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_THROWS(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.called_times = Store.global.called_times + 1
end

Store.global.called_times = 0

Event.register("core.all_turns_finished", my_handler)
Event.register("core.all_turns_finished", my_handler)
Event.register("core.all_turns_finished", my_handler)
Event.register("core.all_turns_finished", my_handler)
)"));
}

TEST_CASE(
    "Test registering of multiple callbacks on one event type",
    "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function first()
   Store.global.called_times = Store.global.called_times + 1
end

local function second()
   Store.global.called_times = Store.global.called_times + 1
end

Store.global.called_times = 0

Event.register("core.all_turns_finished", first)
Event.register("core.all_turns_finished", second)
)"));

    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times == 2))"));
}

TEST_CASE("Test unregistering of callback", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.thing = "dood"
end

Store.global.thing = nil

Event.register("core.all_turns_finished", my_handler)
Event.unregister("core.all_turns_finished", my_handler)
)"));

    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.thing == nil))"));
}

TEST_CASE("Test unregistering of callback multiple times", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.called_times = Store.global.called_times + 1
end

Store.global.called_times = 0

Event.register("core.all_turns_finished", my_handler)

Event.unregister("core.all_turns_finished", my_handler)
Event.unregister("core.all_turns_finished", my_handler)
Event.unregister("core.all_turns_finished", my_handler)
)"));

    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times == 0))"));
}

TEST_CASE("Test unregistering of callback without registering", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.called_times = Store.global.called_times + 1
end

Store.global.called_times = 0

Event.unregister("core.all_turns_finished", my_handler)
)"));

    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times == 0))"));
}

TEST_CASE("Test unregistering of callback inside callback", "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_handler()
   Store.global.called_times = Store.global.called_times + 1
   Event.unregister("core.all_turns_finished", my_handler)
end

Store.global.called_times = 0

Event.register("core.all_turns_finished", my_handler)
)"));

    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));
    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times == 1))"));
}

TEST_CASE(
    "Test triggering of callback inside another callback",
    "[Lua: Events]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function first_handler()
   Store.global.first = true
   Event.trigger("core.player_turn_started", {})
end

local function second_handler()
   Store.global.second = true
end

Store.global.first = false
Store.global.second = false

Event.register("core.all_turns_finished", first_handler)
Event.register("core.player_turn_started", second_handler)
)"));

    lua.get_event_manager().trigger(lua::BaseEvent("core.all_turns_finished"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.first == true))"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.second == true))"));
}
