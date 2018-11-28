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
#include "card.hpp"
#include "casino.hpp"
#include "casino_card.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "command.hpp"
#include "config/config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "event.hpp"
#include "filesystem.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "log.hpp"
#include "lua_env/interface.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "main.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "network.hpp"
#include "putit.hpp"
#include "quest.hpp"
#include "race.hpp"
#include "random.hpp"
#include "random_event.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "turn_sequence.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "version.hpp"
#include "wish.hpp"

using namespace elona;


namespace
{

std::string atbuff;



std::string lang(const std::string& a, const std::string& b)
{
    return jp ? a : b;
}



void select_house_board_tile()
{
    snd("core.pop2");

    while (1)
    {
        gmode(0);
        p = 0;
        for (int y = 0; y < 20; ++y)
        {
            for (int x = 0; x < 33; ++x)
            {
                if (p < listmax)
                {
                    pos(x * 24, y * 24);
                    gcopy(
                        2,
                        list(0, p) % 33 * 48,
                        list(0, p) / 33 * 48,
                        48,
                        48,
                        24,
                        24);
                    if (chipm(7, list(0, p)) & 4)
                    {
                        boxl(x * 24, y * 24, 24, 24, {240, 230, 220});
                    }
                }
                ++p;
            }
        }

        gmode(2);
        redraw();
        await(Config::instance().wait1);
        const auto input = stick();
        if (input == StickKey::mouse_left)
        {
            p = mousex / 24 + mousey / 24 * 33;
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
        if (game_data.pc_x_in_world_map < 65
            && game_data.pc_y_in_world_map > 10)
        {
            game_data.weather = 3;
            sound_play_environmental();
            game_data.hours_until_weather_changes += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.locale.action.weather.changes"));
            }
            else
            {
                Message::instance().msg_append(
                    i18n::s.get("core.locale.action.weather.changes"));
            }
        }
    }
    if (game_data.weather == 4 || game_data.weather == 3)
    {
        if (game_data.pc_x_in_world_map > 65
            || game_data.pc_y_in_world_map < 10)
        {
            game_data.weather = 2;
            sound_play_environmental();
            game_data.hours_until_weather_changes += 3;
            if (output_immediately)
            {
                txt(i18n::s.get("core.locale.action.weather.changes"));
            }
            else
            {
                Message::instance().msg_append(
                    i18n::s.get("core.locale.action.weather.changes"));
            }
        }
    }
}

} // namespace



