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
	std::string filepath_str = filesystem::to_narrow_path(filepath);
	if (luaL_dofile(ptr(), filepath_str.c_str()) != 0) {
		throw std::runtime_error(u8"Could not load lua script at "s + filepath_str + u8"."s);
	}
}


void engine::register_function(const char* name, lua_CFunction func)
{
    lua_pushcfunction(ptr(), func);
    lua_setglobal(ptr(), name);
}



} // namespace cat
} // namespace elona
