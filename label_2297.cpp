#include "elona.hpp"
#include "variables.hpp"



#define RACE(is_extra_race, name) \
    do \
    { \
        if (val == (is_extra_race) ? 1 : 0) \
        { \
            listn(1, listmax) = (name); \
            list(0, listmax) = (is_extra_race) ? 1 : 0; \
            ++listmax; \
        } \
    } while (0)

#define EXTRA_RACE(name) RACE(true, name)
#define BASIC_RACE(name) RACE(false, name)



namespace
{


void label_2297_dbmode1()
{
    BASIC_RACE(u8"yerles");
    BASIC_RACE(u8"eulderna");
    BASIC_RACE(u8"fairy");
    BASIC_RACE(u8"dwarf");
    BASIC_RACE(u8"juere");
    BASIC_RACE(u8"elea");
    BASIC_RACE(u8"snail");
    BASIC_RACE(u8"lich");
    BASIC_RACE(u8"goblin");
    BASIC_RACE(u8"golem");
    BASIC_RACE(u8"mutant");

    EXTRA_RACE(u8"kobolt");
    EXTRA_RACE(u8"orc");
    EXTRA_RACE(u8"troll");
    EXTRA_RACE(u8"lizardman");
    EXTRA_RACE(u8"minotaur");
    EXTRA_RACE(u8"norland");
    EXTRA_RACE(u8"asura");
    EXTRA_RACE(u8"slime");
    EXTRA_RACE(u8"wolf");
    EXTRA_RACE(u8"zombie");
    EXTRA_RACE(u8"rabbit");
    EXTRA_RACE(u8"sheep");
    EXTRA_RACE(u8"frog");
    EXTRA_RACE(u8"centipede");
    EXTRA_RACE(u8"mandrake");
    EXTRA_RACE(u8"beetle");
    EXTRA_RACE(u8"mushroom");
    EXTRA_RACE(u8"bat");
    EXTRA_RACE(u8"ent");
    EXTRA_RACE(u8"hound");
    EXTRA_RACE(u8"ghost");
    EXTRA_RACE(u8"spirit");
    EXTRA_RACE(u8"eye");
    EXTRA_RACE(u8"wyvern");
    EXTRA_RACE(u8"wasp");
    EXTRA_RACE(u8"giant");
    EXTRA_RACE(u8"imp");
    EXTRA_RACE(u8"hand");
    EXTRA_RACE(u8"snake");
    EXTRA_RACE(u8"drake");
    EXTRA_RACE(u8"bear");
    EXTRA_RACE(u8"armor");
    EXTRA_RACE(u8"medusa");
    EXTRA_RACE(u8"cupid");
    EXTRA_RACE(u8"phantom");
    EXTRA_RACE(u8"harpy");
    EXTRA_RACE(u8"dragon");
    EXTRA_RACE(u8"dinosaur");
    EXTRA_RACE(u8"cerberus");
    EXTRA_RACE(u8"spider");
    EXTRA_RACE(u8"rock");
    EXTRA_RACE(u8"crab");
    EXTRA_RACE(u8"skeleton");
    EXTRA_RACE(u8"piece");
    EXTRA_RACE(u8"cat");
    EXTRA_RACE(u8"dog");
    EXTRA_RACE(u8"roran");
    EXTRA_RACE(u8"rat");
    EXTRA_RACE(u8"shell");
    EXTRA_RACE(u8"catgod");
    EXTRA_RACE(u8"machinegod");
    EXTRA_RACE(u8"undeadgod");
    EXTRA_RACE(u8"machine");
    EXTRA_RACE(u8"wisp");
    EXTRA_RACE(u8"chicken");
    EXTRA_RACE(u8"stalker");
    EXTRA_RACE(u8"catsister");
    EXTRA_RACE(u8"yeek");
    EXTRA_RACE(u8"yith");
    EXTRA_RACE(u8"servant");
    EXTRA_RACE(u8"horse");
    EXTRA_RACE(u8"god");
    EXTRA_RACE(u8"quickling");
    EXTRA_RACE(u8"metal");
    EXTRA_RACE(u8"bike");
}


} // namespace



