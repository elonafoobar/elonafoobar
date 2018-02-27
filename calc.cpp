#include "calc.hpp"
#include "ability.hpp"
#include "buff.hpp"
#include "character.hpp"
#include "debug.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "map.hpp"
#include "variables.hpp"



namespace
{


std::tuple<int, int> calc_buff_effect(int id, int power)
{
    switch (id)
    {
    case 1: return {25 + power / 15, 0};
    case 2: return {0, 0};
    case 3: return {0, 0};
    case 4: return {0, 0};
    case 5: return {50 + std::sqrt(power / 5), 0};
    case 6: return {std::min(20 + power / 20, 50), 0};
    case 7: return {5 + power / 30, 0};
    case 8: return {0, 0};
    case 9: return {0, 0};
    case 10: return {50 + power / 3 * 2, 0};
    case 11: return {0, 0};
    case 12: return {6 + power / 40, 3 + power / 100};
    case 13: return {20, 0};
    case 14: return {155 + power / 5, 0};
    case 15: return {0, 0};
    case 16: return {0, 0};
    case 17: return {120, 0};
    case 18: return {std::clamp(25 + power / 17, 25, 80), 0};
    case 19: return {power, 0};
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28: return {power, 0};
    default: assert(0);
    }
}



std::vector<int> calc_effective_range(int id)
{
    switch (id)
    {
    case 788: return {60, 90, 100, 100, 80, 60, 20, 20, 20, 20};
    case 758: return {100, 90, 70, 50, 20, 20, 20, 20, 20, 20};
    case 725: return {60, 100, 70, 20, 20, 20, 20, 20, 20, 20};
    case 718: return {50, 100, 50, 20, 20, 20, 20, 20, 20, 20};
    case 716: return {60, 100, 70, 20, 20, 20, 20, 20, 20, 20};
    case 714: return {80, 100, 90, 80, 60, 20, 20, 20, 20, 20};
    case 713: return {60, 100, 70, 20, 20, 20, 20, 20, 20, 20};
    case 674: return {100, 40, 20, 20, 20, 20, 20, 20, 20, 20};
    case 673: return {50, 90, 100, 90, 80, 80, 70, 60, 50, 20};
    case 633: return {50, 100, 50, 20, 20, 20, 20, 20, 20, 20};
    case 514: return {100, 100, 100, 100, 100, 100, 100, 50, 20, 20};
    case 512: return {100, 100, 100, 100, 100, 100, 100, 20, 20, 20};
    case 496: return {100, 60, 20, 20, 20, 20, 20, 20, 20, 20};
    case 482: return {80, 100, 90, 80, 70, 60, 50, 20, 20, 20};
    case 231: return {80, 100, 100, 90, 80, 70, 20, 20, 20, 20};
    case 230: return {70, 100, 100, 80, 60, 20, 20, 20, 20, 20};
    case 210: return {60, 100, 70, 20, 20, 20, 20, 20, 20, 20};
    case 207: return {50, 90, 100, 90, 80, 80, 70, 60, 50, 20};
    case 60: return {100, 90, 70, 50, 20, 20, 20, 20, 20, 20};
    case 58: return {50, 90, 100, 90, 80, 80, 70, 60, 50, 20};
    default: return {100, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    }
}


} // namespace



namespace elona
{


int rangedist = 0;



int calc_buff_duration(int id, int power)
{
    auto func = the_buff_db[id].duration;
    return cat::global.call<int>(func, power);
}


std::string get_buff_description(int id, int power)
{
    const auto [effect1, effect2] = calc_buff_effect(id, power);

    switch (id)
    {
    case 1:
        return lang(
            u8"PVを"s + effect1 + u8"上昇/耐恐怖"s,
            u8"Increases PV by "s + effect1 + u8"/RES+ fear"s);
    case 2: return lang(u8"魔法の使用を禁止"s, u8"Inhibits casting"s);
    case 3: return lang(u8"自然回復強化"s, u8"Enhances regeneration"s);
    case 4:
        return lang(u8"炎冷気電撃耐性の獲得"s, u8"RES+ fire,cold,lightning"s);
    case 5:
        return lang(
            ""s + effect1 + u8"の加速"s, u8"Increases speed by "s + effect1);
    case 6:
        return lang(
            ""s + effect1 + u8"の鈍足"s, u8"Decreases speed by "s + effect1);
    case 7:
        return lang(
            u8"筋力・器用を"s + effect1 + u8"上昇/耐恐怖/耐混乱"s,
            u8"Increases STR,DEX by "s + effect1 + u8"/RES+ fear,confusion"s);
    case 8: return lang(u8"DVとPVを半減"s, u8"Halves DV and PV"s);
    case 9:
        return lang(u8"炎冷気電撃耐性の減少"s, u8"RES- fire,cold,lightning"s);
    case 10:
        return lang(
            u8"ﾊﾟﾜｰ"s + effect1 + u8"の呪い(hex)への抵抗"s,
            u8"grants hex protection(power:"s + effect1 + u8")"s);
    case 11: return lang(u8"神経幻影耐性の減少"s, u8"RES- mind,nerve"s);
    case 12:
        return lang(
            u8"習得・魔力を"s + effect1 + u8"上昇/読書を"s + effect2
                + u8"上昇"s,
            u8"Increases LER,MAG by "s + effect1 + u8", literacy skill by "s
                + effect2);
    case 13:
        return lang(
            ""s + effect1 + u8"の鈍足/PVを20%減少"s,
            u8"Decreases speed by "s + effect1 + u8", PV by 20%"s);
    case 14:
        return lang(
            ""s + effect1 + u8"の加速"s, u8"Increases speed by "s + effect1);
    case 15: return lang(u8"変装"s, u8"Grants new identify"s);
    case 16:
        return lang(
            u8"呪いが完了したときに確実なる死"s,
            u8"Guaranteed death when the hex ends"s);
    case 17:
        return lang(
            ""s + effect1 + u8"の加速と能力のアップ"s,
            u8"Increases speed by "s + effect1
                + u8"/Boosts physical attributes"s);
    case 18:
        return lang(
            u8"致命傷を負ったとき"s + effect1 + u8"%の確率でダメージ分回復。"s,
            ""s + effect1
                + u8"% chances taking a lethal damage heals you instead"s);
    case 19:
        return lang(
            ""s + effect1 + u8"の幸運の上昇"s,
            u8"Increase luck by "s + effect1 + u8"."s);
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
        return lang(
            i18n::_(u8"ability", std::to_string(id - 20 + 10), u8"name")
                + u8"の成長率を"s + effect1 + u8"%上昇"s,
            u8"Increases the growth rate "s
                + i18n::_(u8"ability", std::to_string(id - 20 + 10), u8"name")
                + u8" by "s + effect1 + ""s);
    default: assert(0);
    }
}



void apply_buff(int cc, int id, int power)
{
    const auto [effect1, effect2] = calc_buff_effect(id, power);

    switch (id)
    {
    case 1:
        cdata[cc].pv += effect1;
        cdata[cc].fear = 0;
        break;
    case 2: break;
    case 3: sdata(154, cc) += 40; break;
    case 4:
        sdata(50, cc) += 100;
        sdata(51, cc) += 100;
        sdata(52, cc) += 100;
        break;
    case 5: sdata(18, cc) += effect1; break;
    case 6: sdata(18, cc) -= effect1; break;
    case 7:
        sdata(10, cc) += effect1;
        sdata(12, cc) += effect1;
        cdata[cc].fear = 0;
        cdata[cc].confused = 0;
        break;
    case 8:
        cdata[cc].dv = cdata[cc].dv / 2;
        cdata[cc].pv = cdata[cc].pv / 2;
        break;
    case 9:
        sdata(50, cc) =
            std::clamp(sdata(50, cc) + -100, int{sdata(50, cc) > 0}, 9999);
        sdata(51, cc) =
            std::clamp(sdata(51, cc) + -100, int{sdata(51, cc) > 0}, 9999);
        sdata(52, cc) =
            std::clamp(sdata(52, cc) + -100, int{sdata(52, cc) > 0}, 9999);
        break;
    case 10: break;
    case 11:
        sdata(58, cc) =
            std::clamp(sdata(58, cc) + -100, int{sdata(58, cc) > 0}, 9999);
        sdata(54, cc) =
            std::clamp(sdata(54, cc) + -100, int{sdata(54, cc) > 0}, 9999);
        break;
    case 12:
        sdata(14, cc) += effect1;
        sdata(16, cc) += effect1;
        sdata(150, cc) += effect2;
        break;
    case 13:
        sdata(18, cc) -= effect1;
        if (cdata[cc].pv > 1)
        {
            cdata[cc].pv -= cdata[cc].pv / 5;
        }
        break;
    case 14: sdata(18, cc) += effect1; break;
    case 15: cbitmod(16, cc, 1); break;
    case 16: cbitmod(973, cc, 1); break;
    case 17:
        sdata(18, cc) += effect1;
        sdata(10, cc) = sdata(10, cc) * 150 / 100 + 10;
        sdata(12, cc) = sdata(12, cc) * 150 / 100 + 10;
        sdata(154, cc) += 50;
        cdata[cc].pv = cdata[cc].pv * 150 / 100 + 25;
        cdata[cc].dv = cdata[cc].dv * 150 / 100 + 25;
        cdata[cc].hit_bonus = cdata[cc].hit_bonus * 150 / 100 + 50;
        break;
    case 18: cbitmod(980, cc, 1); break;
    case 19: sdata(19, cc) += effect1; break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28: cdata[cc].growth_buffs[id - 20] = effect1; break;
    default: assert(0);
    }
}



std::optional<skill_damage> calc_skill_damage(int skill, int cc, int power)
{
    int x = sdata(the_ability_db[skill].related_basic_attribute, cc);

    switch (skill)
    {
    case 412: return skill_damage{0, 1, x * power * 5 / 100, 0, 0};
    case 461:
        return skill_damage{
            0, 1, std::clamp((x * 5 + power) / 20 + 40, 40, 100), 0, 0};
    case 411: return skill_damage{0, 1, x * power * 10 / 100, 0, 0};
    case 400:
        return skill_damage{1 + x / 30, power / 40 + 5 + 1, power / 30, 0, 0};
    case 401:
        return skill_damage{2 + x / 26, power / 25 + 5 + 1, power / 15, 0, 0};
    case 405:
        return skill_damage{2 + x / 22, power / 18 + 5 + 1, power / 10, 0, 0};
    case 402:
        return skill_damage{3 + x / 15, power / 12 + 5 + 1, power / 6, 0, 0};
    case 403:
        return skill_damage{5 + x / 10, power / 7 + 5 + 1, power / 2, 0, 0};
    case 406: return skill_damage{0, 1, x * 5 + power * 2, 0, 0};
    case 407: return skill_damage{0, 1, x * 5 + power * 3 / 2, 0, 0};
    case 623:
        return skill_damage{
            1 + x / 10, cdata[cc].piety_point / 70 + 1 + 1, 0, 0, 0};
    case 624:
        return skill_damage{
            1 + x / 20, cdata[cc].piety_point / 140 + 1 + 1, 0, 0, 0};
    case 414:
        return skill_damage{power / 125 + 2 + x / 50,
                            power / 60 + 9 + 1,
                            0,
                            60,
                            100 + power / 4};
    case 459:
        return skill_damage{power / 100 + 3 + x / 25,
                            power / 40 + 12 + 1,
                            0,
                            60,
                            100 + power / 4};
    case 418:
        return skill_damage{power / 80 + 1 + x / 18,
                            power / 25 + 8 + 1,
                            0,
                            53,
                            200 + power / 3};
    case 415:
        return skill_damage{power / 70 + 1 + x / 18,
                            power / 25 + 8 + 1,
                            0,
                            56,
                            200 + power / 3};
    case 417:
        return skill_damage{power / 70 + 1 + x / 18,
                            power / 25 + 8 + 1,
                            0,
                            59,
                            200 + power / 3};
    case 416:
        return skill_damage{power / 70 + 1 + x / 18,
                            power / 25 + 8 + 1,
                            0,
                            58,
                            200 + power / 3};
    case 419:
        return skill_damage{power / 50 + 1 + x / 20,
                            power / 26 + 4 + 1,
                            0,
                            51,
                            180 + power / 4};
    case 420:
        return skill_damage{power / 50 + 1 + x / 20,
                            power / 26 + 4 + 1,
                            0,
                            50,
                            180 + power / 4};
    case 421:
        return skill_damage{power / 50 + 1 + x / 20,
                            power / 26 + 4 + 1,
                            0,
                            52,
                            180 + power / 4};
    case 422:
        return skill_damage{power / 50 + 1 + x / 20,
                            power / 25 + 4 + 1,
                            0,
                            53,
                            180 + power / 4};
    case 423:
        return skill_damage{power / 50 + 1 + x / 20,
                            power / 25 + 4 + 1,
                            0,
                            54,
                            180 + power / 4};
    case 431:
        return skill_damage{power / 100 + 1 + x / 20,
                            power / 15 + 2 + 1,
                            0,
                            51,
                            150 + power / 5};
    case 432:
        return skill_damage{power / 100 + 1 + x / 20,
                            power / 15 + 2 + 1,
                            0,
                            50,
                            150 + power / 5};
    case 433:
        return skill_damage{power / 80 + 1 + x / 20,
                            power / 12 + 2 + 1,
                            0,
                            59,
                            150 + power / 5};
    case 434:
        return skill_damage{power / 80 + 1 + x / 20,
                            power / 12 + 2 + 1,
                            0,
                            57,
                            150 + power / 5};
    case 460:
        return skill_damage{
            power / 100 + 1 + x / 25, power / 18 + 2 + 1, 0, 60, 100};
    case 404:
        return skill_damage{x / 20 + 3, power / 15 + 5 + 1, power / 10, 0, 0};
    case 644: return skill_damage{1 + x / 25, 15 + x / 5 + 1, 1, 0, 0};
    case 601: return skill_damage{1 + x / 15, 7, x / 4, 56, 200};
    case 612: return skill_damage{1 + x / 20, 7, x / 15, 0, 0};
    case 602: return skill_damage{1 + x / 15, 8, x / 8, 50, 100};
    case 603: return skill_damage{1 + x / 15, 8, x / 8, 51, 100};
    case 604: return skill_damage{1 + x / 15, 8, x / 8, 52, 100};
    case 605: return skill_damage{1 + x / 15, 8, x / 8, 53, 100};
    case 606: return skill_damage{1 + x / 15, 8, x / 8, 59, 100};
    case 608: return skill_damage{1 + x / 15, 8, x / 8, 56, 100};
    case 610: return skill_damage{1 + x / 15, 8, x / 8, 55, 100};
    case 607: return skill_damage{1 + x / 15, 8, x / 8, 57, 100};
    case 609: return skill_damage{1 + x / 15, 8, x / 8, 58, 100};
    case 611: return skill_damage{1 + x / 15, 8, x / 8, 54, 100};
    case 613: return skill_damage{1 + x / 10, 4, 1, 0, 0};
    case 614: return skill_damage{1 + x / 10, 4, 1, 0, 0};
    case 617: return skill_damage{1 + x / 10, 4, 0, 0, 100 + x * 2};
    case 618: return skill_damage{1 + x / 10, 4, 0, 0, 100 + x * 3};
    case 615: return skill_damage{1 + x / 10, 5, 0, 55, x * 4 + 20};
    case 616: return skill_damage{1 + x / 10, 5, 0, 58, x * 4 + 20};
    case 636: return skill_damage{1 + x / 20, 11, 1, 0, 0};
    case 655:
        return skill_damage{
            power / 80 + 1, power / 8 + 2 + 1, 0, 57, 150 + power / 2};
    default: return std::nullopt;
    }
}



int calcobjlv(int base)
{
    int ret = base <= 0 ? gdata_current_dungeon_level : base;
    if (gdata_current_map == 30)
    {
        ret = 1;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (rnd(30 + i * 5) == 0)
        {
            ret += rnd(10 * i);
            continue;
        }
        break;
    }
    if (base <= 3)
    {
        if (rnd(4) != 0)
        {
            ret = rnd(3) + 1;
        }
    }
    return ret;
}



int calcfixlv(int base)
{
    int ret = base == 0 ? 2 : base;
    for (int i = 0; i < 3; ++i)
    {
        int p = rnd(30 + i * 5);
        if (p == 0)
        {
            ++ret;
            continue;
        }
        else if (p < 3)
        {
            --ret;
            continue;
        }
        break;
    }
    return std::clamp(ret, 1, 5);
}



int calcfame(int cc, int base)
{
    int ret = base * 100
        / (100 + cdata[cc].fame / 100 * (cdata[cc].fame / 100) / 2500);
    if (ret < 5)
    {
        ret = rnd(5) + 1;
    }
    return ret;
}



int decfame(int cc, int base)
{
    int ret = cdata[cc].fame / base + 5;
    ret = ret + rnd(ret / 2) - rnd(ret / 2);
    cdata[cc].fame -= ret;
    if (cdata[cc].fame < 0)
    {
        cdata[cc].fame = 0;
    }
    return ret;
}



int calcshopreform()
{
    return mdata(18) * 100 + 1000;
}



int calc_rate_to_pierce(int id)
{
    switch (id)
    {
    case 788: return 15;
    case 781: return 40;
    case 759: return 100;
    case 758: return 35;
    case 741: return 20;
    case 739: return 65;
    case 735: return 5;
    case 725: return 0;
    case 718: return 5;
    case 716: return 50;
    case 714: return 0;
    case 713: return 15;
    case 678: return 10;
    case 677: return 30;
    case 675: return 15;
    case 674: return 30;
    case 673: return 20;
    case 633: return 5;
    case 514: return 5;
    case 512: return 5;
    case 496: return 30;
    case 482: return 25;
    case 359: return 40;
    case 266: return 5;
    case 235: return 30;
    case 231: return 0;
    case 230: return 15;
    case 228: return 25;
    case 225: return 10;
    case 224: return 20;
    case 213: return 25;
    case 211: return 5;
    case 210: return 5;
    case 207: return 20;
    case 206: return 20;
    case 73: return 20;
    case 64: return 15;
    case 63: return 15;
    case 60: return 10;
    case 58: return 20;
    case 57: return 25;
    case 56: return 10;
    case 2: return 10;
    case 1: return 5;
    default: return 0;
    }
}



std::string calcage(int cc)
{
    int n = gdata_year - cdata[cc].birth_year;
    return n >= 0 ? std::to_string(n) : lang(u8"不明", u8"Unknown");
}



int calcexpalive(int level)
{
    return level * 100;
}



int calc_evasion(int cc)
{
    return sdata(13, cc) / 3 + sdata(173, cc) + cdata[cc].dv + 25;
}


int calc_accuracy(bool consider_distance)
{
    critical = 0;
    int accuracy;

    if (attackskill == 106)
    {
        accuracy =
            sdata(12, cc) / 5 + sdata(10, cc) / 2 + sdata(attackskill, cc) + 50;
        if (cdata[cc].equipment_type & 1)
        {
            accuracy = accuracy * 100 / 130;
        }
        accuracy +=
            sdata(12, cc) / 5 + sdata(10, cc) / 10 + cdata[cc].hit_bonus;
    }
    else
    {
        accuracy = sdata(12, cc) / 4 + sdata(inv[cw].skill, cc) / 3
            + sdata(attackskill, cc) + 50;
        accuracy += cdata[cc].hit_bonus + inv[cw].hit_bonus;
        if (ammo != -1)
        {
            accuracy += inv[ammo].hit_bonus;
        }
    }

    if (attackskill != 106)
    {
        if (attackrange)
        {
            if (consider_distance)
            {
                rangedist = std::clamp(
                    dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y)
                        - 1,
                    0,
                    9);
                const auto effective_range = calc_effective_range(inv[cw].id);
                accuracy = accuracy * effective_range[rangedist] / 100;
            }
        }
        else
        {
            if (cdata[cc].equipment_type & 2)
            {
                accuracy += 25;
                if (inv[cw].weight >= 4000)
                {
                    accuracy += sdata(167, cc);
                }
            }
            else if (cdata[cc].equipment_type & 4)
            {
                if (attacknum == 1)
                {
                    if (inv[cw].weight >= 4000)
                    {
                        accuracy -= (inv[cw].weight - 4000 + 400)
                            / (10 + sdata(166, cc) / 5);
                    }
                }
                else if (inv[cw].weight > 1500)
                {
                    accuracy -= (inv[cw].weight - 1500 + 100)
                        / (10 + sdata(166, cc) / 5);
                }
            }
        }
    }

