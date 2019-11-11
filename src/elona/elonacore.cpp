#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "../version.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "adventurer.hpp"
#include "ai.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "autopick.hpp"
#include "blending.hpp"
#include "buff.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "casino.hpp"
#include "casino_card.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "command.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "filesystem.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "log.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/interface.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/character_instance_event.hpp"
#include "lua_env/mod_manager.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "net.hpp"
#include "quest.hpp"
#include "race.hpp"
#include "random.hpp"
#include "random_event.hpp"
#include "save.hpp"
#include "save_update.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "turn_sequence.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "wish.hpp"

using namespace elona;


namespace
{

std::string atbuff;



void select_house_board_tile()
{
    snd("core.pop2");

    auto box_size = inf_tiles / 2;
    while (1)
    {
        gmode(0);
        p = 0;
        // TODO
        for (int y = 0; y < 20; ++y)
        {
            for (int x = 0; x < 33; ++x)
            {
                if (p < listmax)
                {
                    const auto& chip = chip_data[list(0, p)];
                    draw_map_tile(
                        list(0, p),
                        x * box_size,
                        y * box_size,
                        inf_tiles,
                        inf_tiles,
                        box_size,
                        box_size);
                    if (chip.effect & 4)
                    {
                        boxl(
                            x * box_size,
                            y * box_size,
                            box_size,
                            box_size,
                            {240, 230, 220});
                    }
                }
                ++p;
            }
        }

        gmode(2);
        redraw();
        await(g_config.general_wait());
        const auto input = stick();
        if (input == StickKey::mouse_left)
        {
            p = mousex / box_size + mousey / box_size * 33;
            if (p >= listmax)
            {
                snd("core.fail1");
                continue;
            }
            tile = list(0, p);
            snd("core.ok1");
            house_board_update_screen();
            return;
        }
        if (input == StickKey::mouse_right)
        {
            house_board_update_screen();
            return;
        }
    }
}



void weather_changes_by_location(bool output_immediately = true)
{
    if (game_data.weather == 2)
    {
        if (game_data.pc_x_in_world_map < 65 &&
            game_data.pc_y_in_world_map > 10)
        {
            game_data.weather = 3;
            sound_play_environmental();
            game_data.hours_until_weather_changes += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.action.weather.changes"));
            }
            else
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.weather.changes"));
            }
        }
    }
    if (game_data.weather == 4 || game_data.weather == 3)
    {
        if (game_data.pc_x_in_world_map > 65 ||
            game_data.pc_y_in_world_map < 10)
        {
            game_data.weather = 2;
            sound_play_environmental();
            game_data.hours_until_weather_changes += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.action.weather.changes"));
            }
            else
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.weather.changes"));
            }
        }
    }
}

} // namespace



namespace elona
{

double r_at_m133;


elona_vector1<int> ranknorma;
int f_at_m14 = 0;
int pagebk = 0;
int csprev = 0;
int pagesaved = 0;
int himc_at_ime_control = 0;
int hwnd = 0;
int dx_at_m133 = 0;
elona_vector1<int> dy_at_m133;
int f_at_con = 0;
int p_at_con = 0;
int dx_at_m136 = 0;
int dy_at_m136 = 0;
int r3 = 0;
int refdiff = 0;
int traveldone = 0;
elona_vector1<int> fsetincome;
elona_vector1<int> fsetrare;
elona_vector1<int> fsetplantartifact;
elona_vector1<int> fsetplantunknown;
elona_vector1<int> fsetbarrel;
elona_vector1<int> isetgiftminor;
elona_vector1<int> isetgiftmajor;
elona_vector1<int> isetgiftgrand;
int cibk = 0;
int cansee = 0;
int kdx = 0;
int kdy = 0;
int tglocx = 0;
int tglocy = 0;
std::string fileext;
std::string filedsc;
int lenhead = 0;
int lensum = 0;
elona_vector1<std::string> filebuff;
elona_vector1<std::string> filetemp;
int lensum_at_m188 = 0;
elona_vector1<std::string> filebuff_at_m188;
elona_vector1<int> p_at_m188;
int len_at_m188 = 0;
int lenhead_at_m188 = 0;
elona_vector1<std::string> filetemp_at_m188;
elona_vector1<std::string> txtbuff;
int initunid = 0;
int cun = 0;
elona_vector1<int> unaiactsubfreq;
elona_vector1<int> bmpbuff;
std::string usertitle;
std::string dbm;
int dbg_exitshowroom = 0;
int noeffect = 0;
int inumbk = 0;
int attackitem = 0;
int extraattack = 0;



std::string ranktitle(int rank_id)
{
    int rank_value = game_data.ranks.at(rank_id) / 100;
    if (rank_value == 1)
    {
        return rankn(0, rank_id);
    }
    if (rank_value <= 5)
    {
        return rankn(1, rank_id);
    }
    if (rank_value <= 10)
    {
        return rankn(2, rank_id);
    }
    if (rank_value <= 80)
    {
        return rankn(rank_value / 15 + 3, rank_id);
    }
    return rankn(9, rank_id);
}



void initialize_rankn()
{
    SDIM4(rankn, 30, 11, 9);

    for (int category = 0; category < 9; category++)
    {
        if (category == 7)
        {
            // Skips the 7th row because there are no defined locale resources.
            continue;
        }
        for (int rank = 0; rank < 11; rank++)
        {
            rankn(rank, category) =
                i18n::s.get_enum("core.rank._"s + category, rank);
        }
    }

    DIM2(ranknorma, 9);
    ranknorma(0) = 20;
    ranknorma(1) = 60;
    ranknorma(2) = 45;
    ranknorma(6) = 30;
}



std::string guildname()
{
    if (game_data.guild.belongs_to_mages_guild)
    {
        return i18n::s.get("core.guild.mages.name");
    }
    else if (game_data.guild.belongs_to_fighters_guild)
    {
        return i18n::s.get("core.guild.fighters.name");
    }
    else if (game_data.guild.belongs_to_thieves_guild)
    {
        return i18n::s.get("core.guild.thieves.name");
    }
    else
    {
        return i18n::s.get("core.guild.none.name");
    }
}



void initialize_post_data()
{
    DIM4(pochart, 10, 10, 10);
    pochart(0, 0, 0) = 2;
    pochart(0, 1, 0) = 3;
    pochart(1, 1, 0) = 4;
    pochart(0, 2, 0) = 5;
    pochart(1, 2, 0) = 6;
    DIM3(podata, 300, 20);
}



void initialize_building_data()
{
    DIM4(bddata, 40, 20, 10);
    DIM3(bdref, 10, 7);
    bdref(0, 1) = 0;
    bdref(1, 1) = 1500;
    bdref(0, 2) = 1;
    bdref(1, 2) = 2500;
    bdref(0, 3) = 2;
    bdref(1, 3) = 2500;
    bdref(0, 4) = 3;
    bdref(1, 4) = 2500;
    bdref(0, 5) = 4;
    bdref(1, 5) = 2500;
    bdref(0, 6) = 5;
    bdref(1, 6) = 2500;
}


void initialize_pc_character()
{
    cdata.player().quality = Quality::good;
    cdata.player().relationship = 10;
    cdata.player().original_relationship = 10;
    cdata.player().has_own_sprite() = true;
    flt();
    itemcreate(0, 333, -1, -1, 0);
    inv[ci].set_number(8);
    flt();
    itemcreate(0, 233, -1, -1, 0);
    inv[ci].set_number(4);
    flt();
    itemcreate(0, 31, -1, -1, 0);
    inv[ci].set_number(2);
    if (sdata(150, 0) == 0)
    {
        flt();
        itemcreate(0, 68, -1, -1, 0);
        inv[ci].set_number(3);
    }
    if (cdatan(3, 0) == u8"core.pianist"s)
    {
        flt();
        itemcreate(0, 88, -1, -1, 0);
    }
    if (cdatan(3, 0) == u8"core.farmer"s)
    {
        flt();
        itemcreate(0, 256, -1, -1, 0);
    }
    if (cdatan(3, 0) == u8"core.wizard"s || cdatan(3, 0) == u8"core.warmage"s)
    {
        flt();
        itemcreate(0, 116, -1, -1, 0);
        flt();
        itemcreate(0, 257, -1, -1, 0);
        inv[ci].set_number(3);
    }
    if (cdatan(3, 0) == u8"core.priest"s)
    {
        flt();
        itemcreate(0, 249, -1, -1, 0);
        inv[ci].set_number(3);
        flt();
        itemcreate(0, 378, -1, -1, 0);
    }
    gain_race_feat();
    cdata.player().skill_bonus = 5 + trait(154);
    cdata.player().total_skill_bonus = 5 + trait(154);
    for (auto&& item : inv.pc())
    {
        if (item.number() == 0)
        {
            continue;
        }
        item.identify_state = IdentifyState::completely;
    }
    chara_refresh(0);
}



int randskill()
{
    return rnd(40) + 150;
}



int randattb()
{
    return rnd(8) + 10;
}



void clear_trait_data()
{
    DIM2(traitref, 10);
    SDIM3(traitrefn, 80, 9);
    SDIM3(traitrefn2, 20, 6);
}



void gain_race_feat()
{
    if (cdatan(2, 0) == u8"core.dwarf"s)
    {
        trait(152) = 2;
        trait(155) = 1;
    }
    if (cdatan(2, 0) == u8"core.elea"s)
    {
        trait(168) = 1;
        trait(156) = 1;
    }
    if (cdatan(2, 0) == u8"core.eulderna"s)
    {
        trait(153) = 1;
    }
    if (cdatan(2, 0) == u8"core.lich"s)
    {
        trait(151) = 1;
        trait(155) = 2;
        trait(152) = 1;
    }
    if (cdatan(2, 0) == u8"core.golem"s)
    {
        trait(157) = 1;
        trait(152) = 2;
    }
    if (cdatan(2, 0) == u8"core.yerles"s)
    {
        trait(154) = 1;
    }
    if (cdatan(2, 0) == u8"core.juere"s)
    {
        trait(158) = 1;
        trait(159) = 1;
    }
    if (cdatan(2, 0) == u8"core.goblin"s)
    {
        trait(155) = 1;
        trait(159) = 1;
    }
    if (cdatan(2, 0) == u8"core.mutant"s)
    {
        trait(0) = 1;
    }
    if (cdatan(2, 0) == u8"core.fairy"s)
    {
        trait(160) = 1;
        trait(161) = 1;
    }
}



int roundmargin(int x, int y)
{
    if (x > y)
        return x - rnd(x - y);
    else if (x < y)
        return x + rnd(y - x);
    else
        return x;
}



void auto_turn(int delay)
{
    if (cc != 0)
        return;

    autoturn = 1;
    if (g_config.auto_turn_speed() == "normal")
    {
        await(delay);
        ++scrturn;
    }
    if (g_config.auto_turn_speed() != "highest" || firstautoturn == 1)
    {
        screenupdate = -1;
        update_screen();
    }
    if (g_config.auto_turn_speed() == "normal")
    {
        redraw();
    }
}



std::string txttargetlevel(int cc, int tc)
{
    int x = cdata[cc].level;
    int y = cdata[tc].level;
    int danger;
    if (x * 20 < y)
    {
        danger = 10;
    }
    else if (x * 10 < y)
    {
        danger = 9;
    }
    else if (x * 5 < y)
    {
        danger = 8;
    }
    else if (x * 3 < y)
    {
        danger = 7;
    }
    else if (x * 2 < y)
    {
        danger = 6;
    }
    else if (x * 3 / 2 < y)
    {
        danger = 5;
    }
    else if (x < y)
    {
        danger = 4;
    }
    else if (x / 3 * 2 < y)
    {
        danger = 3;
    }
    else if (x / 2 < y)
    {
        danger = 2;
    }
    else if (x / 3 < y)
    {
        danger = 1;
    }
    else
    {
        danger = 0;
    }

    return i18n::s.get_enum("core.action.target.level", danger, cdata[tc]);
}



void initialize_picfood()
{
    DIM3(picfood, 10, 9);
    picfood(0, 8) = 230;
    picfood(1, 8) = 230;
    picfood(2, 8) = 230;
    picfood(3, 8) = 190;
    picfood(4, 8) = 229;
    picfood(5, 8) = 190;
    picfood(6, 8) = 342;
    picfood(7, 8) = 168;
    picfood(8, 8) = 347;
    picfood(9, 8) = 194;
    picfood(0, 1) = 230;
    picfood(1, 1) = 230;
    picfood(2, 1) = 230;
    picfood(3, 1) = 195;
    picfood(4, 1) = 227;
    picfood(5, 1) = 167;
    picfood(6, 1) = 167;
    picfood(7, 1) = 194;
    picfood(8, 1) = 229;
    picfood(9, 1) = 227;
    picfood(0, 2) = 230;
    picfood(1, 2) = 230;
    picfood(2, 2) = 230;
    picfood(3, 2) = 229;
    picfood(4, 2) = 342;
    picfood(5, 2) = 194;
    picfood(6, 2) = 229;
    picfood(7, 2) = 342;
    picfood(8, 2) = 229;
    picfood(9, 2) = 194;
    picfood(0, 3) = 230;
    picfood(1, 3) = 230;
    picfood(2, 3) = 230;
    picfood(3, 3) = 229;
    picfood(4, 3) = 346;
    picfood(5, 3) = 346;
    picfood(6, 3) = 345;
    picfood(7, 3) = 345;
    picfood(8, 3) = 347;
    picfood(9, 3) = 346;
    picfood(0, 4) = 230;
    picfood(1, 4) = 230;
    picfood(2, 4) = 230;
    picfood(3, 4) = 108;
    picfood(4, 4) = 346;
    picfood(5, 4) = 110;
    picfood(6, 4) = 346;
    picfood(7, 4) = 347;
    picfood(8, 4) = 347;
    picfood(9, 4) = 347;
    picfood(0, 5) = 230;
    picfood(1, 5) = 230;
    picfood(2, 5) = 229;
    picfood(3, 5) = 343;
    picfood(4, 5) = 344;
    picfood(5, 5) = 344;
    picfood(6, 5) = 343;
    picfood(7, 5) = 343;
    picfood(8, 5) = 344;
    picfood(9, 5) = 343;
    picfood(0, 6) = 230;
    picfood(1, 6) = 230;
    picfood(2, 6) = 230;
    picfood(3, 6) = 228;
    picfood(4, 6) = 342;
    picfood(5, 6) = 342;
    picfood(6, 6) = 228;
    picfood(7, 6) = 341;
    picfood(8, 6) = 228;
    picfood(9, 6) = 228;
    picfood(0, 7) = 230;
    picfood(1, 7) = 230;
    picfood(2, 7) = 110;
    picfood(3, 7) = 108;
    picfood(4, 7) = 110;
    picfood(5, 7) = 112;
    picfood(6, 7) = 114;
    picfood(7, 7) = 113;
    picfood(8, 7) = 115;
    picfood(9, 7) = 111;
}



void finish_elona()
{
    if (g_config.autodisable_numlock())
    {
        snail::Input::instance().restore_numlock();
    }
}



void addefmap(int x, int y, int efmap0, int efmap1, int efmap2, int efmap3)
{
    efmap(0, x, y) = efmap0;
    efmap(1, x, y) = efmap1;
    efmap(2, x, y) = efmap2;
    efmap(3, x, y) = efmap3;
}



void csvsort(
    elona_vector1<std::string>& result,
    std::string line,
    int separator)
{
    elona_vector1<int> p_at_m40;
    p_at_m40(0) = 0;
    for (int cnt = 0; cnt < 40; ++cnt)
    {
        result(cnt) = "";
        getstr(result(cnt), line, p_at_m40(0), separator);
        if (strsize == 0)
        {
            break;
        }
        p_at_m40(0) += strsize;
    }
}



void flt(int level, Quality quality)
{
    filtermax = 0;
    fltselect = 0;
    flttypemajor = 0;
    flttypeminor = 0;
    fltnrace = "";
    objlv = level == 0 ? calcobjlv(game_data.current_dungeon_level) : level;
    fixlv = quality == Quality::none ? calcfixlv(Quality::bad) : quality;
}



void fltn(const std::string& filter)
{
    std::string s2_at_m44;
    int p_at_m44 = 0;
    s2_at_m44 = filter;
    p_at_m44 = 0;
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        getstr(filtern(cnt), s2_at_m44, p_at_m44, 47);
        if (strsize == 0)
        {
            break;
        }
        filtern(cnt) = u8"/"s + filtern(cnt) + u8"/"s;
        p_at_m44 += strsize;
        ++filtermax;
    }
}



int discsetmc()
{
    return rnd(47);
}



int fltsetdungeon()
{
    if (rnd(20) == 0)
    {
        return choice(fsetrare);
    }
    if (rnd(3) == 0)
    {
        return choice(fsetwear);
    }
    return choice(fsetitem);
}



int cargocheck()
{
    if (!the_item_db[itemid2int(inv[ci].id)]->is_cargo)
    {
        return 1;
    }
    if (map_data.type != mdata_t::MapType::world_map &&
        map_data.type != mdata_t::MapType::player_owned &&
        map_data.type != mdata_t::MapType::town &&
        map_data.type != mdata_t::MapType::field &&
        map_data.type != mdata_t::MapType::shelter &&
        map_data.type != mdata_t::MapType::guild)
    {
        txt(i18n::s.get("core.ui.inv.cannot_use_cargo_items"),
            Message::only_once{true});
        snd("core.fail1");
        return 0;
    }
    else
    {
        return 1;
    }
}



int dist(int x1, int y1, int x2, int y2)
{
    const auto dx = x1 - x2;
    const auto dy = y1 - y2;
    return int(std::sqrt(dx * dx + dy * dy));
}



int winposy(int y, int not_gaming)
{
    if (not_gaming == 0)
    {
        return ((inf_screenh + 1) * inf_tiles - y) / 2 + 8;
    }
    return (windowh - y) / 2;
}



void cutname(std::string& utf8_string, int max_length_charwise)
{
    utf8_string = utf8_string.substr(
        0, strutil::utf8_cut_index(utf8_string, max_length_charwise));
}



void go_hostile()
{
    for (auto&& cc : cdata.others())
    {
        if (cc.character_role == 14 || cc.character_role == 16 ||
            cc.character_role == 1010)
        {
            cc.relationship = -3;
            cc.hate = 80;
            cc.emotion_icon = 218;
        }
    }
}



void modrank(int rank_id, int amount, int min)
{
    int rank_factor = game_data.ranks.at(rank_id) / 100;
    int orgrank_at_m75 = game_data.ranks.at(rank_id);
    int i_at_m75 = amount;
    if (amount > 0)
    {
        i_at_m75 = amount * (rank_factor + 20) * (rank_factor + 20) / 2500;
        game_data.rank_deadlines.at(rank_id) = ranknorma(rank_id);
        if (game_data.ranks.at(rank_id) == 100)
        {
            return;
        }
        if (min != 0)
        {
            if (i_at_m75 / 100 > min)
            {
                i_at_m75 = min * 100;
            }
        }
    }
    game_data.ranks.at(rank_id) -= i_at_m75;
    if (game_data.ranks.at(rank_id) >= 10000)
    {
        game_data.ranks.at(rank_id) = 10000;
    }
    if (game_data.ranks.at(rank_id) < 100)
    {
        game_data.ranks.at(rank_id) = 100;
    }
    if (orgrank_at_m75 / 100 != game_data.ranks.at(rank_id) / 100)
    {
        i_at_m75 = game_data.ranks.at(rank_id) / 100 - orgrank_at_m75 / 100;
        if (i_at_m75 < 0)
        {
            Message::instance().txtef(ColorIndex::green);
        }
        else
        {
            Message::instance().txtef(ColorIndex::purple);
        }
        const auto from = orgrank_at_m75 / 100;
        const auto to = game_data.ranks.at(rank_id) / 100;
        txt(i18n::s.get(
            "core.misc.ranking.changed",
            rankn(10, rank_id),
            from,
            to,
            ranktitle(rank_id)));
    }
    else if (i_at_m75 > 0)
    {
        txt(i18n::s.get("core.misc.ranking.closer_to_next_rank"),
            Message::color{ColorIndex::green});
    }
}



int getworker(int map_id, int exclude_with)
{
    int ret = -1;
    for (int i = 1; i < 16; ++i)
    {
        if (exclude_with != 0 && i != exclude_with)
            continue;
        if (cdata[i].current_map == map_id)
        {
            ret = i;
            break;
        }
    }
    return ret;
}



int route_info(int& x, int& y, int n)
{
    if (maxroute == 0)
    {
        return -1;
    }
    if (route(0, n % maxroute) == 1)
    {
        x += route(1, n % maxroute);
    }
    else
    {
        y += route(1, n % maxroute);
    }
    if (n % maxroute % 2 == 0)
    {
        if (route(0, (n + 1) % maxroute) != route(0, n % maxroute))
        {
            return -1;
        }
    }
    if (n >= maxroute)
    {
        if (x < scx || y < scy || x >= scx + inf_screenw ||
            y >= scy + inf_screenh)
        {
            return 0;
        }
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
        {
            return 0;
        }
        if (chip_data.for_cell(x, y).effect & 1)
        {
            return 0;
        }
        if (cell_data.at(x, y).feats != 0)
        {
            cell_featread(x, y);
            if (chip_data[feat].effect & 1)
            {
                return 0;
            }
        }
    }
    if (route(1, n % maxroute) == 0)
    {
        return -1;
    }
    return 1;
}



int breath_list()
{
    int breathw = 0;
    DIM3(breathlist, 2, 100);
    maxbreath = 0;
    breathw = 1;
    dx = cdata[cc].position.x;
    dy = cdata[cc].position.y;
    for (int cnt = 0, cnt_end = cnt + (the_ability_db[efid]->range % 1000 + 1);
         cnt < cnt_end;
         ++cnt)
    {
        if (route(0, cnt % maxroute) == 1)
        {
            dx += route(1, cnt % maxroute);
        }
        else
        {
            dy += route(1, cnt % maxroute);
        }
        if (cnt < 6)
        {
            if (cnt % 3 == 1)
            {
                breathw += 2;
            }
        }
        else
        {
            breathw -= 2;
            if (breathw < 3)
            {
                breathw = 3;
            }
        }
        for (int cnt = 0, cnt_end = (breathw); cnt < cnt_end; ++cnt)
        {
            ty = cnt - breathw / 2 + dy;
            for (int cnt = 0, cnt_end = (breathw); cnt < cnt_end; ++cnt)
            {
                tx = cnt - breathw / 2 + dx;
                if (tx < scx || ty < scy || tx >= scx + inf_screenw ||
                    ty >= scy + inf_screenh)
                {
                    continue;
                }
                if (tx < 0 || ty < 0 || tx >= map_data.width ||
                    ty >= map_data.height)
                {
                    continue;
                }
                if (chip_data.for_cell(tx, ty).effect & 1)
                {
                    continue;
                }
                if (maxbreath >= 100)
                {
                    break;
                }
                p = 0;
                for (int cnt = 0, cnt_end = (maxbreath); cnt < cnt_end; ++cnt)
                {
                    if (breathlist(0, cnt) == tx)
                    {
                        if (breathlist(1, cnt) == ty)
                        {
                            p = 1;
                            break;
                        }
                    }
                }
                if (p == 1)
                {
                    continue;
                }
                breathlist(0, maxbreath) = tx;
                breathlist(1, maxbreath) = ty;
                ++maxbreath;
            }
        }
    }
    return 1;
}



void lenfix(std::string& str, int length)
{
    int p_at_m89 = 0;
    p_at_m89 = length - strlen_u(str);
    if (p_at_m89 < 1)
    {
        p_at_m89 = 1;
    }
    for (int cnt = 0, cnt_end = (p_at_m89); cnt < cnt_end; ++cnt)
    {
        str += u8" "s;
    }
}



int roll(int x, int y, int z)
{
    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;
    int ret = 0;
    for (int i = 0; i < x; ++i)
    {
        ret += rnd(y) + 1;
    }
    return ret + z;
}



int roll_max(int x, int y, int z)
{
    return x * y + z;
}



void page_save()
{
    pagebk = page;
    csprev = cs;
    pagesaved = 1;
}



void page_load()
{
    if (pagesaved == 1)
    {
        page = pagebk;
        cs = csprev;
        pagesaved = 0;
    }
}



std::string fixtxt(const std::string& str, int length)
{
    std::string m_at_m104;
    m_at_m104 = ""s + str;
    if (strlen_u(str) < size_t(length))
    {
        while (1)
        {
            if (strlen_u(m_at_m104) >= size_t(length))
            {
                break;
            }
            m_at_m104 += u8" "s;
        }
    }
    else
    {
        m_at_m104 = ""s + strmid(str, 0, length);
    }
    return ""s + m_at_m104;
}



int direction(int x1, int y1, int x2, int y2)
{
    if (std::abs(x1 - x2) > std::abs(y1 - y2))
    {
        return x1 > x2 ? 1 : 2;
    }
    else
    {
        return y1 > y2 ? 3 : 0;
    }
}



void ride_begin(int mount)
{
    txt(i18n::s.get(
        "core.magic.mount.mount.execute",
        cdata[mount],
        cdata[mount].current_speed));
    cdata[mount].is_ridden() = true;
    cell_data.at(cdata[mount].position.x, cdata[mount].position.y)
        .chara_index_plus_one = 0;
    game_data.mount = mount;
    create_pcpic(cdata.player());
    cdata[game_data.mount].activity.finish();
    refresh_speed(cdata[game_data.mount]);
    txt(""s + cdata[mount].current_speed + u8") "s);
    if (cdata[game_data.mount].is_suitable_for_mount())
    {
        txt(i18n::s.get("core.magic.mount.mount.suitable"));
    }
    else if (cdata[game_data.mount].is_unsuitable_for_mount())
    {
        txt(i18n::s.get("core.magic.mount.mount.unsuitable"));
    }
}



void ride_end()
{
    int mount = game_data.mount;
    cdata[mount].is_ridden() = false;
    cdata[mount].activity.finish();
    game_data.mount = 0;
    create_pcpic(cdata.player());
    refresh_speed(cdata[mount]);
}



void turn_aggro(int cc, int tc, int hate)
{
    if (tc < 16)
    {
        cdata[cc].relationship = -3;
    }
    cdata[cc].hate = hate;
    cdata[cc].emotion_icon = 218;
    cdata[cc].enemy_id = tc;
}



void make_sound(
    int source_x,
    int source_y,
    int distance_threshold,
    int waken,
    int may_make_angry,
    int source_chara_index)
{
    for (int cnt = 1; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (dist(
                source_x,
                source_y,
                cdata[cnt].position.x,
                cdata[cnt].position.y) < distance_threshold)
        {
            if (rnd(waken) == 0)
            {
                if (cdata[cnt].sleep != 0)
                {
                    cdata[cnt].sleep = 0;
                    if (is_in_fov(cdata[cnt]))
                    {
                        txt(i18n::s.get("core.misc.sound.waken", cdata[cnt]));
                    }
                    cdata[cnt].emotion_icon = 221;
                    if (may_make_angry)
                    {
                        if (rnd(500) == 0)
                        {
                            if (is_in_fov(cdata[cnt]))
                            {
                                txt(i18n::s.get(
                                        "core.misc.sound.get_anger",
                                        cdata[cnt]),
                                    Message::color{ColorIndex::cyan});
                                txt(
                                    i18n::s.get("core.misc.sound.can_no_"
                                                "longer_stand"));
                            }
                            turn_aggro(cnt, source_chara_index, 80);
                        }
                    }
                }
            }
        }
    }
}



void hostileaction(int chara_index1, int chara_index2)
{
    if (chara_index1 >= 16 || chara_index2 == 0)
    {
        return;
    }
    if (cdata[chara_index2].relationship != -3)
    {
        cdata[chara_index2].emotion_icon = 418;
    }
    if (cdata[chara_index2].relationship == 10)
    {
        txt(i18n::s.get(
                "core.misc.hostile_action.glares_at_you", cdata[chara_index2]),
            Message::color{ColorIndex::purple});
    }
    else
    {
        if (cdata[chara_index2].relationship == 0)
        {
            modify_karma(cdata.player(), -2);
        }
        if (cdata[chara_index2].id == CharaId::ebon)
        {
            if (game_data.released_fire_giant == 0)
            {
                txt(i18n::s.get(
                        "core.misc.hostile_action.glares_at_you",
                        cdata[chara_index2]),
                    Message::color{ColorIndex::purple});
                return;
            }
        }
        if (cdata[chara_index2].relationship > -2)
        {
            txt(i18n::s.get(
                    "core.misc.hostile_action.glares_at_you",
                    cdata[chara_index2]),
                Message::color{ColorIndex::purple});
            cdata[chara_index2].relationship = -2;
        }
        else
        {
            if (cdata[chara_index2].relationship != -3)
            {
                txt(i18n::s.get(
                        "core.misc.hostile_action.gets_furious",
                        cdata[chara_index2]),
                    Message::color{ColorIndex::purple});
            }
            cdata[chara_index2].relationship = -3;
            cdata[chara_index2].hate = 80;
            cdata[chara_index2].enemy_id = chara_index1;
        }
        chara_custom_talk(chara_index2, 101);
    }
    if (cdata[chara_index2].is_livestock() == 1)
    {
        if (rnd(50) == 0)
        {
            txt(i18n::s.get("core.misc.hostile_action.get_excited"),
                Message::color{ColorIndex::red});
            for (auto&& cnt : cdata.all())
            {
                if (cnt.is_livestock() == 1)
                {
                    cnt.enemy_id = 0;
                    cnt.hate = 20;
                    cnt.emotion_icon = 318;
                }
            }
        }
    }
    cdata[chara_index2].activity.finish();
}



void wake_up()
{
    if (game_data.date.hour >= 7 && game_data.date.hour <= 22)
    {
        for (auto&& cnt : cdata.others())
        {
            if (cnt.sleep > 0)
            {
                if (rnd(10))
                {
                    cnt.sleep = 0;
                }
            }
        }
    }
}



void incognitobegin()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[cnt].character_role == 1010)
        {
            continue;
        }
        if (cdata[cnt].character_role == 16)
        {
            continue;
        }
        if (cdata[cnt].original_relationship >= -2)
        {
            if (cdata[cnt].relationship <= -2)
            {
                cdata[cnt].hate = 0;
                cdata[cnt].relationship = cdata[cnt].original_relationship;
                cdata[cnt].emotion_icon = 221;
            }
        }
    }
}



void incognitoend()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cdata[cnt].character_role == 14)
        {
            if (cdata.player().karma < -30)
            {
                cdata[cnt].relationship = -3;
                cdata[cnt].hate = 80;
                cdata[cnt].emotion_icon = 218;
            }
        }
    }
}



