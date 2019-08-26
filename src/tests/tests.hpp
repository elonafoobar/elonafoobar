#pragma once
#include "util.hpp"
#define PUTIT_PROTO_ID 3
#define PUTITORO_PROTO_ID int2itemid(792)

// macros for boost::optional results
#define REQUIRE_SOME(x) REQUIRE(static_cast<bool>(x) == true)
#define REQUIRE_NONE(x) REQUIRE(static_cast<bool>(x) == false)
#define REQUIRE_IN_MOD(mod_id, assertion) \
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod( \
        mod_id, "assert(assertion)"));
