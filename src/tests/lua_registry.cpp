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