void animeload(int animation_type, int chara_index)
{
    elona_vector1<int> i_at_m133;
    if (mode != 0)
    {
        return;
    }
    if (is_in_fov(cdata[chara_index]) == 0)
    {
        return;
    }
    if (g_config.animation_wait() == 0)
    {
        return;
    }
    screenupdate = -1;
    update_screen();
    dx_at_m133 =
        (cdata[chara_index].position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133 =
        (cdata[chara_index].position.y - scy) * inf_tiles + inf_screeny;
    gsel(7);
    picload(
        filesystem::dirs::graphic() / (u8"anime"s + animation_type + u8".bmp"),
        0,
        0,
        true);
    gsel(4);
    gmode(0);
    gcopy(0, dx_at_m133 - 24, dy_at_m133 - 40, 96, 96, 0, 0);
    gsel(0);
    gmode(2);
    i_at_m133(0) = 5;
    i_at_m133(1) = g_config.animation_wait() * 3.5;
    r_at_m133 = 0;
    if (animation_type == 8)
    {
        snd("core.offer1");
    }
    if (animation_type == 10)
    {
        i_at_m133(0) = 8;
        i_at_m133(1) = g_config.animation_wait() * 2.5;
        r_at_m133 = 0.2;
        snd("core.enc2");
    }
    if (animation_type == 11)
    {
        i_at_m133(0) = 5;
        i_at_m133(1) = g_config.animation_wait() * 3.5;
        r_at_m133 = 0;
        snd("core.enc");
    }
    if (animation_type == 14)
    {
        i_at_m133(0) = 6;
        i_at_m133(1) = g_config.animation_wait() * 3.5;
    }
    for (int cnt = 0, cnt_end = (i_at_m133); cnt < cnt_end; ++cnt)
    {
        gmode(2);
        grotate(
            7,
            cnt * 96,
            0,
            96,
            96,
            dx_at_m133 + 24,
            dy_at_m133 + 8,
            r_at_m133 * cnt);
        gmode(0);
        redraw();
        gcopy(4, 0, 0, 96, 96, dx_at_m133 - 24, dy_at_m133 - 40);
        await(i_at_m133(1));
    }
    gmode(2);
}



void animeblood(int cc, int animation_type, int element)
{
    if (is_in_fov(cdata[cc]) == 0)
        return;
    if (g_config.animation_wait() == 0)
        return;

    int cnt2_at_m133 = 0;

    screenupdate = -1;
    update_screen();

    if (animation_type == 0)
    {
        prepare_item_image(16, 0);
    }
    if (animation_type == 1)
    {
        prepare_item_image(18, 0);
    }
    dx_at_m133 = (cdata[cc].position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133(0) = (cdata[cc].position.y - scy) * inf_tiles + inf_screeny;
    dy_at_m133(1) = 0;
    gsel(4);
    gmode(0);
    gcopy(0, dx_at_m133 - 48, dy_at_m133 - 56, 144, 160, 0, 0);

    int ele2_at_m133 = 1;
    gsel(7);
    switch (element)
    {
    case 52:
        picload(filesystem::dirs::graphic() / u8"anime18.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 51:
        picload(filesystem::dirs::graphic() / u8"anime19.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 50:
        picload(filesystem::dirs::graphic() / u8"anime20.bmp", 0, 0, true);
        dy_at_m133(1) = -20;
        break;
    case 56:
        picload(filesystem::dirs::graphic() / u8"anime22.bmp", 0, 0, true);
        dy_at_m133(1) = -24;
        break;
    case 53:
        picload(filesystem::dirs::graphic() / u8"anime21.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 54:
        picload(filesystem::dirs::graphic() / u8"anime23.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 57:
        picload(filesystem::dirs::graphic() / u8"anime24.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 59:
        picload(filesystem::dirs::graphic() / u8"anime25.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 58:
        picload(filesystem::dirs::graphic() / u8"anime26.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 55:
    case 63:
        picload(filesystem::dirs::graphic() / u8"anime27.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    default: ele2_at_m133 = 0; break;
    }

    gmode(2);
    gsel(0);

    elona_vector1<int> x_at_m133;
    elona_vector1<int> y_at_m133;
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        x_at_m133(cnt) = rnd(48) - 24;
        y_at_m133(cnt) = rnd(16);
    }

    for (int cnt = 0; cnt < 6; ++cnt)
    {
        cnt2_at_m133 = cnt * 2;
        gmode(2);
        if (ele2_at_m133)
        {
            gcopy(
                7,
                cnt * 96,
                0,
                96,
                96,
                dx_at_m133 - 24,
                dy_at_m133 - 32 + dy_at_m133(1));
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                dx_at_m133 + 24 + x_at_m133(cnt) +
                    (x_at_m133(cnt) < 3) * ((1 + (cnt % 2 == 0)) * -1) *
                        cnt2_at_m133 +
                    (x_at_m133(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2_at_m133,
                dy_at_m133 + y_at_m133(cnt) + cnt2_at_m133 * cnt2_at_m133 / 2 -
                    12 + cnt,
                24 - cnt2_at_m133 * 2,
                24 - cnt2_at_m133 * 2,
                0.2 * cnt);
        }
        gmode(0);
        redraw();
        gcopy(4, 0, 0, 144, 160, dx_at_m133 - 48, dy_at_m133 - 56);
        await(g_config.animation_wait() * (ele2_at_m133 == 0 ? 1.75 : 2.75));
    }

    gmode(2);
}



void spillblood(int x, int y, int range)
{
    for (int cnt = 0, cnt_end = (range + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = x;
            dy_at_m136 = y;
        }
        else
        {
            dx_at_m136 = x + rnd(2) - rnd(2);
            dy_at_m136 = y + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0 ||
            dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chip_data.for_cell(dx_at_m136, dy_at_m136).wall_kind)
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10 < 5)
        {
            ++cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments;
        }
    }
}



void spillfrag(int x, int y, int range)
{
    for (int cnt = 0, cnt_end = (range + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = x;
            dy_at_m136 = y;
        }
        else
        {
            dx_at_m136 = x + rnd(2) - rnd(2);
            dy_at_m136 = y + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0 ||
            dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chip_data.for_cell(dx_at_m136, dy_at_m136).wall_kind)
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10 < 4)
        {
            cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments =
                cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10 +
                (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10 +
                 1) *
                    10;
        }
    }
}



void check_kill(int killer_chara_index, int victim_chara_index)
{
    int p_at_m137 = 0;
    if (game_data.current_map == mdata_t::MapId::pet_arena ||
        game_data.current_map == mdata_t::MapId::show_house ||
        game_data.current_map == mdata_t::MapId::arena)
    {
        return;
    }
    p_at_m137 = 0;
    if (killer_chara_index >= 0)
    {
        if (killer_chara_index == 0 ||
            cdata[killer_chara_index].relationship >= 10)
        {
            if (victim_chara_index >= 16)
            {
                ++game_data.kill_count;
                if (cdata[victim_chara_index].id ==
                    int2charaid(game_data.guild.fighters_guild_target))
                {
                    if (game_data.guild.fighters_guild_quota > 0)
                    {
                        --game_data.guild.fighters_guild_quota;
                    }
                }
                if (cdata[victim_chara_index].original_relationship >= 0)
                {
                    p_at_m137 = -2;
                }
                if (cdata[victim_chara_index].id == CharaId::rich_person)
                {
                    p_at_m137 = -15;
                }
                if (cdata[victim_chara_index].id == CharaId::noble_child)
                {
                    p_at_m137 = -10;
                }
                if (cdata[victim_chara_index].id == CharaId::tourist)
                {
                    p_at_m137 = -5;
                }
                if ((cdata[victim_chara_index].character_role >= 1000 &&
                     cdata[victim_chara_index].character_role < 2000) ||
                    cdata[victim_chara_index].character_role == 2003)
                {
                    p_at_m137 = -10;
                }
                if (cdata[victim_chara_index].character_role == 13)
                {
                    chara_modify_impression(cdata[victim_chara_index], -25);
                }
            }
        }
        if (cdata[killer_chara_index].relationship >= 10)
        {
            if (killer_chara_index != 0)
            {
                if (cdata[killer_chara_index].impression < 200)
                {
                    if (rnd(2))
                    {
                        chara_modify_impression(cdata[killer_chara_index], 1);
                        cdata[killer_chara_index].emotion_icon = 317;
                    }
                }
                else if (rnd(10) == 0)
                {
                    chara_modify_impression(cdata[killer_chara_index], 1);
                    cdata[killer_chara_index].emotion_icon = 317;
                }
            }
        }
    }
    if (p_at_m137 != 0)
    {
        modify_karma(cdata.player(), p_at_m137);
    }
}



std::string cnveqweight(int cc)
{
    int id = chara_armor_class(cdata[cc]);
    if (id == 169)
    {
        return i18n::s.get("core.item.armor_class.heavy");
    }
    else if (id == 170)
    {
        return i18n::s.get("core.item.armor_class.medium");
    }
    else
    {
        return i18n::s.get("core.item.armor_class.light");
    }
}



void cnvbonus(int ability_id, int bonus)
{
    // TODO: i18n
    if (ability_id >= 50 && ability_id < 61)
    {
        if (bonus > 0)
        {
            buff += u8"　　"s +
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(ability_id)->get(),
                    "name") +
                u8"耐性に <green>クラス"s + bonus / 50 + u8"<col>("s + bonus +
                u8") のボーナス\n"s;
        }
        if (bonus < 0)
        {
            buff += u8"　　"s +
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(ability_id)->get(),
                    "name") +
                u8"耐性に <red>クラス"s + bonus / 50 + u8"<col>("s + bonus +
                u8") のマイナス修正\n"s;
        }
    }
    else
    {
        if (bonus > 0)
        {
            buff += u8"　　"s +
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(ability_id)->get(),
                    "name") +
                u8"に <green>+"s + bonus + u8"<col> のボーナス\n"s;
        }
        if (bonus < 0)
        {
            buff += u8"　　"s +
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(ability_id)->get(),
                    "name") +
                u8"に <red>"s + bonus + u8"<col> のマイナス修正\n"s;
        }
    }
}



void wet(int cc, int turns)
{
    cdata[cc].wet += turns;
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.misc.wet.gets_wet", cdata[cc]));
        if (cdata[cc].is_invisible())
        {
            txt(i18n::s.get("core.misc.wet.is_revealed", cdata[cc]));
        }
    }
}



int try_to_cast_spell()
{
    int r4 = 0;
    f = 1;
    tc = cc;
    if (cdata[cc].blind != 0)
    {
        f = 0;
    }
    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (rnd(4) != 0)
        {
            f = 0;
        }
    }
    else
    {
        if (r3 == 0)
        {
            r4 = sdata(16, cc);
        }
        else
        {
            r4 = sdata(the_ability_db[r3]->related_basic_attribute, cc);
        }
        if (rnd(sdata(150, cc) * r4 * 4 + 250) < rnd(r2 + 1))
        {
            if (rnd(7) == 0)
            {
                f = 0;
            }
            if (r4 * 10 < r2)
            {
                if (rnd(r4 * 10 + 1) < rnd(r2 + 1))
                {
                    f = 0;
                }
            }
            if (r4 * 20 < r2)
            {
                if (rnd(r4 * 20 + 1) < rnd(r2 + 1))
                {
                    f = 0;
                }
            }
            if (r4 * 30 < r2)
            {
                if (rnd(r4 * 30 + 1) < rnd(r2 + 1))
                {
                    f = 0;
                }
            }
        }
    }
    if (f == 1)
    {
        return 1;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.misc.fail_to_cast.mana_is_absorbed", cdata[cc]));
        }
        if (cc == 0)
        {
            damage_mp(cdata[cc], cdata[cc].max_mp);
        }
        else
        {
            damage_mp(cdata[cc], cdata[cc].max_mp / 3);
        }
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (cdata[cc].confused != 0)
            {
                txt(i18n::s.get(
                    "core.misc.fail_to_cast.is_confused_more", cdata[cc]));
            }
            else
            {
                txt(i18n::s.get("core.misc.fail_to_cast.too_difficult"));
            }
        }
        status_ailment_damage(cdata[cc], StatusAilment::confused, 100);
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.misc.fail_to_cast.creatures_are_summoned"));
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                calcfixlv(Quality::bad));
            int stat =
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get(
            "core.misc.fail_to_cast.dimension_door_opens", cdata[cc]));
    }
    tc = cc;
    efid = 408;
    magic();
    return 0;
}



int try_to_reveal()
{
    if (rnd(sdata(159, cc) * 15 + 20 + sdata(13, cc)) >
        rnd(game_data.current_dungeon_level * 8 + 60))
    {
        chara_gain_exp_detection(cdata[cc]);
        return 1;
    }
    return 0;
}



int can_evade_trap()
{
    if (feat(2) == 7)
    {
        return 0;
    }
    if (cc < 16)
    {
        if (rnd(refdiff + 1) < sdata(13, cc) + sdata(159, cc) * 4)
        {
            return 1;
        }
    }
    else if (rnd(4) != 0)
    {
        return 1;
    }
    return 0;
}



int try_to_disarm_trap()
{
    if (rnd(sdata(175, cc) * 15 + 20 + sdata(12, cc)) >
        rnd(game_data.current_dungeon_level * 12 + 100))
    {
        chara_gain_exp_disarm_trap(cdata[cc]);
        return 1;
    }
    return 0;
}



int try_to_perceive_npc(int cc)
{
    int cv = 0;
    cv = 8;
    if (cdata[cc].position.x > cdata[r2].position.x - cv &&
        cdata[cc].position.x < cdata[r2].position.x + cv)
    {
        if (cdata[cc].position.y > cdata[r2].position.y - cv &&
            cdata[cc].position.y < cdata[r2].position.y + cv)
        {
            if (cdata[r2].hate > 0)
            {
                return 1;
            }
            p = dist(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[r2].position.x,
                    cdata[r2].position.y) *
                    150 +
                (sdata(157, cc) * 100 + 150) + 1;
            if (rnd(p(0)) < rnd(sdata(13, r2) * 60 + 150))
            {
                return 1;
            }
        }
    }
    return 0;
}



void start_stealing()
{
    game_data.activity_about_to_start = 105;
    activity_others();
}



void proc_turn_end(int cc)
{
    int regen = 0;
    regen = 1;
    if (cdata[cc].sleep > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::sleep, 1);
        if (cdata[cc].sleep > 0)
        {
            cdata[cc].emotion_icon = 114;
        }
        heal_hp(cdata[cc], 1);
        heal_mp(cdata[cc], 1);
    }
    if (cdata[cc].poisoned > 0)
    {
        damage_hp(cdata[cc], rnd(2 + sdata(11, cc) / 10), -4);
        status_ailment_heal(cdata[cc], StatusAilment::poisoned, 1);
        if (cdata[cc].poisoned > 0)
        {
            cdata[cc].emotion_icon = 108;
        }
        regen = 0;
    }
    if (cdata[cc].choked > 0)
    {
        if (cdata[cc].choked % 3 == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.misc.status_ailment.choked"));
            }
        }
        ++cdata[cc].choked;
        if (cdata[cc].choked > 15)
        {
            damage_hp(cdata[cc], 500, -21);
        }
        regen = 0;
    }
    if (cdata[cc].gravity > 0)
    {
        --cdata[cc].gravity;
        if (cdata[cc].gravity == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.misc.status_ailment.breaks_away_from_gravity",
                    cdata[cc]));
            }
        }
    }
    if (cdata[cc].furious > 0)
    {
        --cdata[cc].furious;
        if (cdata[cc].furious == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.misc.status_ailment.calms_down", cdata[cc]));
            }
        }
    }
    if (cdata[cc].sick > 0)
    {
        if (rnd(80) == 0)
        {
            p = rnd(10);
            if (!enchantment_find(cdata[cc], 60010 + p))
            {
                cdata[cc].attr_adjs[p] -=
                    sdata.get(10 + p, cc).original_level / 25 + 1;
                chara_refresh(cc);
            }
        }
        if (rnd(5))
        {
            regen = 0;
        }
        if (cc >= 16)
        {
            if (cdata[cc].quality >= Quality::miracle)
            {
                if (rnd(200) == 0)
                {
                    status_ailment_heal(cdata[cc], StatusAilment::sick);
                }
            }
        }
    }
    if (cdata[cc].blind > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::blinded, 1);
        if (cdata[cc].blind > 0)
        {
            cdata[cc].emotion_icon = 110;
        }
    }
    if (cdata[cc].paralyzed > 0)
    {
        regen = 0;
        status_ailment_heal(cdata[cc], StatusAilment::paralyzed, 1);
        if (cdata[cc].paralyzed > 0)
        {
            cdata[cc].emotion_icon = 115;
        }
    }
    if (cdata[cc].confused > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::confused, 1);
        if (cdata[cc].confused > 0)
        {
            cdata[cc].emotion_icon = 111;
        }
    }
    if (cdata[cc].fear > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::fear, 1);
        if (cdata[cc].fear > 0)
        {
            cdata[cc].emotion_icon = 113;
        }
    }
    if (cdata[cc].dimmed > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::dimmed, 1);
        if (cdata[cc].dimmed > 0)
        {
            cdata[cc].emotion_icon = 112;
        }
    }
    if (cdata[cc].drunk > 0)
    {
        status_ailment_heal(cdata[cc], StatusAilment::drunk, 1);
        if (cdata[cc].drunk > 0)
        {
            cdata[cc].emotion_icon = 106;
        }
    }
    if (cdata[cc].bleeding > 0)
    {
        damage_hp(
            cdata[cc],
            rnd(cdata[cc].hp * (1 + cdata[cc].bleeding / 4) / 100 + 3) + 1,
            -13);
        status_ailment_heal(
            cdata[cc],
            StatusAilment::bleeding,
            1 + cdata[cc].cures_bleeding_quickly() * 3);
        if (cdata[cc].bleeding > 0)
        {
            cdata[cc].emotion_icon = 109;
        }
        regen = 0;
        spillblood(cdata[cc].position.x, cdata[cc].position.y);
    }
    if (cdata[cc].wet > 0)
    {
        --cdata[cc].wet;
    }
    if (cdata[cc].insane > 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (rnd(3) == 0)
            {
                txt(i18n::s.get("core.misc.status_ailment.insane", cdata[cc]),
                    Message::color{ColorIndex::cyan});
            }
        }
        if (rnd(5) == 0)
        {
            cdata[cc].confused += rnd(10);
        }
        if (rnd(5) == 0)
        {
            cdata[cc].dimmed += rnd(10);
        }
        if (rnd(5) == 0)
        {
            cdata[cc].sleep += rnd(5);
        }
        if (rnd(5) == 0)
        {
            cdata[cc].fear += rnd(10);
        }
        status_ailment_heal(cdata[cc], StatusAilment::insane, 1);
        if (cdata[cc].insane > 0)
        {
            cdata[cc].emotion_icon = 124;
        }
    }
    if (cc == 0)
    {
        if (cdata[cc].nutrition < 2000)
        {
            if (cdata[cc].nutrition < 1000)
            {
                if (cdata[cc].activity.type != Activity::Type::eat)
                {
                    damage_hp(
                        cdata[cc], rnd(2) + cdata.player().max_hp / 50, -3);
                    if (game_data.play_turns % 10 == 0)
                    {
                        rowact_check(cc);
                        if (rnd(50) == 0)
                        {
                            modify_weight(cdata[cc], -1);
                        }
                    }
                }
            }
            regen = 0;
        }
        if (game_data.continuous_active_hours >= 30)
        {
            if (debug::voldemort)
            {
                game_data.continuous_active_hours = 0;
            }
            if (game_data.play_turns % 100 == 0)
            {
                txt(i18n::s.get("core.misc.status_ailment.sleepy"));
            }
            if (rnd(2))
            {
                regen = 0;
            }
            if (game_data.continuous_active_hours >= 50)
            {
                regen = 0;
                damage_sp(cdata[cc], 1);
            }
        }
    }
    else if (cdata[cc].related_quest_id != 0)
    {
        p = cdata[cc].related_quest_id - 1;
        if (quest_data[p].delivery_has_package_flag > 0)
        {
            cdata[cc].emotion_icon = 122;
        }
        if (quest_data[p].progress != 0)
        {
            if (cdata[cc].turn % 2 == 1)
            {
                cdata[cc].emotion_icon = 123;
            }
        }
    }
    if (game_data.executing_immediate_quest_type == 1009)
    {
        if (cc >= 57)
        {
            if (cdata[cc].impression >= 53)
            {
                cdata[cc].emotion_icon = 225;
            }
        }
    }
    if (regen == 1)
    {
        if (rnd(6) == 0)
        {
            heal_hp(cdata[cc], rnd(sdata(154, cc) / 3 + 1) + 1);
        }
        if (rnd(5) == 0)
        {
            heal_mp(cdata[cc], rnd(sdata(155, cc) / 2 + 1) + 1);
        }
    }
}



void refresh_burden_state()
{
    cdata.player().inventory_weight = clamp(inv_weight(0), 0, 20000000) *
        (100 - trait(201) * 10 + trait(205) * 20) / 100;
    cdata.player().max_inventory_weight =
        sdata(10, 0) * 500 + sdata(11, 0) * 250 + sdata(153, 0) * 2000 + 45000;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight * 2)
        {
            cdata.player().inventory_weight_type = 4;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight)
        {
            cdata.player().inventory_weight_type = 3;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight / 4 * 3)
        {
            cdata.player().inventory_weight_type = 2;
            break;
        }
        if (cdata.player().inventory_weight >
            cdata.player().max_inventory_weight / 2)
        {
            cdata.player().inventory_weight_type = 1;
            break;
        }
        cdata.player().inventory_weight_type = 0;
    }
    refresh_speed(cdata.player());
}



void revive_character()
{
    do_chara_revival();
    cxinit = cdata.player().position.x;
    cyinit = cdata.player().position.y;
    chara_place();
    cdata[rc].current_map = 0;
    snd("core.pray1");
    txt(i18n::s.get("core.misc.resurrect", cdatan(0, rc), cdata[rc]),
        Message::color{ColorIndex::orange});
}



void do_chara_revival()
{
    chara_set_revived_status();
    chara_clear_status_effects();
}



void chara_clear_status_effects_b()
{
    chara_clear_status_effects();
}



void chara_set_revived_status()
{
    cdata[rc].will_explode_soon() = false;
    cdata[rc].is_sentenced_daeth() = false;
    cdata[rc].is_pregnant() = false;
    cdata[rc].is_contracting_with_reaper() = false;
    cdata[rc].has_anorexia() = false;
    cdata[rc].hp = cdata[rc].max_hp / 3;
    cdata[rc].mp = cdata[rc].max_mp / 3;
    cdata[rc].sp = cdata[rc].max_sp / 3;
    cdata[rc].insanity = 0;
    cdata[rc].current_map = 0;
    cdata[rc].relationship = cdata[rc].original_relationship;
    cdata[rc].nutrition = 8000;
    cdata[rc].set_state(Character::State::alive);
}



void chara_clear_status_effects()
{
    cdata[rc].is_contracting_with_reaper() = false;
    cdata[rc].activity.finish();
    cdata[rc].poisoned = 0;
    cdata[rc].sleep = 0;
    cdata[rc].confused = 0;
    cdata[rc].blind = 0;
    cdata[rc].paralyzed = 0;
    cdata[rc].choked = 0;
    cdata[rc].furious = 0;
    cdata[rc].dimmed = 0;
    cdata[rc].drunk = 0;
    cdata[rc].bleeding = 0;
    cdata[rc].gravity = 0;
    cdata[rc].item_which_will_be_used = 0;
    cdata[rc].hate = 0;
    cdata[rc].enemy_id = 0;
    cdata[rc].sick = 0;
    cdata[rc].emotion_icon = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        cdata[rc].attr_adjs[cnt] = 0;
    }
    if (cdata[rc].buffs[0].id != 0)
    {
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[rc].buffs[cnt].id == 0)
            {
                break;
            }
            if (cdata[rc].buffs[cnt].id == 13)
            {
                continue;
            }
            buff_delete(cdata[rc], cnt);
            --cnt;
            continue;
        }
    }
    chara_refresh(rc);
}



void revive_player()
{
    do_chara_revival();
    if (rc == 0)
    {
        game_data.is_returning_or_escaping = 0;
        traveldone = 0;
        if (game_data.executing_immediate_quest_type == 0)
        {
            event_add(6);
        }
    }
    if (cdata[rc].character_role == 1)
    {
        cdata[rc].relationship = 0;
    }
    if (cdata[rc].character_role == 14)
    {
        p = rnd(5) + 1;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            r2 = 1;
            gain_level(cdata[rc]);
        }
    }
    if (cdata[rc].id == CharaId::bard)
    {
        chara_gain_fixed_skill_exp(cdata[rc], 183, 1000);
    }
    chara_refresh(rc);
}



int convertartifact(int item_index, int ignore_external_container)
{
    int f_at_m163 = 0;
    int tc_at_m163 = 0;
    std::string n_at_m163;
    if (the_item_db[itemid2int(inv[item_index].id)]->category >= 50000)
    {
        return item_index;
    }
    if (inv[item_index].quality != Quality::special)
    {
        return item_index;
    }
    if (inv[item_index].body_part != 0)
    {
        return item_index;
    }
    f_at_m163 = 0;
    for (int cnt = 0; cnt < ELONA_MAX_ITEMS; ++cnt)
    {
        if (ignore_external_container)
        {
            if (cnt >= ELONA_ITEM_ON_GROUND_INDEX)
            {
                break;
            }
        }
        if (cnt >= 520 && cnt < 5060)
        {
            continue;
        }
        tc_at_m163 = inv_getowner(cnt);
        if (tc_at_m163 != -1)
        {
            if (cdata[tc_at_m163].state() == Character::State::empty ||
                cdata[tc_at_m163].character_role == 13)
            {
                continue;
            }
        }
        if (inv[cnt].number() > 0)
        {
            if (inv[cnt].id == inv[item_index].id)
            {
                if (cnt != item_index)
                {
                    f_at_m163 = 1;
                    break;
                }
            }
        }
    }
    if (f_at_m163 == 0)
    {
        return item_index;
    }
    n_at_m163 = ""s + itemname(item_index);

    while (1)
    {
        flt(the_item_db[itemid2int(inv[item_index].id)]->level,
            Quality::miracle);
        flttypeminor = the_item_db[itemid2int(inv[item_index].id)]->subcategory;
        inv[item_index].remove();

        itemcreate(
            inv_getowner(item_index),
            0,
            inv[item_index].position.x,
            inv[item_index].position.y,
            0);
        if (inv[item_index].quality != Quality::special)
        {
            break;
        }
    }

    txt(i18n::s.get("core.misc.artifact_regeneration", n_at_m163, inv[ci]));
    return item_index;
}



void initialize_set_of_random_generation()
{
    fsetincome(0) = 52000;
    fsetincome(1) = 52000;
    fsetincome(2) = 52000;
    fsetincome(3) = 53000;
    fsetincome(4) = 53000;
    fsetincome(5) = 56000;
    fsetincome(6) = 54000;
    fsetincome(7) = 77000;
    fsetincome(8) = 57000;
    fsetincome(9) = 57000;
    fsetchest(0) = 10000;
    fsetchest(1) = 24000;
    fsetchest(2) = 12000;
    fsetchest(3) = 16000;
    fsetchest(4) = 20000;
    fsetchest(5) = 19000;
    fsetchest(6) = 18000;
    fsetchest(7) = 22000;
    fsetchest(8) = 14000;
    fsetchest(9) = 32000;
    fsetchest(10) = 34000;
    fsetchest(11) = 54000;
    fsetchest(12) = 59000;
    fsetwear(0) = 10000;
    fsetwear(1) = 10000;
    fsetwear(2) = 24000;
    fsetwear(3) = 24000;
    fsetwear(4) = 25000;
    fsetwear(5) = 12000;
    fsetwear(6) = 16000;
    fsetwear(7) = 20000;
    fsetwear(8) = 19000;
    fsetwear(9) = 18000;
    fsetwear(10) = 22000;
    fsetwear(11) = 14000;
    fsetwear(12) = 32000;
    fsetwear(13) = 34000;
    fsetitem(0) = 52000;
    fsetitem(1) = 52000;
    fsetitem(2) = 53000;
    fsetitem(3) = 53000;
    fsetitem(4) = 56000;
    fsetitem(5) = 68000;
    fsetitem(6) = 54000;
    fsetitem(7) = 64000;
    fsetitem(8) = 59000;
    fsetitem(9) = 55000;
    fsetrewardsupply(0) = 52000;
    fsetrewardsupply(1) = 53000;
    fsetrewardsupply(2) = 56000;
    fsetrewardsupply(3) = 54000;
    fsetrewardsupply(4) = 57000;
    fsetrare(0) = 60000;
    fsetrare(1) = 72000;
    fsetrare(2) = 77000;
    fsetrare(3) = 55000;
    fsetrare(4) = 57000;
    fsetperform(0) = 77000;
    fsetperform(1) = 57000;
    fsetperform(2) = 57000;
    fsetperform(3) = 57000;
    fsetperform(4) = 60000;
    fsetperform(5) = 18000;
    fsetperform(6) = 20000;
    fsetperform(7) = 32000;
    fsetperform(8) = 34000;
    fsetperform(9) = 52000;
    fsetperform(10) = 64000;
    fsetperform(11) = 64000;
    fsetdeliver(0) = 60000;
    fsetdeliver(1) = 77000;
    fsetdeliver(2) = 54000;
    fsetdeliver(3) = 64000;
    fsetsupply(0) = 60000;
    fsetsupply(1) = 77000;
    fsetsupply(2) = 56000;
    fsetsupply(3) = 54000;
    fsetsupply(4) = 64000;
    fsetmagic(0) = 53000;
    fsetmagic(1) = 56000;
    fsetmagic(2) = 54000;
    fsetarmor(0) = 12000;
    fsetarmor(1) = 16000;
    fsetarmor(2) = 20000;
    fsetarmor(3) = 19000;
    fsetarmor(4) = 18000;
    fsetarmor(5) = 22000;
    fsetarmor(6) = 14000;
    fsetweapon(0) = 10000;
    fsetweapon(1) = 24000;
    fsetweapon(2) = 25000;
    fsetplantartifact(0) = 32000;
    fsetplantartifact(1) = 34000;
    fsetplantunknown(0) = 57000;
    fsetplantunknown(1) = 57000;
    fsetplantunknown(2) = 54000;
    fsetplantunknown(3) = 64000;
    fsetplantunknown(4) = 77000;
    fsetbarrel(0) = 25000;
    fsetbarrel(1) = 57000;
    fsetbarrel(2) = 53000;
    fsetbarrel(3) = 52000;
    fsetbarrel(4) = 77000;
    fsetbarrel(5) = 64000;
    fsetcollect(0) = 64000;
    fsetcollect(1) = 60000;
    fsetcollect(2) = 57000;
    fsetcollect(3) = 77000;
    isetfruit(0) = 180;
    isetfruit(1) = 181;
    isetfruit(2) = 196;
    isetfruit(3) = 197;
    isetfruit(4) = 192;
    isetfruit(5) = 183;
    isetthrowpotionminor(0) = 27;
    isetthrowpotionminor(1) = 28;
    isetthrowpotionminor(2) = 376;
    isetthrowpotionminor(3) = 30;
    isetthrowpotionminor(4) = 262;
    isetthrowpotionminor(5) = 253;
    isetthrowpotionminor(6) = 379;
    isetthrowpotionminor(7) = 392;
    isetthrowpotionmajor(0) = 28;
    isetthrowpotionmajor(1) = 376;
    isetthrowpotionmajor(2) = 205;
    isetthrowpotionmajor(3) = 368;
    isetthrowpotionmajor(4) = 433;
    isetthrowpotionmajor(5) = 382;
    isetthrowpotionmajor(6) = 577;
    isetthrowpotionmajor(7) = 577;
    isetthrowpotiongreater(0) = 28;
    isetthrowpotiongreater(1) = 205;
    isetthrowpotiongreater(2) = 368;
    isetthrowpotiongreater(3) = 432;
    isetthrowpotiongreater(4) = 429;
    isetthrowpotiongreater(5) = 29;
    isetthrowpotiongreater(6) = 577;
    isethire(0) = 205;
    isethire(1) = 70;
    isethire(2) = 74;
    isethire(3) = 41;
    isethire(4) = 69;
    isethire(5) = 76;
    isethire(6) = 1;
    isethire(7) = 1;
    isethire(8) = 1;
    isetgiftminor(0) = 753;
    isetgiftminor(1) = 754;
    isetgiftminor(2) = 754;
    isetgiftminor(3) = 756;
    isetgiftminor(4) = 756;
    isetgiftminor(5) = 540;
    isetgiftminor(6) = 541;
    isetgiftminor(7) = 537;
    isetgiftminor(8) = 538;
    isetgiftminor(9) = 526;
    isetgiftminor(10) = 415;
    isetgiftminor(11) = 511;
    isetgiftminor(12) = 343;
    isetgiftminor(13) = 340;
    isetgiftminor(14) = 338;
    isetgiftminor(15) = 328;
    isetgiftminor(16) = 220;
    isetgiftminor(17) = 575;
    isetgiftminor(18) = 622;
    isetgiftminor(19) = 167;
    isetgiftmajor(0) = 755;
    isetgiftmajor(1) = 755;
    isetgiftmajor(2) = 633;
    isetgiftmajor(3) = 626;
    isetgiftmajor(4) = 502;
    isetgiftmajor(5) = 632;
    isetgiftmajor(6) = 667;
    isetgiftmajor(7) = 555;
    isetgiftmajor(8) = 748;
    isetgiftmajor(9) = 640;
    isetgiftgrand(0) = 757;
    isetgiftgrand(1) = 558;
    isetgiftgrand(2) = 664;
    isetgiftgrand(3) = 758;
    isetgiftgrand(4) = 759;
    isetgiftgrand(5) = 761;
    isethirerole(0) = 18;
    isethirerole(1) = 9;
    isethirerole(2) = 12;
    isethirerole(3) = 5;
    isethirerole(4) = 8;
    isethirerole(5) = 14;
    isethirerole(6) = 1008;
    isethirerole(7) = 1008;
    isethirerole(8) = 1008;
    isetcrop(0) = 180;
    isetcrop(1) = 181;
    isetcrop(2) = 197;
    isetcrop(3) = 192;
    isetcrop(4) = 183;
    isetcrop(5) = 188;
    isetcrop(6) = 200;
    isetgod(0) = 0;
    isetgod(1) = 1;
    isetgod(2) = 2;
    isetgod(3) = 3;
    isetgod(4) = 4;
    isetgod(5) = 5;
    isetgod(6) = 6;
    isetgod(7) = 7;
    asettown(0) = 5;
    asettown(1) = 11;
    asettown(2) = 14;
    asettown(3) = 15;
    asettown(4) = 12;
    moneybox(0) = 500;
    moneybox(1) = 2000;
    moneybox(2) = 10000;
    moneybox(3) = 50000;
    moneybox(4) = 500000;
    moneybox(5) = 5000000;
    moneybox(6) = 100000000;
    giftvalue(0) = 10;
    giftvalue(1) = 20;
    giftvalue(2) = 30;
    giftvalue(3) = 50;
    giftvalue(4) = 75;
    giftvalue(5) = 100;

    bool in_booktitle_definition = false;
    int isetbook_index = 0;
    for (const auto& line : fileutil::read_by_line(
             i18n::s.get_locale_dir("core") / "lazy" / "book.txt"))
    {
        if (line == u8"%DEFINE")
        {
            in_booktitle_definition = true;
        }
        else if (line == u8"%END")
        {
            break;
        }
        else if (in_booktitle_definition)
        {
            // E.g., 7,Book Title,T
            const auto columns = strutil::split(line, ',');
            const auto id = elona::stoi(columns.at(0));
            const auto& title = columns.at(1);
            const auto is_generated = columns.at(2) == "T";

            booktitle(id) = title;
            if (is_generated)
            {
                isetbook(isetbook_index) = id;
                ++isetbook_index;
            }
        }
    }
}



