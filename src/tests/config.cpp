#include "../thirdparty/catch2/catch.hpp"

#include "../elona/config/config.hpp"
#include "../elona/config/config_def.hpp"
#include "../elona/testing.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;

namespace
{
Config load(
    const std::string& def_str,
    const std::string& config_str,
    bool preload = false)
{
    ConfigDef def;
    Config conf;

    {
        std::stringstream ss(def_str);
        REQUIRE_NOTHROW(def.load(ss, "config_def_test.hcl"));
    }

    {
        std::stringstream ss(config_str);
        REQUIRE_NOTHROW(conf.init(def));
        REQUIRE_NOTHROW(conf.load(ss, "config_test.hcl", preload));
    }

    return conf;
}

bool load_fails(
    const std::string& def_str,
    const std::string& config_str,
    bool preload = false)
{
    ConfigDef def;
    Config conf;

    {
        std::stringstream ss(def_str);
        REQUIRE_NOTHROW(def.load(ss, "config_def_test.hcl"));
    }

    {
        std::stringstream ss(config_str);
        try
        {
            conf.init(def);
            conf.load(ss, "config_test.hcl", preload);
        }
        catch (...)
        {
            return true;
        }
    }

    return false;
}
} // namespace

TEST_CASE("Test invalid config format", "[Config: Loading]")
{
    REQUIRE(load_fails(R"(config {})", R"(blah = 42)"));
}

TEST_CASE("Test invalid config object name", "[Config: Loading]")
{
    REQUIRE(load_fails(R"(config {})", R"(conf {})"));
}

TEST_CASE("Test loading blank config", "[Config: Loading]")
{
    REQUIRE_FALSE(load_fails(R"(config {})", R"(config core {})"));
}

TEST_CASE("Test loading config with differing type", "[Config: Loading]")
{
    REQUIRE(
        load_fails(R"(config {foo = false})", R"(config core {foo = "bar"})"));
}

TEST_CASE("Test loading config with invalid enum variant", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(
config {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)",
        R"(config core {foo = "hoge"})"));
}

TEST_CASE("Test fallback to default config value", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = false
    bar = "baz"
})",
        R"(config core {})");

    REQUIRE(conf.get<bool>("core.foo") == false);
    REQUIRE(conf.get<std::string>("core.bar") == "baz");
}

TEST_CASE("Test loading config with out-of-bounds value", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = {
        default = 42
        min = 0
        max = 100
    }
    bar = {
        default = 42
        min = 0
        max = 100
    }
})",
        R"(config core {
    foo = 101
    bar = -1
})");

    REQUIRE(conf.get<int>("core.foo") == 100);
    REQUIRE(conf.get<int>("core.bar") == 0);
}

TEST_CASE("Test value getter", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = "bar"
})",
        R"(config core {})");

    REQUIRE_NOTHROW(conf.bind_getter("core.foo", [&]() { return "hoge"; }));
    REQUIRE_THROWS(conf.bind_getter("core.baz", [&]() { return "hoge"; }));

    REQUIRE(conf.get<std::string>("core.foo") == "hoge");
    REQUIRE_THROWS(conf.get<std::string>("core.baz"));
}

TEST_CASE("Test value setter", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = "bar"
})",
        R"(config core {})");

    std::string result = "";

    REQUIRE_NOTHROW(conf.bind_setter<std::string>(
        "core.foo", [&](auto value) { result = value; }));
    REQUIRE_THROWS(conf.bind_setter<std::string>(
        "core.baz", [&](auto value) { result = value; }));

    REQUIRE_NOTHROW(conf.set("core.foo", "hoge"));
    REQUIRE(result == "hoge");

    result = "";
    REQUIRE_THROWS(conf.set("core.baz", "hoge"));
    REQUIRE(result == "");
}

TEST_CASE("Test invalid injected enum type", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(
config {
    foo = {
        type = "runtime_enum"
    }
})",
        R"(
config core {
    foo = 42
}
)"));
}

TEST_CASE("Test invalid injected enum value", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = {
        type = "runtime_enum"
    }
})",
        R"(
config core {
    foo = "hoge"
}
)");

    REQUIRE_NOTHROW(conf.inject_enum("core.foo", {"foo", "bar", "baz"}, "baz"));
    REQUIRE(conf.get<std::string>("core.foo") == "baz");
}
