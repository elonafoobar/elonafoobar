#include "character.hpp"
#include "elona.hpp"
#include "variables.hpp"


namespace elona
{


elona_vector1<std::string> _tone_at_m34;
int p_at_m34 = 0;
int talkref = 0;
std::string s_at_m41;
elona_vector1<int> p_at_m41;


std::string cnvrank(int prm_248)
{
    if (jp)
    {
        return ""s + prm_248;
    }
    if (prm_248 % 10 == 1)
    {
        if (prm_248 != 11)
        {
            return ""s + prm_248 + u8"st"s;
        }
    }
    if (prm_248 % 10 == 2)
    {
        if (prm_248 != 12)
        {
            return ""s + prm_248 + u8"nd"s;
        }
    }
    if (prm_248 % 10 == 3)
    {
        if (prm_248 != 13)
        {
            return ""s + prm_248 + u8"rd"s;
        }
    }
    return ""s + prm_248 + u8"th"s;
}



std::string cnvtalk(const std::string& prm_249)
{
    return u8"\""s + prm_249 + u8"\" "s;
}



std::string cnvarticle(const std::string& prm_250)
{
    if (jp)
    {
        return prm_250;
    }
    return u8"["s + prm_250 + u8"]"s;
}



std::string cnvitemname(int prm_251)
{
    if (jp)
    {
        return ioriginalnameref(prm_251);
    }
    if (ioriginalnameref2(prm_251) == ""s)
    {
        return ioriginalnameref(prm_251);
    }
    return ioriginalnameref2(prm_251) + u8" of "s + ioriginalnameref(prm_251);
}



std::string cnven(const std::string& prm_252)
{
    std::string s_at_m1;
    int p_at_m1 = 0;
    if (jp)
    {
        return prm_252;
    }
    s_at_m1 = prm_252;
    p_at_m1 = peek(s_at_m1, 0);
    if (p_at_m1 == 42)
    {
        p_at_m1 = peek(s_at_m1, 1);
        if (p_at_m1 >= 97)
        {
            if (p_at_m1 <= 122)
            {
                poke(s_at_m1, 1, p_at_m1 - 32);
            }
        }
    }
    else if (p_at_m1 >= 97)
    {
        if (p_at_m1 <= 122)
        {
            poke(s_at_m1, 0, p_at_m1 - 32);
        }
    }
    return s_at_m1;
}



std::string cnvfix(int prm_339)
{
    if (prm_339 >= 0)
    {
        return u8"+"s + prm_339;
    }
    else
    {
        return ""s + prm_339;
    }
}



std::string cnvdate(int prm_342, int prm_343)
{
    int p_at_m27 = 0;
    int hour_at_m27 = 0;
    int day_at_m27 = 0;
    int month_at_m27 = 0;
    int year_at_m27 = 0;
    std::string s_at_m27;
    p_at_m27 = prm_342;
    hour_at_m27 = prm_342 % 24;
    day_at_m27 = prm_342 / 24 % 30;
    if (day_at_m27 == 0)
    {
        day_at_m27 = 30;
        p_at_m27 -= 720;
    }
    month_at_m27 = p_at_m27 / 24 / 30 % 12;
    if (month_at_m27 == 0)
    {
        month_at_m27 = 12;
        p_at_m27 -= 8640;
    }
    year_at_m27 = p_at_m27 / 24 / 30 / 12;
    if (jp)
    {
        s_at_m27 = ""s + year_at_m27 + u8"年"s + month_at_m27 + u8"月"s
            + day_at_m27 + u8"日"s;
        if (prm_343 == 1)
        {
            s_at_m27 += ""s + hour_at_m27 + u8"時"s;
        }
    }
    else
    {
        s_at_m27 = ""s + year_at_m27 + u8" "s + month_at_m27 + u8"/"s
            + day_at_m27 + u8" "s;
        if (prm_343 == 1)
        {
            s_at_m27 += ""s + hour_at_m27 + u8"h"s;
        }
    }
    return s_at_m27;
}



std::string cnvplaytime(int prm_344)
{
    return ""s + prm_344 / 60 / 60 + lang(u8"時間"s, u8":"s) + prm_344 / 60 % 60
        + lang(u8"分"s, u8":"s) + prm_344 % 60 + lang(u8"秒"s, u8" Sec"s);
}



std::string sncnv(std::string& prm_349)
{
    return strmid(prm_349, 0, instr(prm_349, 0, u8" "s)) + u8" "s;
}



void sngeneral(std::string& prm_350)
{
    prm_350 =
        lang(u8"雑貨屋の"s + prm_350, sncnv(prm_350) + u8"the general vendor"s);
    return;
}



void sninn(std::string& prm_351)
{
    prm_351 = lang(u8"宿屋の"s + prm_351, sncnv(prm_351) + u8"the Innkeeper"s);
    return;
}



void sntrade(std::string& prm_352)
{
    prm_352 = lang(u8"交易店の"s + prm_352, sncnv(prm_352) + u8"the trader"s);
    return;
}



void sngoods(std::string& prm_353)
{
    prm_353 =
        lang(u8"何でも屋の"s + prm_353, sncnv(prm_353) + u8"the goods vendor"s);
    return;
}



void snbakery(std::string& prm_354)
{
    prm_354 = lang(u8"パン屋の"s + prm_354, sncnv(prm_354) + u8"the baker"s);
    return;
}



void snmagic(std::string& prm_355)
{
    prm_355 =
        lang(u8"魔法店の"s + prm_355, sncnv(prm_355) + u8"the magic vendor"s);
    return;
}



void snarmor(std::string& prm_356)
{
    prm_356 =
        lang(u8"武具店の"s + prm_356, sncnv(prm_356) + u8"the blacksmith"s);
    return;
}



void sntrainer(std::string& prm_357)
{
    prm_357 = lang(u8"ギルドの"s + prm_357, sncnv(prm_357) + u8"the trainer"s);
    return;
}



void snfish(std::string& prm_358)
{
    prm_358 = lang(u8"釣具店の"s + prm_358, sncnv(prm_358) + u8"the fisher"s);
    return;
}



void snblack(std::string& prm_359)
{
    prm_359 = lang(
        u8"ブラックマーケットの"s + prm_359,
        sncnv(prm_359) + u8"the blackmarket vendor"s);
    return;
}



void snfood(std::string& prm_360)
{
    prm_360 =
        lang(u8"食品店"s + prm_360, sncnv(prm_360) + u8"the food vendor"s);
    return;
}



void txtsetlastword()
{
    std::vector<std::string> last_words;
    range::copy(
        fileutil::read_by_line{fs::u8path(u8"./user")
                               / lang(u8"lastwords.txt", u8"lastwords-e.txt")},
        std::back_inserter(last_words));
    lastword = last_words[rnd(std::size(last_words))];
    // TODO: bug? rnd(noteinfo(0)) ?
    // noteget(lastword, rnd(noteinfo(0) + 1));
}



void txtsetwinword(int prm_361)
{
    {
        int cnt = 0;
        for (int cnt_end = cnt + (6); cnt < cnt_end; ++cnt)
        {
            i = rnd(cnt + 1);
            p(cnt) = p(i);
            p(i) = cnt;
        }
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (prm_361); cnt < cnt_end; ++cnt)
        {
            if (p(cnt) == 0)
            {
                s(cnt) = lang(u8"遂に…！"s, u8"Finally!"s);
            }
            if (p(cnt) == 1)
            {
                s(cnt) = lang(u8"当然の結果だ"s, u8"It's a matter of course."s);
            }
            if (p(cnt) == 2)
            {
                s(cnt) = lang(u8"おぉぉぉぉ！"s, u8"Woooooo!"s);
            }
            if (p(cnt) == 3)
            {
                s(cnt) = lang(u8"ふっ"s, u8"Heh."s);
            }
            if (p(cnt) == 4)
            {
                s(cnt) =
                    lang(u8"今日は眠れないな"s, u8"I can't sleep tonight."s);
            }
            if (p(cnt) == 5)
            {
                s(cnt) = lang(u8"またそんな冗談を"s, u8"You're kidding."s);
            }
        }
    }
    return;
}



void label_0140()
{
    SDIM4(mapnamerd, 20, 2, 5);
    mapnamerd(0, 0) = lang(u8"はじまりの"s, u8"Beginner's "s);
    mapnamerd(1, 0) = lang(u8"安全な"s, u8"Safe "s);
    mapnamerd(0, 1) = lang(u8"冒険者の"s, u8"Adventurer's"s);
    mapnamerd(1, 1) = lang(u8"時めきの"s, u8"Exciting "s);
    mapnamerd(0, 2) = lang(u8"迷いの"s, u8"Dangerous "s);
    mapnamerd(1, 2) = lang(u8"勇者の"s, u8"Servant's "s);
    mapnamerd(0, 3) = lang(u8"死の"s, u8"Fearful "s);
    mapnamerd(1, 3) = lang(u8"闇の"s, u8"Shadow "s);
    mapnamerd(0, 4) = lang(u8"不帰の"s, u8"King's "s);
    mapnamerd(1, 4) = lang(u8"混沌の"s, u8"Chaotic "s);
    return;
}



std::string maplevel(int)
{
    if (gdata_current_map == 7)
    {
        if (gdata_current_dungeon_level != 1)
        {
            if (gdata_current_dungeon_level > 0)
            {
                return u8"B."s + (gdata_current_dungeon_level - 1);
            }
            else
            {
                return u8"L."s + (gdata_current_dungeon_level - 2) * -1;
            }
        }
    }
    if (adata(0, gdata_current_map) != 3)
    {
        if (adata(16, gdata_current_map) == 3
            || adata(16, gdata_current_map) == 8
            || adata(16, gdata_current_map) == 13
            || (mdata(6) >= 20 && mdata(6) <= 23) == 1)
        {
            return ""s
                + cnvrank(
                       (gdata_current_dungeon_level
                        - adata(17, gdata_current_map) + 1))
                + lang(u8"層"s, ""s);
        }
    }
    return "";
}



