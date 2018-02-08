#include "ability.hpp"
#include "character.hpp"
#include "debug.hpp"
#include "elona.hpp"
#include "item.hpp"
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


} // namespace



namespace elona
{


elona_vector1<int> rangemap;
int rangedist = 0;
int value_at_m153 = 0;
int p_at_m153 = 0;
int cost_at_m153 = 0;



int calc_buff_duration(int id, int power)
{
    switch (id)
    {
    case 1: return 10 + power / 10;
    case 2: return 5 + power / 40;
    case 3: return 12 + power / 20;
    case 4: return 4 + power / 6;
    case 5: return 8 + power / 30;
    case 6: return 8 + power / 30;
    case 7: return 10 + power / 4;
    case 8: return 6 + power / 10;
    case 9: return 4 + power / 15;
    case 10: return 15 + power / 5;
    case 11: return 4 + power / 15;
    case 12: return 10 + power / 4;
    case 13: return power;
    case 14: return 7;
    case 15: return 4 + power / 40;
    case 16: return 20;
    case 17: return 5;
    case 18: return 66;
    case 19: return 777;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28: return 10 + power / 10;
    default: assert(0);
    }
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
            skillname(id - 20 + 10) + u8"の成長率を"s + effect1 + u8"%上昇"s,
            u8"Increases the growth rate "s + skillname((id - 20 + 10))
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



int calcskill(int prm_269, int prm_270, int prm_271)
{
    int ep = 0;
    int rs_at_m9 = 0;
    rs_at_m9 = sdata(sdataref(0, prm_269), prm_270);
    ele = 0;
    elep = 0;
    if (prm_269 == 412)
    {
        dice1 = 0;
        dice2 = 1;
        bonus = rs_at_m9 * prm_271 * 5 / 100;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 461)
    {
        dice1 = 0;
        dice2 = 1;
        bonus = std::clamp((rs_at_m9 * 5 + prm_271) / 20 + 40, 40, 100);
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 411)
    {
        dice1 = 0;
        dice2 = 1;
        bonus = rs_at_m9 * prm_271 * 10 / 100;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 400)
    {
        dice1 = 1 + rs_at_m9 / 30;
        dice2 = prm_271 / 40 + 5 + 1;
        bonus = prm_271 / 30;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 401)
    {
        dice1 = 2 + rs_at_m9 / 26;
        dice2 = prm_271 / 25 + 5 + 1;
        bonus = prm_271 / 15;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 405)
    {
        dice1 = 2 + rs_at_m9 / 22;
        dice2 = prm_271 / 18 + 5 + 1;
        bonus = prm_271 / 10;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 402)
    {
        dice1 = 3 + rs_at_m9 / 15;
        dice2 = prm_271 / 12 + 5 + 1;
        bonus = prm_271 / 6;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 403)
    {
        dice1 = 5 + rs_at_m9 / 10;
        dice2 = prm_271 / 7 + 5 + 1;
        bonus = prm_271 / 2;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 406)
    {
        dice1 = 0;
        dice2 = 1;
        bonus = rs_at_m9 * 5 + prm_271 * 2;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 407)
    {
        dice1 = 0;
        dice2 = 1;
        bonus = rs_at_m9 * 5 + prm_271 * 3 / 2;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 623)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = cdata[prm_270].piety_point / 70 + 1 + 1;
        bonus = 0;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 624)
    {
        dice1 = 1 + rs_at_m9 / 20;
        dice2 = cdata[prm_270].piety_point / 140 + 1 + 1;
        bonus = 0;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 414)
    {
        dice1 = prm_271 / 125 + 2 + rs_at_m9 / 50;
        dice2 = prm_271 / 60 + 9 + 1;
        bonus = 0;
        ele = 60;
        elep = 100 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 459)
    {
        dice1 = prm_271 / 100 + 3 + rs_at_m9 / 25;
        dice2 = prm_271 / 40 + 12 + 1;
        bonus = 0;
        ele = 60;
        elep = 100 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 418)
    {
        dice1 = prm_271 / 80 + 1 + rs_at_m9 / 18;
        dice2 = prm_271 / 25 + 8 + 1;
        bonus = 0;
        ele = 53;
        elep = 200 + prm_271 / 3;
        return 1;
    }
    if (prm_269 == 415)
    {
        dice1 = prm_271 / 70 + 1 + rs_at_m9 / 18;
        dice2 = prm_271 / 25 + 8 + 1;
        bonus = 0;
        ele = 56;
        elep = 200 + prm_271 / 3;
        return 1;
    }
    if (prm_269 == 417)
    {
        dice1 = prm_271 / 70 + 1 + rs_at_m9 / 18;
        dice2 = prm_271 / 25 + 8 + 1;
        bonus = 0;
        ele = 59;
        elep = 200 + prm_271 / 3;
        return 1;
    }
    if (prm_269 == 416)
    {
        dice1 = prm_271 / 70 + 1 + rs_at_m9 / 18;
        dice2 = prm_271 / 25 + 8 + 1;
        bonus = 0;
        ele = 58;
        elep = 200 + prm_271 / 3;
        return 1;
    }
    if (prm_269 == 419)
    {
        dice1 = prm_271 / 50 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 26 + 4 + 1;
        bonus = 0;
        ele = 51;
        elep = 180 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 420)
    {
        dice1 = prm_271 / 50 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 26 + 4 + 1;
        bonus = 0;
        ele = 50;
        elep = 180 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 421)
    {
        dice1 = prm_271 / 50 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 26 + 4 + 1;
        bonus = 0;
        ele = 52;
        elep = 180 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 422)
    {
        dice1 = prm_271 / 50 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 25 + 4 + 1;
        bonus = 0;
        ele = 53;
        elep = 180 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 423)
    {
        dice1 = prm_271 / 50 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 25 + 4 + 1;
        bonus = 0;
        ele = 54;
        elep = 180 + prm_271 / 4;
        return 1;
    }
    if (prm_269 == 431)
    {
        dice1 = prm_271 / 100 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 15 + 2 + 1;
        bonus = 0;
        ele = 51;
        elep = 150 + prm_271 / 5;
        return 1;
    }
    if (prm_269 == 432)
    {
        dice1 = prm_271 / 100 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 15 + 2 + 1;
        bonus = 0;
        ele = 50;
        elep = 150 + prm_271 / 5;
        return 1;
    }
    if (prm_269 == 433)
    {
        dice1 = prm_271 / 80 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 12 + 2 + 1;
        bonus = 0;
        ele = 59;
        elep = 150 + prm_271 / 5;
        return 1;
    }
    if (prm_269 == 434)
    {
        dice1 = prm_271 / 80 + 1 + rs_at_m9 / 20;
        dice2 = prm_271 / 12 + 2 + 1;
        bonus = 0;
        ele = 57;
        elep = 150 + prm_271 / 5;
        return 1;
    }
    if (prm_269 == 460)
    {
        dice1 = prm_271 / 100 + 1 + rs_at_m9 / 25;
        dice2 = prm_271 / 18 + 2 + 1;
        bonus = 0;
        ele = 60;
        elep = 100;
        return 1;
    }
    if (prm_269 == 404)
    {
        dice1 = rs_at_m9 / 20 + 3;
        dice2 = prm_271 / 15 + 5 + 1;
        bonus = prm_271 / 10;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 644)
    {
        dice1 = 1 + rs_at_m9 / 25;
        dice2 = 15 + rs_at_m9 / 5 + 1;
        bonus = ele == 0;
        elep = 0;
        return 1;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 601)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 7;
        bonus = rs_at_m9 / 4;
        ele = 56;
        elep = 200;
        return 1;
    }
    if (prm_269 == 612)
    {
        dice1 = 1 + rs_at_m9 / 20;
        dice2 = 7;
        bonus = rs_at_m9 / 15;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 602)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 50;
        elep = 100;
        return 1;
    }
    if (prm_269 == 603)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 51;
        elep = 100;
        return 1;
    }
    if (prm_269 == 604)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 52;
        elep = 100;
        return 1;
    }
    if (prm_269 == 605)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 53;
        elep = 100;
        return 1;
    }
    if (prm_269 == 606)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 59;
        elep = 100;
        return 1;
    }
    if (prm_269 == 608)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 56;
        elep = 100;
        return 1;
    }
    if (prm_269 == 610)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 55;
        elep = 100;
        return 1;
    }
    if (prm_269 == 607)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 57;
        elep = 100;
        return 1;
    }
    if (prm_269 == 609)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 58;
        elep = 100;
        return 1;
    }
    if (prm_269 == 611)
    {
        dice1 = 1 + rs_at_m9 / 15;
        dice2 = 8;
        bonus = rs_at_m9 / 8;
        ele = 54;
        elep = 100;
        return 1;
    }
    if (prm_269 == 613)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 4;
        bonus = ep == 0;
        return 1;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 614)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 4;
        bonus = ep == 0;
        return 1;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 617)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 4;
        bonus = 0;
        ele = 0;
        elep = 100 + rs_at_m9 * 2;
        return 1;
    }
    if (prm_269 == 618)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 4;
        bonus = 0;
        ele = 0;
        elep = 100 + rs_at_m9 * 3;
        return 1;
    }
    if (prm_269 == 615)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 5;
        bonus = 0;
        ele = 55;
        elep = rs_at_m9 * 4 + 20;
        return 1;
    }
    if (prm_269 == 616)
    {
        dice1 = 1 + rs_at_m9 / 10;
        dice2 = 5;
        bonus = 0;
        ele = 58;
        elep = rs_at_m9 * 4 + 20;
        return 1;
    }
    if (prm_269 == 636)
    {
        dice1 = 1 + rs_at_m9 / 20;
        dice2 = 11;
        bonus = elep == 0;
        return 1;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 655)
    {
        dice1 = prm_271 / 80 + 1;
        dice2 = prm_271 / 8 + 2 + 1;
        bonus = 0;
        ele = 57;
        elep = 150 + prm_271 / 2;
        return 1;
    }
    return 0;
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