namespace elona
{


int prm_518;

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
    if (jp)
    {
        rankn(0, 0) = u8"アリーナのチャンピオン"s;
        rankn(1, 0) = u8"アリーナの超エリート闘士"s;
        rankn(2, 0) = u8"アリーナのスター闘士"s;
        rankn(3, 0) = u8"アリーナのエリート闘士"s;
        rankn(4, 0) = u8"アリーナの熟練闘士"s;
        rankn(5, 0) = u8"アリーナの中堅闘士"s;
        rankn(6, 0) = u8"アリーナの期待の星"s;
        rankn(7, 0) = u8"アリーナのダークホース"s;
        rankn(8, 0) = u8"アリーナの下級闘士"s;
        rankn(9, 0) = u8"アリーナの無名の闘士"s;
        rankn(10, 0) = u8"アリーナ"s;
        rankn(0, 1) = u8"全てのペットの王"s;
        rankn(1, 1) = u8"超エリートペット使い"s;
        rankn(2, 1) = u8"ペットの王子"s;
        rankn(3, 1) = u8"ペットの憧れの的"s;
        rankn(4, 1) = u8"ペット使いのエリート"s;
        rankn(5, 1) = u8"名の知れたペット使い"s;
        rankn(6, 1) = u8"ペットの母"s;
        rankn(7, 1) = u8"なかなかのペット使い"s;
        rankn(8, 1) = u8"駆け出しのペット使い"s;
        rankn(9, 1) = u8"無名のペット使い"s;
        rankn(10, 1) = u8"ペットアリーナ"s;
        rankn(0, 2) = u8"ネフィアを統べる者"s;
        rankn(1, 2) = u8"迷宮の覇者"s;
        rankn(2, 2) = u8"ダンジョンの主"s;
        rankn(3, 2) = u8"高名な探検者"s;
        rankn(4, 2) = u8"子供達の憧れの的"s;
        rankn(5, 2) = u8"ダンジョン案内人"s;
        rankn(6, 2) = u8"名の知れた遺跡荒らし"s;
        rankn(7, 2) = u8"探検者"s;
        rankn(8, 2) = u8"ちんけな遺跡荒らし"s;
        rankn(9, 2) = u8"観光客"s;
        rankn(10, 2) = u8"クローラー"s;
        rankn(0, 3) = u8"ティリス最大の博物館"s;
        rankn(1, 3) = u8"超有名な博物館"s;
        rankn(2, 3) = u8"大人気の博物館"s;
        rankn(3, 3) = u8"有名な博物館"s;
        rankn(4, 3) = u8"来客の絶えない博物館"s;
        rankn(5, 3) = u8"ちょっと人気のある博物館"s;
        rankn(6, 3) = u8"名の知れた博物館"s;
        rankn(7, 3) = u8"まあまあの博物館"s;
        rankn(8, 3) = u8"来客の少ない博物館"s;
        rankn(9, 3) = u8"無名の博物館"s;
        rankn(10, 3) = u8"博物館"s;
        rankn(0, 4) = u8"ティリスの楽園"s;
        rankn(1, 4) = u8"超セレブな家"s;
        rankn(2, 4) = u8"ティリス有数の家"s;
        rankn(3, 4) = u8"とても住みたくなる家"s;
        rankn(4, 4) = u8"主婦の憧れの家"s;
        rankn(5, 4) = u8"ちょっと人目をひく家"s;
        rankn(6, 4) = u8"まあまあの家"s;
        rankn(7, 4) = u8"少しみすぼらしい家"s;
        rankn(8, 4) = u8"貧困にあえぐ家"s;
        rankn(9, 4) = u8"乞食の家"s;
        rankn(10, 4) = u8"ホーム"s;
        rankn(0, 5) = u8"ティリス最大の店"s;
        rankn(1, 5) = u8"王様が来る店"s;
        rankn(2, 5) = u8"大繁盛している店"s;
        rankn(3, 5) = u8"セレブが来る店"s;
        rankn(4, 5) = u8"来客の絶えない店"s;
        rankn(5, 5) = u8"マダムの来る店"s;
        rankn(6, 5) = u8"リピーターのいる店"s;
        rankn(7, 5) = u8"人が増えてきた売店"s;
        rankn(8, 5) = u8"ほとんど売れない売店"s;
        rankn(9, 5) = u8"無名の売店"s;
        rankn(10, 5) = u8"店"s;
        rankn(0, 6) = u8"ボス"s;
        rankn(1, 6) = u8"王様のアドバイザー"s;
        rankn(2, 6) = u8"エリートコンサルター"s;
        rankn(3, 6) = u8"ご意見番"s;
        rankn(4, 6) = u8"有権者の鑑"s;
        rankn(5, 6) = u8"マダム好みの有権者"s;
        rankn(6, 6) = u8"名の知れた有権者"s;
        rankn(7, 6) = u8"普通の有権者"s;
        rankn(8, 6) = u8"無関心な有権者"s;
        rankn(9, 6) = u8"ぎりぎり有権者"s;
        rankn(10, 6) = u8"コミュニティ"s;
        rankn(0, 8) = u8"グランドマスター"s;
        rankn(1, 8) = u8"マスター"s;
        rankn(2, 8) = u8"ギルドの重役"s;
        rankn(3, 8) = u8"ギルドの重役候補"s;
        rankn(4, 8) = u8"アダプト"s;
        rankn(5, 8) = u8"エキスパート"s;
        rankn(6, 8) = u8"ジャーニーマン"s;
        rankn(7, 8) = u8"ギルドの正式メンバー"s;
        rankn(8, 8) = u8"ギルドのメンバー候補"s;
        rankn(9, 8) = u8"見習い"s;
        rankn(10, 8) = u8"ギルド"s;
    }
    else
    {
        rankn(0, 0) = u8"Arena champion"s;
        rankn(1, 0) = u8"Super elite gladiator"s;
        rankn(2, 0) = u8"Star gladiator"s;
        rankn(3, 0) = u8"Elite gladiator"s;
        rankn(4, 0) = u8"Veteran gladiator"s;
        rankn(5, 0) = u8"Popular gladiator"s;
        rankn(6, 0) = u8"New hope"s;
        rankn(7, 0) = u8"Darkhorse"s;
        rankn(8, 0) = u8"Low class fighter"s;
        rankn(9, 0) = u8"Unknown fighter"s;
        rankn(10, 0) = u8"Arena"s;
        rankn(0, 1) = u8"King of tamer"s;
        rankn(1, 1) = u8"Super elite tamer"s;
        rankn(2, 1) = u8"Prince of animals"s;
        rankn(3, 1) = u8"Chief of animals"s;
        rankn(4, 1) = u8"Elite tamer"s;
        rankn(5, 1) = u8"Notorious tamer"s;
        rankn(6, 1) = u8"New hope"s;
        rankn(7, 1) = u8"Average tamer"s;
        rankn(8, 1) = u8"Petty tamer"s;
        rankn(9, 1) = u8"Unknown tamer"s;
        rankn(10, 1) = u8"Pet Arena"s;
        rankn(0, 2) = u8"King of Nefia"s;
        rankn(1, 2) = u8"Champion of labyrinth"s;
        rankn(2, 2) = u8"Dungeon master"s;
        rankn(3, 2) = u8"Famous adventurer"s;
        rankn(4, 2) = u8"Children's star"s;
        rankn(5, 2) = u8"Guide of Nefia"s;
        rankn(6, 2) = u8"Notorious tomb robber"s;
        rankn(7, 2) = u8"Tomb robber"s;
        rankn(8, 2) = u8"Famous tourist"s;
        rankn(9, 2) = u8"Tourist"s;
        rankn(10, 2) = u8"Crawler"s;
        rankn(0, 3) = u8"Tyris' greatest museum"s;
        rankn(1, 3) = u8"Royal museum"s;
        rankn(2, 3) = u8"Great museum"s;
        rankn(3, 3) = u8"Top museum"s;
        rankn(4, 3) = u8"Great museum"s;
        rankn(5, 3) = u8"Good museum"s;
        rankn(6, 3) = u8"Average museum"s;
        rankn(7, 3) = u8"Small museum"s;
        rankn(8, 3) = u8"Unknown museum"s;
        rankn(9, 3) = u8"Unknown Ruin"s;
        rankn(10, 3) = u8"Museum"s;
        rankn(0, 4) = u8"Heaven of Tyris"s;
        rankn(1, 4) = u8"Royal mansion"s;
        rankn(2, 4) = u8"Celebrity mansion"s;
        rankn(3, 4) = u8"Dream mansion"s;
        rankn(4, 4) = u8"Cozy mansion"s;
        rankn(5, 4) = u8"Attractive house"s;
        rankn(6, 4) = u8"Average house"s;
        rankn(7, 4) = u8"Poor house"s;
        rankn(8, 4) = u8"Peasant's shack"s;
        rankn(9, 4) = u8"Beggar's shack"s;
        rankn(10, 4) = u8"Home"s;
        rankn(0, 5) = u8"Tyris' greatest mall"s;
        rankn(1, 5) = u8"Royal mall"s;
        rankn(2, 5) = u8"Prosperous mall"s;
        rankn(3, 5) = u8"Celebrity shop"s;
        rankn(4, 5) = u8"Prosperous shop"s;
        rankn(5, 5) = u8"Popular shop"s;
        rankn(6, 5) = u8"Average shop"s;
        rankn(7, 5) = u8"Small shop"s;
        rankn(8, 5) = u8"Souvenir shop "s;
        rankn(9, 5) = u8"Unknown shop"s;
        rankn(10, 5) = u8"Shop"s;
        rankn(0, 6) = u8"Boss"s;
        rankn(1, 6) = u8"King's advisor"s;
        rankn(2, 6) = u8"Elite consultant"s;
        rankn(3, 6) = u8"Famous consultant"s;
        rankn(4, 6) = u8"Model voter"s;
        rankn(5, 6) = u8"Nice voter"s;
        rankn(6, 6) = u8"Infamous voter"s;
        rankn(7, 6) = u8"Average voter"s;
        rankn(8, 6) = u8"Indifferent voter"s;
        rankn(9, 6) = u8"Almost voter"s;
        rankn(10, 6) = u8"Community"s;
        rankn(0, 8) = u8"Grand master"s;
        rankn(1, 8) = u8"Master"s;
        rankn(2, 8) = u8"Adept"s;
        rankn(3, 8) = u8"Expert"s;
        rankn(4, 8) = u8"Journeyman"s;
        rankn(5, 8) = u8"Senior"s;
        rankn(6, 8) = u8"Apprentice"s;
        rankn(7, 8) = u8"Official member"s;
        rankn(8, 8) = u8"Candidate"s;
        rankn(9, 8) = u8"Thug"s;
        rankn(10, 8) = u8"Guild"s;
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
        return i18n::s.get("core.locale.guild.mages.name");
    }
    else if (game_data.guild.belongs_to_fighters_guild)
    {
        return i18n::s.get("core.locale.guild.fighters.name");
    }
    else if (game_data.guild.belongs_to_thieves_guild)
    {
        return i18n::s.get("core.locale.guild.thieves.name");
    }
    else
    {
        return i18n::s.get("core.locale.guild.none.name");
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
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() == 0)
        {
            continue;
        }
        inv[cnt].identification_state = IdentifyState::completely_identified;
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



int iequiploc(int ci)
{
    switch (the_item_db[inv[ci].id]->category)
    {
    case 12000: return 1;
    case 34000: return 2;
    case 20000: return 3;
    case 16000: return 4;
    case 10000: return 5;
    case 14000: return 5;
    case 32000: return 6;
    case 22000: return 7;
    case 18000: return 9;
    case 24000: return 10;
    case 25000: return 11;
    case 19000: return 8;
    default: return 0;
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
    if (Config::instance().autoturn == "normal")
    {
        await(delay);
        ++scrturn;
    }
    if (Config::instance().autoturn != "highest" || firstautoturn == 1)
    {
        screenupdate = -1;
        update_screen();
    }
    if (Config::instance().autoturn == "normal")
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

    return i18n::s.get_enum(
        "core.locale.action.target.level", danger, cdata[tc]);
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
    if (Config::instance().autonumlock)
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
    elona_vector1<std::string>& prm_435,
    std::string prm_436,
    int prm_437)
{
    elona_vector1<int> p_at_m40;
    p_at_m40(0) = 0;
    for (int cnt = 0; cnt < 40; ++cnt)
    {
        prm_435(cnt) = "";
        getstr(prm_435(cnt), prm_436, p_at_m40(0), prm_437);
        if (strsize == 0)
        {
            break;
        }
        p_at_m40(0) += strsize;
    }
}



void load_random_name_table()
{
    std::vector<std::string> lines;
    range::copy(
        fileutil::read_by_line(
            i18n::s.get_locale_dir("core") / "lazy" / "ndata.csv"),
        std::back_inserter(lines));

    SDIM3(randn1, 30, 20);
    SDIM4(rnlist, 20, 15, lines.size());

    for (size_t i = 0; i < lines.size(); ++i)
    {
        csvsort(randn1, lines[i], 44);
        for (size_t j = 0; j < 15; ++j)
        {
            rnlist(j, i) = randn1(j);
        }
    }
}



void load_random_title_table()
{
    std::vector<std::string> lines;
    range::copy(
        fileutil::read_by_line(filesystem::dir::data() / u8"name.csv"),
        std::back_inserter(lines));

    SDIM3(rn1, 15, lines.size());
    SDIM3(rn2, 15, lines.size());

    for (size_t i = 0; i < lines.size(); ++i)
    {
        csvsort(randn1, lines[i], 44);
        rn1(i) = lang(randn1(0), randn1(1));
        rn2(i) = lang(randn1(2), randn1(3));
    }
}



void getinheritance(int prm_440, elona_vector1<int>& inhlist_, int& inhmax_)
{
    int p_at_m42 = 0;
    int f_at_m42 = 0;
    randomize(inv[prm_440].turn + 1);
    DIM2(inhlist_, 15);
    inhmax_ = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p_at_m42 = rnd(15);
        if (inv[prm_440].enchantments[p_at_m42].id == 0)
        {
            continue;
        }
        f_at_m42 = 0;
        for (int cnt = 0, cnt_end = (inhmax_ + 1); cnt < cnt_end; ++cnt)
        {
            if (p_at_m42 == inhlist_(cnt))
            {
                f_at_m42 = 1;
                break;
            }
        }
        if (f_at_m42 == 1)
        {
            continue;
        }
        if (rnd(4) > inhmax_ || inv[prm_440].enchantments[p_at_m42].power < 0)
        {
            inhlist_(inhmax_) = p_at_m42;
            ++inhmax_;
        }
    }
    randomize();
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



void fltn(const std::string& prm_447)
{
    std::string s2_at_m44;
    int p_at_m44 = 0;
    s2_at_m44 = prm_447;
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
    if (!the_item_db[inv[ci].id]->is_cargo)
    {
        return 1;
    }
    if (map_data.type != mdata_t::MapType::world_map
        && map_data.type != mdata_t::MapType::player_owned
        && map_data.type != mdata_t::MapType::town
        && map_data.type != mdata_t::MapType::field
        && map_data.type != mdata_t::MapType::shelter
        && map_data.type != mdata_t::MapType::guild)
    {
        txt(i18n::s.get("core.locale.ui.inv.cannot_use_cargo_items"),
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



int winposy(int prm_539, int prm_540)
{
    if (prm_540 == 0)
    {
        return ((inf_screenh + 1) * inf_tiles - prm_539) / 2 + 8;
    }
    return (windowh - prm_539) / 2;
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
        if (cc.character_role == 14 || cc.character_role == 16
            || cc.character_role == 1010)
        {
            cc.relationship = -3;
            cc.hate = 80;
            cc.emotion_icon = 218;
        }
    }
}



void modrank(int rank_id, int amount, int prm_554)
{
    int orgrank_at_m75 = 0;
    int i_at_m75 = 0;
    int rank_factor = game_data.ranks.at(rank_id) / 100;
    orgrank_at_m75 = game_data.ranks.at(rank_id);
    i_at_m75 = amount;
    if (amount > 0)
    {
        i_at_m75 = amount * (rank_factor + 20) * (rank_factor + 20) / 2500;
        game_data.rank_deadlines.at(rank_id) = ranknorma(rank_id);
        if (game_data.ranks.at(rank_id) == 100)
        {
            return;
        }
        if (prm_554 != 0)
        {
            if (i_at_m75 / 100 > prm_554)
            {
                i_at_m75 = prm_554 * 100;
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
            "core.locale.misc.ranking.changed",
            rankn(10, rank_id),
            from,
            to,
            ranktitle(rank_id)));
    }
    else if (i_at_m75 > 0)
    {
        txt(i18n::s.get("core.locale.misc.ranking.closer_to_next_rank"),
            Message::color{ColorIndex::green});
    }
}



int getworker(int map_id, int prm_579)
{
    int ret = -1;
    for (int i = 1; i < 16; ++i)
    {
        if (prm_579 != 0 && i != prm_579)
            continue;
        if (cdata[i].current_map == map_id)
        {
            ret = i;
            break;
        }
    }
    return ret;
}



int route_info(int& prm_612, int& prm_613, int prm_614)
{
    if (maxroute == 0)
    {
        return -1;
    }
    if (route(0, prm_614 % maxroute) == 1)
    {
        prm_612 += route(1, prm_614 % maxroute);
    }
    else
    {
        prm_613 += route(1, prm_614 % maxroute);
    }
    if (prm_614 % maxroute % 2 == 0)
    {
        if (route(0, (prm_614 + 1) % maxroute) != route(0, prm_614 % maxroute))
        {
            return -1;
        }
    }
    if (prm_614 >= maxroute)
    {
        if (prm_612 < scx || prm_613 < scy || prm_612 >= scx + inf_screenw
            || prm_613 >= scy + inf_screenh)
        {
            return 0;
        }
        if (prm_612 < 0 || prm_613 < 0 || prm_612 >= map_data.width
            || prm_613 >= map_data.height)
        {
            return 0;
        }
        if (chipm(7, cell_data.at(prm_612, prm_613).chip_id_actual) & 1)
        {
            return 0;
        }
        if (cell_data.at(prm_612, prm_613).feats != 0)
        {
            cell_featread(prm_612, prm_613);
            if (chipm(7, feat) & 1)
            {
                return 0;
            }
        }
    }
    if (route(1, prm_614 % maxroute) == 0)
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
                if (tx < scx || ty < scy || tx >= scx + inf_screenw
                    || ty >= scy + inf_screenh)
                {
                    continue;
                }
                if (tx < 0 || ty < 0 || tx >= map_data.width
                    || ty >= map_data.height)
                {
                    continue;
                }
                if (chipm(7, cell_data.at(tx, ty).chip_id_actual) & 1)
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



void lenfix(std::string& prm_644, int prm_645)
{
    int p_at_m89 = 0;
    p_at_m89 = prm_645 - strlen_u(prm_644);
    if (p_at_m89 < 1)
    {
        p_at_m89 = 1;
    }
    for (int cnt = 0, cnt_end = (p_at_m89); cnt < cnt_end; ++cnt)
    {
        prm_644 += u8" "s;
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



void fix_input_chat(std::string& str)
{
    str = strutil::replace(str, u8" ", u8"+");
    str = strutil::replace(str, u8"%", u8"per");
    str = strutil::replace(str, u8"&", u8"and");
    str = strutil::remove_str(str, u8"<");
    str = strutil::remove_str(str, u8">");
}



void fix_input_chat2(std::string& str)
{
    str = strutil::replace(str, u8"fucking", u8"nyoro~n");
    str = strutil::replace(str, u8"fuck", u8"nyou talk funny");
}



void cnv_filestr(std::string& str)
{
    str = strutil::replace(str, u8"\"", u8"_");
    str = strutil::replace(str, u8"\\", u8"_");
    str = strutil::replace(str, u8"<", u8"_");
    str = strutil::replace(str, u8">", u8"_");
    str = strutil::replace(str, u8"/", u8"_");
    str = strutil::replace(str, u8"?", u8"_");
    str = strutil::replace(str, u8"|", u8"_");
    str = strutil::replace(str, u8"*", u8"_");
}



std::string fixtxt(const std::string& prm_724, int prm_725)
{
    std::string m_at_m104;
    m_at_m104 = ""s + prm_724;
    if (strlen_u(prm_724) < size_t(prm_725))
    {
        while (1)
        {
            if (strlen_u(m_at_m104) >= size_t(prm_725))
            {
                break;
            }
            m_at_m104 += u8" "s;
        }
    }
    else
    {
        m_at_m104 = ""s + strmid(prm_724, 0, prm_725);
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
        "core.locale.magic.mount.mount.execute",
        cdata[mount],
        cdata[mount].current_speed));
    cdata[mount].is_ridden() = true;
    cell_data.at(cdata[mount].position.x, cdata[mount].position.y)
        .chara_index_plus_one = 0;
    game_data.mount = mount;
    create_pcpic(0, true);
    cdata[game_data.mount].continuous_action.finish();
    refresh_speed(cdata[game_data.mount]);
    txt(""s + cdata[mount].current_speed + u8") "s);
    if (cdata[game_data.mount].is_suitable_for_mount())
    {
        txt(i18n::s.get("core.locale.magic.mount.mount.suitable"));
    }
    else if (cdata[game_data.mount].is_unsuitable_for_mount())
    {
        txt(i18n::s.get("core.locale.magic.mount.mount.unsuitable"));
    }
}



void ride_end()
{
    int mount = game_data.mount;
    cdata[mount].is_ridden() = false;
    cdata[mount].continuous_action.finish();
    game_data.mount = 0;
    create_pcpic(0, true);
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
    int prm_777,
    int prm_778,
    int prm_779,
    int prm_780,
    int prm_781,
    int prm_782)
{
    for (int cnt = 1; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (dist(prm_777, prm_778, cdata[cnt].position.x, cdata[cnt].position.y)
            < prm_779)
        {
            if (rnd(prm_780) == 0)
            {
                if (cdata[cnt].sleep != 0)
                {
                    cdata[cnt].sleep = 0;
                    if (is_in_fov(cdata[cnt]))
                    {
                        txt(i18n::s.get(
                            "core.locale.misc.sound.waken", cdata[cnt]));
                    }
                    cdata[cnt].emotion_icon = 221;
                    if (prm_781)
                    {
                        if (rnd(500) == 0)
                        {
                            if (is_in_fov(cdata[cnt]))
                            {
                                txt(i18n::s.get(
                                        "core.locale.misc.sound.get_anger",
                                        cdata[cnt]),
                                    Message::color{ColorIndex::cyan});
                                txt(
                                    i18n::s.get("core.locale.misc.sound.can_no_"
                                                "longer_stand"));
                            }
                            turn_aggro(cnt, prm_782, 80);
                        }
                    }
                }
            }
        }
    }
}



void hostileaction(int prm_787, int prm_788)
{
    if (prm_787 >= 16 || prm_788 == 0)
    {
        return;
    }
    if (cdata[prm_788].relationship != -3)
    {
        cdata[prm_788].emotion_icon = 418;
    }
    if (cdata[prm_788].relationship == 10)
    {
        txt(i18n::s.get(
                "core.locale.misc.hostile_action.glares_at_you",
                cdata[prm_788]),
            Message::color{ColorIndex::purple});
    }
    else
    {
        if (cdata[prm_788].relationship == 0)
        {
            modify_karma(cdata.player(), -2);
        }
        if (cdata[prm_788].id == 202)
        {
            if (game_data.released_fire_giant == 0)
            {
                txt(i18n::s.get(
                        "core.locale.misc.hostile_action.glares_at_you",
                        cdata[prm_788]),
                    Message::color{ColorIndex::purple});
                return;
            }
        }
        if (cdata[prm_788].relationship > -2)
        {
            txt(i18n::s.get(
                    "core.locale.misc.hostile_action.glares_at_you",
                    cdata[prm_788]),
                Message::color{ColorIndex::purple});
            cdata[prm_788].relationship = -2;
        }
        else
        {
            if (cdata[prm_788].relationship != -3)
            {
                txt(i18n::s.get(
                        "core.locale.misc.hostile_action.gets_furious",
                        cdata[prm_788]),
                    Message::color{ColorIndex::purple});
            }
            cdata[prm_788].relationship = -3;
            cdata[prm_788].hate = 80;
            cdata[prm_788].enemy_id = prm_787;
        }
        chara_custom_talk(prm_788, 101);
    }
    if (cdata[prm_788].is_livestock() == 1)
    {
        if (rnd(50) == 0)
        {
            txt(i18n::s.get("core.locale.misc.hostile_action.get_excited"),
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
    cdata[prm_788].continuous_action.finish();
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



void animeload(int prm_807, int prm_808)
{
    elona_vector1<int> i_at_m133;
    if (mode != 0)
    {
        return;
    }
    if (is_in_fov(cdata[prm_808]) == 0)
    {
        return;
    }
    if (Config::instance().animewait == 0)
    {
        return;
    }
    screenupdate = -1;
    update_screen();
    dx_at_m133 = (cdata[prm_808].position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133 = (cdata[prm_808].position.y - scy) * inf_tiles + inf_screeny;
    gsel(7);
    picload(filesystem::dir::graphic() / (u8"anime"s + prm_807 + u8".bmp"));
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, dx_at_m133 - 24, dy_at_m133 - 40, 96, 96);
    gsel(0);
    gmode(2);
    i_at_m133(0) = 5;
    i_at_m133(1) = Config::instance().animewait * 3.5;
    r_at_m133 = 0;
    if (prm_807 == 8)
    {
        snd("core.offer1");
    }
    if (prm_807 == 10)
    {
        i_at_m133(0) = 8;
        i_at_m133(1) = Config::instance().animewait * 2.5;
        r_at_m133 = 0.2;
        snd("core.enc2");
    }
    if (prm_807 == 11)
    {
        i_at_m133(0) = 5;
        i_at_m133(1) = Config::instance().animewait * 3.5;
        r_at_m133 = 0;
        snd("core.enc");
    }
    if (prm_807 == 14)
    {
        i_at_m133(0) = 6;
        i_at_m133(1) = Config::instance().animewait * 3.5;
    }
    for (int cnt = 0, cnt_end = (i_at_m133); cnt < cnt_end; ++cnt)
    {
        gmode(2);
        pos(dx_at_m133 + 24, dy_at_m133 + 8);
        grotate(7, cnt * 96, 0, 96, 96, r_at_m133 * cnt);
        gmode(0);
        redraw();
        pos(dx_at_m133 - 24, dy_at_m133 - 40);
        gcopy(4, 0, 0, 96, 96);
        await(i_at_m133(1));
    }
    gmode(2);
}



void animeblood(int cc, int animation_type, int element)
{
    if (is_in_fov(cdata[cc]) == 0)
        return;
    if (Config::instance().animewait == 0)
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
    pos(0, 0);
    gcopy(0, dx_at_m133 - 48, dy_at_m133 - 56, 144, 160);

    int ele2_at_m133 = 1;
    gsel(7);
    switch (element)
    {
    case 52:
        picload(filesystem::dir::graphic() / u8"anime18.bmp");
        dy_at_m133(1) = -16;
        break;
    case 51:
        picload(filesystem::dir::graphic() / u8"anime19.bmp");
        dy_at_m133(1) = -16;
        break;
    case 50:
        picload(filesystem::dir::graphic() / u8"anime20.bmp");
        dy_at_m133(1) = -20;
        break;
    case 56:
        picload(filesystem::dir::graphic() / u8"anime22.bmp");
        dy_at_m133(1) = -24;
        break;
    case 53:
        picload(filesystem::dir::graphic() / u8"anime21.bmp");
        dy_at_m133(1) = -16;
        break;
    case 54:
        picload(filesystem::dir::graphic() / u8"anime23.bmp");
        dy_at_m133(1) = -16;
        break;
    case 57:
        picload(filesystem::dir::graphic() / u8"anime24.bmp");
        dy_at_m133(1) = -16;
        break;
    case 59:
        picload(filesystem::dir::graphic() / u8"anime25.bmp");
        dy_at_m133(1) = -16;
        break;
    case 58:
        picload(filesystem::dir::graphic() / u8"anime26.bmp");
        dy_at_m133(1) = -16;
        break;
    case 55:
    case 63:
        picload(filesystem::dir::graphic() / u8"anime27.bmp");
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
            pos(dx_at_m133 - 24, dy_at_m133 - 32 + dy_at_m133(1));
            gcopy(7, cnt * 96, 0, 96, 96);
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            pos(dx_at_m133 + 24 + x_at_m133(cnt)
                    + (x_at_m133(cnt) < 3) * ((1 + (cnt % 2 == 0)) * -1)
                        * cnt2_at_m133
                    + (x_at_m133(cnt) > -4) * (1 + (cnt % 2 == 0))
                        * cnt2_at_m133,
                dy_at_m133 + y_at_m133(cnt) + cnt2_at_m133 * cnt2_at_m133 / 2
                    - 12 + cnt);
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                24 - cnt2_at_m133 * 2,
                24 - cnt2_at_m133 * 2,
                0.2 * cnt);
        }
        gmode(0);
        redraw();
        pos(dx_at_m133 - 48, dy_at_m133 - 56);
        gcopy(4, 0, 0, 144, 160);
        await(Config::instance().animewait * (ele2_at_m133 == 0 ? 1.75 : 2.75));
    }

    gmode(2);
}



void spillblood(int prm_830, int prm_831, int prm_832)
{
    for (int cnt = 0, cnt_end = (prm_832 + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = prm_830;
            dy_at_m136 = prm_831;
        }
        else
        {
            dx_at_m136 = prm_830 + rnd(2) - rnd(2);
            dy_at_m136 = prm_831 + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0
            || dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chipm(2, cell_data.at(dx_at_m136, dy_at_m136).chip_id_actual))
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10 < 5)
        {
            ++cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments;
        }
    }
}



void spillfrag(int prm_833, int prm_834, int prm_835)
{
    for (int cnt = 0, cnt_end = (prm_835 + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            dx_at_m136 = prm_833;
            dy_at_m136 = prm_834;
        }
        else
        {
            dx_at_m136 = prm_833 + rnd(2) - rnd(2);
            dy_at_m136 = prm_834 + rnd(2) - rnd(2);
        }
        if (dx_at_m136 < 0 || dx_at_m136 >= map_data.width || dy_at_m136 < 0
            || dy_at_m136 >= map_data.height)
        {
            continue;
        }
        if (chipm(2, cell_data.at(dx_at_m136, dy_at_m136).chip_id_actual))
        {
            continue;
        }
        if (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10 < 4)
        {
            cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments =
                cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments % 10
                + (cell_data.at(dx_at_m136, dy_at_m136).blood_and_fragments / 10
                   + 1)
                    * 10;
        }
    }
}



void check_kill(int prm_836, int prm_837)
{
    int p_at_m137 = 0;
    if (game_data.current_map == mdata_t::MapId::pet_arena
        || game_data.current_map == mdata_t::MapId::show_house
        || game_data.current_map == mdata_t::MapId::arena)
    {
        return;
    }
    p_at_m137 = 0;
    if (prm_836 >= 0)
    {
        if (prm_836 == 0 || cdata[prm_836].relationship >= 10)
        {
            if (prm_837 >= 16)
            {
                ++game_data.kill_count;
                if (cdata[prm_837].id == game_data.guild.fighters_guild_target)
                {
                    if (game_data.guild.fighters_guild_quota > 0)
                    {
                        --game_data.guild.fighters_guild_quota;
                    }
                }
                if (cdata[prm_837].original_relationship >= 0)
                {
                    p_at_m137 = -2;
                }
                if (cdata[prm_837].id == 183)
                {
                    p_at_m137 = -15;
                }
                if (cdata[prm_837].id == 184)
                {
                    p_at_m137 = -10;
                }
                if (cdata[prm_837].id == 185)
                {
                    p_at_m137 = -5;
                }
                if ((cdata[prm_837].character_role >= 1000
                     && cdata[prm_837].character_role < 2000)
                    || cdata[prm_837].character_role == 2003)
                {
                    p_at_m137 = -10;
                }
                if (cdata[prm_837].character_role == 13)
                {
                    chara_modify_impression(cdata[prm_837], -25);
                }
            }
        }
        if (cdata[prm_836].relationship >= 10)
        {
            if (prm_836 != 0)
            {
                if (cdata[prm_836].impression < 200)
                {
                    if (rnd(2))
                    {
                        chara_modify_impression(cdata[prm_836], 1);
                        cdata[prm_836].emotion_icon = 317;
                    }
                }
                else if (rnd(10) == 0)
                {
                    chara_modify_impression(cdata[prm_836], 1);
                    cdata[prm_836].emotion_icon = 317;
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
        return i18n::s.get("core.locale.item.armor_class.heavy");
    }
    else if (id == 170)
    {
        return i18n::s.get("core.locale.item.armor_class.medium");
    }
    else
    {
        return i18n::s.get("core.locale.item.armor_class.light");
    }
}



void cnvbonus(int prm_895, int prm_896)
{
    // TODO: i18n
    if (prm_895 >= 50 && prm_895 < 61)
    {
        if (prm_896 > 0)
        {
            buff += u8"　　"s
                + i18n::s.get_m(
                      "locale.ability",
                      the_ability_db.get_id_from_legacy(prm_895)->get(),
                      "name")
                + u8"耐性に <green>クラス"s + prm_896 / 50 + u8"<col>("s
                + prm_896 + u8") のボーナス\n"s;
        }
        if (prm_896 < 0)
        {
            buff += u8"　　"s
                + i18n::s.get_m(
                      "locale.ability",
                      the_ability_db.get_id_from_legacy(prm_895)->get(),
                      "name")
                + u8"耐性に <red>クラス"s + prm_896 / 50 + u8"<col>("s + prm_896
                + u8") のマイナス修正\n"s;
        }
    }
    else
    {
        if (prm_896 > 0)
        {
            buff += u8"　　"s
                + i18n::s.get_m(
                      "locale.ability",
                      the_ability_db.get_id_from_legacy(prm_895)->get(),
                      "name")
                + u8"に <green>+"s + prm_896 + u8"<col> のボーナス\n"s;
        }
        if (prm_896 < 0)
        {
            buff += u8"　　"s
                + i18n::s.get_m(
                      "locale.ability",
                      the_ability_db.get_id_from_legacy(prm_895)->get(),
                      "name")
                + u8"に <red>"s + prm_896 + u8"<col> のマイナス修正\n"s;
        }
    }
}



void wet(int cc, int turns)
{
    cdata[cc].wet += turns;
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.locale.misc.wet.gets_wet", cdata[cc]));
        if (cdata[cc].is_invisible())
        {
            txt(i18n::s.get("core.locale.misc.wet.is_revealed", cdata[cc]));
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
                "core.locale.misc.fail_to_cast.mana_is_absorbed", cdata[cc]));
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
                    "core.locale.misc.fail_to_cast.is_confused_more",
                    cdata[cc]));
            }
            else
            {
                txt(i18n::s.get("core.locale.misc.fail_to_cast.too_difficult"));
            }
        }
        dmgcon(cc, StatusAilment::confused, 100);
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.misc.fail_to_cast.creatures_are_summoned"));
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
            "core.locale.misc.fail_to_cast.dimension_door_opens", cdata[cc]));
    }
    tc = cc;
    efid = 408;
    magic();
    return 0;
}



int try_to_reveal()
{
    if (rnd(sdata(159, cc) * 15 + 20 + sdata(13, cc))
        > rnd(game_data.current_dungeon_level * 8 + 60))
    {
        gain_detection_experience(cc);
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
    if (rnd(sdata(175, cc) * 15 + 20 + sdata(12, cc))
        > rnd(game_data.current_dungeon_level * 12 + 100))
    {
        gain_disarm_trap_experience();
        return 1;
    }
    return 0;
}



int try_to_perceive_npc(int cc)
{
    int cv = 0;
    cv = 8;
    if (cdata[cc].position.x > cdata[r2].position.x - cv
        && cdata[cc].position.x < cdata[r2].position.x + cv)
    {
        if (cdata[cc].position.y > cdata[r2].position.y - cv
            && cdata[cc].position.y < cdata[r2].position.y + cv)
        {
            if (cdata[r2].hate > 0)
            {
                return 1;
            }
            p = dist(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[r2].position.x,
                    cdata[r2].position.y)
                    * 150
                + (sdata(157, cc) * 100 + 150) + 1;
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
    game_data.continuous_action_about_to_start = 105;
    continuous_action_others();
}



void proc_turn_end(int cc)
{
    int regen = 0;
    regen = 1;
    if (cdata[cc].sleep > 0)
    {
        healcon(cc, StatusAilment::sleep, 1);
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
        healcon(cc, StatusAilment::poisoned, 1);
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
                txt(i18n::s.get("core.locale.misc.status_ailment.choked"));
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
                    "core.locale.misc.status_ailment.breaks_away_from_gravity",
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
                    "core.locale.misc.status_ailment.calms_down", cdata[cc]));
            }
        }
    }
    if (cdata[cc].sick > 0)
    {
        if (rnd(80) == 0)
        {
            p = rnd(10);
            if (encfind(cc, 60010 + p) == -1)
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
                    healcon(cc, StatusAilment::sick);
                }
            }
        }
    }
    if (cdata[cc].blind > 0)
    {
        healcon(cc, StatusAilment::blinded, 1);
        if (cdata[cc].blind > 0)
        {
            cdata[cc].emotion_icon = 110;
        }
    }
    if (cdata[cc].paralyzed > 0)
    {
        regen = 0;
        healcon(cc, StatusAilment::paralyzed, 1);
        if (cdata[cc].paralyzed > 0)
        {
            cdata[cc].emotion_icon = 115;
        }
    }
    if (cdata[cc].confused > 0)
    {
        healcon(cc, StatusAilment::confused, 1);
        if (cdata[cc].confused > 0)
        {
            cdata[cc].emotion_icon = 111;
        }
    }
    if (cdata[cc].fear > 0)
    {
        healcon(cc, StatusAilment::fear, 1);
        if (cdata[cc].fear > 0)
        {
            cdata[cc].emotion_icon = 113;
        }
    }
    if (cdata[cc].dimmed > 0)
    {
        healcon(cc, StatusAilment::dimmed, 1);
        if (cdata[cc].dimmed > 0)
        {
            cdata[cc].emotion_icon = 112;
        }
    }
    if (cdata[cc].drunk > 0)
    {
        healcon(cc, StatusAilment::drunk, 1);
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
        healcon(
            cc,
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
                txt(i18n::s.get(
                        "core.locale.misc.status_ailment.insane", cdata[cc]),
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
        healcon(cc, StatusAilment::insane, 1);
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
                if (cdata[cc].continuous_action.type
                    != ContinuousAction::Type::eat)
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
                txt(i18n::s.get("core.locale.misc.status_ailment.sleepy"));
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
    cdata.player().inventory_weight = clamp(inv_weight(0), 0, 20000000)
        * (100 - trait(201) * 10 + trait(205) * 20) / 100;
    cdata.player().max_inventory_weight =
        sdata(10, 0) * 500 + sdata(11, 0) * 250 + sdata(153, 0) * 2000 + 45000;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cdata.player().inventory_weight
            > cdata.player().max_inventory_weight * 2)
        {
            cdata.player().inventory_weight_type = 4;
            break;
        }
        if (cdata.player().inventory_weight
            > cdata.player().max_inventory_weight)
        {
            cdata.player().inventory_weight_type = 3;
            break;
        }
        if (cdata.player().inventory_weight
            > cdata.player().max_inventory_weight / 4 * 3)
        {
            cdata.player().inventory_weight_type = 2;
            break;
        }
        if (cdata.player().inventory_weight
            > cdata.player().max_inventory_weight / 2)
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
    txt(i18n::s.get("core.locale.misc.resurrect", cdatan(0, rc), cdata[rc]),
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
    cdata[rc].continuous_action.finish();
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
    if (cdata[rc].id == 326)
    {
        chara_gain_fixed_skill_exp(cdata[rc], 183, 1000);
    }
    chara_refresh(rc);
}



int convertartifact(int prm_930, int prm_931)
{
    int f_at_m163 = 0;
    int tc_at_m163 = 0;
    std::string n_at_m163;
    if (the_item_db[inv[prm_930].id]->category >= 50000)
    {
        return prm_930;
    }
    if (inv[prm_930].quality != Quality::special)
    {
        return prm_930;
    }
    if (inv[prm_930].body_part != 0)
    {
        return prm_930;
    }
    f_at_m163 = 0;
    for (int cnt = 0; cnt < 5480; ++cnt)
    {
        if (prm_931)
        {
            if (cnt >= 5080)
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
            if (cdata[tc_at_m163].state() == Character::State::empty
                || cdata[tc_at_m163].character_role == 13)
            {
                continue;
            }
        }
        if (inv[cnt].number() > 0)
        {
            if (inv[cnt].id == inv[prm_930].id)
            {
                if (cnt != prm_930)
                {
                    f_at_m163 = 1;
                    break;
                }
            }
        }
    }
    if (f_at_m163 == 0)
    {
        return prm_930;
    }
    n_at_m163 = ""s + itemname(prm_930);

    while (1)
    {
        flt(the_item_db[inv[prm_930].id]->level, Quality::miracle);
        flttypeminor = the_item_db[inv[prm_930].id]->subcategory;
        inv[prm_930].remove();

        itemcreate(
            inv_getowner(prm_930),
            0,
            inv[prm_930].position.x,
            inv[prm_930].position.y,
            0);
        if (inv[prm_930].quality != Quality::special)
        {
            break;
        }
    }

    txt(i18n::s.get(
        "core.locale.misc.artifact_regeneration", n_at_m163, inv[ci]));
    return prm_930;
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
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"book.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, u8"%DEFINE"s);
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    notedel(0);
    SDIM3(booktitle, noteinfo(), 25);
    p = 0;
    elona_vector1<std::string> tmp;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(tmp, cnt);
        csvsort(s, tmp, 44);
        booktitle(elona::stoi(s(0))) = lang(s(1), s(2));
        if (elona::stoi(s(3)) == 1)
        {
            isetbook(p) = elona::stoi(s(0));
            ++p;
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
        for (const auto& cnt : items(rc))
        {
            ci = cnt;
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (map_data.refresh_type == 0)
            {
                if (inv[cnt].body_part != 0)
                {
                    continue;
                }
                if (ibit(5, ci))
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
            if (the_item_db[inv[ci].id]->is_cargo)
            {
                if (map_data.type != mdata_t::MapType::world_map
                    && map_data.type != mdata_t::MapType::player_owned
                    && map_data.type != mdata_t::MapType::town
                    && map_data.type != mdata_t::MapType::field
                    && map_data.type != mdata_t::MapType::shelter
                    && map_data.type != mdata_t::MapType::guild)
                {
                    continue;
                }
                else if (rnd(2))
                {
                    continue;
                }
            }
            f = 0;
            if (inv[ci].body_part != 0)
            {
                if (rnd(10))
                {
                    f = 1;
                }
                if (inv[ci].curse_state == CurseState::blessed)
                {
                    if (rnd(2))
                    {
                        f = 1;
                    }
                }
                if (is_cursed(inv[ci].curse_state))
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
                if (inv[ci].curse_state == CurseState::doomed)
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
            }
            else if (
                inv[ci].identification_state
                == IdentifyState::completely_identified)
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
            if (inv[ci].body_part != 0)
            {
                cdata[rc].body_parts[inv[ci].body_part - 100] =
                    cdata[rc].body_parts[inv[ci].body_part - 100] / 10000
                    * 10000;
                inv[ci].body_part = 0;
            }
            f = 0;
            if (ibit(5, ci) == 0)
            {
                if (rnd(4) == 0)
                {
                    f = 1;
                }
                if (inv[ci].curse_state == CurseState::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 0;
                    }
                }
                if (is_cursed(inv[ci].curse_state))
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
                if (inv[ci].curse_state == CurseState::doomed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
            }
            if (f)
            {
                inv[ci].remove();
                continue;
            }
            inv[ci].position.x = cdata[rc].position.x;
            inv[ci].position.y = cdata[rc].position.y;
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
        create_pcpic(0, true);
        return;
    }
    else
    {
        if (rc < 16)
        {
            if (cdata[rc].has_own_sprite() == 1)
            {
                create_pcpic(rc, true);
            }
        }
        if (cdata[rc].relationship == 10)
        {
            return;
        }
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (cdata[rc].id == 185)
        {
            return;
        }
        if (cdata[rc].id == 204)
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
    for (const auto& cnt : items(rc))
    {
        if (inv[cnt].number() == 0)
        {
            continue;
        }
        ci = cnt;
        f = 0;
        if (cdata[rc].character_role == 20)
        {
            break;
        }
        if (inv[ci].quality > Quality::miracle || inv[ci].id == 55)
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
        if (inv[ci].quality == Quality::special)
        {
            f = 1;
        }
        if (ibit(12, ci))
        {
            f = 1;
        }
        if (f == 0)
        {
            continue;
        }
        if (catitem != 0)
        {
            if (ibit(8, ci) == 0)
            {
                if (the_item_db[inv[ci].id]->category < 50000)
                {
                    if (inv[ci].quality >= Quality::great)
                    {
                        if (rnd(3))
                        {
                            txt(i18n::s.get(
                                    "core.locale.misc.black_cat_licks",
                                    cdata[catitem],
                                    inv[ci]),
                                Message::color{ColorIndex::cyan});
                            ibitmod(8, ci, 1);
                            reftype = the_item_db[inv[ci].id]->category;
                            enchantment_add(
                                ci,
                                enchantment_generate(
                                    enchantment_gen_level(rnd(4))),
                                enchantment_gen_p());
                            animeload(8, rc);
                        }
                    }
                }
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
        itemturn(ci);
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
    if (cdata[rc].quality >= Quality::miracle || rnd(20) == 0
        || cdata[rc].drops_gold() == 1 || rc < 16)
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

    switch (access_class_info(16, cdatan(3, rc)))
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

    dbid = cdata[rc].id;
    dbmode = 16;
    dbspec = 3;
    switch (access_character_info())
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
    if (game_data.current_map != mdata_t::MapId::arena
        && cdata[rc].character_role != 20)
    {
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0
            || (cdata[rc].quality == Quality::miracle && rnd(2) == 0)
            || (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            itemcreate(-1, 504, cdata[rc].position.x, cdata[rc].position.y, 0);
            inv[ci].param1 = cdata[rc].image;
            inv[ci].subname = cdata[rc].id;
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (rnd(175) == 0 || cdata[rc].quality == Quality::special || 0
            || (cdata[rc].quality == Quality::miracle && rnd(2) == 0)
            || (cdata[rc].quality == Quality::godly && rnd(3) == 0))
        {
            flt();
            itemcreate(-1, 503, cdata[rc].position.x, cdata[rc].position.y, 0);
            inv[ci].param1 = cdata[rc].image;
            inv[ci].subname = cdata[rc].id;
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
    if (rollanatomy == 1 || cdata[rc].quality >= Quality::miracle || 0
        || cdata[rc].is_livestock() == 1 || 0)
    {
        flt();
        int stat =
            itemcreate(-1, 204, cdata[rc].position.x, cdata[rc].position.y, 0);
        if (stat != 0)
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

    // ../runtime/mods/core/exports/impl/chara_drop.lua
    lua::call(
        "exports:core.impl.chara_drop.drop_from_chara", lua::handle(cdata[rc]));

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
                txt(i18n::s.get(
                        "core.locale.misc.curse.gold_stolen", cdata[cc]),
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
            txt(i18n::s.get(
                "core.locale.misc.pregnant.pats_stomach", cdata[cc]));
            txt(i18n::s.get("core.locale.misc.pregnant.something_is_wrong"));
        }
    }
    if (map_data.type != mdata_t::MapType::world_map)
    {
        if (rnd(30) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.misc.pregnant.something_breaks_out",
                    cdata[cc]));
            }
            cdata[cc].bleeding += 15;
            flt();
            initlv = cdata[cc].level / 2 + 1;
            novoidlv = 1;
            int stat = chara_create(
                -1, 330, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (strlen_u(cdatan(0, cc)) > 10
                    || instr(
                           cdatan(0, cc),
                           0,
                           i18n::s.get("core.locale.chara.job.alien.child"))
                        != -1)
                {
                    cdatan(0, rc) =
                        i18n::s.get("core.locale.chara.job.alien.alien_kid");
                }
                else
                {
                    cdatan(0, rc) = i18n::s.get(
                        "core.locale.chara.job.alien.child_of", cdatan(0, cc));
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
                    if (rnd(25)
                        < clamp(
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
                                "core.locale.misc.curse.blood_sucked",
                                cdata[cc]),
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
                                "core.locale.misc.curse.experience_reduced",
                                cdata[cc]),
                            Message::color{ColorIndex::purple});
                    }
                    cdata[cc].experience -= cdata[cc].required_experience
                            / (300
                               - clamp(
                                     std::abs(inv[ci].enchantments[cnt].power)
                                         / 2,
                                     0,
                                     50))
                        + rnd(100);
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
                        if (rnd(50)
                            < clamp(
                                  std::abs(inv[ci].enchantments[cnt].power)
                                      / 50,
                                  1,
                                  50))
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                txt(i18n::s.get("core.locale.misc.curse."
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
    if (cdata.player().confused != 0 || cdata.player().sleep != 0
        || cdata.player().paralyzed != 0 || cdata.player().choked != 0)
    {
        return;
    }
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() == 0
            || inv[cnt].identification_state
                == IdentifyState::completely_identified)
        {
            continue;
        }
        if (the_item_db[inv[cnt].id]->category >= 50000)
        {
            continue;
        }
        ci = cnt;
        p(0) = sdata(13, 0) + sdata(162, 0) * 5;
        p(1) = 1500 + inv[ci].difficulty_of_identification * 5;
        if (p > rnd(p(1) * 5))
        {
            s = itemname(ci);
            item_identify(inv[ci], IdentifyState::completely_identified);
            itemmemory(0, inv[ci].id) = 1;
            if (!Config::instance().hideautoidentify)
            {
                txt(i18n::s.get(
                    "core.locale.misc.identify.fully_identified",
                    s(0),
                    inv[ci]));
            }
            chara_gain_skill_exp(cdata.player(), 162, 50);
        }
        if (inv[ci].identification_state <= IdentifyState::partly_identified)
        {
            if (p > rnd(p(1)))
            {
                if (!Config::instance().hideautoidentify)
                {
                    txt(i18n::s.get(
                        "core.locale.misc.identify.almost_identified",
                        inv[ci],
                        i18n::_(
                            u8"ui",
                            u8"quality",
                            u8"_"s + static_cast<int>(inv[ci].quality))));
                }
                item_identify(inv[ci], IdentifyState::almost_identified);
                chara_gain_skill_exp(cdata.player(), 162, 50);
            }
        }
    }
}



void lovemiracle(int prm_932)
{
    if (rnd(2) || prm_932 == 0)
    {
        return;
    }
    cibk = ci;
    txt(i18n::s.get("core.locale.misc.love_miracle.uh"),
        Message::color{ColorIndex::cyan});
    flt();
    if (rnd(2))
    {
        int stat = itemcreate(
            -1, 573, cdata[prm_932].position.x, cdata[prm_932].position.y, 0);
        if (stat)
        {
            inv[ci].subname = cdata[prm_932].id;
            inv[ci].weight = cdata[prm_932].weight * 10 + 250;
            inv[ci].value = clamp(
                cdata[prm_932].weight * cdata[prm_932].weight / 10000,
                200,
                40000);
        }
    }
    else
    {
        int stat = itemcreate(
            -1, 574, cdata[prm_932].position.x, cdata[prm_932].position.y, 0);
        if (stat)
        {
            inv[ci].subname = cdata[prm_932].id;
        }
    }
    ci = cibk;
    snd("core.atk_elec");
    animeload(15, prm_932);
}



void get_pregnant()
{
    if (encfind(tc, 48) != -1)
    {
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.misc.pregnant.pukes_out", cdata[tc]));
        }
        return;
    }
    if (cdata[tc].is_pregnant() == 0)
    {
        txt(i18n::s.get("core.locale.misc.pregnant.gets_pregnant", cdata[tc]),
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
    Message::instance().msg_append_begin("  ");
    if (game_data.current_map == mdata_t::MapId::show_house
        || game_data.current_map == mdata_t::MapId::arena
        || game_data.current_map == mdata_t::MapId::pet_arena)
    {
        usermapid = 0;
    }
    rdtry = 0;
    fixstart = 0;
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon)
    {
        if (game_data.current_dungeon_level
            == area_data[game_data.current_map].deepest_level)
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
    if (game_data.previous_map == 30)
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
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 751)
                != -1)
            {
                feat(1) = 11;
                feat(2) = 0;
            }
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 750)
                != -1)
            {
                feat(1) = 10;
                feat(2) = 0;
            }
        }
        f = 0;
        if (feat(1) == 11)
        {
            Message::instance().msg_append(
                i18n::s.get("core.locale.misc.walk_down_stairs"));
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
            Message::instance().msg_append(
                i18n::s.get("core.locale.misc.walk_up_stairs"));
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
                    if (area_data[game_data.current_map].id
                        == mdata_t::MapId::the_void)
                    {
                        if (itemfind(0, 742) == -1)
                        {
                            txt(i18n::s.get(
                                "core.locale.action.exit_map.not_permitted"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id
                        == mdata_t::MapId::pyramid)
                    {
                        if (game_data.quest_flags.pyramid_trial == 0)
                        {
                            txt(
                                i18n::s.get("core.locale.action.exit_map.no_"
                                            "invitation_to_pyramid"));
                            msg_halt();
                            game_data.current_map =
                                static_cast<int>(mdata_t::MapId::fields);
                        }
                    }
                    if (area_data[game_data.current_map].id
                        == mdata_t::MapId::jail)
                    {
                        txt(i18n::s.get(
                            "core.locale.action.exit_map.cannot_enter_jail"));
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
            if (map_data.type == mdata_t::MapType::town
                || map_data.type == mdata_t::MapType::field
                || map_data.type == mdata_t::MapType::player_owned
                || map_data.type == mdata_t::MapType::shelter
                || map_data.type == mdata_t::MapType::guild)
            {
                game_data.current_map = game_data.destination_outer_map;
            }
        }
        if (mdata_t::is_nefia(map_data.type)
            || map_data.type == static_cast<int>(mdata_t::MapType::shelter))
        {
            if (game_data.current_dungeon_level
                < area_data[game_data.current_map].danger_level)
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
                    Message::instance().msg_append(i18n::s.get(
                        "core.locale.action.exit_map.surface.returned_to",
                        mapname(game_data.current_map)));
                }
                else
                {
                    Message::instance().msg_append(i18n::s.get(
                        "core.locale.action.exit_map.surface.left",
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
            if (game_data.previous_map != 2)
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
        game_data.destination_outer_map = area_data[7].outer_map;
        game_data.current_dungeon_level = 1;
    }
    if (rdtry > 1)
    {
        Message::instance().msg_append(u8"(再生成"s + rdtry + u8"回)"s);
    }
    if (game_data.current_map != game_data.previous_map)
    {
        if (map_is_town_or_guild()
            || game_data.previous_map == mdata_t::MapId::your_home
            || game_data.departure_date == 0)
        {
            game_data.departure_date = game_data.date.hours();
            game_data.distance_between_town = 0;
            game_data.left_town_map = game_data.previous_map;
        }
        if (area_data[game_data.current_map].type != mdata_t::MapType::world_map
            && area_data[game_data.current_map].type != mdata_t::MapType::field
            && game_data.current_map != mdata_t::MapId::show_house)
        {
            autosave =
                1 * (game_data.current_map != mdata_t::MapId::show_house);
        }
        if (map_data.type != mdata_t::MapType::world_map)
        {
            if (map_data.type != mdata_t::MapType::field
                || map_data.type == mdata_t::MapType::player_owned)
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
            Message::instance().msg_append(i18n::s.get(
                "core.locale.action.exit_map.delivered_to_your_home"));
            weather_changes_by_location(false);
        }
        else if (
            area_data[game_data.previous_map].type
            == mdata_t::MapType::world_map)
        {
            Message::instance().msg_append(i18n::s.get(
                "core.locale.action.exit_map.entered",
                mapname(game_data.current_map)));
        }
        else if (map_data.type == mdata_t::MapType::temporary)
        {
            Message::instance().msg_append(i18n::s.get(
                "core.locale.action.exit_map.returned_to",
                mapname(game_data.current_map)));
        }
        else
        {
            Message::instance().msg_append(i18n::s.get(
                "core.locale.action.exit_map.left",
                mapname(game_data.previous_map)));
        }
        if (game_data.cargo_weight > game_data.current_cart_limit)
        {
            if (area_data[game_data.current_map].type
                    == mdata_t::MapType::world_map
                || area_data[game_data.current_map].type
                    == mdata_t::MapType::field)
            {
                Message::instance().msg_append(i18n::s.get(
                    "core.locale.action.exit_map.burdened_by_cargo"));
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
            Message::instance().msg_append(
                i18n::s.get("core.locale.action.exit_map.mountain_pass"));
        }
    }
    if (game_data.current_map == mdata_t::MapId::mountain_pass)
    {
        if (game_data.current_dungeon_level
            == area_data[game_data.current_map].deepest_level)
        {
            game_data.current_map = static_cast<int>(mdata_t::MapId::larna);
            game_data.current_dungeon_level = 1;
            game_data.entrance_type = 2;
            Message::instance().msg_append(
                i18n::s.get("core.locale.action.exit_map.larna"));
        }
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        cdata[cnt].hate = 0;
        cdata[cnt].enemy_id = 0;
        cdata[cnt].continuous_action.finish();
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
    }
    else
    {
        // This is a temporary map, so wipe its data (shelter, special
        // quest instance)
        prepare_charas_for_map_unload();

        tmpload(filesystem::u8path("mdata_" + mid + ".s2"));
        // delete all map-local data
        if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            ctrl_file(FileOperation::map_delete);
        }

        // forget about all NPCs that were here
        for (auto&& cnt : cdata.others())
        {
            if (cnt.state() != Character::State::empty)
            {
                --npcmemory(1, cnt.id);
            }
        }
    }

    bool map_changed = game_data.current_map != previous_map
        || game_data.current_dungeon_level != previous_dungeon_level;

    // Only clear map-local data if the map was changed. The map might
    // not change if access to it is refused (jail, pyramid, etc.).
    if (map_changed)
    {
        lua::lua->get_event_manager()
            .run_callbacks<lua::EventKind::map_unloading>();

        lua::lua->get_mod_manager().clear_map_local_data();
        lua::lua->get_handle_manager().clear_map_local_handles();
    }

    mode = 2;
    return TurnResult::initialize_map;
}



void prepare_charas_for_map_unload()
{
    // interrupt continuous actions
    for (int cnt = 0; cnt < 57; ++cnt)
    {
        cdata[cnt].continuous_action.finish();
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



void map_prepare_tileset_atlas()
{
    gsel(6);
    if (map_data.atlas_number != mtilefilecur)
    {
        pos(0, 0);
        picload(
            filesystem::dir::graphic()
                / (u8"map"s + map_data.atlas_number + u8".bmp"),
            1);
        mtilefilecur = map_data.atlas_number;
        initialize_map_chip();
    }
    map_tileset(map_data.tileset);
    gsel(2);
    gmode(0);
    pos(0, 0);
    // gcopy(6, 0, 0, 33 * inf_tiles, 25 * inf_tiles);

    int shadow = 5;
    if (map_data.indoors_flag == 2)
    {
        if (game_data.date.hour >= 24
            || (game_data.date.hour >= 0 && game_data.date.hour < 4))
        {
            shadow = 110;
        }
        if (game_data.date.hour >= 4 && game_data.date.hour < 10)
        {
            shadow = std::min(10, 70 - (game_data.date.hour - 3) * 10);
        }
        if (game_data.date.hour >= 10 && game_data.date.hour < 12)
        {
            shadow = 10;
        }
        if (game_data.date.hour >= 12 && game_data.date.hour < 17)
        {
            shadow = 1;
        }
        if (game_data.date.hour >= 17 && game_data.date.hour < 21)
        {
            shadow = (game_data.date.hour - 17) * 20;
        }
        if (game_data.date.hour >= 21 && game_data.date.hour < 24)
        {
            shadow = 80 + (game_data.date.hour - 21) * 10;
        }
        if (game_data.weather == 3 && shadow < 40)
        {
            shadow = 40;
        }
        if (game_data.weather == 4 && shadow < 65)
        {
            shadow = 65;
        }
        if (game_data.current_map == mdata_t::MapId::noyel
            && (game_data.date.hour >= 17 || game_data.date.hour < 7))
        {
            shadow += 35;
        }
    }

    pos(0, 0);
    gmode(0);
    set_color_mod(255 - shadow, 255 - shadow, 255 - shadow, 6);
    gcopy(6, 0, 0, 33 * inf_tiles, 25 * inf_tiles);
    set_color_mod(255, 255, 255, 6);
    gmode(4, 30);
    if (map_data.atlas_number == 0)
    {
        pos(0, 192);
        gcopy(6, 0, 192, 1360, 48);
    }
    if (map_data.atlas_number == 1)
    {
        pos(0, 1056);
        gcopy(6, 0, 1056, 1360, 48);
    }
    if (map_data.atlas_number != 2)
    {
        pos(0, 336);
        gcopy(6, 0, 336, 1360, 48);
    }
    gmode(0);
    gsel(0);
    gmode(2);
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
    if (p <= 25 || rnd(150) == 0 || game_data.diastrophism_flag != 0
        || game_data.reset_world_map_in_diastrophism_flag)
    {
        game_data.diastrophism_flag = 0;
        Message::instance().msg_append(
            i18n::s.get("core.locale.action.move.global.diastrophism"));
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
    initialize_map_chip();
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
        if (area_data[cnt].id == mdata_t::MapId::none
            || area_data[cnt].appearance == 0)
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
        if (area_data[cnt].position.x <= 0 || area_data[cnt].position.y <= 0
            || area_data[cnt].position.x >= map_data.width
            || area_data[cnt].position.y >= map_data.height)
        {
            area_data[cnt].position.x = map_data.width / 2;
            area_data[cnt].position.y = map_data.height / 2;
        }
        p = cnt;
        if (chipm(
                7,
                cell_data
                    .at(area_data[cnt].position.x, area_data[cnt].position.y)
                    .chip_id_actual)
                & 4
            || cell_data
                    .at(area_data[cnt].position.x, area_data[cnt].position.y)
                    .feats
                != 0)
        {
            for (int cnt = 0;; ++cnt)
            {
                dx = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.width);
                dy = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.height);
                x = area_data[p].position.x + rnd(dx(0)) - rnd(dx(0));
                y = area_data[p].position.y + rnd(dy) - rnd(dy);
                if (x <= 0 || y <= 0 || x >= map_data.width - 1
                    || y >= map_data.height - 1)
                {
                    continue;
                }
                if (33 <= cell_data.at(x, y).chip_id_actual
                    && cell_data.at(x, y).chip_id_actual < 66)
                {
                    continue;
                }
                if (chipm(7, cell_data.at(x, y).chip_id_actual) & 4)
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
        if (area_data[cnt].type == mdata_t::MapType::town
            || area_data[cnt].type == mdata_t::MapType::guild)
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



int random_material(int prm_1028, int prm_1029)
{
    int f_at_m174 = 0;
    int lv_at_m174 = 0;
    int rare_at_m174 = 0;
    int loc_at_m174 = 0;
    int p_at_m174 = 0;
    int f2_at_m174 = 0;
    int p2_at_m174 = 0;
    f_at_m174 = 0;
    lv_at_m174 = prm_1028;
    rare_at_m174 = prm_1029;
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
    if (atxthrough == 0)
    {
        atbuff = "";
        notesel(atbuff);
    }
    atxthrough = 0;
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
        gsel(4);
        gmode(0);
        pos(0, 0);
        picload(filesystem::dir::graphic() / (atxbg + u8".bmp"s), 1);
        pos(0, inf_msgh);
        gcopy(4, 0, 0, 240, 160, windoww, windowh - inf_verh - inf_msgh);
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
            pos(cnt * 192, 0);
            gcopy(3, 496, 528, sx, inf_msgh);
        }
        window2(windoww - 208, 0, 208, 98, 0, 0);
        pos(windoww - 204, 4);
        gcopy(0, 120, 88, windoww - 120, windowh - inf_verh - 112, 200, 90);
        gsel(0);
    }
}



void begintempinv()
{
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    for (const auto& cnt : items(-1))
    {
        inv[cnt].remove();
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
    tmpload(filesystem::u8path(u8"shop4.s2"));
    if (fs::exists(filesystem::dir::tmp() / u8"shop4.s2"s))
    {
        ctrl_file(FileOperation2::map_items_read, u8"shop4.s2"s);
    }
    else
    {
        for (const auto& cnt : items(-1))
        {
            inv[cnt].remove();
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
        p = calcincome(cnt) + rnd((calcincome(cnt) / 3 + 1))
            - rnd((calcincome(cnt) / 3 + 1));
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
            txt(i18n::s.get(
                    "core.locale.misc.income.sent_to_your_house", income(0)),
                Message::color{ColorIndex::orange});
        }
        else
        {
            txt(i18n::s.get(
                    "core.locale.misc.income.sent_to_your_house2",
                    income(0),
                    income(1)),
                Message::color{ColorIndex::orange});
        }
        autosave = 1 * (game_data.current_map != mdata_t::MapId::show_house);
    }
    if (game_data.date.day == 1)
    {
        if (cdata.player().level > 5)
        {
            autosave =
                1 * (game_data.current_map != mdata_t::MapId::show_house);
            p = -1;
            for (const auto& cnt : items(-1))
            {
                if (inv[cnt].number() == 0)
                {
                    p = cnt;
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
            txt(i18n::s.get("core.locale.misc.tax.bill"));
            if (game_data.left_bill > 1)
            {
                if (game_data.left_bill <= 4)
                {
                    if (game_data.left_bill > 3)
                    {
                        s(0) = i18n::s.get("core.locale.misc.tax.warning");
                        s(1) = i18n::s.get(
                            "core.locale.misc.tax.have_to_go_embassy");
                    }
                    else
                    {
                        s(0) = i18n::s.get("core.locale.misc.tax.caution");
                        s(1) = "";
                    }
                    txt(s
                            + i18n::s.get(
                                  "core.locale.misc.tax.left_bills",
                                  game_data.left_bill - 1)
                            + s(1),
                        Message::color{ColorIndex::red});
                }
            }
            if (game_data.left_bill > 4)
            {
                txt(i18n::s.get(
                        "core.locale.misc.tax.accused",
                        game_data.left_bill - 1),
                    Message::color{ColorIndex::red});
                int stat = decfame(0, 50);
                p = stat;
                txt(i18n::s.get("core.locale.misc.tax.lose_fame", p(0)),
                    Message::color{ColorIndex::red});
                modify_karma(cdata.player(), -30 * 2);
            }
        }
        else
        {
            txt(i18n::s.get("core.locale.misc.tax.no_duty"));
        }
    }
    ctrl_file(FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
    mode = 0;
    maybe_show_ex_help(16);
}



std::string txtitemoncell(int prm_1055, int prm_1056)
{
    elona_vector1<int> p_at_m185;
    elona_vector1<int> i_at_m185;
    const auto item_info = cell_itemoncell({prm_1055, prm_1056});
    const auto number = item_info.first;
    const auto item = item_info.second;

    if (number <= 3)
    {
        if (cell_data.at(prm_1055, prm_1056).item_appearances_memory < 0)
        {
            rtvaln = "";
            p_at_m185(0) =
                -cell_data.at(prm_1055, prm_1056).item_appearances_memory;
            p_at_m185(1) = 0;
            i_at_m185(0) = p_at_m185 % 1000 + 5080;
            i_at_m185(1) = p_at_m185 / 1000 % 1000 + 5080;
            i_at_m185(2) = p_at_m185 / 1000000 % 1000 + 5080;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (i_at_m185(cnt) == 6079)
                {
                    continue;
                }
                if (p_at_m185(1) != 0)
                {
                    rtvaln += i18n::s.get("core.locale.misc.and");
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
            return i18n::s.get(
                "core.locale.action.move.item_on_cell.item", rtvaln(0));
        }
        else if (inv[item].own_state == 3)
        {
            return i18n::s.get(
                "core.locale.action.move.item_on_cell.building", rtvaln(0));
        }
        else
        {
            return i18n::s.get(
                "core.locale.action.move.item_on_cell.not_owned", rtvaln(0));
        }
    }
    else
    {
        return i18n::s.get(
            "core.locale.action.move.item_on_cell.more_than_three", number);
    }
}



void txttargetnpc(int prm_1057, int prm_1058, int prm_1059)
{
    int dy_at_m186 = 0;
    int i_at_m186 = 0;
    int p_at_m186 = 0;
    dy_at_m186 = 0;
    font(14 - en * 2);
    if (prm_1059 == 0)
    {
        if (fov_los(
                cdata.player().position.x,
                cdata.player().position.y,
                prm_1057,
                prm_1058)
                == 0
            || dist(
                   cdata.player().position.x,
                   cdata.player().position.y,
                   prm_1057,
                   prm_1058)
                > cdata.player().vision_distance / 2)
        {
            bmes(
                i18n::s.get("core.locale.action.target.out_of_sight"),
                100,
                windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            cansee = 0;
            return;
        }
    }
    if (cell_data.at(prm_1057, prm_1058).chara_index_plus_one != 0)
    {
        i_at_m186 = cell_data.at(prm_1057, prm_1058).chara_index_plus_one - 1;
        if (cdata[i_at_m186].is_invisible() == 0
            || cdata.player().can_see_invisible() || cdata[i_at_m186].wet)
        {
            tc = i_at_m186;
            s = txttargetlevel(cc, tc);
            bmes(s, 100, windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            bmes(
                i18n::s.get(
                    "core.locale.action.target.you_are_targeting",
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
    if (cell_data.at(prm_1057, prm_1058).item_appearances_memory != 0)
    {
        bmes(
            txtitemoncell(prm_1057, prm_1058),
            100,
            windowh - inf_verh - 45 - dy_at_m186 * 20);
        ++dy_at_m186;
    }
    if (cell_data.at(prm_1057, prm_1058).feats != 0)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            if (cell_data.at(prm_1057, prm_1058).feats / 1000 % 100 == 15)
            {
                p_at_m186 =
                    cell_data.at(prm_1057, prm_1058).feats / 100000 % 100
                    + cell_data.at(prm_1057, prm_1058).feats / 10000000 * 100;
                bmes(
                    mapname(p_at_m186, true),
                    100,
                    windowh - inf_verh - 45 - dy_at_m186 * 20);
                ++dy_at_m186;
            }
            if (cell_data.at(prm_1057, prm_1058).feats / 1000 % 100 == 34)
            {
                bmes(
                    txtbuilding(
                        cell_data.at(prm_1057, prm_1058).feats / 100000 % 100,
                        cell_data.at(prm_1057, prm_1058).feats / 10000000),
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

    if (1 && game_data.wizard == 0)
    {
        do_save_game();
    }
    txt(i18n::s.get("core.locale.action.exit_map.gate.step_into"));
    inv[ci].modify_number(-1);
    txt(i18n::s.get("core.locale.action.exit_map.gate.need_network"));
    update_screen();
    return TurnResult::pc_turn_user_error;
}



int target_position()
{
    if (tlocinitx != 0 || tlocinity != 0)
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
        if (cdata.player().enemy_id == 0)
        {
            find_enemy_target();
        }
        build_target_list();
        if (listmax == 0)
        {
            txt(i18n::s.get("core.locale.misc.no_target_around"));
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

    while (1)
    {
        screenupdate = -1;
        update_screen();
        dx = (tlocx - scx) * inf_tiles + inf_screenx;
        dy = (tlocy - scy) * inf_tiles + inf_screeny;
        if (dy + inf_tiles <= windowh - inf_verh)
        {
            pos(dx, dy * (dy > 0));
            snail::Application::instance().get_renderer().set_blend_mode(
                snail::BlendMode::blend);
            snail::Application::instance().get_renderer().set_draw_color(
                {127, 127, 255, 50});
            snail::Application::instance().get_renderer().fill_rect(
                dx,
                dy * (dy > 0),
                inf_tiles
                    - (dx + inf_tiles > windoww) * (dx + inf_tiles - windoww),
                inf_tiles + (dy < 0) * inf_screeny
                    - (dy + inf_tiles > windowh - inf_verh)
                        * (dy + inf_tiles - windowh + inf_verh));
        }
        if (homemapmode == 1)
        {
            pos(windoww - 80, 20);
            gcopy(
                2,
                tile % 33 * inf_tiles,
                tile / 33 * inf_tiles,
                inf_tiles,
                inf_tiles);
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
                        cdata[rc].position.y)
                    == 0)
                {
                    break;
                }
                if ((cdata[rc].is_invisible() == 0
                     || cdata.player().can_see_invisible() || cdata[rc].wet)
                    == 0)
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
                            pos(sx, sy * (sy > 0));
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
                                    inf_tiles
                                        - (sx + inf_tiles > windoww)
                                            * (sx + inf_tiles - windoww),
                                    inf_tiles + (sy < 0) * inf_screeny
                                        - (sy + inf_tiles > windowh - inf_verh)
                                            * (sy + inf_tiles - windowh
                                               + inf_verh));
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
                if (chipm(0, cell_data.at(tlocx, tlocy).chip_id_actual) == 2
                    || chipm(0, cell_data.at(tlocx, tlocy).chip_id_actual) == 1)
                {
                    snd("core.fail1");
                    wait_key_released();
                    continue;
                }
                tile = cell_data.at(tlocx, tlocy).chip_id_actual;
                snd("core.cursor1");
                wait_key_released();
            }
            tx = clamp(mousex - inf_screenx, 0, windoww) / 48;
            ty = clamp(mousey - inf_screeny, 0, (windowh - inf_verh)) / 48;
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
                if (x >= 0 && y >= 0 && x < map_data.width
                    && y < map_data.height)
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
                if (cansee == 0
                    || chipm(7, cell_data.at(tlocx, tlocy).chip_id_actual) & 4)
                {
                    txt(i18n::s.get(
                        "core.locale.action.which_direction.cannot_see"));
                    continue;
                }
                snd("core.ok1");
                if (rc > 0)
                {
                    cdata.player().enemy_id = rc;
                    txt(i18n::s.get(
                        "core.locale.action.look.target", cdata[rc]));
                }
                else
                {
                    tgloc = 1;
                    tglocx = tlocx;
                    tglocy = tlocy;
                    txt(i18n::s.get("core.locale.action.look.target_ground"));
                }
            }
            else if (homemapmode == 0)
            {
                snd("core.cursor1");
            }
            scposval = 0;
            if (tlocinitx == 0 && tlocinity == 0)
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
                    "core.locale.action.equip.two_handed.fits_well", inv[cw]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.action.equip.two_handed.too_light", inv[cw]));
            }
        }
        if (cdata[cc].equipment_type & 4)
        {
            if (attacknum == 1)
            {
                if (inv[cw].weight >= 4000)
                {
                    txt(i18n::s.get(
                        "core.locale.action.equip.two_handed.too_heavy",
                        inv[cw]));
                }
            }
            else if (inv[cw].weight > 1500)
            {
                txt(i18n::s.get(
                    "core.locale.action.equip.two_handed.too_heavy_other_hand",
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
                        "core.locale.action.equip.two_handed.too_heavy_when_"
                        "riding",
                        inv[cw]));
                }
            }
        }
    }
}



TurnResult try_interact_with_npc()
{
    if (cdata[tc].continuous_action.turn != 0)
    {
        i18n::s.get("core.locale.action.npc.is_busy_now", cdata[tc]);
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
            i18n::s.get("core.locale.action.ranged.no_target");
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
    txt(i18n::s.get("core.locale.action.really_attack", cdata[tc]));
    rtval = yes_or_no(promptx, prompty, 160);
    if (rtval == 0)
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
        txt(i18n::s.get("core.locale.misc.return.forbidden"));
        if (yes_or_no(promptx, prompty, 160) == 0)
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
            auto text = mapname(i) + u8" "s
                + cnvrank(
                            (area_data[i].visited_deepest_level
                             - area_data[i].danger_level + 1))
                + i18n::s.get("core.locale.misc.dungeon_level");
            prompt.append(text);
            ++p;
        }
    }
    listmax = p;
    if (listmax == 0)
    {
        txt(i18n::s.get("core.locale.misc.return.no_location"));
        return;
    }
    txt(i18n::s.get("core.locale.misc.return.where_do_you_want_to_go"));
    display_msg(inf_screeny + inf_tiles);
    rtval = prompt.query(promptx, prompty, 240);
    update_screen();
    if (rtval >= 0)
    {
        txt(i18n::s.get("core.locale.misc.return.air_becomes_charged"));
        if (area_data[game_data.current_map].id
            == mdata_t::MapId::random_dungeon)
        {
            if (game_data.current_dungeon_level
                == area_data[game_data.current_map].deepest_level)
            {
                if (area_data[game_data.current_map].has_been_conquered != -1)
                {
                    txt(
                        i18n::s.get("core.locale.misc.return.lord_of_dungeon_"
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
    if (inv[ci].id == 413)
    {
        tmat = 40;
    }
    if (inv[ci].id == 414)
    {
        tmat = 41;
    }
    txt(i18n::s.get("core.locale.action.gatcha.prompt", matname(tmat)));
    rtval = yes_or_no(promptx, prompty, 160);
    if (rtval == 0)
    {
        if (mat(tmat) > 0)
        {
            snd("core.gasha");
            matdelmain(tmat);
            if (inv[ci].id == 413)
            {
                p = 415;
            }
            else
            {
                p = 416;
            }
            flt();
            int stat = itemcreate(
                -1, p, cdata[cc].position.x, cdata[cc].position.y, 0);
            if (stat != 0)
            {
                inv[ci].param2 = 0;
            }
            txt(i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground"));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.action.gatcha.do_not_have", matname(tmat)));
        }
    }
    return TurnResult::turn_end;
}



int read_textbook()
{
    if (inv[ci].id == 563)
    {
        if (sdata.get(inv[ci].param1, 0).original_level == 0)
        {
            txt(i18n::s.get("core.locale.action.read.book.not_interested"));
            rtval = yes_or_no(promptx, prompty, 160);
            if (rtval != 0)
            {
                return 0;
            }
        }
    }
    game_data.continuous_action_about_to_start = 104;
    continuous_action_others();
    return 1;
}



void dump_player_info()
{
    // TODO: i18n
    cc = 0;
    access_class_info(2, cdatan(3, 0));
    buff = "";
    notesel(buff);
    noteadd(latest_version.long_string());
    noteadd(
        u8"キャラクター情報 "s + game_data.date.year + u8"年"s
        + game_data.date.month + u8"月"s + game_data.date.day + u8"日 "s
        + game_data.date.hour + u8"時"s + game_data.date.minute + u8"分  "s
        + mdatan(0));
    noteadd(""s);
    noteadd(
        u8"  "s + fixtxt((""s + cdatan(1, 0) + cdatan(0, 0)), 34)
        + i18n::_(u8"ui", u8"sex", u8"_"s + cdata.player().sex) + u8" "s
        + calcage(0) + u8"歳"s + u8"  "s + cdata.player().height + u8"cm"s
        + u8" "s + cdata.player().weight + u8"kg"s);
    noteadd(""s);
    noteadd(
        fixtxt(
            u8"種族       : "s
                + i18n::s.get_m("locale.race", cdatan(2, 0), "name"),
            30)
        + fixtxt((u8"信仰      : "s + god_name(cdata.player().god_id)), 32));
    noteadd(
        fixtxt(u8"職業       : "s + classname, 30)
        + fixtxt((u8"所属      : "s + guildname()), 32));
    noteadd(
        fixtxt(u8"レベル     : "s + cdata.player().level, 30)
        + fixtxt((u8"経過日数  : "s + game_data.play_days), 32));
    noteadd(
        fixtxt(u8"残りBP     : "s + cdata.player().skill_bonus, 30)
        + fixtxt((u8"経過ターン: "s + game_data.play_turns), 32));
    noteadd(
        fixtxt(u8"金貨       : "s + cdata.player().gold, 30)
        + fixtxt((u8"殺害数    : "s + game_data.kill_count), 32));
    noteadd(
        fixtxt(u8"プラチナ   : "s + cdata.player().platinum_coin, 30)
        + fixtxt(
              (u8"最深到達  : "s + game_data.deepest_dungeon_level
               + u8"階相当"s),
              32));
    noteadd(fixtxt(
        u8"プレイ時間 : "s
            + cnvplaytime(
                  (game_data.play_time + timeGetTime() / 1000 - time_begin)),
        30));
    noteadd(""s);
    s(1) = u8"生命力    : "s + sdata(2, 0) + u8"("s
        + sdata.get(2, 0).original_level + u8")"s;
    s(2) = u8"マナ      : "s + sdata(3, 0) + u8"("s
        + sdata.get(3, 0).original_level + u8")"s;
    s(3) = u8"狂気度    : "s + cdata.player().insanity;
    s(4) = u8"速度      : "s + cdata.player().current_speed;
    s(5) = u8"名声度    : "s + cdata.player().fame;
    s(6) = u8"カルマ    : "s + cdata.player().karma;
    s(7) = u8"DV        : "s + cdata.player().dv;
    s(8) = u8"PV        : "s + cdata.player().pv;
    s(9) = "";
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        s = "";
        p = sdata.get(10 + cnt, 0).potential;
        if (p >= 200)
        {
            s += u8"superb"s;
        }
        else if (p >= 150)
        {
            s += u8"great"s;
        }
        else if (p >= 100)
        {
            s += u8"good"s;
        }
        else if (p >= 50)
        {
            s += u8"bad"s;
        }
        else
        {
            s += u8"hopeless"s;
        }
        s = fixtxt(s, 15);
        s = fixtxt(
                i18n::_(u8"ui", u8"attribute", u8"_"s + cnt) + u8"    : "s
                    + sdata((10 + cnt), 0) + u8"("s
                    + sdata.get(10 + cnt, 0).original_level + u8")"s,
                24)
            + s;
        noteadd(s + s((1 + cnt)));
    }
    noteadd(""s);
    append_accuracy_info(1);
    tc = 0;
    attackskill = 106;
    int evade = calc_evasion(tc);
    prot = calcattackdmg(2);
    noteadd(u8"回避    : "s + evade + u8"%"s);
    noteadd(
        u8"軽減    : "s + (100 - 10000 / (prot + 100)) + u8"% + "s + protdice1
        + u8"d"s + protdice2);
    noteadd(""s);
    noteadd(
        u8"------------------------------ 装備品 合計重量"s
        + cnvweight(cdata[cc].sum_of_equipment_weight) + u8" "s
        + cnveqweight(cc));
    noteadd(""s);
    listmax = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        if (cdata[cc].body_parts[cnt] != 0)
        {
            if (trait(206) != 0)
            {
                if (cdata[cc].body_parts[cnt] / 10000 == 2)
                {
                    continue;
                }
            }
            if (trait(203) != 0)
            {
                if (cdata[cc].body_parts[cnt] / 10000 == 9)
                {
                    continue;
                }
            }
            if (trait(205) != 0)
            {
                if (cdata[cc].body_parts[cnt] / 10000 == 3)
                {
                    continue;
                }
            }
            p(1) = cdata[cc].body_parts[cnt];
            q(0) = u8"装備なし"s;
            q(1) = "";
            if (p(1) % 10000 != 0)
            {
                p(1) = p(1) % 10000 - 1;
                q(0) = itemname(p(1));
                q(1) = cnvweight(inv[p(1)].weight);
                ci = p(1);
                item_dump_desc(inv[ci]);
            }
            else
            {
                listmax = 0;
            }
            s = i18n::_(
                u8"ui",
                u8"body_part",
                u8"_"s + (cdata[cc].body_parts[cnt] / 10000));
            if (strmid(s, 0, 2) == u8"　"s)
            {
                s = strmid(s, 2, 2);
            }
            noteadd(s + u8":"s);
            noteadd(q + u8" "s + q(1));
            for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
            {
                noteadd(listn(0, cnt));
            }
            noteadd(""s);
        }
    }
    noteadd(u8"------------------------------ 特徴"s);
    noteadd(""s);
    tc = 0;
    trait_load_desc();
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        if (list(0, cnt) < 0)
        {
            continue;
        }
        if (list(1, cnt) < 10000)
        {
            continue;
        }
        noteadd(listn(0, cnt));
    }
    noteadd(""s);
    noteadd(u8"------------------------------ 仲間"s);
    noteadd(""s);
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() == Character::State::empty)
        {
            continue;
        }
        if (cnt == 0)
        {
            continue;
        }
        access_class_info(2, cdatan(3, cnt));
        noteadd(
            cdatan(0, cnt) + u8" "s
            + i18n::s.get_m("locale.race", cdatan(2, cnt), "name") + u8"の"s
            + classname + u8" "s
            + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[cnt].sex) + u8" "s
            + calcage(cnt) + u8"歳"s + u8"  "s + cdata[cnt].height + u8"cm"s
            + u8" "s + cdata[cnt].weight + u8"kg"s);
        s = u8"レベル "s + cdata[cnt].level + u8" "s;
        if (cdata[cnt].is_married() == 1)
        {
            s += u8"婚約済み "s;
        }
        noteadd(s);
        noteadd(""s);
    }
    noteadd(u8"------------------------------ 称号"s);
    noteadd(""s);
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (game_data.ranks.at(cnt) < 10000)
        {
            noteadd(
                ""s + ranktitle(cnt) + u8" Rank."s
                + game_data.ranks.at(cnt) / 100);
            s = u8"給料: 約 "s + calcincome(cnt) + u8" gold  "s + u8"ノルマ: "s;
            gold += calcincome(cnt);
            if (cnt == 3 || cnt == 4 || cnt == 5 || cnt == 8)
            {
                s += u8"なし"s;
            }
            else
            {
                s += ""s + game_data.rank_deadlines.at(cnt) + u8"日以内"s;
            }
            noteadd(s);
            noteadd(""s);
        }
    }
    std::ofstream out{
        (filesystem::dir::save() / (playerid + u8".txt")).native(),
        std::ios::binary};
    out << s(0) << std::endl;
}



void remove_card_and_figures()
{
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].id == 504 || inv[cnt].id == 503)
        {
            inv[cnt].remove();
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
    for (const auto& cnt : items(-1))
    {
        inv[cnt].remove();
    }
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() == 0)
        {
            continue;
        }
        if (inv[cnt].id == 717)
        {
            lomiaseaster = 1;
        }
        if (inv[cnt].id == 511
            || the_item_db[inv[cnt].id]->subcategory == 53100)
        {
            continue;
        }
        if (inv[cnt].id == 578)
        {
            continue;
        }
        if (inv[cnt].quality == Quality::special)
        {
            continue;
        }
        if (ibit(5, cnt))
        {
            continue;
        }
        if (the_item_db[inv[cnt].id]->category == 25000)
        {
            inv[cnt].count = -1;
        }
        inv[cnt].body_part = 0;
        item_copy(cnt, inv_getfreeid(-1));
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



std::string getnpctxt(const std::string& prm_1068, const std::string& prm_1069)
{
    int p_at_m189 = 0;
    p_at_m189 = instr(txtbuff, 0, prm_1068);
    if (p_at_m189 == -1)
    {
        return prm_1069;
    }
    p_at_m189 += instr(txtbuff, p_at_m189, u8"\""s);
    if (p_at_m189 == -1)
    {
        return prm_1069;
    }
    return strmid(
        txtbuff,
        p_at_m189 + 1,
        clamp(instr(txtbuff, p_at_m189 + 1, u8"\""s), 0, 70));
}



// TODO: split
void update_save_data(const fs::path& save_dir, int serial_id)
{
    switch (serial_id)
    {
    case 0:
    {
        bool is_autodig_enabled;
        {
            int dummy_i;
            std::string dummy_s;
            std::ifstream in{(save_dir / "foobar_data.s1").native(),
                             std::ios::binary};
            putit::BinaryIArchive ar{in};
            ar.load(dummy_i);
            ar.load(dummy_i);
            ar.load(dummy_i);
            ar.load(dummy_s);
            ar.load(dummy_s);
            ar.load(dummy_s);
            ar.load(is_autodig_enabled);
        }
        {
            std::ofstream out{(save_dir / "foobar_data.s1").native(),
                              std::ios::binary};
            putit::BinaryOArchive ar{out};
            ar.save(is_autodig_enabled);
        }
        break;
    }
    case 1:
    {
        // Prepend "core." prefix to old race ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"(cdatan.*\.s[12])"}))
        {
            std::vector<std::string> lines;
            range::copy(
                fileutil::read_by_line(entry.path()),
                std::back_inserter(lines));

            // Read cdatan.
            std::vector<std::vector<std::string>> cdatan_;
            size_t idx{};
            for (const auto& line : lines)
            {
                const auto i = idx / 10;
                const auto j = idx % 10;
                if (j == 0)
                {
                    cdatan_.emplace_back(10);
                }
                cdatan_.at(i).at(j) = line;
                ++idx;
            }

            // Prepend "core." prefix to the old race ID.
            for (auto&& chara : cdatan_)
            {
                const auto old_race_id = chara.at(2);
                if (!old_race_id.empty()
                    && !strutil::starts_with(old_race_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to "
                        << chara.at(0) << ": " << old_race_id);
                    chara.at(2) = "core." + old_race_id;
                }
            }

            std::ofstream out{entry.path().native(), std::ios::binary};
            if (!out)
            {
                throw std::runtime_error(
                    u8"Error: fail to write "
                    + filesystem::make_preferred_path_in_utf8(entry.path()));
            }

            for (const auto& chara : cdatan_)
            {
                for (const auto& line : chara)
                {
                    out << line << std::endl;
                }
            }
        }
        break;
    }
    case 2:
    {
        // Prepend "core." prefix to old class ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"(cdatan.*\.s[12])"}))
        {
            std::vector<std::string> lines;
            range::copy(
                fileutil::read_by_line(entry.path()),
                std::back_inserter(lines));

            // Read cdatan.
            std::vector<std::vector<std::string>> cdatan_;
            size_t idx{};
            for (const auto& line : lines)
            {
                const auto i = idx / 10;
                const auto j = idx % 10;
                if (j == 0)
                {
                    cdatan_.emplace_back(10);
                }
                cdatan_.at(i).at(j) = line;
                ++idx;
            }

            // Prepend "core." prefix to the old class ID.
            for (auto&& chara : cdatan_)
            {
                const auto old_class_id = chara.at(3);
                if (!old_class_id.empty()
                    && !strutil::starts_with(old_class_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to "
                        << chara.at(0) << ": " << old_class_id);
                    chara.at(3) = "core." + old_class_id;
                }
            }

            std::ofstream out{entry.path().native(), std::ios::binary};
            if (!out)
            {
                throw std::runtime_error(
                    u8"Error: fail to write "
                    + filesystem::make_preferred_path_in_utf8(entry.path()));
            }

            for (const auto& chara : cdatan_)
            {
                for (const auto& line : chara)
                {
                    out << line << std::endl;
                }
            }
        }
        break;
    }
    case 3:
    {
        // Prepend "core." prefix to old class ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"((g_)?cdata(_.*)?\.s[12])"}))
        {
            // Open file.
            std::ifstream fin{entry.path().native(), std::ios::binary};
            putit::BinaryIArchive iar{fin};

            // Prepare a temporary output stream.
            // It is a string stream, but used as a memory stream here.
            // `std::stringstream` class does not convert line endings and
            // treat NUL as a terminator of string, so that it can be safely
            // used as a memory stream.
            std::ostringstream out;
            putit::BinaryOArchive oar{out};

            const auto is_cdatas1 = entry.path().filename() == "cdata.s1"
                || entry.path().filename() == "g_cdata.s1";
            const auto begin = is_cdatas1 ? 0 : ELONA_MAX_PARTY_CHARACTERS;
            const auto end =
                is_cdatas1 ? ELONA_MAX_PARTY_CHARACTERS : ELONA_MAX_CHARACTERS;
            for (int idx = begin; idx < end; ++idx)
            {
                // DO NOT use usual serialization utilities to migrate old data
                // safely because they may be changed in the future version.

                // Prepare variables.
                Position position;
                Position next_position;
                int time_to_revive = 0;
                int vision_flag = 0;
                int image = 0;
                int sex = 0;
                int relationship = 0;
                int turn_cost = 0;
                int current_speed = 0;
                int item_which_will_be_used = 0;
                int portrait = 0;
                int interest = 0;
                int time_interest_revive = 0;
                int personality = 0;
                int impression = 0;
                int talk_type = 0;
                int height = 0;
                int weight = 0;
                int birth_year = 0;
                int nutrition = 0;
                int can_talk = 0;
                Quality quality = Quality::none;
                int turn = 0;
                int id = 0;
                int vision_distance = 0;
                int enemy_id = 0;
                int gold = 0;
                int platinum_coin = 0;
                int equipment_type = 0;
                int melee_attack_type = 0;
                int fame = 0;
                int experience = 0;
                int required_experience = 0;
                int speed_percentage = 0;
                int level = 0;
                int speed_percentage_in_next_turn = 0;
                int skill_bonus = 0;
                int total_skill_bonus = 0;
                int inventory_weight = 0;
                int max_inventory_weight = 0;
                int inventory_weight_type = 0;
                int max_level = 0;
                int karma = 0;
                int hp = 0;
                int max_hp = 0;
                int sp = 0;
                int max_sp = 0;
                int mp = 0;
                int max_mp = 0;
                int heal_value_per_nether_attack = 0;
                GodId god_id;
                int piety_point = 0;
                int praying_point = 0;
                int sum_of_equipment_weight = 0;
                int special_attack_type = 0;
                int rate_to_pierce = 0;
                int rate_of_critical_hit = 0;
                int speed_correction_value = 0;
                int original_relationship = 0;
                int pv = 0;
                int dv = 0;
                int hit_bonus = 0;
                int damage_bonus = 0;
                int pv_correction_value = 0;
                int dv_correction_value = 0;
                int damage_reaction_info = 0;
                int emotion_icon = 0;
                int current_map = 0;
                int current_dungeon_level = 0;
                int related_quest_id = 0;
                int direction = 0;
                int period_of_contract = 0;
                int hire_count = 0;
                int insanity = 0;
                int curse_power = 0;
                int extra_attack = 0;
                int extra_shot = 0;
                int decrease_physical_damage = 0;
                int nullify_damage = 0;
                int cut_counterattack = 0;
                int anorexia_count = 0;
                ContinuousAction continuous_action;
                int stops_continuous_action_if_damaged = 0;
                int quality_of_performance = 0;
                int tip_gold = 0;
                int character_role = 0;
                int shop_rank = 0;
                int continuous_action_target = 0;
                int shop_store_id = 0;
                int time_to_restore = 0;
                int cnpc_id = 0;
                Position initial_position;
                int hate = 0;
                int ai_calm = 0;
                int ai_move = 0;
                int ai_dist = 0;
                int ai_act_sub_freq = 0;
                int ai_heal = 0;
                int element_of_unarmed_attack = 0;
                int poisoned = 0;
                int sleep = 0;
                int paralyzed = 0;
                int blind = 0;
                int confused = 0;
                int fear = 0;
                int dimmed = 0;
                int drunk = 0;
                int bleeding = 0;
                int wet = 0;
                int insane = 0;
                int sick = 0;
                int gravity = 0;
                int choked = 0;
                int furious = 0;

                std::vector<int> growth_buffs(10);
                std::vector<int> body_parts(30);
                std::vector<int> normal_actions;
                std::vector<int> special_actions;
                std::vector<Buff> buffs(16);
                std::vector<int> attr_adjs(10);

                int _156 = 0;
                int _203 = 0;
                int _205 = 0;
                int _206 = 0;

                Character::State state_ = Character::State::empty;

                std::bitset<sizeof(int) * 8 * 50> _flags;

                // Load character data.
                {
                    iar(state_);
                    iar(position);
                    iar(next_position);
                    iar(time_to_revive);
                    iar(vision_flag);
                    iar(image);
                    iar(sex);
                    iar(relationship);
                    iar(turn_cost);
                    iar(current_speed);
                    iar(item_which_will_be_used);
                    iar(portrait);
                    iar(interest);
                    iar(time_interest_revive);
                    iar(personality);
                    iar(impression);
                    iar(talk_type);
                    iar(height);
                    iar(weight);
                    iar(birth_year);
                    iar(nutrition);
                    iar(can_talk);
                    iar(quality);
                    iar(turn);
                    iar(id);
                    iar(vision_distance);
                    iar(enemy_id);
                    iar(gold);
                    iar(platinum_coin);
                    iar(equipment_type);
                    iar(melee_attack_type);
                    iar(fame);
                    iar(experience);
                    iar(required_experience);
                    iar(speed_percentage);
                    iar(level);
                    iar(speed_percentage_in_next_turn);
                    iar(skill_bonus);
                    iar(total_skill_bonus);
                    iar(inventory_weight);
                    iar(max_inventory_weight);
                    iar(inventory_weight_type);
                    iar(max_level);
                    iar(karma);
                    iar(hp);
                    iar(max_hp);
                    iar(sp);
                    iar(max_sp);
                    iar(mp);
                    iar(max_mp);
                    iar(heal_value_per_nether_attack);
                    iar(god_id);
                    iar(piety_point);
                    iar(praying_point);
                    iar(sum_of_equipment_weight);
                    iar(special_attack_type);
                    iar(rate_to_pierce);
                    iar(rate_of_critical_hit);
                    iar(speed_correction_value);
                    iar(original_relationship);
                    iar(pv);
                    iar(dv);
                    iar(hit_bonus);
                    iar(damage_bonus);
                    iar(pv_correction_value);
                    iar(dv_correction_value);
                    iar(damage_reaction_info);
                    iar(emotion_icon);
                    iar(current_map);
                    iar(current_dungeon_level);
                    iar(related_quest_id);
                    iar(direction);
                    iar(period_of_contract);
                    iar(hire_count);
                    iar(insanity);
                    iar(curse_power);
                    iar(extra_attack);
                    iar(extra_shot);
                    iar(decrease_physical_damage);
                    iar(nullify_damage);
                    iar(cut_counterattack);
                    iar(anorexia_count);
                    iar(continuous_action);
                    iar(stops_continuous_action_if_damaged);
                    iar(quality_of_performance);
                    iar(tip_gold);
                    iar(character_role);
                    iar(shop_rank);
                    iar(continuous_action_target);
                    iar(shop_store_id);
                    iar(time_to_restore);
                    iar(cnpc_id);
                    iar(initial_position);
                    iar(hate);
                    iar(ai_calm);
                    iar(ai_move);
                    iar(ai_dist);
                    iar(ai_act_sub_freq);
                    iar(ai_heal);
                    iar(element_of_unarmed_attack);
                    iar(poisoned);
                    iar(sleep);
                    iar(paralyzed);
                    iar(blind);
                    iar(confused);
                    iar(fear);
                    iar(dimmed);
                    iar(drunk);
                    iar(bleeding);
                    iar(wet);
                    iar(insane);
                    iar(sick);
                    iar(gravity);
                    iar(choked);
                    iar(furious);
                    range::for_each(growth_buffs, [&](auto&& growth_buff) {
                        iar(growth_buff);
                    });
                    range::for_each(
                        body_parts, [&](auto&& body_part) { iar(body_part); });
                    iar(normal_actions);
                    iar(special_actions);
                    range::for_each(buffs, [&](auto&& buff) { iar(buff); });
                    range::for_each(
                        attr_adjs, [&](auto&& attr_adj) { iar(attr_adj); });
                    iar(_flags);
                    iar(_156);
                    iar(_203);
                    iar(_205);
                    iar(_206);
                }
                // Prepend "core" prefix to old god IDs.
                if (god_id != core_god::eyth
                    && !strutil::starts_with(god_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to character("
                        << idx << "): " << god_id);
                    god_id = "core." + god_id;
                }
                // Dump character data to the memory stream.
                {
                    oar(state_);
                    oar(position);
                    oar(next_position);
                    oar(time_to_revive);
                    oar(vision_flag);
                    oar(image);
                    oar(sex);
                    oar(relationship);
                    oar(turn_cost);
                    oar(current_speed);
                    oar(item_which_will_be_used);
                    oar(portrait);
                    oar(interest);
                    oar(time_interest_revive);
                    oar(personality);
                    oar(impression);
                    oar(talk_type);
                    oar(height);
                    oar(weight);
                    oar(birth_year);
                    oar(nutrition);
                    oar(can_talk);
                    oar(quality);
                    oar(turn);
                    oar(id);
                    oar(vision_distance);
                    oar(enemy_id);
                    oar(gold);
                    oar(platinum_coin);
                    oar(equipment_type);
                    oar(melee_attack_type);
                    oar(fame);
                    oar(experience);
                    oar(required_experience);
                    oar(speed_percentage);
                    oar(level);
                    oar(speed_percentage_in_next_turn);
                    oar(skill_bonus);
                    oar(total_skill_bonus);
                    oar(inventory_weight);
                    oar(max_inventory_weight);
                    oar(inventory_weight_type);
                    oar(max_level);
                    oar(karma);
                    oar(hp);
                    oar(max_hp);
                    oar(sp);
                    oar(max_sp);
                    oar(mp);
                    oar(max_mp);
                    oar(heal_value_per_nether_attack);
                    oar(god_id);
                    oar(piety_point);
                    oar(praying_point);
                    oar(sum_of_equipment_weight);
                    oar(special_attack_type);
                    oar(rate_to_pierce);
                    oar(rate_of_critical_hit);
                    oar(speed_correction_value);
                    oar(original_relationship);
                    oar(pv);
                    oar(dv);
                    oar(hit_bonus);
                    oar(damage_bonus);
                    oar(pv_correction_value);
                    oar(dv_correction_value);
                    oar(damage_reaction_info);
                    oar(emotion_icon);
                    oar(current_map);
                    oar(current_dungeon_level);
                    oar(related_quest_id);
                    oar(direction);
                    oar(period_of_contract);
                    oar(hire_count);
                    oar(insanity);
                    oar(curse_power);
                    oar(extra_attack);
                    oar(extra_shot);
                    oar(decrease_physical_damage);
                    oar(nullify_damage);
                    oar(cut_counterattack);
                    oar(anorexia_count);
                    oar(continuous_action);
                    oar(stops_continuous_action_if_damaged);
                    oar(quality_of_performance);
                    oar(tip_gold);
                    oar(character_role);
                    oar(shop_rank);
                    oar(continuous_action_target);
                    oar(shop_store_id);
                    oar(time_to_restore);
                    oar(cnpc_id);
                    oar(initial_position);
                    oar(hate);
                    oar(ai_calm);
                    oar(ai_move);
                    oar(ai_dist);
                    oar(ai_act_sub_freq);
                    oar(ai_heal);
                    oar(element_of_unarmed_attack);
                    oar(poisoned);
                    oar(sleep);
                    oar(paralyzed);
                    oar(blind);
                    oar(confused);
                    oar(fear);
                    oar(dimmed);
                    oar(drunk);
                    oar(bleeding);
                    oar(wet);
                    oar(insane);
                    oar(sick);
                    oar(gravity);
                    oar(choked);
                    oar(furious);
                    range::for_each(growth_buffs, [&](auto&& growth_buff) {
                        oar(growth_buff);
                    });
                    range::for_each(
                        body_parts, [&](auto&& body_part) { oar(body_part); });
                    oar(normal_actions);
                    oar(special_actions);
                    range::for_each(buffs, [&](auto&& buff) { oar(buff); });
                    range::for_each(
                        attr_adjs, [&](auto&& attr_adj) { oar(attr_adj); });
                    oar(_flags);
                    oar(_156);
                    oar(_203);
                    oar(_205);
                    oar(_206);
                }
            }

            // Close the file and reopen to write.
            fin.close();
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
        break;
    }
    case 4:
    {
        // Replace double bed and happy bed's image.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"((g_)?inv(_.*)?\.s[12])"}))
        {
            // Open file.
            std::ifstream fin{entry.path().native(), std::ios::binary};
            putit::BinaryIArchive iar{fin};

            // Prepare a temporary output stream.
            // It is a string stream, but used as a memory stream here.
            // `std::stringstream` class does not convert line endings and
            // treat NUL as a terminator of string, so that it can be safely
            // used as a memory stream.
            std::ostringstream out;
            putit::BinaryOArchive oar{out};

            const auto is_invs1 = entry.path().filename() == "inv.s1"
                || entry.path().filename() == "g_inv.s1";
            const auto begin = is_invs1 ? 0 : 1320;
            const auto end = is_invs1 ? 1320 : 5480;
            for (int idx = begin; idx < end; ++idx)
            {
                // DO NOT use usual serialization utilities to migrate old data
                // safely because they may be changed in the future version.

                // Prepare variables.
                int number_ = 0;
                int value = 0;
                int image = 0;
                int id = 0;
                Quality quality = Quality::none;
                Position position;
                int weight = 0;
                IdentifyState identification_state =
                    IdentifyState::unidentified;
                int count = 0;
                int dice_x = 0;
                int dice_y = 0;
                int damage_bonus = 0;
                int hit_bonus = 0;
                int dv = 0;
                int pv = 0;
                int skill = 0;
                CurseState curse_state = CurseState::none;
                int body_part = 0;
                int function = 0;
                int enhancement = 0;
                int own_state = 0;
                int color = 0;
                int subname = 0;
                int material = 0;
                int param1 = 0;
                int param2 = 0;
                int param3 = 0;
                int param4 = 0;
                int difficulty_of_identification = 0;
                int turn = 0;

                int flags = 0;

                std::vector<Enchantment> enchantments(15);

                // Load item data.
                {
                    iar(number_);
                    iar(value);
                    iar(image);
                    iar(id);
                    iar(quality);
                    iar(position);
                    iar(weight);
                    iar(identification_state);
                    iar(count);
                    iar(dice_x);
                    iar(dice_y);
                    iar(damage_bonus);
                    iar(hit_bonus);
                    iar(dv);
                    iar(pv);
                    iar(skill);
                    iar(curse_state);
                    iar(body_part);
                    iar(function);
                    iar(enhancement);
                    iar(own_state);
                    iar(color);
                    iar(subname);
                    iar(material);
                    iar(param1);
                    iar(param2);
                    iar(param3);
                    iar(param4);
                    iar(difficulty_of_identification);
                    iar(turn);
                    iar(flags);
                    range::for_each(enchantments, [&](auto&& enchantment) {
                        iar(enchantment);
                    });
                }
                // Prepend "core" prefix to old god IDs.
                if (image == 649)
                {
                    ELONA_LOG("[Save data] Change item chip 649 to 261.");
                    image = 261;
                }
                // Dump item data to the memory stream.
                {
                    oar(number_);
                    oar(value);
                    oar(image);
                    oar(id);
                    oar(quality);
                    oar(position);
                    oar(weight);
                    oar(identification_state);
                    oar(count);
                    oar(dice_x);
                    oar(dice_y);
                    oar(damage_bonus);
                    oar(hit_bonus);
                    oar(dv);
                    oar(pv);
                    oar(skill);
                    oar(curse_state);
                    oar(body_part);
                    oar(function);
                    oar(enhancement);
                    oar(own_state);
                    oar(color);
                    oar(subname);
                    oar(material);
                    oar(param1);
                    oar(param2);
                    oar(param3);
                    oar(param4);
                    oar(difficulty_of_identification);
                    oar(turn);
                    oar(flags);
                    range::for_each(enchantments, [&](auto&& enchantment) {
                        oar(enchantment);
                    });
                }
            }

            // Close the file and reopen to write.
            fin.close();
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
        break;
    }
    default: break;
    }
}



void update_save_data(const fs::path& save_dir)
{
    const auto version_filepath = save_dir / "version.s0";

    Version version;
    putit::BinaryIArchive::load(version_filepath, version);

    if (version.serial_id > latest_version.serial_id)
    {
        // FIXME:
        // It is far away from the best solution, but we do not have the way to
        // report a fatal error to end-users by GUI window, except for
        // OS-builtin exception handling.
        throw std::runtime_error{"Incompatible save data!"};
    }

    for (int serial_id = version.serial_id;
         serial_id != latest_version.serial_id;
         ++serial_id)
    {
        ELONA_LOG(
            "[Save data] Update save data from #" << serial_id << " to #"
                                                  << (serial_id + 1) << ".");
        update_save_data(save_dir, serial_id);
    }
    version = latest_version;
    putit::BinaryOArchive::save(version_filepath, version);
}



void load_save_data()
{
    ELONA_LOG("Load save data: " << playerid);

    // TODO instead serialize/deserialize data
    lua::lua->get_handle_manager().clear_map_local_handles();

    Save::instance().clear();
    writeloadedbuff_clear();

    ctrl_file(FileOperation::temp_dir_delete);
    const auto save_dir = filesystem::dir::save(playerid);

    // TODO: Delete this line when the v1.0.0 stable is released!
    if (!fs::exists(save_dir / "version.s0"))
    {
        if (!fs::exists(save_dir / "foobar_data.s1"))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        int major;
        int minor;
        int patch;
        {
            std::ifstream in{(save_dir / "foobar_data.s1").native(),
                             std::ios::binary};
            putit::BinaryIArchive ar{in};
            ar.load(major);
            ar.load(minor);
            ar.load(patch);
        }

        if (!(major == 0 && minor == 2 && patch == 7))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        Version v028 = {0, 2, 8, 0, "", "", ""};
        putit::BinaryOArchive::save(save_dir / "version.s0", v028);
    }

    update_save_data(save_dir);
    ctrl_file(FileOperation2::global_read, save_dir);

    chara_delete(56);
    set_item_info();
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].has_own_sprite() == 1 || cnt == 0)
        {
            create_pcpic(cnt, true);
        }
    }
    if (game_data.wizard == 1)
    {
        cdatan(1, 0) = u8"*Debug*"s;
    }
    refresh_speed(cdata.player());
    time_begin = timeGetTime() / 1000;
    ELONA_LOG("Load save data end: " << playerid);
}



void do_save_game()
{
    snd("core.write1");
    save_game();
    txt(i18n::s.get("core.locale.ui.save"), Message::color{ColorIndex::orange});
}



void save_game()
{
    ELONA_LOG("Save game: " << playerid);

    int save_f = 0;
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.locale.misc.save.cannot_save_in_user_map"),
            Message::color{ColorIndex::red});
        update_screen();
        return;
    }
    ctrl_file(FileOperation::map_write);
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
    save_f = 0;
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::save(), filesystem::DirEntryRange::Type::dir))
    {
        if (filesystem::to_utf8_path(entry.path().filename()) == playerid)
        {
            save_f = 1;
            break;
        }
    }
    const auto save_dir = filesystem::dir::save(playerid);
    if (save_f == 0)
    {
        fs::create_directory(save_dir);
    }
    Save::instance().save(save_dir);
    ctrl_file(FileOperation2::global_write, save_dir);
    Save::instance().clear();
    ELONA_LOG("Save game: finish");
}



TurnResult do_enter_strange_gate()
{
    snd("core.exitmap1");
    game_data.previous_map2 = game_data.current_map;
    game_data.previous_dungeon_level = game_data.current_dungeon_level;
    game_data.previous_x = cdata.player().position.x;
    game_data.previous_y = cdata.player().position.y;
    game_data.destination_map = 35;
    game_data.destination_dungeon_level = 1;
    levelexitby = 2;
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
    pos(0, 0);
    gcopy(0, x, y, 144, 144);
    gsel(0);
    t = 0;
label_2128_internal:
    ++t;
    gmode(4, 200 - t / 2 % 20 * (t / 2 % 20));
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
    pos(x - 48 - 24, y - 48 - 24);
    gcopy(4, 0, 0, 144, 144);
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
            goto label_2128_internal;
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
            goto label_2128_internal;
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
            goto label_2128_internal;
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
            goto label_2128_internal;
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
        if (x == cdata.player().position.x && y == cdata.player().position.y)
        {
            return 0;
        }
        tlocx = x;
        tlocy = y;
        keyhalt = 1;
        return 1;
    }
    goto label_2128_internal;
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
        txt(i18n::s.get("core.locale.action.move.trap.disarm.dismantle"));
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
        txt(i18n::s.get("core.locale.action.move.trap.disarm.succeed"));
    }
}



void proc_trap()
{
label_21451_internal:
    if (Config::instance().scroll)
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
                if ((cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                    || cdata[cc].is_immune_to_mine() == 1)
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
                                "core.locale.action.move.trap.disarm.fail"));
                        }
                    }
                }
            }
            int stat = can_evade_trap();
            if (stat == 1)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.locale.action.move.trap.evade", cdata[cc]));
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
                        "core.locale.action.move.trap.activate.text",
                        cdata[cc]));
                }
                if (feat(2) == 4)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.action.move.trap.activate.blind"));
                    }
                    dmgcon(
                        cc,
                        StatusAilment::blinded,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 6)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.action.move.trap.activate.paralyze"));
                    }
                    dmgcon(
                        cc,
                        StatusAilment::paralyzed,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 5)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.action.move.trap.activate.confuse"));
                    }
                    dmgcon(
                        cc,
                        StatusAilment::confused,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 3)
                {
                    cell_featset(movx, movy, 0);
                    if (encfind(cc, 22) != -1)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                "core.locale.magic.teleport.prevented"));
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
                                    "core.locale.magic.teleport.disappears",
                                    cdata[cc]));
                            }
                            cdata[cc].continuous_action.finish();
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
                            i18n::s.get("core.locale.action.move.trap.activate."
                                        "spears.text"));
                    }
                    if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                "core.locale.action.move.trap.activate.spears."
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
                            "core.locale.action.move.trap.activate.poison"));
                    }
                    dmgcon(
                        cc,
                        StatusAilment::poisoned,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 2)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.action.move.trap.activate.sleep"));
                    }
                    dmgcon(
                        cc,
                        StatusAilment::sleep,
                        100 + game_data.current_dungeon_level * 2);
                }
                if (feat(2) == 7)
                {
                    txt(i18n::s.get(
                            "core.locale.action.move.trap.activate.mine"),
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
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh - inf_verh);
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
    gsel(4);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"bg_night.bmp", 1);
    pos(0, 0);
    gcopy(4, 0, 0, 640, 480, windoww, windowh - inf_verh);
    gsel(0);
}



