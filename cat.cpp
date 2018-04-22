#include "cat.hpp"
#include <iostream>


namespace elona
{
namespace cat
{


engine global;



void engine::initialize()
{
    L.reset(luaL_newstate());
    luaL_openlibs(ptr());
    load(filesystem::path(u8"../__init__.lua"));
}


void engine::load(const fs::path& filepath)
{
    luaL_dofile(ptr(), filesystem::to_narrow_path(filepath).c_str());
}


void engine::register_function(const char* name, lua_CFunction func)
{
    lua_pushcfunction(ptr(), func);
    lua_setglobal(ptr(), name);
}



} // namespace cat
} // namespace elona
