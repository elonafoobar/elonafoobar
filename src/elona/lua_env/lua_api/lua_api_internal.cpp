#include "lua_api_internal.hpp"
#include "../../lua_env/interface.hpp"

namespace elona
{
namespace lua
{

#define GET_QUEST_FLAG(id_) \
    if (id == #id_) \
    { \
        return game_data.quest_flags.id_; \
    }

#define SET_QUEST_FLAG(id_, value) \
    if (id == #id_) \
    { \
        game_data.quest_flags.id_ = value; \
        return; \
    }

int LuaApiInternal::get_quest_flag(const std::string& id)
{
    GET_QUEST_FLAG(tutorial);

    return 0;
}

void LuaApiInternal::set_quest_flag(const std::string& id, int value)
{
    SET_QUEST_FLAG(tutorial, value);
}

#undef GET_QUEST_FLAG
#undef SET_QUEST_FLAG

/**
 * Returns the name of this character as displayed in the dialog screen.
 */
std::string LuaApiInternal::speaker_name(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return talk_get_speaker_name(chara_ref);
}


void LuaApiInternal::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, get_quest_flag);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, set_quest_flag);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, speaker_name);
}

} // namespace lua
} // namespace elona
