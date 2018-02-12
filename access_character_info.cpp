#include "ability.hpp"
#include "character.hpp"
#include "class.hpp"
#include "elona.hpp"
#include "race.hpp"
#include "variables.hpp"



namespace elona
{


int access_character_info()
{
    const auto data = the_character_db[dbid];
    if (!data)
        return 0;

    switch (dbmode)
    {
    case 16:
        switch (dbspec)
        {
        case 2: refstr = lang(data->name_jp, data->name_en); return 0;
        case 3: return data->dbmode16_dbspec3;
        case 5: return data->dbmode16_dbspec5;
        case 6: return data->dbmode16_dbspec6;
        case 8: refstr = data->filter; return 0;
        default: assert(0);
        }
    case 2: access_race_info(2, data->race); return 0;
    case 3:
        cdata[rc].id = dbid;
        cdata[rc].level = initlv != 0 ? initlv : data->level;
        if (voidlv != 0)
        {
            cdata[rc].level = voidlv * (100 + data->level * 2) / 100;
        }
        cdata[rc].portrait = data->portrait;
        cdata[rc].ai_calm = data->ai_calm;
        cdata[rc].ai_heal = data->ai_heal;
        cdata[rc].ai_move = data->ai_move;
        cdata[rc].ai_dist = data->ai_dist;
        cdata[rc].ai_act_sub_freq = data->ai_act_sub_freq;
        cdata[rc].ai_act_num = data->ai_act_num;
        cdata[rc].act[0] = data->act_0;
        cdata[rc].act[1] = data->act_1;
        cdata[rc].act[2] = data->act_2;
        cdata[rc].act[3] = data->act_3;
        cdata[rc].act[4] = data->act_4;
        cdata[rc].act[5] = data->act_5;
        cdata[rc].act[6] = data->act_6;
        cdata[rc].act[7] = data->act_7;
        cdata[rc].act[8] = data->act_8;
        creaturepack = data->creaturepack;
        cdata[rc].can_talk = data->can_talk;
        cdatan(0, rc) = lang(data->name_jp, data->name_en);
        if (data->has_random_name)
        {
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cbitmod(977, rc, 1);
        }
        if (data->cbit_988)
        {
            cbitmod(988, rc, 1);
        }
        cdata[rc].original_relationship = cdata[rc].relationship =
            data->original_relationship;
        if (!std::empty(data->race))
        {
            access_race_info(3, data->race);
        }
        if (!std::empty(data->class_))
        {
            access_class_info(3, data->class_);
        }
        cdata[rc].element_of_unarmed_attack = data->element_of_unarmed_attack;
        for (const auto& [k, v] : data->resistances)
        {
            sdata(k, rc) = v;
        }
        if (data->sex != -1)
        {
            cdata[rc].sex = data->sex;
        }
        if (data->image != 0)
        {
            cdata[rc].image = data->image;
        }
        if (cdata[rc].sex == 0 && data->male_image != 0)
        {
            cdata[rc].image = data->male_image;
        }
        if (cdata[rc].sex == 1 && data->female_image != 0)
        {
            cdata[rc].image = data->female_image;
        }
        cdata[rc].image += data->color * 1000;
        eqammo(0) = data->eqammo_0;
        eqammo(1) = data->eqammo_1;
        eqmultiweapon = data->eqmultiweapon;
        eqrange(0) = data->eqrange_0;
        eqrange(1) = data->eqrange_1;
        eqring1 = data->eqring1;
        eqtwohand = data->eqtwohand;
        eqweapon1 = data->eqweapon1;
        if (data->fixlv == 6)
        {
            fixlv = 6;
        }
        cspecialeq = data->cspecialeq;
        cdata[rc].damage_reaction_info = data->damage_reaction_info;
        return 0;
    default: break;
    }

    if (false)
    {
    }
    else if (dbid == 0)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 343)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 1;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 1)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 140;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 353)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 443;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 70)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 144;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 69)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 15;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 73)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 41;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 74)
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
            eating_effect_eat_holy_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 69;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 206)
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
            eating_effect_eat_holy_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 163;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 38)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 142;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 40)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 7;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 333)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 415;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 76)
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
            eating_effect_eat_guard();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 363;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 77)
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
            eating_effect_eat_guard();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 25;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 204)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 74;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 2)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"elea");
            cpicref = 297;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 63;
            return 0;
        }
        return 0;
    }
    else if (dbid == 37)
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
            eating_effect_eat_at();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 347;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 23)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 331;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 64;
            return 0;
        }
        return 0;
    }
    else if (dbid == 26)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 332;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 27)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 333;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 28)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 334;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 73;
            return 0;
        }
        return 0;
    }
    else if (dbid == 29)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 337;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 140)
    {
        if (dbmode == 12)
        {
            eating_effect_fire();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref = 338;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 30)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 8;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 31)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 109;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 351)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 478;
            cpicref += 0;
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
    else if (dbid == 352)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 479;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 32)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 344;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 33)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"elea");
            cpicref = 345;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 206;
            return 0;
        }
        return 0;
    }
    else if (dbid == 34)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"elea");
            cpicref = 346;
            cpicref += 0;
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
    else if (dbid == 139)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 99;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 146)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 99;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 142)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 340;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 141)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity2();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref = 339;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 358;
            return 0;
        }
        return 0;
    }
    else if (dbid == 143)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 341;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 359;
            return 0;
        }
        return 0;
    }
    else if (dbid == 144)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 343;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 356;
            return 0;
        }
        return 0;
    }
    else if (dbid == 145)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref = 342;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqring1 = 357;
            return 0;
        }
        return 0;
    }
    else if (dbid == 306)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 393;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 331)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 413;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 336)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 413;
            cpicref += 0;
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
    else if (dbid == 338)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 432;
            cpicref += 0;
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
    else if (dbid == 339)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 433;
            cpicref += 0;
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
    else if (dbid == 342)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 447;
            cpicref += 0;
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
    else if (dbid == 340)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"god");
            cpicref = 435;
            cpicref += 0;
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
    else if (dbid == 3)
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
            eating_effect_eat_cute_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 4)
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
            eating_effect_eat_cute_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 169)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref = 257;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 194)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref = 257;
            cpicref += 2000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 286)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref = 400;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 285)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"slime");
            cpicref = 400;
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 287)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"drake");
            cpicref = 401;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 327)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref = 282;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 5)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"rabbit");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 6)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"snail");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 7)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 37;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 8)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 139;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 9)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 102;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 269)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 179;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 320)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 410;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 273)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 187;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 326)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 148;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 270)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 181;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 349)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 442;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 348)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 473;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 347)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 285;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 271)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 183;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 335)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 418;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 337)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 419;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 272)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 185;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 274)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 189;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 289)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"eulderna");
            cpicref = 195;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 293)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 76;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 295)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 78;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 35)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 104;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 36)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 106;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 174)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 112;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 10)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"sheep");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 11)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"frog");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 12)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 31;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 13)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"kobolt");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 236)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 238)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 241)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref += 2000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 240)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref += 8000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 237)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 244)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 385;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 245)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"rock");
            cpicref = 386;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 321)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 411;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 242)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yeek");
            cpicref = 381;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 239)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 379;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 14)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"centipede");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 15)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"mushroom");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 283)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mushroom");
            cpicref = 399;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 284)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"mushroom");
            cpicref = 399;
            cpicref += 8000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 16)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 136;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 39)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 134;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 171)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 128;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 172)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 127;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 173)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 146;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 71)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 120;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 72)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 119;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 79)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 117;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 80)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 116;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 17)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"orc");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 281)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"lizardman");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 282)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"minotaur");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 296)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"minotaur");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 298)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"minotaur");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 299)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"minotaur");
            cpicref += 8000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 300)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"minotaur");
            cpicref += 10000;
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
    else if (dbid == 251)
    {
        if (dbmode == 12)
        {
            eating_effect_regeneration();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"troll");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 18)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"elea");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 24)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"elea");
            cpicref = 47;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 309)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"asura");
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 2;
            return 0;
        }
        return 0;
    }
    else if (dbid == 310)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"asura");
            cpicref += 2000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 266;
            return 0;
        }
        return 0;
    }
    else if (dbid == 311)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"asura");
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqmultiweapon = 224;
            return 0;
        }
        return 0;
    }
    else if (dbid == 41)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 13;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 75)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 21;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 19)
    {
        if (dbmode == 12)
        {
            eating_effect_magic();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 22)
    {
        if (dbmode == 12)
        {
            eating_effect_strength();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"beetle");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 20)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"orc");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 25)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"orc");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 21)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 42)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"bat");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 43)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"bat");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 44)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"bat");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 45)
    {
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ent");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 46)
    {
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 51, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ent");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 47)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 48)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 49)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 307)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref = 404;
            cpicref += 0;
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
    else if (dbid == 308)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"lich");
            cpicref = 404;
            cpicref += 4000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 735;
            return 0;
        }
        return 0;
    }
    else if (dbid == 50)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 6000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 51)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 52)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 12000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 53)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 54)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 55)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 10000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 56)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 9000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 57)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 2000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 58)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 11000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 59)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 15000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 60)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 61)
    {
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"rabbit");
            cpicref = 204;
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 62)
    {
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"rabbit");
            cpicref = 204;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 63)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity3();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 64)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity3();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref += 2000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 312)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"ent");
            cpicref = 406;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 313)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"ent");
            cpicref = 406;
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 65)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 52, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"spirit");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 66)
    {
        if (dbmode == 12)
        {
            eating_effect_chaos();
            if (rnd(5) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"spirit");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 67)
    {
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 315)
    {
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref += 8000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 316)
    {
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref = 407;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 314)
    {
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref = 407;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 68)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"wyvern");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 78)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"eulderna");
            cpicref = 209;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 81)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"wasp");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 82)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"wasp");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 83)
    {
        if (dbmode == 12)
        {
            eating_effect_constitution();
            skillexp(11, cc, 500);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"giant");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 84)
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
            eating_effect_constitution();
            skillexp(11, cc, 800);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"giant");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 85)
    {
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"imp");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 86)
    {
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"imp");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 87)
    {
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"imp");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 88)
    {
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"hand");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 89)
    {
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"hand");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 90)
    {
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"hand");
            cpicref += 16000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 91)
    {
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 250);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref = 214;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 92)
    {
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 400);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref = 214;
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 93)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 215;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 94)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 215;
            cpicref += 10000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 95)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"snake");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 96)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"snake");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 97)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"drake");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 98)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"drake");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 99)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref = 219;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 100)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref = 219;
            cpicref += 10000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 101)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref = 219;
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 257)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref = 219;
            cpicref += 8000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 254)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"zombie");
            cpicref = 395;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 102)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"goblin");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 103)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"goblin");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 104)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"goblin");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 105)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"goblin");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 106)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref = 221;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 107)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref = 221;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 108)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"bear");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 109)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"bear");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 344)
    {
        if (dbmode == 12)
        {
            eating_effect_strength2();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"bear");
            cpicref = 439;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 110)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"armor");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 111)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"armor");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 112)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"armor");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 113)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"armor");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 114)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"medusa");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 115)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"medusa");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 116)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"medusa");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 117)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_lovely_one();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"cupid");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 118)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"phantom");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 248)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dinosaur");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 119)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"harpy");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 120)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 19000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 121)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 122)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 123)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 124)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 125)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"dragon");
            cpicref += 18000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 126)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"cerberus");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 255)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"centipede");
            cpicref = 396;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 256)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"centipede");
            cpicref = 396;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 127)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"spider");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 128)
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
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"spider");
            cpicref += 19000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 129)
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
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"spider");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 130)
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
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"spider");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 131)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"spider");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 132)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 133)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 134)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 15000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 135)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 136)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 137)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 9000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 138)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"golem");
            cpicref += 2000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 147)
    {
        if (dbmode == 12)
        {
            eating_effect_calm();
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"crab");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 148)
    {
        if (dbmode == 12)
        {
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"centipede");
            cpicref = 239;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 149)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"goblin");
            cpicref = 240;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 150)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"skeleton");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 151)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"skeleton");
            cpicref += 3000;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 152)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"eulderna");
            cpicref = 243;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 153)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 154)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref = 245;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 155)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref = 246;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 156)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref = 247;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 157)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref = 248;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 158)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"piece");
            cpicref = 249;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 159)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 159;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 160)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 57;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 161)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 100;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 302)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 150;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 303)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 31;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 304)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 158;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 305)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 157;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 162)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 250;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 234)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 250;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 231)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 370;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 232)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 373;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 233)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 377;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 235)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 377;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 163)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 251;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    }
    else if (dbid == 164)
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
            eating_effect_eat_cat();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 246)
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
            eating_effect_eat_cat();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 387;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 332)
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
            eating_effect_eat_cat();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 387;
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 229)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 368;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 230)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"catgod");
            cpicref = 369;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 228)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 367;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 165)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"dog");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 225)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"dog");
            cpicref = 364;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 226)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 365;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 227)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 366;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 166)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 4;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 167)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"rat");
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 168)
    {
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"shell");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 170)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 258;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    }
    else if (dbid == 175)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"catgod");
            cpicref = 348;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 176)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata[0].sex) + u8"ちゃんー」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん？」",
                    u8"「" + _onii(cdata[0].sex) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん♪」");
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
                txt(u8"「おかえり、" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + _onii(cdata[0].sex)
                        + u8"ちゃん♪」",
                    u8"「待ってたよ、" + _onii(cdata[0].sex) + u8"ちゃん」");
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 105;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 249)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata[0].sex) + u8"ちゃんー」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん？」",
                    u8"「" + _onii(cdata[0].sex) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん♪」");
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
                txt(u8"「おかえり、" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「おかえりなさーい、" + _onii(cdata[0].sex)
                        + u8"ちゃん♪」",
                    u8"「待ってたよ、" + _onii(cdata[0].sex) + u8"ちゃん」");
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 105;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 210)
    {
        if (dbmode == 100)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「" + _onii(cdata[0].sex) + u8"ちゃんー」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃ〜ん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃんっ」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん？」",
                    u8"「" + _onii(cdata[0].sex) + u8"〜ちゃん」",
                    u8"「" + _onii(cdata[0].sex) + u8"ちゃん♪」");
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
                txt(u8"「おかえりにゃ、" + _onii(cdata[0].sex) + u8"ちゃん！」",
                    u8"「おかえりなさいにゃー、" + _onii(cdata[0].sex)
                        + u8"ちゃん♪」",
                    u8"「待ってたにゃ、" + _onii(cdata[0].sex) + u8"ちゃん」");
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"catsister");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 211)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 355;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 177)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"machinegod");
            cpicref = 349;
            cpicref += 0;
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
    else if (dbid == 178)
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
            eating_effect_insanity2();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"undeadgod");
            cpicref = 339;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 179)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 350;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 208)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"dwarf");
            cpicref = 352;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 209)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"dwarf");
            cpicref = 353;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 180)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"cat");
            cpicref = 259;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 181)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"hound");
            cpicref = 260;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 182)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 208;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 183)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 71;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 184)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 73;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 185)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 122;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 350)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 477;
            cpicref += 1000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 186)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 187)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 188)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 345)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"bike");
            cpicref = 470;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 346)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"bike");
            cpicref = 471;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 341)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref = 434;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 258)
    {
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machine");
            cpicref = 198;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 189)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref = 271;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 190)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"eye");
            cpicref = 271;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 191)
    {
        if (dbmode == 12)
        {
            eating_effect_ether();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"wisp");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 192)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"crab");
            cpicref = 273;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 193)
    {
        if (dbmode == 12)
        {
            eating_effect_ether();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"crab");
            cpicref = 273;
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 195)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"chicken");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 196)
    {
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 275;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 201)
    {
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 275;
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 197)
    {
        if (dbmode == 12)
        {
            if (rnd(8) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 275;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 198)
    {
        if (dbmode == 12)
        {
            if (rnd(6) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"mandrake");
            cpicref = 275;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 199)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"stalker");
            cpicref = 276;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 200)
    {
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"stalker");
            cpicref = 276;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 202)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"giant");
            cpicref = 351;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 203)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 23;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 205)
    {
        if (dbmode == 100)
        {
            txtmore();
            txtef(9);
            if (jp)
            {
                txt(u8"「" + _syujin(cdata[0].sex) + u8"〜」",
                    _syujin(cdata[0].sex) + u8"〜",
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
                    u8"「" + _syujin(cdata[0].sex) + u8"ー！」");
                return 1;
            }
        }
        if (dbmode == 104)
        {
            if (jp)
            {
                txtmore();
                txtef(9);
                txt(u8"「おかえりなさいませ、" + _syujin(cdata[0].sex)
                        + u8"〜」",
                    u8"「おかえりなさいまし〜」");
                return 1;
            }
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 104;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 207)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"giant");
            cpicref = 351;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 212)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 117;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 56;
            return 0;
        }
        return 0;
    }
    else if (dbid == 213)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 356;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 221)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 358;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 222)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 359;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 223)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 361;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 224)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 362;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 243)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 383;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 247)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 388;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 252)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 392;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 253)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 394;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 259)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 199;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 301)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 403;
            cpicref += 0;
            return 0;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    }
    else if (dbid == 214)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 166;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 215)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 166;
            cpicref += 3000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 217)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 166;
            cpicref += 4000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 216)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"yith");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 218)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"yith");
            cpicref = 277;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 219)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"orc");
            cpicref = 278;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 220)
    {
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"yith");
            cpicref = 430;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 250)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"fairy");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 260)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 211;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 261)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 217;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 262)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 218;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 263)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 236;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 264)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 269;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 265)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 267;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 266)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"servant");
            cpicref = 242;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 267)
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
            eating_effect_eat_horse();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"horse");
            cpicref += 17000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 276)
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
            eating_effect_eat_horse();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"horse");
            cpicref += 6000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 275)
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
            eating_effect_eat_horse();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"horse");
            cpicref += 15000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 268)
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
            eating_effect_eat_horse();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"horse");
            cpicref += 16000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 277)
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
            eating_effect_eat_horse();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"horse");
            cpicref += 10000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 278)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"mutant");
            cpicref = 191;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 279)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"yerles");
            cpicref = 263;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 280)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 192;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 288)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 193;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 290)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 292)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 197;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 294)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 291)
    {
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 80;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 297)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"norland");
            cpicref = 196;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 317)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 279;
            cpicref += 0;
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
    else if (dbid == 318)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"machinegod");
            cpicref = 408;
            cpicref += 0;
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
    else if (dbid == 319)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"mutant");
            cpicref = 409;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 322)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"roran");
            cpicref = 412;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 334)
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
        if (dbmode == 2)
        {
            access_race_info(2, u8"juere");
            cpicref = 416;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 323)
    {
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 250);
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"ghost");
            cpicref = 280;
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 324)
    {
        if (dbmode == 12)
        {
            eating_effect_quick();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"quickling");
            cpicref += 19000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 325)
    {
        if (dbmode == 12)
        {
            eating_effect_quick();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"quickling");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 328)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"metal");
            cpicref += 0;
            return 0;
        }
        return 0;
    }
    else if (dbid == 329)
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
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"metal");
            cpicref += 5000;
            return 0;
        }
        return 0;
    }
    else if (dbid == 330)
    {
        if (dbmode == 12)
        {
            eating_effect_pregnant();
            return -1;
        }
        if (dbmode == 2)
        {
            access_race_info(2, u8"dinosaur");
            cpicref = 283;
            cpicref += 17000;
            return 0;
        }
        return 0;
    }

    return 0;
}



} // namespace elona
