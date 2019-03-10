#include "../thirdparty/catch2/catch.hpp"

#include <iostream>
#include "../elona/spec.hpp"

using namespace std::literals::string_literals;
using namespace elona;

class TestSpec : public spec::Object
{
public:
    TestSpec()
        : spec::Object("test")
    {
    }
};

namespace
{
TestSpec load(const std::string& str)
{
    TestSpec def;

    std::stringstream ss(str);

    REQUIRE_NOTHROW(def.load(ss, "spec_test.hcl", "spec_test"));
    return def;
}

bool load_fails(const std::string& str)
{
    TestSpec def;

    std::stringstream ss(str);

    try
    {
        def.load(ss, "spec_test.hcl", "spec_test");
    }
    catch (...)
    {
        return true;
    }

    return false;
}
} // namespace

TEST_CASE("Test invalid spec format", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
blah = 4
)"));
}

TEST_CASE("Test invalid spec object name", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
config {}
)"));
}

TEST_CASE("Test loading blank spec", "[Spec: Definition]")
{
    REQUIRE_FALSE(load_fails(R"(
test {}
)"));
}

TEST_CASE("testining boolean config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = true
}
)");

    REQUIRE(def.is<spec::BoolDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<bool>());
    REQUIRE(def.get_default("spec_test.foo").as<bool>() == true);
}

TEST_CASE("testining integer config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        default = 42
        min = 0
        max = 0
    }
}
)");

    REQUIRE(def.is<spec::IntDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<int>());
    REQUIRE(def.get_default("spec_test.foo").as<int>() == 42);
}

TEST_CASE("testining bare integer", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = 42
}
)"));
}

TEST_CASE("testining integer without min", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = 42
    max = 100
}
)"));
}

TEST_CASE("testining integer without max", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = 42
    min = 0
}
)"));
}

TEST_CASE("testining string config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = "bar"
}
)");

    REQUIRE(def.is<spec::StringDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<std::string>());
    REQUIRE(def.get_default("spec_test.foo").as<std::string>() == "bar");
}

TEST_CASE("testining list config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = ["bar", "baz", "quux"]
}
)");

    REQUIRE(def.is<spec::ListDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<hcl::List>());
    auto list = def.get_default("spec_test.foo").as<hcl::List>();
    REQUIRE(list.at(0).as<std::string>() == "bar");
    REQUIRE(list.at(1).as<std::string>() == "baz");
    REQUIRE(list.at(2).as<std::string>() == "quux");
}

TEST_CASE("testining enum config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.is<spec::EnumDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<std::string>());
    REQUIRE(def.get_default("spec_test.foo").as<std::string>() == "baz");
}

TEST_CASE("Test not providing enum variants", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        default = "baz"
    }
}
)"));
}

TEST_CASE("Test not providing enum default", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
    }
}
)"));
}

TEST_CASE("Test providing non-existent enum default", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "hoge"
    }
}
)"));
}

TEST_CASE("Test providing non-string enum variant", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", 42]
        default = "bar"
    }
}
)"));
}

TEST_CASE(
    "Test providing non-string default value in enum",
    "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = 42
    }
}
)"));
}

TEST_CASE("Test providing non-list variants in enum", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "enum"
        variants = 42
        default = "foo"
    }
}
)"));
}

TEST_CASE("testining runtime enum config value", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "runtime_enum"
    }
    bar = "baz"
}
)");

    REQUIRE(def.is<spec::EnumDef>("spec_test.foo"));
    REQUIRE(def.get_default("spec_test.foo").is<std::string>());
    REQUIRE(
        def.get_default("spec_test.foo").as<std::string>() == "__unknown__");
    REQUIRE(def.get_variants("spec_test.foo").size() == 1);

    REQUIRE_NOTHROW(
        def.inject_enum("spec_test.foo", {"foo", "bar", "baz"}, "baz"));

    REQUIRE(def.get_default("spec_test.foo").is<std::string>());
    REQUIRE(def.get_default("spec_test.foo").as<std::string>() == "baz");
    auto variants = def.get_variants("spec_test.foo");
    REQUIRE(variants.size() == 4);
    REQUIRE(variants.at(0) == "__unknown__");
    REQUIRE(variants.at(1) == "foo");
    REQUIRE(variants.at(2) == "bar");
    REQUIRE(variants.at(3) == "baz");

    REQUIRE_THROWS(
        def.inject_enum("spec_test.bar", {"foo", "bar", "baz"}, "bar"));
}

