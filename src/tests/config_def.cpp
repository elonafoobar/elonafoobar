// TODO don't skip these test!
#if 0
#include "../elona/config/config_def.hpp"

#include "../elona/testing.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;

namespace
{

ConfigDef load(const std::string& str)
{
    ConfigDef def;

    std::stringstream ss(str);

    REQUIRE_NOTHROW(def.load(ss, "spec_test.hcl", "spec_test"));
    return def;
}
} // namespace

TEST_CASE("Test metadata: visible", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
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

    REQUIRE(def.get_metadata("spec_test.foo").visible == true);
    REQUIRE(def.get_metadata("spec_test.baz").visible == true);
    REQUIRE(def.get_metadata("spec_test.hoge").visible == false);
}

TEST_CASE("Test metadata: preload", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
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

    REQUIRE(def.get_metadata("spec_test.foo").preload == false);
    REQUIRE(def.get_metadata("spec_test.baz").preload == true);
    REQUIRE(def.get_metadata("spec_test.hoge").preload == false);
}

TEST_CASE("Test metadata: translate_variants", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
    foo = "bar"
    baz = {
        default = "quux"
        translate_variants = true
    }
    hoge = {
        default = "piyo"
        translate_variants = false
    }
}
)");

    REQUIRE(def.get_metadata("spec_test.foo").translate_variants == true);
    REQUIRE(def.get_metadata("spec_test.baz").translate_variants == true);
    REQUIRE(def.get_metadata("spec_test.hoge").translate_variants == false);
}

TEST_CASE("Test metadata: platform", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
    foo = "bar"
    baz = {
        default = "quux"
        platform = "desktop"
    }
    hoge = {
        default = "piyo"
        platform = "android"
    }
    fuga = {
        default = "hogera"
        platform = "blah"
    }
}
)");

    REQUIRE(
        def.get_metadata("spec_test.foo").platform == ConfigDef::Platform::all);
    REQUIRE(
        def.get_metadata("spec_test.baz").platform ==
        ConfigDef::Platform::desktop);
    REQUIRE(
        def.get_metadata("spec_test.hoge").platform ==
        ConfigDef::Platform::android);
    REQUIRE(
        def.get_metadata("spec_test.fuga").platform ==
        ConfigDef::Platform::all);
}

TEST_CASE("Test metadata: platform_default", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
    foo = false
    bar = {
        default = "baz"
        platform_default {
            desktop = "hoge"
        }
    }
    baz = {
        default = "quux"
        platform_default {
            android = "fuga"
        }
    }
}
)");

    REQUIRE(
        static_cast<bool>(def.get_metadata("spec_test.foo").default_value) ==
        false);
    REQUIRE(
        def.get_metadata("spec_test.bar").default_value->as<std::string>() ==
        "hoge");
    REQUIRE(
        static_cast<bool>(def.get_metadata("spec_test.baz").default_value) ==
        false);
}

TEST_CASE("Test metadata: is_visible()", "[Config: Definition]")
{
    ConfigDef def = load(R"(
config {
    foo = "bar"
    baz = {
        default = "quux"
        platform = "desktop"
    }
    hoge = {
        default = "piyo"
        platform = "android"
    }
    fuga = {
        default = "hogera"
        platform = "blah"
    }
}
)");

    REQUIRE(def.get_metadata("spec_test.foo").is_visible() == true);
    REQUIRE(def.get_metadata("spec_test.hoge").is_visible() == false);
    REQUIRE(def.get_metadata("spec_test.baz").is_visible() == true);
}
#endif
