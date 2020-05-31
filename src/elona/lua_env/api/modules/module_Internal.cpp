#include "module_Internal.hpp"

#include "../../../audio.hpp"
#include "../../../calc.hpp"
#include "../../../character.hpp"
#include "../../../crafting.hpp"
#include "../../../data/types/type_map.hpp"
#include "../../../i18n.hpp"
#include "../../../item.hpp"
#include "../../../itemgen.hpp"
#include "../../../map.hpp"
#include "../../../menu.hpp"
#include "../../../shop.hpp"
#include "../../../ui.hpp"
#include "../../interface.hpp"



namespace elona::lua::api::modules::module_Internal
{

int Internal_get_quest_flag(const std::string& id)
{
#define GET_QUEST_FLAG(id_) \
    if (id == #id_) \
    { \
        return game_data.quest_flags.id_; \
    }

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
    GET_QUEST_FLAG(duration_of_kamikaze_attack);
    GET_QUEST_FLAG(kill_count_of_little_sister);
    GET_QUEST_FLAG(save_count_of_little_sister);
    GET_QUEST_FLAG(gift_count_of_little_sister);

    throw sol::error("No such quest " + id);
    return 0;

#undef GET_QUEST_FLAG
}



void Internal_set_quest_flag(const std::string& id, int value)
{
#define SET_QUEST_FLAG(id_, value) \
    if (id == #id_) \
    { \
        game_data.quest_flags.id_ = value; \
        return; \
    }


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
    SET_QUEST_FLAG(duration_of_kamikaze_attack, value);
    SET_QUEST_FLAG(kill_count_of_little_sister, value);
    SET_QUEST_FLAG(save_count_of_little_sister, value);
    SET_QUEST_FLAG(gift_count_of_little_sister, value);

    throw sol::error("No such quest " + id);

#undef SET_QUEST_FLAG
}



void Internal_go_to_quest_map(const std::string& map_name, int dungeon_level)
{
    auto id = the_mapdef_db[data::InstanceId{map_name}]->legacy_id;
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
std::string Internal_speaker_name(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    return talk_get_speaker_name(chara_ref);
}



void Internal_material_kit_crafting_menu()
{
    invctrl = 1;
    snd("core.pop2");
    elona::crafting_menu();
}



int Internal_filter_set_dungeon()
{
    return elona::fltsetdungeon();
}



void Internal_trade_small_medals(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    invctrl = 28;
    invfile = chara_ref.shop_store_id;
    shop_sell_item(chara_ref);
    screenupdate = -1;
    update_screen();
    cs = 0;
}



int Internal_generate_fighters_guild_target(int level)
{
    while (true)
    {
        flt(level);
        chara_create(56, 0, -3, 0);
        if (the_character_db[charaid2int(cdata.tmp().id)]->rarity / 1000 < 70)
        {
            continue;
        }
        if (cdata.tmp().relationship != -3)
        {
            continue;
        }
        if (cdata.tmp().quality >= Quality::miracle)
        {
            continue;
        }
        break;
    }

    auto id = charaid2int(cdata.tmp().id);
    chara_vanquish(cdata.tmp());

    return id;
}



void Internal_leave_map()
{
    levelexitby = 4;
    chatteleport = 1;
}



void Internal_strange_scientist_pick_reward()
{
    begintempinv();
    mode = 6;
    flt();
    itemcreate_extra_inv(283, -1, -1, 0);
    flt();
    itemcreate_extra_inv(284, -1, -1, 0);
    for (int cnt = 0; cnt < 800; ++cnt)
    {
        if (cnt == 672)
        {
            continue;
        }
        randomize(game_data.date.day + cnt);
        f = 0;
        if (itemmemory(0, cnt))
        {
            f = 1;
        }
        if (cnt == 662)
        {
            if (game_data.quest_flags.kamikaze_attack >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 655)
        {
            if (game_data.quest_flags.rare_books >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 639)
        {
            if (game_data.quest_flags.pael_and_her_mom >= 1000)
            {
                f = 1;
            }
        }
        if (f)
        {
            flt(cdata.player().level * 3 / 2, calcfixlv(Quality::good));
            if (const auto item = itemcreate_extra_inv(cnt, -1, -1, 0))
            {
                if (item->quality < Quality::miracle)
                {
                    item->remove();
                }
            }
        }
        randomize();
    }
    txt(i18n::s.get("core.talk.unique.strange_scientist.reward.choose_one"));
    invsubroutine = 1;
    invctrl(0) = 22;
    invctrl(1) = 4;
    ctrl_inventory();
    exittempinv();
    mode = 0;
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("get_quest_flag", Internal_get_quest_flag);
    ELONA_LUA_API_BIND_FUNCTION("set_quest_flag", Internal_set_quest_flag);
    ELONA_LUA_API_BIND_FUNCTION("go_to_quest_map", Internal_go_to_quest_map);
    ELONA_LUA_API_BIND_FUNCTION("speaker_name", Internal_speaker_name);
    ELONA_LUA_API_BIND_FUNCTION("material_kit_crafting_menu", Internal_material_kit_crafting_menu);
    ELONA_LUA_API_BIND_FUNCTION("filter_set_dungeon", Internal_filter_set_dungeon);
    ELONA_LUA_API_BIND_FUNCTION("trade_small_medals", Internal_trade_small_medals);
    ELONA_LUA_API_BIND_FUNCTION("generate_fighters_guild_target", Internal_generate_fighters_guild_target);
    ELONA_LUA_API_BIND_FUNCTION("leave_map", Internal_leave_map);
    ELONA_LUA_API_BIND_FUNCTION("strange_scientist_pick_reward", Internal_strange_scientist_pick_reward);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Internal
