#include "activity.hpp"
#include "character.hpp"
#include "variables.hpp"

namespace elona
{

void rowact_check(int prm_789)
{
    if (cdata[prm_789].continuous_action_id != 0)
    {
        if (cdata[prm_789].continuous_action_id != 3)
        {
            cdata[prm_789].stops_continuous_action_if_damaged = 1;
        }
    }
    return;
}



void rowact_item(int prm_790)
{
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].continuous_action_turn <= 0)
        {
            continue;
        }
        if (cdata[cnt].continuous_action_id == 1
            || cdata[cnt].continuous_action_id == 2)
        {
            if (cdata[cnt].continuous_action_item == prm_790)
            {
                rowactend(cnt);
                txt(lang(
                    name(cnt) + u8"は行動を中断した。"s,
                    name(cnt) + u8" cancel"s + _s(cnt) + u8" "s + his(cnt)
                        + u8" action."s));
            }
        }
    }
    return;
}

void rowactend(int cc)
{
    cdata[cc].continuous_action_id = 0;
    cdata[cc].continuous_action_turn = 0;
    cdata[cc].continuous_action_item = 0;
}


void activity_handle_damage(character& chara)
{
    if (chara == 0)
    {
        if (chara.continuous_action_id != 1
            && chara.continuous_action_id != 2
            && chara.continuous_action_id != 3)
        {
            rtval = 0;
        }
        else
        {
            screenupdate = -1;
            update_screen();
            prompt_stop_continuous_action();
        }
    }
    if (chara != 0 || rtval == 0)
    {
        if (is_in_fov(chara))
        {
            txt(lang(
                    name(chara) + u8"は"s
                    + i18n::_(
                        u8"ui",
                        u8"action",
                        u8"_"s + chara.continuous_action_id)
                    + u8"を中断した。"s,
                    name(chara) + u8" stop"s + _s(chara) + u8" "s
                    + i18n::_(
                        u8"ui",
                        u8"action",
                        u8"_"s + chara.continuous_action_id)
                    + u8"."s));
        }
        rowactend(chara);
    }
    screenupdate = -1;
    update_screen();
    chara.stops_continuous_action_if_damaged = 0;
}

void activity_proc(character& chara)
{
    ci = chara.continuous_action_item;
    --chara.continuous_action_turn;
    if (chara.continuous_action_id == 7)
    {
        auto_turn(config::instance().animewait * 2);
        spot_fishing();
    }
    if (chara.continuous_action_id == 5)
    {
        auto_turn(config::instance().animewait * 0.75);
        spot_mining_or_wall();
    }
    if (chara.continuous_action_id == 8)
    {
        auto_turn(config::instance().animewait * 0.75);
        spot_material();
    }
    if (chara.continuous_action_id == 9)
    {
        auto_turn(config::instance().animewait * 0.75);
        spot_digging();
    }
    if (chara.continuous_action_id == 4)
    {
        auto_turn(config::instance().animewait / 4);
        do_rest();
    }
    if (chara.continuous_action_id == 1)
    {
        auto_turn(config::instance().animewait * 5);
        return do_eat_command();
    }
    if (chara.continuous_action_id == 2)
    {
        auto_turn(config::instance().animewait * 1.25);
        return do_read_command();
    }
    if (chara.continuous_action_id == 11)
    {
        auto_turn(config::instance().animewait * 2.5);
        continuous_action_sex();
    }
    if (chara.continuous_action_id == 10)
    {
        if (gdata(91) == 103)
        {
            auto_turn(config::instance().animewait * 2);
        }
        else if (gdata(91) == 104)
        {
            auto_turn(config::instance().animewait * 2);
        }
        else if (gdata(91) == 105)
        {
            auto_turn(config::instance().animewait * 2.5);
        }
        else
        {
            auto_turn(config::instance().animewait);
        }
        continuous_action_others();
    }
    if (chara.continuous_action_id == 12)
    {
        auto_turn(config::instance().animewait);
        continuous_action_blending();
    }
    if (chara.continuous_action_id == 6)
    {
        auto_turn(config::instance().animewait * 2);
        continuous_action_perform();
    }
    if (chara.continuous_action_id == 3)
    {
        label_2153();
        return proc_movement_event();
    }
    if (chara.continuous_action_turn > 0)
    {
        return turn_result_t::turn_end;
    }
    rowactend(cc);
    if (cc == 0)
    {
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return turn_result_t::exit_map;
        }
    }
}

