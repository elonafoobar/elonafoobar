#include "cat.hpp"
#include <iostream>


namespace cat
{


void register_function(lua_State* state, const char* name, lua_CFunction func)
{
    lua_pushcfunction(state, func);
    lua_setglobal(state, name);
}


void load(lua_State* state, const fs::path& filepath)
{
    luaL_dofile(state, filepath.c_str());
}


} // namespace cat
