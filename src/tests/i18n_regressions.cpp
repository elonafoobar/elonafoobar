#include "../thirdparty/catch2/catch.hpp"

#include "../i18n.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../testing.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;

TEST_CASE("test foodname", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    testing::set_japanese();

    {
        item& item = testing::create_item(260);
        update_slight();

        item.param2 = 1;
        REQUIRE(i18n::fmt_hil("${itemname(_1)}", item) == u8"恐怖のパン");
        item.param2 = 8;
        REQUIRE(i18n::fmt_hil("${itemname(_1)}", item) == u8"カレーパン");
    }
    {
        item& item = testing::create_item(573);
        update_slight();

        item.param2 = 1;
        REQUIRE(
            i18n::fmt_hil("${itemname(_1)}", item) == u8"グロテスクな鳥の卵");
        item.param2 = 8;
        REQUIRE(
            i18n::fmt_hil("${itemname(_1)}", item) == u8"鳥のレアチーズケーキ");
        item.subname = 3;
        REQUIRE(
            i18n::fmt_hil("${itemname(_1)}", item)
            == u8"プチのレアチーズケーキ");
    }
}