    if (gdata_mount != 0)
    {
        if (cc == 0)
        {
            accuracy = accuracy * 100
                / std::clamp((150 - sdata(301, cc) / 2), 115, 150);
            if (attackskill != 106 && attackrange == 0
                && inv[cw].weight >= 4000)
            {
                accuracy -=
                    (inv[cw].weight - 4000 + 400) / (10 + sdata(301, cc) / 5);
            }
        }
        if (cc == gdata_mount)
        {
            accuracy = accuracy * 100
                / std::clamp((150 - sdata(10, cc) / 2), 115, 150);
            if (attackskill != 106 && attackrange == 0
                && inv[cw].weight >= 4000)
            {
                accuracy -=
                    (inv[cw].weight - 4000 + 400) / (10 + sdata(10, cc) / 10);
            }
        }
    }

    if (attacknum > 1)
    {
        int twohit =
            100 - (attacknum - 1) * (10000 / (100 + sdata(166, cc) * 10));
        if (accuracy > 0)
        {
            accuracy = accuracy * twohit / 100;
        }
    }

    return accuracy;
}



int calcattackhit()
{
    int tohit = calc_accuracy(true);
    int evasion = calc_evasion(tc);

    if (cdata[tc].dimmed != 0)
    {
        if (rnd(4) == 0)
        {
            critical = 1;
            return 1;
        }
        evasion /= 2;
    }
    if (cdata[cc].blind != 0)
    {
        tohit /= 2;
    }
    if (cdata[tc].blind != 0)
    {
        evasion /= 2;
    }
    if (cdata[tc].sleep != 0)
    {
        return 1;
    }
    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (attackrange)
        {
            tohit /= 5;
        }
        else
        {
            tohit = tohit / 3 * 2;
        }
    }
    if (sdata(187, tc) != 0)
    {
        if (tohit < sdata(187, tc) * 10)
        {
            int evaderef = evasion * 100 / std::clamp(tohit, 1, tohit);
            if (evaderef > 300)
            {
                if (rnd(sdata(187, tc) + 250) > 100)
                {
                    return -2;
                }
            }
            if (evaderef > 200)
            {
                if (rnd(sdata(187, tc) + 250) > 150)
                {
                    return -2;
                }
            }
            if (evaderef > 150)
            {
                if (rnd(sdata(187, tc) + 250) > 200)
                {
                    return -2;
                }
            }
        }
    }
    if (rnd(5000) < sdata(13, cc) + 50)
    {
        critical = 1;
        return 1;
    }
    if (cdata[cc].rate_of_critical_hit > rnd(200))
    {
        critical = 1;
        return 1;
    }
    if (rnd(20) == 1)
    {
        return -1;
    }
    if (rnd(20) == 0)
    {
        return 1;
    }
    if (tohit < 1)
    {
        return -1;
    }
    if (evasion < 1)
    {
        return 1;
    }
    if (rnd(tohit) > rnd(evasion * 3 / 2))
    {
        return 1;
    }
    return -1;
}