void sleep_start()
{
    int timeslept = 0;
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        txt(i18n::s.get("core.locale.activity.sleep.but_you_cannot"));
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
        gmode(4, cnt * 10);
        draw_sleep_background_frame();
        await(Config::instance().animewait * 10);
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
        healcon(tc, StatusAilment::sick, 7 + rnd(7));
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
        await(Config::instance().animewait * 25);
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
                i18n::s.get("core.locale.activity.sleep.new_gene.title"),
                i18n::s.get(
                    "core.locale.activity.sleep.new_gene.text", cdata[tc]),
                {i18n::s.get_enum(
                    "core.locale.activity.sleep.new_gene.choices", 0)},
                u8"bg_re14");
            save_gene();
        }
    }
    draw_sleep_background_frame();
    game_data.character_and_status_for_gene = 0;
    mode = 0;
    wake_up();
    cdata[cc].nutrition -= 1500 / (trait(158) + 1);
    txt(i18n::s.get("core.locale.activity.sleep.slept_for", timeslept),
        Message::color{ColorIndex::green});
    f = 0;
    if (cdata.player().continuous_action.item == -1)
    {
        f = 1;
    }
    else
    {
        ci = cdata.player().continuous_action.item;
        if (inv[ci].param1 == 0 || inv[ci].number() == 0
            || the_item_db[inv[ci].id]->subcategory != 60004)
        {
            f = 1;
        }
    }
    if (f)
    {
        txt(i18n::s.get("core.locale.activity.sleep.wake_up.so_so"));
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
        txt(i18n::s.get("core.locale.activity.sleep.wake_up.good", grown),
            Message::color{ColorIndex::green});
    }
    msg_halt();
    play_music();
    autosave = 1 * (game_data.current_map != mdata_t::MapId::show_house);
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        update_shop();
    }
}



