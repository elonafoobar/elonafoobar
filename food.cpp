#include "food.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "variables.hpp"

namespace elona
{

int cieat = 0;
int nutrition = 0;
int fdmax = 0;
elona_vector2<int> fdlist;

void continuous_action_eating()
{
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 1;
        cdata[cc].continuous_action_turn = 8;
        cdata[cc].continuous_action_item = ci;
        if (is_in_fov(cc))
        {
            snd(18);
            if (inv[ci].own_state == 1 && cc < 16)
            {
                txt(lang(
                    name(cc) + u8"は"s + itemname(ci, 1)
                        + u8"をこっそりと口に運んだ。"s,
                    name(cc) + u8" start"s + _s(cc) + u8" to eat "s
                        + itemname(ci, 1) + u8" in secret."s));
            }
            else
            {
                txt(lang(
                    name(cc) + u8"は"s + itemname(ci, 1) + u8"を口に運んだ。"s,
                    name(cc) + u8" start"s + _s(cc) + u8" to eat "s
                        + itemname(ci, 1) + u8"."s));
            }
            if (inv[ci].id == 204 && inv[ci].subname == 344)
            {
                txt(lang(u8"「いただきマンモス」"s, u8"\"Let's eatammoth.\""s));
            }
        }
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        return;
    }
    if (is_in_fov(cc))
    {
        txt(lang(
            npcn(cc) + itemname(ci, 1) + u8"を食べ終えた。"s,
            name(cc) + u8" "s + have(cc) + u8" finished eating "s
                + itemname(ci, 1) + u8"."s));
    }
    continuous_action_eating_finish();
    rowactend(cc);
    return;
}



void continuous_action_eating_finish()
{
    cieat = ci;
    apply_general_eating_effect();
    ci = cieat;
    if (cc == 0)
    {
        item_identify(inv[ci], identification_state_t::partly_identified);
    }
    if (chara_unequip(ci))
    {
        chara_refresh(cc);
    }
    --inv[ci].number;
    if (ci >= 5080)
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
    }
    else if (cc == 0)
    {
        refresh_burden_state();
    }
    if (cc == 0)
    {
        show_eating_message();
    }
    else
    {
        if (ci == cdata[cc].item_which_will_be_used)
        {
            cdata[cc].item_which_will_be_used = 0;
        }
        if (cdata[cc].was_passed_item_by_you_just_now())
        {
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    txtef(9);
                    if (jp)
                    {
                        txt(u8"「うぐぐ！なんだこの飯は！」"s,
                            u8"「うっ！」"s,
                            u8"「……！！」"s,
                            u8"「あれれ…」"s,
                            u8"「…これは何の嫌がらせですか」"s,
                            u8"「まずい！」"s);
                    }
                    if (en)
                    {
                        txt(u8"\"Yuck!!\""s,
                            u8"\"....!!\""s,
                            u8"\"W-What...\""s,
                            u8"\"Are you teasing me?\""s,
                            u8"\"You fool!\""s);
                    }
                    dmghp(cc, 999, -12);
                    if (cdata[cc].state != 1)
                    {
                        if (cdata[cc].relationship > 0)
                        {
                            modify_karma(0, -5);
                        }
                        else
                        {
                            modify_karma(0, -1);
                        }
                    }
                    chara_mod_impression(tc, -25);
                    return;
                }
            }
        }
    }
    chara_anorexia(cc);
    if ((inv[ci].id == 755 && rnd(3)) || (inv[ci].id == 756 && rnd(10) == 0))
    {
        if (is_in_fov(cc))
        {
            txtef(8);
            txt(lang(
                name(cc) + u8"はもちを喉につまらせた！"s,
                name(cc) + u8" choke"s + _s(cc) + u8" on mochi!"s));
            txt(lang(u8"「むがっ」"s, u8"\"Mm-ghmm\""s));
        }
        ++cdata[cc].choked;
    }
    return;
}



