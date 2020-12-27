#include "i18n.hpp"

#include <fstream>
#include <memory>

#include "config.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "lua_env/mod_manager.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{

void Store::init()
{
    for (const auto& mod_id : lua::lua->get_mod_manager().sorted_mods())
    {
        lua::lua->get_i18n_manager().load(
            *lua::lua->get_mod_manager().get_mod(mod_id));
    }
}



void Store::load_from_string(const std::string& src, const std::string& mod_id)
{
    lua::lua->get_i18n_manager().load_string(
        src, *lua::lua->get_mod_manager().get_mod(mod_id));
}



std::string space_if_needed()
{
    if (jp)
    {
        return "";
    }
    else
    {
        return " ";
    }
}

} // namespace i18n
} // namespace elona
