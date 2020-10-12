#include "../../../audio.hpp"
#include "../../../calc.hpp"
#include "../../../character.hpp"
#include "../../../character_status.hpp"
#include "../../../crafting.hpp"
#include "../../../data/types/type_ability.hpp"
#include "../../../data/types/type_map.hpp"
#include "../../../game.hpp"
#include "../../../i18n.hpp"
#include "../../../inventory.hpp"
#include "../../../item.hpp"
#include "../../../itemgen.hpp"
#include "../../../map.hpp"
#include "../../../menu.hpp"
#include "../../../shop.hpp"
#include "../../../ui.hpp"
#include "../../fmt.hpp"
#include "../../interface.hpp"
#include "../../mod_manager.hpp"
#include "../common.hpp"



/**
 * Functions solely needed for implementing mod functionality, but which are
 * inconvenient to move to Lua completely.
 */
namespace elona::lua::api::modules::module_Internal
{

void Internal_go_to_quest_map(const std::string& map_name, int dungeon_level)
{
    auto id = the_mapdef_db[data::InstanceId{map_name}]->integer_id;
    map_data.stair_down_pos =
        cdata.player().position.y * 1000 + cdata.player().position.x;
    game()->destination_map = id;
    game()->destination_dungeon_level = dungeon_level;
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
        if (cdata.tmp().relationship != Relationship::enemy)
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
    inv_open_tmp_inv_no_physical_file();
    mode = 6;
    flt();
    itemcreate_tmp_inv(283, 0);
    flt();
    itemcreate_tmp_inv(284, 0);
    for (int cnt = 0; cnt < 800; ++cnt)
    {
        if (cnt == 672)
        {
            continue;
        }
        randomize(game_date().day() + cnt);
        f = 0;
        if (const auto id = the_item_db.get_id_from_integer(cnt))
        {
            if (game()->item_memories.identify_state(*id) !=
                IdentifyState::unidentified)
            {
                f = 1;
            }
        }
        if (cnt == 662)
        {
            if (story_quest_progress("core.kamikaze_attack") >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 655)
        {
            if (story_quest_progress("core.rare_books") >= 1000)
            {
                f = 1;
            }
        }
        if (cnt == 639)
        {
            if (story_quest_progress("core.pael_and_her_mom") >= 1000)
            {
                f = 1;
            }
        }
        if (f)
        {
            flt(cdata.player().level * 3 / 2, calcfixlv(Quality::good));
            if (const auto item = itemcreate_tmp_inv(cnt, 0))
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
    inv_close_tmp_inv_no_physical_file();
    mode = 0;
}



fmt::ParseResult Internal_parse_fmt(
    const std::string& src,
    sol::this_state state)
{
    fmt::FormatParser parser{src, state};
    return parser.parse();
}



std::vector<std::string> Internal_get_enabled_mods()
{
    std::vector<std::string> ret;
    const auto& mod_mgr = lua::lua->get_mod_manager();
    auto mods = mod_mgr.sorted_mods();
    range::sort(mods);
    for (const auto& mod : mods)
    {
        const auto version = mod_mgr.get_enabled_version(mod)->to_string();
        ret.push_back(mod + " v" + version);
    }
    return ret;
}



void Internal_gain_spell()
{
    for (int i = 400; i < 467; ++i)
    {
        if (i != 426 && i != 427)
        {
            chara_gain_skill(cdata.player(), i, 100, 10000);
        }
    }
}



void Internal_gain_spact()
{
    for (int i = 1; i < 61; ++i)
    {
        cdata.player().spacts().gain(
            *the_ability_db.get_id_from_integer(i + 600));
    }
}



void Internal_gain_exp(int exp)
{
    cdata.player().experience += exp;
    gain_level(cdata.player());
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("go_to_quest_map", Internal_go_to_quest_map);
    ELONA_LUA_API_BIND_FUNCTION("speaker_name", Internal_speaker_name);
    ELONA_LUA_API_BIND_FUNCTION("material_kit_crafting_menu", Internal_material_kit_crafting_menu);
    ELONA_LUA_API_BIND_FUNCTION("filter_set_dungeon", Internal_filter_set_dungeon);
    ELONA_LUA_API_BIND_FUNCTION("trade_small_medals", Internal_trade_small_medals);
    ELONA_LUA_API_BIND_FUNCTION("generate_fighters_guild_target", Internal_generate_fighters_guild_target);
    ELONA_LUA_API_BIND_FUNCTION("leave_map", Internal_leave_map);
    ELONA_LUA_API_BIND_FUNCTION("strange_scientist_pick_reward", Internal_strange_scientist_pick_reward);
    ELONA_LUA_API_BIND_FUNCTION("parse_fmt", Internal_parse_fmt);
    ELONA_LUA_API_BIND_FUNCTION("get_enabled_mods", Internal_get_enabled_mods);
    ELONA_LUA_API_BIND_FUNCTION("gain_spell", Internal_gain_spell);
    ELONA_LUA_API_BIND_FUNCTION("gain_spact", Internal_gain_spact);
    ELONA_LUA_API_BIND_FUNCTION("gain_exp", Internal_gain_exp);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Internal