int calcattackdmg(int prm_894)
{
    int prot2 = 0;
    int protfix = 0;
    int damagepierce = 0;
    int damagenormal = 0;
    int pierce;
    if (attackskill == 106)
    {
        dmgfix =
            sdata(10, cc) / 8 + sdata(106, cc) / 8 + cdata[cc].damage_bonus;
        dice1 = 2;
        dice2 = sdata(106, cc) / 8 + 5;
        dmgmulti = 0.5
            + double(
                  (sdata(10, cc) + sdata(attackskill, cc) / 5
                   + sdata(152, cc) * 2))
                / 40;
        pierce = std::clamp(sdata(attackskill, cc) / 5, 5, 50);
    }
    else
    {
        dmgfix = cdata[cc].damage_bonus + inv[cw].damage_bonus
            + inv[cw].enhancement + (inv[cw].curse_state == 1);
        dice1 = inv[cw].dice_x;
        dice2 = inv[cw].dice_y;
        if (ammo != -1)
        {
            dmgfix += inv[ammo].damage_bonus
                + inv[ammo].dice_x * inv[ammo].dice_y / 2;
            dmgmulti = 0.5
                + double(
                      (sdata(13, cc) + sdata(inv[cw].skill, cc) / 5
                       + sdata(attackskill, cc) / 5 + sdata(189, cc) * 3 / 2))
                    / 40;
        }
        else
        {
            dmgmulti = 0.6
                + double(
                      (sdata(10, cc) + sdata(inv[cw].skill, cc) / 5
                       + sdata(attackskill, cc) / 5 + sdata(152, cc) * 2))
                    / 45;
        }
        pierce = calc_rate_to_pierce(inv[cw].id);
    }
    if (attackrange)
    {
        if (prm_894 == 0)
        {
            const auto effective_range = calc_effective_range(inv[cw].id);
            dmgmulti = dmgmulti * effective_range[rangedist] / 100;
        }
    }
    else if (cdata[cc].equipment_type & 2)
    {
        if (inv[cw].weight >= 4000)
        {
            dmgmulti *= 1.5;
        }
        else
        {
            dmgmulti *= 1.2;
        }
        dmgmulti += 0.03 * sdata(167, cc);
    }
    if (cc == 0)
    {
        if (trait(207))
        {
            dmgfix += 5 + cdata[0].level * 2 / 3;
        }
    }
    if (prm_894 == 1)
    {
        return damage;
    }
    prot = cdata[tc].pv + sdata(carmor(tc), tc) + sdata(12, tc) / 10;
    if (prot > 0)
    {
        prot2 = prot / 4;
        protdice1 = prot2 / 10 + 1;
        if (protdice1 < 0)
        {
            protdice1 = 1;
        }
        protdice2 = prot2 / protdice1 + 2;
        protfix = 0;
    }
    else
    {
        prot2 = 0;
        protdice1 = 1;
        protdice2 = 1;
        protfix = 0;
        prot = 0;
    }
    if (prm_894 == 2)
    {
        return prot;
    }
    if (dmgfix < -100)
    {
        dmgfix = -100;
    }
    dmgmulti = int(dmgmulti * 100);
    damage = roll(dice1, dice2, dmgfix);
    if (critical)
    {
        damage = roll_max(dice1, dice2, dmgfix);
        if (attackskill == 106)
        {
            dmgmulti *= 1.25;
        }
        else if (ammo != -1)
        {
            dmgmulti = dmgmulti
                * std::clamp((inv[ammo].weight / 100 + 100), 100, 150) / 100;
        }
        else
        {
            dmgmulti = dmgmulti
                * std::clamp((inv[cw].weight / 200 + 100), 100, 150) / 100;
        }
    }
    damage = damage * dmgmulti / 100;
    orgdmg = damage;
    if (prot > 0)
    {
        damage = damage * 100 / (100 + prot);
    }
    if (attackrange == 0)
    {
        if (cdata[cc].rate_to_pierce > rnd(100))
        {
            pierce = 100;
            if (is_in_fov(cc))
            {
                txtef(5);
                txt(lang(u8" *シャキーン* "s, u8"*vopal*"s));
            }
        }
    }
    else
    {
        if (ammoproc == 2)
        {
            pierce = 60;
            if (is_in_fov(cc))
            {
                txtef(5);
                txt(lang(u8" *ズバシュッ* "s, u8"*vopal*"s));
            }
        }
        if (ammoproc == 0)
        {
            damage /= 2;
        }
        if (ammoproc == 5)
        {
            damage /= 3;
        }
        if (ammoproc == 3)
        {
            damage /= 10;
        }
    }
    damagepierce = damage * pierce / 100;
    damagenormal = damage - damagepierce;
    if (prot > 0)
    {
        damagenormal -= roll(protdice1, protdice2, protfix);
        if (damagenormal < 0)
        {
            damagenormal = 0;
        }
    }
    damage = damagenormal + damagepierce;
    if (tc == 0)
    {
        if (trait(164) != 0)
        {
            --damage;
        }
    }
    if (cdata[tc].decrease_physical_damage != 0)
    {
        damage = damage * 100
            / std::clamp((100 + cdata[tc].decrease_physical_damage), 25, 1000);
    }
    if (damage < 0)
    {
        damage = 0;
    }
    return damage;
}



