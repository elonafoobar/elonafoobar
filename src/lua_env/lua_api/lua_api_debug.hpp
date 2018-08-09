#pragma once
#include <string>
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{
namespace Debug
{
void log(const std::string&);

void report_error(const std::string&);

void dump_characters();

void dump_items();


void bind(sol::table&);
} // namespace Debug
} // namespace lua
} // namespace elona
