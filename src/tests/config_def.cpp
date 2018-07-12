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

    REQUIRE_NOTHROW(def.load(ss, "spec_test.hcl"));
    return def;
}
} // namespace

TEST_CASE("Test metadata: visible", "[Config: Definition]")
{
    config_def def = load(R"(
config def {
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

    REQUIRE(def.get_metadata("core.config.foo").preload == true);
    REQUIRE(def.get_metadata("core.config.baz").preload == true);
    REQUIRE(def.get_metadata("core.config.hoge").preload == false);
}

TEST_CASE("Test metadata: preload", "[Config: Definition]")
{
    config_def def = load(R"(
config def {
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

    REQUIRE(def.get_metadata("core.config.foo").preload == false);
    REQUIRE(def.get_metadata("core.config.baz").preload == true);
    REQUIRE(def.get_metadata("core.config.hoge").preload == false);
}

TEST_CASE("Test metadata: translate_variants", "[Config: Definition]")
{
    config_def def = load(R"(
config def {
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

    REQUIRE(def.get_metadata("core.config.foo").translate_variants == true);
    REQUIRE(def.get_metadata("core.config.baz").translate_variants == true);
    REQUIRE(def.get_metadata("core.config.hoge").translate_variants == false);
}
