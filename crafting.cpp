#include "crafting.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

int matid = 0;
elona_vector1<int> matval;

void initialize_craft_material_data()
{
    DIM2(matval, 4);
    DIM3(matref, 5, 400);
    DIM3(matspot, 5, 400);
    SDIM3(matname, 40, 400);
    SDIM3(matdesc, 80, 400);

    matref(0, 0) = 0;
    matref(1, 0) = 1;
    matref(2, 0) = 240;
    matname(0) = lang(u8"クズ"s, u8"Garbage"s);
    matdesc(0) = lang(u8"何の価値もないクズ"s, u8"Just garbage."s);
    matspot(0, 0) = 18;

    matref(0, 1) = 1;
    matref(1, 1) = 80;
    matref(2, 1) = 434;
    matname(1) = lang(u8"カジノチップ"s, u8"Casino chip"s);
    matdesc(1) = lang(u8"カジノで使うチップ"s, u8"Chips used in casinos."s);
    matspot(0, 1) = 18;

    matref(0, 40) = 1;
    matref(1, 40) = 200;
    matref(2, 40) = 437;
    matname(40) = lang(u8"100Yen硬貨"s, u8"100 Yen coin"s);
    matdesc(40) = lang(u8"異国のお金"s, u8"Foreign money."s);
    matspot(0, 40) = 18;

    matref(0, 41) = 1;
    matref(1, 41) = 1000;
    matref(2, 41) = 437;
    matname(41) = lang(u8"500Yen硬貨"s, u8"500 Yen coin"s);
    matdesc(41) = lang(u8"異国のお金"s, u8"Foreign money."s);
    matspot(0, 41) = 18;

    matref(0, 43) = 1;
    matref(1, 43) = 20;
    matref(2, 43) = 470;
    matname(43) = lang(u8"紙"s, u8"Paper"s);
    matdesc(43) = lang(u8"白紙"s, u8"Blank paper."s);
    matspot(0, 43) = 18;

    matref(0, 2) = 1;
    matref(1, 2) = 10;
    matref(2, 2) = 239;
    matname(2) = lang(u8"炭"s, u8"Charcoal"s);
    matdesc(2) = lang(u8"良質な炭"s, u8"This is good quality charcoal."s);
    matspot(0, 2) = 18;

    matref(0, 3) = 1;
    matref(1, 3) = 10;
    matref(2, 3) = 239;
    matname(3) = lang(u8"流木"s, u8"Driftwood"s);
    matdesc(3) = lang(u8"あまり質の良くない木材"s, u8"Common driftwood."s);
    matspot(0, 3) = 18;

    matref(0, 48) = 1;
    matref(1, 48) = 10;
    matref(2, 48) = 209;
    matname(48) = lang(u8"石ころ"s, u8"Pebble"s);
    matdesc(48) =
        lang(u8"どこにでも落ちている"s, u8"These are around everywhere."s);
    matspot(0, 48) = 18;

    matref(0, 6) = 1;
    matref(1, 6) = 70;
    matref(2, 6) = 239;
    matname(6) = lang(u8"杖"s, u8"Stick"s);
    matdesc(6) = lang(u8"杖"s, u8"A specially shaped piece of wood."s);
    matspot(0, 6) = 18;

    matref(0, 45) = 3;
    matref(1, 45) = 20;
    matref(2, 45) = 155;
    matname(45) = lang(u8"布きれ"s, u8"Cloth"s);
    matdesc(45) = lang(u8"ただの布きれ"s, u8"A piece of cloth."s);
    matspot(0, 45) = 18;

    matref(0, 38) = 4;
    matref(1, 38) = 30;
    matref(2, 38) = 8;
    matname(38) = lang(u8"わめく狂人"s, u8"Yelling madman"s);
    matdesc(38) = lang(u8"黙らない"s, u8"It never shuts up."s);
    matspot(0, 38) = 18;

    matref(0, 30) = 10;
    matref(1, 30) = 150;
    matref(2, 30) = 7;
    matname(30) = lang(u8"マジックマス"s, u8"Magic mass"s);
    matdesc(30) = lang(u8"謎の魔力の塊"s, u8"Unknown magical mass."s);
    matspot(0, 30) = 18;

    matref(0, 23) = 12;
    matref(1, 23) = 20;
    matref(2, 23) = 7;
    matname(23) = lang(u8"電気"s, u8"Electricity"s);
    matdesc(23) = lang(u8"放電している"s, u8"It is discharging."s);
    matspot(0, 23) = 18;

    matref(0, 44) = 25;
    matref(1, 44) = 150;
    matref(2, 44) = 7;
    matname(44) = lang(u8"生成機械"s, u8"Generator"s);
    matdesc(44) =
        lang(u8"何かを生み出す機械"s, u8"This machine generates something."s);
    matspot(0, 44) = 18;

    matref(0, 50) = 1;
    matref(1, 50) = 30;
    matref(2, 50) = 209;
    matname(50) = lang(u8"魔力の結晶"s, u8"Magic fragment"s);
    matdesc(50) = lang(u8"魔力が込められている"s, u8"This is magical."s);
    matspot(0, 50) = 9;

    matref(0, 46) = 2;
    matref(1, 46) = 20;
    matref(2, 46) = 239;
    matname(46) = lang(u8"枝"s, u8"Branch"s);
    matdesc(46) = lang(u8"枝"s, u8"Broken off of a tree."s);
    matspot(0, 46) = 10;

    matref(0, 33) = 4;
    matref(1, 33) = 20;
    matref(2, 33) = 155;
    matname(33) = lang(u8"革"s, u8"Leather"s);
    matdesc(33) = lang(u8"なめした皮"s, u8"A tanned hide."s);
    matspot(0, 33) = 10;

    matref(0, 53) = 6;
    matref(1, 53) = 20;
    matref(2, 53) = 202;
    matname(53) = lang(u8"ツル"s, u8"Vein"s);
    matdesc(53) = lang(u8"ツル"s, u8"Vein."s);
    matspot(0, 53) = 10;

    matref(0, 47) = 10;
    matref(1, 47) = 20;
    matref(2, 47) = 239;
    matname(47) = lang(u8"頑丈な枝"s, u8"Thick wood"s);
    matdesc(47) =
        lang(u8"なかなか折れない"s, u8"This doesn't break down easily."s);
    matspot(0, 47) = 10;

    matref(0, 37) = 12;
    matref(1, 37) = 60;
    matref(2, 37) = 471;
    matname(37) = lang(u8"曲がった杖"s, u8"Curved stick"s);
    matdesc(37) = lang(u8"杖の役割を果たさない"s, u8"Almost unusable."s);
    matspot(0, 37) = 10;

    matref(0, 54) = 1;
    matref(1, 54) = 50;
    matref(2, 54) = 354;
    matname(54) = lang(u8"接着剤"s, u8"Adhesive"s);
    matdesc(54) = lang(u8"ネトネトしている"s, u8"It's sticky."s);
    matspot(0, 54) = 12;

    matref(0, 49) = 5;
    matref(1, 49) = 50;
    matref(2, 49) = 150;
    matname(49) = lang(u8"記憶の欠片"s, u8"Memory fragment"s);
    matdesc(49) =
        lang(u8"思い出が残っている"s, u8" Reminds you of something."s);
    matspot(0, 49) = 12;

    matref(0, 35) = 8;
    matref(1, 35) = 40;
    matref(2, 35) = 470;
    matname(35) = lang(u8"魔法の紙"s, u8"Magic paper"s);
    matdesc(35) = lang(u8"魔力を秘めた紙"s, u8"Magical paper."s);
    matspot(0, 35) = 12;

    matref(0, 36) = 8;
    matref(1, 36) = 40;
    matref(2, 36) = 354;
    matname(36) = lang(u8"魔法のインク"s, u8"Magic ink"s);
    matdesc(36) = lang(u8"魔力を秘めたインク"s, u8"Wizards love to use it."s);
    matspot(0, 36) = 12;

    matref(0, 12) = 1;
    matref(1, 12) = 10;
    matref(2, 12) = 354;
    matname(12) = lang(u8"海水"s, u8"Seawater"s);
    matdesc(12) = lang(u8"しょっぱい水"s, u8"Very salty."s);
    matspot(0, 12) = 13;

    matref(0, 5) = 1;
    matref(1, 5) = 10;
    matref(2, 5) = 354;
    matname(5) = lang(u8"水滴"s, u8"Waterdrop"s);
    matdesc(5) = lang(u8"水滴"s, u8"A drop of water."s);
    matspot(0, 5) = 13;

    matref(0, 10) = 4;
    matref(1, 10) = 50;
    matref(2, 10) = 354;
    matname(10) = lang(u8"天使の涙"s, u8"Angel's tear"s);
    matdesc(10) = lang(u8"不思議な輝きを放つ涙"s, u8"Hard to gather."s);
    matspot(0, 10) = 13;

    matref(0, 25) = 4;
    matref(1, 25) = 20;
    matref(2, 25) = 354;
    matname(25) = lang(u8"お湯"s, u8"Hot water"s);
    matdesc(25) =
        lang(u8"なぜか冷めない"s, u8"Somehow it's not cooling down."s);
    matspot(0, 25) = 13;

    matref(0, 11) = 8;
    matref(1, 11) = 30;
    matref(2, 11) = 354;
    matname(11) = lang(u8"魔女の涙"s, u8"Witch's tear"s);
    matdesc(11) = lang(u8"決して乾かない涙"s, u8"Never dries up."s);
    matspot(0, 11) = 13;

    matref(0, 20) = 12;
    matref(1, 20) = 15;
    matref(2, 20) = 7;
    matname(20) = lang(u8"雪"s, u8"Snow"s);
    matdesc(20) = lang(u8"なぜか溶けない"s, u8"It won't melt somehow."s);
    matspot(0, 20) = 13;

    matref(0, 7) = 1;
    matref(1, 7) = 40;
    matref(2, 7) = 209;
    matname(7) = lang(u8"ミスリルの欠片"s, u8"Mithril fragment"s);
    matdesc(7) = lang(u8"ミスリルを含んだ鉱石の欠片"s, u8"Contains mithril."s);
    matspot(0, 7) = 14;

    matref(0, 9) = 1;
    matref(1, 9) = 10;
    matref(2, 9) = 209;
    matname(9) = lang(u8"鉄の欠片"s, u8"Iron fragment"s);
    matdesc(9) = lang(u8"鉄分を含んだ鉱石の欠片"s, u8"Contains iron."s);
    matspot(0, 9) = 14;

    matref(0, 26) = 5;
    matref(1, 26) = 10;
    matref(2, 26) = 209;
    matname(26) = lang(u8"火炎石"s, u8"Fire stone"s);
    matdesc(26) = lang(u8"熱を帯びた石"s, u8"This is hot."s);
    matspot(0, 26) = 14;

    matref(0, 27) = 5;
    matref(1, 27) = 10;
    matref(2, 27) = 209;
    matname(27) = lang(u8"冷凍石"s, u8"Ice stone"s);
    matdesc(27) = lang(u8"冷たい石"s, u8"This is cool."s);
    matspot(0, 27) = 14;

    matref(0, 28) = 5;
    matref(1, 28) = 10;
    matref(2, 28) = 209;
    matname(28) = lang(u8"帯電石"s, u8"Discharging stone"s);
    matdesc(28) = lang(u8"電気を帯びた石"s, u8"It's electrified."s);
    matspot(0, 28) = 14;

    matref(0, 52) = 8;
    matref(1, 52) = 50;
    matref(2, 52) = 209;
    matname(52) = lang(u8"上等な石"s, u8"Fine stone"s);
    matdesc(52) = lang(u8"状態の良い石"s, u8"A good quality stone."s);
    matspot(0, 52) = 14;

    matref(0, 8) = 10;
    matref(1, 8) = 40;
    matref(2, 8) = 209;
    matname(8) = lang(u8"エーテルの欠片"s, u8"Ether fragment"s);
    matdesc(8) = lang(u8"エーテルを含んだ鉱石の欠片"s, u8"Contains ether."s);
    matspot(0, 8) = 14;

    matref(0, 22) = 20;
    matref(1, 22) = 100;
    matref(2, 22) = 209;
    matname(22) = lang(u8"元素の欠片"s, u8"Element fragment"s);
    matdesc(22) = lang(u8"元素の力を宿した石"s, u8"Elemental."s);
    matspot(0, 22) = 14;

    matref(0, 51) = 40;
    matref(1, 51) = 200;
    matref(2, 51) = 209;
    matname(51) = lang(u8"混沌の石"s, u8"Chaos stone"s);
    matdesc(51) = lang(u8"混沌の力が封じられた石"s, u8"Chaotic."s);
    matspot(0, 51) = 14;

    matref(0, 13) = 1;
    matref(1, 13) = 10;
    matref(2, 13) = 170;
    matname(13) = lang(u8"唸る草"s, u8"Howling weed"s);
    matdesc(13) = lang(u8"変な音を出す草"s, u8"It's making a whining sound."s);
    matspot(0, 13) = 15;

    matref(0, 14) = 1;
    matref(1, 14) = 20;
    matref(2, 14) = 170;
    matname(14) = lang(u8"赤い草"s, u8"Red weed"s);
    matdesc(14) = lang(u8"ほんのり赤い草"s, u8"A faintly reddish weed."s);
    matspot(0, 14) = 15;

    matref(0, 15) = 1;
    matref(1, 15) = 20;
    matref(2, 15) = 170;
    matname(15) = lang(u8"青い草"s, u8"Blue weed"s);
    matdesc(15) = lang(u8"ほんのり青い草"s, u8"A faintly blueish weed."s);
    matspot(0, 15) = 15;

    matref(0, 16) = 1;
    matref(1, 16) = 10;
    matref(2, 16) = 170;
    matname(16) = lang(u8"呪いの草"s, u8"Curse weed"s);
    matdesc(16) = lang(u8"呪われた草"s, u8"A cursed weed."s);
    matspot(0, 16) = 15;

    matref(0, 42) = 3;
    matref(1, 42) = 20;
    matref(2, 42) = 170;
    matname(42) = lang(u8"薬草"s, u8"Medicinal weed"s);
    matdesc(42) = lang(u8"少し傷を癒す"s, u8"Slightly cures wounds."s);
    matspot(0, 42) = 15;

    matref(0, 29) = 7;
    matref(1, 29) = 50;
    matref(2, 29) = 170;
    matname(29) = lang(u8"浮き草"s, u8"Floating weed"s);
    matdesc(29) = lang(u8"とても軽い草"s, u8"Very light."s);
    matspot(0, 29) = 15;

    matref(0, 17) = 12;
    matref(1, 17) = 20;
    matref(2, 17) = 170;
    matname(17) = lang(u8"聖なる草"s, u8"Holy weed"s);
    matdesc(17) = lang(u8"祝福された草"s, u8"It's blessed."s);
    matspot(0, 17) = 15;

    matref(0, 24) = 15;
    matref(1, 24) = 40;
    matref(2, 24) = 8;
    matname(24) = lang(u8"黒い霧"s, u8"Black mist"s);
    matdesc(24) = lang(u8"真っ黒な霧"s, u8"It's as black as coal."s);
    matspot(0, 24) = 15;

    matref(0, 34) = 25;
    matref(1, 34) = 200;
    matref(2, 34) = 354;
    matname(34) = lang(u8"世界樹の樹液"s, u8"Sap of Yaggdrasil"s);
    matdesc(34) = lang(u8"どんな傷も癒す樹液"s, u8"It's pretty rare."s);
    matspot(0, 34) = 15;

    matspot(1, 34) = 10;
    matref(0, 4) = 1;
    matref(1, 4) = 10;
    matref(2, 4) = 436;
    matname(4) = lang(u8"鳥の羽"s, u8"Bird's feather"s);
    matdesc(4) = lang(u8"普通の鳥の羽"s, u8"A piece of Feather."s);
    matspot(0, 4) = 16;

    matref(0, 18) = 1;
    matref(1, 18) = 80;
    matref(2, 18) = 301;
    matname(18) = lang(u8"ウサギの尻尾"s, u8"Rabbit's tail"s);
    matdesc(18) = lang(u8"幸運を呼ぶ尻尾"s, u8"Scut."s);
    matspot(0, 18) = 16;

    matref(0, 31) = 1;
    matref(1, 31) = 20;
    matref(2, 31) = 304;
    matname(31) = lang(u8"ヒトの遺伝子"s, u8"Human gene"s);
    matdesc(31) = lang(u8"普通の遺伝子"s, u8"It's common."s);
    matspot(0, 31) = 16;

    matref(0, 39) = 3;
    matref(1, 39) = 20;
    matref(2, 39) = 301;
    matname(39) = lang(u8"クマの尻尾"s, u8"Bear's tail"s);
    matdesc(39) = lang(u8"とても短い"s, u8"Very short."s);
    matspot(0, 39) = 16;

    matref(0, 19) = 5;
    matref(1, 19) = 15;
    matref(2, 19) = 304;
    matname(19) = lang(u8"トロールの遺伝子"s, u8"Troll gene"s);
    matdesc(19) = lang(u8"再生する遺伝子"s, u8"It's regenerating."s);
    matspot(0, 19) = 16;

    matref(0, 32) = 8;
    matref(1, 32) = 40;
    matref(2, 32) = 304;
    matname(32) = lang(u8"魔女の瞳"s, u8"Witch's eye"s);
    matdesc(32) = lang(u8"まだ動いている"s, u8"These eyes are still moving."s);
    matspot(0, 32) = 16;

    matref(0, 21) = 15;
    matref(1, 21) = 45;
    matref(2, 21) = 209;
    matname(21) = lang(u8"フェアリーダスト"s, u8"Fairy dust"s);
    matdesc(21) = lang(u8"妖精の燐粉"s, u8"Fairies leave it."s);
    matspot(0, 21) = 16;
}