int calcmedalvalue(int ci)
{
    switch (inv[ci].id)
    {
    case 430: return 5;
    case 431: return 8;
    case 502: return 7;
    case 480: return 20;
    case 421: return 15;
    case 603: return 20;
    case 615: return 5;
    case 559: return 10;
    case 516: return 3;
    case 616: return 18;
    case 623: return 85;
    case 624: return 25;
    case 505: return 12;
    case 625: return 11;
    case 626: return 30;
    case 627: return 55;
    case 56: return 65;
    case 742: return 72;
    case 760: return 94;
    default: return 1;
    }
}



int calcitemvalue(int ci, int situation)
{
    int category = the_item_db[inv[ci].id]->category;
    int ret = 0;
    if (inv[ci].identification_state == 0)
    {
        if (situation == 2)
        {
            ret = inv[ci].value * 4 / 10;
        }
        else
        {
            ret = cdata[0].level / 5
                    * ((gdata_random_seed + ci * 31) % cdata[0].level + 4)
                + 10;
        }
    }
    else if (category >= 50000)
    {
        ret = inv[ci].value;
    }
    else
    {
        if (inv[ci].identification_state == 1)
        {
            ret = inv[ci].value * 2 / 10;
        }
        if (inv[ci].identification_state == 2)
        {
            ret = inv[ci].value * 5 / 10;
        }
        if (inv[ci].identification_state >= 3)
        {
            ret = inv[ci].value;
        }
    }
    if (inv[ci].identification_state >= 3)
    {
        if (inv[ci].curse_state == 1)
        {
            ret = ret * 120 / 100;
        }
        if (inv[ci].curse_state == -1)
        {
            ret = ret / 2;
        }
        if (inv[ci].curse_state == -2)
        {
            ret = ret / 5;
        }
    }
    if (category == 57000)
    {
        if (inv[ci].param2 > 0)
        {
            ret = ret * inv[ci].param2 * inv[ci].param2 / 10;
        }
    }
    if (inv[ci].id == 333)
    {
        if (situation == 0)
        {
            ret += std::clamp(
                cdata[0].fame / 40 + ret * (cdata[0].fame / 80) / 100, 0, 800);
        }
    }
    if (inv[ci].weight < 0)
    {
        if (mode == 6)
        {
            if (category == 92000)
            {
                ret = ret * trate(inv[ci].param1) / 100;
                if (situation == 1)
                {
                    ret = ret * 65 / 100;
                }
                return ret;
            }
        }
    }
    if (ibit(4, ci) == 1)
    {
        dbid = inv[ci].id;
        access_item_db(2);
        if (inv[ci].count < 0)
        {
            ret = ret / 10;
        }
        else if (category == 54000)
        {
            ret = ret / 5 + ret * inv[ci].count / (ichargelevel * 2 + 1);
        }
        else
        {
            ret = ret / 2 + ret * inv[ci].count / (ichargelevel * 3 + 1);
        }
    }
    if (category == 72000)
    {
        if (inv[ci].param1 == 0)
        {
            ret = ret / 100 + 1;
        }
    }
    if (situation == 0)
    {
        int max = ret / 2;
        ret = ret * 100 / (100 + sdata(156, 0));
        if (gdata_belongs_to_mages_guild != 0)
        {
            if (category == 54000)
            {
                ret = ret * 80 / 100;
            }
        }
        if (ret <= max)
        {
            ret = max;
        }
    }
    if (situation == 1)
    {
        int max = sdata(156, 0) * 250 + 5000;
        if (ret / 3 < max)
        {
            max = ret / 3;
        }
        ret = ret * (100 + sdata(156, 0) * 5) / 1000;
        if (category < 50000)
        {
            ret /= 20;
        }
        if (ibit(9, ci))
        {
            if (gdata_belongs_to_thieves_guild == 0)
            {
                ret /= 10;
            }
            else
            {
                ret = ret / 3 * 2;
            }
        }
        if (ret >= max)
        {
            ret = max;
        }
    }
    if (situation == 2)
    {
        ret = ret / 5;
        if (category < 50000)
        {
            ret /= 3;
        }
        if (ret > 15000)
        {
            ret = 15000;
        }
        if (ibit(9, ci))
        {
            ret = 1;
        }
    }
    if (ret <= 0)
    {
        ret = 1;
    }
    return ret;
}