void show_eating_message()
{
    txtef(2);
    if (cdata[cc].nutrition >= 12000)
    {
        txt(lang(
                u8"もう当分食べなくてもいい。"s,
                u8"Phew! You are pretty bloated."s),
            lang(
                u8"こんなに食べたことはない！"s,
                u8"You've never eaten this much before!"s),
            lang(
                u8"信じられないぐらい満腹だ！"s,
                u8"Your stomach is unbelievably full!"s));
        return;
    }
    if (cdata[cc].nutrition >= 10000)
    {
        txt(lang(u8"あなたは満足した。"s, u8"You are satisfied!"s),
            lang(u8"満腹だ！"s, u8"This hearty meal has filled your stomach."s),
            lang(u8"あなたは食欲を満たした。"s, u8"You really ate!"s),
            lang(
                u8"あなたは幸せそうに腹をさすった。"s,
                u8"You pat your stomach contentedly."s));
        return;
    }
    if (cdata[cc].nutrition >= 5000)
    {
        txt(lang(u8"まだ食べられるな…"s, u8"You can eat more."s),
            lang(u8"あなたは腹をさすった。"s, u8"You pat your stomach."s),
            lang(
                u8"少し食欲を満たした。"s,
                u8"You satisfied your appetite a little."s));
        return;
    }
    if (cdata[cc].nutrition >= 2000)
    {
        txt(lang(u8"まだまだ食べたりない。"s, u8"You are still a bit hungry."s),
            lang(u8"物足りない…"s, u8"Not enough..."s),
            lang(u8"まだ空腹だ。"s, u8"You want to eat more."s),
            lang(
                u8"少しは腹の足しになったか…"s,
                u8"Your stomach is still somewhat empty."s));
        return;
    }
    if (cdata[cc].nutrition >= 1000)
    {
        txt(lang(u8"全然食べたりない！"s, u8"No, it was not enough at all."s),
            lang(u8"腹の足しにもならない。"s, u8"You still feel very hungry."s),
            lang(u8"すぐにまた腹が鳴った。"s, u8"You aren't satisfied."s));
        return;
    }
    txt(lang(
            u8"こんな量では意味がない！"s,
            u8"It didn't help you from starving!"s),
        lang(
            u8"これぐらいでは、死を少し先に延ばしただけだ。"s,
            u8"It prolonged your death for seconds."s),
        lang(
            u8"無意味だ…もっと栄養をとらなければ。"s,
            u8"Empty! Your stomach is still empty!"s));
    return;
}



void eat_rotten_food()
{
    if (cdata[cc].can_digest_rotten_food() == 1)
    {
        txt(lang(
            u8"しかし、"s + name(cc) + u8"は何ともなかった。"s,
            u8"But "s + name(cc) + your(cc) + u8" stomach isn't affected."s));
        return;
    }
    fdmax = 0;
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 10;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 11;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 17;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 16;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 12;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 13;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 14;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 15;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    nutrition = 1000;
    dmgcon(cc, status_ailment_t::paralyzed, 100);
    dmgcon(cc, status_ailment_t::confused, 200);
    return;
}



void cure_anorexia(int cc)
{
    if (cdata[cc].has_anorexia() == 0)
        return;

    cdata[cc].has_anorexia() = false;
    if (is_in_fov(cc) || cc < 16)
    {
        txt(lang(
            name(cc) + u8"の拒食症は治った。"s,
            name(cc) + u8" manage"s + _s(cc)
                + u8" to recover from anorexia."s));
        snd(65);
    }
}



void chara_vomit(int prm_876)
{
    int p_at_m146 = 0;
    ++cdata[prm_876].anorexia_count;
    if (is_in_fov(prm_876))
    {
        snd(104);
        txt(lang(
            name(prm_876) + u8"は吐いた。"s,
            name(prm_876) + u8" vomit"s + _s(prm_876) + u8"."s));
    }
    if (cdata[prm_876].is_pregnant())
    {
        cdata[prm_876].is_pregnant() = false;
        if (is_in_fov(prm_876))
        {
            txt(lang(
                name(prm_876) + u8"は体内のエイリアンを吐き出した！"s,
                name(prm_876) + u8" spit"s + _s(prm_876)
                    + u8" alien children from "s + his(prm_876) + u8" body!"s));
        }
    }
    if (cdata[prm_876].buffs[0].id != 0)
    {
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[prm_876].buffs[cnt].id == 0)
            {
                break;
            }
            if (the_buff_db[cdata[prm_876].buffs[cnt].id]->type
                == buff_data::type_t::food)
            {
                buff_delete(prm_876, cnt);
                --cnt;
                continue;
            }
        }
    }
    if (mdata(6) != 1)
    {
        p_at_m146 = 2;
        for (const auto& cnt : items(-1))
        {
            if (inv[cnt].number > 0)
            {
                if (inv[cnt].id == 704)
                {
                    ++p_at_m146;
                }
            }
        }
        if (rnd(p_at_m146 * p_at_m146 * p_at_m146) == 0 || prm_876 == 0)
        {
            flt();
            int stat = itemcreate(
                -1,
                704,
                cdata[prm_876].position.x,
                cdata[prm_876].position.y,
                0);
            if (stat != 0)
            {
                if (prm_876 != 0)
                {
                    inv[ci].subname = cdata[prm_876].id;
                }
            }
        }
    }
    if (cdata[prm_876].has_anorexia() == 0)
    {
        if ((prm_876 < 16 && cdata[prm_876].anorexia_count > 10)
            || (prm_876 >= 16 && rnd(4) == 0))
        {
            if (rnd(5) == 0)
            {
                cdata[prm_876].has_anorexia() = true;
                if (is_in_fov(prm_876))
                {
                    txt(lang(
                        name(prm_876) + u8"は拒食症になった。"s,
                        name(prm_876) + u8" develop"s + _s(prm_876)
                            + u8" anorexia."s));
                    snd(65);
                }
            }
        }
    }
    else
    {
        skillmod(10, prm_876, -50);
        skillmod(11, prm_876, -75);
        skillmod(17, prm_876, -100);
    }
    dmgcon(prm_876, status_ailment_t::dimmed, 100);
    modweight(prm_876, -(1 + rnd(5)));
    if (cdata[prm_876].nutrition <= 0)
    {
        dmghp(prm_876, 9999, -3);
    }
    cdata[prm_876].nutrition -= 3000;
    return;
}



