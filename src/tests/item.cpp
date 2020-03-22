#include "../elona/item.hpp"

#include "../elona/itemgen.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

TEST_CASE("Test that index of copied item is set", "[C++: Item]")
{
    testing::start_in_debug_map();
    int amount = 1;

    REQUIRE_SOME(
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, amount));
    Item& i = elona::inv[elona::ci];

    int ti = elona::inv_getfreeid(-1);
    elona::Item::copy(i, elona::inv[ti]);

    REQUIRE(elona::inv[elona::ci].index == elona::ci);
    REQUIRE(elona::inv[ti].index == ti);
}