int calcinvestvalue()
{
    int rank = std::clamp(cdata[tc].shop_rank, 1, 200);
    int ret = rank * rank * 15 + 200;
    if (ret > 500'000)
    {
        ret = 500'000;
    }
    return ret * 100 / (100 + sdata(160, 0) * 10) + 200;
}



int calcguiltvalue()
{
    return -(cdata[0].karma + 30) * (cdata[0].fame / 2 + cdata[0].level * 200);
}



int calchireadv(int adventurer)
{
    return 250 + cdata[adventurer].level * cdata[adventurer].level * 30;
}



int calchirecost(int cc)
{
    switch (cdata[cc].character_role)
    {
    case 18: return 450;
    case 7: return 250;
    case 9: return 350;
    case 12: return 500;
    case 5: return 750;
    case 8: return 250;
    case 14: return 50;
    case 1007: return 4000;
    case 2003: return 0;
    default:
        if (cdata[cc].character_role >= 1000 && cdata[cc].character_role < 2000)
        {
            return 1000;
        }
        else
        {
            return 0;
        }
    }
}



void generatemoney(int cc)
{
    int gold = rnd(100) + rnd(cdata[cc].level * 50 + 1);
    if ((cdata[cc].character_role >= 1000 && cdata[cc].character_role < 2000)
        || cdata[cc].character_role == 2003)
    {
        gold += 2500 + cdata[cc].shop_rank * 250;
    }
    if (cdata[cc].gold < gold / 2)
    {
        cdata[cc].gold = gold;
    }
}



void calccosthire()
{
    int cost{};
    for (int cnt = 57; cnt < 245; ++cnt)
    {
        if (cdata[cnt].character_role == 0)
            continue;
        if (cdata[cnt].state != 1)
            continue;
        cost += calchirecost(cnt);
    }
    cost = cost
        * std::clamp(
               100 - std::clamp(cdata[0].karma / 2, 0, 50) - 7 * trait(38)
                   - (cdata[0].karma >= 20) * 5,
               25,
               200)
        / 100;
    gdata_cost_to_hire = cost;
}



int calccostbuilding()
{
    int cost = gdata_home_scale * gdata_home_scale * 200;

    for (int cnt = 300; cnt < 450; ++cnt)
    {
        switch (adata(16, cnt))
        {
        case 101: cost += 1500; break;
        case 31: cost += 1000; break;
        case 103: cost += 750; break;
        case 102: cost += 5000; break;
        case 104: cost += 750; break;
        default: break;
        }
    }

    return cost
        * std::clamp(
               100 - std::clamp(cdata[0].karma / 2, 0, 50) - 7 * trait(38)
                   - (cdata[0].karma >= 20) * 5,
               25,
               200)
        / 100;
}



int calccosttax()
{
    int cost{};
    cost += cdata[0].gold / 1000;
    cost += cdata[0].fame;
    cost += cdata[0].level * 200;
    return cost
        * std::clamp(
               100 - std::clamp(cdata[0].karma / 2, 0, 50) - 7 * trait(38)
                   - (cdata[0].karma >= 20) * 5,
               25,
               200)
        / 100;
}



int calcmealvalue()
{
    return 140;
}



int calccostreload(int owner, bool do_reload)
{
    int cost{};

    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
            continue;
        if (the_item_db[inv[cnt].id]->category != 25000)
            continue;

        int ammo = cnt;
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[ammo].enchantments[cnt].id == 0)
                break;

            int enc = inv[ammo].enchantments[cnt].id;
            if (enc / 10000 == 9)
            {
                int type = enc % 10000;
                int current = inv[ammo].enchantments[cnt].power % 1000;
                int max = inv[ammo].enchantments[cnt].power / 1000;
                cost += (max - current) * (50 + type * type * 10);
                if (do_reload)
                {
                    inv[ammo].enchantments[cnt].power = max * 1000 + max;
                }
            }
        }
    }

    return cost;
}



