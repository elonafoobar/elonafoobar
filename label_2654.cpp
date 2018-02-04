#include "character.hpp"
#include "elona.hpp"
#include "variables.hpp"



#define DBMODE16_DBSPEC(n, value) \
    do \
    { \
        if (dbspec == (n)) \
        { \
            return value; \
        } \
    } while (0)


#define DBMODE16_DBSPEC_STR(n, value) \
    do \
    { \
        if (dbspec == (n)) \
        { \
            refstr = value; \
            return 0; \
        } \
    } while (0)


#define SET_LEVEL(level) \
    do \
    { \
        cdata_level(rc) = initlv != 0 ? initlv : (level); \
        if (voidlv != 0) \
        { \
            cdata_level(rc) = voidlv * (100 + (level)*2) / 100; \
        } \
    } while (0)



namespace elona
{


int label_2654()
{
    if (dbid == 0)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"バグ", u8"bug"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 0;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"バグ", u8"bug");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 343)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"user", u8"user"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 1;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 343;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"user", u8"user");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 1;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 1)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ガード！ガード！」",
                    u8"「襲撃だ！」",
                    u8"「強盗め！」");
                return 1;
            }
            else
            {
                txt(u8"\"Guard! Guard!\"", u8"\"Ambush!\"", u8"\"You thief!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「命だけわぁ」", u8"「あぁぁ…」");
                return 1;
            }
            else
            {
                txt(u8"\"Please spare my life.\"", u8"\"Ahhhh....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あの世で後悔するがいい」", u8"「虫けらめ」");
                return 1;
            }
            else
            {
                txt(u8"\"Die thief.\"", u8"\"You deserve this.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"店主", u8"shopkeeper"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 140;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 1;
            SET_LEVEL(35);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 6;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"店主", u8"shopkeeper");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 140;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 141;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 353)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"キャラバンの隊長", u8"caravan master"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 443;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 353;
            SET_LEVEL(22);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"キャラバンの隊長", u8"caravan master");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 443;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 70)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"カクテルをシェイクする音が聞こえる。",
                    u8"「一杯どうだい？」",
                    u8"「年季物のクリムエールがあるよ」",
                    u8"酒場は多くの人でにぎわっている。");
                return 1;
            }
            else
            {
                txt(u8"You hear the sound of cocktail shakers.",
                    u8"\"How 'bout a drink sir?\"",
                    u8"\"We got vintage crim ales.\"",
                    u8"The bar is crowded with people.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この酔っ払いめ！」", u8"「悪酔いはいけませんよ」");
                return 1;
            }
            else
            {
                txt(u8"\"Hey, stop it drunkard.\"",
                    u8"\"Are you sick from drinking too much?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「酔っ払いごときに…」", u8"「ふざけた運命だ」");
                return 1;
            }
            else
            {
                txt(u8"\"I got killed by a drunkard.\"",
                    u8"\"This is ridiculous.\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お帰りですか。美味い酒を用意してありますよ」",
                    u8"「お疲れだったでしょう。冷酒でもどうですか」");
                return 1;
            }
            else
            {
                txt(u8"\"Welcome home. I've got some decent ales for you.\"",
                    u8"\"Are you tired? How'bout a drink?\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「酔いは覚めましたか？」");
                return 1;
            }
            else
            {
                txt(u8"\"Sober up now huh?\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"バーテンダー", u8"bartender"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 144;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 70;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"バーテンダー", u8"bartender");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 144;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 145;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 69)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"情報屋", u8"informer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 15;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 69;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"情報屋", u8"informer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 15;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 16;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 73)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"アリーナマスター", u8"arena master"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 41;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 73;
            SET_LEVEL(40);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"アリーナマスター", u8"arena master");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 41;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 74)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お怪我はありませんか？」",
                    u8"「無事な姿で何よりです。おかえりなさい」");
                return 1;
            }
            else
            {
                txt(u8"\"Are you wonded?\"",
                    u8"\"Good to see you again. Welcome home.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1592();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"癒し手", u8"healer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 69;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 74;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"癒し手", u8"healer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 69;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 206)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"誰かが祈りを捧げる声が聞こえる。",
                    u8"「おお、この迷える子猫に道標の光を…」",
                    u8"「祈りなさい。どんな時でも救いはあります」",
                    u8"「他人を憎んではなりません」");
                return 1;
            }
            else
            {
                txt(u8"You hear the chants of prayer in the distance.",
                    u8"\"Come hither stray kittens, I shall guide you to the "
                    u8"light.\"",
                    u8"\"Pray hard. There's always chance for salvation.\"",
                    u8"\"Do unto others as you wish others to do unto you.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「償いなさい」",
                    u8"「あなたには罰が必要なようですね」",
                    u8"「てめー♪」",
                    u8"「くそがーっ」");
                return 1;
            }
            else
            {
                txt(u8"\"Atone for you sin.\"",
                    u8"\"Well, you need to be punished.\"",
                    u8"\"You sonova...\"",
                    u8"\"Shit!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おお、神よー」");
                return 1;
            }
            else
            {
                txt(u8"\"God help me!\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お怪我はありませんか？」",
                    u8"「無事な姿で何よりです。おかえりなさい」");
                return 1;
            }
            else
            {
                txt(u8"\"Are you wonded?\"",
                    u8"\"Good to see you again. Welcome home.\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「地獄に墜ちなさい♪」");
                return 1;
            }
            else
            {
                txt(u8"\"Go to hell.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1592();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"シスター", u8"sister"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 163;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 206;
            SET_LEVEL(50);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"シスター", u8"sister");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 163;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 38)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"長", u8"elder"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 142;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 38;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"長", u8"elder");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 142;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 143;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 40)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「準備はいいかい？いくぞ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"トレイナー", u8"trainer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 7;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 40;
            SET_LEVEL(40);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"トレイナー", u8"trainer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 7;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 10;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 333)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「準備はいいかい？いくぞ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ギルドトレイナー", u8"guild trainer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 415;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 333;
            SET_LEVEL(69);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ギルドトレイナー", u8"guild trainer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 415;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 414;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 76)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お尋ね者だ！」",
                    u8"「犯罪者め、おとなしくしろ」",
                    u8"「のこのこ現れるとはな！」",
                    u8"「罪をつぐなってもらおう」");
                return 1;
            }
            else
            {
                txt(u8"\"Stop there criminal!\"",
                    u8"\"You scum! Stay there.\"",
                    u8"\"You are under arrest.\"",
                    u8"\"You will pay for your sin.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1594();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ガード", u8"guard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 363;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 76;
            SET_LEVEL(40);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ガード", u8"guard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 363;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 363;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 77)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お尋ね者だ！」",
                    u8"「犯罪者め、おとなしくしろ」",
                    u8"「のこのこ現れるとはな！」",
                    u8"「罪をつぐなってもらおう」");
                return 1;
            }
            else
            {
                txt(u8"\"Stop there criminal!\"",
                    u8"\"You scum! Stay there.\"",
                    u8"\"You are under arrest.\"",
                    u8"\"You will pay for your sin.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1594();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ガード", u8"guard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 25;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 77;
            SET_LEVEL(40);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ガード", u8"guard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 25;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 25;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 204)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「どこの馬鹿がこいつを放った！」",
                    u8"「撃て、撃て、撃ちまくれー！！」",
                    u8"「こいつは、ちょっと無理です」",
                    u8"「隊長！血が血がー！！」",
                    u8"「くそっ。この化け物め！」",
                    u8"「なんなんだこの怪物は！」",
                    u8"「ひるむな、突撃しろ！」");
                return 1;
            }
            else
            {
                txt(u8"\"Who the hell released this monster!\"",
                    u8"\"Fire, fire, fire!\"",
                    u8"\"This is ridiculous.\"",
                    u8"\"Blood! My blooood!\"",
                    u8"\"Holy cow!\"",
                    u8"\"What is THIS?\"",
                    u8"\"Go go go!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「隊長！もうダメです…」",
                    u8"「うぎゃぁぁぁぁぁぁ」",
                    u8"「隊長！味方がまた一人やられました！」",
                    u8"「ぐふっ」",
                    u8"「ふばぼー」");
                return 1;
            }
            else
            {
                txt(u8"\"Ok, I'm done.\"",
                    u8"\"Arrrrrggghhh!\"",
                    u8"\"Man down! Man down!\"",
                    u8"\"M-Medic!\"",
                    u8"\"We got another man killed!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"パルミア特殊部隊", u8"palmian elite soldier"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 74;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 204;
            SET_LEVEL(10);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act(rc, 1) = -3;
            cdata_ai_act(rc, 2) = -2;
            cdata_ai_act_num(rc) = 3;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"パルミア特殊部隊", u8"palmian elite soldier");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 74;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 75;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 2)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"ひどくしゃがれた笑い声が聞こえる… ");
                return 1;
            }
            else
            {
                txt(u8"You hear raspy bitter laughter in the distance…");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「愚かな！」");
                return 1;
            }
            else
            {
                txt(u8"\"Fool!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ば、馬鹿な…！」");
                return 1;
            }
            else
            {
                txt(u8"\"Impossible!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ふははははっ」");
                return 1;
            }
            else
            {
                txt(u8"\"Hahaha!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"偽りの預言者『ゼーム』", u8"<Zeome> the false prophet"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"elea";
            dbmode = 2;
            label_2297();
            cpicref = 297;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 2;
            SET_LEVEL(55);
            cdata_portrait(rc) = 53;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 414;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = 433;
            cdata_ai_act_sub(rc, 0) = 424;
            cdata_ai_act_num(rc) = 13;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_ai_heal(rc) = 403;
            cdatan(0, rc) =
                lang(u8"偽りの預言者『ゼーム』", u8"<Zeome> the false prophet");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"elea";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 297;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 63;
            return 0;
        }
        return 0;
    }
    if (dbid == 37)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Ｑｙ＠」");
                return 1;
            }
            else
            {
                txt(u8"\"Qy@\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Ｑｙ＠！！」");
                return 1;
            }
            else
            {
                txt(u8"\"Qy@!!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Ｑ…Ｑｙ＠…」");
                return 1;
            }
            else
            {
                txt(u8"\"Q...Qy...@\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Ｑｙ＠！」");
                return 1;
            }
            else
            {
                txt(u8"\"Qy@!\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1593();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＠", u8"@"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 347;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 37;
            SET_LEVEL(1);
            cdata_portrait(rc) = 53;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"＠", u8"@");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 347;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 23)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"何かがクスクスと笑った。",
                    u8"あなたは誰かに見つめられている感じがした。");
                return 1;
            }
            else
            {
                txt(u8"You hear childish laughter, only it's oddly distorted "
                    u8"in some eldritch manner",
                    u8"You have been looking for someone like this…");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"オルフェ "
                    u8"「お前がこうすることを、予期していなかったとでも？」",
                    u8"オルフェ 「さあ、少しは楽しませてくれ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"オルフェ「こんな結末があるとは…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *クスクス* ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"混沌の寵児『オルフェ』", u8"<Orphe> the chaos child"));
            DBMODE16_DBSPEC_STR(8, u8"/man/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 331;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 23;
            SET_LEVEL(20);
            cdata_portrait(rc) = 51;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"混沌の寵児『オルフェ』", u8"<Orphe> the chaos child");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 331;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 64;
            return 0;
        }
        return 0;
    }
    if (dbid == 26)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『マッドサイエンティスト』", u8"<Mad scientist>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 332;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 26;
            SET_LEVEL(6);
            cdata_portrait(rc) = 6;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) =
                lang(u8"『マッドサイエンティスト』", u8"<Mad scientist>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 332;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 27)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"堕天使『イスカ』", u8"<Isca> the fallen angel"));
            DBMODE16_DBSPEC_STR(8, u8"/man/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 333;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 27;
            SET_LEVEL(42);
            cdata_portrait(rc) = 51;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) =
                lang(u8"堕天使『イスカ』", u8"<Isca> the fallen angel");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 333;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 28)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"あなたはひどい無力感に襲われた。",
                    u8"重たい空気が辺りに漂っている。しかし希望はまだ失われては"
                    u8"いない、とあなたは感じた。",
                    u8"「エリシェ…なぜ……お前が…」");
                return 1;
            }
            else
            {
                txt(u8"You have been struck by a terrible feeling of "
                    u8"powerlessness. ",
                    u8"The air around here is heavy and sorrowful. But you "
                    u8"somehow feel not all is lost.",
                    u8"\"Elishe...why did it have to be you...\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"『虚空を這いずる者』はあなたに冷ややかな視線を送った。",
                    u8"「くだらない…」と誰かが言った。",
                    u8"あなたは死を覚悟した。");
                return 1;
            }
            else
            {
                txt(u8"You are like a rabbit fascinated by a snake.",
                    u8"Someone mutters. \"Worthless.\"",
                    u8"You sense death.");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やっと…これでお前の元に…」");
                return 1;
            }
            else
            {
                txt(u8"\"Finally...I come to you...Elishe...\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"『虚空を這いずる者』は深いため息をついた。「…また生き延"
                    u8"びてしまった」");
                return 1;
            }
            else
            {
                txt(u8"\"I live again...in vain.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"『虚空を這いずる者』", u8"<Whom dwell in the vanity>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 334;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 28;
            SET_LEVEL(78);
            cdata_portrait(rc) = 50;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"『虚空を這いずる者』", u8"<Whom dwell in the vanity>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 334;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 73;
            return 0;
        }
        return 0;
    }
    if (dbid == 29)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"ロイター「…情けないな！」",
                    u8"誰かが呟く声が聞こえる。",
                    u8"ロイター「まだあの男に未練があるのか？」");
                return 1;
            }
            else
            {
                txt(u8"Loyter grumbles incessantly. \"How he sounds so "
                    u8"miserable...\"",
                    u8"You hear someone muttering sulfurously somewhere",
                    u8"Loyter mutters to himself. \"Why are you still attached "
                    u8"to him...\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「馬鹿な奴だ！」", u8"「身の程を思い知らせやる」");
                return 1;
            }
            else
            {
                txt(u8"\"Oh what a jerk.\"",
                    u8"\"Die like a maggot you are.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「俺が…奴以外の者に負けるだと？」");
                return 1;
            }
            else
            {
                txt(u8"\"You are shit.\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「もう終わりか？」");
                return 1;
            }
            else
            {
                txt(u8"\"Huh? Done already?\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"ザナンの紅の英雄『ロイター』",
                    u8"<Loyter> the crimson of Zanan"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 337;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 29;
            SET_LEVEL(50);
            cdata_portrait(rc) = 49;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"ザナンの紅の英雄『ロイター』",
                u8"<Loyter> the crimson of Zanan");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 337;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 140)
    {
        if (dbmode == 12)
        {
            label_1595();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"火炎竜『ヴェスダ』", u8"<Vesda> the fire dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref = 338;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 140;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) =
                lang(u8"火炎竜『ヴェスダ』", u8"<Vesda> the fire dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) = 338;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 30)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"小鳥のさえずりのような笑い声がする。",
                    u8"「ねえ、君って面白い顔してるね」",
                    u8"「旅は楽しい？」",
                    u8"「退屈だよ。どこかに連れていって欲しいな」");
                return 1;
            }
            else
            {
                txt(u8"You hear childish laughter nearby",
                    u8"\"You know your face is funny looking. Were you born "
                    u8"that way?\"",
                    u8"\"How are your travels? I'd love to go but I'm stuck "
                    u8"here...\"",
                    u8"\"I'm so bored. Maybe we can play a game of Purits & "
                    u8"Yeeks later.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「何するのよ、変態！」", u8"「いや！」");
                return 1;
            }
            else
            {
                txt(u8"\"You molester!\"", u8"\"Stop it!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「だめぇ…」");
                return 1;
            }
            else
            {
                txt(u8"\"N-Nooo...\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なーんだ、弱いじゃない」");
                return 1;
            }
            else
            {
                txt(u8"\"You are so weak.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"見習い『ミシェス』", u8"<Miches> the apprentice"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 8;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 30;
            SET_LEVEL(20);
            cdata_portrait(rc) = 50;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"見習い『ミシェス』", u8"<Miches> the apprentice");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 8;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 31)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「お酒いかが〜」",
                    u8"「やだっ。どこ触ってるんですか」",
                    u8" *ざわざわ* ",
                    u8"盃を交わす音が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"\"Come on in! The ale is flowing well tonight!\"",
                    u8"\"Hey! Keep yer stinking hands of the serving ladies!\"",
                    u8"The rowdy crowd is making a fair bit of noise tonight",
                    u8"You hear the sound of tankerds striking in a toast ");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ちょっと飲みすぎですよ！」",
                    u8"「いい加減怒りますからね」");
                return 1;
            }
            else
            {
                txt(u8"\"You are drinking too much!\"",
                    u8"\"Stop it before I get angry.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なんであたしがこんな目に…」");
                return 1;
            }
            else
            {
                txt(u8"\"Why me?\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「キャー！お客さま、大丈夫ですか？！");
                return 1;
            }
            else
            {
                txt(u8"\"Ahhh! Are you alright, sir?\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"看板娘『シーナ』", u8"<Shena> the draw"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 109;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 31;
            SET_LEVEL(20);
            cdata_portrait(rc) = 49;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"看板娘『シーナ』", u8"<Shena> the draw");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 109;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 351)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「暁の女神アウラ…その名をどうやら俺は知っているようだ」",
                    u8"「俺はあなたが好きだ。あなたは俺のたったひとりの姫だ。可"
                    u8"愛いシルヴィア」",
                    u8"「子供たちよ戦え、そして希望しろ」",
                    u8"「俺は自分が何者で、この仮面は何故かを、着き止めねばなら"
                    u8"ん」",
                    u8"「俺は…誰だ…？」",
                    u8"「ヤーンがそう望むのなら」");
                return 1;
            }
            else
            {
                txt(u8"\"Aural...it seems I know that name\"",
                    u8"\"Lady Silvia, you are my only princess\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ヤーンがそう望むならば仕方あるまい」",
                    u8"「ガルルル」",
                    u8"「ドールめ！」",
                    u8"「追い詰められたトルクに噛まれぬよう、気をつけなければな"
                    u8"」");
                return 1;
            }
            else
            {
                txt(u8"\"If Jarn wishes, then let it be done.\"",
                    u8"\"Grrrrrr!\"",
                    u8"\"Doal!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
            else
            {
                txt(u8"\"Me...meow....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ヤヌスのみ心のままに」",
                    u8"「ヤーンは与えたまい、また奪いたまう」");
                return 1;
            }
            else
            {
                txt(u8"\"Let Janus decide your fate\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『豹頭の戦士』", u8"<The leopard warrior>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 478;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 351;
            SET_LEVEL(130);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 2;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 647;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"『豹頭の戦士』", u8"<The leopard warrior>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 478;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 232;
            return 0;
        }
        return 0;
    }
    if (dbid == 352)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「何よ、この、ばか豹！いじわるの、ばかの、何もわかってな"
                    u8"い唐変木のでくのぼう！」",
                    u8"「触らないで！私に触らないでよ、この豹！」",
                    u8"誰かが足で床を踏み鳴らす音が聞こえる。",
                    u8"「どうせ私は姉さんとはメダカとクジラほど違う、ガリガリの"
                    u8"痩せっぽっちで貧相なちびの妹よ。私の味方なんて、一人もい"
                    u8"やしないんだわ！」",
                    u8"「あんたが＊＊＊してくれないんなら、宮廷中の男をくわえこ"
                    u8"んで＊＊＊してやる！」");
                return 1;
            }
            else
            {
                txt(u8"\"Come on, you stupid leopard! You ignorant, mean, "
                    u8"stupid, uncouth numbnut!\"",
                    u8"\"Don't touch! Don't touch me, leopard!\"",
                    u8"You hear someone stamps her feet.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ムチをくれるわよ！」",
                    u8"「こ、この、無礼者！お前なんか死刑にするわよ！」",
                    u8"「よくも切ったな！よくも私を切ったな！」",
                    u8"「アアアアア！ヒィィィィ！人殺し！お父様にいってやる！"
                    u8"」",
                    u8"「いまやっとわかったわ。あなたは私が死ねばいいと本気で思"
                    u8"ってるのね！」");
                return 1;
            }
            else
            {
                txt(u8"\"I will beat you with a whip!\"",
                    u8"\"You...you insolent peasant! I will bring you to the "
                    u8"scaffold!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私なんか、生まれてこなければよかったんだわ！」",
                    u8"「非人！悪魔！鬼！人殺し、人殺し、人殺し！」");
                return 1;
            }
            else
            {
                txt(u8"\"To hell with me!\"",
                    u8"\"Villain! Devil! Fiend! Murderer, murderer "
                    u8"murderer!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私を一人にしないでって約束した、あんなに固く約束したの"
                    u8"に」");
                return 1;
            }
            else
            {
                txt(u8"\"And you promised you wouldn't leave me alone...\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"皇女『シルヴィア』", u8"<Silvia> The princess"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 479;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 352;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 5;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"皇女『シルヴィア』", u8"<Silvia> The princess");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 479;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 32)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"*ぶ〜ん* ", u8"何かが高速で回転している。");
                return 1;
            }
            else
            {
                txt(u8"*bzzzz*whirrrrrrr*click*",
                    u8"Something is buffing the floor at an inhuman speed");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Target Acquired.」", u8"「Resistance is futile!」");
                return 1;
            }
            else
            {
                txt(u8"\"Target accuired!\"", u8"\"Resistance is futile!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Pwned!」");
                return 1;
            }
            else
            {
                txt(u8"\"Pwned!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「wtf」");
                return 1;
            }
            else
            {
                txt(u8"\"WTF\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『ダンジョンクリーナー』", u8"<Dungeon cleaner>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 344;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 32;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"『ダンジョンクリーナー』", u8"<Dungeon cleaner>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 344;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 33)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「獣に変えられた王子の童話をしっているかしら？」",
                    u8"痺れるほど美しいエレアの横顔にあなたは見とれた。",
                    u8"「この世界は今、大きく変わろうとしているの」",
                    u8"「ヴェルニースで見かけたあの男…まさか…」",
                    u8"神秘的な古代の言葉で誰かが囁いた。",
                    u8"「あなたはプライドが高すぎるのよ。ただでさえエレアは異端"
                    u8"視されているのに」");
                return 1;
            }
            else
            {
                txt(u8"\"You know the fairy tale where a wicked witch "
                    u8"transforms a dashing prince into an monster?\"",
                    u8"The stunning beauty of Elea's face halts your step a "
                    u8"moment.",
                    u8"\"The world is thrown into bedlam and chaos. We must "
                    u8"remain strong in the face of it.\"",
                    u8"\"The man we saw in Vernis, he just might be...\"",
                    u8"Someone mutters in mysterious ancient language.",
                    u8"\"Eleas is already being regarded as a heretic, your "
                    u8"lofty dignity isn't helping this.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なぜ戦わなければならないの？」",
                    u8"「悪いけど、遊んでいる暇は無いの」",
                    u8"エレアの少女は凍りつくような美しい瞳をとがらせた。");
                return 1;
            }
            else
            {
                txt(u8"\"Do we really have to fight?\"",
                    u8"\"Sorry, I don't have time for this.\"",
                    u8"The Elean little girl has an angry look in her "
                    u8"beautiful cold eyes.");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「うぅ…誰かが…ジャビ王に風の異変を伝えなければ…このまま"
                    u8"では…」");
                return 1;
            }
            else
            {
                txt(u8"\"A-ah...I failed my task...this world....this world "
                    u8"will....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ごめんなさい…」");
                return 1;
            }
            else
            {
                txt(u8"\"Sorry...\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"風を聴く者『ラーネイレ』",
                    u8"<Larnneire> the listener of wind"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"elea";
            dbmode = 2;
            label_2297();
            cpicref = 345;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 33;
            SET_LEVEL(20);
            cdata_portrait(rc) = 48;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 416;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"風を聴く者『ラーネイレ』",
                u8"<Larnneire> the listener of wind");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"elea";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 345;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 206;
            return 0;
        }
        return 0;
    }
    if (dbid == 34)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「異形の森、か…。我等のもたらす真実を、彼らはどう受け止"
                    u8"めるか」",
                    u8"「この洞窟は、なかなか住み心地がよさそうじゃないか」",
                    u8"「ヴェルニースの炭鉱街までは、子供の足でも一日でたどり着"
                    u8"けるだろう」",
                    u8"「あの酒場の娘にはまいったな！」",
                    u8"誰かが弓矢を手入れする音が聞こえた。");
                return 1;
            }
            else
            {
                txt(u8"\"Wait'll they hear the news we bring. And they think "
                    u8"they have problems. Hah!\"",
                    u8"\"Hey... This is a fine looking cave. I oughta enquire "
                    u8"about it sometime. Everyone needs a hideaway...\"",
                    u8"\"Pah! It would take a child less than a day to walk to "
                    u8"Vernis, we won't be late.\"",
                    u8"\"Man, that girl at the pub... She could clean my glass "
                    u8"if you know what I mean!\"",
                    u8"You hear someone testing the string of his bow.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「恩を仇で返すとはこのことだ」",
                    u8"「貴様、かの者の手先だったのか？」");
                return 1;
            }
            else
            {
                txt(u8"\"You repay kindness with ingratitude?\"",
                    u8"\"Do you really mean it?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おいおい、冗談だろう…」");
                return 1;
            }
            else
            {
                txt(u8"\"Jesus...you are kidding...\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「世の中には、おかしな奴がいるものだ」");
                return 1;
            }
            else
            {
                txt(u8"\"There's always someone I can never understand.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"異形の森の使者『ロミアス』",
                    u8"<Lomias> the messenger from Vindale"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"elea";
            dbmode = 2;
            label_2297();
            cpicref = 346;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 34;
            SET_LEVEL(20);
            cdata_portrait(rc) = 57;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 447;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"異形の森の使者『ロミアス』",
                u8"<Lomias> the messenger from Vindale");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"elea";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 346;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 1;
            eqrange = 207;
            eqammo(0) = 25001;
            eqammo(1) = 3;
            return 0;
        }
        return 0;
    }
    if (dbid == 139)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「…うぅ…」",
                    u8"「誰か、誰かいないか？」",
                    u8"何者かが助けを求める声が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"\"H-help me… please...\"",
                    u8"\"Is someone there? Help me... The King must be "
                    u8"forewarned!\"",
                    u8"You hear cries of help echoing off the walls. They "
                    u8"sound quite weak....");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"パルミアの影『スラン』",
                    u8"<Slan> the shadow of Palmia"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 99;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 139;
            SET_LEVEL(10);
            cdata_portrait(rc) = 56;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"パルミアの影『スラン』", u8"<Slan> the shadow of Palmia");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 99;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 146)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「…不覚だった…」",
                    u8"「こんな場所が墓場になるとは…」",
                    u8"何者かのうめき声が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"\"Curse my weakness! This shouldn't have happened.\"",
                    u8"\"This place will be the end of me I fear.\"",
                    u8"You hear a low moan of pain somewhere");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"カルーンの孤狼『カラム』",
                    u8"<Karam> the lonely wolf of Karune"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 99;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 146;
            SET_LEVEL(10);
            cdata_portrait(rc) = 56;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"カルーンの孤狼『カラム』",
                u8"<Karam> the lonely wolf of Karune");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 99;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 142)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この文はどういう意味かしら…」",
                    u8"「興味深いわね」",
                    u8"誰かが本を整理する音が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"\"I wonder what the runic translation of this is...\"",
                    u8"\"Hmm...interesting. Interesting indeed...\"",
                    u8"You hear someone arranging books on shelves.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やめてください！」",
                    u8"「あなたは、そんな人だったのですね」");
                return 1;
            }
            else
            {
                txt(u8"\"Stop it, please!\"", u8"\"Why are you doing this?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ひどい…」");
                return 1;
            }
            else
            {
                txt(u8"\"How can you....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この役立たず！」");
                return 1;
            }
            else
            {
                txt(u8"\"You are useless!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"歴史を学ぶ『エリステア』",
                    u8"<Erystia> the scholar of history"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 340;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 142;
            SET_LEVEL(10);
            cdata_portrait(rc) = 55;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"歴史を学ぶ『エリステア』",
                u8"<Erystia> the scholar of history");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 340;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 141)
    {
        if (dbmode == 12)
        {
            label_1596();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"闇の奇形『イスシズル』",
                    u8"<Issizzle> the dark abomination"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref = 339;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 141;
            SET_LEVEL(28);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 443;
            cdata_ai_act_num(rc) = 24;
            cdatan(0, rc) = lang(
                u8"闇の奇形『イスシズル』",
                u8"<Issizzle> the dark abomination");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 339;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 358;
            return 0;
        }
        return 0;
    }
    if (dbid == 143)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"古城の主『ワイナン』",
                    u8"<Wynan> the lord of the Ancient Castle"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 341;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 143;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(
                u8"古城の主『ワイナン』",
                u8"<Wynan> the lord of the Ancient Castle");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 341;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 359;
            return 0;
        }
        return 0;
    }
    if (dbid == 144)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"赤き義眼の『クルイツゥア』",
                    u8"<Quruiza> the red-eyed Deceiver"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 343;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 144;
            SET_LEVEL(24);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(
                u8"赤き義眼の『クルイツゥア』",
                u8"<Quruiza> the red-eyed Deceiver");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) = 343;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 356;
            return 0;
        }
        return 0;
    }
    if (dbid == 145)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"鋼鉄竜『コルゴン』", u8"<Corgon> the steel dragon"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref = 342;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 145;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) =
                lang(u8"鋼鉄竜『コルゴン』", u8"<Corgon> the steel dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            sdata(50, rc) = 500;
            cdata_image(rc) = 342;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqring1 = 357;
            return 0;
        }
        return 0;
    }
    if (dbid == 306)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"《風のルルウィ》", u8"<Luluwy>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 393;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 306;
            SET_LEVEL(350);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 648;
            cdata_ai_act_sub(rc, 1) = 636;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"《風のルルウィ》", u8"<Luluwy>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 393;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 331)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"《幸運のエヘカトル》", u8"<Ehekatl>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 413;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 331;
            SET_LEVEL(350);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 657;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"《幸運のエヘカトル》", u8"<Ehekatl>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 413;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 336)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"《エヘカトルの中の神》", u8"<God inside Ehekatl>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 413;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 336;
            SET_LEVEL(1200);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 612;
            cdata_ai_act_sub(rc, 1) = 459;
            cdata_ai_act_sub(rc, 2) = 620;
            cdata_ai_act_sub(rc, 3) = 601;
            cdata_ai_act_num(rc) = 41;
            cdatan(0, rc) =
                lang(u8"《エヘカトルの中の神》", u8"<God inside Ehekatl>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 413;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    }
    if (dbid == 338)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"《地のオパートス》", u8"<Opatos>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 432;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 338;
            SET_LEVEL(350);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 657;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"《地のオパートス》", u8"<Opatos>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 432;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    }
    if (dbid == 339)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"《収穫のクミロミ》", u8"<Kumiromi>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 433;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 339;
            SET_LEVEL(350);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 657;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"《収穫のクミロミ》", u8"<Kumiromi>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"farmer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 433;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    }
    if (dbid == 342)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"《機械のマニ》", u8"<Mani>"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 447;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 342;
            SET_LEVEL(350);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 657;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"《機械のマニ》", u8"<Mani>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 447;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    }
    if (dbid == 340)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"_test", u8"_test"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"god";
            dbmode = 2;
            label_2297();
            cpicref = 435;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 340;
            SET_LEVEL(1200);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 612;
            cdata_ai_act_sub(rc, 1) = 459;
            cdata_ai_act_sub(rc, 2) = 620;
            cdata_ai_act_sub(rc, 3) = 601;
            cdata_ai_act_num(rc) = 41;
            cdatan(0, rc) = lang(u8"_test", u8"_test");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"god";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 435;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    }
    if (dbid == 3)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1597();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 80);
            DBMODE16_DBSPEC_STR(2, lang(u8"プチ", u8"putit"));
            DBMODE16_DBSPEC_STR(8, u8"/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 3;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 3;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"プチ", u8"putit");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            sdata(63, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 4)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1597();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"ベスプチ", u8"red putit"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 4;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 3;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ベスプチ", u8"red putit");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            sdata(63, rc) = 500;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 169)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"スライム", u8"slime"));
            DBMODE16_DBSPEC_STR(8, u8"/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref = 257;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 169;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 3;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"スライム", u8"slime");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(63, rc) = 500;
            cdata_image(rc) = 257;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            cdata_damage_reaction_info(rc) = 100063;
            return 0;
        }
        return 0;
    }
    if (dbid == 194)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"弱酸性スライム", u8"acid slime"));
            DBMODE16_DBSPEC_STR(8, u8"/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref = 257;
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 194;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 3;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 455;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"弱酸性スライム", u8"acid slime");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 6300100;
            sdata(63, rc) = 500;
            cdata_image(rc) = 257;
            cdata_image(rc) += 2000;
            cspecialeq = 0;
            cdata_damage_reaction_info(rc) = 200063;
            return 0;
        }
        return 0;
    }
    if (dbid == 286)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"バブル", u8"bubble"));
            DBMODE16_DBSPEC_STR(8, u8"/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref = 400;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 286;
            SET_LEVEL(9);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"バブル", u8"bubble");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            sdata(63, rc) = 500;
            cdata_image(rc) = 400;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 285)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぷちゅ* ");
                return 1;
            }
            else
            {
                txt(u8"*putit*");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブルーバブル", u8"blue bubble"));
            DBMODE16_DBSPEC_STR(8, u8"/slime/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"slime";
            dbmode = 2;
            label_2297();
            cpicref = 400;
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 285;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ブルーバブル", u8"blue bubble");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"slime";
            dbmode = 3;
            label_2297();
            sdata(63, rc) = 500;
            cdata_image(rc) = 400;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 287)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"塊の怪物", u8"mass monster"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"drake";
            dbmode = 2;
            label_2297();
            cpicref = 401;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 287;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 20;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 613;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"塊の怪物", u8"mass monster");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"drake";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 401;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 327)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(2, lang(u8"キューブ", u8"cube"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref = 282;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 327;
            SET_LEVEL(52);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 20;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 638;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"キューブ", u8"cube");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 282;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 5)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"野うさぎ", u8"rabbit"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"rabbit";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 5;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"野うさぎ", u8"rabbit");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"rabbit";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 6)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"ズルズル…");
                return 1;
            }
            else
            {
                txt(u8"*Zzzzle*");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"かたつむり", u8"snail"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"snail";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 6;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"かたつむり", u8"snail");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"snail";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 7)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なにしやがる！」",
                    u8"「この野郎」",
                    u8"「今更謝っても遅いぞ」",
                    u8"「なめやがって」",
                    u8"「上等だ！」",
                    u8"「かかってこい、おらぁ」",
                    u8"「指一本触れて見やがれ」");
                return 1;
            }
            else
            {
                txt(u8"\"What the hell!\"",
                    u8"\"You will regret this.\"",
                    u8"\"Ok, no turning back now.\"",
                    u8"\"Now you die!\"",
                    u8"\"Come on chicken.\"",
                    u8"\"Huh.\"",
                    u8"\"You touch me, you die.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「貴様…覚えていろ」",
                    u8"「うわぁぁ」",
                    u8"「人殺し！」",
                    u8"「やめろー」",
                    u8"「次があるとは思うなよ」",
                    u8"「ひぃー」",
                    u8"「命だけは助けてくれー」");
                return 1;
            }
            else
            {
                txt(u8"\"You....you will pay for this someday...\"",
                    u8"\"Nooo!\"",
                    u8"\"A murderer!\"",
                    u8"\"Stop it!\"",
                    u8"\"F-forgive me...\"",
                    u8"\"Arrr--rr...\"",
                    u8"\"D-don't!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「いいざまだ」", u8"「出直して来い」");
                return 1;
            }
            else
            {
                txt(u8"\"Look at you.\"", u8"\"Bye bye.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"敗残兵", u8"fallen soldier"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 37;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 7;
            SET_LEVEL(3);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"敗残兵", u8"fallen soldier");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 37;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 8)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なにしやがる！」",
                    u8"「この野郎」",
                    u8"「今更謝っても遅いぞ」",
                    u8"「なめやがって」",
                    u8"「上等だ！」",
                    u8"「かかってこい、おらぁ」",
                    u8"「指一本触れて見やがれ」");
                return 1;
            }
            else
            {
                txt(u8"\"What the hell!\"",
                    u8"\"You will regret this.\"",
                    u8"\"Ok, no turning back now.\"",
                    u8"\"Now you die!\"",
                    u8"\"Come on chicken.\"",
                    u8"\"Huh.\"",
                    u8"\"You touch me, you die.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「貴様…覚えていろ」",
                    u8"「うわぁぁ」",
                    u8"「人殺し！」",
                    u8"「やめろー」",
                    u8"「次があるとは思うなよ」",
                    u8"「ひぃー」",
                    u8"「命だけは助けてくれー」");
                return 1;
            }
            else
            {
                txt(u8"\"You....you will pay for this someday...\"",
                    u8"\"Nooo!\"",
                    u8"\"A murderer!\"",
                    u8"\"Stop it!\"",
                    u8"\"F-forgive me...\"",
                    u8"\"Arrr--rr...\"",
                    u8"\"D-don't!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「いいざまだ」", u8"「出直して来い」");
                return 1;
            }
            else
            {
                txt(u8"\"Look at you.\"", u8"\"Bye bye.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"傭兵", u8"mercenary"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 139;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 8;
            SET_LEVEL(4);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"傭兵", u8"mercenary");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 139;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 178;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 9)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やめて下さい、旦那」",
                    u8"「ひぃ！」",
                    u8"「私を殺しても何の得にもならないよ」",
                    u8"「馬鹿にするな！」",
                    u8"「なぜこんなことを！」",
                    u8"「暴力反対！」",
                    u8"「ちょ、ちょっと…！」");
                return 1;
            }
            else
            {
                txt(u8"\"P-please, no sir...\"",
                    u8"\"Waaaa!\"",
                    u8"\"You get nothing from killing me...\"",
                    u8"\"Don't make a fool of me!\"",
                    u8"\"Why are you doing this?\"",
                    u8"\"A violent revolution!\"",
                    u8"\"W-w-what...!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「殺生な！」",
                    u8"「ぐわぁ」",
                    u8"「なんでこんな目に…」",
                    u8"「ひどい」",
                    u8"「乞食だからって…」",
                    u8"「私の人生っていったい」");
                return 1;
            }
            else
            {
                txt(u8"\"You are cruel.\"",
                    u8"\"Ahhhh!\"",
                    u8"\"I don't deserve this...\"",
                    u8"\"It's unfair.\"",
                    u8"\"Beggars always cry...\"",
                    u8"\"My life is pathetic.\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「よわ！」",
                    u8"「何がしたかったんだ？」",
                    u8"「ははは！」");
                return 1;
            }
            else
            {
                txt(u8"\"Weak! Weak!\"", u8"\"Huh?\"", u8"\"Ha ha ha!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"乞食", u8"beggar"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 102;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 9;
            SET_LEVEL(2);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"乞食", u8"beggar");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 102;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 103;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 269)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「なにするだー」", u8"「やめるだー」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おらは…おらはー！」",
                    u8"「田舎モンだからって…！」",
                    u8"「食べ物を粗末にするな！」",
                    u8"「はぐわ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「よわいべ」");
                return 1;
            }
            else
            {
                txt(u8"\"Weak!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"農夫", u8"farmer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 179;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 269;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"農夫", u8"farmer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 179;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 180;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 320)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「なめくじぃ」", u8"「俺様に歯向かうとはいい度胸だ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ああ、俺の肉片が街を汚してしまう！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「フハハハハ！」", u8"「この下等生物め」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"清掃員", u8"cleaner"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 410;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 320;
            SET_LEVEL(32);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 5;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = -9996;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"清掃員", u8"cleaner");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 410;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 273)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「炭鉱の毒にでもやられたか？」",
                    u8"「この街の平和は俺が守る」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「夢だ。これは悪い夢なんだ」", u8"「うげあー」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「炭鉱で鍛えた成果だな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"鉱夫", u8"miner"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 187;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 273;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"鉱夫", u8"miner");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 187;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 188;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 326)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「タラララララー♪」",
                    u8"「チキチキ♪」",
                    u8"「ドナドナドナ〜♪」",
                    u8"「ダバダ〜♪」");
                return 1;
            }
            else
            {
                txt(u8"\"Oh I once heard of a place called Nantucket...\"",
                    u8"\"Ninety-nine Yeeks in a dank hole. Ninety-nine Yeeks "
                    u8"in a Hole!\"",
                    u8"\"Crawling in my Robes! These wounds will need a "
                    u8"Healer!\"",
                    u8"\"If you go down to the woods today. You're sure of a "
                    u8"big surprise. If you go down to the woods today. You'd "
                    u8"better go in disguise.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「や、やめてくれたまえ」",
                    u8"「そんなに耳障りな演奏だったかい？」");
                return 1;
            }
            else
            {
                txt(u8"\"-Stop it..!\"", u8"\"Was my music that bad?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「そんな馬鹿な…」",
                    u8"「厳しい客だぜ」",
                    u8"「下手で悪かったよ」");
                return 1;
            }
            else
            {
                txt(u8"\"No way!\"",
                    u8"\"It's a bitter tirade.\"",
                    u8"\"Did I suck that bad?\" ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"吟遊詩人", u8"bard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 148;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 326;
            SET_LEVEL(16);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 5;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"吟遊詩人", u8"bard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"pianist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 148;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 270)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おやめなさい」", u8"「暴力はダメです」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「なんという悪」", u8"「大罪です…」", u8"「ふにゃー」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"修道女", u8"sister"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 181;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 270;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"修道女", u8"sister");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 181;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 182;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 349)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おめでたや。おめでたや」",
                    u8"祭りは人で溢れかえり、太鼓や笛の音が絶え間なく聞こえる"
                    u8"。",
                    u8"「祭りじゃー」",
                    u8"あなたはワクワクしてきた。",
                    u8"祭りの熱気で雪も溶けてしまいそうだ！");
                return 1;
            }
            else
            {
                txt(u8"\"Happy holy night!\"",
                    u8"The town is awash with people arriving at the festival "
                    u8"and drums and whistles make a merry rhythm.",
                    u8"\"It's a festival!\"",
                    u8"You feel excited.",
                    u8"Fervor!");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"聖獣", u8"holy beast"));
            DBMODE16_DBSPEC_STR(8, u8"/man/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 442;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 349;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"聖獣", u8"holy beast");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 442;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 348)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「今なら無料でジュア様の抱き枕が手に入るよ〜」",
                    u8"「見てらっしゃい、よってらっしゃい」",
                    u8"「そこの君、清楚で綺麗なお姉さんが君を待ってるよ」",
                    u8"「この荒れすさんだ世に咲く一輪の花、気高く汚れを知らぬ純"
                    u8"白の乙女、その名も癒しのジュア！」");
                return 1;
            }
            else
            {
                txt(u8"\"St.Jure's body pillow for FREE!\"",
                    u8"\"Step right up!\"",
                    u8"\"You there lucky one, a beautiful and sweet woman "
                    u8"awaits for you!\"",
                    u8"\"A flower growing in the desert, fragile yet most "
                    u8"noble. A maiden pure in heart with compassion and "
                    u8"indomitable will to vanquish evil. Jure of Healing, our "
                    u8"only Goddess!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"着ぐるみのバイト", u8"part time worker"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 473;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 348;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"着ぐるみのバイト", u8"part time worker");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"pianist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 473;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 347)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ジュア様、ああ、ジュア様、罪深き私たちをどうかお許しく"
                    u8"ださい」",
                    u8"「我々はあなた様のご光臨を強く願っております！」",
                    u8"「ジュア様に栄光あれ！ジュア様に勝利を！」",
                    u8"「さあ、あなたもジュア教に改宗しなさい」",
                    u8"「異教徒に死を！ジュアの名を汚すものに裁きの鉄槌を！」");
                return 1;
            }
            else
            {
                txt(u8"\"Jure, oh holy Jure, forgive our sins and purify us "
                    u8"from all unrighteousness.\"",
                    u8"\"We're so ready to see you, Goddness Jure!\"",
                    u8"\"Glory to Jure! May the victory always be with Jure!\"",
                    u8"\"Come, become a new servant of Jure today.\"",
                    u8"\"Death to the heretic! Crack down those who bring "
                    u8"shame to the name of Jure!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"ジュアの狂信者", u8"Jure fanatic"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 285;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 347;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_ai_heal(rc) = 404;
            cdatan(0, rc) = lang(u8"ジュアの狂信者", u8"Jure fanatic");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 285;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 284;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 271)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「喧嘩か」", u8"「みぐるみはいでやるよ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「きさまー」", u8"「このままでは終わらないぞ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おねんねしてな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"ならずもの", u8"rogue"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 183;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 271;
            SET_LEVEL(8);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 50;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ならずもの", u8"rogue");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 183;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 184;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 335)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「喧嘩か」", u8"「みぐるみはいでやるよ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「きさまー」", u8"「このままでは終わらないぞ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おねんねしてな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"娼婦", u8"prostitue"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 418;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 335;
            SET_LEVEL(8);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 5;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"娼婦", u8"prostitue");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 418;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 417;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 337)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「だしてくれ！」", u8"「私は無実なのだよ」");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うわ、なにをする」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「あばよ」", u8"「死のう」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"囚人", u8"prisoner"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 419;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 337;
            SET_LEVEL(3);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"囚人", u8"prisoner");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 419;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 420;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 272)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「感性の下劣なやつめ！」", u8"「低俗なやつだ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「これぞ芸術！」",
                    u8"「争いとは無縁の世界に生きていたのに」",
                    u8"「アートだー！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「人をあやめてしまった！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"芸術家", u8"artist"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 185;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 272;
            SET_LEVEL(6);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"芸術家", u8"artist");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 185;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 186;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 274)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無礼者！」",
                    u8"「ガード、とっととこのアホを捕まえろ」",
                    u8"「ガード！きてくれー！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「パパにいいつけてやるんだ」",
                    u8"「なんという！なんという…！」",
                    u8"「や、やめて…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ゴミくずめ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"貴族", u8"noble"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 189;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 274;
            SET_LEVEL(10);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"貴族", u8"noble");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 189;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 190;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 289)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「侵入者か？」",
                    u8"「ギルドメンバーを集めろ。敵襲だ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無念！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ネズミめ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"魔術士ギルド", u8"mage guild member"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eulderna";
            dbmode = 2;
            label_2297();
            cpicref = 195;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 289;
            SET_LEVEL(26);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_num(rc) = 4;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"魔術士ギルド", u8"mage guild member");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"eulderna";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 195;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 194;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 293)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「侵入者か？」",
                    u8"「ギルドメンバーを集めろ。敵襲だ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無念！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ネズミめ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"盗賊ギルド", u8"thief guild member"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 76;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 293;
            SET_LEVEL(26);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"盗賊ギルド", u8"thief guild member");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 76;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 77;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 295)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「侵入者か？」",
                    u8"「ギルドメンバーを集めろ。敵襲だ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無念！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ネズミめ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"戦士ギルド", u8"fighter guild member"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 78;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 295;
            SET_LEVEL(26);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"戦士ギルド", u8"fighter guild member");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 78;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 79;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 35)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「たすけてー」",
                    u8"「や、やめて」",
                    u8"「悪の手先だ！」",
                    u8"「変質者！」",
                    u8"「わ、わわあ」",
                    u8"「なんで叩くの？」",
                    u8"「大人はこれだから」");
                return 1;
            }
            else
            {
                txt(u8"\"H-help-!\"",
                    u8"\"No no!\"",
                    u8"\"You are evil.\"",
                    u8"\"Pervert!\"",
                    u8"\"G-g-go away!\"",
                    u8"\"Why are you teasing me?\"",
                    u8"\"Adults.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おかーさん…」",
                    u8"「えーん」",
                    u8"「地獄に落ちろ！」",
                    u8"「わぁぁん」",
                    u8"「うぐぅ！」",
                    u8"「もっと…生きたかった…」",
                    u8"「先立つ不幸をお許し下さい…」");
                return 1;
            }
            else
            {
                txt(u8"\"Mom....\"",
                    u8"\"A---ahh-\"",
                    u8"\"Go to hell!\"",
                    u8"\"Waaaan!\"",
                    u8"\"Urghhh!\"",
                    u8"\"My life ends here.\"",
                    u8"\"Sorry, mom, dad....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この人よわーい」");
                return 1;
            }
            else
            {
                txt(u8"\"Weak! You are weak!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"街の子供", u8"town child"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 104;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 35;
            SET_LEVEL(1);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"街の子供", u8"town child");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 104;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 357;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 36)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「止めてくだされ」",
                    u8"「ご無体な」",
                    u8"「なんと卑劣な」",
                    u8"「たわけ！」",
                    u8"「いまどきの若者は…」",
                    u8"「老人をいたわれ！」",
                    u8"「金などもっていないんじゃ」");
                return 1;
            }
            else
            {
                txt(u8"\"Stop it, please.\"",
                    u8"\"Unreasonable!\"",
                    u8"\"You foul scum.\"",
                    u8"\"Fool!\"",
                    u8"\"Youngsters.\"",
                    u8"\"Respect elders!\"",
                    u8"\"Leave me alone.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「神様はみておるぞ！」",
                    u8"「わしの老後が…」",
                    u8"「鬼！」",
                    u8"「ぐほぉ」",
                    u8"「化けて出ちゃるぞ」",
                    u8"「わしゃ死んだのか」");
                return 1;
            }
            else
            {
                txt(u8"\"God will punish you.\"",
                    u8"\"My remaining years...\"",
                    u8"\"Demon!\"",
                    u8"\"Grrhhh\"",
                    u8"\"I hate this planet.\"",
                    u8"\"Am I dead?\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なんとよわっちぃ奴じゃ」",
                    u8"「いまどきの若者はなっとらんのぉ」");
                return 1;
            }
            else
            {
                txt(u8"\"Holy...why are you so weak?\"", u8"\"Muwahahaha!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"老人", u8"old person"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 106;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 36;
            SET_LEVEL(1);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"老人", u8"old person");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 106;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 107;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 174)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「チキショー」",
                    u8"「カモンベイベー」",
                    u8"「ウラァ」",
                    u8"「ヘドぶち吐きなッ！」",
                    u8"「さあ、お仕置きの時間だよ」",
                    u8"「コラー」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「逃げろぉぉ」",
                    u8"「お前プッツンしてるぜ」",
                    u8"「くそったれー」",
                    u8"「やめてくれー」",
                    u8"「うそだー」",
                    u8"「俺は負けんのだぁ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「二度と俺を馬鹿にするな」",
                    u8"「ギャハハハハ！」",
                    u8"「ゴゥトゥヘル」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 0);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"パンク", u8"punk"));
            DBMODE16_DBSPEC_STR(8, u8"/man/sf/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 112;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 174;
            SET_LEVEL(1);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"パンク", u8"punk");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 112;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 27;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 10)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"羊", u8"wild sheep"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"sheep";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 10;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"羊", u8"wild sheep");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"sheep";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 11)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"飛び蛙", u8"flying frog"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"frog";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 11;
            SET_LEVEL(2);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"飛び蛙", u8"flying frog");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"frog";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 12)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「チキショー」",
                    u8"「カモンベイベー」",
                    u8"「ウラァ」",
                    u8"「ヘドぶち吐きなッ！」",
                    u8"「さあ、お仕置きの時間だよ」",
                    u8"「コラー」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「逃げろぉぉ」",
                    u8"「お前プッツンしてるぜ」",
                    u8"「くそったれー」",
                    u8"「やめてくれー」",
                    u8"「うそだー」",
                    u8"「俺は負けんのだぁ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「二度と俺を馬鹿にするな」",
                    u8"「ギャハハハハ！」",
                    u8"「ゴゥトゥヘル」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ごろつき", u8"gangster"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 31;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 12;
            SET_LEVEL(3);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ごろつき", u8"gangster");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 31;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 36;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 13)
    {
        if (dbmode == 12)
        {
            label_1599();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"コボルト", u8"kobold"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"kobolt";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 13;
            SET_LEVEL(3);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 5;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"コボルト", u8"kobold");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"kobolt";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 236)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"イーク", u8"yeek"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 236;
            SET_LEVEL(2);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 7;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"イーク", u8"yeek");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 238)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"イークの戦士", u8"yeek warrior"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 238;
            SET_LEVEL(6);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 7;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"イークの戦士", u8"yeek warrior");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 241)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"イークの射手", u8"yeek archer"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 241;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 7;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"イークの射手", u8"yeek archer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 2000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 240)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 8);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"マスター・イーク", u8"master yeek"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 240;
            SET_LEVEL(9);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 7;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 410;
            cdata_ai_act(rc, 2) = 418;
            cdata_ai_act(rc, 3) = -3;
            cdata_ai_act_sub(rc, 0) = 640;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"マスター・イーク", u8"master yeek");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 8000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 237)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 150);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"カミカゼ・イーク", u8"kamikaze yeek"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 237;
            SET_LEVEL(6);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 12;
            cdata_ai_act(rc, 0) = 644;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"カミカゼ・イーク", u8"kamikaze yeek");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 244)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「武士とは死ぬこととみつけたり！」",
                    u8"「玉砕じゃ！」",
                    u8"「死なばもろとも」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「バンザーイ！」", u8"「スシ！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「討ち取ったり！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"地雷侍", u8"kamikaze samurai"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 385;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 244;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 12;
            cdata_ai_act(rc, 0) = 644;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"地雷侍", u8"kamikaze samurai");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 385;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 245)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(2, lang(u8"爆弾岩", u8"bomb rock"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"rock";
            dbmode = 2;
            label_2297();
            cpicref = 386;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 245;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 10;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 644;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"爆弾岩", u8"bomb rock");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"rock";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 386;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 321)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「フーーーーｰｰ！」",
                    u8"「フーーー」",
                    u8"「フゥーーーー！」");
                return 1;
            }
            else
            {
                txt(u8"\"Foooooo!\"", u8"\"Fooooo\"", u8"\"Foooooo!\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「フーーーーｰｰ！」",
                    u8"「フーーー」",
                    u8"「フゥーーーー！」");
                return 1;
            }
            else
            {
                txt(u8"\"Foooooo!\"", u8"\"Fooooo\"", u8"\"Foooooo!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「フーーーーｰｰ！」",
                    u8"「フーーー」",
                    u8"「フゥーーーー！」");
                return 1;
            }
            else
            {
                txt(u8"\"Foooooo!\"", u8"\"Fooooo\"", u8"\"Foooooo!\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「フーーーーｰｰ！」",
                    u8"「フーーー」",
                    u8"「フゥーーーー！」");
                return 1;
            }
            else
            {
                txt(u8"\"Foooooo!\"", u8"\"Fooooo\"", u8"\"Foooooo!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「フーーーーｰｰ！」",
                    u8"「フーーー」",
                    u8"「フゥーーーー！」");
                return 1;
            }
            else
            {
                txt(u8"\"Foooooo!\"", u8"\"Fooooo\"", u8"\"Foooooo!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(2, lang(u8"ハードゲイ", u8"hard gay"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 411;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 321;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 644;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ハードゲイ", u8"hard gay");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 411;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 242)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ケケケッ」", u8"「コロセ！」", u8"「愚か者に死を」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イーク万歳！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イーク万歳！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"イークの首領『ルードルボ』", u8"yeek"));
            DBMODE16_DBSPEC_STR(8, u8"/yeek/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yeek";
            dbmode = 2;
            label_2297();
            cpicref = 381;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 242;
            SET_LEVEL(14);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 7;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -3;
            cdata_ai_act(rc, 2) = 640;
            cdata_ai_act(rc, 3) = 418;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 645;
            cdata_ai_act_num(rc) = 24;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_ai_heal(rc) = 402;
            cdatan(0, rc) = lang(u8"イークの首領『ルードルボ』", u8"yeek");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yeek";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 381;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 239)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「何をするんですか！」",
                    u8"「野蛮人！」",
                    u8"「私だって」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「市民パワー」", u8"「ぺっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"温泉マニア", u8"citizen"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 379;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 239;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"温泉マニア", u8"citizen");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 379;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 380;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 14)
    {
        if (dbmode == 12)
        {
            label_1599();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ムカデ", u8"centipede"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"centipede";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 14;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ムカデ", u8"centipede");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"centipede";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 15)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"きのこ", u8"mushroom"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mushroom";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 15;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act(rc, 1) = -3;
            cdata_ai_act(rc, 2) = 649;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) = lang(u8"きのこ", u8"mushroom");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mushroom";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 283)
    {
        if (dbmode == 12)
        {
            label_1599();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"胞子きのこ", u8"spore mushroom"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mushroom";
            dbmode = 2;
            label_2297();
            cpicref = 399;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 283;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act(rc, 1) = 650;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"胞子きのこ", u8"spore mushroom");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mushroom";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400150;
            cdata_image(rc) = 399;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 284)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 8);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"混沌きのこ", u8"chaos mushroom"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mushroom";
            dbmode = 2;
            label_2297();
            cpicref = 399;
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 284;
            SET_LEVEL(21);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act(rc, 1) = 650;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"混沌きのこ", u8"chaos mushroom");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mushroom";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5900250;
            cdata_image(rc) = 399;
            cdata_image(rc) += 8000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 16)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「何をするんですか！」",
                    u8"「野蛮人！」",
                    u8"「私だって」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「市民パワー」", u8"「ぺっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"市民", u8"citizen"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 136;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 16;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"市民", u8"citizen");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 136;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 137;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 39)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「何をするんですか！」",
                    u8"「野蛮人！」",
                    u8"「私だって」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「市民パワー」", u8"「ぺっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"市民", u8"citizen"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 134;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 39;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"市民", u8"citizen");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 134;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 135;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 171)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「何をするんですか！」",
                    u8"「野蛮人！」",
                    u8"「私だって」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「市民パワー」", u8"「ぺっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"サイバードームの住人", u8"citizen of cyber dome"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 128;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 171;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"サイバードームの住人", u8"citizen of cyber dome");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 128;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 129;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 172)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「何をするんですか！」",
                    u8"「野蛮人！」",
                    u8"「私だって」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「市民パワー」", u8"「ぺっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"サイバードームの住人", u8"citizen of cyber dome"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 127;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 172;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"サイバードームの住人", u8"citizen of cyber dome");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 127;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 131;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 173)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガード！ガード！」",
                    u8"「襲撃だ！」",
                    u8"「強盗め！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「命だけわぁ」", u8"「あぁぁ…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「あの世で後悔するがいい」", u8"「虫けらめ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"セールスマン", u8"sales person"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 146;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 173;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"セールスマン", u8"sales person");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 146;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 147;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 71)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"水夫", u8"sailor"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 120;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 71;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"水夫", u8"sailor");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 120;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 121;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 72)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私は善良な市民だったのに」",
                    u8"「くそめ」",
                    u8"「まいった」",
                    u8"「ぐえ」",
                    u8"「嘘でしょ」",
                    u8"「なぜなんだー」",
                    u8"「何の冗談ですか」");
                return 1;
            }
            else
            {
                txt(u8"\"I was a good citizen.\"",
                    u8"\"Go to hell!\"",
                    u8"\"I give up.\"",
                    u8"\"Nooooo.....\"",
                    u8"\"Is it a joke?\"",
                    u8"\"Why me.\"",
                    u8"\"W-What have you done!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"船長", u8"captain"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 119;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 72;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"船長", u8"captain");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 119;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 79)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"荘厳な感じが漂っている。",
                    u8"辺りは厳重に警備されている。",
                    u8"宮廷から華麗な音楽の響きが聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"The quiet majesty of the room makes you feel small and "
                    u8"grubby",
                    u8"You note just how alert and well armed the guards are",
                    u8"Somewhere, a harpsicord is playing a tune befitting "
                    u8"nobility");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おやめなさい！」",
                    u8"「皆の者、この曲者をどうにかするのです」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無念じゃ…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「さあ、この見苦しい死体を片付けるのです」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"パルミア王妃『スターシャ』",
                    u8"<Stersha> the queen of Palmia"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 117;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 79;
            SET_LEVEL(25);
            cdata_portrait(rc) = 54;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"パルミア王妃『スターシャ』",
                u8"<Stersha> the queen of Palmia");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 117;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 80)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おお、乱心者だ！」",
                    u8"「近衛兵、何をしている。奴をとらえよ！」",
                    u8"「血迷ったか！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「役に立たない兵どもだ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「愚か者め」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"パルミア王『ジャビ』", u8"<Xabi> the king of Palmia"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 116;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 80;
            SET_LEVEL(35);
            cdata_portrait(rc) = 55;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"パルミア王『ジャビ』", u8"<Xabi> the king of Palmia");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 116;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 17)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"オーク", u8"orc"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"orc";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 17;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 2;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"オーク", u8"orc");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"orc";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 281)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"リザードマン", u8"lizard man"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lizardman";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 281;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"リザードマン", u8"lizard man");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lizardman";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 282)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"ミノタウロス", u8"minotaur"));
            DBMODE16_DBSPEC_STR(8, u8"/mino/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"minotaur";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 282;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ミノタウロス", u8"minotaur");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"minotaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 296)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ミノタウロスの術士", u8"minotaur magician"));
            DBMODE16_DBSPEC_STR(8, u8"/mino/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"minotaur";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 296;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 420;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 415;
            cdata_ai_act_sub(rc, 0) = 645;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"ミノタウロスの術士", u8"minotaur magician");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"minotaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"priest";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 298)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ミノタウロスの闘士", u8"minotaur boxer"));
            DBMODE16_DBSPEC_STR(8, u8"/mino/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"minotaur";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 298;
            SET_LEVEL(23);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ミノタウロスの闘士", u8"minotaur boxer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"minotaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 299)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 8);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ミノタウロスの戦士", u8"minotaur king"));
            DBMODE16_DBSPEC_STR(8, u8"/mino/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"minotaur";
            dbmode = 2;
            label_2297();
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 299;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ミノタウロスの戦士", u8"minotaur king");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"minotaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 8000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 300)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 10);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"ミノタウロスの王『ウンガガ』",
                    u8"<Ungaga> the minotaur king"));
            DBMODE16_DBSPEC_STR(8, u8"/mino/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"minotaur";
            dbmode = 2;
            label_2297();
            cpicref += 10000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 300;
            SET_LEVEL(31);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 5;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 647;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(
                u8"ミノタウロスの王『ウンガガ』",
                u8"<Ungaga> the minotaur king");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"minotaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 10000;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 695;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 251)
    {
        if (dbmode == 12)
        {
            label_1600();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"トロール", u8"troll"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"troll";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 251;
            SET_LEVEL(14);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 2;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"トロール", u8"troll");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"troll";
            dbmode = 3;
            label_2297();
            sdata(50, rc) = 50;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 18)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"エレアの戦士", u8"warrior of Elea"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"elea";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 18;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 4;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"エレアの戦士", u8"warrior of Elea");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"elea";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 34;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 24)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"エレアの魔術士", u8"wizard of Elea"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"elea";
            dbmode = 2;
            label_2297();
            cpicref = 47;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 24;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 4;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act_sub(rc, 0) = 416;
            cdata_ai_act_sub(rc, 1) = 410;
            cdata_ai_act_num(rc) = 22;
            cdatan(0, rc) = lang(u8"エレアの魔術士", u8"wizard of Elea");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"elea";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 47;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 42;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 309)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"阿修羅", u8"asura"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"asura";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 309;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"阿修羅", u8"asura");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"asura";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 2;
            return 0;
        }
        return 0;
    }
    if (dbid == 310)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ミトラ", u8"mitra"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"asura";
            dbmode = 2;
            label_2297();
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 310;
            SET_LEVEL(26);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ミトラ", u8"mitra");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"asura";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 2000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 266;
            return 0;
        }
        return 0;
    }
    if (dbid == 311)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ヴァルナ", u8"varuna"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"asura";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 311;
            SET_LEVEL(37);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ヴァルナ", u8"varuna");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"asura";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 3000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 224;
            return 0;
        }
        return 0;
    }
    if (dbid == 41)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"魔術士", u8"wizard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 13;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 41;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 414;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act_sub(rc, 0) = 443;
            cdata_ai_act_sub(rc, 1) = 447;
            cdata_ai_act_sub(rc, 2) = 451;
            cdata_ai_act_num(rc) = 32;
            cdatan(0, rc) = lang(u8"魔術士", u8"wizard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 13;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 14;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 75)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"戦士", u8"warrior"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 21;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 75;
            SET_LEVEL(5);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"戦士", u8"warrior");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 21;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 20;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 19)
    {
        if (dbmode == 12)
        {
            label_1603();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"マンドレイク", u8"mandrake"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 19;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"マンドレイク", u8"mandrake");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 22)
    {
        if (dbmode == 12)
        {
            label_1602();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"かぶと虫", u8"beetle"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"beetle";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 22;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"かぶと虫", u8"beetle");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"beetle";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 20)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"オークの戦士", u8"orc warrior"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"orc";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 20;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 2;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"オークの戦士", u8"orc warrior");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"orc";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 25)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"オークの隊長『ゴダ』", u8"<Goda> the captain of orc"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"orc";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 25;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 2;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) =
                lang(u8"オークの隊長『ゴダ』", u8"<Goda> the captain of orc");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"orc";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 3000;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 21)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ゾンビ", u8"zombie"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 21;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 9;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ゾンビ", u8"zombie");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 42)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"コウモリ", u8"bat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bat";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 42;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"コウモリ", u8"bat");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 43)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"吸血コウモリ", u8"vampire bat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bat";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 43;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 601;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"吸血コウモリ", u8"vampire bat");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bat";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(56, rc) = 500;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 44)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"ドラゴンバット", u8"dragon bat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/fire/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bat";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 44;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ドラゴンバット", u8"dragon bat");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bat";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 45)
    {
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"火炎樹", u8"fire ent"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ent";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 45;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"火炎樹", u8"fire ent");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ent";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 5000200;
            sdata(51, rc) = 50;
            sdata(50, rc) = 500;
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 46)
    {
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 51, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"氷結樹", u8"ice ent"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ent";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 46;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"氷結樹", u8"ice ent");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ent";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 5100200;
            sdata(50, rc) = 50;
            sdata(51, rc) = 500;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 47)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"リッチ", u8"lich"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 47;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"リッチ", u8"lich");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 48)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"マスターリッチ", u8"master lich"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 48;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act(rc, 4) = 450;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 15;
            cdatan(0, rc) = lang(u8"マスターリッチ", u8"master lich");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 49)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"デミリッチ", u8"demi lich"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 49;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"デミリッチ", u8"demi lich");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 307)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"死刑執行人", u8"executioner"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref = 404;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 307;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = 421;
            cdata_ai_act(rc, 3) = 410;
            cdata_ai_act_sub(rc, 0) = 646;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"死刑執行人", u8"executioner");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 404;
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 735;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 308)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"死神の使い", u8"messenger of death"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"lich";
            dbmode = 2;
            label_2297();
            cpicref = 404;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 308;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 421;
            cdata_ai_act(rc, 2) = 410;
            cdata_ai_act_sub(rc, 0) = 646;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) = lang(u8"死神の使い", u8"messenger of death");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"lich";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 404;
            cdata_image(rc) += 4000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 735;
            return 0;
        }
        return 0;
    }
    if (dbid == 50)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 80);
            DBMODE16_DBSPEC_STR(2, lang(u8"猟犬", u8"hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 50;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"猟犬", u8"hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 6000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 51)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"ファイアハウンド", u8"fire hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 51;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 14;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ファイアハウンド", u8"fire hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(51, rc) = 50;
            sdata(50, rc) = 500;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 52)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 12);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"アイスハウンド", u8"ice hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 12000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 52;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 15;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 603;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"アイスハウンド", u8"ice hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 50;
            sdata(51, rc) = 500;
            cdata_image(rc) += 12000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 53)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ライトニングハウンド", u8"lightning hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 53;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 16;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 604;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ライトニングハウンド", u8"lightning hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(52, rc) = 500;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 54)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"ダークハウンド", u8"dark hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 54;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 17;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 605;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ダークハウンド", u8"dark hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(53, rc) = 500;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 55)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 10);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"幻惑ハウンド", u8"illusion hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 10000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 55;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 18;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 611;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"幻惑ハウンド", u8"illusion hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(54, rc) = 500;
            cdata_image(rc) += 10000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 56)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 9);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"神経ハウンド", u8"nerve hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 9000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 56;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 19;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 609;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"神経ハウンド", u8"nerve hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(58, rc) = 500;
            cdata_image(rc) += 9000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 57)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ポイズンハウンド", u8"poison hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 57;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 20;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 610;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ポイズンハウンド", u8"poison hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(55, rc) = 500;
            cdata_image(rc) += 2000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 58)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 11);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"轟音ハウンド", u8"sound hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 11000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 58;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 21;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 607;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"轟音ハウンド", u8"sound hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(57, rc) = 500;
            cdata_image(rc) += 11000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 59)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 15);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"地獄ハウンド", u8"nether hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 15000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 59;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 22;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 608;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"地獄ハウンド", u8"nether hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(56, rc) = 500;
            cdata_image(rc) += 15000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 60)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"カオスハウンド", u8"chaos hound"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 60;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 12;
            creaturepack = 23;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 606;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"カオスハウンド", u8"chaos hound");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(59, rc) = 500;
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 61)
    {
        if (dbmode == 12)
        {
            label_1605();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"巨大リス", u8"giant squirrel"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"rabbit";
            dbmode = 2;
            label_2297();
            cpicref = 204;
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 61;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"巨大リス", u8"giant squirrel");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"rabbit";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 204;
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 62)
    {
        if (dbmode == 12)
        {
            label_1605();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"殺人リス", u8"killer squirrel"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"rabbit";
            dbmode = 2;
            label_2297();
            cpicref = 204;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 62;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"殺人リス", u8"killer squirrel");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"rabbit";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 204;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 63)
    {
        if (dbmode == 12)
        {
            label_1604();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"怨念", u8"grudge"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 63;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 613;
            cdata_ai_act_sub(rc, 0) = 447;
            cdata_ai_act_sub(rc, 1) = 449;
            cdata_ai_act_num(rc) = 22;
            cdatan(0, rc) = lang(u8"怨念", u8"grudge");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 64)
    {
        if (dbmode == 12)
        {
            label_1604();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"餓鬼", u8"hungry demon"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 64;
            SET_LEVEL(3);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 614;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"餓鬼", u8"hungry demon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 2000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 312)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"大食いトド", u8"hungry sea lion"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ent";
            dbmode = 2;
            label_2297();
            cpicref = 406;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 312;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 651;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"大食いトド", u8"hungry sea lion");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ent";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 406;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 313)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"超大食いトド", u8"super hungry sea lion"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ent";
            dbmode = 2;
            label_2297();
            cpicref = 406;
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 313;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 651;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"超大食いトド", u8"super hungry sea lion");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ent";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 406;
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 65)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 52, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"放電雲", u8"electric cloud"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spirit";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 65;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 421;
            cdata_ai_act(rc, 2) = 604;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) = lang(u8"放電雲", u8"electric cloud");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spirit";
            dbmode = 3;
            label_2297();
            sdata(52, rc) = 500;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 66)
    {
        if (dbmode == 12)
        {
            label_1607();
            if (rnd(5) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"混沌の塊", u8"chaos cloud"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spirit";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 66;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 433;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"混沌の塊", u8"chaos cloud");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spirit";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5900300;
            sdata(59, rc) = 500;
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 67)
    {
        if (dbmode == 12)
        {
            label_1608();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 80);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"フローティングアイ", u8"floating eye"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 67;
            SET_LEVEL(2);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 15;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"フローティングアイ", u8"floating eye");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5800250;
            sdata(54, rc) = 500;
            if (nerve != 0)
            {
                sdata(58, rc) = 500;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 315)
    {
        if (dbmode == 12)
        {
            label_1608();
            if (rnd(3) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 8);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"カオスアイ", u8"chaos eye"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 315;
            SET_LEVEL(14);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 15;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 632;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"カオスアイ", u8"chaos eye");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 5900400;
            sdata(54, rc) = 500;
            if (nerve != 0)
            {
                sdata(58, rc) = 500;
            }
            cdata_image(rc) += 8000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 316)
    {
        if (dbmode == 12)
        {
            label_1608();
            if (rnd(3) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"マッドゲイズ", u8"mad gaze"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref = 407;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 316;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 15;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 636;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"マッドゲイズ", u8"mad gaze");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400300;
            sdata(54, rc) = 500;
            if (nerve != 0)
            {
                sdata(58, rc) = 500;
            }
            cdata_image(rc) = 407;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 314)
    {
        if (dbmode == 12)
        {
            label_1608();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"デスゲイズ", u8"death gaze"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref = 407;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 314;
            SET_LEVEL(29);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 15;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 652;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"デスゲイズ", u8"death gaze");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 5800450;
            sdata(54, rc) = 500;
            if (nerve != 0)
            {
                sdata(58, rc) = 500;
            }
            cdata_image(rc) = 407;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 68)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 4);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"ワイバーン", u8"wyvern"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"wyvern";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 68;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ワイバーン", u8"wyvern");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"wyvern";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 78)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"パペット", u8"puppet"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eulderna";
            dbmode = 2;
            label_2297();
            cpicref = 209;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 78;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 449;
            cdata_ai_act_sub(rc, 1) = 447;
            cdata_ai_act_sub(rc, 2) = 450;
            cdata_ai_act_num(rc) = 31;
            cdatan(0, rc) = lang(u8"パペット", u8"puppet");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eulderna";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 209;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 81)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ワスプ", u8"wasp"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"wasp";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 81;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 615;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ワスプ", u8"wasp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"wasp";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 82)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"レッドワスプ", u8"red wasp"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"wasp";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 82;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 616;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"レッドワスプ", u8"red wasp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"wasp";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 83)
    {
        if (dbmode == 12)
        {
            label_1611();
            skillexp(11, cc, 500);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"サイクロプス", u8"cyclops"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"giant";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 83;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 85;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"サイクロプス", u8"cyclops");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"giant";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 84)
    {
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ドスン* ");
                return 1;
            }
            else
            {
                txt(u8"*THUMP*");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1611();
            skillexp(11, cc, 800);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"タイタン", u8"titan"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"giant";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 84;
            SET_LEVEL(40);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 85;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"タイタン", u8"titan");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"giant";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 85)
    {
        if (dbmode == 12)
        {
            label_1612();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"インプ", u8"imp"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"imp";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 85;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = 414;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 450;
            cdata_ai_act_num(rc) = 23;
            cdatan(0, rc) = lang(u8"インプ", u8"imp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"imp";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 86)
    {
        if (dbmode == 12)
        {
            label_1612();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"冥界の使い", u8"nether imp"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"imp";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 86;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act(rc, 2) = 414;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) = lang(u8"冥界の使い", u8"nether imp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"imp";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 87)
    {
        if (dbmode == 12)
        {
            label_1612();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"カオスインプ", u8"chaos imp"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"imp";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 87;
            SET_LEVEL(27);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 417;
            cdata_ai_act(rc, 2) = 414;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) = lang(u8"カオスインプ", u8"chaos imp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"imp";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 88)
    {
        if (dbmode == 12)
        {
            label_1613();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"亡者の手", u8"hand of the dead"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hand";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 88;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 25;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 620;
            cdata_ai_act_sub(rc, 1) = 613;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"亡者の手", u8"hand of the dead");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hand";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5300080;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 89)
    {
        if (dbmode == 12)
        {
            label_1613();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"混沌の手", u8"hand of the chaos"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hand";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 89;
            SET_LEVEL(11);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 25;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 620;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"混沌の手", u8"hand of the chaos");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hand";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5900180;
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 90)
    {
        if (dbmode == 12)
        {
            label_1613();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"殺人鬼の手", u8"hand of the murderer"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hand";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 90;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 25;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = 620;
            cdata_ai_act_sub(rc, 1) = 449;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"殺人鬼の手", u8"hand of the murderer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"hand";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 91)
    {
        if (dbmode == 12)
        {
            label_1614();
            skillexp(15, cc, 250);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"亡霊", u8"ghost"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref = 214;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 91;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 617;
            cdata_ai_act(rc, 2) = 613;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) = lang(u8"亡霊", u8"ghost");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5600080;
            cdata_image(rc) = 214;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 92)
    {
        if (dbmode == 12)
        {
            label_1614();
            skillexp(15, cc, 400);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ニンフ", u8"nymph"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref = 214;
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 92;
            SET_LEVEL(13);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 618;
            cdata_ai_act(rc, 1) = 618;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 603;
            cdata_ai_act_num(rc) = 4;
            cdatan(0, rc) = lang(u8"ニンフ", u8"nymph");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400200;
            sdata(51, rc) = 500;
            cdata_image(rc) = 214;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 93)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"人食い花", u8"man eater flower"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 215;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 93;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 20;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"人食い花", u8"man eater flower");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400200;
            cdata_image(rc) = 215;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 94)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 10);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"カオスフラワー", u8"chaos flower"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 215;
            cpicref += 10000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 94;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 20;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"カオスフラワー", u8"chaos flower");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5900250;
            cdata_image(rc) = 215;
            cdata_image(rc) += 10000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 95)
    {
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"コブラ", u8"cobra"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"snake";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 95;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 615;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"コブラ", u8"cobra");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"snake";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 96)
    {
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"キングコブラ", u8"king cobra"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"snake";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 96;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 615;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"キングコブラ", u8"king cobra");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"snake";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 97)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 4);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ファイアドレイク", u8"fire drake"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"drake";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 97;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ファイアドレイク", u8"fire drake");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"drake";
            dbmode = 3;
            label_2297();
            sdata(50, rc) = 500;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 98)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 4);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"アイスドレイク", u8"ice drake"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"drake";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 98;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 603;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"アイスドレイク", u8"ice drake");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"drake";
            dbmode = 3;
            label_2297();
            sdata(51, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 99)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"レッサーマミー", u8"lesser mummy"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref = 219;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 99;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 13;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 617;
            cdata_ai_act_sub(rc, 1) = 613;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"レッサーマミー", u8"lesser mummy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 219;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 100)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 10);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"マミー", u8"mummy"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref = 219;
            cpicref += 10000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 100;
            SET_LEVEL(14);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 13;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 617;
            cdata_ai_act_sub(rc, 1) = 613;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"マミー", u8"mummy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 219;
            cdata_image(rc) += 10000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 101)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"グレイターマミー", u8"greater mummy"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref = 219;
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 101;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 13;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 617;
            cdata_ai_act_sub(rc, 1) = 613;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(u8"グレイターマミー", u8"greater mummy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 219;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 257)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 8);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"ピラミッドの主『ツェン』",
                    u8"<Tuwen> the master of the pyramid"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref = 219;
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 257;
            SET_LEVEL(28);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 13;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 646;
            cdata_ai_act_sub(rc, 1) = 613;
            cdata_ai_act_num(rc) = 21;
            cdatan(0, rc) = lang(
                u8"ピラミッドの主『ツェン』",
                u8"<Tuwen> the master of the pyramid");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 219;
            cdata_image(rc) += 8000;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 254)
    {
        if (dbmode == 12)
        {
            label_1601();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"古代の棺", u8"ancient coffin"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"zombie";
            dbmode = 2;
            label_2297();
            cpicref = 395;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 254;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 13;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = 638;
            cdata_ai_act(rc, 3) = 449;
            cdata_ai_act_sub(rc, 0) = 645;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"古代の棺", u8"ancient coffin");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"zombie";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 395;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 102)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ゴブリン", u8"goblin"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"goblin";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 102;
            SET_LEVEL(2);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 1;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ゴブリン", u8"goblin");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"goblin";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 103)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ゴブリンの戦士", u8"goblin warrior"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"goblin";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 103;
            SET_LEVEL(6);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 1;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ゴブリンの戦士", u8"goblin warrior");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"goblin";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 104)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ゴブリンシャーマン", u8"goblin shaman"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"goblin";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 104;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 85;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 1;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 420;
            cdata_ai_act_sub(rc, 0) = 425;
            cdata_ai_act_sub(rc, 1) = 447;
            cdata_ai_act_num(rc) = 22;
            cdata_ai_heal(rc) = 400;
            cdatan(0, rc) = lang(u8"ゴブリンシャーマン", u8"goblin shaman");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"goblin";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 105)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ゴブリンの魔法使い", u8"goblin wizard"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"goblin";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 105;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 1;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act_num(rc) = 2;
            cdatan(0, rc) = lang(u8"ゴブリンの魔法使い", u8"goblin wizard");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"goblin";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 106)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"赤の洗礼者", u8"red baptist"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref = 221;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 106;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 420;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 12;
            cdatan(0, rc) = lang(u8"赤の洗礼者", u8"red baptist");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) = 221;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 107)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"青の洗礼者", u8"blue baptist"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref = 221;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 107;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 419;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 12;
            cdatan(0, rc) = lang(u8"青の洗礼者", u8"blue baptist");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            sdata(51, rc) = 500;
            cdata_image(rc) = 221;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 108)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うぉーん…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ぐるる」", u8"「ぐるぁ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブラウンベア", u8"brown bear"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bear";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 108;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 11;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ブラウンベア", u8"brown bear");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bear";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 109)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"グリズリー", u8"grizzly"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bear";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 109;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 11;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"グリズリー", u8"grizzly");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bear";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 344)
    {
        if (dbmode == 12)
        {
            label_1613();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"マンモス", u8"Mammoth"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bear";
            dbmode = 2;
            label_2297();
            cpicref = 439;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 344;
            SET_LEVEL(28);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 11;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"マンモス", u8"Mammoth");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"bear";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 439;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 110)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"リビングアーマー", u8"living armor"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"armor";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 110;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"リビングアーマー", u8"living armor");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"armor";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 111)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"鉄塊", u8"steel mass"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"armor";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 111;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"鉄塊", u8"steel mass");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"armor";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 112)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ゴールデンアーマー", u8"golden armor"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"armor";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 112;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ゴールデンアーマー", u8"golden armor");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"armor";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 113)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"デスアーマー", u8"death armor"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"armor";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 113;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 613;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"デスアーマー", u8"death armor");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"armor";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 114)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"メデューサ", u8"medusa"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"medusa";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 114;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"メデューサ", u8"medusa");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"medusa";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 115)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"エウリュアレ", u8"euryale"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"medusa";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 115;
            SET_LEVEL(33);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"エウリュアレ", u8"euryale");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"medusa";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 116)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ステンノ", u8"stheno"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"medusa";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 116;
            SET_LEVEL(44);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ステンノ", u8"stheno");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"medusa";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 117)
    {
        if (dbmode == 12)
        {
            label_1598();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"恋のキューピット", u8"cupid of love"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cupid";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 117;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 443;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"恋のキューピット", u8"cupid of love");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"cupid";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 118)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"レッサーファントム", u8"lesser phantom"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"phantom";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 118;
            SET_LEVEL(9);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 447;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"レッサーファントム", u8"lesser phantom");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"phantom";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 248)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ティラノサウルス", u8"Tyrannosaurus"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dinosaur";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 248;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ティラノサウルス", u8"Tyrannosaurus");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dinosaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 119)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ハーピー", u8"harpy"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"harpy";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 119;
            SET_LEVEL(13);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ハーピー", u8"harpy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"harpy";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 120)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 19);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"グリーンドラゴン", u8"green dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 19000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 120;
            SET_LEVEL(32);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 612;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"グリーンドラゴン", u8"green dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 19000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 121)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(2, lang(u8"レッドドラゴン", u8"red dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 121;
            SET_LEVEL(40);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"レッドドラゴン", u8"red dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 122)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ホワイトドラゴン", u8"white dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 122;
            SET_LEVEL(40);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 603;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ホワイトドラゴン", u8"white dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(51, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 123)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(2, lang(u8"エレキドラゴン", u8"elec dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 123;
            SET_LEVEL(40);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 604;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"エレキドラゴン", u8"elec dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(52, rc) = 500;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 124)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"冥界ドラゴン", u8"nether dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 124;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 608;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"冥界ドラゴン", u8"nether dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(56, rc) = 500;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 125)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 5);
            DBMODE16_DBSPEC(5, 18);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"カオスドラゴン", u8"chaos dragon"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dragon";
            dbmode = 2;
            label_2297();
            cpicref += 18000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 125;
            SET_LEVEL(50);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 606;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"カオスドラゴン", u8"chaos dragon");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dragon";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(59, rc) = 500;
            cdata_image(rc) += 18000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 126)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 4);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"ケルベロス", u8"cerberus"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cerberus";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 126;
            SET_LEVEL(23);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ケルベロス", u8"cerberus");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"cerberus";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 255)
    {
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"サソリ", u8"scorpion"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"centipede";
            dbmode = 2;
            label_2297();
            cpicref = 396;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 255;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"サソリ", u8"scorpion");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"centipede";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5500150;
            sdata(55, rc) = 500;
            cdata_image(rc) = 396;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 256)
    {
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ダイオウサソリ", u8"king scorpion"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"centipede";
            dbmode = 2;
            label_2297();
            cpicref = 396;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 256;
            SET_LEVEL(24);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ダイオウサソリ", u8"king scorpion");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"centipede";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5500350;
            sdata(55, rc) = 500;
            cdata_image(rc) = 396;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 127)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *カサカサ* ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"まだら蜘蛛", u8"spider"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spider";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 127;
            SET_LEVEL(3);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 6;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"まだら蜘蛛", u8"spider");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spider";
            dbmode = 3;
            label_2297();
            sdata(55, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 128)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *カサカサ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 19);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブラックウィドウ", u8"black widow"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spider";
            dbmode = 2;
            label_2297();
            cpicref += 19000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 128;
            SET_LEVEL(11);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 6;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ブラックウィドウ", u8"black widow");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spider";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5500150;
            sdata(55, rc) = 500;
            cdata_image(rc) += 19000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 129)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *カサカサ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"パラライザー", u8"paralyzer"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spider";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 129;
            SET_LEVEL(21);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 6;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"パラライザー", u8"paralyzer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spider";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5800150;
            sdata(55, rc) = 500;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 130)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *カサカサ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1599();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"タランチュラ", u8"tarantula"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spider";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 130;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 6;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"タランチュラ", u8"tarantula");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spider";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5500200;
            sdata(55, rc) = 500;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 131)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *カサカサ* ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"吸血蜘蛛", u8"blood spider"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"spider";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 131;
            SET_LEVEL(28);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 6;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"吸血蜘蛛", u8"blood spider");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"spider";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5600100;
            sdata(55, rc) = 500;
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 132)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"ウッドゴーレム", u8"wooden golem"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 132;
            SET_LEVEL(13);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ウッドゴーレム", u8"wooden golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 133)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"ストーンゴーレム", u8"stone golem"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 133;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ストーンゴーレム", u8"stone golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 134)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 15);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"スティールゴーレム", u8"steel golem"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 15000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 134;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"スティールゴーレム", u8"steel golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 15000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 135)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ゴールドゴーレム", u8"golden golem"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 135;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ゴールドゴーレム", u8"golden golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 136)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ミスリルゴーレム", u8"mithril golem"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 136;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ミスリルゴーレム", u8"mithril golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 137)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 9);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(2, lang(u8"スカイゴーレム", u8"sky golem"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 9000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 137;
            SET_LEVEL(40);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"スカイゴーレム", u8"sky golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 9000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 138)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8" *ガチャ* ");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 2);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"アダマンタイトゴーレム", u8"adamantium golem"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"golem";
            dbmode = 2;
            label_2297();
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 138;
            SET_LEVEL(50);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"アダマンタイトゴーレム", u8"adamantium golem");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"golem";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 2000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 147)
    {
        if (dbmode == 12)
        {
            label_1605();
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"火蟹", u8"fire crab"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"crab";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 147;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"火蟹", u8"fire crab");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"crab";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5000150;
            sdata(50, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 148)
    {
        if (dbmode == 12)
        {
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"火炎ムカデ", u8"fire centipede"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"centipede";
            dbmode = 2;
            label_2297();
            cpicref = 239;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 148;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"火炎ムカデ", u8"fire centipede");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"centipede";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5000200;
            sdata(50, rc) = 500;
            cdata_image(rc) = 239;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 149)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"炎の信仰者", u8"cultist of fire"));
            DBMODE16_DBSPEC_STR(8, u8"/fire/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"goblin";
            dbmode = 2;
            label_2297();
            cpicref = 240;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 149;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 85;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 642;
            cdata_ai_act_sub(rc, 1) = 450;
            cdata_ai_act_num(rc) = 21;
            cdata_ai_heal(rc) = 400;
            cdatan(0, rc) = lang(u8"炎の信仰者", u8"cultist of fire");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"goblin";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            sdata(50, rc) = 500;
            cdata_image(rc) = 240;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 150)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"骸骨戦士", u8"skeleton warrior"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"skeleton";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 150;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 9;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"骸骨戦士", u8"skeleton warrior");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"skeleton";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 151)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"骸骨狂戦士", u8"skeleton berserker"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"skeleton";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 151;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 9;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"骸骨狂戦士", u8"skeleton berserker");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"skeleton";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 3000;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 152)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「改宗せよ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「神はいないのですか！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"闇の宣教師", u8"missionary of darkness"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eulderna";
            dbmode = 2;
            label_2297();
            cpicref = 243;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 152;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 9;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 613;
            cdata_ai_act_num(rc) = 2;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"闇の宣教師", u8"missionary of darkness");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eulderna";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400150;
            cdata_image(rc) = 243;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 153)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜ポーン＞", u8"<Pawn>"));
            DBMODE16_DBSPEC_STR(8, u8"/pawn/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 153;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"＜ポーン＞", u8"<Pawn>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 154)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜ルーク＞", u8"<Rook>"));
            DBMODE16_DBSPEC_STR(8, u8"/pawn/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref = 245;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 154;
            SET_LEVEL(16);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"＜ルーク＞", u8"<Rook>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 245;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 155)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜ビショップ＞", u8"<Bishop>"));
            DBMODE16_DBSPEC_STR(8, u8"/pawn/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref = 246;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 155;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 447;
            cdata_ai_act_num(rc) = 22;
            cdatan(0, rc) = lang(u8"＜ビショップ＞", u8"<Bishop>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 246;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 156)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜ナイト＞", u8"<Knight>"));
            DBMODE16_DBSPEC_STR(8, u8"/pawn/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref = 247;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 156;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"＜ナイト＞", u8"<Knight>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 247;
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 157)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜クィーン＞", u8"<Queen>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref = 248;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 157;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act(rc, 2) = 414;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) = lang(u8"＜クィーン＞", u8"<Queen>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 248;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 158)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"＜キング＞", u8"<King>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"piece";
            dbmode = 2;
            label_2297();
            cpicref = 249;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 158;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 641;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"＜キング＞", u8"<King>");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"piece";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 249;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 159)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「お尋ね者だ！」",
                    u8"「犯罪者め、おとなしくしろ」",
                    u8"「のこのこ現れるとはな！」",
                    u8"「罪をつぐなってもらおう」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ぐふっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"傭兵戦士", u8"mercenary warrior"));
            DBMODE16_DBSPEC_STR(8, u8"/man/shopguard/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 159;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 159;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 8;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"傭兵戦士", u8"mercenary warrior");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 159;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 159;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 160)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「お尋ね者だ！」",
                    u8"「犯罪者め、おとなしくしろ」",
                    u8"「のこのこ現れるとはな！」",
                    u8"「罪をつぐなってもらおう」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ぐふっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"傭兵射手", u8"mercenary archer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/shopguard/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 57;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 160;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 8;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"傭兵射手", u8"mercenary archer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 57;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 57;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 161)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「お尋ね者だ！」",
                    u8"「犯罪者め、おとなしくしろ」",
                    u8"「のこのこ現れるとはな！」",
                    u8"「罪をつぐなってもらおう」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ぐふっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"傭兵魔術士", u8"mercenary wizard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/shopguard/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 100;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 161;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 8;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act_num(rc) = 2;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"傭兵魔術士", u8"mercenary wizard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 100;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 100;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 302)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イヒヒヒヒ」",
                    u8"「もうすぐ殺してあげるよ」",
                    u8"「かわいそうに、ウヒャ」",
                    u8"「おまえさん、ついてないな」",
                    u8"「馬鹿な選択をしたね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「たちけて」",
                    u8"「ひぃぃ、こいつ強い」",
                    u8"「命だけは！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ついてなかったな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"盗賊団の頭領", u8"rogue boss"));
            DBMODE16_DBSPEC_STR(8, u8"/man/rogue/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 150;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 302;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 4;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 647;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"盗賊団の頭領", u8"rogue boss");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 150;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 150;
            }
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 303)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イヒヒヒヒ」",
                    u8"「もうすぐ殺してあげるよ」",
                    u8"「かわいそうに、ウヒャ」",
                    u8"「おまえさん、ついてないな」",
                    u8"「馬鹿な選択をしたね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「たちけて」",
                    u8"「ひぃぃ、こいつ強い」",
                    u8"「命だけは！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ついてなかったな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"盗賊団の用心棒", u8"rogue warrior"));
            DBMODE16_DBSPEC_STR(8, u8"/man/rogue/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 31;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 303;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"盗賊団の用心棒", u8"rogue warrior");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 31;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 31;
            }
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 304)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イヒヒヒヒ」",
                    u8"「もうすぐ殺してあげるよ」",
                    u8"「かわいそうに、ウヒャ」",
                    u8"「おまえさん、ついてないな」",
                    u8"「馬鹿な選択をしたね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「たちけて」",
                    u8"「ひぃぃ、こいつ強い」",
                    u8"「命だけは！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ついてなかったな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"盗賊団の殺し屋", u8"rogue archer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/rogue/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 158;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 304;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -2;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"盗賊団の殺し屋", u8"rogue archer");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 158;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 158;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 305)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イヒヒヒヒ」",
                    u8"「もうすぐ殺してあげるよ」",
                    u8"「かわいそうに、ウヒャ」",
                    u8"「おまえさん、ついてないな」",
                    u8"「馬鹿な選択をしたね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「たちけて」",
                    u8"「ひぃぃ、こいつ強い」",
                    u8"「命だけは！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ついてなかったな」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"盗賊団の術士", u8"rogue wizard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/rogue/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 157;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 305;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 420;
            cdata_ai_act_sub(rc, 1) = 414;
            cdata_ai_act_sub(rc, 2) = 447;
            cdata_ai_act_num(rc) = 31;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"盗賊団の術士", u8"rogue wizard");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"priest";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 157;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 157;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 162)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「撃てぇ！」",
                    u8"「弾が尽きるまで撃て！」",
                    u8"「虫けらめェ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「隊長！もうだめです」",
                    u8"「メディーック！！」",
                    u8"「マンダウン！マンダウン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ターゲット・ダウン！」", u8"「グッドジョブ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"イェルス機械兵", u8"Yerles machine infantry"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 250;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 162;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"イェルス機械兵", u8"Yerles machine infantry");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 250;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 234)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「撃てぇ！」",
                    u8"「弾が尽きるまで撃て！」",
                    u8"「虫けらめェ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「隊長！もうだめです」",
                    u8"「メディーック！！」",
                    u8"「マンダウン！マンダウン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ターゲット・ダウン！」", u8"「グッドジョブ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"イェルスエリート機械兵",
                    u8"Yerles elite machine infantry"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 250;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 234;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"イェルスエリート機械兵", u8"Yerles elite machine infantry");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 250;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 231)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「困ったことになったぞ」",
                    u8"「敬礼！」",
                    u8"「新王国め…」",
                    u8"「フハハハハッ」");
                return 1;
            }
            else
            {
                txt(u8"\"Help the helpless! Crush the vileness\"",
                    u8"\"Atten-TION! Salute!\"",
                    u8"\"For the Kingdom, we shall never fall!\"",
                    u8"\"Who's house? Mah House!\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「撃てぇ！」", u8"「フハー！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「フハー…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「フハハハハ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"辺境の勇士『ギルバート大佐』",
                    u8"<Gilbert> the carnel"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 370;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 231;
            SET_LEVEL(45);
            cdata_portrait(rc) = 33;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"辺境の勇士『ギルバート大佐』", u8"<Gilbert> the carnel");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 370;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 232)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"イェルス自走砲", u8"yerles self-propelled gun"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 373;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 232;
            SET_LEVEL(17);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 4;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -2;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) =
                lang(u8"イェルス自走砲", u8"yerles self-propelled gun");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 373;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 233)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イェルス兵を殺せ！」",
                    u8"「突っ込め！」",
                    u8"「突撃！突撃！」",
                    u8"「ひるむな！」",
                    u8"「ウォォォ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ギャァァァァ」",
                    u8"「衛生兵！！」",
                    u8"「大佐、また一人死にました！」",
                    u8"「仲間が戦闘不能です、大佐！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「敵兵の首とったり！」", u8"「敵兵撃破！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ジューア歩兵", u8"juere infantry"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 377;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 233;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 95;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ジューア歩兵", u8"juere infantry");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 377;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 235)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「イェルス兵を殺せ！」",
                    u8"「突っ込め！」",
                    u8"「突撃！突撃！」",
                    u8"「ひるむな！」",
                    u8"「ウォォォ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ギャァァァァ」",
                    u8"「衛生兵！！」",
                    u8"「大佐、また一人死にました！」",
                    u8"「仲間が戦闘不能です、大佐！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「敵兵の首とったり！」", u8"「敵兵撃破！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ジューア剣闘士", u8"juere swordman"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 377;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 235;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ジューア剣闘士", u8"juere swordman");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 377;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 163)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ロックスロアー", u8"rock thrower"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 251;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 163;
            SET_LEVEL(9);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 25;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ロックスロアー", u8"rock thrower");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 251;
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    }
    if (dbid == 164)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ミャア」",
                    u8"「にゃ」",
                    u8"「ミャ」",
                    u8"「にゅぅ」",
                    u8"「ニャア」");
                return 1;
            }
            else
            {
                txt(u8"\"Meow.\"",
                    u8"\"Mew.\"",
                    u8"\"Mew mew.\"",
                    u8"\"Rowr!\"",
                    u8"\"Mewl.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ニャー！」",
                    u8"「ニャウ！」",
                    u8"「ニャン！」",
                    u8"「ゥニャ！」");
                return 1;
            }
            else
            {
                txt(u8"\"Meow!\"",
                    u8"\"Mew mew!\"",
                    u8"\"Mew!\"",
                    u8"\"Meow\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
            else
            {
                txt(u8"\"Me...meow....\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりニャン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"* ふしゅぅ * ",
                    u8"「ニャァー！」",
                    u8"「にゃー」」",
                    u8"「ゥニャ！」",
                    u8"爪を研ぐ音が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"*hiss*",
                    u8"\"Meoow!\"",
                    u8"\"Meew!\"",
                    u8"\"Mew!\"",
                    u8"\"Meow meow.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1609();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"猫", u8"cat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 164;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"猫", u8"cat");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 246)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ミャア」",
                    u8"「にゃ」",
                    u8"「ミャ」",
                    u8"「にゅぅ」",
                    u8"「ニャア」");
                return 1;
            }
            else
            {
                txt(u8"\"Meow.\"",
                    u8"\"Mew.\"",
                    u8"\"Mew mew.\"",
                    u8"\"Mew!\"",
                    u8"\"Mewl.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ニャー！」",
                    u8"「ニャウ！」",
                    u8"「ニャン！」",
                    u8"「ゥニャ！」");
                return 1;
            }
            else
            {
                txt(u8"\"Meow!\"",
                    u8"\"Mew mew!\"",
                    u8"\"Mew!\"",
                    u8"\"Meow\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
            else
            {
                txt(u8"\"Me...meow....\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりニャン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"* ふしゅぅ * ",
                    u8"「ニャァー！」",
                    u8"「にゃー」」",
                    u8"「ゥニャ！」",
                    u8"爪を研ぐ音が聞こえる。");
                return 1;
            }
            else
            {
                txt(u8"*hiss*",
                    u8"\"Meoow!\"",
                    u8"\"Meew!\"",
                    u8"\"Mew!\"",
                    u8"\"Meow meow.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1609();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 1);
            DBMODE16_DBSPEC_STR(2, lang(u8"シルバーキャット", u8"silver cat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 387;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 246;
            SET_LEVEL(3);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"シルバーキャット", u8"silver cat");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 387;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 332)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おうちしってう？」",
                    u8"「おうちかえう」",
                    u8"「おうちかえう！」",
                    u8"「ママどっち？おうちどっち？」",
                    u8"「ニャア」");
                return 1;
            }
            else
            {
                txt(u8"\"Do you know where my home is?\"",
                    u8"\"I'm going home.\"",
                    u8"\"I'm going home!\"",
                    u8"\"Momma? Where are you?\"",
                    u8"\"Home! Nyaow!\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ころさえう」", u8"「しぬぅ！」");
                return 1;
            }
            else
            {
                txt(u8"\"I'm gonna be killed.\"", u8"\"I'm gonna die!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おうち…かえ…ぅ…」");
                return 1;
            }
            else
            {
                txt(u8"\"I'm...going...hom....e...\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あぁ〜ビックリしたぁ」");
                return 1;
            }
            else
            {
                txt(u8"\"That scared me!\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1609();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"迷子の子猫", u8"stray cat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 387;
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 332;
            SET_LEVEL(9);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"迷子の子猫", u8"stray cat");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 387;
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 229)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ガルルル…」");
                return 1;
            }
            else
            {
                txt(u8"You hear the near silent footfalls of a cat. A Big "
                    u8"cat.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガウッ」", u8"「ガルル！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりニャン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガオー」", u8"「ガル♪」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ライオン", u8"lion"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 368;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 229;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 10;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ライオン", u8"lion");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 368;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 230)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガルルル…」");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガウッ」", u8"「ガルル！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりニャン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガオー」", u8"「ガル♪」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"猫使い『ケシー』", u8"<Cacy> the cat tamer"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"catgod";
            dbmode = 2;
            label_2297();
            cpicref = 369;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 230;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 639;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"猫使い『ケシー』", u8"<Cacy> the cat tamer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"catgod";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 369;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 228)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ミャア」",
                    u8"「にゃ」",
                    u8"「ミャ」",
                    u8"「にゅぅ」",
                    u8"「ニャア」");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"ニャー", u8"ニャウ", u8"ニャン", u8"ゥニャ");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりニャン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"* ふしゅぅ *",
                    u8"「ニャァー！」",
                    u8"「にゃー」」",
                    u8"「ゥニャ！」",
                    u8"爪を研ぐ音が聞こえる。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"カーバンクル", u8"carbuncle"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/cat/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 367;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 228;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 436;
            cdata_ai_act_sub(rc, 1) = 638;
            cdata_ai_act_num(rc) = 21;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"カーバンクル", u8"carbuncle");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 367;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 165)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「クゥン…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりワン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「わん！」", u8"「ゥワン！」」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"犬", u8"dog"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dog";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 165;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 10;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"犬", u8"dog");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dog";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 225)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「くぅ〜」", u8"「ぁぅぁぅ」", u8"「ぅ〜」");
                return 1;
            }
            else
            {
                txt(u8"You hear the high pitched yips of a young dog",
                    u8"A plaintive howl is heard in the distance",
                    u8"Rowf!");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「クゥン…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりワン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「わん！」", u8"「ぁぅぁぅ！」」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"子犬の『ポピー』", u8"<Poppy> the little dog"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dog";
            dbmode = 2;
            label_2297();
            cpicref = 364;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 225;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"子犬の『ポピー』", u8"<Poppy> the little dog");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"dog";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 364;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 226)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ポピー！」", u8"「わん〜わん〜」");
                return 1;
            }
            else
            {
                txt(u8"\"Poppy!\"", u8"\"Wuff wuff.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「なにするの！」");
                return 1;
            }
            else
            {
                txt(u8"\"What! Stop!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「来世は犬になりたい…」");
                return 1;
            }
            else
            {
                txt(u8"\"Poppy, where are you poppy....\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「めっ！」");
                return 1;
            }
            else
            {
                txt(u8"\"Idiot!\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"犬好きの少女『リリアン』", u8"<Rilian> the dog lover"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 365;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 226;
            SET_LEVEL(4);
            cdata_portrait(rc) = 16;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"犬好きの少女『リリアン』", u8"<Rilian> the dog lover");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 365;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 227)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ひっ！」",
                    u8"「猫はどうしてあんなに恐ろしいのだろう」",
                    u8"「細い目が苦手です」");
                return 1;
            }
            else
            {
                txt(u8"\" hate those bloody cats!\"",
                    u8"\"Come closer kitty, I gotta present for ya!\"",
                    u8"\"I've got your number, mate. It's down to two for you. "
                    u8"Ahh! There's a oner. Ha ha, yes. Not long for you "
                    u8"now!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うわー猫ー」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ふんっ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"猫嫌いの『タム』", u8"<Tam> the cat hater"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 366;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 227;
            SET_LEVEL(5);
            cdata_portrait(rc) = 16;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"猫嫌いの『タム』", u8"<Tam> the cat hater");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 366;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 166)
    {
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「きゃぁー」", u8"「ダメぇ！」");
                return 1;
            }
            else
            {
                txt(u8"\"No....no...!\"", u8"\"I'm sorry I failed you.\"");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おかえりなさい♪」");
                return 1;
            }
            else
            {
                txt(u8"\"Welcome home!\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"少女は服のほこりをはらった。",
                    u8"少女はあなたを見てにっこり笑った。",
                    u8"あなたは少女に見とれた。",
                    u8"「うふふ♪」");
                return 1;
            }
            else
            {
                txt(u8"The little girl brushes dust off her clothes.",
                    u8"The little girl smiles at you.",
                    u8"You look admiringly at the little girl.",
                    u8"\"Another death. *grin* \"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"少女", u8"little girl"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 4;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 166;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"少女", u8"little girl");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 4;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 4;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 167)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「チュー！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ネズミ", u8"rat"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"rat";
            dbmode = 2;
            label_2297();
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 167;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ネズミ", u8"rat");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"rat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 168)
    {
        if (dbmode == 12)
        {
            label_1605();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"やどかり", u8"hermit crab"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"shell";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 168;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"やどかり", u8"hermit crab");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"shell";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 170)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"愉快な音楽が聞こえる。");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「出直してくる」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おか」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"大道芸人", u8"public performer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 258;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 170;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"大道芸人", u8"public performer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 258;
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    }
    if (dbid == 175)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「負けたニャー」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"フリージアは死体を玩具にして遊び始めた。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"猫の女王『フリージア』", u8"<Frisia> the cat queen"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"catgod";
            dbmode = 2;
            label_2297();
            cpicref = 348;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 175;
            SET_LEVEL(80);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"猫の女王『フリージア』", u8"<Frisia> the cat queen");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"catgod";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 348;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 176)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata_sex(0)) + u8"ちゃんー」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん？」",
                    u8"「" + _onii(cdata_sex(0)) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん♪」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ダメぇ！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえり、" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + _onii(cdata_sex(0))
                        + u8"ちゃん♪」",
                    u8"「待ってたよ、" + _onii(cdata_sex(0)) + u8"ちゃん」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"あなたは妹の頭をなでた。",
                    u8"あなたは妹の姿に目を細めた。",
                    u8"妹は上目づかいにあなたの顔を覗いた。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"妹", u8"younger sister"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 105;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 176;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"妹", u8"younger sister");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 105;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 249)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata_sex(0)) + u8"ちゃんー」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん？」",
                    u8"「" + _onii(cdata_sex(0)) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん♪」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ダメぇ！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえり、" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + _onii(cdata_sex(0))
                        + u8"ちゃん♪」",
                    u8"「待ってたよ、" + _onii(cdata_sex(0)) + u8"ちゃん」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"あなたは妹の頭をなでた。",
                    u8"あなたは妹の姿に目を細めた。",
                    u8"妹は上目づかいにあなたの顔を覗いた。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"妹", u8"younger sister"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 105;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 249;
            SET_LEVEL(50);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 100;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 643;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"妹", u8"younger sister");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 105;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 210)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata_sex(0)) + u8"ちゃんー」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん？」",
                    u8"「" + _onii(cdata_sex(0)) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata_sex(0)) + u8"ちゃん♪」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ダメぇにゃ！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりにゃ、" + _onii(cdata_sex(0)) + u8"ちゃん！」",
                    u8"「おかえりなさいにゃー、" + _onii(cdata_sex(0))
                        + u8"ちゃん♪」",
                    u8"「待ってたにゃ、" + _onii(cdata_sex(0)) + u8"ちゃん」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"あなたは妹の頭をなでた。",
                    u8"あなたは妹の姿に目を細めた。",
                    u8"妹は上目づかいにあなたの顔を覗いた。",
                    u8"「うにゃん」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"妹猫", u8"younger cat sister"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"catsister";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 210;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"妹猫", u8"younger cat sister");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"catsister";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 211)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「きゃぁー」", u8"「ダメぇ！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりなさい♪」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"嬢は服のほこりをはらった。",
                    u8"嬢はあなたを見てにっこり笑った。",
                    u8"あなたは嬢に見とれた。",
                    u8"「うふふ♪」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"嬢", u8"young lady"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 355;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 211;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = -9998;
            cdata_ai_act_sub(rc, 1) = 449;
            cdata_ai_act_sub(rc, 2) = 447;
            cdata_ai_act_num(rc) = 31;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_ai_heal(rc) = 404;
            cdatan(0, rc) = lang(u8"嬢", u8"young lady");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 355;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 177)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ピー…ザザザザ…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ターゲット破壊確認！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"ゼイレン究極破壊兵器『ウティマ』",
                    u8"<Utima> the destroyer of Xeren"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machinegod";
            dbmode = 2;
            label_2297();
            cpicref = 349;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 177;
            SET_LEVEL(80);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 4;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -2;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = -1;
            cdata_ai_act_sub(rc, 0) = 647;
            cdata_ai_act_num(rc) = 13;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"ゼイレン究極破壊兵器『ウティマ』",
                u8"<Utima> the destroyer of Xeren");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machinegod";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 349;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 1;
            eqrange = 514;
            eqammo(0) = 25030;
            eqammo(1) = 3;
            return 0;
        }
        return 0;
    }
    if (dbid == 178)
    {
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひぃ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"不浄なる者はあなたの死体をむさぼった。");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1596();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 6);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"不浄なる者『アズラシズル』", u8"<Azzrssil> the impure"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"undeadgod";
            dbmode = 2;
            label_2297();
            cpicref = 339;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 178;
            SET_LEVEL(80);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 414;
            cdata_ai_act(rc, 2) = 419;
            cdata_ai_act(rc, 3) = 422;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 443;
            cdata_ai_act_num(rc) = 24;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"不浄なる者『アズラシズル』", u8"<Azzrssil> the impure");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"undeadgod";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 339;
            cdata_image(rc) += 3000;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 179)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"ペットアリーナの主催者『ニノ』",
                    u8"master of pet arena"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 350;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 179;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(
                u8"ペットアリーナの主催者『ニノ』", u8"master of pet arena");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 350;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 208)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *トンカン*  ",
                    u8" *カーン*  ",
                    u8" *キン*  ",
                    u8"鉄を打つ音が響いている。",
                    u8"「つまらんのう」",
                    u8"「ミラルの奴め、何の役にも立たないものばかり作りおって"
                    u8"」",
                    u8"「宝の持ち腐れじゃ」");
                return 1;
            }
            else
            {
                txt(u8"You hear the rhymthic clang of a hammer on steel",
                    u8"You hear the whoosh of a bellows being pumped",
                    u8"You hear the perfect ring of steel-on-steel. It makes "
                    u8"your blood race",
                    u8"\"And just what shall you be, oh noble ingot? A dagger "
                    u8"perhaps, an axe blade by chance? Let us find out...\"",
                    u8"\"Ah! A good shipment of steel today. Oh, what to make, "
                    u8"decisions, decisions...\"",
                    u8"\"With this, I have created half a legend. Your wielder "
                    u8"will make the other half with you.\"",
                    u8"\"Let's just sit you on the shelf oh noble blade, for "
                    u8"soon your brothers shall join you.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"伝説の職人『ガロク』",
                    u8"<Garokk> the legendary smith"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dwarf";
            dbmode = 2;
            label_2297();
            cpicref = 352;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 208;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"伝説の職人『ガロク』", u8"<Garokk> the legendary smith");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"dwarf";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 352;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 209)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「今日のご飯はなんにしよう」",
                    u8"「ガロクの作品には遊びがないね」",
                    u8"「暇だぬ」",
                    u8"「おお、客人かな？」",
                    u8"「猫 イズ フリ〜ダ〜ム♪ 猫 イズ フリ〜ダ〜ム♪」");
                return 1;
            }
            else
            {
                txt(u8"\"Oh, what to make for dinner.\"",
                    u8"\"All work and no play makes Miral a dull boy.\"",
                    u8"\"There's never enough time in the world to get "
                    u8"everything done.\"",
                    u8"\"Guests? Goodness it has been a while indeed.\"",
                    u8"\"I've got a cat I wanna frame! And now nothing shall "
                    u8"ever be the same.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"伝説の職人『ミラル』", u8"<Miral> the legendary smith"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dwarf";
            dbmode = 2;
            label_2297();
            cpicref = 353;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 209;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"伝説の職人『ミラル』", u8"<Miral> the legendary smith");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"dwarf";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 353;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 180)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"辺りは神聖な雰囲気に包まれている。",
                    u8"あなたは何者かの穏やかな視線を感じた。",
                    u8"とても静かで、平和な場所だ。",
                    u8"心の中で、奇妙な祈りの声がこだました。");
                return 1;
            }
            else
            {
                txt(u8"All around you is the sensation of being in a sacred "
                    u8"place",
                    u8"You have seldom felt such an air of peace",
                    u8"All around is very quiet, yet you aren't the least bit "
                    u8"lonely",
                    u8"In your mind you hear the strange echoes of a voice in "
                    u8"prayer");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ニャァー…ァ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"* ふしゅぅ *",
                    u8"「ニャァー！」",
                    u8"「にゃー」」",
                    u8"「ゥニャ！」",
                    u8"爪を研ぐ音が聞こえる。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ツインテール", u8"twintail"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"cat";
            dbmode = 2;
            label_2297();
            cpicref = 259;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 180;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ツインテール", u8"twintail");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"cat";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 259;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 181)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"辺りは神聖な雰囲気に包まれている。",
                    u8"あなたは何者かの穏やかな視線を感じた。",
                    u8"とても静かで、平和な場所だ。",
                    u8"心の中で、奇妙な祈りの声がこだました。");
                return 1;
            }
            else
            {
                txt(u8"All around you is the sensation of being in a sacred "
                    u8"place",
                    u8"You have seldom felt such an air of peace",
                    u8"All around is very quiet, yet you aren't the least bit "
                    u8"lonely",
                    u8"In your mind you hear the strange echoes of a voice in "
                    u8"prayer");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"銀狼", u8"silver wolf"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"hound";
            dbmode = 2;
            label_2297();
            cpicref = 260;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 181;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"銀狼", u8"silver wolf");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"hound";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 260;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 182)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"ナースの匂いがする…");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「キャァー」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりなさい。怪我はしていませんか♪」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"白衣のナース", u8"nurse"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 208;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 182;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 405;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"白衣のナース", u8"nurse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 208;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 183)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「金か？金が欲しいのか？」",
                    u8"「汚い手で触らないでくれるか」",
                    u8"「周りの衆、見てないで助けぬか」",
                    u8"「金の亡者め！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「貴様には一銭もやらん…」",
                    u8"「なんとまあ」",
                    u8"「下衆め」",
                    u8"「まだ死にたくないー…ぐぉ」",
                    u8"「遺言書いといてよかったわ」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「帰ってきおったか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「フン」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(2, lang(u8"大富豪", u8"rich person"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 71;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 183;
            SET_LEVEL(15);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"大富豪", u8"rich person");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 71;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 70;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 184)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「無礼者！」",
                    u8"「お父上に言いつけてやる」",
                    u8"「下郎め」",
                    u8"「汚い！触るな！」",
                    u8"「誰か！」",
                    u8"「下がれ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うわぁ」",
                    u8"「こ、殺さないで」",
                    u8"「助、助けて…うぐ」",
                    u8"「お父上ぇー」",
                    u8"「む、無念」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「チェッ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「この人よわーい」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"貴族の子供", u8"noble child"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 73;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 184;
            SET_LEVEL(9);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"貴族の子供", u8"noble child");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 73;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 72;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 185)
    {
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「観光客だからって馬鹿にするな」",
                    u8"「なんて治安の悪い国だ」",
                    u8"「野蛮な土地だな」",
                    u8"「金などもってないぞ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「こんな国二度とくるか」",
                    u8"「無差別テロだー」",
                    u8"「いやーん」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえり。いやぁ、いい家に住ませてもらっています」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「弱い弱い」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"観光客", u8"tourist"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 122;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 185;
            SET_LEVEL(20);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"観光客", u8"tourist");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 122;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 129;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 350)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「屋台でおいしいもの売ってるかな？」",
                    u8"「今日ははじけるぜ」",
                    u8"「なんとも騒々しいな」",
                    u8"「これが噂の聖夜祭か…」",
                    u8"「見て見て、子供が雪だるまをつくっているよ」",
                    u8"「なんだあの巨人は！」",
                    u8"「すげえ！」",
                    u8"「もう今年も終わりなんだな」",
                    u8"「見ろ人がゴミのようだ」");
                return 1;
            }
            else
            {
                txt(u8"\"Let's check the food stall.\"",
                    u8"\"No! I want to play a little longer!\"",
                    u8"\"What a noisy street.\"",
                    u8"\"So it's the holy night festival people were talking "
                    u8"about...\"",
                    u8"\"Hey look, those children are making cute snowmen.\"",
                    u8"\"Where does the giant come from?\"",
                    u8"\"Holy cow!\"",
                    u8"\"It's that time of year again.\"",
                    u8"\"Aha, some human garbage.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「観光客だからって馬鹿にするな」",
                    u8"「なんて治安の悪い国だ」",
                    u8"「野蛮な土地だな」",
                    u8"「金などもってないぞ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「こんな国二度とくるか」",
                    u8"「無差別テロだー」",
                    u8"「いやーん」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえり。いやぁ、いい家に住ませてもらっています」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「弱い弱い」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 1);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"祭りの観光客", u8"festival tourist"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 477;
            cpicref += 1000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 350;
            SET_LEVEL(10);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"祭りの観光客", u8"festival tourist");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 477;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 476;
            }
            cdata_image(rc) += 1000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 186)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブレイド", u8"blade"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 186;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ブレイド", u8"blade");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 6100100;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 187)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブレイドβ", u8"blade alpha"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 187;
            SET_LEVEL(13);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ブレイドβ", u8"blade alpha");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 6100120;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 188)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ブレイドΩ", u8"blade omega"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 188;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ブレイドΩ", u8"blade omega");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 6100150;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 345)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"*ブルン ブルン* ", u8"*バババババ* ");
                return 1;
            }
            else
            {
                txt(u8"*Varoom!*", u8"*Va-Va-Va*");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「てつぅぅぅうううおおおおおおお！！」",
                    u8"「よう、どうした。揉め事か？」",
                    u8"「やっとモーターのコイルが温まって来た所だぜ」");
                return 1;
            }
            else
            {
                txt(u8"\"Teeee tsuuu oooooo!!.\"",
                    u8"\"Yo, what's up? A fight?\"",
                    u8"\"Relax, it's gonna take some time to warm my engine "
                    u8"up.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"*ぷすん* ");
                return 1;
            }
            else
            {
                txt(u8"*Pan*");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ピーキーすぎてお前には無理だよ」",
                    u8"「テツオ、まってろよ。俺が苦痛を終わらせてやる」");
                return 1;
            }
            else
            {
                txt(u8"\"My body is too peaky for ya.\"",
                    u8"\"Just hold on Tetsuo. I'm gonna find you to end your "
                    u8"pain.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『カネダのバイク』", u8"<Kaneda Bike>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bike";
            dbmode = 2;
            label_2297();
            cpicref = 470;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 345;
            SET_LEVEL(22);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"『カネダのバイク』", u8"<Kaneda Bike>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"bike";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 470;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 346)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"* ボ ボ ボ * ", u8"* プスン * ");
                return 1;
            }
            else
            {
                txt(u8"*Bo-Bo-Bo*", u8"*Pusss*");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「われぇ、いい度胸じゃぁ！」", u8"「おんどりゃぁ！」");
                return 1;
            }
            else
            {
                txt(u8"\"Craaaap! You are so dead!.\"",
                    u8"\"You dorf, get away get away!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"*ぷすん* ");
                return 1;
            }
            else
            {
                txt(u8"*Pan*");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「てつぅぅぅうううおおおおおおお！！」",
                    u8"「よう、どうした。揉め事か？」",
                    u8"「やっとモーターのコイルが温まって来た所だぜ」");
                return 1;
            }
            else
            {
                txt(u8"\"Teeee tsuuu oooooo!!.\"",
                    u8"\"Yo, what's up? A fight?\"",
                    u8"\"Relax, it's gonna take some time to warm my engine "
                    u8"up.\"");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 5);
            DBMODE16_DBSPEC_STR(2, lang(u8"カブ", u8"cub"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"bike";
            dbmode = 2;
            label_2297();
            cpicref = 471;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 346;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"カブ", u8"cub");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"bike";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 471;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 341)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 25);
            DBMODE16_DBSPEC_STR(2, lang(u8"地雷犬", u8"mine dog"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref = 434;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 341;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 15;
            creaturepack = 0;
            cbitmod(988, rc, 1);
            cdata_ai_act(rc, 0) = 659;
            cdata_ai_act(rc, 1) = -4;
            cdata_ai_act_sub(rc, 0) = 466;
            cdata_ai_act_num(rc) = 12;
            cdatan(0, rc) = lang(u8"地雷犬", u8"mine dog");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 434;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 258)
    {
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"鉄の処女", u8"iron maiden"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machine";
            dbmode = 2;
            label_2297();
            cpicref = 198;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 258;
            SET_LEVEL(25);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"鉄の処女", u8"iron maiden");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"machine";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 6100150;
            cdata_image(rc) = 198;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            cdata_damage_reaction_info(rc) = 250061;
            return 0;
        }
        return 0;
    }
    if (dbid == 189)
    {
        if (dbmode == 12)
        {
            label_1590();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"異形の目", u8"deformed eye"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref = 271;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 189;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 632;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"異形の目", u8"deformed eye");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 271;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 190)
    {
        if (dbmode == 12)
        {
            label_1590();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"不浄なる瞳", u8"impure eye"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"eye";
            dbmode = 2;
            label_2297();
            cpicref = 271;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 190;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 632;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"不浄なる瞳", u8"impure eye");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"eye";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 271;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 191)
    {
        if (dbmode == 12)
        {
            label_1610();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"ウィスプ", u8"wisp"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/ether/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"wisp";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 191;
            SET_LEVEL(14);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 421;
            cdata_ai_act(rc, 2) = 604;
            cdata_ai_act_sub(rc, 0) = 633;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) = lang(u8"ウィスプ", u8"wisp");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"wisp";
            dbmode = 3;
            label_2297();
            sdata(52, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 192)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"ハリねずみ", u8"hedgehog"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"crab";
            dbmode = 2;
            label_2297();
            cpicref = 273;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 192;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ハリねずみ", u8"hedgehog");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"crab";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 273;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            cdata_damage_reaction_info(rc) = 200061;
            return 0;
        }
        return 0;
    }
    if (dbid == 193)
    {
        if (dbmode == 12)
        {
            label_1610();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"輝くハリねずみ", u8"shining hedgehog"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/ether/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"crab";
            dbmode = 2;
            label_2297();
            cpicref = 273;
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 193;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"輝くハリねずみ", u8"shining hedgehog");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"crab";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 273;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            cdata_damage_reaction_info(rc) = 500062;
            return 0;
        }
        return 0;
    }
    if (dbid == 195)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *クックッ* ", u8"「コケー」", u8"「コッ」");
                return 1;
            }
            else
            {
                txt(u8"You hear something scratching for worms",
                    u8"\"*Bwwwuuuuu-buk-buk-buk-buKAWK*\"",
                    u8"You hear poultry in the distance");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「コケー」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"鶏", u8"chicken"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"chicken";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 195;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"鶏", u8"chicken");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"chicken";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 196)
    {
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"パンプキン", u8"pumpkin"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 275;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 196;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = -9999;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"パンプキン", u8"pumpkin");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400100;
            cdata_image(rc) = 275;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 201)
    {
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(2, lang(u8"パピー", u8"puppy"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 275;
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 201;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = -9999;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"パピー", u8"puppy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400150;
            cdata_image(rc) = 275;
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 197)
    {
        if (dbmode == 12)
        {
            if (rnd(8) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(2, lang(u8"南瓜の怪物", u8"greater pumpkin"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 275;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 197;
            SET_LEVEL(18);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = -9998;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"南瓜の怪物", u8"greater pumpkin");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400200;
            cdata_image(rc) = 275;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 198)
    {
        if (dbmode == 12)
        {
            if (rnd(6) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 2);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 60);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ハロウィンナイトメア", u8"halloween nightmare"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mandrake";
            dbmode = 2;
            label_2297();
            cpicref = 275;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 198;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act_sub(rc, 0) = -9997;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) =
                lang(u8"ハロウィンナイトメア", u8"halloween nightmare");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mandrake";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5400250;
            cdata_image(rc) = 275;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 199)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"闇子", u8"stalker"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"stalker";
            dbmode = 2;
            label_2297();
            cpicref = 276;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 199;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"闇子", u8"stalker");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"stalker";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 276;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 200)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"闇の老師", u8"shadow stalker"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"stalker";
            dbmode = 2;
            label_2297();
            cpicref = 276;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 200;
            SET_LEVEL(26);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"闇の老師", u8"shadow stalker");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"stalker";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 276;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 202)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ぐぉぉぉん」");
                return 1;
            }
            else
            {
                txt(u8"You hear a bonfire in the distance, only it sounds like "
                    u8"it's breathing");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ウフハァ」",
                    u8"「グゴガー」",
                    u8"「ギャオース！」",
                    u8" *どすん* ",
                    u8" *ドスッ* ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"火の巨人『エボン』", u8"<Ebon> the fire giant"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"giant";
            dbmode = 2;
            label_2297();
            cpicref = 351;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 202;
            SET_LEVEL(80);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 65;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"火の巨人『エボン』", u8"<Ebon> the fire giant");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"giant";
            dbmode = 3;
            label_2297();
            sdata(50, rc) = 500;
            cdata_sex(rc) = 0;
            cdata_image(rc) = 351;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 203)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"モイアー「さあ、寄った寄った！」",
                    u8"モイアー「これなるは伝説の火の巨人、見なきゃ損だよ！」",
                    u8"モイアー「他の店じゃ手に入らない珍品を見ていってくれ」");
                return 1;
            }
            else
            {
                txt(u8"\"Hey now, I stopped, I stopped!\"",
                    u8"\"Behold! a Legendary Giant of Fire! Be careful you "
                    u8"aren't burned now.\"",
                    u8"\"And if you think that's special, wait till you see "
                    u8"what I got over here!\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「観光客だからって馬鹿にするな」",
                    u8"「なんて治安の悪い国だ」",
                    u8"「野蛮な土地だな」",
                    u8"「金などもってないぞ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"見世物屋の『モイアー』", u8"<Moyer> the crooked"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 23;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 203;
            SET_LEVEL(10);
            cdata_portrait(rc) = 0;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"見世物屋の『モイアー』", u8"<Moyer> the crooked");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 23;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 205)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「" + _syujin(cdata_sex(0)) + u8"〜」",
                    _syujin(cdata_sex(0)) + u8"〜",
                    u8"「用事はありませんか♪」",
                    u8"メイドの熱い視線を感じる…");
                return 1;
            }
            else
            {
                txt("",
                    u8"\"Oh Master, I don't do THOSE sorts of things♪...\"",
                    u8"The maid looks good enough to touch");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おいたが過ぎますよ！」", u8"「お仕置きです！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ダメぇ！」",
                    u8"「" + _syujin(cdata_sex(0)) + u8"ー！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりなさいませ、" + _syujin(cdata_sex(0))
                        + u8"〜」",
                    u8"「おかえりなさいまし〜」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(2, lang(u8"メイド", u8"maid"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 104;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 205;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"メイド", u8"maid");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 104;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 105;
            }
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 207)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ぐぉぉぉん」");
                return 1;
            }
            else
            {
                txt(u8"You hear a bonfire in the distance, only it sounds like "
                    u8"it's breathing, AND moving...");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ウフハァ」",
                    u8"「グゴガー」",
                    u8"「ギャオース！」",
                    u8" *どすん* ",
                    u8" *ドスッ* ");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"火の巨人『エボン』", u8"<Ebon> the fire giant"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"giant";
            dbmode = 2;
            label_2297();
            cpicref = 351;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 207;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 65;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 602;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"火の巨人『エボン』", u8"<Ebon> the fire giant");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"giant";
            dbmode = 3;
            label_2297();
            sdata(50, rc) = 500;
            cdata_sex(rc) = 0;
            cdata_image(rc) = 351;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 212)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"実験台", u8"<Stersha> the queen of Palmia"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 117;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 212;
            SET_LEVEL(1);
            cdata_portrait(rc) = 54;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"実験台", u8"<Stersha> the queen of Palmia");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 117;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 56;
            return 0;
        }
        return 0;
    }
    if (dbid == 213)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あー…かわいいお花！」",
                    u8"「ついていっていい？」",
                    u8"「サンドラさんの赤いケープほしい…」",
                    u8"「ざっつあぷりちーふらわー」",
                    u8"「赤って好きな色なの〜」",
                    u8"「この花の冠はお母さんに編んでもらったの」",
                    u8"「るるる♪」");
                return 1;
            }
            else
            {
                txt(u8"\"Oh my! Such pretty flowers♪\"",
                    u8"\"Can I tag along? I won't be a bother♪\"",
                    u8"\"I hope Sandra's red cape...♪\"",
                    u8"\"Eat flowers evil-doer!♪\"",
                    u8"\"Red is the color of love, of blood, and of roses♪\"",
                    u8"\"A crown of flowers did his mother weave with all her "
                    u8"heart...♪\"",
                    u8"\"♪La, laaaah, la, la-la. Lah, la-la,, la la....♪\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「どうして、そんなことするの？」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「あ…もどってきた！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「怖いのはいや…」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"無邪気な少女『グウェン』", u8"<Gwen> the innocent"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 356;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 213;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 4;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"無邪気な少女『グウェン』", u8"<Gwen> the innocent");
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 356;
            if (cdata_sex(rc) == 1)
            {
                cdata_image(rc) = 356;
            }
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 221)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「おかあさん…」",
                    u8"「ひとりにしないでよ」",
                    u8"「みゅ…」");
                return 1;
            }
            else
            {
                txt(u8"\"Mother…\"",
                    u8"\"Do not go alone.\"",
                    u8"\"Oh, look at you…\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ごめんね…ごめんね…おかあさん」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"ひとりぼっちの『パエル』", u8"Lonely <Pael>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 358;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 221;
            SET_LEVEL(10);
            cdata_portrait(rc) = 15;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"ひとりぼっちの『パエル』", u8"Lonely <Pael>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 358;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 222)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「うふっ。パエルはいつまでも甘えん坊さんね」",
                    u8"「あらあら。心配しないでも、私は平気よ」",
                    u8"「けほっ。けほっ」",
                    u8"「いい子ね」");
                return 1;
            }
            else
            {
                txt(u8"\"Pael, such a spoiled child…dear oh dear.\"",
                    u8"\"Hush now, I've got you.\"",
                    u8"\"I hope Pael is not in trouble with the guards "
                    u8"again…\"",
                    u8"\"Now you be good dear, understand?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ああ…パエル…パエル…」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"パエルの母『リリィ』", u8"Pael's mom <Lily>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 359;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 222;
            SET_LEVEL(15);
            cdata_portrait(rc) = 13;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"パエルの母『リリィ』", u8"Pael's mom <Lily>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 359;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 223)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あんな極上の女はそうはいねえ」",
                    u8"「俺の手に掛かれば、どんな女もイチコロよ」",
                    u8" *レロレロレロ* ",
                    u8"「まったく罪な男に生まれちまったもんだ」");
                return 1;
            }
            else
            {
                txt(u8"\"Ladies! The line starts here!\"",
                    u8"\"No woman can resist my charms, be they my dashing "
                    u8"good looks, my wit and charm, or even my coinpurse.\"",
                    u8"\"ero-ero-ero-ero, mushroom, mushroom!\"",
                    u8"\"I am the Gods gift to women. Come and get a memory "
                    u8"you shall never forget!\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「真の男ってものを見せてやるよ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ママー！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ペッ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"女たらしの『ラファエロ』", u8"<Raphael> the womanizer"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 361;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 223;
            SET_LEVEL(10);
            cdata_portrait(rc) = 14;
            cdata_ai_calm(rc) = 2;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"女たらしの『ラファエロ』", u8"<Raphael> the womanizer");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 361;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 224)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「イーック」",
                    u8"「か、かみかぜ…」",
                    u8"「ィィーック」",
                    u8"「なんという生物だ」");
                return 1;
            }
            else
            {
                txt(u8"\"Let's roll!\"",
                    u8"\"I may be new to this whole knight gig, but I won't be "
                    u8"for long!\"",
                    u8"\"Are my spurs polished enough you think? I'd just die "
                    u8"if a senior thought they were sub-par.\"",
                    u8"You hear someone adjusting their armor for the "
                    u8"umpteenth time");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「けが人相手に卑怯な！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ああ…立派な騎士になりたかった…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ガードに突き出してやる」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"見習い騎士『アインク』", u8"<Ainc> the novice knight"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 362;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 224;
            SET_LEVEL(7);
            cdata_portrait(rc) = 18;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"見習い騎士『アインク』", u8"<Ainc> the novice knight");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 362;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 243)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「ヤ、ヤツらがくる！」",
                    u8"「撃つのを止めるな…ヤツらを近づけるな！」",
                    u8"「オーマイガッ！」",
                    u8"「神よぉ…」");
                return 1;
            }
            else
            {
                txt(u8"\"Pah, a minor flesh wound…\"",
                    u8"\"Come closer… I got rounds for this thing still…\"",
                    u8"\"It's not a tumor!\"",
                    u8"\"I'll be back.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うわぁぁぁ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「爆死よりはマシか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「アポ！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"負傷兵『アーノルド』",
                    u8"<Arnord> the injured soldier"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 383;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 243;
            SET_LEVEL(15);
            cdata_portrait(rc) = 36;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"負傷兵『アーノルド』", u8"<Arnord> the injured soldier");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 383;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 247)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「るんるんるん♪」",
                    u8"「うみみゃ？」",
                    u8"「にしし！」",
                    u8"「ふ〜んふ〜んふ〜ん♪1」",
                    u8"「きのこのこのこげんきのこぉ〜♪ 」",
                    u8"「おー。えりんぎまいたけぶなしめじぃ〜」",
                    u8"「フーン　フンフン　フーン　フンフン　ネコのフ〜ン♪　フ"
                    u8"ーン　フンフン　フーン　フンフン　かたい♪」");
                return 1;
            }
            else
            {
                txt(u8"\"I nyo talk funny, nyou talk funny♪\"",
                    u8"\"Nyah! Water! I hates it so.\"",
                    u8"\"Pug!\"",
                    u8"\"Nyo touching! No Bump-Bump for nyou.\"",
                    u8"\"♪Nyobody knyows the touble Mia's seen, nyobody knyows "
                    u8"Mia's Tru-bull♪\"",
                    u8"You hear the oddest voice in the crowd, it is lilting "
                    u8"and...cat-like?",
                    u8"\"Meow♪1\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「はわわ、きっと来世は猫に生まれるんだモン」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「アーン、バカ♪」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"猫かぶり『ミーア』", u8"<Mia> the cat freak"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 388;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 247;
            SET_LEVEL(4);
            cdata_portrait(rc) = 34;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"猫かぶり『ミーア』", u8"<Mia> the cat freak");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 388;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 252)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「意味なんてものはないさ」",
                    u8"「身体はまだ動くよ、油の切れた機械のように。だが心は…」",
                    u8"「もし生まれ変われるのなら…」",
                    u8"「もう死んでもいいかな？」");
                return 1;
            }
            else
            {
                txt(u8"\"I mean there's nothing in my soul but pain and "
                    u8"misery. Oh and agony too, can't leave that out.\"",
                    u8"\"My body will keep moving, like a machine, but without "
                    u8"the oils of love, my heart will not stop squeaking\"",
                    u8"You hear the shuffling step of a man who's world is "
                    u8"nothing but pain and misery. With just an aftertase of "
                    u8"agony, for good measure",
                    u8"\"Will the kiss of Death bring an end to the cloying, "
                    u8"double-plus-ungood that is my life?\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ああ、わかりやすくていいね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「死か。別に何も感じない」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「心配するな。生きている価値なんて、もともとこの世界には"
                    u8"ないよ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"悩める魔術士『レントン』",
                    u8"<Renton> the suffering wizard"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 392;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 252;
            SET_LEVEL(45);
            cdata_portrait(rc) = 5;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 417;
            cdata_ai_act(rc, 1) = 434;
            cdata_ai_act(rc, 2) = 415;
            cdata_ai_act(rc, 3) = 454;
            cdata_ai_act_num(rc) = 4;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"悩める魔術士『レントン』",
                u8"<Renton> the suffering wizard");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 392;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 253)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「私に不可能はないのです」",
                    u8"「捕まえられるものなら、どうぞいつでも」",
                    u8"「そこらのコソ泥と、一緒にしないでください」");
                return 1;
            }
            else
            {
                txt(u8"\"Impossible? Bah, to you maybe.\"",
                    u8"\"You catch me? Ha! You'd have a better chance "
                    u8"shackling your shadow!\"",
                    u8"You hear the swagger of a man of supreme confidence, "
                    u8"only it's oh so quiet…");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ホッホッホッ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「これは何かの間違いです」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ホホーっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(u8"稀代の泥棒『マークス』", u8"<Marks> the great thief"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 394;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 253;
            SET_LEVEL(25);
            cdata_portrait(rc) = 1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"稀代の泥棒『マークス』", u8"<Marks> the great thief");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 394;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 259)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「もえちゃえ」",
                    u8"「クズね。この世界は」",
                    u8"「あたし、綺麗かしら？」");
                return 1;
            }
            else
            {
                txt(u8"You hear a someone making ticking sounds, followed by a "
                    u8"pantomimed 'Ka-BOOOOM', followed by manical laughter",
                    u8"\"He says to me, he says to me, 'Baby I'm TIRED of "
                    u8"workin' for the MAN!' I says, I says, WHY DON'T YOU "
                    u8"BLOW HIM TO BITS?\"",
                    u8"\"You got STYLE, baby. But if you're going to be a real "
                    u8"villain, you gotta get a gimmick.' And so I go I says "
                    u8"YEAH, baby. A gimmick, that's it. High explosives.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヘンタイ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「全部、全部、真っ赤にもえちゃ…」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「綺麗な血。ぺろっ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"爆弾魔『ノエル』", u8"<Noel> the bomber"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 199;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 259;
            SET_LEVEL(20);
            cdata_portrait(rc) = 15;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"爆弾魔『ノエル』", u8"<Noel> the bomber");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 199;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 301)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「うむうむ、精進せよ」",
                    u8"「困ったことになったぞ」",
                    u8"「軍人たるもの、常に身だしなみに気をつけねばならぬ」");
                return 1;
            }
            else
            {
                txt(u8"\"Kill a man, they put you in the gallows. Kill "
                    u8"ten-thousand, they make you a General.\"",
                    u8"\"We're going to need all the help we can get, yes "
                    u8"indeed.\"",
                    u8"\"You know what separates a soldier from a thug? The "
                    u8"polish on his buttons, that's what.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「貴様、軍事裁判にかけてやるわ」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ちょこざいなー！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「こわっぱが」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"パルミア少将『コネリー』",
                    u8"<Conery> Palmian major general"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 403;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 301;
            SET_LEVEL(38);
            cdata_portrait(rc) = 39;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"パルミア少将『コネリー』",
                u8"<Conery> Palmian major general");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 403;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 214)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やばいヤマだったぜ」",
                    u8"「お、カモだ…」",
                    u8"「ククク…」");
                return 1;
            }
            else
            {
                txt(u8"\"Heh, easy money…\"",
                    u8"\"Think I can get some good coin for those fancy bits "
                    u8"you got on stranger?\"",
                    u8"\"Another one with a coinpurse just dangling there, "
                    u8"like a bit of ripe fruit. Time to pluck it.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「覚えていろよ」", u8"「やめてください！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「よう、生きてたか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ふん！青二才め」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"見習い盗賊", u8"thief"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 166;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 214;
            SET_LEVEL(2);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"見習い盗賊", u8"thief");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            cdata_image(rc) = 166;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 215)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やばいヤマだったぜ」",
                    u8"「お、カモだ…」",
                    u8"「ククク…」");
                return 1;
            }
            else
            {
                txt(u8"\"Man, this one'll feed me for a week. Two even!\"",
                    u8"\"I was just sayin' we needed some coin, and look, it "
                    u8"just came walkin' towards us.\"",
                    u8"\"Your GP or your HP good chum!\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「覚えていろよ」", u8"「やめてください！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「よう、生きてたか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ふん！青二才め」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 3);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"強盗", u8"robber"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 166;
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 215;
            SET_LEVEL(5);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"強盗", u8"robber");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 166;
            cdata_image(rc) += 3000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 217)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「やばいヤマだったぜ」",
                    u8"「お、カモだ…」",
                    u8"「ククク…」");
                return 1;
            }
            else
            {
                txt(u8"\"Like taking candy from a baby in armor.\"",
                    u8"You hear someone humming the *Money* tune while "
                    u8"cracking their knuckles",
                    u8"\"Another satisifying finance adjustment.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「覚えていろよ」", u8"「やめてください！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「よう、生きてたか」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ふん！青二才め」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 4);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"マスターシーフ", u8"master thief"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 166;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 217;
            SET_LEVEL(35);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 25;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 635;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"マスターシーフ", u8"master thief");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 166;
            cdata_image(rc) += 4000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 216)
    {
        if (dbmode == 12)
        {
            label_1606();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 20);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"イスの偉大なる種族", u8"great race of Yith"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yith";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 216;
            SET_LEVEL(50);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 601;
            cdata_ai_act(rc, 2) = 636;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) =
                lang(u8"イスの偉大なる種族", u8"great race of Yith");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yith";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(54, rc) = 500;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 218)
    {
        if (dbmode == 12)
        {
            label_1606();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"シュブ＝ニグラス", u8"Shub-Niggurath"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yith";
            dbmode = 2;
            label_2297();
            cpicref = 277;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 218;
            SET_LEVEL(45);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 0;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -3;
            cdata_ai_act(rc, 1) = -3;
            cdata_ai_act(rc, 2) = 410;
            cdata_ai_act(rc, 3) = 636;
            cdata_ai_act_sub(rc, 0) = 424;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"シュブ＝ニグラス", u8"Shub-Niggurath");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yith";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            sdata(54, rc) = 500;
            cdata_image(rc) = 277;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 219)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 80);
            DBMODE16_DBSPEC_STR(2, lang(u8"ガグ", u8"gagu"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"orc";
            dbmode = 2;
            label_2297();
            cpicref = 278;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 219;
            SET_LEVEL(38);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 613;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"ガグ", u8"gagu");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"orc";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 278;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 220)
    {
        if (dbmode == 12)
        {
            label_1606();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 30);
            DBMODE16_DBSPEC_STR(2, lang(u8"螺旋の王", u8"spiral king"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yith";
            dbmode = 2;
            label_2297();
            cpicref = 430;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 220;
            SET_LEVEL(65);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 417;
            cdata_ai_act(rc, 1) = 434;
            cdata_ai_act(rc, 2) = 415;
            cdata_ai_act(rc, 3) = 454;
            cdata_ai_act_sub(rc, 0) = 636;
            cdata_ai_act_num(rc) = 14;
            cdatan(0, rc) = lang(u8"螺旋の王", u8"spiral king");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"yith";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            sdata(54, rc) = 500;
            cdata_image(rc) = 430;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 250)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"妖精", u8"fairy"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"fairy";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 250;
            SET_LEVEL(13);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 60;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 40;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 423;
            cdata_ai_act_sub(rc, 0) = 410;
            cdata_ai_act_sub(rc, 1) = 635;
            cdata_ai_act_num(rc) = 22;
            cdatan(0, rc) = lang(u8"妖精", u8"fairy");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"fairy";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 260)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うみみゃ」",
                    u8"「みゅー」",
                    u8"「みゃ」",
                    u8" *ごろごろ* ");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「フシューッ」", u8"「うみみゃ！」", u8"「みゃ！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「うみ…みゃ…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりみゃー」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"黒猫は尻尾をふった。");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"黒猫", u8"black cat"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 211;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 260;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 75;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 30;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 414;
            cdata_ai_act_sub(rc, 1) = 601;
            cdata_ai_act_sub(rc, 2) = 636;
            cdata_ai_act_num(rc) = 31;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"黒猫", u8"black cat");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 211;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 261)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *パタパタ*  ", u8"「にひひ」", u8" *ハタハタ* ");
                return 1;
            }
            else
            {
                txt(u8"You hear the fluttering of gossamer wings",
                    u8"You hear tittering laughter like tiny crystal bells",
                    u8"You smell what reminds you of sugerplums…");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"妖精さん", u8"cute fairy"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 217;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 261;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 20;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -2;
            cdata_ai_act_sub(rc, 0) = 443;
            cdata_ai_act_sub(rc, 1) = 447;
            cdata_ai_act_sub(rc, 2) = 415;
            cdata_ai_act_num(rc) = 31;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"妖精さん", u8"cute fairy");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 217;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 262)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"アンドロイド", u8"android"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 218;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 262;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 40;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 3;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 647;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"アンドロイド", u8"android");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 218;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 263)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *パタパタ*  ", u8" * ばさっばさっ*", u8" *ハタハタ* ");
                return 1;
            }
            else
            {
                txt(u8"You hear what sounds like wings of feather, but with "
                    u8"grace and dignity somehow...",
                    u8"You hear a quiet voice in prayer, but with a note of "
                    u8"sadness...",
                    u8"You smell Myrrh in the air, but with the faintest hints "
                    u8"of charcoal…");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「きゃあ！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「地獄に落ちなさい」", u8"「いいざまね」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"黒天使", u8"black angel"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 236;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 263;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 8;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -1;
            cdata_ai_act(rc, 2) = 648;
            cdata_ai_act(rc, 3) = -2;
            cdata_ai_act_sub(rc, 0) = 446;
            cdata_ai_act_sub(rc, 1) = 647;
            cdata_ai_act_sub(rc, 2) = 447;
            cdata_ai_act_num(rc) = 34;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"黒天使", u8"black angel");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 236;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 264)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"追放者", u8"exile"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 269;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 264;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 65;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 414;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act(rc, 2) = 418;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) = lang(u8"追放者", u8"exile");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 269;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 265)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"黄金の騎士", u8"golden knight"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 267;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 265;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 8;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 648;
            cdata_ai_act_sub(rc, 1) = 444;
            cdata_ai_act_num(rc) = 21;
            cdata_ai_heal(rc) = 401;
            cdatan(0, rc) = lang(u8"黄金の騎士", u8"golden knight");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 267;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 266)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"防衛者", u8"defender"));
            DBMODE16_DBSPEC_STR(8, u8"/god/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"servant";
            dbmode = 2;
            label_2297();
            cpicref = 242;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 266;
            SET_LEVEL(8);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 8;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 442;
            cdata_ai_act_sub(rc, 1) = 444;
            cdata_ai_act_num(rc) = 21;
            cdata_ai_heal(rc) = 404;
            cdatan(0, rc) = lang(u8"防衛者", u8"defender");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"servant";
            dbmode = 3;
            label_2297();
            dbidn = u8"warmage";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 242;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 267)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぱかぱか* ", u8" *ぱからっぱからっ*", u8" *パコパコ*");
                return 1;
            }
            else
            {
                txt(u8"You hear faltering hoofbeats in the distance");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひ…ひん…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1591();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"駄馬", u8"lame horse"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/horse/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"horse";
            dbmode = 2;
            label_2297();
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 267;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"駄馬", u8"lame horse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"horse";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 276)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぱかぱか* ", u8" *ぱからっぱからっ*", u8" *パコパコ*");
                return 1;
            }
            else
            {
                txt(u8"You hear hoofbeats, but they are wild and free");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひ…ひん…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1591();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 6);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"野生馬", u8"wild horse"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/horse/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"horse";
            dbmode = 2;
            label_2297();
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 276;
            SET_LEVEL(4);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"野生馬", u8"wild horse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"horse";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 6000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 275)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぱかぱか* ", u8" *ぱからっぱからっ*", u8" *パコパコ*");
                return 1;
            }
            else
            {
                txt(u8"You hear hoofbeats, a trot that almost belongs on a "
                    u8"parade");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひ…ひん…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1591();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 15);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"ノイエル馬", u8"Noyel horse"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/horse/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"horse";
            dbmode = 2;
            label_2297();
            cpicref += 15000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 275;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ノイエル馬", u8"Noyel horse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"horse";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 15000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 268)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぱかぱか* ", u8" *ぱからっぱからっ*", u8" *パコパコ*");
                return 1;
            }
            else
            {
                txt(u8"You hear the crisp hoofbeats of a horse trained for "
                    u8"war");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひ…ひん…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1591();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 16);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"ヨウィン馬", u8"Yowyn horse"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/horse/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"horse";
            dbmode = 2;
            label_2297();
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 268;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ヨウィン馬", u8"Yowyn horse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"horse";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 16000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 277)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ぱかぱか* ", u8" *ぱからっぱからっ*", u8" *パコパコ*");
                return 1;
            }
            else
            {
                txt(u8"You hear hoofbeats. You hope it's not zebras");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ひ…ひん…」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ヒヒーン！」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1591();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 10);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"サラブレッド", u8"wild horse"));
            DBMODE16_DBSPEC_STR(8, u8"/wild/horse/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"horse";
            dbmode = 2;
            label_2297();
            cpicref += 10000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 277;
            SET_LEVEL(20);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"サラブレッド", u8"wild horse");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -1;
            cdata_original_relationship(rc) = -1;
            cdata_40(rc) = -10000;
            dbidn = u8"horse";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 10000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 278)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 70);
            DBMODE16_DBSPEC_STR(2, lang(u8"ミュータント", u8"mutant"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mutant";
            dbmode = 2;
            label_2297();
            cpicref = 191;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 278;
            SET_LEVEL(6);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"ミュータント", u8"mutant");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"mutant";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_image(rc) = 191;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 279)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「これからの世界はカガクなのじゃ」",
                    u8"「実験体が足りぬ」",
                    u8"「ふむふむ…この遺伝子を猫に組み込めば…」");
                return 1;
            }
            else
            {
                txt(u8"\"Science is it's own reward!\"",
                    u8"\"With a little bit of this, and a little bit of that, "
                    u8"why, who knows what you are going to get?\"",
                    u8"\"I wonder if a black cat's genes are more or less "
                    u8"lucky than a regular cat?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「カガク万歳！」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"生化学者『イコール』", u8"<Icolle> the biologist"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"yerles";
            dbmode = 2;
            label_2297();
            cpicref = 263;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 279;
            SET_LEVEL(15);
            cdata_portrait(rc) = 17;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"生化学者『イコール』", u8"<Icolle> the biologist");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"yerles";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 263;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 280)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「街の衛生は俺が守る！」",
                    u8"「街道にゴミを捨てる奴はゆるさねえ」",
                    u8"「俺はゴミの天敵だ」");
                return 1;
            }
            else
            {
                txt(u8"\"This citie's health is my charge!\"",
                    u8"\"Those who DARE litter before me shall face my "
                    u8"broom!\"",
                    u8"\"I am garbage's worst nightmare.\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「俺はゴミじゃない！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「掃除完了」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"掃除屋『バルザック』", u8"<Balzak> the janiator"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 192;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 280;
            SET_LEVEL(10);
            cdata_portrait(rc) = 30;
            cdata_ai_calm(rc) = 5;
            cdata_ai_move(rc) = 70;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"掃除屋『バルザック』", u8"<Balzak> the janiator");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 192;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 288)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"魔法を詠唱する声が聞こえる。",
                    u8"辺りはピリピリとした緊張で包まれている。",
                    u8"部屋全体に魔力の波がただよっている。");
                return 1;
            }
            else
            {
                txt(u8"\"Magic is not for the faint of heart, nor dull of "
                    u8"mind.\"",
                    u8"You hear chants for spells you can't even begin to "
                    u8"imagine the purpose of",
                    u8"A pulse of arcane and raw eldritch energies nearly "
                    u8"knocks you off your feet");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「口で言っても無駄のようですね」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「そ、そんなはずはないのです！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「みなさん、新たな献体が手に入りましたよ」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"魔術士ギルドマスター『レヴラス』",
                    u8"<Revlus> the mage guildmaster"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 193;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 288;
            SET_LEVEL(55);
            cdata_portrait(rc) = 13;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 65;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 414;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act(rc, 2) = 418;
            cdata_ai_act_num(rc) = 3;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"魔術士ギルドマスター『レヴラス』",
                u8"<Revlus> the mage guildmaster");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 193;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 290)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この先は魔術士ギルドの管轄だ」",
                    u8"「止まれ…身分を照会させてもらう」");
                return 1;
            }
            else
            {
                txt(u8"\"I am an officer of the Mage Guild's jurisdiction. "
                    u8"Beware the un-learn-ed.\"",
                    u8"\"Stop... Let me make sure you are on my lists.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"魔術士ギルドの番人『レクサス』",
                    u8"<Lexus> the guild watchman"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 290;
            SET_LEVEL(38);
            cdata_portrait(rc) = 5;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 65;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = 414;
            cdata_ai_act(rc, 1) = 415;
            cdata_ai_act(rc, 2) = 418;
            cdata_ai_act_num(rc) = 3;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"魔術士ギルドの番人『レクサス』",
                u8"<Lexus> the guild watchman");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"wizard";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 196;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 292)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"盗賊ギルドマスター『シン』",
                    u8"<Sin> the thief guildmaster"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 197;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 292;
            SET_LEVEL(55);
            cdata_portrait(rc) = 6;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 65;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(
                u8"盗賊ギルドマスター『シン』",
                u8"<Sin> the thief guildmaster");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 197;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 294)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この先は盗賊ギルドの管轄だ」",
                    u8"「止まれ…身分を照会させてもらう」");
                return 1;
            }
            else
            {
                txt(u8"\"I am an officer of the Thief Guild's jurisdiction. "
                    u8"Beware the clumsy-fingered.\"",
                    u8"\"Stop… Let me make sure you are on my lists.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"盗賊ギルドの番人『アビス』",
                    u8"<Abyss> the thief watchman"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 294;
            SET_LEVEL(38);
            cdata_portrait(rc) = 5;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 65;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"盗賊ギルドの番人『アビス』", u8"<Abyss> the thief watchman");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"thief";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 196;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 291)
    {
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"戦士ギルドマスター『フレイ』",
                    u8"<Fray> the fighter guildmaster"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 80;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 291;
            SET_LEVEL(55);
            cdata_portrait(rc) = 17;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(
                u8"戦士ギルドマスター『フレイ』",
                u8"<Fray> the fighter guildmaster");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 80;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 297)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「この先は戦士ギルドの管轄だ」",
                    u8"「止まれ…身分を照会させてもらう」");
                return 1;
            }
            else
            {
                txt(u8"\"I am an officer of the Fighter Guild's jurisdiction. "
                    u8"Beware the weak-thewed.\"",
                    u8"\"Stop… Let me make sure you are on my lists.\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 100);
            DBMODE16_DBSPEC_STR(
                2,
                lang(
                    u8"戦士ギルドの番人『ドリア』",
                    u8"<Doria> the fighter watchman"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"norland";
            dbmode = 2;
            label_2297();
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 297;
            SET_LEVEL(38);
            cdata_portrait(rc) = 5;
            cdata_ai_calm(rc) = 3;
            cdata_ai_move(rc) = 90;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(
                u8"戦士ギルドの番人『ドリア』",
                u8"<Doria> the fighter watchman");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"norland";
            dbmode = 3;
            label_2297();
            dbidn = u8"warrior";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 196;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 317)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「何故私に興味を持つ？怖くは無いのか？」 ",
                    u8"「やれやれ。ペットを持った気分だ」");
                return 1;
            }
            else
            {
                txt(u8"\"What do I have to fear? You aren't an Abyssal One.\"",
                    u8"\"Good grief, is someone trying to cop a feel?\" ");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「オマエ…私と同じ目をしているな」",
                    u8"「ついてこれるか？」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「ふっ。人のまま死ねて嬉しいよ」",
                    u8"「どうせすぐ忘れられる名だ」 ");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「オマエ弱いな。ナンバーはいくつだ？」",
                    u8"「優秀だが長く生きすぎたな」",
                    u8"「金は要らん。後から取りに来る者がいるから金はその時に渡"
                    u8"せばいい」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"銀眼の斬殺者", u8"silver eyed witch"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 279;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 317;
            SET_LEVEL(28);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 80;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 10;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 648;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"銀眼の斬殺者", u8"silver eyed witch");
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"claymore";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 279;
            cdata_image(rc) += 0;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 232;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    if (dbid == 318)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *ドスン*  ",
                    u8"リトルシスター「見てMr Bubbles、天使がいるわ」",
                    u8"リトルシスター「急いでMr "
                    u8"Bubbles、空で天使が踊っているの！」",
                    u8" *ドン*  ");
                return 1;
            }
            else
            {
                txt(u8"You feel the ground tremble with the steps of a large, "
                    u8"angry, Protector",
                    u8"Little Sister: \"Look Mr. Bubbles, the angels.\"",
                    u8"Little Sister: \"Look Mr. Bubbles, the angels are "
                    u8"dancing in the sky!\"",
                    u8"You hear the tread of something you do NOT want to "
                    u8"anger. Ever.");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"リトルシスター「殺せ！殺せ！」",
                    u8"リトルシスター「粉々に砕いちゃいなさい！」",
                    u8"リトルシスター「いけMr Bubbles、いけ！！」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「グウォォォォ！」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"リトルシスター「天使の血でお腹を満たすの」");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(2, lang(u8"『ビッグダディ』", u8"<Big daddy>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"machinegod";
            dbmode = 2;
            label_2297();
            cpicref = 408;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 318;
            SET_LEVEL(30);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 25;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"『ビッグダディ』", u8"<Big daddy>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"machinegod";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 408;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 1;
            return 0;
        }
        if (dbmode == 4)
        {
            eqrange(0) = 496;
            eqrange(1) = 4;
            eqammo(0) = 25020;
            eqammo(1) = 3;
            return 0;
        }
        return 0;
    }
    if (dbid == 319)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「Mr Bubbles、動いて…おねがい！」",
                    u8"「来ないで！触わらないで！」",
                    u8"「天使…天使に出会うまで、まだ死にたくないの…」");
                return 1;
            }
            else
            {
                txt(u8"\"Mr. Bubbles, please stand up… Please!\"",
                    u8"You hear the sound of a frightened little girl "
                    u8"somewhere",
                    u8"\"Angel, angel, until we find the right one we don't "
                    u8"dare die…\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「い、いや…！こないで！やだ…助けて…お願い…」");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「死…死にたくない…いやあぁ…ぁ」");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「天使の血でお腹を満たすの」");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『リトルシスター』", u8"<Little sister>"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"mutant";
            dbmode = 2;
            label_2297();
            cpicref = 409;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 319;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 5;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"『リトルシスター』", u8"<Little sister>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"mutant";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 409;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 322)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「正しいことを行うのが時には難しいこともあるわ」",
                    u8"「私の子供達を傷つけたらひどいわよ」");
                return 1;
            }
            else
            {
                txt(u8"\"The path of the righteous is not always easy, yes?\"",
                    u8"\"I'll not have him hurt my Little ones… I've worked "
                    u8"far too long on them to see them fail now.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「どうしてそんなことができるの？」");
                return 1;
            }
            else
            {
                txt(u8"\"How can you do this things?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あなたには心がないの？」");
                return 1;
            }
            else
            {
                txt(u8"\"Have you no heart?\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あなたには心がないの？」");
                return 1;
            }
            else
            {
                txt(u8"\"Have you no heart?\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『謎の科学者』", u8"<Strange scientist>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"roran";
            dbmode = 2;
            label_2297();
            cpicref = 412;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 322;
            SET_LEVEL(15);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"『謎の科学者』", u8"<Strange scientist>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"roran";
            dbmode = 3;
            label_2297();
            dbidn = u8"gunner";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 1;
            cdata_image(rc) = 412;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 334)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「正しいことを行うのが時には難しいこともあるわ」",
                    u8"「私の子供達を傷つけたらひどいわよ」");
                return 1;
            }
            else
            {
                txt(u8"\"The problem is about choice. It is always about the "
                    u8"choices we make.\"",
                    u8"\"While choices make the man, a pity most see only the "
                    u8"shallowest ones to choose from.\"");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「どうしてそんなことができるの？」");
                return 1;
            }
            else
            {
                txt(u8"\"How can you do this things?\"");
                return 1;
            }
        }
        if (dbmode == 102)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あなたには心がないの？」");
                return 1;
            }
            else
            {
                txt(u8"\"Have you no heart?\"");
                return 1;
            }
        }
        if (dbmode == 103)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「あなたには心がないの？」");
                return 1;
            }
            else
            {
                txt(u8"\"Have you no heart?\"");
                return 1;
            }
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 50);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"『謎のプロデューサー』", u8"<Mysterious Producer>"));
            DBMODE16_DBSPEC_STR(8, u8"/man/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"juere";
            dbmode = 2;
            label_2297();
            cpicref = 416;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 334;
            SET_LEVEL(7);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) =
                lang(u8"『謎のプロデューサー』", u8"<Mysterious Producer>");
            cdata_relationship(rc) = 0;
            cdata_original_relationship(rc) = 0;
            cdata_40(rc) = -10000;
            dbidn = u8"juere";
            dbmode = 3;
            label_2297();
            dbidn = u8"tourist";
            dbmode = 3;
            label_2298();
            cdata_sex(rc) = 0;
            cdata_image(rc) = 416;
            cdata_image(rc) += 0;
            fixlv = 6;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 323)
    {
        if (dbmode == 12)
        {
            label_1614();
            skillexp(15, cc, 250);
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 10);
            DBMODE16_DBSPEC_STR(2, lang(u8"シェイド", u8"shade"));
            DBMODE16_DBSPEC_STR(8, u8"/undead/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"ghost";
            dbmode = 2;
            label_2297();
            cpicref = 280;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 323;
            SET_LEVEL(12);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = 617;
            cdata_ai_act(rc, 2) = 613;
            cdata_ai_act_num(rc) = 3;
            cdatan(0, rc) = lang(u8"シェイド", u8"shade");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"ghost";
            dbmode = 3;
            label_2297();
            cdata_element_of_unarmed_attack(rc) = 5600400;
            cdata_image(rc) = 280;
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 324)
    {
        if (dbmode == 12)
        {
            label_1615();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 19);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(2, lang(u8"クイックリング", u8"quickling"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"quickling";
            dbmode = 2;
            label_2297();
            cpicref += 19000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 324;
            SET_LEVEL(10);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 2;
            cdata_ai_act_sub_freq(rc) = 0;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_num(rc) = 1;
            cdatan(0, rc) = lang(u8"クイックリング", u8"quickling");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"quickling";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 19000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 325)
    {
        if (dbmode == 12)
        {
            label_1615();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 3);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 15);
            DBMODE16_DBSPEC_STR(
                2, lang(u8"クイックリングの弓使い", u8"quickling archer"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"quickling";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 325;
            SET_LEVEL(17);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 50;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 2;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act(rc, 1) = -3;
            cdata_ai_act(rc, 2) = -3;
            cdata_ai_act_sub(rc, 0) = 648;
            cdata_ai_act_num(rc) = 13;
            cdatan(0, rc) =
                lang(u8"クイックリングの弓使い", u8"quickling archer");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"quickling";
            dbmode = 3;
            label_2297();
            dbidn = u8"archer";
            dbmode = 3;
            label_2298();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 328)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *リン* ");
                return 1;
            }
            else
            {
                txt(u8"*ring*");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *リン* ");
                return 1;
            }
            else
            {
                txt(u8"*ring*");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 0);
            DBMODE16_DBSPEC(6, 2);
            DBMODE16_DBSPEC_STR(2, lang(u8"シルバーベル", u8"silver bell"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"metal";
            dbmode = 2;
            label_2297();
            cpicref += 0;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 328;
            SET_LEVEL(3);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 4;
            cdata_ai_act_sub_freq(rc) = 1;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 653;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"シルバーベル", u8"silver bell");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"metal";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 0;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 329)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *リン* ");
                return 1;
            }
            else
            {
                txt(u8"*ring*");
                return 1;
            }
        }
        if (dbmode == 101)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8" *リン* ");
                return 1;
            }
            else
            {
                txt(u8"*ring*");
                return 1;
            }
        }
        if (dbmode == 12)
        {
            label_1589();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 5);
            DBMODE16_DBSPEC(6, 5);
            DBMODE16_DBSPEC_STR(2, lang(u8"ゴールドベル", u8"gold bell"));
            DBMODE16_DBSPEC_STR(8, "");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"metal";
            dbmode = 2;
            label_2297();
            cpicref += 5000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 329;
            SET_LEVEL(1);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 30;
            cdata_ai_dist(rc) = 3;
            cdata_ai_act_sub_freq(rc) = 1;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 653;
            cdata_ai_act_num(rc) = 11;
            cdata_can_talk(rc) += 1;
            cdata_can_talk(rc) += 1;
            cdatan(0, rc) = lang(u8"ゴールドベル", u8"gold bell");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"metal";
            dbmode = 3;
            label_2297();
            cdata_image(rc) += 5000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    if (dbid == 330)
    {
        if (dbmode == 12)
        {
            label_1616();
            return -1;
        }
        if (dbmode == 16)
        {
            DBMODE16_DBSPEC(3, 1);
            DBMODE16_DBSPEC(5, 17);
            DBMODE16_DBSPEC(6, 40);
            DBMODE16_DBSPEC_STR(2, lang(u8"エイリアン", u8"alien"));
            DBMODE16_DBSPEC_STR(8, u8"/dragon/");
            return 0;
        }
        if (dbmode == 2)
        {
            dbidn = u8"dinosaur";
            dbmode = 2;
            label_2297();
            cpicref = 283;
            cpicref += 17000;
            return 0;
        }
        if (dbmode == 3)
        {
            cdata_id(rc) = 330;
            SET_LEVEL(19);
            cdata_portrait(rc) = -1;
            cdata_ai_calm(rc) = 1;
            cdata_ai_move(rc) = 100;
            cdata_ai_dist(rc) = 1;
            cdata_ai_act_sub_freq(rc) = 7;
            creaturepack = 0;
            cdata_ai_act(rc, 0) = -1;
            cdata_ai_act_sub(rc, 0) = 654;
            cdata_ai_act_num(rc) = 11;
            cdatan(0, rc) = lang(u8"エイリアン", u8"alien");
            cdata_relationship(rc) = -3;
            cdata_original_relationship(rc) = -3;
            cdata_40(rc) = -10000;
            dbidn = u8"dinosaur";
            dbmode = 3;
            label_2297();
            dbidn = u8"predator";
            dbmode = 3;
            label_2298();
            cdata_element_of_unarmed_attack(rc) = 6300250;
            cdata_image(rc) = 283;
            cdata_image(rc) += 17000;
            cspecialeq = 0;
            return 0;
        }
        return 0;
    }
    return 0;
}



} // namespace elona
