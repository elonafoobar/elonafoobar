#include "../thirdparty/catch2/catch.hpp"

#include "tests.hpp"
#include "../testing.hpp"
#include "../character.hpp"
#include "../i18n.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../variables.hpp"
#include <sstream>

using namespace std::literals::string_literals;
using namespace elona;

i18n::store load(const std::string& str)
{
    i18n::store store;

    std::stringstream ss(str);

    REQUIRE_NOTHROW(store.load(ss, "test.hcl"));
    return store;
}

TEST_CASE("test formats", "[I18N: Format]")
{
    REQUIRE(i18n::fmt_hil("${_1}", 1) == u8"1"s);
    REQUIRE(i18n::fmt_hil("${_1}", u8"foo"s) == u8"foo"s);
    REQUIRE(i18n::fmt_hil("${_1} ${_2}", u8"foo"s, 2) == u8"foo 2"s);
    REQUIRE(i18n::fmt_hil("${_1} ${_1}", u8"foo"s, 2) == u8"foo foo"s);
    REQUIRE(i18n::fmt_hil("You see ${_1}.", u8"Palmia") == u8"You see Palmia."s);
    REQUIRE(i18n::fmt_hil("You see ${_1} the ${_2}.", u8"Adam" , u8"rock thrower")
            == u8"You see Adam the rock thrower."s);
}

TEST_CASE("test format chara", "[I18N: Format]")
{
    testing::start_in_debug_map();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    character& chara = elona::cdata[elona::rc];

    REQUIRE(i18n::fmt_hil("${_1}", chara) == u8"<character: "s + std::to_string(chara.index) + u8">"s);
}

TEST_CASE("test format item", "[I18N: Format]")
{
    testing::start_in_debug_map();
    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
    item& i = elona::inv[elona::ci];

    REQUIRE(i18n::fmt_hil("${_1}", i) == u8"<item: "s + std::to_string(i.index) + u8">"s);
}

TEST_CASE("test format character by function", "[I18N: Format]")
{
    testing::start_in_debug_map();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    character& chara = elona::cdata[elona::rc];

    REQUIRE(i18n::fmt_hil("${name(_1)}", chara) == u8"何か"s);
    REQUIRE(i18n::fmt_hil("${basename(_1)}", chara) == u8"プチ"s);
}

TEST_CASE("test format item by function", "[I18N: Format]")
{
    testing::start_in_debug_map();
    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
    item& i = elona::inv[elona::ci];

    REQUIRE(i18n::fmt_hil("${name(_1)}", i) == u8"3個のプチトロ"s);
    REQUIRE(i18n::fmt_hil("${basename(_1)}", i) == u8"プチトロ"s);
}


TEST_CASE("test i18n builtin: s()", "[I18N: Builtins]")
{
    testing::start_in_debug_map();
    set_english();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    character& chara = elona::cdata[elona::rc];
    TODO normalize randomization

    REQUIRE(i18n::fmt_hil("${name(_1)} go${s(_1, true)} to hell.", chara) == u8"The putit goes to hell.")
}


TEST_CASE("test i18n store literal", "[I18N: Store]")
{
    i18n::store store = load(R"(
locale {
    foo = "bar"
}
)");

    REQUIRE(store.get(u8"core.locale.foo") == u8"bar");
    REQUIRE(store.get(u8"core.locale.baz") == u8"Unknown ID: core.locale.baz");
}

TEST_CASE("test i18n store nested literal", "[I18N: Store]")
{
    i18n::store store = load(R"(
locale {
    foo {
        bar = "baz"
    }
}
)");

    REQUIRE(store.get(u8"core.locale.foo.bar") == u8"baz");
}

TEST_CASE("test i18n store multiple nested literals", "[I18N: Store]")
{
    i18n::store store = load(R"(
locale {
    foo {
        bar = "baz"
    }
    hoge {
        fuga = "piyo"
    }
}
)");

    REQUIRE(store.get(u8"core.locale.foo.bar") == u8"baz");
    REQUIRE(store.get(u8"core.locale.hoge.fuga") == u8"piyo");
}

TEST_CASE("test i18n store interpolation", "[I18N: Store]")
{
    i18n::store store = load(R"(
locale {
    foo = "bar: ${_1}"
}
)");

    REQUIRE(store.get(u8"core.locale.foo") == u8"bar: ");
    REQUIRE(store.get(u8"core.locale.foo", 12) == u8"bar: 12");
    REQUIRE(store.get(u8"core.locale.foo", u8"baz") == u8"bar: baz");
}

TEST_CASE("test i18n store multiple interpolation", "[I18N: Store]")
{
    i18n::store store = load(R"(
locale {
    foo = "${_2}: ${_1}"
}
)");

    REQUIRE(store.get(u8"core.locale.foo") == u8": ");
    REQUIRE(store.get(u8"core.locale.foo", 42) == u8": 42");
    REQUIRE(store.get(u8"core.locale.foo", 12, u8"bar") == u8"bar: 12");
    REQUIRE(store.get(u8"core.locale.foo", u8"bar", u8"baz") == u8"baz: bar");
}

