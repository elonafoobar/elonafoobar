#include "cat.hpp"
#include <iostream>
#include <string>
using namespace std::string_literals;

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
#ifdef _WIN32
    std::wstring filepath_str = filepath.native();
    if (luaL_dowfile(ptr(), filepath_str.c_str()) != 0)
#else
    std::string filepath_str = filesystem::to_narrow_path(filepath);
    if (luaL_dofile(ptr(), filepath_str.c_str()) != 0)
#endif
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