void eatstatus(curse_state_t curse_state, int eater)
{
    if (cdata[eater].state != 1)
        return;

    if (is_cursed(curse_state))
    {
        cdata[eater].nutrition -= 1500;
        if (is_in_fov(eater))
        {
            txt(lang(
                name(eater) + u8"は嫌な感じがした。"s,
                name(eater) + u8" feel"s + _s(eater) + u8" bad."s));
        }
        chara_vomit(eater);
    }
    else if (curse_state == curse_state_t::blessed)
    {
        if (is_in_fov(eater))
        {
            txt(lang(
                name(eater) + u8"は良い予感がした。"s,
                name(eater) + u8" feel"s + _s(eater) + u8" good."s));
        }
        if (rnd(5) == 0)
        {
            buff_add(eater, 19, 100, 500 + rnd(500));
        }
        healsan(eater, 2);
    }
}



int chara_anorexia(int prm_879)
{
    if (cdata[prm_879].has_anorexia() == 0)
    {
        return 0;
    }
    chara_vomit(prm_879);
    return 1;
}



void sickifcursed(curse_state_t curse_state, int drinker, int prm_882)
{
    if (!is_cursed(curse_state))
        return;

    if (rnd(prm_882) == 0)
    {
        if (is_in_fov(drinker))
        {
            txt(lang(
                name(drinker) + u8"は気分が悪くなった。"s,
                name(drinker) + u8" feel"s + _s(drinker) + u8" grumpy."s));
        }
        dmgcon(drinker, status_ailment_t::sick, 200);
    }
}



void cook()
{
    snd(25);
    item_separate(ci);
    s = itemname(ci);
    p = rnd(sdata(184, cc) + 6) + rnd((inv[cooktool].param1 / 50 + 1));
    if (p > sdata(184, cc) / 5 + 7)
    {
        p = sdata(184, cc) / 5 + 7;
    }
    p = rnd(p + 1);
    if (p > 3)
    {
        p = rnd(p);
    }
    if (sdata(184, cc) >= 5)
    {
        if (p < 3)
        {
            if (rnd(4) == 0)
            {
                p = 3;
            }
        }
    }
    if (sdata(184, cc) >= 10)
    {
        if (p < 3)
        {
            if (rnd(3) == 0)
            {
                p = 3;
            }
        }
    }
    p += inv[cooktool].param1 / 100;
    if (p > 9)
    {
        p = 9;
    }
    if (p < 1)
    {
        p = 1;
    }
    make_dish(ci, p);
    txt(lang(
        itemname(cooktool) + u8"で"s + s + u8"を料理して、"s + itemname(ci, 1)
            + u8"を作った。"s,
        u8"You cook "s + s + u8" with "s + itemname(cooktool, 1)
            + u8" and make "s + itemname(ci, 1) + u8"."s));
    item_stack(0, ci, 1);
    int rank = inv[ci].param2;
    if (rank > 2)
    {
        skillexp(184, cc, 30 + rank * 5);
    }
    refresh_burden_state();
    return;
}



void make_dish(int ci, int type)
{
    inv[ci].image = picfood(type, inv[ci].param1 / 1000);
    inv[ci].weight = 500;
    inv[ci].param2 = type;
    if (inv[ci].material == 35 && inv[ci].param3 >= 0)
    {
        inv[ci].param3 = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12 + 72;
    }
}