void character_drops_item()
{
    if (rc == 0)
    {
        if (game_data.executing_immediate_quest_type != 0)
        {
            return;
        }
        for (auto&& item : inv.for_chara(cdata[rc]))
        {
            ci = item.index;
            if (item.number() == 0)
            {
                continue;
            }
            if (map_data.refresh_type == 0)
            {
                if (item.body_part != 0)
                {
                    continue;
                }
                if (item.is_precious())
                {
                    continue;
                }
                if (rnd(3))
                {
                    continue;
                }
            }
            else if (rnd(5))
            {
                continue;
            }
            if (the_item_db[itemid2int(item.id)]->is_cargo)
            {
                if (map_data.type != mdata_t::MapType::world_map &&
                    map_data.type != mdata_t::MapType::player_owned &&
                    map_data.type != mdata_t::MapType::town &&
                    map_data.type != mdata_t::MapType::field &&
                    map_data.type != mdata_t::MapType::shelter &&
                    map_data.type != mdata_t::MapType::guild)
                {
                    continue;
                }
                else if (rnd(2))
                {
                    continue;
                }
            }
            f = 0;
            if (item.body_part != 0)
            {
                if (rnd(10))
                {
                    f = 1;
                }
                if (item.curse_state == CurseState::blessed)
                {
                    if (rnd(2))
                    {
                        f = 1;
                    }
                }
                if (is_cursed(item.curse_state))
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
                if (item.curse_state == CurseState::doomed)
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
            }
            else if (item.identify_state == IdentifyState::completely)
            {
                if (rnd(4))
                {
                    f = 1;
                }
            }
            if (f)
            {
                continue;
            }
            if (item.body_part != 0)
            {
                cdata[rc].body_parts[item.body_part - 100] =
                    cdata[rc].body_parts[item.body_part - 100] / 10000 * 10000;
                item.body_part = 0;
            }
            f = 0;
            if (!item.is_precious())
            {
                if (rnd(4) == 0)
                {
                    f = 1;
                }
                if (item.curse_state == CurseState::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 0;
                    }
                }
                if (is_cursed(item.curse_state))
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
                if (item.curse_state == CurseState::doomed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
            }
            if (f)
            {
                item.remove();
                continue;
            }
            item.position.x = cdata[rc].position.x;
            item.position.y = cdata[rc].position.y;
            int stat = item_stack(-1, ci);
            if (stat == 0)
            {
                ti = inv_getfreeid(-1);
                if (ti == -1)
                {
                    break;
                }
                item_copy(ci, ti);
                inv[ti].own_state = -2;
            }
            inv[ci].remove();
        }
        cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
        create_pcpic(cdata.player());
        return;
    }
    else
    {
        if (rc < 16)
        {
            if (cdata[rc].has_own_sprite() == 1)
            {
                create_pcpic(cdata[rc]);
            }
        }
        if (cdata[rc].relationship == 10)
        {
            return;
        }
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (cdata[rc].id == CharaId::tourist)
        {
            return;
        }
        if (cdata[rc].id == CharaId::palmian_elite_soldier)
        {
            return;
        }
    }
    if (cdata[rc].is_contracting())
    {
        return;
    }
    if (cdata[rc].splits() || cdata[rc].splits2())
    {
        if (rnd(6))
        {
            return;
        }
    }
    for (auto&& item : inv.for_chara(cdata[rc]))
    {
        if (item.number() == 0)
        {
            continue;
        }
        ci = item.index;
        f = 0;
        if (cdata[rc].character_role == 20)
        {
            break;
        }
        if (item.quality > Quality::miracle || item.id == ItemId::platinum_coin)
        {
            f = 1;
        }
        if (rnd(30) == 0)
        {
            f = 1;
        }
        if (cdata[rc].quality >= Quality::miracle)
        {
            if (rnd(2) == 0)
            {
                f = 1;
            }
        }
        if (cdata[rc].character_role == 13)
        {
            if (rnd(5))
            {
                f = 0;
            }
        }
        if (game_data.current_map == mdata_t::MapId::arena)
        {
            if (rnd(4))
            {
                f = 0;
            }
        }
        if (item.quality == Quality::special)
        {
            f = 1;
        }
        if (item.is_quest_target())
        {
            f = 1;
        }
        if (f == 0)
        {
            continue;
        }
        if (catitem != 0 && !item.is_blessed_by_ehekatl() &&
            the_item_db[itemid2int(item.id)]->category < 50000 &&
            item.quality >= Quality::great)
        {
            if (rnd(3))
            {
                txt(i18n::s.get(
                        "core.misc.black_cat_licks", cdata[catitem], item),
                    Message::color{ColorIndex::cyan});
                item.is_blessed_by_ehekatl() = true;
                reftype = the_item_db[itemid2int(item.id)]->category;
                enchantment_add(
                    item,
                    enchantment_generate(enchantment_gen_level(rnd(4))),
                    enchantment_gen_p());
                animeload(8, rc);
            }
        }
        if (inv[ci].body_part != 0)
        {
            cdata[rc].body_parts[inv[ci].body_part - 100] =
                cdata[rc].body_parts[inv[ci].body_part - 100] / 10000 * 10000;
            inv[ci].body_part = 0;
        }
        inv[ci].position.x = cdata[rc].position.x;
        inv[ci].position.y = cdata[rc].position.y;
        itemturn(inv[ci]);
        int stat = item_stack(-1, ci);
        if (stat == 0)
        {
            ti = inv_getfreeid(-1);
            if (ti == -1)
            {
                break;
            }
            item_copy(ci, ti);
        }
        inv[ci].remove();
    }
    if (cdata[rc].quality >= Quality::miracle || rnd(20) == 0 ||
        cdata[rc].drops_gold() == 1 || rc < 16)
    {
        if (cdata[rc].gold > 0)
        {
            flt();
            itemcreate(
                -1,
                54,
                cdata[rc].position.x,
                cdata[rc].position.y,
                cdata[rc].gold / (1 + 3 * (cdata[rc].drops_gold() == 0)));
            cdata[rc].gold -=
                cdata[rc].gold / (1 + 3 * (cdata[rc].drops_gold() == 0));
        }
    }

    switch (class_get_item_type(cdatan(3, rc)))
    {
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 7:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 3:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 4:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 5:
        if (rnd(50) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    }

    switch (chara_db_get_item_type(cdata[rc].id))
    {
    case 3:
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
            remain_make(ci, rc);
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 62000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
            remain_make(ci, rc);
        }
        break;
    case 6:
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 32000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 34000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 4:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 5:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetwear);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = choice(fsetweapon);
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(15) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    }

    if (rnd(40) == 0)
    {
        p = 0;
        flt(calcobjlv(cdata[tc].level), calcfixlv(Quality::bad));
        flttypemajor = 62000;
        flttypeminor = 0;
        itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        remain_make(ci, rc);
    }
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
        return;
    }
    if (game_data.current_map != mdata_t::MapId::arena &&
        cdata[rc].character_role != 20)
    {
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0 ||
            (cdata[rc].quality == Quality::miracle && rnd(2) == 0) ||
            (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            itemcreate(-1, 504, cdata[rc].position.x, cdata[rc].position.y, 0);
            inv[ci].param1 = cdata[rc].image;
            inv[ci].subname = charaid2int(cdata[rc].id);
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0 ||
            (cdata[rc].quality == Quality::miracle && rnd(2) == 0) ||
            (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            itemcreate(-1, 503, cdata[rc].position.x, cdata[rc].position.y, 0);
            inv[ci].param1 = cdata[rc].image;
            inv[ci].subname = charaid2int(cdata[rc].id);
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
    }
    if (cdata[rc].character_role == 1010)
    {
        flt();
        itemcreate(-1, 361, cdata[rc].position.x, cdata[rc].position.y, 0);
        inv[ci].param1 = cdata[rc].shop_store_id;
        inv[ci].own_state = 2;
    }
    if (rollanatomy == 1 || cdata[rc].quality >= Quality::miracle || 0 ||
        cdata[rc].is_livestock() == 1 || 0)
    {
        flt();
        if (itemcreate(-1, 204, cdata[rc].position.x, cdata[rc].position.y, 0))
        {
            remain_make(ci, rc);
            if (cdata[rc].is_livestock() == 1)
            {
                if (sdata(161, 0) != 0)
                {
                    inv[ci].modify_number(
                        rnd(1 + (sdata(161, 0) > cdata[rc].level)));
                }
            }
        }
    }

    // ../runtime/profile/_/mod/core/exports/impl/chara_drop.lua
    lua::call("core.impl.chara_drop.drop_from_chara", lua::handle(cdata[rc]));

    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    if (cdata[rc].character_role == 13)
    {
        supply_new_equipment();
    }
}



void damage_by_cursed_equipments()
{
    if (rnd(4) == 0)
    {
        damage_hp(
            cdata[cc],
            cdata[cc].hp * (5 + cdata[cc].curse_power / 5) / 100,
            -5);
        return;
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (rnd(10 - clamp(cdata[cc].curse_power / 10, 0, 9)) == 0)
        {
            efid = 408;
            tc = cc;
            magic();
            return;
        }
    }
    if (rnd(10) == 0)
    {
        if (cdata[cc].gold > 0)
        {
            p = rnd(cdata[cc].gold) / 100 + rnd(10) + 1;
            if (p > cdata[cc].gold)
            {
                p = cdata[cc].gold;
            }
            cdata[cc].gold -= p;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.misc.curse.gold_stolen", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
            return;
        }
    }
}



void proc_pregnant()
{
    if (rnd(15) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.misc.pregnant.pats_stomach", cdata[cc]));
            txt(i18n::s.get("core.misc.pregnant.something_is_wrong"));
        }
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (rnd(30) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.misc.pregnant.something_breaks_out", cdata[cc]));
            }
            cdata[cc].bleeding += 15;
            flt();
            initlv = cdata[cc].level / 2 + 1;
            novoidlv = 1;
            int stat = chara_create(
                -1, 330, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (strlen_u(cdatan(0, cc)) > 10 ||
                    instr(
                        cdatan(0, cc),
                        0,
                        i18n::s.get("core.chara.job.alien.child")) != -1)
                {
                    cdatan(0, rc) =
                        i18n::s.get("core.chara.job.alien.alien_kid");
                }
                else
                {
                    cdatan(0, rc) = i18n::s.get(
                        "core.chara.job.alien.child_of", cdatan(0, cc));
                }
            }
        }
    }
}



void proc_negative_equipments()
{
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[cc].body_parts[i] % 10000 == 0)
        {
            continue;
        }
        ci = cdata[cc].body_parts[i] % 10000 - 1;
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[ci].enchantments[cnt].id == 0)
            {
                break;
            }
            if (inv[ci].enchantments[cnt].id == 21)
            {
                if (map_data.type != mdata_t::MapType::world_map)
                {
                    if (rnd(25) <
                        clamp(
                            std::abs(inv[ci].enchantments[cnt].power) / 50,
                            1,
                            25))
                    {
                        efid = 408;
                        tc = cc;
                        magic();
                        continue;
                    }
                }
            }
            if (inv[ci].enchantments[cnt].id == 45)
            {
                if (rnd(4) == 0)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                                "core.misc.curse.blood_sucked", cdata[cc]),
                            Message::color{ColorIndex::purple});
                    }
                    cdata[cc].bleeding +=
                        std::abs(inv[ci].enchantments[cnt].power) / 25 + 3;
                    continue;
                }
            }
            if (inv[ci].enchantments[cnt].id == 46)
            {
                if (rnd(20) == 0)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                                "core.misc.curse.experience_reduced",
                                cdata[cc]),
                            Message::color{ColorIndex::purple});
                    }
                    cdata[cc].experience -= cdata[cc].required_experience /
                            (300 -
                             clamp(
                                 std::abs(inv[ci].enchantments[cnt].power) / 2,
                                 0,
                                 50)) +
                        rnd(100);
                    if (cdata[cc].experience < 0)
                    {
                        cdata[cc].experience = 0;
                    }
                    continue;
                }
            }
            if (inv[ci].enchantments[cnt].id == 47)
            {
                if (map_data.type != mdata_t::MapType::world_map)
                {
                    if (map_data.type != mdata_t::MapType::player_owned)
                    {
                        if (rnd(50) <
                            clamp(
                                std::abs(inv[ci].enchantments[cnt].power) / 50,
                                1,
                                50))
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                txt(i18n::s.get("core.misc.curse."
                                                "creature_summoned"),
                                    Message::color{ColorIndex::purple});
                            }
                            for (int cnt = 0, cnt_end = (1 + rnd(3));
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                                    calcfixlv(Quality::bad));
                                chara_create(
                                    -1,
                                    0,
                                    cdata[cc].position.x,
                                    cdata[cc].position.y);
                            }
                            continue;
                        }
                    }
                }
            }
        }
    }
}



void auto_identify()
{
    if (cdata.player().confused != 0 || cdata.player().sleep != 0 ||
        cdata.player().paralyzed != 0 || cdata.player().choked != 0)
    {
        return;
    }
    for (const auto& item : inv.pc())
    {
        if (item.number() == 0 ||
            item.identify_state == IdentifyState::completely)
        {
            continue;
        }
        if (the_item_db[itemid2int(item.id)]->category >= 50000)
        {
            continue;
        }
        ci = item.index;
        p(0) = sdata(13, 0) + sdata(162, 0) * 5;
        p(1) = 1500 + item.difficulty_of_identification * 5;
        if (p > rnd(p(1) * 5))
        {
            s = itemname(ci);
            item_identify(inv[ci], IdentifyState::completely);
            itemmemory(0, itemid2int(inv[ci].id)) = 1;
            if (!g_config.hide_autoidentify())
            {
                txt(i18n::s.get(
                    "core.misc.identify.fully_identified", s(0), inv[ci]));
            }
            chara_gain_skill_exp(cdata.player(), 162, 50);
        }
        if (inv[ci].identify_state <= IdentifyState::partly)
        {
            if (p > rnd(p(1)))
            {
                if (!g_config.hide_autoidentify())
                {
                    txt(i18n::s.get(
                        "core.misc.identify.almost_identified",
                        inv[ci],
                        i18n::s.get_enum(
                            u8"core.ui.quality",
                            static_cast<int>(inv[ci].quality))));
                }
                item_identify(inv[ci], IdentifyState::almost);
                chara_gain_skill_exp(cdata.player(), 162, 50);
            }
        }
    }
}



void lovemiracle(int chara_index)
{
    if (rnd(2) || chara_index == 0)
    {
        return;
    }
    cibk = ci;
    txt(i18n::s.get("core.misc.love_miracle.uh"),
        Message::color{ColorIndex::cyan});
    flt();
    if (rnd(2))
    {
        if (itemcreate(
                -1,
                573,
                cdata[chara_index].position.x,
                cdata[chara_index].position.y,
                0))
        {
            inv[ci].subname = charaid2int(cdata[chara_index].id);
            inv[ci].weight = cdata[chara_index].weight * 10 + 250;
            inv[ci].value = clamp(
                cdata[chara_index].weight * cdata[chara_index].weight / 10000,
                200,
                40000);
        }
    }
    else
    {
        if (itemcreate(
                -1,
                574,
                cdata[chara_index].position.x,
                cdata[chara_index].position.y,
                0))
        {
            inv[ci].subname = charaid2int(cdata[chara_index].id);
        }
    }
    ci = cibk;
    snd("core.atk_elec");
    animeload(15, chara_index);
}



void get_pregnant()
{
    if (enchantment_find(cdata[tc], 48))
    {
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.misc.pregnant.pukes_out", cdata[tc]));
        }
        return;
    }
    if (cdata[tc].is_pregnant() == 0)
    {
        txt(i18n::s.get("core.misc.pregnant.gets_pregnant", cdata[tc]),
            Message::color{ColorIndex::orange});
        animeload(8, tc);
        cdata[tc].is_pregnant() = true;
    }
}



void removeworker(int map_id)
{
    for (int i = 1; i < 16; ++i)
    {
        if (cdata[i].current_map == map_id)
        {
            cdata[i].current_map = 0;
        }
    }
}



void monster_respawn()
{
    if (area_data[game_data.current_map].is_museum_or_shop())
    {
        if (game_data.crowd_density < map_data.max_crowd_density / 2)
        {
            if (rnd(2) == 0)
            {
                map_set_chara_generation_filter();
                chara_create(-1, dbid, -2, 0);
            }
        }
    }
    if (map_data.max_crowd_density == 0)
    {
        return;
    }
    if (game_data.crowd_density < map_data.max_crowd_density / 4)
    {
        if (rnd(2) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (game_data.crowd_density < map_data.max_crowd_density / 2)
    {
        if (rnd(4) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (game_data.crowd_density < map_data.max_crowd_density)
    {
        if (rnd(8) == 0)
        {
            map_set_chara_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
}



TurnResult exit_map()
{
    int previous_map = game_data.current_map;
    int previous_dungeon_level = game_data.current_dungeon_level;
    int fixstart = 0;

    ELONA_LOG("map") << "exit_map levelexitby begin " << levelexitby << " cur "
                     << game_data.current_map << " cur_level "
                     << game_data.current_dungeon_level;

    game_data.left_minutes_of_executing_quest = 0;
    game_data.rogue_boss_encountered = 0;
    if (map_data.type == mdata_t::MapType::player_owned)
    {
        maybe_show_ex_help(1);
    }
    if (map_data.type == mdata_t::MapType::temporary)
    {
        rq = game_data.executing_immediate_quest;
        quest_exit_map();
    }
    Message::instance().buffered_message_begin("  ");
    if (game_data.current_map == mdata_t::MapId::show_house ||
        game_data.current_map == mdata_t::MapId::arena ||
        game_data.current_map == mdata_t::MapId::pet_arena)
    {
        usermapid = 0;
    }
    rdtry = 0;
    fixstart = 0;
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            if (area_data[game_data.current_map].has_been_conquered > 0)
            {
                chara_vanquish(
                    area_data[game_data.current_map].has_been_conquered);
                area_data[game_data.current_map].has_been_conquered = -1;
            }
        }
    }
    game_data.previous_map = game_data.current_map;
    if (game_data.previous_map == mdata_t::MapId::shelter_)
    {
        game_data.current_map = game_data.previous_map2;
        game_data.current_dungeon_level = game_data.previous_dungeon_level;
        mapstartx = game_data.previous_x;
        mapstarty = game_data.previous_y;
        game_data.entrance_type = 7;
        fixstart = 1;
        levelexitby = 5;
    }
    if (levelexitby == 4)
    {
        cell_featread(cdata.player().position.x, cdata.player().position.y);
        if (game_data.current_map == mdata_t::MapId::your_home)
        {
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 751) !=
                -1)
            {
                feat(1) = 11;
                feat(2) = 0;
            }
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 750) !=
                -1)
            {
                feat(1) = 10;
                feat(2) = 0;
            }
        }
        f = 0;
        if (feat(1) == 11)
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.misc.walk_down_stairs"));
            f = 1;
            game_data.entrance_type = 1;
            map_data.stair_down_pos =
                cdata.player().position.y * 1000 + cdata.player().position.x;
            if (feat(2) == 0)
            {
                ++game_data.current_dungeon_level;
                game_data.current_dungeon_level -=
                    (area_data[game_data.current_map].entrance == 2) * 2;
            }
            else
            {
                game_data.current_dungeon_level = feat(2);
            }
        }
        if (feat(1) == 10)
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.misc.walk_up_stairs"));
            f = 1;
            game_data.entrance_type = 2;
            map_data.stair_up_pos =
                cdata.player().position.y * 1000 + cdata.player().position.x;
            if (feat(2) == 0)
            {
                --game_data.current_dungeon_level;
                game_data.current_dungeon_level +=
                    (area_data[game_data.current_map].entrance == 2) * 2;
            }
            else
            {
                game_data.current_dungeon_level = feat(2);
            }
        }
        if (f == 0)
        {
            if (map_data.type == mdata_t::MapType::world_map)
            {
                game_data.pc_x_in_world_map = cdata[cc].position.x;
                game_data.pc_y_in_world_map = cdata[cc].position.y;
                game_data.current_dungeon_level = 1;
                if (feat(2) != 0 || feat(3) != 0)
                {
                    game_data.current_map = feat(2) + feat(3) * 100;
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::the_void)
                    {
                        if (itemfind(0, 742) == -1)
                        {
                            txt(i18n::s.get(
                                "core.action.exit_map.not_permitted"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::pyramid)
                    {
                        if (game_data.quest_flags.pyramid_trial == 0)
                        {
                            txt(
                                i18n::s.get("core.action.exit_map.no_"
                                            "invitation_to_pyramid"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id ==
                        mdata_t::MapId::jail)
                    {
                        txt(i18n::s.get(
                            "core.action.exit_map.cannot_enter_jail"));
                        msg_halt();
                        game_data.current_map =
                            static_cast<int>(mdata_t::MapId::fields);
                    }
                }
                else
                {
                    game_data.current_map =
                        static_cast<int>(mdata_t::MapId::fields);
                }
                if (feat(1) != 15)
                {
                    game_data.current_map =
                        static_cast<int>(mdata_t::MapId::fields);
                }
            }
            if (map_data.type == mdata_t::MapType::town ||
                map_data.type == mdata_t::MapType::field ||
                map_data.type == mdata_t::MapType::player_owned ||
                map_data.type == mdata_t::MapType::shelter ||
                map_data.type == mdata_t::MapType::guild)
            {
                game_data.current_map = game_data.destination_outer_map;
            }
        }
        if (mdata_t::is_nefia(map_data.type) ||
            map_data.type == static_cast<int>(mdata_t::MapType::shelter))
        {
            if (game_data.current_dungeon_level <
                area_data[game_data.current_map].danger_level)
            {
                game_data.current_map = game_data.destination_outer_map;
            }
        }
        if (area_data[game_data.current_map].type == mdata_t::MapType::town)
        {
            if (game_data.current_map == game_data.previous_map)
            {
                if (game_data.current_dungeon_level == 1)
                {
                    Message::instance().buffered_message_append(i18n::s.get(
                        "core.action.exit_map.surface.returned_to",
                        mapname(game_data.current_map)));
                }
                else
                {
                    Message::instance().buffered_message_append(i18n::s.get(
                        "core.action.exit_map.surface.left",
                        mapname(game_data.current_map)));
                }
            }
        }
    }
    if (map_data.type == mdata_t::MapType::temporary)
    {
        game_data.current_map = game_data.previous_map2;
        game_data.current_dungeon_level = game_data.previous_dungeon_level;
        mapstartx = game_data.previous_x;
        mapstarty = game_data.previous_y;
        game_data.entrance_type = 7;
        fixstart = 1;
    }
    if (levelexitby == 2)
    {
        game_data.current_map = game_data.destination_map;
        game_data.current_dungeon_level = game_data.destination_dungeon_level;
        if (game_data.executing_immediate_quest_type == 0)
        {
            if (game_data.previous_map !=
                static_cast<int>(mdata_t::MapId::fields))
            {
                game_data.pc_x_in_world_map =
                    area_data[game_data.current_map].position.x;
                game_data.pc_y_in_world_map =
                    area_data[game_data.current_map].position.y;
                weather_changes_by_location(false);
            }
        }
        if (game_data.current_map == mdata_t::MapId::jail)
        {
            mapstartx = 29;
            mapstarty = 3;
            game_data.entrance_type = 7;
            fixstart = 1;
        }
    }
    if (cdata.player().state() == Character::State::empty)
    {
        rc = 0;
        revive_player();
        game_data.current_map = static_cast<int>(mdata_t::MapId::your_home);
        game_data.destination_outer_map =
            area_data[static_cast<int>(mdata_t::MapId::your_home)].outer_map;
        game_data.current_dungeon_level = 1;
    }
    if (rdtry > 1)
    {
        Message::instance().buffered_message_append(
            u8"(再生成"s + rdtry + u8"回)"s);
    }
    if (game_data.current_map != game_data.previous_map)
    {
        if (map_is_town_or_guild() ||
            game_data.previous_map == mdata_t::MapId::your_home ||
            game_data.departure_date == 0)
        {
            game_data.departure_date = game_data.date.hours();
            game_data.distance_between_town = 0;
            game_data.left_town_map = game_data.previous_map;
        }
        if (area_data[game_data.current_map].type !=
                mdata_t::MapType::world_map &&
            area_data[game_data.current_map].type != mdata_t::MapType::field &&
            game_data.current_map != mdata_t::MapId::show_house)
        {
            save_set_autosave();
        }
        if (map_data.type != mdata_t::MapType::world_map)
        {
            if (map_data.type != mdata_t::MapType::field ||
                map_data.type == mdata_t::MapType::player_owned)
            {
                if (fixtransfermap == 0)
                {
                    game_data.pc_x_in_world_map =
                        area_data[game_data.previous_map].position.x;
                    game_data.pc_y_in_world_map =
                        area_data[game_data.previous_map].position.y;
                }
                else
                {
                    fixtransfermap = 0;
                }
            }
        }
        if (fixstart == 0)
        {
            game_data.entrance_type = area_data[game_data.current_map].entrance;
        }
        if (event_find(6))
        {
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.delivered_to_your_home"));
            weather_changes_by_location(false);
        }
        else if (
            area_data[game_data.previous_map].type ==
            mdata_t::MapType::world_map)
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.entered",
                mapname(game_data.current_map)));
        }
        else if (map_data.type == mdata_t::MapType::temporary)
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.returned_to",
                mapname(game_data.current_map)));
        }
        else
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.action.exit_map.left", mapname(game_data.previous_map)));
        }
        if (game_data.cargo_weight > game_data.current_cart_limit)
        {
            if (area_data[game_data.current_map].type ==
                    mdata_t::MapType::world_map ||
                area_data[game_data.current_map].type ==
                    mdata_t::MapType::field)
            {
                Message::instance().buffered_message_append(
                    i18n::s.get("core.action.exit_map.burdened_by_cargo"));
            }
        }
    }
    if (game_data.current_map == mdata_t::MapId::larna)
    {
        if (game_data.current_dungeon_level == 2)
        {
            game_data.current_map =
                static_cast<int>(mdata_t::MapId::mountain_pass);
            game_data.current_dungeon_level =
                area_data[game_data.current_map].deepest_level - 1;
            game_data.entrance_type = 1;
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.mountain_pass"));
        }
    }
    if (game_data.current_map == mdata_t::MapId::mountain_pass)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            game_data.current_map = static_cast<int>(mdata_t::MapId::larna);
            game_data.current_dungeon_level = 1;
            game_data.entrance_type = 2;
            Message::instance().buffered_message_append(
                i18n::s.get("core.action.exit_map.larna"));
        }
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        cdata[cnt].hate = 0;
        cdata[cnt].enemy_id = 0;
        cdata[cnt].activity.finish();
        if (cdata[cnt].state() != Character::State::alive)
        {
            if (cdata[cnt].state() == Character::State::pet_in_other_map)
            {
                cdata[cnt].set_state(Character::State::alive);
            }
            continue;
        }
        cell_data.at(cdata[cnt].position.x, cdata[cnt].position.y)
            .chara_index_plus_one = 0;
        if (cnt != 0)
        {
            if (cdata[cnt].current_map != 0)
            {
                cdata[cnt].set_state(Character::State::pet_moving_to_map);
            }
        }
    }
    if (map_data.refresh_type == 1)
    {
        // This map should be saved.
        save_map_local_data();

        ELONA_LOG("map") << "exit_map save local";
    }
    else
    {
        // This is a temporary map, so wipe its data (shelter, special
        // quest instance)
        prepare_charas_for_map_unload();

        tmpload(filepathutil::u8path("mdata_" + mid + ".s2"));
        // delete all map-local data
        if (fs::exists(filesystem::dirs::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            ctrl_file(FileOperation::map_delete);
        }

        // forget about all NPCs that were here
        for (auto&& cnt : cdata.others())
        {
            if (cnt.state() != Character::State::empty)
            {
                --npcmemory(1, charaid2int(cnt.id));
            }
        }

        ELONA_LOG("map") << "exit_map clear temporary";
    }

    bool map_changed = game_data.current_map != previous_map ||
        game_data.current_dungeon_level != previous_dungeon_level;

    ELONA_LOG("map") << "exit_map levelexitby end " << levelexitby << " cur "
                     << game_data.current_map << " cur_level "
                     << game_data.current_dungeon_level << " prev "
                     << previous_map << " prev_level "
                     << previous_dungeon_level;

    // Only trigger the map unload event if the map was changed. The map might
    // not change if access to it is refused (jail, pyramid, etc.).
    if (map_changed)
    {
        lua::lua->get_event_manager().trigger(
            lua::BaseEvent("core.before_map_unload"));
    }

    mode = 2;
    return TurnResult::initialize_map;
}



void prepare_charas_for_map_unload()
{
    // interrupt continuous actions
    for (int cnt = 0; cnt < 57; ++cnt)
    {
        cdata[cnt].activity.finish();
        cdata[cnt].item_which_will_be_used = 0;
    }

    // remove living adventurers from the map and set their states
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        if (cdata[cnt].state() == Character::State::alive)
        {
            cell_data.at(cdata[cnt].position.x, cdata[cnt].position.y)
                .chara_index_plus_one = 0;
            cdata[cnt].set_state(Character::State::adventurer_in_other_map);
        }
    }
}



void save_map_local_data()
{
    prepare_charas_for_map_unload();
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).blood_and_fragments = 0;
        }
    }

    // write map data and characters/skill data local to this map
    ctrl_file(FileOperation::map_write);

    // write data for items/character inventories local to this map
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
}



int initialize_world_map()
{
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
        {
            if (area_data[cnt].has_been_conquered != -1)
            {
                ++p;
            }
        }
    }
    p = 40 - p;
    if (p < 1)
    {
        p = 1;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        cxinit = rnd(map_data.width);
        cyinit = rnd(map_data.height);
        map_global_place_random_nefias();
    }
    map_global_prepare();
    return 1;
}



void map_global_proc_diastrophism()
{
    if (game_data.reset_world_map_in_diastrophism_flag == 1)
    {
        initialize_adata();
        map_global_prepare();
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            area_data[cnt].id = static_cast<int>(mdata_t::MapId::none);
        }
    }
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
        {
            if (area_data[cnt].has_been_conquered != -1)
            {
                ++p;
            }
        }
    }
    if (p <= 25 || rnd(150) == 0 || game_data.diastrophism_flag != 0 ||
        game_data.reset_world_map_in_diastrophism_flag)
    {
        game_data.diastrophism_flag = 0;
        Message::instance().buffered_message_append(
            i18n::s.get("core.action.move.global.diastrophism"));
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            if (area_data[cnt].id == mdata_t::MapId::random_dungeon)
            {
                if (rnd(5) == 0 || area_data[cnt].has_been_conquered == -1)
                {
                    area_data[cnt].id = static_cast<int>(mdata_t::MapId::none);
                }
            }
        }
        initialize_world_map();
        map_global_prepare();
    }
    game_data.reset_world_map_in_diastrophism_flag = 0;
}



void map_global_prepare()
{
    map_clear_material_spots_and_light();
    map_global_place_entrances();
}



void map_global_place_entrances()
{
    draw_prepare_map_chips();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        int cnt2 = cnt;
        if (game_data.destination_outer_map != 4)
        {
            break;
        }
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (bddata(0, cnt2, cnt) != 0)
            {
                p = bddata(0, cnt2, cnt);
                cell_featset(
                    bddata(1, cnt2, cnt),
                    bddata(2, cnt2, cnt),
                    bddata(3, cnt2, cnt),
                    34,
                    cnt2,
                    cnt);
            }
        }
    }
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none ||
            area_data[cnt].appearance == 0)
        {
            continue;
        }
        if (area_data[cnt].outer_map != game_data.destination_outer_map)
        {
            continue;
        }
        if (area_data[cnt].id == 900)
        {
            area_data[cnt].id = 40;
            continue;
        }
        if (area_data[cnt].id >= 900)
        {
            area_data[cnt].id -= 800;
            continue;
        }
        if (area_data[cnt].position.x <= 0 || area_data[cnt].position.y <= 0 ||
            area_data[cnt].position.x >= map_data.width ||
            area_data[cnt].position.y >= map_data.height)
        {
            area_data[cnt].position.x = map_data.width / 2;
            area_data[cnt].position.y = map_data.height / 2;
        }
        p = cnt;
        if (chip_data
                    .for_cell(
                        area_data[cnt].position.x, area_data[cnt].position.y)
                    .effect &
                4 ||
            cell_data.at(area_data[cnt].position.x, area_data[cnt].position.y)
                    .feats != 0)
        {
            for (int cnt = 0;; ++cnt)
            {
                dx = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.width);
                dy = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.height);
                x = area_data[p].position.x + rnd(dx(0)) - rnd(dx(0));
                y = area_data[p].position.y + rnd(dy) - rnd(dy);
                if (x <= 0 || y <= 0 || x >= map_data.width - 1 ||
                    y >= map_data.height - 1)
                {
                    continue;
                }
                if (33 <= cell_data.at(x, y).chip_id_actual &&
                    cell_data.at(x, y).chip_id_actual < 66)
                {
                    continue;
                }
                if (chip_data.for_cell(x, y).effect & 4)
                {
                    continue;
                }
                if (cell_data.at(x, y).feats != 0)
                {
                    continue;
                }
                area_data[p].position.x = x;
                area_data[p].position.y = y;
                break;
            }
        }
        cell_featset(
            area_data[cnt].position.x,
            area_data[cnt].position.y,
            area_data[cnt].appearance,
            15,
            cnt % 100,
            cnt / 100);
        if (area_data[cnt].type == mdata_t::MapType::town ||
            area_data[cnt].type == mdata_t::MapType::guild)
        {
            cell_data.at(area_data[cnt].position.x, area_data[cnt].position.y)
                .light = 11;
        }
    }
}



void map_clear_material_spots_and_light()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_featread(x, y);
            // material spot
            if (feat(1) < 24 || feat(1) > 28)
            {
                cell_data.at(x, y).feats = 0;
            }
            cell_data.at(x, y).light = 0;
        }
    }
}



