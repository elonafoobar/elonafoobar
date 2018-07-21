#include "../thirdparty/catch2/catch.hpp"

#include "../character.hpp"
#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

static sol::table load(elona::lua::lua_env& lua, const fs::path& data_file)
{
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();
    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("core", "chara"));
    REQUIRE_NOTHROW(lua.get_registry_manager().register_data("core", "chara", data_file));
    auto table = lua.get_registry_manager().get_table("core", "chara");
    REQUIRE(table);
    return *table;
}

TEST_CASE("test reading nonexistent file", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();
    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("core", "chara"));

    REQUIRE_THROWS(lua.get_registry_manager().register_data("core", "chara", "blah"));
}

TEST_CASE("test reading of official chara.hcl", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, filesystem::dir::mods() / "core" / "data" / "chara.hcl");

    character_db_ex db;
    REQUIRE_NOTHROW(db.initialize(table));
}

TEST_CASE("test reading invalid enum", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "tests/data/registry/chara_invalid_enum.hcl");

    character_db_ex db;
    REQUIRE_THROWS(db.initialize(table));
}

TEST_CASE("test reading duplicate keys", "[Lua: Registry]")
{
    const fs::path data_path = "tests/data/registry/chara_duplicate_key.hcl";

    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod();
    REQUIRE_NOTHROW(lua.get_registry_manager().register_datatype("core", "chara"));

    REQUIRE_THROWS(lua.get_registry_manager().register_data("core", "chara", data_path));
}

TEST_CASE("test registering character", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "tests/data/registry/chara.hcl");

    character_db_ex db;
    db.initialize(table);

    auto data = db["core.chara.spiral_putit"];

    REQUIRE(data);
    REQUIRE(data->id == 500);
    REQUIRE(data->item_type == 2);
    REQUIRE(data->filter == "/slime/ether/");
    REQUIRE(data->level == 2);
    REQUIRE(data->portrait == 200);
    REQUIRE(data->image == 430);
    REQUIRE(data->female_image == 431);
    REQUIRE(data->male_image == 432);
    REQUIRE(data->race == "slime");
    REQUIRE(data->class_ == "wizard");

    {
        std::vector<int> expected = {417, 434, 415, 454};
        REQUIRE(data->normal_actions == expected);
    }
    {
        std::vector<int> expected = {636};
        REQUIRE(data->special_actions == expected);
    }
    {
        std::unordered_map<int, int> expected = {{54, 500}};
        REQUIRE(data->resistances == expected);
    }

    REQUIRE(data->color == 3);
    REQUIRE(data->sex == 1);
    REQUIRE(data->original_relationship == -3);
    REQUIRE(data->_flags[22] == true);
    REQUIRE(data->_flags[27] == true);
}

TEST_CASE("test registering with all defaults specified", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "tests/data/registry/chara_defaults.hcl");

    character_db_ex db;
    db.initialize(table);

    auto data = db["core.chara.nothing"];

    REQUIRE(data);
    REQUIRE(data->id == -1);
    REQUIRE(data->item_type == 0);
    REQUIRE(data->filter == "");
    REQUIRE(data->level == 0);
    REQUIRE(data->portrait == 0);
    REQUIRE(data->image == 0);
    REQUIRE(data->race == "");
    REQUIRE(data->class_ == "");

    {
        std::vector<int> expected = {-1};
        REQUIRE(data->normal_actions == expected);
    }
    {
        std::vector<int> expected = {};
        REQUIRE(data->special_actions == expected);
    }
    {
        std::unordered_map<int, int> expected = {};
        REQUIRE(data->resistances == expected);
    }

    REQUIRE(data->color == 0);
    REQUIRE(data->sex == -1);
    REQUIRE(data->original_relationship == 0);
    REQUIRE(data->_flags[22] == false);
    REQUIRE(data->_flags[27] == false);
}


TEST_CASE("test usage of legacy ID", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "tests/data/registry/chara.hcl");

    character_db_ex db;
    db.initialize(table);

    auto data = db[500];

    REQUIRE(data);
    REQUIRE(data->id == 500);
}

TEST_CASE("test character flags", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "tests/data/registry/chara_defaults.hcl");

    character_db_ex db;
    db.initialize(table);

    auto data = db["core.chara.nothing"];

    REQUIRE(data);
    for (size_t i = 0; i < 32 * 30; ++i)
    {
        REQUIRE(data->_flags[i] == false);
    }
}
