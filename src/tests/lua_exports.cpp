#include "../elona/filesystem.hpp"
#include "../elona/lua_env/export_manager.hpp"
#include "../elona/lua_env/handle_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"
#include "util.hpp"

TEST_CASE("test registering Lua functions", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local exports = {}
exports.nesting = {}

function exports.my_callback()
   mod.store.global.called_times_a = mod.store.global.called_times_a + 1
end

function exports.nesting.my_callback()
   mod.store.global.called_times_b = mod.store.global.called_times_b + 1
end

mod.store.global.called_times_a = 0
mod.store.global.called_times_b = 0

return exports
)"));

    lua.get_export_manager().register_all_exports();

    {
        auto function =
            lua.get_export_manager().get_exported_function("test.my_callback");
        REQUIRE(static_cast<bool>(function));
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    {
        auto function = lua.get_export_manager().get_exported_function(
            "test.nesting.my_callback");
        REQUIRE(static_cast<bool>(function));
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(mod.store.global.called_times_a == 2))"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(mod.store.global.called_times_b == 3))"));
}

TEST_CASE("test registering Lua functions with arguments", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    testing::register_lua_function(
        lua, "test", "my_callback(arg)", "mod.store.global.value = arg");

    auto function =
        lua.get_export_manager().get_exported_function("test.my_callback");
    REQUIRE(static_cast<bool>(function));
    REQUIRE_NOTHROW(function->call(42));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(mod.store.global.value == 42))"));
}

TEST_CASE(
    "test registering Lua functions with userdata arguments",
    "[Lua: Exports]")
{
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_registry_chara_callback", R"(
local exports = {}

function exports.my_callback(chara)
   mod.store.global.found_index = chara.index
end

mod.store.global.found_index = -1

return exports
)"));

    elona::testing::start_in_debug_map();
    elona::lua::lua->get_export_manager().register_all_exports();

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = elona::lua::lua->get_handle_manager().get_handle(chara);

    auto function = elona::lua::lua->get_export_manager().get_exported_function(
        "test_registry_chara_callback.my_callback");
    REQUIRE(static_cast<bool>(function));
    REQUIRE_NOTHROW(function->call(handle));

    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_registry_chara_callback")
        ->env.set("index", elona::rc);
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_registry_chara_callback",
        R"(assert(mod.store.global.found_index == index))"));
}

TEST_CASE("test calling unknown exported function for result", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    lua.get_mod_manager().load_mods(filesystem::dirs::mod());
    lua.get_export_manager().register_all_exports();

    bool result = lua.get_export_manager().call_with_result("dood", false);
    REQUIRE(result == false);
}

TEST_CASE("test calling exported function with return type", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    testing::register_lua_function(
        lua, "test", "my_callback(arg)", "return 42");

    SECTION("wrong return type")
    {
        std::string result = lua.get_export_manager().call_with_result(
            "test.my_callback", "dood");

        REQUIRE(result == "dood");
    }
    SECTION("correct return type")
    {
        int result =
            lua.get_export_manager().call_with_result("test.my_callback", -1);

        REQUIRE(result == 42);
    }
}

TEST_CASE("test calling exported function with nil result", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    testing::register_lua_function(lua, "test", "my_callback()", "return nil");

    int result =
        lua.get_export_manager().call_with_result("test.my_callback", -1);

    REQUIRE(result == -1);
}

TEST_CASE("test calling exported function with error", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    testing::register_lua_function(
        lua, "test", "my_callback()", "error(\"error\")");

    int result =
        lua.get_export_manager().call_with_result("test.my_callback", -1);

    REQUIRE(result == -1);
}

TEST_CASE("test calling exported function with table result", "[Lua: Exports]")
{
    elona::lua::LuaEnv lua;

    testing::register_lua_function(
        lua, "test", "my_callback()", "return {foo = \"bar\"}");

    sol::table result = lua.get_export_manager().call_with_result(
        "test.my_callback", static_cast<sol::table>(sol::lua_nil));

    REQUIRE(result != sol::lua_nil);

    std::string foo = result["foo"];
    REQUIRE(foo == "bar");
}
