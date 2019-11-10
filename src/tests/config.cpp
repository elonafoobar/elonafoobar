// TODO don't skip these test!
#if 0
#include "../thirdparty/catch2/catch.hpp"

#include "../elona/config/config.hpp"
#include "../elona/config/config_def.hpp"
#include "../elona/testing.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;



namespace
{

Config load(const std::string& def_str, const std::string& config_str)
{
    Config config;

    {
        std::stringstream ss(def_str);
        REQUIRE_NOTHROW(config.load_def(ss, "config_test"));
    }

    {
        std::stringstream ss(config_str);
        REQUIRE_NOTHROW(config.load(ss, "config_test.json"));
    }

    return config;
}



bool load_fails(const std::string& def_str, const std::string& config_str)
{
    Config config;

    {
        std::stringstream ss(def_str);
        REQUIRE_NOTHROW(config.load_def(ss, "config_test"));
    }

    {
        std::stringstream ss(config_str);
        try
        {
            config.load(ss, "config_test.json");
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
    REQUIRE(load_fails(R"(config {})", R"(42)"));
    REQUIRE(load_fails(R"(config {})", R"('string')"));
}



TEST_CASE("Test loading blank config", "[Config: Loading]")
{
    REQUIRE_FALSE(load_fails(R"(config {})", R"({ config_test: {} })"));
}



TEST_CASE("Test loading config with differing type", "[Config: Loading]")
{
    REQUIRE(load_fails(
        R"(config {foo = false})", R"({ config_test: { foo: "bar" } })"));
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
        R"({ config_test: { foo: "hoge" } })"));
}



TEST_CASE("Test fallback to default config value", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = false
    bar = "baz"
})",
        R"({ config_test: {} })");

    REQUIRE(conf.get<bool>("config_test.foo") == false);
    REQUIRE(conf.get<std::string>("config_test.bar") == "baz");
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
        R"({
  config_test: {
    foo: 101,
    bar: -1,
  }
})");

    REQUIRE(conf.get<int>("config_test.foo") == 100);
    REQUIRE(conf.get<int>("config_test.bar") == 0);
}



TEST_CASE("Test value getter", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = "bar"
})",
        R"({ config_test: {} })");

    REQUIRE_NOTHROW(
        conf.bind_getter("config_test.foo", [&]() { return "hoge"; }));
    REQUIRE_THROWS(
        conf.bind_getter("config_test.baz", [&]() { return "hoge"; }));

    REQUIRE(conf.get<std::string>("config_test.foo") == "hoge");
    REQUIRE_THROWS(conf.get<std::string>("config_test.baz"));
}



TEST_CASE("Test value setter", "[Config: Loading]")
{
    Config conf = load(
        R"(
config {
    foo = "bar"
})",
        R"({ config_test: {} })");

    std::string result = "";

    REQUIRE_NOTHROW(conf.bind_setter<std::string>(
        "config_test.foo", [&](auto value) { result = value; }));
    REQUIRE_THROWS(conf.bind_setter<std::string>(
        "config_test.baz", [&](auto value) { result = value; }));

    REQUIRE_NOTHROW(conf.set("config_test.foo", "hoge"));
    REQUIRE(result == "hoge");

    result = "";
    REQUIRE_THROWS(conf.set("config_test.baz", "hoge"));
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
        R"({
  config_test: {
    foo: 42
  }
})"));
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
        R"({
  config_test: {
    foo: "hoge"
  }
})");

    REQUIRE_NOTHROW(
        conf.inject_enum("config_test.foo", {"foo", "bar", "baz"}, "baz"));
    REQUIRE(conf.get<std::string>("config_test.foo") == "baz");
}
#endif