int calcweaponfix(int prm_752)
{
    pierce = 0;
    rangemap(0) = 100;
    rangemap(1) = 20;
    rangemap(2) = 20;
    rangemap(3) = 20;
    rangemap(4) = 20;
    rangemap(5) = 20;
    rangemap(6) = 20;
    rangemap(7) = 20;
    rangemap(8) = 20;
    rangemap(9) = 20;
    if (prm_752 == 788)
    {
        pierce = 15;
        rangemap(0) = 60;
        rangemap(1) = 90;
        rangemap(2) = 100;
        rangemap(3) = 100;
        rangemap(4) = 80;
        rangemap(5) = 60;
        return 1;
    }
    if (prm_752 == 781)
    {
        pierce = 40;
        return 1;
    }
    if (prm_752 == 759)
    {
        pierce = 100;
        return 1;
    }
    if (prm_752 == 758)
    {
        pierce = 35;
        rangemap(0) = 100;
        rangemap(1) = 90;
        rangemap(2) = 70;
        rangemap(3) = 50;
        return 1;
    }
    if (prm_752 == 741)
    {
        pierce = 20;
        return 1;
    }
    if (prm_752 == 739)
    {
        pierce = 65;
        return 1;
    }
    if (prm_752 == 735)
    {
        pierce = 5;
        return 1;
    }
    if (prm_752 == 725)
    {
        pierce = 0;
        rangemap(0) = 60;
        rangemap(1) = 100;
        rangemap(2) = 70;
        return 1;
    }
    if (prm_752 == 718)
    {
        pierce = 5;
        rangemap(0) = 50;
        rangemap(1) = 100;
        rangemap(2) = 50;
        return 1;
    }
    if (prm_752 == 716)
    {
        pierce = 50;
        rangemap(0) = 60;
        rangemap(1) = 100;
        rangemap(2) = 70;
        return 1;
    }
    if (prm_752 == 714)
    {
        pierce = 0;
        rangemap(0) = 80;
        rangemap(1) = 100;
        rangemap(2) = 90;
        rangemap(3) = 80;
        rangemap(4) = 60;
        return 1;
    }
    if (prm_752 == 713)
    {
        pierce = 15;
        rangemap(0) = 60;
        rangemap(1) = 100;
        rangemap(2) = 70;
        return 1;
    }
    if (prm_752 == 678)
    {
        pierce = 10;
        return 1;
    }
    if (prm_752 == 677)
    {
        pierce = 30;
        return 1;
    }
    if (prm_752 == 675)
    {
        pierce = 15;
        return 1;
    }
    if (prm_752 == 674)
    {
        pierce = 30;
        rangemap(0) = 100;
        rangemap(1) = 40;
        return 1;
    }
    if (prm_752 == 673)
    {
        pierce = 20;
        rangemap(0) = 50;
        rangemap(1) = 90;
        rangemap(2) = 100;
        rangemap(3) = 90;
        rangemap(4) = 80;
        rangemap(5) = 80;
        rangemap(6) = 70;
        rangemap(7) = 60;
        rangemap(8) = 50;
        return 1;
    }
    if (prm_752 == 633)
    {
        pierce = 5;
        rangemap(0) = 50;
        rangemap(1) = 100;
        rangemap(2) = 50;
        return 1;
    }
    if (prm_752 == 514)
    {
        pierce = 5;
        rangemap(0) = 100;
        rangemap(1) = 100;
        rangemap(2) = 100;
        rangemap(3) = 100;
        rangemap(4) = 100;
        rangemap(5) = 100;
        rangemap(6) = 100;
        rangemap(7) = 50;
        return 1;
    }
    if (prm_752 == 512)
    {
        pierce = 5;
        rangemap(0) = 100;
        rangemap(1) = 100;
        rangemap(2) = 100;
        rangemap(3) = 100;
        rangemap(4) = 100;
        rangemap(5) = 100;
        rangemap(6) = 100;
        return 1;
    }
    if (prm_752 == 496)
    {
        pierce = 30;
        rangemap(0) = 100;
        rangemap(1) = 60;
        return 1;
    }
    if (prm_752 == 482)
    {
        pierce = 25;
        rangemap(0) = 80;
        rangemap(1) = 100;
        rangemap(2) = 90;
        rangemap(3) = 80;
        rangemap(4) = 70;
        rangemap(5) = 60;
        rangemap(6) = 50;
        return 1;
    }
    if (prm_752 == 359)
    {
        pierce = 40;
        return 1;
    }
    if (prm_752 == 266)
    {
        pierce = 5;
        return 1;
    }
    if (prm_752 == 235)
    {
        pierce = 30;
        return 1;
    }
    if (prm_752 == 231)
    {
        pierce = 0;
        rangemap(0) = 80;
        rangemap(1) = 100;
        rangemap(2) = 100;
        rangemap(3) = 90;
        rangemap(4) = 80;
        rangemap(5) = 70;
        return 1;
    }
    if (prm_752 == 230)
    {
        pierce = 15;
        rangemap(0) = 70;
        rangemap(1) = 100;
        rangemap(2) = 100;
        rangemap(3) = 80;
        rangemap(4) = 60;
        return 1;
    }
    if (prm_752 == 228)
    {
        pierce = 25;
        return 1;
    }
    if (prm_752 == 225)
    {
        pierce = 10;
        return 1;
    }
    if (prm_752 == 224)
    {
        pierce = 20;
        return 1;
    }
    if (prm_752 == 213)
    {
        pierce = 25;
        return 1;
    }
    if (prm_752 == 211)
    {
        pierce = 5;
        return 1;
    }
    if (prm_752 == 210)
    {
        pierce = 5;
        rangemap(0) = 60;
        rangemap(1) = 100;
        rangemap(2) = 70;
        return 1;
    }
    if (prm_752 == 207)
    {
        pierce = 20;
        rangemap(0) = 50;
        rangemap(1) = 90;
        rangemap(2) = 100;
        rangemap(3) = 90;
        rangemap(4) = 80;
        rangemap(5) = 80;
        rangemap(6) = 70;
        rangemap(7) = 60;
        rangemap(8) = 50;
        return 1;
    }
    if (prm_752 == 206)
    {
        pierce = 20;
        return 1;
    }
    if (prm_752 == 73)
    {
        pierce = 20;
        return 1;
    }
    if (prm_752 == 64)
    {
        pierce = 15;
        return 1;
    }
    if (prm_752 == 63)
    {
        pierce = 15;
        return 1;
    }
    if (prm_752 == 60)
    {
        pierce = 10;
        rangemap(0) = 100;
        rangemap(1) = 90;
        rangemap(2) = 70;
        rangemap(3) = 50;
        return 1;
    }
    if (prm_752 == 58)
    {
        pierce = 20;
        rangemap(0) = 50;
        rangemap(1) = 90;
        rangemap(2) = 100;
        rangemap(3) = 90;
        rangemap(4) = 80;
        rangemap(5) = 80;
        rangemap(6) = 70;
        rangemap(7) = 60;
        rangemap(8) = 50;
        return 1;
    }
    if (prm_752 == 57)
    {
        pierce = 25;
        return 1;
    }
    if (prm_752 == 56)
    {
        pierce = 10;
        return 1;
    }
    if (prm_752 == 2)
    {
        pierce = 10;
        return 1;
    }
    if (prm_752 == 1)
    {
        pierce = 5;
        return 1;
    }
    return 0;
}



