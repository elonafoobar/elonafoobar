#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../character.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test that store can be reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test", "Store.global.thing = 1"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.thing == nil)"));
}

TEST_CASE("Test that store can be reset across mods", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test1", "Store.global.mine = false; Store.global.thing = 1"));
    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test2", "Store.global.theirs = true; Store.global.thing = 2"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(Store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(Store.global.mine == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(Store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(Store.global.theirs == nil)"));
}

TEST_CASE("Test that API tables aren't reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(Rand = Elona.require("Rand"); assert(Rand ~= nil))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(Rand = Elona.require("Rand"); assert(Rand ~= nil))"));
}

TEST_CASE("Test that globals aren't reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_NAME == "test"))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_NAME == "test"))"));
}

TEST_CASE(
    "Test that store can be reset and map init hooks re-run",
    "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_map_init_hook()
   Store.global.val = 42
end

Event.register(Event.EventKind.MapInitialized, my_map_init_hook)
)"));

    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::map_initialized>();
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.val == 42)"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.thing == nil)"));

    lua.get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::map_initialized>();
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.val == 42)"));
}

TEST_CASE("Test preservation of global data", "[Lua: Serialization]")
{
    start_in_map(9999, 2);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_global", R"(
local Event = Elona.require("Event")

local function my_hook()
   Store.global.val = 42
end

Event.register(Event.EventKind.AllTurnsFinished, my_hook)
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(Store.global.val == nil)"));
    elona::lua::lua->get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(Store.global.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_global", "assert(Store.global.val == 42)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(Store.global.val == 42)"));
}


TEST_CASE("Test preservation of map local data", "[Lua: Serialization]")
{
    start_in_map(9999, 2);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_map_local", R"(
local Event = Elona.require("Event")

local function my_hook()
   Store.map_local.val = 42
end

Event.register(Event.EventKind.AllTurnsFinished, my_hook)
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map_local", "assert(Store.map_local.val == nil)"));
    elona::lua::lua->get_event_manager()
        .run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map_local", "assert(Store.map_local.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_map_local", "assert(Store.map_local.val == nil)"));
    });

    // TODO after serialization is implemented
    // run_in_temporary_map(9999, 2);
    // REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod("test",
    // "assert(Store.map_local.val == 42)"));
}