int random_material(int level, int rarity)
{
    int f_at_m174 = 0;
    int lv_at_m174 = 0;
    int rare_at_m174 = 0;
    int loc_at_m174 = 0;
    int p_at_m174 = 0;
    int f2_at_m174 = 0;
    int p2_at_m174 = 0;
    f_at_m174 = 0;
    lv_at_m174 = level;
    rare_at_m174 = rarity;
    loc_at_m174 = atxspot;
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        p_at_m174 = rnd(55);
        if (p_at_m174 == 0)
        {
            continue;
        }
        if (cnt % 10 == 0)
        {
            ++lv_at_m174;
            ++rare_at_m174;
        }
        if (matref(0, p_at_m174) > lv_at_m174)
        {
            continue;
        }
        if (matref(1, p_at_m174) > rare_at_m174)
        {
            continue;
        }
        f2_at_m174 = 0;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            p2_at_m174 = matspot(cnt, p_at_m174);
            if (p2_at_m174 == 0)
            {
                break;
            }
            if (p2_at_m174 == loc_at_m174 || p2_at_m174 == 18)
            {
                f2_at_m174 = 1;
                break;
            }
        }
        if (f2_at_m174 == 0)
        {
            continue;
        }
        if (rnd(matref(1, p_at_m174)) == 0)
        {
            f_at_m174 = p_at_m174;
            break;
        }
    }
    return f_at_m174;
}



void atxinit()
{
    atbuff = "";
    notesel(atbuff);
    listmax = 0;
    cs = 0;
    page = 0;
    cc = 0;
    cs_bk = -1;
    pagesize = 16;
    chatesc = -1;
    if (atxbg != atxbgbk)
    {
        mode = 0;
        screenupdate = -1;
        update_screen();
        mode = 9;
        atxbgbk = atxbg;
        gmode(0);
        asset_load(atxbg);
        draw(
            "atx_background",
            0,
            inf_msgh,
            windoww,
            windowh - inf_verh - inf_msgh);
        gmode(2);
        p = windoww / 192;
        for (int cnt = 0, cnt_end = (p + 1); cnt < cnt_end; ++cnt)
        {
            if (cnt == p)
            {
                sx = windoww % 192;
            }
            else
            {
                sx = 192;
            }
            draw_region("message_window", cnt * 192, 0, sx, inf_msgh);
        }
        window2(windoww - 208, 0, 208, 98, 0, 0);
        gcopy(
            0,
            120,
            88,
            windoww - 120,
            windowh - inf_verh - 112,
            windoww - 204,
            4,
            200,
            90);
        gsel(0);
    }
}



void begintempinv()
{
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    for (auto&& item : inv.ground())
    {
        item.remove();
    }
}



void exittempinv()
{
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
}



void god_fail_to_take_over_penalty()
{
    efid = 1114;
    efp = 500;
    tc = 0;
    magic();
    if (rnd(2))
    {
        efid = 622;
        efp = 250;
        tc = 0;
        magic();
        snd("core.punish1");
    }
    if (rnd(2))
    {
        efid = 1106;
        efp = 100;
        tc = 0;
        magic();
    }
}



int calcincome(int rank_id)
{
    int rank_amount = 100 - game_data.ranks.at(rank_id) / 100;
    if (rank_amount == 99)
    {
        rank_amount = rank_amount * 70;
    }
    else
    {
        rank_amount = rank_amount * 50;
    }
    if (rank_id == 2)
    {
        rank_amount = rank_amount * 120 / 100;
    }
    if (rank_id == 4)
    {
        rank_amount = rank_amount * 60 / 100;
    }
    if (rank_id == 0)
    {
        rank_amount = rank_amount * 80 / 100;
    }
    if (rank_id == 1)
    {
        rank_amount = rank_amount * 70 / 100;
    }
    if (rank_id == 6)
    {
        rank_amount = rank_amount * 25 / 100;
    }
    if (rank_id == 5)
    {
        rank_amount = rank_amount * 20 / 100;
    }
    if (rank_id == 8)
    {
        rank_amount = rank_amount * 15 / 100;
    }
    return rank_amount;
}



void supply_income()
{
    invfile = 4;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    tmpload(filepathutil::u8path(u8"shop4.s2"));
    if (fs::exists(filesystem::dirs::tmp() / u8"shop4.s2"s))
    {
        ctrl_file(FileOperation2::map_items_read, u8"shop4.s2"s);
    }
    else
    {
        for (auto&& item : inv.ground())
        {
            item.remove();
        }
    }
    mode = 6;
    income(0) = 0;
    income(1) = 0;
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (game_data.ranks.at(cnt) >= 10000)
        {
            continue;
        }
        p = calcincome(cnt) + rnd((calcincome(cnt) / 3 + 1)) -
            rnd((calcincome(cnt) / 3 + 1));
        income += p;
        flt();
        itemcreate(-1, 54, -1, -1, p);
        if (cnt == 5 || cnt == 6)
        {
            continue;
        }
        if (cnt == 5 || cnt == 6 || cnt == 3)
        {
            continue;
        }
        p = rnd(rnd(3) + 1) + 1;
        int rank_id = cnt;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            dbid = 0;
            flt(calcobjlv((100 - game_data.ranks.at(rank_id) / 100) / 2 + 1),
                calcfixlv(
                    (rnd(12) < trait(39)) ? Quality::miracle : Quality::great));
            flttypemajor = choice(fsetincome);
            if (rnd(5) == 0)
            {
                flttypemajor = choice(fsetwear);
            }
            if (rnd(100 + game_data.ranks.at(rank_id) / 5) < 2)
            {
                dbid = 559;
            }
            itemcreate(-1, dbid, -1, -1, 0);
            ++income(1);
        }
    }
    if (cdata.player().fame > 0)
    {
        p = clamp(cdata.player().fame / 10, 100, 25000);
        if (cdata.player().fame >= 25000)
        {
            p += (cdata.player().fame - 25000) / 100;
        }
        income += p;
        flt();
        itemcreate(-1, 54, -1, -1, p);
    }
    if (income != 0 || income(1) != 0)
    {
        snd("core.ding2");
        if (income(1) == 0)
        {
            txt(i18n::s.get("core.misc.income.sent_to_your_house", income(0)),
                Message::color{ColorIndex::orange});
        }
        else
        {
            txt(i18n::s.get(
                    "core.misc.income.sent_to_your_house2",
                    income(0),
                    income(1)),
                Message::color{ColorIndex::orange});
        }
        save_set_autosave();
    }
    if (game_data.date.day == 1)
    {
        if (cdata.player().level > 5)
        {
            save_set_autosave();
            p = -1;
            for (const auto& item : inv.ground())
            {
                if (item.number() == 0)
                {
                    p = item.index;
                    break;
                }
            }
            if (p == -1)
            {
                inv_compress(-1);
            }
            flt();
            itemcreate(-1, 615, -1, -1, 0);
            inv[ci].subname =
                game_data.cost_to_hire + calccostbuilding() + calccosttax();
            inv[ci].subname = inv[ci].subname * (100 + rnd(20)) / 100;
            mode = 0;
            ++game_data.left_bill;
            txt(i18n::s.get("core.misc.tax.bill"));
            if (game_data.left_bill > 1)
            {
                if (game_data.left_bill <= 4)
                {
                    if (game_data.left_bill > 3)
                    {
                        s(0) = i18n::s.get("core.misc.tax.warning");
                        s(1) = i18n::s.get("core.misc.tax.have_to_go_embassy");
                    }
                    else
                    {
                        s(0) = i18n::s.get("core.misc.tax.caution");
                        s(1) = "";
                    }
                    txt(s +
                            i18n::s.get(
                                "core.misc.tax.left_bills",
                                game_data.left_bill - 1) +
                            s(1),
                        Message::color{ColorIndex::red});
                }
            }
            if (game_data.left_bill > 4)
            {
                txt(i18n::s.get(
                        "core.misc.tax.accused", game_data.left_bill - 1),
                    Message::color{ColorIndex::red});
                int stat = decfame(0, 50);
                p = stat;
                txt(i18n::s.get("core.misc.tax.lose_fame", p(0)),
                    Message::color{ColorIndex::red});
                modify_karma(cdata.player(), -30 * 2);
            }
        }
        else
        {
            txt(i18n::s.get("core.misc.tax.no_duty"));
        }
    }
    ctrl_file(FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
    mode = 0;
    maybe_show_ex_help(16);
}



std::string txtitemoncell(int x, int y)
{
    elona_vector1<int> p_at_m185;
    elona_vector1<int> i_at_m185;
    const auto item_info = cell_itemoncell({x, y});
    const auto number = item_info.first;
    const auto item = item_info.second;

    if (number <= 3)
    {
        if (cell_data.at(x, y).item_appearances_memory < 0)
        {
            rtvaln = "";
            p_at_m185(0) = -cell_data.at(x, y).item_appearances_memory;
            p_at_m185(1) = 0;
            i_at_m185(0) = p_at_m185 % 1000 + ELONA_ITEM_ON_GROUND_INDEX;
            i_at_m185(1) = p_at_m185 / 1000 % 1000 + ELONA_ITEM_ON_GROUND_INDEX;
            i_at_m185(2) =
                p_at_m185 / 1000000 % 1000 + ELONA_ITEM_ON_GROUND_INDEX;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (i_at_m185(cnt) == 6079)
                {
                    continue;
                }
                if (p_at_m185(1) != 0)
                {
                    rtvaln += i18n::s.get("core.misc.and");
                }
                rtvaln += itemname(i_at_m185(cnt));
                ++p_at_m185(1);
            }
        }
        else
        {
            rtvaln = itemname(item);
        }
        if (inv[item].own_state <= 0)
        {
            return i18n::s.get("core.action.move.item_on_cell.item", rtvaln(0));
        }
        else if (inv[item].own_state == 3)
        {
            return i18n::s.get(
                "core.action.move.item_on_cell.building", rtvaln(0));
        }
        else
        {
            return i18n::s.get(
                "core.action.move.item_on_cell.not_owned", rtvaln(0));
        }
    }
    else
    {
        return i18n::s.get(
            "core.action.move.item_on_cell.more_than_three", number);
    }
}



void txttargetnpc(int x, int y)
{
    int dy_at_m186 = 0;
    int i_at_m186 = 0;
    int p_at_m186 = 0;
    dy_at_m186 = 0;
    font(14 - en * 2);
    if (fov_los(cdata.player().position.x, cdata.player().position.y, x, y) ==
            0 ||
        dist(cdata.player().position.x, cdata.player().position.y, x, y) >
            cdata.player().vision_distance / 2)
    {
        bmes(
            i18n::s.get("core.action.target.out_of_sight"),
            100,
            windowh - inf_verh - 45 - dy_at_m186 * 20);
        ++dy_at_m186;
        cansee = 0;
        return;
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        i_at_m186 = cell_data.at(x, y).chara_index_plus_one - 1;
        if (cdata[i_at_m186].is_invisible() == 0 ||
            cdata.player().can_see_invisible() || cdata[i_at_m186].wet)
        {
            tc = i_at_m186;
            s = txttargetlevel(cc, tc);
            bmes(s, 100, windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            bmes(
                i18n::s.get(
                    "core.action.target.you_are_targeting",
                    cdata[i_at_m186],
                    dist(
                        cdata.player().position.x,
                        cdata.player().position.y,
                        cdata[i_at_m186].position.x,
                        cdata[i_at_m186].position.y)),
                100,
                windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
        }
    }
    if (cell_data.at(x, y).item_appearances_memory != 0)
    {
        bmes(
            txtitemoncell(x, y),
            100,
            windowh - inf_verh - 45 - dy_at_m186 * 20);
        ++dy_at_m186;
    }
    if (cell_data.at(x, y).feats != 0)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (cell_data.at(x, y).feats / 1000 % 100 == 15)
            {
                p_at_m186 = cell_data.at(x, y).feats / 100000 % 100 +
                    cell_data.at(x, y).feats / 10000000 * 100;
                bmes(
                    mapname(p_at_m186, true),
                    100,
                    windowh - inf_verh - 45 - dy_at_m186 * 20);
                ++dy_at_m186;
            }
            if (cell_data.at(x, y).feats / 1000 % 100 == 34)
            {
                bmes(
                    txtbuilding(
                        cell_data.at(x, y).feats / 100000 % 100,
                        cell_data.at(x, y).feats / 10000000),
                    100,
                    windowh - inf_verh - 45 - dy_at_m186 * 20);
                ++dy_at_m186;
            }
        }
    }
    cansee = 1;
}



int key_direction(const std::string& action)
{
    kdx = 0;
    kdy = 0;
    if (action == "north")
    {
        --kdy;
        return 1;
    }
    if (action == "south")
    {
        ++kdy;
        return 1;
    }
    if (action == "west")
    {
        --kdx;
        return 1;
    }
    if (action == "east")
    {
        ++kdx;
        return 1;
    }
    if (action == "northwest")
    {
        --kdx;
        --kdy;
        return 1;
    }
    if (action == "northeast")
    {
        ++kdx;
        --kdy;
        return 1;
    }
    if (action == "southwest")
    {
        --kdx;
        ++kdy;
        return 1;
    }
    if (action == "southeast")
    {
        ++kdx;
        ++kdy;
        return 1;
    }
    return 0;
}



TurnResult step_into_gate()
{
    if (maybe_show_ex_help(17, true))
    {
        return TurnResult::pc_turn_user_error;
    }

    if (!game_data.wizard)
    {
        save_game();
    }
    txt(i18n::s.get("core.action.exit_map.gate.step_into"));
    inv[ci].modify_number(-1);
    txt(i18n::s.get("core.action.exit_map.gate.need_network"));
    update_screen();
    return TurnResult::pc_turn_user_error;
}



int target_position(bool target_chara)
{
    if (tlocinitx != 0 || tlocinity != 0 || homemapmode == 1)
    {
        tlocx = tlocinitx;
        tlocy = tlocinity;
    }
    else
    {
        tlocx = cdata[cc].position.x;
        tlocy = cdata[cc].position.y;
    }

    if (homemapmode)
    {
        scposval = 0;
    }
    else
    {
        scposval = 1;

        if (target_chara)
        {
            if (cdata.player().enemy_id == 0)
            {
                find_enemy_target();
            }
            build_target_list();
            if (listmax == 0)
            {
                txt(i18n::s.get("core.misc.no_target_around"));
            }
            for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
            {
                if (list(0, cnt) == 0)
                {
                    continue;
                }
                if (list(0, cnt) == cdata.player().enemy_id)
                {
                    tlocx = cdata[list(0, cnt)].position.x;
                    tlocy = cdata[list(0, cnt)].position.y;
                    break;
                }
            }
        }
    }

    while (1)
    {
        screenupdate = -1;
        update_screen();
        dx = (tlocx - scx) * inf_tiles + inf_screenx;
        dy = (tlocy - scy) * inf_tiles + inf_screeny;
        if (dy + inf_tiles <= windowh - inf_verh)
        {
            snail::Application::instance().get_renderer().set_blend_mode(
                snail::BlendMode::blend);
            snail::Application::instance().get_renderer().set_draw_color(
                {127, 127, 255, 50});
            snail::Application::instance().get_renderer().fill_rect(
                dx,
                dy * (dy > 0),
                inf_tiles -
                    (dx + inf_tiles > windoww) * (dx + inf_tiles - windoww),
                inf_tiles + (dy < 0) * inf_screeny -
                    (dy + inf_tiles > windowh - inf_verh) *
                        (dy + inf_tiles - windowh + inf_verh));
        }
        if (homemapmode == 1)
        {
            draw_map_tile(tile, windoww - 80, 20);
        }
        else
        {
            rc = -1;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (cell_data.at(tlocx, tlocy).chara_index_plus_one <= 1)
                {
                    break;
                }
                rc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
                if (is_in_fov(cdata[rc]) == 0)
                {
                    break;
                }
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[rc].position.x,
                        cdata[rc].position.y) == 0)
                {
                    break;
                }
                if ((cdata[rc].is_invisible() == 0 ||
                     cdata.player().can_see_invisible() || cdata[rc].wet) == 0)
                {
                    break;
                }
                get_route(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[rc].position.x,
                    cdata[rc].position.y);
                dx = (tlocx - scx) * inf_tiles + inf_screenx;
                dy = (tlocy - scy) * inf_tiles + inf_screeny;
                if (maxroute != 0)
                {
                    dx = cdata[cc].position.x;
                    dy = cdata[cc].position.y;
                    for (int cnt = 0; cnt < 100; ++cnt)
                    {
                        int stat = route_info(dx, dy, cnt);
                        if (stat == 0)
                        {
                            break;
                        }
                        else if (stat == -1)
                        {
                            continue;
                        }
                        sx = (dx - scx) * inf_tiles + inf_screenx;
                        sy = (dy - scy) * inf_tiles + inf_screeny;
                        if (sy + inf_tiles <= windowh - inf_verh)
                        {
                            snail::Application::instance()
                                .get_renderer()
                                .set_blend_mode(snail::BlendMode::blend);
                            snail::Application::instance()
                                .get_renderer()
                                .set_draw_color({255, 255, 255, 25});
                            snail::Application::instance()
                                .get_renderer()
                                .fill_rect(
                                    sx,
                                    sy * (sy > 0),
                                    inf_tiles -
                                        (sx + inf_tiles > windoww) *
                                            (sx + inf_tiles - windoww),
                                    inf_tiles + (sy < 0) * inf_screeny -
                                        (sy + inf_tiles > windowh - inf_verh) *
                                            (sy + inf_tiles - windowh +
                                             inf_verh));
                        }
                    }
                }
            }
        }
        txttargetnpc(tlocx, tlocy);
        redraw();
        auto action = key_check();
        if (homemapmode == 1)
        {
            if (action == "enter")
            {
                select_house_board_tile();
                wait_key_released();
                continue;
            }
            const auto input =
                stick(StickKey::mouse_left | StickKey::mouse_right);
            if (input == StickKey::mouse_left)
            {
                action = "enter";
            }
            if (input == StickKey::mouse_right)
            {
                if (chip_data.for_cell(tlocx, tlocy).kind == 2 ||
                    chip_data.for_cell(tlocx, tlocy).kind == 1)
                {
                    snd("core.fail1");
                    wait_key_released();
                    continue;
                }
                tile = cell_data.at(tlocx, tlocy).chip_id_actual;
                snd("core.cursor1");
                wait_key_released();
            }
            tx = clamp(mousex - inf_screenx, 0, windoww) / inf_tiles;
            ty = clamp(mousey - inf_screeny, 0, (windowh - inf_verh)) /
                inf_tiles;
            int stat = key_direction(action);
            if (stat == 1)
            {
                cdata.player().position.x += kdx;
                cdata.player().position.y += kdy;
                if (cdata.player().position.x < 0)
                {
                    cdata.player().position.x = 0;
                }
                else if (cdata.player().position.x >= map_data.width)
                {
                    cdata.player().position.x = map_data.width - 1;
                }
                if (cdata.player().position.y < 0)
                {
                    cdata.player().position.y = 0;
                }
                else if (cdata.player().position.y >= map_data.height)
                {
                    cdata.player().position.y = map_data.height - 1;
                }
            }
            tlocx = clamp(tx + scx, 0, map_data.width - 1);
            tlocy = clamp(ty + scy, 0, map_data.height - 1);
        }
        else
        {
            int stat = key_direction(action);
            if (stat == 1)
            {
                x = tlocx + kdx;
                y = tlocy + kdy;
                if (x >= 0 && y >= 0 && x < map_data.width &&
                    y < map_data.height)
                {
                    tlocx += kdx;
                    tlocy += kdy;
                }
            }
        }
        if (findlocmode == 1)
        {
            if (rc == -1)
            {
                i = 0;
            }
            else
            {
                i = rc;
            }
            f = 0;
            p = 0;
            for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
            {
                if (cdata[list(0, cnt)].position.x == cdata[i].position.x)
                {
                    if (cdata[list(0, cnt)].position.y == cdata[i].position.y)
                    {
                        p = cnt;
                        break;
                    }
                }
            }
            if (action == "next_page")
            {
                ++p;
                f = 1;
                if (p >= listmax)
                {
                    p = 0;
                }
            }
            if (action == "previous_page")
            {
                --p;
                f = 1;
                if (p < 0)
                {
                    p = listmax - 1;
                    if (p < 0)
                    {
                        p = 0;
                    }
                }
            }
            i = list(0, p);
            if (f)
            {
                snd("core.cursor1");
                tlocx = cdata[list(0, p)].position.x;
                tlocy = cdata[list(0, p)].position.y;
            }
        }
        if (action == "enter")
        {
            if (findlocmode == 1)
            {
                if (cansee == 0 || chip_data.for_cell(tlocx, tlocy).effect & 4)
                {
                    txt(i18n::s.get(
                        "core.action.which_direction.cannot_see_location"));
                    continue;
                }
                snd("core.ok1");
                if (rc > 0)
                {
                    cdata.player().enemy_id = rc;
                    txt(i18n::s.get("core.action.look.target", cdata[rc]));
                }
                else
                {
                    tgloc = 1;
                    tglocx = tlocx;
                    tglocy = tlocy;
                    txt(i18n::s.get("core.action.look.target_ground"));
                }
            }
            else if (homemapmode == 0)
            {
                snd("core.cursor1");
            }
            scposval = 0;
            if (tlocinitx == 0 && tlocinity == 0 && homemapmode != 1)
            {
                update_screen();
            }
            tlocinitx = 0;
            tlocinity = 0;
            return cansee;
        }
        if (action == "cancel")
        {
            tlocinitx = 0;
            tlocinity = 0;
            scposval = 0;
            update_screen();
            return -1;
        }
    }
}



TurnResult do_use_magic()
{
    int stat = do_magic_attempt();
    if (stat == 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}


void equip_melee_weapon()
{
    attacknum = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] / 10000 != 5)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        if (inv[cw].dice_x == 0)
        {
            continue;
        }
        ++attacknum;
        if (cdata[cc].equipment_type & 2)
        {
            if (inv[cw].weight >= 4000)
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.fits_well", inv[cw]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.too_light", inv[cw]));
            }
        }
        if (cdata[cc].equipment_type & 4)
        {
            if (attacknum == 1)
            {
                if (inv[cw].weight >= 4000)
                {
                    txt(i18n::s.get(
                        "core.action.equip.two_handed.too_heavy", inv[cw]));
                }
            }
            else if (inv[cw].weight > 1500)
            {
                txt(i18n::s.get(
                    "core.action.equip.two_handed.too_heavy_other_hand",
                    inv[cw]));
            }
        }
        if (cc == 0)
        {
            if (game_data.mount != 0)
            {
                if (inv[cw].weight >= 4000)
                {
                    txt(i18n::s.get(
                        "core.action.equip.two_handed.too_heavy_when_"
                        "riding",
                        inv[cw]));
                }
            }
        }
    }
}



TurnResult try_interact_with_npc()
{
    if (cdata[tc].activity.turn != 0)
    {
        txt(i18n::s.get("core.action.npc.is_busy_now", cdata[tc]));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    menucycle = 1;
    invally = 1;
    invctrl = 10;
    snd("core.inv");
    MenuResult mr = ctrl_inventory();
    assert(mr.turn_result != TurnResult::none);
    return mr.turn_result;
}



void sort_list_by_column1()
{
    if (listmax < 1)
    {
        return;
    }
    while (1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            if (list(1, cnt) > list(1, cnt + 1))
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                p = 1;
            }
        }
        if (p == 0)
        {
            break;
        }
    }
}



void sort_list_and_listn_by_column1()
{
    if (listmax < 1)
    {
        return;
    }
    while (1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            if (list(1, cnt) > list(1, cnt + 1))
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                s(0) = listn(0, cnt);
                s(1) = listn(1, cnt);
                listn(0, cnt) = listn(0, cnt + 1);
                listn(1, cnt) = listn(1, cnt + 1);
                listn(0, cnt + 1) = s;
                listn(1, cnt + 1) = s(1);
                p = 1;
            }
        }
        if (p == 0)
        {
            break;
        }
    }
}



void savecycle()
{
    if (menucycle == 1)
    {
        menucycle = 0;
        if (invally == 0 && invcontainer == 0)
        {
            lastctrl = invctrl;
        }
    }
}



int find_enemy_target()
{
    if (cdata[cdata[cc].enemy_id].state() != Character::State::alive)
    {
        cdata[cc].enemy_id = 0;
    }
    else if (is_in_fov(cdata[cdata[cc].enemy_id]) == 0)
    {
        cdata[cc].enemy_id = 0;
    }
    if (cdata[cc].enemy_id == 0)
    {
        build_target_list();
        if (listmax != 0)
        {
            f = 0;
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                p(0) = -3;
                p(1) = -1;
                p(2) = 0;
            }
            else
            {
                p(0) = 10;
                p(1) = 0;
                p(2) = 0;
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                int cnt2 = cnt;
                for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
                {
                    if (cdata[list(0, cnt)].relationship <= p(cnt2))
                    {
                        cdata[cc].enemy_id = list(0, cnt);
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    break;
                }
            }
        }
    }
    if (cdata[cc].enemy_id == 0 || cdata[cc].blind != 0)
    {
        if (cc == 0)
        {
            txt(i18n::s.get("core.action.ranged.no_target"));
            update_screen();
        }
        return 0;
    }
    if (cdata[cc].enemy_id < 0)
    {
        cdata[cc].enemy_id = 0;
    }
    return 1;
}



int prompt_really_attack()
{
    s = txttargetlevel(cc, tc);
    txt(s);
    txt(i18n::s.get("core.action.really_attack", cdata[tc]));
    if (yes_no())
    {
        update_screen();
        return 1;
    }
    else
    {
        update_screen();
        return 0;
    }
}



int can_do_ranged_attack()
{
    cw = -1;
    ammo = -1;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            ammo = cdata[cc].body_parts[cnt] % 10000 - 1;
        }
    }
    if (cw == -1)
    {
        cw = 0;
        return -1;
    }
    if (ammo == -1)
    {
        if (inv[cw].skill != 111)
        {
            cw = 0;
            return -2;
        }
    }
    if (ammo != -1)
    {
        if (inv[cw].skill != inv[ammo].skill)
        {
            return -3;
        }
    }
    attackskill = inv[cw].skill;
    return 1;
}



void build_target_list()
{
    listmax = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() != Character::State::alive)
            {
                continue;
            }
            if (is_in_fov(cnt) == 0)
            {
                continue;
            }
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                if (cnt.relationship == 10)
                {
                    if (cnt.index == 0)
                    {
                        continue;
                    }
                }
            }
            x = cnt.position.x;
            y = cnt.position.y;
            if (x == cdata[cc].position.x && y == cdata[cc].position.y)
            {
                continue;
            }
            if (fov_los(cdata[cc].position.x, cdata[cc].position.y, x, y) == 0)
            {
                continue;
            }
            if (cnt.is_invisible() == 1)
            {
                if (cdata[cc].can_see_invisible() == 0)
                {
                    if (cnt.wet == 0)
                    {
                        continue;
                    }
                }
            }
            list(0, listmax) = cnt.index;
            list(1, listmax) = x;
            list(2, listmax) = y;
            ++listmax;
            if (listmax >= 499)
            {
                break;
            }
        }
        if (listmax != 0)
        {
            break;
        }
    }
    while (1)
    {
        if (listmax < 2)
        {
            break;
        }
        i = 1;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            p = dist(
                cdata[cc].position.x,
                cdata[cc].position.y,
                list(1, cnt),
                list(2, cnt));
            p(1) = dist(
                cdata[cc].position.x,
                cdata[cc].position.y,
                list(1, cnt + 1),
                list(2, cnt + 1));
            if (p(1) < p)
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                p(2) = list(2, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(2, cnt) = list(2, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                list(2, cnt + 1) = p(2);
                i = 0;
                break;
            }
        }
        if (i == 1)
        {
            break;
        }
    }
}



void try_to_return()
{
    int stat = quest_is_return_forbidden();
    if (stat == 1)
    {
        txt(i18n::s.get("core.misc.return.forbidden"));
        if (!yes_no())
        {
            update_screen();
            return;
        }
    }
    Prompt prompt;
    p = 0;
    p = 0;
    i = 7;
    if (area_data[i].outer_map == game_data.destination_outer_map)
    {
        list(0, p) = i;
        list(1, p) = 1;
        prompt.append(mapname(i));
        ++p;
    }
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        i = 500 - (cnt + 1);
        if (area_data[i].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[i].outer_map != game_data.destination_outer_map)
        {
            continue;
        }
        if (area_data[i].id == mdata_t::MapId::your_home)
        {
            continue;
        }
        if (area_data[i].visited_deepest_level == 0)
        {
            continue;
        }
        f = 0;
        if (area_data[i].can_return_to())
        {
            f = 1;
        }
        if (game_data.wizard)
        {
            if (area_data[i].can_return_to_if_wizard())
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            list(0, p) = i;
            list(1, p) = area_data[i].visited_deepest_level;
            auto text = mapname(i) + u8" "s +
                cnvrank(
                            (area_data[i].visited_deepest_level -
                             area_data[i].danger_level + 1)) +
                i18n::s.get("core.misc.dungeon_level");
            prompt.append(text);
            ++p;
        }
    }
    listmax = p;
    if (listmax == 0)
    {
        txt(i18n::s.get("core.misc.return.no_location"));
        return;
    }
    txt(i18n::s.get("core.misc.return.where_do_you_want_to_go"));
    rtval = prompt.query(promptx, prompty, 240);
    update_screen();
    if (rtval >= 0)
    {
        txt(i18n::s.get("core.misc.return.air_becomes_charged"));
        if (area_data[game_data.current_map].id ==
            mdata_t::MapId::random_dungeon)
        {
            if (game_data.current_dungeon_level ==
                area_data[game_data.current_map].deepest_level)
            {
                if (area_data[game_data.current_map].has_been_conquered != -1)
                {
                    txt(
                        i18n::s.get("core.misc.return.lord_of_dungeon_"
                                    "might_disappear"));
                }
            }
        }
        game_data.destination_map = list(0, rtval);
        game_data.destination_dungeon_level = list(1, rtval);
        game_data.is_returning_or_escaping = 15 + rnd(15);
    }
    update_screen();
}



TurnResult do_gatcha()
{
    int tmat = 0;
    screenupdate = -1;
    update_screen();
    if (inv[ci].id == ItemId::red_treasure_machine)
    {
        tmat = 40;
    }
    if (inv[ci].id == ItemId::blue_treasure_machine)
    {
        tmat = 41;
    }
    txt(i18n::s.get("core.action.gatcha.prompt", matname(tmat)));
    if (yes_no())
    {
        if (mat(tmat) > 0)
        {
            snd("core.gasha");
            matdelmain(tmat);
            if (inv[ci].id == ItemId::red_treasure_machine)
            {
                p = 415;
            }
            else
            {
                p = 416;
            }
            flt();
            if (itemcreate(
                    -1, p, cdata[cc].position.x, cdata[cc].position.y, 0))
            {
                inv[ci].param2 = 0;
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        else
        {
            txt(i18n::s.get("core.action.gatcha.do_not_have", matname(tmat)));
        }
    }
    return TurnResult::turn_end;
}



int read_textbook()
{
    if (inv[ci].id == ItemId::textbook)
    {
        if (sdata.get(inv[ci].param1, 0).original_level == 0)
        {
            txt(i18n::s.get("core.action.read.book.not_interested"));
            if (!yes_no())
            {
                return 0;
            }
        }
    }
    game_data.activity_about_to_start = 104;
    activity_others();
    return 1;
}



void remove_card_and_figures()
{
    for (auto&& item : inv.ground())
    {
        if (item.id == ItemId::card || item.id == ItemId::figurine)
        {
            item.remove();
        }
    }
}



void clear_existing_quest_list()
{
    ++game_data.map_regenerate_count;
    DIM3(qdata, 20, 500);
    SDIM3(qname, 40, 500);
    game_data.number_of_existing_quests = 0;
    initialize_adata();
}



void get_inheritance()
{
    ctrl_file(FileOperation2::map_items_write, u8"shop3.s2");
    p = 0;
    i = 0;
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        if (cnt >= 10 && cnt < 20)
        {
            p += sdata.get(cnt, 56).original_level;
        }
        if (cnt >= 100 && cnt < 400)
        {
            i += sdata.get(cnt, 56).original_level;
        }
    }
    p = (p - 250) / 7;
    if (p < 5)
    {
        p = 5;
    }
    else if (p > 50)
    {
        p = 50;
    }
    i = (p - 250) / 8;
    if (i < 5)
    {
        i = 5;
    }
    else if (i > 40)
    {
        i = 40;
    }
    earn_gold(cdata.player(), clamp(cdata.tmp().gold / 100, 1000, 100000));
    earn_platinum(cdata.player(), p);
    cdata.player().skill_bonus += i;
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        mat(cnt) = mat(cnt) / 3;
    }
}



void load_gene_files()
{
    ctrl_file(FileOperation::gene_read);
    DIM2(spell, 200);
    DIM2(spact, 500);
    for (auto&& cnt : cdata.all())
    {
        cnt.set_state(Character::State::empty);
    }
    sdata.copy(56, 0);
    sdata.clear(0);
    Character::copy(cdata.player(), cdata.tmp());
    cdata.player().clear();
    for (auto&& item : inv.ground())
    {
        item.remove();
    }
    for (auto&& item : inv.pc())
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (item.id == ItemId::secret_experience_of_lomias)
        {
            lomiaseaster = 1;
        }
        if (item.id == ItemId::deed_of_heirship ||
            the_item_db[itemid2int(item.id)]->subcategory == 53100)
        {
            continue;
        }
        if (item.id == ItemId::kitty_bank)
        {
            continue;
        }
        if (item.quality == Quality::special)
        {
            continue;
        }
        if (item.is_precious())
        {
            continue;
        }
        if (the_item_db[itemid2int(item.id)]->category == 25000)
        {
            item.count = -1;
        }
        item.body_part = 0;
        item_copy(item.index, inv_getfreeid(-1));
    }
    for (auto&& cnt : cdata.all())
    {
        chara_delete(cnt.index);
    }
    game_data.play_time = genetemp(805);
}



