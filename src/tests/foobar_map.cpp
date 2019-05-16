#include "../thirdparty/catch2/catch.hpp"

#include "../elona/map.hpp"
#include "../elona/map_cell.hpp"
#include "../elona/mapgen.hpp"
#include "../elona/testing.hpp"
#include "tests.hpp"

#include "../elona/foobar_map/foobar_map.hpp"
#include "../elona/foobar_map/map_instantiator.hpp"
#include "../elona/foobar_map/map_loader.hpp"

using namespace elona;
using namespace elona::testing;


TEST_CASE("Test foobar map is instantiated correctly", "[FoobarMap]")
{
    testing::reset_state();

    for (auto&& i : cdata.others())
    {
        i.clear();
    }

    for (auto&& i : items(-1))
    {
        inv[i].clear();
    }

    auto map = fmp::MapLoader::load(
        testing::get_test_data_path() / "map" / "puti.fmp");
    fmp::instantiate_map(map);

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

TEST_CASE("Test vanilla map is instantiated correctly", "[FoobarMap]")
{
    testing::reset_state();

    for (auto&& i : cdata.others())
    {
        i.clear();
    }

    for (auto&& i : items(-1))
    {
        inv[i].clear();
    }

    map_data.tileset = 0;
    map_initcustom("puti");

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