void do_rest()
{
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::sleep;
        cdata[cc].continuous_action.turn = 50;
        txt(i18n::s.get("core.locale.activity.rest.start"));
        update_screen();
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (cdata[cc].continuous_action.turn % 2 == 0)
        {
            heal_sp(cdata[cc], 1);
        }
        if (cdata[cc].continuous_action.turn % 3 == 0)
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
            txt(i18n::s.get("core.locale.activity.rest.drop_off_to_sleep"));
            cdata[cc].continuous_action.item = -1;
            sleep_start();
            cdata[cc].continuous_action.finish();
            return;
        }
    }
    txt(i18n::s.get("core.locale.activity.rest.finish"));
    cdata[cc].continuous_action.finish();
}



void map_global_proc_travel_events()
{
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::travel;
        cdata[cc].continuous_action.turn = 20;
        if (game_data.weather == 3)
        {
            cdata[cc].continuous_action.turn =
                cdata[cc].continuous_action.turn * 13 / 10;
        }
        if (game_data.weather == 4)
        {
            cdata[cc].continuous_action.turn =
                cdata[cc].continuous_action.turn * 16 / 10;
        }
        if (game_data.weather == 2
            || chipm(
                   0,
                   cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                       .chip_id_actual)
                == 4)
        {
            cdata[cc].continuous_action.turn =
                cdata[cc].continuous_action.turn * 22 / 10;
        }
        if (game_data.weather == 1)
        {
            cdata[cc].continuous_action.turn =
                cdata[cc].continuous_action.turn * 5 / 10;
        }
        cdata[cc].continuous_action.turn = cdata[cc].continuous_action.turn
            * 100 / (100 + game_data.seven_league_boot_effect + sdata(182, 0));
        return;
    }
    if (cdata.player().nutrition <= 5000)
    {
        f = 0;
        for (const auto& cnt : items(cc))
        {
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (the_item_db[inv[cnt].id]->category == 91000)
            {
                f = 1;
                ci = cnt;
                break;
            }
        }
        if (f == 1)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.misc.finished_eating", cdata[cc], inv[ci]));
            }
            continuous_action_eating_finish();
        }
    }
    if (game_data.weather == 2
        || chipm(
               0,
               cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                   .chip_id_actual)
            == 4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0
                    || cdata.player().gravity > 0)
                {
                    txt(i18n::s.get("core.locale.action.move.global.weather."
                                    "snow.sound"),
                        Message::color{ColorIndex::cyan});
                    cdata[cc].continuous_action.turn += 10;
                }
            }
            if (rnd(1000) == 0)
            {
                txt(i18n::s.get(
                        "core.locale.action.move.global.weather.snow.message"),
                    Message::color{ColorIndex::purple});
                cdata[cc].continuous_action.turn += 50;
            }
        }
        if (cdata.player().nutrition <= 2000)
        {
            if (cdata.player().has_anorexia() == 0)
            {
                snd("core.eat1");
                txt(i18n::s.get(
                    "core.locale.action.move.global.weather.snow.eat"));
                cdata[cc].nutrition += 5000;
                show_eating_message();
                dmgcon(0, StatusAilment::dimmed, 1000);
            }
        }
    }
    if (game_data.weather == 4)
    {
        if (game_data.protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata.player().is_floating() == 0
                    || cdata.player().gravity > 0)
                {
                    txt(i18n::s.get(
                            "core.locale.action.move.global.weather.heavy_rain."
                            "sound"),
                        Message::color{ColorIndex::cyan});
                    cdata[cc].continuous_action.turn += 5;
                }
            }
            if (cdata.player().confused == 0)
            {
                if (rnd(500) == 0)
                {
                    txt(i18n::s.get(
                            "core.locale.action.move.global.weather.heavy_rain."
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
    if (cdata[cc].continuous_action.turn > 0)
    {
        ++game_data.date.minute;
        return;
    }
    traveldone = 1;
    game_data.distance_between_town += 4;
    cdata[cc].continuous_action.finish();
}


int decode_book()
{
    int cibkread = 0;
    if (!cdata[cc].continuous_action)
    {
        if (inv[ci].id == 687)
        {
            if (inv[ci].param2 != 0)
            {
                txt(i18n::s.get(
                    "core.locale.action.read.book.already_decoded"));
                return 0;
            }
        }
        if (cdata[cc].blind != 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.action.read.cannot_see", cdata[cc]));
            }
            return 0;
        }
        cdata[cc].continuous_action.type = ContinuousAction::Type::read;
        if (inv[ci].id == 783)
        {
            p = 50;
        }
        else if (inv[ci].id == 687)
        {
            p = 50 + inv[ci].param1 * 50 + inv[ci].param1 * inv[ci].param1 * 20;
        }
        else
        {
            p = the_ability_db[efid]->difficulty;
        }
        cdata[cc].continuous_action.turn = p / (2 + sdata(150, 0)) + 1;
        cdata[cc].continuous_action.item = ci;
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.activity.read.start", cdata[cc], inv[ci]));
        }
        item_separate(ci);
        return 0;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        ci = cdata[cc].continuous_action.item;
        cibkread = ci;
        gain_literacy_experience();
        if (inv[ci].id == 783)
        {
            return 0;
        }
        if (inv[ci].id == 687)
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
            cdata[cc].continuous_action.finish();
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
                        "core.locale.action.read.book.falls_apart", inv[ci]));
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get(
            "core.locale.activity.read.finish", cdata[cc], inv[ci]));
    }
    if (inv[ci].id == 783)
    {
        if (inv[ci].param1 == 0)
        {
            cdata[cc].continuous_action.finish();
            return 1;
        }
        txt(i18n::s.get("core.locale.action.read.recipe.learned", inv[ci]));
        ++recipememory(inv[ci].subname);
        item_identify(inv[ci], IdentifyState::partly_identified);
        inv[ci].modify_number(-1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.action.read.book.falls_apart", inv[ci]));
        }
        cdata[cc].continuous_action.finish();
        return 1;
    }
    if (inv[ci].id == 687)
    {
        item_identify(inv[ci], IdentifyState::completely_identified);
        txt(i18n::s.get(
            "core.locale.action.read.book.finished_decoding", inv[ci]));
        inv[ci].param2 = 1;
        inv[ci].count = 1;
        ibitmod(4, ci, 0);
        item_stack(0, ci, 1);
    }
    else
    {
        chara_gain_skill(
            cdata[cc],
            efid,
            1,
            (rnd(51) + 50) * (90 + sdata(165, cc) + (sdata(165, cc) > 0) * 20)
                    / clamp((100 + spell((efid - 400)) / 2), 50, 1000)
                + 1);
        gain_memorization_experience(0);
        if (itemmemory(2, inv[ci].id) == 0)
        {
            itemmemory(2, inv[ci].id) = 1;
        }
    }
    item_identify(inv[ci], IdentifyState::partly_identified);
    if (inv[ci].id != 687)
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
                txt(i18n::s.get(
                    "core.locale.action.read.book.falls_apart", inv[ci]));
            }
        }
    }
    cdata[cc].continuous_action.finish();
    return 1;
}



