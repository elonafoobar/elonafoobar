#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
int label_2176()
{
    efcibk = ci;
    efcancel = 0;
    obvious = 1;
    if (efsource != 4 && efsource != 1 && efsource != 2)
    {
        efstatus = 0;
    }
    efsource = 0;
    efbad = 0;
    if (efid >= 300)
    {
        if (efid < 661)
        {
            f = 0;
            if (sdataref(1, efid) / 1000 == 1)
            {
                f = 1;
                p = sdataref(1, efid) % 1000;
                if (bdataref(0, p) == 2)
                {
                    efbad = 1;
                }
            }
            if (sdataref(1, efid) == 7)
            {
                efbad = 1;
            }
            if (efbad == 0)
            {
                if (efstatus >= 1)
                {
                    efp = efp * 150 / 100;
                }
                if (efstatus <= -1)
                {
                    efp = 50;
                }
            }
            else
            {
                if (efstatus >= 1)
                {
                    efp = 50;
                }
                if (efstatus <= -1)
                {
                    efp = efp * 150 / 100;
                }
            }
            if (f)
            {
                if (bdataref(0, p) == 1)
                {
                    animeload(11, tc);
                }
                else if (bdataref(0, p) == 2)
                {
                    animeid = 6;
                    label_1426();
                }
                if (efid == 625 || efid == 446)
                {
                    if (tc == 0 && cc == 0 || cc == gdata(183))
                    {
                        if (gdata(183) != 0)
                        {
                            tc = gdata(183);
                        }
                    }
                }
                calcbuff(-1, p, efp);
                addbuff(tc, p, efp, dur);
                if (efid == 447)
                {
                    if (efstatus >= 1)
                    {
                        cdata_birth_year(tc) += rnd(3) + 1;
                        if (cdata_birth_year(tc) + 12 > gdata(10))
                        {
                            cdata_birth_year(tc) = gdata(10) - 12;
                        }
                        if (synccheck(tc, -1))
                        {
                            txtef(2);
                            txt(lang(
                                name(tc) + u8"の老化は遅くなった。"s,
                                name(tc) + your(tc)
                                    + u8" aging process slows down."s));
                        }
                    }
                }
                if (efid == 446)
                {
                    if (efstatus <= -1)
                    {
                        cdata_birth_year(tc) -= rnd(3) + 1;
                        if (synccheck(tc, -1))
                        {
                            txtef(8);
                            txt(lang(
                                name(tc) + u8"の老化は速くなった。"s,
                                name(tc) + your(tc)
                                    + u8" aging process speeds up."s));
                        }
                    }
                }
                if (efid == 458)
                {
                    if (tc == 0)
                    {
                        incognitobegin();
                    }
                }
                goto label_2186_internal;
            }
            calcskill(efid, cc, efp);
            if (cc == 0)
            {
                if (trait(165))
                {
                    if (ele == 50 || ele == 51 || ele == 52)
                    {
                        dice2 = dice2 * 125 / 100;
                    }
                }
            }
            if (rapidmagic)
            {
                efp = efp / 2 + 1;
                dice1 = dice1 / 2 + 1;
                dice2 = dice2 / 2 + 1;
                bonus = bonus / 2 + 1;
            }
            switch (sdataref(1, efid))
            {
            case 10:
                animeid = 18;
                label_1426();
                label_2218();
                goto label_2186_internal;
            case 1:
            {
                int stat = get_route(cdata_x(cc), cdata_y(cc), tlocx, tlocy);
                if (stat == 0)
                {
                    goto label_2186_internal;
                }
            }
                animeid = 0;
                label_1426();
                dx = cdata_x(cc);
                dy = cdata_y(cc);
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt)
                    {
                        int stat = route_info(dx, dy, cnt);
                        if (stat == 0)
                        {
                            break;
                        }
                        else if (stat == -1)
                        {
                            continue;
                        }
                        if (dist(dx, dy, cdata_x(cc), cdata_y(cc))
                            > sdataref(3, efid) % 1000 + 1)
                        {
                            break;
                        }
                        if (dx == cdata_x(cc) && dy == cdata_y(cc))
                        {
                            continue;
                        }
                        if (ele == 50)
                        {
                            mapitem_fire(dx, dy);
                        }
                        if (ele == 51)
                        {
                            mapitem_cold(dx, dy);
                        }
                        if (map(dx, dy, 1) != 0)
                        {
                            tc = map(dx, dy, 1) - 1;
                            if (cc != tc)
                            {
                                if (gdata(183) != 0)
                                {
                                    if (gdata(183) == cc)
                                    {
                                        if (tc == 0)
                                        {
                                            continue;
                                        }
                                    }
                                }
                                dmg = role(dice1, dice2, bonus);
                                int stat = calcmagiccontrol(cc, tc);
                                if (stat == 1)
                                {
                                    continue;
                                }
                                if (synccheck(tc, -1))
                                {
                                    txtmore();
                                    if (tc >= 16)
                                    {
                                        gdata(809) = 2;
                                        txt3rd = 1;
                                        txt(lang(
                                            u8"ボルトは"s + name(tc)
                                                + u8"に命中し"s,
                                            u8"The bolt hits "s + name(tc)
                                                + u8" and"s));
                                    }
                                    else
                                    {
                                        txt(lang(
                                            u8"ボルトが"s + name(tc)
                                                + u8"に命中した。"s,
                                            u8"The bolt hits "s + name(tc)
                                                + u8"."s));
                                    }
                                }
                                dmghp(tc, dmg, cc, ele, elep);
                            }
                        }
                    }
                }
                goto label_2186_internal;
            case 3:
                chainbomb = 0;
                ccbk = cc;
                if (efid == 644)
                {
                    stxt(
                        cc,
                        lang(
                            name(cc) + u8"は爆発した。"s,
                            name(cc) + u8" explode"s + _s(cc) + u8"."s));
                }
            label_2177_internal:
                cbitmod(972, cc, 0);
                range = sdataref(3, efid) % 1000 + 1;
                if (efid == 644)
                {
                    range = 2;
                }
                if (efid != 404 && efid != 637)
                {
                    aniref = range;
                    animeid = 2;
                    anix = tlocx;
                    aniy = tlocy;
                    label_1426();
                }
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (range * 2 + 1); cnt < cnt_end;
                         ++cnt)
                    {
                        dy = tlocy - range + cnt;
                        if (dy < 0 || dy >= mdata(1))
                        {
                            continue;
                        }
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (range * 2 + 1);
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                dx = tlocx - range + cnt;
                                if (dx < 0 || dx >= mdata(0))
                                {
                                    continue;
                                }
                                if (dist(tlocx, tlocy, dx, dy) > range)
                                {
                                    continue;
                                }
                                if (fov_los(tlocx, tlocy, dx, dy) == 0)
                                {
                                    continue;
                                }
                                if (map(dx, dy, 1) == 0)
                                {
                                    continue;
                                }
                                tc = map(dx, dy, 1) - 1;
                                if (efid == 404)
                                {
                                    f = 0;
                                    if (cc == 0 || cdata_relationship(cc) >= 0)
                                    {
                                        if (cdata_relationship(tc) >= 0)
                                        {
                                            f = 1;
                                        }
                                    }
                                    else if (cdata_relationship(tc) <= -1)
                                    {
                                        f = 1;
                                    }
                                    if (f == 1)
                                    {
                                        animeid = 11;
                                        label_1426();
                                        if (synccheck(tc, -1))
                                        {
                                            txt(lang(
                                                name(tc) + u8"は回復した。"s,
                                                name(tc) + u8" "s + is(tc)
                                                    + u8" healed."s));
                                        }
                                        label_2187();
                                    }
                                    continue;
                                }
                                if (efid == 637)
                                {
                                    f = 0;
                                    if (cc == 0 || cdata_relationship(cc) >= 0)
                                    {
                                        if (cdata_relationship(tc) >= 0)
                                        {
                                            f = 1;
                                        }
                                    }
                                    else if (cdata_relationship(tc) <= -1)
                                    {
                                        f = 1;
                                    }
                                    if (f == 1)
                                    {
                                        animeid = 11;
                                        label_1426();
                                        txt(lang(
                                            name(tc)
                                                + u8"の狂気は消え去った。"s,
                                            name(tc) + u8" "s + is(tc)
                                                + u8" completely sane again."s));
                                        healsan(tc, efp / 10);
                                        healcon(tc, 11, 9999);
                                    }
                                    continue;
                                }
                                if (dx == cdata_x(cc) && dy == cdata_y(cc))
                                {
                                    continue;
                                }
                                if (gdata(183) != 0)
                                {
                                    if (gdata(183) == cc)
                                    {
                                        if (tc == 0)
                                        {
                                            continue;
                                        }
                                    }
                                }
                                if (ele == 50)
                                {
                                    mapitem_fire(dx, dy);
                                }
                                if (ele == 51)
                                {
                                    mapitem_cold(dx, dy);
                                }
                                if (cc != tc)
                                {
                                    dmg = role(dice1, dice2, bonus) * 100
                                        / (75
                                           + dist(tlocx, tlocy, dx, dy) * 25);
                                    txtmore();
                                    int stat = calcmagiccontrol(cc, tc);
                                    if (stat == 1)
                                    {
                                        continue;
                                    }
                                    if (efid == 644)
                                    {
                                        if (synccheck(tc, -1))
                                        {
                                            txtmore();
                                            if (tc >= 16)
                                            {
                                                gdata(809) = 2;
                                                txt3rd = 1;
                                                txt(lang(
                                                    u8"爆風は"s + name(tc)
                                                        + u8"に命中し"s,
                                                    u8"The explosion hits "s
                                                        + name(tc)
                                                        + u8" and"s));
                                            }
                                            else
                                            {
                                                txt(lang(
                                                    u8"爆風が"s + name(tc)
                                                        + u8"に命中した。"s,
                                                    u8"The explosion hits "s
                                                        + name(tc) + u8"."s));
                                            }
                                        }
                                        if (cbit(18, tc))
                                        {
                                            chainbomblist(chainbomb) = tc;
                                            ++chainbomb;
                                            continue;
                                        }
                                    }
                                    else if (synccheck(tc, -1))
                                    {
                                        txtmore();
                                        if (tc >= 16)
                                        {
                                            gdata(809) = 2;
                                            txt3rd = 1;
                                            txt(lang(
                                                u8"ボールは"s + name(tc)
                                                    + u8"に命中し"s,
                                                u8"The ball hits "s + name(tc)
                                                    + u8" and"s));
                                        }
                                        else
                                        {
                                            txt(lang(
                                                u8"ボールが"s + name(tc)
                                                    + u8"に命中した。"s,
                                                u8"The Ball hits "s + name(tc)
                                                    + u8"."s));
                                        }
                                    }
                                    dmghp(tc, dmg, cc, ele, elep);
                                }
                            }
                        }
                    }
                }
                if (efid == 644)
                {
                    dmghp(cc, 99999, -16);
                }
                if (chainbomb > 0)
                {
                label_2178_internal:
                    --chainbomb;
                    if (chainbomb < 0)
                    {
                        goto label_2179_internal;
                    }
                    cc = chainbomblist(chainbomb);
                    tlocx = cdata_x(cc);
                    tlocy = cdata_y(cc);
                    if (cdata_state(cc) == 1)
                    {
                        calcskill(efid, cc, efp);
                        stxt(
                            cc,
                            lang(
                                name(cc) + u8"は誘爆した。"s,
                                name(cc) + u8" explode"s + _s(cc) + u8"."s));
                        goto label_2177_internal;
                    }
                    goto label_2178_internal;
                }
            label_2179_internal:
                cc = ccbk;
                goto label_2186_internal;
            case 2:
                animeid = 1;
                label_1426();
                dmg = role(dice1, dice2, bonus);
                if (synccheck(tc, -1))
                {
                    txtmore();
                    if (tc >= 16)
                    {
                        gdata(809) = 2;
                        txt3rd = 1;
                        txt(lang(
                            u8"矢は"s + name(tc) + u8"に命中し"s,
                            u8"The arrow hits "s + name(tc) + u8" and"s));
                    }
                    else
                    {
                        txt(lang(
                            u8"矢が"s + name(tc) + u8"に命中した。"s,
                            u8"The arrow hits "s + name(tc) + u8"."s));
                    }
                }
                dmghp(tc, dmg, cc, ele, elep);
                goto label_2186_internal;
            case 4:
                if (efid == 400)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            name(tc) + u8"の傷はふさがった。"s,
                            name(tc) + u8" "s + is(tc)
                                + u8" slightly healed."s));
                    }
                }
                if (efid == 401 || efid == 405)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            name(tc) + u8"は回復した。"s,
                            name(tc) + u8" "s + is(tc) + u8" healed."s));
                    }
                }
                if (efid == 402)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            name(tc) + u8"の身体に生命力がみなぎった。"s,
                            name(tc) + u8" "s + is(tc)
                                + u8" greatly healed."s));
                    }
                }
                if (efid == 403)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            name(tc) + u8"は完全に回復した。"s,
                            name(tc) + u8" "s + is(tc)
                                + u8" completely healed."s));
                    }
                }
                label_2187();
                if (efstatus >= 1)
                {
                    healcon(tc, 12, 5 + rnd(5));
                }
                sickifcursed(efstatus, tc, 3);
                animeid = 5;
                label_1426();
                goto label_2186_internal;
            case 6:
                if (cdata_special_attack_type(cc) != 0)
                {
                    if (synccheck(cc, -1))
                    {
                        if (cc == 0)
                        {
                            txt(lang(
                                name(cc) + u8"は"s + skillname(efid) + u8"の"s
                                    + _cast(cdata_special_attack_type(cc)),
                                name(cc) + u8" cast "s + skillname(efid)
                                    + u8"."s));
                            txtmore();
                        }
                        else
                        {
                            txt(lang(
                                name(cc) + u8"は"s
                                    + _cast(cdata_special_attack_type(cc)),
                                name(cc) + ""s
                                    + _cast(cdata_special_attack_type(cc))));
                            txtmore();
                        }
                    }
                }
                else if (efid == 601)
                {
                    if (synccheck(cc, -1))
                    {
                        if (tc >= 16)
                        {
                            gdata(809) = 2;
                            txt(lang(
                                aln(cc) + name(tc) + u8"の血を吸い"s,
                                name(cc) + u8" suck"s + _s(cc) + u8" "s
                                    + name(tc) + your(tc) + u8" blood and"s));
                        }
                        else
                        {
                            txt(lang(
                                name(cc) + u8"に血を吸われた。"s,
                                name(cc) + u8" suck"s + _s(cc) + u8" "s
                                    + name(tc) + your(tc) + u8" blood."s));
                        }
                    }
                }
                else if (synccheck(cc, -1))
                {
                    if (tc >= 16)
                    {
                        gdata(809) = 2;
                        txt(lang(
                            aln(cc) + name(tc) + u8"を"s + elename(ele)
                                + _melee(2, cdata_melee_attack_type(cc))
                                + u8"で"s
                                + _melee(0, cdata_melee_attack_type(cc)),
                            name(cc) + u8" touch"s + _s(cc) + u8" "s + name(tc)
                                + u8" with "s + his(cc) + u8" "s + elename(ele)
                                + u8" "s
                                + _melee(2, cdata_melee_attack_type(cc))
                                + u8" and"s));
                    }
                    else
                    {
                        txt(lang(
                            name(tc) + u8"は"s + name(cc) + u8"に"s
                                + elename(ele)
                                + _melee(2, cdata_melee_attack_type(cc))
                                + u8"で"s
                                + _melee(1, cdata_melee_attack_type(cc)),
                            name(cc) + u8" touch"s + _s(cc) + u8" "s + name(tc)
                                + u8" with "s + his(cc) + u8" "s + elename(ele)
                                + u8" "s
                                + _melee(2, cdata_melee_attack_type(cc))
                                + u8"."s));
                    }
                }
                if (efid == 660)
                {
                    txt(lang(
                        u8"「余分な機能は削除してしまえ」"s,
                        cnvtalk(u8"Delete."s)));
                    cdata_hp(tc) = cdata_max_hp(tc) / 12 + 1;
                    goto label_2186_internal;
                }
                dmghp(tc, role(dice1, dice2, bonus), cc, ele, elep);
                if (efid == 617)
                {
                    dmgcon(tc, 6, elep);
                }
                if (efid == 618)
                {
                    dmgcon(tc, 2, elep);
                }
                if (efid == 614)
                {
                    cdata_nutrition(tc) -= 800;
                    if (synccheck(tc, -1))
                    {
                        txtmore();
                        txtef(8);
                        txt(lang(
                            name(tc) + u8"はお腹が減った。"s,
                            u8"Suddenly "s + name(tc) + u8" feel"s + _s(tc)
                                + u8" hungry."s));
                    }
                    r1 = tc;
                    label_1519();
                }
                if (efid == 613)
                {
                    p = rnd(10);
                    if (cdata_quality(tc) >= 4 && rnd(4)
                        || encfind(tc, 60010 + p) != -1)
                    {
                        p = -1;
                    }
                    if (p != -1)
                    {
                        i = sorg(10 + p, tc) - cdata((240 + p), tc);
                        if (i > 0)
                        {
                            i = i * efp / 2000 + 1;
                            cdata(240 + p, tc) -= i;
                        }
                        if (synccheck(tc, -1))
                        {
                            txtmore();
                            txtef(8);
                            txt(lang(
                                name(tc) + u8"は弱くなった。"s,
                                name(tc) + u8" "s + is(tc) + u8" weakened."s));
                        }
                        r1 = tc;
                        label_1477();
                    }
                }
                goto label_2186_internal;
            case 7:
                if (cc == 0)
                {
                    if (gdata(3) + 100 >= 188)
                    {
                        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                        obvious = 0;
                        goto label_2186_internal;
                    }
                }
                p = 3;
                efp = (efp / 25 + efp * efp / 10000 + cdata_level(cc)) / 2;
                if (efp < 1)
                {
                    efp = 1;
                }
                if (efid == 641)
                {
                    efp = 15 + rnd(8);
                }
                if (efid == 639)
                {
                    efp = 2 + rnd(18);
                }
                if (efid == 642)
                {
                    efp = 15 + rnd(15);
                }
                if (efid == 640)
                {
                    efp = 5 + rnd(12);
                }
                if (efid == 643)
                {
                    p = 10;
                }
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (1 + rnd(p)); cnt < cnt_end; ++cnt)
                    {
                        flt(calcobjlv(efp), 2);
                        dbid = 0;
                        if (efid == 425)
                        {
                            fltn(u8"wild"s);
                        }
                        if (efid == 642)
                        {
                            fltn(u8"fire"s);
                        }
                        if (efid == 641)
                        {
                            fltn(u8"pawn"s);
                        }
                        if (efid == 639)
                        {
                            fltn(u8"cat"s);
                        }
                        if (efid == 640)
                        {
                            fltn(u8"yeek"s);
                        }
                        if (efid == 643)
                        {
                            dbid = 176;
                        }
                        characreate(-1, dbid, cdata_x(tc), cdata_y(tc));
                        if (efid != 643)
                        {
                            if (cdata_id(rc) == cdata_id(cc))
                            {
                                chara_vanquish(rc);
                                --cnt;
                                continue;
                            }
                        }
                    }
                }
                if (synccheck(cc, -1))
                {
                    txt(lang(
                        u8"魔法でモンスターが召喚された。"s,
                        u8"Several monsters come out from a portal."s));
                }
                goto label_2186_internal;
            case 5:
                tcprev = tc;
                if (gdata(183) != 0)
                {
                    if (gdata(183) == tc)
                    {
                        goto label_2186_internal;
                    }
                }
                if (efid == 408)
                {
                    tc = cc;
                }
                if (efid == 619)
                {
                    telex = cdata_x(tc);
                    teley = cdata_y(tc);
                    tc = cc;
                }
                if (efid == 620)
                {
                    telex = cdata_x(cc);
                    teley = cdata_y(cc);
                }
                if (efid == 409 || efid == 635)
                {
                    if (map(tlocx, tlocy, 1) == 0)
                    {
                        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                        obvious = 0;
                        goto label_2186_internal;
                    }
                    tc = map(tlocx, tlocy, 1) - 1;
                }
                if (gdata(20) == 40 || mdata(6) == 1 || gdata(20) == 37
                    || gdata(20) == 41)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            u8"魔法の力がテレポートを防いだ。"s,
                            u8"Magical field prevents teleportation."s));
                    }
                    goto label_2186_internal;
                }
                if (efid == 619)
                {
                }
                else if (encfind(tc, 22) != -1)
                {
                    if (synccheck(tc, -1))
                    {
                        txt(lang(
                            u8"魔法の力がテレポートを防いだ。"s,
                            u8"Magical field prevents teleportation."s));
                    }
                    goto label_2186_internal;
                }
                if (efid == 635)
                {
                    if (tc == cc)
                    {
                        if (synccheck(tc, -1))
                        {
                            txt(lang(
                                u8"魔法の力がテレポートを防いだ。"s,
                                u8"Magical field prevents teleportation."s));
                        }
                        goto label_2186_internal;
                    }
                    p = rnd(cdata_gold(tc) / 10 + 1);
                    if (rnd(sdata(13, tc)) > rnd(sdata(12, tc) * 4)
                        || cbit(15, tc) == 1)
                    {
                        txt(lang(
                            name(tc) + u8"は自分の財布を守った。"s,
                            name(tc) + u8" guard"s + _s(tc) + u8" "s + his(tc)
                                + u8" wallet from a thief."s));
                        p = 0;
                    }
                    if (p != 0)
                    {
                        snd(12);
                        cdata_gold(tc) -= p;
                        txt(lang(
                            name(cc) + u8"は"s + name(tc) + u8"から"s + p
                                + u8"枚の金貨を奪った。"s,
                            name(cc) + u8" steal"s + _s(cc) + u8" "s + p
                                + u8" gold pieces from "s + name(tc) + u8"."s));
                        cdata_gold(cc) += p;
                    }
                    tc = cc;
                    if (gdata(183) != 0)
                    {
                        if (gdata(183) == tc)
                        {
                            goto label_2186_internal;
                        }
                    }
                }
                if (synccheck(tc, -1))
                {
                    snd(72);
                }
                tx = cdata_x(tc);
                ty = cdata_y(tc);
                efidprev = efid;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (200); cnt < cnt_end; ++cnt)
                    {
                        if (efidprev == 410 || efidprev == 627)
                        {
                            p(0) = -1;
                            p(1) = 1;
                            cdata_next_x(tc) = cdata_x(tc)
                                + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
                            cdata_next_y(tc) = cdata_y(tc)
                                + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
                        }
                        else if (efidprev == 619)
                        {
                            cdata_next_x(tc) =
                                telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                            cdata_next_y(tc) =
                                teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                        }
                        else if (efidprev == 620)
                        {
                            cdata_next_x(tc) =
                                telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                            cdata_next_y(tc) =
                                teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                        }
                        else
                        {
                            cdata_next_x(tc) = rnd(mdata(0) - 2) + 1;
                            cdata_next_y(tc) = rnd(mdata(1) - 2) + 1;
                        }
                        cell_check(cdata_next_x(tc), cdata_next_y(tc));
                        if (cellaccess == 1)
                        {
                            if (efidprev == 619)
                            {
                                if (synccheck(cc, -1))
                                {
                                    txt(lang(
                                        name(cc) + u8"は"s + cdatan(0, tcprev)
                                            + u8"の元に移動した。"s,
                                        name(cc) + u8" teleport"s + _s(cc)
                                            + u8" toward "s + cdatan(0, tcprev)
                                            + u8"."s));
                                }
                            }
                            else if (efidprev == 620)
                            {
                                if (synccheck(cc, -1))
                                {
                                    txtmore();
                                    txt(lang(
                                        name(tc) + u8"は引き寄せられた。"s,
                                        name(tc) + u8" "s + is(tc)
                                            + u8" drawn."s));
                                }
                            }
                            else if (synccheck(cc, -1))
                            {
                                if (efidprev == 635)
                                {
                                    txtmore();
                                    txt(lang(
                                        u8"泥棒は笑って逃げた。"s,
                                        u8"A thief escapes laughing."s));
                                }
                                else
                                {
                                    txt(lang(
                                        name(tc) + u8"は突然消えた。"s,
                                        u8"Suddenly, "s + name(tc)
                                            + u8" disappear"s + _s(tc)
                                            + u8"."s));
                                }
                            }
                            rowactend(cc);
                            ccprev = cc;
                            cc = tc;
                            label_21452();
                            cc = ccprev;
                            if (tc == 0)
                            {
                                label_1419();
                            }
                            break;
                        }
                    }
                }
                tc = tcprev;
                goto label_2186_internal;
            case 8:
                int stat = get_route(cdata_x(cc), cdata_y(cc), tlocx, tlocy);
                if (stat == 0)
                {
                    goto label_2186_internal;
                }
                if (ele)
                {
                    valn = skillname(ele) + lang(u8"の"s, u8" breath"s);
                }
                else
                {
                    valn = lang(""s, u8"breath"s);
                }
                if (synccheck(cc, -1))
                {
                    txt(lang(
                        name(cc) + u8"は"s + valn + u8"ブレスを吐いた。"s,
                        name(cc) + u8" bellow"s + _s(cc) + u8" "s + valn
                            + u8" from "s + his(cc) + u8" mouth."s));
                }
                dx = cdata_x(cc);
                dy = cdata_y(cc);
                breath_list();
                animeid = 3;
                label_1426();
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (maxbreath); cnt < cnt_end; ++cnt)
                    {
                        dx = breathlist(0, cnt);
                        dy = breathlist(1, cnt);
                        if (fov_los(cdata_x(cc), cdata_y(cc), dx, dy) == 0)
                        {
                            continue;
                        }
                        if (dx == cdata_x(cc) && dy == cdata_y(cc))
                        {
                            continue;
                        }
                        if (gdata(183) != 0)
                        {
                            if (gdata(183) == cc)
                            {
                                if (tc == 0)
                                {
                                    continue;
                                }
                            }
                        }
                        if (ele == 50)
                        {
                            mapitem_fire(dx, dy);
                        }
                        if (ele == 51)
                        {
                            mapitem_cold(dx, dy);
                        }
                        if (map(dx, dy, 1) != 0)
                        {
                            tc = map(dx, dy, 1) - 1;
                            if (cc != tc)
                            {
                                dmg = role(dice1, dice2, bonus);
                                if (synccheck(tc, -1))
                                {
                                    txtmore();
                                    if (tc >= 16)
                                    {
                                        gdata(809) = 2;
                                        txt3rd = 1;
                                        txt(lang(
                                            u8"ブレスは"s + name(tc)
                                                + u8"に命中し"s,
                                            u8"The breath hits "s + name(tc)
                                                + u8" and"s));
                                    }
                                    else
                                    {
                                        txt(lang(
                                            u8"ブレスは"s + name(tc)
                                                + u8"に命中した。"s,
                                            u8"The breath hits "s + name(tc)
                                                + u8"."s));
                                    }
                                }
                                dmghp(tc, dmg, cc, ele, elep);
                            }
                        }
                    }
                }
                goto label_2186_internal;
            }
            goto label_2181_internal;
            goto label_2186_internal;
        }
        else
        {
            if (efstatus >= 1)
            {
                efp = efp * 150 / 100;
            }
            if (efstatus <= -1)
            {
                efp = 50;
            }
        }
    }