int calccargoupdate()
{
    return 10000;
}



int calccargoupdatecost()
{
    return (gdata_current_cart_limit - gdata_initial_cart_limit) / 10000 + 1;
}



int calcidentifyvalue(int type)
{
    int cost;

    cost = 300;
    if (type == 2)
    {
        cost = 5000;
    }
    if (type == 1)
    {
        int need_to_identify{};
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].identification_state < 3)
            {
                ++need_to_identify;
            }
        }
        if (need_to_identify >= 2)
        {
            cost = cost * need_to_identify * 70 / 100;
        }
    }
    cost = cost * 100 / (100 + sdata(156, 0) * 2);

    return gdata_belongs_to_fighters_guild ? cost / 2 : cost;
}



int calctraincost(int skill_id, int cc, bool discount)
{
    int platinum = sdata.get(skill_id, cc).original_level / 5 + 2;
    return discount ? platinum / 2 : platinum;
}



int calclearncost(int skill_id, int cc, bool discount)
{
    (void)skill_id;
    (void)cc;

    int platinum = 15 + 3 * gdata_number_of_learned_skills_by_trainer;
    return discount ? platinum * 2 / 3 : platinum;
}



int calcresurrectvalue(int pet)
{
    return cdata[pet].state != 6 ? 100
                                 : cdata[pet].level * cdata[pet].level * 15;
}