int read_normal_book()
{
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.action.read.cannot_see", cdata[cc]));
        }
        return 0;
    }
    if (inv[ci].id == 742)
    {
        snd("core.book1");
        txt(i18n::s.get("core.locale.action.read.book.void_permit"));
        return 1;
    }
    if (inv[ci].id == 563)
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
    if (inv[ci].id == 668)
    {
        snd("core.book1");
        txt(i18n::s.get("core.locale.action.read.book.book_of_rachel"));
        return 1;
    }
    tc = cc;
    item_identify(inv[ci], IdentifyState::partly_identified);
    show_book_window();
    return 1;
}



int calcmagiccontrol(int prm_1076, int prm_1077)
{
    if (sdata(188, prm_1076) != 0)
    {
        if (belong_to_same_team(cdata[prm_1076], cdata[prm_1077]))
        {
            if (sdata(188, prm_1076) * 5 > rnd(dmg + 1))
            {
                dmg = 0;
            }
            else
            {
                dmg = rnd(dmg * 100 / (100 + sdata(188, prm_1076) * 10) + 1);
            }
            if (dmg < 1)
            {
                if (is_in_fov(cdata[prm_1077]))
                {
                    txt(i18n::s.get(
                        "core.locale.misc.spell_passes_through",
                        cdata[prm_1077]));
                }
                chara_gain_skill_exp(cdata[prm_1076], 188, 8, 4);
                return 1;
            }
            chara_gain_skill_exp(cdata[prm_1076], 188, 30, 2);
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
        gain_casting_experience(cc, spellbk);
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
            if (!Config::instance().skip_overcasting_warning)
            {
                txt(i18n::s.get("core.locale.action.cast.overcast_warning"));
                rtval = yes_or_no(promptx, prompty, 160);
                if (rtval != 0)
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
            if (cdata[cc].relationship == 10
                || game_data.current_map == mdata_t::MapId::pet_arena)
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
            txt(i18n::s.get("core.locale.action.cast.confused", cdata[cc]));
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
                "core.locale.action.cast.self",
                cdata[cc],
                i18n::s.get_m(
                    "locale.ability",
                    the_ability_db.get_id_from_legacy(efid)->get(),
                    "name"),
                i18n::_(
                    u8"ui",
                    u8"cast_style",
                    u8"_"s + cdata[cc].special_attack_type)));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.action.cast.other",
                cdata[cc],
                i18n::_(
                    u8"ui",
                    u8"cast_style",
                    u8"_"s + cdata[cc].special_attack_type)));
        }
    }
    if (buff_has(cdata[cc], "core.mist_of_silence"))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.action.cast.silenced"));
        }
        efsource = 0;
        return 1;
    }
    if (rnd(100) >= calcspellfail(efid, cc))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.action.cast.fail", cdata[cc]));
            FailureToCastAnimation(cdata[cc].position).play();
        }
        efsource = 0;
        return 1;
    }
    if (noeffect == 1)
    {
        txt(i18n::s.get("core.locale.common.nothing_happens"));
        efsource = 0;
        return 1;
    }
    efp = calcspellpower(efid, cc);
    p = encfind(cc, 34);
    if (p != -1)
    {
        efp = efp * (100 + p / 10) / 100;
    }
    rapidmagic = 0;
    if (cdata[cc].can_cast_rapid_magic()
        && the_ability_db[efid]->ability_type == 2)
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
            txt(i18n::s.get(
                "core.locale.action.drink.potion", cdata[tc], inv[ci]));
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
                item_identify(inv[ci], IdentifyState::partly_identified);
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
    if (inv[ci].param1 < -5 || inv[ci].param3 >= 20
        || (inv[ci].id == 602 && game_data.holy_well_count <= 0))
    {
        const auto valn = itemname(ci);
        txt(i18n::s.get("core.locale.action.drink.well.is_dry", valn));
        return 1;
    }
    snd_at("core.drink1", cdata[cc].position);
    const auto valn = itemname(ci);
    txt(i18n::s.get("core.locale.action.drink.well.draw", cdata[cc], valn));
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
                    "core.locale.action.drink.well.effect.falls.text",
                    cdata[cc]));
                txt(i18n::s.get(
                        "core.locale.action.drink.well.effect.falls.dialog",
                        cdata[cc]),
                    Message::color{ColorIndex::cyan});
                if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                {
                    txt(i18n::s.get(
                        "core.locale.action.drink.well.effect.falls.floats",
                        cdata[cc]));
                }
                else
                {
                    damage_hp(cdata[cc], 9999, -1);
                }
                break;
            }
        }
        if (inv[ci].id == 602)
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
                "core.locale.action.drink.well.effect.finds_gold", cdata[cc]));
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
                    "core.locale.action.drink.well.effect.pregnancy",
                    cdata[cc]));
            }
            tc = cc;
            get_pregnant();
            break;
        }
        if (p > 35)
        {
            txt(i18n::s.get("core.locale.action.drink.well.effect.monster"));
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
                txt(i18n::s.get("core.locale.action.drink.well.effect.wish_too_"
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
            txt(i18n::s.get("core.locale.action.drink.well.effect.default"));
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
    if (inv[ci].id == 602)
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
                "core.locale.action.drink.well.completely_dried_up", inv[ci]));
            return 1;
        }
    }
    if (inv[ci].param1 < -5)
    {
        txt(i18n::s.get("core.locale.action.drink.well.dried_up", inv[ci]));
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
            txt(i18n::s.get("core.locale.action.read.cannot_see", cdata[cc]));
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
                    "core.locale.action.read.scroll.dimmed_or_confused",
                    cdata[cc]));
            }
            efsource = 0;
            return 0;
        }
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get(
            "core.locale.action.read.scroll.execute", cdata[cc], inv[ci]));
    }
    if (inv[ci].id != 621)
    {
        inv[ci].modify_number(-1);
        chara_gain_skill_exp(cdata[cc], 150, 25, 2);
    }
    magic();
    if (cc == 0)
    {
        if (obvious == 1)
        {
            item_identify(inv[ci], IdentifyState::partly_identified);
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
            txt(i18n::s.get("core.locale.action.zap.execute", inv[ci]));
            txt(i18n::s.get("core.locale.common.nothing_happens"));
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
        if ((stat == 0 && the_ability_db[efid]->range / 1000 * 1000 == 2000)
            || noeffect == 1)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.locale.action.zap.execute", inv[ci]));
                txt(i18n::s.get("core.locale.common.nothing_happens"));
            }
            goto label_2173_internal;
        }
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.locale.action.zap.execute", inv[ci]));
    }
    efp = efp
        * (100 + sdata(174, cc) * 10 + sdata(16, cc) / 2 + sdata(13, cc) / 2)
        / 100;
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
    if (f == 1 || inv[ci].id == 290 || cc != 0)
    {
        magic();
        if (cc == 0)
        {
            if (obvious == 1)
            {
                item_identify(inv[ci], IdentifyState::partly_identified);
            }
        }
        gain_magic_device_experience(cc);
    }
    else if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.locale.action.zap.fail", cdata[cc]));
    }