void apply_general_eating_effect()
{
    tc = cc;
    DIM3(fdlist, 2, 10);
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        fdlist(0, cnt) = 0;
        fdlist(1, cnt) = 0;
    }
    nutrition = 2500;
    if (the_item_db[inv[ci].id]->is_cargo == 1)
    {
        nutrition += 2500;
    }
    fdmax = 0;
    i = inv[ci].param1 / 1000;
    if (i == 1)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (i == 8)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 2)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 3)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 7)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        nutrition = 2800;
    }
    if (i == 4)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 6)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 3000;
    }
    if (i == 5)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 60;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (the_item_db[inv[ci].id]->category == 57000)
    {
        nutrition = nutrition * (100 + inv[ci].param2 * 15) / 100;
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        if (fdlist(1, cnt) > 0)
        {
            if (inv[ci].param2 < 3)
            {
                fdlist(1, cnt) = fdlist(1, cnt) / 2;
            }
            else
            {
                fdlist(1, cnt) =
                    fdlist(1, cnt) * (50 + inv[ci].param2 * 20) / 100;
            }
        }
        else if (inv[ci].param2 < 3)
        {
            fdlist(1, cnt) =
                fdlist(1, cnt) * ((3 - inv[ci].param2) * 100 + 100) / 100;
        }
        else
        {
            fdlist(1, cnt) = fdlist(1, cnt) * 100 / (inv[ci].param2 * 50);
        }
    }
    if (cc == 0)
    {
        p = inv[ci].param1 / 1000;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cc == 0)
            {
                if (trait(41))
                {
                    if (inv[ci].id == 204)
                    {
                        s = chara_refstr(inv[ci].subname, 8);
                        if (strutil::contains(s(0), u8"/man/"))
                        {
                            txt(lang(u8"ウマイ！"s, u8"Delicious!"s));
                            break;
                        }
                    }
                }
            }
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    txt(lang(
                        u8"うげっ！腐ったものを食べてしまった…うわ…"s,
                        u8"Ugh! Rotten food!"s));
                    break;
                }
            }
            if (inv[ci].param2 == 0)
            {
                if (p == 1)
                {
                    txt(lang(u8"生肉だ…"s, u8"Ugh...Raw meat..."s));
                    break;
                }
                if (p == 7)
                {
                    txt(lang(
                        u8"粉の味がする…"s, u8"It tastes like...powder..."s));
                    break;
                }
                if (p == 5)
                {
                    txt(lang(
                        u8"生で食べるものじゃないな…"s,
                        u8"Er...this needs to be cooked."s));
                    break;
                }
                txt(lang(
                        u8"まずいわけではないが…"s,
                        u8"It doesn't taste awful but..."s),
                    lang(u8"平凡な味だ。"s, u8"Very boring food."s));
                break;
            }
            if (inv[ci].param2 < 3)
            {
                txt(lang(
                        u8"うぅ…腹を壊しそうだ。"s,
                        u8"Boy, it gives your stomach trouble!"s),
                    lang(u8"まずい！"s, u8"Ugh! Yuk!"s),
                    lang(u8"ひどい味だ！"s, u8"Awful taste!!"s));
                break;
            }
            if (inv[ci].param2 < 5)
            {
                txt(lang(
                        u8"まあまあの味だ。"s, u8"Uh-uh, the taste is so so."s),
                    lang(u8"悪くない味だ。"s, u8"The taste is not bad."s));
                break;
            }
            if (inv[ci].param2 < 7)
            {
                txt(lang(u8"かなりいける。"s, u8"It tasted good."s),
                    lang(u8"それなりに美味しかった。"s, u8"Decent meal."s));
                break;
            }
            if (inv[ci].param2 < 9)
            {
                txt(lang(u8"美味しい！"s, u8"Delicious!"s),
                    lang(u8"これはいける！"s, u8"Gee what a good taste!"s),
                    lang(u8"いい味だ！"s, u8"It tasted pretty good!"s));
                break;
            }
            txt(lang(u8"最高に美味しい！"s, u8"Wow! Terrific food!"s),
                lang(u8"まさに絶品だ！"s, u8"Yummy! Absolutely yummy!"s),
                lang(
                    u8"天にも昇る味だ！"s,
                    u8"It tasted like seventh heaven!"s));
        }
    }
    else if (inv[ci].material == 35)
    {
        if (inv[ci].param3 < 0)
        {
            txt(lang(
                name(cc) + u8"は渋い顔をした。"s,
                name(cc) + u8" looks glum."s));
        }
    }
    if (inv[ci].id == 425)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        nutrition = 2500;
        if (cc == 0)
        {
            txtef(2);
            txt(lang(
                u8"このハーブは活力の源だ。"s,
                u8"This herb invigorates you."s));
        }
    }
    if (inv[ci].id == 422)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 900;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 10, 2);
        modify_potential(cc, 11, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(lang(
                u8"新たな力が湧きあがってくる。"s,
                u8"You feel might coming through your body."s));
        }
    }
    if (inv[ci].id == 423)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 16, 2);
        modify_potential(cc, 15, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(lang(
                u8"魔力の向上を感じる。"s,
                u8"You feel magical power springs up inside you."s));
        }
    }
    if (inv[ci].id == 424)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 750;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        modify_potential(cc, 12, 2);
        modify_potential(cc, 13, 2);
        nutrition = 500;
        if (cc == 0)
        {
            txtef(2);
            txt(lang(
                u8"感覚が研ぎ澄まされるようだ。"s,
                u8"You feel as your sense is sharpened."s));
        }
    }
    if (inv[ci].id == 426)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 850;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 17, 2);
        modify_potential(cc, 14, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(lang(
                u8"ホルモンが活発化した。"s,
                u8"Your hormones are activated."s));
        }
    }
    if (inv[ci].id == 427)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 20000;
    }
    if (inv[ci].id == 738)
    {
        nutrition = 750;
    }
    if (cc == 0)
    {
        if (inv[ci].material == 35)
        {
            if (inv[ci].param3 < 0)
            {
                eat_rotten_food();
            }
        }
    }
    if (inv[ci].id == 204)
    {
        s = chara_refstr(inv[ci].subname, 8);
        if (cc == 0)
        {
            if (strutil::contains(s(0), u8"/man/"))
            {
                if (trait(41))
                {
                    txt(lang(
                        u8"これはあなたの大好きな人肉だ！"s,
                        u8"It's your favorite human flesh!"s));
                }
                else
                {
                    txt(lang(
                        u8"これは人肉だ…うぇぇ！"s,
                        u8"Eeeek! It's human flesh!"s));
                    damage_insanity(cc, 15);
                    dmgcon(cc, status_ailment_t::insane, 150);
                    if (trait(41) == 0)
                    {
                        if (rnd(5) == 0)
                        {
                            get_trait_info(0, 41);
                            txtef(2);
                            txt(traitrefn(0));
                            trait(41) = 1;
                        }
                    }
                }
            }
            else if (trait(41))
            {
                txt(lang(
                    u8"人肉の方が好みだが…"s,
                    u8"You would've rather eaten human flesh."s));
                nutrition = nutrition * 2 / 3;
            }
        }
    }
    if (inv[ci].id == 204
        || ((inv[ci].id == 571 || inv[ci].id == 573) && rnd(3) == 0))
    {
        dbmode = 12;
        dbid = inv[ci].subname;
        access_character_info();
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        i = 100;
        if (cdata[cc].nutrition >= 5000)
        {
            p = (cdata[cc].nutrition - 5000) / 25;
            i = i * 100 / (100 + p);
        }
        if (cc != 0)
        {
            i = 1500;
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    i = 500;
                }
            }
        }
        if (i > 0)
        {
            skillexp(fdlist(0, cnt), cc, fdlist(1, cnt) * i / 100);
        }
    }
    if (inv[ci].curse_state == curse_state_t::blessed)
    {
        nutrition = nutrition * 150 / 100;
    }
    if (is_cursed(inv[ci].curse_state))
    {
        nutrition = nutrition * 50 / 100;
    }
    cdata[cc].nutrition += nutrition;
    if (nutrition >= 3000)
    {
        if (rnd(10) == 0 || cdata[cc].nutrition >= 12000)
        {
            modweight(cc, rnd(3) + 1, cdata[cc].nutrition >= 12000);
        }
    }
    if (cdata[cc].id == 261)
    {
        if (nutrition >= 2000)
        {
            int cibk = ci;
            flt(calcobjlv(cdata[cc].level));
            flttypeminor = 58500;
            itemcreate(-1, 0, cdata[cc].position.x, cdata[cc].position.y, 0);
            txtef(9);
            txt(lang(
                u8"「げふぅ」"s + name(cc) + u8"は"s + itemname(ci, 1)
                    + u8"を吐き出した。"s,
                u8"「Ugh-Ughu」 "s + name(cc) + u8" spews up "s
                    + itemname(ci, 1) + u8"."s));
            ci = cibk;
        }
    }
    if (inv[ci].id == 204)
    {
        if (inv[ci].subname == 319)
        {
            txtef(2);
            txt(lang(
                name(cc) + u8"は進化した。"s,
                name(cc) + u8" evolve"s + _s(cc) + u8"."s));
            if (rnd(sdata.get(2, cc).original_level
                        * sdata.get(2, cc).original_level
                    + 1)
                < 2000)
            {
                skillmod(2, cc, 1000);
            }
            if (rnd(sdata.get(3, cc).original_level
                        * sdata.get(3, cc).original_level
                    + 1)
                < 2000)
            {
                skillmod(3, cc, 1000);
            }
            for (int cnt = 100; cnt < 400; ++cnt)
            {
                if (!the_ability_db[cnt]
                    || the_ability_db[cnt]->related_basic_attribute == 0
                    || sdata.get(cnt, cc).original_level == 0)
                {
                    continue;
                }
                modify_potential(cc, cnt, rnd(10) + 1);
            }
        }
    }
    if (inv[ci].id == 755)
    {
        txt(lang(u8"これは縁起がいい！"s, u8"The food is a charm!"s));
        skillmod(19, cc, 2000);
    }
    if (inv[ci].id == 702)
    {
        skillmod(19, cc, 1000);
    }
    if (inv[ci].id == 639)
    {
        skillmod(19, cc, 20000);
    }
    if (inv[ci].id == 655)
    {
        skillmod(2, cc, 3000);
    }
    if (inv[ci].id == 662)
    {
        skillmod(3, cc, 3000);
    }
    if (inv[ci].id == 738)
    {
        if (cc < 16)
        {
            txt(lang(
                name(cc) + u8"はクッキーの中のおみくじを読んだ。"s,
                name(cc) + u8" read"s + _s(cc) + u8" the paper fortune."s));
            read_talk_file(u8"%COOKIE2");
            if (inv[ci].curse_state == curse_state_t::blessed
                || (inv[ci].curse_state == curse_state_t::none && rnd(2)))
            {
                read_talk_file(u8"%COOKIE1");
            }
            txtef(5);
            txt(""s + buff);
        }
    }
    if (inv[ci].id == 667)
    {
        txt(lang(
            name(cc) + u8"の心はすこし癒された。"s,
            name(cc) + your(cc) + u8" heart is warmed."s));
        healsan(cc, 30);
    }
    if (ibit(14, ci) == 1)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"これは毒されている！"s + name(cc)
                    + u8"はもがき苦しみのたうちまわった！"s,
                u8"It's poisoned! "s + name(cc) + u8" writhe"s + _s(cc)
                    + u8" in agony!"s));
            txt(lang(u8"「ギャァァ…！」"s, u8"\"Gyaaaaa...!\""s),
                lang(u8"「ブッ！」"s, u8"\"Ugh!\""s));
        }
        dmghp(cc, rnd(250) + 250, -4);
        if (cdata[cc].state != 1)
        {
            if (cc != 0)
            {
                if (cdata[cc].relationship >= 0)
                {
                    modify_karma(0, -1);
                }
            }
            return;
        }
    }
    if (ibit(6, ci) == 1)
    {
        if (cc == 0)
        {
            txt(lang(u8"あなたは興奮した！"s, u8"You are excited!"s));
        }
        else
        {
            txtef(9);
            txt(name(cc)
                    + lang(
                          u8"「なんだか…変な気分なの…」"s,
                          (u8" gasps, "s + u8"\"I f-feel...strange...\""s)),
                name(cc)
                    + lang(
                          u8"「あれ…なにこの感じは…」"s,
                          (u8"gasps "s
                           + u8"\"Uh..uh..What is this feeling...\""s)));
            cdata[cc].emotion_icon = 317;
            chara_mod_impression(cc, 30);
            modify_karma(0, -10);
            lovemiracle(cc);
        }
        dmgcon(cc, status_ailment_t::dimmed, 500);
        cdata[cc].emotion_icon = 317;
    }
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[ci].enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 50 + 1) + 1;
            healsp(cc, p);
            continue;
        }
        if (enc == 38)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 25 + 1) + 1;
            healmp(cc, p / 5);
            continue;
        }
        if (enc == 37)
        {
            event_add(18, cc);
            continue;
        }
        if (enc == 40)
        {
            if (gdata_left_turns_of_timestop == 0)
            {
                txtef(9);
                txt(lang(
                    name(cc) + u8"は時を止めた。"s,
                    name(cc) + u8" stop"s + _s(cc) + u8" time."s));
                gdata_left_turns_of_timestop =
                    inv[ci].enchantments[cnt].power / 100 + 1 + 1;
                continue;
            }
        }
        enc2 = enc / 10000;
        if (enc2 != 0)
        {
            enc = enc % 10000;
            if (enc2 == 1)
            {
                skillexp(
                    enc,
                    cc,
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 100
                        * (1 + (cc != 0) * 5));
                if (is_in_fov(cc))
                {
                    if (inv[ci].enchantments[cnt].power / 50 + 1 >= 0)
                    {
                        txt(lang(
                            name(cc) + u8"の"s
                                + i18n::_(
                                      u8"ability",
                                      std::to_string(enc),
                                      u8"name")
                                + u8"は発達した。"s,
                            name(cc) + his(cc) + u8" "s
                                + i18n::_(
                                      u8"ability",
                                      std::to_string(enc),
                                      u8"name")
                                + u8" develops."s));
                    }
                    else
                    {
                        txt(lang(
                            name(cc) + u8"の"s
                                + i18n::_(
                                      u8"ability",
                                      std::to_string(enc),
                                      u8"name")
                                + u8"は衰えた。"s,
                            name(cc) + his(cc) + u8" "s
                                + i18n::_(
                                      u8"ability",
                                      std::to_string(enc),
                                      u8"name")
                                + u8" deteriorates."s));
                    }
                }
                continue;
            }
            if (enc2 == 6)
            {
                if (is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"の"s
                            + i18n::_(
                                  u8"ability", std::to_string(enc), u8"name")
                            + u8"は成長期に突入した。"s,
                        name(cc) + his(cc) + u8" "s
                            + i18n::_(
                                  u8"ability", std::to_string(enc), u8"name")
                            + u8" enters a period of rapid growth."s));
                }
                buff_add(
                    cc,
                    20 + (enc - 10),
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 5
                        * (1 + (cc != 0) * 2),
                    2000);
                continue;
            }
        }
    }
    eatstatus(inv[cieat].curse_state, cc);
    return;
}