int get_required_craft_materials()
{
    matneed(0) = -1;
    matneed(1) = -1;
    matneed(2) = -1;
    matneed(3) = -1;
    matneed(4) = -1;
    matneed(5) = -1;
    matneed(6) = -1;
    matneed(7) = -1;
    matneed(8) = -1;
    matneed(9) = -1;
    if (matid == 502)
    {
        matval(0) = 179;
        matval(1) = 40;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 44;
        matneed(3) = 2;
        matneed(4) = 51;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 501)
    {
        matval(0) = 179;
        matval(1) = 13;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 44;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 500)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 38;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 455)
    {
        matval(0) = 177;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 4;
        matneed(2) = 53;
        matneed(3) = 2;
        matneed(4) = 7;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 411)
    {
        matval(0) = 179;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 4;
        matneed(2) = 36;
        matneed(3) = 1;
        matneed(4) = 23;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 408)
    {
        matval(0) = 176;
        matval(1) = 11;
        matval(2) = 100;
        matneed(0) = 47;
        matneed(1) = 3;
        matneed(2) = 52;
        matneed(3) = 2;
        matneed(4) = 21;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 407)
    {
        matval(0) = 178;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 20;
        matneed(3) = 3;
        matneed(4) = 42;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 405)
    {
        matval(0) = 176;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 48;
        matneed(1) = 8;
        matneed(2) = 9;
        matneed(3) = 5;
        matneed(4) = 52;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 403)
    {
        matval(0) = 176;
        matval(1) = 12;
        matval(2) = 100;
        matneed(0) = 47;
        matneed(1) = 5;
        matneed(2) = 16;
        matneed(3) = 2;
        matneed(4) = 10;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 402)
    {
        matval(0) = 177;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 53;
        matneed(1) = 7;
        matneed(2) = 45;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 401)
    {
        matval(0) = 179;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 3;
        matneed(1) = 8;
        matneed(2) = 53;
        matneed(3) = 4;
        matneed(4) = 21;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 400)
    {
        matval(0) = 176;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 3;
        matneed(1) = 6;
        matneed(2) = 46;
        matneed(3) = 4;
        matneed(4) = 2;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 399)
    {
        matval(0) = 177;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 5;
        matneed(2) = 33;
        matneed(3) = 2;
        matneed(4) = 20;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 395)
    {
        matval(0) = 179;
        matval(1) = 30;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 5;
        matneed(2) = 30;
        matneed(3) = 1;
        matneed(4) = 44;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 390)
    {
        matval(0) = 179;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 36;
        matneed(3) = 2;
        matneed(4) = 30;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 389)
    {
        matval(0) = 179;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 36;
        matneed(3) = 2;
        matneed(4) = 17;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 388)
    {
        matval(0) = 179;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 17;
        matneed(3) = 2;
        matneed(4) = 23;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 384)
    {
        matval(0) = 179;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 2;
        matneed(2) = 17;
        matneed(3) = 4;
        matneed(4) = 16;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 362)
    {
        matval(0) = 179;
        matval(1) = 18;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 49;
        matneed(3) = 2;
        matneed(4) = 30;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 287)
    {
        matval(0) = 178;
        matval(1) = 45;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 2;
        matneed(2) = 10;
        matneed(3) = 5;
        matneed(4) = 25;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 286)
    {
        matval(0) = 178;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 14;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 285)
    {
        matval(0) = 178;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 4;
        matneed(2) = 15;
        matneed(3) = 4;
        return 1;
    }
    if (matid == 253)
    {
        matval(0) = 178;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 4;
        return 1;
    }
    if (matid == 245)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 2;
        matneed(3) = 2;
        matneed(4) = 4;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 242)
    {
        matval(0) = 179;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 35;
        matneed(1) = 1;
        matneed(2) = 36;
        matneed(3) = 1;
        matneed(4) = 23;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 236)
    {
        matval(0) = 179;
        matval(1) = 4;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 3;
        matneed(2) = 13;
        matneed(3) = 2;
        matneed(4) = 2;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 209)
    {
        matval(0) = 179;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 4;
        matneed(2) = 17;
        matneed(3) = 2;
        matneed(4) = 16;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 175)
    {
        matval(0) = 176;
        matval(1) = 17;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 28;
        matneed(3) = 5;
        matneed(4) = 54;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 123)
    {
        matval(0) = 176;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 26;
        matneed(3) = 5;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 122)
    {
        matval(0) = 176;
        matval(1) = 14;
        matval(2) = 100;
        matneed(0) = 37;
        matneed(1) = 1;
        matneed(2) = 27;
        matneed(3) = 5;
        matneed(4) = 20;
        matneed(5) = 5;
        return 1;
    }
    if (matid == 120)
    {
        matval(0) = 176;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 9;
        matneed(3) = 4;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 119)
    {
        matval(0) = 176;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 14;
        matneed(3) = 4;
        matneed(4) = 54;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 76)
    {
        matval(0) = 178;
        matval(1) = 40;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 2;
        matneed(2) = 5;
        matneed(3) = 5;
        matneed(4) = 42;
        matneed(5) = 4;
        return 1;
    }
    if (matid == 75)
    {
        matval(0) = 178;
        matval(1) = 30;
        matval(2) = 100;
        matneed(0) = 34;
        matneed(1) = 1;
        matneed(2) = 25;
        matneed(3) = 4;
        matneed(4) = 14;
        matneed(5) = 5;
        return 1;
    }
    if (matid == 74)
    {
        matval(0) = 178;
        matval(1) = 25;
        matval(2) = 100;
        matneed(0) = 15;
        matneed(1) = 3;
        matneed(2) = 25;
        matneed(3) = 4;
        matneed(4) = 42;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 72)
    {
        matval(0) = 178;
        matval(1) = 20;
        matval(2) = 100;
        matneed(0) = 10;
        matneed(1) = 1;
        matneed(2) = 5;
        matneed(3) = 4;
        matneed(4) = 42;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 71)
    {
        matval(0) = 178;
        matval(1) = 15;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 3;
        matneed(2) = 42;
        matneed(3) = 2;
        return 1;
    }
    if (matid == 70)
    {
        matval(0) = 178;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 25;
        matneed(1) = 3;
        matneed(2) = 14;
        matneed(3) = 1;
        matneed(4) = 15;
        matneed(5) = 1;
        return 1;
    }
    if (matid == 69)
    {
        matval(0) = 178;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 3;
        matneed(2) = 15;
        matneed(3) = 2;
        return 1;
    }
    if (matid == 68)
    {
        matval(0) = 178;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 5;
        matneed(1) = 3;
        matneed(2) = 14;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 66)
    {
        matval(0) = 177;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 33;
        matneed(1) = 4;
        matneed(2) = 39;
        matneed(3) = 5;
        matneed(4) = 18;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 65)
    {
        matval(0) = 177;
        matval(1) = 10;
        matval(2) = 100;
        matneed(0) = 33;
        matneed(1) = 5;
        matneed(2) = 54;
        matneed(3) = 3;
        matneed(4) = 31;
        matneed(5) = 6;
        return 1;
    }
    if (matid == 19)
    {
        matval(0) = 176;
        matval(1) = 5;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 4;
        matneed(3) = 4;
        matneed(4) = 29;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 18)
    {
        matval(0) = 176;
        matval(1) = 8;
        matval(2) = 100;
        matneed(0) = 6;
        matneed(1) = 1;
        matneed(2) = 32;
        matneed(3) = 2;
        matneed(4) = 49;
        matneed(5) = 2;
        return 1;
    }
    if (matid == 16)
    {
        matval(0) = 179;
        matval(1) = 7;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 3;
        matneed(2) = 2;
        matneed(3) = 2;
        matneed(4) = 4;
        matneed(5) = 3;
        return 1;
    }
    if (matid == 14)
    {
        matval(0) = 179;
        matval(1) = 1;
        matval(2) = 100;
        matneed(0) = 43;
        matneed(1) = 2;
        matneed(2) = 49;
        matneed(3) = 1;
        return 1;
    }
    if (matid == 8)
    {
        matval(0) = 177;
        matval(1) = 4;
        matval(2) = 100;
        matneed(0) = 45;
        matneed(1) = 6;
        matneed(2) = 53;
        matneed(3) = 3;
        matneed(4) = 50;
        matneed(5) = 2;
        return 1;
    }
    return -1;
}



