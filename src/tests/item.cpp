#include "../thirdparty/catch2/catch.hpp"

#include "../item.hpp"
#include "../itemgen.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

TEST_CASE("Test that index of copied item is set", "[C++: Item]")
{
    testing::start_in_debug_map();
    int amount = 1;

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, amount));
    item& i = elona::inv[elona::ci];

    int ti = elona::inv_getfreeid(-1);
    elona::item::copy(i, elona::inv[ti]);

    REQUIRE(elona::inv[elona::ci].index == elona::ci);
    REQUIRE(elona::inv[ti].index == ti);
}
