#include "../thirdparty/catch2/catch.hpp"

#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

const auto base_path = filesystem::dir::exe() / "tests" / "data" / "registry";

TEST_CASE("test reading invalid HCL file", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_THROWS(lua.get_registry_manager().load_mod_data(
        {{base_path / "invalid" / "data.hcl", "test"}}));
}

TEST_CASE("test declaring and loading datatype", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
        {{base_path / "putit" / "data.hcl", "test"}}));

    auto table = lua.get_registry_manager().get_table("test", "putit");
    REQUIRE(table != sol::nullopt);

    sol::table normal = (*table)["test"]["normal"];
    REQUIRE(normal["name"].get<std::string>() == "putit");
    REQUIRE(normal["id"].get<int>() == 3);
    REQUIRE(normal["_id"].get<std::string>() == "test.normal");
    REQUIRE(normal["_full_id"].get<std::string>() == "test.putit:test.normal");
    REQUIRE(normal["_mod"].get<std::string>() == "test");

    sol::table red = (*table)["test"]["red"];
    REQUIRE(red["name"].get<std::string>() == "red putit");
    REQUIRE(red["id"].get<int>() == 4);
    REQUIRE(red["_id"].get<std::string>() == "test.red");
    REQUIRE(red["_full_id"].get<std::string>() == "test.putit:test.red");
    REQUIRE(red["_mod"].get<std::string>() == "test");
}

TEST_CASE("test loading datatype originating from other mod", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
        {{base_path / "putit" / "data.hcl", "test"}}));
    REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
        {{base_path / "putit_b" / "data.hcl", "putit_b"}}));

    auto table = lua.get_registry_manager().get_table("test", "putit");
    REQUIRE(table != sol::nullopt);

    sol::table normal = (*table)["putit_b"]["normal"];
    REQUIRE(normal["name"].get<std::string>() == "putit");
    REQUIRE(normal["id"].get<int>() == 3);
    REQUIRE(normal["_id"].get<std::string>() == "putit_b.normal");
    REQUIRE(
        normal["_full_id"].get<std::string>() == "test.putit:putit_b.normal");
    REQUIRE(normal["_mod"].get<std::string>() == "putit_b");

    sol::table red = (*table)["putit_b"]["red"];
    REQUIRE(red["name"].get<std::string>() == "red putit");
    REQUIRE(red["id"].get<int>() == 4);
    REQUIRE(red["_id"].get<std::string>() == "putit_b.red");
    REQUIRE(red["_full_id"].get<std::string>() == "test.putit:putit_b.red");
    REQUIRE(red["_mod"].get<std::string>() == "putit_b");
}

TEST_CASE("test registering Lua functions", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Exports = {}
Exports.nesting = {}

function Exports.my_callback()
   Store.global.called_times_a = Store.global.called_times_a + 1
end

function Exports.nesting.my_callback()
   Store.global.called_times_b = Store.global.called_times_b + 1
end

Store.global.called_times_a = 0
Store.global.called_times_b = 0

return {
    Exports = Exports
}
)"));

    lua.get_export_manager().register_all_exports();

    {
        auto function = lua.get_export_manager().get_exported_function(
            "test.exports.my_callback");
        REQUIRE(static_cast<bool>(function));
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    {
        auto function = lua.get_export_manager().get_exported_function(
            "test.exports.nesting.my_callback");
        REQUIRE(static_cast<bool>(function));
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times_a == 2))"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.called_times_b == 3))"));
}

TEST_CASE("test registering Lua functions with arguments", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Exports = {}

function Exports.my_callback(arg)
   Store.global.value = arg
end

Store.global.value = 0

return {
    Exports = Exports
}
)"));

    lua.get_export_manager().register_all_exports();

    auto function = lua.get_export_manager().get_exported_function(
        "test.exports.my_callback");
    REQUIRE(static_cast<bool>(function));
    REQUIRE_NOTHROW(function->call(42));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(Store.global.value == 42))"));
}

TEST_CASE(
    "test registering Lua functions with userdata arguments",
    "[Lua: Registry]")
{
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_registry_chara_callback", R"(
local Exports = {}

function Exports.my_callback(chara)
   Store.global.found_index = chara.index
end

Store.global.found_index = -1

return {
    Exports = Exports
}
)"));

    elona::testing::start_in_debug_map();
    elona::lua::lua->get_export_manager().register_all_exports();

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    character& chara = elona::cdata[elona::rc];
    auto handle = elona::lua::lua->get_handle_manager().get_handle(chara);

    auto function = elona::lua::lua->get_export_manager().get_exported_function(
        "test_registry_chara_callback.exports.my_callback");
    REQUIRE(static_cast<bool>(function));
    REQUIRE_NOTHROW(function->call(handle));

    elona::lua::lua->get_mod_manager()
        .get_mod("test_registry_chara_callback")
        ->env.set("index", elona::rc);
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_registry_chara_callback",
        R"(assert(Store.global.found_index == index))"));
}

TEST_CASE(
    "test verification that API tables only have string keys",
    "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    REQUIRE_THROWS(lua.get_mod_manager().load_mods(
        filesystem::dir::mods(),
        {filesystem::dir::exe() / u8"tests/data/mods/test_export_keys"}));
}
