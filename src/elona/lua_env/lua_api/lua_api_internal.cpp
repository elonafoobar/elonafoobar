#include "lua_api_internal.hpp"
#include "../../audio.hpp"
#include "../../character.hpp"
#include "../../crafting.hpp"
#include "../../data/types/type_map.hpp"
#include "../../item.hpp"
#include "../../map.hpp"
#include "../../shop.hpp"
#include "../../ui.hpp"
#include "../interface.hpp"

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
    GET_QUEST_FLAG(main_quest);
    GET_QUEST_FLAG(putit_attacks);
    GET_QUEST_FLAG(thieves_hideout);
    GET_QUEST_FLAG(nightmare);
    GET_QUEST_FLAG(pael_and_her_mom);
    GET_QUEST_FLAG(wife_collector);
    GET_QUEST_FLAG(puppys_cave);
    GET_QUEST_FLAG(cat_house);
    GET_QUEST_FLAG(defense_line);
    GET_QUEST_FLAG(novice_knight);
    GET_QUEST_FLAG(kamikaze_attack);
    GET_QUEST_FLAG(mias_dream);
    GET_QUEST_FLAG(rare_books);
    GET_QUEST_FLAG(pyramid_trial);
    GET_QUEST_FLAG(red_blossom_in_palmia);
    GET_QUEST_FLAG(ambitious_scientist);
    GET_QUEST_FLAG(sewer_sweeping);
    GET_QUEST_FLAG(minotaur_king);
    GET_QUEST_FLAG(little_sister);
    GET_QUEST_FLAG(blue_capsule_drug);

    throw sol::error("No such quest " + id);
    return 0;
}

void LuaApiInternal::set_quest_flag(const std::string& id, int value)
{
    SET_QUEST_FLAG(tutorial, value);
    SET_QUEST_FLAG(main_quest, value);
    SET_QUEST_FLAG(putit_attacks, value);
    SET_QUEST_FLAG(thieves_hideout, value);
    SET_QUEST_FLAG(nightmare, value);
    SET_QUEST_FLAG(pael_and_her_mom, value);
    SET_QUEST_FLAG(wife_collector, value);
    SET_QUEST_FLAG(puppys_cave, value);
    SET_QUEST_FLAG(cat_house, value);
    SET_QUEST_FLAG(defense_line, value);
    SET_QUEST_FLAG(novice_knight, value);
    SET_QUEST_FLAG(kamikaze_attack, value);
    SET_QUEST_FLAG(mias_dream, value);
    SET_QUEST_FLAG(rare_books, value);
    SET_QUEST_FLAG(pyramid_trial, value);
    SET_QUEST_FLAG(red_blossom_in_palmia, value);
    SET_QUEST_FLAG(ambitious_scientist, value);
    SET_QUEST_FLAG(sewer_sweeping, value);
    SET_QUEST_FLAG(minotaur_king, value);
    SET_QUEST_FLAG(little_sister, value);
    SET_QUEST_FLAG(blue_capsule_drug, value);

    throw sol::error("No such quest " + id);
}

#undef GET_QUEST_FLAG
#undef SET_QUEST_FLAG

void LuaApiInternal::go_to_quest_map(
    const std::string& map_name,
    int dungeon_level)
{
    auto id = the_mapdef_db[map_name]->id;
    map_data.stair_down_pos =
        cdata.player().position.y * 1000 + cdata.player().position.x;
    game_data.destination_map = id;
    game_data.destination_dungeon_level = dungeon_level;
    levelexitby = 2;
    chatteleport = 1;
}

/**
 * Returns the name of this character as displayed in the dialog screen.
 */
std::string LuaApiInternal::speaker_name(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return talk_get_speaker_name(chara_ref);
}

void LuaApiInternal::material_kit_crafting_menu()
{
    invctrl = 1;
    snd("core.pop2");
    elona::crafting_menu();
}

int LuaApiInternal::filter_set_dungeon()
{
    return elona::fltsetdungeon();
}

void LuaApiInternal::trade_small_medals(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    invctrl = 28;
    invfile = chara_ref.shop_store_id;
    shop_sell_item();
    screenupdate = -1;
    update_screen();
    cs = 0;
}

void LuaApiInternal::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, get_quest_flag);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, set_quest_flag);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, go_to_quest_map);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, speaker_name);
    LUA_API_BIND_FUNCTION(
        api_table, LuaApiInternal, material_kit_crafting_menu);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, filter_set_dungeon);
    LUA_API_BIND_FUNCTION(api_table, LuaApiInternal, trade_small_medals);
}

} // namespace lua
} // namespace elona
