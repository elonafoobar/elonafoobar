#include "../thirdparty/catch2/catch.hpp"

#include "../config.hpp"
#include "../config_def.hpp"
#include "../testing.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;

namespace
{
config load(
    const std::string& def_str,
    const std::string& config_str,
    bool preload = false)
{
    config_def def;
    config conf;

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
    config_def def;
    config conf;

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
    REQUIRE(load_fails(R"(config def {})", R"(blah = 42)"));
}

TEST_CASE("Test invalid config object name", "[Config: Loading]")
{
    REQUIRE(load_fails(R"(config def {})", R"(conf {})"));
}

TEST_CASE("Test loading blank config", "[Config: Loading]")
{
    REQUIRE_FALSE(load_fails(R"(config def {})", R"(config core {})"));
}

TEST_CASE("Test loading config with unknown value", "[Config: Loading]")
{
    REQUIRE(load_fails(R"(config def {})", R"(config core {foo = "bar"})"));
}

TEST_CASE("Test loading config with differing type", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(config def {foo = false})", R"(config core {foo = "bar"})"));
}

TEST_CASE("Test loading config with invalid enum variant", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(
config def {
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
    config conf = load(
        R"(
config def {
    foo = false
    bar = "baz"
})",
        R"(config core {})");

    REQUIRE(conf.get<bool>("core.config.foo") == false);
    REQUIRE(conf.get<std::string>("core.config.bar") == "baz");
}

TEST_CASE("Test loading config with out-of-bounds value", "[Config: Loading]")
{
    config conf = load(
        R"(
config def {
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

    REQUIRE(conf.get<int>("core.config.foo") == 100);
    REQUIRE(conf.get<int>("core.config.bar") == 0);
}

TEST_CASE("Test value getter", "[Config: Loading]")
{
    config conf = load(
        R"(
config def {
    foo = "bar"
})",
        R"(config core {})");

    REQUIRE_NOTHROW(
        conf.bind_getter("core.config.foo", [&]() { return "hoge"; }));
    REQUIRE_THROWS(
        conf.bind_getter("core.config.baz", [&]() { return "hoge"; }));

    REQUIRE(conf.get<std::string>("core.config.foo") == "hoge");
    REQUIRE_THROWS(conf.get<std::string>("core.config.baz"));
}

TEST_CASE("Test value setter", "[Config: Loading]")
{
    config conf = load(
        R"(
config def {
    foo = "bar"
})",
        R"(config core {})");

    std::string result = "";

    REQUIRE_NOTHROW(conf.bind_setter<std::string>(
        "core.config.foo", [&](auto value) { result = value; }));
    REQUIRE_THROWS(conf.bind_setter<std::string>(
        "core.config.baz", [&](auto value) { result = value; }));

    REQUIRE_NOTHROW(conf.set("core.config.foo", "hoge"));
    REQUIRE(result == "hoge");

    result = "";
    REQUIRE_THROWS(conf.set("core.config.baz", "hoge"));
    REQUIRE(result == "");
}

TEST_CASE("Test invalid injected enum type", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(
config def {
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
    config conf = load(
        R"(
config def {
    foo = {
        type = "runtime_enum"
    }
})",
        R"(
config core {
    foo = "hoge"
}
)");

    REQUIRE_NOTHROW(
        conf.inject_enum("core.config.foo", {"foo", "bar", "baz"}, "baz"));
    REQUIRE(conf.get<std::string>("core.config.foo") == "baz");
}
