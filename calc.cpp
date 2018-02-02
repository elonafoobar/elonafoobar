#include "elona.hpp"
#include "variables.hpp"



namespace elona
{


void calcbuff(int prm_266, int prm_267, int prm_268)
{
    elona_vector1<int> p_at_m8;
    if (prm_267 >= 20 && prm_267 <= 28)
    {
        dur = 10 + prm_268 / 10;
        p_at_m8 = prm_268;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    skillname(prm_267 - 20 + 10) + u8"の成長率を"s + p_at_m8
                        + u8"%上昇"s,
                    u8"Increases the growth rate "s
                        + skillname((prm_267 - 20 + 10)) + u8" by "s + p_at_m8
                        + ""s);
                return;
            }
        }
        cdata(270 + (prm_267 - 20 + 10) - 10, prm_266) = p_at_m8;
        return;
    }
    if (prm_267 == 1)
    {
        dur = 10 + prm_268 / 10;
        p_at_m8 = 25 + prm_268 / 15;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"PVを"s + p_at_m8 + u8"上昇/耐恐怖"s,
                    u8"Increases PV by "s + p_at_m8 + u8"/RES+ fear"s);
                return;
            }
        }
        cdata_pv(prm_266) += p_at_m8;
        cdata_fear(prm_266) = 0;
        return;
    }
    if (prm_267 == 2)
    {
        dur = 5 + prm_268 / 40;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"魔法の使用を禁止"s, u8"Inhibits casting"s);
                return;
            }
        }
        return;
    }
    if (prm_267 == 3)
    {
        dur = 12 + prm_268 / 20;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"自然回復強化"s, u8"Enhances regeneration"s);
                return;
            }
        }
        sdata(154, prm_266) += 40;
        return;
    }
    if (prm_267 == 4)
    {
        dur = 4 + prm_268 / 6;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"炎冷気電撃耐性の獲得"s, u8"RES+ fire,cold,lightning"s);
                return;
            }
        }
        sdata(50, prm_266) += 100;
        sdata(51, prm_266) += 100;
        sdata(52, prm_266) += 100;
        return;
    }
    if (prm_267 == 5)
    {
        p_at_m8 = 50 + std::sqrt(prm_268 / 5);
        dur = 8 + prm_268 / 30;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の加速"s,
                    u8"Increases speed by "s + p_at_m8);
                return;
            }
        }
        sdata(18, prm_266) += p_at_m8;
        return;
    }
    if (prm_267 == 6)
    {
        p_at_m8 = 20 + prm_268 / 20;
        if (p_at_m8 > 50)
        {
            p_at_m8 = 50;
        }
        dur = 8 + prm_268 / 30;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の鈍足"s,
                    u8"Decreases speed by "s + p_at_m8);
                return;
            }
        }
        sdata(18, prm_266) -= p_at_m8;
        return;
    }
    if (prm_267 == 7)
    {
        dur = 10 + prm_268 / 4;
        p_at_m8 = 5 + prm_268 / 30;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"筋力・器用を"s + p_at_m8 + u8"上昇/耐恐怖/耐混乱"s,
                    u8"Increases STR,DEX by "s + p_at_m8
                        + u8"/RES+ fear,confusion"s);
                return;
            }
        }
        sdata(10, prm_266) += p_at_m8;
        sdata(12, prm_266) += p_at_m8;
        cdata_fear(prm_266) = 0;
        cdata_confused(prm_266) = 0;
        return;
    }
    if (prm_267 == 8)
    {
        p_at_m8(0) = 30 + prm_268 / 10;
        p_at_m8(1) = 5 + prm_268 / 15;
        dur = 6 + prm_268 / 10;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"DVとPVを半減"s, u8"Halves DV and PV"s);
                return;
            }
        }
        cdata_dv(prm_266) = cdata_dv(prm_266) / 2;
        cdata_pv(prm_266) = cdata_pv(prm_266) / 2;
        return;
    }
    if (prm_267 == 9)
    {
        dur = 4 + prm_268 / 15;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"炎冷気電撃耐性の減少"s, u8"RES- fire,cold,lightning"s);
                return;
            }
        }
        sdata(50, prm_266) = std::clamp(
            sdata(50, prm_266) + -100, int{sdata(50, prm_266) > 0}, 9999);
        sdata(51, prm_266) = std::clamp(
            sdata(51, prm_266) + -100, int{sdata(51, prm_266) > 0}, 9999);
        sdata(52, prm_266) = std::clamp(
            sdata(52, prm_266) + -100, int{sdata(52, prm_266) > 0}, 9999);
        return;
    }
    if (prm_267 == 10)
    {
        p_at_m8 = 50 + prm_268 / 3 * 2;
        dur = 15 + prm_268 / 5;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"ﾊﾟﾜｰ"s + p_at_m8 + u8"の呪い(hex)への抵抗"s,
                    u8"grants hex protection(power:"s + p_at_m8 + u8")"s);
                return;
            }
        }
        return;
    }
    if (prm_267 == 11)
    {
        dur = 4 + prm_268 / 15;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"神経幻影耐性の減少"s, u8"RES- mind,nerve"s);
                return;
            }
        }
        sdata(58, prm_266) = std::clamp(
            sdata(58, prm_266) + -100, int{sdata(58, prm_266) > 0}, 9999);
        sdata(54, prm_266) = std::clamp(
            sdata(54, prm_266) + -100, int{sdata(54, prm_266) > 0}, 9999);
        return;
    }
    if (prm_267 == 12)
    {
        dur = 10 + prm_268 / 4;
        p_at_m8(0) = 6 + prm_268 / 40;
        p_at_m8(1) = 3 + prm_268 / 100;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"習得・魔力を"s + p_at_m8 + u8"上昇/読書を"s + p_at_m8(1)
                        + u8"上昇"s,
                    u8"Increases LER,MAG by "s + p_at_m8
                        + u8", literacy skill by "s + p_at_m8(1));
                return;
            }
        }
        sdata(14, prm_266) += p_at_m8;
        sdata(16, prm_266) += p_at_m8;
        sdata(150, prm_266) += p_at_m8(1);
        return;
    }
    if (prm_267 == 13)
    {
        p_at_m8 = 20;
        dur = prm_268;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の鈍足/PVを20%減少"s,
                    u8"Decreases speed by "s + p_at_m8 + u8", PV by 20%"s);
                return;
            }
        }
        sdata(18, prm_266) -= p_at_m8;
        if (cdata_pv(prm_266) > 1)
        {
            cdata_pv(prm_266) -= cdata_pv(prm_266) / 5;
        }
        return;
    }
    if (prm_267 == 14)
    {
        p_at_m8 = 155 + prm_268 / 5;
        dur = 7;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の加速"s,
                    u8"Increases speed by "s + p_at_m8);
                return;
            }
        }
        sdata(18, prm_266) += p_at_m8;
        return;
    }
    if (prm_267 == 15)
    {
        dur = 4 + prm_268 / 40;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"変装"s, u8"Grants new identify"s);
                return;
            }
        }
        cbitmod(16, prm_266, 1);
        return;
    }
    if (prm_267 == 16)
    {
        dur = 20;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    u8"呪いが完了したときに確実なる死"s,
                    u8"Guaranteed death when the hex ends"s);
                return;
            }
        }
        cbitmod(973, prm_266, 1);
        return;
    }
    if (prm_267 == 17)
    {
        p_at_m8 = 120;
        dur = 5;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の加速と能力のアップ"s,
                    u8"Increases speed by "s + p_at_m8
                        + u8"/Boosts physical attributes"s);
                return;
            }
        }
        sdata(18, prm_266) += p_at_m8;
        sdata(10, prm_266) = sdata(10, prm_266) * 150 / 100 + 10;
        sdata(12, prm_266) = sdata(12, prm_266) * 150 / 100 + 10;
        sdata(154, prm_266) += 50;
        cdata_pv(prm_266) = cdata_pv(prm_266) * 150 / 100 + 25;
        cdata_dv(prm_266) = cdata_dv(prm_266) * 150 / 100 + 25;
        cdata_hit_bonus(prm_266) = cdata_hit_bonus(prm_266) * 150 / 100 + 50;
        return;
    }
    if (prm_267 == 18)
    {
        dur = 66;
        p_at_m8 = std::clamp(25 + prm_268 / 17, 25, 80);
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(u8"致命傷を負ったとき"s + p_at_m8 +
                        u8"%の確率でダメージ分回復。"s,
                    ""s + p_at_m8 +
                        u8"% chances taking a lethal damage heals you instead"s);
                return;
            }
        }
        cbitmod(980, prm_266, 1);
        return;
    }
    if (prm_267 == 19)
    {
        p_at_m8 = prm_268;
        dur = 777;
        if (prm_266 < 0)
        {
            if (prm_266 == -1)
            {
                return;
            }
            else
            {
                buffdesc = lang(
                    ""s + p_at_m8 + u8"の幸運の上昇"s,
                    u8"Increase luck by "s + p_at_m8 + u8"."s);
                return;
            }
        }
        sdata(19, prm_266) += p_at_m8;
        return;
    }
    return;
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
        dice2 = cdata_piety_point(prm_270) / 70 + 1 + 1;
        bonus = 0;
        ele = 0;
        elep = 0;
        return 1;
    }
    if (prm_269 == 624)
    {
        dice1 = 1 + rs_at_m9 / 20;
        dice2 = cdata_piety_point(prm_270) / 140 + 1 + 1;
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



int calcobjlv(int prm_443)
{
    int objlv_at_m43 = 0;
    if (prm_443 <= 0)
    {
        objlv_at_m43 = gdata_current_dungeon_level;
    }
    else
    {
        objlv_at_m43 = prm_443;
    }
    if (gdata_current_map == 30)
    {
        objlv_at_m43 = 1;
    }
    {
        int cnt = 1;
        for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
        {
            p_at_m43 = rnd(30 + cnt * 5);
            if (p_at_m43 == 0)
            {
                objlv_at_m43 += rnd(10 * cnt);
                continue;
            }
            break;
        }
    }
    if (prm_443 <= 3)
    {
        if (rnd(4) != 0)
        {
            objlv_at_m43 = rnd(3) + 1;
        }
    }
    return objlv_at_m43;
}



int calcfixlv(int prm_444)
{
    int fixlv_at_m43 = 0;
    if (prm_444 == 0)
    {
        fixlv_at_m43 = 2;
    }
    else
    {
        fixlv_at_m43 = prm_444;
    }
    {
        int cnt = 1;
        for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
        {
            p_at_m43 = rnd(30 + cnt * 5);
            if (p_at_m43 == 0)
            {
                ++fixlv_at_m43;
                continue;
            }
            if (p_at_m43 < 3)
            {
                --fixlv_at_m43;
                continue;
            }
            break;
        }
    }
    if (fixlv_at_m43 < 1)
    {
        fixlv_at_m43 = 1;
    }
    if (fixlv_at_m43 > 5)
    {
        fixlv_at_m43 = 5;
    }
    return fixlv_at_m43;
}



int calcfame(int prm_574, int prm_575)
{
    p_at_m77 = prm_575 * 100
        / (100
           + cdata_fame(prm_574) / 100 * (cdata_fame(prm_574) / 100) / 2500);
    if (p_at_m77 < 5)
    {
        p_at_m77 = rnd(5) + 1;
    }
    return p_at_m77;
}



int decfame(int prm_576, int prm_577)
{
    p_at_m77 = cdata_fame(prm_576) / prm_577 + 5;
    p_at_m77 = p_at_m77 + rnd(p_at_m77 / 2) - rnd(p_at_m77 / 2);
    cdata_fame(prm_576) -= p_at_m77;
    if (cdata_fame(prm_576) < 0)
    {
        cdata_fame(prm_576) = 0;
    }
    return p_at_m77;
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
    if (gdata_year - cdata_birth_year(prm_762) < 0)
    {
        return lang(u8"不明"s, u8"Unknown"s);
    }
    return std::to_string(gdata_year - cdata_birth_year(prm_762));
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
        tohitfix = sdata(12, cc) / 5 + sdata(10, cc) / 10 + cdata_hit_bonus(cc);
        pierce = std::clamp(sdata(attackskill, cc) / 5, 5, 50);
        if (cdata_equipment_type(cc) & 1)
        {
            tohitorg = tohitorg * 100 / 130;
        }
    }
    else
    {
        tohitorg = sdata(12, cc) / 4 + sdata(inv_skill(cw), cc) / 3
            + sdata(attackskill, cc) + 50;
        tohitfix = cdata_hit_bonus(cc) + inv_hit_bonus(cw);
        if (ammo != -1)
        {
            tohitfix += inv_hit_bonus(ammo);
        }
        calcweaponfix(inv_id(cw));
    }
    tohit = tohitorg + tohitfix;
    if (attackskill != 106)
    {
        if (attackrange)
        {
            if (prm_893 == 0)
            {
                rangedist = std::clamp(
                    dist(cdata_x(cc), cdata_y(cc), cdata_x(tc), cdata_y(tc))
                        - 1,
                    0,
                    9);
                tohi = tohit * rangemap(rangedist) / 100;
            }
        }
        else
        {
            if (cdata_equipment_type(cc) & 2)
            {
                tohit += 25;
                if (inv_weight(cw) >= 4000)
                {
                    tohit += sdata(167, cc);
                }
            }
            if (cdata_equipment_type(cc) & 4)
            {
                if (attacknum == 1)
                {
                    if (inv_weight(cw) >= 4000)
                    {
                        tohit -= (inv_weight(cw) - 4000 + 400)
                            / (10 + sdata(166, cc) / 5);
                    }
                }
                else if (inv_weight(cw) > 1500)
                {
                    tohit -= (inv_weight(cw) - 1500 + 100)
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
                    if (inv_weight(cw) >= 4000)
                    {
                        tohit -= (inv_weight(cw) - 4000 + 400)
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
                    if (inv_weight(cw) >= 4000)
                    {
                        tohit -= (inv_weight(cw) - 4000 + 400)
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
    evade = sdata(13, tc) / 3 + sdata(173, tc) + cdata_dv(tc) + 25;
    if (prm_893 == 2)
    {
        return evade;
    }
    if (cdata_dimmed(tc) != 0)
    {
        if (rnd(4) == 0)
        {
            critical = 1;
            return 1;
        }
        evade /= 2;
    }
    if (cdata_blind(cc) != 0)
    {
        tohit /= 2;
    }
    if (cdata_blind(tc) != 0)
    {
        evade /= 2;
    }
    if (cdata_sleep(tc) != 0)
    {
        return 1;
    }
    if (cdata_confused(cc) != 0 || cdata_dimmed(cc) != 0)
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
    if (cdata_rate_of_critical_hit(cc) > rnd(200))
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
            sdata(10, cc) / 8 + sdata(106, cc) / 8 + cdata_damage_bonus(cc);
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
        dmgfix = cdata_damage_bonus(cc) + inv_damage_bonus(cw)
            + inv_enhancement(cw) + (inv_curse_state(cw) == 1);
        dice1 = inv_dice_x(cw);
        dice2 = inv_dice_y(cw);
        if (ammo != -1)
        {
            dmgfix += inv_damage_bonus(ammo)
                + inv_dice_x(ammo) * inv_dice_y(ammo) / 2;
            dmgmulti = 0.5
                + double(
                      (sdata(13, cc) + sdata(inv_skill(cw), cc) / 5
                       + sdata(attackskill, cc) / 5 + sdata(189, cc) * 3 / 2))
                    / 40;
        }
        else
        {
            dmgmulti = 0.6
                + double(
                      (sdata(10, cc) + sdata(inv_skill(cw), cc) / 5
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
    else if (cdata_equipment_type(cc) & 2)
    {
        if (inv_weight(cw) >= 4000)
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
            dmgfix += 5 + cdata_level(0) * 2 / 3;
        }
    }
    if (prm_894 == 1)
    {
        return damage;
    }
    prot = cdata_pv(tc) + sdata(carmor(tc), tc) + sdata(12, tc) / 10;
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
                * std::clamp((inv_weight(ammo) / 100 + 100), 100, 150) / 100;
        }
        else
        {
            dmgmulti = dmgmulti
                * std::clamp((inv_weight(cw) / 200 + 100), 100, 150) / 100;
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
        if (cdata_rate_to_pierce(cc) > rnd(100))
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
    if (cdata_decrease_physical_damage(tc) != 0)
    {
        damage = damage * 100
            / std::clamp((100 + cdata_decrease_physical_damage(tc)), 25, 1000);
    }
    if (damage < 0)
    {
        damage = 0;
    }
    return damage;
}



int calcmedalvalue(int prm_897)
{
    if (inv_id(prm_897) == 430)
    {
        return 5;
    }
    if (inv_id(prm_897) == 431)
    {
        return 8;
    }
    if (inv_id(prm_897) == 502)
    {
        return 7;
    }
    if (inv_id(prm_897) == 480)
    {
        return 20;
    }
    if (inv_id(prm_897) == 421)
    {
        return 15;
    }
    if (inv_id(prm_897) == 603)
    {
        return 20;
    }
    if (inv_id(prm_897) == 615)
    {
        return 5;
    }
    if (inv_id(prm_897) == 559)
    {
        return 10;
    }
    if (inv_id(prm_897) == 516)
    {
        return 3;
    }
    if (inv_id(prm_897) == 616)
    {
        return 18;
    }
    if (inv_id(prm_897) == 623)
    {
        return 85;
    }
    if (inv_id(prm_897) == 624)
    {
        return 25;
    }
    if (inv_id(prm_897) == 505)
    {
        return 12;
    }
    if (inv_id(prm_897) == 625)
    {
        return 11;
    }
    if (inv_id(prm_897) == 626)
    {
        return 30;
    }
    if (inv_id(prm_897) == 627)
    {
        return 55;
    }
    if (inv_id(prm_897) == 56)
    {
        return 65;
    }
    if (inv_id(prm_897) == 742)
    {
        return 72;
    }
    if (inv_id(prm_897) == 760)
    {
        return 94;
    }
    return 1;
}



int calcitemvalue(int prm_898, int prm_899)
{
    int reftype_at_m153 = 0;
    int limitvalue_at_m153 = 0;
    reftype_at_m153 = refitem(inv_id(prm_898), 5);
    if (inv_identification_state(prm_898) == 0)
    {
        if (prm_899 == 2)
        {
            value_at_m153 = inv_value(prm_898) * 4 / 10;
        }
        else
        {
            value_at_m153 = cdata_level(0) / 5
                    * ((gdata_random_seed + prm_898 * 31) % cdata_level(0) + 4)
                + 10;
        }
    }
    else if (reftype_at_m153 >= 50000)
    {
        value_at_m153 = inv_value(prm_898);
    }
    else
    {
        if (inv_identification_state(prm_898) == 1)
        {
            value_at_m153 = inv_value(prm_898) * 2 / 10;
        }
        if (inv_identification_state(prm_898) == 2)
        {
            value_at_m153 = inv_value(prm_898) * 5 / 10;
        }
        if (inv_identification_state(prm_898) >= 3)
        {
            value_at_m153 = inv_value(prm_898);
        }
    }
    if (inv_identification_state(prm_898) >= 3)
    {
        if (inv_curse_state(prm_898) == 1)
        {
            value_at_m153 = value_at_m153 * 120 / 100;
        }
        if (inv_curse_state(prm_898) == -1)
        {
            value_at_m153 = value_at_m153 / 2;
        }
        if (inv_curse_state(prm_898) == -2)
        {
            value_at_m153 = value_at_m153 / 5;
        }
    }
    if (reftype_at_m153 == 57000)
    {
        if (inv_param2(prm_898) > 0)
        {
            value_at_m153 =
                value_at_m153 * inv_param2(prm_898) * inv_param2(prm_898) / 10;
        }
    }
    if (inv_id(prm_898) == 333)
    {
        if (prm_899 == 0)
        {
            value_at_m153 += std::clamp(
                cdata_fame(0) / 40 + value_at_m153 * (cdata_fame(0) / 80) / 100,
                0,
                800);
        }
    }
    if (inv_weight(prm_898) < 0)
    {
        if (mode == 6)
        {
            if (reftype_at_m153 == 92000)
            {
                value_at_m153 =
                    value_at_m153 * trate(inv_param1(prm_898)) / 100;
                if (prm_899 == 1)
                {
                    value_at_m153 = value_at_m153 * 65 / 100;
                }
                return value_at_m153;
            }
        }
    }
    if (ibit(4, prm_898) == 1)
    {
        dbid = inv_id(prm_898);
        dbmode = 2;
        label_1275();
        if (inv_count(prm_898) < 0)
        {
            value_at_m153 = value_at_m153 / 10;
        }
        else if (reftype_at_m153 == 54000)
        {
            value_at_m153 = value_at_m153 / 5
                + value_at_m153 * inv_count(prm_898) / (ichargelevel * 2 + 1);
        }
        else
        {
            value_at_m153 = value_at_m153 / 2
                + value_at_m153 * inv_count(prm_898) / (ichargelevel * 3 + 1);
        }
    }
    if (reftype_at_m153 == 72000)
    {
        if (inv_param1(prm_898) == 0)
        {
            value_at_m153 = value_at_m153 / 100 + 1;
        }
    }
    if (prm_899 == 0)
    {
        limitvalue_at_m153 = value_at_m153 / 2;
        value_at_m153 = value_at_m153 * 100 / (100 + sdata(156, 0));
        if (gdata_belongs_to_mages_guild != 0)
        {
            if (reftype_at_m153 == 54000)
            {
                value_at_m153 = value_at_m153 * 80 / 100;
            }
        }
        if (value_at_m153 <= limitvalue_at_m153)
        {
            value_at_m153 = limitvalue_at_m153;
        }
    }
    if (prm_899 == 1)
    {
        limitvalue_at_m153 = sdata(156, 0) * 250 + 5000;
        if (value_at_m153 / 3 < limitvalue_at_m153)
        {
            limitvalue_at_m153 = value_at_m153 / 3;
        }
        value_at_m153 = value_at_m153 * (100 + sdata(156, 0) * 5) / 1000;
        if (reftype_at_m153 < 50000)
        {
            value_at_m153 /= 20;
        }
        if (ibit(9, prm_898))
        {
            if (gdata_belongs_to_thieves_guild == 0)
            {
                value_at_m153 /= 10;
            }
            else
            {
                value_at_m153 = value_at_m153 / 3 * 2;
            }
        }
        if (value_at_m153 >= limitvalue_at_m153)
        {
            value_at_m153 = limitvalue_at_m153;
        }
    }
    if (prm_899 == 2)
    {
        value_at_m153 = value_at_m153 / 5;
        if (reftype_at_m153 < 50000)
        {
            value_at_m153 /= 3;
        }
        if (value_at_m153 > 15000)
        {
            value_at_m153 = 15000;
        }
        if (ibit(9, prm_898))
        {
            value_at_m153 = 1;
        }
    }
    if (value_at_m153 <= 0)
    {
        value_at_m153 = 1;
    }
    return value_at_m153;
}



int calcinvestvalue(int)
{
    value_at_m153 = std::clamp(cdata_shop_rank(tc), 1, 200)
            * std::clamp(cdata_shop_rank(tc), 1, 200) * 15
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
        (-cdata_karma(0) + -30) * (cdata_fame(0) / 2 + cdata_level(0) * 200);
    return value_at_m153;
}



int calchireadv(int prm_902)
{
    return 250 + cdata_level(prm_902) * cdata_level(prm_902) * 30;
}



int calchirecost(int prm_903)
{
    value_at_m153 = 0;
    if (cdata_character_role(prm_903) == 18)
    {
        value_at_m153 = 450;
    }
    if (cdata_character_role(prm_903) == 7)
    {
        value_at_m153 = 250;
    }
    if (cdata_character_role(prm_903) == 9)
    {
        value_at_m153 = 350;
    }
    if (cdata_character_role(prm_903) == 12)
    {
        value_at_m153 = 500;
    }
    if (cdata_character_role(prm_903) == 5)
    {
        value_at_m153 = 750;
    }
    if (cdata_character_role(prm_903) == 8)
    {
        value_at_m153 = 250;
    }
    if (cdata_character_role(prm_903) == 14)
    {
        value_at_m153 = 50;
    }
    if (cdata_character_role(prm_903) >= 1000
            && cdata_character_role(prm_903) < 2000
        || cdata_character_role(prm_903) == 2003)
    {
        value_at_m153 = 1000;
        if (cdata_character_role(prm_903) == 1007)
        {
            value_at_m153 *= 4;
        }
        if (cdata_character_role(prm_903) == 2003)
        {
            value_at_m153 = 0;
        }
    }
    return value_at_m153;
}



void generatemoney(int prm_904)
{
    p_at_m153 = rnd(100) + rnd((cdata_level(prm_904) * 50 + 1));
    if (cdata_character_role(prm_904) >= 1000
            && cdata_character_role(prm_904) < 2000
        || cdata_character_role(prm_904) == 2003)
    {
        p_at_m153 += 2500 + cdata_shop_rank(prm_904) * 250;
    }
    if (cdata_gold(prm_904) < p_at_m153 / 2)
    {
        cdata_gold(prm_904) = p_at_m153;
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
            if (cdata_character_role(cnt) == 0)
            {
                continue;
            }
            if (cdata_state(cnt) != 1)
            {
                continue;
            }
            cost_at_m153 += calchirecost(cnt);
        }
    }
    cost_at_m153 = cost_at_m153
        * std::clamp((100 - std::clamp(cdata_karma(0) / 2, 0, 50)
                      - 7 * trait(38) - (cdata_karma(0) >= 20) * 5),
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
        * std::clamp((100 - std::clamp(cdata_karma(0) / 2, 0, 50)
                      - 7 * trait(38) - (cdata_karma(0) >= 20) * 5),
                     25,
                     200)
        / 100;
    return cost_at_m153;
}



int calccosttax()
{
    cost_at_m153 = 0;
    cost_at_m153 += cdata_gold(0) / 1000;
    cost_at_m153 += cdata_fame(0);
    cost_at_m153 += cdata_level(0) * 200;
    cost_at_m153 = cost_at_m153
        * std::clamp((100 - std::clamp(cdata_karma(0) / 2, 0, 50)
                      - 7 * trait(38) - (cdata_karma(0) >= 20) * 5),
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
            if (inv_number(cnt) == 0)
            {
                continue;
            }
            if (refitem(inv_id(cnt), 5) != 25000)
            {
                continue;
            }
            ci_at_m153 = cnt;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt)
                {
                    if (inv_enchantment_id(ci_at_m153, cnt) == 0)
                    {
                        break;
                    }
                    enc_at_m153 = inv_enchantment_id(ci_at_m153, cnt);
                    i_at_m153 = enc_at_m153 / 10000;
                    if (i_at_m153 != 0)
                    {
                        enc_at_m153 = enc_at_m153 % 10000;
                        if (i_at_m153 == 9)
                        {
                            i_at_m153(0) =
                                inv_enchantment_power(ci_at_m153, cnt) % 1000;
                            i_at_m153(1) =
                                inv_enchantment_power(ci_at_m153, cnt) / 1000;
                            cost_at_m153 += (i_at_m153(1) - i_at_m153)
                                * (50 + enc_at_m153 * enc_at_m153 * 10);
                            if (prm_906 == 1)
                            {
                                inv_enchantment_power(ci_at_m153, cnt) =
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
                if (inv_number(cnt) == 0)
                {
                    continue;
                }
                if (inv_identification_state(cnt) < 3)
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
    value_at_m153 = sorg(prm_908, prm_909) / 5 + 2;
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
    if (cdata_state(prm_914) != 6)
    {
        return 100;
    }
    value_at_m153 = cdata_level(prm_914) * cdata_level(prm_914) * 15;
    return value_at_m153;
}



int calcslavevalue(int prm_915)
{
    value_at_m153 = sdata(10, prm_915) * sdata(11, prm_915)
        + cdata_level(prm_915) * cdata_level(prm_915) + 1000;
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
    if (cdata_id(prm_917) == 183)
    {
        lootrich_at_m155 = 10;
    }
    if (cdata_id(prm_917) == 184)
    {
        lootrich_at_m155 = 4;
    }
    if (cdata_id(prm_917) == 185)
    {
        lootrich_at_m155 = 2;
    }
    if (lootrich_at_m155 != -1)
    {
        return lootrich_at_m155 * 500 + rnd((1000 + lootrich_at_m155 * 1000));
    }
    return rnd(cdata_level(prm_917) * 25 + 10) + 1;
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
            return cdata_level(prm_919) * 6 + 10;
        }
    }
    return sdata(172, prm_919) * 6 + 10;
}



int calcspellfail(int prm_920, int prm_921)
{
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
    if (cdata_equipment_type(prm_921) & 4)
    {
        p_at_m157 -= 6;
    }
    if (cdata_equipment_type(prm_921) & 1)
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
            sdataref(2, prm_922) * (50 + cdata_level(prm_923) * 3) / 100;
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
    p = cdata_level(0) * cdata_level(0)
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
            if (cdata_state(cnt) != 1)
            {
                continue;
            }
            if (cdata_impression(cnt) >= 53)
            {
                p += cdata_level(cnt) + 5;
            }
            if (cdata_impression(cnt) < 50)
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
            if (cdata_state(cnt) != 1)
            {
                continue;
            }
            if (cdata_impression(cnt) >= 53)
            {
                if (cdata_quality(cnt) >= 4)
                {
                    p += 20 + cdata_level(cnt) / 2;
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
