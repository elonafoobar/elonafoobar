#include "../thirdparty/catch2/catch.hpp"

#include "tests.hpp"
#include "../testing.hpp"
#include "../config_def.hpp"

using namespace std::literals::string_literals;
using namespace elona;

namespace
{
config_def load(const std::string& str)
{
    config_def def;

    std::stringstream ss(str);

    REQUIRE_NOTHROW(def.load(ss, "config_def_test.hcl"));
    return def;
}

bool load_fails(const std::string& str)
{
    config_def def;

    std::stringstream ss(str);

    try
    {
        def.load(ss, "config_def_test.hcl");
    }
    catch (...)
    {
        return true;
    }

    return false;
}
}

TEST_CASE("Test invalid config def format", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
blah = 4
)"));
}

TEST_CASE("Test wrong config def object name", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config {}
)"));
}

TEST_CASE("Test loading blank config def", "[Config: Definition]")
{
    REQUIRE_FALSE(load_fails(R"(
config_def {}
)"));
}

TEST_CASE("Test defining boolean config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = true
}
)");

    REQUIRE(def.is<config_def::config_bool_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<bool>());
    REQUIRE(def.get_default("core.config.foo").as<bool>() == true);
}

TEST_CASE("Test defining integer config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        default = 42
        min = 0
        max = 0
    }
}
)");

    REQUIRE(def.is<config_def::config_int_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<int>());
    REQUIRE(def.get_default("core.config.foo").as<int>() == 42);
}

TEST_CASE("Test defining bare integer", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = 42
}
)"));
}

TEST_CASE("Test defining integer without min", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = 42
    max = 100
}
)"));
}

TEST_CASE("Test defining integer without max", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = 42
    min = 0
}
)"));
}

TEST_CASE("Test defining string config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = "bar"
}
)");

    REQUIRE(def.is<config_def::config_string_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<std::string>());
    REQUIRE(def.get_default("core.config.foo").as<std::string>() == "bar");
}

TEST_CASE("Test defining list config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = ["bar", "baz", "quux"]
}
)");

    REQUIRE(def.is<config_def::config_list_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<hcl::List>());
    auto list = def.get_default("core.config.foo").as<hcl::List>();
    REQUIRE(list.at(0).as<std::string>() == "bar");
    REQUIRE(list.at(1).as<std::string>() == "baz");
    REQUIRE(list.at(2).as<std::string>() == "quux");
}

TEST_CASE("Test defining enum config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.is<config_def::config_enum_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<int>());
    REQUIRE(def.get_default("core.config.foo").as<int>() == 1);
}

TEST_CASE("Test not providing enum variants", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        default = "baz"
    }
}
)"));
}

TEST_CASE("Test not providing enum default", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
    }
}
)"));
}

TEST_CASE("Test providing non-existent enum default", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "hoge"
    }
}
)"));
}

TEST_CASE("Test providing non-string enum variant", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", 42]
        default = "bar"
    }
}
)"));
}

TEST_CASE("Test providing non-string default value in enum", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = 42
    }
}
)"));
}

TEST_CASE("Test providing non-list variants in enum", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "enum"
        variants = 42
        default = "foo"
    }
}
)"));
}

TEST_CASE("Test defining runtime enum config value", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "runtime_enum"
    }
    bar = "baz"
}
)");

    REQUIRE(def.is<config_def::config_enum_def>("core.config.foo"));
    REQUIRE(def.get_default("core.config.foo").is<int>());
    REQUIRE(def.get_default("core.config.foo").as<int>() == 0);
    REQUIRE(def.get_variants("core.config.foo").size() == 0);

    REQUIRE_NOTHROW(def.inject_enum("core.config.foo", {"foo", "bar", "baz"}, 1));

    REQUIRE(def.get_default("core.config.foo").is<int>());
    REQUIRE(def.get_default("core.config.foo").as<int>() == 1);
    auto variants = def.get_variants("core.config.foo");
    REQUIRE(variants.size() == 3);
    REQUIRE(variants.at(0) == "foo");
    REQUIRE(variants.at(1) == "bar");
    REQUIRE(variants.at(2) == "baz");

    REQUIRE_THROWS(def.inject_enum("core.config.bar", {"foo", "bar", "baz"}, 1));
}

