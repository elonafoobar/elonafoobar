#include "../thirdparty/catch2/catch.hpp"

#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

TEST_CASE("test registering datatype", "[Lua: Registry]")
{
    fs::path data = "tests/data/registry/putit.hcl";

    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("test", "putit_def.hcl"));
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