void eating_effect_eat_iron()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            u8"まるで鉄のように硬い！"s + name(cc) + u8"の胃は悲鳴をあげた。"s,
            u8"It's too hard! "s + name(cc) + your(cc)
                + u8" stomach screams."s));
    }
    dmgcon(cc, status_ailment_t::dimmed, 200);
    return;
}



void eating_effect_insanity()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            u8"気が変になりそうな味だ。"s,
            u8"It tastes really, really strange."s));
    }
    damage_insanity(cc, 25);
    dmgcon(cc, status_ailment_t::insane, 500);
    return;
}



void eating_effect_eat_horse()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"馬肉だ！これは精がつきそうだ。"s,
            u8"A horsemeat! It's nourishing"s));
    }
    skillexp(11, cc, 100);
    return;
}



void eating_effect_eat_holy_one()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            name(cc) + u8"は神聖なものを汚した気がした。"s,
            name(cc) + u8" feel"s + _s(cc) + u8" as "s + he(cc) + u8" "s
                + have(cc) + u8" been corrupted."s));
    }
    if (rnd(5) == 0)
    {
        resistmod(cc, 53, 50);
    }
    return;
}



void eating_effect_eat_at()
{
    if (is_in_fov(cc))
    {
        txt(lang(u8"＠を食べるなんて…"s, u8"You dare to eat @..."s));
    }
    return;
}