void crafting_menu()
{
    int matuse = 0;
label_18551_internal:
    listmax = 0;
    page = 0;
    pagesize = 10;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_load();
    if (invctrl == 0)
    {
        for (int cnt = 0, cnt_end = (maxitemid); cnt < cnt_end; ++cnt)
        {
            matid = cnt;
            int stat = get_required_craft_materials();
            if (stat == -1)
            {
                continue;
            }
            if (prodtype == 2)
            {
                if (matval != 178)
                {
                    continue;
                }
            }
            if (prodtype == 1)
            {
                if (matval != 176)
                {
                    continue;
                }
            }
            if (prodtype == 3)
            {
                if (matval != 179)
                {
                    continue;
                }
            }
            if (prodtype == 4)
            {
                if (matval != 177)
                {
                    continue;
                }
            }
            if (sdata(matval, 0) + 3 < matval(1))
            {
                continue;
            }
            listn(0, listmax) = ""s + prodcheck();
            list(0, listmax) = cnt;
            list(1, listmax) = 0;
            ++listmax;
        }
    }
    else
    {
        for (int cnt = 0; cnt < 50; ++cnt)
        {
            listn(0, listmax) = ""s + prodcheck();
            list(0, listmax) = 630;
            list(1, listmax) = cnt;
            ++listmax;
        }
    }
    windowshadow = 1;
label_1857_internal:
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
    s(0) = lang(u8"生産品の選択"s, u8"Production"s);
    s(1) = strhint2 + strhint3b;
    display_window((windoww - 640) / 2 + inf_screenx, winposy(448), 640, 448);
    display_topic(lang(u8"生産品"s, u8"Product"s), wx + 28, wy + 36);
    display_topic(lang(u8"説明"s, u8"Detail"s), wx + 296, wy + 36);
    display_topic(lang(u8"詳細"s, u8"Requirement"s), wx + 28, wy + 258);
    display_topic(lang(u8"必要素材"s, u8"Material"s), wx + 28, wy + 304);
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
    cs_listbk();
    f = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i(0) = list(0, p);
        i(1) = list(1, p);
        if (cs == cnt)
        {
            matid = i;
            if (invctrl == 0)
            {
                get_required_craft_materials();
                font(13 - en * 2);
                s = lang(u8"必要スキル: "s, u8"Skill needed: "s);
                if (matval == 178)
                {
                    s += lang(u8"錬金術"s, u8"Alchemy"s);
                }
                if (matval == 176)
                {
                    s += lang(u8"大工"s, u8"Carpentory"s);
                }
                if (matval == 179)
                {
                    s += lang(u8"宝石細工"s, u8"Jewelling"s);
                }
                if (matval == 177)
                {
                    s += lang(u8"裁縫"s, u8"Tailoring"s);
                }
                s += u8" "s + matval(1) + u8"("s + sdata(matval, 0) + u8")"s;
                if (matval(1) <= sdata(matval, 0))
                {
                    color(30, 30, 200);
                }
                else
                {
                    color(200, 30, 30);
                }
                pos(wx + 37, wy + 288);
                mes(s + u8" "s);
                color(0, 0, 0);
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                int j0 = matneed(cnt * 2);
                int j1 = matneed(cnt * 2 + 1);
                if (j0 == -1)
                {
                    break;
                }
                s = matname(j0) + lang(u8" ? "s, u8" x "s) + j1 + u8"("s
                    + mat(j0) + u8")"s;
                if (mat(j0) >= j1)
                {
                    color(30, 30, 200);
                }
                else
                {
                    color(200, 30, 30);
                }
                pos(wx + 37 + cnt % 3 * 192, wy + 334 + cnt / 3 * 16);
                mes(s);
                color(0, 0, 0);
            }
            f = 1;
        }
        s = ioriginalnameref(i);
        p(1) = ipicref(i);
        prepare_item_image(p(1), 0);
        s(1) = lang(u8"アイテム["s + s + u8"]"s, u8"Make ["s + s + u8"]"s);
        font(14 - en * 2);
        if (elona::stoi(listn(0, p)) == -1)
        {
            p(2) = 3;
        }
        else
        {
            p(2) = 0;
        }
        cs_list(cs == cnt, cnven(s), wx + 86, wy + 66 + cnt * 19 - 1, 0, p(2));
        pos(wx + 308, wy + 66 + cnt * 19 + 2);
        mes(s(1));
        pos(wx + 37, wy + 69 + cnt * 19 + 2);
        gmode(2, inf_tiles, inf_tiles);
        grotate(1, 0, 960, 0, chipi(2, p(1)), chipi(3, p(1)));
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    if (f == 1 || listmax == 0)
    {
        redraw();
    }
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (p != -1)
    {
        matid = p;
        get_required_craft_materials();
        s = ioriginalnameref(matid);
        if (prodcheck() == -1)
        {
            snd(27);
            txt(lang(
                u8"生産の条件を満たしてない。"s,
                u8"You don't meet requirements to create the item."s));
            goto label_1857_internal;
        }
        if (!inv_getspace(0))
        {
            snd(27);
            txt(lang(
                u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
            goto label_1857_internal;
        }
        matuse = 0;
        for (int cnt = 0; cnt < 6; ++cnt)
        {
            int j0 = matneed(cnt * 2);
            int j1 = matneed(cnt * 2 + 1);
            if (j0 == -1)
            {
                break;
            }
            mat(j0) -= j1;
            matuse += j1;
        }
        snd(58);
        fixlv = 2;
        if (rnd(200 + matval(1) * 2) < sdata(matval, 0) + 20)
        {
            fixlv = 4;
        }
        if (rnd(100 + matval(1) * 2) < sdata(matval, 0) + 20)
        {
            fixlv = 3;
        }
        flt(calcobjlv(sdata(matval, 0)), calcfixlv(fixlv));
        itemcreate(0, p, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"を製造した。"s,
            u8"You producted "s + itemname(ci, 1) + u8"."s));
        r2 = matuse;
        gain_crafting_experience(matval);
        chara_refresh(0);
        render_hud();
        page_save();
        goto label_18551_internal;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1857_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1857_internal;
        }
    }
    if (key == key_cancel)
    {
        return;
    }
    goto label_1857_internal;
}


int prodcheck()
{
    int f_at_m110 = 0;
    elona_vector1<int> j_at_m110;
    f_at_m110 = 1;
    if (matval(1) > sdata(matval, 0))
    {
        f_at_m110 = -1;
    }
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        j_at_m110(0) = matneed(cnt * 2);
        j_at_m110(1) = matneed(cnt * 2 + 1);
        if (j_at_m110 == -1)
        {
            break;
        }
        if (mat(j_at_m110) < j_at_m110(1))
        {
            f_at_m110 = -1;
        }
    }
    return f_at_m110;
}


} // namespace elona