namespace elona
{



int label_2297()
{
    if (dbmode == 1)
    {
        label_2297_dbmode1();
        return 0;
    }

    if (dbidn == u8"kobolt"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 250;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"コボルト"s, cnven(u8"kobolt"s));
            cpicref = 171;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 171;
            ref2 = 171;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"kobolt"s;
            cdata(158, rc) = 1;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 150;
            if (rnd(100) < 50)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 171;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 6);
            skillinit(12, rc, 5);
            skillinit(13, rc, 3);
            skillinit(14, rc, 2);
            skillinit(15, rc, 2);
            skillinit(16, rc, 4);
            skillinit(17, rc, 2);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(300, rc, 3);
            skillinit(157, rc, 2);
            skillinit(174, rc, 3);
            s(1) = u8"HD|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"orc"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 300;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"オーク"s, cnven(u8"orc"s));
            cpicref = 165;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 165;
            ref2 = 165;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"orc"s;
            cdata(158, rc) = 2;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 150;
            if (rnd(100) < 51)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 165;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 130);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 6);
            skillinit(12, rc, 3);
            skillinit(13, rc, 2);
            skillinit(14, rc, 2);
            skillinit(15, rc, 3);
            skillinit(16, rc, 4);
            skillinit(17, rc, 2);
            skillinit(18, rc, 70);
            skillinit(106, rc, 1);
            skillinit(154, rc, 3);
            skillinit(169, rc, 3);
            skillinit(168, rc, 3);
            s(1) = u8"HD|BD|BK|HA|HA|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"troll"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 250;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"トロール"s, cnven(u8"troll"s));
            cpicref = 391;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 391;
            ref2 = 391;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"troll"s;
            cdata(158, rc) = 3;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 400;
            if (rnd(100) < 51)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 391;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 90);
            skillinit(3, rc, 80);
            skillinit(10, rc, 10);
            skillinit(11, rc, 9);
            skillinit(12, rc, 1);
            skillinit(13, rc, 2);
            skillinit(14, rc, 2);
            skillinit(15, rc, 2);
            skillinit(16, rc, 3);
            skillinit(17, rc, 3);
            skillinit(18, rc, 60);
            skillinit(106, rc, 3);
            skillinit(154, rc, 40);
            s(1) = u8"HD|BD|BK|HA|HA|A_|W_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"lizardman"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 300;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"リザードマン"s, cnven(u8"lizardman"s));
            cpicref = 397;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 397;
            ref2 = 397;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"lizardman"s;
            cdata(158, rc) = 4;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 240;
            if (rnd(100) < 51)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 397;
            cdata_dv_correction_value(rc) = 120;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 70);
            skillinit(10, rc, 7);
            skillinit(11, rc, 5);
            skillinit(12, rc, 6);
            skillinit(13, rc, 7);
            skillinit(14, rc, 4);
            skillinit(15, rc, 4);
            skillinit(16, rc, 5);
            skillinit(17, rc, 3);
            skillinit(18, rc, 80);
            skillinit(106, rc, 2);
            skillinit(104, rc, 3);
            skillinit(168, rc, 3);
            skillinit(173, rc, 2);
            s(1) = u8"HD|BD|BK|HA|HA|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"minotaur"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 300;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ミノタウロス"s, cnven(u8"minotaur"s));
            cpicref = 398;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 398;
            ref2 = 398;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"minotaur"s;
            cdata(158, rc) = 5;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 350;
            if (rnd(100) < 51)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 398;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 160);
            skillinit(3, rc, 60);
            skillinit(10, rc, 12);
            skillinit(11, rc, 8);
            skillinit(12, rc, 3);
            skillinit(13, rc, 4);
            skillinit(14, rc, 3);
            skillinit(15, rc, 4);
            skillinit(16, rc, 7);
            skillinit(17, rc, 4);
            skillinit(18, rc, 65);
            skillinit(106, rc, 3);
            skillinit(152, rc, 4);
            skillinit(186, rc, 3);
            s(1) = u8"HD|BD|HA|HA|R_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"yerles"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 220;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"イェルス"s, cnven(u8"yerles"s));
            cpicref = 1;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"シエラ・テール西方で急速に台頭してきた新王国の人間が、イェルスです。彼らは現実的な思考を好み、エイス・テールの文明を崇拝する一方で、それが例え自らの理解を超えていても、利益になるものであれば積極的にとりいれようとする柔軟性を持っています。彼らは高い学習能力を持ち、ほぼ全ての職業に適応することができます。イェルスは機械武装の扱いにたけ、追加の成長ボーナスを受け取ります。"s,
                u8"The young kingdom which worships the ancient scientific civilization called Eyth Terre has gained power in the west. While they are realists amd materialistic, they are also adaptable to things that are beyond their comprehension if it benefits the kingdom. Yerles fit well in every class with their outstanding learning ability. They receive extra skill points with every level that they gain."s);
            ref1 = 1;
            ref2 = 1;
            ref2 = 2;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"yerles"s;
            cdata(158, rc) = 6;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(20) + 15);
            cdata_height(rc) = 165;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 1;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 2;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 110);
            skillinit(3, rc, 90);
            skillinit(10, rc, 7);
            skillinit(11, rc, 8);
            skillinit(12, rc, 8);
            skillinit(13, rc, 8);
            skillinit(14, rc, 12);
            skillinit(15, rc, 8);
            skillinit(16, rc, 8);
            skillinit(17, rc, 7);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(110, rc, 5);
            skillinit(150, rc, 3);
            skillinit(156, rc, 2);
            skillinit(111, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"norland"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 220;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ノーランド"s, cnven(u8"norland"s));
            cpicref = 1;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 1;
            ref2 = 1;
            ref2 = 2;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"norland"s;
            cdata(158, rc) = 7;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(20) + 15);
            cdata_height(rc) = 170;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 1;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 2;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 90);
            skillinit(10, rc, 8);
            skillinit(11, rc, 8);
            skillinit(12, rc, 6);
            skillinit(13, rc, 6);
            skillinit(14, rc, 7);
            skillinit(15, rc, 9);
            skillinit(16, rc, 7);
            skillinit(17, rc, 6);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(172, rc, 3);
            skillinit(152, rc, 3);
            skillinit(167, rc, 3);
            skillinit(188, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"eulderna"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 180;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"エウダーナ"s, cnven(u8"eulderna"s));
            cpicref = 5;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"エウダーナは最も古い国の一つで、今もなお強力な大国です。彼らは、自分たちのみが世界を動かすに値すると考える選民意識の持ち主で、エリートであり、完ぺき主義者です。エウダーナは魔法や魔法道具の扱いにたけ、キャスターや中間的な職業に向いています。彼らは高い詠唱能力と魔法への耐性をもっています。"s,
                u8"Eulderna is one of the most ancient races in Sierra Terre. Egoism and elitism dominate every thought behind actions of these perfectionists. They, are suitable to caster or hybrid classes as they are adept at magics and using magical devices. Euldernas have resistance to magic."s);
            ref1 = 5;
            ref2 = 5;
            ref2 = 6;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"eulderna"s;
            cdata(158, rc) = 8;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(20) + 16);
            cdata_height(rc) = 175;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 5;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 6;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 100);
            skillinit(10, rc, 6);
            skillinit(11, rc, 7);
            skillinit(12, rc, 7);
            skillinit(13, rc, 10);
            skillinit(14, rc, 8);
            skillinit(15, rc, 10);
            skillinit(16, rc, 12);
            skillinit(17, rc, 8);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(172, rc, 5);
            skillinit(150, rc, 3);
            skillinit(174, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"fairy"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 180;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"妖精"s, cnven(u8"fairy"s));
            cpicref = 390;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"妖精は可憐で非力で儚い生物です。彼女達は、人間族と比べて高い魔力と回避力、目にも止まらぬすばしっこさを持ち、ほぼ全ての耐性に高い抵抗力を持っています。反面、妖精は重さ1s以上の装備を身につけることができず、防御力をあげるのは困難です。その体力の低さからも、まともな物理攻撃を一度でもくらうと危機に陥るでしょう。"s,
                u8"Fairies are cute, mysterious, and fragile. Compared to the human race, they are gifted with superior skills of using magic and evading. In contrast, the lack of physical power makes it difficult for them to carry even the smallest of things, making it impossible for them to wear equipment weighing more than 1s. Fairies have outstanding resistances to all elements."s);
            ref1 = 390;
            ref2 = 390;
            ref2 = 390;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"fairy"s;
            cdata(158, rc) = 9;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(100) + 5);
            cdata_height(rc) = 50;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 390;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 390;
            }
            sdata(60, rc) = 200;
            sdata(53, rc) = 200;
            sdata(58, rc) = 200;
            sdata(56, rc) = 200;
            sdata(54, rc) = 200;
            sdata(57, rc) = 200;
            sdata(59, rc) = 200;
            cdata_dv_correction_value(rc) = 250;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 40);
            skillinit(3, rc, 130);
            skillinit(10, rc, 3);
            skillinit(11, rc, 4);
            skillinit(12, rc, 9);
            skillinit(13, rc, 10);
            skillinit(14, rc, 8);
            skillinit(15, rc, 8);
            skillinit(16, rc, 13);
            skillinit(17, rc, 12);
            skillinit(18, rc, 120);
            skillinit(106, rc, 1);
            skillinit(172, rc, 5);
            skillinit(300, rc, 3);
            skillinit(171, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"asura"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 100;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"阿修羅"s, cnven(u8"asura"s));
            cpicref = 405;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 405;
            ref2 = 405;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"asura"s;
            cdata(158, rc) = 10;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(20) + 15);
            cdata_height(rc) = 220;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 405;
            cdata_dv_correction_value(rc) = 200;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 70);
            skillinit(10, rc, 11);
            skillinit(11, rc, 9);
            skillinit(12, rc, 14);
            skillinit(13, rc, 6);
            skillinit(14, rc, 4);
            skillinit(15, rc, 4);
            skillinit(16, rc, 5);
            skillinit(17, rc, 5);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(166, rc, 30);
            skillinit(187, rc, 6);
            skillinit(161, rc, 4);
            s(1) = u8"HA|HA|HA|HA|N_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"slime"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 700;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"スライム"s, cnven(u8"slime"s));
            cpicref = 168;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 168;
            ref2 = 168;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"slime"s;
            cdata(158, rc) = 11;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 2;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 1);
            cdata_height(rc) = 40;
            if (rnd(100) < 54)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 168;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 100);
            skillinit(10, rc, 4);
            skillinit(11, rc, 5);
            skillinit(12, rc, 7);
            skillinit(13, rc, 5);
            skillinit(14, rc, 6);
            skillinit(15, rc, 8);
            skillinit(16, rc, 4);
            skillinit(17, rc, 13);
            skillinit(18, rc, 55);
            skillinit(106, rc, 2);
            skillinit(173, rc, 2);
            skillinit(183, rc, 3);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"wolf"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 800;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"狼"s, cnven(u8"wolf"s));
            cpicref = 254;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 254;
            ref2 = 254;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"wolf"s;
            cdata(158, rc) = 12;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 2);
            cdata_height(rc) = 100;
            if (rnd(100) < 55)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 254;
            cdata_dv_correction_value(rc) = 140;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 8);
            skillinit(12, rc, 6);
            skillinit(13, rc, 11);
            skillinit(14, rc, 7);
            skillinit(15, rc, 8);
            skillinit(16, rc, 4);
            skillinit(17, rc, 6);
            skillinit(18, rc, 80);
            skillinit(106, rc, 2);
            skillinit(173, rc, 2);
            skillinit(187, rc, 2);
            s(1) = u8"HD|N_|BD|BK|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"dwarf"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 150;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"丘の民"s, cnven(u8"dwarf"s));
            cpicref = 66;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"丘の民、別名ドワーフは頑強で無骨な背の低い種族です。彼らは高い耐久力と力を持ち、幾つかの生産系の技術にも精通しています。彼らには暗黒と強い毒への耐性があります。"s,
                u8"A Dwarf is a child of the earth. As tough and unyielding as the mountains they love, most Dwarves will live their whole lives underground, mining, smelting, and smithing. Some few leave the depths to become adventurers, hoping to make enough coin to start their own clan. Good with technology, and tough against things dark and poisonous."s);
            ref1 = 66;
            ref2 = 66;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"dwarf"s;
            cdata(158, rc) = 13;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(60) + 20);
            cdata_height(rc) = 100;
            if (rnd(100) < 56)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 66;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 100);
            skillinit(10, rc, 10);
            skillinit(11, rc, 11);
            skillinit(12, rc, 8);
            skillinit(13, rc, 6);
            skillinit(14, rc, 6);
            skillinit(15, rc, 7);
            skillinit(16, rc, 6);
            skillinit(17, rc, 6);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(184, rc, 4);
            skillinit(179, rc, 3);
            skillinit(163, rc, 4);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"juere"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 210;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ジューア"s, cnven(u8"juere"s));
            cpicref = 9;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"ジューアは、元は盗賊や悪人のあつまりであり、今もならず者国家として嫌われる国です。彼らは束縛されることを嫌い、自分の意思を尊重し、自由に生きることを好みます。ジューアは手先が器用で、鋭い感覚と高い学習能力を持ち、多彩な技術に精通しています。彼らはパフォーマンスをすることで生計をたてることができ、食事をゆっくりと消化し、採取スポットでより長い時間採取できます。"s,
                u8"The Juere are a people wild and free. Scorning the \"weaker\" laws of others, they quickly learn the tricks and technologies of others before ever moving onwards. Their pride makes them great performers, and are used to being hungry for long periods of time. Nimble of hand, and Bold of character, no two Juere are ever the same."s);
            ref1 = 9;
            ref2 = 9;
            ref2 = 10;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"juere"s;
            cdata(158, rc) = 14;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 165;
            if (rnd(100) < 50)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 9;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 10;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 100);
            skillinit(10, rc, 7);
            skillinit(11, rc, 8);
            skillinit(12, rc, 12);
            skillinit(13, rc, 10);
            skillinit(14, rc, 10);
            skillinit(15, rc, 8);
            skillinit(16, rc, 8);
            skillinit(17, rc, 11);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(183, rc, 4);
            skillinit(158, rc, 2);
            skillinit(156, rc, 2);
            skillinit(111, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"zombie"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 100;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ゾンビ"s, cnven(u8"zombie"s));
            cpicref = 167;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 167;
            ref2 = 167;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"zombie"s;
            cdata(158, rc) = 15;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(200) + 10);
            cdata_height(rc) = 160;
            if (rnd(100) < 50)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 167;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 100);
            skillinit(10, rc, 10);
            skillinit(11, rc, 8);
            skillinit(12, rc, 2);
            skillinit(13, rc, 2);
            skillinit(14, rc, 1);
            skillinit(15, rc, 6);
            skillinit(16, rc, 6);
            skillinit(17, rc, 2);
            skillinit(18, rc, 45);
            skillinit(106, rc, 3);
            skillinit(184, rc, 3);
            skillinit(185, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|R_|A_|W_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"elea"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 120;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"エレア"s, cnven(u8"elea"s));
            cpicref = 3;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"エレアは、幾つもの世代を生き抜いたエルフの末梢で、他の種族から姿を隠し、静かに生活しています。彼らこそが、エイス・テールを滅ぼした災厄の元凶であるとするイェルスの皇子のバッシングにより、彼らは他の種族から嫌われています。エレアはエーテルへの耐性と高い魔力を持ち、魔力の反動によるダメージを軽減することができます。"s,
                u8"Elea, known by the other peoples of the world as \"Elf's\", live quietly in their forests, far from man. Nimble and graceful, their bows are of legend, and their wizards have forgotten more of magic than many will ever know. Still, the young ones from time to time leave and go on adventures, if only to fill their memories for their long lives."s);
            ref1 = 3;
            ref2 = 3;
            ref2 = 4;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"elea"s;
            cdata(158, rc) = 16;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(200) + 10);
            cdata_height(rc) = 180;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 3;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 4;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 110);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 8);
            skillinit(13, rc, 8);
            skillinit(14, rc, 8);
            skillinit(15, rc, 12);
            skillinit(16, rc, 13);
            skillinit(17, rc, 10);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(164, rc, 5);
            skillinit(172, rc, 2);
            skillinit(165, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"rabbit"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 800;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ウサギ"s, cnven(u8"rabbit"s));
            cpicref = 169;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 169;
            ref2 = 169;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"rabbit"s;
            cdata(158, rc) = 17;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(5) + 2);
            cdata_height(rc) = 40;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 169;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 4);
            skillinit(12, rc, 6);
            skillinit(13, rc, 11);
            skillinit(14, rc, 5);
            skillinit(15, rc, 4);
            skillinit(16, rc, 4);
            skillinit(17, rc, 10);
            skillinit(18, rc, 100);
            skillinit(106, rc, 1);
            skillinit(301, rc, 3);
            s(1) = u8"HD|N_|BD|BK|A_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"sheep"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1000;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"羊"s, cnven(u8"sheep"s));
            cpicref = 170;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 170;
            ref2 = 170;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"sheep"s;
            cdata(158, rc) = 18;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(5) + 2);
            cdata_height(rc) = 150;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 170;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 130);
            skillinit(3, rc, 80);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 5);
            skillinit(13, rc, 6);
            skillinit(14, rc, 4);
            skillinit(15, rc, 5);
            skillinit(16, rc, 4);
            skillinit(17, rc, 8);
            skillinit(18, rc, 60);
            skillinit(106, rc, 1);
            skillinit(154, rc, 3);
            skillinit(161, rc, 3);
            s(1) = u8"HD|N_|BD|BK|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"frog"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 600;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"蛙"s, cnven(u8"frog"s));
            cpicref = 172;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 172;
            ref2 = 172;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"frog"s;
            cdata(158, rc) = 19;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(5) + 2);
            cdata_height(rc) = 10;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 172;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 80);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 6);
            skillinit(13, rc, 8);
            skillinit(14, rc, 5);
            skillinit(15, rc, 5);
            skillinit(16, rc, 5);
            skillinit(17, rc, 6);
            skillinit(18, rc, 60);
            skillinit(106, rc, 1);
            skillinit(183, rc, 3);
            skillinit(160, rc, 2);
            s(1) = u8"BD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"centipede"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 400;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ムカデ"s, cnven(u8"centipede"s));
            cpicref = 173;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 173;
            ref2 = 173;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"centipede"s;
            cdata(158, rc) = 20;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 10;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 173;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 80);
            skillinit(10, rc, 6);
            skillinit(11, rc, 5);
            skillinit(12, rc, 5);
            skillinit(13, rc, 6);
            skillinit(14, rc, 3);
            skillinit(15, rc, 2);
            skillinit(16, rc, 2);
            skillinit(17, rc, 2);
            skillinit(18, rc, 70);
            skillinit(106, rc, 1);
            skillinit(186, rc, 3);
            s(1) = u8"BK|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"snail"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 500;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"かたつむり"s, cnven(u8"snail"s));
            cpicref = 174;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"カタツムリは非常に鈍い生き物です。彼らは脆く、非力で、不器用で、学習能力がなく、塩で溶けます。"s,
                u8"Despite the fears that one day the rats will inherit the World, thanks to the Etherwind it seems the snails have gotten a head start. Slow and dull, even the mightiest among them fears salt, garlic and butter. Still for those seeking a true challenge, ony can harly do worse than being a snail. Can you imagine the looks of others when you inch ever so slowly towards them?"s);
            ref1 = 174;
            ref2 = 174;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"snail"s;
            cdata(158, rc) = 21;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 8;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 174;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 4);
            skillinit(11, rc, 5);
            skillinit(12, rc, 3);
            skillinit(13, rc, 6);
            skillinit(14, rc, 3);
            skillinit(15, rc, 4);
            skillinit(16, rc, 2);
            skillinit(17, rc, 4);
            skillinit(18, rc, 25);
            skillinit(106, rc, 1);
            skillinit(111, rc, 5);
            s(1) = u8"BK|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"mandrake"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 80;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"マンドレイク"s, cnven(u8"mandrake"s));
            cpicref = 175;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 175;
            ref2 = 175;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"mandrake"s;
            cdata(158, rc) = 22;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 25;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 175;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 70);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 6);
            skillinit(12, rc, 5);
            skillinit(13, rc, 10);
            skillinit(14, rc, 8);
            skillinit(15, rc, 8);
            skillinit(16, rc, 10);
            skillinit(17, rc, 4);
            skillinit(18, rc, 60);
            skillinit(106, rc, 2);
            skillinit(165, rc, 3);
            skillinit(150, rc, 2);
            skillinit(164, rc, 3);
            s(1) = u8"HD|BK|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"beetle"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 750;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"昆虫"s, cnven(u8"beetle"s));
            cpicref = 176;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 176;
            ref2 = 176;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"beetle"s;
            cdata(158, rc) = 23;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 10;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 176;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 140;
            skillinit(2, rc, 80);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 6);
            skillinit(12, rc, 5);
            skillinit(13, rc, 7);
            skillinit(14, rc, 4);
            skillinit(15, rc, 5);
            skillinit(16, rc, 4);
            skillinit(17, rc, 3);
            skillinit(18, rc, 75);
            skillinit(106, rc, 2);
            skillinit(159, rc, 3);
            skillinit(157, rc, 3);
            s(1) = u8"N_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"mushroom"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 440;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"きのこ"s, cnven(u8"mushroom"s));
            cpicref = 177;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 177;
            ref2 = 177;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"mushroom"s;
            cdata(158, rc) = 24;
            cdata_melee_attack_type(rc) = 7;
            cdata_special_attack_type(rc) = 5;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 20;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 177;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 50);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 7);
            skillinit(12, rc, 4);
            skillinit(13, rc, 8);
            skillinit(14, rc, 4);
            skillinit(15, rc, 8);
            skillinit(16, rc, 10);
            skillinit(17, rc, 4);
            skillinit(18, rc, 60);
            skillinit(106, rc, 1);
            skillinit(177, rc, 3);
            skillinit(178, rc, 2);
            s(1) = u8"HD|N_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"bat"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 350;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"コウモリ"s, cnven(u8"bat"s));
            cpicref = 200;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 200;
            ref2 = 200;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"bat"s;
            cdata(158, rc) = 25;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 70;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 200;
            cdata_dv_correction_value(rc) = 320;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 10);
            skillinit(3, rc, 80);
            skillinit(10, rc, 3);
            skillinit(11, rc, 5);
            skillinit(12, rc, 9);
            skillinit(13, rc, 9);
            skillinit(14, rc, 4);
            skillinit(15, rc, 3);
            skillinit(16, rc, 6);
            skillinit(17, rc, 2);
            skillinit(18, rc, 140);
            skillinit(106, rc, 2);
            skillinit(187, rc, 3);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"ent"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 35;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"エント"s, cnven(u8"ent"s));
            cpicref = 201;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 201;
            ref2 = 201;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"ent"s;
            cdata(158, rc) = 26;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1500;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 201;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 170);
            skillinit(3, rc, 80);
            skillinit(10, rc, 9);
            skillinit(11, rc, 12);
            skillinit(12, rc, 4);
            skillinit(13, rc, 6);
            skillinit(14, rc, 2);
            skillinit(15, rc, 3);
            skillinit(16, rc, 6);
            skillinit(17, rc, 2);
            skillinit(18, rc, 50);
            skillinit(106, rc, 3);
            skillinit(154, rc, 2);
            skillinit(176, rc, 4);
            s(1) = u8"HA|R_|R_|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"lich"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"リッチ"s, cnven(u8"lich"s));
            cpicref = 202;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"リッチは高い知能と魔力を備えた不朽のアンデッドです。彼らは通常の種族よりも高いマナと瞑想の技術を得ますが、肉弾戦に耐え切れるほどの体力はありません。リッチは冷気と毒と強い暗黒への耐性を持っています。"s,
                u8"When a powerful magus grows near death, their desire to live on makes them attempt lichdom. Of the many who try every century, barely a handful succeed. Most fail and die, but some few partially make it, though the process robs them of much of their memories and skills. Their young \"age\" is their new \"life\" beginning anew, but they are patient. After all, they have all the time in the world now."s);
            ref1 = 202;
            ref2 = 202;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"lich"s;
            cdata(158, rc) = 27;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 180;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 202;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 190;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 80);
            skillinit(3, rc, 140);
            skillinit(10, rc, 5);
            skillinit(11, rc, 8);
            skillinit(12, rc, 7);
            skillinit(13, rc, 10);
            skillinit(14, rc, 10);
            skillinit(15, rc, 13);
            skillinit(16, rc, 15);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 3);
            skillinit(155, rc, 5);
            skillinit(174, rc, 3);
            skillinit(172, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"hound"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 540;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"猟犬"s, cnven(u8"hound"s));
            cpicref = 203;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 203;
            ref2 = 203;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"hound"s;
            cdata(158, rc) = 28;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 160;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 203;
            cdata_dv_correction_value(rc) = 120;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 9);
            skillinit(12, rc, 11);
            skillinit(13, rc, 10);
            skillinit(14, rc, 5);
            skillinit(15, rc, 4);
            skillinit(16, rc, 3);
            skillinit(17, rc, 3);
            skillinit(18, rc, 90);
            skillinit(106, rc, 2);
            skillinit(159, rc, 4);
            skillinit(183, rc, 2);
            s(1) = u8"HD|N_|BD|BK|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"ghost"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 30;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"幽霊"s, cnven(u8"ghost"s));
            cpicref = 205;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 205;
            ref2 = 205;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"ghost"s;
            cdata(158, rc) = 29;
            cdata_melee_attack_type(rc) = 6;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 180;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 205;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 160;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 60);
            skillinit(3, rc, 80);
            skillinit(10, rc, 4);
            skillinit(11, rc, 8);
            skillinit(12, rc, 6);
            skillinit(13, rc, 14);
            skillinit(14, rc, 7);
            skillinit(15, rc, 6);
            skillinit(16, rc, 11);
            skillinit(17, rc, 11);
            skillinit(18, rc, 60);
            skillinit(106, rc, 2);
            skillinit(164, rc, 4);
            skillinit(174, rc, 2);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"spirit"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"精霊"s, cnven(u8"spirit"s));
            cpicref = 206;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 206;
            ref2 = 206;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"spirit"s;
            cdata(158, rc) = 30;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 100;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 206;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 9);
            skillinit(12, rc, 5);
            skillinit(13, rc, 7);
            skillinit(14, rc, 8);
            skillinit(15, rc, 10);
            skillinit(16, rc, 13);
            skillinit(17, rc, 4);
            skillinit(18, rc, 60);
            skillinit(106, rc, 2);
            skillinit(172, rc, 3);
            skillinit(188, rc, 2);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"eye"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 50;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"目"s, cnven(u8"eye"s));
            cpicref = 207;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 207;
            ref2 = 207;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"eye"s;
            cdata(158, rc) = 31;
            cdata_melee_attack_type(rc) = 4;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 40;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 207;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 3);
            skillinit(11, rc, 9);
            skillinit(12, rc, 4);
            skillinit(13, rc, 6);
            skillinit(14, rc, 4);
            skillinit(15, rc, 7);
            skillinit(16, rc, 10);
            skillinit(17, rc, 4);
            skillinit(18, rc, 25);
            skillinit(106, rc, 2);
            skillinit(159, rc, 3);
            skillinit(161, rc, 3);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"wyvern"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 100;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ワイバーン"s, cnven(u8"wyvern"s));
            cpicref = 235;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 235;
            ref2 = 235;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"wyvern"s;
            cdata(158, rc) = 32;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1600;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 235;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 190);
            skillinit(3, rc, 80);
            skillinit(10, rc, 11);
            skillinit(11, rc, 13);
            skillinit(12, rc, 8);
            skillinit(13, rc, 9);
            skillinit(14, rc, 5);
            skillinit(15, rc, 7);
            skillinit(16, rc, 8);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 3);
            skillinit(150, rc, 3);
            skillinit(182, rc, 3);
            s(1) = u8"N_|BD|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"wasp"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 580;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ワスプ"s, cnven(u8"wasp"s));
            cpicref = 210;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 210;
            ref2 = 210;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"wasp"s;
            cdata(158, rc) = 33;
            cdata_melee_attack_type(rc) = 5;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 80;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 210;
            cdata_dv_correction_value(rc) = 220;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 50);
            skillinit(3, rc, 80);
            skillinit(10, rc, 7);
            skillinit(11, rc, 6);
            skillinit(12, rc, 13);
            skillinit(13, rc, 11);
            skillinit(14, rc, 4);
            skillinit(15, rc, 6);
            skillinit(16, rc, 3);
            skillinit(17, rc, 2);
            skillinit(18, rc, 100);
            skillinit(106, rc, 2);
            skillinit(187, rc, 2);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"giant"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 60;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"巨人"s, cnven(u8"giant"s));
            cpicref = 232;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 232;
            ref2 = 232;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"giant"s;
            cdata(158, rc) = 34;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1800;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 232;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 200);
            skillinit(3, rc, 80);
            skillinit(10, rc, 12);
            skillinit(11, rc, 14);
            skillinit(12, rc, 9);
            skillinit(13, rc, 4);
            skillinit(14, rc, 8);
            skillinit(15, rc, 5);
            skillinit(16, rc, 6);
            skillinit(17, rc, 3);
            skillinit(18, rc, 60);
            skillinit(106, rc, 4);
            skillinit(161, rc, 3);
            skillinit(174, rc, 2);
            skillinit(176, rc, 3);
            s(1) = u8"BD|BK|HA|HA|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"imp"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 240;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"インプ"s, cnven(u8"imp"s));
            cpicref = 212;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 212;
            ref2 = 212;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"imp"s;
            cdata(158, rc) = 35;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 80;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 212;
            cdata_dv_correction_value(rc) = 200;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 70);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 6);
            skillinit(12, rc, 8);
            skillinit(13, rc, 8);
            skillinit(14, rc, 8);
            skillinit(15, rc, 4);
            skillinit(16, rc, 7);
            skillinit(17, rc, 3);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(165, rc, 3);
            skillinit(188, rc, 3);
            s(1) = u8"N_|BD|HA|HA|R_|R_R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"hand"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 160;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"手"s, cnven(u8"hand"s));
            cpicref = 213;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 213;
            ref2 = 213;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"hand"s;
            cdata(158, rc) = 36;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 70;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 213;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 9);
            skillinit(12, rc, 9);
            skillinit(13, rc, 4);
            skillinit(14, rc, 8);
            skillinit(15, rc, 6);
            skillinit(16, rc, 5);
            skillinit(17, rc, 2);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(186, rc, 4);
            s(1) = u8"HA|HA|R_|R_|A_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"snake"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 430;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"蛇"s, cnven(u8"snake"s));
            cpicref = 216;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 216;
            ref2 = 216;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"snake"s;
            cdata(158, rc) = 37;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 50;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 216;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 6);
            skillinit(11, rc, 9);
            skillinit(12, rc, 8);
            skillinit(13, rc, 10);
            skillinit(14, rc, 4);
            skillinit(15, rc, 6);
            skillinit(16, rc, 6);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(157, rc, 4);
            s(1) = u8"BD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"drake"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 120;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ドレイク"s, cnven(u8"drake"s));
            cpicref = 233;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 233;
            ref2 = 233;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"drake"s;
            cdata(158, rc) = 38;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1400;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 233;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 120;
            skillinit(2, rc, 160);
            skillinit(3, rc, 80);
            skillinit(10, rc, 11);
            skillinit(11, rc, 12);
            skillinit(12, rc, 11);
            skillinit(13, rc, 8);
            skillinit(14, rc, 6);
            skillinit(15, rc, 9);
            skillinit(16, rc, 8);
            skillinit(17, rc, 7);
            skillinit(18, rc, 85);
            skillinit(106, rc, 3);
            skillinit(182, rc, 3);
            skillinit(185, rc, 2);
            s(1) = u8"N_|BD|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"goblin"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 290;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ゴブリン"s, cnven(u8"goblin"s));
            cpicref = 220;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"ゴブリンは好戦的で獰猛な種族です。彼らは特筆するべき能力を持っておらず、またこれといった弱点もありません。ゴブリンははやや高い能力と、暗黒への耐性と、自然治癒の技術を持っています。また、採取スポットでより長く採取することができます。"s,
                u8"If Dwarves are the people of the earth, then the Goblins are the vermin. While clumsy and ugly, there are ever so many goblins about, and more every year. Their scrawny bodies heal quickly, and they love the taste of fish. Their beady little eyes miss little in the dark, and you never want to grapple with them, who knows what diseases you might get."s);
            ref1 = 220;
            ref2 = 220;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"goblin"s;
            cdata(158, rc) = 39;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 140;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 220;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 110);
            skillinit(3, rc, 90);
            skillinit(10, rc, 8);
            skillinit(11, rc, 8);
            skillinit(12, rc, 5);
            skillinit(13, rc, 5);
            skillinit(14, rc, 8);
            skillinit(15, rc, 7);
            skillinit(16, rc, 7);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(154, rc, 5);
            skillinit(185, rc, 2);
            skillinit(163, rc, 2);
            skillinit(186, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"bear"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 350;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"熊"s, cnven(u8"bear"s));
            cpicref = 222;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 222;
            ref2 = 222;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"bear"s;
            cdata(158, rc) = 40;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 280;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 222;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 160);
            skillinit(3, rc, 80);
            skillinit(10, rc, 9);
            skillinit(11, rc, 10);
            skillinit(12, rc, 5);
            skillinit(13, rc, 6);
            skillinit(14, rc, 6);
            skillinit(15, rc, 6);
            skillinit(16, rc, 3);
            skillinit(17, rc, 5);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(154, rc, 3);
            skillinit(183, rc, 2);
            skillinit(186, rc, 3);
            s(1) = u8"HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"armor"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 40;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"鎧"s, cnven(u8"armor"s));
            cpicref = 223;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 223;
            ref2 = 223;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"armor"s;
            cdata(158, rc) = 41;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 550;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 223;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 300;
            skillinit(2, rc, 40);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 4);
            skillinit(12, rc, 7);
            skillinit(13, rc, 5);
            skillinit(14, rc, 6);
            skillinit(15, rc, 6);
            skillinit(16, rc, 7);
            skillinit(17, rc, 4);
            skillinit(18, rc, 50);
            skillinit(106, rc, 2);
            skillinit(158, rc, 3);
            skillinit(174, rc, 2);
            s(1) = u8"HD|N_|BD|BK|HA|HA|A_|W_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"medusa"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 180;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"メデューサ"s, cnven(u8"medusa"s));
            cpicref = 224;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 224;
            ref2 = 224;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"medusa"s;
            cdata(158, rc) = 42;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 160;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 224;
            cdata_dv_correction_value(rc) = 140;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 110);
            skillinit(10, rc, 7);
            skillinit(11, rc, 6);
            skillinit(12, rc, 8);
            skillinit(13, rc, 7);
            skillinit(14, rc, 7);
            skillinit(15, rc, 9);
            skillinit(16, rc, 11);
            skillinit(17, rc, 5);
            skillinit(18, rc, 70);
            skillinit(106, rc, 3);
            skillinit(164, rc, 3);
            skillinit(188, rc, 3);
            s(1) = u8"BD|HA|HA|R_|R_|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"cupid"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 350;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"キューピット"s, cnven(u8"cupid"s));
            cpicref = 225;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 225;
            ref2 = 225;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"cupid"s;
            cdata(158, rc) = 43;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 120;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 225;
            cdata_dv_correction_value(rc) = 200;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 130);
            skillinit(10, rc, 6);
            skillinit(11, rc, 7);
            skillinit(12, rc, 9);
            skillinit(13, rc, 8);
            skillinit(14, rc, 8);
            skillinit(15, rc, 7);
            skillinit(16, rc, 12);
            skillinit(17, rc, 8);
            skillinit(18, rc, 80);
            skillinit(106, rc, 2);
            skillinit(150, rc, 4);
            skillinit(188, rc, 3);
            s(1) = u8"N_|BD|HA|HA|R_|R_|A_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"phantom"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 35;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ファントム"s, cnven(u8"phantom"s));
            cpicref = 226;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 226;
            ref2 = 226;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"phantom"s;
            cdata(158, rc) = 44;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 450;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 226;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 200;
            skillinit(2, rc, 60);
            skillinit(3, rc, 90);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 8);
            skillinit(13, rc, 7);
            skillinit(14, rc, 6);
            skillinit(15, rc, 6);
            skillinit(16, rc, 9);
            skillinit(17, rc, 4);
            skillinit(18, rc, 85);
            skillinit(106, rc, 2);
            skillinit(157, rc, 3);
            skillinit(175, rc, 3);
            s(1) = u8"N_|BD|HA|HA|R_|R_|A_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"harpy"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 420;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ハーピー"s, cnven(u8"harpy"s));
            cpicref = 227;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 227;
            ref2 = 227;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"harpy"s;
            cdata(158, rc) = 45;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 140;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 227;
            cdata_dv_correction_value(rc) = 150;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 100);
            skillinit(10, rc, 8);
            skillinit(11, rc, 6);
            skillinit(12, rc, 9);
            skillinit(13, rc, 9);
            skillinit(14, rc, 6);
            skillinit(15, rc, 8);
            skillinit(16, rc, 9);
            skillinit(17, rc, 4);
            skillinit(18, rc, 80);
            skillinit(106, rc, 2);
            skillinit(164, rc, 3);
            skillinit(174, rc, 2);
            s(1) = u8"N_|HA|HA|R_|R_|A_|L_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"dragon"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 20;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ドラゴン"s, cnven(u8"dragon"s));
            cpicref = 228;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 228;
            ref2 = 228;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"dragon"s;
            cdata(158, rc) = 46;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 2400;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 228;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 120;
            skillinit(2, rc, 220);
            skillinit(3, rc, 80);
            skillinit(10, rc, 13);
            skillinit(11, rc, 15);
            skillinit(12, rc, 10);
            skillinit(13, rc, 9);
            skillinit(14, rc, 10);
            skillinit(15, rc, 9);
            skillinit(16, rc, 13);
            skillinit(17, rc, 9);
            skillinit(18, rc, 70);
            skillinit(106, rc, 3);
            skillinit(182, rc, 3);
            skillinit(179, rc, 3);
            s(1) = u8"N_|BD|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"dinosaur"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 100;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"恐竜"s, cnven(u8"dinosaur"s));
            cpicref = 389;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 389;
            ref2 = 389;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"dinosaur"s;
            cdata(158, rc) = 47;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 2000;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 389;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 120;
            skillinit(2, rc, 140);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 10);
            skillinit(12, rc, 6);
            skillinit(13, rc, 5);
            skillinit(14, rc, 4);
            skillinit(15, rc, 5);
            skillinit(16, rc, 6);
            skillinit(17, rc, 5);
            skillinit(18, rc, 120);
            skillinit(106, rc, 4);
            skillinit(182, rc, 3);
            skillinit(187, rc, 2);
            s(1) = u8"N_|BD|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"cerberus"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 80;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ケルベロス"s, cnven(u8"cerberus"s));
            cpicref = 229;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 229;
            ref2 = 229;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"cerberus"s;
            cdata(158, rc) = 48;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1200;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 229;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 160);
            skillinit(3, rc, 80);
            skillinit(10, rc, 11);
            skillinit(11, rc, 9);
            skillinit(12, rc, 10);
            skillinit(13, rc, 11);
            skillinit(14, rc, 6);
            skillinit(15, rc, 8);
            skillinit(16, rc, 7);
            skillinit(17, rc, 4);
            skillinit(18, rc, 85);
            skillinit(106, rc, 3);
            skillinit(159, rc, 3);
            skillinit(177, rc, 3);
            s(1) = u8"HD|N_|BD|BK|A_|L_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"spider"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 560;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"蜘蛛"s, cnven(u8"spider"s));
            cpicref = 230;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 230;
            ref2 = 230;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"spider"s;
            cdata(158, rc) = 49;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 1;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 60;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 230;
            cdata_dv_correction_value(rc) = 170;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 50);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 5);
            skillinit(12, rc, 9);
            skillinit(13, rc, 12);
            skillinit(14, rc, 5);
            skillinit(15, rc, 6);
            skillinit(16, rc, 8);
            skillinit(17, rc, 4);
            skillinit(18, rc, 120);
            skillinit(106, rc, 2);
            skillinit(157, rc, 3);
            skillinit(161, rc, 5);
            s(1) = u8"R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"golem"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 40;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ゴーレム"s, cnven(u8"golem"s));
            cpicref = 231;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"ゴーレムは魔力により生命を与えられた物質です。ゴーレムは他の種族に比べ遥かに高い体力を持っています。その代償としてか、彼らのマナと速度は、通常よりも劣っています。ゴーレムには毒への強い耐性があり、また朦朧状態にならないという利点があります。"s,
                u8"While certainly not a natural creature, the flows of the Etherwind have ingrained into them a spark of sentience. Strong as a team of oxen, and as tough as the rock they were sculpted from, those are pretty much the only strengths of a Golem. The wizards that made them wanted only laborers, not poets. Still, a Golem can slowly get better, and thankfully they lack the wit to even beome bored doing so."s);
            ref1 = 231;
            ref2 = 231;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"golem"s;
            cdata(158, rc) = 50;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 700;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 231;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 140;
            skillinit(2, rc, 150);
            skillinit(3, rc, 70);
            skillinit(10, rc, 10);
            skillinit(11, rc, 14);
            skillinit(12, rc, 4);
            skillinit(13, rc, 5);
            skillinit(14, rc, 4);
            skillinit(15, rc, 9);
            skillinit(16, rc, 6);
            skillinit(17, rc, 3);
            skillinit(18, rc, 45);
            skillinit(106, rc, 4);
            skillinit(153, rc, 5);
            skillinit(163, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"rock"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 200;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"岩"s, cnven(u8"rock"s));
            cpicref = 386;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 386;
            ref2 = 386;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"rock"s;
            cdata(158, rc) = 51;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 500;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 386;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 200;
            skillinit(2, rc, 40);
            skillinit(3, rc, 50);
            skillinit(10, rc, 8);
            skillinit(11, rc, 22);
            skillinit(12, rc, 3);
            skillinit(13, rc, 8);
            skillinit(14, rc, 2);
            skillinit(15, rc, 3);
            skillinit(16, rc, 4);
            skillinit(17, rc, 10);
            skillinit(18, rc, 70);
            skillinit(106, rc, 1);
            skillinit(153, rc, 3);
            skillinit(163, rc, 3);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"crab"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 420;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"蟹"s, cnven(u8"crab"s));
            cpicref = 237;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 237;
            ref2 = 237;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"crab"s;
            cdata(158, rc) = 52;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 50;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 237;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 60);
            skillinit(3, rc, 80);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 7);
            skillinit(13, rc, 7);
            skillinit(14, rc, 3);
            skillinit(15, rc, 4);
            skillinit(16, rc, 4);
            skillinit(17, rc, 3);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(175, rc, 2);
            skillinit(168, rc, 3);
            s(1) = u8"BK|HA|HA|R_|R_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"skeleton"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 30;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"骸骨"s, cnven(u8"skeleton"s));
            cpicref = 241;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 241;
            ref2 = 241;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"skeleton"s;
            cdata(158, rc) = 53;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 160;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 241;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 8);
            skillinit(11, rc, 7);
            skillinit(12, rc, 8);
            skillinit(13, rc, 6);
            skillinit(14, rc, 4);
            skillinit(15, rc, 6);
            skillinit(16, rc, 9);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(100, rc, 3);
            skillinit(168, rc, 2);
            skillinit(158, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"piece"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"駒"s, cnven(u8"piece"s));
            cpicref = 244;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 244;
            ref2 = 244;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"piece"s;
            cdata(158, rc) = 54;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 750;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 244;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 120);
            skillinit(3, rc, 80);
            skillinit(10, rc, 9);
            skillinit(11, rc, 7);
            skillinit(12, rc, 6);
            skillinit(13, rc, 4);
            skillinit(14, rc, 5);
            skillinit(15, rc, 9);
            skillinit(16, rc, 10);
            skillinit(17, rc, 4);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(164, rc, 2);
            skillinit(150, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"cat"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 950;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"猫"s, cnven(u8"cat"s));
            cpicref = 253;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 253;
            ref2 = 253;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"cat"s;
            cdata(158, rc) = 55;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 4;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 60;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 253;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 120);
            skillinit(10, rc, 6);
            skillinit(11, rc, 7);
            skillinit(12, rc, 7);
            skillinit(13, rc, 7);
            skillinit(14, rc, 4);
            skillinit(15, rc, 4);
            skillinit(16, rc, 7);
            skillinit(17, rc, 12);
            skillinit(18, rc, 110);
            skillinit(106, rc, 2);
            skillinit(183, rc, 2);
            skillinit(187, rc, 3);
            skillinit(173, rc, 2);
            s(1) = u8"HD|N_|BD|BK|HA|L_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"dog"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 920;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"犬"s, cnven(u8"dog"s));
            cpicref = 254;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 254;
            ref2 = 254;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"dog"s;
            cdata(158, rc) = 56;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 80;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 254;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 80);
            skillinit(10, rc, 7);
            skillinit(11, rc, 8);
            skillinit(12, rc, 7);
            skillinit(13, rc, 7);
            skillinit(14, rc, 8);
            skillinit(15, rc, 7);
            skillinit(16, rc, 7);
            skillinit(17, rc, 7);
            skillinit(18, rc, 85);
            skillinit(106, rc, 2);
            skillinit(153, rc, 3);
            skillinit(183, rc, 2);
            skillinit(159, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|L_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"roran"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 220;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ローラン"s, cnven(u8"roran"s));
            cpicref = 4;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 4;
            ref2 = 4;
            ref2 = 4;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"roran"s;
            cdata(158, rc) = 57;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 150;
            if (rnd(100) < 0)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 4;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 4;
            }
            cdata_dv_correction_value(rc) = 150;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 4);
            skillinit(11, rc, 6);
            skillinit(12, rc, 5);
            skillinit(13, rc, 7);
            skillinit(14, rc, 7);
            skillinit(15, rc, 6);
            skillinit(16, rc, 7);
            skillinit(17, rc, 10);
            skillinit(18, rc, 95);
            skillinit(106, rc, 2);
            skillinit(155, rc, 3);
            skillinit(150, rc, 4);
            skillinit(160, rc, 2);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"rat"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1100;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ねずみ"s, cnven(u8"rat"s));
            cpicref = 255;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 255;
            ref2 = 255;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"rat"s;
            cdata(158, rc) = 58;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 30;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 255;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 4);
            skillinit(12, rc, 8);
            skillinit(13, rc, 10);
            skillinit(14, rc, 3);
            skillinit(15, rc, 3);
            skillinit(16, rc, 2);
            skillinit(17, rc, 3);
            skillinit(18, rc, 75);
            skillinit(106, rc, 1);
            skillinit(157, rc, 3);
            skillinit(161, rc, 2);
            s(1) = u8"BK|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"shell"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 450;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"やどかり"s, cnven(u8"shell"s));
            cpicref = 256;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 256;
            ref2 = 256;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"shell"s;
            cdata(158, rc) = 59;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 120;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 256;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 340;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 7);
            skillinit(11, rc, 7);
            skillinit(12, rc, 5);
            skillinit(13, rc, 4);
            skillinit(14, rc, 4);
            skillinit(15, rc, 5);
            skillinit(16, rc, 3);
            skillinit(17, rc, 4);
            skillinit(18, rc, 20);
            skillinit(106, rc, 1);
            skillinit(155, rc, 3);
            skillinit(162, rc, 3);
            s(1) = u8"L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"catgod"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"猫の神"s, cnven(u8"catgod"s));
            cpicref = 199;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 199;
            ref2 = 199;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"catgod"s;
            cdata(158, rc) = 60;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 120;
            if (rnd(100) < 0)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 199;
            cdata_dv_correction_value(rc) = 250;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 80);
            skillinit(10, rc, 12);
            skillinit(11, rc, 13);
            skillinit(12, rc, 21);
            skillinit(13, rc, 28);
            skillinit(14, rc, 8);
            skillinit(15, rc, 13);
            skillinit(16, rc, 12);
            skillinit(17, rc, 25);
            skillinit(18, rc, 500);
            skillinit(106, rc, 3);
            skillinit(173, rc, 3);
            skillinit(187, rc, 3);
            skillinit(186, rc, 2);
            s(1) = u8"HD|N_|BD|HA|R_|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"machinegod"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"機械の神"s, cnven(u8"machinegod"s));
            cpicref = 349;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 349;
            ref2 = 349;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"machinegod"s;
            cdata(158, rc) = 61;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 3000;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 349;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 200);
            skillinit(3, rc, 80);
            skillinit(10, rc, 15);
            skillinit(11, rc, 14);
            skillinit(12, rc, 11);
            skillinit(13, rc, 24);
            skillinit(14, rc, 12);
            skillinit(15, rc, 15);
            skillinit(16, rc, 8);
            skillinit(17, rc, 10);
            skillinit(18, rc, 70);
            skillinit(106, rc, 5);
            skillinit(110, rc, 30);
            s(1) = u8"HD|BD|BK|HA|HA|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"undeadgod"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"死霊の神"s, cnven(u8"undeadgod"s));
            cpicref = 350;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 350;
            ref2 = 350;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"undeadgod"s;
            cdata(158, rc) = 62;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 1500;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 350;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 150);
            skillinit(3, rc, 500);
            skillinit(10, rc, 10);
            skillinit(11, rc, 13);
            skillinit(12, rc, 14);
            skillinit(13, rc, 18);
            skillinit(14, rc, 16);
            skillinit(15, rc, 18);
            skillinit(16, rc, 28);
            skillinit(17, rc, 7);
            skillinit(18, rc, 110);
            skillinit(106, rc, 4);
            skillinit(188, rc, 3);
            skillinit(164, rc, 5);
            s(1) = u8"N_|BD|BK|HA|HA|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"machine"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 15;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"機械"s, cnven(u8"machine"s));
            cpicref = 270;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 270;
            ref2 = 270;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"machine"s;
            cdata(158, rc) = 63;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 6;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 240;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 270;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 80);
            skillinit(10, rc, 7);
            skillinit(11, rc, 10);
            skillinit(12, rc, 7);
            skillinit(13, rc, 9);
            skillinit(14, rc, 5);
            skillinit(15, rc, 12);
            skillinit(16, rc, 5);
            skillinit(17, rc, 6);
            skillinit(18, rc, 65);
            skillinit(106, rc, 2);
            skillinit(155, rc, 3);
            skillinit(158, rc, 3);
            skillinit(175, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"wisp"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ウィスプ"s, cnven(u8"wisp"s));
            cpicref = 272;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 272;
            ref2 = 272;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"wisp"s;
            cdata(158, rc) = 64;
            cdata_melee_attack_type(rc) = 4;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 40;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 272;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 150);
            skillinit(3, rc, 150);
            skillinit(10, rc, 5);
            skillinit(11, rc, 10);
            skillinit(12, rc, 10);
            skillinit(13, rc, 20);
            skillinit(14, rc, 10);
            skillinit(15, rc, 15);
            skillinit(16, rc, 15);
            skillinit(17, rc, 4);
            skillinit(18, rc, 35);
            skillinit(106, rc, 1);
            skillinit(188, rc, 3);
            skillinit(164, rc, 5);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"chicken"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1000;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"鶏"s, cnven(u8"chicken"s));
            cpicref = 274;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 274;
            ref2 = 274;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"chicken"s;
            cdata(158, rc) = 65;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 40;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 274;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 80);
            skillinit(10, rc, 5);
            skillinit(11, rc, 8);
            skillinit(12, rc, 10);
            skillinit(13, rc, 11);
            skillinit(14, rc, 4);
            skillinit(15, rc, 4);
            skillinit(16, rc, 5);
            skillinit(17, rc, 7);
            skillinit(18, rc, 60);
            skillinit(106, rc, 1);
            skillinit(161, rc, 3);
            skillinit(155, rc, 3);
            s(1) = u8"HD|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"stalker"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"ストーカー"s, cnven(u8"stalker"s));
            cpicref = 276;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 276;
            ref2 = 276;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"stalker"s;
            cdata(158, rc) = 66;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 180;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 276;
            sdata(53, rc) = 500;
            sdata(58, rc) = 500;
            sdata(56, rc) = 500;
            sdata(50, rc) = 80;
            cdata_dv_correction_value(rc) = 130;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 120);
            skillinit(3, rc, 140);
            skillinit(10, rc, 9);
            skillinit(11, rc, 8);
            skillinit(12, rc, 5);
            skillinit(13, rc, 11);
            skillinit(14, rc, 7);
            skillinit(15, rc, 6);
            skillinit(16, rc, 9);
            skillinit(17, rc, 3);
            skillinit(18, rc, 100);
            skillinit(106, rc, 2);
            skillinit(186, rc, 3);
            skillinit(157, rc, 4);
            s(1) = u8"N_|HA|HA|R_|R_|A_||"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"catsister"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"妹猫"s, cnven(u8"catsister"s));
            cpicref = 354;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 354;
            ref2 = 354;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"catsister"s;
            cdata(158, rc) = 67;
            cdata_melee_attack_type(rc) = 1;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (10 + rnd(4));
            cdata_height(rc) = 140;
            if (rnd(100) < 0)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 354;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 30);
            skillinit(3, rc, 100);
            skillinit(10, rc, 7);
            skillinit(11, rc, 5);
            skillinit(12, rc, 13);
            skillinit(13, rc, 15);
            skillinit(14, rc, 8);
            skillinit(15, rc, 10);
            skillinit(16, rc, 13);
            skillinit(17, rc, 22);
            skillinit(18, rc, 200);
            skillinit(106, rc, 4);
            skillinit(167, rc, 6);
            skillinit(152, rc, 4);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"mutant"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 50;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"カオスシェイプ"s, cnven(u8"mutant"s));
            cpicref = 3;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(
                u8"カオスシェイプについて分かっていることは、ほとんどありません。異形の人とも呼ばれる彼らは、かろうじて人の形を保っています。カオスシェイプは成長とともに新しい身体の部位を獲得しますが、何が生えてくるかは予測不可能です。"s,
                u8"A living warning of the perils of Gene-Engineering, Chaos, and why pregnant women should not be caught in the Etherwind, most mutants live short and pain-filled lives. Still, one in every thousand not only lives but thrives due to the changes wrought on them. Healing quickly due to their quickened blood, and at least starting out mostly human-like, Mutants are the proof that a third hand is always helpful."s);
            ref1 = 3;
            ref2 = 3;
            ref2 = 4;
        }
        if (dbmode == 9)
        {
            return 1;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"mutant"s;
            cdata(158, rc) = 68;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(50) + 25);
            cdata_height(rc) = 180;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 3;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 4;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 100);
            skillinit(3, rc, 100);
            skillinit(10, rc, 9);
            skillinit(11, rc, 5);
            skillinit(12, rc, 5);
            skillinit(13, rc, 7);
            skillinit(14, rc, 7);
            skillinit(15, rc, 9);
            skillinit(16, rc, 7);
            skillinit(17, rc, 1);
            skillinit(18, rc, 70);
            skillinit(106, rc, 2);
            skillinit(164, rc, 3);
            skillinit(154, rc, 4);
            s(1) = u8"BD|HA|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"yeek"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 500;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"イーク"s, cnven(u8"yeek"s));
            cpicref = 378;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 378;
            ref2 = 378;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"yeek"s;
            cdata(158, rc) = 69;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(30) + 15);
            cdata_height(rc) = 90;
            if (rnd(100) < 50)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 378;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 80);
            skillinit(3, rc, 90);
            skillinit(10, rc, 4);
            skillinit(11, rc, 7);
            skillinit(12, rc, 6);
            skillinit(13, rc, 7);
            skillinit(14, rc, 6);
            skillinit(15, rc, 4);
            skillinit(16, rc, 6);
            skillinit(17, rc, 6);
            skillinit(18, rc, 90);
            skillinit(106, rc, 1);
            skillinit(155, rc, 3);
            skillinit(156, rc, 4);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"yith"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 25;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"イス"s, cnven(u8"yith"s));
            cpicref = 429;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 429;
            ref2 = 429;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"yith"s;
            cdata(158, rc) = 70;
            cdata_melee_attack_type(rc) = 6;
            cdata_special_attack_type(rc) = 3;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 950;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 429;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 150);
            skillinit(3, rc, 200);
            skillinit(10, rc, 13);
            skillinit(11, rc, 14);
            skillinit(12, rc, 9);
            skillinit(13, rc, 15);
            skillinit(14, rc, 6);
            skillinit(15, rc, 5);
            skillinit(16, rc, 11);
            skillinit(17, rc, 11);
            skillinit(18, rc, 70);
            skillinit(106, rc, 3);
            skillinit(188, rc, 4);
            skillinit(155, rc, 3);
            skillinit(181, rc, 4);
            s(1) = u8"HA|HA|HA|HA|R_|R_|R_|R_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"servant"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 5;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"神の化身"s, cnven(u8"servant"s));
            cpicref = 1;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 1;
            ref2 = 1;
            ref2 = 2;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"servant"s;
            cdata(158, rc) = 71;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(200) + 100);
            cdata_height(rc) = 165;
            if (rnd(100) < 52)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 1;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 2;
            }
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 90);
            skillinit(3, rc, 150);
            skillinit(10, rc, 6);
            skillinit(11, rc, 6);
            skillinit(12, rc, 6);
            skillinit(13, rc, 6);
            skillinit(14, rc, 6);
            skillinit(15, rc, 6);
            skillinit(16, rc, 6);
            skillinit(17, rc, 6);
            skillinit(18, rc, 100);
            skillinit(106, rc, 3);
            skillinit(152, rc, 3);
            skillinit(172, rc, 4);
            skillinit(156, rc, 3);
            skillinit(111, rc, 3);
            skillinit(166, rc, 4);
            skillinit(110, rc, 4);
            skillinit(167, rc, 3);
            s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"horse"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1000;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"馬"s, cnven(u8"horse"s));
            cpicref = 262;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 262;
            ref2 = 262;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"horse"s;
            cdata(158, rc) = 72;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 250;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 262;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 150);
            skillinit(3, rc, 50);
            skillinit(10, rc, 9);
            skillinit(11, rc, 8);
            skillinit(12, rc, 4);
            skillinit(13, rc, 5);
            skillinit(14, rc, 4);
            skillinit(15, rc, 4);
            skillinit(16, rc, 3);
            skillinit(17, rc, 6);
            skillinit(18, rc, 125);
            skillinit(106, rc, 1);
            skillinit(154, rc, 4);
            s(1) = u8"BD|L_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"god"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"神"s, cnven(u8"god"s));
            cpicref = 393;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 393;
            ref2 = 393;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"god"s;
            cdata(158, rc) = 73;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - 999999;
            cdata_height(rc) = 180;
            if (rnd(100) < 0)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 393;
            cdata_dv_correction_value(rc) = 300;
            cdata_pv_correction_value(rc) = 200;
            skillinit(2, rc, 200);
            skillinit(3, rc, 100);
            skillinit(10, rc, 17);
            skillinit(11, rc, 13);
            skillinit(12, rc, 19);
            skillinit(13, rc, 17);
            skillinit(14, rc, 16);
            skillinit(15, rc, 25);
            skillinit(16, rc, 24);
            skillinit(17, rc, 21);
            skillinit(18, rc, 150);
            skillinit(106, rc, 6);
            skillinit(173, rc, 3);
            skillinit(187, rc, 3);
            skillinit(186, rc, 2);
            skillinit(110, rc, 8);
            skillinit(108, rc, 7);
            skillinit(166, rc, 7);
            skillinit(167, rc, 5);
            skillinit(152, rc, 7);
            s(1) = u8"HA|HA|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"quickling"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"クイックリング"s, cnven(u8"quickling"s));
            cpicref = 281;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 281;
            ref2 = 281;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"quickling"s;
            cdata(158, rc) = 74;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 25;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 281;
            sdata(60, rc) = 500;
            cdata_dv_correction_value(rc) = 550;
            cdata_pv_correction_value(rc) = 100;
            skillinit(2, rc, 3);
            skillinit(3, rc, 40);
            skillinit(10, rc, 2);
            skillinit(11, rc, 4);
            skillinit(12, rc, 18);
            skillinit(13, rc, 16);
            skillinit(14, rc, 5);
            skillinit(15, rc, 8);
            skillinit(16, rc, 9);
            skillinit(17, rc, 7);
            skillinit(18, rc, 750);
            skillinit(106, rc, 1);
            skillinit(157, rc, 3);
            skillinit(173, rc, 7);
            skillinit(187, rc, 6);
            s(1) = u8"HD|BD|BK|HA|HA|R_|R_|A_|L_|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"metal"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 0;
            }
            if (dbspec == 9)
            {
                return 1;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"メタル"s, cnven(u8"metal"s));
            cpicref = 252;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 252;
            ref2 = 252;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"metal"s;
            cdata(158, rc) = 75;
            cdata_melee_attack_type(rc) = 3;
            cdata_special_attack_type(rc) = 0;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 12;
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 252;
            sdata(60, rc) = 500;
            cdata_dv_correction_value(rc) = 150;
            cdata_pv_correction_value(rc) = 1000;
            skillinit(2, rc, 1);
            skillinit(3, rc, 100);
            skillinit(10, rc, 4);
            skillinit(11, rc, 1);
            skillinit(12, rc, 3);
            skillinit(13, rc, 32);
            skillinit(14, rc, 2);
            skillinit(15, rc, 4);
            skillinit(16, rc, 4);
            skillinit(17, rc, 16);
            skillinit(18, rc, 640);
            skillinit(106, rc, 1);
            skillinit(164, rc, 4);
            skillinit(187, rc, 6);
            s(1) = u8"HD|BD|BK|"s;
            label_1531();
        }
        return 0;
    }
    if (dbidn == u8"bike"s)
    {
        if (dbmode == 16)
        {
            if (dbspec == 7)
            {
                return 1;
            }
            if (dbspec == 9)
            {
                return 15;
            }
            return 0;
        }
        if (dbmode == 2)
        {
            racename = lang(u8"バイク"s, cnven(u8"bike"s));
            cpicref = 471;
            return 0;
        }
        if (dbmode == 11)
        {
            buff = lang(""s, ""s);
            ref1 = 471;
            ref2 = 471;
        }
        if (dbmode == 9)
        {
            return 0;
        }
        if (dbmode == 3)
        {
            cdatan(2, rc) = u8"bike"s;
            cdata(158, rc) = 76;
            cdata_melee_attack_type(rc) = 0;
            cdata_special_attack_type(rc) = 6;
            cdata_birth_year(rc) = gdata_year - (rnd(10) + 10);
            cdata_height(rc) = 240;
            cbitmod(983, rc, 1);
            if (rnd(100) < 53)
            {
                cdata_sex(rc) = 0;
            }
            else
            {
                cdata_sex(rc) = 1;
            }
            if (mode == 1)
            {
                cdata_sex(rc) = cmsex;
            }
            cdata_image(rc) = 471;
            cdata_dv_correction_value(rc) = 100;
            cdata_pv_correction_value(rc) = 150;
            skillinit(2, rc, 170);
            skillinit(3, rc, 60);
            skillinit(10, rc, 11);
            skillinit(11, rc, 13);
            skillinit(12, rc, 4);
            skillinit(13, rc, 3);
            skillinit(14, rc, 4);
            skillinit(15, rc, 5);
            skillinit(16, rc, 3);
            skillinit(17, rc, 11);
            skillinit(18, rc, 155);
            skillinit(106, rc, 2);
            skillinit(173, rc, 11);
            skillinit(158, rc, 3);
            skillinit(175, rc, 3);
            s(1) = u8"HD|BD|BK|HA|HA|W_|L_|L_"s;
            label_1531();
        }
        return 0;
    }
    return 0;
}



} // namespace elona
