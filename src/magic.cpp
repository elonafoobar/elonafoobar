#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "db_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "wish.hpp"


namespace elona
{


int magic()
{
    int efcibk = 0;
    int efbad = 0;
    int chainbomb = 0;
    elona_vector1<int> chainbomblist;
    int tcprev = 0;
    int telex = 0;
    int teley = 0;
    int efidprev = 0;
    int ccprev = 0;
    int fltbk = 0;
    int valuebk = 0;
    efcibk = ci;
    efcancel = 0;
    obvious = 1;
    if (efsource != 4 && efsource != 1 && efsource != 2)
    {
        efstatus = CurseState::none;
    }
    efsource = 0;
    efbad = 0;


    if (efid >= 300)
    {
        if (efid < 661)
        {
            f = 0;
            if (the_ability_db[efid]->sdataref1 / 1000 == 1)
            {
                f = 1;
                p = the_ability_db[efid]->sdataref1 % 1000;
                if (the_buff_db[p]->type == buff_data::Type::hex)
                {
                    efbad = 1;
                }
            }
            if (the_ability_db[efid]->sdataref1 == 7)
            {
                efbad = 1;
            }
            if (efbad == 0)
            {
                if (efstatus == CurseState::blessed)
                {
                    efp = efp * 150 / 100;
                }
                if (is_cursed(efstatus))
                {
                    efp = 50;
                }
            }
            else
            {
                if (efstatus == CurseState::blessed)
                {
                    efp = 50;
                }
                if (is_cursed(efstatus))
                {
                    efp = efp * 150 / 100;
                }
            }
            if (f)
            {
                if (the_buff_db[p]->type == buff_data::Type::buff)
                {
                    animeload(11, tc);
                }
                else if (the_buff_db[p]->type == buff_data::Type::hex)
                {
                    bright_aura_animation(
                        cdata[tc].position,
                        bright_aura_animation::Type::debuff)
                        .play();
                }
                if (efid == 625 || efid == 446)
                {
                    if ((tc == 0 && cc == 0) || cc == gdata_mount)
                    {
                        if (gdata_mount != 0)
                        {
                            tc = gdata_mount;
                        }
                    }
                }
                buff_add(
                    cdata[tc], p, efp, calc_buff_duration(p, efp), cdata[cc]);
                if (efid == 447)
                {
                    if (efstatus == CurseState::blessed)
                    {
                        cdata[tc].birth_year += rnd(3) + 1;
                        if (cdata[tc].birth_year + 12 > gdata_year)
                        {
                            cdata[tc].birth_year = gdata_year - 12;
                        }
                        if (is_in_fov(cdata[tc]))
                        {
                            txtef(2);
                            txt(i18n::s.get(
                                "core.locale.magic.slow", cdata[tc]));
                        }
                    }
                }
                if (efid == 446)
                {
                    if (is_cursed(efstatus))
                    {
                        cdata[tc].birth_year -= rnd(3) + 1;
                        if (is_in_fov(cdata[tc]))
                        {
                            txtef(8);
                            txt(i18n::s.get(
                                "core.locale.magic.speed", cdata[tc]));
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
                goto the_end;
            }
            if (const auto damage = calc_skill_damage(efid, cc, efp))
            {
                dice1 = damage->dice_x;
                dice2 = damage->dice_y;
                bonus = damage->damage_bonus;
                ele = damage->element;
                elep = damage->element_power;
            }
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
                elep = elep * 4 / 5 + 1;
                dice1 = dice1 * 4 / 5 + 1;
                dice2 = dice2 * 4 / 5 + 1;
                bonus = bonus * 4 / 5 + 1;
            }
            switch (the_ability_db[efid]->sdataref1)
            {
            case 10:
                ranged_attack_animation(
                    cdata[cc].position,
                    cdata[tc].position,
                    ranged_attack_animation::Type::distant_attack)
                    .play();
                try_to_melee_attack();
                goto the_end;
            case 1:
            {
                int stat = get_route(
                    cdata[cc].position.x, cdata[cc].position.y, tlocx, tlocy);
                if (stat == 0)
                {
                    goto the_end;
                }
            }
                {
                    int distance = the_ability_db[efid]->sdataref3 % 1000 + 1;
                    bolt_animation(
                        cdata[cc].position, {tlocx, tlocy}, ele, distance)
                        .play();
                }
                dx = cdata[cc].position.x;
                dy = cdata[cc].position.y;
                for (int cnt = 0; cnt < 20; ++cnt)
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
                    if (dist(dx, dy, cdata[cc].position.x, cdata[cc].position.y)
                        > the_ability_db[efid]->sdataref3 % 1000 + 1)
                    {
                        break;
                    }
                    if (dx == cdata[cc].position.x
                        && dy == cdata[cc].position.y)
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
                            if (gdata_mount != 0)
                            {
                                if (gdata_mount == cc)
                                {
                                    if (tc == 0)
                                    {
                                        continue;
                                    }
                                }
                            }
                            dmg = roll(dice1, dice2, bonus);
                            int stat = calcmagiccontrol(cc, tc);
                            if (stat == 1)
                            {
                                continue;
                            }
                            if (is_in_fov(cdata[tc]))
                            {
                                if (tc >= 16)
                                {
                                    gdata(809) = 2;
                                    txt3rd = 1;
                                    txt(i18n::s.get(
                                        "core.locale.magic.bolt.other",
                                        cdata[tc]));
                                }
                                else
                                {
                                    txt(i18n::s.get(
                                        "core.locale.magic.bolt.ally",
                                        cdata[tc]));
                                }
                            }
                            damage_hp(cdata[tc], dmg, cc, ele, elep);
                        }
                    }
                }
                goto the_end;
            case 3:
                chainbomb = 0;
                ccbk = cc;
                if (efid == 644)
                {
                    stxt(
                        cc,
                        i18n::s.get(
                            "core.locale.magic.explosion.begins", cdata[cc]));
                }
            label_2177_internal:
                cdata[cc].will_explode_soon() = false;
                range_ = the_ability_db[efid]->sdataref3 % 1000 + 1;
                if (debug::voldemort && cc == 0)
                {
                    range_ *= 2;
                }
                if (efid == 644)
                {
                    range_ = 2;
                }
                if (efid != 404 && efid != 637)
                {
                    ball_animation(
                        {tlocx, tlocy},
                        range_,
                        ball_animation::Type::ball,
                        ele)
                        .play();
                }
                for (int cnt = 0, cnt_end = (range_ * 2 + 1); cnt < cnt_end;
                     ++cnt)
                {
                    dy = tlocy - range_ + cnt;
                    if (dy < 0 || dy >= mdata_map_height)
                    {
                        continue;
                    }
                    for (int cnt = 0, cnt_end = (range_ * 2 + 1); cnt < cnt_end;
                         ++cnt)
                    {
                        dx = tlocx - range_ + cnt;
                        if (dx < 0 || dx >= mdata_map_width)
                        {
                            continue;
                        }
                        if (dist(tlocx, tlocy, dx, dy) > range_)
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
                            if (cc == 0 || cdata[cc].relationship >= 0)
                            {
                                if (cdata[tc].relationship >= 0)
                                {
                                    f = 1;
                                }
                            }
                            else if (cdata[tc].relationship <= -1)
                            {
                                f = 1;
                            }
                            if (f == 1)
                            {
                                bright_aura_animation(
                                    cdata[tc].position,
                                    bright_aura_animation::Type::healing_rain)
                                    .play();
                                if (is_in_fov(cdata[tc]))
                                {
                                    txt(i18n::s.get(
                                        "core.locale.magic.healed.normal",
                                        cdata[tc]));
                                }
                                heal_both_rider_and_mount();
                            }
                            continue;
                        }
                        if (efid == 637)
                        {
                            f = 0;
                            if (cc == 0 || cdata[cc].relationship >= 0)
                            {
                                if (cdata[tc].relationship >= 0)
                                {
                                    f = 1;
                                }
                            }
                            else if (cdata[tc].relationship <= -1)
                            {
                                f = 1;
                            }
                            if (f == 1)
                            {
                                bright_aura_animation(
                                    cdata[tc].position,
                                    bright_aura_animation::Type::healing_rain)
                                    .play();
                                txt(i18n::s.get(
                                    "core.locale.magic.rain_of_sanity",
                                    cdata[tc]));
                                heal_insanity(cdata[tc], efp / 10);
                                healcon(tc, 11, 9999);
                            }
                            continue;
                        }
                        if (dx == cdata[cc].position.x
                            && dy == cdata[cc].position.y)
                        {
                            continue;
                        }
                        if (gdata_mount != 0)
                        {
                            if (gdata_mount == cc)
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
                            dmg = roll(dice1, dice2, bonus) * 100
                                / (75 + dist(tlocx, tlocy, dx, dy) * 25);
                            int stat = calcmagiccontrol(cc, tc);
                            if (stat == 1)
                            {
                                continue;
                            }
                            if (efid == 644)
                            {
                                if (is_in_fov(cdata[tc]))
                                {
                                    if (tc >= 16)
                                    {
                                        gdata(809) = 2;
                                        txt3rd = 1;
                                        txt(i18n::s.get(
                                            "core.locale.magic.explosion.other",
                                            cdata[tc]));
                                    }
                                    else
                                    {
                                        txt(i18n::s.get(
                                            "core.locale.magic.explosion.ally",
                                            cdata[tc]));
                                    }
                                }
                                if (cdata[tc].explodes())
                                {
                                    chainbomblist(chainbomb) = tc;
                                    ++chainbomb;
                                    continue;
                                }
                            }
                            else if (is_in_fov(cdata[tc]))
                            {
                                if (tc >= 16)
                                {
                                    gdata(809) = 2;
                                    txt3rd = 1;
                                    txt(i18n::s.get(
                                        "core.locale.magic.ball.other",
                                        cdata[tc]));
                                }
                                else
                                {
                                    txt(i18n::s.get(
                                        "core.locale.magic.ball.ally",
                                        cdata[tc]));
                                }
                            }
                            damage_hp(cdata[tc], dmg, cc, ele, elep);
                        }
                    }
                }
                if (efid == 644)
                {
                    damage_hp(cdata[cc], 99999, -16);
                }
                if (chainbomb > 0)
                {
                    while (1)
                    {
                        --chainbomb;
                        if (chainbomb < 0)
                            break;
                        cc = chainbomblist(chainbomb);
                        tlocx = cdata[cc].position.x;
                        tlocy = cdata[cc].position.y;
                        if (cdata[cc].state() == character::State::alive)
                        {
                            const auto damage =
                                calc_skill_damage(efid, cc, efp);
                            dice1 = damage->dice_x;
                            dice2 = damage->dice_y;
                            bonus = damage->damage_bonus;
                            ele = damage->element;
                            elep = damage->element_power;
                            stxt(
                                cc,
                                i18n::s.get(
                                    "core.locale.magic.explosion.chain",
                                    cdata[cc]));
                            goto label_2177_internal;
                        }
                    }
                }
                cc = ccbk;
                goto the_end;
            case 2:
                ranged_attack_animation(
                    cdata[cc].position,
                    cdata[tc].position,
                    ranged_attack_animation::Type::magic_arrow)
                    .play();
                dmg = roll(dice1, dice2, bonus);
                if (is_in_fov(cdata[tc]))
                {
                    if (tc >= 16)
                    {
                        gdata(809) = 2;
                        txt3rd = 1;
                        txt(i18n::s.get(
                            "core.locale.magic.arrow.other", cdata[tc]));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.arrow.ally", cdata[tc]));
                    }
                }
                damage_hp(cdata[tc], dmg, cc, ele, elep);
                goto the_end;
            case 4:
                if (efid == 400)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.healed.slightly", cdata[tc]));
                    }
                }
                if (efid == 401 || efid == 405)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.healed.normal", cdata[tc]));
                    }
                }
                if (efid == 402)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.healed.greatly", cdata[tc]));
                    }
                }
                if (efid == 403)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.healed.completely", cdata[tc]));
                    }
                }
                heal_both_rider_and_mount();
                if (efstatus == CurseState::blessed)
                {
                    healcon(tc, 12, 5 + rnd(5));
                }
                if (rnd(3) == 0)
                {
                    get_sick_if_cursed(efstatus, cdata[tc]);
                }
                bright_aura_animation(
                    cdata[tc].position, bright_aura_animation::Type::healing)
                    .play();
                goto the_end;
            case 6:
                if (cdata[cc].special_attack_type != 0)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        if (cc == 0)
                        {
                            txt(i18n::s.get(
                                "core.locale.magic.special_attack.self",
                                cdata[cc],
                                i18n::_(
                                    u8"ability",
                                    std::to_string(efid),
                                    u8"name"),
                                i18n::_(
                                    u8"ui",
                                    u8"cast_style",
                                    u8"_"s + cdata[cc].special_attack_type)));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.locale.magic.special_attack.other",
                                cdata[cc],
                                i18n::_(
                                    u8"ui",
                                    u8"cast_style",
                                    u8"_"s + cdata[cc].special_attack_type)));
                        }
                    }
                }
                else if (efid == 601)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        if (tc >= 16)
                        {
                            gdata(809) = 2;
                            txt(i18n::s.get(
                                "core.locale.magic.sucks_blood.other",
                                cdata[cc],
                                cdata[tc]));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.locale.magic.sucks_blood.ally",
                                cdata[cc],
                                cdata[tc]));
                        }
                    }
                }
                else if (efid == 660)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get("core.locale.magic.disassembly"));
                    }
                }
                else if (is_in_fov(cdata[cc]))
                {
                    if (tc >= 16)
                    {
                        gdata(809) = 2;
                        txt(i18n::s.get(
                            "core.locale.magic.touch.other",
                            cdata[cc],
                            cdata[tc],
                            elename(ele),
                            _melee(2, cdata[cc].melee_attack_type),
                            _melee(0, cdata[cc].melee_attack_type)));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.touch.ally",
                            cdata[cc],
                            cdata[tc],
                            elename(ele),
                            _melee(2, cdata[cc].melee_attack_type),
                            _melee(1, cdata[cc].melee_attack_type)));
                    }
                }
                if (efid == 660)
                {
                    cdata[tc].hp = cdata[tc].max_hp / 12 + 1;
                    goto the_end;
                }
                damage_hp(cdata[tc], roll(dice1, dice2, bonus), cc, ele, elep);
                if (efid == 617)
                {
                    dmgcon(tc, StatusAilment::fear, elep);
                }
                if (efid == 618)
                {
                    dmgcon(tc, StatusAilment::sleep, elep);
                }
                if (efid == 614)
                {
                    cdata[tc].nutrition -= 800;
                    if (is_in_fov(cdata[tc]))
                    {
                        txtef(8);
                        txt(i18n::s.get("core.locale.magic.hunger", cdata[tc]));
                    }
                    get_hungry(cdata[tc]);
                }
                if (efid == 613)
                {
                    p = rnd(10);
                    if ((cdata[tc].quality >= 4 && rnd(4))
                        || encfind(tc, 60010 + p) != -1)
                    {
                        p = -1;
                    }
                    if (p != -1)
                    {
                        i = sdata.get(10 + p, tc).original_level
                            + cdata[tc].attr_adjs[p];
                        if (i > 0)
                        {
                            i = i * efp / 2000 + 1;
                            cdata[tc].attr_adjs[p] -= i;
                        }
                        if (is_in_fov(cdata[tc]))
                        {
                            txtef(8);
                            txt(i18n::s.get(
                                "core.locale.magic.weaken", cdata[tc]));
                        }
                        chara_refresh(tc);
                    }
                }
                goto the_end;
            case 7:
                if (cc == 0)
                {
                    if (gdata_crowd_density + 100 >= ELONA_MAX_OTHER_CHARACTERS)
                    {
                        txt(i18n::s.get("core.locale.common.nothing_happens"));
                        obvious = 0;
                        goto the_end;
                    }
                }
                p = 3;
                efp = (efp / 25 + efp * efp / 10000 + cdata[cc].level) / 2;
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
                for (int cnt = 0, cnt_end = (1 + rnd(p)); cnt < cnt_end; ++cnt)
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
                    const auto success = chara_create(
                        -1, dbid, cdata[tc].position.x, cdata[tc].position.y);
                    if (success && efid != 643)
                    {
                        if (cdata[rc].id == cdata[cc].id)
                        {
                            chara_vanquish(rc);
                            --cnt;
                            continue;
                        }
                    }
                }
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.locale.magic.summon"));
                }
                goto the_end;
            case 5:
                tcprev = tc;
                if (gdata_mount != 0)
                {
                    if (gdata_mount == tc)
                    {
                        goto the_end;
                    }
                }
                if (efid == 408)
                {
                    tc = cc;
                }
                if (efid == 619)
                {
                    telex = cdata[tc].position.x;
                    teley = cdata[tc].position.y;
                    tc = cc;
                    if (gdata_mount != 0 && gdata_mount == tc)
                    {
                        goto the_end;
                    }
                }
                if (efid == 620)
                {
                    telex = cdata[cc].position.x;
                    teley = cdata[cc].position.y;
                }
                if (efid == 409 || efid == 635)
                {
                    if (map(tlocx, tlocy, 1) == 0)
                    {
                        txt(i18n::s.get("core.locale.common.nothing_happens"));
                        obvious = 0;
                        goto the_end;
                    }
                    tc = map(tlocx, tlocy, 1) - 1;
                }
                if (gdata_current_map == mdata_t::MapId::pet_arena
                    || mdata_map_type == mdata_t::MapType::world_map
                    || gdata_current_map == mdata_t::MapId::pyramid
                    || gdata_current_map == mdata_t::MapId::jail)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.teleport.prevented"));
                    }
                    goto the_end;
                }
                if (efid != 619 && efid != 635 && encfind(tc, 22) != -1)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.teleport.prevented"));
                    }
                    goto the_end;
                }
                if (efid == 635)
                {
                    if (encfind(cc, 22) != -1)
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                "core.locale.magic.teleport.prevented"));
                        }
                        goto the_end;
                    }
                    p = rnd(cdata[tc].gold / 10 + 1);
                    if (rnd(sdata(13, tc)) > rnd(sdata(12, cc) * 4)
                        || cdata[tc].is_protected_from_thieves() == 1)
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.teleport.suspicious_hand."
                            "prevented",
                            cdata[tc]));
                        p = 0;
                    }
                    if (p != 0)
                    {
                        snd(12);
                        cdata[tc].gold -= p;
                        txt(i18n::s.get(
                            "core.locale.magic.teleport.suspicious_hand."
                            "succeeded",
                            cdata[cc],
                            cdata[tc],
                            p(0)));
                        earn_gold(cdata[cc], p);
                    }
                    tc = cc;
                    if (gdata_mount != 0)
                    {
                        if (gdata_mount == tc)
                        {
                            goto the_end;
                        }
                    }
                }
                if (is_in_fov(cdata[tc]))
                {
                    snd_at(72, cdata[tc].position);
                }
                tx = cdata[tc].position.x;
                ty = cdata[tc].position.y;
                efidprev = efid;
                for (int cnt = 0; cnt < 200; ++cnt)
                {
                    if (efidprev == 410 || efidprev == 627)
                    {
                        p(0) = -1;
                        p(1) = 1;
                        cdata[tc].next_position.x = cdata[tc].position.x
                            + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
                        cdata[tc].next_position.y = cdata[tc].position.y
                            + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
                    }
                    else if (efidprev == 619)
                    {
                        cdata[tc].next_position.x =
                            telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                        cdata[tc].next_position.y =
                            teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                    }
                    else if (efidprev == 620)
                    {
                        cdata[tc].next_position.x =
                            telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                        cdata[tc].next_position.y =
                            teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                    }
                    else
                    {
                        cdata[tc].next_position.x =
                            rnd(mdata_map_width - 2) + 1;
                        cdata[tc].next_position.y =
                            rnd(mdata_map_height - 2) + 1;
                    }
                    cell_check(
                        cdata[tc].next_position.x, cdata[tc].next_position.y);
                    if (cellaccess == 1)
                    {
                        if (efidprev == 619)
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                txt(i18n::s.get(
                                    "core.locale.magic.teleport.shadow_step",
                                    cdata[cc],
                                    cdata[tcprev]));
                            }
                        }
                        else if (efidprev == 620)
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                txt(i18n::s.get(
                                    "core.locale.magic.teleport.draw_shadow",
                                    cdata[tc]));
                            }
                        }
                        else if (is_in_fov(cdata[cc]))
                        {
                            if (efidprev == 635)
                            {
                                txt(
                                    i18n::s.get("core.locale.magic.teleport."
                                                "suspicious_hand.after"));
                            }
                            else
                            {
                                txt(i18n::s.get(
                                    "core.locale.magic.teleport.disappears",
                                    cdata[tc]));
                            }
                        }
                        rowactend(cc);
                        ccprev = cc;
                        cc = tc;
                        proc_trap();
                        cc = ccprev;
                        if (tc == 0)
                        {
                            update_screen();
                        }
                        break;
                    }
                }
                tc = tcprev;
                goto the_end;
            case 8:
                int stat = get_route(
                    cdata[cc].position.x, cdata[cc].position.y, tlocx, tlocy);
                if (stat == 0)
                {
                    goto the_end;
                }
                std::string valn;
                if (ele)
                {
                    valn = i18n::s.get(
                        "core.locale.magic.breath.named",
                        i18n::_(u8"ability", std::to_string(ele), u8"name"));
                }
                else
                {
                    valn = i18n::s.get("core.locale.magic.breath.no_element");
                }
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.locale.magic.breath.bellows", cdata[cc], valn));
                }
                dx = cdata[cc].position.x;
                dy = cdata[cc].position.y;
                breath_list();
                breath_animation(cdata[cc].position, {tlocx, tlocy}, ele)
                    .play();
                for (int cnt = 0, cnt_end = (maxbreath); cnt < cnt_end; ++cnt)
                {
                    dx = breathlist(0, cnt);
                    dy = breathlist(1, cnt);
                    if (fov_los(
                            cdata[cc].position.x, cdata[cc].position.y, dx, dy)
                        == 0)
                    {
                        continue;
                    }
                    if (dx == cdata[cc].position.x
                        && dy == cdata[cc].position.y)
                    {
                        continue;
                    }
                    if (gdata_mount != 0)
                    {
                        if (gdata_mount == cc)
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
                            dmg = roll(dice1, dice2, bonus);
                            if (is_in_fov(cdata[tc]))
                            {
                                if (tc >= 16)
                                {
                                    gdata(809) = 2;
                                    txt3rd = 1;
                                    txt(i18n::s.get(
                                        "core.locale.magic.breath.other",
                                        cdata[tc]));
                                }
                                else
                                {
                                    txt(i18n::s.get(
                                        "core.locale.magic.breath.ally",
                                        cdata[tc]));
                                }
                            }
                            damage_hp(cdata[tc], dmg, cc, ele, elep);
                        }
                    }
                }
                goto the_end;
            }
            goto label_2181_internal;
        }
        else
        {
            if (efstatus == CurseState::blessed)
            {
                efp = efp * 150 / 100;
            }
            if (is_cursed(efstatus))
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
        txt(i18n::s.get("core.locale.magic.insanity", cdata[cc], cdata[tc]));
        damage_insanity(cdata[tc], rnd(roll(dice1, dice2, bonus) + 1));
        break;
    case 1136:
        if (mdata_map_type != mdata_t::MapType::world_map)
        {
            txt(i18n::s.get("core.locale.magic.map.need_global_map"));
            break;
        }
        if (is_cursed(efstatus))
        {
            if (rnd(5) == 0)
            {
                txt(i18n::s.get("core.locale.magic.map.cursed"));
                inv[ci].modify_number(-1);
                break;
            }
        }
        if (inv[ci].param1 == 0)
        {
            item_separate(ci);
            for (int cnt = 0; cnt < 1000; ++cnt)
            {
                dx = 4 + rnd((mdata_map_width - 8));
                dy = 3 + rnd((mdata_map_height - 6));
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
                for (int cnt = 0; cnt < 4; ++cnt)
                {
                    f = 1;
                    int cnt2 = cnt;
                    for (int cnt = 0; cnt < 3; ++cnt)
                    {
                        p = map(dx + x(cnt2) * cnt, dy + y(cnt2) * cnt, 0);
                        if ((264 <= p && p < 363) || chipm(7, p) & 4)
                        {
                            f = 0;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        break;
                    }
                }
                if (f == 1)
                {
                    break;
                }
            }
            inv[ci].param1 = dx;
            inv[ci].param2 = dy;
        }
        txt(i18n::s.get("core.locale.magic.map.apply"));
        snd(59);
        gsel(4);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"paper.bmp", 1);
        gsel(0);
        ww = 400;
        wh = 300;
        wx = (windoww - ww) / 2 + inf_screenx;
        wy = winposy(wh);
        gmode(2);
        pos(wx, wy);
        gcopy(4, 0, 0, ww, wh);
        gmode(1);
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            y = cnt + inv[ci].param2 - 2;
            sy = cnt * inf_tiles + wy + 26;
            for (int cnt = 0; cnt < 7; ++cnt)
            {
                x = cnt + inv[ci].param1 - 3;
                sx = cnt * inf_tiles + wx + 46;
                p = map(x, y, 0);
                pos(sx + 1, sy + 1);
                gcopy(
                    2,
                    p % 33 * inf_tiles,
                    p / 33 * inf_tiles,
                    inf_tiles,
                    inf_tiles);
                if (x == inv[ci].param1)
                {
                    if (y == inv[ci].param2)
                    {
                        pos(sx, sy);
                        font(40 - en * 2, snail::font_t::Style::italic);
                        color(255, 20, 20);
                        mes(i18n::s.get("core.locale.magic.map.mark"));
                        color(0, 0, 0);
                    }
                }
            }
        }
        gmode(2);
        pos(wx, wy);
        gcopy(4, 400, 0, ww, wh);
        redraw();
        wait_key_pressed();
        snd(71);
        break;
    case 1135:
        if (is_cursed(efstatus))
        {
            if (tc == 0)
            {
                eatstatus(efstatus, tc);
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.magic.love_potion.cursed", cdata[tc]));
                chara_modify_impression(cdata[tc], -15);
            }
            obvious = 0;
            break;
        }
        cdata[tc].emotion_icon = 317;
        if (potionspill || potionthrow)
        {
            txt(i18n::s.get("core.locale.magic.love_potion.spill", cdata[tc]));
            chara_modify_impression(cdata[tc], clamp(efp / 15, 0, 15));
            dmgcon(tc, StatusAilment::dimmed, 100);
            lovemiracle(tc);
            break;
        }
        if (tc == 0)
        {
            txt(i18n::s.get("core.locale.magic.love_potion.self", cdata[tc]));
        }
        else
        {
            txt(i18n::s.get("core.locale.magic.love_potion.other", cdata[tc]));
            lovemiracle(tc);
            chara_modify_impression(cdata[tc], clamp(efp / 4, 0, 25));
        }
        dmgcon(tc, StatusAilment::dimmed, 500);
        break;
    case 654:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get(
                "core.locale.magic.pregnant", cdata[cc], cdata[tc]));
        }
        get_pregnant();
        break;
    case 626:
        txt(i18n::s.get("core.locale.magic.mirror"));
        animeload(10, tc);
        screen_analyze_self();
        break;
    case 1101:
        if (is_in_fov(cdata[tc]))
        {
            snd(107);
            if (is_cursed(efstatus))
            {
                if (tc == 0)
                {
                    txt(i18n::s.get("core.locale.magic.milk.cursed.self"));
                }
                else
                {
                    txtef(9);
                    txt(i18n::s.get("core.locale.magic.milk.cursed.other"));
                }
            }
            else if (tc == 0)
            {
                txt(i18n::s.get("core.locale.magic.milk.self"));
            }
            else
            {
                txtef(9);
                txt(i18n::s.get("core.locale.magic.milk.other"));
            }
        }
        if (efstatus == CurseState::blessed)
        {
            modify_height(cdata[tc], rnd(5) + 1);
        }
        if (is_cursed(efstatus))
        {
            modify_height(cdata[tc], (rnd(5) + 1) * -1);
        }
        cdata[tc].nutrition += 1000 * (efp / 100);
        if (tc == 0)
        {
            show_eating_message();
        }
        eatstatus(efstatus, tc);
        animeload(15, tc);
        break;
    case 1102:
        if (is_in_fov(cdata[tc]))
        {
            if (is_cursed(efstatus))
            {
                txtef(9);
                txt(i18n::s.get("core.locale.magic.alcohol.cursed"));
            }
            else
            {
                txtef(9);
                txt(i18n::s.get("core.locale.magic.alcohol.normal"));
            }
        }
        dmgcon(tc, StatusAilment::drunk, efp);
        eatstatus(efstatus, tc);
        break;
    case 1116:
        if (is_in_fov(cdata[tc]))
        {
            if (tc == 0)
            {
                txt(i18n::s.get("core.locale.magic.acid.self"));
            }
            txt(i18n::s.get("core.locale.magic.acid.apply", cdata[tc]));
        }
        if (cdata[tc].is_pregnant())
        {
            cdata[tc].is_pregnant() = false;
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.common.melts_alien_children",
                    cdata[tc]));
            }
        }
        damage_hp(
            cdata[tc],
            efp * efstatusfix(500, 400, 100, 50) / 1000,
            -15,
            63,
            efp);
        break;
    case 1103:
        if (is_in_fov(cdata[tc]))
        {
            if (tc == 0)
            {
                txt(i18n::s.get("core.locale.magic.water.self"));
            }
            else
            {
                txt(i18n::s.get("core.locale.magic.water.other"));
            }
        }
        get_sick_if_cursed(efstatus, cdata[tc]);
        break;
    case 1146:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.restore_stamina.dialog"));
            txt(i18n::s.get(
                "core.locale.magic.restore_stamina.apply", cdata[tc]));
        }
        heal_sp(cdata[tc], 25);
        get_sick_if_cursed(efstatus, cdata[tc]);
        break;
    case 1147:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get(
                "core.locale.magic.restore_stamina_greater.dialog"));
            txt(i18n::s.get(
                "core.locale.magic.restore_stamina_greater.apply", cdata[tc]));
        }
        heal_sp(cdata[tc], 100);
        get_sick_if_cursed(efstatus, cdata[tc]);
        break;
    case 1142:
        if (cdatan(2, tc) == u8"snail"s)
        {
            if (is_in_fov(cdata[tc]))
            {
                txtef(3);
                txt(i18n::s.get("core.locale.magic.salt.snail", cdata[tc]));
            }
            if (cdata[tc].hp > 10)
            {
                damage_hp(cdata[tc], cdata[tc].hp - rnd(10), -15);
            }
            else
            {
                damage_hp(cdata[tc], rnd(20000), -15);
            }
        }
        else if (is_in_fov(cdata[tc]))
        {
            txtef(9);
            txt(i18n::s.get("core.locale.magic.salt.apply"));
        }
        break;
    case 1130:
        if (is_in_fov(cdata[tc]))
        {
            if (tc == 0)
            {
                txt(i18n::s.get("core.locale.magic.dirty_water.self"));
            }
            else
            {
                txt(i18n::s.get("core.locale.magic.dirty_water.other"));
            }
        }
        get_sick_if_cursed(efstatus, cdata[tc]);
        break;
    case 300:
        if (gdata_executing_immediate_quest_type == 1008
            || gdata_executing_immediate_quest_type == 1010)
        {
            txt(i18n::s.get("core.locale.magic.steal.in_quest"));
            return 0;
        }
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    break;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
        }
        invsubroutine = 1;
        invctrl(0) = 27;
        invctrl(1) = 0;
        snd(100);
        ctrl_inventory();
        break;
    case 301:
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    break;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
        }
        if (gdata_mount != 0)
        {
            if (tc == cc)
            {
                int stat = cell_findspace(
                    cdata.player().position.x, cdata.player().position.y, 1);
                if (stat == 0)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.mount.no_place_to_get_off"));
                    break;
                }
                cell_setchara(gdata_mount, rtval, rtval(1));
                txt(i18n::s.get(
                    "core.locale.magic.mount.dismount", cdata[gdata_mount]));
                txtef(9);
                txt(name(gdata_mount)
                    + i18n::s.get("core.locale.magic.mount.dismount_dialog"));
                ride_end();
                break;
            }
        }
        if (tc >= 16)
        {
            txt(i18n::s.get("core.locale.magic.mount.only_ally"));
            break;
        }
        if (cdata[tc].is_escorted() == 1
            || cdata[tc].is_escorted_in_sub_quest() == 1)
        {
            txt(i18n::s.get("core.locale.magic.mount.not_client"));
            break;
        }
        if (tc == cc)
        {
            if (gdata_mount == 0)
            {
                txt(i18n::s.get(
                    "core.locale.magic.mount.ride_self", cdata[cc]));
            }
            break;
        }
        if (cdata[tc].current_map != 0)
        {
            txt(i18n::s.get("core.locale.magic.mount.stays_in_area"));
            break;
        }
        if (gdata_mount != 0)
        {
            txt(i18n::s.get(
                "core.locale.magic.mount.currently_riding",
                cdata[cc],
                cdata[gdata_mount]));
        }
        else
        {
            ride_begin(tc);
            txtef(9);
            txt(name(gdata_mount)
                + i18n::s.get("core.locale.magic.mount.mount.dialog"));
        }
        break;
    case 183:
        if (cc != 0)
        {
            f = 0;
            for (const auto& cnt : items(cc))
            {
                if (inv[cnt].number() == 0)
                {
                    continue;
                }
                if (inv[cnt].skill == 183)
                {
                    ci = cnt;
                    f = 1;
                    break;
                }
            }
            if (f == 0)
            {
                return 0;
            }
        }
        if (sdata(183, cc) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.perform.do_not_know", cdata[cc]));
                return 0;
            }
        }
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    break;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
        }
        continuous_action_perform();
        break;
    case 184:
        if (sdata(184, 0) == 0)
        {
            txt(i18n::s.get("core.locale.magic.cook.do_not_know"));
            return 0;
        }
        cooktool = ci;
        invsubroutine = 1;
        invctrl = 16;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            if (!result.succeeded)
            {
                return 0;
            }
        }
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    break;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
        }
        cook();
        break;
    case 185:
        if (sdata(185, 0) == 0)
        {
            txt(i18n::s.get("core.locale.magic.fish.do_not_know"));
            return 0;
        }
        if (!inv_getspace(0))
        {
            txt(i18n::s.get("core.locale.ui.inv.common.inventory_is_full"));
            return 0;
        }
        if (inv[ci].count == 0)
        {
            txt(i18n::s.get("core.locale.magic.fish.need_bait"));
            return 0;
        }
        f = 0;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            y = cdata[cc].position.y + cnt - 1;
            x = cdata[cc].position.x;
            if (x < 0 || y < 0 || x >= mdata_map_width || y >= mdata_map_height)
            {
                continue;
            }
            if (chipm(0, map(x, y, 0)) == 3)
            {
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                y = cdata[cc].position.y;
                x = cdata[cc].position.x + cnt - 1;
                if (x < 0 || y < 0 || x >= mdata_map_width
                    || y >= mdata_map_height)
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
            ++msgdup;
            txt(i18n::s.get("core.locale.magic.fish.not_good_place"));
            update_screen();
            return 0;
        }
        if (chipm(
                0, map(cdata.player().position.x, cdata.player().position.y, 0))
            == 3)
        {
            txt(i18n::s.get("core.locale.magic.fish.cannot_during_swim"));
            update_screen();
            return 0;
        }
        if (cdata.player().position.x - x > 0)
        {
            cdata.player().direction = 1;
        }
        if (cdata.player().position.x - x < 0)
        {
            cdata.player().direction = 2;
        }
        if (cdata.player().position.y - y > 0)
        {
            cdata.player().direction = 3;
        }
        if (cdata.player().position.y - y < 0)
        {
            cdata.player().direction = 0;
        }
        gdata(35) = cdata.player().direction;
        fishx = x;
        fishy = y;
        addefmap(fishx, fishy, 1, 3);
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    break;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1)
                    + the_ability_db[efid]->cost / 2 + 1);
        }
        item_separate(ci);
        --inv[ci].count;
        rowactre = 0;
        spot_fishing();
        break;
    case 406:
    case 407:
        if (is_cursed(efstatus))
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.common.cursed", cdata[tc]));
            }
            goto label_2183_internal;
        }
        p = 0;
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            i = 16 - cnt - 1;
            if (efid == 406)
            {
                if (p >= 1)
                {
                    break;
                }
            }
            if (the_buff_db[cdata[tc].buffs[i].id]->type
                != buff_data::Type::hex)
            {
                continue;
            }
            if (cdata[tc].buffs[i].id == 13)
            {
                continue;
            }
            if (cdata[tc].buffs[i].id == 0)
            {
                continue;
            }
            if (rnd(efp * 2 + 1) > rnd(cdata[tc].buffs[i].power + 1))
            {
                buff_delete(cdata[tc], i);
                ++p;
                --cnt;
                continue;
            }
        }
        buff_add(cdata[tc], 10, efp, 5 + efp / 30, cdata[cc]);
        animeload(11, tc);
        break;
    case 1120:
        txtef(5);
        txt(i18n::s.get("core.locale.magic.prayer", cdata[tc]));
        heal_completely();
        bright_aura_animation(
            cdata[tc].position, bright_aura_animation::Type::healing)
            .play();
        break;
    case 1117:
        if (tc >= 16)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (!is_cursed(efstatus))
        {
            s = i18n::s.get("core.locale.magic.create_material.materials");
        }
        else
        {
            s = i18n::s.get("core.locale.magic.create_material.junks");
        }
        snd(24);
        txt(i18n::s.get("core.locale.magic.create_material.apply", s(0)));
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        for (int cnt = 0,
                 cnt_end =
                     (rnd(3) + 3 + (efstatus == CurseState::blessed) * 6);
             cnt < cnt_end;
             ++cnt)
        {
            atxspot = 19;
            if (!is_cursed(efstatus))
            {
                p = random_material(efp / 10, efp / 50);
            }
            else
            {
                p = 0;
            }
            matgetmain(p, 1);
        }
        break;
    case 632:
    case 454:
    case 1144:
        if (tc != 0)
        {
            goto label_2184_internal;
        }
        if (efid == 632)
        {
            txt(i18n::s.get(
                "core.locale.magic.mutation.spell", cdata[cc], cdata[tc]));
            if (rnd(3))
            {
                break;
            }
        }
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
        }
        if (encfind(tc, 33) != -1)
        {
            if (rnd(5))
            {
                txt(i18n::s.get("core.locale.magic.mutation.resist"));
                break;
            }
        }
    label_2182_internal:
        f = 0;
        p = 1;
        if (efid == 1144)
        {
            p = 2 + rnd(3);
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            for (int cnt = 0; cnt < 100; ++cnt)
            {
                int tid = rnd(45);
                int stat = trait_get_info(0, tid);
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
                if (is_cursed(efstatus))
                {
                    if (p == 1)
                    {
                        continue;
                    }
                }
                else if (p == -1)
                {
                    if (efstatus == CurseState::blessed)
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
                txt(i18n::s.get("core.locale.magic.mutation.apply"));
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
        if (f == 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        chara_refresh(0);
        break;
    case 1121:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
        }
        if (is_cursed(efstatus))
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.common.it_is_cursed"));
            }
            goto label_2182_internal;
        }
        f = 0;
        for (int cnt = 0,
                 cnt_end = cnt
                 + (1 + (efstatus == CurseState::blessed)
                    + (!is_cursed(efstatus)) + rnd(2));
             cnt < cnt_end;
             ++cnt)
        {
            for (int cnt = 0; cnt < 100; ++cnt)
            {
                int tid = rnd(217);
                int stat = trait_get_info(0, tid);
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
                txt(i18n::s.get("core.locale.magic.cure_mutation"));
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
        if (f == 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        chara_refresh(0);
        break;
    case 411:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl = 13;
        snd(100);
        ctrl_inventory();
        break;
    case 461:
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (is_cursed(efstatus))
        {
            txt(i18n::s.get("core.locale.magic.resurrection.cursed"));
            for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata.player().level), calcfixlv(3));
                fltn(u8"undead"s);
                chara_create(
                    -1,
                    0,
                    cdata.player().position.x,
                    cdata.player().position.y);
            }
            obvious = 0;
            break;
        }
        {
            int stat = show_hire_menu(HireOperation::revive);
            if (stat == -1)
            {
                txt(i18n::s.get("core.locale.common.nothing_happens"));
                obvious = 0;
                break;
            }
            if (bonus < rnd(100))
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.locale.magic.resurrection.fail", cdata[cc]));
                }
                break;
            }
            rc = stat;
        }
        do_chara_revival();
        cxinit = cdata[cc].position.x;
        cyinit = cdata[cc].position.y;
        chara_place();
        cdata[rc].current_map = 0;
        txtef(5);
        txt(i18n::s.get(
            "core.locale.magic.resurrection.apply",
            cnven(cdatan(0, rc)),
            cdata[rc]));
        txt(i18n::s.get("core.locale.magic.resurrection.dialog"));
        animode = 100 + rc;
        miracle_animation().play();
        snd(120);
        cdata[rc].emotion_icon = 317;
        if (cc == 0)
        {
            chara_modify_impression(cdata[rc], 15);
            if (rc >= 16)
            {
                modify_karma(cdata.player(), 2);
            }
        }
        break;
    case 412:
        if (efstatus == CurseState::none)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.uncurse.apply", cdata[tc]));
            }
        }
        if (efstatus == CurseState::blessed)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.uncurse.blessed", cdata[tc]));
            }
        }
        if (is_cursed(efstatus))
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.common.cursed", cdata[tc]));
            }
            goto label_2183_internal;
        }
        p(1) = 0;
        p(2) = 0;
        for (const auto& cnt : items(tc))
        {
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (!is_cursed(inv[cnt].curse_state))
            {
                continue;
            }
            ci = cnt;
            p = 0;
            if (inv[ci].curse_state == CurseState::cursed)
            {
                p = rnd(200) + 1;
            }
            if (inv[ci].curse_state == CurseState::doomed)
            {
                p = rnd(1000) + 1;
            }
            if (efstatus == CurseState::blessed)
            {
                p = p / 2 + 1;
            }
            else if (inv[ci].body_part == 0)
            {
                continue;
            }
            if (p != 0)
            {
                if (efp >= p)
                {
                    ++p(1);
                    inv[ci].curse_state = CurseState::none;
                    item_stack(tc, ci, 1);
                }
                else
                {
                    ++p(2);
                }
            }
        }
        if (efstatus == CurseState::blessed)
        {
            if (p(1) != 0)
            {
                if (is_in_fov(cdata[tc]))
                {
                    txt(i18n::s.get(
                        "core.locale.magic.uncurse.item", cdata[tc]));
                }
            }
        }
        else if (p(1) != 0)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.uncurse.equipment", cdata[tc]));
            }
        }
        if (p(2) != 0)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.uncurse.resist"));
            }
        }
        if (p(1) == 0 && p(2) == 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        else
        {
            animeload(10, tc);
        }
        chara_refresh(tc);
        break;
    case 413:
        if (tc >= 16)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
        }
        if (is_cursed(efstatus))
        {
            artifactlocation.clear();
            txt(i18n::s.get("core.locale.magic.oracle.cursed"));
            break;
        }
        if (artifactlocation.empty())
        {
            txt(i18n::s.get("core.locale.magic.oracle.no_artifacts"));
        }
        else
        {
            range::for_each(
                artifactlocation, [](const auto& line) { txt(cnven(line)); });
            artifactlocation.clear();
        }
        break;
    case 1104:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        f = 0;
        for (int cnt = 0, cnt_end = (1 + (efstatus == CurseState::blessed));
             cnt < cnt_end;
             ++cnt)
        {
            int cnt2 = cnt;
            for (int cnt = 0; cnt < 2000; ++cnt)
            {
                p = rnd(67) + 400;
                if (p == 441)
                {
                    if (rnd(10))
                    {
                        continue;
                    }
                }
                if (!is_cursed(efstatus))
                {
                    if (the_ability_db[p])
                    {
                        if (cnt2 == 0)
                        {
                            s = i18n::s.get(
                                "core.locale.magic.gain_knowledge.suddenly");
                        }
                        else
                        {
                            s = i18n::s.get(
                                "core.locale.magic.gain_knowledge.furthermore");
                        }
                        chara_gain_skill(cdata.player(), p, 1, 200);
                        txtef(2);
                        txt(s
                            + i18n::s.get(
                                  "core.locale.magic.gain_knowledge.gain",
                                  i18n::_(
                                      u8"ability",
                                      std::to_string(p),
                                      u8"name")));
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
                        txt(i18n::s.get(
                            "core.locale.magic.common.it_is_cursed"));
                        txtef(3);
                        txt(i18n::s.get(
                            "core.locale.magic.gain_knowledge.lose",
                            i18n::_(
                                u8"ability",
                                std::to_string(p + 400),
                                u8"name")));
                        snd(117);
                        animeload(14, 0);
                        f = 1;
                        break;
                    }
                }
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        break;
    case 1143:
        if (efstatus == CurseState::blessed)
        {
            cdata[tc].experience = cdata[tc].required_experience;
            r2 = 0;
            gain_level(cdata[tc]);
            if (is_in_fov(cdata[tc]))
            {
                snd(60);
            }
        }
        else
        {
            if (cdata[tc].level <= 1)
            {
                txt(i18n::s.get("core.locale.common.nothing_happens"));
                obvious = 0;
                break;
            }
            --cdata[tc].level;
            cdata[tc].experience = 0;
            update_required_experience(cdata[tc]);
            txtef(8);
            txt(i18n::s.get("core.locale.magic.descent", cdata[tc]));
        }
        if (is_cursed(efstatus))
        {
            txt(i18n::s.get("core.locale.magic.common.it_is_cursed"));
            for (int cnt = 10; cnt < 50; ++cnt)
            {
                if (rnd(3) == 0)
                {
                    if (cnt <= 17)
                    {
                        if (sdata(cnt, tc) != 0)
                        {
                            chara_gain_skill_exp(cdata[tc], cnt, -1000);
                        }
                    }
                }
            }
            animeload(8, tc);
        }
        chara_refresh(tc);
        break;
    case 1105:
        for (int cnt = 0;; ++cnt)
        {
            p = rnd(300) + 100;
            if (the_ability_db[p])
            {
                if (!is_cursed(efstatus))
                {
                    if (cnt < efstatusfix(0, 0, 100, 2000))
                    {
                        if (sdata(p, tc) != 0)
                        {
                            continue;
                        }
                    }
                    chara_gain_skill(cdata[tc], p, 1);
                    if (is_in_fov(cdata[tc]))
                    {
                        snd(24);
                        txtef(2);
                        txt(i18n::s.get(
                            "core.locale.magic.gain_skill",
                            cdata[tc],
                            i18n::_(u8"ability", std::to_string(p), u8"name")));
                    }
                    break;
                }
                else
                {
                    if (sdata(p, tc) == 0)
                    {
                        continue;
                    }
                    if (is_in_fov(cdata[tc]))
                    {
                        snd(38);
                        txt(i18n::s.get(
                            "core.locale.magic.common.it_is_cursed"));
                    }
                    chara_gain_skill_exp(cdata[tc], p, -1000);
                    break;
                }
            }
        }
        chara_refresh(tc);
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        break;
    case 1107:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (cdata.player().god_id.empty())
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (is_cursed(efstatus))
        {
            txt(i18n::s.get("core.locale.magic.faith.doubt"));
            snd(117);
            animeload(14, 0);
            chara_gain_skill_exp(cdata.player(), 181, -1000);
            break;
        }
        if (cdata.player().god_id.empty())
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        else
        {
            txtef(2);
            txt(i18n::s.get(
                "core.locale.magic.faith.apply",
                i18n::_(u8"god", cdata.player().god_id, u8"name")));
            if (efstatus == CurseState::blessed)
            {
                txt(i18n::s.get("core.locale.magic.faith.blessed"));
            }
            animode = 100 + tc;
            miracle_animation().play();
            snd(120);
            cdata.player().praying_point += 500;
            modpiety(75);
            chara_gain_skill_exp(
                cdata.player(),
                181,
                1000 + (efstatus == CurseState::blessed) * 750,
                6,
                1000);
        }
        chara_refresh(tc);
        break;
    case 1119:
        for (int cnt = 0, cnt_end = (1 + (efstatus == CurseState::blessed));
             cnt < cnt_end;
             ++cnt)
        {
            int cnt2 = cnt;
            while (1)
            {
                p = rnd(300) + 100;
                if (the_ability_db[p])
                {
                    if (sdata.get(p, tc).original_level == 0)
                    {
                        continue;
                    }
                    modify_potential(
                        cdata[tc], p, efp * efstatusfix(-4, -2, 5, 5) / 100);
                    if (cnt2 == 0)
                    {
                        s = i18n::s.get(
                            "core.locale.magic.gain_skill_potential.the");
                    }
                    else
                    {
                        s = i18n::s.get(
                            "core.locale.magic.gain_skill_potential."
                            "furthermore_the");
                    }
                    if (!is_cursed(efstatus))
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            snd(24);
                            txtef(2);
                            txt(s
                                + i18n::s.get(
                                      "core.locale.magic.gain_skill_potential."
                                      "increases",
                                      cdata[tc],
                                      i18n::_(
                                          u8"ability",
                                          std::to_string(p),
                                          u8"name")));
                        }
                    }
                    else if (is_in_fov(cdata[tc]))
                    {
                        snd(117);
                        txtef(3);
                        txt(i18n::s.get(
                            "core.locale.magic.gain_skill_potential.decreases",
                            cdata[tc],
                            i18n::_(u8"ability", std::to_string(p), u8"name")));
                    }
                    break;
                }
            }
        }
        chara_refresh(tc);
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        break;
    case 1106:
        i = rnd(10) + 10;
        chara_gain_skill_exp(
            cdata[tc], i, efstatusfix(-2000, -2000, -1000, -250));
        bright_aura_animation(
            cdata[tc].position, bright_aura_animation::Type::debuff)
            .play();
        chara_refresh(tc);
        break;
    case 1139:
        txt(i18n::s.get("core.locale.magic.troll_blood.apply", cdata[tc]));
        chara_gain_skill_exp(
            cdata[tc], 18, efstatusfix(-4000, -1000, 8000, 12000));
        if (efstatus == CurseState::blessed)
        {
            modify_potential(cdata[tc], 18, 15);
            txtef(2);
            txt(i18n::s.get("core.locale.magic.troll_blood.blessed"));
        }
        chara_refresh(tc);
        break;
    case 1113:
        if (efstatus == CurseState::blessed)
        {
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                modify_potential(
                    cdata[tc],
                    cnt,
                    rnd(sdata.get(cnt, tc).potential / 20 + 3) + 1);
            }
            txt(i18n::s.get(
                "core.locale.magic.gain_potential.blessed", cdata[tc]));
            animode = 100 + tc;
            miracle_animation().play();
            snd(61);
        }
        else
        {
            i = rnd(8) + 10;
            const auto valn = i18n::_(u8"ability", std::to_string(i), u8"name");
            if (efstatus == CurseState::none)
            {
                txt(i18n::s.get(
                    "core.locale.magic.gain_potential.increases",
                    cdata[tc],
                    valn));
                modify_potential(
                    cdata[tc],
                    i,
                    rnd(sdata.get(i, tc).potential / 10 + 10) + 1);
                snd(24);
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.magic.gain_potential.decreases",
                    cdata[tc],
                    valn));
                modify_potential(
                    cdata[tc],
                    i,
                    (rnd(sdata.get(i, tc).potential / 10 + 10) + 1) * -1);
                snd(117);
            }
        }
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        break;
    case 653:
        if (tc < 57)
        {
            break;
        }
        if (cdata[tc].quality >= 4)
        {
            break;
        }
        txt(i18n::s.get("core.locale.magic.vanish", cdata[tc]));
        chara_vanquish(tc);
        break;
    case 430:
    case 429:
        if (tc >= 16)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        p = 1;
        if (efid == 430)
        {
            p = 2;
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end;
                 ++cnt)
            {
                y = cnt;
                for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end;
                     ++cnt)
                {
                    x = cnt;
                    p = dist(cdata[tc].position.x, cdata[tc].position.y, x, y);
                    if (is_cursed(efstatus))
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
                        || efstatus == CurseState::blessed)
                    {
                        if (efid == 429)
                        {
                            map(x, y, 2) = map(x, y, 0);
                        }
                        if (efid == 430)
                        {
                            if (map(x, y, 6) != 0 || map(x, y, 5) != 0)
                            {
                                map(x, y, 2) = map(x, y, 0);
                            }
                        }
                    }
                }
            }
        }
        if (is_cursed(efstatus))
        {
            txt(i18n::s.get("core.locale.magic.sense.cursed"));
        }
        else
        {
            if (efid == 429)
            {
                txt(i18n::s.get(
                    "core.locale.magic.sense.magic_mapping", cdata[tc]));
            }
            if (efid == 430)
            {
                txt(i18n::s.get(
                    "core.locale.magic.sense.sense_object", cdata[tc]));
            }
        }
        animeload(10, tc);
        update_minimap();
        update_screen();
        break;
    case 658:
        if (cdata[tc].hp > cdata[tc].max_hp / 8)
        {
            break;
        }
        if (is_in_fov(cdata[tc]))
        {
            snd(105);
            txtef(3);
            txt(i18n::s.get("core.locale.magic.vorpal.sound"));
            if (tc >= 16)
            {
                gdata(809) = 2;
                txt3rd = 1;
                txt(i18n::s.get(
                    "core.locale.magic.vorpal.other", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.magic.vorpal.ally", cdata[cc], cdata[tc]));
            }
        }
        damage_hp(cdata[tc], cdata[tc].max_hp, cc, 658);
        break;
    case 440:
    case 439:
        if (efid == 439)
        {
            if (is_in_fov(cdata[tc]))
            {
                if (is_cursed(efstatus))
                {
                    snd(117);
                    txt(i18n::s.get(
                        "core.locale.magic.restore.body.cursed", cdata[tc]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.locale.magic.restore.body.apply", cdata[tc]));
                    animeload(10, tc);
                }
                if (efstatus == CurseState::blessed)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.restore.body.blessed", cdata[tc]));
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
            if (is_in_fov(cdata[tc]))
            {
                if (is_cursed(efstatus))
                {
                    snd(117);
                    txt(i18n::s.get(
                        "core.locale.magic.restore.mind.cursed", cdata[tc]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.locale.magic.restore.mind.apply", cdata[tc]));
                    animeload(10, tc);
                }
                if (efstatus == CurseState::blessed)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.restore.mind.blessed", cdata[tc]));
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
        for (int cnt = 0;; ++cnt)
        {
            if (p(cnt) == -1)
            {
                break;
            }
            const auto attr = p(cnt) - 10;
            if (is_cursed(efstatus))
            {
                if (cdata[tc].quality <= 3)
                {
                    cdata[tc].attr_adjs[attr] -=
                        rnd(sdata.get(p(cnt), tc).original_level) / 5 + rnd(5);
                    continue;
                }
            }
            if (cdata[tc].attr_adjs[attr] < 0)
            {
                cdata[tc].attr_adjs[attr] = 0;
            }
            if (efstatus == CurseState::blessed)
            {
                cdata[tc].attr_adjs[attr] =
                    sdata.get(p(cnt), tc).original_level / 10 + 5;
            }
        }
        chara_refresh(tc);
        break;
    case 441:
        what_do_you_wish_for();
        screenupdate = -1;
        gmode(2);
        update_screen();
        break;
    case 1141:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (gdata_is_returning_or_escaping != 0)
        {
            txt(i18n::s.get("core.locale.magic.escape.cancel"));
            gdata_is_returning_or_escaping = 0;
        }
        else
        {
            int stat = quest_is_return_forbidden();
            if (stat == 1)
            {
                txt(i18n::s.get("core.locale.magic.escape.during_quest"));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    break;
                }
            }
            txt(i18n::s.get("core.locale.magic.escape.begin"));
            if (adata(16, gdata_current_map)
                == mdata_t::MapId::random_dungeon)
            {
                if (gdata_current_dungeon_level == adata(10, gdata_current_map))
                {
                    if (adata(20, gdata_current_map) != -1)
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.escape.lord_may_disappear"));
                    }
                }
            }
            gdata_destination_map = gdata(850);
            gdata_destination_dungeon_level = 1;
            if (is_cursed(efstatus))
            {
                if (rnd(3) == 0)
                {
                    gdata_destination_map = 41;
                    gdata_destination_dungeon_level = 1;
                }
            }
            gdata_is_returning_or_escaping = 5 + rnd(10);
        }
        break;
    case 428:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (gdata_is_returning_or_escaping != 0)
        {
            txt(i18n::s.get("core.locale.magic.return.cancel"));
            gdata_is_returning_or_escaping = 0;
        }
        else
        {
            try_to_return();
            if (is_cursed(efstatus))
            {
                if (rnd(3) == 0)
                {
                    gdata_destination_map = 41;
                    gdata_destination_dungeon_level = 1;
                }
            }
        }
        break;
    case 621:
        heal_mp(cdata[tc], efp / 2 + rnd((efp / 2 + 1)));
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.harvest_mana", cdata[tc]));
            bright_aura_animation(
                cdata[tc].position, bright_aura_animation::Type::healing)
                .play();
        }
        break;
    case 624:
        heal_mp(cdata[tc], roll(dice1, dice2, bonus));
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.absorb_magic", cdata[tc]));
            bright_aura_animation(
                cdata[tc].position, bright_aura_animation::Type::healing)
                .play();
        }
        break;
    case 1108:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.poison_attack", cdata[tc]));
        }
        if (cdata[tc].is_pregnant())
        {
            cdata[tc].is_pregnant() = false;
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.common.melts_alien_children",
                    cdata[tc]));
            }
        }
        dmgcon(tc, StatusAilment::poisoned, efp);
        break;
    case 1111:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.ink_attack", cdata[tc]));
        }
        dmgcon(tc, StatusAilment::blinded, efp);
        break;
    case 1109:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.confusion", cdata[tc]));
        }
        dmgcon(tc, StatusAilment::confused, efp);
        break;
    case 1110:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.paralysis", cdata[tc]));
        }
        dmgcon(tc, StatusAilment::paralyzed, efp);
        break;
    case 1112:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.sleep", cdata[tc]));
        }
        dmgcon(tc, StatusAilment::sleep, efp);
        break;
    case 645:
    case 1114:
    label_2183_internal:
        if (efid == 645)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.curse.spell", cdata[cc], cdata[tc]));
            }
        }
        p = 75 + sdata(19, tc);
        if (encfind(tc, 43) != -1)
        {
            p += encfind(tc, 43) / 2;
        }
        if (rnd(p) > efp / 2 + (is_cursed(efstatus)) * 100)
        {
            break;
        }
        if (tc < 16)
        {
            if (rnd(3))
            {
                if (trait(42))
                {
                    txt(i18n::s.get("core.locale.magic.curse.no_effect"));
                    break;
                }
            }
        }
        i = 0;
        for (int cnt = 0; cnt < 30; ++cnt)
        {
            if (cdata[tc].body_parts[cnt] % 10000 == 0)
            {
                continue;
            }
            p(i) = cdata[tc].body_parts[cnt] % 10000 - 1;
            if (inv[p(i)].curse_state == CurseState::blessed)
            {
                if (rnd(10))
                {
                    continue;
                }
            }
            ++i;
        }
        if (i == 0)
        {
            for (int cnt = 0; cnt < 200; ++cnt)
            {
                p = get_random_inv(tc);
                if (inv[p].number() == 0)
                {
                    continue;
                }
                if (inv[p].curse_state == CurseState::blessed)
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
        if (i > 0)
        {
            i = p(rnd(i));
            const auto valn = itemname(i, 1, 1);
            if (inv[i].curse_state == CurseState::cursed)
            {
                inv[i].curse_state = CurseState::doomed;
            }
            else
            {
                inv[i].curse_state = CurseState::cursed;
            }
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.curse.apply", cdata[tc], valn));
            }
            chara_refresh(tc);
            snd(117);
            animeload(14, tc);
            item_stack(tc, i, 1);
        }
        else
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        break;
    case 1118:
        f = 0;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            p = rnd(11) + 50;
            if (sdata.get(p, tc).original_level >= 150)
            {
                ++f;
                resistmod(tc, p, 50 * -1);
                if (f >= efp / 100)
                {
                    break;
                }
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get(
                "core.locale.magic.weaken_resistance.nothing_happens"));
            obvious = 0;
        }
        else
        {
            snd(38);
        }
        chara_refresh(tc);
        break;
    case 1138:
    case 1123:
    case 1122:
    case 1137:
        if (cc != 0 && cc < 16)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
        }
        flt(cdata.player().level / 2 + 5, 3);
        p = 0;
        if (rnd(3) == 0)
        {
            fltn(u8"man"s);
        }
        if (efid == 1138)
        {
            txt(i18n::s.get("core.locale.magic.diary.cat_sister"));
            p = 210;
        }
        if (efid == 1123)
        {
            txt(i18n::s.get("core.locale.magic.diary.younger_sister"));
            p = 176;
        }
        if (efid == 1137)
        {
            txt(i18n::s.get("core.locale.magic.diary.young_lady"));
            p = 211;
        }
        novoidlv = 1;
        chara_create(56, p, -3, 0);
        rc = 56;
        new_ally_joins();
        break;
    case 435:
        if (cc != 0 || tc == 0 || cdata[tc].relationship == 10)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (gdata_current_map == mdata_t::MapId::arena
            || gdata_current_map == mdata_t::MapId::pet_arena
            || gdata_current_map == mdata_t::MapId::the_void)
        {
            obvious = 0;
            txt(i18n::s.get(
                "core.locale.magic.domination.does_not_work_in_area"));
            break;
        }
        f = 1;
        {
            int stat = inv_find(663, cc);
            if (stat != -1)
            {
                efp = efp * 3 / 2;
            }
        }
        if (rnd(efp / 15 + 5) < cdata[tc].level)
        {
            f = 0;
        }
        if (cdata[tc].quality >= 4 || cdata[tc].character_role != 0
            || cdata[tc].is_lord_of_dungeon() == 1)
        {
            f = -1;
        }
        if (f == 1)
        {
            rc = tc;
            new_ally_joins();
            quest_check();
        }
        else if (f == 0)
        {
            txt(i18n::s.get("core.locale.magic.common.resists", cdata[tc]));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.magic.domination.cannot_be_charmed", cdata[tc]));
        }
        break;
    case 436:
    case 437:
    case 455:
    case 634:
    case 456:
        if (efid == 436)
        {
            p(0) = 3;
            p(1) = 2 + rnd((efp / 50 + 1));
            txt(i18n::s.get("core.locale.magic.map_effect.web"));
        }
        if (efid == 437)
        {
            txt(i18n::s.get("core.locale.magic.map_effect.fog"));
            p(0) = 3;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 455)
        {
            txt(i18n::s.get("core.locale.magic.map_effect.acid"));
            p(0) = 2;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 456)
        {
            txt(i18n::s.get("core.locale.magic.map_effect.fire"));
            p(0) = 2;
            p(1) = 2 + rnd((efp / 50 + 1));
        }
        if (efid == 634)
        {
            txt(i18n::s.get("core.locale.magic.map_effect.ether_mist"));
            p(0) = 2;
            p(1) = 1 + rnd((efp / 100 + 2));
        }
        snd(68);
        for (int cnt = 0, cnt_end = (p(1)); cnt < cnt_end; ++cnt)
        {
            x = rnd(p) + tlocx - rnd(p);
            y = rnd(p) + tlocy - rnd(p);
            f = 1;
            if (x < 0 || y < 0 || x >= mdata_map_width || y >= mdata_map_height)
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
                mef_add(x, y, 4, 20, rnd(4) + 2, efp, cc);
            }
            if (efid == 455)
            {
                mef_add(x, y, 3, 19, rnd(10) + 5, efp, cc);
            }
            if (efid == 456)
            {
                mef_add(x, y, 5, 24, rnd(10) + 5, efp, cc);
                mapitem_fire(x, y);
            }
            if (efid == 436)
            {
                mef_add(x, y, 1, 11, -1, efp * 2);
            }
            if (efid == 437)
            {
                mef_add(x, y, 2, 30, 8 + rnd((15 + efp / 25)), efp);
            }
        }
        break;
    case 1145:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 0;
        snd(100);
        ctrl_inventory();
        if (inv[ci].quality < 4 || inv[ci].quality == 6)
        {
            txt(i18n::s.get("core.locale.common.it_is_impossible"));
            obvious = 0;
            break;
        }
        txt(i18n::s.get("core.locale.magic.name.prompt"));
        {
            int stat = select_alias(3);
            if (stat == 0)
            {
                obvious = 0;
                randomize();
                break;
            }
            p = stat;
        }
        inv[ci].subname = list(1, p) + 40000;
        randomize();
        txt(i18n::s.get("core.locale.magic.name.apply", listn(0, p)));
        break;
    case 49:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 7;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            if (!result.succeeded)
            {
                break;
            }
        }
        if (inv[ci].quality >= 4 || ibit(10, ci) == 1)
        {
            txt(i18n::s.get("core.locale.magic.garoks_hammer.no_effect"));
            fixmaterial = 0;
            objfix = 0;
            break;
        }
        randomize(inv[efcibk].param1);
        equip = inv[ci].body_part;
        animeload(8, cc);
        inv[ci].quality = 4;
        fixmaterial = inv[ci].material;
        change_item_material();
        randomize(inv[efcibk].param1);
        inv[ci].subname = 40000 + rnd(30000);
        p = rnd(rnd(rnd(10) + 1) + 3) + 3;
        egolv = rnd(clamp(rnd(6), 0, 4) + 1);
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            randomize(inv[efcibk].param1);
            enchantment_add(
                ci,
                enchantment_generate(enchantment_gen_level(egolv)),
                enchantment_gen_p() + (fixlv == 5) * 100
                    + (ibit(15, ci) == 1) * 100,
                20 - (fixlv == 5) * 10 - (ibit(15, ci) == 1) * 20);
        }
        randomize();
        txt(i18n::s.get("core.locale.magic.garoks_hammer.apply", inv[ci]));
        if (equip != 0)
        {
            cdata[cc].body_parts[equip - 100] =
                cdata[cc].body_parts[equip - 100] / 10000 * 10000 + ci + 1;
            inv[ci].body_part = equip;
        }
        chara_refresh(cc);
        fixmaterial = 0;
        objfix = 0;
        ci = efcibk;
        inv[ci].modify_number(-1);
        autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
        break;
    case 21:
    case 1127:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 0;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            f = result.succeeded ? 1 : 0;
        }
        if (inv[ci].quality == 5 || ibit(10, ci) == 1)
        {
            if (efid == 1127)
            {
                f = 0;
            }
        }
        equip = inv[ci].body_part;
        if (f == 1)
        {
            if (inv[ci].quality == 6)
            {
                if (efp < 350)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.change_material.more_power_needed"));
                    break;
                }
                animeload(8, cc);
                txt(i18n::s.get(
                    "core.locale.magic.change_material.artifact_reconstructed",
                    cdata[cc],
                    inv[ci]));
                inv[ci].modify_number(-1);
                flt();
                itemcreate(0, inv[ci].id, -1, -1, 0);
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
                change_item_material();
                txt(i18n::s.get(
                    "core.locale.magic.change_material.apply",
                    cdata[cc],
                    s(0),
                    inv[ci]));
            }
        }
        else
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        if (equip != 0)
        {
            cdata[cc].body_parts[equip - 100] =
                cdata[cc].body_parts[equip - 100] / 10000 * 10000 + ci + 1;
            inv[ci].body_part = equip;
        }
        chara_refresh(cc);
        fixmaterial = 0;
        objfix = 0;
        break;
    case 1128:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        snd(24);
        p = rnd((efp + 1)) / 100 + 1;
        gdata_rights_to_succeed_to += p;
        txtef(5);
        txt(i18n::s.get("core.locale.magic.deed_of_inheritance.claim", p(0)));
        txt(i18n::s.get(
            "core.locale.magic.deed_of_inheritance.can_now_inherit",
            gdata_rights_to_succeed_to));
        break;
    case 1124:
    case 1125:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
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
            menu_result result = ctrl_inventory();
            if (result.succeeded)
            {
                if (inv[ci].enhancement < efp / 100)
                {
                    snd(24);
                    txt(i18n::s.get(
                        "core.locale.magic.enchant.apply", inv[ci]));
                    ++inv[ci].enhancement;
                }
                else
                {
                    txt(i18n::s.get(
                        "core.locale.magic.enchant.resist", inv[ci]));
                }
                chara_refresh(cc);
            }
            else
            {
                obvious = 0;
            }
        }
        break;
    case 630:
    case 1129:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        if (efid == 630)
        {
            if (gdata_charge_power < 10)
            {
                txt(i18n::s.get(
                    "core.locale.magic.fill_charge.more_power_needed"));
                break;
            }
            gdata_charge_power -= 10;
            txt(i18n::s.get(
                "core.locale.magic.fill_charge.spend", gdata_charge_power));
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 3;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            if (result.succeeded)
            {
                dbid = inv[ci].id;
                access_item_db(2);
                if (ichargelevel < 1 || inv[ci].id == 290 || inv[ci].id == 480
                    || inv[ci].id == 289 || inv[ci].id == 732
                    || (inv[ci].id == 687 && inv[ci].param2 != 0))
                {
                    txt(i18n::s.get(
                        "core.locale.magic.fill_charge.cannot_recharge"));
                    break;
                }
                f = 1;
                if (inv[ci].count > ichargelevel)
                {
                    f = -1;
                }
                if (f == -1)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.fill_charge.cannot_recharge_anymore",
                        inv[ci]));
                    break;
                }
                if (rnd(efp / 25 + 1) == 0)
                {
                    f = 0;
                }
                if (the_item_db[inv[ci].id]->category == 54000)
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
                    if (p + inv[ci].count > ichargelevel)
                    {
                        p = ichargelevel - inv[ci].count + 1;
                    }
                    if (the_item_db[inv[ci].id]->category == 54000)
                    {
                        p = 1;
                    }
                    txt(i18n::s.get(
                        "core.locale.magic.fill_charge.apply", inv[ci], p(0)));
                    inv[ci].count += p;
                    animeload(8, cc);
                }
                else
                {
                    if (rnd(4) == 0)
                    {
                        txt(i18n::s.get(
                            "core.locale.magic.fill_charge.explodes", inv[ci]));
                        inv[ci].modify_number(-1);
                        refresh_burden_state();
                        break;
                    }
                    txt(i18n::s.get(
                        "core.locale.magic.fill_charge.fail", inv[ci]));
                }
            }
            else
            {
                obvious = 0;
            }
        }
        break;
    case 629:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 5;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            if (result.succeeded)
            {
                dbid = inv[ci].id;
                access_item_db(2);
                for (int cnt = 0; cnt < 1; ++cnt)
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
                animeload(8, cc);
                p = p * inv[ci].count;
                gdata_charge_power += p;
                txt(i18n::s.get(
                    "core.locale.magic.draw_charge",
                    inv[ci],
                    p(0),
                    gdata_charge_power));
                inv[ci].remove();
                refresh_burden_state();
            }
        }
        break;
    case 628:
    label_2184_internal:
        if (tc == 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        f = 1;
        if (efp / 10 + 10 < cdata[tc].level)
        {
            f = 0;
        }
        if (cdata[tc].quality >= 4 || cdata[tc].character_role != 0
            || cdata[tc].is_escorted() == 1
            || cdata[tc].is_lord_of_dungeon() == 1)
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
            txt(i18n::s.get("core.locale.magic.change.apply", cdata[tc]));
            flt(calcobjlv(cdata[tc].level + 3), 2);
            chara_create(56, 0, -3, 0);
            chara_relocate(cdata.tmp(), tc(0), CharaRelocationMode::change);
            cdata[tc].enemy_id = cc;
            cdata[tc].is_quest_target() = false;
            quest_check();
        }
        else if (f == 0)
        {
            txt(i18n::s.get("core.locale.magic.common.resists", cdata[tc]));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.magic.change.cannot_be_changed", cdata[tc]));
        }
        break;
    case 1140:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 6;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            if (result.succeeded)
            {
                autosave =
                    1 * (gdata_current_map != mdata_t::MapId::show_house);
                animeload(8, cc);
                if (!is_cursed(efstatus))
                {
                    if (inv[ci].weight > 0)
                    {
                        inv[ci].weight = clamp(
                            inv[ci].weight * (100 - efp / 10) / 100,
                            1,
                            inv[ci].weight);
                        if (inv[ci].pv > 0)
                        {
                            inv[ci].pv -= inv[ci].pv / 10 + 1
                                + (efstatus != CurseState::blessed);
                        }
                        if (inv[ci].damage_bonus > 0)
                        {
                            inv[ci].damage_bonus -= inv[ci].damage_bonus / 10
                                + 1 + (efstatus != CurseState::blessed);
                        }
                    }
                    txt(i18n::s.get("core.locale.magic.flying.apply", inv[ci]));
                }
                else
                {
                    inv[ci].weight = inv[ci].weight * 150 / 100 + 1000;
                    if (inv[ci].pv > 0)
                    {
                        inv[ci].pv += clamp(inv[ci].pv / 10, 1, 5);
                    }
                    if (inv[ci].damage_bonus > 0)
                    {
                        inv[ci].damage_bonus +=
                            clamp(inv[ci].damage_bonus / 10, 1, 5);
                    }
                    txt(i18n::s.get(
                        "core.locale.magic.flying.cursed", inv[ci]));
                }
                refresh_burden_state();
            }
            else
            {
                txt(i18n::s.get("core.locale.common.nothing_happens"));
                obvious = 0;
            }
        }
        chara_refresh(cc);
        break;
    case 1132:
        if (cc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
            break;
        }
        invsubroutine = 1;
        invctrl(0) = 23;
        invctrl(1) = 4;
        snd(100);
        {
            menu_result result = ctrl_inventory();
            f = result.succeeded ? 1 : 0;
        }
        if (f)
        {
            if (inv[ci].quality > 4 || ibit(5, ci) == 1)
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
            animeload(8, cc);
            fltbk = the_item_db[inv[ci].id]->category;
            valuebk = calcitemvalue(ci, 0);
            inv[ci].remove();
            for (int cnt = 0;; ++cnt)
            {
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
                if (inv[ci].value > valuebk * 3 / 2 + 1000)
                {
                    inv[ci].remove();
                    continue;
                }
                else
                {
                    break;
                }
            }
            txt(i18n::s.get("core.locale.magic.alchemy", inv[ci]));
            refresh_burden_state();
        }
        else
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            obvious = 0;
        }
        break;
    case 457:
    case 438:
        x = tlocx;
        y = tlocy;
        f = 1;
        if (x < 0 || y < 0 || x >= mdata_map_width || y >= mdata_map_height)
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
                    txt(i18n::s.get("core.locale.magic.create.wall"));
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
                    txt(i18n::s.get("core.locale.magic.create.door.resist"));
                    break;
                }
                txt(i18n::s.get("core.locale.magic.create.door.apply"));
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
                txt(i18n::s.get("core.locale.common.nothing_happens"));
            }
            obvious = 0;
        }
        break;
    case 631:
        txtef(4);
        txt(i18n::s.get("core.locale.magic.swarm"));
        for (auto&& cnt : cdata.all())
        {
            if (cdata[cc].state() != character::State::alive)
            {
                continue;
            }
            if (cnt.state() != character::State::alive)
            {
                continue;
            }
            if (cc == cnt.index)
            {
                continue;
            }
            if (belong_to_same_team(cdata[cc], cnt))
            {
                continue;
            }
            tc = cnt.index;
            dx = cdata[tc].position.x;
            dy = cdata[tc].position.y;
            if (dist(cdata[cc].position.x, cdata[cc].position.y, dx, dy)
                > the_ability_db[631]->sdataref3 % 1000 + 1)
            {
                continue;
            }
            if (fov_los(cdata[cc].position.x, cdata[cc].position.y, dx, dy)
                == 0)
            {
                continue;
            }
            swarm_animation(cdata[tc].position).play();
            try_to_melee_attack();
        }
        break;
    case 659:
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            break;
        }
        if (map(cdata[cc].position.x, cdata[cc].position.y, 6) != 0)
        {
            break;
        }
        cell_featset(cdata[cc].position.x, cdata[cc].position.y, 0, 14, 7, cc);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.magic.drop_mine", cdata[cc]));
        }
        break;
    case 466:
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() != character::State::alive)
            {
                continue;
            }
            if (cc == cnt.index)
            {
                continue;
            }
            if (cnt.is_immune_to_mine())
            {
                continue;
            }
            tc = cnt.index;
            dx = cdata[tc].position.x;
            dy = cdata[tc].position.y;
            if (dist(cdata[cc].position.x, cdata[cc].position.y, dx, dy) > 4)
            {
                continue;
            }
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get("core.locale.magic.gravity", cdata[tc]));
            }
            cdata[tc].gravity += 100 + rnd(100);
        }
        break;
    case 657:
        txtef(4);
        txt(i18n::s.get("core.locale.magic.mewmewmew"));
        animode = 0;
        miracle_animation().play();
        for (auto&& cnt : cdata.all())
        {
            if (cdata[cc].state() != character::State::alive)
            {
                continue;
            }
            if (cnt.state() != character::State::alive)
            {
                continue;
            }
            if (cc == cnt.index)
            {
                continue;
            }
            tc = cnt.index;
            damage_hp(cdata[tc], 9999999, cc);
        }
        break;
    case 465:
        txtef(4);
        txt(i18n::s.get("core.locale.magic.meteor"));
        meteor_animation().play();
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            dy = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                dx = cnt;
                if (rnd(3) == 0)
                {
                    map(dx, dy, 0) = 12 + rnd(2);
                }
                if (rnd(40) == 0)
                {
                    mef_add(dx, dy, 5, 24, rnd(4) + 3, 50);
                }
                if (map(dx, dy, 1) != 0)
                {
                    tc = map(dx, dy, 1) - 1;
                    dmg = sdata(16, cc) * efp / 10;
                    damage_hp(cdata[tc], dmg, cc, 50, 1000);
                }
            }
        }
        break;
    case 656:
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.magic.cheer.apply", cdata[cc]));
        }
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() != character::State::alive)
            {
                continue;
            }
            if (cc == cnt.index)
            {
                continue;
            }
            if (cc < 16)
            {
                if (cnt.index >= 16)
                {
                    continue;
                }
                else if (cdata[cc].relationship != cdata[tc].relationship)
                {
                    continue;
                }
            }
            tc = cnt.index;
            dx = cdata[tc].position.x;
            dy = cdata[tc].position.y;
            if (dist(cdata[cc].position.x, cdata[cc].position.y, dx, dy)
                > the_ability_db[656]->sdataref3 % 1000 + 1)
            {
                continue;
            }
            if (fov_los(cdata[cc].position.x, cdata[cc].position.y, dx, dy)
                == 0)
            {
                continue;
            }
            if (is_in_fov(cdata[tc]))
            {
                txtef(4);
                txt(i18n::s.get(
                    "core.locale.magic.cheer.is_excited", cdata[tc]));
            }
            buff_add(cdata[tc], 5, sdata(17, cc) * 5 + 50, 15, cdata[cc]);
            buff_add(cdata[tc], 7, sdata(17, cc) * 5 + 100, 60, cdata[cc]);
            buff_add(cdata[tc], 18, 1500, 30, cdata[cc]);
        }
        break;
    case 1131:
        if (tc != 0)
        {
            txt(i18n::s.get("core.locale.common.nothing_happens"));
            break;
        }
        snd(64);
        if (!is_cursed(efstatus))
        {
            txtef(2);
            txt(i18n::s.get("core.locale.magic.cure_corruption.apply"));
            modify_ether_disease_stage(efp * -10);
        }
        else
        {
            txtef(8);
            txt(i18n::s.get("core.locale.magic.cure_corruption.cursed"));
            modify_ether_disease_stage(200);
        }
        break;
    case 633:
        if (tc != 0)
        {
            break;
        }
        txtef(8);
        txt(i18n::s.get("core.locale.magic.eye_of_ether", cdata[cc]));
        modify_ether_disease_stage(100);
        break;
    case 638:
    case 648:
        if (efid == 648)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.insult.apply", cdata[cc], cdata[tc]));
                txtef(9);
                if (jp)
                {
                    if (cdata[cc].sex == 0)
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
                    txt(u8"\"You suck!\""s,
                        u8"\"You will die alone.\""s,
                        u8"\"Bow down before me.\""s,
                        u8"\"Go jump off a bridge.\""s,
                        u8"\"Bang your head against the wall!\""s,
                        u8"\"Why do you sniff under your dog's tail?\""s);
                }
                else
                {
                    txt(u8"\"The world is against you because you are a unsavory decomposing virus.\""s,
                        u8"\"You are no better than a immoral guzzling bureaucrat.\""s,
                        u8"\"You are so lowly.\""s,
                        u8"\"Get off me.\""s);
                }
            }
        }
        if (efid == 638)
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.gaze", cdata[cc], cdata[tc]));
            }
        }
        dmgcon(tc, StatusAilment::dimmed, 200);
        break;
    case 652:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.gaze", cdata[cc], cdata[tc]));
        }
        damage_mp(cdata[tc], rnd(20) + 1);
        break;
    case 1133:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get("core.locale.magic.molotov", cdata[tc]));
        }
        mef_add(
            cdata[tc].position.x,
            cdata[tc].position.y,
            5,
            24,
            rnd(15) + 25,
            efp,
            cc);
        mapitem_fire(cdata[tc].position.x, cdata[tc].position.y);
        return 0;
    case 651:
        if (is_in_fov(cdata[tc]))
        {
            txt(i18n::s.get(
                "core.locale.magic.scavenge.apply", cdata[cc], cdata[tc]));
        }
        p = -1;
        for (const auto& cnt : items(tc))
        {
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (inv[cnt].id == 618)
            {
                p = cnt;
                break;
            }
        }
        if (p == -1)
        {
            for (const auto& cnt : items(tc))
            {
                if (inv[cnt].number() == 0)
                {
                    continue;
                }
                if (ibit(5, cnt))
                {
                    continue;
                }
                if (the_item_db[inv[cnt].id]->category != 57000)
                {
                    continue;
                }
                p = cnt;
                break;
            }
        }
        if (p == -1)
        {
            break;
        }
        ci = p;
        if (ibit(6, ci))
        {
            if (is_in_fov(cdata[tc]))
            {
                txt(i18n::s.get(
                    "core.locale.magic.scavenge.rotten", cdata[cc], inv[ci]));
            }
            break;
        }
        rowact_item(ci);
        if (is_in_fov(cdata[tc]))
        {
            snd(18);
            txt(i18n::s.get(
                "core.locale.magic.scavenge.eats", cdata[cc], inv[ci]));
        }
        heal_hp(cdata[cc], cdata[cc].max_hp / 3);
        continuous_action_eating_finish();
        refresh_burden_state();
        break;
    case 464:
    {
        bool fastest = config::instance().animewait == 0;
        std::string messages;

        animeload(10, tc);
        for (int i = 0; i < clamp(4 + rnd(efp / 50 + 1), 1, 15); ++i)
        {
            snd(64);
            flt(calcobjlv(efp / 10), calcfixlv(3));
            dbid = 54;
            int number = 400 + rnd(efp);
            if (rnd(30) == 0)
            {
                dbid = 55;
                number = 1;
            }
            if (rnd(80) == 0)
            {
                dbid = 622;
                number = 1;
            }
            if (rnd(2000) == 0)
            {
                dbid = 290;
                number = 1;
            }
            nostack = 1;
            itemcreate(
                -1, dbid, cdata[cc].position.x, cdata[cc].position.y, number);
            const auto message =
                i18n::s.get("core.locale.magic.wizards_harvest", inv[ci]);
            if (fastest)
            {
                messages += message;
            }
            else
            {
                txt(message);
                await(config::instance().animewait * 4);
                redraw();
            }
        }
        if (fastest)
        {
            txt(messages);
            redraw();
        }
        break;
    }
    case 463:
        snd(72);
        txt(i18n::s.get("core.locale.magic.four_dimensional_pocket"));
        invfile = 8;
        ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
        tmpload(filesystem::u8path(u8"shop"s + invfile + u8".s2"));
        if (fs::exists(
                filesystem::dir::tmp() / (u8"shop"s + invfile + u8".s2")))
        {
            ctrl_file(
                FileOperation2::map_items_read,
                u8"shop"s + invfile + u8".s2");
        }
        else
        {
            for (const auto& cnt : items(-1))
            {
                inv[cnt].remove();
            }
        }
        shoptrade = 0;
        menucycle = 1;
        invsubroutine = 1;
        invctrl(0) = 22;
        invctrl(1) = 5;
        invcontainer = clamp(efp / 10 + 10, 10, 300);
        mode = 6;
        snd(100);
        ctrl_inventory();
        invcontainer = 0;
        ctrl_file(
            FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
        ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
        mode = 0;
        break;
    }

the_end:
    ci = efcibk;
    efstatus = CurseState::none;
    efsource = 0;
    return 1;
}



} // namespace elona
