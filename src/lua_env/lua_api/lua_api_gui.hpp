#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace GUI
{
void txt(const std::string&);
void txt_txtef(const std::string&, const enum_string&);

void txtnew();

void txtef(const enum_string&);


void bind(sol::table&);
}; // namespace GUI

} // namespace lua
} // namespace elona
