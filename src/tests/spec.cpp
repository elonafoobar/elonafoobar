#include "../thirdparty/catch2/catch.hpp"

#include "../spec.hpp"

using namespace std::literals::string_literals;
using namespace elona;

class test_spec : public spec::object
{
public:
    test_spec() : spec::object("test") {}
};

namespace
{
test_spec load(const std::string& str)
{
    test_spec def;

    std::stringstream ss(str);

    REQUIRE_NOTHROW(def.load(ss, "spec_test.hcl"));
    return def;
}

bool load_fails(const std::string& str)
{
    test_spec def;

    std::stringstream ss(str);

    try
    {
        def.load(ss, "spec_test.hcl");
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
test def {}
)"));
}

TEST_CASE("Test defining boolean config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = true
}
)");

    REQUIRE(def.is<spec::bool_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<bool>());
    REQUIRE(def.get_default("core.test.foo").as<bool>() == true);
}

TEST_CASE("Test defining integer config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        default = 42
        min = 0
        max = 0
    }
}
)");

    REQUIRE(def.is<spec::int_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<int>());
    REQUIRE(def.get_default("core.test.foo").as<int>() == 42);
}

TEST_CASE("Test defining bare integer", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = 42
}
)"));
}

TEST_CASE("Test defining integer without min", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = 42
    max = 100
}
)"));
}

TEST_CASE("Test defining integer without max", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = 42
    min = 0
}
)"));
}

TEST_CASE("Test defining string config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = "bar"
}
)");

    REQUIRE(def.is<spec::string_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<std::string>());
    REQUIRE(def.get_default("core.test.foo").as<std::string>() == "bar");
}

TEST_CASE("Test defining list config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = ["bar", "baz", "quux"]
}
)");

    REQUIRE(def.is<spec::list_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<hcl::List>());
    auto list = def.get_default("core.test.foo").as<hcl::List>();
    REQUIRE(list.at(0).as<std::string>() == "bar");
    REQUIRE(list.at(1).as<std::string>() == "baz");
    REQUIRE(list.at(2).as<std::string>() == "quux");
}

TEST_CASE("Test defining enum config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.is<spec::enum_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<std::string>());
    REQUIRE(def.get_default("core.test.foo").as<std::string>() == "baz");
}

TEST_CASE("Test not providing enum variants", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
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
test def {
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
test def {
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
test def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", 42]
        default = "bar"
    }
}
)"));
}

TEST_CASE("Test providing non-string default value in enum", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
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
test def {
    foo = {
        type = "enum"
        variants = 42
        default = "foo"
    }
}
)"));
}

TEST_CASE("Test defining runtime enum config value", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "runtime_enum"
    }
    bar = "baz"
}
)");

    REQUIRE(def.is<spec::enum_def>("core.test.foo"));
    REQUIRE(def.get_default("core.test.foo").is<std::string>());
    REQUIRE(def.get_default("core.test.foo").as<std::string>() == "__unknown__");
    REQUIRE(def.get_variants("core.test.foo").size() == 1);

    REQUIRE_NOTHROW(def.inject_enum("core.test.foo", {"foo", "bar", "baz"}, "baz"));

    REQUIRE(def.get_default("core.test.foo").is<std::string>());
    REQUIRE(def.get_default("core.test.foo").as<std::string>() == "baz");
    auto variants = def.get_variants("core.test.foo");
    REQUIRE(variants.size() == 3);
    REQUIRE(variants.at(0) == "foo");
    REQUIRE(variants.at(1) == "bar");
    REQUIRE(variants.at(2) == "baz");

    REQUIRE_THROWS(def.inject_enum("core.test.bar", {"foo", "bar", "baz"}, "bar"));
}

TEST_CASE("Test providing invalid default index in injected enum", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "runtime_enum"
    }
}
)");

    REQUIRE_THROWS(def.inject_enum("core.test.foo", {"foo", "bar", "baz"}, "asdfg"));
    REQUIRE_THROWS(def.inject_enum("core.test.foo", {"foo", "bar", "baz"}, ""));
}

TEST_CASE("Test error when injecting non-runtime enum", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "enum"
        variants = ["foo", "bar", "baz"]
        default = "bar"
    }
}
)");

    REQUIRE_THROWS(def.inject_enum("core.test.foo", {"quux"}, "quux"));
}

TEST_CASE("Test defining config section", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "section"
        options = {
            bar = false
            baz = "quux"
        }
    }
}
)");

    REQUIRE_THROWS(def.get_default("core.test.foo"));
}

TEST_CASE("Test defining config section with no options", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = {
        type = "section"
    }
}
)"));
}

TEST_CASE("Test defining config section with invalid options", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = {
        type = "section"
        options = "foo"
    }
}
)"));
}


TEST_CASE("Test defining invalid type", "[Spec: Definition]")
{
    REQUIRE(load_fails(R"(
test def {
    foo = {
        type = "bar"
        default = 42
    }
}
)"));
}

TEST_CASE("Test get_variants", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
    hoge = "piyo"
}
)");
    auto variants = def.get_variants("core.test.foo");
    REQUIRE(variants.size() == 3);
    REQUIRE(variants.at(0) == "bar");
    REQUIRE(variants.at(1) == "baz");
    REQUIRE(variants.at(2) == "quux");

    REQUIRE_THROWS(def.get_variants("core.test.hoge"));
}

TEST_CASE("Test get_children", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
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
    auto children = def.get_children("core.test.foo");
    REQUIRE(children.size() == 2);
    REQUIRE(children.at(0) == "baz");
    REQUIRE(children.at(1) == "bar");

    REQUIRE_THROWS(def.get_children("core.test.hoge"));
}

TEST_CASE("Test get_max/get_min (integer)", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        default = 42
        min = 0
        max = 100
    }
    hoge = "piyo"
}
)");
    REQUIRE(def.get_min("core.test.foo") == 0);
    REQUIRE(def.get_max("core.test.foo") == 100);

    REQUIRE_THROWS(def.get_min("core.test.hoge"));
    REQUIRE_THROWS(def.get_max("core.test.hoge"));
}

TEST_CASE("Test get_max/get_min (enum)", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        type = "enum"
        variants = ["bar", "baz", "quux"]
        default = "baz"
    }
}
)");

    REQUIRE(def.get_min("core.test.foo") == 0);
    REQUIRE(def.get_max("core.test.foo") == 2);
}

TEST_CASE("Test definition with extended syntax", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = {
        default = "bar"
    }
}
)");

    REQUIRE(def.get_default("core.test.foo").is<std::string>());
    REQUIRE(def.get_default("core.test.foo").as<std::string>() == "bar");
}

TEST_CASE("Test exists", "[Spec: Definition]")
{
    test_spec def = load(R"(
test def {
    foo = "bar"
}
)");

    REQUIRE(def.exists("core.test.foo") == true);
    REQUIRE(def.exists("core.test.baz") == false);
}
