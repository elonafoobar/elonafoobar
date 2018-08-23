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

int Skill::resistance(
    const enum_string& element_name,
    lua_character_handle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<character>(handle);
    Element element = LuaEnums::ElementTable.ensure_from_string(element_name);
    return elona::sdata(static_cast<int>(element), chara.index);
}

void Skill::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Skill, level);
    LUA_API_BIND_FUNCTION(api_table, Skill, resistance);
}

} // namespace lua
} // namespace elona
