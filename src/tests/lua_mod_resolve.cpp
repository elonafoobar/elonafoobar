#include "../elona/lua_env/mod_version_resolver.hpp"
#include "../thirdparty/catch2/catch.hpp"

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



#define VERSION_REQUIREMENT(major, minor, patch) \
    (VersionRequirement::from_version(Version(major, minor, patch)))
#define DEP(mod) \
    { \
        mod, VERSION_REQUIREMENT(1, 0, 0) \
    }
#define DEPS(...) \
    { \
        __VA_ARGS__ \
    }
#define MOD_CORE \
    { \
        "core", \
        { \
            { \
                Version{0, 2, 6}, {}, {}, \
            } \
        } \
    }
#define MOD(mod_id, deps, opt_deps) \
    { \
        mod_id, \
            { \
                { \
                    Version{1, 0, 0}, \
                    deps, \
                    opt_deps, \
                }, \
            }, \
    }



TEST_CASE("Test calculation of loading order of mods", "[Lua: Mods]")
{
    ModList list{ModList::from_string("{ mods: { a: '*' } }")};
    ModLock lock{};
    ModIndex index{{
        MOD_CORE,

        MOD("a", DEPS(DEP("c")), DEPS()),
        MOD("b", DEPS(), DEPS()),
        MOD("c", DEPS(DEP("b"), DEP("d")), DEPS()),
        MOD("d", DEPS(), DEPS()),
    }};
    ModVersionResolver resolver{};
    const auto resolve_result = resolver.resolve(list, lock, index);
    const auto& sorted = resolve_result.right().sorted_mods();

    REQUIRE(sorted.at(0) == "b");
    REQUIRE(sorted.at(1) == "core");
    REQUIRE(sorted.at(2) == "d");
    REQUIRE(sorted.at(3) == "c");
    REQUIRE(sorted.at(4) == "a");
}



TEST_CASE(
    "Test failure to calculate loading order of mods (unknown dependency)",
    "[Lua: Mods]")
{
    ModList list{ModList::from_string("{ mods: { a: '*' } }")};
    ModLock lock{};
    ModIndex index{{
        MOD_CORE,

        MOD("a", DEPS(DEP("b"), DEP("c")), DEPS()),
        MOD("b", DEPS(), DEPS()),
    }};
    ModVersionResolver resolver{};
    const auto resolve_result = resolver.resolve(list, lock, index);
    REQUIRE_FALSE(static_cast<bool>(resolve_result));
}



TEST_CASE(
    "Test failure to calculate loading order of mods (cyclic dependency)",
    "[Lua: Mods]")
{
    ModList list{ModList::from_string("{ mods: { a: '*' } }")};
    ModLock lock{};
    ModIndex index{{
        MOD_CORE,

        MOD("a", DEPS(DEP("b")), DEPS()),
        MOD("b", DEPS(DEP("c")), DEPS()),
        MOD("c", DEPS(DEP("a")), DEPS()),
    }};
    ModVersionResolver resolver{};
    const auto resolve_result = resolver.resolve(list, lock, index);
    REQUIRE_FALSE(static_cast<bool>(resolve_result));
}



TEST_CASE(
    "Test that optional dependencies don't affect version resolution",
    "[Lua: Mods]")
{
    ModList list{ModList::from_string("{ mods: { a: '*' } }")};
    ModLock lock{};
    ModIndex index{{
        MOD_CORE,

        MOD("a", DEPS(DEP("b")), DEPS()),
        MOD("b", DEPS(), DEPS(DEP("c"))),
    }};
    ModVersionResolver resolver{};
    const auto resolve_result = resolver.resolve(list, lock, index);
    REQUIRE(static_cast<bool>(resolve_result));
}



TEST_CASE(
    "Test calculation of loading order of mods with optional dependencies",
    "[Lua: Mods]")
{
    ModList list{ModList::from_string("{ mods: { a: '*' } }")};
    ModLock lock{};
    ModIndex index{{
        MOD_CORE,

        MOD("a", DEPS(DEP("c")), DEPS()),
        MOD("b", DEPS(), DEPS()),
        MOD("c", DEPS(DEP("b"), DEP("d")), DEPS()),
        MOD("d", DEPS(DEP("e"), DEP("f")), DEPS()),
        MOD("e", DEPS(), DEPS(DEP("f"))),
        MOD("f", DEPS(), DEPS()),
    }};
    ModVersionResolver resolver{};
    const auto resolve_result = resolver.resolve(list, lock, index);
    const auto& sorted = resolve_result.right().sorted_mods();

    REQUIRE(sorted.at(0) == "b");
    REQUIRE(sorted.at(1) == "core");
    REQUIRE(sorted.at(2) == "f");
    REQUIRE(sorted.at(3) == "e");
    REQUIRE(sorted.at(4) == "d");
    REQUIRE(sorted.at(5) == "c");
    REQUIRE(sorted.at(6) == "a");
}