std::string calcage(int prm_762)
{
    if (gdata_year - cdata[prm_762].birth_year < 0)
    {
        return lang(u8"不明"s, u8"Unknown"s);
    }
    return std::to_string(gdata_year - cdata[prm_762].birth_year);
}



int calcexpalive(int prm_892)
{
    return prm_892 * 100;
}



int calcattackhit(int prm_893)
{
    int tohitorg = 0;
    int tohitfix = 0;
    int tohi = 0;
    int twohit = 0;
    int evaderef = 0;
    critical = 0;
    if (attackskill == 106)
    {
        tohitorg =
            sdata(12, cc) / 5 + sdata(10, cc) / 2 + sdata(attackskill, cc) + 50;
        tohitfix = sdata(12, cc) / 5 + sdata(10, cc) / 10 + cdata[cc].hit_bonus;
        pierce = std::clamp(sdata(attackskill, cc) / 5, 5, 50);
        if (cdata[cc].equipment_type & 1)
        {
            tohitorg = tohitorg * 100 / 130;
        }
    }
    else
    {
        tohitorg = sdata(12, cc) / 4 + sdata(inv[cw].skill, cc) / 3
            + sdata(attackskill, cc) + 50;
        tohitfix = cdata[cc].hit_bonus + inv[cw].hit_bonus;
        if (ammo != -1)
        {
            tohitfix += inv[ammo].hit_bonus;
        }
        calcweaponfix(inv[cw].id);
    }
    tohit = tohitorg + tohitfix;
    if (attackskill != 106)
    {
        if (attackrange)
        {
            if (prm_893 == 0)
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
                tohi = tohit * rangemap(rangedist) / 100;
            }
        }
        else
        {
            if (cdata[cc].equipment_type & 2)
            {
                tohit += 25;
                if (inv[cw].weight >= 4000)
                {
                    tohit += sdata(167, cc);
                }
            }
            if (cdata[cc].equipment_type & 4)
            {
                if (attacknum == 1)
                {
                    if (inv[cw].weight >= 4000)
                    {
                        tohit -= (inv[cw].weight - 4000 + 400)
                            / (10 + sdata(166, cc) / 5);
                    }
                }
                else if (inv[cw].weight > 1500)
                {
                    tohit -= (inv[cw].weight - 1500 + 100)
                        / (10 + sdata(166, cc) / 5);
                }
            }
        }
    }
    if (gdata_mount != 0)
    {
        if (cc == 0)
        {
            tohit =
                tohit * 100 / std::clamp((150 - sdata(301, cc) / 2), 115, 150);
            if (attackskill != 106)
            {
                if (attackrange == 0)
                {
                    if (inv[cw].weight >= 4000)
                    {
                        tohit -= (inv[cw].weight - 4000 + 400)
                            / (10 + sdata(301, cc) / 5);
                    }
                }
            }
        }
        if (cc == gdata_mount)
        {
            tohit =
                tohit * 100 / std::clamp((150 - sdata(10, cc) / 2), 115, 150);
            if (attackskill != 106)
            {
                if (attackrange == 0)
                {
                    if (inv[cw].weight >= 4000)
                    {
                        tohit -= (inv[cw].weight - 4000 + 400)
                            / (10 + sdata(10, cc) / 10);
                    }
                }
            }
        }
    }
    if (attacknum > 1)
    {
        twohit = 100 - (attacknum - 1) * (10000 / (100 + sdata(166, cc) * 10));
        if (tohit > 0)
        {
            tohit = tohit * twohit / 100;
        }
    }
    if (prm_893 == 1)
    {
        return tohit;
    }
    evade = sdata(13, tc) / 3 + sdata(173, tc) + cdata[tc].dv + 25;
    if (prm_893 == 2)
    {
        return evade;
    }
    if (cdata[tc].dimmed != 0)
    {
        if (rnd(4) == 0)
        {
            critical = 1;
            return 1;
        }
        evade /= 2;
    }
    if (cdata[cc].blind != 0)
    {
        tohit /= 2;
    }
    if (cdata[tc].blind != 0)
    {
        evade /= 2;
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
            evaderef = evade * 100 / std::clamp(tohit, 1, tohit);
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
    if (evade < 1)
    {
        return 1;
    }
    if (rnd(tohit) > rnd(evade * 3 / 2))
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
    }
    if (attackrange)
    {
        if (prm_894 == 0)
        {
            dmgmulti = dmgmulti * rangemap(rangedist) / 100;
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
    damage = role(dice1, dice2, dmgfix);
    if (critical)
    {
        damage = rolemax(dice1, dice2, dmgfix);
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
            if (synccheck(cc, -1))
            {
                txtef(5);
                txt(lang(u8" *シャキーン* "s, u8"*vopal*"s));
                txtmore();
            }
        }
    }
    else
    {
        if (ammoproc == 2)
        {
            pierce = 60;
            if (synccheck(cc, -1))
            {
                txtef(5);
                txt(lang(u8" *ズバシュッ* "s, u8"*vopal*"s));
                txtmore();
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
        damagenormal -= role(protdice1, protdice2, protfix);
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
    int category = refitem(inv[ci].id, 5);
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
        dbmode = 2;
        access_item_db();
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



int calcinvestvalue(int)
{
    value_at_m153 = std::clamp(cdata[tc].shop_rank, 1, 200)
            * std::clamp(cdata[tc].shop_rank, 1, 200) * 15
        + 200;
    if (value_at_m153 > 500000)
    {
        value_at_m153 = 500000;
    }
    value_at_m153 = value_at_m153 * 100 / (100 + sdata(160, 0) * 10) + 200;
    return value_at_m153;
}



int calcguiltvalue(int)
{
    value_at_m153 =
        (-cdata[0].karma + -30) * (cdata[0].fame / 2 + cdata[0].level * 200);
    return value_at_m153;
}



int calchireadv(int prm_902)
{
    return 250 + cdata[prm_902].level * cdata[prm_902].level * 30;
}



int calchirecost(int prm_903)
{
    value_at_m153 = 0;
    if (cdata[prm_903].character_role == 18)
    {
        value_at_m153 = 450;
    }
    if (cdata[prm_903].character_role == 7)
    {
        value_at_m153 = 250;
    }
    if (cdata[prm_903].character_role == 9)
    {
        value_at_m153 = 350;
    }
    if (cdata[prm_903].character_role == 12)
    {
        value_at_m153 = 500;
    }
    if (cdata[prm_903].character_role == 5)
    {
        value_at_m153 = 750;
    }
    if (cdata[prm_903].character_role == 8)
    {
        value_at_m153 = 250;
    }
    if (cdata[prm_903].character_role == 14)
    {
        value_at_m153 = 50;
    }
    if (cdata[prm_903].character_role >= 1000
            && cdata[prm_903].character_role < 2000
        || cdata[prm_903].character_role == 2003)
    {
        value_at_m153 = 1000;
        if (cdata[prm_903].character_role == 1007)
        {
            value_at_m153 *= 4;
        }
        if (cdata[prm_903].character_role == 2003)
        {
            value_at_m153 = 0;
        }
    }
    return value_at_m153;
}



void generatemoney(int prm_904)
{
    p_at_m153 = rnd(100) + rnd((cdata[prm_904].level * 50 + 1));
    if (cdata[prm_904].character_role >= 1000
            && cdata[prm_904].character_role < 2000
        || cdata[prm_904].character_role == 2003)
    {
        p_at_m153 += 2500 + cdata[prm_904].shop_rank * 250;
    }
    if (cdata[prm_904].gold < p_at_m153 / 2)
    {
        cdata[prm_904].gold = p_at_m153;
    }
    return;
}



void calccosthire()
{
    cost_at_m153 = 0;
    {
        int cnt = 57;
        for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt)
        {
            if (cdata[cnt].character_role == 0)
            {
                continue;
            }
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            cost_at_m153 += calchirecost(cnt);
        }
    }
    cost_at_m153 = cost_at_m153
        * std::clamp((100 - std::clamp(cdata[0].karma / 2, 0, 50)
                      - 7 * trait(38) - (cdata[0].karma >= 20) * 5),
                     25,
                     200)
        / 100;
    gdata_cost_to_hire = cost_at_m153;
    return;
}



int calccostbuilding()
{
    cost_at_m153 = 0;
    cost_at_m153 += gdata_home_scale * gdata_home_scale * 200;
    {
        int cnt = 300;
        for (int cnt_end = cnt + (150); cnt < cnt_end; ++cnt)
        {
            if (adata(16, cnt) == 101)
            {
                cost_at_m153 += 1500;
            }
            if (adata(16, cnt) == 31)
            {
                cost_at_m153 += 1000;
            }
            if (adata(16, cnt) == 103)
            {
                cost_at_m153 += 750;
            }
            if (adata(16, cnt) == 102)
            {
                cost_at_m153 += 5000;
            }
            if (adata(16, cnt) == 104)
            {
                cost_at_m153 += 750;
            }
        }
    }
    cost_at_m153 = cost_at_m153
        * std::clamp((100 - std::clamp(cdata[0].karma / 2, 0, 50)
                      - 7 * trait(38) - (cdata[0].karma >= 20) * 5),
                     25,
                     200)
        / 100;
    return cost_at_m153;
}



int calccosttax()
{
    cost_at_m153 = 0;
    cost_at_m153 += cdata[0].gold / 1000;
    cost_at_m153 += cdata[0].fame;
    cost_at_m153 += cdata[0].level * 200;
    cost_at_m153 = cost_at_m153
        * std::clamp((100 - std::clamp(cdata[0].karma / 2, 0, 50)
                      - 7 * trait(38) - (cdata[0].karma >= 20) * 5),
                     25,
                     200)
        / 100;
    return cost_at_m153;
}



int calcmealvalue()
{
    value_at_m153 = 140;
    return value_at_m153;
}



int calccostreload(int prm_905, int prm_906)
{
    int ci_at_m153 = 0;
    int enc_at_m153 = 0;
    elona_vector1<int> i_at_m153;
    cost_at_m153 = 0;
    inv_getheader(prm_905);
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (refitem(inv[cnt].id, 5) != 25000)
            {
                continue;
            }
            ci_at_m153 = cnt;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt)
                {
                    if (inv[ci_at_m153].enchantments[cnt].id == 0)
                    {
                        break;
                    }
                    enc_at_m153 = inv[ci_at_m153].enchantments[cnt].id;
                    i_at_m153 = enc_at_m153 / 10000;
                    if (i_at_m153 != 0)
                    {
                        enc_at_m153 = enc_at_m153 % 10000;
                        if (i_at_m153 == 9)
                        {
                            i_at_m153(0) =
                                inv[ci_at_m153].enchantments[cnt].power % 1000;
                            i_at_m153(1) =
                                inv[ci_at_m153].enchantments[cnt].power / 1000;
                            cost_at_m153 += (i_at_m153(1) - i_at_m153)
                                * (50 + enc_at_m153 * enc_at_m153 * 10);
                            if (prm_906 == 1)
                            {
                                inv[ci_at_m153].enchantments[cnt].power =
                                    i_at_m153(1) * 1000 + i_at_m153(1);
                            }
                        }
                    }
                }
            }
        }
    }
    return cost_at_m153;
}