label_2173_internal:
    efsource = 0;
    if (inv[ci].number() == 0)
    {
        if (ci >= 5080)
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
    if (the_ability_db[efid]->range / 1000 * 1000 != 3000
        && the_ability_db[efid]->range / 1000 * 1000 != 10000)
    {
        if (cdata[cc].confused != 0 || cdata[cc].blind != 0)
        {
            if (rnd(5) == 0)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.locale.misc.shakes_head"));
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
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    return 1;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
            chara_gain_skill_exp(
                cdata[cc], the_ability_db[efid]->related_basic_attribute, 25);
        }
    }
    efp = calcspellpower(efid, cc);
    if (noeffect == 1)
    {
        if (efid != 300)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
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
            txt(i18n::s.get("core.locale.action.which_direction.ask"));
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
                    cdata[cc].position.y)
                > the_ability_db[efid]->range % 1000 + 1)
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
                                   tglocy)
                        == 0)
                {
                    if (stat == 0)
                    {
                        txt(
                            i18n::s.get("core.locale.action.which_direction."
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
                            i18n::s.get("core.locale.action.which_direction."
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
                    cdata[cc].position.y)
                == 0)
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
                        cdata[cc].position.y)
                    > the_ability_db[efid]->range % 1000 + 1)
                {
                    return 0;
                }
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y)
                    == 0)
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
                cdata[cc].position.y)
            > the_ability_db[efid]->range % 1000 + 1)
        {
            if (cc == 0)
            {
                txt(i18n::s.get(
                        "core.locale.action.which_direction.out_of_range"),
                    Message::only_once{true});
                update_screen();
            }
            return 0;
        }
        if (fov_los(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[tc].position.x,
                cdata[tc].position.y)
            == 0)
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
                txt(i18n::s.get("core.locale.action.which_direction.spell"));
            }
            else
            {
                txt(i18n::s.get("core.locale.action.which_direction.wand"));
            }
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(i18n::s.get("core.locale.common.it_is_impossible"));
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
        healcon(tc(cnt), StatusAilment::fear);
        healcon(tc(cnt), StatusAilment::poisoned, 50);
        healcon(tc(cnt), StatusAilment::confused, 50);
        healcon(tc(cnt), StatusAilment::dimmed, 30);
        healcon(tc(cnt), StatusAilment::bleeding, 20);
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