void save_gene()
{
    ctrl_file(FileOperation::gene_write);
}



std::string getnpctxt(const std::string& tag, const std::string& default_text)
{
    int p_at_m189 = 0;
    p_at_m189 = instr(txtbuff, 0, tag);
    if (p_at_m189 == -1)
    {
        return default_text;
    }
    p_at_m189 += instr(txtbuff, p_at_m189, u8"\""s);
    if (p_at_m189 == -1)
    {
        return default_text;
    }
    return strmid(
        txtbuff,
        p_at_m189 + 1,
        clamp(instr(txtbuff, p_at_m189 + 1, u8"\""s), 0, 70));
}



TurnResult do_enter_strange_gate()
{
    snd("core.exitmap1");
    map_prepare_for_travel_with_prev(
        static_cast<int>(mdata_t::MapId::show_house));
    return TurnResult::exit_map;
}



int ask_direction()
{
    keywait = 1;
    snail::Input::instance().clear_pressed_keys();
    snd("core.pop2");
    gsel(4);
    x = (cdata.player().position.x - scx) * inf_tiles + inf_screenx - 48;
    y = (cdata.player().position.y - scy) * inf_tiles + inf_screeny - 48;
    gmode(0);
    gcopy(0, x, y, 144, 144, 0, 0);
    gsel(0);
    t = 0;

    while (true)
    {
        ++t;
        gmode(2, 200 - t / 2 % 20 * (t / 2 % 20));
        x = (cdata.player().position.x - scx) * inf_tiles + inf_screenx + 24;
        y = (cdata.player().position.y - scy) * inf_tiles + inf_screeny + 24;
        if (!getkey(snail::Key::alt))
        {
            draw_rotated("direction_arrow", x, y - 48, 0);
            draw_rotated("direction_arrow", x, y + 48, 180);
            draw_rotated("direction_arrow", x + 48, y, 90);
            draw_rotated("direction_arrow", x - 48, y, 270);
        }
        draw_rotated("direction_arrow", x - 48, y - 48, 315);
        draw_rotated("direction_arrow", x + 48, y + 48, 135);
        draw_rotated("direction_arrow", x + 48, y - 48, 45);
        draw_rotated("direction_arrow", x - 48, y + 48, 225);
        redraw();
        gmode(0);
        gcopy(4, 0, 0, 144, 144, x - 48 - 24, y - 48 - 24);
        gmode(2);
        auto action = key_check(KeyWaitDelay::walk_run);
        x = cdata.player().position.x;
        y = cdata.player().position.y;
        if (action == "wait" || action == "enter")
        {
            tlocx = x;
            tlocy = y;
            keyhalt = 1;
            return 1;
        }
        if (action == "north")
        {
            if (getkey(snail::Key::alt))
            {
                continue;
            }
            else
            {
                y -= 1;
            }
        }
        if (action == "south")
        {
            if (getkey(snail::Key::alt))
            {
                continue;
            }
            else
            {
                y += 1;
            }
        }
        if (action == "west")
        {
            if (getkey(snail::Key::alt))
            {
                continue;
            }
            else
            {
                x -= 1;
            }
        }
        if (action == "east")
        {
            if (getkey(snail::Key::alt))
            {
                continue;
            }
            else
            {
                x += 1;
            }
        }
        if (action == "northwest")
        {
            x -= 1;
            y -= 1;
        }
        if (action == "northeast")
        {
            x += 1;
            y -= 1;
        }
        if (action == "southwest")
        {
            x -= 1;
            y += 1;
        }
        if (action == "southeast")
        {
            x += 1;
            y += 1;
        }
        if (action != ""s)
        {
            if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
            {
                x = cdata.player().position.x;
                y = cdata.player().position.y;
                keyhalt = 1;
                return 0;
            }
            if (x == cdata.player().position.x &&
                y == cdata.player().position.y)
            {
                return 0;
            }
            tlocx = x;
            tlocy = y;
            keyhalt = 1;
            return 1;
        }
    }
}



int efstatusfix(int doomed, int cursed, int none, int blessed)
{
    switch (efstatus)
    {
    case CurseState::doomed: return doomed;
    case CurseState::cursed: return cursed;
    case CurseState::none: return none;
    case CurseState::blessed: return blessed;
    default: assert(0); return none;
    }
}



void disarm_trap()
{
    cell_featset(movx, movy, 0);
    if (cdata[cc].god_id == core_god::mani)
    {
        txt(i18n::s.get("core.action.move.trap.disarm.dismantle"));
        for (int cnt = 0, cnt_end = (rnd(3) + 1); cnt < cnt_end; ++cnt)
        {
            atxspot = 19;
            matgetmain(
                random_material(
                    game_data.current_dungeon_level,
                    game_data.current_dungeon_level / 5),
                1);
        }
    }
    else
    {
        txt(i18n::s.get("core.action.move.trap.disarm.succeed"));
    }
}



void move_character()
{
label_21451_internal:
    if (g_config.scroll())
    {
        if (cc == 0)
        {
            ui_scroll_screen();
        }
    }
    cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
        .chara_index_plus_one = 0;
    cdata[cc].position.x = cdata[cc].next_position.x;
    cdata[cc].position.y = cdata[cc].next_position.y;
    cell_data.at(cdata[cc].next_position.x, cdata[cc].next_position.y)
        .chara_index_plus_one = cc + 1;
    if (cc == 0)
    {
        if (game_data.mount != 0)
        {
            cdata[game_data.mount].position.x = cdata.player().position.x;
            cdata[game_data.mount].position.y = cdata.player().position.y;
        }
    }
    movx = cdata[cc].position.x;
    movy = cdata[cc].position.y;
    if (cell_data.at(movx, movy).feats != 0)
    {
        cell_featread(movx, movy);
        if (feat(1) == 14)
        {
            if (feat(2) == 7)
            {
                if ((cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0) ||
                    cdata[cc].is_immune_to_mine() == 1)
                {
                    return;
                }
            }
            if (feat(0) != tile_trap && cc == 0)
            {
                int stat = try_to_reveal();
                if (stat == 1)
                {
                    refx = movx;
                    refy = movy;
                    discover_trap();
                    feat(0) = tile_trap;
                }
            }
            refdiff = 100 + game_data.current_dungeon_level * 3;
            if (feat(0) == tile_trap)
            {
                refdiff = refdiff / 3;
                if (cc == 0)
                {
                    if (sdata(175, cc) != 0)
                    {
                        int stat = try_to_disarm_trap();
                        if (stat == 1)
                        {
                            disarm_trap();
                            return;
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.action.move.trap.disarm.fail"));
                        }
                    }
                }
            }
            int stat = can_evade_trap();
            if (stat == 1)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.action.move.trap.evade", cdata[cc]));
                }
                if (cc == 0)
                {
                    refx = movx;
                    refy = movy;
                    discover_trap();
                }
            }
            else
            {
                if (cc == 0)
                {
                    refx = movx;
                    refy = movy;
                    discover_trap();
                    snd("core.trap1");
                }
                efsource = 5;
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.action.move.trap.activate.text", cdata[cc]));
                }
                if (feat(2) == 4)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.action.move.trap.activate.blind"));
                    }
                    status_ailment_damage(
                        cdata[cc],
                        StatusAilment::blinded,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 6)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.action.move.trap.activate.paralyze"));
                    }
                    status_ailment_damage(
                        cdata[cc],
                        StatusAilment::paralyzed,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 5)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.action.move.trap.activate.confuse"));
                    }
                    status_ailment_damage(
                        cdata[cc],
                        StatusAilment::confused,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 3)
                {
                    cell_featset(movx, movy, 0);
                    if (enchantment_find(cdata[cc], 22))
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get("core.magic.teleport.prevented"));
                        }
                        return;
                    }
                    for (int cnt = 0; cnt < 200; ++cnt)
                    {
                        cdata[cc].next_position.x = rnd(map_data.width - 2) + 1;
                        cdata[cc].next_position.y =
                            rnd(map_data.height - 2) + 1;
                        cell_check(
                            cdata[cc].next_position.x,
                            cdata[cc].next_position.y);
                        if (cellaccess == 1)
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                snd("core.teleport1");
                                txt(i18n::s.get(
                                    "core.magic.teleport.disappears",
                                    cdata[cc]));
                            }
                            cdata[cc].activity.finish();
                            update_screen();
                            break;
                        }
                    }
                    goto label_21451_internal;
                }
                if (feat(2) == 0)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(
                            i18n::s.get("core.action.move.trap.activate."
                                        "spears.text"));
                    }
                    if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                "core.action.move.trap.activate.spears."
                                "target_floating",
                                cdata[cc]));
                        }
                    }
                    else
                    {
                        damage_hp(
                            cdata[cc],
                            rnd(game_data.current_dungeon_level * 2 + 10),
                            -1);
                    }
                }
                if (feat(2) == 1)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.action.move.trap.activate.poison"));
                    }
                    status_ailment_damage(
                        cdata[cc],
                        StatusAilment::poisoned,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 2)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.action.move.trap.activate.sleep"));
                    }
                    status_ailment_damage(
                        cdata[cc],
                        StatusAilment::sleep,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 7)
                {
                    txt(i18n::s.get("core.action.move.trap.activate.mine"),
                        Message::color{ColorIndex::cyan});
                    BallAnimation(
                        {movx, movy}, 0, BallAnimation::Type::ball, ele)
                        .play();
                    cell_featset(movx, movy, 0);
                    damage_hp(cdata[cc], 100 + rnd(200), -1);
                }
                efsource = 0;
            }
        }
    }
}



void draw_sleep_background_frame()
{
    gcopy(4, 0, 0, windoww, windowh - inf_verh, 0, 0);
    gmode(2);
    render_hud();
    if (screenupdate == 0)
    {
        redraw();
    }
    screenupdate = 0;
}



void load_sleep_background()
{
    gmode(0);
    asset_load("bg_night");
    draw("bg_night", 0, 0, windoww, windowh - inf_verh);
    gsel(0);
}



void sleep_start()
{
    int timeslept = 0;
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        txt(i18n::s.get("core.activity.sleep.but_you_cannot"));
        game_data.character_and_status_for_gene = 0;
        return;
    }
    if (game_data.catches_god_signal)
    {
        txtgod(cdata.player().god_id, 10);
    }
    load_sleep_background();
    musicloop = 1;
    play_music("core.mcCoda");
    msg_halt();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        gmode(2, cnt * 10);
        draw_sleep_background_frame();
        await(g_config.animation_wait() * 10);
    }
    gmode(2);
    cc = 0;
    for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
    {
        tc = cnt;
        cdata[tc].wet = 0;
        cdata[tc].poisoned = 0;
        cdata[tc].sleep = 0;
        cdata[tc].confused = 0;
        cdata[tc].blind = 0;
        cdata[tc].paralyzed = 0;
        cdata[tc].dimmed = 0;
        cdata[tc].drunk = 0;
        cdata[tc].bleeding = 0;
        game_data.continuous_active_hours = 0;
        cdata[tc].hp = cdata[tc].max_hp;
        cdata[tc].mp = cdata[tc].max_mp;
        cdata[tc].sp = cdata[tc].max_sp;
        status_ailment_heal(cdata[tc], StatusAilment::sick, 7 + rnd(7));
        if (cdata[tc].has_anorexia())
        {
            cdata[tc].anorexia_count -= rnd(6);
        }
        else
        {
            cdata[tc].anorexia_count -= rnd(3);
        }
        if (cdata[tc].anorexia_count < 0)
        {
            cure_anorexia(cdata[tc]);
            cdata[tc].anorexia_count = 0;
        }
        heal_insanity(cdata[tc], 10);
        if (cdata[tc].has_lay_hand())
        {
            cdata[tc].is_lay_hand_available() = true;
        }
    }
    mode = 9;
    timeslept = 7 + rnd(5);
    for (int cnt = 0, cnt_end = (timeslept); cnt < cnt_end; ++cnt)
    {
        ++game_data.date.hour;
        weather_changes();
        if (mode != 9)
        {
            load_sleep_background();
            mode = 9;
        }
        game_data.continuous_active_hours = 0;
        game_data.date.minute = 0;
        cc = 0;
        draw_sleep_background_frame();
        await(g_config.animation_wait() * 25);
    }
    if (game_data.character_and_status_for_gene != 0)
    {
        tc = -1;
        for (int cnt = 1; cnt < 16; ++cnt)
        {
            if (cdata[cnt].has_made_gene() == 1)
            {
                if (cdata[cnt].state() == Character::State::alive)
                {
                    tc = cnt;
                    break;
                }
            }
        }
        if (tc != -1)
        {
            cdata[tc].has_made_gene() = false;
            show_random_event_window(
                i18n::s.get("core.activity.sleep.new_gene.title"),
                i18n::s.get("core.activity.sleep.new_gene.text", cdata[tc]),
                {i18n::s.get_enum("core.activity.sleep.new_gene.choices", 0)},
                u8"bg_re14");
            save_gene();
        }
    }
    draw_sleep_background_frame();
    game_data.character_and_status_for_gene = 0;
    mode = 0;
    wake_up();
    cdata[cc].nutrition -= 1500 / (trait(158) + 1);
    txt(i18n::s.get("core.activity.sleep.slept_for", timeslept),
        Message::color{ColorIndex::green});
    f = 0;
    if (cdata.player().activity.item == -1)
    {
        f = 1;
    }
    else
    {
        ci = cdata.player().activity.item;
        if (inv[ci].param1 == 0 || inv[ci].number() == 0 ||
            the_item_db[itemid2int(inv[ci].id)]->subcategory != 60004)
        {
            f = 1;
        }
    }
    if (f)
    {
        txt(i18n::s.get("core.activity.sleep.wake_up.so_so"));
    }
    else
    {
        i = 0;
        for (int cnt = 10; cnt < 18; ++cnt)
        {
            i += sdata.get(cnt, 0).original_level;
        }
        i = clamp(i / 6, 10, 1000);
        exp = i * i * i / 10;
        game_data.sleep_experience =
            game_data.sleep_experience * inv[ci].param1 / 100;
        grown = 0;
        for (int cnt = 0;; ++cnt)
        {
            if (game_data.sleep_experience >= exp)
            {
                game_data.sleep_experience -= exp;
            }
            else if (cnt != 0)
            {
                break;
            }
            modify_potential(cdata.player(), 10 + rnd(8), 1);
            ++grown;
            if (cnt > 6)
            {
                if (rnd(5) == 0)
                {
                    game_data.sleep_experience = 0;
                    break;
                }
            }
        }
        txt(i18n::s.get("core.activity.sleep.wake_up.good", grown),
            Message::color{ColorIndex::green});
    }
    msg_halt();
    play_music();
    save_set_autosave();
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        update_shop();
    }
}



void do_rest()
{
    if (!cdata[cc].activity)
    {
        cdata[cc].activity.type = Activity::Type::sleep;
        cdata[cc].activity.turn = 50;
        txt(i18n::s.get("core.activity.rest.start"));
        update_screen();
        return;
    }
    if (cdata[cc].activity.turn > 0)
    {
        if (cdata[cc].activity.turn % 2 == 0)
        {
            heal_sp(cdata[cc], 1);
        }
        if (cdata[cc].activity.turn % 3 == 0)
        {
            heal_hp(cdata[cc], 1);
            heal_mp(cdata[cc], 1);
        }
        return;
    }
    if (game_data.continuous_active_hours >= 30)
    {
        f = 0;
        if (game_data.continuous_active_hours >= 50)
        {
            f = 1;
        }
        else if (rnd(2) == 0)
        {
            f = 1;
        }
        if (f == 1)
        {
            txt(i18n::s.get("core.activity.rest.drop_off_to_sleep"));
            cdata[cc].activity.item = -1;
            sleep_start();
            cdata[cc].activity.finish();
            return;
        }
    }
    txt(i18n::s.get("core.activity.rest.finish"));
    cdata[cc].activity.finish();
}



void map_global_proc_travel_events()
{
    if (!cdata[cc].activity)
    {
        cdata[cc].activity.type = Activity::Type::travel;
        cdata[cc].activity.turn = 20;
        if (game_data.weather == 3)
        {
            cdata[cc].activity.turn = cdata[cc].activity.turn * 13 / 10;
        }
        if (game_data.weather == 4)
        {
            cdata[cc].activity.turn = cdata[cc].activity.turn * 16 / 10;
        }
        if (game_data.weather == 2 ||
            chip_data.for_cell(cdata[cc].position.x, cdata[cc].position.y)
                    .kind == 4)
        {
            cdata[cc].activity.turn = cdata[cc].activity.turn * 22 / 10;
        }
        if (game_data.weather == 1)
        {
            cdata[cc].activity.turn = cdata[cc].activity.turn * 5 / 10;
        }
        cdata[cc].activity.turn = cdata[cc].activity.turn * 100 /
            (100 + game_data.seven_league_boot_effect + sdata(182, 0));
        return;
    }
    if (cdata.player().nutrition <= 5000)
    {
        f = 0;
        for (const auto& item : inv.for_chara(cdata[cc]))
        {
            if (item.number() == 0)
            {
                continue;
            }
            if (the_item_db[itemid2int(item.id)]->category == 91000)
            {
                f = 1;
                ci = item.index;
                break;
            }
        }
        if (f == 1)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.misc.finished_eating", cdata[cc], inv[ci]));
            }
            activity_eating_finish();
        }
    }
    if (game_data.weather == 2 ||
        chip_data.for_cell(cdata[cc].position.x, cdata[cc].position.y).kind ==
            4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0 ||
                    cdata.player().gravity > 0)
                {
                    txt(i18n::s.get("core.action.move.global.weather."
                                    "snow.sound"),
                        Message::color{ColorIndex::cyan});
                    cdata[cc].activity.turn += 10;
                }
            }
            if (rnd(1000) == 0)
            {
                txt(i18n::s.get("core.action.move.global.weather.snow.message"),
                    Message::color{ColorIndex::purple});
                cdata[cc].activity.turn += 50;
            }
        }
        if (cdata.player().nutrition <= 2000)
        {
            if (cdata.player().has_anorexia() == 0)
            {
                snd("core.eat1");
                txt(i18n::s.get("core.action.move.global.weather.snow.eat"));
                cdata[cc].nutrition += 5000;
                show_eating_message();
                status_ailment_damage(
                    cdata.player(), StatusAilment::dimmed, 1000);
            }
        }
    }
    if (game_data.weather == 4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0 ||
                    cdata.player().gravity > 0)
                {
                    txt(i18n::s.get(
                            "core.action.move.global.weather.heavy_rain."
                            "sound"),
                        Message::color{ColorIndex::cyan});
                    cdata[cc].activity.turn += 5;
                }
            }
            if (cdata.player().confused == 0)
            {
                if (rnd(500) == 0)
                {
                    txt(i18n::s.get(
                            "core.action.move.global.weather.heavy_rain."
                            "message"),
                        Message::color{ColorIndex::purple});
                    cdata.player().confused = 10;
                }
            }
            else if (rnd(5) == 0)
            {
                cdata.player().confused = 10;
            }
        }
        cdata.player().blind = 3;
    }
    if (cdata[cc].activity.turn > 0)
    {
        ++game_data.date.minute;
        return;
    }
    traveldone = 1;
    game_data.distance_between_town += 4;
    cdata[cc].activity.finish();
}


int decode_book()
{
    int cibkread = 0;
    if (!cdata[cc].activity)
    {
        if (inv[ci].id == ItemId::ancient_book)
        {
            if (inv[ci].param2 != 0)
            {
                txt(i18n::s.get("core.action.read.book.already_decoded"));
                return 0;
            }
        }
        if (cdata[cc].blind != 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
            }
            return 0;
        }
        cdata[cc].activity.type = Activity::Type::read;
        if (inv[ci].id == ItemId::recipe)
        {
            p = 50;
        }
        else if (inv[ci].id == ItemId::ancient_book)
        {
            p = 50 + inv[ci].param1 * 50 + inv[ci].param1 * inv[ci].param1 * 20;
        }
        else
        {
            p = the_ability_db[efid]->difficulty;
        }
        cdata[cc].activity.turn = p / (2 + sdata(150, 0)) + 1;
        cdata[cc].activity.item = ci;
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.activity.read.start", cdata[cc], inv[ci]));
        }
        item_separate(ci);
        return 0;
    }
    if (cdata[cc].activity.turn > 0)
    {
        ci = cdata[cc].activity.item;
        cibkread = ci;
        chara_gain_exp_literacy(cdata.player());
        if (inv[ci].id == ItemId::recipe)
        {
            return 0;
        }
        if (inv[ci].id == ItemId::ancient_book)
        {
            r2 =
                50 + inv[ci].param1 * 50 + inv[ci].param1 * inv[ci].param1 * 20;
            r3 = 0;
        }
        else
        {
            r2 = the_ability_db[efid]->difficulty;
            r3 = efid;
        }
        if (inv[ci].curse_state == CurseState::blessed)
        {
            r2 = r2 * 100 / 120;
        }
        if (is_cursed(inv[ci].curse_state))
        {
            r2 = r2 * 150 / 100;
        }
        int stat = try_to_cast_spell();
        ci = cibkread;
        if (stat == 0)
        {
            cdata[cc].activity.finish();
            --inv[ci].count;
            if (inv[ci].count < 0)
            {
                inv[ci].count = 0;
            }
            if (inv[ci].count == 0)
            {
                inv[ci].modify_number(-1);
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.action.read.book.falls_apart", inv[ci]));
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.activity.read.finish", cdata[cc], inv[ci]));
    }
    if (inv[ci].id == ItemId::recipe)
    {
        if (inv[ci].param1 == 0)
        {
            cdata[cc].activity.finish();
            return 1;
        }
        txt(i18n::s.get("core.action.read.recipe.learned", inv[ci]));
        ++recipememory(inv[ci].subname);
        item_identify(inv[ci], IdentifyState::partly);
        inv[ci].modify_number(-1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.book.falls_apart", inv[ci]));
        }
        cdata[cc].activity.finish();
        return 1;
    }
    if (inv[ci].id == ItemId::ancient_book)
    {
        item_identify(inv[ci], IdentifyState::completely);
        txt(i18n::s.get("core.action.read.book.finished_decoding", inv[ci]));
        inv[ci].param2 = 1;
        inv[ci].count = 1;
        inv[ci].has_charge() = false;
        item_stack(0, ci, 1);
    }
    else
    {
        chara_gain_skill(
            cdata[cc],
            efid,
            1,
            (rnd(51) + 50) * (90 + sdata(165, cc) + (sdata(165, cc) > 0) * 20) /
                    clamp((100 + spell((efid - 400)) / 2), 50, 1000) +
                1);
        chara_gain_exp_memorization(cdata.player(), efid);
        if (itemmemory(2, itemid2int(inv[ci].id)) == 0)
        {
            itemmemory(2, itemid2int(inv[ci].id)) = 1;
        }
    }
    item_identify(inv[ci], IdentifyState::partly);
    if (inv[ci].id != ItemId::ancient_book)
    {
        --inv[ci].count;
        if (inv[ci].count < 0)
        {
            inv[ci].count = 0;
        }
        if (inv[ci].count == 0)
        {
            inv[ci].modify_number(-1);
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.read.book.falls_apart", inv[ci]));
            }
        }
    }
    cdata[cc].activity.finish();
    return 1;
}



int read_normal_book()
{
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
        }
        return 0;
    }
    if (inv[ci].id == ItemId::license_of_the_void_explorer)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.void_permit"));
        return 1;
    }
    if (inv[ci].id == ItemId::textbook)
    {
        int stat = read_textbook();
        if (stat == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (inv[ci].id == ItemId::book_of_rachel)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.book_of_rachel"));
        return 1;
    }
    tc = cc;
    item_identify(inv[ci], IdentifyState::partly);
    show_book_window(inv[ci]);
    return 1;
}



int calcmagiccontrol(int caster_chara_index, int target_chara_index)
{
    if (sdata(188, caster_chara_index) != 0)
    {
        if (belong_to_same_team(
                cdata[caster_chara_index], cdata[target_chara_index]))
        {
            if (sdata(188, caster_chara_index) * 5 > rnd(dmg + 1))
            {
                dmg = 0;
            }
            else
            {
                dmg = rnd(
                    dmg * 100 / (100 + sdata(188, caster_chara_index) * 10) +
                    1);
            }
            if (dmg < 1)
            {
                if (is_in_fov(cdata[target_chara_index]))
                {
                    txt(i18n::s.get(
                        "core.misc.spell_passes_through",
                        cdata[target_chara_index]));
                }
                chara_gain_skill_exp(cdata[caster_chara_index], 188, 8, 4);
                return 1;
            }
            chara_gain_skill_exp(cdata[caster_chara_index], 188, 30, 2);
        }
    }
    return 0;
}



int do_cast_magic()
{
    int spellbk = 0;
    spellbk = efid;
    ccbk = cc;
    int stat = do_cast_magic_attempt();
    if (stat == 1)
    {
        cc = ccbk;
        chara_gain_exp_casting(cdata[cc], spellbk);
        return 1;
    }
    return 0;
}



int do_cast_magic_attempt()
{
    int mp = 0;
    efsource = 3;
    efstatus = CurseState::none;
    efp = calcspellpower(efid, cc);
    if (cc == 0)
    {
        if (calcspellcostmp(efid, cc) > cdata[cc].mp)
        {
            if (!g_config.skip_overcasting_warning())
            {
                txt(i18n::s.get("core.action.cast.overcast_warning"));
                if (!yes_no())
                {
                    update_screen();
                    efsource = 0;
                    return 0;
                }
            }
        }
        screenupdate = -1;
        update_screen();
    }
    int stat = prompt_magic_location();
    if (stat == 0)
    {
        efsource = 0;
        return 0;
    }
    if (cc != 0)
    {
        if (the_ability_db[efid]->ability_type == 7)
        {
            if (cdata[cc].relationship == 10 ||
                game_data.current_map == mdata_t::MapId::pet_arena)
            {
                efsource = 0;
                return 0;
            }
            if (game_data.play_turns % 10 > 4)
            {
                efsource = 0;
                return 0;
            }
        }
    }

    if (cc == 0)
    {
        spell(efid - 400) -= calcspellcoststock(efid, cc);
        if (spell(efid - 400) < 0)
        {
            spell(efid - 400) = 0;
        }
    }
    mp = calcspellcostmp(efid, cc);
    if (cc == 0)
    {
        if (cdata.player().god_id == core_god::ehekatl)
        {
            mp = rnd(mp * 140 / 100 + 1) + 1;
        }
    }
    damage_mp(cdata[cc], mp);
    if (cdata[cc].state() != Character::State::alive)
    {
        efsource = 0;
        return 1;
    }

    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.confused", cdata[cc]));
        }
        const auto tcbk = tc(0);
        int stat = try_to_cast_spell();
        tc = tcbk;
        if (stat == 0)
        {
            efsource = 0;
            return 1;
        }
    }
    else if (is_in_fov(cdata[cc]))
    {
        if (cc == 0)
        {
            txt(i18n::s.get(
                "core.action.cast.self",
                cdata[cc],
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(efid)->get(),
                    "name"),
                i18n::s.get_enum(
                    "core.ui.cast_style", cdata[cc].special_attack_type)));
        }
        else
        {
            txt(i18n::s.get(
                "core.action.cast.other",
                cdata[cc],
                i18n::s.get_enum(
                    "core.ui.cast_style", cdata[cc].special_attack_type)));
        }
    }
    if (buff_has(cdata[cc], "core.mist_of_silence"))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.silenced"));
        }
        efsource = 0;
        return 1;
    }
    if (rnd(100) >= calcspellfail(efid, cc))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.fail", cdata[cc]));
            FailureToCastAnimation(cdata[cc].position).play();
        }
        efsource = 0;
        return 1;
    }
    if (noeffect == 1)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        efsource = 0;
        return 1;
    }
    efp = calcspellpower(efid, cc);
    if (const auto spell_enhancement = enchantment_find(cdata[cc], 34))
    {
        efp = efp * (100 + *spell_enhancement / 10) / 100;
    }
    rapidmagic = 0;
    if (cdata[cc].can_cast_rapid_magic() &&
        the_ability_db[efid]->ability_type == 2)
    {
        rapidmagic = 1 + (rnd(3) != 0) + (rnd(2) != 0);
    }
    if (rapidmagic)
    {
        for (int cnt = 0, cnt_end = (rapidmagic); cnt < cnt_end; ++cnt)
        {
            magic();
            if (cdata[tc].state() != Character::State::alive)
            {
                int stat = find_enemy_target();
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    tc = cdata[cc].enemy_id;
                    if (relationbetween(cc, tc) != -3)
                    {
                        break;
                    }
                }
            }
        }
        rapidmagic = 0;
    }
    else
    {
        magic();
    }
    return 1;
}



int drink_potion()
{
    tc = cc;
    efsource = 4;
    if (potionspill || potionthrow)
    {
        if (potionthrow)
        {
            efp = efp * potionthrow / 100;
            efstatus = inv[ci].curse_state;
        }
    }
    else
    {
        efstatus = inv[ci].curse_state;
        if (is_in_fov(cdata[tc]))
        {
            snd_at("core.drink1", cdata[tc].position);
            txt(i18n::s.get("core.action.drink.potion", cdata[tc], inv[ci]));
        }
    }
    magic();
    if (potionspill || potionthrow)
    {
        potionspill = 0;
        potionthrow = 0;
    }
    else
    {
        if (obvious == 1)
        {
            if (tc == 0)
            {
                item_identify(inv[ci], IdentifyState::partly);
            }
        }
        inv[ci].modify_number(-1);
    }
    cdata[tc].nutrition += 150;
    if (tc < 16)
    {
        if (cdata[tc].nutrition > 12000)
        {
            if (rnd(5) == 0)
            {
                chara_vomit(cdata[tc]);
            }
        }
    }
    return 1;
}



int drink_well()
{
    if (inv[ci].param1 < -5 || inv[ci].param3 >= 20 ||
        (inv[ci].id == ItemId::holy_well && game_data.holy_well_count <= 0))
    {
        const auto valn = itemname(ci);
        txt(i18n::s.get("core.action.drink.well.is_dry", valn));
        return 1;
    }
    item_separate(ci);
    snd_at("core.drink1", cdata[cc].position);
    const auto valn = itemname(ci);
    txt(i18n::s.get("core.action.drink.well.draw", cdata[cc], valn));
    tc = cc;
    cibk = ci;
    p = rnd(100);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cc != 0)
        {
            if (rnd(15) == 0)
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.falls.text", cdata[cc]));
                txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.dialog",
                        cdata[cc]),
                    Message::color{ColorIndex::cyan});
                if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                {
                    txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.floats",
                        cdata[cc]));
                }
                else
                {
                    damage_hp(cdata[cc], 9999, -1);
                }
                break;
            }
        }
        if (inv[ci].id == ItemId::holy_well)
        {
            if (rnd(2) == 0)
            {
                efid = 1113;
                magic();
                break;
            }
        }
        if (p > 70)
        {
            p = rnd(5);
            if (p == 0)
            {
                efid = 1112;
                efp = 100;
                magic();
                break;
            }
            if (p == 1)
            {
                efid = 1110;
                efp = 100;
                magic();
                break;
            }
            if (p == 2)
            {
                efid = 1111;
                efp = 100;
                magic();
                break;
            }
            if (p == 3)
            {
                efid = 1109;
                efp = 100;
                magic();
                break;
            }
            if (p == 4)
            {
                efid = 1108;
                efp = 100;
                magic();
                break;
            }
        }
        if (p > 55)
        {
            flt();
            itemcreate(
                -1,
                54,
                cdata[cc].position.x,
                cdata[cc].position.y,
                rnd(sdata(159, cc) / 2 * 50 + 100) + 1);
            txt(i18n::s.get(
                "core.action.drink.well.effect.finds_gold", cdata[cc]));
            break;
        }
        if (p > 45)
        {
            p = rnd(8) + 10;
            if (rnd(5) > 2)
            {
                chara_gain_fixed_skill_exp(cdata[cc], p, 1000);
            }
            else
            {
                chara_gain_fixed_skill_exp(cdata[cc], p, -1000);
            }
            break;
        }
        if (p > 40)
        {
            if (cdata[cc].level < 5)
            {
                break;
            }
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.pregnancy", cdata[cc]));
            }
            tc = cc;
            get_pregnant();
            break;
        }
        if (p > 35)
        {
            txt(i18n::s.get("core.action.drink.well.effect.monster"));
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata[cc].level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            }
            break;
        }
        if (p > 33)
        {
            efid = 1113;
            magic();
            break;
        }
        if (p > 20)
        {
            efid = 454;
            magic();
            break;
        }
        if (p == 0)
        {
            if (rnd(game_data.wish_count + 1))
            {
                txt(i18n::s.get("core.action.drink.well.effect.wish_too_"
                                "frequent"),
                    Message::color{ColorIndex::orange});
                break;
            }
            ++game_data.wish_count;
            efid = 441;
            magic();
            break;
        }
        if (cc == 0)
        {
            txt(i18n::s.get("core.action.drink.well.effect.default"));
        }
    }
    ci = cibk;
    if (cc != 0)
    {
        cdata[cc].nutrition += 4000;
    }
    else
    {
        cdata[cc].nutrition += 500;
    }
    if (inv[ci].id == ItemId::holy_well)
    {
        --game_data.holy_well_count;
    }
    else
    {
        inv[ci].param1 -= rnd(3);
        inv[ci].param3 += rnd(3);
        if (inv[ci].param3 >= 20)
        {
            txt(i18n::s.get(
                "core.action.drink.well.completely_dried_up", inv[ci]));
            return 1;
        }
    }
    if (inv[ci].param1 < -5)
    {
        txt(i18n::s.get("core.action.drink.well.dried_up", inv[ci]));
    }
    return 1;
}