label_2181_internal:
    switch (efid)
    {
    case 636:
        txtef(8);
        if (jp)
        {
            txt(name(tc) + u8"は"s + name(cc)
                    + u8"の腹の亀裂から蛆虫が沸き出るのを見た。"s,
                name(tc) + u8"は"s + name(cc) + u8"が屍を貪る姿を目撃した。"s,
                name(tc) + u8"は"s + name(cc) + u8"の恐ろしい瞳に震えた。"s,
                name(tc) + u8"は"s + name(cc)
                    + u8"の触手に絡まる臓物に吐き気を感じた。"s);
        }
        if (en)
        {
            txt(name(tc) + u8" see"s + _s(tc)
                    + u8" maggots breed in the rent stomach of "s + name(cc)
                    + u8"."s,
                name(tc) + u8" see"s + _s(tc) + u8" "s + name(cc) + u8" chow"s
                    + _s(cc) + u8" dead bodies."s,
                name(tc) + u8" shudder"s + _s(tc) + u8" at "s + name(cc)
                    + your(cc) + u8" terrifying eyes."s,
                name(tc) + u8" feel"s + _s(tc)
                    + u8" sick at entrails caught in "s + name(cc) + your(cc)
                    + u8" tentacles."s);
        }
        dmgsan(tc, rnd(role(dice1, dice2, bonus) + 1));
        goto label_2186_internal;
    case 1136:
        if (mdata(6) != 1)
        {
            txt(lang(
                u8"それはグローバルマップで読む必要がある。"s,
                u8"You need to read it while you are in the global map."s));
            goto label_2186_internal;
        }
        if (efstatus <= -1)
        {
            if (rnd(5) == 0)
            {
                txt(lang(
                    u8"呪われた地図は触れると崩れ落ちた。"s,
                    u8"The cursed map crumbles as you touch."s));
                --inv_number(ci);
                if (ci >= 5080)
                {
                    cell_refresh(inv_x(ci), inv_y(ci));
                }
                goto label_2186_internal;
            }
        }
        if (inv_param1(ci) == 0)
        {
            item_separate(ci);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (1000); cnt < cnt_end; ++cnt)
                {
                    dx = 4 + rnd((mdata(0) - 8));
                    dy = 3 + rnd((mdata(1) - 6));
                    if (dx >= 50 && dy >= 39 && dx <= 73 && dy <= 54)
                    {
                        continue;
                    }
                    x(0) = 1;
                    x(1) = -1;
                    x(2) = 0;
                    x(3) = 0;
                    y(0) = 0;
                    y(1) = 0;
                    y(2) = 1;
                    y(3) = -1;
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt)
                        {
                            f = 1;
                            cnt2 = cnt;
                            {
                                int cnt = 0;
                                for (int cnt_end = cnt + (3); cnt < cnt_end;
                                     ++cnt)
                                {
                                    p =
                                        map(dx + x(cnt2) * cnt,
                                            dy + y(cnt2) * cnt,
                                            0);
                                    if (264 <= p && p < 363 || chipm(7, p) & 4)
                                    {
                                        f = 0;
                                        break;
                                    }
                                }
                            }
                            if (f == 1)
                            {
                                break;
                            }
                        }
                    }
                    if (f == 1)
                    {
                        break;
                    }
                }
            }
            inv_param1(ci) = dx;
            inv_param2(ci) = dy;
        }
        txt(lang(
            u8"何かの場所を記した地図のようだ…"s,
            u8"There's a mark on the map..."s));
        snd(59);
        gsel(4);
        pos(0, 0);
        picload(fs::u8path(u8"./graphic/paper.bmp"), 1);
        gsel(0);
        redraw(0);
        ww = 400;
        wh = 300;
        wx = (windoww - ww) / 2 + inf_screenx;
        wy = winposy(wh);
        gmode(2);
        pos(wx, wy);
        gcopy(4, 0, 0, ww, wh);
        gmode(1, inf_tiles, inf_tiles);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
            {
                y = cnt + inv_param2(ci) - 2;
                sy = cnt * inf_tiles + wy + 26;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (7); cnt < cnt_end; ++cnt)
                    {
                        x = cnt + inv_param1(ci) - 3;
                        sx = cnt * inf_tiles + wx + 46;
                        p = map(x, y, 0);
                        pos(sx + 1, sy + 1);
                        gcopy(2, p % 33 * inf_tiles, p / 33 * inf_tiles);
                        if (x == inv_param1(ci))
                        {
                            if (y == inv_param2(ci))
                            {
                                pos(sx, sy);
                                font(
                                    lang(cfg_font1, cfg_font2), 40 - en * 2, 2);
                                color(255, 20, 20);
                                mes(lang(u8"○"s, u8"O"s));
                            }
                        }
                    }
                }
            }
        }
        gmode(2);
        pos(wx, wy);
        gcopy(4, 400, 0, ww, wh);
        redraw(1);
        press();
        snd(71);
        goto label_2186_internal;
    case 1135:
        if (efstatus <= -1)
        {
            if (tc == 0)
            {
                eatstatus(efstatus, tc);
            }
            else
            {
                txt(lang(
                    u8"媚薬は呪われていた。"s + name(tc) + u8"は"s + name(0)
                        + u8"を軽蔑のまなざしで見つめた。"s,
                    u8"This love potion is cursed. "s + name(tc) + u8" look"s
                        + _s(tc) + u8" at "s + name(0)
                        + u8" with a contemptuous glance."s));
                modimp(tc, -15);
            }
            obvious = 0;
            goto label_2186_internal;
        }
        cdata_emotion_icon(tc) = 317;
        if (potionspill || potionthrow)
        {
            txt(lang(
                name(tc) + u8"は恋の予感がした。"s,
                name(tc) + u8" sense"s + _s(tc) + u8" a sigh of love,"s));
            modimp(tc, limit(efp / 15, 0, 15));
            dmgcon(tc, 7, 100);
            lovemiracle(tc);
            goto label_2186_internal;
        }
        if (tc == 0)
        {
            txt(lang(name(tc) + u8"は興奮した！"s, u8"You are excited!"s));
        }
        else
        {
            txt(lang(
                name(tc) + u8"は"s + name(0) + u8"を熱いまなざしで見つめた。"s,
                name(tc) + u8" give"s + _s(tc) + u8" "s + name(0)
                    + u8" the eye."s));
            lovemiracle(tc);
            modimp(tc, limit(efp / 4, 0, 25));
        }
        dmgcon(tc, 7, 500);
        goto label_2186_internal;
    case 654:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(cc) + u8"は"s + name(tc)
                    + u8"の口の中に何かを送り込んだ！"s,
                name(cc) + u8" put"s + _s(cc) + u8" something into "s + name(tc)
                    + your(tc) + u8" body!"s));
        }
        label_1617();
        goto label_2186_internal;
    case 626:
        txt(lang(
            u8"あなたは自分の状態を調べた。"s, u8"You examine yourself."s));
        animeload(10, tc);
        label_1964();
        goto label_2186_internal;
    case 1101:
        if (synccheck(tc, -1))
        {
            snd(107);
            if (efstatus <= -1)
            {
                if (tc == 0)
                {
                    txt(lang(
                        u8"うわ、これは呪われている。なんだかやばい味だ…"s,
                        u8"Geee it's cursed! The taste is very dangerous."s));
                }
                else
                {
                    txtef(9);
                    txt(lang(
                        u8"「ぺっぺっ、まずー」"s,
                        cnvtalk(u8"Argh, the milk is cursed!"s)));
                }
            }
            else if (tc == 0)
            {
                txt(lang(
                    u8"濃厚で病み付きになりそうな味だ。"s,
                    u8"The taste is very thick, almost addictive."s));
            }
            else
            {
                txtef(9);
                txt(lang(u8"「うまー」"s, cnvtalk(u8"Yummy!"s)));
            }
        }
        if (efstatus >= 1)
        {
            modheight(tc, rnd(5) + 1);
        }
        if (efstatus <= -1)
        {
            modheight(tc, (rnd(5) + 1) * -1);
        }
        cdata_nutrition(tc) += 1000 * (efp / 100);
        if (tc == 0)
        {
            label_2162();
        }
        eatstatus(efstatus, tc);
        animeload(15, tc);
        goto label_2186_internal;
    case 1102:
        if (synccheck(tc, -1))
        {
            if (efstatus <= -1)
            {
                txtef(9);
                txtmore();
                txt(lang(u8"「うぃっ…」"s, u8"*Hic*"s),
                    lang(u8"「まずいぜ」"s, cnvtalk(u8"Ah, bad booze."s)),
                    lang(u8"「げー♪」"s, cnvtalk(u8"Ugh..."s)),
                    lang(
                        u8"「腐ったミルクみたいな味だ」"s,
                        cnvtalk(u8"Bah, smells like rotten milk."s)));
            }
            else
            {
                txtef(9);
                txtmore();
                txt(lang(u8"「うぃっ！」"s, u8"*Hic*"s),
                    lang(u8"「うまいぜ」"s, cnvtalk(u8"Ah, good booze."s)),
                    lang(u8"「らららー♪」"s, cnvtalk(u8"La-la-la-la."s)),
                    lang(u8"「ひっく」"s, cnvtalk(u8"I'm going to heaven."s)),
                    lang(u8"「ふぅ」"s, cnvtalk(u8"Whew!"s)),
                    lang(u8"「たまらないわ」"s, cnvtalk(u8"I'm revived!"s)),
                    lang(u8"「んまっ♪」"s, cnvtalk(u8"Awesome."s)));
            }
        }
        dmgcon(tc, 8, efp);
        eatstatus(efstatus, tc);
        goto label_2186_internal;
    case 1116:
        if (synccheck(tc, -1))
        {
            if (tc == 0)
            {
                txt(lang(u8"ぐわぁぁ！"s, u8"Arrrrg!"s));
            }
            txt(lang(
                u8"酸が"s + name(tc) + u8"を溶かした。"s,
                u8"The sulfuric acid melts "s + name(tc) + u8"."s));
        }
        if (cbit(978, tc))
        {
            cbitmod(978, tc, 0);
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"の体内のエイリアンは溶けた。"s,
                    name(tc) + your(tc) + u8" alien children melt in "s
                        + his(tc) + u8" stomach."s));
            }
        }
        dmghp(tc, efp * efstatusfix(500, 400, 100, 50) / 1000, -15, 63, efp);
        goto label_2186_internal;
    case 1103:
        if (synccheck(tc, -1))
        {
            if (tc == 0)
            {
                txt(lang(
                    u8"*ごくっ* 綺麗な水だ。"s,
                    u8"*quaff* The water is refreshing."s));
            }
            else
            {
                txt(lang(u8" *ごくっ* "s, u8"*quaff*"s));
            }
        }
        sickifcursed(efstatus, tc, 1);
        goto label_2186_internal;
    case 1146:
        if (synccheck(tc, -1))
        {
            txt(lang(u8"*シュワワ* 刺激的！"s, u8"*quaff* Juicy!"s));
            txt(lang(
                name(tc) + u8"のスタミナが少し回復した。"s,
                name(tc) + u8" restore"s + _s(tc) + u8" some stamina."s));
        }
        healsp(tc, 25);
        sickifcursed(efstatus, tc, 1);
        goto label_2186_internal;
    case 1147:
        if (synccheck(tc, -1))
        {
            txt(lang(u8"*ごくり*"s, u8"*quaff*"s));
            txt(lang(
                name(tc) + u8"のスタミナはかなり回復した。"s,
                name(tc) + u8" greatly restore"s + _s(tc) + u8" stamina."s));
        }
        healsp(tc, 100);
        sickifcursed(efstatus, tc, 1);
        goto label_2186_internal;
    case 1142:
        if (cdatan(2, tc) == u8"snail"s)
        {
            if (synccheck(tc, -1))
            {
                txtef(3);
                txtmore();
                txt(lang(
                    u8"塩だ！"s + name(tc) + u8"は溶けはじめた！"s,
                    u8"It's salt! "s + name(tc) + u8" start"s + _s(tc)
                        + u8" to melt."s));
            }
            if (cdata_hp(tc) > 10)
            {
                dmghp(tc, cdata_hp(tc) - rnd(10), -15);
            }
            else
            {
                dmghp(tc, rnd(20000), -15);
            }
        }
        else if (synccheck(tc, -1))
        {
            txtef(9);
            txtmore();
            txt(lang(u8"「しょっぱ〜」"s, cnvtalk(u8"Salty!"s)));
        }
        goto label_2186_internal;
    case 1130:
        if (synccheck(tc, -1))
        {
            if (tc == 0)
            {
                txt(lang(u8"*ごくっ* まずい！"s, u8"*quaff* Yucky!"s));
            }
            else
            {
                txt(lang(u8" *ごくっ* "s, u8"*quaff*"s));
            }
        }
        sickifcursed(efstatus, tc, 1);
        goto label_2186_internal;
    case 300:
        if (gdata(70) == 1008 || gdata(70) == 1010)
        {
            txt(lang(
                u8"そんなことをしている余裕はない！"s,
                u8"You have no time for it!"s));
            return 0;
        }
        if (cc == 0)
        {
            if (cdata_sp(0) < 50)
            {
                if (cdata_sp(0) < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, sdataref(2, efid) / 2 + 1);
                    goto label_2186_internal;
                }
            }
            dmgsp(
                0, rnd(sdataref(2, efid) / 2 + 1) + sdataref(2, efid) / 2 + 1);
        }
        invsubroutine = 1;
        invctrl(0) = 27;
        invctrl(1) = 0;
        snd(100);
        label_20592();
        goto label_2186_internal;
    case 301:
        if (cc == 0)
        {
            if (cdata_sp(0) < 50)
            {
                if (cdata_sp(0) < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, sdataref(2, efid) / 2 + 1);
                    goto label_2186_internal;
                }
            }
            dmgsp(
                0, rnd(sdataref(2, efid) / 2 + 1) + sdataref(2, efid) / 2 + 1);
        }
        if (gdata(183) != 0)
        {
            if (tc == cc)
            {
                int stat = cell_findspace(cdata_x(0), cdata_y(0), 1);
                if (stat == 0)
                {
                    txt(lang(
                        u8"降りるスペースがない。"s,
                        u8"There's no place to get off."s));
                    goto label_2186_internal;
                }
                cell_setchara(gdata(183), rtval, rtval(1));
                txt(lang(
                    name(gdata(183)) + u8"から降りた。"s,
                    u8"You dismount from "s + name(gdata(183)) + u8"."s));
                txtef(9);
                if (jp)
                {
                    txt(name(gdata(183)) + u8"「ふぅ」"s,
                        name(gdata(183)) + u8"「乗り心地はよかった？」"s,
                        name(gdata(183)) + u8"「疲れた…」"s,
                        name(gdata(183)) + u8"「またいつでも乗ってね♪」"s);
                }
                if (en)
                {
                    txt(name(gdata(183)) + u8" "s + cnvtalk(u8"Phew."s),
                        name(gdata(183)) + u8" "s
                            + cnvtalk(u8"How was my ride?"s),
                        name(gdata(183)) + u8" "s
                            + cnvtalk(u8"Tired...tired..."s),
                        name(gdata(183)) + u8" "s + cnvtalk(u8"It was nice."s));
                }
                ride_end();
                goto label_2186_internal;
            }
        }
        if (tc >= 16)
        {
            txt(lang(
                u8"仲間にしか騎乗できない。"s,
                u8"You can only ride an ally."s));
            goto label_2186_internal;
        }
        if (cbit(963, tc) == 1 || cbit(971, tc) == 1)
        {
            txt(lang(
                u8"護衛対象には騎乗できない。"s,
                u8"You can't ride a client."s));
            goto label_2186_internal;
        }
        if (tc == cc)
        {
            if (gdata(183) == 0)
            {
                txt(lang(
                    name(cc) + u8"は自分に乗ろうとした。"s,
                    u8"You try to ride yourself."s));
            }
            goto label_2186_internal;
        }
        if (cdata_current_map(tc) != 0)
        {
            txt(lang(
                u8"その仲間はこの場所に滞在中だ。"s,
                u8"The ally currently stays in this area."s));
            goto label_2186_internal;
        }
        if (gdata(183) != 0)
        {
            txt(lang(
                u8"現在"s + name(cc) + u8"は"s + name(gdata(183))
                    + u8"に騎乗している。"s,
                name(cc) + u8" "s + is(cc) + u8" currently riding "s
                    + name(gdata(183)) + u8"."s));
        }
        else
        {
            ride_begin(tc);
            txtef(9);
            if (jp)
            {
                txt(name(gdata(183)) + u8"「うぐぅ」"s,
                    name(gdata(183)) + u8"「ダイエットしてよ…」"s,
                    name(gdata(183)) + u8"「いくよ！」"s,
                    name(gdata(183)) + u8"「やさしくしてね♪」"s);
            }
            if (en)
            {
                txt(name(gdata(183)) + u8" "s + cnvtalk(u8"Awww."s),
                    name(gdata(183)) + u8" "s
                        + cnvtalk(u8"You should go on a diet."s),
                    name(gdata(183)) + u8" "s + cnvtalk(u8"Let's roll!"s),
                    name(gdata(183)) + u8" "s + cnvtalk(u8"Be gentle."s));
            }
        }
        goto label_2186_internal;
    case 183:
        if (cc != 0)
        {
            f = 0;
            inv_getheader(cc);
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    if (inv_number(cnt) == 0)
                    {
                        continue;
                    }
                    if (inv_skill(cnt) == 183)
                    {
                        ci = cnt;
                        f = 1;
                        break;
                    }
                }
            }
            if (f == 0)
            {
                return 0;
            }
        }
        if (sdata(183, cc) == 0)
        {
            if (synccheck(cc, -1))
            {
                txt(lang(
                    name(cc) + u8"は演奏のやり方を知らない。"s,
                    name(cc) + u8" "s + does((cc == 0))
                        + u8"n't know how to play an instrument."s));
                return 0;
            }
        }
        if (cc == 0)
        {
            if (cdata_sp(0) < 50)
            {
                if (cdata_sp(0) < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, sdataref(2, efid) / 2 + 1);
                    goto label_2186_internal;
                }
            }
            dmgsp(
                0, rnd(sdataref(2, efid) / 2 + 1) + sdataref(2, efid) / 2 + 1);
        }
        label_2146();
        goto label_2186_internal;
    case 184:
        if (sdata(184, 0) == 0)
        {
            txt(lang(
                u8"料理の仕方を知らない。"s, u8"You don't know how to cook."s));
            return 0;
        }
        cooktool = ci;
        invsubroutine = 1;
        invctrl = 16;
        snd(100);
        {
            int stat = label_20592();
            if (stat == 0)
            {
                return 0;
            }
        }
        if (cc == 0)
        {
            if (cdata_sp(0) < 50)
            {
                if (cdata_sp(0) < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, sdataref(2, efid) / 2 + 1);
                    goto label_2186_internal;
                }
            }
            dmgsp(
                0, rnd(sdataref(2, efid) / 2 + 1) + sdataref(2, efid) / 2 + 1);
        }
        label_1587();
        goto label_2186_internal;
    case 185:
        if (sdata(185, 0) == 0)
        {
            txt(lang(
                u8"釣りの仕方を知らない。"s, u8"You don't know how to fish."s));
            return 0;
        }
        if (inv_getspace() == 0)
        {
            txt(lang(
                u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
            return 0;
        }
        if (inv_count(ci) == 0)
        {
            txt(lang(
                u8"釣竿には餌が付いていない。"s,
                u8"You need a bait to fish."s));
            return 0;
        }
        f = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
            {
                y = cdata_y(cc) + cnt - 1;
                x = cdata_x(cc);
                if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
                {
                    continue;
                }
                if (chipm(0, map(x, y, 0)) == 3)
                {
                    f = 1;
                    break;
                }
            }
        }
        if (f == 0)
        {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
                {
                    y = cdata_y(cc);
                    x = cdata_x(cc) + cnt - 1;
                    if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
                    {
                        continue;
                    }
                    if (chipm(0, map(x, y, 0)) == 3)
                    {
                        f = 1;
                        break;
                    }
                }
            }
        }
        if (f == 0)
        {
            ++msgdup;
            txt(lang(
                u8"釣りをする場所が見当たらない。"s,
                u8"This isn't a good place to fish."s));
            label_1419();
            return 0;
        }
        if (chipm(0, map(cdata_x(0), cdata_y(0), 0)) == 3)
        {
            txt(lang(
                u8"水の中からは釣れない。"s,
                u8"You can't fish while swimming."s));
            label_1419();
            return 0;
        }
        if (cdata_x(0) - x > 0)
        {
            cdata_direction(0) = 1;
        }
        if (cdata_x(0) - x < 0)
        {
            cdata_direction(0) = 2;
        }
        if (cdata_y(0) - y > 0)
        {
            cdata_direction(0) = 3;
        }
        if (cdata_y(0) - y < 0)
        {
            cdata_direction(0) = 0;
        }
        gdata(35) = cdata_direction(0);
        fishx = x;
        fishy = y;
        addefmap(fishx, fishy, 1, 3);
        if (cc == 0)
        {
            if (cdata_sp(0) < 50)
            {
                if (cdata_sp(0) < rnd(75))
                {
                    txt(lang(
                        u8"疲労し過ぎて失敗した！"s,
                        u8"You are too exhausted!"s));
                    dmgsp(0, sdataref(2, efid) / 2 + 1);
                    goto label_2186_internal;
                }
            }
            dmgsp(
                0, rnd(sdataref(2, efid) / 2 + 1) + sdataref(2, efid) / 2 + 1);
        }
        item_separate(ci);
        --inv_count(ci);
        rowactre = 0;
        label_2156();
        goto label_2186_internal;
    case 406:
    case 407:
        if (efstatus <= -1)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"は悪魔が笑う声を聞いた。"s,
                    name(tc) + u8" hear"s + _s(tc) + u8" devils laugh."s));
            }
            goto label_2183_internal;
        }
        p = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt)
            {
                i = 16 - cnt - 1;
                if (efid == 406)
                {
                    if (p >= 1)
                    {
                        break;
                    }
                }
                if (bdataref(0, cdata(280 + i * 3, tc)) != 2)
                {
                    continue;
                }
                if (cdata(280 + i * 3, tc) == 13)
                {
                    continue;
                }
                if (cdata(280 + i * 3, tc) == 0)
                {
                    continue;
                }
                if (rnd(efp * 2 + 1) > rnd(cdata(280 + i * 3 + 1, tc) + 1))
                {
                    delbuff(tc, i);
                    ++p;
                    --cnt;
                    continue;
                }
            }
        }
        addbuff(tc, 10, efp, 5 + efp / 30);
        animeload(11, tc);
        goto label_2186_internal;
    case 1120:
        txtef(5);
        txt(lang(
            name(tc) + u8"は黄金の輝きに包まれた！"s,
            u8"A golden aura wraps "s + name(tc) + u8"!"s));
        label_2188();
        animeid = 5;
        label_1426();
        goto label_2186_internal;
    case 1117:
        if (tc >= 16)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (efstatus >= 0)
        {
            s = lang(u8"素材"s, u8"materials"s);
        }
        else
        {
            s = lang(u8"クズ"s, u8"junks"s);
        }
        snd(24);
        txt(lang(
            u8"たくさんの"s + s + u8"が降ってきた！"s,
            u8"Some "s + s + u8" fall from above!"s));
        autosave = 1 * (gdata(20) != 35);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (rnd(3) + 3 + (efstatus >= 1) * 6);
                 cnt < cnt_end;
                 ++cnt)
            {
                txtmore();
                atxspot = 19;
                if (efstatus >= 0)
                {
                    p = random_material(efp / 10, efp / 50);
                }
                else
                {
                    p = 0;
                }
                matgetmain(p, 1);
            }
        }
        goto label_2186_internal;
    case 632:
    case 454:
    case 1144:
        if (tc != 0)
        {
            goto label_2184_internal;
        }
        if (efid == 632)
        {
            txtmore();
            txt_check(0);
            txt(lang(
                name(cc) + u8"は"s + name(tc)
                    + u8"を気の狂いそうな眼差しで見た。"s,
                name(cc) + u8" cast"s + _s(cc) + u8" an insane glance on "s
                    + name(tc) + u8"."s));
            if (rnd(3))
            {
                goto label_2186_internal;
            }
            txtmore();
        }
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        if (encfind(tc, 33) != -1)
        {
            if (rnd(5))
            {
                txt(lang(
                    u8"あなたは変異を受け付けなかった。"s,
                    u8"You resist the threat of mutation."s));
                goto label_2186_internal;
            }
        }
    label_2182_internal:
        f = 0;
        p = 1;
        if (efid == 1144)
        {
            p = 2 + rnd(3);
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (p); cnt < cnt_end; ++cnt)
            {
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
                    {
                        tid = rnd(45);
                        traitmode = 0;
                        int stat = label_0042();
                        if (stat == 0 || traitref != 1)
                        {
                            continue;
                        }
                        if (rnd(2))
                        {
                            p = 1;
                        }
                        else
                        {
                            p = -1;
                        }
                        if (trait(tid) >= traitref(2))
                        {
                            p = -1;
                        }
                        if (trait(tid) <= traitref(1))
                        {
                            p = 1;
                        }
                        if (efstatus <= -1)
                        {
                            if (p == 1)
                            {
                                continue;
                            }
                        }
                        else if (p == -1)
                        {
                            if (efstatus >= 1)
                            {
                                if (rnd(3) == 0)
                                {
                                    continue;
                                }
                            }
                            if (efid == 1144)
                            {
                                continue;
                            }
                        }
                        trait(tid) += p;
                        txt(lang(u8"あなたは変容した！ "s, u8"You mutate."s));
                        if (p > 0)
                        {
                            txtef(2);
                            txt(traitrefn(0));
                        }
                        else
                        {
                            txtef(3);
                            txt(traitrefn(1));
                        }
                        animeload(8, 0);
                        f = 1;
                        break;
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        r1 = 0;
        label_1477();
        goto label_2186_internal;
    case 1121:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        if (efstatus <= -1)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
            }
            goto label_2182_internal;
        }
        f = 0;
        {
            int cnt = 0;
            for (int cnt_end =
                     cnt + (1 + (efstatus >= 1) + (efstatus >= 0) + rnd(2));
                 cnt < cnt_end;
                 ++cnt)
            {
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
                    {
                        tid = rnd(217);
                        traitmode = 0;
                        int stat = label_0042();
                        if (stat == 0 || traitref != 1)
                        {
                            continue;
                        }
                        if (trait(tid) == 0)
                        {
                            continue;
                        }
                        if (trait(tid) > 0)
                        {
                            p = -1;
                        }
                        if (trait(tid) < 0)
                        {
                            p = 1;
                        }
                        trait(tid) = 0;
                        txt(lang(
                            u8"あなたは元の自分に近づいた気がした。"s,
                            u8"You are now one step closer to yourself."s));
                        if (p > 0)
                        {
                            txtef(2);
                            txt(traitrefn(0));
                        }
                        else
                        {
                            txtef(3);
                            txt(traitrefn(1));
                        }
                        f = 1;
                        break;
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        r1 = 0;
        label_1477();
        goto label_2186_internal;
    case 411:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl = 13;
        snd(100);
        label_20592();
        goto label_2186_internal;
    case 461:
        if (mdata(6) == 1)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (efstatus <= -1)
        {
            txt(lang(
                u8"冥界から死霊が呼び出された！"s,
                u8"Hoards of undead raise from the hell!"s));
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4 + rnd(4)); cnt < cnt_end; ++cnt)
                {
                    flt(calcobjlv(cdata_level(0)), calcfixlv(3));
                    fltn(u8"undead"s);
                    characreate(-1, 0, cdata_x(0), cdata_y(0));
                }
            }
            obvious = 0;
            goto label_2186_internal;
        }
        allyctrl = 2;
        {
            int stat = label_1980();
            if (stat == -1)
            {
                txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                obvious = 0;
                goto label_2186_internal;
            }
            if (bonus < rnd(100))
            {
                if (synccheck(cc, -1))
                {
                    txt(lang(
                        name(cc) + u8"の力は冥界に及ばなかった。"s,
                        name(cc) + your(cc)
                            + u8" prayer doesn't reach the underworld."s));
                }
                goto label_2186_internal;
            }
            rc = stat;
        }
        label_1538();
        cxinit = cdata_x(cc);
        cyinit = cdata_y(cc);
        label_1532();
        cdata_current_map(rc) = 0;
        txtef(5);
        txt(cnven(cdatan(0, rc))
            + lang(
                  u8"は復活した！"s,
                  (u8" "s + have(rc) + u8" been resurrected!"s)));
        txt(lang(u8"「ありがとう！」"s, cnvtalk(u8"Thanks!"s)));
        animeid = 19;
        animode = 100 + rc;
        label_1426();
        snd(120);
        cdata_emotion_icon(rc) = 317;
        if (cc == 0)
        {
            modimp(rc, 15);
            if (rc >= 16)
            {
                modkarma(0, 2);
            }
        }
        goto label_2186_internal;
    case 412:
        if (efstatus == 0)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"の装備品は白い光に包まれた。"s,
                    name(tc) + u8" "s + your(tc)
                        + u8" equipment are surrounded by a white aura."s));
            }
        }
        if (efstatus >= 1)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"は聖なる光に包み込まれた。"s,
                    name(tc) + u8" "s + is(tc)
                        + u8" surrounded by a holy aura."s));
            }
        }
        if (efstatus <= -1)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"は悪魔が笑う声を聞いた。"s,
                    name(tc) + u8" hear"s + _s(tc) + u8" devils laugh."s));
            }
            goto label_2183_internal;
        }
        inv_getheader(tc);
        p(1) = 0;
        p(2) = 0;
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv_number(cnt) == 0)
                {
                    continue;
                }
                if (inv_curse_state(cnt) >= 0)
                {
                    continue;
                }
                ci = cnt;
                p = 0;
                if (inv_curse_state(ci) == -1)
                {
                    p = rnd(200) + 1;
                }
                if (inv_curse_state(ci) == -2)
                {
                    p = rnd(1000) + 1;
                }
                if (efstatus >= 1)
                {
                    p = p / 2 + 1;
                }
                else if (inv_body_part(ci) == 0)
                {
                    continue;
                }
                if (p != 0)
                {
                    if (efp >= p)
                    {
                        ++p(1);
                        inv_curse_state(ci) = 0;
                        item_stack(tc, ci, 1);
                    }
                    else
                    {
                        ++p(2);
                    }
                }
            }
        }
        if (efstatus >= 1)
        {
            if (p(1) != 0)
            {
                if (synccheck(tc, -1))
                {
                    txt(lang(
                        u8"幾つかのアイテムが浄化された。"s,
                        u8"The aura uncurses some "s + his(tc) + u8" stuff."s));
                }
            }
        }
        else if (p(1) != 0)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    u8"身に付けている装備の幾つかが浄化された。"s,
                    u8"The aura uncurses some of "s + his(tc)
                        + u8" equipment."s));
            }
        }
        if (p(2) != 0)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    u8"幾つかのアイテムは抵抗した。"s,
                    u8"Several items resist the aura and remain cursed."s));
            }
        }
        if (p(1) == 0 && p(2) == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        else
        {
            animeload(10, tc);
        }
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 413:
        if (tc >= 16)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        if (efstatus <= -1)
        {
            artifactlocation = "";
            txt(lang(
                u8"何かがあなたの耳元でささやいたが、あなたは聞き取ることができなかった。"s,
                u8"You hear a sepulchral whisper but the voice is too small to distinguish a word."s));
            goto label_2186_internal;
        }
        if (artifactlocation == ""s)
        {
            txt(lang(
                u8"まだ特殊なアイテムは生成されていない。"s,
                u8"No artifacts have been generated yet."s));
        }
        else
        {
            notesel(artifactlocation);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (noteinfo(0)); cnt < cnt_end; ++cnt)
                {
                    noteget(s, 0);
                    txt(cnven(s));
                    notedel(0);
                }
            }
        }
        goto label_2186_internal;
    case 1104:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        f = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (1 + (efstatus >= 1)); cnt < cnt_end;
                 ++cnt)
            {
                cnt2 = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (2000); cnt < cnt_end; ++cnt)
                    {
                        await();
                        p = rnd(67) + 400;
                        if (p == 441)
                        {
                            if (rnd(10))
                            {
                                continue;
                            }
                        }
                        if (efstatus >= 0)
                        {
                            if (sdataref(0, p) != 0)
                            {
                                if (cnt2 == 0)
                                {
                                    s = lang(u8"突然、"s, u8"Suddenly, "s);
                                }
                                else
                                {
                                    s = lang(u8"さらに、"s, u8"Futhermore, "s);
                                }
                                skillgain(0, p, 1, 200);
                                txtef(2);
                                txt(lang(
                                    s + name(0) + u8"は"s + skillname(p)
                                        + u8"の魔法の知識を得た。"s,
                                    s + u8"you gain knowledge of a spell, "s
                                        + skillname(p) + u8"."s));
                                snd(24);
                                f = 1;
                                break;
                            }
                        }
                        else
                        {
                            p = p - 400;
                            if (spell(p) > 0)
                            {
                                spell(p) = 0;
                                txt(lang(
                                    u8"これは呪われている！"s,
                                    u8"It's cursed!"s));
                                txtef(3);
                                txt(lang(
                                    u8"突然、"s + name(0) + u8"は"s
                                        + skillname((p + 400))
                                        + u8"の魔法の知識を失った。"s,
                                    u8"Suddenly, you lose knowledge of a spell, "s
                                        + skillname((p + 400)) + u8"."s));
                                snd(117);
                                animeload(14, 0);
                                f = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        autosave = 1 * (gdata(20) != 35);
        goto label_2186_internal;
    case 1143:
        if (efstatus <= 0)
        {
            if (cdata_level(tc) <= 1)
            {
                txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                obvious = 0;
                goto label_2186_internal;
            }
            --cdata_level(tc);
            cdata_experience(tc) = 0;
            r1 = tc;
            label_1456();
            txtef(8);
            txt(lang(
                name(tc) + u8"のレベルが下がった…"s,
                name(tc) + u8" lose"s + _s(tc) + u8" a level..."s));
        }
        else
        {
            cdata_experience(tc) = cdata_required_experience(tc);
            r1 = tc;
            r2 = 0;
            label_1454();
            if (synccheck(tc, -1))
            {
                snd(60);
            }
        }
        if (efstatus <= -1)
        {
            txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
            {
                int cnt = 10;
                for (int cnt_end = cnt + (40); cnt < cnt_end; ++cnt)
                {
                    if (rnd(3) == 0)
                    {
                        if (cnt <= 17)
                        {
                            if (sdata(cnt, tc) != 0)
                            {
                                skillexp(cnt, tc, -1000);
                            }
                        }
                    }
                }
            }
            animeload(8, tc);
        }
        label_1477();
        goto label_2186_internal;
    case 1105:
    {
        int cnt = 0;
        for (;; ++cnt)
        {
            await();
            p = rnd(300) + 100;
            if (sdataref(0, p) != 0)
            {
                if (efstatus >= 0)
                {
                    if (cnt < efstatusfix(0, 0, 100, 2000))
                    {
                        if (sdata(p, tc) != 0)
                        {
                            continue;
                        }
                    }
                    skillgain(tc, p, 1);
                    if (synccheck(tc, -1))
                    {
                        snd(24);
                        txtef(2);
                        txt(lang(
                            ""s + name(tc) + u8"は"s + skillname(p)
                                + u8"の技術を獲得した！"s,
                            name(tc) + u8" gain"s + _s(tc) + u8" a skill of "s
                                + skillname(p) + u8"!"s));
                    }
                    break;
                }
                else
                {
                    if (sdata(p, tc) == 0)
                    {
                        continue;
                    }
                    if (synccheck(tc, -1))
                    {
                        snd(38);
                        txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
                    }
                    skillexp(p, tc, -1000);
                    break;
                }
            }
        }
    }
        r1 = tc;
        label_1477();
        autosave = 1 * (gdata(20) != 35);
        goto label_2186_internal;
    case 1107:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (cdata_god(0) == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (efstatus <= -1)
        {
            txt(lang(
                u8"あなたの神はあなたの信仰に疑問を抱いた。"s,
                u8"Your god doubts your faith."s));
            snd(117);
            animeload(14, 0);
            skillexp(181, 0, -1000);
            goto label_2186_internal;
        }
        if (cdata_god(0) == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        else
        {
            txtef(2);
            txt(lang(
                u8"あなたは"s + godname(cdata_god(0))
                    + u8"の暖かい眼差しを感じた。"s,
                u8"You feel as if "s + godname(cdata_god(0))
                    + u8" is watching you."s));
            if (efstatus >= 1)
            {
                txt(lang(
                    u8"空から三つ葉のクローバーがふってきた。"s,
                    u8"A three-leaved falls from the sky."s));
            }
            animeid = 19;
            animode = 100 + tc;
            label_1426();
            snd(120);
            cdata_praying_point(0) += 500;
            modpiety(75);
            skillexp(181, 0, 1000 + (efstatus >= 1) * 750, 6, 1000);
        }
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 1119:
    {
        int cnt = 0;
        for (int cnt_end = cnt + (1 + (efstatus >= 1)); cnt < cnt_end; ++cnt)
        {
            cnt2 = cnt;
            {
                int cnt = 0;
                for (;; ++cnt)
                {
                    await();
                    p = rnd(300) + 100;
                    if (sdataref(0, p) != 0)
                    {
                        if (sorg(p, tc) == 0)
                        {
                            continue;
                        }
                        modgrowth(tc, p, efp * efstatusfix(-4, -2, 5, 5) / 100);
                        if (cnt2 == 0)
                        {
                            s = lang(""s, u8"The "s);
                        }
                        else
                        {
                            s = lang(u8"さらに"s, u8"Furthermore, the "s);
                        }
                        if (efstatus >= 0)
                        {
                            if (synccheck(tc, -1))
                            {
                                snd(24);
                                txtef(2);
                                txt(lang(
                                    s + ""s + name(tc) + u8"の"s + skillname(p)
                                        + u8"の技術の潜在能力が上昇した。"s,
                                    s + u8"potential of "s + name(tc) + your(tc)
                                        + u8" "s + skillname(p)
                                        + u8" skill increases."s));
                            }
                        }
                        else if (synccheck(tc, -1))
                        {
                            snd(117);
                            txtef(3);
                            txt(lang(
                                ""s + name(tc) + u8"の"s + skillname(p)
                                    + u8"の技術の潜在能力が減少した。"s,
                                u8"The potential of "s + name(tc) + your(tc)
                                    + u8" "s + skillname(p)
                                    + u8" skill decreases."s));
                        }
                        break;
                    }
                }
            }
        }
    }
        r1 = tc;
        label_1477();
        autosave = 1 * (gdata(20) != 35);
        goto label_2186_internal;
    case 1106:
        i = rnd(10) + 10;
        skillexp(i, tc, efstatusfix(-2000, -2000, -1000, -250));
        animeid = 6;
        label_1426();
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 1139:
        txt(lang(
            name(tc) + u8"の血は沸きあがるように熱くなった。"s,
            name(tc) + your(tc) + u8" blood burns and a new strength fills "s
                + his(tc) + u8" body!"s));
        skillexp(18, tc, efstatusfix(-4000, -1000, 8000, 12000));
        if (efstatus == 1)
        {
            modgrowth(tc, 18, 15);
            txtef(2);
            txt(lang(u8"あつつ！"s, u8"It really burns!"s));
        }
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 1113:
        if (efstatus >= 1)
        {
            {
                int cnt = 10;
                for (int cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
                {
                    modgrowth(tc, cnt, rnd(sgrowth(cnt, tc) / 20 + 3) + 1);
                }
            }
            txt(lang(
                name(tc) + u8"の全ての能力の潜在能力が上昇した。"s,
                name(tc) + your(tc)
                    + u8" potential of every attribute expands."s));
            animeid = 19;
            animode = 100 + tc;
            label_1426();
            snd(61);
        }
        else
        {
            i = rnd(8) + 10;
            valn = skillname(i);
            if (efstatus == 0)
            {
                txt(lang(
                    name(tc) + u8"の"s + valn + u8"の潜在能力が上昇した。"s,
                    name(tc) + your(tc) + u8" potential of "s + valn
                        + u8" expands."s));
                modgrowth(tc, i, rnd(sgrowth(i, tc) / 10 + 10) + 1);
                snd(24);
            }
            else
            {
                txt(lang(
                    name(tc) + u8"の"s + valn + u8"の潜在能力が減少した。"s,
                    name(tc) + your(tc) + u8" potential of "s + valn
                        + u8" decreases."s));
                modgrowth(tc, i, (rnd(sgrowth(i, tc) / 10 + 10) + 1) * -1);
                snd(117);
            }
        }
        autosave = 1 * (gdata(20) != 35);
        goto label_2186_internal;
    case 653:
        if (tc < 57)
        {
            goto label_2186_internal;
        }
        if (cdata_quality(tc) >= 4)
        {
            goto label_2186_internal;
        }
        txt(lang(
            name(tc) + u8"は消え去った。"s,
            name(tc) + u8" vanish"s + _s(tc) + u8"."s));
        chara_vanquish(tc);
        goto label_2186_internal;
    case 430:
    case 429:
        if (tc >= 16)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        p = 1;
        if (efid == 430)
        {
            p = 2;
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (p); cnt < cnt_end; ++cnt)
            {
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt)
                    {
                        y = cnt;
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end;
                                 ++cnt)
                            {
                                x = cnt;
                                p = dist(cdata_x(tc), cdata_y(tc), x, y);
                                if (efstatus <= -1)
                                {
                                    if (efid == 429)
                                    {
                                        map(x, y, 2) = tile_default;
                                    }
                                    if (efid == 430)
                                    {
                                        map(x, y, 5) = 0;
                                    }
                                    continue;
                                }
                                if (p < 7 || rnd(efp + 1) > rnd(p * 8 + 1)
                                    || efstatus >= 1)
                                {
                                    if (efid == 429)
                                    {
                                        map(x, y, 2) = map(x, y, 0);
                                    }
                                    if (efid == 430)
                                    {
                                        if (map(x, y, 6) != 0
                                            || map(x, y, 5) != 0)
                                        {
                                            map(x, y, 2) = map(x, y, 0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (efstatus <= -1)
        {
            txt(lang(
                u8"あれ…？あなたは軽い記憶障害を受けた。"s,
                u8"Hmm? You suffer minor memory defect."s));
        }
        else
        {
            if (efid == 429)
            {
                txt(lang(
                    name(tc) + u8"は周囲の地形を察知した。"s,
                    name(tc) + u8" sense"s + _s(tc) + u8" nearby locations."s));
            }
            if (efid == 430)
            {
                txt(lang(
                    name(tc) + u8"周囲の物質を感知した。"s,
                    name(tc) + u8" sense"s + _s(tc) + u8" nearby objects."s));
            }
        }
        animeload(10, tc);
        redraw(0);
        label_1418();
        goto label_2186_internal;
    case 658:
        if (cdata_hp(tc) > cdata_max_hp(tc) / 8)
        {
            goto label_2186_internal;
        }
        if (synccheck(tc, -1))
        {
            snd(105);
            txtef(3);
            txt(lang(u8" *ブシュッ* "s, u8"*Gash*"s));
            if (tc >= 16)
            {
                gdata(809) = 2;
                txt3rd = 1;
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"の首をちょんぎり"s,
                    name(cc) + u8" cut"s + _s(cc) + u8" "s + name(tc) + your(tc)
                        + u8" head and"s));
            }
            else
            {
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"の首をちょんぎった。"s,
                    name(cc) + u8" cut"s + _s(cc) + u8" "s + name(tc) + your(tc)
                        + u8" head."s));
            }
        }
        dmghp(tc, cdata_max_hp(tc), cc, 658);
        goto label_2186_internal;
    case 440:
    case 439:
        if (efid == 439)
        {
            if (synccheck(tc, -1))
            {
                if (efstatus <= -1)
                {
                    snd(117);
                    txt(lang(
                        name(tc) + u8"の肉体は蝕まれた。"s,
                        name(tc) + your(tc) + u8" body is damaged."s));
                }
                else
                {
                    txt(lang(
                        name(tc) + u8"の肉体は復活した。"s,
                        name(tc) + your(tc) + u8" body is restored."s));
                    animeload(10, tc);
                }
                if (efstatus >= 1)
                {
                    txt(lang(
                        u8"さらに、"s + name(tc) + u8"の肉体は強化された。"s,
                        u8"In addition, "s + his(tc)
                            + u8" body is enchanted."s));
                    animeload(10, tc);
                }
            }
            p(0) = 10;
            p(1) = 11;
            p(2) = 12;
            p(3) = 17;
            p(4) = 18;
            p(5) = -1;
        }
        if (efid == 440)
        {
            if (synccheck(tc, -1))
            {
                if (efstatus <= -1)
                {
                    snd(117);
                    txt(lang(
                        name(tc) + u8"の精神は蝕まれた。"s,
                        name(tc) + your(tc) + u8" spirit is damaged."s));
                }
                else
                {
                    txt(lang(
                        name(tc) + u8"の精神は復活した。"s,
                        name(tc) + your(tc) + u8" spirit is restored."s));
                    animeload(10, tc);
                }
                if (efstatus >= 1)
                {
                    txt(lang(
                        u8"さらに、"s + name(tc) + u8"の精神は強化された。"s,
                        u8"In addition, "s + his(tc)
                            + u8" spirit is enchanted."s));
                    animeload(10, tc);
                }
            }
            p(0) = 14;
            p(1) = 13;
            p(2) = 16;
            p(3) = 15;
            p(4) = 19;
            p(5) = -1;
        }
        {
            int cnt = 0;
            for (;; ++cnt)
            {
                if (p(cnt) == -1)
                {
                    break;
                }
                i = p(cnt) + 240 - 10;
                if (efstatus <= -1)
                {
                    if (cdata_quality(tc) <= 3)
                    {
                        cdata(i, tc) -= rnd(sorg(p(cnt), tc)) / 5 + rnd(5);
                        continue;
                    }
                }
                if (cdata(i, tc) < 0)
                {
                    cdata(i, tc) = 0;
                }
                if (efstatus >= 1)
                {
                    cdata(i, tc) = sorg(p(cnt), tc) / 10 + 5;
                }
            }
        }
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 441:
        label_1997();
        screenupdate = -1;
        label_1416();
        goto label_2186_internal;
    case 1141:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (gdata(63) != 0)
        {
            txt(lang(
                u8"脱出を中止した。"s,
                u8"The air around you gradually loses power."s));
            gdata(63) = 0;
        }
        else
        {
            int stat = label_2080();
            if (stat == 1)
            {
                txt(lang(
                    u8"依頼請負中の帰還は法律で禁止されている。それでも帰還する？"s,
                    u8"Returning while taking a quest if forbidden. Are you sure you want to return?"s));
                promptl(0, 0) = stryes;
                promptl(1, 0) = u8"y"s;
                promptl(2, 0) = u8"0"s;
                promptl(0, 1) = strno;
                promptl(1, 1) = u8"n"s;
                promptl(2, 1) = u8"1"s;
                promptmax = 2;
                val(0) = promptx;
                val(1) = prompty;
                val(2) = 160;
                val(3) = 1;
                label_2131();
                if (rtval != 0)
                {
                    goto label_2186_internal;
                }
            }
            txt(lang(
                u8"周囲の大気がざわめきだした。"s,
                u8"The air around you becomes charged."s));
            if (adata(16, gdata(20)) == 8)
            {
                if (gdata(22) == adata(10, gdata(20)))
                {
                    if (adata(20, gdata(20)) != -1)
                    {
                        txt(lang(
                            u8"このままダンジョンを出ると、この階のクエストは達成できない…"s,
                            u8"The lord of the dungeon might disappear if you escape now."s));
                    }
                }
            }
            gdata(64) = gdata(850);
            gdata(65) = 1;
            if (efstatus <= -1)
            {
                if (rnd(3) == 0)
                {
                    gdata(64) = 41;
                    gdata(65) = 1;
                }
            }
            gdata(63) = 5 + rnd(10);
        }
        goto label_2186_internal;
    case 428:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (gdata(63) != 0)
        {
            txt(lang(
                u8"帰還を中止した。"s,
                u8"The air around you gradually loses power."s));
            gdata(63) = 0;
        }
        else
        {
            label_2081();
            if (efstatus <= -1)
            {
                if (rnd(3) == 0)
                {
                    gdata(64) = 41;
                    gdata(65) = 1;
                }
            }
        }
        goto label_2186_internal;
    case 621:
        healmp(tc, efp / 2 + rnd((efp / 2 + 1)));
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"のマナが回復した。"s,
                name(tc) + your(tc) + u8" mana is restored."s));
            animeid = 5;
            label_1426();
        }
        goto label_2186_internal;
    case 624:
        healmp(tc, role(dice1, dice2, bonus));
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は周囲からマナを吸い取った。"s,
                name(tc) + u8" absorb"s + _s(tc) + u8" mana from the air."s));
            animeid = 5;
            label_1426();
        }
        goto label_2186_internal;
    case 1108:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は毒を浴びた！"s,
                name(tc) + u8" "s + is(tc) + u8" hit by poison!"s));
        }
        if (cbit(978, tc))
        {
            cbitmod(978, tc, 0);
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"の体内のエイリアンは溶けた。"s,
                    name(tc) + your(tc) + u8" alien children melt in "s
                        + his(tc) + u8" stomach."s));
            }
        }
        dmgcon(tc, 1, efp);
        goto label_2186_internal;
    case 1111:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は墨を浴びた！"s,
                u8"Ink squirts into "s + name(tc) + your(tc) + u8" face!"s));
        }
        dmgcon(tc, 4, efp);
        goto label_2186_internal;
    case 1109:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"はひどい頭痛におそわれた！"s,
                u8"A foul stench floods "s + name(tc) + your(tc)
                    + u8" nostrils!"s));
        }
        dmgcon(tc, 5, efp);
        goto label_2186_internal;
    case 1110:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は痺れた！"s,
                name(tc) + u8" get"s + _s(tc) + u8" numbness!"s));
        }
        dmgcon(tc, 3, efp);
        goto label_2186_internal;
    case 1112:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は甘い液体を浴びた！"s,
                u8"Strange sweet liquid splashs onto "s + name(tc) + u8"!"s));
        }
        dmgcon(tc, 2, efp);
        goto label_2186_internal;
    case 645:
    case 1114:
    label_2183_internal:
        if (efid == 645)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(cc) + u8"は"s + name(tc)
                        + u8"を指差して呪いの言葉を呟いた。"s,
                    name(cc) + u8" point"s + _s(cc) + u8" "s + name(tc)
                        + u8" and mutter"s + _s(cc) + u8" a curse."s));
            }
        }
        p = 75 + sdata(19, tc);
        if (encfind(tc, 43) != -1)
        {
            p += encfind(tc, 43) / 2;
        }
        if (rnd(p) > efp / 2 + (efstatus <= -1) * 100)
        {
            goto label_2186_internal;
        }
        if (tc < 16)
        {
            if (rnd(3))
            {
                if (trait(42))
                {
                    txt(lang(
                        u8"あなたは祈祷を捧げ呪いのつぶやきを無効にした。"s,
                        u8"Your prayer nullifies the curse."s));
                    goto label_2186_internal;
                }
            }
        }
        i = 0;
        {
            int cnt = 100;
            for (int cnt_end = cnt + (30); cnt < cnt_end; ++cnt)
            {
                if (cdata(cnt, tc) % 10000 == 0)
                {
                    continue;
                }
                p(i) = cdata(cnt, tc) % 10000 - 1;
                if (inv_curse_state(p(i)) == 1)
                {
                    if (rnd(10))
                    {
                        continue;
                    }
                }
                ++i;
            }
        }
        if (i == 0)
        {
            inv_getheader(tc);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (200); cnt < cnt_end; ++cnt)
                {
                    p = invhead + rnd(invrange);
                    if (inv_number(p) == 0)
                    {
                        continue;
                    }
                    if (inv_curse_state(p) == 1)
                    {
                        if (rnd(10))
                        {
                            continue;
                        }
                    }
                    i = 1;
                    break;
                }
            }
        }
        if (i > 0)
        {
            i = p(rnd(i));
            valn = itemname(i, 1, 1);
            if (inv_curse_state(i) == -1)
            {
                inv_curse_state(i) = -2;
            }
            else
            {
                inv_curse_state(i) = -1;
            }
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"の"s + valn + u8"は黒く輝いた。"s,
                    name(tc) + your(tc) + u8" "s + valn + u8" glows black."s));
            }
            r1 = tc;
            label_1477();
            snd(117);
            animeload(14, tc);
            item_stack(tc, i, 1);
        }
        else
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        goto label_2186_internal;
    case 1118:
        f = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
            {
                p = rnd(11) + 50;
                if (sorg(p, tc) >= 150)
                {
                    ++f;
                    resistmod(tc, p, 50 * -1);
                    if (f >= efp / 100)
                    {
                        break;
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(lang(u8"何も起こらなかったようだ。"s, u8"Nothing happenes."s));
            obvious = 0;
        }
        else
        {
            snd(38);
        }
        r1 = tc;
        label_1477();
        goto label_2186_internal;
    case 1138:
    case 1123:
    case 1122:
    case 1137:
        if (cc != 0 && cc < 16)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        flt(cdata_level(0) / 2 + 5, 3);
        p = 0;
        if (rnd(3) == 0)
        {
            fltn(u8"man"s);
        }
        if (efid == 1138)
        {
            txt(lang(
                u8"なんと、あなたには生き別れた血の繋がっていないぬこの妹がいた！"s,
                u8"How...! You suddenly get a younger cat sister!"s));
            p = 210;
        }
        if (efid == 1123)
        {
            txt(lang(
                u8"なんと、あなたには生き別れた血の繋がっていない妹がいた！"s,
                u8"How...! You suddenly get a younger sister!"s));
            p = 176;
        }
        if (efid == 1137)
        {
            txt(lang(
                u8"お嬢さんが空から降ってきた！"s,
                u8"A young lady falls from the sky."s));
            p = 211;
        }
        novoidlv = 1;
        characreate(56, p, -3, 0);
        rc = 56;
        label_2659();
        goto label_2186_internal;
    case 435:
        if (cc != 0 || tc == 0 || cdata_relationship(tc) == 10)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (gdata(20) == 6 || gdata(20) == 40 || gdata(20) == 42)
        {
            obvious = 0;
            txt(lang(
                u8"この場所では効果がない。"s,
                u8"The effect doesn't work in this area."s));
            goto label_2186_internal;
        }
        f = 1;
        {
            int stat = inv_find(663, cc);
            if (stat != -1)
            {
                efp = efp * 3 / 2;
            }
        }
        if (rnd(efp / 15 + 5) < cdata_level(tc))
        {
            f = 0;
        }
        if (cdata_quality(tc) >= 4 || cdata_character_role(tc) != 0
            || cbit(976, tc) == 1)
        {
            f = -1;
        }
        if (f == 1)
        {
            rc = tc;
            label_2659();
            check_quest();
        }
        else if (f == 0)
        {
            txt(lang(
                name(tc) + u8"は抵抗した。"s,
                name(tc) + u8" resist"s + _s(tc) + u8"."s));
        }
        else
        {
            txt(lang(
                name(tc) + u8"は支配できない。"s,
                name(tc) + u8" cannot be charmed."s));
        }
        goto label_2186_internal;
    case 436:
    case 437:
    case 455:
    case 634:
    case 456:
        if (efid == 436)
        {
            p(0) = 3;
            p(1) = 2 + rnd((efp / 50 + 1));
            txt(lang(
                u8"蜘蛛の巣が辺りを覆った。"s,
                u8"The ground is covered with thick webbing."s));
        }
        if (efid == 437)
        {
            txt(lang(
                u8"辺りを濃い霧が覆った。"s,
                u8"The air is wrapped in a dense fog."s));
            p(0) = 3;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 455)
        {
            txt(lang(
                u8"酸の水溜りが発生した。"s, u8"Acid puddles are generated."s));
            p(0) = 2;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 456)
        {
            txt(lang(
                u8"火柱が発生した。"s,
                u8"Walls of fire come out from the ground."s));
            p(0) = 2;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 634)
        {
            txt(lang(u8"エーテルの霧が発生した。"s, u8"Ether mist spreads."s));
            p(0) = 2;
            p(1) = 1 + rnd((efp / 100 + 2));
        }
        snd(68);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (p(1)); cnt < cnt_end; ++cnt)
            {
                x = rnd(p) + tlocx - rnd(p);
                y = rnd(p) + tlocy - rnd(p);
                f = 1;
                if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
                {
                    f = 0;
                }
                else if (chipm(7, map(x, y, 0)) & 4)
                {
                    f = 0;
                }
                if (dist(tlocx, tlocy, x, y) >= p)
                {
                    f = 0;
                }
                if (f == 0)
                {
                    if (rnd(2) == 0)
                    {
                        continue;
                    }
                    else
                    {
                        --cnt;
                        continue;
                    }
                }
                if (efid == 634)
                {
                    addmef(x, y, 4, 20, rnd(4) + 2, efp, cc);
                }
                if (efid == 455)
                {
                    addmef(x, y, 3, 19, rnd(10) + 5, efp, cc);
                }
                if (efid == 456)
                {
                    addmef(x, y, 5, 24, rnd(10) + 5, efp, cc);
                    mapitem_fire(x, y);
                }
                if (efid == 436)
                {
                    addmef(x, y, 1, 11, -1, efp * 2);
                }
                if (efid == 437)
                {
                    addmef(x, y, 2, 30, 8 + rnd((15 + efp / 25)), efp);
                }
            }
        }
        goto label_2186_internal;
    case 1145:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 0;
        snd(100);
        label_20592();
        if (inv_quality(ci) < 4 || inv_quality(ci) == 6)
        {
            txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
            obvious = 0;
            goto label_2186_internal;
        }
        txt(lang(
            u8"アーティファクトの新しい銘は？"s,
            u8"What do you want to name this artifact?"s));
        val = 3;
        {
            int stat = label_1993();
            if (stat == 0)
            {
                obvious = 0;
                randomize();
                goto label_2186_internal;
            }
            p = stat;
        }
        inv_subname(ci) = list(1, p) + 40000;
        randomize();
        txt(lang(
            u8"それは"s + listn(0, p) + u8"という銘になった。"s,
            u8"It's now called "s + listn(0, p) + u8"."s));
        goto label_2186_internal;
    case 49:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 7;
        snd(100);
        {
            int stat = label_20592();
            f = stat;
        }
        if (inv_quality(ci) >= 4 || ibit(10, ci) == 1)
        {
            txt(lang(
                u8"そのアイテムに改良の余地はない。"s,
                u8"This item leaves no room for improvement."s));
            fixmaterial = 0;
            objfix = 0;
            goto label_2186_internal;
        }
        randomize(inv_param1(efcibk));
        equip = inv_body_part(ci);
        animeload(8, cc);
        fixmaterial = inv_material(ci);
        label_0265();
        randomize(inv_param1(efcibk));
        inv_quality(ci) = 4;
        inv_subname(ci) = 40000 + rnd(30000);
        p = rnd(rnd(rnd(10) + 1) + 3) + 3;
        egolv = rnd(limit(rnd(6), 0, 4) + 1);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (p); cnt < cnt_end; ++cnt)
            {
                randomize(inv_param1(efcibk));
                encadd(
                    ci,
                    randomenc(randomenclv(egolv)),
                    randomencp() + (fixlv == 5) * 100
                        + (ibit(15, ci) == 1) * 100,
                    20 - (fixlv == 5) * 10 - (ibit(15, ci) == 1) * 20);
            }
        }
        randomize();
        txt(lang(
            u8"それは"s + itemname(ci, 1) + u8"になった。"s,
            u8"It becomes "s + itemname(ci, 1) + u8"."s));
        if (equip != 0)
        {
            cdata(equip, cc) = cdata(equip, cc) / 10000 * 10000 + ci + 1;
            inv_body_part(ci) = equip;
        }
        r1 = cc;
        label_1477();
        fixmaterial = 0;
        objfix = 0;
        ci = efcibk;
        --inv_number(ci);
        cell_refresh(inv_x(ci), inv_y(ci));
        autosave = 1 * (gdata(20) != 35);
        goto label_2186_internal;
    case 21:
    case 1127:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 0;
        snd(100);
        {
            int stat = label_20592();
            f = stat;
        }
        if (inv_quality(ci) == 5 || ibit(10, ci) == 1)
        {
            if (efid == 1127)
            {
                f = 0;
            }
        }
        equip = inv_body_part(ci);
        if (f == 1)
        {
            if (inv_quality(ci) == 6)
            {
                if (efp < 350)
                {
                    txt(lang(
                        u8"アーティファクトの再生成にはパワーが足りない。"s,
                        u8"More magic power is needed to reconstruct an artifact."s));
                    goto label_2186_internal;
                }
                animeload(8, cc);
                txt(lang(
                    name(cc) + u8"の"s + itemname(ci, 1)
                        + u8"は再生成された。"s,
                    name(cc) + your(cc) + u8" "s + itemname(ci, 1, 1)
                        + u8" is reconstructed."s));
                --inv_number(ci);
                cell_refresh(inv_x(ci), inv_y(ci));
                flt();
                itemcreate(0, inv_id(ci), -1, -1, 0);
            }
            else
            {
                animeload(8, cc);
                if (efp <= 50)
                {
                    if (rnd(3) == 0)
                    {
                        fixmaterial = 35;
                    }
                }
                s = itemname(ci, 1, 1);
                objlv = efp / 10;
                objfix = efp / 100;
                randomize();
                label_0265();
                txt(lang(
                    name(cc) + u8"の"s + s + u8"は"s + itemname(ci, 1)
                        + u8"に変化した。"s,
                    name(cc) + your(cc) + u8" "s + s + u8" transforms into "s
                        + itemname(ci, 1) + u8"."s));
            }
        }
        else
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        if (equip != 0)
        {
            cdata(equip, cc) = cdata(equip, cc) / 10000 * 10000 + ci + 1;
            inv_body_part(ci) = equip;
        }
        r1 = cc;
        label_1477();
        fixmaterial = 0;
        objfix = 0;
        goto label_2186_internal;
    case 1128:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        snd(24);
        p = rnd((efp + 1)) / 100 + 1;
        gdata(97) += p;
        txtef(5);
        txt(lang(
            u8"あなたは遺産相続人として認められた(+"s + p + u8")"s,
            u8"You claim the right of succession. (+"s + p + u8")"s));
        txt(lang(
            u8"今やあなたは"s + gdata(97) + u8"個の遺産を相続できる。"s,
            u8"You can now inherit "s + gdata(97) + u8" items."s));
        goto label_2186_internal;
    case 1124:
    case 1125:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        invsubroutine = 1;
        if (efid == 1124)
        {
            invctrl(0) = 23;
            invctrl(1) = 1;
        }
        else
        {
            invctrl(0) = 23;
            invctrl(1) = 2;
        }
        snd(100);
        {
            int stat = label_20592();
            if (stat == 1)
            {
                if (inv_enhancement(ci) < efp / 100)
                {
                    snd(24);
                    txt(lang(
                        itemname(ci) + u8"は黄金の光に包まれた。"s,
                        itemname(ci) + u8" "s + is2(inv_number(ci))
                            + u8" surrounded by a golden aura."s));
                    ++inv_enhancement(ci);
                }
                else
                {
                    txt(lang(
                        itemname(ci) + u8"は抵抗した。"s,
                        itemname(ci) + u8" resist"s + _s2(inv_number(ci))
                            + u8"."s));
                }
                r1 = cc;
                label_1477();
            }
            else
            {
                obvious = 0;
            }
        }
        goto label_2186_internal;
    case 630:
    case 1129:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        if (efid == 630)
        {
            if (gdata(25) < 10)
            {
                txt(lang(
                    u8"充填するには最低でも魔力の貯蓄が10必要だ。"s,
                    u8"You need at least 10 recharge powers to recharge items."s));
                goto label_2186_internal;
            }
            gdata(25) -= 10;
            txt(lang(
                u8"魔力の貯蓄を10消費した(残り"s + gdata(25) + u8")"s,
                u8"You spend 10 recharge powers. (Total:"s + gdata(25)
                    + u8")"s));
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 3;
        snd(100);
        {
            int stat = label_20592();
            if (stat == 1)
            {
                dbid = inv_id(ci);
                dbmode = 2;
                label_1275();
                if (ichargelevel < 1 || inv_id(ci) == 290 || inv_id(ci) == 480
                    || inv_id(ci) == 289 || inv_id(ci) == 732
                    || inv_id(ci) == 687 && inv_param2(ci) != 0)
                {
                    txt(lang(
                        u8"それは充填ができないようだ。"s,
                        u8"You can't recharge this item."s));
                    goto label_2186_internal;
                }
                f = 1;
                if (inv_count(ci) > ichargelevel)
                {
                    f = -1;
                }
                if (f == -1)
                {
                    txt(lang(
                        itemname(ci) + u8"はこれ以上充填できないようだ。"s,
                        itemname(ci) + u8" cannot be recharged anymore."s));
                    goto label_2186_internal;
                }
                if (rnd(efp / 25 + 1) == 0)
                {
                    f = 0;
                }
                if (refitem(inv_id(ci), 5) == 54000)
                {
                    if (rnd(4) == 0)
                    {
                        f = 0;
                    }
                }
                if (rnd(ichargelevel * ichargelevel + 1) == 0)
                {
                    f = 0;
                }
                if (f == 1)
                {
                    p = 1 + rnd((ichargelevel / 2 + 1));
                    if (p + inv_count(ci) > ichargelevel)
                    {
                        p = ichargelevel - inv_count(ci) + 1;
                    }
                    if (refitem(inv_id(ci), 5) == 54000)
                    {
                        p = 1;
                    }
                    txt(lang(
                        itemname(ci) + u8"は充填された(+"s + p + u8")"s,
                        itemname(ci) + u8" "s + is2(inv_number(ci))
                            + u8" recharged by +"s + p + u8"."s));
                    inv_count(ci) += p;
                    animeload(8, cc);
                }
                else
                {
                    if (rnd(4) == 0)
                    {
                        txt(lang(
                            itemname(ci) + u8"は破裂した。"s,
                            itemname(ci) + u8" explode"s + _s2(inv_number(ci))
                                + u8"."s));
                        --inv_number(ci);
                        label_1521();
                        goto label_2186_internal;
                    }
                    txt(lang(
                        itemname(ci) + u8"への充填は失敗した。"s,
                        u8"You fail to recharge "s + itemname(ci) + u8"."s));
                }
            }
            else
            {
                obvious = 0;
            }
        }
        goto label_2186_internal;
    case 629:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 5;
        snd(100);
        {
            int stat = label_20592();
            if (stat == 1)
            {
                dbid = inv_id(ci);
                dbmode = 2;
                label_1275();
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
                    {
                        if (ichargelevel == 1)
                        {
                            p = 100;
                            break;
                        }
                        if (ichargelevel == 2)
                        {
                            p = 25;
                            break;
                        }
                        if (ichargelevel <= 4)
                        {
                            p = 5;
                            break;
                        }
                        if (ichargelevel <= 6)
                        {
                            p = 3;
                            break;
                        }
                        p = 1;
                    }
                }
                animeload(8, cc);
                p = p * inv_count(ci);
                gdata(25) += p;
                txt(lang(
                    itemname(ci) + u8"を破壊して"s + p
                        + u8"の魔力を抽出した(計"s + gdata(25) + u8")"s,
                    u8"You destroy "s + itemname(ci) + u8" and extract "s + p
                        + u8" recharge powers. (Total:"s + gdata(25) + u8")"s));
                inv_number(ci) = 0;
                label_1521();
            }
        }
        goto label_2186_internal;
    case 628:
    label_2184_internal:
        if (tc == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        f = 1;
        if (efp / 10 + 10 < cdata_level(tc))
        {
            f = 0;
        }
        if (cdata_quality(tc) >= 4 || cdata_character_role(tc) != 0
            || cbit(963, tc) == 1 || cbit(976, tc) == 1)
        {
            f = -1;
        }
        if (tc < 57)
        {
            f = 0;
        }
        if (f == 1)
        {
            animeload(8, tc);
            txt(lang(
                name(tc) + u8"は変化した。"s,
                name(tc) + u8" change"s + _s(tc) + u8"."s));
            flt(calcobjlv(cdata_level(tc) + 3), 2);
            characreate(56, 0, -3, 0);
            relocate_chara(56, tc, 1);
            cdata_enemy_id(tc) = cc;
            cbitmod(970, tc, 0);
            check_quest();
        }
        else if (f == 0)
        {
            txt(lang(
                name(tc) + u8"は抵抗した。"s,
                name(tc) + u8" resist"s + _s(tc) + u8"."s));
        }
        else
        {
            txt(lang(
                name(tc) + u8"は変化できない。"s,
                name(tc) + u8" cannot be changed."s));
        }
        goto label_2186_internal;
    case 1140:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 6;
        snd(100);
        {
            int stat = label_20592();
            if (stat == 1)
            {
                autosave = 1 * (gdata(20) != 35);
                animeload(8, cc);
                if (efstatus >= 0)
                {
                    if (inv_weight(ci) > 0)
                    {
                        inv_weight(ci) = limit(
                            inv_weight(ci) * (100 - efp / 10) / 100,
                            1,
                            inv_weight(ci));
                        if (inv_pv(ci) > 0)
                        {
                            inv_pv(ci) -= inv_pv(ci) / 10 + 1 + (efstatus < 1);
                        }
                        if (inv_damage_bonus(ci) > 0)
                        {
                            inv_damage_bonus(ci) -=
                                inv_damage_bonus(ci) / 10 + 1 + (efstatus < 1);
                        }
                    }
                    txt(lang(
                        ""s + itemname(ci, 1)
                            + u8"は羽が生えたように軽くなった。"s,
                        itemname(ci, 1) + u8" becomes light as a feather."s));
                }
                else
                {
                    inv_weight(ci) = inv_weight(ci) * 150 / 100 + 1000;
                    if (inv_pv(ci) > 0)
                    {
                        inv_pv(ci) += limit(inv_pv(ci) / 10, 1, 5);
                    }
                    if (inv_damage_bonus(ci) > 0)
                    {
                        inv_damage_bonus(ci) +=
                            limit(inv_damage_bonus(ci) / 10, 1, 5);
                    }
                    txt(lang(
                        ""s + itemname(ci, 1) + u8"はずしりと重くなった。"s,
                        itemname(ci, 1) + u8" becomes heavy."s));
                }
                label_1521();
            }
            else
            {
                txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
                obvious = 0;
            }
        }
        r1 = cc;
        label_1477();
        goto label_2186_internal;
    case 1132:
        if (cc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvisou = 0;
            goto label_2186_internal;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 4;
        snd(100);
        {
            int stat = label_20592();
            f = stat;
        }
        if (f)
        {
            if (inv_quality(ci) > 4 || ibit(5, ci) == 1)
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            autosave = 1 * (gdata(20) != 35);
            animeload(8, cc);
            fltbk = refitem(inv_id(ci), 5);
            valuebk = calcitemvalue(ci, 0);
            inv_number(ci) = 0;
            {
                int cnt = 0;
                for (;; ++cnt)
                {
                    await();
                    flt(calcobjlv(efp / 10) + 5, calcfixlv(3));
                    if (cnt < 10)
                    {
                        flttypemajor = fltbk;
                    }
                    int stat = itemcreate(0, 0, -1, -1, 0);
                    if (stat == 0)
                    {
                        continue;
                    }
                    if (inv_value(ci) > valuebk * 3 / 2 + 1000)
                    {
                        inv_number(ci) = 0;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            txt(lang(
                u8"それは"s + itemname(ci, 1) + u8"に変容した。"s,
                u8"It is metamorphosed into "s + itemname(ci, 1) + u8"."s));
            label_1521();
        }
        else
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            obvious = 0;
        }
        goto label_2186_internal;
    case 457:
    case 438:
        x = tlocx;
        y = tlocy;
        f = 1;
        if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
        {
            f = 0;
        }
        else
        {
            if (chipm(7, map(x, y, 0)) & 4)
            {
                if (homemapmode == 0)
                {
                    if (efid != 457)
                    {
                        f = 0;
                    }
                    else if (chipm(0, map(x, y, 0)) == 3)
                    {
                        f = 0;
                    }
                }
            }
            if (map(x, y, 1) != 0 || map(x, y, 6) != 0)
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            if (efid == 438)
            {
                if (homemapmode == 0)
                {
                    txt(lang(
                        u8"床が盛り上がってきた。"s, u8"A wall appears."s));
                    p = tile_wall;
                }
                else
                {
                    p = tile;
                }
                if (map(x, y, 0) != p)
                {
                    snd(65);
                }
                map(x, y, 0) = p;
                map(x, y, 2) = p;
            }
            if (efid == 457)
            {
                snd(65);
                if (chipm(0, map(x, y, 0)) == 6)
                {
                    txt(lang(
                        u8"この壁は魔法を受け付けないようだ。"s,
                        u8"These walls seem to resist your magic."s));
                    goto label_2186_internal;
                }
                txt(lang(u8"扉が出現した。"s, u8"A door appears."s));
                cell_featset(x, y, tile_doorclosed, 21, rnd(efp / 10 + 1));
                if (chipm(7, map(x, y, 0)) & 4)
                {
                    map(x, y, 0) = tile_tunnel;
                }
            }
        }
        else
        {
            if (homemapmode == 0)
            {
                txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            }
            obvious = 0;
        }
        goto label_2186_internal;
    case 631:
        txtef(4);
        txt(lang(u8"スウォーム！"s, u8"Swarm!"s));
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
            {
                if (cdata_state(cc) != 1)
                {
                    continue;
                }
                if (cdata_state(cnt) != 1)
                {
                    continue;
                }
                if (cc == cnt)
                {
                    continue;
                }
                if (cnt <= 16)
                {
                    continue;
                }
                tc = cnt;
                dx = cdata_x(tc);
                dy = cdata_y(tc);
                if (dist(cdata_x(cc), cdata_y(cc), dx, dy)
                    > sdataref(3, 631) % 1000 + 1)
                {
                    continue;
                }
                if (fov_los(cdata_x(cc), cdata_y(cc), dx, dy) == 0)
                {
                    continue;
                }
                animeid = 9;
                label_1426();
                label_2218();
            }
        }
        goto label_2186_internal;
    case 659:
        if (mdata(6) == 1)
        {
            goto label_2186_internal;
        }
        if (map(cdata_x(cc), cdata_y(cc), 6) != 0)
        {
            goto label_2186_internal;
        }
        cell_featset(cdata_x(cc), cdata_y(cc), 0, 14, 7, cc);
        if (synccheck(cc, -1))
        {
            txt(lang(
                name(cc) + u8"は何かを投下した。"s,
                name(cc) + u8" drop"s + _s(cc)
                    + u8" something on the ground."s));
        }
        goto label_2186_internal;
    case 466:
    {
        int cnt = 0;
        for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
        {
            if (cdata_state(cnt) != 1)
            {
                continue;
            }
            if (cc == cnt)
            {
                continue;
            }
            if (cbit(31, cnt))
            {
                continue;
            }
            tc = cnt;
            dx = cdata_x(tc);
            dy = cdata_y(tc);
            if (dist(cdata_x(cc), cdata_y(cc), dx, dy) > 4)
            {
                continue;
            }
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(tc) + u8"は重力を感じた。"s,
                    name(tc) + u8" feel"s + _s(tc) + u8" gravity."s));
            }
            cdata_gravity(tc) += 100 + rnd(100);
        }
    }
        goto label_2186_internal;
    case 657:
        txtef(4);
        txt(lang(u8"うみみゃぁ！"s, u8"Mewmewmew!"s));
        animeid = 19;
        animode = 0;
        label_1426();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
            {
                if (cdata_state(cc) != 1)
                {
                    continue;
                }
                if (cdata_state(cnt) != 1)
                {
                    continue;
                }
                if (cc == cnt)
                {
                    continue;
                }
                tc = cnt;
                dmghp(tc, 9999999, cc);
            }
        }
        goto label_2186_internal;
    case 465:
        txtef(4);
        txt(lang(
            u8"隕石が落ちてきた！"s,
            u8"Innumerable meteorites fall all over the area!"s));
        animeid = 22;
        label_1426();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt)
            {
                dy = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt)
                    {
                        dx = cnt;
                        if (rnd(3) == 0)
                        {
                            map(dx, dy, 0) = 12 + rnd(2);
                        }
                        if (rnd(40) == 0)
                        {
                            addmef(dx, dy, 5, 24, rnd(4) + 3, 50);
                        }
                        if (map(dx, dy, 1) != 0)
                        {
                            tc = map(dx, dy, 1) - 1;
                            dmg = sdata(16, cc) * efp / 10;
                            dmghp(tc, dmg, cc, 50, 1000);
                        }
                    }
                }
            }
        }
        goto label_2186_internal;
    case 656:
        if (synccheck(cc, -1))
        {
            txt(lang(
                name(cc) + u8"は仲間を鼓舞した。"s,
                name(cc) + u8" cheer"s + _s(cc) + u8"."s));
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
            {
                if (cdata_state(cnt) != 1)
                {
                    continue;
                }
                if (cc == cnt)
                {
                    continue;
                }
                if (cc < 16)
                {
                    if (cnt >= 16)
                    {
                        continue;
                    }
                    else if (cdata_relationship(cc) != cdata_relationship(tc))
                    {
                        continue;
                    }
                }
                tc = cnt;
                dx = cdata_x(tc);
                dy = cdata_y(tc);
                if (dist(cdata_x(cc), cdata_y(cc), dx, dy)
                    > sdataref(3, 656) % 1000 + 1)
                {
                    continue;
                }
                if (fov_los(cdata_x(cc), cdata_y(cc), dx, dy) == 0)
                {
                    continue;
                }
                if (synccheck(tc, -1))
                {
                    txtef(4);
                    txt(lang(
                        name(tc) + u8"は興奮した！"s,
                        name(tc) + u8" "s + is(tc) + u8" excited!"s));
                }
                addbuff(tc, 5, sdata(17, cc) * 5 + 50, 15);
                addbuff(tc, 7, sdata(17, cc) * 5 + 100, 60);
                addbuff(tc, 18, 1500, 30);
            }
        }
        goto label_2186_internal;
    case 1131:
        if (tc != 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            goto label_2186_internal;
        }
        snd(64);
        if (efstatus >= 0)
        {
            txtef(2);
            txt(lang(
                u8"エーテルの抗体があなたの体内に行き渡った。"s,
                u8"Your Ether Disease is cured greatly."s));
            modcorrupt(efp * -10);
        }
        else
        {
            txtef(8);
            txt(lang(
                u8"エーテルの病菌があなたの体内に行き渡った。"s,
                u8" The Ether Disease spreads around your body."s));
            modcorrupt(200);
        }
        goto label_2186_internal;
    case 633:
        if (tc != 0)
        {
            goto label_2186_internal;
        }
        txtef(8);
        txt(lang(
            name(cc) + u8"に睨まれ、あなたはエーテルに侵食された。"s,
            name(cc) + u8" gazes you. Your Ether Disease deteriorates."s));
        modcorrupt(100);
        goto label_2186_internal;
    case 638:
    case 648:
        if (efid == 648)
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(cc) + u8"は"s + name(tc) + u8"を罵倒した。"s,
                    name(cc) + u8" insult"s + _s(cc) + u8" "s + name(tc)
                        + u8"."s));
                txtmore();
                txtef(9);
                if (jp)
                {
                    if (cdata_sex(cc) == 0)
                    {
                        txt(u8"「すっこんでろ雑魚め」"s,
                            u8"「オマエ程度が戦うだと？」"s,
                            u8"「すぐに殺してやるよ」"s,
                            u8"「消えろザコめ」"s,
                            u8"「このかたつむり野郎」"s,
                            u8"「すぐにミンチにしてやるよ」"s);
                    }
                    else if (rnd(2))
                    {
                        txt(u8"「グシャグシャにしてやるわ」"s,
                            u8"「地べたを這いずりなさい」"s,
                            u8"「ウージッムシ♪ウージッムシ♪」"s,
                            u8"「目障りよ」"s,
                            u8"「もがけ。苦しめ！」"s,
                            u8"「その下品な眼をくりぬくの」"s);
                    }
                    else
                    {
                        txt(u8"「このカタツムリが」"s,
                            u8"「どうしたの？もう終わりなの？」"s,
                            u8"「潔く、くたばりなさい」"s,
                            u8"「生まれてきたことを後悔するのね」"s,
                            u8"「このブタめ」"s,
                            u8"「すぐにミンチにしてあげる」"s);
                    }
                }
                else if (rnd(2))
                {
                    txt(cnvtalk(u8"You suck!"s),
                        cnvtalk(u8"You will die alone."s),
                        cnvtalk(u8"Bow down before me."s),
                        cnvtalk(u8"Go jump off a bridge."s),
                        cnvtalk(u8"Bang your head against the wall!"s),
                        cnvtalk(u8"Why do you sniff under your dog's tail?"s));
                }
                else
                {
                    txt(cnvtalk(
                            u8"The world is against you because you are a unsavory decomposing virus."s),
                        cnvtalk(
                            u8"You are no better than a immoral guzzling bureaucrat."s),
                        cnvtalk(u8"You are so lowly."s),
                        cnvtalk(u8"Get off me."s));
                }
            }
        }
        dmgcon(tc, 7, 200);
        goto label_2186_internal;
    case 652:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(cc) + u8"は"s + name(tc) + u8"を睨み付けた。"s,
                name(cc) + u8" gaze"s + _s(cc) + u8" "s + name(tc) + u8"."s));
        }
        dmgmp(tc, rnd(20) + 1);
        goto label_2186_internal;
    case 1133:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(tc) + u8"は炎に包まれた。"s,
                name(tc) + u8" "s + is(tc) + u8" surrounded by flames."s));
        }
        addmef(cdata_x(tc), cdata_y(tc), 5, 24, rnd(15) + 25, efp, cc);
        mapitem_fire(cdata_x(tc), cdata_y(tc));
        return 0;
    case 651:
        if (synccheck(tc, -1))
        {
            txt(lang(
                name(cc) + u8"は"s + name(tc) + u8"のバックパックを漁った。"s,
                name(cc) + u8" loot"s + _s(cc) + u8" "s + name(tc) + your(tc)
                    + u8" backpack."s));
        }
        p = -1;
        inv_getheader(tc);
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv_number(cnt) == 0)
                {
                    continue;
                }
                if (inv_id(cnt) == 618)
                {
                    p = cnt;
                    break;
                }
            }
        }
        if (p == -1)
        {
            inv_getheader(tc);
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    if (inv_number(cnt) == 0)
                    {
                        continue;
                    }
                    if (ibit(5, cnt))
                    {
                        continue;
                    }
                    if (refitem(inv_id(cnt), 5) != 57000)
                    {
                        continue;
                    }
                    p = cnt;
                    break;
                }
            }
        }
        if (p == -1)
        {
            goto label_2186_internal;
        }
        ci = p;
        if (ibit(6, ci))
        {
            if (synccheck(tc, -1))
            {
                txt(lang(
                    name(cc) + u8"は"s + itemname(ci, 1)
                        + u8"の異臭に気付き手をひっこめた。"s,
                    name(cc) + u8" notice"s + _s(cc) + u8" unusual odor from "s
                        + itemname(ci, 1) + u8" and step"s + _s(cc)
                        + u8" back."s));
            }
            goto label_2186_internal;
        }
        rowact_item(ci);
        if (synccheck(tc, -1))
        {
            snd(18);
            txt(lang(
                name(cc) + u8"は"s + itemname(ci, 1) + u8"を食べた！"s,
                name(cc) + u8" eat"s + _s(cc) + u8" "s + itemname(ci, 1)
                    + u8"!"s));
        }
        healhp(cc, cdata_max_hp(cc) / 3);
        label_2161();
        label_1521();
        goto label_2186_internal;
    case 464:
        animeload(10, tc);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (limit(4 + rnd((efp / 50 + 1)), 1, 15));
                 cnt < cnt_end;
                 ++cnt)
            {
                snd(64);
                flt(calcobjlv(efp / 10), calcfixlv(3));
                dbid = 0;
                dbid = 54;
                p = 400 + rnd(efp);
                if (rnd(30) == 0)
                {
                    dbid = 55;
                    p = 1;
                }
                if (rnd(80) == 0)
                {
                    dbid = 622;
                    p = 1;
                }
                if (rnd(2000) == 0)
                {
                    dbid = 290;
                    p = 1;
                }
                nostack = 1;
                itemcreate(-1, dbid, cdata_x(cc), cdata_y(cc), p);
                txt(lang(
                    itemname(ci) + u8"が降ってきた！"s,
                    itemname(ci) + u8" fall"s + _s2(inv_number(ci))
                        + u8" down!"s));
                await(100);
                redraw(1);
            }
        }
        goto label_2186_internal;
    case 463:
        snd(72);
        txt(lang(
            u8"あなたは四次元のポケットを召喚した。"s,
            u8"You summon 4 dimensional pocket."s));
        invfile = 8;
        file = u8"shoptmp.s2"s;
        fmode = 4;
        label_2107();
        file = u8"shop"s + invfile + u8".s2"s;
        exist(fs::u8path(u8"./tmp/"s + file));
        if (strsize != -1)
        {
            fmode = 3;
            label_2107();
        }
        else
        {
            inv_getheader(-1);
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    inv_number(cnt) = 0;
                }
            }
        }
        shoptrade = 0;
        menucycle = 1;
        invsubroutine = 1;
        invctrl(0) = 22;
        invctrl(1) = 5;
        invcontainer = limit(efp / 10 + 10, 10, 300);
        mode = 6;
        snd(100);
        label_20592();
        invcontainer = 0;
        file = u8"shop"s + invfile + u8".s2"s;
        fmode = 4;
        label_2107();
        file = u8"shoptmp.s2"s;
        fmode = 3;
        label_2107();
        mode = 0;
        goto label_2186_internal;
    }
label_2186_internal:
    ci = efcibk;
    efstatus = 0;
    efsource = 0;
    return 1;
}


} // namespace elona
