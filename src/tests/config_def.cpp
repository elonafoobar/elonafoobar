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

TEST_CASE("Test is_visible", "[Config: Definition]")
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

    REQUIRE(def.is_visible("core.config.foo") == true);
    REQUIRE(def.is_visible("core.config.baz") == true);
    REQUIRE(def.is_visible("core.config.hoge") == false);
}

TEST_CASE("Test is_preload", "[Config: Definition]")
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

    REQUIRE(def.is_preload("core.config.foo") == false);
    REQUIRE(def.is_preload("core.config.baz") == true);
    REQUIRE(def.is_preload("core.config.hoge") == false);
}