int calccargoupdate()
{
    return 10000;
}



int calccargoupdatecost()
{
    return (gdata_current_cart_limit - gdata_initial_cart_limit) / 10000 + 1;
}



int calcidentifyvalue(int prm_907)
{
    value_at_m153 = 300;
    if (prm_907 == 2)
    {
        value_at_m153 = 5000;
    }
    if (prm_907 == 1)
    {
        inv_getheader(0);
        p_at_m153 = 0;
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv[cnt].number == 0)
                {
                    continue;
                }
                if (inv[cnt].identification_state < 3)
                {
                    ++p_at_m153;
                }
            }
        }
        if (p_at_m153 >= 2)
        {
            value_at_m153 = value_at_m153 * p_at_m153 * 70 / 100;
        }
    }
    value_at_m153 = value_at_m153 * 100 / (100 + sdata(156, 0) * 2);
    if (gdata_belongs_to_fighters_guild)
    {
        value_at_m153 /= 2;
    }
    return value_at_m153;
}



int calctraincost(int prm_908, int prm_909, int prm_910)
{
    value_at_m153 = sdata.get(prm_908, prm_909).original_level / 5 + 2;
    if (prm_910)
    {
        value_at_m153 /= 2;
    }
    return value_at_m153;
}



int calclearncost(int, int, int prm_913)
{
    value_at_m153 = 15 + 3 * gdata_number_of_learned_skills_by_trainer;
    if (prm_913)
    {
        value_at_m153 = value_at_m153 * 2 / 3;
    }
    return value_at_m153;
}