std::string mapname(int prm_366, int prm_367)
{
    s(0) = "";
    s(1) = "";
    if (adata(16, prm_366) == 4)
    {
        s = lang(u8"ノースティリス"s, u8"North Tyris"s);
    }
    if (adata(16, prm_366) == 5)
    {
        s(0) = lang(u8"ヴェルニース"s, u8"Vernis"s);
        s(1) = lang(
            u8"ヴェルニースの街が見える。辺りは活気に満ちている。"s,
            u8"You see Vernis. The mining town is full of liveliness."s);
    }
    if (adata(16, prm_366) == 11)
    {
        s(0) = lang(u8"ポート・カプール"s, u8"Port Kapul"s);
        s(1) = lang(
            u8"ポート・カプールが見える。港は船で賑わっている。"s,
            u8"You see Port Kapul. The port is crowded with merchants."s);
    }
    if (adata(16, prm_366) == 12)
    {
        s(0) = lang(u8"ヨウィン"s, u8"Yowyn"s);
        s(1) = lang(
            u8"ヨウィンの村が見える。懐かしい土の匂いがする。"s,
            u8"You see a small town, Yowyn. You remember fondly the smell of the soil."s);
    }
    if (adata(16, prm_366) == 14)
    {
        s(0) = lang(u8"ダルフィ"s, u8"Derphy"s);
        s(1) = lang(
            u8"ダルフィの街がある。何やら危険な香りがする。"s,
            u8"You see the infamous rogue's den Derphy."s);
    }
    if (adata(16, prm_366) == 15)
    {
        s(0) = lang(u8"パルミア"s, u8"Palmia"s);
        s(1) = lang(
            u8"パルミアの都がある。都は高い壁に囲われている。"s,
            u8"You see the great city of Palmia. Entire city is surrounded by tall wall."s);
    }
    if (adata(16, prm_366) == 16)
    {
        s = lang(u8"灼熱の塔"s, u8"the Tower of Fire"s);
    }
    if (adata(16, prm_366) == 17)
    {
        s = lang(u8"死者の洞窟"s, u8" the crypt of the damned "s);
    }
    if (adata(16, prm_366) == 18)
    {
        s = lang(u8"古城"s, u8"the Ancient Castle"s);
    }
    if (adata(16, prm_366) == 7)
    {
        s(0) = lang(u8"わが家"s, u8"Your Home"s);
        s(1) = lang(u8"あなたの家だ。"s, u8"It's your sweet home."s);
    }
    if (adata(16, prm_366) == 3)
    {
        s(0) = lang(u8"レシマス"s, u8"Lesimas"s);
        s(1) = lang(
            u8"レシマスの洞窟がある。運命の鼓動を感じる。"s,
            u8"You see the dungeon of Lesimas. The wheel of fortune starts to turn."s);
    }
    if (adata(16, prm_366) == 42)
    {
        s(0) = lang(u8"すくつ"s, u8"the Void"s);
        s(1) = lang(u8"なんだこの場所は…？"s, u8"What is this place?"s);
    }
    if (adata(16, prm_366) == 2)
    {
        s = lang(u8"野外"s, u8"Wilderness"s);
    }
    if (adata(16, prm_366) == 10)
    {
        s(0) = lang(u8"ルミエスト墓所"s, u8"the graveyard"s);
        s(1) = lang(
            u8"墓所が見える。辺りは静寂に包まれている…"s,
            u8"You see the graveyard of Lumiest. It's slient. Very silent."s);
    }
    if (adata(16, prm_366) == 6)
    {
        s = lang(u8"闘技場"s, u8"Arena"s);
    }
    if (adata(16, prm_366) == 19)
    {
        s = lang(u8"竜窟"s, u8"the Dragon's Nest"s);
    }
    if (adata(16, prm_366) == 20)
    {
        s(0) = lang(u8"神々の休戦地"s, u8"the Truce Ground"s);
        s(1) = lang(
            u8"寺院がある。神聖な雰囲気がする。"s,
            u8"You see old shrines. Sacred air surrounds the ground."s);
    }
    if (adata(16, prm_366) == 21)
    {
        s(0) = lang(u8"アクリ・テオラ"s, u8"Cyber Dome"s);
        s(1) = lang(
            u8"何やら奇妙な建物がある。"s,
            u8"You see a very strange building."s);
    }
    if (adata(16, prm_366) == 22)
    {
        s(0) = lang(u8"混沌の城《獣》"s, u8"Fort of Chaos <Beast>"s);
        s(1) = lang(
            u8"不気味な城がある。絶対に入ってはいけない予感がする。(危険度は666階相当)"s,
            u8"You see an unearthly fort. Your inner voice wanrs you to not go there. (Approximate danger level: 666) "s);
    }
    if (adata(16, prm_366) == 23)
    {
        s(0) = lang(u8"混沌の城《機甲》"s, u8"Fort of Chaos <Machine>"s);
        s(1) = lang(
            u8"不気味な城がある。絶対に入ってはいけない予感がする。(危険度は666階相当)"s,
            u8"You see an unearthly fort. Your inner voice wanrs you to not go there. (Approximate danger level: 666) "s);
    }
    if (adata(16, prm_366) == 24)
    {
        s(0) = lang(u8"混沌の城《奇形》"s, u8"Fort of Chaos <Collapsed>"s);
        s(1) = lang(
            u8"不気味な城がある。絶対に入ってはいけない予感がする。(危険度は666階相当)"s,
            u8"You see an unearthly fort. Your inner voice wanrs you to not go there. (Approximate danger level: 666) "s);
    }
    if (adata(16, prm_366) == 40)
    {
        s = lang(u8"コロシアム"s, u8"Pet Arena"s);
    }
    if (adata(16, prm_366) == 101)
    {
        s = lang(u8"博物館"s, u8"My Museum"s);
    }
    if (adata(16, prm_366) == 102)
    {
        s = lang(u8"店"s, u8"Shop"s);
    }
    if (adata(16, prm_366) == 103)
    {
        s = lang(u8"畑"s, u8"Crop"s);
    }
    if (adata(16, prm_366) == 104)
    {
        s = lang(u8"倉庫"s, u8"Storage House"s);
    }
    if (adata(16, prm_366) == 31)
    {
        s = lang(u8"牧場"s, u8"Ranch"s);
    }
    if (adata(16, prm_366) == 30)
    {
        s = lang(u8"シェルター"s, u8"Shelter"s);
    }
    if (adata(16, prm_366) == 32)
    {
        s = lang(u8"パルミア大使館"s, u8"the Embassy"s);
    }
    if (adata(16, prm_366) == 9)
    {
        s = lang(u8"実験場"s, u8"Test Ground"s);
    }
    if (adata(16, prm_366) == 33)
    {
        s(0) = lang(u8"ノイエル"s, u8"Noyel"s);
        s(1) = lang(
            u8"ノイエルの村がある。子供たちの笑い声が聞こえる。"s,
            u8"You see Noyel. The laughters of children travel from the playground."s);
    }
    if (adata(16, prm_366) == 34)
    {
        s = lang(u8"工房ミラル・ガロク"s, u8"Miral and Garok's Workshop"s);
    }
    if (adata(16, prm_366) == 35)
    {
        s = lang(u8"ハウスドーム"s, u8"Show House"s);
    }
    if (adata(16, prm_366) == 25)
    {
        s = lang(u8"ラーナ"s, u8"Larna"s);
    }
    if (adata(16, prm_366) == 26)
    {
        s = lang(u8"山道"s, u8"the Mountain Pass"s);
    }
    if (adata(16, prm_366) == 27)
    {
        s = lang(u8"子犬の洞窟"s, u8"the Puppy Cave"s);
    }
    if (adata(16, prm_366) == 28)
    {
        s = lang(u8"イークの洞窟"s, u8"the Yeek's Nest"s);
    }
    if (adata(16, prm_366) == 29)
    {
        s = lang(u8"妹の館"s, u8"the mansion of younger sister"s);
    }
    if (adata(16, prm_366) == 36)
    {
        s(0) = lang(u8"ルミエスト"s, u8"Lumiest"s);
        s(1) = lang(
            u8"ルミエストの都が見える。水のせせらぎが聴こえる。"s,
            u8"You see Lumiest. Murmuring of water pleasantly echos."s);
    }
    if (adata(16, prm_366) == 37)
    {
        s = lang(u8"ピラミッド"s, u8"the Pyramid"s);
    }
    if (adata(16, prm_366) == 38)
    {
        s = lang(u8"ﾐﾉﾀｳﾛｽの巣"s, u8"the Minotaur's Nest"s);
    }
    if (adata(16, prm_366) == 41)
    {
        s(0) = lang(u8"牢獄"s, u8"Jail"s);
        s(1) = lang(
            u8"収容所がある。入り口は固く閉ざされている。"s,
            u8"You see a prison. The entrance is strictly closed."s);
    }
    if (adata(16, prm_366) == 43)
    {
        s = lang(u8"ノースティリス南関所"s, u8"North Tyris south border"s);
    }
    if (adata(16, prm_366) == 44)
    {
        s = lang(u8"サウスティリス"s, u8"South Tyris"s);
    }
    if (adata(16, prm_366) == 45)
    {
        s = lang(u8"サウスティリス北関所"s, u8"South Tyris north border"s);
    }
    if (adata(16, prm_366) == 46)
    {
        s = lang(u8"煙とパイプ亭"s, u8"The smoke and pipe"s);
    }
    if (adata(16, prm_366) == 47)
    {
        s = lang(u8"テストワールド"s, u8"Test World"s);
    }
    if (adata(16, prm_366) == 48)
    {
        s = lang(u8"テストワールド北関所"s, u8"Test World north border"s);
    }
    if (adata(16, prm_366) == 13)
    {
        if (gdata_executing_immediate_quest_type == 1001)
        {
            s = lang(u8"街近辺"s, u8"The outskirts"s);
        }
        if (gdata_executing_immediate_quest_type == 1010
            || gdata_executing_immediate_quest_type == 1008)
        {
            s = lang(u8"市街地"s, u8"Urban area"s);
        }
    }
    if (adata(16, prm_366) == 8)
    {
        s = mapnamerd(
            adata(5, prm_366),
            std::min(adata(17, prm_366) / 5, int(length2(mapnamerd) - 1)));
        if (adata(0, prm_366) == 20)
        {
            s += lang(u8"洞窟"s, u8"Dungeon"s);
        }
        if (adata(0, prm_366) == 22)
        {
            s += lang(u8"森"s, u8"Forest"s);
        }
        if (adata(0, prm_366) == 21)
        {
            s += lang(u8"塔"s, u8"Tower"s);
        }
        if (adata(0, prm_366) == 23)
        {
            s += lang(u8"砦"s, u8"Fort"s);
        }
    }
    if (prm_367 == 1)
    {
        if (adata(16, prm_366) == 29)
        {
            return "";
        }
        if (s(1) != ""s)
        {
            return s(1);
        }
        if (adata(0, prm_366) >= 20)
        {
            return lang(
                s + u8"への入り口がある(入り口の危険度は"s + adata(17, prm_366)
                    + u8"階相当)。"s,
                u8"You see an entrance leading to "s + s
                    + u8".(Approximate danger level: "s + adata(17, prm_366)
                    + u8") "s);
        }
        return lang(s + u8"がある。"s, u8"You see "s + s + u8"."s);
    }
    return s;
}



std::string txtbuilding(int prm_368, int prm_369)
{
    int p_at_m32 = 0;
    std::string s_at_m32;
    p_at_m32 = bddata(0, prm_368, prm_369);
    s_at_m32 = lang(
        bdrefn(p_at_m32) + u8"がある。"s, u8"You see "s + bdrefn(p_at_m32));
    return s_at_m32;
}



std::string txtskillchange(int prm_370, int prm_371, int prm_372)
{
    if (prm_370 == 2)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は生命力の上昇を感じた。"s,
                name(prm_372) + your(prm_372) + u8" life force increases."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は生命力の衰えを感じた。"s,
                name(prm_372) + your(prm_372) + u8" life force decreases."s);
        }
    }
    if (prm_370 == 3)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"はマナの向上を感じた。"s,
                name(prm_372) + your(prm_372) + u8" mana increases."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"はマナの衰えを感じた。"s,
                name(prm_372) + your(prm_372) + u8" mana decreases."s);
        }
    }
    if (prm_370 == 10)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"はより強くなった。"s,
                name(prm_372) + your(prm_372) + u8" muscles feel stronger."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は少し贅肉が増えたような気がした。"s,
                name(prm_372) + your(prm_372) + u8" muscles soften."s);
        }
    }
    if (prm_370 == 11)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は我慢することの快感を知った。"s,
                name(prm_372) + u8" begin"s + _s(prm_372)
                    + u8" to feel good when being hit hard."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は我慢ができなくなった。"s,
                name(prm_372) + u8" lose"s + _s(prm_372) + u8" patience."s);
        }
    }
    if (prm_370 == 12)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は器用になった。"s,
                name(prm_372) + u8" become"s + _s(prm_372) + u8" dexterous."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は不器用になった。"s,
                name(prm_372) + u8" become"s + _s(prm_372) + u8" clumsy."s);
        }
    }
    if (prm_370 == 13)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は世界をより身近に感じるようになった。"s,
                name(prm_372) + u8" feel"s + _s(prm_372)
                    + u8" more in touch with the world."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は感覚のずれを感じた。"s,
                name(prm_372) + u8" "s + is(prm_372)
                    + u8" getting out of touch with the world"s);
        }
    }
    if (prm_370 == 14)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は急に色々なことを学びたくなった。"s,
                name(prm_372) + u8" feel"s + _s(prm_372) + u8" studious."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"の学習意欲が低下した。"s,
                name(prm_372) + u8" lose"s + _s(prm_372) + u8" curiosity."s);
        }
    }
    if (prm_370 == 15)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"の意思は固くなった。"s,
                name(prm_372) + your(prm_372) + u8" will hardens."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は何でもすぐ諦める。"s,
                name(prm_372) + your(prm_372) + u8" will softens."s);
        }
    }
    if (prm_370 == 16)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は魔力の上昇を感じた。"s,
                name(prm_372) + your(prm_372) + u8" magic improves."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は魔力の衰えを感じた。"s,
                name(prm_372) + your(prm_372) + u8" magic degrades."s);
        }
    }
    if (prm_370 == 17)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は周囲の視線を心地よく感じる。"s,
                name(prm_372) + u8" enjoy"s + _s(prm_372) + u8" showing off "s
                    + his(prm_372) + u8" body."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は急に人前に出るのが嫌になった。"s,
                name(prm_372) + u8" start"s + _s(prm_372)
                    + u8" to avoid eyes of people."s);
        }
    }
    if (prm_370 == 18)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は周りの動きが遅く見えるようになった。"s,
                name(prm_372) + your(prm_372) + u8" speed increases."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は遅くなった。"s,
                name(prm_372) + your(prm_372) + u8" speed decreases."s);
        }
    }
    if (prm_370 == 19)
    {
        if (prm_371 == 0)
        {
            return lang(
                name(prm_372) + u8"は幸運になった。"s,
                name(prm_372) + u8" become"s + _s(prm_372) + u8" lucky."s);
        }
        else
        {
            return lang(
                name(prm_372) + u8"は不幸になった。"s,
                name(prm_372) + u8" become"s + _s(prm_372) + u8" unlucky."s);
        }
    }
    if (prm_371 == 0)
    {
        return lang(
            name(prm_372) + u8"は"s + skillname(prm_370)
                + u8"の技術の向上を感じた。"s,
            name(prm_372) + your(prm_372) + u8" "s + skillname(prm_370)
                + u8" skill increases."s);
    }
    else
    {
        return lang(
            name(prm_372) + u8"は"s + skillname(prm_370)
                + u8"の技術の衰えを感じた。"s,
            name(prm_372) + your(prm_372) + u8" "s + skillname(prm_370)
                + u8" skill falls off."s);
    }
}