int pick_up_item()
{
    int sellgold = 0;
    if (cc != -1)
    {
        if (inv[ci].id == 54 || inv[ci].id == 55)
        {
            snd("core.getgold1");
            ti = ci;
            in = inv[ci].number();
            inv[ci].remove();
            msgkeep = 1;
            txt(i18n::s.get(
                "core.locale.action.pick_up.execute",
                cdata[cc],
                itemname(ti, in)));
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            if (inv[ci].id == 54)
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
            if (cdata[game_data.mount].continuous_action)
            {
                if (cdata[game_data.mount].continuous_action.item == ci)
                {
                    txt(i18n::s.get(
                        "core.locale.action.pick_up.used_by_mount",
                        cdata[game_data.mount]));
                    return 1;
                }
            }
        }
        if (the_item_db[inv[ci].id]->category == 57000)
        {
            if (inv[ci].own_state == 4)
            {
                if (!cdata.player().continuous_action)
                {
                    if (!inv_getspace(0))
                    {
                        txt(i18n::s.get(
                            "core.locale.ui.inv.common.inventory_is_full"));
                        return 0;
                    }
                    game_data.continuous_action_about_to_start = 103;
                    continuous_action_others();
                    return -1;
                }
            }
        }
        if (inv[ci].own_state == 3)
        {
            txt(i18n::s.get(
                "core.locale.action.pick_up.do_you_want_to_remove", inv[ci]));
            rtval = yes_or_no(promptx, prompty, 160);
            if (rtval == 0)
            {
                snd("core.build1");
                if (inv[ci].id == 555)
                {
                    std::string midbk = mid;
                    mid = ""s + 30 + u8"_"s + (100 + inv[ci].count);
                    tmpload(filesystem::u8path(u8"mdata_"s + mid + u8".s2"));
                    if (fs::exists(
                            filesystem::dir::tmp()
                            / (u8"mdata_"s + mid + u8".s2")))
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
            txt(i18n::s.get(
                "core.locale.action.pick_up.your_inventory_is_full"));
            return 0;
        }
    }
    inumbk = inv[ci].number() - in;
    inv[ci].set_number(in);
    if (cc == 0)
    {
        if (trait(215) != 0)
        {
            if (the_item_db[inv[ci].id]->category == 56000)
            {
                if (inv[ci].count > 0)
                {
                    dbid = inv[ci].id;
                    access_item_db(14);
                    txt(i18n::s.get(
                        "core.locale.action.pick_up.you_absorb_magic",
                        inv[ci]));
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
            if (the_item_db[inv[ci].id]->category == 52000)
            {
                if (inv[ci].id != 262 && inv[ci].id != 559)
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get(
                            "core.locale.action.pick_up.poison_drips"));
                        inv[ci].id = 262;
                    }
                }
            }
        }
    }
    if (inv[ci].own_state < 0)
    {
        inv[ci].own_state = 0;
    }
    ibitmod(12, ci, 0);
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
                    i18n::s.get("core.locale.action.pick_up.shopkeepers_"
                                "inventory_is_full"));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.action.pick_up.your_inventory_is_full"));
            }
            return 0;
        }
        item_copy(ci, ti);
        inv[ti].set_number(in);
    }
    inv[ci].set_number(inumbk);
    if (mode == 6)
    {
        if (the_item_db[inv[ti].id]->category == 57000)
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
                    inv[ti].param3 = game_data.date.hours()
                        + the_item_db[inv[ti].id]->expiration_date;
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
            msgkeep = 1;
            txt(i18n::s.get(
                "core.locale.action.pick_up.you_buy", itemname(ti, in)));
            sellgold = calcitemvalue(ti, 0) * in;
            snd("core.paygold1");
            cdata.player().gold -= sellgold;
            earn_gold(cdata[tc], sellgold);
            if (the_item_db[inv[ti].id]->category == 92000)
            {
                inv[ti].param2 = calcitemvalue(ti, 0);
            }
        }
        if (invctrl == 12)
        {
            msgkeep = 1;
            sellgold = calcitemvalue(ci, 1) * in;
            if (ibit(9, ti) == 0)
            {
                txt(i18n::s.get(
                    "core.locale.action.pick_up.you_sell", itemname(ti, in)));
            }
            else
            {
                ibitmod(9, ti, 0);
                txt(i18n::s.get(
                    "core.locale.action.pick_up.you_sell_stolen",
                    itemname(ti, in)));
                if (game_data.guild.thieves_guild_quota > 0)
                {
                    game_data.guild.thieves_guild_quota -= sellgold;
                    if (game_data.guild.thieves_guild_quota < 0)
                    {
                        game_data.guild.thieves_guild_quota = 0;
                    }
                    txt(i18n::s.get(
                        "core.locale.action.pick_up.thieves_guild_quota",
                        game_data.guild.thieves_guild_quota));
                }
            }
            snd("core.getgold1");
            earn_gold(cdata.player(), sellgold);
            cdata[tc].gold -= sellgold;
            if (cdata[tc].gold < 0)
            {
                cdata[tc].gold = 0;
            }
            inv[ti].identification_state = IdentifyState::completely_identified;
        }
        if (invctrl == 22 || invctrl == 24)
        {
            sound_pick_up();
            msgkeep = 1;
            if (invctrl == 22)
            {
                txt(i18n::s.get(
                    "core.locale.action.pick_up.execute",
                    cdata[cc],
                    itemname(ti, in)));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.action.pick_up.put_in_container",
                    itemname(ti, in)));
            }
        }
        else
        {
            gain_negotiation_experience(0, sellgold);
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
        msgkeep = 1;
        txt(i18n::s.get(
            "core.locale.action.pick_up.execute", cdata[cc], itemname(ti, in)));
    }
    if (cc == 0)
    {
        if (inv[ti].id == 255)
        {
            if (map_data.play_campfire_sound == 1)
            {
                f = 0;
                for (const auto& cnt : items(-1))
                {
                    if (inv[cnt].number() == 0)
                    {
                        continue;
                    }
                    if (inv[cnt].id == 255)
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
        item_identify(inv[ci], IdentifyState::almost_identified);
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
            txt(i18n::s.get("core.locale.action.bash.tree.execute", inv[ci]));
            if (inv[ci].own_state == 5 || inv[ci].param1 <= 0)
            {
                txt(i18n::s.get("core.locale.action.bash.tree.no_fruits"));
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
                if ((chipm(7, cell_data.at(x, y + 1).chip_id_actual) & 4) == 0)
                {
                    ++y;
                }
            }
            flt();
            itemcreate(-1, inv[ci].param2, x, y, 0);
            txt(i18n::s.get(
                "core.locale.action.bash.tree.falls_down", inv[ci]));
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
                    "core.locale.action.bash.choked.execute",
                    cdata[cc],
                    cdata[tc]));
                damage_hp(cdata[tc], sdata(10, cc) * 5, cc);
                if (cdata[tc].state() == Character::State::alive)
                {
                    txt(i18n::s.get(
                        "core.locale.action.bash.choked.spits", cdata[tc]));
                    txt(i18n::s.get("core.locale.action.bash.choked.dialog"));
                    cdata[tc].choked = 0;
                    chara_modify_impression(cdata[tc], 10);
                }
            }
            else
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.locale.action.bash.execute", cdata[cc], cdata[tc]));
                hostileaction(cc, tc);
            }
        }
        else
        {
            snd("core.bash1");
            txt(i18n::s.get(
                "core.locale.action.bash.execute", cdata[cc], cdata[tc]));
            txt(i18n::s.get(
                "core.locale.action.bash.disturbs_sleep",
                cdata[cc],
                cdata[tc]));
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
                    game_data.current_dungeon_level
                    * (game_data.current_map != mdata_t::MapId::shelter_)),
                calcfixlv(Quality::bad));
            flttypemajor = choice(fsetbarrel);
            itemcreate(-1, 0, x, y, 0);
            if (is_in_fov(cdata[cc]))
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.locale.action.bash.shatters_pot", cdata[cc]));
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
                txt(i18n::s.get("core.locale.action.bash.door.destroyed"));
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
                txt(i18n::s.get("core.locale.action.bash.door.execute"));
                if (game_data.current_map == mdata_t::MapId::jail)
                {
                    txt(i18n::s.get("core.locale.action.bash.door.jail"));
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
                    if (cdata[cc].quality < Quality::miracle
                        && encfind(cc, 60010) == -1)
                    {
                        --cdata[cc].attr_adjs[0];
                        chara_refresh(cc);
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.locale.action.bash.door.hurt",
                                    cdata[cc]),
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
                            txt(i18n::s.get(
                                "core.locale.action.bash.door.cracked"));
                        }
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }
    txt(i18n::s.get("core.locale.action.bash.air", cdata[cc]));
    snd("core.miss");
    return TurnResult::turn_end;
}



TurnResult proc_movement_event()
{
    if (auto handle = lua::handle_opt(cdata[cc]))
    {
        lua::run_event<lua::EventKind::character_moved>(*handle);
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
            .mef_index_plus_one
        != 0)
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
    proc_trap();
    p = cell_data.at(cdata[cc].position.x, cdata[cc].position.y).chip_id_actual;
    if (chipm(0, p) == 3)
    {
        if (chipm(1, p) == 5)
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
            if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y).feats
                == 0)
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
                if (rnd(220 + cdata.player().level * 10
                        - clamp(
                              game_data.cargo_weight * 150
                                  / (game_data.current_cart_limit + 1),
                              0,
                              (210 + cdata.player().level * 10)))
                    == 0)
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
                txt(i18n::s.get("core.locale.misc.caught_by_assassins"));
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
                if (33 <= cell_data
                              .at(cdata[cc].position.x, cdata[cc].position.y)
                              .chip_id_actual
                    && cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
                            .chip_id_actual
                        < 66)
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
                                "core.locale.action.move.global.ambush."
                                "distance_from_nearest_town",
                                p(0))
                    + " "
                    + i18n::s.get(
                          "core.locale.action.move.global.ambush.enemy_"
                          "strength");
                for (int cnt = 0; cnt < 1; ++cnt)
                {
                    if (encounterlv < 5)
                    {
                        valn += i18n::s.get(
                            "core.locale.action.move.global.ambush.rank.putit");
                        break;
                    }
                    if (encounterlv < 10)
                    {
                        valn += i18n::s.get(
                            "core.locale.action.move.global.ambush.rank.orc");
                        break;
                    }
                    if (encounterlv < 20)
                    {
                        valn += i18n::s.get(
                            "core.locale.action.move.global.ambush.rank."
                            "grizzly_bear");
                        break;
                    }
                    if (encounterlv < 30)
                    {
                        valn += i18n::s.get(
                            "core.locale.action.move.global.ambush.rank.drake");
                        break;
                    }
                    if (encounterlv < 40)
                    {
                        valn += i18n::s.get(
                            "core.locale.action.move.global.ambush.rank.lich");
                        break;
                    }
                    valn += i18n::s.get(
                        "core.locale.action.move.global.ambush.rank.dragon");
                }
                valn += u8")"s;
                txt(i18n::s.get("core.locale.action.move.global.ambush.text")
                    + valn);
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
    if (!Config::instance().use_autopick)
        return;
    if (is_modifier_pressed(snail::ModKey::ctrl))
        return;
    if (area_data[game_data.current_map].type == mdata_t::MapType::player_owned
        && area_data[game_data.current_map].id != mdata_t::MapId::shelter_
        && area_data[game_data.current_map].id != mdata_t::MapId::ranch)
        return;


    for (const auto& ci : items(-1))
    {
        if (inv[ci].number() == 0)
            continue;
        if (inv[ci].position != cdata.player().position)
            continue;
        if (inv[ci].own_state > 0)
            continue;

        item_checkknown(ci);

        const auto x = cdata.player().position.x;
        const auto y = cdata.player().position.y;

        bool did_something = true;
        const auto op = Autopick::instance().get_operation(inv[ci]);
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
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_pick_up")(
                    itemname(ci)));
                rtval = yes_or_no(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            in = inv[ci].number();
            elona::ci = ci;
            pick_up_item();
            if (int(op.type) & int(Autopick::Operation::Type::no_drop))
            {
                ibitmod(13, ti, 1);
                txt(i18n::s.get(
                    "core.locale.ui.inv.examine.no_drop.set", inv[ti]));
            }
            if (int(op.type) & int(Autopick::Operation::Type::save))
            {
                if (game_data.wizard == 0)
                {
                    do_save_game();
                }
            }
            break;
        case Autopick::Operation::Type::destroy:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_destroy")(
                    itemname(ci)));
                rtval = yes_or_no(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            snd("core.crush1");
            txt(i18n::fmt(u8"ui", u8"autopick", u8"destroyed")(itemname(ci)));
            inv[ci].remove();
            cell_refresh(x, y);
            cell_data.at(x, y).item_appearances_memory =
                cell_data.at(x, y).item_appearances_actual;
            break;
        case Autopick::Operation::Type::open:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_open")(
                    itemname(ci)));
                rtval = yes_or_no(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            elona::ci = ci;
            (void)do_open_command(); // Result is unused.
            break;
        }
        if (did_something && !op.sound.empty())
        {
            DSLOADFNAME(filesystem::dir::sound() / op.sound, 15);
            DSPLAY(15, 0);
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
        if (getkey(snail::Key::shift)
            && game_data.player_cellaccess_check_flag == 0
            && cdata.player().confused == 0 && cdata.player().dimmed == 0)
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
                txt(i18n::s.get("core.locale.action.move.sense_something"));
            }
        }
        p = chipm(0, cell_data.at(x, y).chip_id_actual);
        if (p != 0)
        {
            if (tname(p) != ""s)
            {
                txt(i18n::s.get("core.locale.action.move.walk_into", tname(p)));
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
                if (keybd_wait <= Config::instance().walkwait
                            * Config::instance().startrun
                    || cdata.player().turn % 2 == 0
                    || map_data.type == mdata_t::MapType::world_map)
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
                txt(i18n::s.get("core.locale.action.move.twinkle"),
                    Message::color{ColorIndex::orange});
            }
            if (feat(1) == 15)
            {
                txt(mapname(feat(2) + feat(3) * 100, true));
                if (area_data[feat(2) + feat(3) * 100].id
                    == mdata_t::MapId::random_dungeon)
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
                txt(i18n::s.get("core.locale.action.move.feature.stair.down"));
            }
            if (feat(1) == 10)
            {
                txt(i18n::s.get("core.locale.action.move.feature.stair.up"));
            }
            if (feat(1) == 24)
            {
                txt(i18n::s.get(
                    "core.locale.action.move.feature.material.spot"));
            }
            if (feat(1) == 27)
            {
                txt(i18n::s.get(
                    "core.locale.action.move.feature.material.remains"));
            }
            if (feat(1) == 25)
            {
                txt(i18n::s.get(
                    "core.locale.action.move.feature.material.mining"));
            }
            if (feat(1) == 26)
            {
                txt(i18n::s.get(
                    "core.locale.action.move.feature.material.spring"));
            }
            if (feat(1) == 28)
            {
                txt(i18n::s.get(
                    "core.locale.action.move.feature.material.plants"));
            }
            if (feat(1) == 29)
            {
                if (feat(2) == 36)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.vegetable");
                }
                if (feat(2) == 37)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.fruit");
                }
                if (feat(2) == 38)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.herb");
                }
                if (feat(2) == 39)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.strange");
                }
                if (feat(2) == 40)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.artifact");
                }
                if (feat(2) == 41)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.gem");
                }
                if (feat(2) == 42)
                {
                    s = i18n::s.get(
                        "core.locale.action.move.feature.seed.type.magic");
                }
                if (feat == tile_plant)
                {
                    txt(i18n::s.get(
                        "core.locale.action.move.feature.seed.growth.seed",
                        s(0)));
                }
                if (feat == tile_plant + 1)
                {
                    txt(i18n::s.get(
                        "core.locale.action.move.feature.seed.growth.bud",
                        s(0)));
                }
                if (feat == tile_plant + 2)
                {
                    txt(i18n::s.get(
                        "core.locale.action.move.feature.seed.growth.tree",
                        s(0)));
                }
                if (feat == tile_plant + 3)
                {
                    txt(i18n::s.get(
                        "core.locale.action.move.feature.seed.growth.withered",
                        s(0)));
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
        txt(i18n::s.get("core.locale.action.unlock.do_not_have_lockpicks"));
        return 0;
    }
    ti = stat;
    txt(i18n::s.get("core.locale.action.unlock.use_lockpick"));
    snd("core.locked1");
    {
        int stat = item_find(637, 3);
        if (stat != -1)
        {
            i = sdata(158, 0) * 150 / 100 + 5;
            txt(i18n::s.get("core.locale.action.unlock.use_skeleton_key"));
        }
        else
        {
            i = sdata(158, 0);
        }
    }
    f = 0;
    if (i * 2 < difficulty)
    {
        txt(i18n::s.get("core.locale.action.unlock.too_difficult"));
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
            txt(i18n::s.get("core.locale.action.unlock.easy"));
        }
        else if (rnd(rnd(i * 2) + 1) < difficulty)
        {
            txt(i18n::s.get("core.locale.action.unlock.fail"));
            f = 1;
        }
    }
    if (f)
    {
        if (rnd(3) == 0)
        {
            inv[ti].modify_number(-1);
            txt(i18n::s.get("core.locale.action.unlock.lockpick_breaks"));
        }
        Message::instance().linebreak();
        txt(i18n::s.get("core.locale.action.unlock.try_again"));
        rtval = yes_or_no(promptx, prompty, 160);
        if (rtval == 0)
        {
            unlock_box(difficulty);
            return 0;
        }
        return 0;
    }
    txt(i18n::s.get("core.locale.action.unlock.succeed"));
    gain_lock_picking_experience(cc);
    return 1;
}



void open_box()
{
    snd("core.chest1");
    txt(i18n::s.get("core.locale.action.open.text", inv[ci]));
    msg_halt();
    ri = ci;
    if (inv[ri].id == 394)
    {
        tc = cc;
        efid = 1117;
        efp = 100 + inv[ri].param1 * 10;
        inv[ri].param1 = 0;
        magic();
        return;
    }
    p = 3 + rnd(5);
    if (inv[ri].id == 415 || inv[ri].id == 416 || inv[ri].id == 734)
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
        if (inv[ri].id == 239)
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
        if (inv[ri].id == 241)
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
        if (inv[ri].id == 415 || inv[ri].id == 416)
        {
            flttypeminor = 0;
            flttypemajor = choice(fsetwear);
            fixlv = Quality::great;
            if (inv[ri].id == 416)
            {
                fixlv = Quality::miracle;
            }
            if (rnd(30) == 0)
            {
                dbid = 559;
            }
        }
        in = 0;
        if (inv[ri].id == 734)
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
        if (inv[ri].id == 284)
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
    if (inv[ri].id != 734)
    {
        if (rnd(10) == 0)
        {
            f = 1;
        }
    }
    if (inv[ri].id == 239 || inv[ri].id == 240)
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
    txt(i18n::s.get("core.locale.action.open.goods", inv[ri]));
    autosave = 1 * (game_data.current_map != mdata_t::MapId::show_house);
    inv[ri].param1 = 0;
    if (inv[ri].id == 284)
    {
        modify_karma(cdata.player(), -4);
    }
    if (inv[ri].id == 283)
    {
        modify_karma(cdata.player(), -8);
    }
}



