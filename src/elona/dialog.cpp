#include "dialog.hpp"
#include "character.hpp"
#include "lua_env/interface.hpp"
#include "talk.hpp"

namespace elona
{

void dialog_start(Character& speaker, const std::string& id)
{
    lua::call("core.impl.show_dialog", lua::handle(speaker), id);
}

} // namespace elona