std::string
foodname(int prm_373, const std::string& prm_374, int prm_375, int prm_376)
{
    std::string s_at_m33;
    std::string n_at_m33;
    int p_at_m33 = 0;
    s_at_m33 = prm_374;
    if (prm_373 == 1)
    {
        if (prm_376 == 0)
        {
            n_at_m33 = lang(u8"動物"s, u8"beast"s);
        }
        else
        {
            n_at_m33 = refchara_str(prm_376, 2);
        }
        if (prm_375 == 1)
        {
            p_at_m33 = (lang(
                            u8"グロテスクな"s + n_at_m33 + u8"の肉"s,
                            u8"grotesque "s + n_at_m33 + u8" meat"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"グロテスクな"s + n_at_m33 + u8"の肉"s,
                    u8"grotesque "s + n_at_m33 + u8" meat"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 = (lang(
                            u8"焼け焦げた"s + n_at_m33 + u8"の肉"s,
                            u8"charred "s + n_at_m33 + u8" meat"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"焼け焦げた"s + n_at_m33 + u8"の肉"s,
                    u8"charred "s + n_at_m33 + u8" meat"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(
                     ""s + n_at_m33 + u8"のこんがり肉"s, u8"roast "s + n_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"のこんがり肉"s, u8"roast "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 = (lang(
                            ""s + n_at_m33 + u8"肉のオードブル"s,
                            u8"deep fried "s + n_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"肉のオードブル"s,
                    u8"deep fried "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(
                            ""s + n_at_m33 + u8"のピリ辛炒め"s,
                            u8"skewer grilled "s + n_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"のピリ辛炒め"s,
                    u8"skewer grilled "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(
                     ""s + n_at_m33 + u8"コロッケ"s, n_at_m33 + u8" croquette"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"コロッケ"s, n_at_m33 + u8" croquette"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 = (lang(
                            ""s + n_at_m33 + u8"のハンバーグ"s,
                            n_at_m33 + u8" hamburger"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"のハンバーグ"s,
                    n_at_m33 + u8" hamburger"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 = (lang(
                            ""s + n_at_m33 + u8"肉の大葉焼き"s,
                            n_at_m33 + u8" cutlet"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"肉の大葉焼き"s,
                    n_at_m33 + u8" cutlet"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 =
                (lang(""s + n_at_m33 + u8"ステーキ"s, n_at_m33 + u8" steak"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + n_at_m33 + u8"ステーキ"s, n_at_m33 + u8" steak"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 2)
    {
        if (s_at_m33 == ""s)
        {
            s_at_m33 = lang(u8"野菜"s, u8"vegetable"s);
        }
        if (prm_375 == 1)
        {
            p_at_m33 = (lang(
                            u8"生ごみ同然の"s + s_at_m33,
                            u8"kitchen refuse "s + s_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"生ごみ同然の"s + s_at_m33,
                    u8"kitchen refuse "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 =
                (lang(u8"悪臭を放つ"s + s_at_m33, u8"smelly "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"悪臭を放つ"s + s_at_m33, u8"smelly "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"のサラダ"s, s_at_m33 + u8" salad"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のサラダ"s, s_at_m33 + u8" salad"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の炒め物"s, u8"fried "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の炒め物"s, u8"fried "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"風味の肉じゃが"s,
                            s_at_m33 + u8" roll"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"風味の肉じゃが"s,
                    s_at_m33 + u8" roll"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の天ぷら"s, s_at_m33 + u8" tenpura"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の天ぷら"s, s_at_m33 + u8" tenpura"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の煮込み"s, s_at_m33 + u8" gratin"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の煮込み"s, s_at_m33 + u8" gratin"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"シチュー"s,
                            u8"meat and "s + s_at_m33 + u8" stew"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"シチュー"s,
                    u8"meat and "s + s_at_m33 + u8" stew"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"風カレー"s, s_at_m33 + u8" curry"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"風カレー"s, s_at_m33 + u8" curry"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 3)
    {
        if (s_at_m33 == ""s)
        {
            s_at_m33 = lang(u8"果物"s, u8"fruit"s);
        }
        if (prm_375 == 1)
        {
            p_at_m33 = (lang(
                            u8"食べてはならない"s + s_at_m33,
                            u8"dangerous "s + s_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"食べてはならない"s + s_at_m33,
                    u8"dangerous "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 =
                (lang(u8"べっちょりした"s + s_at_m33, u8"doubtful "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"べっちょりした"s + s_at_m33, u8"doubtful "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"のフルーツサラダ"s,
                            s_at_m33 + u8" jelly salad"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のフルーツサラダ"s,
                    s_at_m33 + u8" jelly salad"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"のプリン"s, s_at_m33 + u8" pudding"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のプリン"s, s_at_m33 + u8" pudding"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"シャーベット"s,
                            s_at_m33 + u8" sherbet"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"シャーベット"s,
                    s_at_m33 + u8" sherbet"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(
                     ""s + s_at_m33 + u8"シェイク"s, s_at_m33 + u8" ice cream"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"シェイク"s, s_at_m33 + u8" ice cream"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"クレープ"s, s_at_m33 + u8" crepe"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"クレープ"s, s_at_m33 + u8" crepe"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"フルーツケーキ"s,
                            s_at_m33 + u8" fruit cake"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"フルーツケーキ"s,
                    s_at_m33 + u8" fruit cake"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"パフェ"s,
                            s_at_m33 + u8" grand parfait"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"パフェ"s,
                    s_at_m33 + u8" grand parfait"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 5)
    {
        n_at_m33 = lang(u8"麺"s, u8"noodle"s);
        if (prm_375 == 1)
        {
            p_at_m33 =
                (lang(u8"禁断の"s + n_at_m33, u8"risky "s + n_at_m33) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"禁断の"s + n_at_m33, u8"risky "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 = (lang(
                            u8"のびてふにゃった"s + n_at_m33,
                            u8"exhausted "s + n_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"のびてふにゃった"s + n_at_m33,
                    u8"exhausted "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(u8"サラダパスタ"s, u8"salad pasta"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"サラダパスタ"s, u8"salad pasta"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 = (lang(u8"うどん"s, u8"udon"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"うどん"s, u8"udon"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(u8"冷やし蕎麦"s, u8"soba"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"冷やし蕎麦"s, u8"soba"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(u8"ペペロンチーノ"s, u8"peperoncino"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"ペペロンチーノ"s, u8"peperoncino"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 = (lang(u8"カルボナーラ"s, u8"carbonara"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"カルボナーラ"s, u8"carbonara"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 = (lang(u8"ラーメン"s, u8"ramen"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"ラーメン"s, u8"ramen"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 = (lang(u8"ミートスパゲティ"s, u8"meat spaghetti"s) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"ミートスパゲティ"s, u8"meat spaghetti"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 4)
    {
        if (s_at_m33 == ""s)
        {
            s_at_m33 = lang(u8"お菓子"s, u8"candy"s);
        }
        if (prm_375 == 1)
        {
            p_at_m33 =
                (lang(
                     u8"原型を留めない"s + s_at_m33, u8"collapsed "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"原型を留めない"s + s_at_m33, u8"collapsed "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 = (lang(u8"まずそうな"s + s_at_m33, u8"nasty "s + s_at_m33)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"まずそうな"s + s_at_m33, u8"nasty "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"クッキー"s, s_at_m33 + u8" cookie"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"クッキー"s, s_at_m33 + u8" cookie"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"のゼリー"s, s_at_m33 + u8" jelly"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のゼリー"s, s_at_m33 + u8" jelly"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"パイ"s, s_at_m33 + u8" pie"s) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(""s + s_at_m33 + u8"パイ"s, s_at_m33 + u8" pie"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"まんじゅう"s, s_at_m33 + u8" bun"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"まんじゅう"s, s_at_m33 + u8" bun"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"風味のシュークリーム"s,
                            s_at_m33 + u8" cream puff"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"風味のシュークリーム"s,
                    s_at_m33 + u8" cream puff"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"のケーキ"s, s_at_m33 + u8" cake"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のケーキ"s, s_at_m33 + u8" cake"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 = (lang(
                            ""s + s_at_m33 + u8"風ザッハトルテ"s,
                            s_at_m33 + u8" sachertorte"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"風ザッハトルテ"s,
                    s_at_m33 + u8" sachertorte"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 6)
    {
        if (s_at_m33 == ""s)
        {
            s_at_m33 = lang(u8"魚"s, u8"fish"s);
        }
        if (prm_375 == 1)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の残骸"s, u8"leftover "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の残骸"s, u8"leftover "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 =
                (lang(u8"骨だけ残った"s + s_at_m33, u8"bony "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"骨だけ残った"s + s_at_m33, u8"bony "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"のフライ"s, u8"fried "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"のフライ"s, u8"fried "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の煮込み"s, u8"stewed "s + s_at_m33)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の煮込み"s, u8"stewed "s + s_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"スープ"s, s_at_m33 + u8" soup"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"スープ"s, s_at_m33 + u8" soup"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の天ぷら"s, s_at_m33 + u8" tenpura"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の天ぷら"s, s_at_m33 + u8" tenpura"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 =
                (lang(
                     ""s + s_at_m33 + u8"ソーセージ"s, s_at_m33 + u8" sausage"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"ソーセージ"s, s_at_m33 + u8" sausage"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の刺身"s, s_at_m33 + u8" sashimi"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の刺身"s, s_at_m33 + u8" sashimi"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 =
                (lang(""s + s_at_m33 + u8"の活け作り"s, s_at_m33 + u8" sushi"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    ""s + s_at_m33 + u8"の活け作り"s, s_at_m33 + u8" sushi"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 7)
    {
        n_at_m33 = lang(u8"パン"s, u8"bread"s);
        if (prm_375 == 1)
        {
            p_at_m33 =
                (lang(u8"恐怖の"s + n_at_m33, u8"fearsome "s + n_at_m33) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"恐怖の"s + n_at_m33, u8"fearsome "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 =
                (lang(u8"ガチガチの"s + n_at_m33, u8"hard "s + n_at_m33) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"ガチガチの"s + n_at_m33, u8"hard "s + n_at_m33);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 =
                (lang(u8"くるみパン"s, u8"walnut bread"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"くるみパン"s, u8"walnut bread"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 = (lang(u8"アップルパイ"s, u8"apple pie"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"アップルパイ"s, u8"apple pie"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(u8"サンドイッチ"s, u8"sandwich"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"サンドイッチ"s, u8"sandwich"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 = (lang(u8"クロワッサン"s, u8"croissant"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"クロワッサン"s, u8"croissant"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 = (lang(u8"コロッケパン"s, u8"croquette sandwich"s) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"コロッケパン"s, u8"croquette sandwich"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 =
                (lang(u8"カレーパン"s, u8"chocolate babka"s) != ""s) + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"カレーパン"s, u8"chocolate babka"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 = (lang(u8"メロンパン"s, u8"melon flavored bread"s) != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(u8"メロンパン"s, u8"melon flavored bread"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    if (prm_373 == 8)
    {
        if (prm_376 == 0)
        {
            n_at_m33 = lang(u8"鳥"s, u8"animal"s);
        }
        else
        {
            n_at_m33 = refchara_str(prm_376, 2);
        }
        if (prm_375 == 1)
        {
            p_at_m33 = (lang(
                            u8"グロテスクな"s + n_at_m33 + u8"の卵"s,
                            u8"grotesque "s + n_at_m33 + u8" egg"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"グロテスクな"s + n_at_m33 + u8"の卵"s,
                    u8"grotesque "s + n_at_m33 + u8" egg"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 2)
        {
            p_at_m33 = (lang(
                            u8"焦げた"s + n_at_m33 + u8"の卵"s,
                            u8"overcooked "s + n_at_m33 + u8" egg"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"焦げた"s + n_at_m33 + u8"の卵"s,
                    u8"overcooked "s + n_at_m33 + u8" egg"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 3)
        {
            p_at_m33 = (lang(
                            n_at_m33 + u8"の卵の目玉焼き"s,
                            u8"fried "s + n_at_m33 + u8" egg"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    n_at_m33 + u8"の卵の目玉焼き"s,
                    u8"fried "s + n_at_m33 + u8" egg"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 4)
        {
            p_at_m33 =
                (lang(
                     n_at_m33 + u8"風味のキッシュ"s, n_at_m33 + u8" egg toast"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    n_at_m33 + u8"風味のキッシュ"s, n_at_m33 + u8" egg toast"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 5)
        {
            p_at_m33 = (lang(
                            u8"半熟"s + n_at_m33,
                            u8"soft boiled "s + n_at_m33 + u8" egg"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"半熟"s + n_at_m33,
                    u8"soft boiled "s + n_at_m33 + u8" egg"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 6)
        {
            p_at_m33 = (lang(
                            n_at_m33 + u8"の卵入りスープ"s,
                            u8"soup with "s + n_at_m33 + u8" egg"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    n_at_m33 + u8"の卵入りスープ"s,
                    u8"soup with "s + n_at_m33 + u8" egg"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 7)
        {
            p_at_m33 = (lang(
                            u8"熟成"s + n_at_m33 + u8"チーズ"s,
                            u8"mature "s + n_at_m33 + u8" cheeze"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    u8"熟成"s + n_at_m33 + u8"チーズ"s,
                    u8"mature "s + n_at_m33 + u8" cheeze"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 8)
        {
            p_at_m33 = (lang(
                            n_at_m33 + u8"のレアチーズケーキ"s,
                            n_at_m33 + u8" cheeze cake"s)
                        != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    n_at_m33 + u8"のレアチーズケーキ"s,
                    n_at_m33 + u8" cheeze cake"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        if (prm_375 == 9)
        {
            p_at_m33 =
                (lang(n_at_m33 + u8"風オムライス"s, n_at_m33 + u8" omelet"s)
                 != ""s)
                + 0 + 0;
            p_at_m33 = prm_376 % p_at_m33;
            if (p_at_m33 == 0)
            {
                return lang(
                    n_at_m33 + u8"風オムライス"s, n_at_m33 + u8" omelet"s);
            }
            else if (p_at_m33 == 1)
            {
                return "";
            }
            else
            {
                return "";
            }
        }
        return s_at_m33;
    }
    return s_at_m33;
}



std::string _yoro(int prm_377)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしくお願いします"s;
            _tone_at_m34(1) = u8"どうぞ、よろしくです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくお願いしますわ"s;
            _tone_at_m34(1) = u8"よろしくです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしく頼むぜ"s;
            _tone_at_m34(1) = u8"よろしくな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくね"s;
            _tone_at_m34(1) = u8"よろしくな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしくね"s;
            _tone_at_m34(1) = u8"よろしくお願いするよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくねっ"s;
            _tone_at_m34(1) = u8"よろしく〜"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしく…"s;
            _tone_at_m34(1) = u8"今後とも、よろしく…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくね…"s;
            _tone_at_m34(1) = u8"よろ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしく頼もう"s;
            _tone_at_m34(1) = u8"よろしく頼むぞよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしく頼むぞよ"s;
            _tone_at_m34(1) = u8"よろしく頼むぞな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よしなに"s;
            _tone_at_m34(1) = u8"よろしく頼むでござる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくでござりまする"s;
            _tone_at_m34(1) = u8"どうぞよしなに"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よろしくッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
        else
        {
            _tone_at_m34(0) = u8"よろしくにゃの"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_377);
        }
    }
    return _tone_at_m34;
}



std::string _dozo(int prm_378)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"はい、どうぞ"s;
            _tone_at_m34(1) = u8"お待ちどうさまです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"はい、どうぞ"s;
            _tone_at_m34(1) = u8"注文の品ですわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ほらよ"s;
            _tone_at_m34(1) = u8"ほれ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"ほら"s;
            _tone_at_m34(1) = u8"待たせたね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"はい、お待ち"s;
            _tone_at_m34(1) = u8"さあ、どうぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"さあ、どうぞ"s;
            _tone_at_m34(1) = u8"お待ちどうさま"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ほら…"s;
            _tone_at_m34(1) = u8"待たせたな…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"はい…"s;
            _tone_at_m34(1) = u8"どうぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ほうれ"s;
            _tone_at_m34(1) = u8"ほれ、受け取りたまえ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"ほれ、受け取るが良い"s;
            _tone_at_m34(1) = u8"ほれ、待たせたのう"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"お待たせ申した"s;
            _tone_at_m34(1) = u8"待たせたでござる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"お待たせ致しました"s;
            _tone_at_m34(1) = u8"ささ、どうぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"お待たせッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
        else
        {
            _tone_at_m34(0) = u8"お待たせにゃん"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_378);
        }
    }
    return _tone_at_m34;
}



std::string _thanks(int prm_379)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"感謝します"s;
            _tone_at_m34(1) = u8"ありがとうございます"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"感謝します"s;
            _tone_at_m34(1) = u8"ありがとうございます"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ありがとよ"s;
            _tone_at_m34(1) = u8"ありがたい"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"礼を言うよ"s;
            _tone_at_m34(1) = u8"ありがたいね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ありがとう"s;
            _tone_at_m34(1) = u8"感謝するよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"ありがとう〜"s;
            _tone_at_m34(1) = u8"感謝するわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"礼を言う…"s;
            _tone_at_m34(1) = u8"感謝する…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"ありがと…"s;
            _tone_at_m34(1) = u8"礼を言うわ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"礼を申すぞ"s;
            _tone_at_m34(1) = u8"感謝してつかわす"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"くるしゅうない"s;
            _tone_at_m34(1) = u8"礼をいってつかわす"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かたじけない"s;
            _tone_at_m34(1) = u8"恩に着る"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"ありがたや"s;
            _tone_at_m34(1) = u8"お礼申し上げます"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"アザーッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃりーん"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_379);
        }
    }
    return _tone_at_m34;
}



std::string _rob(int prm_380)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"悪いことは言わない。おやめなさい"s;
            _tone_at_m34(1) = u8"止めてください。きっと後悔しますよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"止めてくださいませ"s;
            _tone_at_m34(1) =
                u8"こういう時のために、傭兵に金をかけているのです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"なんだ、貴様賊だったのか"s;
            _tone_at_m34(1) = u8"馬鹿な奴だ。後になって謝っても遅いぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"ふん、返り討ちにしてくれるよ"s;
            _tone_at_m34(1) = u8"ごろつき風情に何が出来る"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) =
                u8"おい、傭兵さんたち、このごろつきを追い払ってくれ"s;
            _tone_at_m34(1) =
                u8"馬鹿な真似をするな。こっちには屈強の傭兵がいるんだぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"やめて"s;
            _tone_at_m34(1) = u8"傭兵さんたち〜出番ですよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"甘く見られたものだ…"s;
            _tone_at_m34(1) = u8"この護衛の数が見えないのか…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"おやめ…"s;
            _tone_at_m34(1) = u8"愚かな試みよ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"なんたる無礼者か"s;
            _tone_at_m34(1) = u8"ほほほ、こやつめ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"下賤の者どもの分際で"s;
            _tone_at_m34(1) = u8"ほほほ、殺してあげなさい"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"何をするでござるか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"ご無体な"s;
            _tone_at_m34(1) = u8"まあ、お戯れが過ぎますわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"見損なったッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃりーん"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_380);
        }
    }
    return _tone_at_m34;
}



std::string _ka(int prm_381)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ですか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"ですか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かよ"s;
            _tone_at_m34(1) = u8"か"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"かい"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かい"s;
            _tone_at_m34(1) = u8"なの"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"なの"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"か…"s;
            _tone_at_m34(1) = u8"かよ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"なの…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かのう"s;
            _tone_at_m34(1) = u8"であるか"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"であるか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござるか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"でござりまするか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
        else
        {
            _tone_at_m34(0) = u8"かにゃ"s;
            _tone_at_m34(1) = u8"かニャン"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_381);
        }
    }
    return _tone_at_m34;
}



std::string _da(int prm_382)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"です"s;
            _tone_at_m34(1) = u8"ですね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"ですわ"s;
            _tone_at_m34(1) = u8"です"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だぜ"s;
            _tone_at_m34(1) = u8"だ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = u8"よ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だよ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"だわ"s;
            _tone_at_m34(1) = u8"よ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だ…"s;
            _tone_at_m34(1) = u8"さ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"よ…"s;
            _tone_at_m34(1) = u8"ね…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"じゃ"s;
            _tone_at_m34(1) = u8"でおじゃる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"じゃ"s;
            _tone_at_m34(1) = u8"でおじゃるぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござる"s;
            _tone_at_m34(1) = u8"でござるよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"でござりまする"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
        else
        {
            _tone_at_m34(0) = u8"みゃん"s;
            _tone_at_m34(1) = u8"ミャ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_382);
        }
    }
    return _tone_at_m34;
}



std::string _nda(int prm_383)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のです"s;
            _tone_at_m34(1) = u8"んです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"のですわ"s;
            _tone_at_m34(1) = u8"のです"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = "";
            _tone_at_m34(1) = u8"んだ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"の"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"んだよ"s;
            _tone_at_m34(1) = u8"んだ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"わ"s;
            _tone_at_m34(1) = u8"のよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"…"s;
            _tone_at_m34(1) = u8"んだ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"の…"s;
            _tone_at_m34(1) = u8"わ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のじゃ"s;
            _tone_at_m34(1) = u8"のだぞよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"のじゃわ"s;
            _tone_at_m34(1) = u8"のだぞよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のでござる"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"のでございます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"んだッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
        else
        {
            _tone_at_m34(0) = u8"のニャ"s;
            _tone_at_m34(1) = u8"のにゃん"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_383);
        }
    }
    return _tone_at_m34;
}



std::string _noka(int prm_384)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のですか"s;
            _tone_at_m34(1) = u8"んですか"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"のですか"s;
            _tone_at_m34(1) = u8"んですか"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のか"s;
            _tone_at_m34(1) = u8"のだな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"の"s;
            _tone_at_m34(1) = u8"のかい"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のかい"s;
            _tone_at_m34(1) = u8"の"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"の"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のか…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"の…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のかのう"s;
            _tone_at_m34(1) = u8"のだな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"のかね"s;
            _tone_at_m34(1) = u8"のだな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のでござるか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"のでございます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"のッスか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃんか"s;
            _tone_at_m34(1) = u8"ニャン"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_384);
        }
    }
    return _tone_at_m34;
}



std::string _kana(int prm_385)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でしょうか"s;
            _tone_at_m34(1) = u8"ですか"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"かしら"s;
            _tone_at_m34(1) = u8"でしょう"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"か"s;
            _tone_at_m34(1) = u8"かい"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"か"s;
            _tone_at_m34(1) = u8"かい"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かな"s;
            _tone_at_m34(1) = u8"かなぁ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"かな"s;
            _tone_at_m34(1) = u8"かなー"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かな…"s;
            _tone_at_m34(1) = u8"か…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"かな…"s;
            _tone_at_m34(1) = u8"か…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"かのう"s;
            _tone_at_m34(1) = u8"かの"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"かのう"s;
            _tone_at_m34(1) = u8"かの"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござるか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"でございますか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスか"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
        else
        {
            _tone_at_m34(0) = u8"かにゃん"s;
            _tone_at_m34(1) = u8"かニャ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_385);
        }
    }
    return _tone_at_m34;
}



std::string _kimi(int prm_386)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"貴方"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"貴方"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"お前"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"お前"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"君"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"君"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"君"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"君"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"お主"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"お主"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"そこもと"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"そなた様"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"アンタ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
        else
        {
            _tone_at_m34(0) = u8"あにゃた"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_386);
        }
    }
    return _tone_at_m34;
}



std::string _ru(int prm_387)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ます"s;
            _tone_at_m34(1) = u8"ますよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"ますわ"s;
            _tone_at_m34(1) = u8"ますの"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"るぜ"s;
            _tone_at_m34(1) = u8"るぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"るわ"s;
            _tone_at_m34(1) = u8"るよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"るよ"s;
            _tone_at_m34(1) = u8"るね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"るの"s;
            _tone_at_m34(1) = u8"るわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"る…"s;
            _tone_at_m34(1) = u8"るが…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"る…"s;
            _tone_at_m34(1) = u8"るわ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"るぞよ"s;
            _tone_at_m34(1) = u8"るぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"るぞよ"s;
            _tone_at_m34(1) = u8"るぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"るでござる"s;
            _tone_at_m34(1) = u8"るでござるよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"るのでございます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"るッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
        else
        {
            _tone_at_m34(0) = u8"るのニャ"s;
            _tone_at_m34(1) = u8"るにゃん"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_387);
        }
    }
    return _tone_at_m34;
}



std::string _tanomu(int prm_388)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"お願いします"s;
            _tone_at_m34(1) = u8"頼みます"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"お願いしますわ"s;
            _tone_at_m34(1) = u8"頼みますわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼む"s;
            _tone_at_m34(1) = u8"頼むな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"頼むよ"s;
            _tone_at_m34(1) = u8"頼む"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼むね"s;
            _tone_at_m34(1) = u8"頼むよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"頼むわ"s;
            _tone_at_m34(1) = u8"頼むね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼む…"s;
            _tone_at_m34(1) = u8"頼むぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"頼むわ…"s;
            _tone_at_m34(1) = u8"頼むよ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼むぞよ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"頼むぞよ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼み申す"s;
            _tone_at_m34(1) = u8"頼むでござる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"お頼み申し上げます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頼むッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
        else
        {
            _tone_at_m34(0) = u8"おねがいにゃ"s;
            _tone_at_m34(1) = u8"おねがいニャン"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_388);
        }
    }
    return _tone_at_m34;
}



std::string _ore(int prm_389)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"私"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"私"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"俺"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"あたし"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"僕"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"わたし"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"自分"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"自分"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"麻呂"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"わらわ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"拙者"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"手前"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あっし"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
        else
        {
            _tone_at_m34(0) = u8"みゅー"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_389);
        }
    }
    return _tone_at_m34;
}



std::string _ga(int prm_390)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ですが"s;
            _tone_at_m34(1) = u8"ですけど"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"ですが"s;
            _tone_at_m34(1) = u8"ですけど"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"が"s;
            _tone_at_m34(1) = u8"がな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"が"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"けど"s;
            _tone_at_m34(1) = u8"が"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"が"s;
            _tone_at_m34(1) = u8"けど"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"が…"s;
            _tone_at_m34(1) = u8"けど…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"が…"s;
            _tone_at_m34(1) = u8"けど…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"であるが"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"であるが"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござるが"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"でございますが"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスけど"s;
            _tone_at_m34(1) = u8"ッスが"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
        else
        {
            _tone_at_m34(0) = u8"ニャけど"s;
            _tone_at_m34(1) = u8"にゃが"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_390);
        }
    }
    return _tone_at_m34;
}



std::string _dana(int prm_391)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ですね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"ですわね"s;
            _tone_at_m34(1) = u8"ですね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"だね"s;
            _tone_at_m34(1) = u8"ね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だな…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"だね…"s;
            _tone_at_m34(1) = u8"ね…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"であるな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"であるな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござるな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"でございますね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃ"s;
            _tone_at_m34(1) = u8"みゃ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_391);
        }
    }
    return _tone_at_m34;
}



std::string _kure(int prm_392)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ください"s;
            _tone_at_m34(1) = u8"くださいよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"くださいな"s;
            _tone_at_m34(1) = u8"ください"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"くれ"s;
            _tone_at_m34(1) = u8"くれよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"くれ"s;
            _tone_at_m34(1) = u8"よ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = u8"よ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = u8"ね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"くれ…"s;
            _tone_at_m34(1) = u8"…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"よ…"s;
            _tone_at_m34(1) = u8"…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"つかわせ"s;
            _tone_at_m34(1) = u8"たもれ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"つかわせ"s;
            _tone_at_m34(1) = u8"たもれ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"頂きたいでござる"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"くださいませ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"くれッス"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃ"s;
            _tone_at_m34(1) = u8"みゃ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_392);
        }
    }
    return _tone_at_m34;
}



std::string _daro(int prm_393)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でしょう"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"でしょう"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だろ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"だろうね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だろうね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"でしょ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"だろ…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"でしょ…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"であろう"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"であろうな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござろうな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"でございましょう"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスね"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃ"s;
            _tone_at_m34(1) = u8"みゃ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_393);
        }
    }
    return _tone_at_m34;
}



std::string _yo(int prm_394)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ですよ"s;
            _tone_at_m34(1) = u8"です"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"ですよ"s;
            _tone_at_m34(1) = u8"です"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ぜ"s;
            _tone_at_m34(1) = u8"ぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"わ"s;
            _tone_at_m34(1) = u8"よ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"よ"s;
            _tone_at_m34(1) = u8"ぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"わよ"s;
            _tone_at_m34(1) = u8"わ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"…"s;
            _tone_at_m34(1) = u8"ぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"わ…"s;
            _tone_at_m34(1) = u8"…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"であろう"s;
            _tone_at_m34(1) = u8"でおじゃる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"であろうぞ"s;
            _tone_at_m34(1) = u8"でおじゃる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござろう"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"でございますわ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスよ"s;
            _tone_at_m34(1) = u8"ッス"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
        else
        {
            _tone_at_m34(0) = u8"にゃぁ"s;
            _tone_at_m34(1) = u8"みゃぁ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_394);
        }
    }
    return _tone_at_m34;
}



std::string _aru(int prm_395)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あります"s;
            _tone_at_m34(1) = u8"ありますね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あります"s;
            _tone_at_m34(1) = u8"ありますわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ある"s;
            _tone_at_m34(1) = u8"あるな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あるね"s;
            _tone_at_m34(1) = u8"あるよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あるね"s;
            _tone_at_m34(1) = u8"あるよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あるわ"s;
            _tone_at_m34(1) = u8"あるわね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ある…"s;
            _tone_at_m34(1) = u8"あるぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あるわ…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あろう"s;
            _tone_at_m34(1) = u8"おじゃる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あろう"s;
            _tone_at_m34(1) = u8"おじゃる"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あるでござる"s;
            _tone_at_m34(1) = u8"あるでござるな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"ござます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"あるッスよ"s;
            _tone_at_m34(1) = u8"あるッス"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
        else
        {
            _tone_at_m34(0) = u8"あにゅ"s;
            _tone_at_m34(1) = u8"あみぅ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_395);
        }
    }
    return _tone_at_m34;
}



std::string _u(int prm_396)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"います"s;
            _tone_at_m34(1) = u8"いますよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"いますわ"s;
            _tone_at_m34(1) = u8"います"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"うぜ"s;
            _tone_at_m34(1) = u8"うぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うわ"s;
            _tone_at_m34(1) = u8"うよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"うよ"s;
            _tone_at_m34(1) = u8"う"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うわ"s;
            _tone_at_m34(1) = u8"う"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"う…"s;
            _tone_at_m34(1) = u8"うぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うわ…"s;
            _tone_at_m34(1) = u8"う…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"うぞよ"s;
            _tone_at_m34(1) = u8"うぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うぞよ"s;
            _tone_at_m34(1) = u8"うぞ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"うでござる"s;
            _tone_at_m34(1) = u8"うでござるよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うでございます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"うッスよ"s;
            _tone_at_m34(1) = u8"うッス"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
        else
        {
            _tone_at_m34(0) = u8"うにぁ"s;
            _tone_at_m34(1) = u8"うみぁ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_396);
        }
    }
    return _tone_at_m34;
}



std::string _na(int prm_397)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ですね"s;
            _tone_at_m34(1) = u8"です"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"ですわ"s;
            _tone_at_m34(1) = u8"ですね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ぜ"s;
            _tone_at_m34(1) = u8"な"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = u8"な"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ね"s;
            _tone_at_m34(1) = u8"なぁ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"わ"s;
            _tone_at_m34(1) = u8"わね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"…"s;
            _tone_at_m34(1) = u8"な…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"…"s;
            _tone_at_m34(1) = u8"わ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でおじゃるな"s;
            _tone_at_m34(1) = u8"のう"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"でおじゃるな"s;
            _tone_at_m34(1) = u8"のう"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"でござるな"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"でございますわ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ッスね"s;
            _tone_at_m34(1) = u8"ッス"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
        else
        {
            _tone_at_m34(0) = u8"ニァ"s;
            _tone_at_m34(1) = u8"ミァ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_397);
        }
    }
    return _tone_at_m34;
}



std::string _ta(int prm_398)
{
    if (cdata_talk_type(tc) == 0)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"ました"s;
            _tone_at_m34(1) = u8"ましたね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"ました"s;
            _tone_at_m34(1) = u8"ましたわ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 1)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"た"s;
            _tone_at_m34(1) = u8"たな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"たね"s;
            _tone_at_m34(1) = u8"たよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 2)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"たね"s;
            _tone_at_m34(1) = u8"たよ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"たよ"s;
            _tone_at_m34(1) = u8"たね"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 3)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"た…"s;
            _tone_at_m34(1) = u8"たぞ…"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"たわ…"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 4)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"たぞよ"s;
            _tone_at_m34(1) = u8"たぞな"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"たぞよ"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 5)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"たでござる"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"ましてございます"s;
            _tone_at_m34(1) = "";
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 1;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    if (cdata_talk_type(tc) == 6)
    {
        if (cdata_sex(tc) == 0)
        {
            _tone_at_m34(0) = u8"たッスよ"s;
            _tone_at_m34(1) = u8"たッス"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
        else
        {
            _tone_at_m34(0) = u8"たにゃぁ"s;
            _tone_at_m34(1) = u8"たみゃぁ"s;
            _tone_at_m34(2) = "";
            _tone_at_m34(3) = "";
            _tone_at_m34(4) = "";
            p_at_m34 = 2;
            _tone_at_m34 = _tone_at_m34(rnd(p_at_m34)) + _mark(prm_398);
        }
    }
    return _tone_at_m34;
}



void label_0173()
{
    {
        int cnt = 0;
        for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt)
        {
            await();
            p(0) = instr(buff, 0, u8"{"s);
            p(1) = instr(buff, p, u8"}"s);
            p(2) = std::size(buff(0));
            if (p == -1)
            {
                break;
            }
            s(0) = strmid(buff, p + 1, p(1) - 1);
            s(1) = strmid(buff, 0, p);
            s(2) = strmid(buff, p + p(1) + 1, p(2) - p(1) - p);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
                {
                    if (s == u8"ref"s)
                    {
                        if (talkref == 1)
                        {
                            s = lang(
                                ""s + gdata_number_of_waiting_guests,
                                ""s + gdata_number_of_waiting_guests
                                    + u8" guest"s
                                    + _s2(gdata_number_of_waiting_guests));
                            break;
                        }
                    }
                    if (s == u8"you"s)
                    {
                        s = _kimi(3);
                        break;
                    }
                    if (s == u8"sex"s)
                    {
                        s = _sex2(0);
                        break;
                    }
                    if (s == u8"player"s)
                    {
                        s = cdatan(0, 0);
                        break;
                    }
                    if (s == u8"aka"s)
                    {
                        s = cdatan(1, 0);
                        break;
                    }
                    if (s == u8"npc"s)
                    {
                        s = cdatan(0, tc);
                        break;
                    }
                    if (s == u8"ある"s)
                    {
                        s = _aru(3);
                        break;
                    }
                    if (s == u8"が"s)
                    {
                        s = _ga(3);
                        break;
                    }
                    if (s == u8"か"s)
                    {
                        s = _ka(3);
                        break;
                    }
                    if (s == u8"かな"s)
                    {
                        s = _kana(3);
                        break;
                    }
                    if (s == u8"だ"s)
                    {
                        s = _da(3);
                        break;
                    }
                    if (s == u8"よ"s)
                    {
                        s = _yo(3);
                        break;
                    }
                    if (s == u8"だな"s)
                    {
                        s = _dana(3);
                        break;
                    }
                    if (s == u8"だろ"s)
                    {
                        s = _daro(3);
                        break;
                    }
                    if (s == u8"る"s)
                    {
                        s = _ru(3);
                        break;
                    }
                    if (s == u8"のだ"s)
                    {
                        s = _nda(3);
                        break;
                    }
                    if (s == u8"な"s)
                    {
                        s = _na(3);
                        break;
                    }
                    if (s == u8"くれ"s)
                    {
                        s = _kure(3);
                        break;
                    }
                    s = u8"Unknown Code"s;
                }
            }
            buff = s(1) + s + s(2);
        }
    }
    return;
}



void label_0174()
{
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    if (noteinfo(0) <= 1)
    {
        buff(0).clear();
        std::ifstream in{fs::u8path(u8"./data/talk.txt")};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
        p = instr(buff, 0, u8"%DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
        buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    }
    notedel(0);
    p = rnd(noteinfo(0));
    noteget(s, p);
    buff = s;
    label_0173();
    return;
}



void label_0175()
{
    buff = "";
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{fs::u8path(u8"./data/talk.txt")};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, valn + u8","s + lang(u8"JP"s, u8"EN"s));
    label_0174();
    return;
}



void label_0176()
{
    buff = "";
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{fs::u8path(u8"./data/talk.txt")};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
        {
            if (cdata_character_role(tc) == 18)
            {
                if (gdata_number_of_waiting_guests > 0)
                {
                    talkref = 1;
                    p = instr(buff, 0, u8"%MAID,"s + lang(u8"JP"s, u8"EN"s));
                    break;
                }
            }
            if (cdata_interest(tc) <= 0)
            {
                p = instr(buff, 0, u8"%BORED,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (tc < 16)
            {
                p = instr(
                    buff, 0, u8"%ALLY_DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (cdata_id(tc) == 335)
            {
                p = instr(buff, 0, u8"%BITCH,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (cdata_character_role(tc) == 1015)
            {
                p = instr(buff, 0, u8"%MOYER,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (cdata_character_role(tc) == 17)
            {
                p = instr(buff, 0, u8"%SLAVEKEEPER,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (cdata_character_role(tc) >= 1000
                    && cdata_character_role(tc) < 2000
                || cdata_character_role(tc) == 2003)
            {
                if (rnd(3))
                {
                    p = instr(
                        buff, 0, u8"%SHOPKEEPER,"s + lang(u8"JP"s, u8"EN"s));
                    break;
                }
            }
            if (cdata_impression(tc) >= 100)
            {
                if (rnd(3) == 0)
                {
                    p = instr(
                        buff, 0, u8"%RUMOR,LOOT,"s + lang(u8"JP"s, u8"EN"s));
                    break;
                }
            }
            if (adata(29, gdata_current_map))
            {
                if (gdata_current_map == 33)
                {
                    if (rnd(3))
                    {
                        p = instr(
                            buff,
                            0,
                            u8"%FEST,"s + gdata_current_map + u8","s
                                + lang(u8"JP"s, u8"EN"s));
                        break;
                    }
                }
            }
            if (rnd(2))
            {
                p = instr(
                    buff,
                    0,
                    u8"%PERSONALITY,"s + cdata_personality(tc) + u8","s
                        + lang(u8"JP"s, u8"EN"s));
                break;
            }
            if (rnd(3))
            {
                p = instr(
                    buff,
                    0,
                    u8"%AREA,"s + gdata_current_map + u8","s
                        + lang(u8"JP"s, u8"EN"s));
                break;
            }
        }
    }
    if (p == -1)
    {
        p = instr(buff, 0, u8"%DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
    }
    label_0174();
    return;
}



std::string cnvweight(int prm_399)
{
    std::string s_at_m35;
    s_at_m35 = ""s + std::abs(prm_399) / 1000 + u8"."s
        + std::abs(prm_399) % 1000 / 100 + ""s + strweight;
    return s_at_m35;
}



std::string fltname(int prm_400)
{
    if (prm_400 == 60001)
    {
        return lang(u8"井戸"s, u8"well"s);
    }
    if (prm_400 == 57000)
    {
        return lang(u8"食べ物"s, u8"food"s);
    }
    if (prm_400 == 56000)
    {
        return lang(u8"杖"s, u8"rods"s);
    }
    if (prm_400 == 53000)
    {
        return lang(u8"巻物"s, u8"scrolls"s);
    }
    if (prm_400 == 52000)
    {
        return lang(u8"ポーション"s, u8"potions"s);
    }
    if (prm_400 == 64000)
    {
        return lang(u8"ジャンク"s, u8"junks"s);
    }
    if (prm_400 == 77000)
    {
        return lang(u8"鉱石"s, u8"ores"s);
    }
    if (prm_400 == 60000)
    {
        return lang(u8"家具"s, u8"furniture"s);
    }
    if (prm_400 == 25000)
    {
        return lang(u8"矢弾"s, u8"ammos"s);
    }
    return lang(u8"不明"s, u8"Unknown"s);
}



void label_0180()
{
    noteadd(lang(u8"@QM[メインクエスト]"s, u8"@QM[Main Quest]"s));
    if (gdata_main_quest_flag >= 0 && gdata_main_quest_flag < 30)
    {
        s1 = lang(
            u8"ヴェルニースの南にあるネフィアの迷宮群のひとつ《レシマス》で、何かが見つかるかもしれない。"s,
            u8"I should check the dungeon called Lesimas. It's located south of Vernis."s);
    }
    if (gdata_main_quest_flag >= 30 && gdata_main_quest_flag < 50)
    {
        s1 = lang(
            u8"致命傷を負った斥候に、パルミアのジャビ王へ書簡を渡すよう頼まれた。パルミアには、ヴェルニースから東の街道を進めば辿り着ける。"s,
            u8"The injured scout asked me to devliver a letter to the king of Palmia. Palmia is located east of Vernis."s);
    }
    if (gdata_main_quest_flag >= 50 && gdata_main_quest_flag < 60)
    {
        s1 = lang(
            u8"ジャビ王によると、仕事が欲しい時は城の図書館にいるエリステアを訪ねればいいようだ。"s,
            u8"Eristia will have some tasks for me if I want to work for Palmia. She's in the library of the castle."s);
    }
    if (gdata_main_quest_flag >= 60 && gdata_main_quest_flag < 100)
    {
        s1 = lang(
            u8"レシマスに赴き、冒険者カラムという人物を探すよう依頼された。彼は最低でもレシマスの16階より先の階層にいるらしい。"s,
            u8"Eristia asked to look for an adventurer called Karam in the dungeon of Lesimas. He was on the 16th level of the dungeon the last time he sent a report. I may have to go deeper if I am to find him."s);
    }
    if (gdata_main_quest_flag >= 100 && gdata_main_quest_flag < 110)
    {
        s1 = lang(
            u8"瀕死のカラムから得た情報を、パルミアのエリステアに伝えなければならない。"s,
            u8"I need to bring information Karam gave me to Eristia at once."s);
    }
    if (gdata_main_quest_flag >= 110 && gdata_main_quest_flag < 125)
    {
        s1 = lang(
            u8"レシマス最下層の封印を解く為に必要な三つの魔石の入手を依頼された。賢者の魔石は《灼熱の塔》に、愚者の魔石は《死者の洞窟》に、覇者の魔石は《古城》にある。"s,
            u8"I need to find 3 magic stones to break the seal of Lesimas. They can be found at the Tower of Fire, the crypt of the damned and the Ancient Castle"s);
    }
    if (gdata_main_quest_flag >= 125 && gdata_main_quest_flag < 180)
    {
        s1 = lang(
            u8"三つの魔石の力で最下層の封印を解き、レシマスの秘宝を持ち帰るようエリステアに依頼された。"s,
            u8"With 3 magic stones I have, I need to get to the deepest level of Lesimas and break the seal. Then bring back an item called Hidden Artifact of Lesimas, whatever it is."s);
    }
    if (gdata_main_quest_flag >= 180 && gdata_main_quest_flag < 1000)
    {
        s1 = lang(
            u8"第一部メインクエスト完了"s,
            u8"You have completed the main quest."s);
    }
    talk_conv(s1, 40 - en * 4);
    buff += s1;
    noteadd(""s);
    return;
}



void label_0181()
{
    if (val == 0)
    {
        noteadd(""s);
        noteadd(lang(u8"@QM[サブクエスト]"s, u8"@QM[Sub Quest]"s));
    }
    p = 0;
    if (gdata_putit_attacks != 0)
    {
        s = lang(u8"ぬいぐるみを守れ！ Lv6相当"s, u8"Putit attacks Lv6"s);
        p = gdata_putit_attacks;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのミシェスに、スライムの退治を頼まれた。スライムの巣窟は、ミシェスの家のすぐ南の家のようだ。"s,
                u8"Miches of Vernis asked me to investigate the house just south of her home."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ヴェルニースのミシェスに頼まれたスライムの退治を完了した。あとは報告するだけだ。"s,
                u8"I've wiped out the putit's nest. I have to visit Miches of Vernis to report it."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_thieves_hideout != 0)
    {
        s = lang(u8"お酒泥棒 Lv2相当"s, u8"Thieves' hideout Lv2"s);
        p = gdata_thieves_hideout;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのシーナが勤める酒場に、酒泥棒が頻出しているらしい。盗賊団を壊滅させてシーナに報告しよう。"s,
                u8"Bandits have been stealing things in Vernis. I need to find and destroy their hideout."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"酒樽を盗んでいたごろつき団を殲滅した。あとはヴェルニースのシーナに報告するだけだ。"s,
                u8"Those bandits are no more. All I have to do now is bring the news to Shena of Vernis."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_puppys_cave != 0)
    {
        s = lang(u8"迷子の子犬 Lv4相当"s, u8"Puppy's cave Lv4"s);
        p = gdata_puppys_cave;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのリリアンに、迷子の子犬ポピーを捜すよう頼まれた。どうやら子犬はヴェルニースのすぐ東にある洞窟にいるらしい。"s,
                u8"Rilian of Vernis asked me to find her puppy named poppy in the puppy's cave located east of Vernis."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_nightmare != 0)
    {
        s = lang(u8"実験場のナイトメア Lv50相当"s, u8"Nightmare Lv50"s);
        p = gdata_nightmare;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのロイターに金になる仕事を持ちかけられた。何やら危険な仕事のようだ。万全の準備を整えてからロイターに話し掛けよう。"s,
                u8"Loyter of Vernis has a dangerous, yet highly profitable job for me. I need to prepare well before talking to him again."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"実験場の全ての敵を殲滅しなければならない。"s,
                u8"I need to eliminate all of the monsters in the test ground."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"実験を生き延びて完了させた。ヴェルニースのロイターに報告しよう。"s,
                u8"I've survived the nightmare. Now to meet Loyer of Vernis to receive the reward."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_pael_and_her_mom != 0)
    {
        s = lang(u8"エーテル病を治せ Lv20相当"s, u8"Pael and her mom Lv20"s);
        p = gdata_pael_and_her_mom;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 4)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 5)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 6)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 7)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 8)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 9)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 10)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_wife_collector != 0)
    {
        s = lang(u8"嫁泥棒 Lv3相当"s, u8"Wife collector LV3"s);
        p = gdata_wife_collector;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"カプールのラファエロに嫁を持ってくるよう頼まれた。なんという下劣な男だ。"s,
                u8"I was asked by Raphael of Port Kapul to bring my wife. What a moron."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_cat_house != 0)
    {
        s = lang(u8"猫退治 Lv25相当"s, u8"Cat house Lv25"s);
        p = gdata_cat_house;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのタムに、家の猫退治を依頼された。家は南の畑のあたりにあるそうだ。"s,
                u8"Tam of Yowyn asked me to eliminate the cats in his house. The house is located southern part of Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"タムの家の中の猫を退治した。あとはヨウィンでタムに報告するだけだ。"s,
                u8"I've freed Tam's house from the cats. To get the reward, I need to speak Tam again in Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_defense_line != 0)
    {
        s = lang(u8"防衛戦線の死闘 Lv17相当"s, u8"Defense line Lv17"s);
        p = gdata_defense_line;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのギルバート大佐に、ジューア解放軍の援護を求められた。準備が整い次第、大佐に話し掛けよう。"s,
                u8"Carnel Gilbert of Yowyn asked me to help the Juere freedom force fight the Yerles Army. I should speak to him again when I'm ready."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"イェルスの防衛軍を殲滅しなければならない。"s,
                u8"I need to destroy the Yerles Army."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"防衛線を見事に突破した。ヨウィンのギルバート大佐に報告しよう。"s,
                u8"I've won the war. Now to bring the good news to carnel Gilbert."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_novice_knight != 0)
    {
        s = lang(u8"騎士昇格試験の手伝い Lv8相当"s, u8"Novice knightLv8"s);
        p = gdata_novice_knight;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのアインクに騎士昇格試験の手伝いを頼まれた。ヨウィンの西にあるイークの洞窟に住むイークの首領を倒せばいいそうだ。"s,
                u8"Ainc of Yowyn asked me to help his promotion task. I need to enter the Yeek's dungeon which is located west of Yowyn and kill the chief."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"イークの首領を無事討伐した。ヨウィンのアインクに報告しよう。"s,
                u8"I've defeated the chief of Yeek. I should head back to Yowyn and report to Ainc."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_kamikaze_attack != 0)
    {
        s = lang(u8"カミカゼ特攻隊 Lv14相当"s, u8"Kamikaze attack Lv14"s);
        p = gdata_kamikaze_attack;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"カプールのアーノルドに、カミカゼ特攻隊に耐えるパルミア軍への援軍を頼まれた。準備が整い次第、アーノルドに話し掛けよう。"s,
                u8"Arnord of Port Kapul asked me to help the isolated Palmian 10th regiment from massive Kamikaze attacks. I should prepare and speak to Arnord when ready."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"パルミア軍が撤退を完了するまでの間、カミカゼ特攻隊の猛攻に耐えなければならない。パルミア軍が撤退したら、知らせが入るはずだ。"s,
                u8"I have to hold the battle line to gain time while the Palmian army retreats. A messenger will inform me when it's done."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"カミカゼ特攻隊の猛攻に耐えきった。カプールのアーノルドに報告しよう。"s,
                u8"I survived the kamikaze attack. I have to bring the good news to Arnord of Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_mias_dream != 0)
    {
        s = lang(u8"ミーアの夢 Lv1相当"s, u8"Mia's dream Lv1"s);
        p = gdata_mias_dream;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"パルミアのミーアは、稀少猫シルバーキャットが欲しいらしい。なんとか捕まえて、ミーアに渡そう。"s,
                u8"Mia of Palmia wants a silver cat, a very rare cat. If I happen to capture one, I should bring it to Mia."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_rare_books != 0)
    {
        s = lang(u8"幻の絵本 Lv12相当"s, u8"Rare books Lv12"s);
        p = gdata_rare_books;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ルミエストのレントンが、レイチェルという童話作家によって描かれた絵本を探している。絵本は全部で4巻あるらしい。全て見つけたら、レントンに報告しよう。"s,
                u8"Renton of Lumiest is looking for the fairy tale books written by Rachael. I should bring it to him if I happen to find one. There're total of 4 books in the series."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_pyramid_trial != 0)
    {
        s = lang(u8"ピラミッドからの挑戦状 Lv16相当"s, u8"Pyramid trial Lv16"s);
        p = gdata_pyramid_trial;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ピラミッドに出入りする資格を得た。ピラミッドはカプールの北にあり、中には古代の秘宝が眠っているといわれている。"s,
                u8"I've got a invitation to the pyramid. The pyramid is located north of Port Kapul and it is rumored that it holds great treasure."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_red_blossom_in_palmia != 0)
    {
        s = lang(
            u8"パルミアに赤い花を Lv14相当"s, u8"Red blossom in Palmia Lv14"s);
        p = gdata_red_blossom_in_palmia;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ダルフィのノエルにパルミアの街に爆弾をしかけるように依頼された。爆弾をパルミアの宿屋の部屋にあるぬいぐるみにしかけよう。"s,
                u8"Noel of Derphy asked me to set up a bomb in Palmia. I need to place it right on the teddy bear in the inn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"見事にパルミアを壊滅させた。あとはダルフィのノエルの元に戻り、報告するだけだ。"s,
                u8"I have successfully destroyed Palmia. Now all I need to report back to Noel in Derphy."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_ambitious_scientist != 0)
    {
        s = lang(u8"生化学者の野望 Lv5相当"s, u8"Ambitious scientist Lv5"s);
        p = gdata_ambitious_scientist;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p
            == gdata_ambitious_scientist * (gdata_ambitious_scientist < 6)
                + (gdata_ambitious_scientist == 0))
        {
            s1 = lang(
                u8"カプールのイコールに、実験用の生物5体の捕獲を頼まれた。依頼品、モンスターボールに捕獲したものでなくてはならない。あと"s
                    + (6 - gdata_ambitious_scientist)
                    + u8"個の捕獲済みモンスターボールを届ける必要がある。"s,
                u8"Icolle of Port Kapul asked me to bring 5 filled monster balls. I still need to bring him "s
                    + (6 - gdata_ambitious_scientist) + u8" of them."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_sewer_sweeping != 0)
    {
        s = lang(u8"下水道大作戦 Lv23相当"s, u8"Sewer sweeping Lv23"s);
        p = gdata_sewer_sweeping;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ルミエストのバルザックに、下水道の清掃を頼まれた。下水道の入り口は宿屋の近くにあるみたいだ。。"s,
                u8"Balzak of Lumiest wants me to sweep the entire sewer. I can find the entrance to the sewer around the inn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"下水道の大掃除を完了した。あとはルミエストのバルザックに報告するだけだ。"s,
                u8"I've finished sweeping the sewer. I need to report it to Balzak of Lumiest."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_mages_guild != 0)
    {
        s = lang(u8"魔術士ギルド審査"s, u8"Joining the Mages Guild"s);
        p = gdata_joining_mages_guild;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"魔術士ギルドに加入するには、ルミエストのメイジギルドの納入箱に、解読済みの古書物を納入し、ギルドポイントを貯めた後、ギルドの番人に話しかけなければならない。審査をクリアするには、あと"s +
                    gdata_mages_guild_quota + u8"ギルドポイントを獲得する必要がある。"s,
                u8"To join the Mages Guild, I need to gather "s + gdata_mages_guild_quota +
                    u8" more guild points and talk to the guild guard in Lumiest. I can earn the guild points by collecting ancients books, decrypt them, and put them into the delivery box near the guild guard."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_thieves_guild != 0)
    {
        s = lang(u8"盗賊ギルド審査"s, u8"Joining the Thieves Guild"s);
        p = gdata_joining_thieves_guild;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"盗賊ギルドに加入するには、税金を4ヶ月以上滞納した状態で、ダルフィのギルドの番人に話しかける必要がある。"s,
                u8"To join the Thieves Guild, I need to not pay tax for 4 months, that means I'll be a criminal for sure."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_fighters_guild != 0)
    {
        s = lang(u8"戦士ギルド審査"s, u8"Joining the Fighters Guild"s);
        p = gdata_joining_fighters_guild;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"戦士ギルドに加入するには、"s +
                    refchara_str(gdata_fighters_guild_target, 2) + u8"をあと"s + gdata_fighters_guild_quota +
                    u8"匹討伐してから、カプールのギルドの番人に話しかける必要がある。"s,
                u8"To join the Fighters Guild, I need to slay "s + gdata_fighters_guild_quota +
                    u8" more "s + refchara_str(gdata_fighters_guild_target, 2) +
                    u8" and talk to the guild guard in Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_mages_guild_quota2 != 0)
    {
        s = lang(u8"魔術士ギルドノルマ"s, u8"The Mages Guild quota"s);
        p = gdata_mages_guild_quota2;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"魔術士ギルドのランクを上げるためには、ルミエストのメイジギルドの納入箱に、解読済みの古書物を納入し、ギルドポイントを貯めた後、ギルドの番人に話しかけなければならない。ランク上昇のためには、あと"s +
                    gdata_mages_guild_quota + u8"ギルドポイントを獲得する必要がある。"s,
                u8"To raise the rank in the Mages Guild, you need to gather "s +
                    gdata_mages_guild_quota +
                    u8" more guild points and talk to the guard in Lumiest. I can earn the guild points by collecting ancients books, decrypt them, and put them into the delivery box near the guild guard."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_fighters_guild_quota2 != 0)
    {
        s = lang(u8"戦士ギルドノルマ"s, u8"The Fighters Guild quota"s);
        p = gdata_fighters_guild_quota2;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"戦士ギルドのランクを上げるためには、"s +
                    refchara_str(gdata_fighters_guild_target, 2) + u8"をあと"s + gdata_fighters_guild_quota +
                    u8"匹討伐してから、カプールのギルドの番人に話しかける必要がある。"s,
                u8"To raise the rank in the Fighters Guild, I need to slay "s +
                    gdata_fighters_guild_quota + u8" more "s + refchara_str(gdata_fighters_guild_target, 2) +
                    u8" and talk to the guild guard in Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_thieves_guild_quota2 != 0)
    {
        s = lang(u8"盗賊ギルドノルマ"s, u8"The Thieves Guild quota"s);
        p = gdata_thieves_guild_quota2;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"盗賊ギルドのランクを上げるためには、あと金貨"s +
                    gdata_thieves_guild_quota +
                    u8"枚分の盗品を売りさばき、ダルフィのギルドの番人に話しかける必要がある。"s,
                u8"To raise the rank in the Thieves Guild, I need to sell stolen goods worth total of "s +
                    gdata_thieves_guild_quota +
                    u8" gold pices and talk to the guild guard in Derphy."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_minotaur_king != 0)
    {
        s = lang(u8"ミノタウロスの王 Lv24相当"s, u8"Minotaur king Lv24"s);
        p = gdata_minotaur_king;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"パルミアのコネリー少将に、ミノタウロスの首領の退治を頼まれた。ミノタウロスの巣窟は、ヨウィンの南にあるみたいだ。"s,
                u8"General Conery wants me to hunt the chief of minotaur. The nest is located south of Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ミノタウロスの首領を無事討伐した。パルミアのコネリー少将に報告しよう。"s,
                u8"I've killed the chief of minotaur. I should head back to Palmia and speak to General Conery."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_little_sister != 0)
    {
        s = lang(u8"リトルシスター Lv30相当"s, u8"Little sister Lv30"s);
        p = gdata_little_sister;
        if (val == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"アクリ・テオラの謎の科学者に、リトルシスターを連れてくるよう頼まれた。捕獲するためには、ビッグダディを倒し、捕獲玉をリトルにぶつける必要がある。"s,
                u8"A strange scientist asked me to bring little sisters to her. To capture a little sister, I need to kill Big Daddy first then throw the little ball at her."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    return;
}



void label_0182()
{
    noteadd(lang(u8"[古びたお守り]"s, u8"[An old talisman]"s));
    if (gdata_main_quest_flag >= 30)
    {
        noteadd(lang(u8"[ジャビ王への書簡]"s, u8"A letter to the king"s));
    }
    if (gdata_magic_stone_of_fool != 0)
    {
        noteadd(lang(u8"[愚者の魔石]"s, u8"Fool's magic stone"s));
    }
    if (gdata_magic_stone_of_king != 0)
    {
        noteadd(lang(u8"[覇者の魔石]"s, u8"King's magic stone"s));
    }
    if (gdata_magic_stone_of_sage != 0)
    {
        noteadd(lang(u8"[賢者の魔石]"s, u8"Sage's magic stone"s));
    }
    return;
}



void label_0183()
{
    elona_vector1<std::string> buff2;
    notesel(buffboard);
    SDIM1(buff2);
    p = instr(buffboard, 0, s + u8","s + lang(u8"JP"s, u8"EN"s));
    buff2 = strmid(buffboard, p, instr(buffboard, p, u8"%END"s));
    notesel(buff2);
    if (noteinfo(0) <= 1)
    {
        buff2 = u8"no txt"s;
        return;
    }
    p = rnd(noteinfo(0) - 1) + 1;
    noteget(buff2, p);
    p = instr(buff2, 0, u8":"s);
    s(3) = strmid(buff2, 0, p);
    if (val == 2)
    {
        notesel(buff);
        return;
    }
    buff2 = strmid(buff2, p + 1, std::size(buff2(0)) - p - 1);
    if (val != 2)
    {
        buff = buff2;
    }
    return;
}



void txtgod(int prm_407, int prm_408)
{
    if (prm_407 == 0)
    {
        return;
    }
    txtef(5);
    if (prm_408 == 12)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                    u8"「お前も体を機械化したらどうだ？」"s,
                    cnvtalk(u8"You should mechanize your body."s)),
                lang(
                    u8"「常に、私の名に恥じぬよう振舞え」"s,
                    cnvtalk(u8"Always behave true to my name."s)),
                lang(
                    u8"「焦るな。すぐに機械が全てを支配する時代が来る」"s,
                    cnvtalk(
                        u8"No need to hurry. The day machines dominate the world is much closer than you think."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(u8"「みじめなブタども」"s, cnvtalk(u8"Pathetic pigs."s)),
                lang(
                    u8"「マニ？その名を再び口にしたらミンチよ、子猫ちゃん」"s,
                    cnvtalk(
                        u8"Mani? Say that name again and I'll mince you, kitty."s)),
                lang(
                    u8"「前の下僕は、八つ裂きにしてシルフ達の餌にしたわ。髪型がちょっと気に食わなかったから。アハハ！」"s,
                    cnvtalk(
                        u8"I've teared the former servant limb from limb to feed the sylphs. I just didn't like his hair style. Ahaha!"s)),
                lang(
                    u8"「私の子供達は風の声、何事にも縛られてはいけない。オマエもよ」"s,
                    cnvtalk(
                        u8"My children are the voices of the wind, never tied to anything."s)));
        }
        if (prm_407 == 3)
        {
            if (rnd(3))
            {
                txt(lang(
                        u8"「汝油断することなかれ」"s,
                        cnvtalk(u8"Idleness is the devil's workshop."s)),
                    lang(
                        u8"「我々の抱える痛みを、定命の者が理解することはないであろう」"s,
                        cnvtalk(
                            u8"You mortals will never understand the pain we hold."s)),
                    lang(
                        u8"「我が名はイツパロトル。元素の起源にて、最古の炎を従えし王、全ての神の主なり」"s,
                        cnvtalk(
                            u8"My name is Itzpalt. I am the origin of elements, the king that bears the earliest flame and the master of all the Gods."s)));
            }
            else
            {
                txt(lang(
                    u8"「神々の戦いに終わりはない。来るべき時は、汝も我が軍門の元で働いてもらうであろう」"s,
                    cnvtalk(
                        u8"God's war never end. In times to come, you shall be a warrior of my faction."s)));
            }
        }
        if (prm_407 == 4)
        {
            txt(lang(u8"「たらばがに！」"s, cnvtalk(u8"Coconut crab!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(u8"「フハハハハ」"s, cnvtalk(u8"Muwahaha."s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(u8"「な、なによバカ！」"s, cnvtalk(u8"W-What? Silly!"s)),
                lang(
                    u8"「私はこの仕事に向いているのかなあ」"s,
                    cnvtalk(u8"Am I really suitable for this job?"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                    u8"「木々のさえずり…森の命が奏でる歌…耳をすませば…」"s,
                    cnvtalk(
                        u8"Twitter of trees...song weaved by forests...if you strain your ears...."s)),
                lang(
                    u8"「争いごとは…醜い」"s,
                    cnvtalk(u8"This conflict between Gods...ugly."s)),
                lang(
                    u8"「僕のエヘカトル…今はもう…かつての面影さえない」"s,
                    cnvtalk(
                        u8"My Ehekatl...you are not what you used to be..."s)),
                lang(
                    u8"「僕は与えよう…君たちが奪う以上のものを」"s,
                    cnvtalk(u8"I will give...more than you spoil..."s)));
        }
    }
    if (prm_408 == 9)
    {
        if (prm_407 == 1)
        {
            txt(lang(u8"「いいぞ」"s, cnvtalk(u8"Nice kill."s)),
                lang(
                    u8"「分解してみたくならないか？」"s,
                    cnvtalk(u8"Don't you want to decompose it?"s)),
                lang(
                    u8"「その魂なら質の良い機械が組めそうだ」"s,
                    cnvtalk(
                        u8"Ah, this soul could be a good component for a new machine."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                    u8"「不潔ね。血を拭いなさいよ」"s,
                    cnvtalk(u8"How dirty. Wipe the blood off your hands."s)),
                lang(
                    u8"「アハハ！ミンチミンチィ！」"s,
                    cnvtalk(u8"Aha! Mince! Mince!."s)),
                lang(
                    u8"「まあ、いけない子猫ちゃん」"s,
                    cnvtalk(u8"Bad kitty."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(u8"「なかなかのものだ」"s, cnvtalk(u8"Impressive."s)),
                lang(
                    u8"「そして魂は元素へと還る」"s,
                    cnvtalk(u8"And so the soul returns to the element."s)),
                lang(
                    u8"「高らかに我が名を唱えよ。屍に炎と安息を」"s,
                    cnvtalk(
                        u8"Chant my name proudly. Flame and eternal rest for the dead."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(u8"「もっと！もっと！」"s, cnvtalk(u8"More! More!"s)),
                lang(
                    u8"「死んじゃったよ！たよ！」"s,
                    cnvtalk(u8"It's dead! Dead!"s)),
                lang(
                    u8"「うっみゅーうみゅうみゅ」"s,
                    cnvtalk(u8"Meoow mew mew."s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(u8"「フハハハ！」"s, cnvtalk(u8"Mwahaha!"s)),
                lang(
                    u8"「逝け！逝け！フハハハッ！」"s,
                    cnvtalk(u8"Die! Die! Mwahahaha!"s)),
                lang(u8"「フハーン！」"s, cnvtalk(u8"Muhan!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                    u8"「や、やるじゃない」"s,
                    cnvtalk(u8"N-Not bad, for you"s)),
                lang(
                    u8"「や、やめてよ。気持ち悪い」"s,
                    cnvtalk(u8"S-Stop it. Disgusting..."s)),
                lang(
                    u8"「こっち来ないで！」"s,
                    cnvtalk(u8"Don't look at me!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(u8"「汚れたね」"s, cnvtalk(u8"You got dirty."s)),
                lang(u8"「ほどほどに」"s, cnvtalk(u8"Don't kill too much."s)),
                lang(
                    u8"「…これが…君の望んでいた結果？」"s,
                    cnvtalk(u8"...are you satisfied now?"s)));
        }
    }
    if (prm_408 == 10)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「短い命の多くを無駄な眠りに費やすとは、生身の体とは不自由なものだ。だが今はそう、休むがいい。また私に仕えるために」"s,
                cnvtalk(
                    u8"Flesh and blood, how pathetic to waste much of your limited life sleeping. But rest well for now, for you will need to serve me again."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「いいわ、少しの間だけ首枷を外してあげる。存分に休息を楽しみなさい」"s,
                cnvtalk(
                    u8"Fine, I'll unshackle you for a little while. Enjoy your sleep. But remember kitty, if you cheat on me in your dream, you'll never see a daylight again."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「旅の疲れを癒すがよい。我が費えることなき紅蓮の炎が、夜のとばりに紛れる邪なる者から汝を守るであろう」"s,
                cnvtalk(
                    u8"Relieve your fatigue. May the eternal flame protects you from filthy beings that crawl in the shroud of night."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「寝るの？本当に寝るの？おやつみ！」"s,
                cnvtalk(
                    u8"Are you going to sleep? Really sleepy? Good night!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハハハハ。付いて行くぞぉ、夢の中までも」"s,
                cnvtalk(u8"Muwahaha! I'll be following you, to your dream."s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「お、おやすみのキスなんて…絶対にやだからね！」"s,
                cnvtalk(u8"I-I'll never give you a good night kiss...ever!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「おやすみ…明日…また朗らかな芽を吹いておくれ」"s,
                cnvtalk(
                    u8"Good night...May a bright sprout brought forth tomorrow... "s)));
        }
    }
    if (prm_408 == 11)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「戻ってきたか。案外ホネのある奴だな」"s,
                cnvtalk(
                    u8"Ah, you've returned. You're tougher than I thought."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「どこホッツキ歩いてたのよ。もっと調教が必要ね」"s,
                cnvtalk(
                    u8"Where were you until now? You need more breaking, it seems."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「定命の者よ、よくぞ戻ってきた」"s,
                cnvtalk(
                    u8"And so the mortal returns. You shall serve me again."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「みゃみゃ？帰って来たの？来たの？たくさん待ってたよ！」"s,
                cnvtalk(u8"Weeee♪ You are back? You are back!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハハハハハ！！おかえり」"s,
                cnvtalk(u8"Muwahahahahaha! Welcome back."s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「べ、別にアンタが帰ってくるのを待ってたんじゃないからね！」"s,
                cnvtalk(u8"N-no...I-I wasn't looking for you! Silly!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「おかえり…待っていた」"s,
                cnvtalk(u8"Welcome back...I was...waiting for you."s)));
        }
    }
    if (prm_408 == 5)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「入信者か。私の名を貶めないよう励むがいい」"s,
                cnvtalk(
                    u8"Oh, someone comes to me finally. Devote yourself to my tasks, you'll be rewarded greatly, maybe."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「私を選んだのは正解よ。たっぷり可愛がってあげるわ、子猫ちゃん」"s,
                cnvtalk(
                    u8"You know, you've made a right choice. I will treat you with great love, little kitty."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「我が期待に応えて見せよ」"s,
                cnvtalk(u8"Do not fail me, servant."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「わ〜ほんとに信じてくれるの？くれるの？」"s,
                cnvtalk(
                    u8"Weee! You really have faith in me? Do you really?"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハッハハハハ。逃がさんぞ！」"s,
                cnvtalk(u8"Muwahahahahaha. You're mine!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「べ、別にアンタの活躍なんて期待してないんだからねっ」"s,
                cnvtalk(
                    u8"I-I don't expect you to be my servant...I-I r-really don't, you silly!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「よくきたね…期待…しているよ」"s,
                cnvtalk(u8"Welcome...I have...expectations on you..."s)));
        }
    }
    if (prm_408 == 1)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「やってくれたな。裏切り者め！」"s,
                cnvtalk(u8"Great, a trator."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「アハハ。馬鹿ね。私なしで生きていくの？」"s,
                cnvtalk(u8"Huh, fool. A life without me is all but empty."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「我を裏切ると？愚かなり」"s,
                cnvtalk(
                    u8"Remember mortal, a betrayal is not something I can forgive."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「うみみやゅっ！裏切っちゃうの？ちゃうの？」"s,
                cnvtalk(u8"Mewmewmew! Really betray me? Really betray me?"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フフッフフッフハハハハハ！」"s,
                cnvtalk(u8"Muwahahahahahahaha!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「な、何よ。アンタなんか、いなくたって寂しくないんだからね！」"s,
                cnvtalk(u8"I-I don't miss you. I-I really don't!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「裏切り…許さない…」"s,
                cnvtalk(u8"A trator...I can't...tolerate...."s)));
        }
    }
    if (prm_408 == 2)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「やるじゃないか。見直したよ」"s,
                cnvtalk(
                    u8"Well done. After all, you might be useful than I thought."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「褒めてあげるわ。私の可愛い小さなお人形さん」"s,
                cnvtalk(u8"Oh my little puppet, you serve me well."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「良し。汝の行いは覚えておこう」"s,
                cnvtalk(u8"Impressive. Your action shall be remembered."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「わおっ♪嬉しい！好き！大好き！」"s,
                cnvtalk(u8"Weeee! I'm so happy. I like you! I like you!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハハッ、いいぞいいぞ」"s,
                cnvtalk(u8"Muwahaha muwaha. Good. Good!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「な、なによ。ほ、褒めてなんかあげないわよ！」"s,
                cnvtalk(u8"W-What? I-I'm not gonna praise you. I'm not!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「よくやった…ほんとに…」"s,
                cnvtalk(u8"Good work...truly..."s)));
        }
    }
    if (prm_408 == 3)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「馬鹿にしてくれたじゃないか」"s,
                cnvtalk(u8"Heh, Nice try."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「やってくれたわね、ゴミの分際で。お仕置きよ」"s,
                cnvtalk(u8"Bad bad puppy. I need to punish you."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「汝の愚かな試みの代償を味わうがよい」"s,
                cnvtalk(
                    u8"You shall pay a painful price for your foolish try."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「バカバカバカ！バカ！」"s,
                cnvtalk(u8"Stupid stupid! Stupid!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハハハハッ、弱い弱い」"s,
                cnvtalk(u8"Muwahahahaha! Weak! Weak!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「な、なにするのよ！」"s,
                cnvtalk(u8"W-What have you done!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「敵には…容赦しない…絶対」"s,
                cnvtalk(
                    u8"I...will have no mercy..for enemies...absolutely."s)));
        }
    }
    if (prm_408 == 4)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「なかなかの贈り物だ」"s, cnvtalk(u8"Cool. I like it."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「あら、気の利いたものをくれるわね。下心でもあるの？」"s,
                cnvtalk(
                    u8"Oh, such a nice gift. Do you have a secret intention or something?"s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「汝の贈り物に感謝しよう」"s,
                cnvtalk(u8"I appriciate it, mortal."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(u8"「うみみゃぁ！」"s, cnvtalk(u8"Mew mew mew meow!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(u8"「フッハッハハー！」"s, cnvtalk(u8"Muwahahahahaha!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「べ、別に嬉しくなんかないんだからねっ！」"s,
                cnvtalk(u8"I-I'm not that pleased. I-I'm not, you silly!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「ありがたい…とてもいいよ…これ」"s,
                cnvtalk(u8"This is...very good....Thank you."s)));
        }
    }
    if (prm_408 == 6)
    {
        txtmore();
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「お前は忠実なるシモベだ。これを有効に使うがいい」"s,
                cnvtalk(
                    u8"You've been a faithful servant of me. Here, use it wisely."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「下僕のオマエにご褒美よ。大事に使いなさい。」"s,
                cnvtalk(
                    u8"My dear little kitty, you deserve a reward, don't you think?"s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「汝の忠誠に答え、贈り物を授けよう」"s,
                cnvtalk(
                    u8"To answer your loyalty, you shall have this reward."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「これあげるぅ…大切にしてね！…してね！」"s,
                cnvtalk(u8"Here's a gift! For you! Mewmew!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハハハァ！受け取れィ」"s,
                cnvtalk(u8"Muwahahahaha, take it!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「ア、アンタのためにしてあげるんじゃないんだからっ」"s,
                cnvtalk(
                    u8"I-I'm not giving it to you as my gratitude! I-I r-really am not! Silly!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「いいもの…あげる…」"s,
                cnvtalk(u8"Here...there's something for...you..."s)));
        }
    }
    if (prm_408 == 7)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「お前はまさに信者の模範だな」"s,
                cnvtalk(
                    u8"Truly, you are an ideal believer. I'm impressed."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「どこまでも私のために尽くしなさい。オマエは私の一番の奴隷なんだから」"s,
                cnvtalk(
                    u8"Serve me to the end of this pathetic world, for you are my dearest slave."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「我が名を語るに相応しい者が絶えて久しい。汝ならば、あるいは…」"s,
                cnvtalk(
                    u8"Long gone those worthy to bear my name are. But perhaps..."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「どきどきどき。君のこと、好きだよ。だよ！」"s,
                cnvtalk(u8"My heart aches! I think I like you...I guess!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「フハァッハハハハハハ！愉快愉快！」"s,
                cnvtalk(u8"Mwahaha haha! Fun! Fun!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「や、やめてよ。アンタのことなんか、大好きじゃないんだからねっ。バカ！」"s,
                cnvtalk(u8"N-No! Cut it! I-I don't love you. Stupid!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「君は…大切なしもべだ…」"s,
                cnvtalk(u8"You are...my precious valet..."s)));
        }
    }
    if (prm_408 == 8)
    {
        if (prm_407 == 1)
        {
            txt(lang(
                u8"「お前は最愛のシモベだ。その魂を私に捧げろ。お前を必ず守ってみせよう」"s,
                cnvtalk(
                    u8"Sacrifice your very soul to me and I shall protect you with my name."s)));
        }
        if (prm_407 == 2)
        {
            txt(lang(
                u8"「私に従え。全てを委ねろ。オマエの綺麗な顔を傷つけるブタどもは、私がミンチにしてあげるわ」"s,
                cnvtalk(
                    u8"Obey me and surrender everything. I shall mince all the pigs that try to hurt your beautiful face, my kitty."s)));
        }
        if (prm_407 == 3)
        {
            txt(lang(
                u8"「見事なり、定命の者よ。汝を、我が信頼に値する唯一の存在として認めよう」"s,
                cnvtalk(
                    u8"Very impressive, mortal. You shall be the one worthy to carry my name."s)));
        }
        if (prm_407 == 4)
        {
            txt(lang(
                u8"「好き！好き好き好きっ！だいすき！君とは死ぬまでずっと一緒だよ。だよ！」"s,
                cnvtalk(
                    u8"I love you! Love you! You will be with me forever...promise!"s)));
        }
        if (prm_407 == 5)
        {
            txt(lang(
                u8"「ファハハハハハハハハハハハハハー！フワハァー！」"s,
                cnvtalk(u8"Muwahahahaha! Mwaaaahahaha!"s)));
        }
        if (prm_407 == 6)
        {
            txt(lang(
                u8"「べ、別にアンタのこと愛してなんかいないんだからっ。あたしの傍から離れたらしょうちしないからねっ！このバカぁ…！"s,
                cnvtalk(
                    u8"I-I'm not falling l-love with you! D-don't you never ever leave me...okay? You stupid...!"s)));
        }
        if (prm_407 == 7)
        {
            txt(lang(
                u8"「ずっと一緒…だよね？…もう離さない…君が死ぬまで」"s,
                cnvtalk(""s)));
        }
    }
    return;
}



std::string randomname(int)
{
label_0223_internal:
    s_at_m41 = rn1(rnd(length(rn1)));
    if (s_at_m41 == ""s)
    {
        goto label_0223_internal;
    }
    if (jp)
    {
        if (rnd(8) == 0)
        {
            s_at_m41 += u8"ー"s;
        }
    }
    if (rnd(5))
    {
        s_at_m41 += rn2(rnd(length(rn2)));
    }
    p_at_m41 = std::size(s_at_m41);
    if (p_at_m41 < 4)
    {
        goto label_0223_internal;
    }
    if (p_at_m41 < 6)
    {
        if (rnd(3))
        {
            goto label_0223_internal;
        }
    }
    if (p_at_m41 < 8)
    {
        if (rnd(2))
        {
            goto label_0223_internal;
        }
    }
    if (jp)
    {
        if (strmid(s_at_m41, 0, 2) == u8"ー"s)
        {
            goto label_0223_internal;
        }
        if (strutil::contains(s_at_m41, u8"ーッ"))
        {
            goto label_0223_internal;
        }
    }

    return cnven(s_at_m41);
}



std::string random_title(int prm_439)
{
    elona_vector1<std::string> randn2_at_m41;
    int rtval_at_m41 = 0;
    elona_vector1<std::string> s2_at_m41;
    // clang-format off
label_0227_internal:
    {
        int cnt = 0;
        for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt) {
            p_at_m41(2) = rnd(length2(rnlist));
            p_at_m41(1) = rnd(14);
            if (rnlist(p_at_m41(1), p_at_m41(2)) == ""s) {
                --cnt;
                continue;
            }
        }
    }
    // clang-format on

    if (prm_439 == 1 || prm_439 == 3)
    {
        if (rnlist(14, p_at_m41(2)) == u8"具"s)
        {
            goto label_0227_internal;
        }
    }
    randn2_at_m41(0) = rnlist(p_at_m41(1), p_at_m41(2));
    randn2_at_m41(1) = rnlist(14, p_at_m41(2));
    rtval_at_m41 = -1;
    if (jp)
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
            {
                if (p_at_m41(1) == 10 || p_at_m41(1) == 11)
                {
                    if (rnd(5) == 0)
                    {
                        p_at_m41(1) = 0;
                        p_at_m41(3) = rnd(2);
                        if (p_at_m41(3) == 0)
                        {
                            randn2_at_m41 += u8"の"s;
                        }
                        break;
                    }
                    p_at_m41 = rnd(5);
                    if (p_at_m41 == 0)
                    {
                        randn2_at_m41 += u8"・オブ・"s;
                    }
                    if (p_at_m41 == 1)
                    {
                        randn2_at_m41 = u8"ザ・"s + randn2_at_m41;
                        rtval_at_m41 = 1;
                        break;
                    }
                    if (p_at_m41 == 2)
                    {
                        randn2_at_m41 += u8"・"s;
                    }
                }
                if (p_at_m41(1) == 0 || p_at_m41(1) == 1)
                {
                    randn2_at_m41 += u8"の"s;
                    p_at_m41(3) = rnd(10);
                    if (p_at_m41(3) == 0)
                    {
                        p_at_m41(1) = 10;
                    }
                }
            }
        }
    }
    else
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
            {
                if (p_at_m41(1) == 0 || p_at_m41(1) == 1)
                {
                    if (rnd(6) == 0)
                    {
                        randn2_at_m41 += u8" of"s;
                    }
                    else if (rnd(6) == 0)
                    {
                        randn2_at_m41 = u8"the "s + randn2_at_m41;
                        rtval_at_m41 = 1;
                        break;
                    }
                }
                randn2_at_m41 += u8" "s;
            }
        }
        randn2_at_m41 = cnven(randn2_at_m41);
    }
    if (rtval_at_m41 == 1)
    {
        s_at_m41 = randn2_at_m41;
        goto label_0228_internal;
    }
    rtval_at_m41 = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
        {
            p_at_m41(4) = rnd(length2(rnlist));
            if (p_at_m41(4) == p_at_m41(2))
            {
                continue;
            }
            if (rnlist(14, p_at_m41(4)) == randn2_at_m41(1))
            {
                if (rnlist(14, p_at_m41(4)) != u8"万能"s)
                {
                    if (randn2_at_m41(1) != u8"万能"s)
                    {
                        continue;
                    }
                }
            }
            if (p_at_m41(1) < 10)
            {
                p_at_m41(1) = rnd(2);
            }
            else
            {
                p_at_m41(1) = rnd(2);
                p_at_m41(1) += 10;
            }
            if (rnlist(p_at_m41(1), p_at_m41(4)) == ""s)
            {
                continue;
            }
            rtval_at_m41 = 1;
            break;
        }
    }
    if (rtval_at_m41 == -1)
    {
        goto label_0227_internal;
    }
    if (en)
    {
        rnlist(p_at_m41(1), p_at_m41(4)) =
            cnven(rnlist(p_at_m41(1), p_at_m41(4)));
    }
    randn2_at_m41 += rnlist(p_at_m41(1), p_at_m41(4));
    s_at_m41 = randn2_at_m41;
    if (strlen_u(s_at_m41) >= 28)
    {
        goto label_0227_internal;
    }
label_0228_internal:
    if (prm_439 == 2)
    {
        if (jp)
        {
            s2_at_m41(0) = u8"団"s;
            s2_at_m41(1) = u8"チーム"s;
            s2_at_m41(2) = u8"パーティー"s;
            s2_at_m41(3) = u8"の集い"s;
            s2_at_m41(4) = u8"の軍"s;
            s2_at_m41(5) = u8"アーミー"s;
            s2_at_m41(6) = u8"隊"s;
            s2_at_m41(7) = u8"の一家"s;
            s2_at_m41(8) = u8"軍"s;
            s2_at_m41(9) = u8"の隊"s;
            s2_at_m41(10) = u8"の団"s;
            if (rnd(5))
            {
                s_at_m41 += s2_at_m41(rnd(10));
            }
        }
        else if (rnd(2))
        {
            s2_at_m41(0) = u8"The army of "s;
            s2_at_m41(1) = u8"The party of "s;
            s2_at_m41(2) = u8"The house of "s;
            s2_at_m41(3) = u8"Clan "s;
            s_at_m41 = s2_at_m41(rnd(4)) + s_at_m41;
        }
        else
        {
            s2_at_m41(0) = u8"Clan"s;
            s2_at_m41(1) = u8"Party"s;
            s2_at_m41(2) = u8"Band"s;
            s2_at_m41(3) = u8"Gangs"s;
            s2_at_m41(4) = u8"Gathering"s;
            s2_at_m41(5) = u8"House"s;
            s2_at_m41(6) = u8"Army"s;
            s_at_m41 += u8" "s + s2_at_m41(rnd(7));
        }
    }
    return s_at_m41;
}



void label_0230()
{
    if (hour_played == 1)
    {
        s += lang(
            u8"ラーネイレ「がんばれ〜」"s,
            u8"Larneire cheers, "s + cnvtalk(u8"Way to go!"s));
    }
    if (hour_played == 2)
    {
        s += lang(
            u8"ロミアス「陰ながら応援しているよ（ニヤリ）」"s,
            u8"Lomias grins, "s + cnvtalk(u8"Go for it."s));
    }
    if (hour_played == 3)
    {
        s += lang(
            u8"クミロミ「…大丈夫…だよね？」"s,
            u8"Kumiromi worries, "s + cnvtalk(u8"Are you...okay..?"s));
    }
    if (hour_played == 4)
    {
        s += lang(
            u8"ルルウィ「あら、思いの他がんばるのね」"s,
            u8"Lulwy sneers, "s
                + cnvtalk(u8"You're tougher than I thought, little kitty."s));
    }
    if (hour_played == 5)
    {
        s += lang(
            u8"ラーネイレ「いけない。このままでは…手遅れになってしまうわ…」"s,
            u8"Larneire cries, "s
                + cnvtalk(u8"No...before it is too late..."s));
    }
    if (hour_played == 6)
    {
        s += lang(
            u8"ロミアス「まだまだ、これからだろう（ニヤリ）」"s,
            u8"Lomias grins, "s
                + cnvtalk(u8"Tt hasn't even started yet... hasn't it?"s));
    }
    if (hour_played == 7)
    {
        s += lang(
            u8"ルルウィ「休憩しなさい。壊れちゃったら、私の役にたてないじゃない」"s,
            u8"Lulwy warns you, "s
                + cnvtalk(
                      u8"Have a rest, kitty. If you are broken, you're no use to me."s));
    }
    if (hour_played == 8)
    {
        s += lang(
            u8"ルルウィ「何を言っても無駄のようね。好きにするといいわ」"s,
            u8"Lulwy laughs, "s
                + cnvtalk(
                      u8"I guess there's no use warning you. Alright. Do as you please, kitty."s));
    }
    if (hour_played == 12)
    {
        s += lang(
            u8"オパートス「フハハハハッフハー」"s,
            u8"Opatos laughs, "s + cnvtalk(u8"Muwahahahahahaha!"s));
    }
    if (hour_played == 24)
    {
        s += lang(
            u8"虚空「希望はまだあるはずだ」"s,
            u8"Ehekatl hugs you,"s
                + cnvtalk(u8"Don't die! Promise you don't die!"s));
    }
    return;
}



void label_0247()
{
    int sid = 0;
    rtval(0) = 4;
    rtval(1) = 0;
    s = u8"error:"s + val + u8"/"s + val(1);
    val(10) = val / 10000;
    if (val(10) != 0)
    {
        if (val(2) == 1)
        {
            s = "";
            return;
        }
        sid = val % 10000;
        if (val(10) == 1)
        {
            rtval = 2;
            if (val(1) / 50 + 1 < 0)
            {
                rtval = 9;
                s = lang(
                    ""s + skillname(sid) + u8"を"s + std::abs((val(1) / 50 + 1))
                        + u8"下げる"s,
                    u8"decreases your "s + skillname(sid) + u8" by "s
                        + std::abs((val(1) / 50 + 1)) + u8"."s);
                if (val(3) == 57000)
                {
                    s = lang(
                            ""s + skillname(sid)
                                + u8"を減衰させる毒素を含んでいる"s,
                            u8"has which deteriorates your "s + skillname(sid)
                                + u8"."s)
                        + u8" ["s;
                    putenclv(val(1) / 50);
                    s += u8"]"s;
                }
            }
            else
            {
                s = lang(
                    ""s + skillname(sid) + u8"を"s + std::abs((val(1) / 50 + 1))
                        + u8"上げる"s,
                    u8"increases your "s + skillname(sid) + u8" by "s
                        + std::abs((val(1) / 50 + 1)) + u8"."s);
                if (val(3) == 57000)
                {
                    s = lang(
                            ""s + skillname(sid)
                                + u8"を増強させる栄養をもっている"s,
                            u8"has essential nutrients to enhance your "s
                                + skillname(sid) + u8"."s)
                        + u8" ["s;
                    putenclv(val(1) / 50);
                    s += u8"]"s;
                }
            }
        }
        if (val(10) == 2)
        {
            rtval = 3;
            i = val(1) / 2 / 50;
            if (val(1) / 2 < 0)
            {
                rtval = 9;
                s = lang(
                    ""s + skillname(sid) + u8"への耐性を弱化する"s,
                    u8"weaken your resistance to "s + skillname(sid) + u8"."s);
            }
            else
            {
                s = skillencdesc(sid);
                if (s == ""s)
                {
                    s = lang(
                        ""s + skillname(sid) + u8"への耐性を授ける"s,
                        u8"grants your resistance to "s + skillname(sid)
                            + u8"."s);
                }
            }
            s += u8" ["s;
            putenclv(i);
            s += u8"]"s;
        }
        if (val(10) == 3)
        {
            rtval = 1;
            i = val(1) / 50 + 1;
            if (val(1) / 50 + 1 < 0)
            {
                rtval = 9;
                s = lang(
                    ""s + skillname(sid) + u8"の技能を下げる"s,
                    u8"decreases your "s + skillname(sid) + u8" skill."s);
            }
            else
            {
                s = skillencdesc(sid);
                if (s == ""s)
                {
                    s = lang(
                        ""s + skillname(sid) + u8"の技能を上げる"s,
                        u8"improves your "s + skillname(sid) + u8" skill."s);
                }
            }
            s += u8" ["s;
            putenclv(i / 5);
            s += u8"]"s;
        }
        if (val(10) == 6)
        {
            rtval = 8;
            s = lang(
                skillname(sid) + u8"を維持する"s,
                u8"maintains "s + skillname(sid) + u8"."s);
            if (val(3) == 57000)
            {
                s = lang(
                        ""s + skillname(sid)
                            + u8"の成長を助ける栄養をもっている"s,
                        u8"can help you exercise your "s + skillname(sid)
                            + u8" faster."s)
                    + u8" ["s;
                putenclv(val(1) / 50);
                s += u8"]"s;
            }
        }
        if (val(10) == 7)
        {
            rtval = 4;
            i = val(1) / 2 / 50;
            s = skillencdesc(sid);
            if (s == ""s)
            {
                s = lang(
                    ""s + skillname(sid) + u8"属性の追加ダメージを与える"s,
                    u8"deals "s + skillname(sid) + u8" damage."s);
            }
            s += u8" ["s;
            putenclv(i);
            s += u8"]"s;
        }
        if (val(10) == 8)
        {
            rtval = 4;
            i = val(1) / 50;
            sid = encprocref(0, sid);
            s = lang(
                ""s + skillname(sid) + u8"を発動する"s,
                u8"invokes "s + skillname(sid) + u8"."s);
            s += u8" ["s;
            putenclv(i);
            s += u8"]"s;
        }
        if (val(10) == 9)
        {
            rtval = 4;
            s = lang(
                ""s + ammoname(sid) + u8"を装填できる"s,
                u8"can be loaded with "s + ammoname(sid) + u8"."s);
            s += lang(u8" [最大"s, u8" [Max "s) + val(1) / 1000
                + lang(u8"発]"s, u8"]"s);
        }
        return;
    }
    if (val == 0)
    {
        s = u8"?????"s;
    }
    if (val == 21)
    {
        rtval = 9;
        s = lang(
            u8"ランダムなテレポートを引き起こす"s,
            u8"causes random teleport."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 45)
    {
        rtval = 9;
        s = lang(u8"使用者の生き血を吸う"s, u8"sucks blood of the wielder."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 46)
    {
        rtval = 9;
        s = lang(u8"あなたの成長を妨げる"s, u8"disturbs your growth."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 47)
    {
        rtval = 9;
        s = lang(u8"魔物を呼び寄せる"s, u8"attracts monsters."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 22)
    {
        rtval = 4;
        s = lang(
            u8"テレポートを妨害する"s, u8"prevents you from teleporting."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 23)
    {
        rtval = 4;
        s = lang(u8"盲目を無効にする"s, u8"negates the effect of blindness."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 24)
    {
        rtval = 4;
        s = lang(u8"麻痺を無効にする"s, u8"negates the effect of paralysis."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 25)
    {
        rtval = 4;
        s = lang(u8"混乱を無効にする"s, u8"negates the effect of confusion."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 26)
    {
        rtval = 4;
        s = lang(u8"恐怖を無効にする"s, u8"negates the effect of fear."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 27)
    {
        rtval = 4;
        s = lang(u8"睡眠を無効にする"s, u8"negates the effect of sleep."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 28)
    {
        rtval = 4;
        s = lang(u8"毒を無効にする"s, u8"negates the effect of poison."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 41)
    {
        rtval = 4;
        s = lang(
            u8"アイテムを盗まれなくする"s, u8"protects you from thieves."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 42)
    {
        rtval = 4;
        s = lang(
            u8"腐ったものを難なく消化させる"s,
            u8"allows you to digest rotten food."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 29)
    {
        rtval = 4;
        s = lang(
            u8"速度を上げ、ワールドマップでの移動時間を短くする"s,
            u8"speeds up your travel progress."s);
        if (val(1) / 100 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 100);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 100;
            return;
        }
    }
    if (val == 30)
    {
        rtval = 4;
        s = lang(
            u8"エーテルの風からあなたを保護する"s,
            u8"protects you from Etherwind."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 31)
    {
        rtval = 4;
        s = lang(
            u8"雷雨と雪による足止めを無効にする"s,
            u8"negates the effect of being stranded by bad weather."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 48)
    {
        rtval = 4;
        s = lang(
            u8"異物の体内への侵入を防ぐ"s,
            u8"prevents aliens from entering your body."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 32)
    {
        rtval = 4;
        s = lang(u8"あなたを浮遊させる"s, u8"floats you."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 33)
    {
        rtval = 4;
        s = lang(
            u8"あなたを変異から保護する"s, u8"protects you from mutation."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 34)
    {
        rtval = 4;
        s = lang(u8"魔法の威力を高める"s, u8"enchances your spells."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 35)
    {
        rtval = 4;
        s = lang(
            u8"透明な存在を見ることを可能にする"s,
            u8"allows you to see invisible creatures."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 36)
    {
        rtval = 4;
        s = lang(
            u8"攻撃対象からスタミナを吸収する"s,
            u8"absorbs stamina from an enemy."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 37)
    {
        rtval = 4;
        s = lang(u8"全てを終結させる"s, u8"brings an end."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 38)
    {
        rtval = 4;
        s = lang(
            u8"攻撃対象からマナを吸収する"s, u8"absorbs MP from an enemy."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 39)
    {
        rtval = 4;
        s = lang(
            u8"完全貫通攻撃発動の機会を増やす"s,
            u8"gives you a chance to throw an absolute piercing attak."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 44)
    {
        rtval = 4;
        s = lang(
            u8"クリティカルヒットの機会を増やす"s,
            u8"increases your chance to deliver critical hits."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 50)
    {
        rtval = 4;
        s = lang(
            u8"追加打撃の機会を増やす"s,
            u8"increases the chance of extra melee attack."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 51)
    {
        rtval = 4;
        s = lang(
            u8"追加射撃の機会を増やす"s,
            u8"increases the chance of extra ranged attack."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 40)
    {
        rtval = 4;
        s = lang(u8"稀に時を止める"s, u8"occasionally stops time."s);
        if (val(1) == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1));
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1);
            return;
        }
    }
    if (val == 43)
    {
        rtval = 4;
        s = lang(
            u8"呪いの言葉から保護する"s, u8"protects you from cursing words."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 49)
    {
        rtval = 4;
        s = lang(
            u8"演奏報酬の品質を上げる"s,
            u8"increases the qualitiy of reward."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 52)
    {
        rtval = 4;
        s = lang(
            u8"被る物理ダメージを軽減する"s,
            u8"decreases physical damage you take."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 53)
    {
        rtval = 4;
        s = lang(
            u8"被るダメージを稀に無効にする"s,
            u8"sometimes nullifies damage you take."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 54)
    {
        rtval = 4;
        s = lang(
            u8"攻撃された時、相手に切り傷のダメージを与える"s,
            u8"deals cut damage to the attacker."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 55)
    {
        rtval = 4;
        s = lang(u8"出血を抑える"s, u8"diminishs bleeding."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 56)
    {
        rtval = 4;
        s = lang(
            u8"神が発する電波をキャッチする"s, u8"catches signals from God."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 57)
    {
        rtval = 4;
        s = lang(
            u8"竜族に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to dragons."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 58)
    {
        rtval = 4;
        s = lang(
            u8"不死者に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to undeads."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    if (val == 59)
    {
        rtval = 4;
        s = lang(u8"他者の信仰を明らかにする"s, u8"reveals religion."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 60)
    {
        rtval = 4;
        s = lang(
            u8"深い音色で聴衆を酔わす"s,
            u8"makes audience drunk with haunting tones."s);
        if (-1 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(-1);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = -1;
            return;
        }
    }
    if (val == 61)
    {
        rtval = 4;
        s = lang(
            u8"神に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to Gods."s);
        if (val(1) / 50 == -1)
        {
            return;
        }
        else if (val(2) == 0)
        {
            s += u8" ["s;
            putenclv(val(1) / 50);
            s += u8"]"s;
            return;
        }
        else
        {
            rtval(1) = val(1) / 50;
            return;
        }
    }
    return;
}



} // namespace elona