int read_scroll()
{
    tc = cc;
    tlocx = cdata[cc].position.x;
    tlocy = cdata[cc].position.y;
    efstatus = inv[ci].curse_state;
    efsource = 2;
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
        }
        efsource = 0;
        return 0;
    }
    if (cdata[cc].dimmed != 0 || cdata[cc].confused != 0)
    {
        if (rnd(4) != 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.read.scroll.dimmed_or_confused", cdata[cc]));
            }
            efsource = 0;
            return 0;
        }
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.read.scroll.execute", cdata[cc], inv[ci]));
    }
    if (inv[ci].id != ItemId::treasure_map)
    {
        inv[ci].modify_number(-1);
        chara_gain_skill_exp(cdata[cc], 150, 25, 2);
    }
    magic();
    if (cc == 0)
    {
        if (obvious == 1)
        {
            item_identify(inv[ci], IdentifyState::partly);
        }
    }
    return 1;
}



int do_zap()
{
    if (inv[ci].count <= 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.zap.execute", inv[ci]));
            txt(i18n::s.get("core.common.nothing_happens"));
        }
        return 0;
    }
    efstatus = inv[ci].curse_state;
    if (efstatus == CurseState::blessed)
    {
        efstatus = CurseState::none;
    }
    efsource = 1;
    int stat = prompt_magic_location();
    if (stat == 0)
    {
        efsource = 0;
        return 0;
    }
    if (efid >= 400 && efid < 467)
    {
        if ((stat == 0 && the_ability_db[efid]->range / 1000 * 1000 == 2000) ||
            noeffect == 1)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.zap.execute", inv[ci]));
                txt(i18n::s.get("core.common.nothing_happens"));
            }
            goto label_2173_internal;
        }
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.zap.execute", inv[ci]));
    }
    efp = efp *
        (100 + sdata(174, cc) * 10 + sdata(16, cc) / 2 + sdata(13, cc) / 2) /
        100;
    if (efid >= 400 && efid < 467)
    {
        f = 0;
        int skill = sdata(174, cc) * 20 + 100;
        if (inv[ci].curse_state == CurseState::blessed)
        {
            skill = skill * 125 / 100;
        }
        if (is_cursed(inv[ci].curse_state))
        {
            skill = skill * 50 / 100;
        }
        else if (rnd(2))
        {
            f = 1;
        }
        if (rnd((the_ability_db[efid]->difficulty + 1)) / 2 <= skill)
        {
            f = 1;
        }
    }
    else
    {
        f = 1;
    }
    if (rnd(30) == 0)
    {
        f = 0;
    }
    if (f == 1 || inv[ci].id == ItemId::rod_of_wishing || cc != 0)
    {
        magic();
        if (cc == 0)
        {
            if (obvious == 1)
            {
                item_identify(inv[ci], IdentifyState::partly);
            }
        }
        chara_gain_exp_magic_device(cdata[cc]);
    }
    else if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.zap.fail", cdata[cc]));
    }
label_2173_internal:
    efsource = 0;
    if (inv[ci].number() == 0)
    {
        if (ci >= ELONA_ITEM_ON_GROUND_INDEX)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            return 1;
        }
    }
    item_separate(ci);
    --inv[ci].count;
    return 1;
}



int do_magic_attempt()
{
    if (efid == 646)
    {
        if (cdata[tc].is_sentenced_daeth() == 1)
        {
            if (cdata[cc].relationship == -3)
            {
                for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
                {
                    if (cdata[cnt].state() == Character::State::alive)
                    {
                        if (cdata[cnt].relationship == 10)
                        {
                            cdata[cc].enemy_id = cnt;
                            break;
                        }
                    }
                }
            }
            return 0;
        }
    }
    {
        int stat = prompt_magic_location();
        if (stat == 0)
        {
            return 0;
        }
    }
    if (the_ability_db[efid]->range / 1000 * 1000 != 3000 &&
        the_ability_db[efid]->range / 1000 * 1000 != 10000)
    {
        if (cdata[cc].confused != 0 || cdata[cc].blind != 0)
        {
            if (rnd(5) == 0)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.misc.shakes_head", cdata[cc]));
                }
                return 1;
            }
        }
    }
    if (efid >= 600)
    {
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    return 1;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1) +
                    the_ability_db[efid]->cost / 2 + 1);
            chara_gain_skill_exp(
                cdata[cc], the_ability_db[efid]->related_basic_attribute, 25);
        }
    }
    efp = calcspellpower(efid, cc);
    if (noeffect == 1)
    {
        if (efid != 300)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            return 1;
        }
    }
    {
        int stat = magic();
        if (stat == 0)
        {
            return 0;
        }
    }
    return 1;
}



int prompt_magic_location()
{
    noeffect = 0;
    if (efid > 661)
    {
        tc = cc;
        return 1;
    }
    tg = the_ability_db[efid]->range / 1000 * 1000;
    if (efsource == 1)
    {
        if (tg == 3000)
        {
            tg = 8000;
        }
    }
    if (the_ability_db[efid]->ability_type == 7)
    {
        if (cc == 0)
        {
            tc = 0;
            return 1;
        }
    }
    if (tg == 8000)
    {
        if (cc == 0)
        {
            tc = 0;
            txt(i18n::s.get("core.action.which_direction.ask"));
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                return 0;
            }
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one == 0)
            {
                noeffect = 1;
                obvious = 0;
                return 1;
            }
            tc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
        }
        else
        {
            if (dist(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y) >
                the_ability_db[efid]->range % 1000 + 1)
            {
                return 0;
            }
            tlocx = cdata[tc].position.x;
            tlocy = cdata[tc].position.y;
        }
        return 1;
    }
    if (tg == 7000 || (tg == 9000 && tgloc == 1 && cc == 0))
    {
        if (cc == 0)
        {
            if (tg == 9000)
            {
                if (int stat = fov_los(
                                   cdata[cc].position.x,
                                   cdata[cc].position.y,
                                   tglocx,
                                   tglocy) == 0)
                {
                    if (stat == 0)
                    {
                        txt(
                            i18n::s.get("core.action.which_direction."
                                        "cannot_see_location"));
                        update_screen();
                    }
                    obvious = 0;
                    return 0;
                }
                tlocx = tglocx;
                tlocy = tglocy;
            }
            else
            {
                int stat = target_position();
                if (stat != 1)
                {
                    if (stat == 0)
                    {
                        txt(
                            i18n::s.get("core.action.which_direction."
                                        "cannot_see_location"));
                        update_screen();
                    }
                    obvious = 0;
                    return 0;
                }
            }
        }
        else
        {
            if (fov_los(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y) == 0)
            {
                return 0;
            }
            tlocx = cdata[tc].position.x;
            tlocy = cdata[tc].position.y;
        }
        return 1;
    }
    if (tg == 3000 || tg == 10000)
    {
        if (cc != 0)
        {
            if (the_ability_db[efid]->ability_type == 3)
            {
                if (dist(
                        cdata[tc].position.x,
                        cdata[tc].position.y,
                        cdata[cc].position.x,
                        cdata[cc].position.y) >
                    the_ability_db[efid]->range % 1000 + 1)
                {
                    return 0;
                }
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y) == 0)
                {
                    return 0;
                }
            }
        }
        tc = cc;
        tlocx = cdata[cc].position.x;
        tlocy = cdata[cc].position.y;
        return 1;
    }
    if (tg == 2000 || tg == 6000 || tg == 9000)
    {
        if (cc == 0)
        {
            int stat = find_enemy_target();
            if (stat == 0)
            {
                obvious = 0;
                return 0;
            }
            tc = cdata.player().enemy_id;
            if (cdata[tc].relationship >= 0)
            {
                int stat = prompt_really_attack();
                if (stat == 0)
                {
                    obvious = 0;
                    return 0;
                }
            }
        }
        if (dist(
                cdata[tc].position.x,
                cdata[tc].position.y,
                cdata[cc].position.x,
                cdata[cc].position.y) > the_ability_db[efid]->range % 1000 + 1)
        {
            if (cc == 0)
            {
                txt(i18n::s.get("core.action.which_direction.out_of_range"),
                    Message::only_once{true});
                update_screen();
            }
            return 0;
        }
        if (fov_los(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[tc].position.x,
                cdata[tc].position.y) == 0)
        {
            return 0;
        }
        tlocx = cdata[tc].position.x;
        tlocy = cdata[tc].position.y;
        return 1;
    }
    if (tg == 5000)
    {
        if (cc == 0)
        {
            if (efsource == 3)
            {
                txt(i18n::s.get("core.action.which_direction.spell"));
            }
            else
            {
                txt(i18n::s.get("core.action.which_direction.wand"));
            }
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(i18n::s.get("core.common.it_is_impossible"));
                obvious = 0;
                return 0;
            }
        }
    }
    return 1;
}



void heal_both_rider_and_mount()
{
    int subloop = 0;
    subloop = 1;
    if (game_data.mount != 0)
    {
        if (tc == game_data.mount || tc == 0)
        {
            subloop = 2;
            if (tc == game_data.mount)
            {
                tc(1) = 0;
            }
            else
            {
                tc(1) = game_data.mount;
            }
        }
    }
    for (int cnt = 0, cnt_end = (subloop); cnt < cnt_end; ++cnt)
    {
        const auto amount = roll(dice1, dice2, bonus);
        heal_hp(cdata[tc(cnt)], amount);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::fear);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::poisoned, 50);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::confused, 50);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::dimmed, 30);
        status_ailment_heal(cdata[tc(cnt)], StatusAilment::bleeding, 20);
        heal_insanity(cdata[tc(cnt)], 1);
        if (is_in_fov(cdata[tc(cnt)]))
        {
            add_damage_popup(std::to_string(amount), tc(cnt), {127, 255, 127});
        }
    }
}



void heal_completely()
{
    cdata[tc].poisoned = 0;
    cdata[tc].sleep = 0;
    cdata[tc].confused = 0;
    cdata[tc].blind = 0;
    cdata[tc].paralyzed = 0;
    cdata[tc].choked = 0;
    cdata[tc].dimmed = 0;
    cdata[tc].drunk = 0;
    cdata[tc].bleeding = 0;
    game_data.continuous_active_hours = 0;
    cdata[tc].hp = cdata[tc].max_hp;
    cdata[tc].mp = cdata[tc].max_mp;
    cdata[tc].sp = cdata[tc].max_sp;
}



int pick_up_item(bool play_sound)
{
    const auto snd_ = [play_sound](const char* id) {
        if (play_sound)
        {
            snd(id);
        }
    };

    int sellgold = 0;
    if (cc != -1)
    {
        if (inv[ci].id == ItemId::gold_piece ||
            inv[ci].id == ItemId::platinum_coin)
        {
            snd_("core.getgold1");
            ti = ci;
            in = inv[ci].number();
            inv[ci].remove();
            txt(i18n::s.get(
                "core.action.pick_up.execute", cdata[cc], itemname(ti, in)));
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            if (inv[ci].id == ItemId::gold_piece)
            {
                earn_gold(cdata[cc], in);
            }
            else
            {
                earn_platinum(cdata[cc], in);
            }
            return 1;
        }
    }
    if (cc == 0)
    {
        if (game_data.mount != 0)
        {
            if (cdata[game_data.mount].activity)
            {
                if (cdata[game_data.mount].activity.item == ci)
                {
                    txt(i18n::s.get(
                        "core.action.pick_up.used_by_mount",
                        cdata[game_data.mount]));
                    return 1;
                }
            }
        }
        if (the_item_db[itemid2int(inv[ci].id)]->category == 57000)
        {
            if (inv[ci].own_state == 4)
            {
                if (!cdata.player().activity)
                {
                    if (!inv_getspace(0))
                    {
                        txt(i18n::s.get(
                            "core.ui.inv.common.inventory_is_full"));
                        return 0;
                    }
                    game_data.activity_about_to_start = 103;
                    activity_others();
                    return -1;
                }
            }
        }
        if (inv[ci].own_state == 3)
        {
            txt(i18n::s.get(
                "core.action.pick_up.do_you_want_to_remove", inv[ci]));
            if (yes_no())
            {
                snd_("core.build1");
                if (inv[ci].id == ItemId::shelter)
                {
                    std::string midbk = mid;
                    mid = ""s + 30 + u8"_"s + (100 + inv[ci].count);
                    tmpload(filepathutil::u8path(u8"mdata_"s + mid + u8".s2"));
                    if (fs::exists(
                            filesystem::dirs::tmp() /
                            (u8"mdata_"s + mid + u8".s2")))
                    {
                        ctrl_file(FileOperation::map_delete);
                    }
                    mid = midbk;
                    inv[ci].count = 0;
                    inv[ci].own_state = 0;
                }
            }
            else
            {
                return 0;
            }
        }
        if (inv_getfreeid(cc) == -1)
        {
            txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            return 0;
        }
    }
    inumbk = inv[ci].number() - in;
    inv[ci].set_number(in);
    if (cc == 0)
    {
        if (trait(215) != 0)
        {
            if (the_item_db[itemid2int(inv[ci].id)]->category == 56000)
            {
                if (inv[ci].count > 0)
                {
                    dbid = itemid2int(inv[ci].id);
                    item_db_on_zap(inv[ci], dbid);
                    txt(i18n::s.get(
                        "core.action.pick_up.you_absorb_magic", inv[ci]));
                    if (efid >= 400 && efid < 467)
                    {
                        spell(efid - 400) +=
                            inv[ci].count * 5 * inv[ci].number();
                    }
                    else
                    {
                        heal_mp(
                            cdata.player(),
                            inv[ci].count * 5 * inv[ci].number());
                    }
                    inv[ci].count = 0;
                }
            }
        }
        if (trait(216) != 0)
        {
            if (the_item_db[itemid2int(inv[ci].id)]->category == 52000)
            {
                if (inv[ci].id != ItemId::poison &&
                    inv[ci].id != ItemId::potion_of_cure_corruption)
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get("core.action.pick_up.poison_drips"));
                        inv[ci].id = ItemId::poison;
                    }
                }
            }
        }
    }
    if (inv[ci].own_state < 0)
    {
        inv[ci].own_state = 0;
    }
    inv[ci].is_quest_target() = false;
    item_checkknown(ci);
    int stat = item_stack(cc, ci);
    if (stat == 0)
    {
        ti = inv_getfreeid(cc);
        if (ti == -1)
        {
            inv[ci].set_number(inumbk + in);
            if (invctrl == 12)
            {
                txt(
                    i18n::s.get("core.action.pick_up.shopkeepers_"
                                "inventory_is_full"));
            }
            else
            {
                txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            }
            return 0;
        }
        item_copy(ci, ti);
        inv[ti].set_number(in);
    }
    inv[ci].set_number(inumbk);
    if (mode == 6)
    {
        if (the_item_db[itemid2int(inv[ti].id)]->category == 57000)
        {
            if (invctrl == 11 || invctrl == 22)
            {
                if (invctrl == 22 && invctrl(1) == 3)
                {
                    if (inv[ti].param3 > 0)
                    {
                        inv[ti].param3 += game_data.date.hours();
                    }
                }
                else if (inv[ti].param3 != 0 && inv[ti].material == 35)
                {
                    inv[ti].param3 = game_data.date.hours() +
                        the_item_db[itemid2int(inv[ti].id)]->expiration_date;
                    if (inv[ti].param2 != 0)
                    {
                        inv[ti].param3 += 72;
                    }
                }
            }
            if (invctrl == 24 && invctrl(1) == 3)
            {
                if (inv[ti].param3 > 0)
                {
                    inv[ti].param3 = inv[ti].param3 - game_data.date.hours();
                }
            }
        }
        if (invctrl == 11)
        {
            txt(i18n::s.get("core.action.pick_up.you_buy", itemname(ti, in)));
            sellgold = calcitemvalue(ti, 0) * in;
            snd_("core.paygold1");
            cdata.player().gold -= sellgold;
            earn_gold(cdata[tc], sellgold);
            if (the_item_db[itemid2int(inv[ti].id)]->category == 92000)
            {
                inv[ti].param2 = calcitemvalue(ti, 0);
            }
        }
        if (invctrl == 12)
        {
            sellgold = calcitemvalue(ci, 1) * in;
            if (!inv[ti].is_stolen())
            {
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell", itemname(ti, in)));
            }
            else
            {
                inv[ti].is_stolen() = false;
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell_stolen", itemname(ti, in)));
                if (game_data.guild.thieves_guild_quota > 0)
                {
                    game_data.guild.thieves_guild_quota -= sellgold;
                    if (game_data.guild.thieves_guild_quota < 0)
                    {
                        game_data.guild.thieves_guild_quota = 0;
                    }
                    txt(i18n::s.get(
                        "core.action.pick_up.thieves_guild_quota",
                        game_data.guild.thieves_guild_quota));
                }
            }
            snd_("core.getgold1");
            earn_gold(cdata.player(), sellgold);
            cdata[tc].gold -= sellgold;
            if (cdata[tc].gold < 0)
            {
                cdata[tc].gold = 0;
            }
            inv[ti].identify_state = IdentifyState::completely;
        }
        if (invctrl == 22 || invctrl == 24)
        {
            sound_pick_up();
            if (invctrl == 22)
            {
                txt(i18n::s.get(
                    "core.action.pick_up.execute",
                    cdata[cc],
                    itemname(ti, in)));
            }
            else
            {
                txt(i18n::s.get(
                    "core.action.pick_up.put_in_container", itemname(ti, in)));
            }
        }
        else
        {
            chara_gain_exp_negotiation(cdata.player(), sellgold);
        }
    }
    else
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        cell_data.at(inv[ci].position.x, inv[ci].position.y)
            .item_appearances_memory =
            cell_data.at(inv[ci].position.x, inv[ci].position.y)
                .item_appearances_actual;
        sound_pick_up();
        txt(i18n::s.get(
            "core.action.pick_up.execute", cdata[cc], itemname(ti, in)));
    }
    if (cc == 0)
    {
        if (inv[ti].id == ItemId::campfire)
        {
            if (map_data.play_campfire_sound == 1)
            {
                f = 0;
                for (const auto& item : inv.ground())
                {
                    if (item.number() == 0)
                    {
                        continue;
                    }
                    if (item.id == ItemId::campfire)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0)
                {
                    map_data.play_campfire_sound = 0;
                    play_music();
                }
            }
        }
        int stat = convertartifact(ti);
        ti = stat;
        if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
        {
            if (mode == 0)
            {
                update_museum();
            }
        }
        if (game_data.current_map == mdata_t::MapId::your_home)
        {
            if (mode == 0)
            {
                calc_home_rank();
            }
        }
        refresh_burden_state();
    }
    if (cc == -1)
    {
        refresh_burden_state();
    }

    return 1;
}



int equip_item(int cc)
{
    if (ci == -1)
    {
        return 0;
    }
    if (cdata[cc].body_parts[body - 100] % 10000 != 0)
    {
        return 0;
    }
    if (inv[ci].body_part != 0)
    {
        return 0;
    }
    item_separate(ci);
    if (cc == 0)
    {
        item_identify(inv[ci], IdentifyState::almost);
    }
    inv[ci].body_part = body;
    cdata[cc].body_parts[body - 100] =
        cdata[cc].body_parts[body - 100] / 10000 * 10000 + ci + 1;
    return 1;
}



void unequip_item(int cc)
{
    p = cdata[cc].body_parts[body - 100] % 10000;
    if (p == 0)
    {
        rtval = -2;
        return;
    }
    ci = p - 1;
    cdata[cc].body_parts[body - 100] =
        cdata[cc].body_parts[body - 100] / 10000 * 10000;
    inv[ci].body_part = 0;
    item_stack(cc, ci);
}



void lost_body_part(int cc)
{
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        if (cdata[cc].body_parts[cnt] / 10000 == body)
        {
            p = cdata[cc].body_parts[cnt] % 10000;
            if (p == 0)
            {
                continue;
            }
            --p;
            inv[p].body_part = 0;
            cdata[cc].body_parts[cnt] =
                cdata[cc].body_parts[cnt] / 10000 * 10000;
        }
    }
}


TurnResult do_bash()
{
    if (cell_data.at(x, y).item_appearances_memory != 0)
    {
        if (mapitemfind(x, y, 526) != -1)
        {
            ci = mapitemfind(x, y, 526);
            item_separate(ci);
            snd("core.bash1");
            txt(i18n::s.get("core.action.bash.tree.execute", inv[ci]));
            if (inv[ci].own_state == 5 || inv[ci].param1 <= 0)
            {
                txt(i18n::s.get("core.action.bash.tree.no_fruits"));
                return TurnResult::turn_end;
            }
            --inv[ci].param1;
            if (inv[ci].param1 <= 0)
            {
                inv[ci].image = 592;
                cell_refresh(x, y);
            }
            if (y + 1 < map_data.height)
            {
                if ((chip_data.for_cell(x, y + 1).effect & 4) == 0)
                {
                    ++y;
                }
            }
            flt();
            itemcreate(-1, inv[ci].param2, x, y, 0);
            txt(i18n::s.get("core.action.bash.tree.falls_down", inv[ci]));
            item_stack(-1, ci);
            return TurnResult::turn_end;
        }
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        tc = cell_data.at(x, y).chara_index_plus_one - 1;
        if (cdata[tc].sleep == 0)
        {
            if (cc == 0)
            {
                if (cdata[tc].relationship >= 0)
                {
                    int stat = prompt_really_attack();
                    if (stat == 0)
                    {
                        return TurnResult::pc_turn_user_error;
                    }
                }
            }
            if (cdata[tc].choked)
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.choked.execute", cdata[cc], cdata[tc]));
                damage_hp(cdata[tc], sdata(10, cc) * 5, cc);
                if (cdata[tc].state() == Character::State::alive)
                {
                    txt(i18n::s.get(
                        "core.action.bash.choked.spits", cdata[tc]));
                    txt(i18n::s.get("core.action.bash.choked.dialog"));
                    cdata[tc].choked = 0;
                    chara_modify_impression(cdata[tc], 10);
                }
            }
            else
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.execute", cdata[cc], cdata[tc]));
                hostileaction(cc, tc);
            }
        }
        else
        {
            snd("core.bash1");
            txt(i18n::s.get("core.action.bash.execute", cdata[cc], cdata[tc]));
            txt(i18n::s.get(
                "core.action.bash.disturbs_sleep", cdata[cc], cdata[tc]));
            modify_karma(cdata[cc], -1);
            cdata[tc].emotion_icon = 418;
        }
        cdata[tc].sleep = 0;
        return TurnResult::turn_end;
    }
    if (cell_data.at(x, y).feats != 0)
    {
        cell_featread(x, y);
        if (feat(1) == 30)
        {
            cell_data.at(x, y).feats = 0;
            spillfrag(x, y, 2);
            flt(calcobjlv(
                    game_data.current_dungeon_level *
                    (game_data.current_map != mdata_t::MapId::shelter_)),
                calcfixlv(Quality::bad));
            flttypemajor = choice(fsetbarrel);
            itemcreate(-1, 0, x, y, 0);
            if (is_in_fov(cdata[cc]))
            {
                snd("core.bash1");
                txt(i18n::s.get("core.action.bash.shatters_pot", cdata[cc]));
                snd("core.crush1");
                BreakingAnimation({x, y}).play();
            }
            return TurnResult::turn_end;
        }
        if (feat(1) == 21)
        {
            snd("core.bash1");
            p = feat(2) * 3 + 30;
            if (game_data.current_map == mdata_t::MapId::jail)
            {
                p *= 20;
            }
            if (rnd(p(0)) < sdata(10, cc) && rnd(2))
            {
                txt(i18n::s.get("core.action.bash.door.destroyed"));
                if (feat(2) > sdata(10, cc))
                {
                    chara_gain_skill_exp(
                        cdata[cc], 10, (feat(2) - sdata(10, cc)) * 15);
                }
                cell_featset(x, y, 0, 0, 0, 0);
                return TurnResult::turn_end;
            }
            else
            {
                txt(i18n::s.get("core.action.bash.door.execute"));
                if (game_data.current_map == mdata_t::MapId::jail)
                {
                    txt(i18n::s.get("core.action.bash.door.jail"));
                }
                if (rnd(4) == 0)
                {
                    tc = cc;
                    efid = 1109;
                    efp = 200;
                    magic();
                }
                if (rnd(3) == 0)
                {
                    tc = cc;
                    efid = 1110;
                    efp = 200;
                    magic();
                }
                if (rnd(3) == 0)
                {
                    if (cdata[cc].quality < Quality::miracle &&
                        !enchantment_find(cdata[cc], 60010))
                    {
                        --cdata[cc].attr_adjs[0];
                        chara_refresh(cc);
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.action.bash.door.hurt", cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                    }
                }
                if (rnd(3) == 0)
                {
                    if (feat(2) > 0)
                    {
                        --feat(2);
                        cell_featset(x, y, feat(0), feat(1), feat(2), feat(3));
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get("core.action.bash.door.cracked"));
                        }
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }
    txt(i18n::s.get("core.action.bash.air", cdata[cc]));
    snd("core.miss");
    return TurnResult::turn_end;
}



TurnResult proc_movement_event()
{
    auto result = lua::lua->get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_moved", cdata[cc]));
    if (result.blocked())
    {
        return TurnResult::turn_end;
    }

    if (cdata[cc].is_ridden())
    {
        return TurnResult::turn_end;
    }
    dx = cdata[cc].next_position.x;
    dy = cdata[cc].next_position.y;
    if (cc < 16)
    {
        if (cc != 0)
        {
            if (dx != cdata[cc].position.x)
            {
                if (cdata[cc].position.x > dx)
                {
                    cdata[cc].direction = 1;
                }
                else
                {
                    cdata[cc].direction = 2;
                }
            }
            if (dy != cdata[cc].position.y)
            {
                if (cdata[cc].position.y > dy)
                {
                    cdata[cc].direction = 3;
                }
                else
                {
                    cdata[cc].direction = 0;
                }
            }
        }
    }
    if (cell_data.at(dx, dy).feats != 0)
    {
        cell_featread(dx, dy);
        if (feat(1) == 21)
        {
            return try_to_open_locked_door();
        }
        if (feat(1) == 30)
        {
            x = dx;
            y = dy;
            return do_bash();
        }
    }
    if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
            .mef_index_plus_one != 0)
    {
        bool turn_ended = mef_proc_from_movement(cc);
        if (turn_ended)
        {
            return TurnResult::turn_end;
        }
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (cc == 0)
        {
            if (traveldone == 0)
            {
                map_global_proc_travel_events();
                keybd_wait = 1;
                return TurnResult::turn_end;
            }
            else
            {
                traveldone = 0;
            }
        }
    }
    move_character();
    p = cell_data.at(cdata[cc].position.x, cdata[cc].position.y).chip_id_actual;
    if (chip_data[p].kind == 3)
    {
        if (chip_data[p].kind2 == 5)
        {
            heal_insanity(cdata[cc], 1);
        }
        addefmap(cdata[cc].position.x, cdata[cc].position.y, 1, 3);
        if (cdata[cc].wet == 0)
        {
            wet(cc, 20);
        }
    }
    sense_map_feats_on_move();
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (cc == 0)
        {
            encounter = 0;
            game_data.stood_world_map_tile =
                cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                    .chip_id_actual;
            if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                    .feats == 0)
            {
                p = cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                        .chip_id_actual;
                if (rnd(30) == 0)
                {
                    encounter = 1;
                }
                if (game_data.weather == 4)
                {
                    if (rnd(10) == 0)
                    {
                        encounter = 1;
                    }
                }
                if (game_data.weather == 1)
                {
                    if (rnd(13) == 0)
                    {
                        encounter = 1;
                    }
                }
                if (33 <= p && p < 66)
                {
                    if (rnd(2) == 0)
                    {
                        encounter = 0;
                    }
                    if (rnd(100) == 0)
                    {
                        encounter = 2;
                    }
                }
                if (rnd(220 + cdata.player().level * 10 -
                        clamp(
                            game_data.cargo_weight * 150 /
                                (game_data.current_cart_limit + 1),
                            0,
                            (210 + cdata.player().level * 10))) == 0)
                {
                    encounter = 4;
                }
                if (rnd(20) == 0)
                {
                    for (int cnt = 0; cnt < 5; ++cnt)
                    {
                        rq = game_data.taken_quests.at(cnt);
                        if (quest_data[rq].id == 1007)
                        {
                            if (quest_data[rq].progress == 1)
                            {
                                if (quest_data[rq].escort_difficulty == 0)
                                {
                                    if (quest_data[rq].target_chara_index < 2)
                                    {
                                        encounter = 3;
                                        encounterref = rq;
                                        ++quest_data[rq].target_chara_index;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (encounter == 4)
            {
                encounterlv = cdata.player().fame / 1000;
                if (encounterlv == 0)
                {
                    encounterlv = 1;
                }
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 3)
            {
                txt(i18n::s.get("core.misc.caught_by_assassins"));
                msg_halt();
                game_data.previous_map2 = game_data.current_map;
                game_data.previous_dungeon_level =
                    game_data.current_dungeon_level;
                game_data.previous_x = cdata.player().position.x;
                game_data.previous_y = cdata.player().position.y;
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 2)
            {
                encounterlv = 10 + rnd(100);
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            if (encounter == 1)
            {
                p = dist_town();
                encounterlv = p * 3 / 2 - 10;
                if (cdata.player().level <= 5)
                {
                    encounterlv /= 2;
                }
                if (33 <=
                        cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                            .chip_id_actual &&
                    cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                            .chip_id_actual < 66)
                {
                    encounterlv /= 2;
                }
                else if (game_data.weather == 1)
                {
                    encounterlv = encounterlv * 3 / 2 + 10;
                }
                if (encounterlv < 0)
                {
                    encounterlv = 1;
                }
                auto valn = i18n::s.get(
                                "core.action.move.global.ambush."
                                "distance_from_nearest_town",
                                p(0)) +
                    " " +
                    i18n::s.get(
                        "core.action.move.global.ambush.enemy_"
                        "strength");
                for (int cnt = 0; cnt < 1; ++cnt)
                {
                    if (encounterlv < 5)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.putit");
                        break;
                    }
                    if (encounterlv < 10)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.orc");
                        break;
                    }
                    if (encounterlv < 20)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank."
                            "grizzly_bear");
                        break;
                    }
                    if (encounterlv < 30)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.drake");
                        break;
                    }
                    if (encounterlv < 40)
                    {
                        valn += i18n::s.get(
                            "core.action.move.global.ambush.rank.lich");
                        break;
                    }
                    valn += i18n::s.get(
                        "core.action.move.global.ambush.rank.dragon");
                }
                valn += u8")"s;
                txt(i18n::s.get("core.action.move.global.ambush.text") + valn);
                msg_halt();
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            encounter = 0;
        }
    }
    return TurnResult::turn_end;
}



void proc_autopick()
{
    if (!g_config.autopick())
        return;
    if (is_modifier_pressed(snail::ModKey::ctrl))
        return;
    if (area_data[game_data.current_map].type ==
            mdata_t::MapType::player_owned &&
        area_data[game_data.current_map].id != mdata_t::MapId::shelter_ &&
        area_data[game_data.current_map].id != mdata_t::MapId::ranch)
        return;


    for (auto&& item : inv.ground())
    {
        if (item.number() == 0)
            continue;
        if (item.position != cdata.player().position)
            continue;
        if (item.own_state > 0)
            continue;

        item_checkknown(item.index);

        const auto x = cdata.player().position.x;
        const auto y = cdata.player().position.y;

        bool did_something = true;
        const auto op = Autopick::instance().get_operation(item);
        switch (op.type)
        {
        case Autopick::Operation::Type::do_nothing:
            did_something = false;
            break;
        case Autopick::Operation::Type::pick_up:
        case Autopick::Operation::Type::save:
        case Autopick::Operation::Type::no_drop:
        case Autopick::Operation::Type::save_and_no_drop:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get(
                    "core.ui.autopick.do_you_really_pick_up", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            in = item.number();
            elona::ci = item.index;
            pick_up_item(op.sound == "");
            if (int(op.type) & int(Autopick::Operation::Type::no_drop))
            {
                inv[ti].is_marked_as_no_drop() = true;
                txt(i18n::s.get("core.ui.inv.examine.no_drop.set", inv[ti]));
            }
            if (int(op.type) & int(Autopick::Operation::Type::save))
            {
                if (!game_data.wizard)
                {
                    save_game();
                }
            }
            break;
        case Autopick::Operation::Type::destroy:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get(
                    "core.ui.autopick.do_you_really_destroy", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            if (op.sound == "")
            {
                snd("core.crush1");
            }
            txt(i18n::s.get("core.ui.autopick.destroyed", item));
            item.remove();
            cell_refresh(x, y);
            cell_data.at(x, y).item_appearances_memory =
                cell_data.at(x, y).item_appearances_actual;
            break;
        case Autopick::Operation::Type::open:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get("core.ui.autopick.do_you_really_open", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            elona::ci = item.index;
            (void)do_open_command(op.sound == ""); // Result is unused.
            break;
        }
        if (did_something && op.sound != "")
        {
            snd(op.sound);
        }
    }
}



void sense_map_feats_on_move()
{
    if (cc == 0)
    {
        game_data.player_x_on_map_leave = -1;
        game_data.player_y_on_map_leave = -1;
        x = cdata.player().position.x;
        y = cdata.player().position.y;
        if (getkey(snail::Key::shift) &&
            game_data.player_cellaccess_check_flag == 0 &&
            cdata.player().confused == 0 && cdata.player().dimmed == 0)
        {
            if (map_data.type != mdata_t::MapType::world_map)
            {
                game_data.player_cellaccess_check_flag = 1;
                cell_check(cdata[cc].position.x + 1, cdata[cc].position.y);
                game_data.player_cellaccess_e = cellaccess;
                cell_check(cdata[cc].position.x - 1, cdata[cc].position.y);
                game_data.player_cellaccess_w = cellaccess;
                cell_check(cdata[cc].position.x, cdata[cc].position.y + 1);
                game_data.player_cellaccess_s = cellaccess;
                cell_check(cdata[cc].position.x, cdata[cc].position.y - 1);
                game_data.player_cellaccess_n = cellaccess;
            }
        }
        if (cell_data.at(x, y).item_appearances_actual != 0)
        {
            if (cdata.player().blind == 0)
            {
                txt(txtitemoncell(x, y));
                proc_autopick();
            }
            else
            {
                txt(i18n::s.get("core.action.move.sense_something"));
            }
        }
        p = chip_data.for_cell(x, y).kind;
        if (p != 0)
        {
            std::string tname = ""s;
            if (p == 1)
            {
                tname = i18n::s.get("core.item.chip.dryrock");
            }
            if (p == 2)
            {
                tname = i18n::s.get("core.item.chip.field");
            }

            if (tname != ""s)
            {
                txt(i18n::s.get("core.action.move.walk_into", tname));
            }
            if (p == 3)
            {
                snd("core.water2");
            }
            if (p == 4)
            {
                addefmap(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    3,
                    10,
                    dirsub,
                    rnd(2));
                if (keybd_wait <=
                        g_config.walk_wait() * g_config.start_run_wait() ||
                    cdata.player().turn % 2 == 0 ||
                    map_data.type == mdata_t::MapType::world_map)
                {
                    sound_footstep2(foot);
                    foot += 1 + rnd(2);
                }
            }
        }
        else if (map_data.type == mdata_t::MapType::world_map)
        {
            addefmap(cdata[cc].position.x, cdata[cc].position.y, 2, 10, dirsub);
            sound_footstep(foot);
            ++foot;
        }
        if (cell_data.at(x, y).feats != 0)
        {
            cell_featread(x, y);
            if (feat(1) == 32)
            {
                txt(i18n::s.get("core.action.move.twinkle"),
                    Message::color{ColorIndex::orange});
            }
            if (feat(1) == 15)
            {
                txt(mapname(feat(2) + feat(3) * 100, true));
                if (area_data[feat(2) + feat(3) * 100].id ==
                    mdata_t::MapId::random_dungeon)
                {
                    maybe_show_ex_help(6);
                }
            }
            if (feat(1) == 34)
            {
                txt(txtbuilding(feat(2), feat(3)));
            }
            if (feat(1) == 11)
            {
                txt(i18n::s.get("core.action.move.feature.stair.down"));
            }
            if (feat(1) == 10)
            {
                txt(i18n::s.get("core.action.move.feature.stair.up"));
            }
            if (feat(1) == 24)
            {
                txt(i18n::s.get("core.action.move.feature.material.spot"));
            }
            if (feat(1) == 27)
            {
                txt(i18n::s.get("core.action.move.feature.material.remains"));
            }
            if (feat(1) == 25)
            {
                txt(i18n::s.get("core.action.move.feature.material.mining"));
            }
            if (feat(1) == 26)
            {
                txt(i18n::s.get("core.action.move.feature.material.spring"));
            }
            if (feat(1) == 28)
            {
                txt(i18n::s.get("core.action.move.feature.material.plants"));
            }
            if (feat(1) == 29)
            {
                if (feat(2) == 36)
                {
                    s = i18n::s.get(
                        "core.action.move.feature.seed.type.vegetable");
                }
                if (feat(2) == 37)
                {
                    s = i18n::s.get("core.action.move.feature.seed.type.fruit");
                }
                if (feat(2) == 38)
                {
                    s = i18n::s.get("core.action.move.feature.seed.type.herb");
                }
                if (feat(2) == 39)
                {
                    s = i18n::s.get(
                        "core.action.move.feature.seed.type.strange");
                }
                if (feat(2) == 40)
                {
                    s = i18n::s.get(
                        "core.action.move.feature.seed.type.artifact");
                }
                if (feat(2) == 41)
                {
                    s = i18n::s.get("core.action.move.feature.seed.type.gem");
                }
                if (feat(2) == 42)
                {
                    s = i18n::s.get("core.action.move.feature.seed.type.magic");
                }
                if (feat == tile_plant)
                {
                    txt(i18n::s.get(
                        "core.action.move.feature.seed.growth.seed", s(0)));
                }
                if (feat == tile_plant + 1)
                {
                    txt(i18n::s.get(
                        "core.action.move.feature.seed.growth.bud", s(0)));
                }
                if (feat == tile_plant + 2)
                {
                    txt(i18n::s.get(
                        "core.action.move.feature.seed.growth.tree", s(0)));
                }
                if (feat == tile_plant + 3)
                {
                    txt(i18n::s.get(
                        "core.action.move.feature.seed.growth.withered", s(0)));
                }
            }
            if (feat(1) >= 24 && feat(1) <= 28)
            {
                maybe_show_ex_help(5);
            }
        }
    }
}



int unlock_box(int difficulty)
{
    int stat = item_find(636, 3);
    if (stat == -1)
    {
        txt(i18n::s.get("core.action.unlock.do_not_have_lockpicks"));
        return 0;
    }
    ti = stat;
    txt(i18n::s.get("core.action.unlock.use_lockpick"));
    snd("core.locked1");
    {
        int stat = item_find(637, 3);
        if (stat != -1)
        {
            i = sdata(158, 0) * 150 / 100 + 5;
            txt(i18n::s.get("core.action.unlock.use_skeleton_key"));
        }
        else
        {
            i = sdata(158, 0);
        }
    }
    f = 0;
    if (i * 2 < difficulty)
    {
        txt(i18n::s.get("core.action.unlock.too_difficult"));
        f = 1;
    }
    if (debug::voldemort)
    {
        f = 0;
    }
    if (f == 0)
    {
        if (i / 2 >= difficulty)
        {
            txt(i18n::s.get("core.action.unlock.easy"));
        }
        else if (rnd(rnd(i * 2) + 1) < difficulty)
        {
            txt(i18n::s.get("core.action.unlock.fail"));
            f = 1;
        }
    }
    if (f)
    {
        if (rnd(3) == 0)
        {
            inv[ti].modify_number(-1);
            txt(i18n::s.get("core.action.unlock.lockpick_breaks"));
        }
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.unlock.try_again"));
        if (yes_no())
        {
            unlock_box(difficulty);
            return 0;
        }
        return 0;
    }
    txt(i18n::s.get("core.action.unlock.succeed"));
    chara_gain_exp_lock_picking(cdata[cc]);
    return 1;
}



void open_box()
{
    snd("core.chest1");
    txt(i18n::s.get("core.action.open.text", inv[ci]));
    msg_halt();
    ri = ci;
    if (inv[ri].id == ItemId::material_box)
    {
        tc = cc;
        efid = 1117;
        efp = 100 + inv[ri].param1 * 10;
        inv[ri].param1 = 0;
        magic();
        return;
    }
    p = 3 + rnd(5);
    if (inv[ri].id == ItemId::treasure_ball ||
        inv[ri].id == ItemId::rare_treasure_ball ||
        inv[ri].id == ItemId::small_gamble_chest)
    {
        p = 1;
    }
    randomize(inv[ri].param3);
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        dbid = 0;
        Quality base_quality;
        if (cnt == 0)
        {
            base_quality = Quality::great;
        }
        else
        {
            base_quality = Quality::good;
        }
        if (inv[ri].id == ItemId::bejeweled_chest)
        {
            if (cnt == 0 && rnd(3) == 0)
            {
                base_quality = Quality::miracle;
            }
            else
            {
                base_quality = Quality::great;
            }
            if (rnd(60) == 0)
            {
                dbid = 559;
            }
        }
        flt(calcobjlv(inv[ri].param1), calcfixlv(base_quality));
        flttypemajor = choice(fsetchest);
        if (cnt > 0)
        {
            if (rnd(3) != 0)
            {
                if (rnd(3) != 0)
                {
                    flttypeminor = 0;
                    flttypemajor = 68000;
                }
                else
                {
                    flttypemajor = 0;
                    flttypeminor = 77001;
                }
            }
        }
        if (inv[ri].id == ItemId::safe)
        {
            if (rnd(3) != 0)
            {
                flttypeminor = 0;
                flttypemajor = 68000;
            }
            else
            {
                flttypemajor = 0;
                flttypeminor = 77001;
            }
        }
        if (inv[ri].id == ItemId::treasure_ball ||
            inv[ri].id == ItemId::rare_treasure_ball)
        {
            flttypeminor = 0;
            flttypemajor = choice(fsetwear);
            fixlv = Quality::great;
            if (inv[ri].id == ItemId::rare_treasure_ball)
            {
                fixlv = Quality::miracle;
            }
            if (rnd(30) == 0)
            {
                dbid = 559;
            }
        }
        in = 0;
        if (inv[ri].id == ItemId::small_gamble_chest)
        {
            dbid = 54;
            randomize();
            if (rnd(75) == 0)
            {
                in = 50 * inv[ci].value;
            }
            else
            {
                in = rnd(inv[ci].value / 10 + 1) + 1;
            }
        }
        if (inv[ri].id == ItemId::wallet)
        {
            dbid = 54;
            in = rnd(1000) + 1;
            if (rnd(5) == 0)
            {
                in = rnd(9) + 1;
            }
            if (rnd(10) == 0)
            {
                in = rnd(5000) + 5000;
            }
            if (rnd(20) == 0)
            {
                in = rnd(20000) + 10000;
            }
        }
        itemcreate(
            -1, dbid, cdata.player().position.x, cdata.player().position.y, in);
    }
    randomize();
    f = 0;
    if (inv[ri].id != ItemId::small_gamble_chest)
    {
        if (rnd(10) == 0)
        {
            f = 1;
        }
    }
    if (inv[ri].id == ItemId::bejeweled_chest || inv[ri].id == ItemId::chest)
    {
        if (rnd(5) == 0)
        {
            f = 1;
        }
    }
    if (f)
    {
        flt();
        itemcreate(
            -1, 622, cdata.player().position.x, cdata.player().position.y, 1);
    }
    snd("core.ding2");
    txt(i18n::s.get("core.action.open.goods", inv[ri]));
    save_set_autosave();
    inv[ri].param1 = 0;
    if (inv[ri].id == ItemId::wallet)
    {
        modify_karma(cdata.player(), -4);
    }
    if (inv[ri].id == ItemId::suitcase)
    {
        modify_karma(cdata.player(), -8);
    }
}



void open_new_year_gift()
{
    snd("core.chest1");
    txt(i18n::s.get("core.action.open.text", inv[ci]));
    msg_halt();
    snd("core.ding2");
    randomize();
    ri = ci;
    cc = 0;
    inv[ri].param1 = 0;
    if (inv[ri].param3 < 100)
    {
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(
                    i18n::s.get("core.action.open.new_year_gift."
                                "something_jumps_out"));
            }
            for (int cnt = 0, cnt_end = (3 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            }
            return;
        }
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.open.new_year_gift.trap"));
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                tlocx = cdata.player().position.x + rnd(3) - rnd(3);
                tlocy = cdata.player().position.y - rnd(3) + rnd(3);
                if (tlocx < 0 || tlocx >= map_data.width || tlocy < 0 ||
                    tlocy >= map_data.height)
                {
                    continue;
                }
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, 0);
                mapitem_fire(tlocx, tlocy);
            }
            return;
        }
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.cursed_letter"));
        }
        efid = 1114;
        efp = 1000;
        tc = 0;
        magic();
        return;
    }
    if (inv[ri].param3 < 200)
    {
        if (rnd(4) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                    Message::color{ColorIndex::orange});
            }
            flt();
            int stat = chara_create(
                -1, 328 + rnd(2), cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
            return;
        }
        if (rnd(5) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.open.new_year_gift.younger_sister"));
            }
            flt();
            int stat = chara_create(
                -1, 176, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                cdata[rc].gold = 5000;
            }
            return;
        }
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
        }
        flt();
        itemcreate(
            -1,
            choice(isetgiftminor),
            cdata.player().position.x,
            cdata.player().position.y,
            1);
        return;
    }
    if (rnd(3) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                Message::color{ColorIndex::orange});
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt();
            int stat = chara_create(
                -1, 328 + rnd(2), cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
        }
        return;
    }
    if (rnd(50) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.wonderful"));
        }
        flt();
        itemcreate(
            -1,
            choice(isetgiftgrand),
            cdata.player().position.x,
            cdata.player().position.y,
            1);
        return;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
    }
    flt();
    itemcreate(
        -1,
        choice(isetgiftmajor),
        cdata.player().position.x,
        cdata.player().position.y,
        1);
}