void prompt_stop_continuous_action()
{
    txt(lang(
        i18n::_(u8"ui", u8"action", u8"_"s + cdata[cc].continuous_action_id)
            + u8"を中断したほうがいいだろうか？ "s,
        u8"Do you want to cancel "s
            + i18n::_(
                  u8"ui", u8"action", u8"_"s + cdata[cc].continuous_action_id)
            + u8"? "s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    return;
}

void continuous_action_perform()
{
    static int performtips;

    if (cdata[cc].continuous_action_id == 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は"s + itemname(ci) + u8"の演奏をはじめた。"s,
                name(cc) + u8" start"s + _s(cc) + u8" to play "s + itemname(ci)
                    + u8"."s));
        }
        cdata[cc].continuous_action_id = 6;
        cdata[cc].continuous_action_turn = 61;
        cdata[cc].continuous_action_item = ci;
        cdata[cc].quality_of_performance = 40;
        cdata[cc].tip_gold = 0;
        if (cc == 0)
        {
            performtips = 0;
        }
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        ci = cdata[cc].continuous_action_item;
        if (cdata[cc].continuous_action_turn % 10 == 0)
        {
            if (is_in_fov(cc))
            {
                if (rnd(10) == 0)
                {
                    txtef(4);
                    txt(lang(u8"ﾁｬﾗﾝ♪ "s, u8"*Tiki*"s),
                        lang(u8"ﾎﾟﾛﾝ♪ "s, u8"*Dan*"s),
                        lang(u8"ﾀﾞｰﾝ♪ "s, u8"*Lala*"s));
                }
                txtef(4);
                txt(lang(u8"ｼﾞｬﾝ♪ "s, u8"*Cha*"s));
            }
        }
        if (cdata[cc].continuous_action_turn % 20 == 0)
        {
            gold = 0;
            make_sound(cdata[cc].position.x, cdata[cc].position.y, 5, 1, 1, cc);
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12
                    >= cdata[cnt].time_interest_revive)
                {
                    cdata[cnt].interest = 100;
                }
                if (is_in_fov(cc))
                {
                    if (cdata[cnt].vision_flag != msync)
                    {
                        continue;
                    }
                }
                else if (
                    dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[cnt].position.x,
                        cdata[cnt].position.y)
                    > 3)
                {
                    continue;
                }
                if (cdata[cnt].interest <= 0)
                {
                    continue;
                }
                if (cdata[cnt].sleep > 0)
                {
                    continue;
                }
                x = cdata[cnt].position.x;
                y = cdata[cnt].position.y;
                if (map(x, y, 1) == 0)
                {
                    continue;
                }
                tc = cnt;
                if (tc == cc)
                {
                    continue;
                }
                if (cdata[tc].relationship == -3)
                {
                    if (cdata[tc].hate == 0)
                    {
                        if (is_in_fov(tc))
                        {
                            txt(lang(
                                name(tc) + u8"は激怒した。"s,
                                name(tc) + u8" get"s + _s(tc) + u8" angry."s));
                        }
                    }
                    cdata[tc].hate = 30;
                    continue;
                }
                if (cc == 0)
                {
                    cdata[tc].interest -= rnd(15);
                    cdata[tc].time_interest_revive = gdata_hour + gdata_day * 24
                        + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12
                        + 12;
                }
                if (cdata[tc].interest <= 0)
                {
                    if (is_in_fov(cc))
                    {
                        txtef(9);
                        if (jp)
                        {
                            txt(u8"「飽きた」"s,
                                u8"「前にも聴いたよ」"s,
                                u8"「またこの曲か…」"s);
                        }
                        if (en)
                        {
                            txt(u8"\"Boring.\""s,
                                u8"\"I've heard this before.\""s,
                                u8"\"This song again?\""s);
                        }
                    }
                    cdata[tc].interest = 0;
                    continue;
                }
                if (sdata(183, cc) < cdata[tc].level)
                {
                    if (rnd(3) == 0)
                    {
                        cdata[cc].quality_of_performance -= cdata[tc].level / 2;
                        if (is_in_fov(cc))
                        {
                            txtef(9);
                            if (jp)
                            {
                                txt(u8"「引っ込め！」"s,
                                    u8"「うるさい！」"s,
                                    u8"「下手っぴ！」"s,
                                    u8"「何のつもりだ！」"s);
                            }
                            if (en)
                            {
                                txt(u8"\"Boo boo!\""s,
                                    u8"\"Shut it!\""s,
                                    u8"\"What are you doing!\""s,
                                    u8"\"You can't play shit.\""s);
                            }
                            txt(lang(
                                ""s + name(tc) + u8"は石を投げた。"s,
                                name(tc) + u8" throw"s + _s(tc)
                                    + u8" a rock."s));
                        }
                        dmg = rnd(cdata[tc].level + 1) + 1;
                        if (cdata[tc].id == 29)
                        {
                            dmg = cdata[tc].level * 2 + rnd(100);
                        }
                        dmghp(cc, dmg, -8);
                        if (cdata[cc].state == 0)
                        {
                            break;
                        }
                        continue;
                    }
                }
                if (rnd(3) == 0)
                {
                    p = cdata[cc].quality_of_performance
                            * cdata[cc].quality_of_performance
                            * (100
                               + inv[cdata[cc].continuous_action_item].param1
                                   / 5)
                            / 100 / 1000
                        + rnd(10);
                    p = clamp(
                        cdata[tc].gold * clamp(p(0), 1, 100) / 125,
                        0,
                        sdata(183, cc) * 100);
                    if (tc < 16)
                    {
                        p = rnd(clamp(p(0), 1, 100)) + 1;
                    }
                    if ((cdata[tc].character_role >= 1000
                         && cdata[tc].character_role < 2000)
                        || cdata[tc].character_role == 2003)
                    {
                        p /= 5;
                    }
                    if (p > cdata[tc].gold)
                    {
                        p = cdata[tc].gold;
                    }
                    cdata[tc].gold -= p;
                    cdata[cc].gold += p;
                    gold += p;
                }
                if (cdata[tc].level > sdata(183, cc))
                {
                    continue;
                }
                p = rnd(cdata[tc].level + 1) + 1;
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 2 + 1))
                {
                    if (gdata_executing_immediate_quest_type == 1009)
                    {
                        if (tc >= 57)
                        {
                            cdata[tc].impression += rnd(3);
                            calcpartyscore();
                        }
                    }
                    if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance += p;
                    }
                    else if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance -= p;
                    }
                }
                if (encfindspec(cdata[cc].continuous_action_item, 60))
                {
                    if (rnd(15) == 0)
                    {
                        dmgcon(tc, status_ailment_t::drunk, 500);
                    }
                }
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 5 + 1))
                {
                    if (rnd(3) == 0)
                    {
                        if (is_in_fov(cc))
                        {
                            txtef(9);
                            if (jp)
                            {
                                txt(name(tc) + u8"は歓声を上げた。"s,
                                    name(tc) + u8"は目を輝かせた。"s,
                                    u8"「ブラボー」"s,
                                    u8"「いいぞ！」"s,
                                    name(tc) + u8"はうっとりした。"s,
                                    name(tc) + u8"は"s + name(cc)
                                        + u8"の演奏を褒め称えた。"s);
                            }
                            if (en)
                            {
                                txt(name(tc) + u8" clap"s + _s(tc) + u8"."s,
                                    name(tc) + u8" listene"s + _s(tc)
                                        + u8" to "s + name(cc) + your(cc)
                                        + u8" music joyfully."s,
                                    u8"\"Bravo!\""s,
                                    u8"\"Nice song.\""s,
                                    u8"\"Scut!\""s,
                                    name(tc) + u8" "s + is(tc)
                                        + u8" excited!"s);
                            }
                        }
                        cdata[cc].quality_of_performance += cdata[tc].level + 5;
                        if (cc == 0)
                        {
                            if (tc >= 16)
                            {
                                if (rnd(performtips * 2 + 2) == 0)
                                {
                                    x = clamp(
                                        cdata[cc].position.x - 1 + rnd(3),
                                        0,
                                        mdata(0) - 1);
                                    y = clamp(
                                        cdata[cc].position.y - 1 + rnd(3),
                                        0,
                                        mdata(1) - 1);
                                    cell_check(x, y);
                                    if (cellaccess == 0)
                                    {
                                        continue;
                                    }
                                    if (fov_los(
                                            cdata[tc].position.x,
                                            cdata[tc].position.y,
                                            x,
                                            y)
                                        == 0)
                                    {
                                        continue;
                                    }
                                    if (encfindspec(
                                            cdata[cc].continuous_action_item,
                                            49))
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 8),
                                            calcfixlv(3 + (rnd(4) == 0)));
                                    }
                                    else
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 10),
                                            calcfixlv(3));
                                    }
                                    flttypemajor =
                                        fsetperform(rnd(length(fsetperform)));
                                    dbid = 0;
                                    if (gdata_executing_immediate_quest_type
                                        == 1009)
                                    {
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 241;
                                        }
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 622;
                                        }
                                        if (cdata[tc].level > 15)
                                        {
                                            if (rnd(1000) == 0)
                                            {
                                                dbid = 725;
                                            }
                                        }
                                        if (cdata[tc].level > 10)
                                        {
                                            if (rnd(800) == 0)
                                            {
                                                dbid = 726;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (rnd(10) == 0)
                                        {
                                            dbid = 724;
                                        }
                                        if (rnd(250) == 0)
                                        {
                                            dbid = 55;
                                        }
                                    }
                                    int stat = itemcreate(-1, dbid, x, y, 1);
                                    if (stat != 0)
                                    {
                                        --inv[ci].number;
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ccbk = cc;
                                        cc = tc;
                                        aniref(0) = inv[ci].image;
                                        aniref(1) = inv[ci].color;
                                        anix = inv[ci].position.x;
                                        aniy = inv[ci].position.y;
                                        play_animation(15);
                                        cc = ccbk;
                                        ++inv[ci].number;
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ++performtips;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (gold != 0)
            {
                cdata[cc].tip_gold += gold;
                if (is_in_fov(cc))
                {
                    snd(11);
                }
            }
        }
        return;
    }
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cc != 0)
        {
            break;
        }
        if (cdata[cc].quality_of_performance < 0)
        {
            txt(lang(u8"まるで駄目だ…"s, u8"It is a waste of time."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 20)
        {
            txt(lang(u8"不評だった…"s, u8"Almost everyone ignores you."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 40)
        {
            txt(lang(
                u8"もっと練習しなくては…"s,
                u8"You need to practice lot more."s));
            break;
        }
        if (cdata[cc].quality_of_performance == 40)
        {
            txt(lang(u8"演奏を終えた。"s, u8"You finish your performance."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 60)
        {
            txt(lang(u8"いまいちだ。"s, u8"Not good."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 80)
        {
            txt(lang(
                u8"手ごたえがあった。"s,
                u8"People seem to like your performance."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 100)
        {
            txt(lang(
                u8"納得できる演奏ができた。"s,
                u8"Your performance is successful."s));
            break;
        }
        if (cdata[cc].quality_of_performance < 120)
        {
            txt(lang(u8"大盛況だ！"s, u8"Wonderful!"s));
            break;
        }
        if (cdata[cc].quality_of_performance < 150)
        {
            txt(lang(
                u8"素晴らしい！"s,
                u8"Great performance. Everyone cheers you."s));
            break;
        }
        txt(lang(u8"歴史に残る名演だ！"s, u8"A Legendary stage!"s));
        break;
    }
    if (cdata[cc].quality_of_performance > 40)
    {
        cdata[cc].quality_of_performance = cdata[cc].quality_of_performance
            * (100 + inv[cdata[cc].continuous_action_item].param1 / 5) / 100;
    }
    if (cdata[cc].tip_gold != 0)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は合計 "s + cdata[cc].tip_gold
                    + i18n::_(u8"ui", u8"gold") + u8"のおひねりを貰った。"s,
                u8"The audience gives "s + name(cc) + u8" total of "s
                    + cdata[cc].tip_gold + u8" gold pieces."s));
        }
    }
    rowactend(cc);
    int experience = cdata[cc].quality_of_performance - sdata(183, cc) + 50;
    if (experience > 0)
    {
        skillexp(183, cc, experience, 0, 0);
    }
    return;
}



void continuous_action_sex()
{
    int sexhost = 0;
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 11;
        cdata[cc].continuous_action_turn = 25 + rnd(10);
        cdata[cc].continuous_action_target = tc;
        cdata[tc].continuous_action_id = 11;
        cdata[tc].continuous_action_turn = cdata[cc].continuous_action_turn * 2;
        cdata[tc].continuous_action_target = cc + 10000;
        if (is_in_fov(cc))
        {
            txt(lang(
                name(cc) + u8"は服を脱ぎ始めた。"s,
                name(cc) + u8" begin"s + _s(cc) + u8" to take "s + his(cc)
                    + u8" clothes off."s));
        }
        return;
    }
    sexhost = 1;
    tc = cdata[cc].continuous_action_target;
    if (tc >= 10000)
    {
        tc -= 10000;
        sexhost = 0;
    }
    if (cdata[tc].state != 1 || cdata[tc].continuous_action_id != 11)
    {
        if (is_in_fov(cc))
        {
            txt(lang(
                u8"「そ、その"s
                    + i18n::_(u8"ui", u8"sex2", u8"_"s + cdata[tc].sex)
                    + u8"とは体だけの関係"s + _da() + _ore(3)
                    + u8"は何も知らないから、命だけは…！」"s,
                u8"\"I-I don't really know that "s
                    + i18n::_(u8"ui", u8"sex2", u8"_"s + cdata[tc].sex)
                    + u8". Please spare my life!\""s));
        }
        rowactend(cc);
        rowactend(tc);
        return;
    }
    if (cc == 0)
    {
        if (!actionsp(0, 1 + rnd(2)))
        {
            txt(lang(u8"疲労し過ぎて失敗した！"s, u8"You are too exhausted!"s));
            rowactend(cc);
            rowactend(tc);
            return;
        }
    }
    cdata[cc].emotion_icon = 317;
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (sexhost == 0)
        {
            if (cdata[cc].continuous_action_turn % 5 == 0)
            {
                if (is_in_fov(cc))
                {
                    txtef(9);
                    if (jp)
                    {
                        txt(u8"「きくぅ」"s,
                            u8"「もふもふ」"s,
                            u8"「くやしい、でも…」"s,
                            u8"「はぁはぁ！」"s,
                            u8"「ウフフフ」"s);
                    }
                    if (en)
                    {
                        txt(u8"\"Yes!\""s,
                            u8"\"Ohhh\""s,
                            u8"*gasp*"s,
                            u8"*rumble*"s,
                            u8"\"come on!\""s);
                    }
                }
            }
        }
        return;
    }
    if (sexhost == 0)
    {
        rowactend(cc);
        return;
    }
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        int c{};
        if (cnt == 0)
        {
            c = cc;
        }
        else
        {
            c = tc;
        }
        cdata[cc].drunk = 0;
        if (cnt == 1)
        {
            if (rnd(3) == 0)
            {
                dmgcon(c, status_ailment_t::insane, 500);
            }
            if (rnd(5) == 0)
            {
                dmgcon(c, status_ailment_t::paralyzed, 500);
            }
            dmgcon(c, status_ailment_t::insane, 300);
            healsan(c, 10);
            skillexp(11, c, 250 + (c >= 57) * 1000);
            skillexp(15, c, 250 + (c >= 57) * 1000);
        }
        if (rnd(15) == 0)
        {
            dmgcon(c, status_ailment_t::sick, 200);
        }
        skillexp(17, c, 250 + (c >= 57) * 1000);
    }
    sexvalue = sdata(17, cc) * (50 + rnd(50)) + 100;
    if (is_in_fov(cc))
    {
        txtef(9);
        if (jp)
        {
            txt(u8"「よかった"s + _yo(3),
                u8"「す、すごい"s + _yo(3),
                u8"「も、もうだめ"s + _da(3),
                u8"「は、激しかった"s + _yo(3),
                u8"「か、完敗"s + _da(3));
        }
        if (en)
        {
            txt(u8"\"You are awesome!"s,
                u8"\"Oh my god...."s,
                u8"\"Okay, okay, you win!"s,
                u8"\"Holy...!"s);
        }
        txtef(20);
        if (tc == 0)
        {
            txt(lang(u8"」"s, u8"\""s));
        }
    }
    if (tc != 0)
    {
        if (cdata[tc].gold >= sexvalue)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"！さあ、小遣いを受け取って"s + _kure(3) + u8"」"s,
                    u8"Here, take this.\""s));
            }
        }
        else
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    u8"！これが"s + _ore(3) + u8"の財布の中身の全て"s + _da()
                        + u8"」"s,
                    u8"Take this money, it's all I have!\""s));
                if (rnd(3) == 0)
                {
                    if (cc != 0)
                    {
                        txt(lang(
                            name(cc) + u8"は激怒した。「なめてんの？」"s,
                            name(cc)
                                + u8" gets furious, "s
                                  u8"\"And you think you can just run away?\""s));
                        cdata[cc].enemy_id = tc;
                        cdata[cc].hate = 20;
                    }
                }
            }
            if (cdata[tc].gold <= 0)
            {
                cdata[tc].gold = 1;
            }
            sexvalue = cdata[tc].gold;
        }
        cdata[tc].gold -= sexvalue;
        if (cc == 0)
        {
            chara_mod_impression(tc, 5);
            flt();
            itemcreate(
                -1, 54, cdata[cc].position.x, cdata[cc].position.y, sexvalue);
            txt(i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground"));
            modify_karma(0, -1);
        }
        else
        {
            cdata[cc].gold += sexvalue;
        }
    }
    rowactend(cc);
    rowactend(tc);
    return;
}