int calcresurrectvalue(int prm_914)
{
    if (cdata[prm_914].state != 6)
    {
        return 100;
    }
    value_at_m153 = cdata[prm_914].level * cdata[prm_914].level * 15;
    return value_at_m153;
}



int calcslavevalue(int prm_915)
{
    value_at_m153 = sdata(10, prm_915) * sdata(11, prm_915)
        + cdata[prm_915].level * cdata[prm_915].level + 1000;
    if (value_at_m153 > 50000)
    {
        value_at_m153 = 50000;
    }
    if (cbit(23, prm_915) || cbit(27, prm_915))
    {
        value_at_m153 = 10;
    }
    return value_at_m153;
}



int calcrestorecost()
{
    value_at_m153 = 500;
    if (gdata_belongs_to_fighters_guild)
    {
        value_at_m153 /= 2;
    }
    return value_at_m153;
}



int calcinitgold(int prm_917)
{
    int lootrich_at_m155 = 0;
    if (prm_917 < 0)
    {
        return rnd(gdata_current_dungeon_level * 25 * (gdata_current_map != 30)
                   + 10)
            + 1;
    }
    lootrich_at_m155 = -1;
    if (cdata[prm_917].id == 183)
    {
        lootrich_at_m155 = 10;
    }
    if (cdata[prm_917].id == 184)
    {
        lootrich_at_m155 = 4;
    }
    if (cdata[prm_917].id == 185)
    {
        lootrich_at_m155 = 2;
    }
    if (lootrich_at_m155 != -1)
    {
        return lootrich_at_m155 * 500 + rnd((1000 + lootrich_at_m155 * 1000));
    }
    return rnd(cdata[prm_917].level * 25 + 10) + 1;
}