TurnResult try_to_open_locked_door()
{
    cell_featread(dx, dy);
    if (feat == tile_doorclosed4 && feat(2) > 0)
    {
        if (cc == 0)
        {
            int stat = unlock_box(feat(2));
            if (stat == 0)
            {
                screenupdate = -1;
                update_screen();
                await(g_config.animation_wait() * 5);
                return TurnResult::turn_end;
            }
            feat(2) = 0;
        }
        else
        {
            return TurnResult::turn_end;
        }
    }
    if (feat(2) > 0)
    {
        f = 0;
        if (rnd(feat(2) * 20 + 150) < sdata(158, cc) * 20 + 20)
        {
            f = 1;
        }
    }
    else
    {
        f = 1;
    }
    if (debug::voldemort)
    {
        f = 1;
    }
    if (f)
    {
        if (feat(2) > 0)
        {
            chara_gain_exp_lock_picking(cdata[cc]);
        }
        cell_featset(dx, dy, tile_dooropen, 20, 0, -1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.door.succeed", cdata[cc]));
            if (map_data.tileset == 8)
            {
                snd("core.door2");
            }
            else if (map_data.tileset == 9)
            {
                snd("core.card1");
            }
            else
            {
                snd("core.door1");
            }
        }
    }
    else
    {
        if (is_in_fov(cdata[cc]))
        {
            snd("core.locked1");
            txt(i18n::s.get("core.action.open.door.fail", cdata[cc]),
                Message::only_once{true});
        }
    }
    if (cc == 0)
    {
        await(g_config.animation_wait() * 5);
    }
    return TurnResult::turn_end;
}



void do_ranged_attack()
{
    int ammox = 0;
    int ammoy = 0;
    attackrange = 1;
    attacknum = 0;
    ele = 0;
    ammoproc = -1;
    ammoprocbk = -1;
    ammox = cdata[tc].position.x;
    ammoy = cdata[tc].position.y;
    attackitem = cw;
    if (ammo != -1)
    {
        if (inv[ammo].count != -1)
        {
            if (inv[ammo].enchantments[inv[ammo].count].power % 1000 <= 0)
            {
                txt(i18n::s.get("core.action.ranged.load_normal_ammo"));
                inv[ammo].count = -1;
            }
            else
            {
                ammoproc = inv[ammo].enchantments[inv[ammo].count].id % 10000;
                if (cc == 0)
                {
                    if (cdata.player().sp < 50)
                    {
                        if (cdata.player().sp < rnd(75))
                        {
                            txt(i18n::s.get("core.magic.common.too_exhausted"));
                            damage_sp(
                                cdata.player(),
                                encammoref(2, ammoproc) / 2 + 1);
                            ammoproc = -1;
                            return;
                        }
                    }
                    damage_sp(cdata.player(), rnd(encammoref(2, ammoproc) + 1));
                }
                --inv[ammo].enchantments[inv[ammo].count].power;
            }
        }
    }
    if (ammoproc == 0)
    {
        ammoprocbk = ammoproc;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            can_do_ranged_attack();
            ele = 0;
            extraattack = 0;
            do_physical_attack();
            if (cdata[tc].state() != Character::State::alive)
            {
                int stat = find_enemy_target();
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    tc = cdata[cc].enemy_id;
                }
            }
        }
    }
    else if (ammoproc == 5)
    {
        ammoprocbk = ammoproc;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            can_do_ranged_attack();
            ele = 0;
            build_target_list();
            if (listmax == 0)
            {
                break;
            }
            tc = list(0, rnd(listmax));
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                if (cdata[tc].relationship >= 0)
                {
                    if (cnt != 0)
                    {
                        cnt = cnt + (rnd(5) == 0) - 1;
                        continue;
                    }
                }
            }
            else if (cdata[tc].relationship == -3)
            {
                cnt = cnt + (rnd(5) == 0) - 1;
                continue;
            }
            extraattack = 0;
            do_physical_attack();
        }
    }
    else
    {
        extraattack = 0;
        do_physical_attack();
    }
    if (ammoproc == 1)
    {
        tlocx = ammox;
        tlocy = ammoy;
        efid = 460;
        efp = sdata(attackskill, cc) * 8 + 10;
        magic();
    }
    ammoproc = -1;
    ammoprocbk = -1;
}



void try_to_melee_attack()
{
    if (cc != 0)
    {
        if (cdata[tc].damage_reaction_info)
        {
            if (distance < 6)
            {
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y))
                {
                    int stat = can_do_ranged_attack();
                    if (stat == 1)
                    {
                        do_ranged_attack();
                    }
                }
            }
            p = cdata[tc].damage_reaction_info % 1000;
            if (p == 61)
            {
                if (cdata[cc].hp < cdata[cc].max_hp / 2)
                {
                    return;
                }
            }
        }
    }
    attacknum = 0;
    attackrange = 0;
    attackskill = 106;
    ammo = -1;
    ele = 0;
    if (cdata[cc].equipment_type & 1)
    {
        if (clamp(int(std::sqrt(sdata(168, cc)) - 3), 1, 5) +
                cdata[cc].has_power_bash() * 5 >
            rnd(100))
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.melee.shield_bash", cdata[cc], cdata[tc]));
            }
            damage_hp(cdata[tc], rnd(sdata(168, cc)) + 1, cc);
            status_ailment_damage(
                cdata[tc],
                StatusAilment::dimmed,
                50 + int(std::sqrt(sdata(168, cc))) * 15);
            cdata[tc].paralyzed += rnd(3);
        }
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            continue;
        }
        cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        attackitem = cw;
        if (inv[cw].dice_x > 0)
        {
            attackskill = inv[cw].skill;
            ++attacknum;
            extraattack = 0;
            do_physical_attack();
        }
    }
    if (attackskill == 106)
    {
        extraattack = 0;
        do_physical_attack();
    }
}



void do_physical_attack()
{
    int attackdmg;
    int expmodifer = 0;
label_22191_internal:
    if (cdata[cc].state() != Character::State::alive)
    {
        return;
    }
    if (cdata[tc].state() != Character::State::alive)
    {
        return;
    }
    if (cdata[cc].fear != 0)
    {
        txt(i18n::s.get("core.damage.is_frightened", cdata[cc]),
            Message::only_once{true});
        return;
    }
    if (cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .mef_index_plus_one != 0)
    {
        bool return_now = mef_proc_from_physical_attack(tc);
        if (return_now)
        {
            return;
        }
    }
    if (attackrange == 1)
    {
        RangedAttackAnimation(
            cdata[cc].position,
            cdata[tc].position,
            static_cast<RangedAttackAnimation::Type>(attackskill),
            the_item_db[itemid2int(inv[cw].id)]->subcategory,
            inv[cw].image % 1000,
            inv[cw].image / 1000)
            .play();
    }
    if (attacknum > 1 || cc != 0)
    {
    }
    expmodifer = 1 + cdata[tc].is_hung_on_sand_bag() * 15 + cdata[tc].splits() +
        cdata[tc].splits2() +
        (game_data.current_map == mdata_t::MapId::show_house);
    int hit = calcattackhit();
    i = 0;
    if (hit == 1)
    {
        if (critical)
        {
            if (cc == 0)
            {
                txt(i18n::s.get("core.damage.critical_hit"),
                    Message::color{ColorIndex::red});
            }
        }
        dmg = calcattackdmg(AttackDamageCalculationMode::actual_damage);
        attackdmg = dmg;
        if (cc == 0)
        {
            if (g_config.attack_animation())
            {
                int damage_percent = dmg * 100 / cdata[tc].max_hp;
                MeleeAttackAnimation(
                    cdata[tc].position,
                    cdata[tc].breaks_into_debris(),
                    attackskill,
                    damage_percent,
                    critical)
                    .play();
            }
        }
        if (attackskill != 106)
        {
            if (inv[cw].quality >= Quality::miracle)
            {
                if (inv[cw].quality == Quality::special)
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(itemid2int(inv[cw].id));
                }
                else if (inv[cw].subname >= 40000)
                {
                    randomize(inv[cw].subname - 40000);
                    s(1) = random_title(RandomTitleType::weapon);
                    randomize();
                }
                else
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(itemid2int(inv[cw].id));
                }
                if (inv[cw].quality == Quality::godly)
                {
                    s(1) = i18n::s.get("core.item.godly_paren", s(1));
                }
                else
                {
                    s(1) = i18n::s.get("core.item.miracle_paren", s(1));
                }
                if (is_in_fov(cdata[cc]))
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get(
                                "core.damage.wields_proudly", cdata[cc], s(1)),
                            Message::color{ColorIndex::cyan});
                    }
                }
                i = 1;
            }
        }
        if (attackskill == 106)
        {
            if (cdata[cc].element_of_unarmed_attack != 0)
            {
                ele = cdata[cc].element_of_unarmed_attack / 100000;
                elep = cdata[cc].element_of_unarmed_attack % 100000;
            }
        }
        if (is_in_fov(cdata[tc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (attackskill == 106)
            {
                if (tc >= 16)
                {
                    game_data.proc_damage_events_flag = 2;
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed_and",
                        cdata[cc],
                        _melee(0, cdata[cc].melee_attack_type),
                        cdata[tc]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed",
                        cdata[cc],
                        _melee(1, cdata[cc].melee_attack_type),
                        cdata[tc]));
                }
            }
            else
            {
                optional<std::string> weapon_name = none;
                if (attackskill == 111)
                {
                    // Special case for thrown weapons.
                    weapon_name = itemname(cw, 1, 1);
                }
                else
                {
                    weapon_name = i18n::s.get_enum_property_opt(
                        "core.damage.weapon", "name", attackskill);
                }
                if (weapon_name)
                {
                    if (tc >= 16)
                    {
                        game_data.proc_damage_events_flag = 2;
                        if (attackskill == 111)
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_throwing",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc],
                                *weapon_name));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_and",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc]));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.damage.weapon.attacks_with",
                            cdata[cc],
                            i18n::s.get_enum_property(
                                "core.damage.weapon", "verb", attackskill),
                            cdata[tc],
                            *weapon_name));
                    }
                }
            }
        }
        damage_hp(cdata[tc], dmg, cc, ele, elep);
        if (critical)
        {
            chara_gain_skill_exp(cdata[cc], 186, 60 / expmodifer, 2);
            critical = 0;
        }
        if (rtdmg > cdata[tc].max_hp / 20 || rtdmg > sdata(154, tc) ||
            rnd(5) == 0)
        {
            chara_gain_skill_exp(
                cdata[cc],
                attackskill,
                clamp(
                    (sdata(173, tc) * 2 - sdata(attackskill, cc) + 1), 5, 50) /
                    expmodifer,
                0,
                4);
            if (attackrange == 0)
            {
                chara_gain_skill_exp(cdata[cc], 152, 20 / expmodifer, 0, 4);
                if (cdata[cc].equipment_type & 2)
                {
                    chara_gain_skill_exp(cdata[cc], 167, 20 / expmodifer, 0, 4);
                }
                if (cdata[cc].equipment_type & 4)
                {
                    chara_gain_skill_exp(cdata[cc], 166, 20 / expmodifer, 0, 4);
                }
            }
            else if (attackskill == 111)
            {
                chara_gain_skill_exp(cdata[cc], 152, 10 / expmodifer, 0, 4);
            }
            else
            {
                chara_gain_skill_exp(cdata[cc], 189, 25 / expmodifer, 0, 4);
            }
            if (cc == 0)
            {
                if (game_data.mount != 0)
                {
                    chara_gain_skill_exp(
                        cdata.player(), 301, 30 / expmodifer, 0, 5);
                }
            }
            if (cdata[tc].state() == Character::State::alive)
            {
                chara_gain_skill_exp(
                    cdata[tc],
                    chara_armor_class(cdata[tc]),
                    clamp((250 * rtdmg / cdata[tc].max_hp + 1), 3, 100) /
                        expmodifer,
                    0,
                    5);
                if (cdata[tc].equipment_type & 1)
                {
                    chara_gain_skill_exp(cdata[tc], 168, 40 / expmodifer, 0, 4);
                }
            }
        }
        if (attackskill != 106)
        {
            proc_weapon_enchantments();
        }
        if (cdata[tc].cut_counterattack > 0)
        {
            if (attackrange == 0)
            {
                damage_hp(
                    cdata[cc],
                    attackdmg * cdata[tc].cut_counterattack / 100 + 1,
                    tc,
                    61,
                    100);
            }
        }
        if (cdata[tc].damage_reaction_info != 0)
        {
            p = cdata[tc].damage_reaction_info % 1000;
            ccbk = cc;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (attackrange == 0)
                {
                    if (p == 61)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.thorns",
                                    cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            cdata[cc],
                            clamp(attackdmg / 10, 1, cdata[tc].max_hp / 10),
                            tc,
                            p,
                            cdata[tc].damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 62)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.ether_"
                                    "thorns",
                                    cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            cdata[cc],
                            clamp(attackdmg / 10, 1, cdata[tc].max_hp / 10),
                            tc,
                            p,
                            cdata[tc].damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 63)
                    {
                        if (attackskill != 106)
                        {
                            if (rnd(5) == 0)
                            {
                                item_acid(cdata[cc], cw);
                            }
                        }
                    }
                }
                if (attackdmg > cdata[tc].max_hp / 10)
                {
                    cc = tc;
                    tlocx = cdata[cc].position.x;
                    tlocy = cdata[cc].position.y;
                    if (p == 63)
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.acids"),
                                Message::color{ColorIndex::purple});
                        }
                        efid = 455;
                        efp = cdata[tc].damage_reaction_info / 1000;
                        magic();
                        break;
                    }
                }
            }
            cc = ccbk;
        }
    }
    else
    {
        if (cc == 0)
        {
            snd("core.miss");
        }
        if (sdata(attackskill, cc) > sdata(173, tc) || rnd(5) == 0)
        {
            p = clamp(
                    (sdata(attackskill, cc) - sdata(173, tc) / 2 + 1), 1, 20) /
                expmodifer;
            chara_gain_skill_exp(cdata[tc], 173, p, 0, 4);
            chara_gain_skill_exp(cdata[tc], 187, p, 0, 4);
        }
    }
    if (hit == -1)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get("core.damage.miss.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.damage.miss.other", cdata[cc], cdata[tc]));
            }
            add_damage_popup(u8"miss", tc, {191, 191, 191});
        }
    }
    if (hit == -2)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get(
                    "core.damage.evade.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.damage.evade.other", cdata[cc], cdata[tc]));
            }
            add_damage_popup(u8"evade!!", tc, {191, 191, 191});
        }
    }
    if (tc == 0)
    {
        game_data.player_cellaccess_check_flag = 0;
    }
    rowact_check(tc);
    if (attackskill != 106)
    {
        if (cdata[tc].state() != Character::State::alive)
        {
            cw = attackitem;
            if (inv[cw].is_alive())
            {
                if (inv[cw].param2 < calcexpalive(inv[cw].param1))
                {
                    inv[cw].param2 += rnd(cdata[tc].level / inv[cw].param1 + 1);
                    if (inv[cw].param2 >= calcexpalive(inv[cw].param1))
                    {
                        snd("core.ding3");
                        txt(i18n::s.get(
                                "core.misc.living_weapon_taste_blood", inv[cw]),
                            Message::color{ColorIndex::green});
                    }
                }
            }
        }
    }
    ele = 0;
    if (extraattack == 0)
    {
        if (attackrange)
        {
            if (rnd(100) < cdata[cc].extra_shot)
            {
                ammoproc = -1;
                ++extraattack;
                goto label_22191_internal;
            }
        }
        else if (rnd(100) < cdata[cc].extra_attack)
        {
            ++extraattack;
            goto label_22191_internal;
        }
    }
}



void proc_weapon_enchantments()
{
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        cw = attackitem;
        if (inv[cw].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[cw].enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd(inv[cw].enchantments[cnt].power / 50 + 1) + 1;
            heal_sp(cdata[cc], p);
            damage_sp(cdata[tc], p / 2);
            continue;
        }
        if (enc == 38)
        {
            p = rnd(inv[cw].enchantments[cnt].power / 25 + 1) + 1;
            heal_mp(cdata[cc], p / 5);
            if (cdata[tc].state() != Character::State::alive)
            {
                continue;
            }
            damage_mp(cdata[tc], p);
            continue;
        }
        if (enc == 37)
        {
            if (rnd(66) == 0)
            {
                event_add(18, cc);
            }
            continue;
        }
        if (enc == 40)
        {
            if (game_data.left_turns_of_timestop == 0)
            {
                if (rnd(25) == 0)
                {
                    txt(i18n::s.get("core.action.time_stop.begins", cdata[cc]),
                        Message::color{ColorIndex::cyan});
                    game_data.left_turns_of_timestop =
                        inv[cw].enchantments[cnt].power / 100 + 1 + 1;
                }
                continue;
            }
        }
        if (enc == 57)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/dragon/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 61)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/god/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 58)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/undead/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        i = enc / 10000;
        if (i != 0)
        {
            enc = enc % 10000;
            if (i == 7)
            {
                if (orgdmg <= 1)
                {
                    continue;
                }
                ele = enc;
                if (cdata[tc].state() != Character::State::alive)
                {
                    continue;
                }
                game_data.proc_damage_events_flag = 1;
                damage_hp(
                    cdata[tc],
                    rnd(orgdmg * (100 + inv[cw].enchantments[cnt].power) /
                            1000 +
                        1) +
                        5,
                    cc,
                    ele,
                    inv[cw].enchantments[cnt].power / 2 + 100);
                continue;
            }
            if (i == 8)
            {
                if (cdata[tc].state() != Character::State::alive)
                {
                    continue;
                }
                if (enc >= 26)
                {
                    continue;
                }
                tcbk = tc;
                p = encprocref(1, enc);
                if (p == 3000 || p == 10000)
                {
                    tc = cc;
                }
                p = encprocref(5, enc);
                enc = encprocref(0, enc);
                tlocx = cdata[tc].position.x;
                tlocy = cdata[tc].position.y;
                if (rnd(100) < p)
                {
                    efid = enc;
                    efp = inv[cw].enchantments[cnt].power +
                        sdata(attackskill, cc) * 10;
                    magic();
                }
                tc = tcbk;
                continue;
            }
            continue;
        }
    }
    if (ammoproc == 4)
    {
        txt(i18n::s.get("core.action.time_stop.begins", cdata[cc]),
            Message::color{ColorIndex::cyan});
        game_data.left_turns_of_timestop = 4;
    }
    if (ammoproc == 3)
    {
        if (cdata[tc].state() == Character::State::alive)
        {
            game_data.proc_damage_events_flag = 1;
            damage_hp(
                cdata[tc],
                orgdmg * 2 / 3,
                cc,
                rnd(11) + 50,
                sdata(attackskill, cc) * 10 + 100);
        }
    }
}



void discover_trap()
{
    cell_featset(refx, refy, tile_trap, -1, -1);
}



void discover_hidden_path()
{
    cell_data.at(refx, refy).chip_id_actual = tile_tunnel;
    cell_featset(refx, refy, 0, 0);
}



void dipcursed(int item_index, int)
{
    if (the_item_db[itemid2int(inv[item_index].id)]->category == 57000)
    {
        if (inv[item_index].material == 35)
        {
            txt(i18n::s.get("core.action.dip.rots", inv[item_index]));
            inv[item_index].param3 = -1;
            inv[item_index].image = 336;
            cell_refresh(
                inv[item_index].position.x, inv[item_index].position.y);
            return;
        }
        else
        {
            txt(i18n::s.get("core.action.dip.unchanged", inv[item_index]));
            return;
        }
    }
    if (the_item_db[itemid2int(inv[item_index].id)]->category < 50000)
    {
        --inv[item_index].enhancement;
        txt(i18n::s.get("core.action.dip.rusts", inv[item_index]));
        if (inv_getowner(item_index) != -1)
        {
            chara_refresh(inv_getowner(item_index));
        }
        return;
    }
    txt(i18n::s.get("core.common.nothing_happens"));
}



int gain_skills_by_geen_engineering()
{
    if (cdata[tc].splits() || cdata[tc].splits2())
    {
        return 0;
    }
    randomize(charaid2int(cdata[tc].id));
    int dbmax = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        rtval = rnd(40) + 150;
        if (sdata(rtval, rc) == 0)
        {
            if (sdata(rtval, tc) > 0)
            {
                dblist(0, dbmax) = rtval;
                ++dbmax;
            }
        }
    }
    rtval(0) = dblist(0, 0);
    rtval(1) = -1;
    if (dbmax >= 2)
    {
        if (rnd(3) == 0)
        {
            for (int cnt = 1, cnt_end = cnt + (dbmax - 1); cnt < cnt_end; ++cnt)
            {
                if (dblist(0, cnt) != rtval)
                {
                    rtval(1) = dblist(0, cnt);
                    break;
                }
            }
        }
    }
    randomize();
    return dbmax;
}



