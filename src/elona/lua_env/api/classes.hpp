#pragma once

#include "common.hpp"



/**
 * Binding functions for usertype classes.
 *
 * Methods for usertypes do not take a handle as a first argument,
 * because handles will transparently pass their underlying C++
 * references to them via metatables.
 */
namespace elona::lua::api::classes
{

void bind(sol::state& L);
void bind_api(sol::state& L, sol::table core);

} // namespace elona::lua::api::classes