int calcspellpower(int prm_918, int prm_919)
{
    if (prm_918 >= 600)
    {
        if (sdataref(0, prm_918) != 0)
        {
            return sdataref(0, prm_918) * 6 + 10;
        }
        return 100;
    }
    if (prm_919 == 0)
    {
        return sdata(prm_918, prm_919) * 10 + 50;
    }
    if (sdata(172, prm_919) == 0)
    {
        if (prm_919 >= 16)
        {
            return cdata[prm_919].level * 6 + 10;
        }
    }
    return sdata(172, prm_919) * 6 + 10;
}



int calcspellfail(int prm_920, int prm_921)
{
    if (debug::voldemort)
    {
        return 100;
    }

    int i_at_m157 = 0;
    int f_at_m157 = 0;
    int p_at_m157 = 0;
    if (prm_921 != 0)
    {
        if (gdata_mount == prm_921)
        {
            return 95 - std::clamp((30 - sdata(301, 0) / 2), 0, 30);
        }
        else
        {
            return 95;
        }
    }
    i_at_m157 = 4;
    f_at_m157 = carmor(prm_921);
    if (f_at_m157 == 169)
    {
        i_at_m157 = 17 - sdata(169, prm_921) / 5;
    }
    if (f_at_m157 == 170)
    {
        i_at_m157 = 12 - sdata(170, prm_921) / 5;
    }
    if (i_at_m157 < 4)
    {
        i_at_m157 = 4;
    }
    if (gdata_mount != 0)
    {
        i_at_m157 += 4;
    }
    if (prm_920 == 441)
    {
        i_at_m157 += sdata(prm_920, prm_921);
    }
    if (prm_920 == 464)
    {
        i_at_m157 += sdata(prm_920, prm_921) / 3;
    }
    p_at_m157 = 90 + sdata(prm_920, prm_921)
        - sdataref(4, prm_920) * i_at_m157 / (5 + sdata(172, prm_921) * 4);
    if (f_at_m157 == 169)
    {
        if (p_at_m157 > 80)
        {
            p_at_m157 = 80;
        }
    }
    else if (f_at_m157 == 170)
    {
        if (p_at_m157 > 92)
        {
            p_at_m157 = 92;
        }
    }
    else if (p_at_m157 > 100)
    {
        p_at_m157 = 100;
    }
    if (cdata[prm_921].equipment_type & 4)
    {
        p_at_m157 -= 6;
    }
    if (cdata[prm_921].equipment_type & 1)
    {
        p_at_m157 -= 12;
    }
    if (p_at_m157 < 0)
    {
        p_at_m157 = 0;
    }
    return p_at_m157;
}



