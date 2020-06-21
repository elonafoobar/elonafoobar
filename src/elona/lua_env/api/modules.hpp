#pragma once

#include "common.hpp"



/***
 * See doc/api for the API documentation.
 * Be sure to update it if you change anything in the API bindings.
 * LDoc is completely broken when it comes to parsing C++.
 */
namespace elona::lua::api::modules
{

void bind(sol::table core);

}
