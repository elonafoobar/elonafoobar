#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../character.hpp"
#include "../dmgheal.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test that _MOD_NAME is defined", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("my_mod", R"(assert(_MOD_NAME == "my_mod"))"));
}

TEST_CASE("Test that globals cannot be overwritten", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("my_mod", "", true));

    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(_MOD_NAME = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(dood = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(function dood() end)"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(Elona = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(Store = "dood")"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("my_mod", R"(assert(_MOD_NAME == "my_mod"))"));
}

TEST_CASE("Test that sandboxing removes unsafe functions", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("my_mod", ""));

    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(rawset(_G, "assert", nil))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawget(_G, "assert"))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawequal(1, 1))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawlen({}))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(require "mods/core/init")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(collectgarbage())"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(loadstring("i = 1"))"));
    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(dofile("tests/lua/item.lua"))"));
    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(loadfile("tests/lua/item.lua"))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod(
        "my_mod", R"(load("return function(a,b) return a+b end"))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(setmetatable(_G, {}))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(getmetatable(_G))"));
    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(module(..., package.seeall))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(setfenv(print, {}))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(getfenv(print))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod("my_mod", R"(assert(package == nil))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod(
        "my_mod", R"(package.loadlib("LibSDL2.dll", "main")())"));

    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawlen = nil; rawlen({}))"));
}

TEST_CASE("Test no access to os/io", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(mod_mgr.run_in_mod("my_mod", R"(assert(os == nil))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod("my_mod", R"(assert(io == nil))"));
}

TEST_CASE("Test usage of store in mod", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(
        mod_mgr.load_mod_from_script("test", "Store.global.thing = 1"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.thing == 1)"));
    int thing = mod_mgr.get_mod("test")->store_global["thing"].get<int>();
    REQUIRE(thing == 1);
}

TEST_CASE("Test invalid usage of store in main state", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(
        mod_mgr.load_mod_from_script("test", "Store.global.thing = 1"));

    // Accessed from main state, not the mod's environment
    sol::object obj = (*lua.get_state())["Store"];
    REQUIRE(obj == sol::lua_nil);
}

TEST_CASE("Test modification of store inside callback", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_turn_handler()
  Store.global.thing = Store.global.thing + 1
end

Store.global.thing = 1

Event.register(Event.EventKind.AllTurnsFinished, my_turn_handler)
)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.thing == 1)"));

    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.thing == 2)"));

    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.thing == 4)"));
}

TEST_CASE("Test isolation of mod environments", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(
        mod_mgr.load_mod_from_script("first", R"(Store.global.thing = 42)"));
    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script(
        "second", R"(Store.global.thing = "dood")"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("first", R"(assert(Store.global.thing == 42))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod(
        "second", R"(assert(Store.global.thing == "dood"))"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("second", R"(Store.global.thing = false)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("first", R"(assert(Store.global.thing == 42))"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("second", R"(assert(Store.global.thing == false))"));
}


TEST_CASE("Test complex nested table assignment", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    auto& mod_mgr = lua.get_mod_manager();
    ;
    mod_mgr.load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_turn_handler()
   for x = 1, 20 do
      for y = 1, 20 do
         Store.global.grid[x][y] = 1
      end
   end
end

local grid = {}
for i = 1, 20 do
   grid[i] = {}

   for j = 1, 20 do
      grid[i][j] = 0
   end
end

Store.global.grid = grid

Event.register(Event.EventKind.AllTurnsFinished, my_turn_handler)
)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.grid[1][1] == 0)"));

    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(Store.global.grid[1][1] == 1)"));
}

TEST_CASE("Test requiring Lua chunk multiple times", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(),
        filesystem::dir::exe() / u8"tests/data/mods/test_require_chunks");

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod("test_require_chunks", R"(
local a = require("data/script")
local b = require("data/script")

assert(a.value() == 0)
assert(b.value() == 0)

a.increment_locally()

assert(a.value() == 1)
assert(b.value() == 1)
)"));
}

TEST_CASE(
    "Test requiring Lua chunk outside of current directory",
    "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(),
        filesystem::dir::exe() / u8"tests/data/mods/test_require");

    // Attempts to load a file outside the mod's directory.
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod("test_require", R"(
local a = require("../test_require_chunks/data/script")

assert(a == nil)
)"));
}
