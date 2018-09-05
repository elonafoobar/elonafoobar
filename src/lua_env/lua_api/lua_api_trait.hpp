#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Trait
{
sol::optional<int> level(int);

sol::optional<int> min(int);

sol::optional<int> max(int);

void set(int, int);

void modify(int, int);


void bind(sol::table&);
} // namespace Trait

} // namespace lua
} // namespace elona
