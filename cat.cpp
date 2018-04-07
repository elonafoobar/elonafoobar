#include "cat.hpp"
#include <iostream>


namespace elona::cat
{



void engine::initialize()
{
    L.reset(luaL_newstate());
    luaL_openlibs(ptr());
    load(fs::path(u8"../__init__.lua"));
}


void engine::load(const fs::path& filepath)
{
    luaL_dofile(ptr(), filepath.c_str());
}


void engine::register_function(const char* name, lua_CFunction func)
{
    lua_pushcfunction(ptr(), func);
    lua_setglobal(ptr(), name);
}



} // namespace elona::cat