void eating_effect_eat_guard()
{
    if (cc != 0)
    {
        return;
    }
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(u8"ガード達はあなたを憎悪した。"s, u8"Guards hate you."s));
    }
    modify_karma(cc, -15);
    return;
}



void eating_effect_fire()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            name(cc) + u8"の体は一瞬燃え上がった。"s,
            name(cc) + your(cc) + u8" body burns up for a second."s));
    }
    resistmod(cc, 50, 100);
    return;
}



void eating_effect_insanity2()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            name(cc) + u8"の胃は狂気で満たされた。"s, u8"Sheer madness!"s));
    }
    resistmod(cc, 54, 50);
    damage_insanity(cc, 200);
    dmgcon(cc, status_ailment_t::insane, 1000);
    return;
}



void eating_effect_eat_cute_one()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"肌がつるつるになりそうだ。"s,
            name(cc) + your(cc) + u8" skin becomes smooth."s));
    }
    skillexp(17, cc, 150);
    return;
}



void eating_effect_eat_lovely_one()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            name(cc) + u8"は恋をしている気分になった！"s,
            name(cc) + u8" feel"s + _s(cc) + u8" love!"s));
    }
    skillexp(17, cc, 400);
    return;
}



void eating_effect_eat_poisonous_one()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(u8"これは有毒だ！"s, u8"Argh! It's poisonous!"s));
    }
    dmgcon(cc, status_ailment_t::poisoned, 100);
    return;
}



