#pragma once

#include <lua.hpp>
#include "filesystem.hpp"


namespace cat
{


void register_function(lua_State*, const char* name, lua_CFunction);
void load(lua_State*, const fs::path& filepath);


} // namespace cat
