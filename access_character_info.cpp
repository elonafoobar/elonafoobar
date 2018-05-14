#include "ability.hpp"
#include "character.hpp"
#include "class.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "i18n.hpp"
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
        case 2:
            refstr = i18n::_(u8"character", std::to_string(dbid), u8"name");
            return 0;
        case 3: return data->item_type;
        case 8: refstr = data->filter; return 0;
        default: assert(0);
        }
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
        cdata[rc].normal_actions = data->normal_actions;
        cdata[rc].special_actions = data->special_actions;
        creaturepack = data->creaturepack;
        cdata[rc].can_talk = data->can_talk;
        cdatan(0, rc) = i18n::_(u8"character", std::to_string(dbid), u8"name");
        if (data->has_random_name)
        {
            cdatan(0, rc) = lang(
                cdatan(0, rc) + u8"の" + randomname(),
                randomname() + u8" the " + cdatan(0, rc));
            cdata[rc].has_own_name() = true;
        }
        cdata[rc].original_relationship = cdata[rc].relationship =
            data->original_relationship;
        if (!data->race.empty())
        {
            access_race_info(3, data->race);
        }
        if (!data->class_.empty())
        {
            access_class_info(3, data->class_);
        }
        cdata[rc].element_of_unarmed_attack = data->element_of_unarmed_attack;
        for (const auto& pair : data->resistances)
        {
            sdata(pair.first, rc) = pair.second;
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


    switch (dbmode)
    {
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
        if (false)
        {
        }
        else if (dbid == 176)
        {
            if (dbmode == 100)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんー」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃ〜ん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんっ」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん？」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"〜ちゃん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」");
                    return 1;
                }
            }
            if (dbmode == 104)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「おかえり、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「おかえりなさーい、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」",
                        u8"「待ってたよ、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん」");
                    return 1;
                }
            }
        }
        else if (dbid == 249)
        {
            if (dbmode == 100)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんー」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃ〜ん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんっ」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん？」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"〜ちゃん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」");
                    return 1;
                }
            }
            if (dbmode == 104)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「おかえり、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「おかえりなさーい、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」",
                        u8"「待ってたよ、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん」");
                    return 1;
                }
            }
        }
        else if (dbid == 210)
        {
            if (dbmode == 100)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんー」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃ〜ん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃんっ」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん？」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"〜ちゃん」",
                        u8"「"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」");
                    return 1;
                }
            }
            if (dbmode == 104)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「おかえりにゃ、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん！」",
                        u8"「おかえりなさいにゃー、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん♪」",
                        u8"「待ってたにゃ、"
                            + i18n::_(u8"ui", u8"onii", u8"_"s + cdata[0].sex)
                            + u8"ちゃん」");
                    return 1;
                }
            }
        }
        else if (dbid == 205)
        {
            if (dbmode == 100)
            {
                txtef(9);
                if (jp)
                {
                    txt(u8"「"
                            + i18n::_(u8"ui", u8"syujin", u8"_"s + cdata[0].sex)
                            + u8"〜」",
                        i18n::_(u8"ui", u8"syujin", u8"_"s + cdata[0].sex)
                            + u8"〜",
                        u8"「用事はありませんか♪」",
                        u8"メイドの熱い視線を感じる…");
                    return 1;
                }
            }
            if (dbmode == 102)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「ダメぇ！」",
                        u8"「"
                            + i18n::_(u8"ui", u8"syujin", u8"_"s + cdata[0].sex)
                            + u8"ー！」");
                    return 1;
                }
            }
            if (dbmode == 104)
            {
                if (jp)
                {
                    txtef(9);
                    txt(u8"「おかえりなさいませ、"
                            + i18n::_(u8"ui", u8"syujin", u8"_"s + cdata[0].sex)
                            + u8"〜」",
                        u8"「おかえりなさいまし〜」");
                    return 1;
                }
            }
        }
        {
            const auto text = i18n::_(
                u8"character", std::to_string(dbid), u8"text_"s + dbmode);
            if (!text.empty())
            {
                txtef(9);
                txt(text);
            }
        }
        break;
    default: break;
    }

    switch (dbid)
    {
    case 74:
        if (dbmode == 12)
        {
            eating_effect_eat_holy_one();
            return -1;
        }
        return 0;
    case 206:
        if (dbmode == 12)
        {
            eating_effect_eat_holy_one();
            return -1;
        }
        return 0;
    case 76:
        if (dbmode == 12)
        {
            eating_effect_eat_guard();
            return -1;
        }
        return 0;
    case 77:
        if (dbmode == 12)
        {
            eating_effect_eat_guard();
            return -1;
        }
        return 0;
    case 2:
        if (dbmode == 4)
        {
            eqweapon1 = 63;
            return 0;
        }
        return 0;
    case 37:
        if (dbmode == 12)
        {
            eating_effect_eat_at();
            return -1;
        }
        return 0;
    case 23:
        if (dbmode == 4)
        {
            eqweapon1 = 64;
            return 0;
        }
        return 0;
    case 28:
        if (dbmode == 4)
        {
            eqweapon1 = 73;
            return 0;
        }
        return 0;
    case 140:
        if (dbmode == 12)
        {
            eating_effect_fire();
            return -1;
        }
        return 0;
    case 351:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 232;
            return 0;
        }
        return 0;
    case 33:
        if (dbmode == 4)
        {
            eqweapon1 = 206;
            return 0;
        }
        return 0;
    case 34:
        if (dbmode == 4)
        {
            eqweapon1 = 1;
            eqrange = 207;
            eqammo(0) = 25001;
            eqammo(1) = 3;
            return 0;
        }
        return 0;
    case 141:
        if (dbmode == 12)
        {
            eating_effect_insanity2();
            return -1;
        }
        if (dbmode == 4)
        {
            eqweapon1 = 358;
            return 0;
        }
        return 0;
    case 143:
        if (dbmode == 4)
        {
            eqweapon1 = 359;
            return 0;
        }
        return 0;
    case 144:
        if (dbmode == 4)
        {
            eqweapon1 = 356;
            return 0;
        }
        return 0;
    case 145:
        if (dbmode == 4)
        {
            eqring1 = 357;
            return 0;
        }
        return 0;
    case 336:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    case 338:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    case 339:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    case 342:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    case 340:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            eqweapon1 = 739;
            return 0;
        }
        return 0;
    case 3:
        if (dbmode == 12)
        {
            eating_effect_eat_cute_one();
            return -1;
        }
        return 0;
    case 4:
        if (dbmode == 12)
        {
            eating_effect_eat_cute_one();
            return -1;
        }
        return 0;
    case 13:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        return 0;
    case 14:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        return 0;
    case 283:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            return -1;
        }
        return 0;
    case 299:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 300:
        if (dbmode == 4)
        {
            eqweapon1 = 695;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 251:
        if (dbmode == 12)
        {
            eating_effect_regeneration();
            return -1;
        }
        return 0;
    case 309:
        if (dbmode == 4)
        {
            eqmultiweapon = 2;
            return 0;
        }
        return 0;
    case 310:
        if (dbmode == 4)
        {
            eqmultiweapon = 266;
            return 0;
        }
        return 0;
    case 311:
        if (dbmode == 4)
        {
            eqmultiweapon = 224;
            return 0;
        }
        return 0;
    case 19:
        if (dbmode == 12)
        {
            eating_effect_magic();
            return -1;
        }
        return 0;
    case 22:
        if (dbmode == 12)
        {
            eating_effect_strength();
            return -1;
        }
        return 0;
    case 21:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 45:
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        return 0;
    case 46:
        if (dbmode == 12)
        {
            if (rnd(3) == 0)
            {
                resistmod(cc, 51, 50);
            }
            return -1;
        }
        return 0;
    case 47:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 48:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 49:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 307:
        if (dbmode == 4)
        {
            eqweapon1 = 735;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 308:
        if (dbmode == 4)
        {
            eqweapon1 = 735;
            return 0;
        }
        return 0;
    case 50:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 61:
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        return 0;
    case 62:
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        return 0;
    case 63:
        if (dbmode == 12)
        {
            eating_effect_insanity3();
            return -1;
        }
        return 0;
    case 64:
        if (dbmode == 12)
        {
            eating_effect_insanity3();
            return -1;
        }
        return 0;
    case 65:
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 52, 50);
            }
            return -1;
        }
        return 0;
    case 66:
        if (dbmode == 12)
        {
            eating_effect_chaos();
            if (rnd(5) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        return 0;
    case 67:
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        return 0;
    case 315:
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 59, 50);
            }
            return -1;
        }
        return 0;
    case 316:
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        return 0;
    case 314:
        if (dbmode == 12)
        {
            eating_effect_lightning();
            if (rnd(3) == 0)
            {
                resistmod(cc, 58, 50);
            }
            return -1;
        }
        return 0;
    case 83:
        if (dbmode == 12)
        {
            eating_effect_constitution();
            skillexp(11, cc, 500);
            return -1;
        }
        return 0;
    case 84:
        if (dbmode == 12)
        {
            eating_effect_constitution();
            skillexp(11, cc, 800);
            return -1;
        }
        return 0;
    case 85:
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        return 0;
    case 86:
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        return 0;
    case 87:
        if (dbmode == 12)
        {
            eating_effect_magic2();
            skillexp(16, cc, 500);
            return -1;
        }
        return 0;
    case 88:
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        return 0;
    case 89:
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        return 0;
    case 90:
        if (dbmode == 12)
        {
            eating_effect_strength2();
            skillexp(10, cc, 400);
            return -1;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 91:
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 250);
            return -1;
        }
        return 0;
    case 92:
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 400);
            return -1;
        }
        return 0;
    case 95:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 96:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 99:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 100:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 101:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 257:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 254:
        if (dbmode == 12)
        {
            eating_effect_eat_rotten_one();
            return -1;
        }
        return 0;
    case 344:
        if (dbmode == 12)
        {
            eating_effect_strength2();
            return -1;
        }
        return 0;
    case 110:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 111:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 112:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 113:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 117:
        if (dbmode == 12)
        {
            eating_effect_eat_lovely_one();
            return -1;
        }
        return 0;
    case 255:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 256:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 128:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 129:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 130:
        if (dbmode == 12)
        {
            eating_effect_eat_poisonous_one();
            if (rnd(6) == 0)
            {
                resistmod(cc, 55, 50);
            }
            return -1;
        }
        return 0;
    case 132:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 133:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 134:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 135:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 136:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 137:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 138:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 147:
        if (dbmode == 12)
        {
            eating_effect_calm();
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        return 0;
    case 148:
        if (dbmode == 12)
        {
            if (rnd(5) == 0)
            {
                resistmod(cc, 50, 50);
            }
            return -1;
        }
        return 0;
    case 151:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 153:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 154:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 155:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 156:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 157:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 158:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 303:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 163:
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    case 164:
        if (dbmode == 12)
        {
            eating_effect_eat_cat();
            return -1;
        }
        return 0;
    case 246:
        if (dbmode == 12)
        {
            eating_effect_eat_cat();
            return -1;
        }
        return 0;
    case 332:
        if (dbmode == 12)
        {
            eating_effect_eat_cat();
            return -1;
        }
        return 0;
    case 168:
        if (dbmode == 12)
        {
            eating_effect_calm();
            return -1;
        }
        return 0;
    case 170:
        if (dbmode == 4)
        {
            eqrange = 210;
            return 0;
        }
        return 0;
    case 177:
        if (dbmode == 4)
        {
            eqweapon1 = 1;
            eqrange = 514;
            eqammo(0) = 25030;
            eqammo(1) = 3;
            return 0;
        }
        return 0;
    case 178:
        if (dbmode == 12)
        {
            eating_effect_insanity2();
            return -1;
        }
        return 0;
    case 186:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 187:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 188:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 345:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 346:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 341:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 258:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 189:
        if (dbmode == 12)
        {
            eating_effect_insanity();
            return -1;
        }
        return 0;
    case 190:
        if (dbmode == 12)
        {
            eating_effect_insanity();
            return -1;
        }
        return 0;
    case 191:
        if (dbmode == 12)
        {
            eating_effect_ether();
            return -1;
        }
        return 0;
    case 193:
        if (dbmode == 12)
        {
            eating_effect_ether();
            return -1;
        }
        return 0;
    case 196:
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        return 0;
    case 201:
        if (dbmode == 12)
        {
            if (rnd(10) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        return 0;
    case 197:
        if (dbmode == 12)
        {
            if (rnd(8) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        return 0;
    case 198:
        if (dbmode == 12)
        {
            if (rnd(6) == 0)
            {
                resistmod(cc, 54, 50);
            }
            return -1;
        }
        return 0;
    case 199:
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        return 0;
    case 200:
        if (dbmode == 12)
        {
            if (rnd(4) == 0)
            {
                resistmod(cc, 53, 50);
            }
            return -1;
        }
        return 0;
    case 212:
        if (dbmode == 4)
        {
            eqweapon1 = 56;
            return 0;
        }
        return 0;
    case 301:
        if (dbmode == 4)
        {
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 216:
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        return 0;
    case 218:
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        return 0;
    case 220:
        if (dbmode == 12)
        {
            eating_effect_insanity4();
            return -1;
        }
        return 0;
    case 267:
        if (dbmode == 12)
        {
            eating_effect_eat_horse();
            return -1;
        }
        return 0;
    case 276:
        if (dbmode == 12)
        {
            eating_effect_eat_horse();
            return -1;
        }
        return 0;
    case 275:
        if (dbmode == 12)
        {
            eating_effect_eat_horse();
            return -1;
        }
        return 0;
    case 268:
        if (dbmode == 12)
        {
            eating_effect_eat_horse();
            return -1;
        }
        return 0;
    case 277:
        if (dbmode == 12)
        {
            eating_effect_eat_horse();
            return -1;
        }
        return 0;
    case 317:
        if (dbmode == 4)
        {
            eqweapon1 = 232;
            eqtwohand = 1;
            return 0;
        }
        return 0;
    case 318:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
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
    case 323:
        if (dbmode == 12)
        {
            eating_effect_will();
            skillexp(15, cc, 250);
            return -1;
        }
        return 0;
    case 324:
        if (dbmode == 12)
        {
            eating_effect_quick();
            return -1;
        }
        return 0;
    case 325:
        if (dbmode == 12)
        {
            eating_effect_quick();
            return -1;
        }
        return 0;
    case 328:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 329:
        if (dbmode == 12)
        {
            eating_effect_eat_iron();
            return -1;
        }
        return 0;
    case 330:
        if (dbmode == 12)
        {
            eating_effect_pregnant();
            return -1;
        }
        return 0;
    default: return 0;
    }
}



} // namespace elona
