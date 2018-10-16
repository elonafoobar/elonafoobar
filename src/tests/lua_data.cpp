#include "../thirdparty/catch2/catch.hpp"

#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

TEST_CASE("test reading invalid HCL file", "[Lua: Registry]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), base_path / "invalid");

    REQUIRE_THROWS(lua.get_data_manager().init_from_mods());
}

TEST_CASE("test declaring and loading datatype", "[Lua: Registry]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), base_path / "putit");

    REQUIRE_NOTHROW(lua.get_data_manager.init_from_mods());

    const auto& table = lua.get_data_manager().get();

    auto normal = table.raw("putit.putit", "putit.normal");
    REQUIRE(normal.required<std::string>("display_name") == "putit");
    REQUIRE(normal.required<int>("id") == 3);

    auto red = table.raw("putit.putit", "putit.red");
    REQUIRE(red.required<std::string>("display_name") == "red putit");
    REQUIRE(red.required<int>("id") == 4);
}

TEST_CASE("test loading datatype originating from other mod", "[Lua:
Registry]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), {base_path / "putit", base_path / "putit_b"});

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    const auto& table = lua.get_data_manager().get();

    auto green = table.raw("putit.putit", "putit_b.green");
    REQUIRE(green.required<std::string>("display_name") == "green putit");
    REQUIRE(green.required<int>("id") == 5);
}

TEST_CASE(
    "test verification that API tables only have string keys",
    "[Lua: Registry]")
{
    elona::lua::LuaEnv lua;
    REQUIRE_THROWS(lua.get_mod_manager().load_mods(
        filesystem::dir::mods(),
        {testing::get_test_data_path() / "mods" / "test_export_keys"}));
}
