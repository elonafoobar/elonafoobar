#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Rand
{
int rnd(int n);

bool one_in(int n);

bool coinflip();


void bind(sol::table&);
}; // namespace Rand

} // namespace lua
} // namespace elona
