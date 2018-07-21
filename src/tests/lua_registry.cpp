#include "../thirdparty/catch2/catch.hpp"

#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

TEST_CASE("test reading invalid HCL file", "[Lua: Registry]")
{
    const fs::path data_file = "tests/data/registry/invalid.hcl";

    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();

    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("test", "chara"));

    REQUIRE_THROWS(lua.get_registry_manager().register_data("test", "chara", data_file));
}

TEST_CASE("test instantiating character from datatype", "[Lua: Registry]")
{
    const fs::path data = "tests/data/registry/putit.hcl";

    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();

    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("test", "putit"));
    REQUIRE_NOTHROW(lua.get_registry_manager().register_data("test", "putit", data));

    auto table = lua.get_registry_manager().get_table("test", "putit");
    REQUIRE(table != sol::nullopt);

    REQUIRE((*table)["normal"]["name"].get<std::string>() == "putit");
    REQUIRE((*table)["normal"]["id"].get<int>() == 3);
    REQUIRE((*table)["normal"]["_id"].get<std::string>() == "normal");

    REQUIRE((*table)["red"]["name"].get<std::string>() == "red putit");
    REQUIRE((*table)["red"]["id"].get<int>() == 4);
    REQUIRE((*table)["red"]["_id"].get<std::string>() == "red");
}

TEST_CASE("test registering Lua functions", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
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

    lua.get_registry_manager().register_functions();

    {
        auto function = lua.get_registry_manager().get_function("test.exports.my_callback");
        REQUIRE(function);
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    {
        auto function = lua.get_registry_manager().get_function("test.exports.nesting.my_callback");
        REQUIRE(function);
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
        REQUIRE_NOTHROW(function->call());
    }

    REQUIRE_NOTHROW(
        lua.run_in_mod("test", R"(assert(Store.global.called_times_a == 2))"));
    REQUIRE_NOTHROW(
        lua.run_in_mod("test", R"(assert(Store.global.called_times_b == 3))"));
}

TEST_CASE("test registering Lua functions with arguments", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
local Exports = {}

function Exports.my_callback(arg)
   Store.global.value = arg
end

Store.global.value = 0

return {
    Exports = Exports
}
)"));

    lua.get_registry_manager().register_functions();

    auto function = lua.get_registry_manager().get_function("test.exports.my_callback");
    REQUIRE(function);
    REQUIRE_NOTHROW(function->call(42));

    REQUIRE_NOTHROW(
        lua.run_in_mod("test", R"(assert(Store.global.value == 42))"));
}

TEST_CASE("test registering Lua functions with userdata arguments", "[Lua: Registry]")
{
    elona::testing::start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->load_mod_from_script("test_registry_chara_callback", R"(
local Exports = {}

function Exports.my_callback(chara)
   Store.global.found_index = chara.index
end

Store.global.found_index = -1

return {
    Exports = Exports
}
)"));

    elona::lua::lua->get_registry_manager().register_functions();

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    character& chara = elona::cdata[elona::rc];
    auto handle = elona::lua::lua->get_handle_manager()
        .get_chara_handle(chara);

    auto function = elona::lua::lua->get_registry_manager()
        .get_function("test_registry_chara_callback.exports.my_callback");
    REQUIRE(function);
    REQUIRE_NOTHROW(function->call(handle));

    elona::lua::lua->get_mod("test_registry_chara_callback")->env.set("index", elona::rc);
    REQUIRE_NOTHROW(
        elona::lua::lua->run_in_mod("test_registry_chara_callback",
                                    R"(assert(Store.global.found_index == index))"));
}
