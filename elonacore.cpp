#include "ability.hpp"
#include "adventurer.hpp"
#include "ai.hpp"
#include "animation.hpp"
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
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "equipment.hpp"
#include "event.hpp"
#include "filesystem.hpp"
#include "fish.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "item_material.hpp"
#include "itemgen.hpp"
#include "log.hpp"
#include "macro.hpp"
#include "main.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "quest.hpp"
#include "race.hpp"
#include "random.hpp"
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

} // namespace



namespace elona
{


int prm_518;

elona_vector1<int> inhlist;

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
elona_vector1<int> fsetperform;
elona_vector1<int> fsetrare;
elona_vector1<int> fsetplantartifact;
elona_vector1<int> fsetplantunknown;
elona_vector1<int> fsetremain;
elona_vector1<int> fsetbarrel;
elona_vector1<int> isetgiftminor;
elona_vector1<int> isetgiftmajor;
elona_vector1<int> isetgiftgrand;
int cibk = 0;
int n_at_m174 = 0;
std::string s_at_m174;
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
int digx = 0;
int digy = 0;
int noeffect = 0;
int inumbk = 0;
int attackitem = 0;
int extraattack = 0;



int zentohan(const std::string& prm_209, std::string& prm_210, int prm_211)
{
    return LCMapStringA(
        GetUserDefaultLCID(), 4194304, prm_209, -1, prm_210, prm_211);
}



std::string lang(const std::string& prm_246, const std::string& prm_247)
{
    if (jp)
    {
        return prm_246;
    }
    else
    {
        return prm_247;
    }
}



std::string ranktitle(int prm_265)
{
    int p_at_m6 = 0;
    p_at_m6 = gdata((prm_265 + 120)) / 100;
    if (p_at_m6 == 1)
    {
        return rankn(0, prm_265);
    }
    if (p_at_m6 <= 5)
    {
        return rankn(1, prm_265);
    }
    if (p_at_m6 <= 10)
    {
        return rankn(2, prm_265);
    }
    if (p_at_m6 <= 80)
    {
        return rankn(p_at_m6 / 15 + 3, prm_265);
    }
    return rankn(9, prm_265);
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
    return;
}



std::string guildname()
{
    std::string s_at_m7;
    s_at_m7 = lang(u8"なし"s, u8"None"s);
    if (gdata_belongs_to_mages_guild != 0)
    {
        s_at_m7 = lang(u8"魔術士ギルド"s, u8"Mages Guild"s);
    }
    if (gdata_belongs_to_fighters_guild != 0)
    {
        s_at_m7 = lang(u8"戦士ギルド"s, u8"Fighters Guild"s);
    }
    if (gdata_belongs_to_thieves_guild != 0)
    {
        s_at_m7 = lang(u8"盗賊ギルド"s, u8"Thieves Guild"s);
    }
    return s_at_m7;
}



void initialize_post_data()
{
    SDIM3(popostname, 20, 7);
    popostname(1) = lang(u8"市長"s, u8"mayor"s);
    popostname(2) = lang(u8"村長"s, u8"chief"s);
    popostname(3) = lang(u8"司祭"s, u8"priest"s);
    popostname(4) = lang(u8"守衛長"s, u8"guard master"s);
    popostname(5) = lang(u8"徴税官"s, u8"tax master"s);
    popostname(6) = lang(u8"建設主任"s, u8"head architect"s);
    DIM4(pochart, 10, 10, 10);
    pochart(0, 0, 0) = 2;
    pochart(0, 1, 0) = 3;
    pochart(1, 1, 0) = 4;
    pochart(0, 2, 0) = 5;
    pochart(1, 2, 0) = 6;
    DIM3(podata, 300, 20);
    return;
}



void initialize_building_daga()
{
    DIM4(bddata, 40, 20, 10);
    DIM3(bdref, 10, 7);
    SDIM3(bdrefn, 20, 7);
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
    bdrefn(1) = lang(u8"炭鉱"s, u8"Mine"s);
    bdrefn(2) = lang(u8"畑"s, u8"Crop"s);
    bdrefn(3) = lang(u8"アトリエ"s, u8"Art Atelier"s);
    bdrefn(4) = lang(u8"寺院"s, u8"Temple"s);
    bdrefn(5) = lang(u8"盗賊の隠れ家"s, u8"Smuggler's Hideout"s);
    bdrefn(6) = lang(u8"灯台"s, u8"Light House"s);
    return;
}



void initialize_character()
{
    if (mode != 1)
    {
        add_quality_parentheses();
    }
    cdata[rc].state = 1;
    cdata[rc].interest = 100;
    cdata[rc].impression = 50;
    cdata[rc].vision_distance = 14;
    if (cdata[rc].id == 205)
    {
        cdata[rc].image = rnd(33) * 2 + cdata[rc].sex + 1;
    }
    if (rc == 0)
    {
        cdata[rc].nutrition = 9000;
    }
    else
    {
        cdata[rc].nutrition = 5000 + rnd(4000);
    }
    cdata[rc].height = cdata[rc].height + rnd((cdata[rc].height / 5 + 1))
        - rnd((cdata[rc].height / 5 + 1));
    cdata[rc].weight =
        cdata[rc].height * cdata[rc].height * (rnd(6) + 18) / 10000;
    update_required_experience(rc);
    init_character_skills(rc);
    if (cdata[rc].portrait == 0)
    {
        cdata[rc].portrait = rnd(32);
    }
    cdata[rc].personality = rnd(4);
    cdata[rc].talk_type = rnd(7);
    supply_initial_equipments();
    chara_refresh(rc);
    modify_crowd_density(rc, 1);
    cdata[rc].hp = cdata[rc].max_hp;
    cdata[rc].mp = cdata[rc].max_mp;
    cdata[rc].sp = cdata[rc].max_sp;
    if (rc == 0)
    {
        gdata_initial_cart_limit = 80000;
        gdata_current_cart_limit = gdata_initial_cart_limit;
    }
    if (cdata[rc].has_lay_hand())
    {
        cdata[rc].is_lay_hand_available() = true;
    }
    cm = 0;
    return;
}


void initialize_pc_character()
{
    cdata[0].quality = 2;
    cdata[0].relationship = 10;
    cdata[0].original_relationship = 10;
    cdata[0].has_own_sprite() = true;
    flt();
    itemcreate(0, 333, -1, -1, 0);
    inv[ci].number = 8;
    flt();
    itemcreate(0, 233, -1, -1, 0);
    inv[ci].number = 4;
    flt();
    itemcreate(0, 31, -1, -1, 0);
    inv[ci].number = 2;
    if (sdata(150, 0) == 0)
    {
        flt();
        itemcreate(0, 68, -1, -1, 0);
        inv[ci].number = 3;
    }
    if (cdatan(3, 0) == u8"pianist"s)
    {
        flt();
        itemcreate(0, 88, -1, -1, 0);
    }
    if (cdatan(3, 0) == u8"farmer"s)
    {
        flt();
        itemcreate(0, 256, -1, -1, 0);
    }
    if (cdatan(3, 0) == u8"wizard"s || cdatan(3, 0) == u8"warmage"s)
    {
        flt();
        itemcreate(0, 116, -1, -1, 0);
        flt();
        itemcreate(0, 257, -1, -1, 0);
        inv[ci].number = 3;
    }
    if (cdatan(3, 0) == u8"priest"s)
    {
        flt();
        itemcreate(0, 249, -1, -1, 0);
        inv[ci].number = 3;
        flt();
        itemcreate(0, 378, -1, -1, 0);
    }
    gain_race_feat();
    cdata[0].skill_bonus = 5 + trait(154);
    cdata[0].total_skill_bonus = 5 + trait(154);
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        inv[cnt].identification_state =
            identification_state_t::completely_identified;
    }
    chara_refresh(0);
    return;
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
    return;
}



void gain_race_feat()
{
    if (cdatan(2, 0) == u8"dwarf"s)
    {
        trait(152) = 2;
        trait(155) = 1;
    }
    if (cdatan(2, 0) == u8"elea"s)
    {
        trait(168) = 1;
        trait(156) = 1;
    }
    if (cdatan(2, 0) == u8"eulderna"s)
    {
        trait(153) = 1;
    }
    if (cdatan(2, 0) == u8"lich"s)
    {
        trait(151) = 1;
        trait(155) = 2;
        trait(152) = 1;
    }
    if (cdatan(2, 0) == u8"golem"s)
    {
        trait(157) = 1;
        trait(152) = 2;
    }
    if (cdatan(2, 0) == u8"yerles"s)
    {
        trait(154) = 1;
    }
    if (cdatan(2, 0) == u8"juere"s)
    {
        trait(158) = 1;
        trait(159) = 1;
    }
    if (cdatan(2, 0) == u8"goblin"s)
    {
        trait(155) = 1;
        trait(159) = 1;
    }
    if (cdatan(2, 0) == u8"mutant"s)
    {
        trait(0) = 1;
    }
    if (cdatan(2, 0) == u8"fairy"s)
    {
        trait(160) = 1;
        trait(161) = 1;
    }
    return;
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



void setunid(int prm_282, int prm_283)
{
    cdata[prm_282].cnpc_id = prm_283;
    cdata[prm_282].image = 825 + prm_283;
    cdata[prm_282].image += 0;
    return;
}



int getunid(int prm_284)
{
    f_at_m14 = 0;
    for (int cnt = 0, cnt_end = (usernpcmax); cnt < cnt_end; ++cnt)
    {
        if (cdatan(5, prm_284) == userdatan(0, cnt))
        {
            setunid(prm_284, cnt);
            f_at_m14 = 1;
            break;
        }
    }
    if (f_at_m14 == 0)
    {
        cdata[prm_284].image = 1;
        cdata[prm_284].cnpc_id = usernpcmax;
        cdatan(0, prm_284) = lang(u8"残りカス"s, u8"a garbage"s);
    }
    return f_at_m14;
}



int findunid(const std::string& prm_285)
{
    f_at_m14 = 0;
    for (int cnt = 0, cnt_end = (usernpcmax); cnt < cnt_end; ++cnt)
    {
        if (prm_285 == userdatan(0, cnt))
        {
            f_at_m14 = 1 + cnt;
            break;
        }
    }
    return f_at_m14;
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
    if (config::instance().autoturn == 0)
    {
        await(delay);
        ++scrturn;
    }
    if (config::instance().autoturn != 2 || firstautoturn == 1)
    {
        screenupdate = -1;
        update_screen();
    }
    if (config::instance().autoturn == 0)
    {
        redraw();
    }
}



std::string txttargetlevel(int cc, int tc)
{
    int x = cdata[cc].level;
    int y = cdata[tc].level;
    if (x * 20 < y)
    {
        return lang(
            u8"相手が巨人だとすれば、あなたは蟻のフン以下だ。",
            u8"If "s + he(tc)
                + u8" is a giant, you are less than a dropping of an ant.");
    }
    else if (x * 10 < y)
    {
        return lang(
            u8"絶対に勝てない相手だ。",
            cnven(he(tc)) + u8" can mince you with " + his(tc)
                + u8" eyes closed.");
    }
    else if (x * 5 < y)
    {
        return lang(
            u8"確実に殺されるだろう。",
            u8"You will get killed, a hundred percent sure.");
    }
    else if (x * 3 < y)
    {
        return lang(
            u8"奇跡が起きなければ殺されるだろう。",
            u8"You will get killed unless miracles happen.");
    }
    else if (x * 2 < y)
    {
        return lang(
            u8"少なくとも、あなたの倍は強そうだ。",
            cnven(he(tc)) + u8" " + is(tc)
                + u8" at least twice stronger than you.");
    }
    else if (x * 3 / 2 < y)
    {
        return lang(
            u8"相手はかなり強そうだ。", u8"The opponent looks quite strong.");
    }
    else if (x < y)
    {
        return lang(u8"勝てない相手ではない。", u8"Won't be an easy fight.");
    }
    else if (x / 3 * 2 < y)
    {
        return lang(u8"たぶん勝てそうだ。", u8"You will probably win.");
    }
    else if (x / 2 < y)
    {
        return lang(
            u8"負ける気はしない。",
            cnven(he(tc)) + u8" " + is(tc) + u8" an easy opponent.");
    }
    else if (x / 3 < y)
    {
        return lang(
            u8"目隠ししていても勝てそうだ。",
            u8"You bet you can beat "s + him(tc) + u8" with your eyes closed.");
    }
    else
    {
        return lang(
            u8"目隠しして座っていても勝てる。",
            u8"You can absolutely beat "s + him(tc)
                + u8" with your eyes closed and arms crossed.");
    }
}



std::string mapfile(int prm_365)
{
    if (adata(16, prm_365) == 5)
    {
        return u8"vernis"s;
    }
    if (adata(16, prm_365) == 11)
    {
        return u8"kapul"s;
    }
    if (adata(16, prm_365) == 12)
    {
        return u8"yowyn"s;
    }
    if (adata(16, prm_365) == 14)
    {
        return u8"rogueden"s;
    }
    if (adata(16, prm_365) == 15)
    {
        return u8"palmia"s;
    }
    if (adata(16, prm_365) == 33)
    {
        return u8"noyel"s;
    }
    if (adata(16, prm_365) == 36)
    {
        return u8"lumiest"s;
    }
    return u8"vernis"s;
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
    return;
}



void finish_elona()
{
    int ieopen = 0;
    int ie_event = 0;
    int ie = 0;
    if (ieopen)
    {
        delcom(ie_event);
        delcom(ie);
    }
    if (config::instance().autonumlock)
    {
        keybd_event(144);
        keybd_event(144, 0, 2);
    }
    if (mutex_handle != 0)
    {
        CloseHandle(mutex_handle);
    }
    end();
    return;
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
    return;
}



void load_random_name_table()
{
    std::vector<std::string> lines;
    range::copy(
        fileutil::read_by_line{filesystem::dir::data()
                               / lang(u8"ndata.csv", u8"ndata-e.csv")},
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
        fileutil::read_by_line{filesystem::dir::data() / u8"name.csv"},
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



void getinheritance(int prm_440, elona_vector1<int>& prm_441, int& prm_442)
{
    int p_at_m42 = 0;
    int f_at_m42 = 0;
    randomize(inv[prm_440].turn + 1);
    DIM2(prm_441, 15);
    prm_442 = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p_at_m42 = rnd(15);
        if (inv[prm_440].enchantments[p_at_m42].id == 0)
        {
            continue;
        }
        f_at_m42 = 0;
        for (int cnt = 0, cnt_end = (prm_442 + 1); cnt < cnt_end; ++cnt)
        {
            if (p_at_m42 == prm_441(cnt))
            {
                f_at_m42 = 1;
                break;
            }
        }
        if (f_at_m42 == 1)
        {
            continue;
        }
        if (rnd(4) > prm_442 || inv[prm_440].enchantments[p_at_m42].power < 0)
        {
            prm_441(prm_442) = p_at_m42;
            ++prm_442;
        }
    }
    randomize();
    return;
}



void flt(int level, int quality)
{
    filtermax = 0;
    fltselect = 0;
    flttypemajor = 0;
    flttypeminor = 0;
    fltnrace = "";
    objlv = level == 0 ? calcobjlv(gdata_current_dungeon_level) : level;
    fixlv = quality == 0 ? calcfixlv(2) : quality;
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
    return;
}



int discsetmc()
{
    return rnd(40);
}



int fltsetdungeon()
{
    if (rnd(20) == 0)
    {
        return fsetrare(rnd(length(fsetrare)));
    }
    if (rnd(3) == 0)
    {
        return fsetwear(rnd(length(fsetwear)));
    }
    return fsetitem(rnd(length(fsetitem)));
}



void csvstr2(elona_vector1<std::string>& prm_532, const std::string& prm_533)
{
    std::string word_at_m67;
    int p_at_m67 = 0;
    int i_at_m67 = 0;
    word_at_m67 = prm_533;
    p_at_m67 = 0;
    i_at_m67 = word_at_m67.size();
    for (int cnt = 0; cnt < 40; ++cnt)
    {
        prm_532(cnt) = "";
        getstr(prm_532(cnt), word_at_m67, clamp(p_at_m67, 0, i_at_m67), 44);
        if (strsize > i_at_m67)
        {
            break;
        }
        p_at_m67 += strsize;
    }
    return;
}



int cargocheck()
{
    if (the_item_db[inv[ci].id]->is_cargo == 0)
    {
        return 1;
    }
    if (mdata(6) != 1 && mdata(6) != 5 && mdata(6) != 3 && mdata(6) != 4
        && mdata(6) != 6 && mdata(6) != 2)
    {
        ++msgdup;
        txt(lang(
            u8"荷車の荷物は街か野外でしか操作できない。"s,
            u8"You can only use cargo items on the surface."s));
        snd(27);
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



void cutname(std::string& prm_541, int prm_542)
{
    int len_at_m71 = 0;
    elona_vector1<std::string> buf_at_m71;
    int p_at_m71 = 0;
    if (strlen_u(prm_541) > size_t(prm_542))
    {
        len_at_m71 = zentohan(prm_541, buf_at_m71, 0);
        SDIM2(buf_at_m71, len_at_m71);
        zentohan(prm_541, prm_541, len_at_m71);
        if (strlen_u(prm_541) > size_t(prm_542))
        {
            len_at_m71 = 0;
            while (1)
            {
                if (len_at_m71 >= prm_542)
                {
                    break;
                }
                p_at_m71 = prm_541[len_at_m71];
                if ((p_at_m71 >= 129 && p_at_m71 <= 159)
                    || (p_at_m71 >= 224 && p_at_m71 <= 252))
                {
                    p_at_m71 = 2;
                }
                else
                {
                    p_at_m71 = 1;
                }
                len_at_m71 += p_at_m71;
            }
            prm_541 = strmid(prm_541, 0, len_at_m71) + u8".."s;
        }
    }
    return;
}



void go_hostile()
{
    for (int cc = ELONA_MAX_PARTY_CHARACTERS; cc < ELONA_MAX_CHARACTERS; ++cc)
    {
        if (cdata[cc].character_role == 14 || cdata[cc].character_role == 16
            || cdata[cc].character_role == 1010)
        {
            cdata[cc].relationship = -3;
            cdata[cc].hate = 80;
            cdata[cc].emotion_icon = 218;
        }
    }
}



void modify_karma(int cc, int delta)
{
    if (trait(162) && delta < 0)
    {
        delta = delta * 75 / 100;
        if (delta == 0)
            return;
    }
    if (trait(169) && delta < 0)
    {
        delta = delta * 150 / 100;
    }

    if (delta >= 0)
    {
        txtef(5);
    }
    else
    {
        txtef(8);
    }
    txt(lang(u8"カルマ変動("s + delta + u8") ", u8"Karma("s + delta + u8")"));
    if (delta > 0)
    {
        if (cdata[cc].karma < -30 && cdata[cc].karma + delta >= -30)
        {
            txtef(2);
            txt(lang(
                u8"あなたの罪は軽くなった。",
                u8"You are no longer a criminal"));
        }
    }
    else if (delta < 0)
    {
        if (cdata[cc].karma >= -30 && cdata[cc].karma + delta < -30)
        {
            txtef(8);
            txt(lang(u8"あなたは今や罪人だ。", u8"You are a criminal now."));
            go_hostile();
        }
    }

    cdata[cc].karma += delta;

    int max = 20;
    if (trait(162))
    {
        max -= 20;
    }
    if (trait(169))
    {
        max += 20;
    }
    cdata[cc].karma = clamp(cdata[cc].karma, -100, max);
}



void modrank(int prm_552, int prm_553, int prm_554)
{
    elona_vector1<int> p_at_m75;
    int orgrank_at_m75 = 0;
    int i_at_m75 = 0;
    std::string s_at_m75;
    p_at_m75 = 120 + prm_552;
    p_at_m75(1) = gdata(p_at_m75) / 100;
    orgrank_at_m75 = gdata(p_at_m75);
    i_at_m75 = prm_553;
    if (prm_553 > 0)
    {
        i_at_m75 = prm_553 * (p_at_m75(1) + 20) * (p_at_m75(1) + 20) / 2500;
        gdata(140 + prm_552) = ranknorma(prm_552);
        if (gdata(p_at_m75) == 100)
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
    gdata(p_at_m75) -= i_at_m75;
    if (gdata(p_at_m75) >= 10000)
    {
        gdata(p_at_m75) = 10000;
    }
    if (gdata(p_at_m75) < 100)
    {
        gdata(p_at_m75) = 100;
    }
    if (orgrank_at_m75 / 100 != gdata(p_at_m75) / 100)
    {
        i_at_m75 = gdata(p_at_m75) / 100 - orgrank_at_m75 / 100;
        if (i_at_m75 < 0)
        {
            txtef(2);
        }
        else
        {
            txtef(8);
        }
        s_at_m75 = u8" "s + orgrank_at_m75 / 100 + lang(u8"位 → "s, u8" -> "s)
            + gdata(p_at_m75) / 100 + lang(u8"位 "s, ""s);
        txt(lang(u8"ランク変動"s, u8"Ranking Change "s) + u8"("s
            + rankn(10, prm_552) + s_at_m75 + u8") "s + lang(u8"《"s, u8"<"s)
            + ranktitle(prm_552) + lang(u8"》"s, u8">"s));
    }
    else if (i_at_m75 > 0)
    {
        txtef(2);
        txt(lang(
            u8"着実に次のランクに近づいている。"s,
            u8"You are one step closer to the next rank."s));
    }
    return;
}



void modify_potential(int cc, int id, int delta)
{
    sdata.get(id, cc).potential =
        clamp(sdata.get(id, cc).potential + delta, 2, 400);
}



void skillgain(int cc, int id, int initial_level, int stock)
{
    if (id >= 400)
    {
        if (cc == 0)
        {
            spell(id - 400) += stock;
            modify_potential(cc, id, 1);
        }
    }
    if (sdata.get(id, cc).original_level != 0)
    {
        if (id < 400)
        {
            modify_potential(cc, id, 20);
        }
        return;
    }
    int lv = sdata.get(id, cc).original_level + initial_level;
    if (lv < 1)
    {
        lv = 1;
    }
    if (id >= 400)
    {
        modify_potential(cc, id, 200);
    }
    else
    {
        modify_potential(cc, id, 50);
    }
    sdata.get(id, cc).original_level = clamp(lv, 0, 2000);
    chara_refresh(cc);
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
        if (prm_612 < 0 || prm_613 < 0 || prm_612 >= mdata(0)
            || prm_613 >= mdata(1))
        {
            return 0;
        }
        if (chipm(7, map(prm_612, prm_613, 0)) & 1)
        {
            return 0;
        }
        if (map(prm_612, prm_613, 6) != 0)
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
    for (int cnt = 0,
             cnt_end = cnt + (the_ability_db[efid]->sdataref3 % 1000 + 1);
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
                if (tx < 0 || ty < 0 || tx >= mdata(0) || ty >= mdata(1))
                {
                    continue;
                }
                if (chipm(7, map(tx, ty, 0)) & 1)
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



void cursor_check()
{
    if (key == key_north)
    {
        snd(5);
        --cs;
        if (cs < 0)
        {
            cs = keyrange - 1;
            if (cs < 0)
            {
                cs = 0;
            }
        }
    }
    if (key == key_south)
    {
        snd(5);
        ++cs;
        if (cs >= keyrange)
        {
            cs = 0;
        }
    }
    if (key == key_west)
    {
        key = key_pagedown;
    }
    if (key == key_east)
    {
        key = key_pageup;
    }
    if (cs >= keyrange)
    {
        cs_bk = -1;
        cs = keyrange - 1;
        if (cs < 0)
        {
            cs = 0;
        }
    }
    if (key == key_enter)
    {
        key = key_list(cs);
    }
    return;
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
    return;
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
    return;
}



void page_load()
{
    if (pagesaved == 1)
    {
        page = pagebk;
        cs = csprev;
        pagesaved = 0;
    }
    return;
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



void imeset(int prm_709)
{
    himc_at_ime_control = ImmGetContext(hwnd);
    ImmSetOpenStatus(himc_at_ime_control, prm_709);
    ImmReleaseContext(hwnd, himc_at_ime_control);
    return;
}



int imeget()
{
    int imesw_at_ime_control = 0;
    himc_at_ime_control = ImmGetContext(hwnd);
    imesw_at_ime_control = ImmGetOpenStatus(himc_at_ime_control);
    ImmReleaseContext(hwnd, himc_at_ime_control);
    return imesw_at_ime_control;
}



void boxl(int x1, int y1, int x2, int y2)
{
    pos(x1, y2);
    line(x1, y1);
    line(x2, y1);
    line(x2, y2);
    line(x1, y2);
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



void fixaiact(int prm_753)
{
    // FIXME: DRY
    for (auto&& action : cdata[prm_753].normal_actions)
    {
        if (action == 464 || action == 441 || action == 660 || action == 657)
        {
            action = -1;
        }
    }
    for (auto&& action : cdata[prm_753].special_actions)
    {
        if (action == 464 || action == 441 || action == 660 || action == 657)
        {
            action = -1;
        }
    }
    int i_at_m112 = cdata[prm_753].ai_heal;
    if (i_at_m112 == 464 || i_at_m112 == 441 || i_at_m112 == 660
        || i_at_m112 == 657)
    {
        cdata[prm_753].ai_heal = 0;
    }
    return;
}



void refreshspeed(int cc)
{
    cdata[cc].current_speed = sdata(18, cc)
        * clamp((100 - cdata[cc].speed_correction_value), 0, 100) / 100;
    if (cdata[cc].current_speed < 10)
    {
        cdata[cc].current_speed = 10;
    }
    cdata[cc].speed_percentage_in_next_turn = 0;

    if (cc != 0 && gdata_mount != cc)
        return;

    if (gdata_mount != 0)
    {
        const auto mount_speed = sdata(18, gdata_mount)
            * clamp(100 - cdata[gdata_mount].speed_correction_value, 0, 100)
            / 100;

        cdata[0].current_speed = mount_speed * 100
            / clamp(100 + mount_speed - sdata(10, gdata_mount) * 3 / 2
                        - sdata(301, 0) * 2
                        - (cdata[gdata_mount].is_suitable_for_mount() == 1)
                            * 50,
                    100,
                    1000);
        if (cdata[gdata_mount].is_unsuitable_for_mount())
        {
            cdata[0].current_speed /= 10;
        }
        if (gdata_mount == cc)
        {
            cdata[cc].current_speed =
                clamp(sdata(10, cc) + sdata(301, 0), 10, mount_speed);
            return;
        }
    }

    gspdorg = sdata.get(18, 0).original_level;

    if (gdata_mount == 0)
    {
        int n = cdata[0].nutrition / 1000 * 1000;
        if (n < 1000)
        {
            cdata[0].speed_percentage_in_next_turn -= 30;
        }
        if (n < 2000)
        {
            cdata[0].speed_percentage_in_next_turn -= 10;
        }
        if (cdata[0].sp < 0)
        {
            cdata[0].speed_percentage_in_next_turn -= 30;
        }
        if (cdata[0].sp < 25)
        {
            cdata[0].speed_percentage_in_next_turn -= 20;
        }
        if (cdata[0].sp < 50)
        {
            cdata[0].speed_percentage_in_next_turn -= 10;
        }
    }
    if (cdata[0].inventory_weight_type >= 3)
    {
        cdata[0].speed_percentage_in_next_turn -= 50;
    }
    if (cdata[0].inventory_weight_type == 2)
    {
        cdata[0].speed_percentage_in_next_turn -= 30;
    }
    if (cdata[0].inventory_weight_type == 1)
    {
        cdata[0].speed_percentage_in_next_turn -= 10;
    }
    if (mdata(6) == 1 || mdata(6) == 4)
    {
        if (gdata_cargo_weight > gdata_current_cart_limit)
        {
            cdata[0].speed_percentage_in_next_turn -=
                25 + 25 * (gdata_cargo_weight / (gdata_current_cart_limit + 1));
        }
    }
    gspd = cdata[0].current_speed * (100 + cdata[0].speed_percentage) / 100;
    if (gspd < 10)
    {
        gspd = 10;
    }
}



void ride_begin(int mount)
{
    txt(lang(
        name(mount) + u8"に騎乗した("s + name(mount) + u8"の速度: "s
            + cdata[mount].current_speed + u8"→"s,
        u8"You ride "s + name(mount) + u8". ("s + name(mount) + u8"'s speed: "s
            + cdata[mount].current_speed + u8"->"s));
    cdata[mount].is_ridden() = true;
    map(cdata[mount].position.x, cdata[mount].position.y, 1) = 0;
    gdata_mount = mount;
    create_pcpic(0, true);
    rowactend(gdata_mount);
    refreshspeed(gdata_mount);
    txt(""s + cdata[mount].current_speed + u8") "s);
    if (cdata[gdata_mount].is_suitable_for_mount())
    {
        txt(lang(
            u8"この生物は乗馬用にちょうどいい！"s, u8"You feel comfortable."s));
    }
    else if (cdata[gdata_mount].is_unsuitable_for_mount())
    {
        txt(lang(
            u8"この生物はあなたを乗せるには非力すぎる。"s,
            u8"This creature is too weak to carry you."s));
    }
}



void ride_end()
{
    int mount = gdata_mount;
    cdata[mount].is_ridden() = false;
    rowactend(mount);
    gdata_mount = 0;
    create_pcpic(0, true);
    refreshspeed(mount);
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
        if (cdata[cnt].state != 1)
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
                    if (is_in_fov(cnt))
                    {
                        txt(lang(
                            name(cnt) + u8"は物音に気付き目を覚ました。"s,
                            name(cnt) + u8" notice"s + _s(cnt)
                                + u8" the sound and wake"s + _s(cnt)
                                + u8" up."s));
                    }
                    cdata[cnt].emotion_icon = 221;
                    if (prm_781)
                    {
                        if (rnd(500) == 0)
                        {
                            if (is_in_fov(cnt))
                            {
                                txtef(9);
                                txt(lang(
                                    name(cnt) + u8"はキレた。"s,
                                    name(cnt)
                                        + u8" can no longer put up with it."s));
                                txt(lang(
                                    u8"「もう我慢できない」"s,
                                    u8"\"That's it.\""s));
                            }
                            turn_aggro(cnt, prm_782, 80);
                        }
                    }
                }
            }
        }
    }
    return;
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
        txtef(8);
        txt(lang(
            name(prm_788) + u8"は嫌な顔をした。"s,
            name(prm_788) + u8" glares at you."s));
    }
    else
    {
        if (cdata[prm_788].relationship == 0)
        {
            modify_karma(0, -2);
        }
        if (cdata[prm_788].id == 202)
        {
            if (gdata_released_fire_giant == 0)
            {
                txtef(8);
                txt(lang(
                    name(prm_788) + u8"は嫌な顔をした。"s,
                    name(prm_788) + u8" glares at you."s));
                return;
            }
        }
        if (cdata[prm_788].relationship > -2)
        {
            txtef(8);
            txt(lang(
                name(prm_788) + u8"は嫌な顔をした。"s,
                name(prm_788) + u8" glares at you."s));
            cdata[prm_788].relationship = -2;
        }
        else
        {
            if (cdata[prm_788].relationship != -3)
            {
                txtef(8);
                txt(lang(
                    name(prm_788) + u8"は激怒した。"s,
                    name(prm_788) + u8" gets furious!"s));
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
            txtef(3);
            txt(lang(u8"家畜は興奮した！"s, u8"Animals get excited!"s));
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].is_livestock() == 1)
                {
                    cdata[cnt].enemy_id = 0;
                    cdata[cnt].hate = 20;
                    cdata[cnt].emotion_icon = 318;
                }
            }
        }
    }
    rowactend(prm_788);
    return;
}



void rowact_check(int prm_789)
{
    if (cdata[prm_789].continuous_action_id != 0)
    {
        if (cdata[prm_789].continuous_action_id != 3)
        {
            cdata[prm_789].stops_continuous_action_if_damaged = 1;
        }
    }
    return;
}



void rowact_item(int prm_790)
{
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].continuous_action_turn <= 0)
        {
            continue;
        }
        if (cdata[cnt].continuous_action_id == 1
            || cdata[cnt].continuous_action_id == 2)
        {
            if (cdata[cnt].continuous_action_item == prm_790)
            {
                rowactend(cnt);
                txt(lang(
                    name(cnt) + u8"は行動を中断した。"s,
                    name(cnt) + u8" cancel"s + _s(cnt) + u8" "s + his(cnt)
                        + u8" action."s));
            }
        }
    }
    return;
}



void wake_up()
{
    if (gdata_hour >= 7 && gdata_hour <= 22)
    {
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].sleep > 0)
            {
                if (rnd(10))
                {
                    cdata[cnt].sleep = 0;
                }
            }
        }
    }
    return;
}



void incognitobegin()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
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
    return;
}



void incognitoend()
{
    for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].character_role == 14)
        {
            if (cdata[0].karma < -30)
            {
                cdata[cnt].relationship = -3;
                cdata[cnt].hate = 80;
                cdata[cnt].emotion_icon = 218;
            }
        }
    }
    return;
}



void animeload(int prm_807, int prm_808)
{
    elona_vector1<int> i_at_m133;
    if (mode != 0)
    {
        return;
    }
    if (is_in_fov(prm_808) == 0)
    {
        return;
    }
    if (config::instance().animewait == 0)
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
    i_at_m133(1) = 50;
    r_at_m133 = 0;
    if (prm_807 == 8)
    {
        snd(65);
    }
    if (prm_807 == 10)
    {
        i_at_m133(0) = 8;
        i_at_m133(1) = 30;
        r_at_m133 = 0.2;
        snd(119);
    }
    if (prm_807 == 11)
    {
        i_at_m133(0) = 5;
        i_at_m133(1) = 50;
        r_at_m133 = 0;
        snd(118);
    }
    if (prm_807 == 14)
    {
        i_at_m133(0) = 6;
        i_at_m133(1) = 50;
    }
    for (int cnt = 0, cnt_end = (i_at_m133); cnt < cnt_end; ++cnt)
    {
        gmode(2, 96, 96);
        pos(dx_at_m133 + 24, dy_at_m133 + 8);
        grotate(7, cnt * 96, 0, r_at_m133 * cnt, 96, 96);
        gmode(0);
        redraw();
        pos(dx_at_m133 - 24, dy_at_m133 - 40);
        gcopy(4, 0, 0, 96, 96);
        await(config::instance().animewait + i_at_m133(1));
    }
    gmode(2);
    return;
}



void animeblood(int prm_809, int prm_810, int prm_811)
{
    int ele2_at_m133 = 0;
    elona_vector1<int> x_at_m133;
    elona_vector1<int> y_at_m133;
    int cnt2_at_m133 = 0;
    if (is_in_fov(prm_809) == 0)
    {
        return;
    }
    if (config::instance().animewait == 0)
    {
        return;
    }
    screenupdate = -1;
    update_screen();
    if (prm_810 == 0)
    {
        prepare_item_image(16, 0);
    }
    if (prm_810 == 1)
    {
        prepare_item_image(18, 0);
    }
    dx_at_m133 = (cdata[prm_809].position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133(0) = (cdata[prm_809].position.y - scy) * inf_tiles + inf_screeny;
    dy_at_m133(1) = 0;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, dx_at_m133 - 48, dy_at_m133 - 56, 144, 160);
    ele2_at_m133 = 0;
    if (prm_811 == 52)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime18.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 51)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime19.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 50)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime20.bmp");
        dy_at_m133(1) = -20;
    }
    if (prm_811 == 56)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime22.bmp");
        dy_at_m133(1) = -24;
    }
    if (prm_811 == 53)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime21.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 54)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime23.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 57)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime24.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 59)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime25.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 58)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime26.bmp");
        dy_at_m133(1) = -16;
    }
    if (prm_811 == 55 || prm_811 == 63)
    {
        ele2_at_m133 = 1;
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime27.bmp");
        dy_at_m133(1) = -16;
    }
    gmode(2);
    gsel(0);
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        x_at_m133(cnt) = rnd(48) - 24;
        y_at_m133(cnt) = rnd(16);
    }
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        cnt2_at_m133 = cnt * 2;
        gmode(2, inf_tiles, inf_tiles);
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
                0.2 * cnt,
                24 - cnt2_at_m133 * 2,
                24 - cnt2_at_m133 * 2);
        }
        gmode(0);
        redraw();
        pos(dx_at_m133 - 48, dy_at_m133 - 56);
        gcopy(4, 0, 0, 144, 160);
        await(config::instance().animewait + 15 + (ele2_at_m133 != 0) * 20);
    }
    gmode(2);
    return;
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
        if (dx_at_m136 < 0 || dx_at_m136 >= mdata(0) || dy_at_m136 < 0
            || dy_at_m136 >= mdata(1))
        {
            continue;
        }
        if (chipm(2, map(dx_at_m136, dy_at_m136, 0)))
        {
            continue;
        }
        if (map(dx_at_m136, dy_at_m136, 7) % 10 < 5)
        {
            ++map(dx_at_m136, dy_at_m136, 7);
        }
    }
    return;
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
        if (dx_at_m136 < 0 || dx_at_m136 >= mdata(0) || dy_at_m136 < 0
            || dy_at_m136 >= mdata(1))
        {
            continue;
        }
        if (chipm(2, map(dx_at_m136, dy_at_m136, 0)))
        {
            continue;
        }
        if (map(dx_at_m136, dy_at_m136, 7) / 10 < 4)
        {
            map(dx_at_m136, dy_at_m136, 7) = map(dx_at_m136, dy_at_m136, 7) % 10
                + (map(dx_at_m136, dy_at_m136, 7) / 10 + 1) * 10;
        }
    }
    return;
}



void check_kill(int prm_836, int prm_837)
{
    int p_at_m137 = 0;
    if (gdata_current_map == 40 || gdata_current_map == 35
        || gdata_current_map == 6)
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
                ++gdata_kill_count;
                if (cdata[prm_837].id == gdata_fighters_guild_target)
                {
                    if (gdata_fighters_guild_quota > 0)
                    {
                        --gdata_fighters_guild_quota;
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
                    chara_mod_impression(prm_837, -25);
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
                        chara_mod_impression(prm_836, 1);
                        cdata[prm_836].emotion_icon = 317;
                    }
                }
                else if (rnd(10) == 0)
                {
                    chara_mod_impression(prm_836, 1);
                    cdata[prm_836].emotion_icon = 317;
                }
            }
        }
    }
    if (p_at_m137 != 0)
    {
        modify_karma(0, p_at_m137);
    }
    return;
}



void refresh_speed_correction_value(int cc)
{
    int number_of_body_parts = 0;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata_body_part(cc, i) != 0)
        {
            ++number_of_body_parts;
        }
    }
    if (number_of_body_parts > 13)
    {
        cdata[cc].speed_correction_value = (number_of_body_parts - 13) * 5;
    }
    else
    {
        cdata[cc].speed_correction_value = 0;
    }
}



void gain_new_body_part(int cc)
{
    for (int i = 0; i < 30; ++i)
    {
        if (cdata_body_part(cc, i) != 0)
        {
            continue;
        }
        if (rnd(7) == 0)
        {
            cdata_body_part(cc, i) = 20000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_2")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_2") + u8"!"s));
                break;
            }
        }
        if (rnd(9) == 0)
        {
            cdata_body_part(cc, i) = 30000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_3")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_3") + u8"!"s));
                break;
            }
        }
        if (rnd(8) == 0)
        {
            cdata_body_part(cc, i) = 50000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_5")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_5") + u8"!"s));
                break;
            }
        }
        if (rnd(4) == 0)
        {
            cdata_body_part(cc, i) = 60000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_6")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_6") + u8"!"s));
                break;
            }
        }
        if (rnd(6) == 0)
        {
            cdata_body_part(cc, i) = 70000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_7")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_7") + u8"!"s));
                break;
            }
        }
        if (rnd(5) == 0)
        {
            cdata_body_part(cc, i) = 80000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_8")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_8") + u8"!"s));
                break;
            }
        }
        if (rnd(5) == 0)
        {
            cdata_body_part(cc, i) = 90000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_9")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_9") + u8"!"s));
                break;
            }
        }
        if (rnd(1) == 0)
        {
            cdata_body_part(cc, i) = 10000;
            if (cm)
            {
                break;
            }
            else
            {
                txt(lang(
                    name(cc) + u8"の身体から新たな"s
                        + i18n::_(u8"ui", u8"body_part", u8"_1")
                        + u8"が生えてきた！"s,
                    name(cc) + u8" grow"s + _s(cc) + u8" a new "s
                        + i18n::_(u8"ui", u8"body_part", u8"_1") + u8"!"s));
                break;
            }
        }
        break;
    }
    refresh_speed_correction_value(cc);
}



std::string cnveqweight(int cc)
{
    int id = chara_armor_class(cc);
    if (id == 169)
    {
        return lang(u8"(重装備)"s, u8"(Heavy)"s);
    }
    else if (id == 170)
    {
        return lang(u8"(中装備)"s, u8"(Medium)"s);
    }
    else
    {
        return lang(u8"(軽装備)"s, u8"(Light)"s);
    }
}



void cnvbonus(int prm_895, int prm_896)
{
    if (prm_895 >= 50 && prm_895 < 61)
    {
        if (prm_896 > 0)
        {
            buff += u8"　　"s
                + i18n::_(u8"ability", std::to_string(prm_895), u8"name")
                + u8"耐性に <green>クラス"s + prm_896 / 50 + u8"<col>("s
                + prm_896 + u8") のボーナス\n"s;
        }
        if (prm_896 < 0)
        {
            buff += u8"　　"s
                + i18n::_(u8"ability", std::to_string(prm_895), u8"name")
                + u8"耐性に <red>クラス"s + prm_896 / 50 + u8"<col>("s + prm_896
                + u8") のマイナス修正\n"s;
        }
    }
    else
    {
        if (prm_896 > 0)
        {
            buff += u8"　　"s
                + i18n::_(u8"ability", std::to_string(prm_895), u8"name")
                + u8"に <green>+"s + prm_896 + u8"<col> のボーナス\n"s;
        }
        if (prm_896 < 0)
        {
            buff += u8"　　"s
                + i18n::_(u8"ability", std::to_string(prm_895), u8"name")
                + u8"に <red>"s + prm_896 + u8"<col> のマイナス修正\n"s;
        }
    }
    return;
}



void wet(int cc, int turns)
{
    cdata[cc].wet += turns;
    if (is_in_fov(cc))
    {
        txt(lang(
            name(cc) + u8"は濡れた。"s,
            name(cc) + u8" get"s + _s(cc) + u8" wet."s));
        if (cdata[cc].is_invisible())
        {
            txt(lang(
                name(cc) + u8"の姿があらわになった。"s,
                name(cc) + u8" "s + is(cc) + u8" revealed "s + his(cc)
                    + u8" shape."s));
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
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"はマナを吸い取られた！"s,
                name(cc) + your(cc) + u8" mana is absorbed."s));
        }
        if (cc == 0)
        {
            dmgmp(cc, cdata[cc].max_mp);
        }
        else
        {
            dmgmp(cc, cdata[cc].max_mp / 3);
        }
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cc))
        {
            if (cdata[cc].confused != 0)
            {
                txt(lang(
                    name(cc) + u8"は余計に混乱した。"s,
                    name(cc) + u8" "s + is(cc) + u8" confused more."s));
            }
            else
            {
                txt(lang(u8"難解だ！"s, u8"It's too difficult!"s));
            }
        }
        dmgcon(cc, status_ailment_t::confused, 100);
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"魔力の渦が何かを召喚した！"s,
                u8"Several creatures are summoned from a vortex of magic."s));
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata[0].level * 3 / 2 + 3), calcfixlv(2));
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
    if (is_in_fov(cc))
    {
        txt(lang(
            name(cc) + u8"は奇妙な力に捻じ曲げられた！"s,
            u8"A dimension door opens in front of you."s));
    }
    tc = cc;
    efid = 408;
    magic();
    return 0;
}



int try_to_reveal()
{
    if (rnd(sdata(159, cc) * 15 + 20 + sdata(13, cc))
        > rnd(gdata_current_dungeon_level * 8 + 60))
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
        > rnd(gdata_current_dungeon_level * 12 + 100))
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
            if (rnd(p) < rnd(sdata(13, r2) * 60 + 150))
            {
                return 1;
            }
        }
    }
    if (pcnoise != 0)
    {
        if (rnd(150) < pcnoise)
        {
            return 1;
        }
    }
    return 0;
}



void start_stealing()
{
    gdata(91) = 105;
    continuous_action_others();
    return;
}



void get_hungry(int cc)
{
    if ((trait(158) && rnd(3) == 0) || debug::voldemort)
        return;

    int p = cdata[cc].nutrition / 1000;
    cdata[cc].nutrition -= 8;
    if (cdata[cc].nutrition / 1000 != p)
    {
        if (p == 1)
        {
            msgalert = 1;
            txt(lang(u8"このままだと餓死してしまう！"s, u8"You are starving!"s),
                lang(
                    u8"腹が減ってほとんど死にかけている。"s,
                    u8"You are almost dead from hunger."s));
        }
        else if (p == 2)
        {
            msgalert = 1;
            txt(lang(
                    u8"空腹で目が回りだした…"s,
                    u8"Your hunger makes you dizzy."s),
                lang(
                    u8"すぐに何かを食べなくては…"s,
                    u8"You have to eat something NOW."s));
        }
        else if (p == 5)
        {
            msgalert = 1;
            txt(lang(u8"腹がすいてきた。"s, u8"You are getting hungry."s),
                lang(u8"空腹になった。"s, u8"You feel hungry."s),
                lang(u8"さて何を食べようか。"s, u8"Now what shall I eat?"s));
        }
        refreshspeed(cc);
    }
}



void proc_turn_end(int cc)
{
    int regen = 0;
    regen = 1;
    if (cdata[cc].sleep > 0)
    {
        healcon(cc, 2, 1);
        if (cdata[cc].sleep > 0)
        {
            cdata[cc].emotion_icon = 114;
        }
        healhp(cc, 1);
        healmp(cc, 1);
    }
    if (cdata[cc].poisoned > 0)
    {
        dmghp(cc, rnd(2 + sdata(11, cc) / 10), -4);
        healcon(cc, 1, 1);
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
            if (is_in_fov(cc))
            {
                txt(lang(u8"「うぐぐ…！」"s, u8"\"Ughh...!\""s));
            }
        }
        ++cdata[cc].choked;
        if (cdata[cc].choked > 15)
        {
            dmghp(cc, 500, -21);
        }
        regen = 0;
    }
    if (cdata[cc].gravity > 0)
    {
        --cdata[cc].gravity;
        if (cdata[cc].gravity == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"は重力から抜け出した。"s,
                    name(cc) + u8" break"s + _s(cc)
                        + u8" away from gravity."s));
            }
        }
    }
    if (cdata[cc].furious > 0)
    {
        --cdata[cc].furious;
        if (cdata[cc].furious == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"はやや落ち着いた。"s,
                    name(cc) + u8" calm"s + _s(cc) + u8" down."s));
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
            if (cdata[cc].quality >= 4)
            {
                if (rnd(200) == 0)
                {
                    healcon(cc, 12);
                }
            }
        }
    }
    if (cdata[cc].blind > 0)
    {
        healcon(cc, 4, 1);
        if (cdata[cc].blind > 0)
        {
            cdata[cc].emotion_icon = 110;
        }
    }
    if (cdata[cc].paralyzed > 0)
    {
        regen = 0;
        healcon(cc, 3, 1);
        if (cdata[cc].paralyzed > 0)
        {
            cdata[cc].emotion_icon = 115;
        }
    }
    if (cdata[cc].confused > 0)
    {
        healcon(cc, 5, 1);
        if (cdata[cc].confused > 0)
        {
            cdata[cc].emotion_icon = 111;
        }
    }
    if (cdata[cc].fear > 0)
    {
        healcon(cc, 6, 1);
        if (cdata[cc].fear > 0)
        {
            cdata[cc].emotion_icon = 113;
        }
    }
    if (cdata[cc].dimmed > 0)
    {
        healcon(cc, 7, 1);
        if (cdata[cc].dimmed > 0)
        {
            cdata[cc].emotion_icon = 112;
        }
    }
    if (cdata[cc].drunk > 0)
    {
        healcon(cc, 8, 1);
        if (cdata[cc].drunk > 0)
        {
            cdata[cc].emotion_icon = 106;
        }
    }
    if (cdata[cc].bleeding > 0)
    {
        dmghp(
            cc,
            rnd(cdata[cc].hp * (1 + cdata[cc].bleeding / 4) / 100 + 3) + 1,
            -13);
        healcon(cc, 9, 1 + cdata[cc].cures_bleeding_quickly() * 3);
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
        if (is_in_fov(cc))
        {
            if (rnd(3) == 0)
            {
                txtef(9);
                if (jp)
                {
                    r2 = rnd(5);
                    if (r2 == 0)
                    {
                        txt(name(cc) + u8"「キョキョキョ」"s,
                            name(cc) + u8"「クワッ」"s,
                            name(cc) + u8"「シャアァァ」"s,
                            name(cc) + u8"「ばぶっふ！」"s,
                            name(cc) + u8"「煮殺せ！」"s,
                            name(cc) + u8"「許しなさい許しなさい！！」"s);
                    }
                    if (r2 == 1)
                    {
                        txt(name(cc) + u8"「フゥハハハー！」"s,
                            name(cc) + u8"「あ、あ、あ、あ」"s,
                            name(cc) + u8"「ぴ…ぴ…ぴか…」"s,
                            name(cc) + u8"「お兄ちゃん！」"s,
                            name(cc) + u8"「うみみやぁ」"s);
                    }
                    if (r2 == 2)
                    {
                        txt(name(cc) + u8"は突然踊りだした。"s,
                            name(cc) + u8"は着ていたものを脱ぎだした。"s,
                            name(cc) + u8"はぐるぐる回りだした。"s,
                            name(cc) + u8"は奇声を発した。"s,
                            name(cc) + u8"「ねうねう♪ねうねう♪」"s);
                    }
                    if (r2 == 3)
                    {
                        txt(name(cc) + u8"「ウージッムシ♪ウージッムシ♪」"s,
                            name(cc) + u8"「じゃあ殺さなきゃ。うん♪」"s,
                            name(cc) + u8"「このナメクジがっ」"s,
                            name(cc) + u8"「おすわり！」"s,
                            name(cc) +
                                u8"「フーーーーン フーーーーン･･･ フーーーンフ」"s);
                    }
                    if (r2 == 4)
                    {
                        txt(name(cc) + u8"「このかたつむり野郎がっ」"s,
                            name(cc) + u8"「うにゅみゅあ！」"s,
                            name(cc) + u8"「ごめんなさいごめんなさい！」"s,
                            name(cc) + u8"「もうすぐ生まれるよ♪」"s,
                            name(cc) + u8"「フーーーーン フー…クワッ！」"s);
                    }
                }
                else
                {
                    r2 = rnd(2);
                    if (r2 == 0)
                    {
                        txt(name(cc) + u8" start"s + _s(cc) + u8" to take "s
                                + his(cc) + u8" cloths off."s,
                            name(cc) + u8" shout"s + _s(cc) + u8"."s,
                            name(cc) + u8" dance"s + _s(cc) + u8"."s);
                    }
                    if (r2 == 1)
                    {
                        txt(u8"\"Weeeeeee!\""s,
                            u8"\"Forgive me! Forgive me!\""s,
                            u8"\"P-P-Pika!\""s,
                            u8"\"Shhhhhh!\""s,
                            u8"\"So I have to kill.\""s,
                            u8"\"You snail!\""s);
                    }
                }
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
        healcon(cc, 11, 1);
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
                if (cdata[cc].continuous_action_id != 1)
                {
                    dmghp(cc, rnd(2) + cdata[0].max_hp / 50, -3);
                    if (gdata_play_turns % 10 == 0)
                    {
                        rowact_check(cc);
                        if (rnd(50) == 0)
                        {
                            modweight(cc, -1);
                        }
                    }
                }
            }
            regen = 0;
        }
        if (gdata_continuous_active_hours >= 30)
        {
            if (debug::voldemort)
            {
                gdata_continuous_active_hours = 0;
            }
            if (gdata_play_turns % 100 == 0)
            {
                txt(lang(
                    u8"あなたは眠りを必要としている。"s,
                    u8"You need to sleep."s));
            }
            if (rnd(2))
            {
                regen = 0;
            }
            if (gdata_continuous_active_hours >= 50)
            {
                regen = 0;
                dmgsp(cc, 1);
            }
        }
    }
    else if (cdata[cc].related_quest_id != 0)
    {
        p = cdata[cc].related_quest_id - 1;
        if (qdata(15, p) > 0)
        {
            cdata[cc].emotion_icon = 122;
        }
        if (qdata(8, p) != 0)
        {
            if (cdata[cc].turn % 2 == 1)
            {
                cdata[cc].emotion_icon = 123;
            }
        }
    }
    if (gdata_executing_immediate_quest_type == 1009)
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
            healhp(cc, rnd(sdata(154, cc) / 3 + 1) + 1);
        }
        if (rnd(5) == 0)
        {
            healmp(cc, rnd(sdata(155, cc) / 2 + 1) + 1);
        }
    }
}



void refresh_burden_state()
{
    cdata[0].inventory_weight = clamp(inv_weight(0), 0, 20000000)
        * (100 - trait(201) * 10 + trait(205) * 20) / 100;
    cdata[0].max_inventory_weight =
        sdata(10, 0) * 500 + sdata(11, 0) * 250 + sdata(153, 0) * 2000 + 45000;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cdata[0].inventory_weight > cdata[0].max_inventory_weight * 2)
        {
            cdata[0].inventory_weight_type = 4;
            break;
        }
        if (cdata[0].inventory_weight > cdata[0].max_inventory_weight)
        {
            cdata[0].inventory_weight_type = 3;
            break;
        }
        if (cdata[0].inventory_weight > cdata[0].max_inventory_weight / 4 * 3)
        {
            cdata[0].inventory_weight_type = 2;
            break;
        }
        if (cdata[0].inventory_weight > cdata[0].max_inventory_weight / 2)
        {
            cdata[0].inventory_weight_type = 1;
            break;
        }
        cdata[0].inventory_weight_type = 0;
    }
    refreshspeed(0);
    return;
}



void revive_character()
{
    label_1538();
    cxinit = cdata[0].position.x;
    cyinit = cdata[0].position.y;
    chara_place();
    cdata[rc].current_map = 0;
    snd(64);
    txtef(5);
    txt(cnven(cdatan(0, rc))
        + lang(
              u8"は復活した！"s,
              (u8" "s + have(rc) + u8" been resurrected!"s)));
    return;
}



void label_1538()
{
    label_15380();
    label_15390();
    return;
}



void label_1539()
{
    label_15390();
    return;
}



void label_15380()
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
    cdata[rc].state = 1;
    cdata[rc].current_map = 0;
    cdata[rc].relationship = cdata[rc].original_relationship;
    cdata[rc].nutrition = 8000;
    return;
}



void label_15390()
{
    cdata[rc].is_contracting_with_reaper() = false;
    rowactend(rc);
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
            buff_delete(rc, cnt);
            --cnt;
            continue;
        }
    }
    chara_refresh(rc);
    return;
}



void label_1540()
{
    label_1538();
    if (rc == 0)
    {
        gdata_is_returning_or_escaping = 0;
        traveldone = 0;
        if (gdata_executing_immediate_quest_type == 0)
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
            gain_level(rc);
        }
    }
    if (cdata[rc].id == 326)
    {
        skillmod(183, rc, 1000);
    }
    chara_refresh(rc);
    return;
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
    if (inv[prm_930].quality != 6)
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
            if (cdata[tc_at_m163].state == 0
                || cdata[tc_at_m163].character_role == 13)
            {
                continue;
            }
        }
        if (inv[cnt].number > 0)
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
        flt(the_item_db[inv[prm_930].id]->level, 4);
        flttypeminor = the_item_db[inv[prm_930].id]->subcategory;
        inv[prm_930].number = 0;
        itemcreate(
            inv_getowner(prm_930),
            0,
            inv[prm_930].position.x,
            inv[prm_930].position.y,
            0);
        if (inv[prm_930].quality != 6)
        {
            break;
        }
    }

    txt(lang(
        n_at_m163 + u8"は"s + itemname(ci) + u8"に形を変えた。"s,
        n_at_m163 + u8" turns its shape into "s + itemname(ci) + u8"."s));
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
    fsetremain(0) = 25000;
    fsetremain(1) = 57000;
    fsetremain(2) = 57000;
    fsetremain(3) = 77000;
    fsetremain(4) = 53000;
    fsetremain(5) = 52000;
    fsetremain(6) = 57000;
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
    isetdeed(0) = 344;
    isetdeed(1) = 521;
    isetdeed(2) = 522;
    isetdeed(3) = 542;
    isetdeed(4) = 543;
    isetdeed(5) = 555;
    isetdeed(6) = 572;
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
    giftn(0) = lang(u8"つまらない"s, u8"cheap"s);
    giftn(1) = lang(u8"普通の"s, u8"so so"s);
    giftn(2) = lang(u8"ちょっとドキドキする"s, u8"exciting"s);
    giftn(3) = lang(u8"高価な"s, u8"expensive"s);
    giftn(4) = lang(u8"気絶しそうなほど素晴らしい"s, u8"hot and gorgeous"s);
    giftn(5) = lang(u8"王様が羨むほどの"s, u8"crazy epic"s);
    giftn(6) = u8"bug"s;
    moneyboxn(0) = lang(u8"5百金貨"s, u8"500 GP"s);
    moneyboxn(1) = lang(u8"2千金貨"s, u8"2k GP"s);
    moneyboxn(2) = lang(u8"1万金貨"s, u8"10K GP"s);
    moneyboxn(3) = lang(u8"5万金貨"s, u8"50K GP"s);
    moneyboxn(4) = lang(u8"50万金貨"s, u8"500K GP"s);
    moneyboxn(5) = lang(u8"500万金貨"s, u8"5M GP"s);
    moneyboxn(6) = lang(u8"1億金貨"s, u8"500M GP"s);
    biten(0) = lang(u8"ミジンコ"s, u8"water flea"s);
    biten(1) = lang(u8"バッタ"s, u8"grasshopper"s);
    biten(2) = lang(u8"テントウ"s, u8"ladybug"s);
    biten(3) = lang(u8"トンボ"s, u8"dragonfly"s);
    biten(4) = lang(u8"セミ"s, u8"locust"s);
    biten(5) = lang(u8"ヘラクレス"s, u8"beetle"s);
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
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(msgtemp, cnt);
        csvsort(s, msgtemp, 44);
        booktitle(elona::stoi(s(0))) = lang(s(1), s(2));
        if (elona::stoi(s(3)) == 1)
        {
            isetbook(p) = elona::stoi(s(0));
            ++p;
        }
    }
    magebookn(0) = lang(u8"ヴォイニッチ写本"s, u8"Voynich Manuscript"s);
    magebookn(1) = lang(u8"ドール賛歌"s, u8"Dhol Chants"s);
    magebookn(2) = lang(u8"ポナペ教教典"s, u8"Ponape Scripture"s);
    magebookn(3) = lang(u8"グラーキ黙示録"s, u8"Revelations of Glaaki"s);
    magebookn(4) = lang(u8"グ＝ハーン断章"s, u8"G'harne Fragments"s);
    magebookn(5) = lang(u8"断罪の書"s, u8"Liber Damnatus"s);
    magebookn(6) = lang(u8"ドジアンの書"s, u8"Book of Dzyan"s);
    magebookn(7) = lang(u8"エイボンの書"s, u8"Book of Eibon"s);
    magebookn(8) = lang(u8"大いなる教書"s, u8"Grand Grimoire"s);
    magebookn(9) = lang(u8"セラエノ断章"s, u8"Celaeno Fragments"s);
    magebookn(10) = lang(u8"ネクロノミコン"s, u8"Necronomicon"s);
    magebookn(11) = lang(u8"ルルイエ異本"s, u8"The R'lyeh Text"s);
    magebookn(12) = lang(u8"エルトダウン・シャールズ"s, u8"Eltdown Shards"s);
    magebookn(13) = lang(u8"金枝篇"s, u8"The Golden Bough"s);
    magebookn(14) = lang(u8"終焉の書"s, u8"Apocalypse"s);
    return;
}



void character_drops_item()
{
    int lootrich = 0;
    if (rc == 0)
    {
        if (gdata_executing_immediate_quest_type != 0)
        {
            return;
        }
        for (const auto& cnt : items(rc))
        {
            ci = cnt;
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (mdata(7) == 0)
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
            if (the_item_db[inv[ci].id]->is_cargo == 1)
            {
                if (mdata(6) != 1 && mdata(6) != 5 && mdata(6) != 3
                    && mdata(6) != 4 && mdata(6) != 6 && mdata(6) != 2)
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
                if (inv[ci].curse_state == curse_state_t::blessed)
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
                if (inv[ci].curse_state == curse_state_t::doomed)
                {
                    if (rnd(2))
                    {
                        f = 0;
                    }
                }
            }
            else if (
                inv[ci].identification_state
                == identification_state_t::completely_identified)
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
                cdata_body_part(rc, inv[ci].body_part) =
                    cdata_body_part(rc, inv[ci].body_part) / 10000 * 10000;
                inv[ci].body_part = 0;
            }
            f = 0;
            if (ibit(5, ci) == 0)
            {
                if (rnd(4) == 0)
                {
                    f = 1;
                }
                if (inv[ci].curse_state == curse_state_t::blessed)
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
                if (inv[ci].curse_state == curse_state_t::doomed)
                {
                    if (rnd(3) == 0)
                    {
                        f = 1;
                    }
                }
            }
            if (f)
            {
                inv[ci].number = 0;
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
            inv[ci].number = 0;
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
    if (gdata_current_map == 33)
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
        if (inv[cnt].number == 0)
        {
            continue;
        }
        ci = cnt;
        f = 0;
        if (cdata[rc].character_role == 20)
        {
            break;
        }
        if (inv[ci].quality > 4 || inv[ci].id == 55)
        {
            f = 1;
        }
        if (rnd(30) == 0)
        {
            f = 1;
        }
        if (cdata[rc].quality >= 4)
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
        if (gdata_current_map == 6)
        {
            if (rnd(4))
            {
                f = 0;
            }
        }
        if (inv[ci].quality == 6)
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
                    if (inv[ci].quality >= 3)
                    {
                        if (rnd(3))
                        {
                            txtef(9);
                            txt(lang(
                                name(catitem) + u8"は"s + itemname(ci)
                                    + u8"をぺろぺろと舐めた。"s,
                                name(catitem) + " licks " + itemname(ci)
                                    + "."));
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
            cdata_body_part(rc, inv[ci].body_part) =
                cdata_body_part(rc, inv[ci].body_part) / 10000 * 10000;
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
        inv[ci].number = 0;
    }
    if (cdata[rc].quality >= 4 || rnd(20) == 0 || cdata[rc].drops_gold() == 1
        || rc < 16)
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
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 7:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 3:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 2:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 4:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 5:
        if (rnd(50) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
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
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetwear(rnd(length(fsetwear)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(40) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetweapon(rnd(length(fsetweapon)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 1:
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
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
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
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
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 32000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 34000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 4:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetwear(rnd(length(fsetwear)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetweapon(rnd(length(fsetweapon)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(20) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    case 5:
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetwear(rnd(length(fsetwear)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = fsetweapon(rnd(length(fsetweapon)));
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(15) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 54000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 52000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(5) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 53000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(10) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 72000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 68000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(4) == 0)
        {
            p = 0;
            flt(calcobjlv(cdata[tc].level), calcfixlv(2));
            flttypemajor = 77000;
            flttypeminor = 0;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        break;
    }

    if (rnd(40) == 0)
    {
        p = 0;
        flt(calcobjlv(cdata[tc].level), calcfixlv(2));
        flttypemajor = 62000;
        flttypeminor = 0;
        itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        remain_make(ci, rc);
    }
    if (gdata_current_map == 35)
    {
        cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
        return;
    }
    if (gdata_current_map != 6 && cdata[rc].character_role != 20)
    {
        if (rnd(175) == 0 || cdata[rc].quality == 6 || 0
            || (cdata[rc].quality == 4 && rnd(2) == 0)
            || (cdata[rc].quality == 5 && rnd(3) == 0))
        {
            flt();
            itemcreate(-1, 504, cdata[rc].position.x, cdata[rc].position.y, 0);
            inv[ci].param1 = cdata[rc].image;
            inv[ci].subname = cdata[rc].id;
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (rnd(175) == 0 || cdata[rc].quality == 6 || 0
            || (cdata[rc].quality == 4 && rnd(2) == 0)
            || (cdata[rc].quality == 5 && rnd(3) == 0))
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
    if (rollanatomy == 1 || cdata[rc].quality >= 4 || 0
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
                    inv[ci].number +=
                        rnd(1 + (sdata(161, 0) > cdata[rc].level));
                }
            }
        }
    }
    lootrich = -1;
    if (cdata[rc].id == 183)
    {
        lootrich = 8;
    }
    if (cdata[rc].id == 184)
    {
        lootrich = 4;
    }
    if (cdata[rc].id == 185)
    {
        lootrich = 2;
    }
    if (lootrich != -1)
    {
        for (int cnt = 0, cnt_end = (lootrich); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata[rc].level));
            flttypeminor = 77001;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
        if (rnd(3) == 0)
        {
            flt();
            itemcreate(-1, 284, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    drop(0) = -1;
    drop(1) = -1;
    drop(2) = -1;
    drop(3) = -1;
    drop(4) = -1;
    drop(5) = -1;
    drop(6) = -1;
    drop(7) = -1;
    drop(8) = -1;
    drop(9) = -1;
    drop(10) = -1;
    if (cdata[rc].id == 140)
    {
        drop(0) = 355;
        drop(1) = -1;
    }
    if (cdata[rc].id == 175 || cdata[rc].id == 177 || cdata[rc].id == 178)
    {
        if (npcmemory(0, cdata[rc].id) == 0)
        {
            drop(0) = 290;
            drop(1) = 421;
            drop(2) = -1;
        }
        else
        {
            drop(0) = 421;
            drop(1) = 421;
            drop(2) = -1;
        }
    }
    if (gdata_current_map == 37)
    {
        if (cdata[rc].id == 257)
        {
            drop(0) = 665;
            drop(1) = 55;
            drop(2) = 55;
            drop(3) = 55;
            drop(4) = 55;
            drop(5) = 621;
            drop(6) = -1;
        }
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (drop(cnt) == -1)
        {
            break;
        }
        flt();
        itemcreate(
            -1, drop(cnt), cdata[rc].position.x, cdata[rc].position.y, 0);
    }
    if (cdata[rc].id == 5)
    {
        if (rnd(200) == 0)
        {
            flt();
            itemcreate(-1, 702, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 21)
    {
        if (rnd(100) == 0)
        {
            flt();
            itemcreate(-1, 706, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 34)
    {
        if (rnd(4) == 0)
        {
            flt();
            itemcreate(-1, 717, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 99 || cdata[rc].id == 100 || cdata[rc].id == 101)
    {
        if (rnd(300) == 0)
        {
            flt();
            itemcreate(-1, 708, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 117)
    {
        if (rnd(140) == 0)
        {
            flt();
            itemcreate(-1, 720, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 168)
    {
        if (rnd(100) == 0)
        {
            flt();
            itemcreate(-1, 740, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id >= 302 && cdata[rc].id <= 305)
    {
        if (rnd(90) == 0)
        {
            flt();
            itemcreate(-1, 771, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 307 || cdata[rc].id == 308)
    {
        if (rnd(150) == 0)
        {
            flt();
            itemcreate(-1, 709, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 189 || cdata[rc].id == 190)
    {
        if (rnd(150) == 0)
        {
            flt();
            itemcreate(-1, 711, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 213)
    {
        if (rnd(50) == 0)
        {
            flt();
            int stat = itemcreate(
                -1, 672, cdata[rc].position.x, cdata[rc].position.y, 0);
            if (stat != 0)
            {
                inv[ci].param1 = 169;
            }
        }
    }
    if (cdata[rc].id == 250)
    {
        if (rnd(200) == 0)
        {
            flt();
            itemcreate(-1, 715, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 341)
    {
        if (rnd(3) == 0)
        {
            flt();
            itemcreate(-1, 635, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 85 || cdata[rc].id == 86 || cdata[rc].id == 87)
    {
        if (rnd(600) == 0)
        {
            flt();
            itemcreate(-1, 737, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 302)
    {
        for (int cnt = 0, cnt_end = (2 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt(cdata[rc].level, 2);
            flttypemajor = 92000;
            nostack = 1;
            itemcreate(-1, 0, cdata[rc].position.x, cdata[rc].position.y, 0);
            if (inv[ci].value < 800)
            {
                inv[ci].number = rnd(5) + 1;
            }
        }
    }
    if (cdata[rc].id == 328)
    {
        flt();
        itemcreate(
            -1, 55, cdata[rc].position.x, cdata[rc].position.y, 1 + rnd(3));
        if (rnd(2))
        {
            flt();
            itemcreate(-1, 622, cdata[rc].position.x, cdata[rc].position.y, 0);
        }
    }
    if (cdata[rc].id == 329)
    {
        flt();
        itemcreate(
            -1,
            54,
            cdata[rc].position.x,
            cdata[rc].position.y,
            2500 + rnd((cdata[0].fame + 1000)));
    }
    if (cdata[rc].id == 351 || cdata[rc].id == 352)
    {
        for (int cnt = 0; cnt < 12; ++cnt)
        {
            flt();
            nostack = 1;
            int stat = itemcreate(
                -1, 772, cdata[rc].position.x, cdata[rc].position.y, 0);
            if (rnd(2))
            {
                if (stat != 0)
                {
                    inv[ci].param3 = -1;
                    inv[ci].image = 336;
                }
            }
        }
    }
    cell_refresh(cdata[rc].position.x, cdata[rc].position.y);
    if (cdata[rc].character_role == 13)
    {
        supply_new_equipment();
    }
    return;
}



void food_gets_rotten()
{
    i = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
        + gdata_year * 24 * 30 * 12;
    for (int cnt = 0; cnt < 246; ++cnt)
    {
        if (cnt == ELONA_MAX_CHARACTERS)
        {
            p = -1;
        }
        else
        {
            p = cnt;
            if (cdata[p].state == 0)
            {
                continue;
            }
        }
        for (const auto& cnt : items(p))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].material == 35)
            {
                if (inv[cnt].param3 > 0)
                {
                    if (inv[cnt].param3 <= i)
                    {
                        if (inv[cnt].own_state <= 0)
                        {
                            if (p == -1)
                            {
                                if (inv[cnt].id == 204)
                                {
                                    if (chipm(
                                            0,
                                            map(inv[cnt].position.x,
                                                inv[cnt].position.y,
                                                0))
                                        == 1)
                                    {
                                        if (gdata_weather != 0)
                                        {
                                            continue;
                                        }
                                        txt(lang(
                                            itemname(cnt)
                                                + u8"は上手い具合に干された。"s,
                                            itemname(cnt) + is2(inv[cnt].number)
                                                + u8" dried up in the sun."s));
                                        inv[cnt].param3 = gdata_hour
                                            + gdata_day * 24
                                            + gdata_month * 24 * 30
                                            + gdata_year * 24 * 30 * 12 + 2160;
                                        inv[cnt].image = 337;
                                        inv[cnt].id = 571;
                                        inv[cnt].param1 = 0;
                                        inv[cnt].param2 = 5;
                                        cell_refresh(
                                            inv[cnt].position.x,
                                            inv[cnt].position.y);
                                        continue;
                                    }
                                }
                            }
                            if (p != -1)
                            {
                                if (p < 16)
                                {
                                    txt(lang(
                                        itemname(cnt) + u8"は腐った。"s,
                                        itemname(cnt) + u8" rot"s
                                            + _s2(inv[cnt].number) + u8"."s));
                                }
                            }
                            inv[cnt].param3 = -1;
                            inv[cnt].image = 336;
                            if (p == -1)
                            {
                                cell_refresh(
                                    inv[cnt].position.x, inv[cnt].position.y);
                            }
                            if (p == 0)
                            {
                                if (cdata[0].god_id == core_god::kumiromi)
                                {
                                    i = the_item_db[inv[cnt].id]->subcategory;
                                    if (rnd(3) == 0)
                                    {
                                        txt(lang(
                                            u8"あなたは"s + itemname(cnt)
                                                + u8"から種を取り出した。"s,
                                            u8"You extract plant seeds from "s
                                                + itemname(cnt) + u8"."s));
                                        p = rnd(inv[cnt].number) + 1;
                                        removeitem(cnt, inv[cnt].number);
                                        flt(calcobjlv(cdata[0].level));
                                        flttypeminor = 58500;
                                        itemcreate(0, 0, -1, -1, p);
                                        p = 0;
                                        i = gdata_hour + gdata_day * 24
                                            + gdata_month * 24 * 30
                                            + gdata_year * 24 * 30 * 12;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}



void damage_by_cursed_equipments()
{
    if (rnd(4) == 0)
    {
        dmghp(cc, cdata[cc].hp * (5 + cdata[cc].curse_power / 5) / 100, -5);
        return;
    }
    if (mdata(6) != 1)
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
            if (is_in_fov(cc))
            {
                txtef(8);
                txt(lang(
                    u8"悪意のある手が"s + name(cc)
                        + u8"の財布から金貨を抜き去った。"s,
                    u8"A malicious hand filches some gold pieces from "s
                        + name(cc) + your(cc) + u8" wallet."s));
            }
            return;
        }
    }
    return;
}



void proc_pregnant()
{
    if (rnd(15) == 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は不安げに腹を押さえた。"s,
                name(cc) + u8" pat"s + _s(cc) + u8" "s + his(cc)
                    + u8" stomach uneasily."s));
            txt(lang(
                    u8"「なにかが産まれそうだよ！」"s,
                    u8"\"I'm going to have a baby!\""s),
                lang(
                    u8"「腹になにかが…」"s,
                    u8"\"Something is wrong with my stomach...\""s));
        }
    }
    if (mdata(6) != 1)
    {
        if (rnd(30) == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"何かが"s + name(cc) + u8"の腹を破り飛び出した！"s,
                    u8"Something splits "s + name(cc) + your(cc)
                        + u8" body and breaks out!"s));
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
                    || instr(cdatan(0, cc), 0, lang(u8"の子供"s, u8"child"s))
                        != -1)
                {
                    cdatan(0, rc) = lang(u8"エイリアンの子供"s, u8"alien kid"s);
                }
                else
                {
                    cdatan(0, rc) = lang(
                        cdatan(0, cc) + u8"の子供"s,
                        u8"child of "s + cdatan(0, cc));
                }
            }
        }
    }
    return;
}



void proc_negative_equipments()
{
    for (int i = 0; i < 30; ++i)
    {
        if (cdata_body_part(cc, i) % 10000 == 0)
        {
            continue;
        }
        ci = cdata_body_part(cc, i) % 10000 - 1;
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[ci].enchantments[cnt].id == 0)
            {
                break;
            }
            if (inv[ci].enchantments[cnt].id == 21)
            {
                if (mdata(6) != 1)
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
                    if (is_in_fov(cc))
                    {
                        txtef(8);
                        txt(lang(
                            u8"何かが"s + name(cc) + u8"の血を吸った。"s,
                            u8"Something sucks "s + name(cc) + your(cc)
                                + u8" blood."s));
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
                    if (is_in_fov(cc))
                    {
                        txtef(8);
                        txt(lang(
                            name(cc) + u8"は未熟になった。"s,
                            name(cc) + u8" become"s + _s(cc)
                                + u8" inexperienced."s));
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
                if (mdata(6) != 1)
                {
                    if (mdata(6) != 5)
                    {
                        if (rnd(50)
                            < clamp(
                                  std::abs(inv[ci].enchantments[cnt].power)
                                      / 50,
                                  1,
                                  50))
                        {
                            if (is_in_fov(cc))
                            {
                                txtef(8);
                                txt(lang(
                                    u8"魔力の渦が何かを召喚した！"s,
                                    u8"Several creatures are summoned from a vortex of magic."s));
                            }
                            for (int cnt = 0, cnt_end = (1 + rnd(3));
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(calcobjlv(cdata[0].level * 3 / 2 + 3),
                                    calcfixlv(2));
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
    return;
}



void auto_identify()
{
    if (cdata[0].confused != 0 || cdata[0].sleep != 0 || cdata[0].paralyzed != 0
        || cdata[0].choked != 0)
    {
        return;
    }
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number == 0
            || inv[cnt].identification_state
                == identification_state_t::completely_identified)
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
            item_identify(
                inv[ci], identification_state_t::completely_identified);
            itemmemory(0, inv[ci].id) = 1;
            if (config::instance().hideautoidentify <= 1)
            {
                txt(lang(
                    u8"バックパックの中の"s + s + u8"は"s + itemname(ci)
                        + u8"だと判明した。"s,
                    u8"You appraise "s + s + u8" as "s + itemname(ci)
                        + u8"."s));
            }
            skillexp(162, 0, 50);
        }
        if (inv[ci].identification_state
            <= identification_state_t::partly_identified)
        {
            if (p > rnd(p(1)))
            {
                if (config::instance().hideautoidentify == 0)
                {
                    txt(lang(
                        u8"バックパックの中の"s + itemname(ci) + u8"は"s
                            + i18n::_(
                                  u8"ui", u8"quality", u8"_"s + inv[ci].quality)
                            + u8"だという感じがする。"s,
                        u8"You sense the quality of "s + itemname(ci)
                            + u8" is "s
                            + i18n::_(
                                  u8"ui", u8"quality", u8"_"s + inv[ci].quality)
                            + u8"."s));
                }
                item_identify(
                    inv[ci], identification_state_t::almost_identified);
                skillexp(162, 0, 50);
            }
        }
    }
    return;
}



void lovemiracle(int prm_932)
{
    if (rnd(2) || prm_932 == 0)
    {
        return;
    }
    cibk = ci;
    txtef(9);
    txt(lang(u8"「あ…！」"s, u8"\"Uh...!\""s));
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
    snd(107);
    animeload(15, prm_932);
    return;
}



void get_pregnant()
{
    if (encfind(tc, 48) != -1)
    {
        if (is_in_fov(tc))
        {
            txt(lang(
                u8"しかしすぐに吐き出した。"s,
                u8"But "s + he(tc) + u8" puke"s + _s(tc)
                    + u8" it out quickly."s));
        }
        return;
    }
    if (cdata[tc].is_pregnant() == 0)
    {
        txtef(5);
        txt(lang(
            name(tc) + u8"は寄生された。"s,
            name(tc) + u8" get"s + _s(tc) + u8" pregnant."s));
        animeload(8, tc);
        cdata[tc].is_pregnant() = true;
    }
    return;
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



turn_result_t show_house_board()
{
    txtnew();
    if (mdata(6) != 5)
    {
        ++msgdup;
        txt(lang(
            u8"ここはあなたの家ではない。"s,
            u8"You can only use it in your home."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;
    for (const auto& cnt : items(-1))
    {
        ++p(2);
        if (inv[cnt].number != 0)
        {
            if (the_item_db[inv[cnt].id]->category != 60000)
            {
                ++p;
            }
            else
            {
                ++p(1);
            }
        }
    }
    if (mdata(18) != 0)
    {
        p(2) = mdata(18);
    }
    txt(lang(
        mapname(gdata_current_map) + u8"には"s + p + u8"個のアイテムと"s + p(1)
            + u8"個の家具がある(アイテム最大"s + p(2) + u8"個) "s,
        u8"There are "s + p + u8" items and "s + p(1) + u8" furniture in "s
            + mapname(gdata_current_map) + u8".(Max: "s + p(2) + u8") "s));
    if (adata(16, gdata_current_map) == 102)
    {
        if (getworker(gdata_current_map) != -1)
        {
            txt(lang(
                u8"現在の店主は"s + cdatan(0, getworker(gdata_current_map))
                    + u8"だ。"s,
                u8"Current shopkeeper is "s
                    + cdatan(0, getworker(gdata_current_map)) + u8"."s));
        }
        else
        {
            txt(lang(
                u8"現在店主はいない。"s,
                u8"You haven't assigned a shopkeeper yet."s));
        }
    }
    if (adata(16, gdata_current_map) == 31)
    {
        if (getworker(gdata_current_map) != -1)
        {
            txt(lang(
                u8"現在のブリーダーは"s
                    + cdatan(0, getworker(gdata_current_map)) + u8"だ。"s,
                u8"Current breeder is "s
                    + cdatan(0, getworker(gdata_current_map)) + u8"."s));
        }
        else
        {
            txt(lang(
                u8"現在ブリーダーはいない。"s,
                u8"You haven't assigned a breeder yet."s));
        }
    }
    if (gdata_current_map == 7)
    {
        p = 0;
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].state == 1 || cdata[cnt].state == 2)
            {
                if (cdata[cnt].character_role != 0)
                {
                    ++p;
                }
            }
        }
        txt(lang(
            u8"現在"s + p + u8"人の滞在者がいる(最大"s + (gdata_home_scale + 2)
                + u8"人) "s,
            ""s + p + u8" members are staying at your home. (Max: "s
                + (gdata_home_scale + 2) + u8")."s));
    }
    txtnew();
    txt(lang(u8"何をする？"s, u8"What do you want to do?"s));
    p = 0;
    if (adata(16, gdata_current_map) == 102)
    {
        ELONA_APPEND_PROMPT(
            lang(u8"仲間に店主を頼む"s, u8"Assign a shopkeeper"s),
            u8"null"s,
            ""s + 4);
        if (mdata(18) < 400)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"店を拡張"s, u8"Extend"s) + u8"("s + calcshopreform()
                    + u8" GP)"s,
                u8"null"s,
                ""s + 5);
        }
    }
    if (adata(16, gdata_current_map) == 31)
    {
        ELONA_APPEND_PROMPT(
            lang(u8"ブリーダーを任命する"s, u8"Assign a breeder"s),
            u8"null"s,
            ""s + 4);
    }
    ELONA_APPEND_PROMPT(
        lang(u8"家の模様替え"s, u8"Design"s), u8"null"s, ""s + 0);
    if (gdata_current_map == 7)
    {
        ELONA_APPEND_PROMPT(
            lang(u8"家の情報"s, u8"Home rank"s), u8"null"s, ""s + 2);
        ELONA_APPEND_PROMPT(
            lang(u8"仲間の滞在"s, u8"Allies in your home"s),
            u8"null"s,
            ""s + 4);
        if (gdata_current_dungeon_level == 1)
        {
            ELONA_APPEND_PROMPT(
                lang(u8"使用人を募集する"s, u8"Recruit a servant"s),
                u8"null"s,
                ""s + 6);
        }
        ELONA_APPEND_PROMPT(
            lang(u8"滞在者の移動"s, u8"Move a stayer"s), u8"null"s, ""s + 3);
    }
    int stat = show_prompt(promptx, prompty, 240);
    if (stat == -1)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    rtval = stat;
    switch (rtval)
    {
    case 0: start_home_map_mode(); break;
    case 2: show_home_value(); break;
    case 3: prompt_move_ally(); break;
    case 4: prompt_ally_staying(); break;
    case 5: try_extend_shop(); break;
    case 6: prompt_hiring(); break;
    }
    tlocinitx = 0;
    tlocinity = 0;
    screenupdate = -1;
    update_screen();
    return turn_result_t::show_house_board;
}


void monster_respawn()
{
    if (adata(16, gdata_current_map) == 101
        || adata(16, gdata_current_map) == 102)
    {
        if (gdata_crowd_density < mdata(10) / 2)
        {
            if (rnd(2) == 0)
            {
                chara_set_generation_filter();
                chara_create(-1, dbid, -2, 0);
            }
        }
    }
    if (mdata(10) == 0)
    {
        return;
    }
    if (gdata_crowd_density < mdata(10) / 4)
    {
        if (rnd(2) == 0)
        {
            chara_set_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (gdata_crowd_density < mdata(10) / 2)
    {
        if (rnd(4) == 0)
        {
            chara_set_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    if (gdata_crowd_density < mdata(10))
    {
        if (rnd(8) == 0)
        {
            chara_set_generation_filter();
            chara_create(-1, dbid, -2, 0);
        }
    }
    return;
}



turn_result_t exit_map()
{
    int fixstart = 0;
    gdata_left_minutes_of_executing_quest = 0;
    gdata(171) = 0;
    if (mdata(6) == 5)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(201) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(201) = 1;
                        ghelp = 1;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (mdata(6) == 7)
    {
        rq = gdata_executing_immediate_quest;
        quest_exit_map();
    }
    msg_newline();
    msgtemp = u8"  "s;
    if (gdata_current_map == 35 || gdata_current_map == 6
        || gdata_current_map == 40)
    {
        usermapid = 0;
    }
    rdtry = 0;
    fixstart = 0;
    if (adata(16, gdata_current_map) == 8)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (adata(20, gdata_current_map) > 0)
            {
                chara_vanquish(adata(20, gdata_current_map));
                adata(20, gdata_current_map) = -1;
            }
        }
    }
    gdata_previous_map = gdata_current_map;
    if (gdata_previous_map == 30)
    {
        gdata_current_map = gdata_previous_map2;
        gdata_current_dungeon_level = gdata_previous_dungeon_level;
        mapstartx = gdata_previous_x;
        mapstarty = gdata_previous_y;
        gdata_entrance_type = 7;
        fixstart = 1;
        levelexitby = 5;
    }
    if (levelexitby == 4)
    {
        cell_featread(cdata[0].position.x, cdata[0].position.y);
        if (gdata_current_map == 7)
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
            msgtemp +=
                lang(u8"階段を降りた。"s, u8"You walk down the stairs. "s);
            f = 1;
            gdata_entrance_type = 1;
            mdata(4) = cdata[0].position.y * 1000 + cdata[0].position.x;
            if (feat(2) == 0)
            {
                ++gdata_current_dungeon_level;
                gdata_current_dungeon_level -=
                    (adata(3, gdata_current_map) == 2) * 2;
            }
            else
            {
                gdata_current_dungeon_level = feat(2);
            }
        }
        if (feat(1) == 10)
        {
            msgtemp += lang(u8"階段を昇った。"s, u8"You walk up the stairs. "s);
            f = 1;
            gdata_entrance_type = 2;
            mdata(5) = cdata[0].position.y * 1000 + cdata[0].position.x;
            if (feat(2) == 0)
            {
                --gdata_current_dungeon_level;
                gdata_current_dungeon_level +=
                    (adata(3, gdata_current_map) == 2) * 2;
            }
            else
            {
                gdata_current_dungeon_level = feat(2);
            }
        }
        if (f == 0)
        {
            if (mdata(6) == 1)
            {
                gdata_pc_home_x = cdata[cc].position.x;
                gdata_pc_home_y = cdata[cc].position.y;
                gdata_current_dungeon_level = 1;
                if (feat(2) != 0 || feat(3) != 0)
                {
                    gdata_current_map = feat(2) + feat(3) * 100;
                    if (adata(16, gdata_current_map) == 42)
                    {
                        if (itemfind(0, 742) == -1)
                        {
                            txt(lang(
                                u8"あなたはこの洞窟の探索を許可されていない。"s,
                                u8"You are not permitted to explore this dungeon."s));
                            msg_halt();
                            gdata_current_map = 2;
                        }
                    }
                    if (adata(16, gdata_current_map) == 37)
                    {
                        if (gdata_pyramid_trial == 0)
                        {
                            txt(lang(
                                u8"あなたはピラミッドへの招待状を持っていない。"s,
                                u8"You don't have an invitation."s));
                            msg_halt();
                            gdata_current_map = 2;
                        }
                    }
                    if (adata(16, gdata_current_map) == 41)
                    {
                        txt(lang(
                            u8"あなたはガードに追い返された。"s,
                            u8"The guards turn you away from the jail."s));
                        msg_halt();
                        gdata_current_map = 2;
                    }
                }
                else
                {
                    gdata_current_map = 2;
                }
                if (feat(1) != 15)
                {
                    gdata_current_map = 2;
                }
            }
            if (mdata(6) == 3 || mdata(6) == 4 || mdata(6) == 5 || mdata(6) == 6
                || mdata(6) == 2)
            {
                gdata_current_map = gdata(850);
            }
        }
        if (mdata(6) >= 20 || mdata(6) == 6)
        {
            if (gdata_current_dungeon_level < adata(17, gdata_current_map))
            {
                gdata_current_map = gdata(850);
            }
        }
        if (adata(0, gdata_current_map) == 3)
        {
            if (gdata_current_map == gdata_previous_map)
            {
                if (gdata_current_dungeon_level == 1)
                {
                    msgtemp += lang(
                        mapname(gdata_current_map) + u8"の表層に戻った。"s,
                        u8"You returned to the surface of "s
                            + mapname(gdata_current_map));
                }
                else
                {
                    msgtemp += lang(
                        mapname(gdata_current_map) + u8"の表層を後にした。"s,
                        u8"You left the surface of "s
                            + mapname(gdata_current_map) + u8"."s);
                }
            }
        }
    }
    if (mdata(6) == 7)
    {
        gdata_current_map = gdata_previous_map2;
        gdata_current_dungeon_level = gdata_previous_dungeon_level;
        mapstartx = gdata_previous_x;
        mapstarty = gdata_previous_y;
        gdata_entrance_type = 7;
        fixstart = 1;
    }
    if (levelexitby == 2)
    {
        gdata_current_map = gdata_destination_map;
        gdata_current_dungeon_level = gdata_destination_dungeon_level;
        if (gdata_executing_immediate_quest_type == 0)
        {
            if (gdata_previous_map != 2)
            {
                gdata_pc_home_x = adata(1, gdata_current_map);
                gdata_pc_home_y = adata(2, gdata_current_map);
                weather_changes_by_location();
            }
        }
        if (gdata_current_map == 41)
        {
            mapstartx = 29;
            mapstarty = 3;
            gdata_entrance_type = 7;
            fixstart = 1;
        }
    }
    if (cdata[0].state == 0)
    {
        rc = 0;
        label_1540();
        gdata_current_map = 7;
        gdata(850) = adata(30, 7);
        gdata_current_dungeon_level = 1;
    }
    if (rdtry > 1)
    {
        msgtemp += u8"(再生成"s + rdtry + u8"回)"s;
    }
    if (gdata_current_map != gdata_previous_map)
    {
        if (mdata(6) == 3 || gdata_departure_date == 0
            || gdata_previous_map == 7 || mdata(6) == 2)
        {
            gdata_departure_date = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12;
            gdata_distance_between_town = 0;
            gdata_left_town_map = gdata_previous_map;
        }
        if (adata(0, gdata_current_map) != 1 && adata(0, gdata_current_map) != 4
            && gdata_current_map != 35)
        {
            autosave = 1 * (gdata_current_map != 35);
        }
        if (mdata(6) != 1)
        {
            if (mdata(6) != 4 || mdata(6) == 5)
            {
                if (fixtransfermap == 0)
                {
                    gdata_pc_home_x = adata(1, gdata_previous_map);
                    gdata_pc_home_y = adata(2, gdata_previous_map);
                }
                else
                {
                    fixtransfermap = 0;
                }
            }
        }
        if (fixstart == 0)
        {
            gdata_entrance_type = adata(3, gdata_current_map);
        }
        if (event_find(6))
        {
            msgtemp += lang(
                u8"あなたは家まで運ばれた。"s,
                u8"You were delivered to your home."s);
            weather_changes_by_location();
        }
        else if (adata(0, gdata_previous_map) == 1)
        {
            msgtemp += lang(
                mapname(gdata_current_map) + u8"に入った。"s,
                u8"You entered "s + mapname(gdata_current_map) + u8"."s);
        }
        else if (mdata(6) == 7)
        {
            msgtemp += lang(
                mapname(gdata_current_map) + u8"に戻った。"s,
                u8"You returned to "s + mapname(gdata_current_map));
        }
        else
        {
            msgtemp += lang(
                mapname(gdata_previous_map) + u8"を後にした。"s,
                u8"You left "s + mapname(gdata_previous_map) + u8"."s);
        }
        if (gdata_cargo_weight > gdata_current_cart_limit)
        {
            if (adata(0, gdata_current_map) == 1
                || adata(0, gdata_current_map) == 4)
            {
                msgtemp += lang(
                    u8"荷車の重量超過でかなり鈍足になっている！ "s,
                    u8"The weight of your cargo burdens your traveling speed."s);
            }
        }
    }
    if (gdata_current_map == 25)
    {
        if (gdata_current_dungeon_level == 2)
        {
            gdata_current_map = 26;
            gdata_current_dungeon_level = adata(10, gdata_current_map) - 1;
            gdata_entrance_type = 1;
            msgtemp += lang(
                u8"マウンテンパスに降りた。"s,
                u8"You entered the Mountain Pass."s);
        }
    }
    if (gdata_current_map == 26)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            gdata_current_map = 25;
            gdata_current_dungeon_level = 1;
            gdata_entrance_type = 2;
            msgtemp += lang(
                u8"ラーナの村に辿りついた。"s,
                u8"You reached the town of Larna."s);
        }
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        cdata[cnt].hate = 0;
        cdata[cnt].enemy_id = 0;
        rowactend(cnt);
        if (cdata[cnt].state != 1)
        {
            if (cdata[cnt].state == 8)
            {
                cdata[cnt].state = 1;
            }
            continue;
        }
        map(cdata[cnt].position.x, cdata[cnt].position.y, 1) = 0;
        if (cnt != 0)
        {
            if (cdata[cnt].current_map != 0)
            {
                cdata[cnt].state = 9;
            }
        }
    }
    if (mdata(7) == 1)
    {
        // This map should be saved.
        save_map_local_data();
    }
    else
    {
        // This is a tempory map, so wipe its data (shelter, special quest instance)
        prepare_charas_for_map_unload();

        // delete all map-local data
        if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            ctrl_file(file_operation_t::_11);
        }

        // forget about all NPCs that were here
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].state != 0)
            {
                --npcmemory(1, cdata[cnt].id);
            }
        }
    }
    mode = 2;
    return turn_result_t::initialize_map;
}



void prepare_charas_for_map_unload()
{
    // interrupt continuous actions
    for (int cnt = 0; cnt < 57; ++cnt)
    {
        rowactend(cnt);
        cdata[cnt].item_which_will_be_used = 0;
    }

    // remove living adventurers from the map and set their states
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        if (cdata[cnt].state == 1)
        {
            map(cdata[cnt].position.x, cdata[cnt].position.y, 1) = 0;
            cdata[cnt].state = 3;
        }
    }
}



void save_map_local_data()
{
    prepare_charas_for_map_unload();
    for (int y = 0; y < mdata(1); ++y)
    {
        for (int x = 0; x < mdata(0); ++x)
        {
            map(x, y, 7) = 0;
        }
    }

    // write map data and characters/skill data local to this map
    ctrl_file(file_operation_t::_2);

    // write data for items/character inventories local to this map
    ctrl_file(file_operation2_t::_4, u8"inv_"s + mid + u8".s2");
}



void label_1745()
{
    if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12
        >= adata(25, gdata_current_map))
    {
        adata(24, gdata_current_map) = rnd(10000);
        adata(25, gdata_current_map) = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 24;
    }
    if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12
        >= mdata(3))
    {
        if (mdata(17) == 0)
        {
            if (mdata(3) != 0)
            {
                for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
                {
                    y = cnt;
                    for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end;
                         ++cnt)
                    {
                        if (map(cnt, y, 6) != 0)
                        {
                            cell_featread(cnt, y);
                            if (feat(1) >= 24 && feat(1) <= 28)
                            {
                                cell_featclear(cnt, y);
                            }
                        }
                    }
                }
                for (const auto& cnt : items(-1))
                {
                    if (inv[cnt].number == 0)
                    {
                        continue;
                    }
                    if (inv[cnt].id == 526)
                    {
                        if (inv[cnt].param1 < 10)
                        {
                            inv[cnt].param1 += 1;
                            inv[cnt].image = 591;
                            cell_refresh(
                                inv[cnt].position.x, inv[cnt].position.y);
                        }
                    }
                    if (mdata(6) == 3 || mdata(6) == 2)
                    {
                        if (inv[cnt].own_state < 0)
                        {
                            ++inv[cnt].own_state;
                        }
                        if (inv[cnt].own_state == 0)
                        {
                            inv[cnt].number = 0;
                            cell_refresh(
                                inv[cnt].position.x, inv[cnt].position.y);
                        }
                    }
                }
            }
            for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                 cnt < ELONA_MAX_CHARACTERS;
                 ++cnt)
            {
                rc = cnt;
                label_1539();
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].is_temporary() == 1)
                {
                    if (rnd(2))
                    {
                        cdata[cnt].state = 0;
                        map(cdata[cnt].position.x, cdata[cnt].position.y, 1) =
                            0;
                    }
                }
            }
            p = rnd(mdata(1) * mdata(0) / 400 + 3);
            if (mdata(6) == 1)
            {
                p = rnd(40);
            }
            if (mdata(6) == 3)
            {
                p = rnd(rnd(rnd(12) + 1) + 1);
            }
            if (mdata(6) == 2)
            {
                p = rnd(p + 1);
            }
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                map_randsite();
            }
        }
        mdata(3) = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12 + 120;
    }
    if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12
        >= mdata(16))
    {
        if (mdata(16) == 0)
        {
            renewmulti = 1;
        }
        else
        {
            renewmulti = (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                          + gdata_year * 24 * 30 * 12 - mdata(16))
                    / 24
                + 1;
        }
        if (adata(16, gdata_current_map) == 31)
        {
            update_ranch();
        }
        if (adata(16, gdata_current_map) == 7)
        {
            for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                 cnt < ELONA_MAX_CHARACTERS;
                 ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].is_temporary() == 1)
                {
                    cdata[cnt].state = 0;
                    map(cdata[cnt].position.x, cdata[cnt].position.y, 1) = 0;
                }
            }
        }
        if (mdata(17) == 0)
        {
            for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
            {
                y = cnt;
                for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
                {
                    if (map(cnt, y, 6) != 0)
                    {
                        cell_featread(cnt, y);
                        x = cnt;
                        if (feat(1) == 29)
                        {
                            for (int cnt = 0, cnt_end = (renewmulti);
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                if (feat >= tile_plant + 2)
                                {
                                    break;
                                }
                                grow_plant(chipm(0, map(x, y, 0)) == 2 ? 1 : 0);
                            }
                            cell_featset(
                                cnt, y, feat, feat(1), feat(2), feat(3));
                        }
                    }
                }
            }
            if (mdata(6) == 3 || mdata(6) == 2 || gdata_current_map == 7)
            {
                for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                     cnt < ELONA_MAX_CHARACTERS;
                     ++cnt)
                {
                    if (cdata[cnt].state != 1)
                    {
                        continue;
                    }
                    generatemoney(cnt);
                    if (cdata[cnt].id == 326)
                    {
                        if (itemfind(cnt, 60005, 1) == -1)
                        {
                            if (rnd(150) == 0)
                            {
                                flt();
                                itemcreate(cnt, 707, -1, -1, 0);
                            }
                            else
                            {
                                flt(calcobjlv(cdata[cnt].level), calcfixlv());
                                flttypeminor = 60005;
                                itemcreate(cnt, 0, -1, -1, 0);
                            }
                        }
                    }
                    rc = cnt;
                    if (rnd(5) == 0)
                    {
                        supply_new_equipment();
                    }
                    if (rnd(2) == 0)
                    {
                        if (inv_sum(rc) < 8)
                        {
                            flt(calcobjlv(cdata[rc].level), calcfixlv(2));
                            int stat = itemcreate(rc, 0, -1, -1, 0);
                            if (stat != 0)
                            {
                                if (inv[ci].weight <= 0
                                    || inv[ci].weight >= 4000)
                                {
                                    inv[ci].number = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        mdata(16) = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12 + 24;
    }
    return;
}



void label_1746()
{
    gsel(6);
    if (mdata(2) != mtilefilecur)
    {
        pos(0, 0);
        picload(
            filesystem::dir::graphic() / (u8"map"s + mdata(2) + u8".bmp"), 1);
        mtilefilecur = mdata(2);
        initialize_map_chip();
    }
    map_tileset(mdata(12));
    gsel(2);
    gmode(0);
    pos(0, 0);
    gcopy(6, 0, 0, 33 * inf_tiles, 25 * inf_tiles);
    p(0) = 5;
    p(1) = 5;
    p(2) = 5;
    shade = 15;
    if (mdata(14) == 2)
    {
        if (gdata_hour >= 24)
        {
            p(0) = 110;
            p(1) = 90;
            p(2) = 60;
            shade = 8;
        }
        if (gdata_hour >= 0 && gdata_hour < 4)
        {
            p(0) = 110;
            p(1) = 90;
            p(2) = 60;
            shade = 8;
        }
        if (gdata_hour >= 4 && gdata_hour < 10)
        {
            p(0) = 70 - (gdata_hour - 3) * 10;
            p(1) = 80 - (gdata_hour - 3) * 12;
            p(2) = 60 - (gdata_hour - 3) * 10;
            if (p < 10)
            {
                p = 10;
                shade = (gdata_hour - 3) * 2 + 8;
            }
        }
        if (gdata_hour >= 10 && gdata_hour < 12)
        {
            p(0) = 10;
            p(1) = 10;
            p(2) = 10;
            shade = 25;
        }
        if (gdata_hour >= 12 && gdata_hour < 17)
        {
            p(0) = 0;
            p(1) = 0;
            p(2) = 0;
            shade = 25;
        }
        if (gdata_hour >= 17 && gdata_hour < 21)
        {
            p(0) = 0 + (gdata_hour - 17) * 20;
            p(1) = 15 + (gdata_hour - 16) * 15;
            p(2) = 10 + (gdata_hour - 16) * 10;
            shade = 12;
        }
        if (gdata_hour >= 21 && gdata_hour < 24)
        {
            p(0) = 80 + (gdata_hour - 21) * 10;
            p(1) = 70 + (gdata_hour - 21) * 10;
            p(2) = 40 + (gdata_hour - 21) * 5;
            shade = 7;
        }
        if (gdata_weather == 3)
        {
            if (p < 40)
            {
                p(0) = 40;
                p(1) = 40;
                p(2) = 40;
            }
        }
        if (gdata_weather == 4)
        {
            if (p < 65)
            {
                p(0) = 65;
                p(1) = 65;
                p(2) = 65;
            }
        }
        if (gdata_current_map == 33)
        {
            if (gdata_hour >= 17 || gdata_hour < 7)
            {
                p += 35;
                p(1) += 35;
                p(2) += 35;
            }
        }
    }
    pos(0, 0);
    gfini(33 * inf_tiles, 25 * inf_tiles);
    gfdec2(p, p(1), p(2));
    gmode(4, -1, -1, 30);
    if (mdata(2) == 0)
    {
        pos(0, 192);
        gcopy(6, 0, 192, 1360, 48);
    }
    if (mdata(2) == 1)
    {
        pos(0, 1056);
        gcopy(6, 0, 1056, 1360, 48);
    }
    if (mdata(2) != 2)
    {
        pos(0, 336);
        gcopy(6, 0, 336, 1360, 48);
    }
    gmode(0);
    gsel(0);
    gmode(2, 24, 24);
    return;
}



int initialize_world_map()
{
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (adata(16, cnt) == 8)
        {
            if (adata(20, cnt) != -1)
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
        cxinit = rnd(mdata(0));
        cyinit = rnd(mdata(1));
        label_1753();
    }
    label_1749();
    return 1;
}



void label_1748()
{
    if (gdata(79) == 1)
    {
        initialize_adata();
        label_1749();
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            adata(16, cnt) = 0;
        }
    }
    p = 0;
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (adata(16, cnt) == 0)
        {
            continue;
        }
        if (adata(16, cnt) == 8)
        {
            if (adata(20, cnt) != -1)
            {
                ++p;
            }
        }
    }
    if (p <= 25 || rnd(150) == 0 || gdata_diastrophism_flag != 0 || gdata(79))
    {
        gdata_diastrophism_flag = 0;
        msgtemp += lang(
            u8"この大陸に大きな地殻変動が起こった。"s,
            u8"A sudden diastrophism hits the continent."s);
        for (int cnt = 450; cnt < 500; ++cnt)
        {
            if (adata(16, cnt) == 8)
            {
                if (rnd(5) == 0 || adata(20, cnt) == -1)
                {
                    adata(16, cnt) = 0;
                }
            }
        }
        initialize_world_map();
        label_1749();
    }
    gdata(79) = 0;
    return;
}



void label_1749()
{
    label_1751();
    label_1750();
    return;
}



void label_1750()
{
    initialize_map_chip();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        int cnt2 = cnt;
        if (gdata(850) != 4)
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
        if (adata(16, cnt) == 0 || adata(15, cnt) == 0)
        {
            continue;
        }
        if (adata(30, cnt) != gdata(850))
        {
            continue;
        }
        if (adata(16, cnt) == 900)
        {
            adata(16, cnt) = 40;
            continue;
        }
        if (adata(16, cnt) >= 900)
        {
            adata(16, cnt) -= 800;
            continue;
        }
        if (adata(1, cnt) <= 0 || adata(2, cnt) <= 0
            || adata(1, cnt) >= mdata(0) || adata(2, cnt) >= mdata(1))
        {
            adata(1, cnt) = mdata(0) / 2;
            adata(2, cnt) = mdata(1) / 2;
        }
        p = cnt;
        if (chipm(7, map(adata(1, cnt), adata(2, cnt), 0)) & 4
            || map(adata(1, cnt), adata(2, cnt), 6) != 0)
        {
            for (int cnt = 0;; ++cnt)
            {
                dx = clamp(rnd(cnt / 4 + 1) + 1, 1, mdata(0));
                dy = clamp(rnd(cnt / 4 + 1) + 1, 1, mdata(1));
                x = adata(1, p) + rnd(dx) - rnd(dx);
                y = adata(2, p) + rnd(dy) - rnd(dy);
                if (x <= 0 || y <= 0 || x >= mdata(0) - 1 || y >= mdata(1) - 1)
                {
                    continue;
                }
                if (33 <= map(x, y, 0) && map(x, y, 0) < 66)
                {
                    continue;
                }
                if (chipm(7, map(x, y, 0)) & 4)
                {
                    continue;
                }
                if (map(x, y, 6) != 0)
                {
                    continue;
                }
                adata(1, p) = x;
                adata(2, p) = y;
                break;
            }
        }
        cell_featset(
            adata(1, cnt),
            adata(2, cnt),
            adata(15, cnt),
            15,
            cnt % 100,
            cnt / 100);
        if (adata(0, cnt) == 3 || adata(0, cnt) == 2)
        {
            map(adata(1, cnt), adata(2, cnt), 9) = 11;
        }
    }
    return;
}



void label_1751()
{
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_featread(x, y);
            if (feat(1) < 24 || feat(1) > 28)
            {
                map(x, y, 6) = 0;
            }
            map(x, y, 9) = 0;
        }
    }
    return;
}



void initialize_adata()
{
    p = 47;
    adata(16, p) = 47;
    adata(15, p) = 0;
    adata(0, p) = 1;
    adata(1, p) = 26;
    adata(2, p) = 23;
    adata(3, p) = 6;
    adata(4, p) = 2;
    adata(18, p) = 1;
    adata(9, p) = 50000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 47;
    p = 48;
    adata(16, p) = 48;
    adata(15, p) = 158;
    adata(0, p) = 2;
    adata(1, p) = 28;
    adata(2, p) = 1;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 47;
    p = 44;
    adata(16, p) = 44;
    adata(15, p) = 0;
    adata(0, p) = 1;
    adata(1, p) = 26;
    adata(2, p) = 23;
    adata(3, p) = 6;
    adata(4, p) = 2;
    adata(18, p) = 1;
    adata(9, p) = 50000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 44;
    p = 45;
    adata(16, p) = 45;
    adata(15, p) = 158;
    adata(0, p) = 2;
    adata(1, p) = 42;
    adata(2, p) = 1;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 44;
    p = 46;
    adata(16, p) = 46;
    adata(15, p) = 159;
    adata(0, p) = 2;
    adata(1, p) = 39;
    adata(2, p) = 13;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 44;
    p = 4;
    adata(16, p) = 4;
    adata(15, p) = 0;
    adata(0, p) = 1;
    adata(1, p) = 26;
    adata(2, p) = 23;
    adata(3, p) = 6;
    adata(4, p) = 2;
    adata(18, p) = 1;
    adata(9, p) = 50000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 5;
    adata(16, p) = 5;
    adata(15, p) = 132;
    adata(0, p) = 3;
    adata(1, p) = 26;
    adata(2, p) = 23;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 999;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 1;
    adata(30, p) = 4;
    p = 12;
    adata(16, p) = 12;
    adata(15, p) = 142;
    adata(0, p) = 3;
    adata(1, p) = 43;
    adata(2, p) = 32;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 999;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 2;
    adata(30, p) = 4;
    p = 15;
    adata(16, p) = 15;
    adata(15, p) = 136;
    adata(0, p) = 3;
    adata(1, p) = 53;
    adata(2, p) = 24;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 3;
    adata(30, p) = 4;
    p = 14;
    adata(16, p) = 14;
    adata(15, p) = 142;
    adata(0, p) = 3;
    adata(1, p) = 14;
    adata(2, p) = 35;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 999;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 4;
    adata(30, p) = 4;
    p = 11;
    adata(16, p) = 11;
    adata(15, p) = 132;
    adata(0, p) = 3;
    adata(1, p) = 3;
    adata(2, p) = 15;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 999;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 5;
    adata(30, p) = 4;
    p = 33;
    adata(16, p) = 33;
    adata(15, p) = 156;
    adata(0, p) = 3;
    adata(1, p) = 89;
    adata(2, p) = 14;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 6;
    adata(30, p) = 4;
    p = 36;
    adata(16, p) = 36;
    adata(15, p) = 132;
    adata(0, p) = 3;
    adata(1, p) = 61;
    adata(2, p) = 32;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 999;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(28, p) = 7;
    adata(30, p) = 4;
    p = 2;
    adata(16, p) = 2;
    adata(15, p) = 0;
    adata(0, p) = 4;
    adata(1, p) = 0;
    adata(2, p) = 0;
    adata(3, p) = 4;
    adata(4, p) = 1;
    adata(18, p) = 4;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 7;
    adata(16, p) = 7;
    adata(0, p) = 5;
    adata(3, p) = 8;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 10;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    if (gdata_home_scale == 0)
    {
        adata(15, p) = 138;
        adata(1, p) = 22;
        adata(2, p) = 21;
        adata(4, p) = 1;
        adata(18, p) = 3;
        adata(30, p) = 4;
    }
    p = 35;
    adata(16, p) = 35;
    adata(0, p) = 7;
    adata(3, p) = 8;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 1;
    adata(15, p) = 158;
    adata(1, p) = 35;
    adata(2, p) = 27;
    adata(4, p) = 1;
    adata(18, p) = 3;
    adata(30, p) = 4;
    p = 6;
    adata(16, p) = 6;
    adata(15, p) = 0;
    adata(0, p) = 7;
    adata(1, p) = 22;
    adata(2, p) = 21;
    adata(3, p) = 4;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 40;
    adata(16, p) = 40;
    adata(15, p) = 0;
    adata(0, p) = 7;
    adata(1, p) = 23;
    adata(2, p) = 21;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 13;
    adata(16, p) = 13;
    adata(15, p) = 0;
    adata(0, p) = 7;
    adata(1, p) = 22;
    adata(2, p) = 21;
    adata(3, p) = 4;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 3;
    adata(16, p) = 3;
    adata(15, p) = 139;
    adata(0, p) = 20;
    adata(1, p) = 23;
    adata(2, p) = 29;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 45;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 42;
    adata(16, p) = 42;
    adata(15, p) = 139;
    adata(0, p) = 20;
    adata(1, p) = 81;
    adata(2, p) = 51;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 50;
    adata(10, p) = 99999999;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 16;
    adata(16, p) = 16;
    adata(15, p) = 145;
    adata(0, p) = 21;
    adata(1, p) = 43;
    adata(2, p) = 4;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 15;
    adata(10, p) = 18;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 17;
    adata(16, p) = 17;
    adata(15, p) = 141;
    adata(0, p) = 20;
    adata(1, p) = 37;
    adata(2, p) = 20;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 25;
    adata(10, p) = 30;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 18;
    adata(16, p) = 18;
    adata(15, p) = 144;
    adata(0, p) = 23;
    adata(1, p) = 26;
    adata(2, p) = 44;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 17;
    adata(10, p) = 22;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 19;
    adata(16, p) = 19;
    adata(15, p) = 146;
    adata(0, p) = 20;
    adata(1, p) = 13;
    adata(2, p) = 32;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 30;
    adata(10, p) = 33;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 26;
    adata(16, p) = 26;
    adata(15, p) = 146;
    adata(0, p) = 20;
    adata(1, p) = 64;
    adata(2, p) = 43;
    adata(3, p) = 2;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 25;
    adata(10, p) = 29;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 27;
    adata(16, p) = 27;
    adata(15, p) = 146;
    adata(0, p) = 20;
    adata(1, p) = 29;
    adata(2, p) = 24;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 2;
    adata(10, p) = 5;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 38;
    adata(16, p) = 38;
    adata(15, p) = 146;
    adata(0, p) = 20;
    adata(1, p) = 43;
    adata(2, p) = 39;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 23;
    adata(10, p) = 27;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 28;
    adata(16, p) = 28;
    adata(15, p) = 146;
    adata(0, p) = 20;
    adata(1, p) = 38;
    adata(2, p) = 31;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 5;
    adata(10, p) = 5;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 37;
    adata(16, p) = 37;
    adata(15, p) = 160;
    adata(0, p) = 20;
    adata(1, p) = 4;
    adata(2, p) = 11;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 0;
    adata(9, p) = 10000;
    adata(17, p) = 20;
    adata(10, p) = 21;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 10;
    adata(16, p) = 10;
    adata(15, p) = 141;
    adata(0, p) = 6;
    adata(1, p) = 74;
    adata(2, p) = 31;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 4;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 20;
    adata(16, p) = 20;
    adata(15, p) = 147;
    adata(0, p) = 6;
    adata(1, p) = 51;
    adata(2, p) = 9;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 4;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 41;
    adata(16, p) = 41;
    adata(15, p) = 161;
    adata(0, p) = 6;
    adata(1, p) = 28;
    adata(2, p) = 37;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 12;
    adata(9, p) = 100000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    p = 21;
    adata(16, p) = 21;
    adata(15, p) = 148;
    adata(0, p) = 2;
    adata(1, p) = 21;
    adata(2, p) = 27;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 8;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 25;
    adata(16, p) = 25;
    adata(15, p) = 142;
    adata(0, p) = 2;
    adata(1, p) = 64;
    adata(2, p) = 47;
    adata(3, p) = 3;
    adata(4, p) = 1;
    adata(18, p) = 9;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 34;
    adata(16, p) = 34;
    adata(15, p) = 157;
    adata(0, p) = 2;
    adata(1, p) = 88;
    adata(2, p) = 25;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 29;
    adata(16, p) = 29;
    adata(15, p) = 162;
    adata(0, p) = 6;
    adata(1, p) = 18;
    adata(2, p) = 2;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 2;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 32;
    adata(16, p) = 32;
    adata(15, p) = 155;
    adata(0, p) = 2;
    adata(1, p) = 53;
    adata(2, p) = 21;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 43;
    adata(16, p) = 43;
    adata(15, p) = 158;
    adata(0, p) = 2;
    adata(1, p) = 27;
    adata(2, p) = 52;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 2;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 22;
    adata(16, p) = 22;
    adata(15, p) = 149;
    adata(0, p) = 6;
    adata(1, p) = 13;
    adata(2, p) = 43;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 33;
    adata(10, p) = 33;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 23;
    adata(16, p) = 23;
    adata(15, p) = 149;
    adata(0, p) = 6;
    adata(1, p) = 51;
    adata(2, p) = 32;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 33;
    adata(10, p) = 33;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 24;
    adata(16, p) = 24;
    adata(15, p) = 149;
    adata(0, p) = 6;
    adata(1, p) = 35;
    adata(2, p) = 10;
    adata(3, p) = 8;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 10000;
    adata(17, p) = 33;
    adata(10, p) = 33;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 30;
    adata(16, p) = 30;
    adata(15, p) = 0;
    adata(0, p) = 5;
    adata(1, p) = 35;
    adata(2, p) = 10;
    adata(3, p) = 1;
    adata(4, p) = 1;
    adata(18, p) = 100;
    adata(9, p) = 1000000;
    adata(17, p) = -999999;
    adata(10, p) = 999999;
    adata(21, p) = 1;
    adata(11, p) = 1;
    adata(12, p) = 1;
    adata(30, p) = 4;
    p = 9;
    adata(16, p) = 9;
    adata(15, p) = 0;
    adata(0, p) = 6;
    adata(1, p) = 20;
    adata(2, p) = 20;
    adata(3, p) = 4;
    adata(4, p) = 1;
    adata(18, p) = 4;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 45;
    adata(21, p) = 2;
    adata(11, p) = 0;
    adata(12, p) = 0;
    adata(30, p) = 4;
    return;
}



int label_1753()
{
    for (int cnt = 450; cnt < 500; ++cnt)
    {
        if (adata(16, cnt) != 0)
        {
            continue;
        }
        f = -1;
        for (int cnt = 0; cnt < 1000; ++cnt)
        {
            x = cxinit + rnd((cnt + 1)) - rnd((cnt + 1));
            y = cyinit + rnd((cnt + 1)) - rnd((cnt + 1));
            if (x <= 5 || y <= 5 || x >= mdata(0) - 6 || y >= mdata(1) - 6)
            {
                continue;
            }
            if (33 <= map(x, y, 0) && map(x, y, 0) < 66)
            {
                continue;
            }
            if (map(x, y, 0) > 19)
            {
                continue;
            }
            if (map(x, y, 6) % 1000 != 0)
            {
                continue;
            }
            p = 1;
            for (int cnt = 0; cnt < 500; ++cnt)
            {
                if (adata(16, cnt) == 0)
                {
                    continue;
                }
                if (x >= adata(1, cnt) - 2 && x <= adata(1, cnt) + 2)
                {
                    if (y >= adata(2, cnt) - 2 && y <= adata(2, cnt) + 2)
                    {
                        p = 0;
                        break;
                    }
                }
            }
            if (p == 0)
            {
                continue;
            }
            f = 1;
            break;
        }
        if (f == -1)
        {
            p = -1;
            break;
        }
        p = cnt;
        area = p;
        ctrl_file(file_operation_t::_13);
        adata(0, p) = 20 + rnd(4);
        adata(16, p) = 8;
        adata(15, p) = 133;
        adata(1, p) = x;
        adata(2, p) = y;
        adata(3, p) = 1;
        adata(4, p) = 1;
        adata(18, p) = 1;
        adata(9, p) = 10000;
        adata(21, p) = 1;
        adata(30, p) = gdata(850);
        if (rnd(3))
        {
            adata(17, p) = rnd(cdata[0].level + 5) + 1;
        }
        else
        {
            adata(17, p) = rnd(50) + 1;
            if (rnd(5) == 0)
            {
                adata(17, p) *= rnd(3) + 1;
            }
        }
        adata(10, p) = adata(17, p) + rnd(4) + 2;
        adata(11, p) = 1;
        adata(12, p) = 0;
        adata(20, p) = 0;
        adata(5, p) = rnd(length(mapnamerd));
        map(x, y, 6) = 1;
        if (adata(0, p) == 20)
        {
            adata(15, p) = 133;
            adata(18, p) = 0;
        }
        if (adata(0, p) == 21)
        {
            adata(15, p) = 137;
            adata(18, p) = 100;
        }
        if (adata(0, p) == 23)
        {
            adata(15, p) = 140;
            adata(18, p) = 200;
        }
        if (adata(0, p) == 22)
        {
            adata(15, p) = 135;
            adata(18, p) = 300;
        }
        break;
    }
    return p;
}



void label_1754()
{
    if (gdata_current_map == 33)
    {
        if (gdata_released_fire_giant == 1)
        {
            if (cdata[gdata_fire_giant].state == 1)
            {
                if (gdata_crowd_density < 70)
                {
                    if (rnd(4) == 0)
                    {
                        flt();
                        objlv = 1;
                        chara_create(-1, 204, -3, 0);
                    }
                    if (rnd(10) == 0)
                    {
                        flt();
                        objlv = 1;
                        chara_create(-1, 185, -3, 0);
                    }
                }
            }
        }
    }
    if (gdata_executing_immediate_quest_type == 1008)
    {
        if (qdata(8, gdata_executing_immediate_quest) != 3)
        {
            if (gdata_crowd_density
                < gdata_left_minutes_of_executing_quest / 60)
            {
                dbid = 0;
                if (rnd(4) == 0)
                {
                    dbid = 204;
                }
                if (rnd(10) == 0)
                {
                    dbid = 185;
                }
                if (dbid != 0)
                {
                    flt();
                    objlv = 1;
                    int stat = chara_create(-1, dbid, -3, 0);
                    if (stat != 0)
                    {
                        cdata[rc].relationship = -1;
                        cdata[rc].original_relationship = -1;
                        cdata[rc].hate = 100;
                        cdata[rc].enemy_id =
                            qdata(13, gdata_executing_immediate_quest);
                    }
                }
            }
        }
    }
    if (gdata_current_map == 16)
    {
        if (rnd(5) == 0)
        {
            r = sdata(50, 0) / 50;
            if (r < 6)
            {
                dmg = (6 - r) * (6 - r) * 2;
                txtef(3);
                txt(lang(u8"熱い！"s, u8"It's hot!"s));
                dmghp(cc, dmg, -9);
            }
        }
        return;
    }
    if (gdata_current_map == 11)
    {
        if (gdata_current_dungeon_level == 25)
        {
            ++gdata_duration_of_kamikaze_attack;
            x = 1;
            y = rnd(mdata(1));
            if (rnd(4) == 0)
            {
                x = mdata(0) - 2;
                y = rnd(mdata(1));
            }
            if (rnd(5) == 0)
            {
                x = rnd(mdata(0));
                y = 1;
            }
            if (rnd(6) == 0)
            {
                x = rnd(mdata(0));
                y = mdata(1) - 2;
            }
            p = 237;
            if (gdata_duration_of_kamikaze_attack > 50)
            {
                if (rnd(10) == 0)
                {
                    p = 245;
                }
            }
            if (gdata_duration_of_kamikaze_attack > 100)
            {
                if (rnd(10) == 0)
                {
                    p = 244;
                }
            }
            if (gdata_duration_of_kamikaze_attack > 150)
            {
                if (rnd(10) == 0)
                {
                    p = 244;
                }
            }
            if (gdata_duration_of_kamikaze_attack == 250)
            {
                snd(44);
                txtef(2);
                txt(lang(
                    u8"ジャーナルが更新された。"s,
                    u8"Your journal has been updated."s));
                gdata_kamikaze_attack = 3;
                txtef(9);
                txt(lang(
                    u8"伝令「パルミア軍の撤退が完了しました！これ以上ここに留まる必要はありません。機を見て地下から退却してください！」"s,
                    u8"The messenger "s
                        + u8"\"The retreat of our army is over now. You don't need to fight them any more. Please leave at once!\""s));
                txt(lang(u8"階段が現れた。"s, u8"Suddenly, stairs appear."s));
                cell_featset(18, 9, tile_downstairs, 11, 1);
            }
            flt();
            chara_create(-1, p, x, y);
            cdata[rc].hate = 1000;
            cdata[rc].enemy_id = 0;
            return;
        }
    }
    if (gdata_current_map == 41)
    {
        if (rnd(50) == 0)
        {
            if (cdata[0].karma < -30)
            {
                txt(lang(
                    u8"あなたは罪を悔いた。"s, u8"You repent of your sin."s));
                modify_karma(0, 1);
                p = rnd(8) + 10;
                if (sdata.get(p, 0).original_level >= 10)
                {
                    skillmod(p, 0, -300);
                }
            }
        }
        if (cdata[0].karma >= -30)
        {
            if (rnd(1000) == 0)
            {
                cell_featread(29, 6);
                if (feat(1) == 21)
                {
                    txt(lang(
                        u8"あなたはガードの足音が近づいてくるのに気付いた。"s,
                        u8"You hear footsteps coming towards your cell."s));
                    txt(lang(
                        u8"「そこのお前、もう反省したころだろう。出てもいいぞ」"s,
                        u8"\"Hey punk, our boss says you can leave the jail now. Do not come back, okay?\""s));
                    txt(lang(
                        u8"ガードは面倒くさそうにあなたの牢の扉を開けた。"s,
                        u8"A guard unenthusiastically unlocks your cell."s));
                    cell_featset(29, 6, tile_dooropen, 20, 0, -1);
                    snd(48);
                }
            }
        }
    }
    if (gdata_current_map == 30)
    {
        if (gdata_weather == 2 || gdata_weather == 4 || gdata_weather == 1)
        {
            if (cdata[0].nutrition < 5000)
            {
                if (cdata[0].has_anorexia() == 0)
                {
                    snd(18);
                    txt(lang(
                        u8"シェルターの貯蔵食品を食べた。"s,
                        u8"You eat stored food."s));
                    cdata[cc].nutrition += 5000;
                    show_eating_message();
                }
            }
            if (gdata_continuous_active_hours >= 15)
            {
                gdata_continuous_active_hours = 13;
            }
            mdata(9) = 1000000;
        }
        else if (mdata(9) == 1000000)
        {
            mdata(9) = 10000;
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                cdata[cnt].turn_cost = 0;
            }
            txt(lang(
                u8"もうシェルターの中にいる必要は無い。"s,
                u8"You don't need to stay in the shelter any longer."s));
        }
    }
    if (adata(16, gdata_current_map) == 101)
    {
        if (gdata_crowd_density > 0)
        {
            if (rnd(25) == 0)
            {
                txtef(9);
                txt(lang(u8" *ざわざわ* "s, u8"*noise*"s),
                    lang(u8"「ふむ…悪くないな」"s, u8"\"Hmm. Not bad.\""s),
                    lang(u8"「何だろう、これは」"s, u8"\"What's this?\""s),
                    lang(u8"「ほほう…」"s, u8"\"Ohh...\""s),
                    lang(
                        u8"「私も死んだらはく製に…」"s,
                        u8"\"I want to be stuffed...\""s),
                    lang(
                        u8"「ここが噂の…」"s,
                        u8"\"So this is the famous...\""s));
            }
            if (rnd(25) == 0)
            {
                txtef(9);
                txt(lang(u8" *がやがや* "s, u8"*murmur*"s),
                    lang(
                        u8"「やだっ気持ち悪い」"s, u8"\"Gross! Disgusting.\""s),
                    lang(
                        u8"「ねーねーこれ死んでるんでしょ？」"s,
                        u8"\"Hey. Is it really dead?\""s),
                    lang(u8"「かわ、いー♪」"s, u8"\"Scut!\""s),
                    lang(
                        u8"「今日はとことん見るぜ」"s,
                        u8"\"Absolutely amazing.\""s),
                    lang(u8"「触ってもいいの？」"s, u8"\"Can I touch?\""s));
            }
            if (rnd(15) == 0)
            {
                txtef(9);
                for (int cnt = 0; cnt < 1; ++cnt)
                {
                    if (en)
                    {
                        break;
                    }
                    if (gdata(123) > 8000)
                    {
                        txt(u8"「退屈ぅー」"s,
                            u8"「あまり見るものがないな」"s,
                            u8"「こんなので見物料とるの？」"s,
                            u8"館内は少し寂しい…"s);
                        break;
                    }
                    if (gdata(123) > 5000)
                    {
                        txt(u8"「いいんじゃない〜」"s,
                            u8"「まあ、普通の博物館だ」"s,
                            u8"「恋人を連れてくればよかったかも」"s,
                            u8"まあまあの客足だ。"s);
                        break;
                    }
                    if (gdata(123) > 2500)
                    {
                        txt(u8"「この雰囲気好きだなぁ」"s,
                            u8"「もう一度来ようよ」"s,
                            u8"「時間が経つのを忘れるね！」"s,
                            u8"館内はなかなか賑わっている。"s);
                        break;
                    }
                    if (gdata(123) > 500)
                    {
                        txt(u8"「来て良かった♪」"s,
                            u8"「よくこんなに集めたなあ」"s,
                            u8"「むぅ…興味深い」"s,
                            u8"客足が全く絶えない盛況ぶりだ。"s);
                        break;
                    }
                    txt(u8"「素晴らしいコレクションだ！」"s,
                        u8"「感動した」"s,
                        u8"「帰りたくないわ♪」"s,
                        u8"来客は食い入るように展示物を眺めている。"s);
                }
            }
            return;
        }
    }
    if (adata(16, gdata_current_map) == 102)
    {
        if (gdata_crowd_density > 0)
        {
            if (rnd(25) == 0)
            {
                txtef(9);
                txt(lang(u8" *ざわざわ* "s, u8"*murmur*"s),
                    lang(
                        u8"「これ欲しい〜」"s,
                        u8"\"I want this! I want this!\""s),
                    lang(u8"「何だろう、これは」"s, u8"\"Oh what's this?\""s),
                    lang(u8"「お買い物♪」"s, u8"\"I'm just watching\""s),
                    lang(u8"「金が足りん…」"s, u8"\"My wallet is empty...\""s),
                    lang(
                        u8"「ここが噂の…」"s,
                        u8"\"So this is the famous....\""s));
            }
            return;
        }
    }
    return;
}



void label_1755()
{
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].id == 555 || inv[cnt].id == 600)
        {
            continue;
        }
        inv[cnt].number = 0;
        cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
    }
    if (adata(29, gdata_current_map) == 1)
    {
        flt();
        int stat = itemcreate(-1, 763, 29, 16, 0);
        if (stat != 0)
        {
            inv[ci].own_state = 1;
        }
        {
            flt();
            int stat = itemcreate(-1, 686, 29, 16, 0);
            if (stat != 0)
            {
                inv[ci].own_state = 1;
            }
        }
        {
            flt();
            int stat = itemcreate(-1, 171, 29, 17, 0);
            if (stat != 0)
            {
                inv[ci].param1 = 6;
                inv[ci].own_state = 1;
            }
        }
        {
            flt();
            int stat = itemcreate(-1, 756, 29, 17, 0);
            if (stat != 0)
            {
                inv[ci].own_state = 5;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 345, 48, 19);
            if (stat != 0)
            {
                cdata[rc].character_role = 3;
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 348, 30, 17);
            if (stat != 0)
            {
                cdata[rc].character_role = 3;
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 174, 38, 19);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
                cdata[rc].is_hung_on_sand_bag() = true;
                cdatan(0, rc) =
                    lang(u8"オパートスの信者"s, u8"Opatos Fanatic"s);
                if (rnd(2))
                {
                    cdatan(0, rc) = lang(u8"マニの信者"s, u8"Mani Fanatic"s);
                }
                else
                {
                    cdatan(0, rc) =
                        lang(u8"エヘカトルの信者"s, u8"Ehekatl Fanatic"s);
                }
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 35, 19);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 37, 18);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 37, 21);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 39, 20);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 347, 38, 21);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 70, 17, 8);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1002;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = snfood(cdatan(0, rc));
            }
        }
        {
            flt();
            int stat = chara_create(-1, 239, 25, 8);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1018;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = randomname();
                cdatan(0, rc) = lang(
                    u8"おみやげ屋の"s + cdatan(0, rc),
                    sncnv(cdatan(0, rc)) + u8"the souvenir vendor"s);
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 24, 22);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1018;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = randomname();
                cdatan(0, rc) = lang(
                    u8"おみやげ屋の"s + cdatan(0, rc),
                    sncnv(cdatan(0, rc)) + u8"the souvenir vendor"s);
            }
        }
        {
            flt();
            int stat = chara_create(-1, 1, 38, 12);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].character_role = 1007;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = snblack(cdatan(0, rc));
                cdata[rc].only_christmas() = true;
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 28, 9);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1022;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = randomname();
                cdatan(0, rc) = lang(
                    u8"屋台商人の"s + cdatan(0, rc),
                    sncnv(cdatan(0, rc)) + u8"the street vendor"s);
            }
        }
        {
            flt();
            int stat = chara_create(-1, 271, 29, 24);
            if (stat != 0)
            {
                cdata[rc].ai_calm = 3;
                cdata[rc].relationship = 0;
                cdata[rc].original_relationship = 0;
                cdata[rc].only_christmas() = true;
                cdata[rc].character_role = 1022;
                cdata[rc].shop_rank = 30;
                cdatan(0, rc) = randomname();
                cdatan(0, rc) = lang(
                    u8"屋台商人屋の"s + cdatan(0, rc),
                    sncnv(cdatan(0, rc)) + u8"the street vendor"s);
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 349, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            flt();
            {
                int stat = chara_create(-1, 350, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 326, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
        }
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 335, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            {
                flt();
                int stat = chara_create(-1, 185, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
            {
                flt();
                int stat = chara_create(-1, 274, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
            {
                flt();
                int stat = chara_create(-1, 174, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            int stat = chara_create(-1, 332, -3, 0);
            if (stat != 0)
            {
                cdata[rc].only_christmas() = true;
            }
            {
                flt();
                int stat = chara_create(-1, 185, -3, 0);
                if (stat != 0)
                {
                    cdata[rc].only_christmas() = true;
                }
            }
        }
    }
    else
    {
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].only_christmas() == 1)
            {
                chara_vanquish(cnt);
            }
        }
    }
    return;
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



void matgetmain(int prm_1030, int prm_1031, int prm_1032)
{
    n_at_m174 = prm_1031;
    if (n_at_m174 == 0)
    {
        n_at_m174 = 1;
    }
    mat(prm_1030) += n_at_m174;
    snd(21);
    if (en)
    {
        s_at_m174 =
            u8"You get "s + n_at_m174 + u8" "s + matname(prm_1030) + u8". "s;
    }
    else
    {
        s_at_m174 = u8"マテリアル:"s + matname(prm_1030) + u8"を"s + n_at_m174
            + u8"個"s;
        if (prm_1032 == 1)
        {
            s_at_m174 += u8"掘り当てた"s;
        }
        if (prm_1032 == 2)
        {
            s_at_m174 += u8"釣り上げた。"s;
        }
        if (prm_1032 == 3)
        {
            s_at_m174 += u8"採取した。"s;
        }
        if (prm_1032 == 5)
        {
            s_at_m174 += u8"見つけた。"s;
        }
        if (prm_1032 == 0)
        {
            s_at_m174 += u8"入手した"s;
        }
    }
    txtef(4);
    txt(s_at_m174 + u8"("s + mat(prm_1030) + u8") "s);
    return;
}



void matdelmain(int prm_1033, int prm_1034)
{
    n_at_m174 = prm_1034;
    if (n_at_m174 == 0)
    {
        n_at_m174 = 1;
    }
    mat(prm_1033) -= n_at_m174;
    s_at_m174 = u8"マテリアル:"s + matname(prm_1033) + u8"を"s + n_at_m174
        + u8"個失った"s;
    txtef(4);
    txt(s_at_m174 + u8"(残り "s + mat(prm_1033) + u8"個) "s);
    return;
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
        gzoom(4, 0, 0, 240, 160, windoww, windowh - inf_verh - inf_msgh);
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
        gzoom(0, 120, 88, windoww - 120, windowh - inf_verh - 112, 200, 90);
        gsel(0);
    }
    return;
}



void begintempinv()
{
    ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
    for (const auto& cnt : items(-1))
    {
        inv[cnt].number = 0;
    }
    return;
}



void exittempinv()
{
    ctrl_file(file_operation2_t::_3, u8"shoptmp.s2");
    return;
}



void label_1892()
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
        snd(63);
    }
    if (rnd(2))
    {
        efid = 1106;
        efp = 100;
        tc = 0;
        magic();
    }
    return;
}



int proc_random_event()
{
    int id0 = 0;
    int id1 = 0;
    if (gspd < 10)
    {
        return 0;
    }
    if (dbg_skipevent)
    {
        return 0;
    }
    if (mode == 12)
    {
        return 0;
    }
    if (mode == 9)
    {
        if (!cdata[0].god_id.empty())
        {
            if (rnd(12) == 0)
            {
                id0 = 18;
            }
        }
        if (rnd(80) == 0)
        {
            id0 = 4;
            id1 = 120;
        }
        if (rnd(20) == 0)
        {
            id0 = 3;
        }
        if (rnd(25) == 0)
        {
            id0 = 2;
        }
        if (rnd(100) == 0)
        {
            id0 = 5;
            id1 = 65;
        }
        if (rnd(20) == 0)
        {
            id0 = 6;
        }
        if (rnd(20) == 0)
        {
            id0 = 7;
        }
        if (rnd(250) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 19;
            }
        }
        if (rnd(10000) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 21;
            }
        }
        if (rnd(70) == 0)
        {
            id0 = 8;
            id1 = 40;
        }
        if (rnd(200) == 0)
        {
            id0 = 20;
        }
        if (rnd(50) == 0)
        {
            id0 = 23;
        }
        if (rnd(300) == 0)
        {
            id0 = 24;
        }
        if (rnd(90) == 0)
        {
            id0 = 22;
            id1 = 70;
        }
        goto label_1894_internal;
    }
    if (mdata(6) != 1)
    {
        if (cdata[0].continuous_action_id != 0)
        {
            return 0;
        }
    }
    if (mdata(6) == 5)
    {
        return 0;
    }
    if (rnd(30) == 0)
    {
        id0 = 17;
    }
    if (rnd(25) == 0)
    {
        id0 = 16;
    }
    if (rnd(25) == 0)
    {
        id0 = 12;
    }
    if (rnd(50) == 0)
    {
        id0 = 9;
    }
    if (rnd(80) == 0)
    {
        id0 = 14;
    }
    if (rnd(50) == 0)
    {
        id0 = 8;
        id1 = 40;
    }
    if (rnd(80) == 0)
    {
        id0 = 13;
        id1 = 45;
    }
    if (mdata(6) == 3)
    {
        if (rnd(25) == 0)
        {
            id0 = 15;
            id1 = 80;
        }
        goto label_1894_internal;
    }
    if (mdata(6) == 1)
    {
        if (rnd(40))
        {
            return 0;
        }
        goto label_1894_internal;
    }
    if (rnd(25) == 0)
    {
        id0 = 10;
    }
    if (rnd(25) == 0)
    {
        id0 = 11;
    }
label_1894_internal:
    if (id0 == 0)
    {
        return 0;
    }
    cc = 0;
    tc = 0;
    listmax = 0;
    if (id1 != 0)
    {
        if (rnd(sdata(19, 0) + 1) > id1)
        {
            id0 = 1;
        }
    }
    switch (id0)
    {
    case 15:
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            p = rnd(gdata_crowd_density + 1) + 57;
            if (p >= ELONA_MAX_CHARACTERS)
            {
                --cnt;
                continue;
            }
            if (cdata[p].state == 1)
            {
                txt(lang(
                    name(p) + u8"「ぎゃぁーー！」"s,
                    name(p) + u8" screams, "s + u8"\"Ahhhhhhh!\""s));
                dmghp(p, 99999, -11);
                break;
            }
        }
        s = lang(u8"殺人鬼"s, u8"Murderer"s);
        buff = lang(
            u8"街のどこかで悲鳴があがった。あなたはガードが慌しく走っていくのを目撃した。「人殺し、人殺しだ！！」"s,
            u8"Suddenly, a painful shriek rises from somewhere in the town. You see several guards hastily run by."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"なむ…"s, u8"Sorry for you."s);
        ++listmax;
        show_random_event_window(u8"bg_re9");
        break;
    case 14:
        s = lang(u8"謎のご馳走"s, u8"Strange Feast"s);
        buff = lang(
            u8"あなたは目の前にご馳走をみつけた。"s,
            u8"You come across a strange feast."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"食べる"s, u8"(Eat)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"立ち去る"s, u8"(Leave)"s);
        ++listmax;
        show_random_event_window(u8"bg_re10");
        if (rtval == 1)
        {
            cdata[0].nutrition = 15000;
            txt(lang(u8"なかなか美味しかった。"s, u8"It was tasty."s),
                lang(u8"悪くない。"s, u8"Not bad at all."s),
                lang(u8"あなたは舌鼓をうった。"s, u8"You smack your lips."s));
            show_eating_message();
            chara_anorexia(0);
        }
        break;
    case 13:
        s = lang(u8"ご馳走の匂い"s, u8"Smell of Food"s);
        buff = lang(
            u8"どこからともなく漂うご馳走の匂いで、あなたの胃は不満を叫び始めた。"s,
            u8"A sweet smell of food floats from nowhere. Your stomach growls but you can't find out where it comes from."s);
        cdata[0].nutrition -= 5000;
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"腹減った…"s, u8"I'm hungry now!"s);
        ++listmax;
        show_random_event_window(u8"bg_re10");
        break;
    case 1:
        s = lang(u8"不運の回避"s, u8"Avoiding Misfortune"s);
        buff = lang(
            u8"あなたは一瞬嫌な予感がしたが、それはやがて消えた。"s,
            u8"You sense a bad feeling for a moment but it fades away quickly."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re8");
        break;
    case 24:
        efid = 1113;
        tc = 0;
        magic();
        s = lang(u8"才能の開花"s, u8"Your Potential"s);
        buff = lang(
            u8"突然あなたの才能は開花した！"s,
            u8"Suddenly you develop your gift!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 18:
        skillexp(181, 0, 1000, 6, 1000);
        s = lang(u8"信仰の深まり"s, u8"Gaining Faith"s);
        buff = lang(
            u8"夢の中で、あなたは偉大なる者の穏やかな威光に触れた。"s,
            u8"In your dream, a saint comes out and blesses you."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"神よ"s, u8"Great."s);
        ++listmax;
        show_random_event_window(u8"bg_re12");
        break;
    case 12:
        s = lang(u8"マテリアルの発見"s, u8"Small Luck"s);
        buff = lang(
            u8"石ころにつまずいて転んだ拍子に、あなたは幾つかのマテリアルを見つけた。"s,
            u8"You stumble over a stone and find some materials on the ground. "s);
        efid = 1117;
        efp = 100;
        tc = 0;
        magic();
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Nice."s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        break;
    case 23:
        efid = 1117;
        efp = 200;
        tc = 0;
        magic();
        s = lang(u8"夢の中の収穫"s, u8"Dream Harvest"s);
        buff = lang(
            u8"夢の中で、あなたはのんきにマテリアルを採取していた"s,
            u8"In your dream, you harvest materials peacefully."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"るん♪"s, u8"Sweet."s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        break;
    case 10:
        s = lang(u8"野営跡の発見"s, u8"Camping Site"s);
        buff = lang(
            u8"あなたは何者かが野営した跡を見つけた。辺りには食べ残しやがらくたが散らばっている。もしかしたら、何か役に立つものがあるかもしれない。"s,
            u8"You discover a camping site someone left behind. Chunks of leftovers and junks remain here. You may possibly find some useful items."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"調べる"s, u8"(Search)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"立ち去る"s, u8"(Leave)"s);
        ++listmax;
        show_random_event_window(u8"bg_re3");
        if (rtval == 1)
        {
            for (int cnt = 0, cnt_end = (1 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = fsetremain(rnd(length(fsetremain)));
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        break;
    case 4:
        snd(116);
        efid = 1118;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"不気味な夢"s, u8"Creepy Dream"s);
        buff = lang(
            u8"あなたは不気味な夢をみた。陰気な幾つもの瞳があなたを凝視し、どこからともなく笑い声がこだました。「ケラケラケラ…ミツケタヨ…ケラケラ」あなたが二度寝返りをうった後、その夢は終わった。"s,
            u8"In your dreams, several pairs of gloomy eyes stare at you and laughter seemingly from nowhere echoes around you.  \"Keh-la keh-la keh-la I found you...I found you.. keh-la keh-la keh-la\" After tossing around a couple times, the dream is gone."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"おかしな夢だ"s, u8"Strange..."s);
        ++listmax;
        show_random_event_window(u8"bg_re5");
        break;
    case 22:
        snd(116);
        efid = 454;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"怪物の夢"s, u8"Monster Dream"s);
        buff = lang(
            u8"あなたは怪物と戦っていた。醜い化け物に斬りかかろうとした時、怪物は悲鳴をあげた。「オレハオマエダ！オマエハオレダ！」あなたは自分の呻き声に起こされた。"s,
            u8"You are fighting an ugly monster. You are about to thrust a dagger into the neck of the monster. And the monster screams. \"You are me! I am you!\" You are awakened by your own low moan."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ううぅん…"s, u8"Urrgh..hh.."s);
        ++listmax;
        show_random_event_window(u8"bg_re2");
        break;
    case 19:
        flt();
        itemcreate(0, 621, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        s = lang(u8"宝を埋める夢"s, u8"Treasure of Dream"s);
        buff = lang(
            u8"あなたは夢の中で宝を埋めた。あなたはすぐに飛び起き、その場所を紙に書き留めた"s,
            u8"You buried treasure in your dream. You quickly get up and write down the location."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re15");
        break;
    case 20:
        buff_add(tc, 19, 777, 1500);
        s = lang(u8"幸運の日"s, u8"Lucky Day"s);
        buff = lang(u8"うみみゃぁ！"s, u8"Mewmewmew!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re12");
        break;
    case 21:
        flt();
        itemcreate(0, 721, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        s = lang(u8"運命の気まぐれ"s, u8"Quirk of Fate"s);
        buff =
            lang(u8"うみみゃっ、見つけたね！"s, u8"Mewmew? You've found me!"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ワァオー"s, u8"Woohoo!"s);
        ++listmax;
        show_random_event_window(u8"bg_re15");
        break;
    case 5:
        if (trait(42))
        {
            txt(lang(
                u8"あなたは祈祷を捧げ呪いのつぶやきを無効にした。"s,
                u8"Your prayer nullifies the curse."s));
        }
        else
        {
            f = 0;
            tc = 0;
            for (int i = 0; i < 30; ++i)
            {
                if (cdata_body_part(tc, i) % 10000 == 0)
                {
                    continue;
                }
                else
                {
                    f = 1;
                }
            }
            if (f)
            {
                efid = 1114;
                efp = 200;
                magic();
            }
            else if (event_id() == -1)
            {
                event_add(26);
            }
        }
        s = lang(u8"呪いのつぶやき"s, u8"Cursed Whispering"s);
        buff = lang(
            u8"どこからともなく聞こえる呪いのつぶやきが、あなたの眠りを妨げた。"s,
            u8"Your sleep is disturbed by a harshly whispering that comes from nowhere."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"眠れない…"s, u8"Can't...sleep..."s);
        ++listmax;
        show_random_event_window(u8"bg_re5");
        break;
    case 8:
        p = rnd(cdata[0].gold / 8 + 1);
        if (cdata[0].is_protected_from_thieves())
        {
            p = 0;
        }
        if (p > 0)
        {
            txt(lang(
                u8"金貨"s + p + u8"枚を失った。"s,
                u8"You lose "s + p + u8" gold pieces."s));
            cdata[0].gold -= p;
        }
        else
        {
            txt(lang(
                u8"損害はなかった。"s,
                u8"The thief fails to steal money from you."s));
        }
        s = lang(u8"悪意ある手"s, u8"Malicious Hand"s);
        buff = lang(
            u8"悪意のある手が忍び寄り、あなたが気付かない間に金貨を奪って逃げた。"s,
            u8"A malicious hand slips and steals your money."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"盗人め…"s, u8"Bloody thieves..."s);
        ++listmax;
        show_random_event_window(u8"bg_re9");
        break;
    case 11:
        s = lang(u8"冒険者の遺骸"s, u8"Corpse"s);
        buff = lang(
            u8"この場所で力尽きた冒険者の遺骸を見つけた。既に朽ちかけている骨と、身に着けていたと思われる幾つかの装備が散らばっている。"s,
            u8"You find a corpse of an adventurer. There're bones and equipment scatters on the ground waiting to decay."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"あさる"s, u8"(Loot)"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"埋葬する"s, u8"(Bury)"s);
        ++listmax;
        show_random_event_window(u8"bg_re7");
        if (rtval == 1)
        {
            txt(lang(
                u8"あなたは遺留品をあさった。"s, u8"You loot the remains."s));
            modify_karma(0, -2);
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(0, calcfixlv(3));
                if (rnd(3) == 0)
                {
                    flttypemajor = fsetwear(rnd(length(fsetwear)));
                }
                else
                {
                    flttypemajor = fsetremain(rnd(length(fsetremain)));
                }
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        else
        {
            txt(lang(
                u8"あなたは骨と遺留品を埋葬した。"s,
                u8"You bury the corpse with respect."s));
            modify_karma(0, 5);
        }
        break;
    case 2:
        efid = 1104;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"魔法使いの夢"s, u8"Wizard's Dream"s);
        buff = lang(
            u8"夢の中であなたは赤い髪の魔術師に出会った。「誰じゃ、お主は？ふむ、間違った者の夢に現れてしまったようじゃ。すまぬな。お詫びといってはなんじゃが…」魔法使いは指をくるりと回した。あなたは軽い頭痛を覚えた。"s,
            u8"In your dream, you meet a wizard with a red mustache. \"Who are you? Hmm, I guess I picked up the wrong man's dream. My apology for disturbing your sleep. To make up for this...\" The wizard draws a circle in the air and vanishs. You feel the effects of a faint headache."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"おかしな夢だ"s, u8"A weird dream."s);
        ++listmax;
        show_random_event_window(u8"bg_re6");
        break;
    case 3:
        efid = 1119;
        efp = 100;
        tc = 0;
        magic();
        s = lang(u8"成長のきざし"s, u8"Development"s);
        buff = lang(
            u8"長年の鍛錬の成果が実ったようだ。なかなか眠りにつけず考えごとをしていたあなたは、ふと、自らの技術に関する新しいアイデアを思いついた。"s,
            u8"You lie awake, sunk deep into thought. As memories of your journey flow from one into another, you chance upon a new theory to improve one of your skills."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし！"s, u8"Good!"s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 6:
        skillexp(154, 0, 1000);
        s = lang(u8"自然治癒力の向上"s, u8"Regeneration"s);
        buff = lang(
            u8"身体が妙に火照ってあなたは目を覚ました。気がつくと、腕にあった傷跡が完全に消えていた。"s,
            u8"Your entire body flushes. When you wake up, a scar in your arm is gone."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 7:
        skillexp(155, 0, 1000);
        s = lang(u8"瞑想力の向上"s, u8"Meditation"s);
        buff = lang(
            u8"あなたは、夢の中でも驚くほど理性を保っていた。まるで瞑想を行っている時のように、あなたは心の平和を感じた。"s,
            u8"In your dream, you meditate and feel inner peace."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"よし"s, u8"Good."s);
        ++listmax;
        show_random_event_window(u8"bg_re4");
        break;
    case 9:
        ++cdata[0].platinum_coin;
        s = lang(u8"路上に転がる幸運"s, u8"Great Luck"s);
        buff = lang(
            u8"下を向いて歩いていると、幸運にもプラチナ硬貨を見つけた。"s,
            u8"You stumble over a stone and find a platinum coin."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ラッキー！"s, u8"What a luck!"s);
        ++listmax;
        show_random_event_window(u8"bg_re1");
        break;
    case 16:
        p = rnd(cdata[0].gold / 10 + 1000) + 1;
        cdata[0].gold += p;
        txt(lang(
            u8"金貨"s + p + u8"枚を手に入れた。"s,
            u8"You pick up "s + p + u8" gold pieces."s));
        s = lang(u8"発狂した金持ち"s, u8"Mad Millionaire"s);
        buff = lang(
            u8"発狂した金持ちが、何か叫びながら金貨をばらまいている…"s,
            u8"A rich mad man is scattering his money all over the ground."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ラッキー！"s, u8"What a luck!"s);
        ++listmax;
        show_random_event_window(u8"bg_re1");
        break;
    case 17:
        efid = 451;
        efp = 800;
        tc = 0;
        magic();
        s = lang(u8"辻プリースト"s, u8"Wandering Priest"s);
        buff = lang(
            u8"突然、向かいからやって来た一人の神官が、すれ違いざまにあなたに魔法をかけた。「ノープロブレム」"s,
            u8"A priest comes up to you and casts a spell on you. \"No problem.\""s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"ありがとう"s, u8"Thanks."s);
        ++listmax;
        show_random_event_window(u8"bg_re11");
        break;
    }

    cc = 0;
    load_continuous_action_animation();
    return 1;
}



int show_random_event_window(const std::string& file)
{
    if (config::instance().skiprandevents)
    {
        if (listmax <= 1)
        {
            snd(62);
            txt(""s + buff);
            txt(lang(u8"「"s, u8"\""s) + listn(0, 0) + lang(u8"」"s, u8"\""s));
            rtval = -1;
            return rtval;
        }
    }
    keyhalt = 1;
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    key = "";
    objprm(0, ""s);
    keylog = "";
    if (listmax <= 1)
    {
        chatesc = 0;
    }
    else
    {
        chatesc = -1;
    }
    gsel(7);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / (u8""s + file + u8".bmp"), 0);
    tx = ginfo(12);
    ty = ginfo(13);
    gsel(0);
    snd(62);
    dx = tx + 36;
    talk_conv(buff, (dx - 80) / (7 - en) - en * 4);
    notesel(buff);
    dy = ty + noteinfo() * 15 + 80 + listmax * 20;
label_1897_internal:
    gmode(2);
    window(
        (windoww - dx) / 2 + inf_screenx + 4, winposy(dy) - 12, dx, dy, 0, -1);
    window((windoww - dx) / 2 + inf_screenx, winposy(dy) - 16, dx, dy);
    wx = (windoww - dx) / 2 + inf_screenx;
    wy = winposy(dy);
    gmode(0);
    pos(wx + 12, wy + 6);
    gcopy(7, 0, 0, tx, ty);
    gmode(2);
    color(240, 230, 220);
    boxl(wx + 12, wy + 6, wx + tx + 12, wy + ty + 6);
    color(0, 0, 0);
    font(14 - en * 2);
    q = lang(u8"《 "s + s + u8" 》"s, u8" < "s + s + u8" > "s);
    pos(wx + 40, wy + 16);
    color(30, 20, 10);
    bmes(q, 245, 235, 225);
    color(0, 0, 0);
    font(14 - en * 2);
    color(30, 30, 30);
    pos(wx + 24, wy + ty + 20);
    mes(buff);
    color(0, 0, 0);
    keyrange = 0;
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        i = list(0, p);
        display_key(wx + 30, wy + dy + cnt * 20 - listmax * 20 - 52, cnt);
        q = listn(0, p);
        cs_list(cs == cnt, q, wx + 60, wy + dy + cnt * 20 - listmax * 20 - 52);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(rtval, snd(40));
    if (chatesc != -1)
    {
        if (key == key_cancel)
        {
            snd(40);
            rtval = chatesc;
        }
    }
    if (rtval != -1)
    {
        label_1898();
        return 0;
    }
    goto label_1897_internal;
}



int label_1898()
{
    key = "";
    return rtval;
}



int calcincome(int prm_1036)
{
    int p_at_m176 = 0;
    p_at_m176 = 100 - gdata((120 + prm_1036)) / 100;
    if (p_at_m176 == 99)
    {
        p_at_m176 = p_at_m176 * 70;
    }
    else
    {
        p_at_m176 = p_at_m176 * 50;
    }
    if (prm_1036 == 2)
    {
        p_at_m176 = p_at_m176 * 120 / 100;
    }
    if (prm_1036 == 4)
    {
        p_at_m176 = p_at_m176 * 60 / 100;
    }
    if (prm_1036 == 0)
    {
        p_at_m176 = p_at_m176 * 80 / 100;
    }
    if (prm_1036 == 1)
    {
        p_at_m176 = p_at_m176 * 70 / 100;
    }
    if (prm_1036 == 6)
    {
        p_at_m176 = p_at_m176 * 25 / 100;
    }
    if (prm_1036 == 5)
    {
        p_at_m176 = p_at_m176 * 20 / 100;
    }
    if (prm_1036 == 8)
    {
        p_at_m176 = p_at_m176 * 15 / 100;
    }
    return p_at_m176;
}



void supply_income()
{
    invfile = 4;
    ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
    if (fs::exists(filesystem::dir::tmp() / u8"shop4.s2"s))
    {
        ctrl_file(file_operation2_t::_3, u8"shop4.s2"s);
    }
    else
    {
        for (const auto& cnt : items(-1))
        {
            inv[cnt].number = 0;
        }
    }
    mode = 6;
    income(0) = 0;
    income(1) = 0;
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        if (gdata(120 + cnt) >= 10000)
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
        int cnt2 = cnt;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            dbid = 0;
            flt(calcobjlv((100 - gdata((120 + cnt2)) / 100) / 2 + 1),
                calcfixlv(3 + (rnd(12) < trait(39))));
            flttypemajor = fsetincome(rnd(length(fsetincome)));
            if (rnd(5) == 0)
            {
                flttypemajor = fsetwear(rnd(length(fsetwear)));
            }
            if (rnd(100 + gdata((120 + cnt2)) / 5) < 2)
            {
                dbid = 559;
            }
            itemcreate(-1, dbid, -1, -1, 0);
            ++income(1);
        }
    }
    if (cdata[0].fame > 0)
    {
        p = clamp(cdata[0].fame / 10, 100, 25000);
        if (cdata[0].fame >= 25000)
        {
            p += (cdata[0].fame - 25000) / 100;
        }
        income += p;
        flt();
        itemcreate(-1, 54, -1, -1, p);
    }
    s = ""s + income + lang(u8"gold"s, u8" gold pieces"s);
    if (income(1) != 0)
    {
        s += lang(
            u8"と"s + income(1) + u8"個のアイテム"s,
            u8" and "s + income(1) + u8" items"s);
    }
    if (income != 0 || income(1) != 0)
    {
        snd(24);
        txtef(5);
        txt(lang(
            s + u8"が給料として振り込まれた。"s,
            u8"As a salary, "s + s + u8" have been sent to your house."s));
        autosave = 1 * (gdata_current_map != 35);
    }
    if (gdata_day == 1)
    {
        if (cdata[0].level > 5)
        {
            autosave = 1 * (gdata_current_map != 35);
            p = -1;
            for (const auto& cnt : items(-1))
            {
                if (inv[cnt].number == 0)
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
                gdata_cost_to_hire + calccostbuilding() + calccosttax();
            inv[ci].subname = inv[ci].subname * (100 + rnd(20)) / 100;
            mode = 0;
            ++gdata_left_bill;
            txt(lang(
                u8"請求書が送られてきた。"s,
                u8"A bill has been sent to your house."s));
            if (gdata_left_bill > 1)
            {
                if (gdata_left_bill <= 4)
                {
                    txtef(3);
                    if (gdata_left_bill > 3)
                    {
                        s(0) = lang(u8"警告！！"s, u8"Warning!! "s);
                        s(1) = lang(
                            u8"早急にパルミア大使館まで行き、税金を納めなければならない。"s,
                            u8"You have to go to the Embassy of Palmia and pay tax at once. "s);
                    }
                    else
                    {
                        s(0) = lang(u8"注意！"s, u8"Caution! "s);
                        s(1) = "";
                    }
                    txt(s
                        + lang(
                              (u8"税金を"s + (gdata_left_bill - 1)
                               + u8"ヶ月分滞納している。"s),
                              (u8"You are in arrears with your tax for "s
                               + (gdata_left_bill - 1) + u8" months."s))
                        + s(1));
                }
            }
            if (gdata_left_bill > 4)
            {
                txtef(3);
                txt(lang(
                    u8"あなたは税金を"s + (gdata_left_bill - 1)
                        + u8"ヶ月滞納した罪で訴えられた。"s,
                    u8"You have been accused for being in arrears with your tax for"s
                        + (gdata_left_bill - 1) + u8" months."s));
                int stat = decfame(0, 50);
                p = stat;
                txtef(3);
                txt(lang(
                    u8"名声値を"s + p + u8"失った。"s,
                    u8"You lose "s + p + u8" fame."s));
                modify_karma(0, -30 * 2);
            }
        }
        else
        {
            txt(lang(
                u8"レベルが6に達していないので納税の義務はない。"s,
                u8"You don't have to pay tax until you hit level 6."s));
        }
    }
    ctrl_file(file_operation2_t::_4, u8"shop"s + invfile + u8".s2");
    ctrl_file(file_operation2_t::_3, u8"shoptmp.s2");
    mode = 0;
    if (config::instance().extrahelp)
    {
        if (gdata(216) == 0)
        {
            if (mode == 0)
            {
                if (cdata[0].continuous_action_turn == 0)
                {
                    gdata(216) = 1;
                    ghelp = 16;
                    show_ex_help();
                }
            }
        }
    }
    return;
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
        if (map(prm_1055, prm_1056, 5) < 0)
        {
            rtvaln = "";
            p_at_m185(0) = -map(prm_1055, prm_1056, 5);
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
                    rtvaln += lang(u8"と"s, u8" and "s);
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
            return lang(
                rtvaln + u8"が落ちている。"s,
                u8"You see "s + rtvaln + u8" here."s);
        }
        else if (inv[item].own_state == 3)
        {
            return lang(
                rtvaln + u8"が設置されている。"s,
                ""s + rtvaln + u8" is constructed here."s);
        }
        else
        {
            return lang(
                rtvaln + u8"がある。"s,
                u8"You see "s + rtvaln + u8" placed here."s);
        }
    }
    else
    {
        return lang(
            u8"ここには"s + number + u8"種類のアイテムがある。"s,
            u8"There are "s + number + u8" items lying here."s);
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
                cdata[0].position.x, cdata[0].position.y, prm_1057, prm_1058)
                == 0
            || dist(
                   cdata[0].position.x, cdata[0].position.y, prm_1057, prm_1058)
                > cdata[0].vision_distance / 2)
        {
            pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            bmes(
                lang(u8"視界範囲外"s, u8"This location is out of sight."s),
                255,
                2552,
                255);
            cansee = 0;
            return;
        }
    }
    if (map(prm_1057, prm_1058, 1) != 0)
    {
        i_at_m186 = map(prm_1057, prm_1058, 1) - 1;
        if (cdata[i_at_m186].is_invisible() == 0 || cdata[0].can_see_invisible()
            || cdata[i_at_m186].wet)
        {
            tc = i_at_m186;
            s = txttargetlevel(cc, tc);
            pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            bmes(s, 255, 2552, 255);
            pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
            ++dy_at_m186;
            bmes(
                lang(u8"現在のターゲットは"s, u8"You are targeting "s)
                    + name(i_at_m186) + lang(u8" (距離 "s, u8".(Distance "s)
                    + dist(
                          cdata[0].position.x,
                          cdata[0].position.y,
                          cdata[i_at_m186].position.x,
                          cdata[i_at_m186].position.y)
                    + u8")"s,
                255,
                2552,
                255);
        }
    }
    if (map(prm_1057, prm_1058, 5) != 0)
    {
        pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
        ++dy_at_m186;
        bmes(txtitemoncell(prm_1057, prm_1058), 255, 2552, 255);
    }
    if (map(prm_1057, prm_1058, 6) != 0)
    {
        if (mdata(6) == 1)
        {
            if (map(prm_1057, prm_1058, 6) / 1000 % 100 == 15)
            {
                p_at_m186 = map(prm_1057, prm_1058, 6) / 100000 % 100
                    + map(prm_1057, prm_1058, 6) / 10000000 * 100;
                pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
                ++dy_at_m186;
                bmes(mapname(p_at_m186, true), 255, 2552, 255);
            }
            if (map(prm_1057, prm_1058, 6) / 1000 % 100 == 34)
            {
                pos(100, windowh - inf_verh - 45 - dy_at_m186 * 20);
                ++dy_at_m186;
                bmes(
                    txtbuilding(
                        map(prm_1057, prm_1058, 6) / 100000 % 100,
                        map(prm_1057, prm_1058, 6) / 10000000),
                    255,
                    2552,
                    255);
            }
        }
    }
    cansee = 1;
    return;
}



int key_direction()
{
    kdx = 0;
    kdy = 0;
    if (key == key_north)
    {
        --kdy;
        return 1;
    }
    if (key == key_south)
    {
        ++kdy;
        return 1;
    }
    if (key == key_west)
    {
        --kdx;
        return 1;
    }
    if (key == key_east)
    {
        ++kdx;
        return 1;
    }
    if (key == key_northwest)
    {
        --kdx;
        --kdy;
        return 1;
    }
    if (key == key_northeast)
    {
        ++kdx;
        --kdy;
        return 1;
    }
    if (key == key_southwest)
    {
        --kdx;
        ++kdy;
        return 1;
    }
    if (key == key_southeast)
    {
        ++kdx;
        ++kdy;
        return 1;
    }
    return 0;
}



turn_result_t step_into_gate()
{
    if (config::instance().extrahelp)
    {
        if (gdata(217) == 0)
        {
            if (mode == 0)
            {
                if (cdata[0].continuous_action_turn == 0)
                {
                    gdata(217) = 1;
                    ghelp = 17;
                    show_ex_help();
                    screenupdate = -1;
                    update_screen();
                    return turn_result_t::pc_turn_user_error;
                }
            }
        }
    }
    if (1 && gdata_wizard == 0)
    {
        snd(44);
        save_game();
        txtef(5);
        txt(lang(u8" *保存* "s, u8"*saving*"s));
    }
    txt(lang(
        u8"あなたはゲートに足を踏み入れた。ゲートはあなたの背後で消滅した。"s,
        u8"You stepped into the gate. The gate disappears."s));
    --inv[ci].number;
    cell_refresh(inv[ci].position.x, inv[ci].position.y);
    txt(lang(
        u8"ネット機能をONにする必要がある。"s,
        u8"You have to turn on network setting."s));
    update_screen();
    return turn_result_t::pc_turn_user_error;
}



int label_19432()
{
label_19431_internal:
    if (1 && gdata_wizard == 0)
    {
        snd(44);
        save_game();
        txtef(5);
        txt(lang(u8" *保存* "s, u8"*saving*"s));
    }
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    SDIM2(headtemp, 1024);
    const auto pattern =
        comctrl == 1 ? std::regex{u8R"(.*\.ept)"} : std::regex{u8R"(.*\.eum)"};
    for (const auto& entry :
         filesystem::dir_entries{filesystem::dir::user(),
                                 filesystem::dir_entries::type::file,
                                 pattern})
    {
        const auto path = entry.path();
        if (path == filesystem::path(u8"temp.enum")
            || path == filesystem::path(u8"temp.ept"))
            continue;
        bload(path, headtemp, 1024);
        notesel(headtemp);
        noteget(s, 0);
        noteget(s(1), 1);
        noteget(s(2), 4);
        list(0, listmax) = listmax;
        list(1, listmax) = 0;
        list(2, listmax) = elona::stoi(s(2));
        listn(0, listmax) = u8"("s
            + filesystem::make_preferred_path_in_utf8(path.filename()) + u8") "s
            + s + u8" "s + s(1);
        listn(1, listmax) = filesystem::to_utf8_path(path.filename());
        ++listmax;
        noteunsel();
    }
    if (config::instance().net != 0)
    {
        if (comctrl == 1)
        {
            net_dllist(u8".ept"s, 1);
        }
        if (comctrl == 2)
        {
            net_dllist(u8".eum"s, 1);
        }
    }
    if (comctrl == 0 || comctrl == 2)
    {
        txt(lang(
            u8"どのルームを訪問する？ "s,
            u8"Which room do you want to visit? "s));
    }
    if (comctrl == 1)
    {
        txt(lang(
            u8"どのチームと対戦する？"s,
            u8"Which team do you want to play a match? "s));
    }
    windowshadow = 1;
label_1944_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_1945_internal:
    if (comctrl == 0 || comctrl == 2)
    {
        s = lang(u8"ルーム一覧"s, u8"Room List"s);
    }
    if (comctrl == 1)
    {
        s = lang(u8"ペットチーム一覧"s, u8"Team List"s);
    }
    s(1) = lang(u8"BackSpace [削除]  "s, u8"BackSpace [Delete]  "s) + strhint2
        + strhint3;
    display_window((windoww - 640) / 2 + inf_screenx, winposy(448), 640, 448);
    if (comctrl == 0 || comctrl == 2)
    {
        s = lang(u8"ルームの名称"s, u8"Name"s);
    }
    if (comctrl == 1)
    {
        s = lang(u8"チームの名称"s, u8"Name"s);
    }
    display_topic(s, wx + 28, wy + 36);
    display_topic(u8"Ver"s, wx + 534, wy + 36);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            pos(wx + 70, wy + 66 + cnt * 19);
            gfini(540, 18);
            gfdec2(12, 14, 16);
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        s = listn(0, p);
        cutname(s, 64);
        cs_list(cs == cnt, s, wx + 84, wy + 66 + cnt * 19 - 1);
        pos(wx + 570, wy + 66 + cnt * 19);
        mes(""s + (list(2, p) % 1000 + 1) + u8".0"s);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (p != -1)
    {
        if (p == -999)
        {
            snd(27);
            txt(lang(
                u8"互換性のないバージョンのファイルです。"s,
                u8"Selected item is incompatible."s));
            goto label_1944_internal;
        }
        if (listn(1, p) == u8"net"s)
        {
            if (comctrl == 1)
            {
                s = u8".ept"s;
            }
            else
            {
                s = u8".eum"s;
            }
            int stat = net_dl(""s + list(1, p) + s, u8"temp"s + s);
            usermapid = list(1, p);
            if (stat == 0)
            {
                txt(lang(
                    u8"ファイルの取得に失敗した。"s,
                    u8"Failed to retrieve designated files."s));
                goto label_1944_internal;
            }
            userfile = u8"temp"s + s;
        }
        else
        {
            userfile = listn(1, p);
        }
        bload(filesystem::dir::user() / userfile, headtemp, 1024);
        notesel(headtemp);
        noteget(s, 5);
        noteget(s(1), 6);
        if (comctrl == 0 || comctrl == 2)
        {
            username = ""s + s;
            userrelation = elona::stoi(s(1));
        }
        if (comctrl == 1)
        {
            rtval(0) = elona::stoi(s(0));
            rtval(1) = elona::stoi(s(1));
        }
        return 1;
    }
    if (ginfo(2) == 0)
    {
        if (noteinfo() != 0)
        {
            if (getkey(snail::key::backspace))
            {
                userfile = listn(1, cs + pagesize * page);
                if (!fs::exists(filesystem::path(u8"./user/"s + userfile)))
                {
                    goto label_1944_internal;
                }
                txt(lang(
                    u8"本当に"s + userfile + u8"を削除する？ "s,
                    u8"Do you really want to delete "s + userfile + u8"? "s));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval == 0)
                {
                    elona_delete(filesystem::path(u8"./user/"s + userfile));
                    goto label_19431_internal;
                }
                goto label_1944_internal;
            }
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1944_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1944_internal;
        }
    }
    if (key == key_cancel)
    {
        update_screen();
        return 0;
    }
    goto label_1945_internal;
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
        if (cdata[0].enemy_id == 0)
        {
            label_2072();
        }
        label_2076();
        if (listmax == 0)
        {
            txt(lang(
                u8"視界内にターゲットは存在しない。"s,
                u8"You look around and find nothing."s));
        }
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (list(0, cnt) == 0)
            {
                continue;
            }
            if (list(0, cnt) == cdata[0].enemy_id)
            {
                tlocx = cdata[list(0, cnt)].position.x;
                tlocy = cdata[list(0, cnt)].position.y;
                break;
            }
        }
    }
label_1948_internal:
    screenupdate = -1;
    update_screen();
    dx = (tlocx - scx) * inf_tiles + inf_screenx;
    dy = (tlocy - scy) * inf_tiles + inf_screeny;
    if (dy + inf_tiles <= windowh - inf_verh)
    {
        pos(dx, dy * (dy > 0));
        snail::application::instance().get_renderer().set_blend_mode(
            snail::blend_mode_t::blend);
        snail::application::instance().get_renderer().set_draw_color(
            {127, 127, 255, 50});
        snail::application::instance().get_renderer().fill_rect(
            dx,
            dy * (dy > 0),
            inf_tiles - (dx + inf_tiles > windoww) * (dx + inf_tiles - windoww),
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
            if (map(tlocx, tlocy, 1) <= 1)
            {
                break;
            }
            rc = map(tlocx, tlocy, 1) - 1;
            if (is_in_fov(rc) == 0)
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
            if ((cdata[rc].is_invisible() == 0 || cdata[0].can_see_invisible()
                 || cdata[rc].wet)
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
                        snail::application::instance()
                            .get_renderer()
                            .set_blend_mode(snail::blend_mode_t::blend);
                        snail::application::instance()
                            .get_renderer()
                            .set_draw_color({255, 255, 255, 25});
                        snail::application::instance().get_renderer().fill_rect(
                            sx,
                            sy * (sy > 0),
                            inf_tiles
                                - (sx + inf_tiles > windoww)
                                    * (sx + inf_tiles - windoww),
                            inf_tiles + (sy < 0) * inf_screeny
                                - (sy + inf_tiles > windowh - inf_verh)
                                    * (sy + inf_tiles - windowh + inf_verh));
                    }
                }
            }
        }
    }
    txttargetnpc(tlocx, tlocy);
    redraw();
    await(config::instance().wait1);
    key_check();
    if (homemapmode == 1)
    {
        if (key == key_enter)
        {
            label_1955();
            keyrelease();
            goto label_1948_internal;
        }
        int a{};
        stick(a, 768);
        if (a == 256)
        {
            key = key_enter;
        }
        if (a == 512)
        {
            if (chipm(0, map(tlocx, tlocy, 0)) == 2
                || chipm(0, map(tlocx, tlocy, 0)) == 1)
            {
                snd(27);
                keyrelease();
                goto label_1948_internal;
            }
            tile = map(tlocx, tlocy, 0);
            snd(5);
            keyrelease();
        }
        tx = clamp((mousex - inf_screenx), 0, windoww) / 48;
        ty = clamp((mousey - inf_screeny), 0, (windowh - inf_verh)) / 48;
        int stat = key_direction();
        if (stat == 1)
        {
            cdata[0].position.x += kdx;
            cdata[0].position.y += kdy;
            if (cdata[0].position.x < 0)
            {
                cdata[0].position.x = 0;
            }
            else if (cdata[0].position.x >= mdata(0))
            {
                cdata[0].position.x = mdata(0) - 1;
            }
            if (cdata[0].position.y < 0)
            {
                cdata[0].position.y = 0;
            }
            else if (cdata[0].position.y >= mdata(1))
            {
                cdata[0].position.y = mdata(1) - 1;
            }
        }
        tlocx = tx + scx;
        if (tlocx < 0)
        {
            tlocx = 0;
        }
        else if (tlocx >= mdata(0))
        {
            tlocx = mdata(0) - 1;
        }
        tlocy = ty + scy;
        if (tlocy < 0)
        {
            tlocy = 0;
        }
        else if (tlocy >= mdata(1))
        {
            tlocy = mdata(1) - 1;
        }
    }
    else
    {
        int stat = key_direction();
        if (stat == 1)
        {
            x = tlocx + kdx;
            y = tlocy + kdy;
            if (x >= 0 && y >= 0 && x < mdata(0) && y < mdata(1))
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
        if (key == key_pageup)
        {
            ++p;
            f = 1;
            if (p >= listmax)
            {
                p = 0;
            }
        }
        if (key == key_pagedown)
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
            snd(5);
            tlocx = cdata[list(0, p)].position.x;
            tlocy = cdata[list(0, p)].position.y;
        }
    }
    if (key == key_enter)
    {
        if (findlocmode == 1)
        {
            if (cansee == 0 || chipm(7, map(tlocx, tlocy, 0)) & 4)
            {
                txt(lang(
                    u8"その場所は見えない。"s,
                    u8"You can't see the location."s));
                goto label_1948_internal;
            }
            snd(20);
            if (rc > 0)
            {
                cdata[0].enemy_id = rc;
                txt(lang(
                    name(rc) + u8"をターゲットにした。"s,
                    u8"You target "s + name(rc) + u8"."s));
            }
            else
            {
                tgloc = 1;
                tglocx = tlocx;
                tglocy = tlocy;
                txt(lang(
                    u8"地面をターゲットにした。"s,
                    u8"You target the ground."s));
            }
        }
        else if (homemapmode == 0)
        {
            snd(5);
        }
        scposval = 0;
        if (tlocinitx == 0 && tlocinity == 0)
        {
            scposval = 0;
            update_screen();
        }
        tlocinitx = 0;
        tlocinity = 0;
        return cansee;
    }
    if (key == key_cancel)
    {
        tlocinitx = 0;
        tlocinity = 0;
        scposval = 0;
        update_screen();
        return -1;
    }
    goto label_1948_internal;
}



void label_1955()
{
    ww = 33;
    wh = 20;
    wx = 0;
    wy = 0;
    snd(26);
label_1956_internal:
    gmode(0);
    p = 0;
    for (int cnt = 0, cnt_end = (wh); cnt < cnt_end; ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0, cnt_end = (ww); cnt < cnt_end; ++cnt)
        {
            if (p < listmax)
            {
                pos(wx + cnt * 24, wy + cnt2 * 24);
                gzoom(
                    2,
                    list(0, p) % ww * 48,
                    list(0, p) / ww * 48,
                    48,
                    48,
                    24,
                    24);
                if (chipm(7, list(0, p)) & 4)
                {
                    color(240, 230, 220);
                    boxl(
                        wx + cnt * 24,
                        wy + cnt2 * 24,
                        wx + cnt * 24 + 24,
                        wy + cnt2 * 24 + 24);
                    color(0, 0, 0);
                }
            }
            ++p;
        }
    }
    gmode(2);
    redraw();
    await(config::instance().wait1);
    int a{};
    stick(a);
    if (a == 256)
    {
        p = mousex / 24 + mousey / 24 * ww;
        if (p >= listmax)
        {
            snd(27);
            goto label_1956_internal;
        }
        tile = list(0, p);
        snd(20);
        label_1958();
        return;
    }
    if (a == 512)
    {
        label_1958();
        return;
    }
    goto label_1956_internal;
}



turn_result_t do_short_cut()
{
    menucycle = 0;
    if (gdata(40 + sc) == 0)
    {
        ++msgdup;
        txt(lang(
            u8"そのキーにはショートカットが割り当てられていない。"s,
            u8"The key is unassigned."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (gdata(40 + sc) >= 10000)
    {
        invsc = gdata((40 + sc)) % 10000;
        invctrl(0) = gdata((40 + sc)) / 10000;
        invctrl(1) = 0;
        menu_result mr = ctrl_inventory();
        assert(mr.turn_result != turn_result_t::none);
        return mr.turn_result;
    }
    efid = gdata(40 + sc);
    if (efid >= 300 && efid < 400)
    {
        return do_use_magic();
    }
    if (efid >= 600)
    {
        if (mdata(6) == 1)
        {
            txtnew();
            txt(lang(
                u8"その行為は、ワールドマップにいる間はできない。"s,
                u8"You can't do that while you're in a global area."s));
            display_msg();
            redraw();
            return turn_result_t::pc_turn_user_error;
        }
        if (efid < 661)
        {
            if (spact(efid - 600) == 0)
            {
                txt(lang(
                    u8"もうその行動はできない。"s,
                    u8"You can't use this shortcut any more."s));
                update_screen();
                return turn_result_t::pc_turn_user_error;
            }
        }
        return do_use_magic();
    }
    if (efid >= 400)
    {
        if (mdata(6) == 1)
        {
            txtnew();
            txt(lang(
                u8"その行為は、ワールドマップにいる間はできない。"s,
                u8"You can't do that while you're in a global area."s));
            display_msg();
            redraw();
            return turn_result_t::pc_turn_user_error;
        }
        if (spell(efid - 400) <= 0)
        {
            ++msgdup;
            txt(lang(
                u8"その魔法はもう使えない。"s,
                u8"You can't use that spell anymore."s));
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        return do_cast_command();
    }
    return turn_result_t::pc_turn_user_error;
}



turn_result_t do_use_magic()
{
    int stat = label_2174();
    if (stat == 0)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    return turn_result_t::turn_end;
}



turn_result_t call_npc()
{
    txt(lang(
        name(tc) + u8"を何と呼ぶ？ "s,
        u8"What do you want to call "s + him(tc) + u8"? "s));
    inputlog = "";
    input_text_dialog((windoww - 220) / 2 + inf_screenx, winposy(90), 12);
    if (inputlog == ""s)
    {
        txt(lang(u8"名前をつけるのはやめた。"s, u8"You changed your mind."s));
    }
    else
    {
        cdatan(0, tc) = ""s + inputlog;
        cdata[tc].has_own_name() = true;
        txt(lang(
            ""s + cdatan(0, tc) + u8"という名前で呼ぶことにした。"s,
            u8"You named "s + him(tc) + u8" "s + cdatan(0, tc) + u8"."s));
    }
    label_1416();
    return turn_result_t::pc_turn_user_error;
}


void equip_melee_weapon()
{
    attacknum = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata_body_part(cc, cnt) / 10000 != 5)
        {
            continue;
        }
        if (cdata_body_part(cc, cnt) % 10000 == 0)
        {
            continue;
        }
        cw = cdata_body_part(cc, cnt) % 10000 - 1;
        if (inv[cw].dice_x == 0)
        {
            continue;
        }
        ++attacknum;
        if (cdata[cc].equipment_type & 2)
        {
            if (inv[cw].weight >= 4000)
            {
                txt(lang(
                    u8"装備中の"s + itemname(cw)
                        + u8"は両手にしっくりとおさまる。"s,
                    itemname(cw)
                        + u8" fits well for two-hand fighting style."s));
            }
            else
            {
                txt(lang(
                    u8"装備中の"s + itemname(cw)
                        + u8"は両手持ちにはやや軽すぎる。"s,
                    itemname(cw)
                        + u8" is too light for two-hand fighting style."s));
            }
        }
        if (cdata[cc].equipment_type & 4)
        {
            if (attacknum == 1)
            {
                if (inv[cw].weight >= 4000)
                {
                    txt(lang(
                        u8"装備中の"s + itemname(cw)
                            + u8"は利手で扱うにも重すぎる。"s,
                        itemname(cw)
                            + u8" is too heavy for two-wield fighting style."s));
                }
            }
            else if (inv[cw].weight > 1500)
            {
                txt(lang(
                    u8"装備中の"s + itemname(cw)
                        + u8"は片手で扱うには重すぎる。"s,
                    itemname(cw)
                        + u8" is too heavy for two-wield fighting style."s));
            }
        }
        if (cc == 0)
        {
            if (gdata_mount != 0)
            {
                if (inv[cw].weight >= 4000)
                {
                    txt(lang(
                        u8"装備中の"s + itemname(cw)
                            + u8"は乗馬中に扱うには重すぎる。"s,
                        itemname(cw) + u8" is too heavy to use when riding."s));
                }
            }
        }
    }
}



turn_result_t try_interact_with_npc()
{
    if (cdata[tc].continuous_action_turn != 0)
    {
        txt(lang(
            name(tc) + u8"は忙しい。"s,
            name(tc) + u8" "s + is(tc) + u8" busy now."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    menucycle = 1;
    invally = 1;
    invctrl = 10;
    snd(100);
    menu_result mr = ctrl_inventory();
    assert(mr.turn_result != turn_result_t::none);
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
    return;
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
    return;
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
    return;
}



void show_item_description()
{
    int inhmax = 0;
    if (ci < 0)
    {
        dialog(
            u8"暫定エラー回避処置です。お手数ですが、どの持ち物メニュー(例えば飲む、振る、食べるなど）から調査(xキー)を押したか報告お願いします。"s);
        return;
    }
    snd(26);
    page_save();
    page = 0;
    pagesize = 15;
    listmax = 0;
    p = 0;
    s = "";
    reftype = the_item_db[inv[ci].id]->category;
    getinheritance(ci, inhlist, inhmax);
    dbid = inv[ci].id;
    access_item_db(2);
    access_item_db(17);
    if (inv[ci].identification_state
        == identification_state_t::completely_identified)
    {
        std::string buf = trim_item_description(description(3), true);
        if (buf != ""s)
        {
            list(0, p) = 7;
            listn(0, p) = buf;
            ++p;
        }
    }
    if (inv[ci].identification_state
        >= identification_state_t::almost_identified)
    {
        if (inv[ci].material != 0)
        {
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"それは"s
                    + i18n::_(
                          u8"item_material",
                          std::to_string(inv[ci].material),
                          u8"name")
                    + u8"で作られている"s,
                u8"It is made of "s
                    + i18n::_(
                          u8"item_material",
                          std::to_string(inv[ci].material),
                          u8"name")
                    + u8"."s);
            ++p;
        }
        if (inv[ci].material == 8)
        {
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"それは装備している間、エーテルの病の進行を早める"s,
                u8"It speeds up the ether disease while equipping."s);
            ++p;
        }
        if (ibit(1, ci))
        {
            list(0, p) = 7;
            listn(0, p) =
                lang(u8"それは酸では傷つかない"s, u8"It is acidproof."s);
            ++p;
        }
        if (ibit(2, ci))
        {
            list(0, p) = 7;
            listn(0, p) =
                lang(u8"それは炎では燃えない"s, u8"It is fireproof."s);
            ++p;
        }
        if (ibit(5, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(u8"それは貴重な品だ"s, u8"It is precious."s);
            ++p;
        }
        if (ibit(8, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"それはエヘカトルの祝福を受けている"s,
                u8"It is blessed by Ehekatl."s);
            ++p;
        }
        if (ibit(9, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(u8"それは盗品だ"s, u8"It is a stolen item."s);
            ++p;
        }
        if (ibit(10, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(u8"それは生きている"s, u8"It is alive."s)
                + u8" [Lv:"s + inv[ci].param1 + u8" Exp:"s
                + clamp(inv[ci].param2 * 100 / calcexpalive(inv[ci].param1),
                        0,
                        100)
                + u8"%]"s;
            ++p;
        }
        if (ibit(16, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"それはショウルームでのみ使用できる。"s,
                u8"It can be only used in a show room."s);
            ++p;
        }
        if (ibit(17, ci))
        {
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"それは心温まる手作り品だ"s, u8"It is a hand-made item."s);
            ++p;
        }
        if (inv[ci].dice_x != 0)
        {
            const auto pierce = calc_rate_to_pierce(inv[ci].id);
            list(0, p) = 5;
            listn(0, p) = lang(
                              u8"それは武器として扱うことができる"s,
                              u8"It can be wielded as a weapon."s)
                + u8" ("s + inv[ci].dice_x + u8"d"s + inv[ci].dice_y
                + lang(u8" 貫通 "s, u8" Pierce "s) + pierce + u8"%)"s;
            ++p;
            if (reftype == 10000)
            {
                if (inv[ci].weight <= 1500)
                {
                    list(0, p) = 5;
                    listn(0, p) = lang(
                        u8"それは片手でも扱いやすい"s,
                        u8"It is a light weapon."s);
                    ++p;
                }
                if (inv[ci].weight >= 4000)
                {
                    list(0, p) = 5;
                    listn(0, p) = lang(
                        u8"それは両手持ちに適している"s,
                        u8"It is a heavy weapon."s);
                    ++p;
                }
            }
        }
        if (inv[ci].hit_bonus != 0 || inv[ci].damage_bonus != 0)
        {
            list(0, p) = 5;
            listn(0, p) = lang(
                u8"それは攻撃修正に"s + inv[ci].hit_bonus
                    + u8"を加え、ダメージを"s + inv[ci].damage_bonus
                    + u8"増加させる"s,
                u8"It modifies hit bonus by "s + inv[ci].hit_bonus
                    + u8" and damage bonus by "s + inv[ci].damage_bonus
                    + u8"."s);
            ++p;
        }
        if (inv[ci].pv != 0 || inv[ci].dv != 0)
        {
            list(0, p) = 6;
            listn(0, p) = lang(
                u8"それはDVを"s + inv[ci].dv + u8"上昇させ、PVを"s + inv[ci].pv
                    + u8"上昇させる"s,
                u8"It modifies DV by "s + inv[ci].dv + u8" and PV by "s
                    + inv[ci].pv + u8"."s);
            ++p;
        }
        if (inv[ci].id == 701)
        {
            int card_count{};
            for (int i = 0; i < 1000; ++i)
            {
                if (card(0, i))
                    ++card_count;
            }
            int npc_count{};
            for (const auto& discord : the_character_db)
            {
                (void)discord;
                ++npc_count;
            }
            const auto percentage = std::min(100 * card_count / npc_count, 100);
            list(0, p) = 7;
            listn(0, p) = lang(
                u8"集めたカード: "s + card_count + u8"/" + npc_count + u8"("
                    + percentage + u8"%)",
                u8"Collected cards: "s + card_count + u8"/" + npc_count + u8"("
                    + percentage + u8"%)");
            ++p;
        }
    }
    if (inv[ci].identification_state
        <= identification_state_t::partly_identified)
    {
        list(0, p) = 0;
        listn(0, p) = lang(
            u8"このアイテムに関する知識を得るには、鑑定する必要がある。"s,
            u8"You have to identify the item to gain knowledge."s);
        ++p;
    }
    if (inv[ci].identification_state
        == identification_state_t::completely_identified)
    {
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[ci].enchantments[cnt].id == 0)
            {
                break;
            }
            get_enchantment_description(
                inv[ci].enchantments[cnt].id,
                inv[ci].enchantments[cnt].power,
                reftype);
            listn(0, p) = lang(u8"それは"s, u8"It "s) + s;
            list(0, p) = rtval;
            list(1, p) = rtval(1);
            if (inhmax > 0)
            {
                int cnt2 = cnt;
                for (int cnt = 0, cnt_end = (inhmax); cnt < cnt_end; ++cnt)
                {
                    if (cnt2 == inhlist(cnt))
                    {
                        list(0, p) += 10000;
                        break;
                    }
                }
            }
            ++p;
        }
        if (ibit(15, ci))
        {
            list(0, p) = 4;
            listn(0, p) = lang(u8"相手は死ぬ"s, u8"The enemy dies."s);
            ++p;
        }
        if (jp)
        {
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (description(cnt) == ""s)
                {
                    continue;
                }
                list(0, p) = 0;
                listn(0, p) = "";
                ++p;
                std::string buf =
                    trim_item_description(description(cnt), false);
                notesel(buf);
                for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
                {
                    noteget(q, cnt);
                    constexpr size_t max_width = 66;
                    if (strlen_u(q) > max_width)
                    {
                        p(2) = 0;
                        for (size_t i = 0; i < strlen_u(q) / max_width + 1; ++i)
                        {
                            auto one_line = strutil::take_by_width(
                                q(0).substr(p(2)), max_width);
                            p(1) = one_line.size();
                            if (strutil::starts_with(q, u8"。", p(1) + p(2)))
                            {
                                one_line += u8"。";
                                p(1) += std::strlen(u8"。");
                            }
                            if (strutil::starts_with(q, u8"、", p(1) + p(2)))
                            {
                                one_line += u8"、";
                                p(1) += std::strlen(u8"、");
                            }
                            if (strmid(q, p(2), p(1)) == ""s)
                            {
                                break;
                            }
                            list(0, p) = -1;
                            listn(0, p) = one_line;
                            ++p;
                            p(2) += p(1);
                        }
                    }
                    else
                    {
                        list(0, p) = 0;
                        listn(0, p) = q;
                        if (cnt == noteinfo() - 1)
                        {
                            list(0, p) = -2;
                        }
                        ++p;
                    }
                }
            }
        }
    }
    if (p == 0)
    {
        list(0, p) = 0;
        listn(0, p) = lang(
            u8"特に情報はない"s,
            u8"There is no information about this object."s);
        ++p;
    }
    listmax = p;
    pagemax = (listmax - 1) / pagesize;
    if (dump_return == 1)
    {
        dump_return = 0;
        return;
    }
    windowshadow = 1;
label_2069_internal:
    key_list = key_enter;
    keyrange = 0;
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_2070_internal:
    s(0) = lang(u8"アイテムの知識"s, u8"Known Information"s);
    s(1) = strhint4 + strhint3;
    display_window((windoww - 600) / 2 + inf_screenx, winposy(408), 600, 408);
    display_topic(itemname(ci), wx + 28, wy + 34);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        font(14 - en * 2);
        color(0, 0, 0);
        pos(wx + 68, wy + 68 + cnt * 18);
        if (list(0, p) % 10000 == 1)
        {
            color(0, 100, 0);
        }
        if (list(0, p) % 10000 == 2)
        {
            color(0, 0, 100);
        }
        if (list(0, p) % 10000 == 3)
        {
            color(80, 100, 0);
        }
        if (list(0, p) % 10000 == 4)
        {
            color(80, 50, 0);
        }
        if (list(0, p) % 10000 == 9)
        {
            color(180, 0, 0);
        }
        if (list(0, p) % 10000 == 8)
        {
            color(0, 100, 100);
        }
        if (list(0, p) == -1)
        {
            font(13 - en * 2);
        }
        if (list(0, p) == -2)
        {
            font(13 - en * 2, snail::font_t::style_t::italic);
            pos(wx + ww - strlen_u(listn(0, p)) * 6 - 80, wy + 68 + cnt * 18);
        }
        mes(listn(0, p));
        color(0, 0, 0);
        if (list(0, p) > 0)
        {
            pos(wx + 40, wy + 61 + cnt * 18);
            gcopy(3, 72 + list(0, p) % 10000 * 24, 336, 24, 24);
        }
        if (list(0, p) > 10000)
        {
            pos(wx + 15, wy + 63 + cnt * 18);
            gcopy(3, 384, 360, 24, 24);
        }
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_2069_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_2069_internal;
        }
    }
    if (key == key_cancel || key == key_enter)
    {
        returnfromidentify = 1;
        return;
    }
    goto label_2070_internal;
}



int label_2072()
{
    if (cdata[cdata[cc].enemy_id].state != 1)
    {
        cdata[cc].enemy_id = 0;
    }
    else if (is_in_fov(cdata[cc].enemy_id) == 0)
    {
        cdata[cc].enemy_id = 0;
    }
    if (cdata[cc].enemy_id == 0)
    {
        label_2076();
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
            txt(lang(
                u8"ターゲットが見当たらない。"s, u8"You find no target."s));
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



int label_2073()
{
    s = txttargetlevel(cc, tc);
    txt(s);
    txt(lang(
        u8"本当に"s + name(tc) + u8"を攻撃する？ "s,
        u8"Really attack "s + name(tc) + u8"? "s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
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
        if (cdata_body_part(cc, cnt) % 10000 == 0)
        {
            continue;
        }
        if (cdata_body_part(cc, cnt) / 10000 == 10)
        {
            cw = cdata_body_part(cc, cnt) % 10000 - 1;
        }
        if (cdata_body_part(cc, cnt) / 10000 == 11)
        {
            ammo = cdata_body_part(cc, cnt) % 10000 - 1;
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



void label_2076()
{
    listmax = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            if (is_in_fov(cnt) == 0)
            {
                continue;
            }
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                if (cdata[cnt].relationship == 10)
                {
                    if (cnt == 0)
                    {
                        continue;
                    }
                }
            }
            x = cdata[cnt].position.x;
            y = cdata[cnt].position.y;
            if (x == cdata[cc].position.x && y == cdata[cc].position.y)
            {
                continue;
            }
            if (fov_los(cdata[cc].position.x, cdata[cc].position.y, x, y) == 0)
            {
                continue;
            }
            if (cdata[cnt].is_invisible() == 1)
            {
                if (cdata[cc].can_see_invisible() == 0)
                {
                    if (cdata[cnt].wet == 0)
                    {
                        continue;
                    }
                }
            }
            list(0, listmax) = cnt;
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
    return;
}



void prompt_stop_continuous_action()
{
    txt(lang(
        i18n::_(u8"ui", u8"action", u8"_"s + cdata[cc].continuous_action_id)
            + u8"を中断したほうがいいだろうか？ "s,
        u8"Do you want to cancel "s
            + i18n::_(
                  u8"ui", u8"action", u8"_"s + cdata[cc].continuous_action_id)
            + u8"? "s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    return;
}



void try_to_return()
{
    int stat = quest_is_return_forbidden();
    if (stat == 1)
    {
        txt(lang(
            u8"依頼請負中の帰還は法律で禁止されている。それでも帰還する？"s,
            u8"Returning while taking a quest if forbidden. Are you sure you want to return?"s));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval != 0)
        {
            update_screen();
            return;
        }
    }
    p = 0;
    p = 0;
    i = 7;
    if (adata(30, i) == gdata(850))
    {
        list(0, p) = i;
        list(1, p) = 1;
        ELONA_APPEND_PROMPT(mapname(i), u8"null"s, ""s + promptmax);
        ++p;
    }
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        i = 500 - (cnt + 1);
        if (adata(16, i) == 0)
        {
            continue;
        }
        if (adata(30, i) != gdata(850))
        {
            continue;
        }
        if (adata(16, i) == 7)
        {
            continue;
        }
        if (adata(6, i) == 0)
        {
            continue;
        }
        f = 0;
        if (adata(16, i) == 3 || adata(16, i) == 25 || adata(16, i) == 29
            || adata(16, i) == 42)
        {
            f = 1;
        }
        if (gdata_wizard)
        {
            if (adata(0, i) == 3 || adata(0, i) == 2)
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            list(0, p) = i;
            list(1, p) = adata(6, i);
            ELONA_APPEND_PROMPT(
                mapname(i) + u8" "s + cnvrank((adata(6, i) - adata(17, i) + 1))
                    + lang(u8"階"s, u8" Lv"s),
                u8"null"s,
                ""s + promptmax);
            ++p;
        }
    }
    listmax = p;
    if (listmax == 0)
    {
        txt(lang(
            u8"この大陸には帰還できる場所が無い。"s,
            u8"You don't know any location you can return to"s));
        return;
    }
    txt(lang(u8"どの場所に帰還する？"s, u8"Where do you want to go?"s));
    display_msg(inf_screeny + inf_tiles);
    rtval = show_prompt(promptx, prompty, 240);
    update_screen();
    if (rtval >= 0)
    {
        txt(lang(
            u8"周囲の大気がざわめきだした。"s,
            u8"The air around you becomes charged."s));
        if (adata(16, gdata_current_map) == 8)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    txt(lang(
                        u8"このままダンジョンを出ると、この階のクエストは達成できない…"s,
                        u8"The lord of the dungeon might disappear if you escape now."s));
                }
            }
        }
        gdata_destination_map = list(0, rtval);
        gdata_destination_dungeon_level = list(1, rtval);
        gdata_is_returning_or_escaping = 15 + rnd(15);
    }
    update_screen();
    return;
}



turn_result_t do_gatcha()
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
    txt(lang(
        ""s + matname(tmat) + u8"を使ってガシャガシャする？"s,
        u8"Pay "s + matname(tmat) + u8" to gasha-gasha?"s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    if (rtval == 0)
    {
        if (mat(tmat) > 0)
        {
            snd(56);
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
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        else
        {
            txt(lang(
                ""s + matname(tmat) + u8"を持っていない…"s,
                u8"You don't have "s + matname(tmat) + u8"."s));
        }
    }
    return turn_result_t::turn_end;
}



int label_2083()
{
    if (inv[ci].id == 563)
    {
        if (sdata.get(inv[ci].param1, 0).original_level == 0)
        {
            txt(lang(
                u8"この本の内容には興味がない。それでも読む？ "s,
                u8"You are not interested in this book. Do you want to read it anyway? "s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval != 0)
            {
                return 0;
            }
        }
    }
    gdata(91) = 104;
    continuous_action_others();
    return 1;
}



void dump_player_info()
{
    cc = 0;
    access_class_info(2, cdatan(3, 0));
    buff = "";
    notesel(buff);
    noteadd(latest_version.long_string());
    noteadd(
        u8"キャラクター情報 "s + gdata_year + u8"年"s + gdata_month + u8"月"s
        + gdata_day + u8"日 "s + gdata_hour + u8"時"s + gdata_minute + u8"分  "s
        + mdatan(0));
    noteadd(""s);
    noteadd(
        u8"  "s + fixtxt((""s + cdatan(1, 0) + cdatan(0, 0)), 34)
        + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[0].sex) + u8" "s + calcage(0)
        + u8"歳"s + u8"  "s + cdata[0].height + u8"cm"s + u8" "s
        + cdata[0].weight + u8"kg"s);
    noteadd(""s);
    noteadd(
        fixtxt(
            u8"種族       : "s + i18n::_(u8"race", cdatan(2, 0), u8"name"), 30)
        + fixtxt(
              (u8"信仰      : "s + i18n::_(u8"god", cdata[0].god_id, u8"name")),
              32));
    noteadd(
        fixtxt(u8"職業       : "s + classname, 30)
        + fixtxt((u8"所属      : "s + guildname()), 32));
    noteadd(
        fixtxt(u8"レベル     : "s + cdata[0].level, 30)
        + fixtxt((u8"経過日数  : "s + gdata_play_days), 32));
    noteadd(
        fixtxt(u8"残りBP     : "s + cdata[0].skill_bonus, 30)
        + fixtxt((u8"経過ターン: "s + gdata_play_turns), 32));
    noteadd(
        fixtxt(u8"金貨       : "s + cdata[0].gold, 30)
        + fixtxt((u8"殺害数    : "s + gdata_kill_count), 32));
    noteadd(
        fixtxt(u8"プラチナ   : "s + cdata[0].platinum_coin, 30)
        + fixtxt(
              (u8"最深到達  : "s + gdata_deepest_dungeon_level + u8"階相当"s),
              32));
    noteadd(fixtxt(
        u8"プレイ時間 : "s
            + cnvplaytime(
                  (gdata_play_time + timeGetTime() / 1000 - time_begin)),
        30));
    noteadd(""s);
    s(1) = u8"生命力    : "s + sdata(2, 0) + u8"("s
        + sdata.get(2, 0).original_level + u8")"s;
    s(2) = u8"マナ      : "s + sdata(3, 0) + u8"("s
        + sdata.get(3, 0).original_level + u8")"s;
    s(3) = u8"狂気度    : "s + cdata[0].insanity;
    s(4) = u8"速度      : "s + cdata[0].current_speed;
    s(5) = u8"名声度    : "s + cdata[0].fame;
    s(6) = u8"カルマ    : "s + cdata[0].karma;
    s(7) = u8"DV        : "s + cdata[0].dv;
    s(8) = u8"PV        : "s + cdata[0].pv;
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
    for (int cnt = 100; cnt < 130; ++cnt)
    {
        if (cdata_body_part(cc, cnt) != 0)
        {
            if (trait(206) != 0)
            {
                if (cdata_body_part(cc, cnt) / 10000 == 2)
                {
                    continue;
                }
            }
            if (trait(203) != 0)
            {
                if (cdata_body_part(cc, cnt) / 10000 == 9)
                {
                    continue;
                }
            }
            if (trait(205) != 0)
            {
                if (cdata_body_part(cc, cnt) / 10000 == 3)
                {
                    continue;
                }
            }
            p(1) = cdata_body_part(cc, cnt);
            q(0) = u8"装備なし"s;
            q(1) = "";
            if (p(1) % 10000 != 0)
            {
                p(1) = p(1) % 10000 - 1;
                q(0) = itemname(p(1));
                q(1) = cnvweight(inv[p(1)].weight);
                ci = p(1);
                dump_return = 1;
                show_item_description();
            }
            else
            {
                listmax = 0;
            }
            s = i18n::_(
                u8"ui",
                u8"body_part",
                u8"_"s + (cdata_body_part(cc, cnt) / 10000));
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
    dump_return = 1;
    tc = 0;
    label_1969();
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
        if (cdata[cnt].state == 0)
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
            + i18n::_(u8"race", cdatan(2, cnt), u8"name") + u8"の"s + classname
            + u8" "s + i18n::_(u8"ui", u8"sex", u8"_"s + cdata[cnt].sex)
            + u8" "s + calcage(cnt) + u8"歳"s + u8"  "s + cdata[cnt].height
            + u8"cm"s + u8" "s + cdata[cnt].weight + u8"kg"s);
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
        if (gdata(120 + cnt) < 10000)
        {
            noteadd(
                ""s + ranktitle(cnt) + u8" Rank."s + gdata((120 + cnt)) / 100);
            s = u8"給料: 約 "s + calcincome(cnt) + u8" gold  "s + u8"ノルマ: "s;
            gold += calcincome(cnt);
            if (cnt == 3 || cnt == 4 || cnt == 5 || cnt == 8)
            {
                s += u8"なし"s;
            }
            else
            {
                s += ""s + gdata((140 + cnt)) + u8"日以内"s;
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
            inv[cnt].number = 0;
        }
    }
    return;
}



void label_2088()
{
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state == 1)
        {
            if (cdata[cnt].position.x < 0 || cdata[cnt].position.x >= mdata(0)
                || cdata[cnt].position.y < 0
                || cdata[cnt].position.y >= mdata(1))
            {
                cdata[cnt].position.x = 0;
                cdata[cnt].position.y = 0;
            }
        }
    }
    if (mdata(6) != 5)
    {
        if (mdata(18) != 0)
        {
            mdata(18) = 0;
        }
    }
    if (gdata_current_map == 7)
    {
        adata(17, gdata_current_map) = 0;
        adata(10, gdata_current_map) = 10;
        adata(12, gdata_current_map) = 1;
        mdata(8) = 1;
        event_add(17);
        calccosthire();
    }
    return;
}



void migrate_save_data()
{
    int p1 = 0;
    int p3 = 0;
    if (gdata_version != 1220)
    {
        dialog(lang(
            u8"Ver."s + gdata_version
                + u8"のセーブデータをアップデートします。"s,
            u8"Updating your save data from Ver."s + gdata_version
                + u8" now."s));
    }
    if (gdata_rights_to_succeed_to < 0)
    {
        gdata_rights_to_succeed_to = 1;
    }
    if (gdata_departure_date == 0)
    {
        gdata_departure_date = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12;
    }
    for (int i = 0; i < 20; ++i)
    {
        if (gdata(120 + i) == 0)
        {
            gdata(120 + i) = 10000;
        }
    }
    itemmemory(2, 289) = 0;
    itemmemory(2, 732) = 0;
    if (gdata_version < 1170)
    {
        if (adata(0, gdata_current_map) != 3)
        {
            dialog(lang(
                u8"アップデートを行うには、街中でセーブしたセーブデータが必要です。"s,
                u8"To update your game, please save your game in a town in the previous version then retry."s));
            finish_elona();
            return;
        }
        dialog(lang(
            u8"次のプロセスの完了までには、しばらく時間がかかることがあります。"s,
            u8"The next updating process may take a while to complete."s));
        memcpy(adata, 0, 300, adata, 0, 100, 8000);
        memcpy(adata, 0, 450, adata, 0, 150, 8000);
        for (int cnt = 100; cnt < 200; ++cnt)
        {
            p = cnt;
            for (int cnt = 0; cnt < 40; ++cnt)
            {
                adata(cnt, p) = 0;
            }
            for (const auto& entry : filesystem::dir_entries{
                     filesystem::dir::tmp(),
                     filesystem::dir_entries::type::file,
                     std::regex{u8R"(.*_)"s + std::to_string(p)
                                + u8R"(_.*\..*)"}})
            {
                const auto file = entry.path().filename();
                p1 = instr(filesystem::to_utf8_path(file), 0, u8"_"s);
                p2 = instr(filesystem::to_utf8_path(file), p1 + 1, u8"_"s);
                if (p >= 150)
                {
                    p3 = p - 150 + 450;
                }
                else
                {
                    p3 = p - 100 + 300;
                }
                const auto file_cnv = filesystem::dir::tmp()
                    / ((strmid(filesystem::to_utf8_path(file), 0, (p1 + 1))
                        + p3)
                       + strmid(
                             filesystem::to_utf8_path(file),
                             (p1 + p2 + 1),
                             20));
                const auto file_ = filesystem::dir::tmp() / file;
                bcopy(file_, file_cnv);
                fileadd(file_cnv);
                elona_delete(file_);
                fileadd(file_, 1);
            }
        }
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (adata(16, cnt) != 0)
            {
                if (adata(30, cnt) == 0)
                {
                    adata(30, cnt) = 4;
                }
            }
        }
        gdata(850) = 4;
    }
    if (gdata_version != 1220)
    {
        gdata(79) = 1;
    }
    chara_delete(56);
    if (gdata_version > 1220)
    {
        dialog(u8"invalid version"s);
        finish_elona();
        return;
    }
    gdata_version = 1220;
    cdata[0].has_own_sprite() = true;
    initialize_recipememory();
    return;
}



void label_2090()
{
    ++gdata(184);
    DIM3(qdata, 20, 500);
    SDIM3(qname, 40, 500);
    gdata_number_of_existing_quests = 0;
    initialize_adata();
    return;
}



void get_inheritance()
{
    ctrl_file(file_operation2_t::_4, u8"shop3.s2");
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
    cdata[0].gold += clamp(cdata[56].gold / 100, 1000, 100000);
    cdata[0].platinum_coin += p;
    cdata[0].skill_bonus += i;
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        mat(cnt) = mat(cnt) / 3;
    }
    return;
}



void load_gene_files()
{
    ctrl_file(file_operation_t::_15);
    DIM2(spell, 200);
    DIM2(spact, 500);
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        cdata[cnt].state = 0;
    }
    sdata.copy(56, 0);
    sdata.clear(0);
    cdata(56) = cdata(0);
    cdata(0).clear();
    for (const auto& cnt : items(-1))
    {
        inv[cnt].number = 0;
    }
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number == 0)
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
        if (inv[cnt].quality == 6)
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
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        chara_delete(cnt);
    }
    gdata_play_time = genetemp(805);
    return;
}



void save_gene()
{
    ctrl_file(file_operation_t::_14);
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



void create_cnpc()
{
    elona_vector1<std::string> unres;
    if (initunid)
    {
        cdata[rc].cnpc_id = initunid - 1;
        initunid = 0;
    }
    cun = cdata[rc].cnpc_id;
    cdata[rc].id = 343;
    if (initlv != 0)
    {
        cdata[rc].level = initlv;
    }
    else
    {
        cdata[rc].level = clamp(userdata(2, cun), 1, 100);
    }
    cdata[rc].portrait = -1;
    creaturepack = 0;
    cdata[rc].ai_act_sub_freq = unaiactsubfreq(cun);

    cdata[rc].normal_actions.clear();
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        int action = userdata(15 + cnt, cun);
        if (action == 0)
            break;
        cdata[rc].normal_actions.push_back(action);
    }
    cdata[rc].special_actions.clear();
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        int action = userdata(20 + cnt, cun);
        if (action == 0)
            break;
        cdata[rc].special_actions.push_back(action);
    }

    if (userdatan(5, cun) != ""s)
    {
        SDIM3(unres, 6, 32);
        csvstr2(unres, userdatan(5, cun));
        for (int cnt = 0;; ++cnt)
        {
            if (cnt > 15 || unres(cnt) == ""s)
            {
                break;
            }
            sdata(elona::stoi(unres(cnt * 2)), rc) +=
                elona::stoi(unres((cnt * 2 + 1))) * 50;
        }
    }
    cdata[rc].can_talk = 1;
    cdatan(0, rc) = userdatan(1, cun);
    cdatan(5, rc) = userdatan(0, cun);
    cdata[rc].relationship = clamp(userdata(4, cun), -3, 10);
    cdata[rc].ai_calm = clamp(userdata(7, cun), 1, 4);
    cdata[rc].ai_move = clamp(userdata(8, cun), 0, 100);
    cdata[rc].ai_dist = clamp(userdata(9, cun), 1, 100);
    if (userdata(11, cun))
    {
        cdata[rc].element_of_unarmed_attack =
            clamp(userdata(11, cun), 5000000, 6400000);
    }
    cdata[rc].ai_heal = userdata(10, cun);
    access_race_info(3, userdatan(2, cun));
    access_class_info(3, userdatan(3, cun));
    cdata[rc].sex = userdata(3, cun);
    if (userdata(3, cun) != 0)
    {
        if (userdata(3, cun) != 1)
        {
            cdata[rc].sex = rnd(2);
        }
    }
    if (userdata(5, cun))
    {
        fixlv = clamp(userdata(5, cun), 0, 6);
    }
    cspecialeq = 0;
    cdata[rc].original_relationship = cdata[rc].relationship;
    fixaiact(rc);
    setunid(rc, cun);
    return;
}



void load_save_data(const fs::path& base_save_dir)
{
    ELONA_LOG("Load save data: " << playerid);

    filemod = "";
    ctrl_file(file_operation_t::_10);
    const auto save_dir = base_save_dir / filesystem::u8path(playerid);
    buff(0).clear();
    if (!fs::exists(save_dir / u8"filelist.txt"))
    {
        ELONA_LOG("Load save data: from directory");
        for (const auto& entry :
             filesystem::dir_entries{save_dir,
                                     filesystem::dir_entries::type::file,
                                     std::regex{u8R"(.*\..*)"}})
        {
            buff += filesystem::to_utf8_path(entry.path().filename()) + '\n';
        }
    }
    else
    {
        ELONA_LOG("Load save data: from filelist.txt");
        std::ifstream in{(save_dir / u8"filelist.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) +=
                filesystem::to_utf8_path(filesystem::path(tmp).filename())
                + '\n';
        }
    }
    notesel(buff);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(s, cnt);
        if (strutil::contains(s(0), u8".s2"))
        {
            bcopy(save_dir / s(0), filesystem::dir::tmp() / s(0));
        }
    }
    ELONA_LOG("asd " << save_dir);
    ctrl_file(file_operation2_t::_7, save_dir);
    migrate_save_data();
    set_item_info();
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].has_own_sprite() == 1 || cnt == 0)
        {
            create_pcpic(cnt, true);
        }
    }
    if (gdata_wizard == 1)
    {
        cdatan(1, 0) = u8"*Debug*"s;
    }
    refreshspeed(0);
    time_begin = timeGetTime() / 1000;
    return;
}


void save_game()
{
    save_game(filesystem::dir::save());
}

void save_game(const fs::path& base_save_dir)
{
    ELONA_LOG("Save game: " << playerid);

    int save_f = 0;
    if (gdata_current_map == 35)
    {
        txtef(3);
        txt(lang(
            u8"ユーザーマップの中ではセーブできない。"s,
            u8"The game is not saved in a user map."s));
        update_screen();
        return;
    }
    ctrl_file(file_operation_t::_2);
    ctrl_file(file_operation2_t::_4, u8"inv_"s + mid + u8".s2");
    save_f = 0;
    for (const auto& entry : filesystem::dir_entries{
             base_save_dir, filesystem::dir_entries::type::dir})
    {
        if (filesystem::to_utf8_path(entry.path().filename()) == playerid)
        {
            save_f = 1;
            break;
        }
    }
    const auto save_dir = base_save_dir / filesystem::u8path(playerid);
    if (save_f == 0)
    {
        mkdir(save_dir);
    }
    notesel(filemod);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        std::string save_s;
        noteget(save_s, cnt);
        if (save_s.empty())
            continue;
        const auto save_p = save_s.front() == '*';
        save_s = save_s.substr(1);
        const auto path = save_dir / filesystem::u8path(save_s);
        if (save_p)
        {
            bcopy(filesystem::dir::tmp() / filesystem::u8path(save_s), path);
        }
        else
        {
            if (fs::exists(path) && !fs::is_directory(path))
            {
                elona_delete(path);
            }
        }
    }
    ctrl_file(file_operation2_t::_8, save_dir);
    filemod = "";
    buff(0).clear();
    for (const auto& entry :
         filesystem::dir_entries{filesystem::dir::tmp(),
                                 filesystem::dir_entries::type::file,
                                 std::regex{u8R"(.*\..*)"}})
    {
        buff += filesystem::to_utf8_path(entry.path().filename()) + '\n';
    }
    notesel(buff);
    {
        std::ofstream out{
            (save_dir / u8"filelist.txt").native(),
            std::ios::binary};
        out << buff(0) << std::endl;
    }
    ELONA_LOG("Save game: finish");
}



turn_result_t do_enter_strange_gate()
{
    snd(49);
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
    gdata_destination_map = 35;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    return turn_result_t::exit_map;
}



int ask_direction()
{
    snd(26);
    gsel(4);
    x = (cdata[0].position.x - scx) * inf_tiles + inf_screenx - 48;
    y = (cdata[0].position.y - scy) * inf_tiles + inf_screeny - 48;
    gmode(0);
    pos(0, 0);
    gcopy(0, x, y, 144, 144);
    gsel(0);
    t = 0;
label_2128_internal:
    ++t;
    gmode(4, 28, 28, 200 - t / 2 % 20 * (t / 2 % 20));
    x = (cdata[0].position.x - scx) * inf_tiles + inf_screenx + 24;
    y = (cdata[0].position.y - scy) * inf_tiles + inf_screeny + 24;
    if (key_alt == 0)
    {
        pos(x, y - 48);
        grotate(3, 212, 432, 0, 28, 28);
        pos(x, y + 48);
        grotate(3, 212, 432, 1.0 * 3.14, 28, 28);
        pos(x + 48, y);
        grotate(3, 212, 432, 0.5 * 3.14, 28, 28);
        pos(x - 48, y);
        grotate(3, 212, 432, 1.5 * 3.14, 28, 28);
    }
    pos(x - 48, y - 48);
    grotate(3, 212, 432, 1.75 * 3.14, 28, 28);
    pos(x + 48, y + 48);
    grotate(3, 212, 432, 0.75 * 3.14, 28, 28);
    pos(x + 48, y - 48);
    grotate(3, 212, 432, 0.25 * 3.14, 28, 28);
    pos(x - 48, y + 48);
    grotate(3, 212, 432, 1.25 * 3.14, 28, 28);
    redraw();
    gmode(0);
    pos(x - 48 - 24, y - 48 - 24);
    gcopy(4, 0, 0, 144, 144);
    gmode(2);
    await(30);
    key_check(1);
    x = cdata[0].position.x;
    y = cdata[0].position.y;
    if (key == key_alter)
    {
        goto label_2128_internal;
    }
    if (key == key_wait || key == key_enter)
    {
        tlocx = x;
        tlocy = y;
        keyhalt = 1;
        return 1;
    }
    if (key == key_north)
    {
        if (key_alt)
        {
            goto label_2128_internal;
        }
        else
        {
            y -= 1;
        }
    }
    if (key == key_south)
    {
        if (key_alt)
        {
            goto label_2128_internal;
        }
        else
        {
            y += 1;
        }
    }
    if (key == key_west)
    {
        if (key_alt)
        {
            goto label_2128_internal;
        }
        else
        {
            x -= 1;
        }
    }
    if (key == key_east)
    {
        if (key_alt)
        {
            goto label_2128_internal;
        }
        else
        {
            x += 1;
        }
    }
    if (key == key_northwest)
    {
        x -= 1;
        y -= 1;
    }
    if (key == key_northeast)
    {
        x += 1;
        y -= 1;
    }
    if (key == key_southwest)
    {
        x -= 1;
        y += 1;
    }
    if (key == key_southeast)
    {
        x += 1;
        y += 1;
    }
    if (key != ""s)
    {
        if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
        {
            x = cdata[0].position.x;
            y = cdata[0].position.y;
            keyhalt = 1;
            return 0;
        }
        if (x == cdata[0].position.x && y == cdata[0].position.y)
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



turn_result_t do_debug_console()
{
    notesel(dbm);
    buff = "";
    if (dbm == ""s)
    {
        noteadd(latest_version.long_string());
        noteadd(u8"Debug Console    Type \"?\" for help. Hit ESC to exit."s);
        noteadd(""s);
    }
    font(14 - en * 2);
    objmode(2);
    pos(0, 24);
    mesbox(dbm);
    pos(0, 0);
    mesbox(buff);
    objsel(2);
    while (1)
    {
        await(20);
        int a{};
        stick(a);
        if (a == 128)
        {
            return do_exit_debug_console();
        }
    }
}



turn_result_t do_exit_debug_console()
{
    clrobj(1);
    clrobj(2);
    if (dbg_exitshowroom == 1)
    {
        dbg_exitshowroom = 0;
        levelexitby = 4;
        return turn_result_t::exit_map;
    }
    return turn_result_t::pc_turn_user_error;
}



int efstatusfix(int doomed, int cursed, int none, int blessed)
{
    switch (efstatus)
    {
    case curse_state_t::doomed: return doomed;
    case curse_state_t::cursed: return cursed;
    case curse_state_t::none: return none;
    case curse_state_t::blessed: return blessed;
    default: assert(0);
    }
}



int search_material_spot()
{
    if (map(cdata[0].position.x, cdata[0].position.y, 6) == 0)
    {
        return 0;
    }
    if (feat(1) < 24 || 28 < feat(1))
    {
        return 0;
    }
    atxspot = 11;
    atxlv = gdata_current_dungeon_level;
    if (mdata(6) == 20)
    {
        atxspot = 9;
    }
    if (mdata(6) == 21)
    {
        atxspot = 12;
    }
    if (mdata(6) == 22)
    {
        atxspot = 10;
    }
    if (mdata(6) == 23)
    {
        atxspot = 12;
    }
    if (mdata(6) == 1)
    {
        atxlv = cdata[0].level / 2 + rnd(10);
        if (atxlv > 30)
        {
            atxlv = 30 + rnd((rnd(atxlv - 30) + 1));
        }
        if (4 <= gdata(62) && gdata(62) < 9)
        {
            atxspot = 10;
        }
        if (264 <= gdata(62) && gdata(62) < 363)
        {
            atxspot = 11;
        }
        if (9 <= gdata(62) && gdata(62) < 13)
        {
            atxspot = 10;
        }
        if (13 <= gdata(62) && gdata(62) < 17)
        {
            atxspot = 11;
        }
    }
    cell_featread(cdata[0].position.x, cdata[0].position.y);
    if (feat(1) == 27)
    {
        atxlv += sdata(161, 0) / 3;
        atxspot = 16;
    }
    if (feat(1) == 26)
    {
        atxspot = 13;
    }
    if (feat(1) == 25)
    {
        atxspot = 14;
    }
    if (feat(1) == 28)
    {
        atxspot = 15;
    }
    if (rnd(7) == 0)
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            i = 5;
            if (atxspot == 14)
            {
                if (sdata(163, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(lang(
                        u8"採掘に失敗した。"s,
                        u8"Your mining attempt fails."s));
                    break;
                }
                i = 1;
                skillexp(163, 0, 40);
            }
            if (atxspot == 13)
            {
                if (sdata(185, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(lang(
                        u8"釣りに失敗した。"s,
                        u8"Your fishing attempt fails."s));
                    break;
                }
                i = 2;
                skillexp(185, 0, 40);
            }
            if (atxspot == 15)
            {
                if (sdata(180, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(lang(
                        u8"採取に失敗した。"s,
                        u8"Your searching attempt fails."s));
                    break;
                }
                i = 3;
                skillexp(180, 0, 30);
            }
            matgetmain(random_material(atxlv, 0), 1, i);
        }
    }
    if (rnd(50 + trait(159) * 20) == 0)
    {
        s = lang(u8"もう何もない。"s, u8"You can't find anything anymore."s);
        if (feat(1) == 26)
        {
            s = lang(u8"泉は干上がった。"s, u8"The spring dries up."s);
        }
        if (feat(1) == 25)
        {
            s = lang(
                u8"鉱石を掘りつくした。"s, u8"There's no more ore around."s);
        }
        if (feat(1) == 28)
        {
            s = lang(
                u8"もう目ぼしい植物は見当たらない。"s,
                u8"There's no more plant around."s);
        }
        txt(s);
        rowactend(cc);
        map(cdata[0].position.x, cdata[0].position.y, 6) = 0;
    }
    return 0;
}



void disarm_trap()
{
    cell_featset(movx, movy, 0);
    if (cdata[cc].god_id == core_god::mani)
    {
        txt(lang(u8"あなたは罠を解体した。"s, u8"You dismantle the trap."s));
        for (int cnt = 0, cnt_end = (rnd(3) + 1); cnt < cnt_end; ++cnt)
        {
            atxspot = 19;
            matgetmain(
                random_material(
                    gdata_current_dungeon_level,
                    gdata_current_dungeon_level / 5),
                1);
        }
    }
    else
    {
        txt(lang(u8"罠を解除した。"s, u8"You disarm the trap."s));
    }
}



void proc_trap()
{
label_21451_internal:
    if (config::instance().scroll)
    {
        if (cc == 0)
        {
            label_1438();
        }
    }
    map(cdata[cc].position.x, cdata[cc].position.y, 1) = 0;
    cdata[cc].position.x = cdata[cc].next_position.x;
    cdata[cc].position.y = cdata[cc].next_position.y;
    map(cdata[cc].next_position.x, cdata[cc].next_position.y, 1) = cc + 1;
    if (cc == 0)
    {
        if (gdata_mount != 0)
        {
            cdata[gdata_mount].position.x = cdata[0].position.x;
            cdata[gdata_mount].position.y = cdata[0].position.y;
        }
    }
    movx = cdata[cc].position.x;
    movy = cdata[cc].position.y;
    if (map(movx, movy, 6) != 0)
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
            refdiff = 100 + gdata_current_dungeon_level * 3;
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
                            txt(lang(
                                u8"解除に失敗した。"s,
                                u8"You fail to disarm the trap."s));
                        }
                    }
                }
            }
            int stat = can_evade_trap();
            if (stat == 1)
            {
                if (is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"は罠を避けた。"s,
                        name(cc) + u8" evade"s + _s(cc) + u8" a trap."s));
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
                    snd(70);
                }
                efsource = 5;
                if (is_in_fov(cc))
                {
                    txt(lang(
                        aln(cc) + u8"罠にかかった！"s,
                        name(cc) + u8" activate"s + _s(cc) + u8" a trap!"s));
                }
                if (feat(2) == 4)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"墨が噴き出した。"s,
                            u8"Gallons of ink spreads."s));
                    }
                    dmgcon(
                        cc,
                        status_ailment_t::blinded,
                        100 + gdata_current_dungeon_level * 2);
                }
                if (feat(2) == 6)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"刺激的な匂いがただよう。"s,
                            u8"Stimulative gas spreads."s));
                    }
                    dmgcon(
                        cc,
                        status_ailment_t::paralyzed,
                        100 + gdata_current_dungeon_level * 2);
                }
                if (feat(2) == 5)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"臭い匂いがたちこめた。"s,
                            u8"Smelly gas spreads."s));
                    }
                    dmgcon(
                        cc,
                        status_ailment_t::confused,
                        100 + gdata_current_dungeon_level * 2);
                }
                if (feat(2) == 3)
                {
                    cell_featset(movx, movy, 0);
                    if (encfind(cc, 22) != -1)
                    {
                        if (is_in_fov(cc))
                        {
                            txt(lang(
                                u8"魔法の力がテレポートを防いだ。"s,
                                u8"Magical field prevents teleportation."s));
                        }
                        return;
                    }
                    for (int cnt = 0; cnt < 200; ++cnt)
                    {
                        cdata[cc].next_position.x = rnd(mdata(0) - 2) + 1;
                        cdata[cc].next_position.y = rnd(mdata(1) - 2) + 1;
                        cell_check(
                            cdata[cc].next_position.x,
                            cdata[cc].next_position.y);
                        if (cellaccess == 1)
                        {
                            if (is_in_fov(cc))
                            {
                                snd(72);
                                txt(lang(
                                    name(cc) + u8"は突然消えた。"s,
                                    u8"Suddenly, "s + name(cc) + u8" disappear"s
                                        + _s(cc) + u8"."s));
                            }
                            rowactend(cc);
                            update_screen();
                            break;
                        }
                    }
                    goto label_21451_internal;
                }
                if (feat(2) == 0)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"槍が地面から飛び出した。"s,
                            u8"Several spears fly out from the ground."s));
                    }
                    if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                    {
                        if (is_in_fov(cc))
                        {
                            txt(lang(
                                u8"しかし"s + name(cc)
                                    + u8"には届かなかった。"s,
                                u8"But they don't reach "s + name(cc)
                                    + u8"."s));
                        }
                    }
                    else
                    {
                        dmghp(
                            cc, rnd(gdata_current_dungeon_level * 2 + 10), -1);
                    }
                }
                if (feat(2) == 1)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"毒ガスが噴き出した。"s,
                            u8"Poisonous gas spreads."s));
                    }
                    dmgcon(
                        cc,
                        status_ailment_t::poisoned,
                        100 + gdata_current_dungeon_level * 2);
                }
                if (feat(2) == 2)
                {
                    if (is_in_fov(cc))
                    {
                        txt(lang(
                            u8"催眠ガスが噴き出した。"s,
                            u8"Sleeping gas spreads."s));
                    }
                    dmgcon(
                        cc,
                        status_ailment_t::sleep,
                        100 + gdata_current_dungeon_level * 2);
                }
                if (feat(2) == 7)
                {
                    txtef(9);
                    txt(lang(u8" *チュドーン！* "s, u8"*kabooom*"s));
                    aniref = 0;
                    anix = movx;
                    aniy = movy;
                    play_animation(2);
                    cell_featset(movx, movy, 0);
                    dmghp(cc, 100 + rnd(200), -1);
                }
                efsource = 0;
            }
        }
    }
    return;
}



void continuous_action_perform()
{
    static int performtips;

    if (cdata[cc].continuous_action_id == 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は"s + itemname(ci) + u8"の演奏をはじめた。"s,
                name(cc) + u8" start"s + _s(cc) + u8" to play "s + itemname(ci)
                    + u8"."s));
        }
        cdata[cc].continuous_action_id = 6;
        cdata[cc].continuous_action_turn = 61;
        cdata[cc].continuous_action_item = ci;
        cdata[cc].quality_of_performance = 40;
        cdata[cc].tip_gold = 0;
        if (cc == 0)
        {
            performtips = 0;
        }
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        ci = cdata[cc].continuous_action_item;
        if (cdata[cc].continuous_action_turn % 10 == 0)
        {
            if (is_in_fov(cc))
            {
                if (rnd(10) == 0)
                {
                    txtef(4);
                    txt(lang(u8"ﾁｬﾗﾝ♪ "s, u8"*Tiki*"s),
                        lang(u8"ﾎﾟﾛﾝ♪ "s, u8"*Dan*"s),
                        lang(u8"ﾀﾞｰﾝ♪ "s, u8"*Lala*"s));
                }
                txtef(4);
                txt(lang(u8"ｼﾞｬﾝ♪ "s, u8"*Cha*"s));
            }
        }
        if (cdata[cc].continuous_action_turn % 20 == 0)
        {
            gold = 0;
            make_sound(cdata[cc].position.x, cdata[cc].position.y, 5, 1, 1, cc);
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12
                    >= cdata[cnt].time_interest_revive)
                {
                    cdata[cnt].interest = 100;
                }
                if (is_in_fov(cc))
                {
                    if (cdata[cnt].vision_flag != msync)
                    {
                        continue;
                    }
                }
                else if (
                    dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[cnt].position.x,
                        cdata[cnt].position.y)
                    > 3)
                {
                    continue;
                }
                if (cdata[cnt].interest <= 0)
                {
                    continue;
                }
                if (cdata[cnt].sleep > 0)
                {
                    continue;
                }
                x = cdata[cnt].position.x;
                y = cdata[cnt].position.y;
                if (map(x, y, 1) == 0)
                {
                    continue;
                }
                tc = cnt;
                if (tc == cc)
                {
                    continue;
                }
                if (cdata[tc].relationship == -3)
                {
                    if (cdata[tc].hate == 0)
                    {
                        if (is_in_fov(tc))
                        {
                            txt(lang(
                                name(tc) + u8"は激怒した。"s,
                                name(tc) + u8" get"s + _s(tc) + u8" angry."s));
                        }
                    }
                    cdata[tc].hate = 30;
                    continue;
                }
                if (cc == 0)
                {
                    cdata[tc].interest -= rnd(15);
                    cdata[tc].time_interest_revive = gdata_hour + gdata_day * 24
                        + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12
                        + 12;
                }
                if (cdata[tc].interest <= 0)
                {
                    if (is_in_fov(cc))
                    {
                        txtef(9);
                        if (jp)
                        {
                            txt(u8"「飽きた」"s,
                                u8"「前にも聴いたよ」"s,
                                u8"「またこの曲か…」"s);
                        }
                        if (en)
                        {
                            txt(u8"\"Boring.\""s,
                                u8"\"I've heard this before.\""s,
                                u8"\"This song again?\""s);
                        }
                    }
                    cdata[tc].interest = 0;
                    continue;
                }
                if (sdata(183, cc) < cdata[tc].level)
                {
                    if (rnd(3) == 0)
                    {
                        cdata[cc].quality_of_performance -= cdata[tc].level / 2;
                        if (is_in_fov(cc))
                        {
                            txtef(9);
                            if (jp)
                            {
                                txt(u8"「引っ込め！」"s,
                                    u8"「うるさい！」"s,
                                    u8"「下手っぴ！」"s,
                                    u8"「何のつもりだ！」"s);
                            }
                            if (en)
                            {
                                txt(u8"\"Boo boo!\""s,
                                    u8"\"Shut it!\""s,
                                    u8"\"What are you doing!\""s,
                                    u8"\"You can't play shit.\""s);
                            }
                            txt(lang(
                                ""s + name(tc) + u8"は石を投げた。"s,
                                name(tc) + u8" throw"s + _s(tc)
                                    + u8" a rock."s));
                        }
                        dmg = rnd(cdata[tc].level + 1) + 1;
                        if (cdata[tc].id == 29)
                        {
                            dmg = cdata[tc].level * 2 + rnd(100);
                        }
                        dmghp(cc, dmg, -8);
                        if (cdata[cc].state == 0)
                        {
                            break;
                        }
                        continue;
                    }
                }
                if (rnd(3) == 0)
                {
                    p = cdata[cc].quality_of_performance
                            * cdata[cc].quality_of_performance
                            * (100
                               + inv[cdata[cc].continuous_action_item].param1
                                   / 5)
                            / 100 / 1000
                        + rnd(10);
                    p = clamp(
                        cdata[tc].gold * clamp(p(0), 1, 100) / 125,
                        0,
                        sdata(183, cc) * 100);
                    if (tc < 16)
                    {
                        p = rnd(clamp(p(0), 1, 100)) + 1;
                    }
                    if ((cdata[tc].character_role >= 1000
                         && cdata[tc].character_role < 2000)
                        || cdata[tc].character_role == 2003)
                    {
                        p /= 5;
                    }
                    if (p > cdata[tc].gold)
                    {
                        p = cdata[tc].gold;
                    }
                    cdata[tc].gold -= p;
                    cdata[cc].gold += p;
                    gold += p;
                }
                if (cdata[tc].level > sdata(183, cc))
                {
                    continue;
                }
                p = rnd(cdata[tc].level + 1) + 1;
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 2 + 1))
                {
                    if (gdata_executing_immediate_quest_type == 1009)
                    {
                        if (tc >= 57)
                        {
                            cdata[tc].impression += rnd(3);
                            calcpartyscore();
                        }
                    }
                    if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance += p;
                    }
                    else if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance -= p;
                    }
                }
                if (encfindspec(cdata[cc].continuous_action_item, 60))
                {
                    if (rnd(15) == 0)
                    {
                        dmgcon(tc, status_ailment_t::drunk, 500);
                    }
                }
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 5 + 1))
                {
                    if (rnd(3) == 0)
                    {
                        if (is_in_fov(cc))
                        {
                            txtef(9);
                            if (jp)
                            {
                                txt(name(tc) + u8"は歓声を上げた。"s,
                                    name(tc) + u8"は目を輝かせた。"s,
                                    u8"「ブラボー」"s,
                                    u8"「いいぞ！」"s,
                                    name(tc) + u8"はうっとりした。"s,
                                    name(tc) + u8"は"s + name(cc)
                                        + u8"の演奏を褒め称えた。"s);
                            }
                            if (en)
                            {
                                txt(name(tc) + u8" clap"s + _s(tc) + u8"."s,
                                    name(tc) + u8" listene"s + _s(tc)
                                        + u8" to "s + name(cc) + your(cc)
                                        + u8" music joyfully."s,
                                    u8"\"Bravo!\""s,
                                    u8"\"Nice song.\""s,
                                    u8"\"Scut!\""s,
                                    name(tc) + u8" "s + is(tc)
                                        + u8" excited!"s);
                            }
                        }
                        cdata[cc].quality_of_performance += cdata[tc].level + 5;
                        if (cc == 0)
                        {
                            if (tc >= 16)
                            {
                                if (rnd(performtips * 2 + 2) == 0)
                                {
                                    x = clamp(
                                        cdata[cc].position.x - 1 + rnd(3),
                                        0,
                                        mdata(0) - 1);
                                    y = clamp(
                                        cdata[cc].position.y - 1 + rnd(3),
                                        0,
                                        mdata(1) - 1);
                                    cell_check(x, y);
                                    if (cellaccess == 0)
                                    {
                                        continue;
                                    }
                                    if (fov_los(
                                            cdata[tc].position.x,
                                            cdata[tc].position.y,
                                            x,
                                            y)
                                        == 0)
                                    {
                                        continue;
                                    }
                                    if (encfindspec(
                                            cdata[cc].continuous_action_item,
                                            49))
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 8),
                                            calcfixlv(3 + (rnd(4) == 0)));
                                    }
                                    else
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 10),
                                            calcfixlv(3));
                                    }
                                    flttypemajor =
                                        fsetperform(rnd(length(fsetperform)));
                                    dbid = 0;
                                    if (gdata_executing_immediate_quest_type
                                        == 1009)
                                    {
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 241;
                                        }
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 622;
                                        }
                                        if (cdata[tc].level > 15)
                                        {
                                            if (rnd(1000) == 0)
                                            {
                                                dbid = 725;
                                            }
                                        }
                                        if (cdata[tc].level > 10)
                                        {
                                            if (rnd(800) == 0)
                                            {
                                                dbid = 726;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (rnd(10) == 0)
                                        {
                                            dbid = 724;
                                        }
                                        if (rnd(250) == 0)
                                        {
                                            dbid = 55;
                                        }
                                    }
                                    int stat = itemcreate(-1, dbid, x, y, 1);
                                    if (stat != 0)
                                    {
                                        --inv[ci].number;
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ccbk = cc;
                                        cc = tc;
                                        aniref(0) = inv[ci].image;
                                        aniref(1) = inv[ci].color;
                                        anix = inv[ci].position.x;
                                        aniy = inv[ci].position.y;
                                        play_animation(15);
                                        cc = ccbk;
                                        ++inv[ci].number;
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ++performtips;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (gold != 0)
            {
                cdata[cc].tip_gold += gold;
                if (is_in_fov(cc))
                {
                    snd(11);
                }
            }
        }
        return;
    }
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cc != 0)
        {
            break;
        }
        if (cdata[cc].quality_of_performance < 0)
        {
            txt(lang(u8"まるで駄目だ…"s, u8"It is a waste of time."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 20)
        {
            txt(lang(u8"不評だった…"s, u8"Almost everyone ignores you."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 40)
        {
            txt(lang(
                u8"もっと練習しなくては…"s,
                u8"You need to practice lot more."s));
            break;
        }
        if (cdata[cc].quality_of_performance == 40)
        {
            txt(lang(u8"演奏を終えた。"s, u8"You finish your performance."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 60)
        {
            txt(lang(u8"いまいちだ。"s, u8"Not good."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 80)
        {
            txt(lang(
                u8"手ごたえがあった。"s,
                u8"People seem to like your performance."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 100)
        {
            txt(lang(
                u8"納得できる演奏ができた。"s,
                u8"Your performance is successful."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 120)
        {
            txt(lang(u8"大盛況だ！"s, u8"Wonderful!"s));
            break;
        }
        if (cdata[cc].quality_of_performance < 150)
        {
            txt(lang(
                u8"素晴らしい！"s,
                u8"Great performance. Everyone cheers you."s));
            break;
        }
        txt(lang(u8"歴史に残る名演だ！"s, u8"A Legendary stage!"s));
        break;
    }
    if (cdata[cc].quality_of_performance > 40)
    {
        cdata[cc].quality_of_performance = cdata[cc].quality_of_performance
            * (100 + inv[cdata[cc].continuous_action_item].param1 / 5) / 100;
    }
    if (cdata[cc].tip_gold != 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は合計 "s + cdata[cc].tip_gold
                    + i18n::_(u8"ui", u8"gold") + u8"のおひねりを貰った。"s,
                u8"The audience gives "s + name(cc) + u8" total of "s
                    + cdata[cc].tip_gold + u8" gold pieces."s));
        }
    }
    rowactend(cc);
    int experience = cdata[cc].quality_of_performance - sdata(183, cc) + 50;
    if (experience > 0)
    {
        skillexp(183, cc, experience, 0, 0);
    }
    return;
}



void continuous_action_sex()
{
    int sexhost = 0;
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 11;
        cdata[cc].continuous_action_turn = 25 + rnd(10);
        cdata[cc].continuous_action_target = tc;
        cdata[tc].continuous_action_id = 11;
        cdata[tc].continuous_action_turn = cdata[cc].continuous_action_turn * 2;
        cdata[tc].continuous_action_target = cc + 10000;
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は服を脱ぎ始めた。"s,
                name(cc) + u8" begin"s + _s(cc) + u8" to take "s + his(cc)
                    + u8" clothes off."s));
        }
        return;
    }
    sexhost = 1;
    tc = cdata[cc].continuous_action_target;
    if (tc >= 10000)
    {
        tc -= 10000;
        sexhost = 0;
    }
    if (cdata[tc].state != 1 || cdata[tc].continuous_action_id != 11)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"「そ、その"s
                    + i18n::_(u8"ui", u8"sex2", u8"_"s + cdata[tc].sex)
                    + u8"とは体だけの関係"s + _da() + _ore(3)
                    + u8"は何も知らないから、命だけは…！」"s,
                u8"\"I-I don't really know that "s
                    + i18n::_(u8"ui", u8"sex2", u8"_"s + cdata[tc].sex)
                    + u8". Please spare my life!\""s));
        }
        rowactend(cc);
        rowactend(tc);
        return;
    }
    if (cc == 0)
    {
        if (!actionsp(0, 1 + rnd(2)))
        {
            txt(lang(u8"疲労し過ぎて失敗した！"s, u8"You are too exhausted!"s));
            rowactend(cc);
            rowactend(tc);
            return;
        }
    }
    cdata[cc].emotion_icon = 317;
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (sexhost == 0)
        {
            if (cdata[cc].continuous_action_turn % 5 == 0)
            {
                if (is_in_fov(cc))
                {
                    txtef(9);
                    if (jp)
                    {
                        txt(u8"「きくぅ」"s,
                            u8"「もふもふ」"s,
                            u8"「くやしい、でも…」"s,
                            u8"「はぁはぁ！」"s,
                            u8"「ウフフフ」"s);
                    }
                    if (en)
                    {
                        txt(u8"\"Yes!\""s,
                            u8"\"Ohhh\""s,
                            u8"*gasp*"s,
                            u8"*rumble*"s,
                            u8"\"come on!\""s);
                    }
                }
            }
        }
        return;
    }
    if (sexhost == 0)
    {
        rowactend(cc);
        return;
    }
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        int c{};
        if (cnt == 0)
        {
            c = cc;
        }
        else
        {
            c = tc;
        }
        cdata[cc].drunk = 0;
        if (cnt == 1)
        {
            if (rnd(3) == 0)
            {
                dmgcon(c, status_ailment_t::insane, 500);
            }
            if (rnd(5) == 0)
            {
                dmgcon(c, status_ailment_t::paralyzed, 500);
            }
            dmgcon(c, status_ailment_t::insane, 300);
            healsan(c, 10);
            skillexp(11, c, 250 + (c >= 57) * 1000);
            skillexp(15, c, 250 + (c >= 57) * 1000);
        }
        if (rnd(15) == 0)
        {
            dmgcon(c, status_ailment_t::sick, 200);
        }
        skillexp(17, c, 250 + (c >= 57) * 1000);
    }
    sexvalue = sdata(17, cc) * (50 + rnd(50)) + 100;
    if (is_in_fov(cc))
    {
        txtef(9);
        if (jp)
        {
            txt(u8"「よかった"s + _yo(3),
                u8"「す、すごい"s + _yo(3),
                u8"「も、もうだめ"s + _da(3),
                u8"「は、激しかった"s + _yo(3),
                u8"「か、完敗"s + _da(3));
        }
        if (en)
        {
            txt(u8"\"You are awesome!"s,
                u8"\"Oh my god...."s,
                u8"\"Okay, okay, you win!"s,
                u8"\"Holy...!"s);
        }
        txtef(20);
        if (tc == 0)
        {
            txt(lang(u8"」"s, u8"\""s));
        }
    }
    if (tc != 0)
    {
        if (cdata[tc].gold >= sexvalue)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"！さあ、小遣いを受け取って"s + _kure(3) + u8"」"s,
                    u8"Here, take this.\""s));
            }
        }
        else
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"！これが"s + _ore(3) + u8"の財布の中身の全て"s + _da()
                        + u8"」"s,
                    u8"Take this money, it's all I have!\""s));
                if (rnd(3) == 0)
                {
                    if (cc != 0)
                    {
                        txt(lang(
                            name(cc) + u8"は激怒した。「なめてんの？」"s,
                            name(cc)
                                + u8" gets furious, "s
                                  u8"\"And you think you can just run away?\""s));
                        cdata[cc].enemy_id = tc;
                        cdata[cc].hate = 20;
                    }
                }
            }
            if (cdata[tc].gold <= 0)
            {
                cdata[tc].gold = 1;
            }
            sexvalue = cdata[tc].gold;
        }
        cdata[tc].gold -= sexvalue;
        if (cc == 0)
        {
            chara_mod_impression(tc, 5);
            flt();
            itemcreate(
                -1, 54, cdata[cc].position.x, cdata[cc].position.y, sexvalue);
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
            modify_karma(0, -1);
        }
        else
        {
            cdata[cc].gold += sexvalue;
        }
    }
    rowactend(cc);
    rowactend(tc);
    return;
}



void continuous_action_others()
{
    if (cc != 0)
    {
        rowactend(cc);
        return;
    }
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 10;
        cdata[cc].continuous_action_item = ci;
        cdata[cc].continuous_action_target = tc;
        if (gdata(91) == 105)
        {
            txt(lang(
                itemname(ci, 1) + u8"に目星をつけた。"s,
                u8"You target "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn =
                2 + clamp(inv[ci].weight / 500, 0, 50);
        }
        if (gdata(91) == 100)
        {
            if (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)
            {
                txt(lang(u8"寝る仕度を始めた。"s, u8"You lie down."s));
                cdata[cc].continuous_action_turn = 5;
            }
            else
            {
                txt(lang(u8"露営の準備を始めた。"s, u8"You start to camp."s));
                cdata[cc].continuous_action_turn = 20;
            }
        }
        if (gdata(91) == 101)
        {
            txt(lang(
                itemname(ci, 1) + u8"の建設を始めた。"s,
                u8"You start to construct "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn = 25;
        }
        if (gdata(91) == 102)
        {
            txt(lang(
                itemname(ci, 1) + u8"のハッチを回し始めた。"s,
                u8"You start to pull the hatch."s));
            cdata[cc].continuous_action_turn = 10;
        }
        if (gdata(91) == 103)
        {
            txt(lang(
                itemname(ci, 1) + u8"を掘り始めた。"s,
                u8"You start to pick "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn = 10
                + clamp(inv[ci].weight
                            / (1 + sdata(10, 0) * 10 + sdata(180, 0) * 40),
                        1,
                        100);
        }
        if (gdata(91) == 104)
        {
            if (gdata_weather == 0 || gdata_weather == 3)
            {
                if (gdata_time_when_textbook_becomes_available > gdata_hour
                        + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12)
                {
                    txt(lang(u8"もう飽きた。"s, u8"You are bored."s));
                    rowactend(cc);
                    return;
                }
            }
            gdata_time_when_textbook_becomes_available = gdata_hour
                + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12 + 48;
            if (inv[ci].id == 563)
            {
                txt(lang(
                    i18n::_(
                        u8"ability", std::to_string(inv[ci].param1), u8"name")
                        + u8"の学習を始めた。"s,
                    u8"You begin to study "s
                        + i18n::_(
                              u8"ability",
                              std::to_string(inv[ci].param1),
                              u8"name")
                        + u8"."s));
            }
            else
            {
                txt(lang(
                    u8"トレーニングを始めた。"s, u8"You start training."s));
            }
            if (gdata_weather != 0 && gdata_weather != 3)
            {
                if (gdata_current_map == 30
                    || (mdata(14) == 1
                        && (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)))
                {
                    txt(lang(
                        u8"外が悪天候なので、じっくりと取り組むことにした。"s,
                        u8"The weather's bad outside, you have plenty of time to waste."s));
                }
            }
            cdata[cc].continuous_action_turn = 50;
        }
        update_screen();
        return;
    }
    tc = cdata[cc].continuous_action_target;
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (gdata(91) == 103)
        {
            if (rnd(5) == 0)
            {
                skillexp(180, 0, 20, 4);
            }
            if (rnd(6) == 0)
            {
                if (rnd(55) > sdata.get(10, cc).original_level + 25)
                {
                    skillexp(10, cc, 50);
                }
            }
            if (rnd(8) == 0)
            {
                if (rnd(55) > sdata.get(11, cc).original_level + 28)
                {
                    skillexp(11, cc, 50);
                }
            }
            if (rnd(10) == 0)
            {
                if (rnd(55) > sdata.get(15, cc).original_level + 30)
                {
                    skillexp(15, cc, 50);
                }
            }
            if (rnd(4) == 0)
            {
                txtef(9);
                if (jp)
                {
                    txt(u8" *ザクッ* "s,
                        u8" *♪* "s,
                        u8" *ズシュ* "s,
                        u8" *ジャリ* "s);
                }
                if (en)
                {
                    txt(u8"*sing*"s,
                        u8"*pull*"s,
                        u8"*thud*"s,
                        u8"*rumble*"s,
                        u8"*gasp*"s);
                }
            }
        }
        if (gdata(91) == 104)
        {
            p = 25;
            if (gdata_weather != 0 && gdata_weather != 3)
            {
                if (gdata_current_map == 30)
                {
                    p = 5;
                }
                if (gdata_current_map != 30 && mdata(14) == 1)
                {
                    if (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)
                    {
                        p = 5;
                        gdata_minute += 30;
                    }
                }
            }
            if (inv[ci].id == 563)
            {
                if (rnd(p) == 0)
                {
                    skillexp(inv[ci].param1, cc, 25);
                }
            }
            else if (rnd(p) == 0)
            {
                skillexp(randattb(), cc, 25);
            }
        }
        if (gdata(91) == 105)
        {
            if (inv[ci].id == 688)
            {
                if (rnd(15) == 0)
                {
                    rowactend(cc);
                    txt(lang(
                        u8"突然ふたが閉まった！"s,
                        u8"Suddenly, the iron maiden falls forward."s));
                    dmghp(cc, 9999, -18);
                    return;
                }
            }
            if (inv[ci].id == 689)
            {
                if (rnd(15) == 0)
                {
                    rowactend(cc);
                    txt(lang(
                        u8"突然ギロチンが落ちてきた！"s,
                        u8"Suddenly, the guillotine is activated."s));
                    dmghp(cc, 9999, -19);
                    return;
                }
            }
            f = 0;
            f2 = 0;
            tg = inv_getowner(ci);
            if (tg != -1)
            {
                if (cdata[tg].original_relationship == -3)
                {
                    f2 = 1;
                }
            }
            i = sdata(300, 0) * 5 + sdata(12, 0) + 25;
            if (gdata_hour >= 19 || gdata_hour < 7)
            {
                i = i * 15 / 10;
            }
            if (inv[ci].quality == 3)
            {
                i = i * 8 / 10;
            }
            if (inv[ci].quality >= 4)
            {
                i = i * 5 / 10;
            }
            make_sound(cdata[0].position.x, cdata[0].position.y, 5, 8);
            for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].sleep != 0)
                {
                    continue;
                }
                if (dist(
                        cdata[cnt].position.x,
                        cdata[cnt].position.y,
                        cdata[0].position.x,
                        cdata[0].position.y)
                    > 5)
                {
                    continue;
                }
                if (f2 == 1)
                {
                    if (cnt != tg)
                    {
                        continue;
                    }
                }
                p = rnd((i + 1))
                    * (80 + (is_in_fov(cnt) == 0) * 50
                       + dist(
                             cdata[cnt].position.x,
                             cdata[cnt].position.y,
                             cdata[0].position.x,
                             cdata[0].position.y)
                           * 20)
                    / 100;
                if (cnt < 57)
                {
                    p = p * 2 / 3;
                }
                if (rnd(sdata(13, cnt) + 1) > p)
                {
                    if (is_in_fov(cnt))
                    {
                        txt(lang(
                            name(cnt) + u8"は窃盗を見咎めた。"s,
                            name(cnt) + u8" notice"s + _s(cnt) + u8" you,"s));
                    }
                    else
                    {
                        txt(lang(
                            name(cnt) + u8"は不振な物音に気づいた。"s,
                            name(cnt) + u8" hear"s + _s(cnt)
                                + u8" loud noise,"s));
                    }
                    if (cdata[cnt].character_role == 14)
                    {
                        txt(lang(
                            u8"「貴様、何をしている！」"s,
                            u8"\"You there, stop!\""s));
                        chara_mod_impression(cnt, -5);
                    }
                    else
                    {
                        txt(lang(
                            u8"「ガード！ガード！」"s,
                            u8"\"Guards! Guards!\""s));
                        chara_mod_impression(cnt, -5);
                    }
                    cdata[cnt].emotion_icon = 520;
                    f = 1;
                }
            }
            if (f)
            {
                txt(lang(
                    u8"盗みを見咎められた！"s, u8"You are found stealing."s));
                modify_karma(0, -5);
                p = inv_getowner(ci);
                if (tg != -1)
                {
                    if (cdata[p].id != 202)
                    {
                        if (cdata[tg].sleep == 0)
                        {
                            cdata[tg].relationship = -2;
                            hostileaction(0, tg);
                            chara_mod_impression(tg, -20);
                        }
                    }
                }
                go_hostile();
            }
            if (tg != -1)
            {
                if (cdata[tg].state != 1)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"対象は死んでいる"s, u8"The target is dead."s));
                        f = 1;
                    }
                }
                if (cdata[tg].character_role == 20)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"それは盗めない。"s, u8"It can't be stolen."s));
                        f = 1;
                    }
                }
                if (dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tg].position.x,
                        cdata[tg].position.y)
                    >= 3)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"対象が見当たらない。"s,
                            u8"You lose the target."s));
                        f = 0;
                    }
                }
            }
            if (inv[ci].number <= 0)
            {
                f = 1;
            }
            if (ibit(5, ci) == 1)
            {
                if (f != 1)
                {
                    txt(lang(u8"それは盗めない。"s, u8"It can't be stolen."s));
                    f = 1;
                }
            }
            if (inv[ci].weight >= sdata(10, 0) * 500)
            {
                if (f != 1)
                {
                    txt(lang(
                        u8"重すぎて手に負えない。"s, u8"It's too heavy."s));
                    f = 1;
                }
            }
            if (itemusingfind(ci, true) != -1)
            {
                if (f != 1)
                {
                    txt(lang(
                        u8"そのアイテムは他の誰かが使用中だ。"s,
                        u8"Someone else is using the item."s));
                    f = 1;
                }
            }
            if (f)
            {
                txt(lang(u8"行動を中断した。"s, u8"You abort stealing."s));
                rowactend(cc);
            }
        }
        return;
    }
    if (gdata(91) == 105)
    {
        tg = inv_getowner(ci);
        if ((tg != -1 && cdata[tg].state != 1) || inv[ci].number <= 0)
        {
            txt(lang(u8"行動を中断した。"s, u8"You abort stealing."s));
            rowactend(cc);
            return;
        }
        in = 1;
        if (inv[ci].id == 54)
        {
            in = inv[ci].number;
        }
        ti = inv_getfreeid(0);
        if (ti == -1)
        {
            txt(lang(
                u8"バックパックには、もうアイテムを入れる余裕がない。"s,
                u8"Your inventory is full."s));
            return;
        }
        ibitmod(12, ci, 0);
        if (inv[ci].body_part != 0)
        {
            tc = inv_getowner(ci);
            if (tc != -1)
            {
                p = inv[ci].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
            }
            inv[ci].body_part = 0;
            chara_refresh(tc);
        }
        item_copy(ci, ti);
        inv[ti].number = in;
        ibitmod(9, ti, 1);
        inv[ti].own_state = 0;
        inv[ci].number -= in;
        if (inv[ci].number <= 0)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        txt(lang(
            itemname(ti) + u8"を盗んだ。"s,
            u8"You successfully steal "s + itemname(ti) + u8"."s));
        if (inv[ci].id == 54)
        {
            snd(11);
            inv[ti].number = 0;
            cdata[0].gold += in;
        }
        else
        {
            item_stack(0, ti, 1);
            snd(14 + rnd(2));
        }
        refresh_burden_state();
        skillexp(300, 0, clamp(inv[ti].weight / 25, 0, 450) + 50);
        if (cdata[0].karma >= -30)
        {
            if (rnd(3) == 0)
            {
                txt(lang(
                    u8"あなたは良心の呵責を感じた。"s,
                    u8"You feel the stings of conscience."s));
                modify_karma(0, -1);
            }
        }
    }
    if (gdata(91) == 100)
    {
        txt(lang(u8"あなたは眠り込んだ。"s, u8"You fall asleep."s));
        label_2151();
    }
    if (gdata(91) == 101)
    {
        snd(58);
        txt(lang(
            itemname(ci, 1) + u8"を作り終えた。"s,
            u8"You finish constructing"s + itemname(ci, 1) + u8"."s));
        in = 1;
        dropval = 1;
        drop_item();
    }
    if (gdata(91) == 102)
    {
        txt(lang(
            itemname(ci, 1) + u8"のハッチを回し終えた。"s,
            u8"You finish pulling the hatch of "s + itemname(ci, 1) + u8"."s));
        chatteleport = 1;
        gdata_previous_map2 = gdata_current_map;
        gdata_previous_dungeon_level = gdata_current_dungeon_level;
        gdata_previous_x = cdata[0].position.x;
        gdata_previous_y = cdata[0].position.y;
        gdata_destination_map = 30;
        gdata_destination_dungeon_level = inv[ci].count;
        levelexitby = 2;
        snd(49);
    }
    if (gdata(91) == 103)
    {
        txt(lang(
            itemname(ci, 1) + u8"を収穫した("s + cnvweight(inv[ci].weight)
                + u8")"s,
            u8"You harvest "s + itemname(ci, 1) + u8". ("s
                + cnvweight(inv[ci].weight) + u8")"s));
        in = inv[ci].number;
        pick_up_item();
    }
    if (gdata(91) == 104)
    {
        if (inv[ci].id == 563)
        {
            txt(lang(
                i18n::_(u8"ability", std::to_string(inv[ci].param1), u8"name")
                    + u8"の学習を終えた。"s,
                u8"You finish studying "s
                    + i18n::_(
                          u8"ability", std::to_string(inv[ci].param1), u8"name")
                    + u8"."s));
        }
        else
        {
            txt(lang(u8"トレーニングを終えた。"s, u8"You finish training."s));
        }
    }
    rowactend(cc);
    return;
}



void label_2149()
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
    return;
}



void label_2150()
{
    gsel(4);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"bg_night.bmp", 1);
    pos(0, 0);
    gzoom(4, 0, 0, 640, 480, windoww, windowh - inf_verh);
    gsel(0);
    return;
}



void label_2151()
{
    int timeslept = 0;
    if (gdata_current_map == 13)
    {
        txt(lang(
            u8"しかし、大事な用を思い出して飛び起きた。"s,
            u8"But you can't sleep right now."s));
        gdata(98) = 0;
        return;
    }
    if (gdata_catches_god_signal)
    {
        txtgod(cdata[0].god_id, 10);
    }
    label_2150();
    musicloop = 1;
    play_music(78);
    msg_halt();
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        gmode(4, -1, -1, cnt * 10);
        label_2149();
        await(200);
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
        gdata_continuous_active_hours = 0;
        cdata[tc].hp = cdata[tc].max_hp;
        cdata[tc].mp = cdata[tc].max_mp;
        cdata[tc].sp = cdata[tc].max_sp;
        healcon(tc, 12, 7 + rnd(7));
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
            cure_anorexia(tc);
            cdata[tc].anorexia_count = 0;
        }
        healsan(tc, 10);
        if (cdata[tc].has_lay_hand())
        {
            cdata[tc].is_lay_hand_available() = true;
        }
    }
    mode = 9;
    timeslept = 7 + rnd(5);
    for (int cnt = 0, cnt_end = (timeslept); cnt < cnt_end; ++cnt)
    {
        ++gdata_hour;
        weather_changes();
        if (mode != 9)
        {
            label_2150();
            mode = 9;
        }
        gdata_continuous_active_hours = 0;
        gdata_minute = 0;
        cc = 0;
        label_2149();
        await(500);
    }
    if (gdata(98) != 0)
    {
        tc = -1;
        for (int cnt = 1; cnt < 16; ++cnt)
        {
            if (cdata[cnt].has_made_gene() == 1)
            {
                if (cdata[cnt].state == 1)
                {
                    tc = cnt;
                    break;
                }
            }
        }
        if (tc != -1)
        {
            s = lang(u8"遺伝子"s, u8"Gene"s);
            buff = lang(""s + name(tc) +
                    u8"とあなたは熱い一夜を供にした。新たな遺伝子が生成された。"s,
                u8"You spent a night with "s + name(tc) +
                    u8". A new gene is created."s);
            listmax = 0;
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"ふぅ"s, u8"Sweet."s);
            ++listmax;
            cdata[tc].has_made_gene() = false;
            show_random_event_window(u8"bg_re14");
            save_gene();
        }
    }
    label_2149();
    gdata(98) = 0;
    mode = 0;
    wake_up();
    cdata[cc].nutrition -= 1500 / (trait(158) + 1);
    txtef(2);
    txt(lang(
        ""s + timeslept + u8"時間眠った。あなたはリフレッシュした。"s,
        u8"You have slept for "s + timeslept
            + u8" hours. You are refreshed."s));
    f = 0;
    if (cdata[0].continuous_action_item == -1)
    {
        f = 1;
    }
    else
    {
        ci = cdata[0].continuous_action_item;
        if (inv[ci].param1 == 0 || inv[ci].number == 0
            || the_item_db[inv[ci].id]->subcategory != 60004)
        {
            f = 1;
        }
    }
    if (f)
    {
        txt(lang(u8"まあまあの目覚めだ。"s, u8"You wake up feeling so so."s));
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
        gdata_sleep_experience = gdata_sleep_experience * inv[ci].param1 / 100;
        grown = 0;
        for (int cnt = 0;; ++cnt)
        {
            if (gdata_sleep_experience >= exp)
            {
                gdata_sleep_experience -= exp;
            }
            else if (cnt != 0)
            {
                break;
            }
            modify_potential(0, 10 + rnd(8), 1);
            ++grown;
            if (cnt > 6)
            {
                if (rnd(5) == 0)
                {
                    gdata_sleep_experience = 0;
                    break;
                }
            }
        }
        txtef(2);
        txt(lang(
            u8"心地よい目覚めだ。潜在能力が伸びた(計"s + grown + u8"%)"s,
            u8"You wake up feeling good. Your potential increases. (Total:"s
                + grown + u8"%)"s));
    }
    msg_halt();
    play_music();
    autosave = 1 * (gdata_current_map != 35);
    if (adata(16, gdata_current_map) == 102)
    {
        update_shop();
    }
}



void do_rest()
{
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 4;
        cdata[cc].continuous_action_turn = 50;
        txt(lang(u8"あなたは横になった。"s, u8"You lie down to rest."s));
        update_screen();
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (cdata[cc].continuous_action_turn % 2 == 0)
        {
            healsp(cc, 1);
        }
        if (cdata[cc].continuous_action_turn % 3 == 0)
        {
            healhp(cc, 1);
            healmp(cc, 1);
        }
        return;
    }
    if (gdata_continuous_active_hours >= 30)
    {
        f = 0;
        if (gdata_continuous_active_hours >= 50)
        {
            f = 1;
        }
        else if (rnd(2) == 0)
        {
            f = 1;
        }
        if (f == 1)
        {
            txt(lang(
                u8"あなたはそのまま眠りにおちた…"s,
                u8"After a short while, you drop off to sleep."s));
            cdata[cc].continuous_action_item = -1;
            label_2151();
            rowactend(cc);
            return;
        }
    }
    txt(lang(u8"あなたは休息を終えた。"s, u8"You finished taking a rest."s));
    rowactend(cc);
    return;
}



void label_2153()
{
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 3;
        cdata[cc].continuous_action_turn = 20;
        if (gdata_weather == 3)
        {
            cdata[cc].continuous_action_turn =
                cdata[cc].continuous_action_turn * 13 / 10;
        }
        if (gdata_weather == 4)
        {
            cdata[cc].continuous_action_turn =
                cdata[cc].continuous_action_turn * 16 / 10;
        }
        if (gdata_weather == 2
            || chipm(0, map(cdata[cc].position.x, cdata[cc].position.y, 0))
                == 4)
        {
            cdata[cc].continuous_action_turn =
                cdata[cc].continuous_action_turn * 22 / 10;
        }
        if (gdata_weather == 1)
        {
            cdata[cc].continuous_action_turn =
                cdata[cc].continuous_action_turn * 5 / 10;
        }
        cdata[cc].continuous_action_turn = cdata[cc].continuous_action_turn
            * 100 / (100 + gdata_seven_league_boot_effect + sdata(182, 0));
        return;
    }
    if (cdata[0].nutrition <= 5000)
    {
        f = 0;
        for (const auto& cnt : items(cc))
        {
            if (inv[cnt].number == 0)
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
            if (is_in_fov(cc))
            {
                txt(lang(
                    npcn(cc) + itemname(ci, 1) + u8"を食べ終えた。"s,
                    name(cc) + u8" "s + have(cc) + u8" finished eating "s
                        + itemname(ci, 1) + u8"."s));
            }
            continuous_action_eating_finish();
        }
    }
    if (gdata_weather == 2
        || chipm(0, map(cdata[cc].position.x, cdata[cc].position.y, 0)) == 4)
    {
        if (gdata_protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata[0].is_floating() == 0 || cdata[0].gravity > 0)
                {
                    txtef(9);
                    if (jp)
                    {
                        txt(u8" *ずぶっ* "s,
                            u8" *ザシュ* "s,
                            u8" *ズボ* "s,
                            u8" *ズサッ* "s);
                    }
                    if (en)
                    {
                        txt(u8" *kisssh*"s,
                            u8"*thudd*"s,
                            u8"*siz*"s,
                            u8"*clump*"s,
                            u8"*skritch*"s);
                    }
                    cdata[cc].continuous_action_turn += 10;
                }
            }
            if (rnd(1000) == 0)
            {
                txtef(8);
                if (jp)
                {
                    txt(u8"積雪のせいで旅程が遅れている。"s,
                        u8"雪道を進むのは大変な苦労だ。"s,
                        u8"深い雪に脚をとられている。"s);
                }
                if (en)
                {
                    txt(u8"Snow delays your travel."s,
                        u8"You are caught in a snowdrift."s,
                        u8"It's hard to walk on a snowy road."s);
                }
                cdata[cc].continuous_action_turn += 50;
            }
        }
        if (cdata[0].nutrition <= 2000)
        {
            if (cdata[0].has_anorexia() == 0)
            {
                snd(18);
                txt(lang(
                    u8"空腹のあまり、あなたは積もっている雪を腹にかきこんだ。"s,
                    u8"You are too hungry. You chow down snow."s));
                cdata[cc].nutrition += 5000;
                show_eating_message();
                dmgcon(0, status_ailment_t::dimmed, 1000);
            }
        }
    }
    if (gdata_weather == 4)
    {
        if (gdata_protects_from_bad_weather == 0)
        {
            if (rnd(100) == 0)
            {
                if (cdata[0].is_floating() == 0 || cdata[0].gravity > 0)
                {
                    txtef(9);
                    if (jp)
                    {
                        txt(u8" *びしゃ* "s,
                            u8" *ザブッ* "s,
                            u8" *パシャッ* "s,
                            u8" *ざぶ* "s);
                    }
                    if (en)
                    {
                        txt(u8"*drip*"s,
                            u8"*sip*"s,
                            u8"*drizzle*"s,
                            u8"*splash*"s,
                            u8"*kissh*"s);
                    }
                    cdata[cc].continuous_action_turn += 5;
                }
            }
            if (cdata[0].confused == 0)
            {
                if (rnd(500) == 0)
                {
                    txtef(8);
                    if (jp)
                    {
                        txt(u8"雨が激しすぎてどこを歩いているかもわからない！"s,
                            u8"あまりにも視界が悪すぎる。"s,
                            u8"豪雨のせいで前が全く見えない。"s);
                    }
                    if (en)
                    {
                        txt(u8"It's raining heavily. You lose your way."s,
                            u8"You can't see a thing!"s);
                    }
                    cdata[0].confused = 10;
                }
            }
            else if (rnd(5) == 0)
            {
                cdata[0].confused = 10;
            }
        }
        cdata[0].blind = 3;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        ++gdata_minute;
        return;
    }
    traveldone = 1;
    gdata_distance_between_town += 4;
    rowactend(cc);
    return;
}



void select_random_fish()
{
    if (rowactre != 0)
    {
        return;
    }
    ci = cdata[0].continuous_action_item;
    int dbmax = 0;
    int dbsum = 0;
    for (const auto fish : the_fish_db)
    {
        if (fish.no_generate)
        {
            continue;
        }
        i = clamp(inv[ci].param4 + (rnd(5) == 0) - (rnd(5) == 0), 0, 5);
        if (fish.rank != i)
        {
            continue;
        }
        dblist(0, dbmax) = fish.id;
        dblist(1, dbmax) = fish.rarity + dbsum;
        dbsum += fish.rarity;
        ++dbmax;
    }
    fish = 1;
    if (dbsum != 0)
    {
        const auto dbtmp = rnd(dbsum);
        for (int cnt = 0, cnt_end = (dbmax); cnt < cnt_end; ++cnt)
        {
            if (dblist(1, cnt) > dbtmp)
            {
                fish = dblist(0, cnt);
                break;
            }
        }
    }
    return;
}



void get_fish()
{
    flt();
    itemcreate(0, the_fish_db[fish]->item_id, -1, -1, 0);
    inv[ci].subname = fish;
    inv[ci].value = the_fish_db[fish]->value;
    inv[ci].weight = the_fish_db[fish]->weight;
    txt(lang(
        itemname(ci, 1) + u8"を釣り上げた！"s,
        u8"You get "s + itemname(ci, 1) + u8"!"s));
    item_stack(0, ci, 1);
    return;
}



void spot_fishing()
{
    int fishstat = 0;
    if (cdata[cc].continuous_action_id == 0)
    {
        txt(lang(u8"釣りを始めた。"s, u8"You start fishing."s));
        snd(87);
        if (rowactre == 0)
        {
            cdata[cc].continuous_action_item = ci;
        }
        cdata[cc].continuous_action_id = 7;
        cdata[cc].continuous_action_turn = 100;
        racount = 0;
        fishstat = 0;
        gsel(9);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"fishing.bmp");
        gsel(0);
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (rnd(5) == 0)
        {
            fishstat = 1;
            select_random_fish();
        }
        if (fishstat == 1)
        {
            if (rnd(5) == 0)
            {
                for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
                {
                    fishanime(0) = 1;
                    fishanime(1) = 3 + rnd(3);
                    addefmap(fishx, fishy, 4, 2);
                    ++scrturn;
                    update_screen();
                    redraw();
                    await(config::instance().wait1 * 2);
                }
                if (rnd(3) == 0)
                {
                    fishstat = 2;
                }
                if (rnd(6) == 0)
                {
                    fishstat = 0;
                }
                fishanime = 0;
            }
        }
        if (fishstat == 2)
        {
            fishanime = 2;
            snd(46);
            cdata[0].emotion_icon = 220;
            for (int cnt = 0, cnt_end = (8 + rnd(10)); cnt < cnt_end; ++cnt)
            {
                ++scrturn;
                update_screen();
                redraw();
                await(config::instance().wait1 * 2);
            }
            if (rnd(10))
            {
                fishstat = 3;
            }
            else
            {
                fishstat = 0;
            }
            fishanime = 0;
        }
        if (fishstat == 3)
        {
            fishanime = 3;
            for (int cnt = 0, cnt_end = (28 + rnd(15)); cnt < cnt_end; ++cnt)
            {
                if (cnt % 7 == 0)
                {
                    snd(89);
                }
                fishanime(1) = cnt;
                ++scrturn;
                update_screen();
                addefmap(fishx, fishy, 5, 2);
                redraw();
                await(config::instance().wait1 * 2);
            }
            if (the_fish_db[fish]->difficulty >= rnd(sdata(185, 0) + 1))
            {
                fishstat = 0;
            }
            else
            {
                fishstat = 4;
            }
            fishanime = 0;
        }
        if (fishstat == 4)
        {
            fishanime = 4;
            snd(88);
            for (int cnt = 0; cnt < 21; ++cnt)
            {
                fishanime(1) = cnt;
                if (cnt == 1)
                {
                    addefmap(fishx, fishy, 1, 3);
                }
                ++scrturn;
                update_screen();
                redraw();
                await(config::instance().wait1 * 2);
            }
            snd(14 + rnd(2));
            fishanime = 0;
            rowactend(cc);
            get_fish();
            gain_fishing_experience(0);
            cdata[0].emotion_icon = 306;
        }
        if (rnd(10) == 0)
        {
            dmgsp(cc, 1);
        }
        return;
    }
    txt(lang(u8"何も釣れなかった…"s, u8"A waste of a time..."s));
    rowactend(cc);
    return;
}



void spot_material()
{
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 8;
        cdata[cc].continuous_action_turn = 40;
        txt(lang(u8"採取を始めた。"s, u8"You start to search the spot."s));
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    rowactend(cc);
    return;
}



void spot_digging()
{
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 9;
        cdata[cc].continuous_action_turn = 20;
        if (rowactre == 0)
        {
            txt(lang(
                u8"地面を掘り始めた。"s, u8"You start to dig the ground."s));
        }
        else
        {
            txt(lang(u8"探索を始めた。"s, u8"You start to dig the spot."s));
        }
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (cdata[cc].turn % 5 == 0)
        {
            txtef(4);
            txt(lang(u8" *ざくっ* "s, u8"*clink*"s),
                lang(u8" *カキン* "s, u8"*smash*"s),
                lang(u8" *ごつっ* "s, u8"*thud*"s),
                lang(u8" *じゃり* "s, u8"*sing*"s),
                lang(u8" *♪* "s, u8"*sigh*"s));
        }
        return;
    }
    txt(lang(u8"地面を掘り終えた。"s, u8"You finish digging."s));
    if (mdata(6) == 1)
    {
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].id == 621)
            {
                if (inv[cnt].param1 != 0)
                {
                    if (inv[cnt].param1 == cdata[0].position.x)
                    {
                        if (inv[cnt].param2 == cdata[0].position.y)
                        {
                            snd(23);
                            txtef(5);
                            txt(lang(
                                u8" *ガチッ* …何かがある！"s,
                                u8"*click* ...something is there!"s));
                            msg_halt();
                            snd(24);
                            flt();
                            itemcreate(
                                -1,
                                622,
                                cdata[0].position.x,
                                cdata[0].position.y,
                                2 + rnd(3));
                            flt();
                            itemcreate(
                                -1,
                                55,
                                cdata[0].position.x,
                                cdata[0].position.y,
                                1 + rnd(3));
                            flt();
                            itemcreate(
                                -1,
                                54,
                                cdata[0].position.x,
                                cdata[0].position.y,
                                rnd(10000) + 2000);
                            for (int cnt = 0, cnt_end = (4); cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(calcobjlv(cdata[0].level + 10),
                                    calcfixlv(3));
                                if (cnt == 0)
                                {
                                    fixlv = 5;
                                }
                                flttypemajor =
                                    fsetchest(rnd(length(fsetchest)));
                                itemcreate(
                                    -1,
                                    0,
                                    cdata[0].position.x,
                                    cdata[0].position.y,
                                    0);
                            }
                            txt(lang(
                                u8"何かが足元に転がってきた。"s,
                                u8"Something is put on the ground."s));
                            autosave = 1 * (gdata_current_map != 35);
                            --inv[cnt].number;
                            break;
                        }
                    }
                }
            }
        }
    }
    spillfrag(refx, refy, 1);
    rowactend(cc);
    return;
}



void spot_mining_or_wall()
{
    static int countdig{};

    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 5;
        cdata[cc].continuous_action_turn = 40;
        if (rowactre == 0)
        {
            txt(lang(u8"壁を掘りはじめた。"s, u8"You start to dig the wall."s));
        }
        else
        {
            txt(lang(
                u8"鉱石を掘り始めた。"s,
                u8"You start to dig the mining spot."s));
        }
        if (chipm(0, map(refx, refy, 0)) == 6)
        {
            txt(lang(
                u8"この壁はとても固そうだ！"s,
                u8"These walls look pretty hard!"s));
        }
        countdig = 0;
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (rnd(5) == 0)
        {
            dmgsp(cc, 1);
        }
        ++countdig;
        f = 0;
        if (chipm(0, map(refx, refy, 0)) == 6)
        {
            if (rnd(12000) < sdata(10, cc) + sdata(163, cc) * 10)
            {
                f = 1;
            }
            p = 30 - sdata(163, cc) / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        else
        {
            if (rnd(1500) < sdata(10, cc) + sdata(163, cc) * 10)
            {
                f = 1;
            }
            p = 20 - sdata(163, cc) / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        if (f == 1 || (gdata_tutorial_flag == 2 && gdata_current_map == 7))
        {
            rtval = 0;
            if (rnd(5) == 0)
            {
                rtval = 54;
            }
            if (rnd(8) == 0)
            {
                rtval = -1;
            }
            if (map(refx, refy, 6) != 0)
            {
                cell_featread(refx, refy);
                if (feat(1) == 22)
                {
                    discover_hidden_path();
                }
            }
            map(refx, refy, 0) = tile_tunnel;
            spillfrag(refx, refy, 2);
            FIXME_dig_animation_x = refx;
            FIXME_dig_animation_y = refy;
            snd(45);
            aniref = 5;
            play_animation(14);
            txt(lang(
                u8"壁を掘り終えた。"s, u8"You finished digging the wall."s));
            if (gdata_tutorial_flag == 2 && gdata_current_map == 7)
            {
                flt();
                itemcreate(-1, 208, digx, digy, 0);
                inv[ci].curse_state = curse_state_t::cursed;
                txt(lang(
                    u8"何かを見つけた。"s,
                    u8"You found something out of crushed heaps of rock."s));
                gdata_tutorial_flag = 3;
            }
            else if (rtval != 0 && gdata_current_map != 30)
            {
                if (rtval > 0)
                {
                    flt();
                    itemcreate(-1, rtval, digx, digy, 0);
                }
                else if (rtval == -1)
                {
                    flt(calcobjlv(gdata_current_dungeon_level), calcfixlv(3));
                    flttypemajor = 77000;
                    itemcreate(-1, 0, digx, digy, 0);
                }
                txt(lang(
                    u8"何かを見つけた。"s,
                    u8"You found something out of crushed heaps of rock."s));
            }
            gain_digging_experience();
            rowactend(cc);
        }
        else if (cdata[cc].turn % 5 == 0)
        {
            txtef(4);
            txt(lang(u8" *ざくっ* "s, u8"*clink*"s),
                lang(u8" *カキン* "s, u8"*smash*"s),
                lang(u8" *ごつっ* "s, u8"*thud*"s),
                lang(u8" *じゃり* "s, u8"*sing*"s),
                lang(u8" *♪* "s, u8"*sigh*"s));
        }
        return;
    }
    txt(lang(
        u8"背中が痛い…掘るのを諦めた。"s,
        u8"Your back hurts...You give up digging."s));
    rowactend(cc);
    return;
}



int decode_book()
{
    int cibkread = 0;
    if (cdata[cc].continuous_action_id == 0)
    {
        if (inv[ci].id == 687)
        {
            if (inv[ci].param2 != 0)
            {
                txt(lang(
                    u8"それは既に解読済みだ。"s,
                    u8"You already have decoded the book."s));
                return 0;
            }
        }
        if (cdata[cc].blind != 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"は何も見えない。"s,
                    name(cc) + u8" can see nothing."s));
            }
            return 0;
        }
        cdata[cc].continuous_action_id = 2;
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
            p = the_ability_db[efid]->sdataref4;
        }
        cdata[cc].continuous_action_turn = p / (2 + sdata(150, 0)) + 1;
        cdata[cc].continuous_action_item = ci;
        if (is_in_fov(cc))
        {
            txt(lang(
                npcn(cc) + itemname(ci, 1) + u8"を読み始めた。"s,
                name(cc) + u8" start"s + _s(cc) + u8" to read "s
                    + itemname(ci, 1) + u8"."s));
        }
        item_separate(ci);
        return 0;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        ci = cdata[cc].continuous_action_item;
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
            r2 = the_ability_db[efid]->sdataref4;
            r3 = efid;
        }
        if (inv[ci].curse_state == curse_state_t::blessed)
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
            rowactend(cc);
            --inv[ci].count;
            if (inv[ci].count < 0)
            {
                inv[ci].count = 0;
            }
            if (inv[ci].count == 0)
            {
                --inv[ci].number;
                if (ci >= 5080)
                {
                    cell_refresh(inv[ci].position.x, inv[ci].position.y);
                }
                else
                {
                    refresh_burden_state();
                }
                if (is_in_fov(cc))
                {
                    txt(lang(
                        itemname(ci, 1) + u8"は塵となって崩れ落ちた。"s,
                        itemname(ci, 1) + u8" falls apart."s));
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cc))
    {
        txt(lang(
            npcn(cc) + itemname(ci, 1) + u8"を読み終えた。"s,
            name(cc) + u8" "s + have(cc) + u8" finished reading the book."s));
    }
    if (inv[ci].id == 783)
    {
        if (inv[ci].param1 == 0)
        {
            rowactend(cc);
            return 1;
        }
        txt(lang(
            itemname(ci, 1) + u8"を覚えた！"s, u8"You learned the recipe!"s));
        ++recipememory(inv[ci].subname);
        item_identify(inv[ci], identification_state_t::partly_identified);
        removeitem(ci, 1);
        if (is_in_fov(cc))
        {
            txt(lang(
                itemname(ci, 1) + u8"は塵となって崩れ落ちた。"s,
                itemname(ci, 1) + u8" falls apart."s));
        }
        rowactend(cc);
        return 1;
    }
    if (inv[ci].id == 687)
    {
        item_identify(inv[ci], identification_state_t::completely_identified);
        txt(lang(
            itemname(ci, 1) + u8"を解読した！"s,
            u8"You finished decoding "s + itemname(ci, 1) + u8"!"s));
        inv[ci].param2 = 1;
        inv[ci].count = 1;
        ibitmod(4, ci, 0);
        item_stack(0, ci, 1);
    }
    else
    {
        skillgain(
            cc,
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
    item_identify(inv[ci], identification_state_t::partly_identified);
    if (inv[ci].id != 687)
    {
        --inv[ci].count;
        if (inv[ci].count < 0)
        {
            inv[ci].count = 0;
        }
        if (inv[ci].count == 0)
        {
            removeitem(ci, 1);
            if (is_in_fov(cc))
            {
                txt(lang(
                    itemname(ci, 1) + u8"は塵となって崩れ落ちた。"s,
                    itemname(ci, 1) + u8" falls apart."s));
            }
        }
    }
    rowactend(cc);
    return 1;
}



int read_normal_book()
{
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は何も見えない。"s,
                name(cc) + u8" can see nothing."s));
        }
        return 0;
    }
    if (inv[ci].id == 742)
    {
        snd(59);
        txt(lang(
            u8"すくつの探索を許可する、という内容の文面が形式的に書いてある。"s,
            u8"According to the card, you are permitted to explore the void now."s));
        return 1;
    }
    if (inv[ci].id == 563)
    {
        int stat = label_2083();
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
        snd(59);
        txt(lang(
            u8"レイチェルという作家による、心あたたまる童話集だ。"s,
            u8"It's a lovely fairy tale written by Rachel."s));
        return 1;
    }
    tc = cc;
    item_identify(inv[ci], identification_state_t::partly_identified);
    label_2022();
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
                if (is_in_fov(prm_1077))
                {
                    txt(lang(
                        name(prm_1077) + u8"は巻き込みを免れた。"s,
                        u8"The spell passes through "s + name(prm_1077)
                            + u8"."s));
                }
                skillexp(188, prm_1076, 8, 4);
                return 1;
            }
            skillexp(188, prm_1076, 30, 2);
        }
    }
    return 0;
}



int label_2167()
{
    int spellbk = 0;
    spellbk = efid;
    ccbk = cc;
    int stat = label_2168();
    if (stat == 1)
    {
        cc = ccbk;
        r2 = spellbk;
        gain_casting_experience(cc);
        return 1;
    }
    return 0;
}



int label_2168()
{
    int mp = 0;
    efsource = 3;
    efstatus = curse_state_t::none;
    efp = calcspellpower(efid, cc);
    if (cc == 0)
    {
        if (calcspellcostmp(efid, cc) > cdata[cc].mp)
        {
            txt(lang(
                u8"マナが足りないが、それでも詠唱を試みる？"s,
                u8"You are going to over-cast the spell. Are you sure?"s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval != 0)
            {
                update_screen();
                efsource = 0;
                return 0;
            }
        }
        screenupdate = -1;
        update_screen();
    }
    int stat = label_2175();
    if (stat == 0)
    {
        efsource = 0;
        return 0;
    }
    if (cc != 0)
    {
        if (the_ability_db[efid]->sdataref1 == 7)
        {
            if (cdata[cc].relationship == 10 || gdata_current_map == 40)
            {
                efsource = 0;
                return 0;
            }
            if (gdata_play_turns % 10 > 4)
            {
                efsource = 0;
                return 0;
            }
        }
    }
    if (cc == 0 || (cc != 0 && npccostmp == 1))
    {
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
            if (cdata[0].god_id == core_god::ehekatl)
            {
                mp = rnd(mp * 140 / 100 + 1) + 1;
            }
        }
        dmgmp(cc, mp);
        if (cdata[cc].state != 1)
        {
            efsource = 0;
            return 1;
        }
    }
    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は混乱しながらも魔法の詠唱を試みた。"s,
                name(cc) + u8" try"s + _s(cc)
                    + u8" to cast a spell in confusion."s));
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
    else if (is_in_fov(cc))
    {
        if (cc == 0)
        {
            txt(lang(
                name(cc) + u8"は"s
                    + i18n::_(u8"ability", std::to_string(efid), u8"name")
                    + u8"の"s
                    + i18n::_(
                          u8"ui",
                          u8"cast_style",
                          u8"_"s + cdata[cc].special_attack_type),
                name(cc) + u8" cast "s
                    + i18n::_(u8"ability", std::to_string(efid), u8"name")
                    + u8"."s));
        }
        else
        {
            txt(lang(
                name(cc) + u8"は"s
                    + i18n::_(
                          u8"ui",
                          u8"cast_style",
                          u8"_"s + cdata[cc].special_attack_type),
                name(cc) + ""s
                    + i18n::_(
                          u8"ui",
                          u8"cast_style",
                          u8"_"s + cdata[cc].special_attack_type)));
        }
    }
    if (buff_find(cc, 2) != -1)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"沈黙の霧が詠唱を阻止した。"s,
                u8"The mist of silence interrupts a spell."s));
        }
        efsource = 0;
        return 1;
    }
    if (rnd(100) >= calcspellfail(efid, cc))
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は詠唱に失敗した。"s,
                name(cc) + u8" fail"s + _s(cc) + u8" to cast a spell."s));
            play_animation(8);
        }
        efsource = 0;
        return 1;
    }
    if (noeffect == 1)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
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
        && the_ability_db[efid]->sdataref1 == 2)
    {
        rapidmagic = 1 + (rnd(3) != 0) + (rnd(2) != 0);
    }
    if (rapidmagic)
    {
        for (int cnt = 0, cnt_end = (rapidmagic); cnt < cnt_end; ++cnt)
        {
            magic();
            if (cdata[tc].state != 1)
            {
                int stat = label_2072();
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
        if (is_in_fov(tc))
        {
            snd(17);
            txt(lang(
                npcn(tc) + itemname(ci, 1) + u8"を飲み干した。"s,
                name(tc) + u8" drink"s + _s(tc) + u8" "s + itemname(ci, 1)
                    + u8"."s));
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
                item_identify(
                    inv[ci], identification_state_t::partly_identified);
            }
        }
        --inv[ci].number;
        if (ci >= 5080)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        else if (tc == 0)
        {
            refresh_burden_state();
        }
    }
    cdata[tc].nutrition += 150;
    if (tc < 16)
    {
        if (cdata[tc].nutrition > 12000)
        {
            if (rnd(5) == 0)
            {
                chara_vomit(tc);
            }
        }
    }
    return 1;
}



int drink_well()
{
    if (inv[ci].param1 < -5 || inv[ci].param3 >= 20
        || (inv[ci].id == 602 && gdata_holy_well_count <= 0))
    {
        const auto valn = itemname(ci);
        txt(lang(valn + u8"は涸れている。"s, valn + u8" is dry."s));
        return 1;
    }
    snd(17);
    const auto valn = itemname(ci);
    txt(lang(
        name(cc) + u8"は"s + valn + u8"の水をすくって飲んだ。"s,
        name(cc) + u8" draw"s + _s(cc) + u8" water from "s + valn + u8"."s));
    tc = cc;
    cibk = ci;
    p = rnd(100);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cc != 0)
        {
            if (rnd(15) == 0)
            {
                txt(lang(
                    name(cc) + u8"は井戸に落ちた！ "s,
                    name(cc) + u8" falls in the well!"s));
                txtef(9);
                txt(name(cc)
                    + lang(
                          u8"「手を伸ばせー」"s,
                          (u8" yells, "s + u8"\"G-Give me your hands!\""s)));
                if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                {
                    txt(lang(
                        u8"しかしすぐに浮いてきた… "s,
                        u8"Soon "s + he(cc) + u8" floats up to the surface."s));
                }
                else
                {
                    dmghp(cc, 9999, -1);
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
            txt(lang(
                name(cc) + u8"は水の中に金貨を見つけた。"s,
                name(cc) + u8" find"s + _s(cc)
                    + u8" some gold pieces in water."s));
            break;
        }
        if (p > 45)
        {
            p = rnd(8) + 10;
            if (rnd(5) > 2)
            {
                skillmod(p, cc, 1000);
            }
            else
            {
                skillmod(p, cc, -1000);
            }
            break;
        }
        if (p > 40)
        {
            if (cdata[cc].level < 5)
            {
                break;
            }
            if (is_in_fov(cc))
            {
                txt(lang(
                    ""s + name(cc) + u8"は何かいけないものを飲み込んだ。"s,
                    name(cc) + u8" swallow"s + _s(cc) + u8" something bad."s));
            }
            tc = cc;
            get_pregnant();
            break;
        }
        if (p > 35)
        {
            txt(lang(
                u8"井戸から何かが出てきた！"s,
                u8"Something comes out from the well!"s));
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata[cc].level * 3 / 2 + 3), calcfixlv(2));
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
            if (rnd(gdata_wish_count + 1))
            {
                txtef(5);
                txt(lang(
                    u8"ものすごい幸運が訪れた…ような気がしたが気のせいだった。"s,
                    u8"You feel as a stroke of good fortune passed by."s));
                break;
            }
            ++gdata_wish_count;
            efid = 441;
            magic();
            break;
        }
        if (cc == 0)
        {
            txt(lang(
                u8"この水は清涼だ。"s, u8"Phew, fresh water tastes good."s));
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
        --gdata_holy_well_count;
    }
    else
    {
        inv[ci].param1 -= rnd(3);
        inv[ci].param3 += rnd(3);
        if (inv[ci].param3 >= 20)
        {
            txt(lang(
                itemname(ci) + u8"は完全に干上がった。"s,
                itemname(ci) + u8" has completely dried up."s));
            return 1;
        }
    }
    if (inv[ci].param1 < -5)
    {
        txt(lang(
            itemname(ci) + u8"は干上がった。"s,
            itemname(ci) + u8" has dried up."s));
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
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は何も見えない。"s,
                name(cc) + u8" can see nothing."s));
        }
        efsource = 0;
        return 0;
    }
    if (cdata[cc].dimmed != 0 || cdata[cc].confused != 0)
    {
        if (rnd(4) != 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"はふらふらした。"s,
                    name(cc) + u8" stagger"s + _s(cc) + u8"."s));
            }
            efsource = 0;
            return 0;
        }
    }
    if (is_in_fov(cc))
    {
        txt(lang(
            npcn(cc) + itemname(ci, 1) + u8"を読んだ。"s,
            name(cc) + u8" read"s + _s(cc) + u8" "s + itemname(ci, 1)
                + u8"."s));
    }
    if (inv[ci].id != 621)
    {
        --inv[ci].number;
        if (ci >= 5080)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        else
        {
            refresh_burden_state();
        }
        skillexp(150, cc, 25, 2);
    }
    magic();
    if (cc == 0)
    {
        if (obvious == 1)
        {
            item_identify(inv[ci], identification_state_t::partly_identified);
        }
    }
    return 1;
}



int label_2172()
{
    if (inv[ci].count <= 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                itemname(ci, 1) + u8"を振った。"s,
                u8"You zap "s + itemname(ci, 1) + u8"."s));
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        }
        return 0;
    }
    efstatus = inv[ci].curse_state;
    if (efstatus == curse_state_t::blessed)
    {
        efstatus = curse_state_t::none;
    }
    efsource = 1;
    int stat = label_2175();
    if (stat == 0)
    {
        efsource = 0;
        return 0;
    }
    if (efid >= 400 && efid < 467)
    {
        if ((stat == 0 && the_ability_db[efid]->sdataref3 / 1000 * 1000 == 2000)
            || noeffect == 1)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    itemname(ci, 1) + u8"を振った。"s,
                    u8"You zap "s + itemname(ci, 1) + u8"."s));
                txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            }
            goto label_2173_internal;
        }
    }
    if (is_in_fov(cc))
    {
        txt(lang(
            itemname(ci, 1) + u8"を振った。"s,
            u8"You zap "s + itemname(ci, 1) + u8"."s));
    }
    efp = efp
        * (100 + sdata(174, cc) * 10 + sdata(16, cc) / 2 + sdata(13, cc) / 2)
        / 100;
    if (efid >= 400 && efid < 467)
    {
        f = 0;
        int skill = sdata(174, cc) * 20 + 100;
        if (inv[ci].curse_state == curse_state_t::blessed)
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
        if (rnd((the_ability_db[efid]->sdataref4 + 1)) / 2 <= skill)
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
                item_identify(
                    inv[ci], identification_state_t::partly_identified);
            }
        }
        gain_magic_device_experience(cc);
    }
    else if (is_in_fov(cc))
    {
        txt(lang(
            name(cc) + u8"は杖をうまく使えなかった。"s,
            name(cc) + u8" fail to use the power of the rod."s));
    }
label_2173_internal:
    efsource = 0;
    if (inv[ci].number == 0)
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



int label_2174()
{
    if (efid == 646)
    {
        if (cdata[tc].is_sentenced_daeth() == 1)
        {
            if (cdata[cc].relationship == -3)
            {
                for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
                {
                    if (cdata[cnt].state == 1)
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
        int stat = label_2175();
        if (stat == 0)
        {
            return 0;
        }
    }
    if (the_ability_db[efid]->sdataref3 / 1000 * 1000 != 3000
        && the_ability_db[efid]->sdataref3 / 1000 * 1000 != 10000)
    {
        if (cdata[cc].confused != 0 || cdata[cc].blind != 0)
        {
            if (rnd(5) == 0)
            {
                if (is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"は頭を振った。"s,
                        name(cc) + u8" shake"s + _s(cc) + u8" "s + his(cc)
                            + u8" head."s));
                }
                return 1;
            }
        }
    }
    if (efid >= 600)
    {
        if (cc == 0)
        {
            if (cdata[0].sp < 50)
            {
                if (cdata[0].sp < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, the_ability_db[efid]->cost / 2 + 1);
                    return 1;
                }
            }
            dmgsp(
                0,
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
            skillexp(the_ability_db[efid]->related_basic_attribute, cc, 25);
        }
    }
    efp = calcspellpower(efid, cc);
    if (noeffect == 1)
    {
        if (efid != 300)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
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



int label_2175()
{
    noeffect = 0;
    if (efid > 661)
    {
        tc = cc;
        return 1;
    }
    tg = the_ability_db[efid]->sdataref3 / 1000 * 1000;
    if (efsource == 1)
    {
        if (tg == 3000)
        {
            tg = 8000;
        }
    }
    if (the_ability_db[efid]->sdataref1 == 7)
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
            txt(lang(u8"どの方向？"s, u8"Which direction?"s));
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                return 0;
            }
            if (map(tlocx, tlocy, 1) == 0)
            {
                noeffect = 1;
                obvious = 0;
                return 1;
            }
            tc = map(tlocx, tlocy, 1) - 1;
        }
        else
        {
            if (dist(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y)
                > the_ability_db[efid]->sdataref3 % 1000 + 1)
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
                        txt(lang(
                            u8"その場所は見えない。"s,
                            u8"You can't see the location."s));
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
                        txt(lang(
                            u8"その場所は見えない。"s,
                            u8"You can't see the location."s));
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
            if (the_ability_db[efid]->sdataref1 == 3)
            {
                if (dist(
                        cdata[tc].position.x,
                        cdata[tc].position.y,
                        cdata[cc].position.x,
                        cdata[cc].position.y)
                    > the_ability_db[efid]->sdataref3 % 1000 + 1)
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
            int stat = label_2072();
            if (stat == 0)
            {
                obvious = 0;
                return 0;
            }
            tc = cdata[0].enemy_id;
            if (cdata[tc].relationship >= 0)
            {
                int stat = label_2073();
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
            > the_ability_db[efid]->sdataref3 % 1000 + 1)
        {
            if (cc == 0)
            {
                ++msgdup;
                txt(lang(u8"射程距離外だ。"s, u8"It's out of range."s));
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
                txt(lang(
                    u8"どの方向に唱える？ "s,
                    u8"Which direction do you want to cast the spell? "s));
            }
            else
            {
                txt(lang(
                    u8"どの方向に振る？ "s,
                    u8"Which direction do you want to zap the wand? "s));
            }
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
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
    if (gdata_mount != 0)
    {
        if (tc == gdata_mount || tc == 0)
        {
            subloop = 2;
            if (tc == gdata_mount)
            {
                tc(1) = 0;
            }
            else
            {
                tc(1) = gdata_mount;
            }
        }
    }
    for (int cnt = 0, cnt_end = (subloop); cnt < cnt_end; ++cnt)
    {
        healhp(tc(cnt), roll(dice1, dice2, bonus));
        healcon(tc(cnt), 6);
        healcon(tc(cnt), 1, 50);
        healcon(tc(cnt), 5, 50);
        healcon(tc(cnt), 7, 30);
        healcon(tc(cnt), 9, 20);
        healsan(tc(cnt), 1);
    }
    return;
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
    gdata_continuous_active_hours = 0;
    cdata[tc].hp = cdata[tc].max_hp;
    cdata[tc].mp = cdata[tc].max_mp;
    cdata[tc].sp = cdata[tc].max_sp;
    return;
}



int pick_up_item()
{
    int sellgold = 0;
    if (cc != -1)
    {
        if (inv[ci].id == 54 || inv[ci].id == 55)
        {
            snd(11);
            ti = ci;
            in = inv[ci].number;
            inv[ci].number = 0;
            msgkeep = 1;
            txt(lang(
                name(cc) + u8"は"s + itemname(ti, in) + u8"を拾った。"s,
                name(cc) + u8" pick"s + _s(cc) + u8" up "s + itemname(ti, in)
                    + u8"."s));
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            if (inv[ci].id == 54)
            {
                cdata[cc].gold += in;
            }
            else
            {
                cdata[cc].platinum_coin += in;
            }
            return 1;
        }
    }
    if (cc == 0)
    {
        if (gdata_mount != 0)
        {
            if (cdata[gdata_mount].continuous_action_id != 0)
            {
                if (cdata[gdata_mount].continuous_action_item == ci)
                {
                    txt(lang(
                        u8"それは"s + name(gdata_mount) + u8"が使用中だ。"s,
                        name(gdata_mount) + u8" "s + is(gdata_mount)
                            + u8" using it."s));
                    return 1;
                }
            }
        }
        if (the_item_db[inv[ci].id]->category == 57000)
        {
            if (inv[ci].own_state == 4)
            {
                if (cdata[0].continuous_action_id == 0)
                {
                    if (!inv_getspace(0))
                    {
                        txt(lang(
                            u8"バックパックが一杯だ。"s,
                            u8"Your inventory is full."s));
                        return 0;
                    }
                    gdata(91) = 103;
                    continuous_action_others();
                    return -1;
                }
            }
        }
        if (inv[ci].own_state == 3)
        {
            txt(lang(
                itemname(ci) + u8"を撤去する？ "s,
                u8"Do you want to remove "s + itemname(ci) + u8"? "s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval == 0)
            {
                snd(58);
                if (inv[ci].id == 555)
                {
                    std::string midbk = mid;
                    mid = ""s + 30 + u8"_"s + (100 + inv[ci].count);
                    if (fs::exists(
                            filesystem::dir::tmp()
                            / (u8"mdata_"s + mid + u8".s2")))
                    {
                        ctrl_file(file_operation_t::_11);
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
            txt(lang(
                u8"バックパックには、もうアイテムを入れる余裕がない。"s,
                u8"Your inventory is full."s));
            return 0;
        }
    }
    inumbk = inv[ci].number - in;
    inv[ci].number = in;
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
                    txt(lang(
                        u8"あなたは"s + itemname(ci)
                            + u8"から魔力を吸い取った。"s,
                        u8"You absorb magic from "s + itemname(ci) + u8"."s));
                    if (efid >= 400 && efid < 467)
                    {
                        spell(efid - 400) += inv[ci].count * 5 * inv[ci].number;
                    }
                    else
                    {
                        healmp(0, inv[ci].count * 5 * inv[ci].number);
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
                        txt(lang(
                            u8"あなたの手から毒が滴った。"s,
                            u8"Poison drips from your hands."s));
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
            inv[ci].number = inumbk + in;
            if (invctrl == 12)
            {
                txt(lang(
                    u8"店の倉庫が一杯のため売れない。"s,
                    u8"Shopkeeper's inventory is full."s));
            }
            else
            {
                txt(lang(
                    u8"バックパックには、もうアイテムを入れる余裕がない。"s,
                    u8"Your inventory is full."s));
            }
            return 0;
        }
        item_copy(ci, ti);
        inv[ti].number = in;
    }
    inv[ci].number = inumbk;
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
                        inv[ti].param3 += gdata_hour + gdata_day * 24
                            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12;
                    }
                }
                else if (inv[ti].param3 != 0 && inv[ti].material == 35)
                {
                    inv[ti].param3 = gdata_hour + gdata_day * 24
                        + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12
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
                    inv[ti].param3 = inv[ti].param3
                        - (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                           + gdata_year * 24 * 30 * 12);
                }
            }
        }
        if (invctrl == 11)
        {
            msgkeep = 1;
            txt(lang(
                itemname(ti, in) + u8"を買った。"s,
                u8"You buy "s + itemname(ti, in) + u8"."s));
            sellgold = calcitemvalue(ti, 0) * in;
            snd(12);
            cdata[0].gold -= sellgold;
            cdata[tc].gold += sellgold;
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
                txt(lang(
                    itemname(ti, in) + u8"を売った。"s,
                    u8"You sell "s + itemname(ti, in) + u8"."s));
            }
            else
            {
                ibitmod(9, ti, 0);
                txt(lang(
                    u8"盗品の"s + itemname(ti, in) + u8"を売却した。"s,
                    u8"You sell "s + itemname(ti, in)
                        + u8".(Stolen item sold) "s));
                if (gdata_thieves_guild_quota > 0)
                {
                    gdata_thieves_guild_quota -= sellgold;
                    if (gdata_thieves_guild_quota < 0)
                    {
                        gdata_thieves_guild_quota = 0;
                    }
                    txt(lang(
                        u8"盗賊ギルドのノルマ達成まで、あと金貨"s
                            + gdata_thieves_guild_quota
                            + u8"枚相当の盗品を売却する必要がある。"s,
                        u8"You still need to sell stuff worth "s
                            + gdata_thieves_guild_quota
                            + u8" gold pieces in order to advance ranks in the Thieves Guild."s));
                }
            }
            snd(11);
            cdata[0].gold += sellgold;
            cdata[tc].gold -= sellgold;
            if (cdata[tc].gold < 0)
            {
                cdata[tc].gold = 0;
            }
            inv[ti].identification_state =
                identification_state_t::completely_identified;
        }
        if (invctrl == 22 || invctrl == 24)
        {
            snd(14 + rnd(2));
            msgkeep = 1;
            if (invctrl == 22)
            {
                txt(lang(
                    name(cc) + u8"は"s + itemname(ti, in) + u8"を拾った。"s,
                    name(cc) + u8" pick"s + _s(cc) + u8" up "s
                        + itemname(ti, in) + u8"."s));
            }
            else
            {
                txt(lang(
                    itemname(ti, in) + u8"を保管した。"s,
                    u8"You put "s + itemname(ti, in)
                        + u8" in the container."s));
            }
        }
        else
        {
            r2 = sellgold;
            gain_negotiation_experience(0);
        }
    }
    else
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        map(inv[ci].position.x, inv[ci].position.y, 5) =
            map(inv[ci].position.x, inv[ci].position.y, 4);
        snd(14 + rnd(2));
        msgkeep = 1;
        txt(lang(
            name(cc) + u8"は"s + itemname(ti, in) + u8"を拾った。"s,
            name(cc) + u8" pick"s + _s(cc) + u8" up "s + itemname(ti, in)
                + u8"."s));
    }
    if (cc == 0)
    {
        if (inv[ti].id == 255)
        {
            if (mdata(20) == 1)
            {
                f = 0;
                for (const auto& cnt : items(-1))
                {
                    if (inv[cnt].number == 0)
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
                    mdata(20) = 0;
                    play_music();
                }
            }
        }
        int stat = convertartifact(ti);
        ti = stat;
        if (adata(16, gdata_current_map) == 101)
        {
            if (mode == 0)
            {
                update_museum();
            }
        }
        if (gdata_current_map == 7)
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

int drop_item()
{
    inumbk = inv[ci].number - in;
    inv[ci].number = in;
    inv[ci].position.x = cdata[cc].position.x;
    inv[ci].position.y = cdata[cc].position.y;
    itemturn(ci);
    int stat = item_stack(-1, ci);
    const auto tibk = ti; // TODO: refactor
    if (stat == 0 || dropval == 0)
    {
        ti = inv_getfreeid(-1);
        if (ti == -1)
        {
            txt(lang(
                u8"もう周りに物を置くスペースがない！ "s,
                u8"The place is too crowded. You can't drop stuff anymore."s));
            update_screen();
            return 0;
        }
        item_copy(ci, ti);
    }
    if (dropval == 1)
    {
        inv[ti].own_state = 3;
        inv[ti].count = gdata_next_shelter_serial_id + 100;
        ++gdata_next_shelter_serial_id;
    }
    inv[ci].number = inumbk;
    cell_refresh(inv[ti].position.x, inv[ti].position.y);
    if (dropval == 0)
    {
        screenupdate = -1;
        update_screen();
        snd(16);
        txt(lang(
            itemname(ti, in) + u8"を地面に置いた。"s,
            u8"You drop "s + itemname(ti, in) + u8"."s));
    }
    refresh_burden_state();
    if (inv[tibk].id == 516)
    {
        int stat = item_find(60002, 0);
        if (stat != -1)
        {
            p = stat;
            if (core_god::int2godid(inv[p].param1) == cdata[cc].god_id)
            {
                if (inv[tibk].curse_state != curse_state_t::blessed)
                {
                    snd(64);
                    inv[tibk].curse_state = curse_state_t::blessed;
                    txtef(2);
                    txt(lang(
                        u8"水は祝福を受けた。"s, u8"The water is blessed."s));
                }
            }
        }
    }
    if (adata(16, gdata_current_map) == 101)
    {
        if (mode == 0)
        {
            update_museum();
        }
    }
    if (gdata_current_map == 7)
    {
        if (mode == 0)
        {
            calc_home_rank();
        }
    }
    if (inv[ti].id == 255)
    {
        mdata(20) = 1;
        play_music();
    }
    return 1;
}



int equip_item(int cc)
{
    if (ci == -1)
    {
        return 0;
    }
    if (cdata_body_part(cc, body) % 10000 != 0)
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
        item_identify(inv[ci], identification_state_t::almost_identified);
    }
    inv[ci].body_part = body;
    cdata_body_part(cc, body) =
        cdata_body_part(cc, body) / 10000 * 10000 + ci + 1;
    return 1;
}



void unequip_item(int cc)
{
    p = cdata_body_part(cc, body) % 10000;
    if (p == 0)
    {
        rtval = -2;
        return;
    }
    ci = p - 1;
    cdata_body_part(cc, body) = cdata_body_part(cc, body) / 10000 * 10000;
    inv[ci].body_part = 0;
    item_stack(cc, ci);
}



void lost_body_part(int cc)
{
    for (int cnt = 100; cnt < 130; ++cnt)
    {
        if (cdata_body_part(cc, cnt) / 10000 == body)
        {
            p = cdata_body_part(cc, cnt) % 10000;
            if (p == 0)
            {
                continue;
            }
            --p;
            inv[p].body_part = 0;
            cdata_body_part(cc, cnt) = cdata_body_part(cc, cnt) / 10000 * 10000;
        }
    }
    return;
}


turn_result_t do_bash()
{
    if (map(x, y, 5) != 0)
    {
        if (mapitemfind(x, y, 526) != -1)
        {
            ci = mapitemfind(x, y, 526);
            item_separate(ci);
            snd(73);
            txt(lang(
                itemname(ci) + u8"に体当たりした。"s,
                u8"You throw your weight against "s + itemname(ci) + u8"."s));
            if (inv[ci].own_state == 5 || inv[ci].param1 <= 0)
            {
                txt(lang(
                    u8"もう実はないようだ… "s,
                    u8"It seems there are no fruits left on the tree."s));
                return turn_result_t::turn_end;
            }
            --inv[ci].param1;
            if (inv[ci].param1 <= 0)
            {
                inv[ci].image = 592;
                cell_refresh(x, y);
            }
            if (y + 1 < mdata(1))
            {
                if ((chipm(7, map(x, y + 1, 0)) & 4) == 0)
                {
                    ++y;
                }
            }
            flt();
            itemcreate(-1, inv[ci].param2, x, y, 0);
            txt(lang(
                itemname(ci, 1) + u8"が降ってきた。"s,
                itemname(ci, 1) + u8" falls down from the tree."s));
            item_stack(-1, ci);
            return turn_result_t::turn_end;
        }
    }
    if (map(x, y, 1) != 0)
    {
        tc = map(x, y, 1) - 1;
        if (cdata[tc].sleep == 0)
        {
            if (cc == 0)
            {
                if (cdata[tc].relationship >= 0)
                {
                    int stat = label_2073();
                    if (stat == 0)
                    {
                        return turn_result_t::pc_turn_user_error;
                    }
                }
            }
            if (cdata[tc].choked)
            {
                snd(73);
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"に全力で体当たりした。"s,
                    name(cc) + u8" bash"s + _s(cc) + u8" up "s + name(tc)
                        + u8" at full power."s));
                dmghp(tc, sdata(10, cc) * 5, cc);
                if (cdata[tc].state == 1)
                {
                    txt(lang(
                        name(tc) + u8"はもちを吐き出した。"s,
                        name(tc) + u8" spit"s + _s(tc) + u8" mochi."s));
                    txt(lang(u8"「助かったよ！」"s, u8"\"You saved me!\""s));
                    cdata[tc].choked = 0;
                    chara_mod_impression(tc, 10);
                }
            }
            else
            {
                snd(73);
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"に体当たりした。"s,
                    name(cc) + u8" bash"s + _s(cc) + u8" up "s + name(tc)
                        + u8"."s));
                hostileaction(cc, tc);
            }
        }
        else
        {
            snd(73);
            txt(lang(
                name(cc) + u8"は"s + name(tc) + u8"に体当たりした。"s,
                name(cc) + u8" bash"s + _s(cc) + u8" up "s + name(tc)
                    + u8"."s));
            txt(lang(
                name(tc) + u8"は睡眠を妨害された。"s,
                name(cc) + u8" disturb"s + _s(cc) + u8" "s + his(tc)
                    + u8" sleep."s));
            modify_karma(cc, -1);
            cdata[tc].emotion_icon = 418;
        }
        cdata[tc].sleep = 0;
        return turn_result_t::turn_end;
    }
    if (map(x, y, 6) != 0)
    {
        cell_featread(x, y);
        if (feat(1) == 30)
        {
            map(x, y, 6) = 0;
            spillfrag(x, y, 2);
            flt(calcobjlv(
                    gdata_current_dungeon_level * (gdata_current_map != 30)),
                calcfixlv(2));
            flttypemajor = fsetbarrel(rnd(length(fsetbarrel)));
            itemcreate(-1, 0, x, y, 0);
            if (is_in_fov(cc))
            {
                snd(73);
                txt(lang(
                    name(cc) + u8"は壷を割った。"s,
                    name(cc) + u8" shatter"s + _s(cc) + u8" the pot."s));
                snd(45);
                play_animation(14);
            }
            return turn_result_t::turn_end;
        }
        if (feat(1) == 21)
        {
            snd(73);
            p = feat(2) * 3 + 30;
            if (gdata_current_map == 41)
            {
                p *= 20;
            }
            if (rnd(p) < sdata(10, cc) && rnd(2))
            {
                txt(lang(
                    u8"扉に体当たりして破壊した。"s,
                    u8"You bash up the door. The door is destroyed."s));
                if (feat(2) > sdata(10, cc))
                {
                    skillexp(10, cc, (feat(2) - sdata(10, cc)) * 15);
                }
                cell_featset(x, y, 0, 0, 0, 0);
                return turn_result_t::turn_end;
            }
            else
            {
                txt(lang(u8"扉に体当たりした。"s, u8"You bash up the door."s));
                if (gdata_current_map == 41)
                {
                    txt(lang(
                        u8"さすがに牢獄の扉は頑丈だ。"s,
                        u8"As might be expected, the door of the Jail is hard."s));
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
                    if (cdata[cc].quality < 4 && encfind(cc, 60010) == -1)
                    {
                        --cdata[cc].attr_adjs[0];
                        chara_refresh(cc);
                        if (is_in_fov(cc))
                        {
                            txtef(8);
                            txt(lang(
                                name(cc) + u8"は筋肉を痛めた。"s,
                                name(cc) + u8" hurt"s + _s(cc) + u8" "s
                                    + his(cc) + u8" muscle."s));
                        }
                    }
                }
                if (rnd(3) == 0)
                {
                    if (feat(2) > 0)
                    {
                        --feat(2);
                        cell_featset(x, y, feat(0), feat(1), feat(2), feat(3));
                        if (is_in_fov(cc))
                        {
                            txt(lang(
                                u8"扉は少しだけ壊れた。"s,
                                u8"The door is cracked a bit."s));
                        }
                    }
                }
                return turn_result_t::turn_end;
            }
        }
    }
    txt(lang(
        name(cc) + u8"は空気に体当たりした。"s,
        name(cc) + u8" bash"s + _s(cc) + u8" up the air."s));
    snd(4);
    return turn_result_t::turn_end;
}



turn_result_t proc_movement_event()
{
    if (cdata[cc].is_ridden())
    {
        return turn_result_t::turn_end;
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
    if (map(dx, dy, 6) != 0)
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
    if (map(cdata[cc].position.x, cdata[cc].position.y, 8) != 0)
    {
        bool turn_ended = mef_proc_from_movement(cc);
        if (turn_ended)
        {
            return turn_result_t::turn_end;
        }
    }
    if (mdata(6) == 1)
    {
        if (cc == 0)
        {
            if (traveldone == 0)
            {
                label_2153();
                keybd_wait = 1;
                return turn_result_t::turn_end;
            }
            else
            {
                traveldone = 0;
            }
        }
    }
    proc_trap();
    p = map(cdata[cc].position.x, cdata[cc].position.y, 0);
    if (chipm(0, p) == 3)
    {
        if (chipm(1, p) == 5)
        {
            healsan(cc, 1);
        }
        addefmap(cdata[cc].position.x, cdata[cc].position.y, 1, 3);
        if (cdata[cc].wet == 0)
        {
            wet(cc, 20);
        }
    }
    label_2206();
    if (mdata(6) == 1)
    {
        if (cc == 0)
        {
            encounter = 0;
            gdata(62) = map(cdata[cc].position.x, cdata[cc].position.y, 0);
            if (map(cdata[cc].position.x, cdata[cc].position.y, 6) == 0)
            {
                p = map(cdata[cc].position.x, cdata[cc].position.y, 0);
                if (rnd(30) == 0)
                {
                    encounter = 1;
                }
                if (gdata_weather == 4)
                {
                    if (rnd(10) == 0)
                    {
                        encounter = 1;
                    }
                }
                if (gdata_weather == 1)
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
                if (rnd(220 + cdata[0].level * 10
                        - clamp(
                              gdata_cargo_weight * 150
                                  / (gdata_current_cart_limit + 1),
                              0,
                              (210 + cdata[0].level * 10)))
                    == 0)
                {
                    encounter = 4;
                }
                if (rnd(20) == 0)
                {
                    for (int cnt = 0; cnt < 5; ++cnt)
                    {
                        rq = gdata(160 + cnt);
                        if (qdata(3, rq) == 1007)
                        {
                            if (qdata(8, rq) == 1)
                            {
                                if (qdata(4, rq) == 0)
                                {
                                    if (qdata(10, rq) < 2)
                                    {
                                        encounter = 3;
                                        encounterref = rq;
                                        ++qdata(10, rq);
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
                encounterlv = cdata[0].fame / 1000;
                if (encounterlv == 0)
                {
                    encounterlv = 1;
                }
                levelexitby = 4;
                return turn_result_t::exit_map;
            }
            if (encounter == 3)
            {
                txt(lang(
                    u8"暗殺者につかまった。あなたはクライアントを守らなければならない。"s,
                    u8"You are caught by assassins. You have to protect your client."s));
                msg_halt();
                gdata_previous_map2 = gdata_current_map;
                gdata_previous_dungeon_level = gdata_current_dungeon_level;
                gdata_previous_x = cdata[0].position.x;
                gdata_previous_y = cdata[0].position.y;
                levelexitby = 4;
                return turn_result_t::exit_map;
            }
            if (encounter == 2)
            {
                encounterlv = 10 + rnd(100);
                levelexitby = 4;
                return turn_result_t::exit_map;
            }
            if (encounter == 1)
            {
                p = dist_town();
                encounterlv = p * 3 / 2 - 10;
                if (cdata[0].level <= 5)
                {
                    encounterlv /= 2;
                }
                if (33 <= map(cdata[cc].position.x, cdata[cc].position.y, 0)
                    && map(cdata[cc].position.x, cdata[cc].position.y, 0) < 66)
                {
                    encounterlv /= 2;
                }
                else if (gdata_weather == 1)
                {
                    encounterlv = encounterlv * 3 / 2 + 10;
                }
                if (encounterlv < 0)
                {
                    encounterlv = 1;
                }
                auto valn = lang(
                    u8" (最も近い街までの距離:"s + p + u8" 敵勢力:"s,
                    u8" (Distance from nearest town:"s + p
                        + u8" Enemy strength:"s);
                for (int cnt = 0; cnt < 1; ++cnt)
                {
                    if (encounterlv < 5)
                    {
                        valn += lang(u8"プチ級"s, u8"Putit Rank"s);
                        break;
                    }
                    if (encounterlv < 10)
                    {
                        valn += lang(u8"オーク級"s, u8"Orc Rank"s);
                        break;
                    }
                    if (encounterlv < 20)
                    {
                        valn += lang(u8"グリズリー級"s, u8"Grizzly Bear Rank"s);
                        break;
                    }
                    if (encounterlv < 30)
                    {
                        valn += lang(u8"ドレイク級"s, u8"Drake Rank"s);
                        break;
                    }
                    if (encounterlv < 40)
                    {
                        valn += lang(u8"リッチ級"s, u8"Lich Rank"s);
                        break;
                    }
                    valn += lang(u8"ドラゴン級"s, u8"Dragon Rank"s);
                }
                valn += u8")"s;
                txt(lang(u8"襲撃だ！"s, u8"Ambush!"s) + valn);
                msg_halt();
                levelexitby = 4;
                return turn_result_t::exit_map;
            }
            encounter = 0;
        }
    }
    return turn_result_t::turn_end;
}



void proc_autopick()
{
    if (!config::instance().use_autopick)
        return;
    if (key_ctrl)
        return;
    if (adata(0, gdata_current_map) == 5 && adata(16, gdata_current_map) != 30
        && adata(16, gdata_current_map) != 31)
        return;


    for (const auto& ci : items(-1))
    {
        if (inv[ci].number == 0)
            continue;
        if (inv[ci].position != cdata[0].position)
            continue;
        if (inv[ci].own_state > 0)
            continue;

        item_checkknown(ci);

        const auto x = cdata[0].position.x;
        const auto y = cdata[0].position.y;

        bool did_something = true;
        const auto op = autopick::instance().get_operation(inv[ci]);
        switch (op.type)
        {
        case autopick::operation::type_t::do_nothing:
            did_something = false;
            break;
        case autopick::operation::type_t::pick_up:
        case autopick::operation::type_t::save:
        case autopick::operation::type_t::no_drop:
        case autopick::operation::type_t::save_and_no_drop:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_pick_up")(
                    itemname(ci)));
                ELONA_YES_NO_PROMPT();
                show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            in = inv[ci].number;
            elona::ci = ci;
            pick_up_item();
            if (int(op.type) & int(autopick::operation::type_t::no_drop))
            {
                ibitmod(13, ti, 1);
                txt(lang(
                    itemname(ti) + u8"を大事なものに指定した。"s,
                    u8"You set "s + itemname(ti) + u8" as no-drop."s));
            }
            if (int(op.type) & int(autopick::operation::type_t::save))
            {
                if (gdata_wizard == 0)
                {
                    snd(44);
                    save_game();
                    txtef(5);
                    txt(lang(u8" *保存* "s, u8"*saving*"s));
                }
            }
            break;
        case autopick::operation::type_t::destroy:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_destroy")(
                    itemname(ci)));
                ELONA_YES_NO_PROMPT();
                show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            snd(45);
            txt(i18n::fmt(u8"ui", u8"autopick", u8"destroyed")(itemname(ci)));
            inv[ci].number = 0;
            cell_refresh(x, y);
            map(x, y, 5) = map(x, y, 4);
            break;
        case autopick::operation::type_t::open:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::fmt(u8"ui", u8"autopick", u8"do_you_really_open")(
                    itemname(ci)));
                ELONA_YES_NO_PROMPT();
                show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    did_something = false;
                    break;
                }
            }
            elona::ci = ci;
            (void)do_open_command();
            break;
        }
        if (did_something && !op.sound.empty())
        {
            DSLOADFNAME(filesystem::dir::sound() / op.sound, 15);
            DSPLAY(15, 0);
        }
    }
}



void label_2206()
{
    if (cc == 0)
    {
        gdata(60) = -1;
        gdata(61) = -1;
        x = cdata[0].position.x;
        y = cdata[0].position.y;
        if (key_shift && gdata(30) == 0 && cdata[0].confused == 0
            && cdata[0].dimmed == 0)
        {
            if (mdata(6) != 1)
            {
                gdata(30) = 1;
                cell_check(cdata[cc].position.x + 1, cdata[cc].position.y);
                gdata(33) = cellaccess;
                cell_check(cdata[cc].position.x - 1, cdata[cc].position.y);
                gdata(31) = cellaccess;
                cell_check(cdata[cc].position.x, cdata[cc].position.y + 1);
                gdata(34) = cellaccess;
                cell_check(cdata[cc].position.x, cdata[cc].position.y - 1);
                gdata(32) = cellaccess;
            }
        }
        if (map(x, y, 4) != 0)
        {
            if (cdata[0].blind == 0)
            {
                txt(txtitemoncell(x, y));
                proc_autopick();
            }
            else
            {
                txt(lang(
                    u8"地面に何かがあるようだ。"s,
                    u8"You sense something under your foot."s));
            }
        }
        p = chipm(0, map(x, y, 0));
        if (p != 0)
        {
            if (tname(p) != ""s)
            {
                txt(lang(
                    u8"足元には"s + tname(p) + u8"がある。"s,
                    u8"You walk into "s + tname(p) + u8"."s));
            }
            if (p == 3)
            {
                snd(46);
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
                if (keybd_wait <= config::instance().walkwait
                            * config::instance().startrun
                    || cdata[0].turn % 2 == 0 || mdata(6) == 1)
                {
                    snd(83 + foot % 3);
                    foot += 1 + rnd(2);
                }
            }
        }
        else if (mdata(6) == 1)
        {
            addefmap(cdata[cc].position.x, cdata[cc].position.y, 2, 10, dirsub);
            snd(81 + foot % 2);
            ++foot;
        }
        if (map(x, y, 6) != 0)
        {
            cell_featread(x, y);
            if (feat(1) == 32)
            {
                txtef(5);
                txt(lang(u8" *キラン* "s, u8"*twinkle*"s));
            }
            if (feat(1) == 15)
            {
                txt(mapname(feat(2) + feat(3) * 100, true));
                if (adata(16, feat(2) + feat(3) * 100) == 8)
                {
                    if (config::instance().extrahelp)
                    {
                        if (gdata(206) == 0)
                        {
                            if (mode == 0)
                            {
                                if (cdata[0].continuous_action_turn == 0)
                                {
                                    gdata(206) = 1;
                                    ghelp = 6;
                                    show_ex_help();
                                }
                            }
                        }
                    }
                }
            }
            if (feat(1) == 34)
            {
                txt(txtbuilding(feat(2), feat(3)));
            }
            if (feat(1) == 11)
            {
                txt(lang(
                    u8"降り階段がある。"s,
                    u8"There is a stair leading downwards here."s));
            }
            if (feat(1) == 10)
            {
                txt(lang(
                    u8"昇り階段がある。"s,
                    u8"There is a stair leading upwards here."s));
            }
            if (feat(1) == 24)
            {
                txt(lang(
                    u8"何かが見つかりそうだ。"s,
                    u8"You can search this location to collect some materials."s));
            }
            if (feat(1) == 27)
            {
                txt(lang(
                    u8"何かの残骸がある。"s,
                    u8"You can collect materials from the remains lying here."s));
            }
            if (feat(1) == 25)
            {
                txt(lang(
                    u8"採掘場がある。"s,
                    u8"You can collect materials from the mining spot here."s));
            }
            if (feat(1) == 26)
            {
                txt(lang(
                    u8"泉がある。"s,
                    u8"You can collect materials from the spring here."s));
            }
            if (feat(1) == 28)
            {
                txt(lang(
                    u8"色んな植物が生えている。"s,
                    u8"You can collect materials from plants here."s));
            }
            if (feat(1) == 29)
            {
                if (feat(2) == 36)
                {
                    s = lang(u8"野菜"s, u8"vegetable"s);
                }
                if (feat(2) == 37)
                {
                    s = lang(u8"果物"s, u8"fruit"s);
                }
                if (feat(2) == 38)
                {
                    s = lang(u8"ハーブ"s, u8"herb"s);
                }
                if (feat(2) == 39)
                {
                    s = lang(u8"何か"s, u8"strange"s);
                }
                if (feat(2) == 40)
                {
                    s = lang(u8"アーティファクト"s, u8"artifact"s);
                }
                if (feat(2) == 41)
                {
                    s = lang(u8"宝石"s, u8"gem"s);
                }
                if (feat(2) == 42)
                {
                    s = lang(u8"魔法の木"s, u8"magic"s);
                }
                if (feat == tile_plant)
                {
                    txt(lang(
                        ""s + s + u8"の種が植えてある。"s,
                        u8"A "s + s + u8" seed is planted."s));
                }
                if (feat == tile_plant + 1)
                {
                    txt(lang(
                        ""s + s + u8"が育っている。"s,
                        u8"A "s + s + u8" bud is growing."s));
                }
                if (feat == tile_plant + 2)
                {
                    txt(lang(
                        ""s + s + u8"の実が成っている。"s,
                        u8"A"s + s + u8" tree has bore a lot of fruit."s));
                }
                if (feat == tile_plant + 3)
                {
                    txt(lang(
                        ""s + s + u8"の草は枯れてしまっている… "s,
                        u8"A "s + s + u8" tree has withered..."s));
                }
            }
            if (feat(1) >= 24 && feat(1) <= 28)
            {
                if (config::instance().extrahelp)
                {
                    if (gdata(205) == 0)
                    {
                        if (mode == 0)
                        {
                            if (cdata[0].continuous_action_turn == 0)
                            {
                                gdata(205) = 1;
                                ghelp = 5;
                                show_ex_help();
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}



int unlock_box(int difficulty)
{
    int stat = item_find(636, 3);
    if (stat == -1)
    {
        txt(lang(
            u8"ロックピックを所持していない。"s,
            u8"You don't have lockpicks."s));
        return 0;
    }
    ti = stat;
    txt(lang(u8"ロックピックを使用した。"s, u8"You use a lockpick."s));
    snd(22);
    {
        int stat = item_find(637, 3);
        if (stat != -1)
        {
            i = sdata(158, 0) * 150 / 100 + 5;
            txt(lang(
                u8"スケルトンキーも使用した。"s,
                u8"You also use the skeleton key."s));
        }
        else
        {
            i = sdata(158, 0);
        }
    }
    f = 0;
    if (i * 2 < difficulty)
    {
        txt(lang(
            u8"この鍵を開ける技術はない。"s,
            u8"The lock mechanism is beyond your skill."s));
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
            txt(lang(u8"楽勝だ。"s, u8"Easy."s));
        }
        else if (rnd(rnd(i * 2) + 1) < difficulty)
        {
            txt(lang(u8"開錠に失敗した。"s, u8"You fail to unlock it."s));
            f = 1;
        }
    }
    if (f)
    {
        if (rnd(3) == 0)
        {
            --inv[ti].number;
            cell_refresh(inv[ti].position.x, inv[ti].position.y);
            txt(lang(u8"ロックピックは壊れた。"s, u8"Your lockpick breaks."s));
        }
        txtnew();
        txt(lang(u8"もう一度試みる？"s, u8"Try again?"s));
        ELONA_YES_NO_PROMPT();
        rtval = show_prompt(promptx, prompty, 160);
        if (rtval == 0)
        {
            unlock_box(difficulty);
            return 0;
        }
        return 0;
    }
    txt(lang(u8"開錠に成功した。"s, u8"You successfully unlock it."s));
    gain_lock_picking_experience(cc);
    return 1;
}



void open_box()
{
    snd(23);
    txt(lang(
        u8"あなたは"s + itemname(ci) + u8"を開けた。"s,
        u8"You open "s + itemname(ci) + u8"."s));
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
        if (cnt == 0)
        {
            p = 3;
        }
        else
        {
            p = 2;
        }
        if (inv[ri].id == 239)
        {
            if (cnt == 0 && rnd(3) == 0)
            {
                p = 4;
            }
            else
            {
                p = 3;
            }
            if (rnd(60) == 0)
            {
                dbid = 559;
            }
        }
        flt(calcobjlv(inv[ri].param1), calcfixlv(p));
        flttypemajor = fsetchest(rnd(length(fsetchest)));
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
            flttypemajor = fsetwear(rnd(length(fsetwear)));
            fixlv = 3;
            if (inv[ri].id == 416)
            {
                fixlv = 4;
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
        itemcreate(-1, dbid, cdata[0].position.x, cdata[0].position.y, in);
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
        itemcreate(-1, 622, cdata[0].position.x, cdata[0].position.y, 1);
    }
    snd(24);
    txt(lang(
        itemname(ri) + u8"から溢れ出た高級品が、足元に散らばった。"s,
        u8"Several quality goods spread out from "s + itemname(ri) + u8"."s));
    autosave = 1 * (gdata_current_map != 35);
    inv[ri].param1 = 0;
    if (inv[ri].id == 284)
    {
        modify_karma(0, -4);
    }
    if (inv[ri].id == 283)
    {
        modify_karma(0, -8);
    }
    return;
}



void open_new_year_gift()
{
    snd(23);
    txt(lang(
        u8"あなたは"s + itemname(ci) + u8"を開けた。"s,
        u8"You open "s + itemname(ci) + u8"."s));
    msg_halt();
    snd(24);
    randomize();
    ri = ci;
    cc = 0;
    inv[ri].param1 = 0;
    if (inv[ri].param3 < 100)
    {
        if (rnd(3) == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"悪意を持った何かが袋から飛び出してきた！"s,
                    u8"Something jumps out from the pack!"s));
            }
            for (int cnt = 0, cnt_end = (3 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata[0].level * 3 / 2 + 3), calcfixlv(2));
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            }
            return;
        }
        if (rnd(3) == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"罠だ！お年玉袋は発火した。"s,
                    u8"It's trap! The gift ignites."s));
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                tlocx = cdata[0].position.x + rnd(3) - rnd(3);
                tlocy = cdata[0].position.y - rnd(3) + rnd(3);
                if (tlocx < 0 || tlocx >= mdata(0) || tlocy < 0
                    || tlocy >= mdata(1))
                {
                    continue;
                }
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, 0);
                mapitem_fire(tlocx, tlocy);
            }
            return;
        }
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"中には呪いの手紙が入っていた。"s,
                u8"You find a cursed letter inside."s));
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
            if (is_in_fov(cc))
            {
                txtef(5);
                txt(lang(u8" *チリリリリーン* "s, u8"*ring ring ring*"s));
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
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"妹が入っていた！"s,
                    u8"The pack contains your younger sister!"s));
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
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"何かが袋から出てきた。"s,
                u8"There's something inside the pack."s));
        }
        flt();
        itemcreate(
            -1,
            isetgiftminor(rnd(length(isetgiftminor))),
            cdata[0].position.x,
            cdata[0].position.y,
            1);
        return;
    }
    if (rnd(3) == 0)
    {
        if (is_in_fov(cc))
        {
            txtef(5);
            txt(lang(u8" *チリリリリーン* "s, u8"*ring ring ring*"s));
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
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"これは素晴らしい贈り物だ！"s,
                u8"This is truly a wonderful gift!"s));
        }
        flt();
        itemcreate(
            -1,
            isetgiftgrand(rnd(length(isetgiftgrand))),
            cdata[0].position.x,
            cdata[0].position.y,
            1);
        return;
    }
    if (is_in_fov(cc))
    {
        txt(lang(
            u8"何かが袋から出てきた。"s,
            u8"There's something inside the pack."s));
    }
    flt();
    itemcreate(
        -1,
        isetgiftmajor(rnd(length(isetgiftmajor))),
        cdata[0].position.x,
        cdata[0].position.y,
        1);
    return;
}



turn_result_t try_to_open_locked_door()
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
                await(100);
                return turn_result_t::turn_end;
            }
            feat(2) = 0;
        }
        else
        {
            return turn_result_t::turn_end;
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
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は扉を開けた。"s,
                name(cc) + u8" open"s + _s(cc) + u8" the door."s));
            if (mdata(12) == 8)
            {
                snd(67);
            }
            else if (mdata(12) == 9)
            {
                snd(71);
            }
            else
            {
                snd(48);
            }
        }
    }
    else
    {
        ++msgdup;
        if (is_in_fov(cc))
        {
            snd(22);
            txt(lang(
                aln(cc) + u8"開錠に失敗した。"s,
                name(cc) + u8" fail"s + _s(cc) + u8" to open the door."s));
        }
    }
    if (cc == 0)
    {
        await(100);
    }
    return turn_result_t::turn_end;
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
                txt(lang(u8"通常弾を装填した。"s, u8"You load normal ammo."s));
                inv[ammo].count = -1;
            }
            else
            {
                ammoproc = inv[ammo].enchantments[inv[ammo].count].id % 10000;
                if (cc == 0)
                {
                    if (cdata[0].sp < 50)
                    {
                        if (cdata[0].sp < rnd(75))
                        {
                            txt(lang(
                                u8"疲労し過ぎて失敗した！"s,
                                u8"You are too exhausted!"s));
                            dmgsp(0, encammoref(2, ammoproc) / 2 + 1);
                            ammoproc = -1;
                            return;
                        }
                    }
                    dmgsp(0, rnd(encammoref(2, ammoproc) + 1));
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
            if (cdata[tc].state != 1)
            {
                int stat = label_2072();
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
            label_2076();
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
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"は盾で"s + name(tc) + u8"を殴りつけた。"s,
                    name(cc) + u8" bash"s + _s(cc) + u8" "s + name(tc)
                        + u8" with "s + his(cc) + u8" shield."s));
            }
            dmghp(tc, rnd(sdata(168, cc)) + 1, cc);
            dmgcon(
                tc,
                status_ailment_t::dimmed,
                50 + int(std::sqrt(sdata(168, cc))) * 15);
            cdata[tc].paralyzed += rnd(3);
        }
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata_body_part(cc, cnt) % 10000 == 0)
        {
            continue;
        }
        if (cdata_body_part(cc, cnt) / 10000 == 10)
        {
            continue;
        }
        if (cdata_body_part(cc, cnt) / 10000 == 11)
        {
            continue;
        }
        cw = cdata_body_part(cc, cnt) % 10000 - 1;
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
    return;
}



void do_physical_attack()
{
    int attackdmg;
    int expmodifer = 0;
label_22191_internal:
    if (cdata[cc].state != 1)
    {
        return;
    }
    if (cdata[tc].state != 1)
    {
        return;
    }
    if (cdata[cc].fear != 0)
    {
        ++msgdup;
        txt(lang(
            name(cc) + u8"は怖気づいた。"s,
            name(cc) + u8" "s + is(cc) + u8" frightened."s));
        return;
    }
    if (map(cdata[tc].position.x, cdata[tc].position.y, 8) != 0)
    {
        bool return_now = mef_proc_from_physical_attack(tc);
        if (return_now)
        {
            return;
        }
    }
    if (attackrange == 1)
    {
        aniref = cw;
        play_animation(attackskill);
    }
    if (attacknum > 1 || cc != 0)
    {
    }
    expmodifer = 1 + cdata[tc].is_hung_on_sand_bag() * 15 + cdata[tc].splits()
        + cdata[tc].splits2() + (gdata_current_map == 35);
    int hit = calcattackhit();
    i = 0;
    if (hit == 1)
    {
        if (critical)
        {
            if (cc == 0)
            {
                txtef(3);
                txt(lang(u8"会心の一撃！ "s, u8"Critical Hit!"s));
            }
        }
        dmg = calcattackdmg();
        attackdmg = dmg;
        if (cc == 0)
        {
            if (config::instance().attackanime)
            {
                aniref = dmg * 100 / cdata[tc].max_hp;
                play_animation(12);
            }
        }
        if (attackskill != 106)
        {
            if (inv[cw].quality >= 4)
            {
                if (inv[cw].quality == 6)
                {
                    s(1) = lang(""s, u8"The "s) + iknownnameref(inv[cw].id);
                }
                else if (inv[cw].subname >= 40000)
                {
                    randomize(inv[cw].subname - 40000);
                    s(1) = random_title(1);
                    randomize();
                }
                else
                {
                    s(1) = lang(""s, u8"The "s) + iknownnameref(inv[cw].id);
                }
                s(1) = lang(u8"『"s, u8"<"s) + s(1) + lang(u8"』"s, u8">"s);
                if (is_in_fov(cc))
                {
                    if (rnd(5) == 0)
                    {
                        txtef(9);
                        txt(lang(
                            name(cc) + u8"は"s + s(1)
                                + u8"を誇らしげに構えた。"s,
                            name(cc) + u8" wield"s + _s(cc) + u8" "s + s(1)
                                + u8" proudly."s));
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
        if (is_in_fov(tc))
        {
            if (extraattack)
            {
                txt(lang(u8"さらに"s, u8"Furthermore,"s));
                txtcontinue();
            }
            if (attackskill == 106)
            {
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を"s
                            + _melee(0, cdata[cc].melee_attack_type),
                        name(cc) + u8" "s
                            + _melee(0, cdata[cc].melee_attack_type) + _s(cc)
                            + u8" "s + name(tc) + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s
                            + _melee(1, cdata[cc].melee_attack_type),
                        name(cc) + u8" "s
                            + _melee(1, cdata[cc].melee_attack_type) + _s(cc)
                            + u8" "s + name(tc) + u8"."s));
                }
            }
            if (attackskill == 108)
            {
                s = lang(u8"弓"s, u8"bow"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を射撃し"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で撃たれた。"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 109)
            {
                s = lang(u8"クロスボウ"s, u8"crossbow"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を射撃し"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で撃たれた。"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 110)
            {
                s = lang(u8"銃"s, u8"gun"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を射撃し"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で撃たれた。"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 100)
            {
                s = lang(u8"長剣"s, u8"sword"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を切り払い"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で切られた。"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 104)
            {
                s = lang(u8"槍"s, u8"spear"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を突き刺して"s,
                        name(cc) + u8" stab"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で刺された。"s,
                        name(cc) + u8" stab"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 105)
            {
                s = lang(u8"杖"s, u8"staff"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を打って"s,
                        name(cc) + u8" smash"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で打たれた。"s,
                        name(cc) + u8" smash"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 101)
            {
                s = lang(u8"短剣"s, u8"dagger"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を突き刺して"s,
                        name(cc) + u8" stab"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で刺された。"s,
                        name(cc) + u8" stab"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 103)
            {
                s = lang(u8"鈍器"s, u8"mace"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を打って"s,
                        name(cc) + u8" smash"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で打たれた。"s,
                        name(cc) + u8" smash"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 102)
            {
                s = lang(u8"斧"s, u8"axe"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を切り払い"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で切られた。"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 107)
            {
                s = lang(u8"鎌"s, u8"scythe"s);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"を切り払い"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i) + u8"で切られた。"s,
                        name(cc) + u8" slash"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
            if (attackskill == 111)
            {
                s = itemname(cw, 1, 1);
                if (tc >= 16)
                {
                    gdata(809) = 2;
                    txt(lang(
                        aln(cc) + name(tc) + u8"に"s + s(i) + u8"を投げ"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" and"s));
                }
                else
                {
                    txt(lang(
                        aln(tc) + name(cc) + u8"に"s + s(i)
                            + u8"で攻撃された。"s,
                        name(cc) + u8" shoot"s + _s(cc) + u8" "s + name(tc)
                            + u8" with "s + his(cc) + u8" "s + s(i) + u8"."s));
                }
            }
        }
        dmghp(tc, dmg, cc, ele, elep);
        if (critical)
        {
            skillexp(186, cc, 60 / expmodifer, 2);
            critical = 0;
        }
        if (rtdmg > cdata[tc].max_hp / 20 || rtdmg > sdata(154, tc)
            || rnd(5) == 0)
        {
            skillexp(
                attackskill,
                cc,
                clamp((sdata(173, tc) * 2 - sdata(attackskill, cc) + 1), 5, 50)
                    / expmodifer,
                0,
                4);
            if (attackrange == 0)
            {
                skillexp(152, cc, 20 / expmodifer, 0, 4);
                if (cdata[cc].equipment_type & 2)
                {
                    skillexp(167, cc, 20 / expmodifer, 0, 4);
                }
                if (cdata[cc].equipment_type & 4)
                {
                    skillexp(166, cc, 20 / expmodifer, 0, 4);
                }
            }
            else if (attackskill == 111)
            {
                skillexp(152, cc, 10 / expmodifer, 0, 4);
            }
            else
            {
                skillexp(189, cc, 25 / expmodifer, 0, 4);
            }
            if (cc == 0)
            {
                if (gdata_mount != 0)
                {
                    skillexp(301, 0, 30 / expmodifer, 0, 5);
                }
            }
            if (cdata[tc].state == 1)
            {
                skillexp(
                    chara_armor_class(tc),
                    tc,
                    clamp((250 * rtdmg / cdata[tc].max_hp + 1), 3, 100)
                        / expmodifer,
                    0,
                    5);
                if (cdata[tc].equipment_type & 1)
                {
                    skillexp(168, tc, 40 / expmodifer, 0, 4);
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
                dmghp(
                    cc,
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
                        if (is_in_fov(cc))
                        {
                            txtef(8);
                            txt(lang(
                                u8"棘が"s + name(cc) + u8"に刺さった。"s,
                                name(cc) + u8" "s + is(cc)
                                    + u8" stuck by several thorns."s));
                        }
                        dmghp(
                            cc,
                            clamp(attackdmg / 10, 1, cdata[tc].max_hp / 10),
                            tc,
                            p,
                            cdata[tc].damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 62)
                    {
                        if (is_in_fov(cc))
                        {
                            txtef(8);
                            txt(lang(
                                u8"エーテルの棘が"s + name(cc)
                                    + u8"に刺さった。"s,
                                name(cc) + u8" "s + is(cc)
                                    + u8" stuck by several ether thorns."s));
                        }
                        dmghp(
                            cc,
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
                                item_acid(cc, cw);
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
                        if (is_in_fov(tc))
                        {
                            txtef(8);
                            txt(lang(
                                u8"酸が飛び散った。"s,
                                u8"Acids spread over the ground."s));
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
            snd(4);
        }
        if (sdata(attackskill, cc) > sdata(173, tc) || rnd(5) == 0)
        {
            p = clamp((sdata(attackskill, cc) - sdata(173, tc) / 2 + 1), 1, 20)
                / expmodifer;
            skillexp(173, tc, p, 0, 4);
            skillexp(187, tc, p, 0, 4);
        }
    }
    if (hit == -1)
    {
        if (is_in_fov(cc))
        {
            if (extraattack)
            {
                txt(lang(u8"さらに"s, u8"Furthermore,"s));
                txtcontinue();
            }
            if (tc < 16)
            {
                txt(lang(
                    aln(tc) + name(cc) + u8"の攻撃を避けた。"s,
                    name(tc) + u8" evade"s + _s(tc) + u8" "s + name(cc)
                        + u8"."s));
            }
            else
            {
                txt(lang(
                    aln(cc) + u8"攻撃をかわされた。"s,
                    name(cc) + u8" miss"s + _s(cc, true) + u8" "s + name(tc)
                        + u8"."s));
            }
            add_damage_popup(u8"miss", tc, {0, 0, 0});
        }
    }
    if (hit == -2)
    {
        if (is_in_fov(cc))
        {
            if (extraattack)
            {
                txt(lang(u8"さらに"s, u8"Furthermore,"s));
                txtcontinue();
            }
            if (tc < 16)
            {
                txt(lang(
                    aln(tc) + name(cc) + u8"の攻撃を華麗に避けた。"s,
                    name(tc) + u8" skillfully evade"s + _s(tc) + u8" "s
                        + name(cc) + u8"."s));
            }
            else
            {
                txt(lang(
                    aln(cc) + u8"攻撃を華麗にかわされた。"s,
                    name(tc) + u8" skillfully evade"s + _s(tc) + u8" "s
                        + name(cc) + u8"."s));
            }
            add_damage_popup(u8"evade!!", tc, {0, 0, 0});
        }
    }
    if (tc == 0)
    {
        gdata(30) = 0;
    }
    rowact_check(tc);
    if (attackskill != 106)
    {
        if (cdata[tc].state != 1)
        {
            cw = attackitem;
            if (ibit(10, cw))
            {
                if (inv[cw].param2 < calcexpalive(inv[cw].param1))
                {
                    inv[cw].param2 += rnd(cdata[tc].level / inv[cw].param1 + 1);
                    if (inv[cw].param2 >= calcexpalive(inv[cw].param1))
                    {
                        txtef(2);
                        snd(61);
                        txt(lang(
                            itemname(cw) + u8"は十分に血を味わった！"s,
                            itemname(cw) + u8" has tasted enough blood!"s));
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
    return;
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
            healsp(cc, p);
            dmgsp(tc, p / 2);
            continue;
        }
        if (enc == 38)
        {
            p = rnd(inv[cw].enchantments[cnt].power / 25 + 1) + 1;
            healmp(cc, p / 5);
            if (cdata[tc].state != 1)
            {
                continue;
            }
            dmgmp(tc, p);
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
            if (gdata_left_turns_of_timestop == 0)
            {
                if (rnd(25) == 0)
                {
                    txtef(9);
                    txt(lang(
                        name(cc) + u8"は時を止めた。"s,
                        name(cc) + u8" stop"s + _s(cc) + u8" time."s));
                    gdata_left_turns_of_timestop =
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
                gdata(809) = 1;
                dmghp(tc, orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 61)
        {
            s = chara_refstr(cdata[tc].id, 8);
            if (strutil::contains(s(0), u8"/god/"))
            {
                gdata(809) = 1;
                dmghp(tc, orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 58)
        {
            s = chara_refstr(cdata[tc].id, 8);
            if (strutil::contains(s(0), u8"/undead/"))
            {
                gdata(809) = 1;
                dmghp(tc, orgdmg / 2, cc);
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
                if (cdata[tc].state != 1)
                {
                    continue;
                }
                gdata(809) = 1;
                dmghp(
                    tc,
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
                if (cdata[tc].state != 1)
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
        txtef(9);
        txt(lang(
            name(cc) + u8"は時を止めた。"s,
            name(cc) + u8" stop"s + _s(cc) + u8" time."s));
        gdata_left_turns_of_timestop = 4;
    }
    if (ammoproc == 3)
    {
        if (cdata[tc].state == 1)
        {
            gdata(809) = 1;
            dmghp(
                tc,
                orgdmg * 2 / 3,
                cc,
                rnd(11) + 50,
                sdata(attackskill, cc) * 10 + 100);
        }
    }
    return;
}



void discover_trap()
{
    cell_featset(refx, refy, tile_trap, -1, -1);
    return;
}



void discover_hidden_path()
{
    map(refx, refy, 0) = tile_tunnel;
    cell_featset(refx, refy, 0, 0);
    return;
}



turn_result_t do_dig_after_sp_check()
{
    if (cdata[cc].sp < 0)
    {
        txt(lang(
            u8"疲れ過ぎて無理だ。"s, u8"You are too exhausted to do that."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    rowactre = 0;
    digx = tlocx;
    digy = tlocy;
    spot_mining_or_wall();
    return turn_result_t::turn_end;
}



void dipcursed(int prm_1078, int)
{
    if (the_item_db[inv[prm_1078].id]->category == 57000)
    {
        if (inv[prm_1078].material == 35)
        {
            txt(lang(
                itemname(prm_1078) + u8"は腐ってしまった…"s,
                ""s + itemname(prm_1078) + u8" rots."s));
            inv[prm_1078].param3 = -1;
            inv[prm_1078].image = 336;
            cell_refresh(inv[prm_1078].position.x, inv[prm_1078].position.y);
            return;
        }
        else
        {
            txt(lang(
                itemname(prm_1078) + u8"に変化はない。"s,
                ""s + itemname(prm_1078) + u8" remains unchanged."s));
            return;
        }
    }
    if (the_item_db[inv[prm_1078].id]->category < 50000)
    {
        --inv[prm_1078].enhancement;
        txt(lang(
            itemname(prm_1078) + u8"は錆びてしまった…"s,
            ""s + itemname(prm_1078) + u8" rusts."s));
        if (inv_getowner(prm_1078) != -1)
        {
            chara_refresh(inv_getowner(prm_1078));
        }
        return;
    }
    txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
    return;
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
        if (cdata_body_part(rc, i) == 0)
        {
            rtval(1) = i + 100;
        }
    }
    if (rtval(1) == -1)
    {
        return -1;
    }
    for (int cnt = 100; cnt < 130; ++cnt)
    {
        f = cdata_body_part(tc, cnt) / 10000;
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
            if (cdata_body_part(rc, i) == 0)
            {
                continue;
            }
            if (cdata_body_part(rc, i) / 10000 == rtval)
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
        ++dblist(0, cdata_body_part(tc, i) / 10000);
    }
    for (int cnt = 0; cnt < 25; ++cnt)
    {
        rtval = rnd(15) + 1;
        f = 0;
        for (int i = 0; i < 30; ++i)
        {
            if (cdata_body_part(rc, i) / 10000 == rtval)
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



turn_result_t do_plant()
{
    screenupdate = -1;
    update_screen();
    if (mdata(6) == 1 || mdata(6) == 3 || mdata(6) == 2)
    {
        txt(lang(
            u8"この場所には埋められない。"s, u8"You can't plant it here."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (map(cdata[cc].position.x, cdata[cc].position.y, 6) != 0)
    {
        txt(lang(
            u8"この場所には埋められない。"s, u8"You can't plant it here."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    int val0;
    if (chipm(0, map(cdata[0].position.x, cdata[0].position.y, 0)) == 2)
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
        s = u8"畑に"s;
    }
    else
    {
        s = "";
    }
    s += lang(
        ""s + itemname(ci, 1) + u8"を埋めた。"s,
        u8"You plant "s + itemname(ci, 1));
    txt(s);
    snd(55);
    removeitem(ci, 1);
    cell_featset(
        cdata[cc].position.x,
        cdata[cc].position.y,
        tile_plant,
        29,
        inv[ci].material,
        feat(3));
    skillexp(180, 0, 300);
    return turn_result_t::turn_end;
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
    return;
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
        if (gdata_weather < 3)
        {
            p = p * 2;
        }
    }
    if (sdata(180, 0) < rnd(p + 1) || rnd(20) == 0)
    {
        feat(3) += 50;
    }
    return;
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
    if (gdata_weather < 3)
    {
        p = p * 4 / 3;
    }
    if (sdata(180, 0) < rnd(p + 1) || rnd(5) == 0 || feat(2) == 40)
    {
        map(cdata[0].position.x, cdata[0].position.y, 6) = 0;
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
    txtef(2);
    txt(lang(u8"新しい芽が息吹いている！"s, u8"A new plant grows!"s));
    return;
}



void label_2236()
{
    skillexp(180, 0, 75);
    snd(55);
    flt(sdata(180, 0) / 2 + 15, 2);
    dbid = 0;
    if (feat(2) == 39)
    {
        flttypemajor = fsetplantunknown(rnd(length(fsetplantunknown)));
        if (rnd(100) == 0)
        {
            dbid = 559;
        }
    }
    if (feat(2) == 40 || (feat(2) == 39 && rnd(50) == 0))
    {
        flttypemajor = fsetplantartifact(rnd(length(fsetplantartifact)));
        fixlv = 4;
        autosave = 1 * (gdata_current_map != 35);
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
    txt(lang(
        itemname(ci, 1) + u8"を収穫した。"s,
        u8"You harvest "s + itemname(ci, 1) + u8"."s));
    item_stack(0, ci, 1);
    return;
}



void initialize_economy()
{
    elona_vector1<int> bkdata;
    if (initeco)
    {
        gdata(815) = 15;
    }
    bkdata(0) = gdata_current_map;
    bkdata(1) = gdata_current_dungeon_level;
    bkdata(2) = cdata[0].position.x;
    bkdata(3) = cdata[0].position.y;
    snd(44);
    save_game();
    mode = 11;
    cdata[0].position.x = 0;
    cdata[0].position.y = 0;
    scx = cdata[0].position.x;
    scy = cdata[0].position.y;
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        if (adata(16, cnt) == 0)
        {
            continue;
        }
        if (adata(28, cnt) == 0)
        {
            continue;
        }
        gdata_current_map = adata(16, cnt);
        gdata_current_dungeon_level = 1;
        if (gdata_current_map != bkdata(0)
            || gdata_current_dungeon_level != bkdata(1))
        {
            initialize_map();
        }
        p = adata(28, cnt);
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
    gdata_current_map = bkdata(0);
    gdata_current_dungeon_level = bkdata(1);
    cdata[0].position.x = bkdata(2);
    cdata[0].position.y = bkdata(3);
    gdata(79) = 1;
    mode = 3;
    mapsubroutine = 1;
    initialize_map();
    initeco = 0;
    msgtemp = "";
    return;
}



int new_ally_joins()
{
    f = chara_get_free_slot_ally();
    if (f == 0)
    {
        txt(lang(
            u8"仲間の最大数に達しているため、仲間にできなかった…"s,
            u8"Your party is already full. You can't invite someone anymore."s));
        return -1;
    }
    int stat = chara_relocate(rc, f);
    oc = stat;
    cdata[rc].relationship = 10;
    cdata[rc].original_relationship = 10;
    cdata[rc].character_role = 0;
    cdata[rc].is_quest_target() = false;
    cdata[rc].does_not_search_enemy() = false;
    cdata[rc].is_hung_on_sand_bag() = false;
    cdata[rc].is_temporary() = false;
    cdata[rc].only_christmas() = false;
    snd(64);
    txtef(5);
    txt(lang(
        cdatan(0, rc) + u8"が仲間に加わった！"s,
        cdatan(0, rc) + u8" join"s + _s(rc) + u8" your party!"s));
    return 1;
}



void do_play_scene()
{
    int scidx = 0;
    int scidxtop = 0;
    int val0{};
    if (gdata_played_scene < sceneid)
    {
        gdata_played_scene = sceneid;
    }
    if (config::instance().story == 0 || (en == 1 && sceneid != 0))
    {
        return;
    }
    scene_cut = 0;
    msgtempprev = msgtemp;
    scenemode = 1;
    SDIM4(actor, 20, 3, 10);
    std::string file = u8"void"s;
    y1 = 60;
    y2 = windowh - 60;
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{lang((filesystem::dir::data() / u8"scene1.hsp"s).native(),
                              (filesystem::dir::data() / u8"scene2.hsp"s).native()),
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
        label_2685();
        return;
    }
    scidx += s(0).size();
label_2681:
    int a{};
    stick(a, 128);
    if (a == 128)
    {
        scene_cut = 1;
    }
    if (scene_cut == 1)
    {
        label_2685();
        return;
    }
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{lang((filesystem::dir::data() / u8"scene1.hsp"s).native(),
                              (filesystem::dir::data() / u8"scene2.hsp"s).native()),
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
        label_2685();
        return;
    }
    p(2) = instr(buff, scidx, u8"}"s) + scidx + 1;
    if (p(2) == -1)
    {
        label_2685();
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
        boxf();
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
            gmode(4, -1, -1, cnt * 15);
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
        label_2685();
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
        auto music = -1;
        if (s(1) == u8"mcUnrest2"s)
        {
            music = 84;
        }
        if (s(1) == u8"mcTown1"s)
        {
            music = 51;
        }
        if (s(1) == u8"mcMemory"s)
        {
            music = 89;
        }
        if (s(1) == u8"mcIntro"s)
        {
            music = 90;
        }
        if (music == -1)
        {
            musicfile(91) = s(1);
            play_music(91);
        }
        else
        {
            play_music(music);
        }
        goto label_2682_internal;
    }
    if (s == u8"{se}"s)
    {
        sndload(filesystem::dir::sound() / s(1), 28);
        snd(28);
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
    gzoom(4, 0, 0, 640, 480, windoww, y2 - y1);
    gmode(2);
    boxf(0, 0, windoww, y1, {5, 5, 5});
    boxf(0, y2, windoww, windowh, {5, 5, 5});
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
        dx = 80 + s(0).size() * 8;
        if (dx < 180)
        {
            dx = 0;
        }
        pos(windoww / 2, y + 4);
        gmode(6, 344, 72, 70);
        grotate(3, 456, 144, 0, dx, 72);
    }
    x = 40;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        y = y1 + 28 + (9 - noteinfo() / 2 + cnt) * 20;
        noteget(s, cnt);
        x = windoww / 2 - strlen_u(s(0)) * 4;
        color(10, 10, 10);
        pos(x, y);
        bmes(s, 240, 240, 240);
        color(0, 0, 0);
    }
    gsel(0);
    for (int cnt = 1; cnt < 16; ++cnt)
    {
        await(30);
        stick(a, 128);
        if (a == 128)
        {
            scene_cut = 1;
        }
        gmode(4, -1, -1, cnt * 16);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    x_at_txtfunc = windoww - 120;
    y_at_txtfunc = windowh - 60;
    anime_halt();
    boxf(0, 0, windoww, y1, {5, 5, 5});
    boxf(0, y2, windoww, windowh, {5, 5, 5});
    goto label_2681;
}



void label_2685()
{
    gsel(4);
    boxf();
    gsel(0);
    animation_fade_in();
    scenemode = 0;
    msgtemp = msgtempprev;
    msgtempprev = "";
    return;
}



void weather_changes_by_location()
{
    if (gdata_weather == 2)
    {
        if (gdata_pc_home_x < 65 && gdata_pc_home_y > 10)
        {
            gdata_weather = 3;
            envonly = 1;
            play_music();
            gdata_hours_until_weather_changes += 3;
            txt(lang(u8"天候が変わった。"s, u8"The weather changes."s));
        }
    }
    if (gdata_weather == 4 || gdata_weather == 3)
    {
        if (gdata_pc_home_x > 65 || gdata_pc_home_y < 10)
        {
            gdata_weather = 2;
            envonly = 1;
            play_music();
            gdata_hours_until_weather_changes += 3;
            txt(lang(u8"天候が変わった。"s, u8"The weather changes."s));
        }
    }
    return;
}



void weather_changes()
{
    if (adata(16, gdata_current_map) == 101)
    {
        update_museum();
    }
    if (gdata_current_map == 7)
    {
        calc_home_rank();
    }
    if (mdata(6) == 1)
    {
        gdata_pc_home_x = cdata[0].position.x;
        gdata_pc_home_y = cdata[0].position.y;
    }
    --gdata_hours_until_weather_changes;
    weather_changes_by_location();
    if (gdata_hours_until_weather_changes < 0)
    {
        gdata_hours_until_weather_changes = rnd(22) + 2;
        p = gdata_weather;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (gdata_month % 3 == 0)
            {
                if (gdata_day >= 1 && gdata_day <= 10)
                {
                    if (gdata_last_etherwind_month != gdata_month)
                    {
                        if (rnd(15) < gdata_day + 5)
                        {
                            gdata_weather = 1;
                            txtef(3);
                            txt(lang(
                                u8"エーテルの風が吹き始めた。すぐに避難しなくては。"s,
                                u8"Ether Wind starts to blow. You need to find a shelter!"s));
                            gdata_last_etherwind_month = gdata_month;
                            gdata_hours_until_weather_changes = rnd(24) + 24;
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
                        gdata_weather = 3;
                        txt(lang(
                            u8"あなたは雨雲を引き寄せた。"s,
                            u8"You draw a rain cloud."s));
                        break;
                    }
                }
                if (gdata_pc_home_x > 65 || gdata_pc_home_y < 10)
                {
                    if (rnd(2) == 0)
                    {
                        gdata_weather = 2;
                        txt(lang(
                            u8"雪が降ってきた。"s, u8"It starts to snow."s));
                        break;
                    }
                }
                else
                {
                    if (rnd(10) == 0)
                    {
                        gdata_weather = 3;
                        txt(lang(
                            u8"雨が降り出した。"s, u8"It starts to rain."s));
                        break;
                    }
                    if (rnd(40) == 0)
                    {
                        gdata_weather = 4;
                        txt(lang(
                            u8"突然どしゃぶりになった。"s,
                            u8"Suddenly, rain begins to pour down from the sky."s));
                        break;
                    }
                    if (rnd(60) == 0)
                    {
                        gdata_weather = 2;
                        txt(lang(
                            u8"雪が降ってきた。"s, u8"It starts to snow."s));
                        break;
                    }
                }
            }
            if (p == 3)
            {
                if (rnd(4) == 0)
                {
                    gdata_weather = 0;
                    txt(lang(u8"雨は止んだ。"s, u8"It stops raining."s));
                    break;
                }
                if (rnd(15) == 0)
                {
                    gdata_weather = 4;
                    txt(lang(
                        u8"雨が本格的に降り出した。"s,
                        u8"The rain becomes heavier."s));
                    break;
                }
            }
            if (p == 4)
            {
                if (rnd(3) == 0)
                {
                    gdata_weather = 3;
                    txt(lang(
                        u8"雨は小降りになった。"s,
                        u8"The rain becomes lighter."s));
                    break;
                }
            }
            if (p == 1)
            {
                if (rnd(2) == 0)
                {
                    gdata_weather = 0;
                    txt(lang(
                        u8"エーテルの風は止んだ。"s,
                        u8"The Ether Wind dissipates."s));
                    break;
                }
            }
            if (p == 2)
            {
                if (rnd(3) == 0)
                {
                    gdata_weather = 0;
                    txt(lang(u8"雪は止んだ。"s, u8"It stops raining."s));
                    break;
                }
            }
        }
        if (gdata_weather == 4)
        {
            if (config::instance().extrahelp)
            {
                if (gdata(211) == 0)
                {
                    if (mode == 0)
                    {
                        if (cdata[0].continuous_action_turn == 0)
                        {
                            gdata(211) = 1;
                            ghelp = 11;
                            show_ex_help();
                        }
                    }
                }
            }
        }
        if (gdata_weather == 2)
        {
            if (config::instance().extrahelp)
            {
                if (gdata(212) == 0)
                {
                    if (mode == 0)
                    {
                        if (cdata[0].continuous_action_turn == 0)
                        {
                            gdata(212) = 1;
                            ghelp = 12;
                            show_ex_help();
                        }
                    }
                }
            }
        }
        if (gdata_weather == 1)
        {
            if (config::instance().extrahelp)
            {
                if (gdata(213) == 0)
                {
                    if (mode == 0)
                    {
                        if (cdata[0].continuous_action_turn == 0)
                        {
                            gdata(213) = 1;
                            ghelp = 13;
                            show_ex_help();
                        }
                    }
                }
            }
        }
        if (p != gdata_weather)
        {
            envonly = 1;
            play_music();
        }
    }
    label_1746();
    label_2662();
    food_gets_rotten();
    if (mdata(6) == 1)
    {
        if (rnd(3) == 0)
        {
            ++gdata_continuous_active_hours;
        }
        if (rnd(15) == 0)
        {
            if (mode == 0)
            {
                txt(lang(u8"仮眠をとった。"s, u8"You take a nap."s));
                gdata_continuous_active_hours -= 3;
                if (gdata_continuous_active_hours < 0)
                {
                    gdata_continuous_active_hours = 0;
                }
            }
        }
    }
    else if (gdata_current_map != 30)
    {
        ++gdata_continuous_active_hours;
    }
    if (gdata_hour == 6)
    {
        txtef(5);
        txt(lang(u8"夜が明けた。"s, u8"Day breaks."s));
    }
    if (gdata_continuous_active_hours >= 15)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(209) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(209) = 1;
                        ghelp = 9;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (cdata[0].nutrition < 5000)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(210) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(210) = 1;
                        ghelp = 10;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (gdata_hour >= 24)
    {
        if (gdata_number_of_waiting_guests < 3)
        {
            if (rnd(8 + gdata_number_of_waiting_guests * 5) == 0)
            {
                ++gdata_number_of_waiting_guests;
            }
        }
        txtef(5);
        txt(lang(
            u8"一日が終わり、日付が変わった。"s,
            u8"A day passes and a new day begins."s));
        update_shop_and_report();
        for (int cnt = 0; cnt < 9; ++cnt)
        {
            p = 120 + cnt;
            if (gdata(p) >= 10000)
            {
                gdata(p) = 10000;
                continue;
            }
            if (cnt == 3 || cnt == 4 || cnt == 5 || cnt == 8)
            {
                continue;
            }
            --gdata(140 + cnt);
            if (gdata(140 + cnt) <= 0)
            {
                modrank(cnt, (gdata(p) / 12 + 100) * -1);
                gdata(140 + cnt) = ranknorma(cnt);
            }
        }
        snd(74);
        event_add(10);
        gdata_play_days += gdata_hour / 24;
        gdata_day += gdata_hour / 24;
        gdata_hour = gdata_hour % 24;
        if (gdata_day >= 31)
        {
            ++gdata_month;
            gdata_day = gdata_day - 30;
            if (gdata_month % 2 == 0)
            {
                ++gdata_holy_well_count;
            }
        }
        if (gdata_month >= 13)
        {
            ++gdata_year;
            gdata_month = 1;
            gdata_last_month_when_trainer_visited = 0;
            gdata_wish_count = clamp(gdata_wish_count - 1, 0, 10);
            gdata_lost_wallet_count =
                clamp(gdata_lost_wallet_count - 1, 0, 999999);
        }
        if (gdata_day == 1 || gdata_day == 15)
        {
            supply_income();
        }
        if (gdata_pael_and_her_mom == 1 || gdata_pael_and_her_mom == 3
            || gdata_pael_and_her_mom == 5 || gdata_pael_and_her_mom == 7
            || gdata_pael_and_her_mom == 9)
        {
            if (adata(16, gdata_current_map) != 33)
            {
                if (rnd(20) == 0)
                {
                    ++gdata_pael_and_her_mom;
                    snd(44);
                    txtef(2);
                    txt(lang(
                        u8"ジャーナルが更新された。"s,
                        u8"Your journal has been updated."s));
                }
            }
        }
    }
    if (mode == 0)
    {
        if (mdata(6) == 1)
        {
            if (rnd(40) == 0)
            {
                --cdata[0].piety_point;
            }
            cdata[0].praying_point += 4;
        }
        else
        {
            if (rnd(5) == 0)
            {
                --cdata[0].piety_point;
            }
            cdata[0].praying_point += 32;
        }
    }
    if (cdata[0].piety_point < 0)
    {
        cdata[0].piety_point = 0;
    }
    if (cdata[0].continuous_action_turn != 0)
    {
        if (cdata[0].continuous_action_id != 3)
        {
            update_screen();
        }
    }
    if (gdata_current_map != 30)
    {
        if (gdata_current_map != 41)
        {
            proc_random_event();
        }
    }
}



optional<turn_result_t> check_angband()
{
    if (gdata_angband_flag == -1 || mdata(6) == 1)
        return none;

    switch (gdata_angband_flag)
    {
    case 0:
        if (key == u8"Q"s)
        {
            txt(lang(u8"え…", u8"What..."));
            ++gdata_angband_flag;
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        break;
    case 1:
        if (key == u8"y"s)
        {
            txt(lang(u8"まさか…", u8"No...no..."));
            ++gdata_angband_flag;
            update_screen();
            return turn_result_t::pc_turn_user_error;
        }
        break;
    case 2:
        if (key == u8"@"s)
        {
            txt(lang(u8"うわぁぁぁ！！", u8"Ahhhhh!!"));
            for (int i = 0; i < 10; ++i)
            {
                flt();
                chara_create(-1, 37, cdata[0].position.x, cdata[0].position.y);
            }
            gdata_angband_flag = -1;
            update_screen();
            return turn_result_t::turn_end;
        }
        break;
    default: break;
    }

    gdata_angband_flag = 0;
    return none;
}



void conquer_lesimas()
{
    std::string wincomment;
    snd(51);
    play_music(-1);
    txt(lang(
        u8"信じられない！あなたはネフィアの迷宮「レシマス」を制覇した！"s,
        u8"Unbelievable! You conquered Lesimas!"s));
    update_screen();
    const auto win_words = txtsetwinword(3);
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        ELONA_APPEND_PROMPT(win_words[cnt], key_select(cnt), ""s + promptmax);
    }
    rtval = show_prompt(promptx, prompty, 310, show_prompt_type::cannot_cancel);
    wincomment = ""s + promptl(0, rtval);
    mode = 7;
    screenupdate = -1;
    update_screen();
    if (jp)
    {
        msg_clear();
        txt(u8"「お前がここに辿り着くことは」台座から、何かの声が聞こえる。"s);
        flt();
        chara_create(-1, 23, cdata[0].position.x, cdata[0].position.y);
        play_music(69);
        msg_halt();
        msg_clear();
        txt(u8"「決まっていたことなのだ…遅かれ早かれな」"s);
        txt(u8"部屋の空気が突然緊張し、あなたの前に端麗な青年が現れた。"s);
        txt(u8"「我々からすれば、複雑性の一面に過ぎないが、人間は運命とでも呼ぶのだろう？」"s);
        msg_halt();
        msg_clear();
        txt(u8"あなたは懸命に脚の震えを抑えようとしたが、難しかった。"s);
        txt(u8"華奢に見える幼顔の男の影は、人のものではない。"s);
        txt(u8"あどけない瞳の奥に、あなたは底知れない力と闇を感じた。"s);
        msg_halt();
        msg_clear();
        txt(u8"「ネフィアの永遠の盟約に基づき」青年は台座の横の死体を指し、皮肉な微笑を送った。"s);
        txt(u8"「この哀れな老人が守っていたものは、今からお前のものだ」"s);
        msg_halt();
        msg_clear();
        txt(u8"あなたは、台座の上に置かれている絢爛な装飾の本を、いぶかしげに眺めた。"s);
        msg_halt();
        tc = chara_find(23);
        talk_to_npc();
        msg_clear();
        txt(u8"青年は悪戯っぽくニヤリと笑い、壁に寄りかかった。"s);
        msg_halt();
        msg_clear();
        chara_vanquish(chara_find(23));
        screenupdate = -1;
        update_screen();
        txt(u8"…どれくらい時間がたっただろう。氷の瞳の男は、いつの間にか姿を消していた。あなたは不安を振り払い、ゆっくりと本に手を伸ばした…"s);
        msg_halt();
    }
    mode = 0;
    play_music(71);
    label_1442();
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"void.bmp", 1);
    pos(0, 0);
    gzoom(4, 0, 0, 640, 480, windoww, windowh);
    gsel(0);
    animation_fade_in();
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"g1.bmp", 1);
    gsel(0);
    s = lang(
        ""s + cdatan(1, 0) + cdatan(0, 0)
            + u8"に祝福あれ！あなたは遂にレシマスの秘宝を手にいれた！"s,
        u8"Blessing to "s + cdatan(0, 0) + u8", "s + cdatan(1, 0)
            + u8"! You've finally acquired the codex!"s);
    draw_caption();
    s(0) = lang(u8"*勝利*"s, u8"*Win*"s);
    s(1) = ""s + strhint3;
    windowshadow = 1;
    ww = 680;
    wh = 488;
    pagesize = 0;
    display_window(windoww / 2 - ww / 2, windowh / 2 - wh / 2, ww, wh);
    cmbg = 0;
    x = ww / 3 - 20;
    y = wh - 140;
    gmode(4, 180, 300, 250);
    pos(wx + ww - 120, wy + wh / 2);
    grotate(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
    gmode(2);
    display_topic(lang(u8"制覇までの軌跡"s, u8"Trace"s), wx + 28, wy + 40);
    font(14 - en * 2);
    pos(wx + 40, wy + 76);
    mes(lang(
        ""s + 517 + u8"年"s + 8 + u8"月"s + 12
            + u8"日に、あなたはノースティリスに到着した。"s,
        u8"In the year "s + 517 + u8", "s + 12 + u8"/"s + 8
            + u8", you arrived at North Tyris."s));
    pos(wx + 40, wy + 116);
    mes(lang(
        u8"最深で"s + gdata_deepest_dungeon_level + u8"階相当まで到達し、"s
            + gdata_kill_count + u8"匹の敵を殺して、"s,
        u8"You've killed "s + gdata_kill_count
            + u8" creatures and reached\nmaximum of "s
            + cnvrank(gdata_deepest_dungeon_level) + u8" level of dungeons."s));
    pos(wx + 40, wy + 146);
    mes(lang(
        u8"現在"s + calcscore() + u8"点のスコアを叩き出している。"s,
        u8"Your score is "s + calcscore() + u8" points now."s));
    pos(wx + 40, wy + 186);
    mes(lang(
        ""s + gdata_year + u8"年"s + gdata_month + u8"月"s + gdata_day
            + u8"日にレシマスを制覇して、"s,
        u8"In the year "s + gdata_year + u8", "s + gdata_day + u8"/"s
            + gdata_month + u8", you conquered Lesimas."s));
    pos(wx + 40, wy + 206);
    mes(lang(
        u8"あなたは「"s + wincomment + u8"」とコメントした。"s,
        u8"Upon killing Zeome, you said, \""s + wincomment + u8"\""));
    pos(wx + 40, wy + 246);
    mes(lang(
        u8"…あなたの旅はまだ終わらない。"s, u8"Your journey continues..."s));
    redraw();
    key_list = key_enter;
    keyrange = 0;

    while (1)
    {
        await(config::instance().wait1);
        key_check();
        cursor_check();
        if (key == key_cancel)
        {
            play_the_last_scene_again();
            return;
        }
    }
}



void play_the_last_scene_again()
{
    update_entire_screen();
    txt(lang(
        u8"達成のシーンをもう一度再現する？"s,
        u8"You want to watch this event again?"s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    if (rtval == 0)
    {
        conquer_lesimas();
        return;
    }
    gdata_main_quest_flag = 180;
    update_screen();
    return;
}



turn_result_t pc_died()
{
    cc = 0;
    snd(50);
    screenupdate = -1;
    update_screen();
    if (gdata_executing_immediate_quest_type)
    {
        return quest_pc_died_during_immediate_quest();
    }
    txt(lang(u8"さようなら… "s, u8"Good bye... "s));
    txt(lang(u8"遺言は？"s, u8"You leave a dying message."s));
    inputlog = "";
    input_text_dialog((windoww - 310) / 2 + inf_screenx, winposy(90), 16);
    if (inputlog == ""s)
    {
        txtsetlastword();
    }
    else
    {
        lastword = lang(u8"「"s, u8"\""s) + inputlog + lang(u8"」"s, u8"\""s);
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
    s = cdatan(1, cc) + u8" "s + cdatan(0, cc) + lang(""s, u8" "s) + lastword;
    lenfix(s, 60);
    s += lang(
        ""s + gdata_year + u8"年"s + gdata_month + u8"月"s + gdata_day
            + u8"日"s,
        ""s + gdata_year + u8"/"s + gdata_month + u8"/"s + gdata_day);
    noteadd(""s, 0);
    noteadd(s, 1);
    s = lang(
        mdatan(0) + u8"で"s + ndeathcause,
        cnven(ndeathcause) + u8" in "s + mdatan(0) + u8"."s);
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
        noteadd(""s + cnvrank((cnt + 1)) + lang(u8"位"s, ""s), cnt * 4, 1);
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
    s = lang(
        u8"あともう少しで埋葬される…"s, u8"You are about to be buried..."s);
    draw_caption();
    ELONA_APPEND_PROMPT(
        lang(u8"這い上がる"s, u8"Crawl up"s), u8"a"s, ""s + promptmax);
    ELONA_APPEND_PROMPT(
        lang(u8"埋まる"s, u8"Lie on your back"s), u8"b"s, ""s + promptmax);
    rtval = show_prompt(promptx, 100, 240);
    if (rtval == 1)
    {
        show_game_score_ranking();
        s = lang(
            u8"あなたは埋められた。さようなら…（キーを押すと終了します）"s,
            u8"You have been buried. Bye...(Hit any key to exit)"s);
        draw_caption();
        redraw();
        press();
        return turn_result_t::finish_elona;
    }
    s = u8"dead"s
        + lang(
              (cdatan(1, 0) + cdatan(0, 0) + u8"は"s + mdatan(0) + u8"で"s
               + ndeathcause + lastword),
              (cdatan(1, 0) + u8" "s + cdatan(0, 0) + u8" "s + ndeathcause
               + u8" in "s + mdatan(0) + u8" "s + lastword));
    if (gdata_wizard == 0)
    {
        net_send(s);
    }
    screenupdate = -1;
    update_entire_screen();
    levelexitby = 3;
    return turn_result_t::exit_map;
}



void show_game_score_ranking()
{
    notesel(buff);
    gmode(0);
    pos(0, 0);
    gzoom(4, 0, 0, 800, 600, windoww, windowh);
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
            s = u8" "s + cnvrank((cnt + 1)) + lang(u8"位"s, ""s);
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
        mes(""s + s + lang(u8"点"s, ""s));
        p = elona::stoi(s(1)) % 1000;
        chara_preparepic(p);
        pos(x - 22, y + 12);
        gmode(2, chipc(2, p), chipc(3, p));
        grotate(
            5,
            0,
            960,
            0,
            chipc(2, p) / (1 + (chipc(3, p) > inf_tiles)),
            inf_tiles);
        color(0, 0, 0);
    }
    color(0, 0, 0);
    return;
}


} // namespace elona
