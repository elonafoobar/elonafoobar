#pragma once
#include "util.hpp"
#define PUTIT_PROTO_ID 3
#define PUTITORO_PROTO_ID 792

// macros for boost::optional results
#define REQUIRE_SOME(x) REQUIRE(static_cast<bool>(x) == true)
#define REQUIRE_NONE(x) REQUIRE(static_cast<bool>(x) == false)
