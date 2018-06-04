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

TEST_CASE("test formats", "[I18N: Format]")
{
    REQUIRE(i18n::fmt_hil("${_1}", 1) == u8"1"s);
    REQUIRE(i18n::fmt_hil("${_1}", u8"foo"s) == u8"foo"s);
    REQUIRE(i18n::fmt_hil("${_1} ${_2}", u8"foo"s, 2) == u8"foo 2"s);
    REQUIRE(i18n::fmt_hil("${_1} ${_1}", u8"foo"s, 2) == u8"foo foo"s);
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


TEST_CASE("test i18n store loading", "[I18N: Store]")
{
    i18n::store store;

    std::stringstream ss(R"(
locale {
    foo = "bar"
}
)");

    REQUIRE_NOTHROW(store.load(ss, "test.hcl"));
    REQUIRE(store.get(u8"core.locale.foo") == u8"bar");
}