TEST_CASE(
    "Test providing invalid default index in injected enum",
    "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "runtime_enum"
    }
}
)");

    REQUIRE_THROWS(
        def.inject_enum("spec_test.foo", {"foo", "bar", "baz"}, "asdfg"));
    REQUIRE_THROWS(def.inject_enum("spec_test.foo", {"foo", "bar", "baz"}, ""));
}

TEST_CASE("Test error when injecting non-runtime enum", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "enum"
        variants = ["foo", "bar", "baz"]
        default = "bar"
    }
}
)");

    REQUIRE_THROWS(def.inject_enum("spec_test.foo", {"quux"}, "quux"));
}

TEST_CASE("testining config section", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "section"
        options = {
            bar = false
            baz = "quux"
        }
    }
}
)");

    REQUIRE_THROWS(def.get_default("spec_test.foo"));
}

TEST_CASE("testining config section with no options", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "section"
    }
}
)"));
}

TEST_CASE("testining config section with invalid options", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "section"
        options = "foo"
    }
}
)"));
}


TEST_CASE("testining invalid type", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test {
    foo = {
        type = "bar"
        default = 42
    }
}
)"));
}

TEST_CASE("Test get_variants", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
    hoge = "piyo"
}
)");
    auto variants = def.get_variants("spec_test.foo");
    REQUIRE(variants.size() == 3);
    REQUIRE(variants.at(0) == "bar");
    REQUIRE(variants.at(1) == "baz");
    REQUIRE(variants.at(2) == "quux");

    REQUIRE_THROWS(def.get_variants("spec_test.hoge"));
}

TEST_CASE("Test get_children", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo {
        type = "section"
        options = {
            bar = false
            baz = "quux"
            hoge = "fuga"
            piyo = true
        }
    }
}
)");
    auto children = def.get_children("spec_test.foo");
    REQUIRE(children.size() == 4);
    REQUIRE(children.at(0) == "bar");
    REQUIRE(children.at(1) == "baz");
    REQUIRE(children.at(2) == "hoge");
    REQUIRE(children.at(3) == "piyo");

    REQUIRE_THROWS(def.get_children("spec_test.hoge"));
}

TEST_CASE("Test get_max/get_min (integer)", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        default = 42
        min = 0
        max = 100
    }
    hoge = "piyo"
}
)");
    REQUIRE(def.get_min("spec_test.foo") == 0);
    REQUIRE(def.get_max("spec_test.foo") == 100);

    REQUIRE_THROWS(def.get_min("spec_test.hoge"));
    REQUIRE_THROWS(def.get_max("spec_test.hoge"));
}

TEST_CASE("Test get_max/get_min (enum)", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.get_min("spec_test.foo") == 0);
    REQUIRE(def.get_max("spec_test.foo") == 2);
}

TEST_CASE("testinition with extended syntax", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = {
        default = "bar"
    }
}
)");

    REQUIRE(def.get_default("spec_test.foo").is<std::string>());
    REQUIRE(def.get_default("spec_test.foo").as<std::string>() == "bar");
}

TEST_CASE("Test exists", "[Spec: Definition]")
{
    TestSpec def = load(R"(
test {
    foo = "bar"
}
)");

    REQUIRE(def.exists("spec_test.foo") == true);
    REQUIRE(def.exists("spec_test.baz") == false);
}