int transplant_body_parts()
{
    int dbmax = 0;
    s(1) = chara_db_get_filter(cdata[tc].id);
    if (strutil::contains(s(1), u8"/man/"))
    {
        return -1;
    }
    if (cdata[tc].splits() || cdata[tc].splits2())
    {
        return -1;
    }
    rtval(1) = -1;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[rc].body_parts[i] == 0)
        {
            rtval(1) = i + 100;
        }
    }
    if (rtval(1) == -1)
    {
        return -1;
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        f = cdata[tc].body_parts[cnt] / 10000;
        if (f == 11 || f == 10 || f == 4)
        {
            continue;
        }
        if (f != 0)
        {
            dblist(0, dbmax) = f;
            ++dbmax;
        }
    }
    if (dbmax == 0)
    {
        return -1;
    }
    randomize(charaid2int(cdata[tc].id));
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        rtval = dblist(0, rnd(dbmax));
        f = 0;
        for (int i = 0; i < 30; ++i)
        {
            if (cdata[rc].body_parts[i] == 0)
            {
                continue;
            }
            if (cdata[rc].body_parts[i] / 10000 == rtval)
            {
                f = 1;
            }
        }
        if (f)
        {
            break;
        }
    }
    if (f == 0)
    {
        randomize();
        return rtval(1);
    }
    DIM3(dblist, 2, 800);
    for (int i = 0; i < 30; ++i)
    {
        ++dblist(0, cdata[tc].body_parts[i] / 10000);
    }
    for (int cnt = 0; cnt < 25; ++cnt)
    {
        rtval = rnd(15) + 1;
        f = 0;
        for (int i = 0; i < 30; ++i)
        {
            if (cdata[rc].body_parts[i] / 10000 == rtval)
            {
                ++f;
            }
        }
        if (f < dblist(0, rtval))
        {
            f = -1;
            break;
        }
    }
    randomize();
    if (f == -1)
    {
        return rtval(1);
    }
    else
    {
        return -1;
    }
}



TurnResult do_plant()
{
    screenupdate = -1;
    update_screen();
    if (map_data.type == mdata_t::MapType::world_map || map_is_town_or_guild())
    {
        txt(i18n::s.get("core.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y).feats != 0)
    {
        txt(i18n::s.get("core.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    int val0;
    if (chip_data.for_cell(cdata.player().position.x, cdata.player().position.y)
            .kind == 2)
    {
        val0 = 1;
    }
    else
    {
        val0 = 0;
    }
    feat(0) = tile_plant;
    feat(1) = 29;
    feat(2) = inv[ci].material;
    try_to_grow_plant(val0);
    if (val0)
    {
        s = i18n::s.get("core.action.plant.on_field", inv[ci]);
    }
    else
    {
        s = i18n::s.get("core.action.plant.execute", inv[ci]);
    }
    txt(s);
    snd("core.bush1");
    inv[ci].modify_number(-1);
    cell_featset(
        cdata[cc].position.x,
        cdata[cc].position.y,
        tile_plant,
        29,
        inv[ci].material,
        feat(3));
    chara_gain_skill_exp(cdata.player(), 180, 300);
    return TurnResult::turn_end;
}



void grow_plant(int val0)
{
    --feat(3);
    if (feat(3) % 50 == 0)
    {
        if (feat(3) >= 50)
        {
            feat = tile_plant + 3;
        }
        else
        {
            ++feat;
            try_to_grow_plant(val0);
        }
    }
}



void try_to_grow_plant(int val0)
{
    feat(3) = 4 + rnd(5);
    p = 10;
    if (feat(2) == 41)
    {
        p = 15;
    }
    if (feat(2) == 42)
    {
        p = 25;
    }
    if (feat(2) == 38)
    {
        p = 30;
    }
    if (feat(2) == 39)
    {
        p = 25;
    }
    if (feat(2) == 40)
    {
        p = 40;
    }
    if (val0 == 0)
    {
        p = p * 3 / 2;
    }
    if (feat == tile_plant)
    {
        if (game_data.weather < 3)
        {
            p = p * 2;
        }
    }
    if (sdata(180, 0) < rnd(p + 1) || rnd(20) == 0)
    {
        feat(3) += 50;
    }
}



void harvest_plant(int val)
{
    p = 15;
    if (feat(2) == 41)
    {
        p = 25;
    }
    if (feat(2) == 42)
    {
        p = 30;
    }
    if (feat(2) == 38)
    {
        p = 40;
    }
    if (feat(2) == 39)
    {
        p = 35;
    }
    if (val == 0)
    {
        p = p * 2;
    }
    if (game_data.weather < 3)
    {
        p = p * 4 / 3;
    }
    if (sdata(180, 0) < rnd(p + 1) || rnd(5) == 0 || feat(2) == 40)
    {
        cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats = 0;
        return;
    }
    feat = tile_plant;
    try_to_grow_plant();
    cell_featset(
        cdata[cc].position.x,
        cdata[cc].position.y,
        feat,
        feat(1),
        feat(2),
        feat(3));
    txt(i18n::s.get("core.action.plant.new_plant_grows"),
        Message::color{ColorIndex::green});
}



void create_harvested_item()
{
    chara_gain_skill_exp(cdata.player(), 180, 75);
    snd("core.bush1");
    flt(sdata(180, 0) / 2 + 15, Quality::good);
    dbid = 0;
    if (feat(2) == 39)
    {
        flttypemajor = choice(fsetplantunknown);
        if (rnd(100) == 0)
        {
            dbid = 559;
        }
    }
    if (feat(2) == 40 || (feat(2) == 39 && rnd(50) == 0))
    {
        flttypemajor = choice(fsetplantartifact);
        fixlv = Quality::miracle;
        save_set_autosave();
    }
    if (feat(2) == 36)
    {
        flttypeminor = 57003;
    }
    if (feat(2) == 37)
    {
        flttypeminor = 57004;
    }
    if (feat(2) == 38)
    {
        flttypeminor = 58005;
    }
    if (feat(2) == 41)
    {
        flttypeminor = 77001;
    }
    if (feat(2) == 42)
    {
        flttypemajor = 56000;
    }
    itemcreate(0, dbid, -1, -1, 0);
    txt(i18n::s.get("core.action.plant.harvest", inv[ci]));
    item_stack(0, ci, 1);
}



void initialize_economy()
{
    elona_vector1<int> bkdata;
    if (initeco)
    {
        game_data.politics_map_id = static_cast<int>(mdata_t::MapId::palmia);
    }
    bkdata(0) = game_data.current_map;
    bkdata(1) = game_data.current_dungeon_level;
    bkdata(2) = cdata.player().position.x;
    bkdata(3) = cdata.player().position.y;
    save_game(save_game_no_message);
    mode = 11;
    cdata.player().position.x = 0;
    cdata.player().position.y = 0;
    scx = cdata.player().position.x;
    scy = cdata.player().position.y;
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        if (area_data[cnt].id == mdata_t::MapId::none)
        {
            continue;
        }
        if (area_data[cnt].quest_town_id == 0)
        {
            continue;
        }
        game_data.current_map = area_data[cnt].id;
        game_data.current_dungeon_level = 1;
        if (game_data.current_map != bkdata(0) ||
            game_data.current_dungeon_level != bkdata(1))
        {
            initialize_map();
        }
        p = area_data[cnt].quest_town_id;
        if (initeco)
        {
            if (p == 1)
            {
                podata(100, p) = 1500 + rnd(200);
                podata(101, p) = 0;
                addbuilding(p, 1, 27, 22);
                addbuilding(p, 1, 28, 23);
            }
            if (p == 2)
            {
                podata(100, p) = 80 + rnd(20);
                podata(101, p) = 0;
                addbuilding(p, 2, 42, 31);
                addbuilding(p, 2, 43, 33);
            }
            if (p == 3)
            {
                podata(100, p) = 6500 + rnd(500);
                podata(101, p) = 0;
            }
            if (p == 4)
            {
                podata(100, p) = 1100 + rnd(150);
                podata(101, p) = 0;
                addbuilding(p, 5, 12, 34);
            }
            if (p == 5)
            {
                podata(100, p) = 3500 + rnd(300);
                podata(101, p) = 0;
                addbuilding(p, 6, 4, 16);
            }
            if (p == 6)
            {
                podata(100, p) = 800 + rnd(200);
                podata(101, p) = 0;
            }
            if (p == 7)
            {
                podata(100, p) = 2600 + rnd(300);
                podata(101, p) = 0;
                addbuilding(p, 3, 60, 33);
            }
            podata(200, p) = podata(100, p) * 5 + rnd(1000);
        }
        save_map_local_data();
    }
    game_data.current_map = bkdata(0);
    game_data.current_dungeon_level = bkdata(1);
    cdata.player().position.x = bkdata(2);
    cdata.player().position.y = bkdata(3);
    game_data.reset_world_map_in_diastrophism_flag = 1;
    mode = 3;
    mapsubroutine = 1;
    initialize_map();
    initeco = 0;
}



int new_ally_joins()
{
    f = chara_get_free_slot_ally();
    if (f == 0)
    {
        txt(i18n::s.get("core.action.ally_joins.party_full"));
        return -1;
    }
    oc = rc;
    chara_relocate(cdata[rc], f);
    cdata[rc].relationship = 10;
    cdata[rc].original_relationship = 10;
    cdata[rc].character_role = 0;
    cdata[rc].is_quest_target() = false;
    cdata[rc].is_not_attacked_by_enemy() = false;
    cdata[rc].is_hung_on_sand_bag() = false;
    cdata[rc].is_temporary() = false;
    cdata[rc].only_christmas() = false;
    snd("core.pray1");
    txt(i18n::s.get("core.action.ally_joins.success", cdata[rc]),
        Message::color{ColorIndex::orange});
    return 1;
}



void do_play_scene()
{
    int scidx = 0;
    int scidxtop = 0;
    int val0{};
    if (game_data.played_scene < sceneid)
    {
        game_data.played_scene = sceneid;
    }
    if (!g_config.story())
    {
        return;
    }
    scene_cut = 0;
    scenemode = 1;
    SDIM4(actor, 20, 3, 10);
    std::string file = u8"void"s;
    y1 = 60;
    y2 = windowh - 60;
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{
            (i18n::s.get_locale_dir("core") / "lazy" / "scene.hsp").native(),
            std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    s = u8"{"s + sceneid + u8"}"s;
    scidx = instr(buff, 0, s);
    if (scidx == -1)
    {
        scene_fade_to_black();
        return;
    }
    scidx += s(0).size();
label_2681:
    const auto input = stick(StickKey::escape);
    if (input == StickKey::escape)
    {
        scene_cut = 1;
    }
    if (scene_cut == 1)
    {
        scene_fade_to_black();
        return;
    }
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{
            (i18n::s.get_locale_dir("core") / "lazy" / "scene.hsp").native(),
            std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    cs = 0;
    key_list = key_enter;
    scidxtop = scidx;
    scidxtop = 0;
    val0 = 0;
label_2682_internal:
    p(1) = instr(buff, scidx, u8"{"s) + scidx;
    if (p(1) == -1)
    {
        scene_fade_to_black();
        return;
    }
    p(2) = instr(buff, scidx, u8"}"s) + scidx + 1;
    if (p(2) == -1)
    {
        scene_fade_to_black();
        return;
    }
    if (scidxtop != 0)
    {
        scidx = p(1);
        goto label_2684_internal;
        return;
    }
    s = strmid(buff, p(1), p(2) - p(1));
    scidx = p(2) + 1;
    if (s == u8"{txt}"s)
    {
        scidxtop = scidx;
        val0 = 0;
        goto label_2682_internal;
    }
    if (strutil::contains(s(0), u8"{chat_"))
    {
        rc = elona::stoi(strmid(s, 6, 1));
        scidxtop = scidx;
        val0 = 1;
        goto label_2682_internal;
    }
    if (s == u8"{fade}"s)
    {
        gsel(4);
        boxf(0, 0, windoww, windowh, {0, 0, 0, 255});
        gsel(0);
        animation_fade_in();
        goto label_2682_internal;
    }
    if (s == u8"{fadein}"s)
    {
        for (int cnt = 0; cnt < 25; ++cnt)
        {
            redraw();
            gmode(2, cnt * 15);
            gcopy(4, 0, 0, windoww, windowh, 0, 0);
            gmode(2);
            await(10);
        }
        goto label_2682_internal;
    }
    if (s == u8"{wait}"s)
    {
        scidxtop = scidx;
        val0 = 2;
        goto label_2682_internal;
    }
    if (s == u8"{end}"s)
    {
        await(1000);
        scene_fade_to_black();
        return;
    }
    p(3) = instr(buff, scidx, u8"\""s) + scidx + 1;
    p(4) = instr(buff, p(3), u8"\""s) + p(3);
    s(1) = strmid(buff, p(3), p(4) - p(3));
    scidx = p(4) + 1;
    if (s == u8"{pic}"s)
    {
        file = s(1);
        goto label_2682_internal;
    }
    if (s == u8"{mc}"s)
    {
        SharedId music_id(s(1));
        play_music(music_id);
        goto label_2682_internal;
    }
    if (s == u8"{se}"s)
    {
        SharedId sound_id(s(1));
        snd(sound_id);
        goto label_2682_internal;
    }
    if (strutil::contains(s(0), u8"{actor_"))
    {
        rc = elona::stoi(strmid(s, 7, 1));
        csvsort(s, s(1), 44);
        actor(0, rc) = s;
        actor(1, rc) = s(1);
    }
    goto label_2682_internal;
label_2684_internal:
    buff = strmid(buff, scidxtop, scidx - scidxtop);
    p = noteinfo();
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(s, p - cnt - 1);
        if (s == ""s)
        {
            notedel(p - cnt - 1);
        }
    }
    gmode(0);
    asset_load(file);
    draw(file, 0, y1, windoww, y2 - y1);
    gmode(2);
    boxf(0, 0, windoww, y1, {5, 5, 5});
    boxf(0, y2, windoww, windowh - y2, {5, 5, 5});
    if (val0 == 1)
    {
        gsel(0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);
        tc = 0;
        talk_to_npc();
        goto label_2681;
    }
    if (val0 == 2)
    {
        gsel(0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);
        redraw();
        await(1000);
        goto label_2681;
    }
    font(16 - en * 2);
    x = 44;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        y = y1 + 31 + (9 - noteinfo() / 2 + cnt) * 20;
        noteget(s, cnt);
        x = windoww / 2 - s(0).size() * 4;
        dx = 80 + strlen_u(s(0)) * 8;
        if (dx < 180)
        {
            dx = 0;
        }
        gmode(2, 95);
        draw_centered("scene_title", windoww / 2, y + 4, dx, 72);
    }
    x = 40;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        y = y1 + 28 + (9 - noteinfo() / 2 + cnt) * 20;
        noteget(s, cnt);
        x = windoww / 2 - strlen_u(s(0)) * 4;
        gmode(2);
        bmes(s, x, y, {240, 240, 240}, {10, 10, 10});
    }
    gsel(0);
    for (int cnt = 1; cnt < 16; ++cnt)
    {
        await(30);
        const auto input = stick(StickKey::escape);
        if (input == StickKey::escape)
        {
            scene_cut = 1;
        }
        gmode(2, cnt * 16);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        redraw();
    }
    gmode(2);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    anime_halt(windoww - 120, windowh - 60);
    boxf(0, 0, windoww, y1, {5, 5, 5});
    boxf(0, y2, windoww, windowh - y2, {5, 5, 5});
    goto label_2681;
}



void scene_fade_to_black()
{
    gsel(4);
    boxf(0, 0, windoww, windowh, {0, 0, 0, 255});
    gsel(0);
    animation_fade_in();
    scenemode = 0;
}



void weather_changes()
{
    if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
    {
        update_museum();
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        calc_home_rank();
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        game_data.pc_x_in_world_map = cdata.player().position.x;
        game_data.pc_y_in_world_map = cdata.player().position.y;
    }
    --game_data.hours_until_weather_changes;
    weather_changes_by_location();
    if (game_data.hours_until_weather_changes < 0)
    {
        game_data.hours_until_weather_changes = rnd(22) + 2;
        p = game_data.weather;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (game_data.date.month % 3 == 0)
            {
                if (game_data.date.day >= 1 && game_data.date.day <= 10)
                {
                    if (game_data.last_etherwind_month != game_data.date.month)
                    {
                        if (rnd(15) < game_data.date.day + 5)
                        {
                            game_data.weather = 1;
                            txt(i18n::s.get("core.action.weather.ether_"
                                            "wind.starts"),
                                Message::color{ColorIndex::red});
                            game_data.last_etherwind_month =
                                game_data.date.month;
                            game_data.hours_until_weather_changes =
                                rnd(24) + 24;
                            break;
                        }
                    }
                }
            }
            if (p == 0)
            {
                weatherbk = 0;
                if (trait(209) != 0)
                {
                    if (rnd(4) == 0)
                    {
                        game_data.weather = 3;
                        txt(i18n::s.get("core.action.weather.rain.draw_cloud"));
                        break;
                    }
                }
                if (game_data.pc_x_in_world_map > 65 ||
                    game_data.pc_y_in_world_map < 10)
                {
                    if (rnd(2) == 0)
                    {
                        game_data.weather = 2;
                        txt(i18n::s.get("core.action.weather.snow.starts"));
                        break;
                    }
                }
                else
                {
                    if (rnd(10) == 0)
                    {
                        game_data.weather = 3;
                        txt(i18n::s.get("core.action.weather.rain.starts"));
                        break;
                    }
                    if (rnd(40) == 0)
                    {
                        game_data.weather = 4;
                        txt(i18n::s.get(
                            "core.action.weather.rain.starts_heavy"));
                        break;
                    }
                    if (rnd(60) == 0)
                    {
                        game_data.weather = 2;
                        txt(i18n::s.get("core.action.weather.snow.starts"));
                        break;
                    }
                }
            }
            if (p == 3)
            {
                if (rnd(4) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get("core.action.weather.rain.stops"));
                    break;
                }
                if (rnd(15) == 0)
                {
                    game_data.weather = 4;
                    txt(i18n::s.get(
                        "core.action.weather.rain.becomes_heavier"));
                    break;
                }
            }
            if (p == 4)
            {
                if (rnd(3) == 0)
                {
                    game_data.weather = 3;
                    txt(i18n::s.get(
                        "core.action.weather.rain.becomes_lighter"));
                    break;
                }
            }
            if (p == 1)
            {
                if (rnd(2) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get("core.action.weather.ether_wind.stops"));
                    break;
                }
            }
            if (p == 2)
            {
                if (rnd(3) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get("core.action.weather.snow.stops"));
                    break;
                }
            }
        }
        if (game_data.weather == 4)
        {
            maybe_show_ex_help(11);
        }
        if (game_data.weather == 2)
        {
            maybe_show_ex_help(12);
        }
        if (game_data.weather == 1)
        {
            maybe_show_ex_help(13);
        }
        if (p != game_data.weather)
        {
            sound_play_environmental();
        }
    }
    draw_prepare_map_chips();
    adventurer_update();
    foods_get_rotten();
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (rnd(3) == 0)
        {
            ++game_data.continuous_active_hours;
        }
        if (rnd(15) == 0)
        {
            if (mode == 0)
            {
                txt(i18n::s.get("core.action.move.global.nap"));
                game_data.continuous_active_hours -= 3;
                if (game_data.continuous_active_hours < 0)
                {
                    game_data.continuous_active_hours = 0;
                }
            }
        }
    }
    else if (game_data.current_map != mdata_t::MapId::shelter_)
    {
        ++game_data.continuous_active_hours;
    }
    if (game_data.date.hour == 6)
    {
        txt(i18n::s.get("core.action.day_breaks"),
            Message::color{ColorIndex::orange});
    }
    if (game_data.continuous_active_hours >= 15)
    {
        maybe_show_ex_help(9);
    }
    if (cdata.player().nutrition < 5000)
    {
        maybe_show_ex_help(10);
    }
    if (game_data.date.hour >= 24)
    {
        if (game_data.number_of_waiting_guests < 3)
        {
            if (rnd(8 + game_data.number_of_waiting_guests * 5) == 0)
            {
                ++game_data.number_of_waiting_guests;
            }
        }
        txt(i18n::s.get("core.action.new_day"),
            Message::color{ColorIndex::orange});
        update_shop_and_report();
        for (int rank_id = 0; rank_id < 9; ++rank_id)
        {
            if (game_data.ranks.at(rank_id) >= 10000)
            {
                game_data.ranks.at(rank_id) = 10000;
                continue;
            }
            if (rank_id == 3 || rank_id == 4 || rank_id == 5 || rank_id == 8)
            {
                continue;
            }
            --game_data.rank_deadlines.at(rank_id);
            if (game_data.rank_deadlines.at(rank_id) <= 0)
            {
                modrank(rank_id, (game_data.ranks.at(rank_id) / 12 + 100) * -1);
                game_data.rank_deadlines.at(rank_id) = ranknorma(rank_id);
            }
        }
        snd("core.night");
        event_add(10);
        game_data.play_days += game_data.date.hour / 24;
        game_data.date.day += game_data.date.hour / 24;
        game_data.date.hour = game_data.date.hour % 24;
        if (game_data.date.day >= 31)
        {
            ++game_data.date.month;
            game_data.date.day = game_data.date.day - 30;
            if (game_data.date.month % 2 == 0)
            {
                ++game_data.holy_well_count;
            }
        }
        if (game_data.date.month >= 13)
        {
            ++game_data.date.year;
            game_data.date.month = 1;
            game_data.last_month_when_trainer_visited = 0;
            game_data.wish_count = clamp(game_data.wish_count - 1, 0, 10);
            game_data.lost_wallet_count =
                clamp(game_data.lost_wallet_count - 1, 0, 999999);
        }
        if (game_data.date.day == 1 || game_data.date.day == 15)
        {
            supply_income();
        }
        if (game_data.quest_flags.pael_and_her_mom == 1 ||
            game_data.quest_flags.pael_and_her_mom == 3 ||
            game_data.quest_flags.pael_and_her_mom == 5 ||
            game_data.quest_flags.pael_and_her_mom == 7 ||
            game_data.quest_flags.pael_and_her_mom == 9)
        {
            if (area_data[game_data.current_map].id != mdata_t::MapId::noyel)
            {
                if (rnd(20) == 0)
                {
                    ++game_data.quest_flags.pael_and_her_mom;
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (mode == 0)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (rnd(40) == 0)
            {
                --cdata.player().piety_point;
            }
            cdata.player().praying_point += 4;
        }
        else
        {
            if (rnd(5) == 0)
            {
                --cdata.player().piety_point;
            }
            cdata.player().praying_point += 32;
        }
    }
    if (cdata.player().piety_point < 0)
    {
        cdata.player().piety_point = 0;
    }
    if (cdata.player().activity.turn != 0)
    {
        if (cdata.player().activity.type != Activity::Type::travel)
        {
            update_screen();
        }
    }
    if (!map_prevents_random_events())
    {
        proc_random_event();
    }
}



optional<TurnResult> check_angband()
{
    if (game_data.angband_flag == -1 ||
        map_data.type == mdata_t::MapType::world_map)
        return none;

    switch (game_data.angband_flag)
    {
    case 0:
        if (key == u8"Q"s)
        {
            txt(i18n::s.get("core.action.angband.q"));
            ++game_data.angband_flag;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        break;
    case 1:
        if (key == u8"y"s)
        {
            txt(i18n::s.get("core.action.angband.y"));
            ++game_data.angband_flag;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        break;
    case 2:
        if (key == u8"@"s)
        {
            txt(i18n::s.get("core.action.angband.at"));
            for (int i = 0; i < 10; ++i)
            {
                flt();
                chara_create(
                    -1,
                    37,
                    cdata.player().position.x,
                    cdata.player().position.y);
            }
            game_data.angband_flag = -1;
            update_screen();
            return TurnResult::turn_end;
        }
        break;
    default: break;
    }

    game_data.angband_flag = 0;
    return none;
}



std::string ask_win_comment()
{
    std::vector<std::string> choices;
    {
        const auto choices_ = i18n::s.get_list("core.scenario.win_words");
        if (choices_.empty())
        {
            choices.push_back("I can't sleep tonight.");
        }
        else
        {
            choices = sampled(choices_, std::min(choices_.size(), size_t(3)));
        }
    }

    Prompt prompt(Prompt::Type::cannot_cancel);
    for (const auto& choice : choices)
    {
        prompt.append(choice);
    }
    const auto selected_index = prompt.query(promptx, prompty, 310);

    return choices[selected_index];
}



void conquer_lesimas()
{
    snd("core.complete1");
    stop_music();
    txt(i18n::s.get("core.win.conquer_lesimas"));
    update_screen();

    const auto win_comment = ask_win_comment();

    mode = 7;
    screenupdate = -1;
    update_screen();
    if (jp)
    {
        Message::instance().clear();
        txt(u8"「お前がここに辿り着くことは」台座から、何かの声が聞こえる。"s);
        flt();
        chara_create(
            -1, 23, cdata.player().position.x, cdata.player().position.y);
        play_music("core.mcChaos");
        msg_halt();
        Message::instance().clear();
        txt(u8"「決まっていたことなのだ…遅かれ早かれな」"s);
        txt(u8"部屋の空気が突然緊張し、あなたの前に端麗な青年が現れた。"s);
        txt(u8"「我々からすれば、複雑性の一面に過ぎないが、人間は運命とでも呼ぶのだろう？」"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"あなたは懸命に脚の震えを抑えようとしたが、難しかった。"s);
        txt(u8"華奢に見える幼顔の男の影は、人のものではない。"s);
        txt(u8"あどけない瞳の奥に、あなたは底知れない力と闇を感じた。"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"「ネフィアの永遠の盟約に基づき」青年は台座の横の死体を指し、皮肉な微笑を送った。"s);
        txt(u8"「この哀れな老人が守っていたものは、今からお前のものだ」"s);
        msg_halt();
        Message::instance().clear();
        txt(u8"あなたは、台座の上に置かれている絢爛な装飾の本を、いぶかしげに眺めた。"s);
        msg_halt();
        tc = chara_find("core.orphe");
        talk_to_npc();
        Message::instance().clear();
        txt(u8"青年は悪戯っぽくニヤリと笑い、壁に寄りかかった。"s);
        msg_halt();
        Message::instance().clear();
        chara_vanquish(chara_find("core.orphe"));
        screenupdate = -1;
        update_screen();
        txt(u8"…どれくらい時間がたっただろう。氷の瞳の男は、いつの間にか姿を消していた。あなたは不安を振り払い、ゆっくりと本に手を伸ばした…"s);
        msg_halt();
    }
    mode = 0;
    play_music("core.mcMarch2");
    ui_win_screen_fade();
    asset_load("void");
    draw_region("void", 0, 0, 0, 0, 640, 480, windoww, windowh);
    gsel(0);
    animation_fade_in();
    draw_region("void", 0, 0, 0, 0, windoww, windowh);
    asset_load("g1");
    gsel(0);
    ui_draw_caption(
        i18n::s.get("core.win.you_acquired_codex", cdatan(1, 0), cdatan(0, 0)));
    windowshadow = 1;
    ww = 680;
    wh = 488;
    pagesize = 0;
    ui_display_window(
        i18n::s.get("core.win.window.title"),
        ""s + strhint3,
        windoww / 2 - ww / 2,
        windowh / 2 - wh / 2,
        ww,
        wh);
    gmode(2, 250);
    draw_centered("g1", wx + ww - 120, wy + wh / 2, ww / 3 - 20, wh - 140);
    gmode(2);
    display_topic(i18n::s.get("core.win.window.caption"), wx + 28, wy + 40);
    font(14 - en * 2);
    mes(wx + 40,
        wy + 76,
        i18n::s.get("core.win.window.arrived_at_tyris", 517, 8, 12));
    mes(wx + 40,
        wy + 116,
        i18n::s.get(
            "core.win.window.have_killed",
            game_data.deepest_dungeon_level,
            game_data.kill_count));
    mes(wx + 40, wy + 146, i18n::s.get("core.win.window.score", calcscore()));
    mes(wx + 40,
        wy + 186,
        i18n::s.get(
            "core.win.window.lesimas",
            game_data.date.year,
            game_data.date.month,
            game_data.date.day));
    mes(wx + 40, wy + 206, i18n::s.get("core.win.window.comment", win_comment));
    mes(wx + 40,
        wy + 246,
        i18n::s.get("core.win.window.your_journey_continues"));
    redraw();
    key_list = key_enter;
    keyrange = 0;

    while (1)
    {
        auto action = cursor_check_ex();
        if (action == "cancel")
        {
            play_the_last_scene_again();
            return;
        }
    }
}



void play_the_last_scene_again()
{
    update_entire_screen();
    txt(i18n::s.get("core.win.watch_event_again"));
    if (yes_no())
    {
        conquer_lesimas();
        return;
    }
    game_data.quest_flags.main_quest = 180;
    update_screen();
}



TurnResult pc_died()
{
    cc = 0;
    snd("core.dead1");
    screenupdate = -1;
    update_screen();
    if (game_data.executing_immediate_quest_type)
    {
        return quest_pc_died_during_immediate_quest();
    }
    txt(i18n::s.get("core.misc.death.good_bye"));
    txt(i18n::s.get("core.misc.death.you_leave_dying_message"));
    inputlog = "";
    input_text_dialog((windoww - 310) / 2 + inf_screenx, winposy(90), 16);
    std::string last_words;
    if (inputlog == ""s)
    {
        last_words = i18n::s.get("core.system.last_words");
    }
    else
    {
        last_words = i18n::s.get("core.misc.death.dying_message", inputlog(0));
    }
    buff = "";
    notesel(buff);
    const auto bone_filepath = filesystem::dirs::save() / u8"bone.txt";
    if (fs::exists(bone_filepath))
    {
        std::ifstream in{bone_filepath.native(), std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    s = cdatan(1, cc) + u8" "s + cdatan(0, cc) + i18n::space_if_needed() +
        last_words;
    lenfix(s, 60);
    s += i18n::s.get(
        "core.misc.death.date",
        game_data.date.year,
        game_data.date.month,
        game_data.date.day);
    noteadd(""s, 0);
    noteadd(s, 1);
    s = i18n::s.get("core.misc.death.you_died", ndeathcause, mdatan(0));
    noteadd(s, 2);
    s = ""s + calcscore() + u8","s + cdata[cc].image;
    noteadd(s, 3);
    if (noteinfo() >= 320)
        for (int cnt = 320, cnt_end = cnt + (noteinfo() - 320); cnt < cnt_end;
             ++cnt)
        {
            notedel(320);
        }
    page = 0;
    while (1)
    {
        p(1) = 0;
        for (int cnt = 0; cnt < 79; ++cnt)
        {
            p = cnt * 4;
            noteget(s(10), p + 3);
            csvsort(s, s(10), 44);
            p(2) = elona::stoi(s(0));
            noteget(s(10), p + 7);
            csvsort(s, s(10), 44);
            p(3) = elona::stoi(s(0));
            if (p(3) > p(2))
            {
                if (cnt == page)
                {
                    page = cnt + 1;
                }
                else if (cnt + 1 == page)
                {
                    page = cnt;
                }
                for (int cnt = 1; cnt < 4; ++cnt)
                {
                    noteget(s, p + cnt);
                    noteget(s(1), p + 4 + cnt);
                    noteadd(s, p + 4 + cnt, 1);
                    noteadd(s(1), p + cnt, 1);
                }
                p(1) = 1;
            }
        }
        if (p(1) == 0)
        {
            break;
        }
    }
    for (int cnt = 0, cnt_end = (noteinfo() / 4); cnt < cnt_end; ++cnt)
    {
        noteadd(i18n::s.get("core.misc.death.rank", cnt + 1), cnt * 4, 1);
    }
    {
        std::ofstream out{bone_filepath.native(), std::ios::binary};
        out << buff(0) << std::endl;
    }
    asset_load("void");
    gsel(0);
    show_game_score_ranking();
    ui_draw_caption(i18n::s.get("core.misc.death.you_are_about_to_be_buried"));

    Prompt prompt("core.misc.death");
    prompt.append("crawl_up", snail::Key::key_a);
    prompt.append("lie_on_your_back", snail::Key::key_b);
    rtval = prompt.query(promptx, 100, 240);

    if (rtval == 1)
    {
        show_game_score_ranking();
        ui_draw_caption(i18n::s.get("core.misc.death.you_have_been_buried"));
        redraw();
        wait_key_pressed();
        return TurnResult::finish_elona;
    }
    net_send_death(ndeathcause, mdatan(0), last_words);
    screenupdate = -1;
    update_entire_screen();
    levelexitby = 3;
    return TurnResult::exit_map;
}



void show_game_score_ranking()
{
    notesel(buff);
    gmode(0);
    draw("void", 0, 0, windoww, windowh);
    gmode(2);
    x = 135;
    y = 134;
    font(14 - en * 2);
    p = page - 4;
    if (p >= 80)
    {
        p = 72;
    }
    if (p < 0)
    {
        p = 0;
    }

    for (int cnt = p, cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
    {
        p = cnt * 4;
        y += 46;
        if (cnt == page)
        {
            s = u8"New!"s;
        }
        else
        {
            s = " "s + i18n::s.get("core.misc.score.rank", cnt + 1);
        }
        mes(x - 80, y + 10, s, {10, 10, 10});
        bool no_entry = false;
        if (p >= noteinfo())
        {
            no_entry = true;
        }
        else
        {
            noteget(s, p + 1);
            if (s(0).empty())
            {
                no_entry = true;
            }
        }
        if (no_entry)
        {
            mes(x, y, u8"no entry", {10, 10, 10});
            continue;
        }
        mes(x, y, s, {10, 10, 10});
        noteget(s, p + 2);
        mes(x, y + 20, s, {10, 10, 10});
        noteget(s(10), p + 3);
        csvsort(s, s(10), 44);
        mes(x + 480,
            y + 20,
            i18n::s.get("core.misc.score.score", s(0)),
            {10, 10, 10});
        p = elona::stoi(s(1)) % 1000;

        draw_chara_scale_height(elona::stoi(s(1)), x - 22, y + 12);
    }
}


} // namespace elona
