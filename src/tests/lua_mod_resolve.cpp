#include "../thirdparty/catch2/catch.hpp"

#include "../elona/lua_env/mod_version_resolver.hpp"

using namespace elona::lua;
using namespace elona::semver;



TEST_CASE("Test loading invalid mod list", "[Lua: Mods]")
{
    const auto check = [](const ModList& list) {
        REQUIRE(list.mods().size() == 1);
        REQUIRE(list.mods().at("core").is_satisfied(Version{0, 2, 6}));
    };

    check(ModList::from_file("404.not_found"));
    check(ModList::from_string(""));
    check(ModList::from_string("{ invalid JSON5 format }"));
    check(ModList::from_string("42"));
    check(ModList::from_string("{ foo: 123 }"));
    check(ModList::from_string("{ mods: null }"));
    check(ModList::from_string("{ mods: { true: 1, false: 0 } }"));
    check(ModList::from_string("{ mods: { a: 123, b: 456 } }"));
    check(ModList::from_string("{ mods: { a: '1.2.3', b: 'bar' } }"));
}



TEST_CASE("Test loading valid mod list", "[Lua: Mods]")
{
    const auto check =
        [](const ModList& list,
           const std::unordered_map<std::string, std::string>& expected) {
            const auto size = expected.size() + 1 /* +1 is for 'core' */;
            REQUIRE(list.mods().size() == size);
            REQUIRE(list.mods().at("core").is_satisfied(Version{0, 2, 6}));
            for (const auto& pair : expected)
            {
                const auto& id = pair.first;
                const auto& ver = pair.second;
                REQUIRE(list.mods().at(id).is_satisfied(
                    Version::parse(ver).right()));
            }
        };

    check(ModList::from_string("{ mods: { a: '1.2.3' } }"), {{"a", "1.2.3"}});
    check(ModList::from_string("{ mods: { a: '*' } }"), {{"a", "1.2.3"}});
    check(
        ModList::from_string("{ mods: { a: '1', b: '2' } }"),
        {{"a", "1.2.3"}, {"b", "2.3.4"}});
}


#if 0
TEST_CASE("Test calculation of loading order of mods", "[Lua: Mods]")
{
    elona::lua::LuaEnv lua;

    _create_mods(
        lua,
        {
            {"a", {{"c", "*"}}},
            {"b", {}},
            {"c", {{"b", "*"}, {"d", "*"}}},
            {"d", {}},
        });

    const auto order = lua.get_mod_manager().sorted_mods();

    REQUIRE(order.at(0)->manifest.id == "b");
    REQUIRE(order.at(1)->manifest.id == "d");
    REQUIRE(order.at(2)->manifest.id == "c");
    REQUIRE(order.at(3)->manifest.id == "a");
}

TEST_CASE(
    "Test failure to calculate loading order of mods (unknown dependency)",
    "[Lua: Mods]")
{
    REQUIRE_THROWS([]() {
        elona::lua::LuaEnv lua;
        _create_mods(
            lua,
            {
                {"a", {{"b", "*"}, {"c", "*"}}},
                {"b", {}},
            });
    }());
}

TEST_CASE(
    "Test failure to calculate loading order of mods (cyclic dependency)",
    "[Lua: Mods]")
{
    REQUIRE_THROWS([]() {
        elona::lua::LuaEnv lua;
        _create_mods(
            lua,
            {
                {"a", {{"b", "*"}}},
                {"b", {{"c", "*"}}},
                {"c", {{"a", "*"}}},
            });
    }());
}
#endif
