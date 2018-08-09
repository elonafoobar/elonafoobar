#include "lua_api_skill.hpp"
#include "../../ability.hpp"

namespace elona
{
namespace lua
{

int Skill::level(int skill, lua_character_handle handle)
{
    if (skill < 0 || skill >= 600)
    {
        return -1;
    }
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    return elona::sdata(skill, chara.index);
}

void Skill::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Skill, level);
}

} // namespace lua
} // namespace elona