int calcspellcostmp(int prm_922, int prm_923)
{
    if (debug::voldemort)
    {
        return 1;
    }

    int cost_at_m158 = 0;
    if (prm_923 == 0)
    {
        if (prm_922 == 413 || prm_922 == 461 || prm_922 == 457 || prm_922 == 438
            || prm_922 == 409 || prm_922 == 408 || prm_922 == 410
            || prm_922 == 466)
        {
            cost_at_m158 = sdataref(2, prm_922);
            return cost_at_m158;
        }
        cost_at_m158 =
            sdataref(2, prm_922) * (100 + sdata(prm_922, prm_923) * 3) / 100
            + sdata(prm_922, prm_923) / 8;
    }
    else
    {
        cost_at_m158 =
            sdataref(2, prm_922) * (50 + cdata[prm_923].level * 3) / 100;
    }
    return cost_at_m158;
}



int calcspellcoststock(int prm_924, int prm_925)
{
    int cost_at_m159 = 0;
    cost_at_m159 =
        sdataref(2, prm_924) * 200 / (sdata(prm_924, prm_925) * 3 + 100);
    if (cost_at_m159 < sdataref(2, prm_924) / 5)
    {
        cost_at_m159 = sdataref(2, prm_924) / 5;
    }
    cost_at_m159 = rnd(cost_at_m159 / 2 + 1) + cost_at_m159 / 2;
    if (cost_at_m159 < 1)
    {
        cost_at_m159 = 1;
    }
    return cost_at_m159;
}