void open_new_year_gift()
{
    snd("core.chest1");
    txt(i18n::s.get("core.locale.action.open.text", inv[ci]));
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
                    i18n::s.get("core.locale.action.open.new_year_gift."
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
                txt(i18n::s.get("core.locale.action.open.new_year_gift.trap"));
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                tlocx = cdata.player().position.x + rnd(3) - rnd(3);
                tlocy = cdata.player().position.y - rnd(3) + rnd(3);
                if (tlocx < 0 || tlocx >= map_data.width || tlocy < 0
                    || tlocy >= map_data.height)
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
            txt(i18n::s.get(
                "core.locale.action.open.new_year_gift.cursed_letter"));
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
                txt(i18n::s.get("core.locale.action.open.new_year_gift.ring"),
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
                    "core.locale.action.open.new_year_gift.younger_sister"));
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
            txt(i18n::s.get(
                "core.locale.action.open.new_year_gift.something_inside"));
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
            txt(i18n::s.get("core.locale.action.open.new_year_gift.ring"),
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
            txt(i18n::s.get("core.locale.action.open.new_year_gift.wonderful"));
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
        txt(i18n::s.get(
            "core.locale.action.open.new_year_gift.something_inside"));
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
                await(Config::instance().animewait * 5);
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
            gain_lock_picking_experience(cc);
        }
        cell_featset(dx, dy, tile_dooropen, 20, 0, -1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.action.open.door.succeed", cdata[cc]));
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
            txt(i18n::s.get("core.locale.action.open.door.fail", cdata[cc]),
                Message::only_once{true});
        }
    }
    if (cc == 0)
    {
        await(Config::instance().animewait * 5);
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
                txt(i18n::s.get("core.locale.action.ranged.load_normal_ammo"));
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
                            txt(i18n::s.get(
                                "core.locale.magic.common.too_exhausted"));
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
    attackvar = 0;
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
        if (clamp(int(std::sqrt(sdata(168, cc)) - 3), 1, 5)
                + cdata[cc].has_power_bash() * 5
            > rnd(100))
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.action.melee.shield_bash",
                    cdata[cc],
                    cdata[tc]));
            }
            damage_hp(cdata[tc], rnd(sdata(168, cc)) + 1, cc);
            dmgcon(
                tc,
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
    attackvar = 0;
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
        txt(i18n::s.get("core.locale.damage.is_frightened", cdata[cc]),
            Message::only_once{true});
        return;
    }
    if (cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .mef_index_plus_one
        != 0)
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
            the_item_db[inv[cw].id]->subcategory,
            inv[cw].image % 1000,
            inv[cw].image / 1000)
            .play();
    }
    if (attacknum > 1 || cc != 0)
    {
    }
    expmodifer = 1 + cdata[tc].is_hung_on_sand_bag() * 15 + cdata[tc].splits()
        + cdata[tc].splits2()
        + (game_data.current_map == mdata_t::MapId::show_house);
    int hit = calcattackhit();
    i = 0;
    if (hit == 1)
    {
        if (critical)
        {
            if (cc == 0)
            {
                txt(i18n::s.get("core.locale.damage.critical_hit"),
                    Message::color{ColorIndex::red});
            }
        }
        dmg = calcattackdmg();
        attackdmg = dmg;
        if (cc == 0)
        {
            if (Config::instance().attackanime)
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
                    s(1) = i18n::s.get("core.locale.misc.wields_proudly.the")
                        + iknownnameref(inv[cw].id);
                }
                else if (inv[cw].subname >= 40000)
                {
                    randomize(inv[cw].subname - 40000);
                    s(1) = random_title(1);
                    randomize();
                }
                else
                {
                    s(1) = i18n::s.get("core.locale.misc.wields_proudly.the")
                        + iknownnameref(inv[cw].id);
                }
                if (inv[cw].quality == Quality::godly)
                {
                    s(1) = i18n::s.get("core.locale.item.godly_paren", s(1));
                }
                else
                {
                    s(1) = i18n::s.get("core.locale.item.miracle_paren", s(1));
                }
                if (is_in_fov(cdata[cc]))
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get(
                                "core.locale.damage.wields_proudly",
                                cdata[cc],
                                s(1)),
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
                txt(i18n::s.get("core.locale.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (attackskill == 106)
            {
                if (tc >= 16)
                {
                    game_data.proc_damage_events_flag = 2;
                    txt(i18n::s.get(
                        "core.locale.damage.weapon.attacks_unarmed_and",
                        cdata[cc],
                        _melee(0, cdata[cc].melee_attack_type),
                        cdata[tc]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.locale.damage.weapon.attacks_unarmed",
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
                        "core.locale.damage.weapon", "name", attackskill);
                }
                if (weapon_name)
                {
                    if (tc >= 16)
                    {
                        game_data.proc_damage_events_flag = 2;
                        if (attackskill == 111)
                        {
                            txt(i18n::s.get(
                                "core.locale.damage.weapon.attacks_throwing",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.locale.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc],
                                *weapon_name));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.locale.damage.weapon.attacks_and",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.locale.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc]));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.damage.weapon.attacks_with",
                            cdata[cc],
                            i18n::s.get_enum_property(
                                "core.locale.damage.weapon",
                                "verb",
                                attackskill),
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
        if (rtdmg > cdata[tc].max_hp / 20 || rtdmg > sdata(154, tc)
            || rnd(5) == 0)
        {
            chara_gain_skill_exp(
                cdata[cc],
                attackskill,
                clamp((sdata(173, tc) * 2 - sdata(attackskill, cc) + 1), 5, 50)
                    / expmodifer,
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
                    clamp((250 * rtdmg / cdata[tc].max_hp + 1), 3, 100)
                        / expmodifer,
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
                                    "core.locale.damage.reactive_attack.thorns",
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
                                    "core.locale.damage.reactive_attack.ether_"
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
                                    "core.locale.damage.reactive_attack.acids"),
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
            p = clamp((sdata(attackskill, cc) - sdata(173, tc) / 2 + 1), 1, 20)
                / expmodifer;
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
                txt(i18n::s.get("core.locale.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get(
                    "core.locale.damage.miss.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.damage.miss.other", cdata[cc], cdata[tc]));
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
                txt(i18n::s.get("core.locale.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get(
                    "core.locale.damage.evade.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.damage.evade.other", cdata[cc], cdata[tc]));
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
            if (ibit(10, cw))
            {
                if (inv[cw].param2 < calcexpalive(inv[cw].param1))
                {
                    inv[cw].param2 += rnd(cdata[tc].level / inv[cw].param1 + 1);
                    if (inv[cw].param2 >= calcexpalive(inv[cw].param1))
                    {
                        snd("core.ding3");
                        txt(i18n::s.get(
                                "core.locale.misc.living_weapon_taste_blood",
                                inv[cw]),
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
                    txt(i18n::s.get(
                            "core.locale.action.time_stop.begins", cdata[cc]),
                        Message::color{ColorIndex::cyan});
                    game_data.left_turns_of_timestop =
                        inv[cw].enchantments[cnt].power / 100 + 1 + 1;
                }
                continue;
            }
        }
        if (enc == 57)
        {
            s = chara_refstr(cdata[tc].id, 8);
            if (strutil::contains(s(0), u8"/dragon/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 61)
        {
            s = chara_refstr(cdata[tc].id, 8);
            if (strutil::contains(s(0), u8"/god/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 58)
        {
            s = chara_refstr(cdata[tc].id, 8);
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
                    rnd(orgdmg * (100 + inv[cw].enchantments[cnt].power) / 1000
                        + 1)
                        + 5,
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
                    efp = inv[cw].enchantments[cnt].power
                        + sdata(attackskill, cc) * 10;
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
        txt(i18n::s.get("core.locale.action.time_stop.begins", cdata[cc]),
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



void dipcursed(int prm_1078, int)
{
    if (the_item_db[inv[prm_1078].id]->category == 57000)
    {
        if (inv[prm_1078].material == 35)
        {
            txt(i18n::s.get("core.locale.action.dip.rots", inv[prm_1078]));
            inv[prm_1078].param3 = -1;
            inv[prm_1078].image = 336;
            cell_refresh(inv[prm_1078].position.x, inv[prm_1078].position.y);
            return;
        }
        else
        {
            txt(i18n::s.get("core.locale.action.dip.unchanged", inv[prm_1078]));
            return;
        }
    }
    if (the_item_db[inv[prm_1078].id]->category < 50000)
    {
        --inv[prm_1078].enhancement;
        txt(i18n::s.get("core.locale.action.dip.rusts", inv[prm_1078]));
        if (inv_getowner(prm_1078) != -1)
        {
            chara_refresh(inv_getowner(prm_1078));
        }
        return;
    }
    txt(i18n::s.get("core.locale.common.nothing_happens"));
}



int gain_skills_by_geen_engineering()
{
    if (cdata[tc].splits() || cdata[tc].splits2())
    {
        return 0;
    }
    randomize(cdata[tc].id);
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
    s(1) = chara_refstr(cdata[tc].id, 8);
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
    randomize(cdata[tc].id);
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
        txt(i18n::s.get("core.locale.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y).feats != 0)
    {
        txt(i18n::s.get("core.locale.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    int val0;
    if (chipm(
            0,
            cell_data.at(cdata.player().position.x, cdata.player().position.y)
                .chip_id_actual)
        == 2)
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
        s = i18n::s.get("core.locale.action.plant.on_field", inv[ci]);
    }
    else
    {
        s = i18n::s.get("core.locale.action.plant.execute", inv[ci]);
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
    txt(i18n::s.get("core.locale.action.plant.new_plant_grows"),
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
        autosave = 1 * (game_data.current_map != mdata_t::MapId::show_house);
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
    txt(i18n::s.get("core.locale.action.plant.harvest", inv[ci]));
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
    snd("core.write1");
    save_game();
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
        if (game_data.current_map != bkdata(0)
            || game_data.current_dungeon_level != bkdata(1))
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
        txt(i18n::s.get("core.locale.action.ally_joins.party_full"));
        return -1;
    }
    oc = rc;
    chara_relocate(cdata[rc], f);
    cdata[rc].relationship = 10;
    cdata[rc].original_relationship = 10;
    cdata[rc].character_role = 0;
    cdata[rc].is_quest_target() = false;
    cdata[rc].does_not_search_enemy() = false;
    cdata[rc].is_hung_on_sand_bag() = false;
    cdata[rc].is_temporary() = false;
    cdata[rc].only_christmas() = false;
    snd("core.pray1");
    txt(i18n::s.get("core.locale.action.ally_joins.success", cdata[rc]),
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
    if (!Config::instance().story)
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
            pos(0, 0);
            gmode(4, cnt * 15);
            pos(0, 0);
            gcopy(4, 0, 0, windoww, windowh);
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
        actor(2, rc) = s(2);
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
    gsel(4);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / (u8""s + file + u8".bmp"), 1);
    pos(0, y1);
    gcopy(4, 0, 0, 640, 480, windoww, y2 - y1);
    gmode(2);
    boxf(0, 0, windoww, y1, {5, 5, 5});
    boxf(0, y2, windoww, windowh - y2, {5, 5, 5});
    if (val0 == 1)
    {
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        tc = 0;
        talk_to_npc();
        goto label_2681;
    }
    if (val0 == 2)
    {
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
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
        pos(windoww / 2, y + 4);
        gmode(2, 95);
        gcopy_c(3, 456, 144, 344, 72, dx, 72);
    }
    x = 40;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        y = y1 + 28 + (9 - noteinfo() / 2 + cnt) * 20;
        noteget(s, cnt);
        x = windoww / 2 - strlen_u(s(0)) * 4;
        gmode(6, 255);
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
        gmode(4, cnt * 16);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
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
                            txt(i18n::s.get("core.locale.action.weather.ether_"
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
                        txt(i18n::s.get(
                            "core.locale.action.weather.rain.draw_cloud"));
                        break;
                    }
                }
                if (game_data.pc_x_in_world_map > 65
                    || game_data.pc_y_in_world_map < 10)
                {
                    if (rnd(2) == 0)
                    {
                        game_data.weather = 2;
                        i18n::s.get("core.locale.action.weather.snow.starts");
                        break;
                    }
                }
                else
                {
                    if (rnd(10) == 0)
                    {
                        game_data.weather = 3;
                        i18n::s.get("core.locale.action.weather.rain.starts");
                        break;
                    }
                    if (rnd(40) == 0)
                    {
                        game_data.weather = 4;
                        i18n::s.get(
                            "core.locale.action.weather.rain.starts_heavy");
                        break;
                    }
                    if (rnd(60) == 0)
                    {
                        game_data.weather = 2;
                        i18n::s.get("core.locale.action.weather.snow.starts");
                        break;
                    }
                }
            }
            if (p == 3)
            {
                if (rnd(4) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get("core.locale.action.weather.rain.stops"));
                    break;
                }
                if (rnd(15) == 0)
                {
                    game_data.weather = 4;
                    txt(i18n::s.get(
                        "core.locale.action.weather.rain.becomes_heavier"));
                    break;
                }
            }
            if (p == 4)
            {
                if (rnd(3) == 0)
                {
                    game_data.weather = 3;
                    txt(i18n::s.get(
                        "core.locale.action.weather.rain.becomes_lighter"));
                    break;
                }
            }
            if (p == 1)
            {
                if (rnd(2) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get(
                        "core.locale.action.weather.ether_wind.stops"));
                    break;
                }
            }
            if (p == 2)
            {
                if (rnd(3) == 0)
                {
                    game_data.weather = 0;
                    txt(i18n::s.get("core.locale.action.weather.snow.stops"));
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
    map_prepare_tileset_atlas();
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
                i18n::s.get("core.locale.action.move.global.nap");
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
        txt(i18n::s.get("core.locale.action.day_breaks"),
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
        txt(i18n::s.get("core.locale.action.new_day"),
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
        if (game_data.quest_flags.pael_and_her_mom == 1
            || game_data.quest_flags.pael_and_her_mom == 3
            || game_data.quest_flags.pael_and_her_mom == 5
            || game_data.quest_flags.pael_and_her_mom == 7
            || game_data.quest_flags.pael_and_her_mom == 9)
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
    if (cdata.player().continuous_action.turn != 0)
    {
        if (cdata.player().continuous_action.type
            != ContinuousAction::Type::travel)
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
    if (game_data.angband_flag == -1
        || map_data.type == mdata_t::MapType::world_map)
        return none;

    switch (game_data.angband_flag)
    {
    case 0:
        if (key == u8"Q"s)
        {
            txt(i18n::s.get("core.locale.action.angband.q"));
            ++game_data.angband_flag;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        break;
    case 1:
        if (key == u8"y"s)
        {
            txt(i18n::s.get("core.locale.action.angband.y"));
            ++game_data.angband_flag;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        break;
    case 2:
        if (key == u8"@"s)
        {
            txt(i18n::s.get("core.locale.action.angband.at"));
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



void conquer_lesimas()
{
    std::string wincomment;
    snd("core.complete1");
    stop_music();
    txt(i18n::s.get("core.locale.win.conquer_lesimas"));
    update_screen();
    const auto win_words = txtsetwinword(3);

    Prompt prompt(Prompt::Type::cannot_cancel);
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        prompt.append(win_words[cnt]);
    }
    rtval = prompt.query(promptx, prompty, 310);

    wincomment = ""s + promptl(0, rtval);
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
        tc = chara_find(23);
        talk_to_npc();
        Message::instance().clear();
        txt(u8"青年は悪戯っぽくニヤリと笑い、壁に寄りかかった。"s);
        msg_halt();
        Message::instance().clear();
        chara_vanquish(chara_find(23));
        screenupdate = -1;
        update_screen();
        txt(u8"…どれくらい時間がたっただろう。氷の瞳の男は、いつの間にか姿を消していた。あなたは不安を振り払い、ゆっくりと本に手を伸ばした…"s);
        msg_halt();
    }
    mode = 0;
    play_music("core.mcMarch2");
    ui_win_screen_fade();
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"void.bmp", 1);
    pos(0, 0);
    gcopy(4, 0, 0, 640, 480, windoww, windowh);
    gsel(0);
    animation_fade_in();
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"g1.bmp", 1);
    gsel(0);
    s = i18n::s.get(
        "core.locale.win.you_acquired_codex", cdatan(1, 0), cdatan(0, 0));
    draw_caption();
    s(0) = i18n::s.get("core.locale.win.window.title");
    s(1) = ""s + strhint3;
    windowshadow = 1;
    ww = 680;
    wh = 488;
    pagesize = 0;
    display_window(windoww / 2 - ww / 2, windowh / 2 - wh / 2, ww, wh);
    cmbg = 0;
    x = ww / 3 - 20;
    y = wh - 140;
    pos(wx + ww - 120, wy + wh / 2);
    gmode(4, 250);
    gcopy_c(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.win.window.caption"), wx + 28, wy + 40);
    font(14 - en * 2);
    pos(wx + 40, wy + 76);
    mes(i18n::s.get("core.locale.win.window.arrived_at_tyris", 517, 8, 12));
    pos(wx + 40, wy + 116);
    mes(i18n::s.get(
        "core.locale.win.window.have_killed",
        game_data.deepest_dungeon_level,
        game_data.kill_count));
    pos(wx + 40, wy + 146);
    mes(i18n::s.get("core.locale.win.window.score", calcscore()));
    pos(wx + 40, wy + 186);
    mes(i18n::s.get(
        "core.locale.win.window.lesimas",
        game_data.date.year,
        game_data.date.month,
        game_data.date.day));
    pos(wx + 40, wy + 206);
    mes(i18n::s.get("core.locale.win.window.comment", wincomment));
    pos(wx + 40, wy + 246);
    mes(i18n::s.get("core.locale.win.window.your_journey_continues"));
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
    txt(i18n::s.get("core.locale.win.watch_event_again"));
    rtval = yes_or_no(promptx, prompty, 160);
    if (rtval == 0)
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
    txt(i18n::s.get("core.locale.misc.death.good_bye"));
    txt(i18n::s.get("core.locale.misc.death.you_leave_dying_message"));
    inputlog = "";
    input_text_dialog((windoww - 310) / 2 + inf_screenx, winposy(90), 16);
    std::string last_words;
    if (inputlog == ""s)
    {
        last_words = i18n::s.get("core.locale.system.last_words");
    }
    else
    {
        last_words =
            i18n::s.get("core.locale.misc.death.dying_message", inputlog(0));
    }
    buff = "";
    notesel(buff);
    const auto bone_filepath = filesystem::dir::save() / u8"bone.txt";
    if (fs::exists(bone_filepath))
    {
        std::ifstream in{bone_filepath.native(), std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    s = cdatan(1, cc) + u8" "s + cdatan(0, cc) + i18n::space_if_needed()
        + last_words;
    lenfix(s, 60);
    s += i18n::s.get(
        "core.locale.misc.death.date",
        game_data.date.year,
        game_data.date.month,
        game_data.date.day);
    noteadd(""s, 0);
    noteadd(s, 1);
    s = i18n::s.get("core.locale.misc.death.you_died", ndeathcause, mdatan(0));
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
        noteadd(
            i18n::s.get("core.locale.misc.death.rank", cnt + 1), cnt * 4, 1);
    }
    {
        std::ofstream out{bone_filepath.native(), std::ios::binary};
        out << buff(0) << std::endl;
    }
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"void.bmp", 1);
    gsel(0);
    show_game_score_ranking();
    s = i18n::s.get("core.locale.misc.death.you_are_about_to_be_buried");
    draw_caption();

    Prompt prompt("core.locale.misc.death");
    prompt.append("crawl_up", snail::Key::key_a);
    prompt.append("lie_on_your_back", snail::Key::key_b);
    rtval = prompt.query(promptx, 100, 240);

    if (rtval == 1)
    {
        show_game_score_ranking();
        s = i18n::s.get("core.locale.misc.death.you_have_been_buried");
        draw_caption();
        redraw();
        wait_key_pressed();
        return TurnResult::finish_elona;
    }
    s = u8"dead"s
        + i18n::s.get(
              "core.locale.misc.death.sent_message",
              cdatan(1, 0),
              cdatan(0, 0),
              ndeathcause,
              mdatan(0),
              last_words);
    screenupdate = -1;
    update_entire_screen();
    levelexitby = 3;
    return TurnResult::exit_map;
}



void show_game_score_ranking()
{
    notesel(buff);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, 800, 600, windoww, windowh);
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
    color(138, 131, 100);
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
            s = " "s + i18n::s.get("core.locale.misc.score.rank", cnt + 1);
        }
        pos(x - 80, y + 10);
        color(10, 10, 10);
        mes(s);
        color(0, 0, 0);
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
        pos(x, y);
        color(10, 10, 10);
        if (no_entry)
        {
            mes(u8"no entry");
            color(0, 0, 0);
            continue;
        }
        mes(s);
        noteget(s, p + 2);
        pos(x, y + 20);
        mes(s);
        noteget(s(10), p + 3);
        csvsort(s, s(10), 44);
        pos(x + 480, y + 20);
        mes(i18n::s.get("core.locale.misc.score.score", s(0)));
        p = elona::stoi(s(1)) % 1000;

        draw_chara_scale_height(elona::stoi(s(1)), x - 22, y + 12);

        color(0, 0, 0);
    }
    color(0, 0, 0);
}


} // namespace elona