void continuous_action_blending()
{
label_19341_internal:
    rpid = rpref(0);
    if (rpid == 0)
    {
        rowactend(cc);
        return;
    }
    if (cdata[cc].continuous_action_id == 0)
    {
        txtnew();
        txt(i18n::s.get("core.locale.blending.started", cdata[cc], rpname(rpid)));
        cdata[cc].continuous_action_id = 12;
        cdata[cc].continuous_action_turn = rpref(2) % 10000;
        return;
    }
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (rnd(30) == 0)
        {
            txtef(4);
            txt(i18n::s.get_enum("core.locale.blending.sounds", rnd(2)));
        }
        return;
    }
    if (rpref(2) >= 10000)
    {
        cdata[cc].continuous_action_turn = rpref(2) / 10000;
        for (int cnt = 0;; ++cnt)
        {
            mode = 12;
            ++gdata_hour;
            weather_changes();
            render_hud();
            if (cnt % 5 == 0)
            {
                txtef(4);
                txt(i18n::s.get_enum("core.locale.blending.sounds", rnd(2)));
            }
            redraw();
            await(config::instance().animewait * 5);
            gdata_minute = 0;
            cc = 0;
            --cdata[cc].continuous_action_turn;
            if (cdata[cc].continuous_action_turn <= 0)
            {
                int stat = label_1931();
                if (stat == 0)
                {
                    txt(i18n::s.get("core.locale.blending.required_material_not_found"));
                    break;
                }
                label_1933();
                if (rpref(1) > 0)
                {
                    cdata[cc].continuous_action_turn = rpref(2) / 10000;
                    cnt = 0 - 1;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        rowactend(cc);
        mode = 0;
        return;
    }
    int stat = label_1931();
    if (stat == 0)
    {
        txt(i18n::s.get("core.locale.blending.required_material_not_found"));
        rowactend(cc);
        return;
    }
    label_1933();
    if (rpref(1) > 0)
    {
        cdata[cc].continuous_action_id = 0;
        goto label_19341_internal;
    }
    rowactend(cc);
    return;
}

void continuous_action_others()
{
    if (cc != 0)
    {
        rowactend(cc);
        return;
    }
    if (cdata[cc].continuous_action_id == 0)
    {
        cdata[cc].continuous_action_id = 10;
        cdata[cc].continuous_action_item = ci;
        cdata[cc].continuous_action_target = tc;
        if (gdata(91) == 105)
        {
            txt(lang(
                itemname(ci, 1) + u8"に目星をつけた。"s,
                u8"You target "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn =
                2 + clamp(inv[ci].weight / 500, 0, 50);
        }
        if (gdata(91) == 100)
        {
            if (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)
            {
                txt(lang(u8"寝る仕度を始めた。"s, u8"You lie down."s));
                cdata[cc].continuous_action_turn = 5;
            }
            else
            {
                txt(lang(u8"露営の準備を始めた。"s, u8"You start to camp."s));
                cdata[cc].continuous_action_turn = 20;
            }
        }
        if (gdata(91) == 101)
        {
            txt(lang(
                itemname(ci, 1) + u8"の建設を始めた。"s,
                u8"You start to construct "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn = 25;
        }
        if (gdata(91) == 102)
        {
            txt(lang(
                itemname(ci, 1) + u8"のハッチを回し始めた。"s,
                u8"You start to pull the hatch."s));
            cdata[cc].continuous_action_turn = 10;
        }
        if (gdata(91) == 103)
        {
            txt(lang(
                itemname(ci, 1) + u8"を掘り始めた。"s,
                u8"You start to pick "s + itemname(ci, 1) + u8"."s));
            cdata[cc].continuous_action_turn = 10
                + clamp(inv[ci].weight
                            / (1 + sdata(10, 0) * 10 + sdata(180, 0) * 40),
                        1,
                        100);
        }
        if (gdata(91) == 104)
        {
            if (gdata_weather == 0 || gdata_weather == 3)
            {
                if (gdata_time_when_textbook_becomes_available > gdata_hour
                        + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12)
                {
                    txt(lang(u8"もう飽きた。"s, u8"You are bored."s));
                    rowactend(cc);
                    return;
                }
            }
            gdata_time_when_textbook_becomes_available = gdata_hour
                + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12 + 48;
            if (inv[ci].id == 563)
            {
                txt(lang(
                    i18n::_(
                        u8"ability", std::to_string(inv[ci].param1), u8"name")
                        + u8"の学習を始めた。"s,
                    u8"You begin to study "s
                        + i18n::_(
                              u8"ability",
                              std::to_string(inv[ci].param1),
                              u8"name")
                        + u8"."s));
            }
            else
            {
                txt(lang(
                    u8"トレーニングを始めた。"s, u8"You start training."s));
            }
            if (gdata_weather != 0 && gdata_weather != 3)
            {
                if (gdata_current_map == 30
                    || (mdata(14) == 1
                        && (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)))
                {
                    txt(lang(
                        u8"外が悪天候なので、じっくりと取り組むことにした。"s,
                        u8"The weather's bad outside, you have plenty of time to waste."s));
                }
            }
            cdata[cc].continuous_action_turn = 50;
        }
        update_screen();
        return;
    }
    tc = cdata[cc].continuous_action_target;
    if (cdata[cc].continuous_action_turn > 0)
    {
        if (gdata(91) == 103)
        {
            if (rnd(5) == 0)
            {
                skillexp(180, 0, 20, 4);
            }
            if (rnd(6) == 0)
            {
                if (rnd(55) > sdata.get(10, cc).original_level + 25)
                {
                    skillexp(10, cc, 50);
                }
            }
            if (rnd(8) == 0)
            {
                if (rnd(55) > sdata.get(11, cc).original_level + 28)
                {
                    skillexp(11, cc, 50);
                }
            }
            if (rnd(10) == 0)
            {
                if (rnd(55) > sdata.get(15, cc).original_level + 30)
                {
                    skillexp(15, cc, 50);
                }
            }
            if (rnd(4) == 0)
            {
                txtef(9);
                if (jp)
                {
                    txt(u8" *ザクッ* "s,
                        u8" *♪* "s,
                        u8" *ズシュ* "s,
                        u8" *ジャリ* "s);
                }
                if (en)
                {
                    txt(u8"*sing*"s,
                        u8"*pull*"s,
                        u8"*thud*"s,
                        u8"*rumble*"s,
                        u8"*gasp*"s);
                }
            }
        }
        if (gdata(91) == 104)
        {
            p = 25;
            if (gdata_weather != 0 && gdata_weather != 3)
            {
                if (gdata_current_map == 30)
                {
                    p = 5;
                }
                if (gdata_current_map != 30 && mdata(14) == 1)
                {
                    if (mdata(6) == 5 || mdata(6) == 3 || mdata(6) == 2)
                    {
                        p = 5;
                        gdata_minute += 30;
                    }
                }
            }
            if (inv[ci].id == 563)
            {
                if (rnd(p) == 0)
                {
                    skillexp(inv[ci].param1, cc, 25);
                }
            }
            else if (rnd(p) == 0)
            {
                skillexp(randattb(), cc, 25);
            }
        }
        if (gdata(91) == 105)
        {
            if (inv[ci].id == 688)
            {
                if (rnd(15) == 0)
                {
                    rowactend(cc);
                    txt(lang(
                        u8"突然ふたが閉まった！"s,
                        u8"Suddenly, the iron maiden falls forward."s));
                    dmghp(cc, 9999, -18);
                    return;
                }
            }
            if (inv[ci].id == 689)
            {
                if (rnd(15) == 0)
                {
                    rowactend(cc);
                    txt(lang(
                        u8"突然ギロチンが落ちてきた！"s,
                        u8"Suddenly, the guillotine is activated."s));
                    dmghp(cc, 9999, -19);
                    return;
                }
            }
            f = 0;
            f2 = 0;
            tg = inv_getowner(ci);
            if (tg != -1)
            {
                if (cdata[tg].original_relationship == -3)
                {
                    f2 = 1;
                }
            }
            i = sdata(300, 0) * 5 + sdata(12, 0) + 25;
            if (gdata_hour >= 19 || gdata_hour < 7)
            {
                i = i * 15 / 10;
            }
            if (inv[ci].quality == 3)
            {
                i = i * 8 / 10;
            }
            if (inv[ci].quality >= 4)
            {
                i = i * 5 / 10;
            }
            make_sound(cdata[0].position.x, cdata[0].position.y, 5, 8);
            for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].sleep != 0)
                {
                    continue;
                }
                if (dist(
                        cdata[cnt].position.x,
                        cdata[cnt].position.y,
                        cdata[0].position.x,
                        cdata[0].position.y)
                    > 5)
                {
                    continue;
                }
                if (f2 == 1)
                {
                    if (cnt != tg)
                    {
                        continue;
                    }
                }
                p = rnd((i + 1))
                    * (80 + (is_in_fov(cnt) == 0) * 50
                       + dist(
                             cdata[cnt].position.x,
                             cdata[cnt].position.y,
                             cdata[0].position.x,
                             cdata[0].position.y)
                           * 20)
                    / 100;
                if (cnt < 57)
                {
                    p = p * 2 / 3;
                }
                if (rnd(sdata(13, cnt) + 1) > p)
                {
                    if (is_in_fov(cnt))
                    {
                        txt(lang(
                            name(cnt) + u8"は窃盗を見咎めた。"s,
                            name(cnt) + u8" notice"s + _s(cnt) + u8" you,"s));
                    }
                    else
                    {
                        txt(lang(
                            name(cnt) + u8"は不振な物音に気づいた。"s,
                            name(cnt) + u8" hear"s + _s(cnt)
                                + u8" loud noise,"s));
                    }
                    if (cdata[cnt].character_role == 14)
                    {
                        txt(lang(
                            u8"「貴様、何をしている！」"s,
                            u8"\"You there, stop!\""s));
                        chara_mod_impression(cnt, -5);
                    }
                    else
                    {
                        txt(lang(
                            u8"「ガード！ガード！」"s,
                            u8"\"Guards! Guards!\""s));
                        chara_mod_impression(cnt, -5);
                    }
                    cdata[cnt].emotion_icon = 520;
                    f = 1;
                }
            }
            if (f)
            {
                txt(lang(
                    u8"盗みを見咎められた！"s, u8"You are found stealing."s));
                modify_karma(0, -5);
                p = inv_getowner(ci);
                if (tg != -1)
                {
                    if (cdata[p].id != 202)
                    {
                        if (cdata[tg].sleep == 0)
                        {
                            cdata[tg].relationship = -2;
                            hostileaction(0, tg);
                            chara_mod_impression(tg, -20);
                        }
                    }
                }
                go_hostile();
            }
            if (tg != -1)
            {
                if (cdata[tg].state != 1)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"対象は死んでいる"s, u8"The target is dead."s));
                        f = 1;
                    }
                }
                if (cdata[tg].character_role == 20)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"それは盗めない。"s, u8"It can't be stolen."s));
                        f = 1;
                    }
                }
                if (dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tg].position.x,
                        cdata[tg].position.y)
                    >= 3)
                {
                    if (f != 1)
                    {
                        txt(lang(
                            u8"対象が見当たらない。"s,
                            u8"You lose the target."s));
                        f = 0;
                    }
                }
            }
            if (inv[ci].number <= 0)
            {
                f = 1;
            }
            if (ibit(5, ci) == 1)
            {
                if (f != 1)
                {
                    txt(lang(u8"それは盗めない。"s, u8"It can't be stolen."s));
                    f = 1;
                }
            }
            if (inv[ci].weight >= sdata(10, 0) * 500)
            {
                if (f != 1)
                {
                    txt(lang(
                        u8"重すぎて手に負えない。"s, u8"It's too heavy."s));
                    f = 1;
                }
            }
            if (itemusingfind(ci, true) != -1)
            {
                if (f != 1)
                {
                    txt(lang(
                        u8"そのアイテムは他の誰かが使用中だ。"s,
                        u8"Someone else is using the item."s));
                    f = 1;
                }
            }
            if (f)
            {
                txt(lang(u8"行動を中断した。"s, u8"You abort stealing."s));
                rowactend(cc);
            }
        }
        return;
    }
    if (gdata(91) == 105)
    {
        tg = inv_getowner(ci);
        if ((tg != -1 && cdata[tg].state != 1) || inv[ci].number <= 0)
        {
            txt(lang(u8"行動を中断した。"s, u8"You abort stealing."s));
            rowactend(cc);
            return;
        }
        in = 1;
        if (inv[ci].id == 54)
        {
            in = inv[ci].number;
        }
        ti = inv_getfreeid(0);
        if (ti == -1)
        {
            txt(lang(
                u8"バックパックには、もうアイテムを入れる余裕がない。"s,
                u8"Your inventory is full."s));
            return;
        }
        ibitmod(12, ci, 0);
        if (inv[ci].body_part != 0)
        {
            tc = inv_getowner(ci);
            if (tc != -1)
            {
                p = inv[ci].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
            }
            inv[ci].body_part = 0;
            chara_refresh(tc);
        }
        item_copy(ci, ti);
        inv[ti].number = in;
        ibitmod(9, ti, 1);
        inv[ti].own_state = 0;
        inv[ci].number -= in;
        if (inv[ci].number <= 0)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        txt(lang(
            itemname(ti) + u8"を盗んだ。"s,
            u8"You successfully steal "s + itemname(ti) + u8"."s));
        if (inv[ci].id == 54)
        {
            snd(11);
            item_remove(inv[ti]);
            cdata[0].gold += in;
        }
        else
        {
            item_stack(0, ti, 1);
            snd(14 + rnd(2));
        }
        refresh_burden_state();
        skillexp(300, 0, clamp(inv[ti].weight / 25, 0, 450) + 50);
        if (cdata[0].karma >= -30)
        {
            if (rnd(3) == 0)
            {
                txt(lang(
                    u8"あなたは良心の呵責を感じた。"s,
                    u8"You feel the stings of conscience."s));
                modify_karma(0, -1);
            }
        }
    }
    if (gdata(91) == 100)
    {
        txt(lang(u8"あなたは眠り込んだ。"s, u8"You fall asleep."s));
        label_2151();
    }
    if (gdata(91) == 101)
    {
        snd(58);
        txt(lang(
            itemname(ci, 1) + u8"を作り終えた。"s,
            u8"You finish constructing"s + itemname(ci, 1) + u8"."s));
        in = 1;
        dropval = 1;
        drop_item();
    }
    if (gdata(91) == 102)
    {
        txt(lang(
            itemname(ci, 1) + u8"のハッチを回し終えた。"s,
            u8"You finish pulling the hatch of "s + itemname(ci, 1) + u8"."s));
        chatteleport = 1;
        gdata_previous_map2 = gdata_current_map;
        gdata_previous_dungeon_level = gdata_current_dungeon_level;
        gdata_previous_x = cdata[0].position.x;
        gdata_previous_y = cdata[0].position.y;
        gdata_destination_map = 30;
        gdata_destination_dungeon_level = inv[ci].count;
        levelexitby = 2;
        snd(49);
    }
    if (gdata(91) == 103)
    {
        txt(lang(
            itemname(ci, 1) + u8"を収穫した("s + cnvweight(inv[ci].weight)
                + u8")"s,
            u8"You harvest "s + itemname(ci, 1) + u8". ("s
                + cnvweight(inv[ci].weight) + u8")"s));
        in = inv[ci].number;
        pick_up_item();
    }
    if (gdata(91) == 104)
    {
        if (inv[ci].id == 563)
        {
            txt(lang(
                i18n::_(u8"ability", std::to_string(inv[ci].param1), u8"name")
                    + u8"の学習を終えた。"s,
                u8"You finish studying "s
                    + i18n::_(
                          u8"ability", std::to_string(inv[ci].param1), u8"name")
                    + u8"."s));
        }
        else
        {
            txt(lang(u8"トレーニングを終えた。"s, u8"You finish training."s));
        }
    }
    rowactend(cc);
    return;
}

} // namespace elona
