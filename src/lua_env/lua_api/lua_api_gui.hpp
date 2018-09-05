#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace GUI
{
void txt(const std::string&);
void txt_txtef(const std::string&, const EnumString&);

void txtnew();

void txtef(const EnumString&);


void bind(sol::table&);
}; // namespace GUI

} // namespace lua
} // namespace elona