void eating_effect_regeneration()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"血が沸き立つようだ。"s,
            u8"A troll meat. This must be good for your body."s));
    }
    skillexp(154, cc, 200);
    return;
}



void eating_effect_eat_rotten_one()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            u8"腐ってるなんて分かりきっていたのに…うげぇ"s,
            u8"Of course, it's rotten! Urgh..."s));
    }
    eat_rotten_food();
    return;
}



void eating_effect_strength()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(u8"力が湧いてくるようだ。"s, u8"Mighty taste!"s));
    }
    skillexp(10, cc, 250);
    return;
}



void eating_effect_magic()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"微かな魔力の刺激を感じた。"s,
            name(cc) + u8" "s + is(cc) + u8" magically stimulated."s));
    }
    skillexp(155, cc, 500);
    return;
}



void eating_effect_insanity3()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            u8"胃の調子がおかしい…"s,
            u8"Something is wrong with "s + name(cc) + your(cc)
                + u8" stomach..."s));
    }
    dmgcon(cc, status_ailment_t::confused, 200);
    return;
}



void eating_effect_calm()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"この肉は心を落ち着かせる効果があるようだ。"s,
            u8"Eating this brings "s + name(cc) + u8" inner peace."s));
    }
    healsan(cc, 20);
    return;
}



