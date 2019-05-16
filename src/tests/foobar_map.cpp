#include "../thirdparty/catch2/catch.hpp"

#include "../elona/map.hpp"
#include "../elona/map_cell.hpp"
#include "../elona/mapgen.hpp"
#include "../elona/testing.hpp"
#include "tests.hpp"

#include "../elona/foobar_map/init_map.hpp"
#include "../elona/foobar_map/tsx_exporter.hpp"

using namespace elona;
using namespace elona::testing;


TEST_CASE("Test foobar map is instantiated correctly", "[FoobarMap]")
{
    testing::reset_state();

    fmp::export_tsx(
        "core.chara", "/home/ruin/.tiled/Elona_foobar/chara.tsx", 8, {});
    fmp::export_tsx(
        "core.item", "/home/ruin/.tiled/Elona_foobar/item.tsx", 8, {});
    fmp::export_tsx(
        "core.map_object",
        "/home/ruin/.tiled/Elona_foobar/map_object.tsx",
        8,
        {});
    fmp::export_tsx(
        "core.map_chip",
        "/home/ruin/.tiled/Elona_foobar/map0.tsx",
        33,
        {{"atlas_index", "0"}});
    fmp::export_tsx(
        "core.map_chip",
        "/home/ruin/.tiled/Elona_foobar/map1.tsx",
        33,
        {{"atlas_index", "1"}});
    fmp::export_tsx(
        "core.map_chip",
        "/home/ruin/.tiled/Elona_foobar/map2.tsx",
        33,
        {{"atlas_index", "2"}});

    for (auto&& i : cdata.others())
    {
        i.clear();
    }

    for (auto&& i : items(-1))
    {
        inv[i].clear();
    }

    fmp::init_map("puti");

    REQUIRE(chara_get_free_slot() == 153);
    REQUIRE(inv_getfreeid(-1) == 5132);

    cell_featread(7, 8);
    REQUIRE(feat(0) == 726);
    REQUIRE(feat(1) == 21);
    REQUIRE(feat(2) == 15);
    REQUIRE(feat(3) == 0);

    auto& chara = cdata[cell_data.at(51, 7).chara_index_plus_one - 1];
    REQUIRE(chara.id == 4);

    auto& item = inv[cell_itemoncell({19, 4}).second];
    REQUIRE(item.id == 275);
}
