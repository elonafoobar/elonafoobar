#include "cat.hpp"
#include <iostream>
#include <string>
#include "defines.hpp"
using namespace std::string_literals;


#ifdef ELONA_OS_WINDOWS
#define ELONA_luaL_dofile luaL_dowfile
#else
#define ELONA_luaL_dofile luaL_dofile
#endif


namespace elona
{
namespace cat
{


engine global;



void engine::initialize()
{
    L.reset(luaL_newstate());
    luaL_openlibs(ptr());
    load(filesystem::path(u8"__init__.lua"));
}


void engine::load(const fs::path& filepath)
{
    if (ELONA_luaL_dofile(ptr(), filepath.native().c_str()) != 0)
    {
        const char* error_msg = lua_tostring(ptr(), -1);
        throw std::runtime_error(
            u8"Error when loading Lua script:\n"s + std::string(error_msg));
    }
}


void engine::register_function(const char* name, lua_CFunction func)
{
    lua_pushcfunction(ptr(), func);
    lua_setglobal(ptr(), name);
}



} // namespace cat
} // namespace elona