int calcscore()
{
    p = cdata[0].level * cdata[0].level
        + gdata_deepest_dungeon_level * gdata_deepest_dungeon_level
        + gdata_kill_count;
    if (gdata_death_count > 1)
    {
        p = p / 10 + 1;
    }
    if (gdata_wizard)
    {
        p = 0;
    }
    return p;
}



void calcpartyscore()
{
    p = 0;
    {
        int cnt = 57;
        for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            if (cdata[cnt].impression >= 53)
            {
                p += cdata[cnt].level + 5;
            }
            if (cdata[cnt].impression < 50)
            {
                p -= 20;
            }
        }
    }
    if (p > qdata(13, gdata_executing_immediate_quest))
    {
        txtef(4);
        txt(u8"(+"s + (p - qdata(13, gdata_executing_immediate_quest))
            + u8") "s);
    }
    if (p < qdata(13, gdata_executing_immediate_quest))
    {
        txtef(3);
        txt(u8"("s + (p - qdata(13, gdata_executing_immediate_quest))
            + u8") "s);
    }
    qdata(13, gdata_executing_immediate_quest) = p;
    return;
}



void calcpartyscore2()
{
    p = 0;
    {
        int cnt = 57;
        for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            if (cdata[cnt].impression >= 53)
            {
                if (cdata[cnt].quality >= 4)
                {
                    p += 20 + cdata[cnt].level / 2;
                    txt(lang(
                        cdatan(0, cnt) + u8"は満足した。"s,
                        cdatan(0, cnt) + u8" "s + is(cnt) + u8" satisfied."s));
                }
            }
        }
    }
    if (p != 0)
    {
        txt(lang(
            u8"(合計ボーナス:"s + p + u8"%) "s,
            u8"(Total Bonus:"s + p + u8"%)"s));
    }
    qdata(13, gdata_executing_immediate_quest) =
        qdata(13, gdata_executing_immediate_quest) * (100 + p) / 100;
    return;
}



} // namespace elona
