#include "../elona/character.hpp"
#include "../elona/dmgheal.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/event_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/lua_event/base_event.hpp"
#include "../elona/lua_env/lua_event/lua_event_map_initialized.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test that _MOD_ID is defined", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("my_mod", R"(assert(_MOD_ID == "my_mod"))"));
}

TEST_CASE("Test that globals cannot be overwritten", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("my_mod", ""));

    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(_MOD_ID = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(dood = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(function dood() end)"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(Elona = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(mod = "dood")"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(mod.store = "dood")"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("my_mod", R"(assert(_MOD_ID == "my_mod"))"));
}

TEST_CASE("Test that sandboxing removes unsafe functions", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("my_mod", ""));

    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(rawset(_G, "assert", nil))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawget(_G, "assert"))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawequal(1, 1))"));
    REQUIRE_THROWS(mod_mgr.run_in_mod("my_mod", R"(rawlen({}))"));
    REQUIRE_THROWS(
        mod_mgr.run_in_mod("my_mod", R"(require_relative("mods/core/init"))"));
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
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(mod_mgr.run_in_mod("my_mod", R"(assert(os == nil))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod("my_mod", R"(assert(io == nil))"));
}

TEST_CASE("Test usage of store in mod", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
        "test", "mod.store.global.thing = 1"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.thing == 1)"));
    int thing = mod_mgr.get_mod("test")->env.get<int>(
        std::tie("mod", "store", "global", "thing"));
    REQUIRE(thing == 1);
}

TEST_CASE("Test invalid usage of store in main state", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
        "test", "mod.store.global.thing = 1"));

    // Accessed from main state, not the mod's environment
    sol::object obj = (*lua.get_state())["mod.store"];
    REQUIRE(obj == sol::lua_nil);
}

TEST_CASE("Test modification of store inside callback", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test", R"(
local Event = require("game.Event")

local function my_turn_handler()
  mod.store.global.thing = mod.store.global.thing + 1
end

mod.store.global.thing = 1

Event.register("core.all_turns_finished", my_turn_handler)
)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.thing == 1)"));

    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.thing == 2)"));

    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));
    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.thing == 4)"));
}

TEST_CASE("Test isolation of mod environments", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
        "first", R"(mod.store.global.thing = 42)"));
    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
        "second", R"(mod.store.global.thing = "dood")"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("first", R"(assert(mod.store.global.thing == 42))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod(
        "second", R"(assert(mod.store.global.thing == "dood"))"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("second", R"(mod.store.global.thing = false)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("first", R"(assert(mod.store.global.thing == 42))"));
    REQUIRE_NOTHROW(mod_mgr.run_in_mod(
        "second", R"(assert(mod.store.global.thing == false))"));
}


TEST_CASE("Test complex nested table assignment", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    auto& mod_mgr = lua.get_mod_manager();
    lua.load_mods();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test", R"(
local Event = require("game.Event")

local function my_turn_handler()
   for x = 1, 20 do
      for y = 1, 20 do
         mod.store.global.grid[x][y] = 1
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

mod.store.global.grid = grid

Event.register("core.all_turns_finished", my_turn_handler)
)"));

    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.grid[1][1] == 0)"));

    lua.get_event_manager().trigger(
        elona::lua::BaseEvent("core.all_turns_finished"));
    REQUIRE_NOTHROW(
        mod_mgr.run_in_mod("test", "assert(mod.store.global.grid[1][1] == 1)"));
}

TEST_CASE("Test requiring Lua chunk multiple times", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;
    lua.load_mods();
    lua.get_mod_manager().load_testing_mod_from_file(
        filesystem::dirs::exe() / u8"tests/data/mods/test_require_chunks");

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod("test_require_chunks", R"(
local a = require_relative("data/script")
local b = require_relative("data/script")

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
    elona::lua::LuaEnv lua;
    lua.load_mods();
    lua.get_mod_manager().load_testing_mod_from_file(
        filesystem::dirs::exe() / u8"tests/data/mods/test_require");

    // Attempts to load a file outside the mod's directory.
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod("test_require", R"(
local a = require_relative("../test_require_chunks/data/script")

assert(a == nil)
)"));
}



#if 0
TEST_CASE("Test resolve_path_for_mod", "[Lua: Mods]")
{
    using namespace filesystem;

    REQUIRE(
        lua::resolve_path_for_mod("<_builtin_>/dood") == dirs::exe() / "dood");
    REQUIRE(
        lua::resolve_path_for_mod("<test>/dood") ==
        dirs::for_mod("test") / "dood");
    REQUIRE(
        lua::resolve_path_for_mod("<test>/<dood>/file.txt") ==
        dirs::for_mod("test") / "<dood>" / "file.txt");
    REQUIRE(
        lua::resolve_path_for_mod("<test>/file-<LANGUAGE>.txt") ==
        dirs::for_mod("test") / "file-jp.txt");
    REQUIRE(
        lua::resolve_path_for_mod("<test>/<LANGUAGE>/file-<LANGUAGE>.txt") ==
        dirs::for_mod("test") / "jp" / "file-jp.txt");

    REQUIRE_THROWS(lua::resolve_path_for_mod("file.txt"));
    REQUIRE_THROWS(lua::resolve_path_for_mod("<>"));
    REQUIRE_THROWS(lua::resolve_path_for_mod("<$>/file.txt"));
}
#endif