void eating_effect_insanity4()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            name(cc) + u8"の胃は狂気で満たされた。"s, u8"Sheer madness!"s));
    }
    damage_insanity(cc, 50);
    if (rnd(5) == 0)
    {
        resistmod(cc, 54, 50);
    }
    return;
}



void eating_effect_chaos()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            name(cc) + u8"の胃は混沌で満たされた。"s,
            name(cc) + u8" "s + is(cc) + u8" shaken by a chaotic power."s));
    }
    dmgcon(cc, status_ailment_t::confused, 300);
    return;
}



void eating_effect_lightning()
{
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            name(cc) + u8"の神経に電流が走った。"s,
            name(cc) + your(cc) + u8" nerve is damaged."s));
    }
    dmgcon(cc, status_ailment_t::paralyzed, 300);
    return;
}



void eating_effect_eat_cat()
{
    if (cc != 0)
    {
        return;
    }
    if (is_in_fov(cc))
    {
        txt(lang(u8"猫を食べるなんて！！"s, u8"How can you eat a cat!!"s));
    }
    modify_karma(0, -5);
    return;
}



void eating_effect_ether()
{
    if (cc != 0)
    {
        return;
    }
    if (is_in_fov(cc))
    {
        txtef(8);
        txt(lang(
            name(cc) + u8"の体内はエーテルで満たされた。"s,
            u8"Ether corrupts your body."s));
    }
    modcorrupt(1000);
    return;
}



void eating_effect_constitution()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"体力がつきそうだ。"s,
            u8"This food is good for your endurance."s));
    }
    return;
}



void eating_effect_magic2()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"魔力が鍛えられる。"s, u8"This food is good for your magic."s));
    }
    return;
}



void eating_effect_strength2()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"力がつきそうだ。"s, u8"This food is good for your strength."s));
    }
    return;
}



void eating_effect_will()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"精神が少しずぶとくなった。"s,
            u8"This food is good for your will power."s));
    }
    return;
}



void eating_effect_quick()
{
    if (is_in_fov(cc))
    {
        txtef(2);
        txt(lang(
            u8"ワアーォ、"s + name(cc) + u8"は速くなった気がする！"s,
            u8"Wow, "s + name(cc) + u8" speed"s + _s(cc) + u8" up!"s));
    }
    skillexp(
        18, cc, clamp(2500 - sdata(18, cc) * sdata(18, cc) / 10, 20, 2500));
    return;
}



void eating_effect_pregnant()
{
    if (is_in_fov(cc))
    {
        txt(lang(
            u8"何かが"s + name(cc) + u8"の体内に入り込んだ。"s,
            u8"Something gets into "s + name(cc) + your(cc) + u8" body."s));
    }
    tc = cc;
    get_pregnant();
    return;
}

} // namespace elona
