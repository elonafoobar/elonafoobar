#include "../thirdparty/catch2/catch.hpp"

#include "../character.hpp"
#include "../enums.hpp"
#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

static lua::DataTable load(elona::lua::LuaEnv& lua, const std::string& name)
{
    const auto base_path = testing::get_test_data_path() / "registry";

    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), {base_path / name});

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    return lua.get_data_manager().get();
}

TEST_CASE("test reading invalid enum", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_invalid_enum");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_invalid_enum.putit"];
    REQUIRE_NONE(data);
    REQUIRE(
        *db.error(SharedId("chara_invalid_enum.putit"))
        == "Enum value Whatever for Color not found.");
}

TEST_CASE("test reading duplicate keys", "[Lua: Data]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), {base_path / "chara_duplicate_key"});

    REQUIRE_THROWS(lua.get_data_manager().init_from_mods());
}

TEST_CASE("test registering character", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara.spiral_putit"];

    REQUIRE(data);
    REQUIRE(data->id == 9999);
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

    REQUIRE(data->color == ColorIndex::blue);
    REQUIRE(data->sex == 1);
    REQUIRE(data->original_relationship == -3);
    REQUIRE(data->_flags[22] == true);
    REQUIRE(data->_flags[27] == true);
}

TEST_CASE("test registering character with all defaults", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_defaults");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_defaults.nothing"];

    REQUIRE(data);
    REQUIRE(data->id == 9999);
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

    REQUIRE(data->color == ColorIndex::none);
    REQUIRE(data->sex == -1);
    REQUIRE(data->original_relationship == 0);
    REQUIRE(data->_flags[22] == false);
    REQUIRE(data->_flags[27] == false);
}

TEST_CASE("test usage of legacy ID", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db[9999];

    REQUIRE(data);
    REQUIRE(data->id == 9999);
}

TEST_CASE("test character flags", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_defaults");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_defaults.nothing"];

    REQUIRE(data);
    for (size_t i = 0; i < 32 * 30; ++i)
    {
        REQUIRE(data->_flags[i] == false);
    }
}
