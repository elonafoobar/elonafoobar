#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace GUI
{
void txt(const std::string&);
void txt_txtef(const std::string&, color_index_t);

void txtnew();

void txtef(color_index_t);


void bind(sol::table&);
}; // namespace GUI

} // namespace lua
} // namespace elona
