#pragma once
#include "../character.hpp"
#include "../item.hpp"

namespace elona
{

namespace lua
{
class LuaEnv;
}

namespace testing
{

void set_english();
void set_japanese();
void normalize_item(Item&);
std::string test_itemname(int, int, bool = false);
Item& create_item(int, int = 1);
Character& create_chara(int, int = 0, int = 0);

/**
 * Registers a single callback in a mod.

 * This can only be called once per mod name.
 *
 * @param lua Lua environment for mod
 * @param mod_name the mod's name
 * @param callback_signature "my_callback(arg)"
 * @param callback_body "return arg + 42"
 */
void register_lua_function(
    lua::LuaEnv& lua,
    std::string mod_name,
    std::string callback_signature,
    std::string callback_body);

} // namespace testing
} // namespace elona