int calcslavevalue(int pet)
{
    int value = sdata(10, pet) * sdata(11, pet)
        + cdata[pet].level * cdata[pet].level + 1000;
    if (value > 50'000)
    {
        value = 50'000;
    }
    if (cbit(23, pet) || cbit(27, pet))
    {
        value = 10;
    }
    return value;
}



int calcrestorecost()
{
    return gdata_belongs_to_fighters_guild ? 250 : 500;
}



int calcinitgold(int owner)
{
    if (owner < 0)
    {
        return rnd(gdata_current_dungeon_level * 25 * (gdata_current_map != 30)
                   + 10)
            + 1;
    }

    switch (cdata[owner].id)
    {
    case 183: return 5000 + rnd(11000);
    case 184: return 2000 + rnd(5000);
    case 185: return 1000 + rnd(3000);
    default: return rnd(cdata[owner].level * 25 + 10) + 1;
    }
}



int calcspellpower(int id, int cc)
{
    if (id >= 600)
    {
        if (the_ability_db[id].related_basic_attribute != 0)
        {
            return sdata(the_ability_db[id].related_basic_attribute, cc) * 6
                + 10;
        }
        return 100;
    }
    if (cc == 0)
    {
        return sdata(id, cc) * 10 + 50;
    }
    if (sdata(172, cc) == 0 && cc >= 16)
    {
        return cdata[cc].level * 6 + 10;
    }
    return sdata(172, cc) * 6 + 10;
}



int calcspellfail(int id, int cc)
{
    if (debug::voldemort)
    {
        return 100;
    }

    if (cc != 0)
    {
        if (gdata_mount == cc)
        {
            return 95 - std::clamp(30 - sdata(301, 0) / 2, 0, 30);
        }
        else
        {
            return 95;
        }
    }

    int penalty = 4;

    int armor_skill = carmor(cc);
    if (armor_skill == 169)
    {
        penalty = 17 - sdata(169, cc) / 5;
    }
    else if (armor_skill == 170)
    {
        penalty = 12 - sdata(170, cc) / 5;
    }
    if (penalty < 4)
    {
        penalty = 4;
    }
    if (gdata_mount != 0)
    {
        penalty += 4;
    }
    if (id == 441) // Wish
    {
        penalty += sdata(id, cc);
    }
    if (id == 464) // Harvest
    {
        penalty += sdata(id, cc) / 3;
    }

    int percentage = 90 + sdata(id, cc)
        - the_ability_db[id].sdataref4 * penalty / (5 + sdata(172, cc) * 4);
    if (armor_skill == 169)
    {
        if (percentage > 80)
        {
            percentage = 80;
        }
    }
    else if (armor_skill == 170)
    {
        if (percentage > 92)
        {
            percentage = 92;
        }
    }
    else if (percentage > 100)
    {
        percentage = 100;
    }
    if (cdata[cc].equipment_type & 4)
    {
        percentage -= 6;
    }
    if (cdata[cc].equipment_type & 1)
    {
        percentage -= 12;
    }
    if (percentage < 0)
    {
        percentage = 0;
    }
    return percentage;
}



int calcspellcostmp(int id, int cc)
{
    if (debug::voldemort)
        return 1;

    if (cc == 0)
    {
        if (id == 413 || id == 461 || id == 457 || id == 438 || id == 409
            || id == 408 || id == 410 || id == 466)
        {
            return the_ability_db[id].cost;
        }
        else
        {
            return the_ability_db[id].cost * (100 + sdata(id, cc) * 3) / 100
                + sdata(id, cc) / 8;
        }
    }
    else
    {
        return the_ability_db[id].cost * (50 + cdata[cc].level * 3) / 100;
    }
}



int calcspellcoststock(int id, int cc)
{
    if (debug::voldemort)
        return 1;

    int cost = the_ability_db[id].cost * 200 / (sdata(id, cc) * 3 + 100);
    if (cost < the_ability_db[id].cost / 5)
    {
        cost = the_ability_db[id].cost / 5;
    }
    cost = rnd(cost / 2 + 1) + cost / 2;
    if (cost < 1)
    {
        cost = 1;
    }
    return cost;
}



int calcscore()
{
    int score = cdata[0].level * cdata[0].level
        + gdata_deepest_dungeon_level * gdata_deepest_dungeon_level
        + gdata_kill_count;
    if (gdata_death_count > 1)
    {
        score = score / 10 + 1;
    }
    if (gdata_wizard)
    {
        score = 0;
    }
    return score;
}



void calcpartyscore()
{
    int score = 0;
    for (int cnt = 57; cnt < 245; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].impression >= 53)
        {
            score += cdata[cnt].level + 5;
        }
        if (cdata[cnt].impression < 50)
        {
            score -= 20;
        }
    }
    if (score > qdata(13, gdata_executing_immediate_quest))
    {
        txtef(4);
        txt(u8"(+"s + (score - qdata(13, gdata_executing_immediate_quest))
            + u8") "s);
    }
    if (score < qdata(13, gdata_executing_immediate_quest))
    {
        txtef(3);
        txt(u8"("s + (score - qdata(13, gdata_executing_immediate_quest))
            + u8") "s);
    }
    qdata(13, gdata_executing_immediate_quest) = score;
}



void calcpartyscore2()
{
    int score{};
    for (int cnt = 57; cnt < 245; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].impression >= 53 && cdata[cnt].quality >= 4)
        {
            score += 20 + cdata[cnt].level / 2;
            txt(lang(
                cdatan(0, cnt) + u8"は満足した。"s,
                cdatan(0, cnt) + u8" "s + is(cnt) + u8" satisfied."s));
        }
    }
    if (score != 0)
    {
        txt(lang(
            u8"(合計ボーナス:"s + score + u8"%) "s,
            u8"(Total Bonus:"s + score + u8"%)"s));
    }
    qdata(13, gdata_executing_immediate_quest) =
        qdata(13, gdata_executing_immediate_quest) * (100 + score) / 100;
}



} // namespace elona