TEST_CASE("Test providing invalid default index in injected enum", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "runtime_enum"
    }
}
)");

    REQUIRE_THROWS(def.inject_enum("core.config.foo", {"foo", "bar", "baz"}, 99));
    REQUIRE_THROWS(def.inject_enum("core.config.foo", {"foo", "bar", "baz"}, -1));
}

TEST_CASE("Test error when injecting non-runtime enum", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["foo", "bar", "baz"]
        default = "bar"
    }
}
)");

    REQUIRE_THROWS(def.inject_enum("core.config.foo", {"quux"}, 0));
}

TEST_CASE("Test defining config section", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "section"
        options = {
            bar = false
            baz = "quux"
        }
    }
}
)");

    REQUIRE_THROWS(def.get_default("core.config.foo"));
}

TEST_CASE("Test defining config section with no options", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "section"
    }
}
)"));
}

TEST_CASE("Test defining config section with invalid options", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "section"
        options = "foo"
    }
}
)"));
}


TEST_CASE("Test defining invalid type", "[Config: Definition]")
{
    REQUIRE(load_fails(R"(
config_def {
    foo = {
        type = "bar"
        default = 42
    }
}
)"));
}

TEST_CASE("Test get_variants", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
    hoge = "piyo"
}
)");
    auto variants = def.get_variants("core.config.foo");
    REQUIRE(variants.size() == 3);
    REQUIRE(variants.at(0) == "bar");
    REQUIRE(variants.at(1) == "baz");
    REQUIRE(variants.at(2) == "quux");

    REQUIRE_THROWS(def.get_variants("core.config.hoge"));
}

TEST_CASE("Test get_children", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "section"
        options = {
            bar = false
            baz = "quux"
        }
    }
    hoge = "piyo"
}
)");
    auto children = def.get_children("core.config.foo");
    REQUIRE(children.size() == 2);
    REQUIRE(children.at(0) == "baz");
    REQUIRE(children.at(1) == "bar");

    REQUIRE_THROWS(def.get_children("core.config.hoge"));
}

TEST_CASE("Test get_max/get_min (integer)", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        default = 42
        min = 0
        max = 100
    }
    hoge = "piyo"
}
)");
    REQUIRE(def.get_min("core.config.foo") == 0);
    REQUIRE(def.get_max("core.config.foo") == 100);

    REQUIRE_THROWS(def.get_min("core.config.hoge"));
    REQUIRE_THROWS(def.get_max("core.config.hoge"));
}

TEST_CASE("Test get_max/get_min (enum)", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.get_min("core.config.foo") == 0);
    REQUIRE(def.get_max("core.config.foo") == 2);
}

TEST_CASE("Test definition with extended syntax", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = {
        default = "bar"
    }
}
)");

    REQUIRE(def.get_default("core.config.foo").is<std::string>());
    REQUIRE(def.get_default("core.config.foo").as<std::string>() == "bar");
}

TEST_CASE("Test exists", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = "bar"
}
)");

    REQUIRE(def.exists("core.config.foo") == true);
    REQUIRE(def.exists("core.config.baz") == false);
}


TEST_CASE("Test is_visible", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = "bar"
    baz = {
        default = "quux"
        visible = true
    }
    hoge = {
        default = "piyo"
        visible = false
    }
}
)");

    REQUIRE(def.is_visible("core.config.foo") == true);
    REQUIRE(def.is_visible("core.config.baz") == true);
    REQUIRE(def.is_visible("core.config.hoge") == false);
}

TEST_CASE("Test is_preload", "[Config: Definition]")
{
    config_def def = load(R"(
config_def {
    foo = "bar"
    baz = {
        default = "quux"
        preload = true
    }
    hoge = {
        default = "piyo"
        preload = false
    }
}
)");

    REQUIRE(def.is_preload("core.config.foo") == false);
    REQUIRE(def.is_preload("core.config.baz") == true);
    REQUIRE(def.is_preload("core.config.hoge") == false);
}

TEST_CASE("Test is_valid_enum_variant", "[Config: Definition]")
{
    REQUIRE(false);
}
