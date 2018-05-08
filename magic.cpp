#include "magic.hpp"
#include "ability.hpp"
#include "access_item_db.hpp"
#include "animation.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "debug.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "trait.hpp"
#include "variables.hpp"
#include "wish.hpp"


namespace elona
{


magic_result magic(int efid, int cc)
{
    magic_data data(efid, cc);
    return magic(data);
}

magic_result magic(int efid, int cc, int tc)
{
    magic_data data(efid, cc, tc);
    return magic(data);
}

magic_result magic(int efid, int cc, int tc, int efp)
{
    magic_data data(efid, cc, tc, efp);
    return magic(data);
}

magic_result magic(magic_data m)
{
    assert(m.efid != -1);
    magic_result result { true, true, false, true, m.tc };
    bool is_negative_effect = false;
    efcancel = 0;

    bool from_item = m.efsource == efsource_t::potion
        || m.efsource == efsource_t::rod
        || m.efsource == efsource_t::scroll;
    if (!from_item)
    {
        m.efstatus = curse_state_t::none;
    }
    m.efsource = efsource_t::none;

    m.damage.element_power = 0;

    if (m.efid >= 300)
    {
        if (m.efid < 661)
        {
            result.succeeded = false;
            // buffs have ids > 1000
            bool is_buff = the_ability_db[m.efid]->sdataref1 / 1000 == 1;
            if (is_buff)
            {
                result.succeeded = true;
                p = the_ability_db[m.efid]->sdataref1 % 1000;
                if (the_buff_db[p]->type == buff_data::type_t::hex)
                {
                    is_negative_effect = true;
                }
            }
            if (the_ability_db[m.efid]->sdataref1 == 7)
            {
                is_negative_effect = true;
            }
            if (is_negative_effect == false)
            {
                power_up_if_blessed(m);
            }
            else
            {
                power_up_if_cursed(m);
            }
            if (result.succeeded)
            {
                magic_add_buff(m, result);
                goto the_end;
            }
            if (const auto damage = calc_skill_damage(m.efid, m.cc, m.efp))
            {
                m.damage = *damage;
            }
            if (m.cc == 0)
            {
                if (trait(165))
                {
                    if (m.damage.element == element_t::burning
                        || m.damage.element == element_t::icy
                        || m.damage.element == element_t::electric)
                    {
                        m.damage.dice_y = m.damage.dice_y * 125 / 100;
                    }
                }
            }
            if (rapidmagic)
            {
                magic_apply_rapidmagic(m);
            }
            switch (the_ability_db[m.efid]->sdataref1)
            {
            case sdataref1_t::melee:
                magic_melee(m, result);
                goto the_end;
            case sdataref1_t::bolt:
                magic_bolt(m, result);
                goto the_end;
            case sdataref1_t::aoe:
                magic_aoe(m, result);
                goto the_end;
            case sdataref1_t::arrow:
                magic_arrow(m, result);
                goto the_end;
            case sdataref1_t::heal:
            {
                heal_t type = static_cast<heal_t>(m.efid);
                magic_heal(m, result, type);
            }
                goto the_end;
            case sdataref1_t::special:
                if (cdata[m.cc].special_attack_type != 0)
                {
                    magic_special_attack(m, result);
                }
                else if (m.efid == 601)
                {
                    magic_suck_blood(m, result); // TODO not sure if correct
                }
                else if (is_in_fov(m.cc))
                {
                    magic_touch(m, result);
                }
                switch(m.efid) {
                case 660:
                    magic_disassembly(m, result);
                    break;
                case 617:
                    magic_touch_of_fear(m, result);
                    break;
                case 618:
                    magic_touch_of_sleep(m, result);
                    break;
                case 614:
                    magic_hunger(m, result);
                    break;
                case 613:
                    magic_weaken(m, result);
                    break;
                }
                goto the_end;
            case sdataref1_t::summon:
            {
                summon_t type = static_cast<summon_t>(m.efid);
                magic_summon(m, result, type);
            }
                goto the_end;
            case sdataref1_t::teleport:
            {
                teleport_t type = static_cast<teleport_t>(m.efid);
                magic_teleport(m, result, type);
            }
                goto the_end;
            case sdataref1_t::breath:
                magic_breath(m, result);
                goto the_end;
            }
        }
        else
        {
            power_up_if_blessed(m);
        }
    }

    handle_general_magic(m, result);

the_end:
    // TODO until everything is de-globalized
    efsource = efsource_t::none;
    tc = result.selected_target;
    f = result.succeeded ? 1 : 0;
    tlocx = m.tlocx;
    tlocy = m.tlocy;
    return result;
}

void power_up_if_blessed(magic_data& m)
{
    if (m.efstatus == curse_state_t::blessed)
    {
        m.efp = m.efp * 150 / 100;
    }
    if (is_cursed(m.efstatus))
    {
        m.efp = 50;
    }
}

void power_up_if_cursed(magic_data& m)
{
    if (m.efstatus == curse_state_t::blessed)
    {
        m.efp = 50;
    }
    if (is_cursed(m.efstatus))
    {
        m.efp = m.efp * 150 / 100;
    }
}

void handle_general_magic(const magic_data& m, magic_result& result)
{
    switch (m.efid)
    {
    case 636:
        magic_insanity(m, result);
        break;
    case 1136:
        magic_treasure_map(m, result);
        break;
    case 1135:
        magic_love_potion(m, result);
        break;
    case 654:
        magic_pregnancy(m, result);
        break;
    case 626:
        magic_examine_self(m, result);
        break;
    case 1101:
        magic_milk(m, result);
        break;
    case 1102:
        magic_alcohol(m, result);
        break;
    case 1116:
        magic_acid(m, result);
        break;
    case 1103:
        magic_water(m, result);
        break;
    case 1146:
        magic_potion_stamina(m, result);
        break;
    case 1147:
        magic_potion_greater_stamina(m, result);
        break;
    case 1142:
        magic_salt(m, result);
        break;
    case 1130:
        magic_dirty_water(m, result);
        break;
    case 300:
        magic_steal(m, result);
        break;
    case 301:
        magic_mount_dismount(m, result);
        break;
    case 183:
        magic_perform(m, result);
        break;
    case 184:
        magic_cook(m, result);
        break;
    case 185:
        magic_fish(m, result);
        break;
    case 406:
    case 407:
    {
        bool is_vanquish = m.efid == 406;
        magic_remove_hex(m, result, is_vanquish);
    }
        break;
    case 1120:
        magic_aura(m, result);
        break;
    case 1117:
        magic_create_material(m, result);
        break;
    case 632:
    case 454:
    case 1144:
    {
        mutation_t type = static_cast<mutation_t>(m.efid);
        magic_mutate(m, result, type);
    }
        break;
    case 1121:
        magic_cure_mutation(m, result);
        break;
    case 411:
        magic_identify(m, result);
        break;
    case 461:
        magic_resurrection(m, result);
        break;
    case 412:
        magic_vanquish_curse(m, result);
        break;
    case 413:
        magic_oracle(m, result);
        break;
    case 1104:
        magic_gain_spell(m, result);
        break;
    case 1143:
        magic_descent(m, result);
        break;
    case 1105:
        magic_gain_attribute(m, result);
        break;
    case 1107:
        magic_faith(m, result);
        break;
    case 1119:
        magic_growth(m, result);
        break;
    case 1106:
        magic_failed_altar_takeover(m, result);
        break;
    case 1139:
        magic_hermes_blood(m, result);
        break;
    case 1113:
        magic_gain_potential(m, result);
        break;
    case 653:
        magic_vanquish(m, result);
        break;
    case 430:
    case 429:
    {
        bool is_sense_object = m.efid == 430;
        magic_mapping(m, result, is_sense_object);
    }
        break;
    case 658:
        magic_vorpal(m, result);
        break;
    case 440:
    case 439:
    {
        bool is_restore_body = m.efid == 439;
        magic_restore(m, result, is_restore_body);
    }
        break;
    case 441:
        magic_wish(m, result);
        break;
    case 1141:
        magic_escape(m, result);
        break;
    case 428:
        magic_return(m, result);
        break;
    case 621:
        magic_restore_mana(m, result);
        break;
    case 624:
        magic_absorb_mana(m, result);
        break;
    case 1108:
        magic_poison(m, result);
        break;
    case 1111:
        magic_dye(m, result);
        break;
    case 1109:
        magic_confusion(m, result);
        break;
    case 1110:
        magic_potion_numbness(m, result);
        break;
    case 1112:
        magic_juice(m, result);
        break;
    case 645:
    case 1114:
    {
        bool is_attack = m.efid == 645;
        magic_curse(m, result, is_attack);
    }
        break;
    case 1118:
        magic_weaken_resistance(m, result);
        break;
    case 1138:
    case 1123:
    case 1122:
    case 1137:
    {
        ally_t type = static_cast<ally_t>(m.efid);
        magic_ally(m, result, type);
    }
        break;
    case 435:
        magic_domination(m, result);
        break;
    case 436:
    case 437:
    case 455:
    case 634:
    case 456:
    {
        ground_effect_t type = static_cast<ground_effect_t>(m.efid);
        magic_place_ground_effect(m, result, type);
    }
        break;
    case 1145:
        magic_create_artifact(m, result);
        break;
    case 49:
        magic_superior_material(m, result);
        break;
    case 21:
    case 1127:
    {
        bool is_material_kit = m.efid == 21;
        magic_change_material(m, result, is_material_kit);
    }
        break;
    case 1128:
        magic_deed_of_inheritance(m, result);
        break;
    case 1124:
    case 1125:
    {
        bool is_armor = m.efid == 1125;
        magic_enchant(m, result, is_armor);
    }
        break;
    case 630:
    case 1129:
    {
        bool is_fill_charge = m.efid == 630;
        magic_recharge(m, result, is_fill_charge);
    }
        break;
    case 629:
        magic_draw_charge(m, result);
        break;
    case 628:
        magic_change_creature(m, result);
        break;
    case 1140:
        magic_flying(m, result);
        break;
    case 1132:
        magic_alchemy(m, result);
        break;
    case 457:
    case 438:
    {
        bool create_door = m.efid == 457;
        magic_wall_creation(m, result, create_door);
    }
        break;
    case 631:
        magic_swarm(m, result);
        break;
    case 659:
        magic_drop_item(m, result);
        break;
    case 466:
        magic_gravity(m, result);
        break;
    case 657:
        magic_ehekatl(m, result);
        break;
    case 465:
        magic_meteorite(m, result);
        break;
    case 656:
        magic_cheer(m, result);
        break;
    case 1131:
        magic_cure_corruption(m, result);
        break;
    case 633:
        magic_corrupt_player(m, result);
        break;
    case 638:
    case 648:
    {
        bool is_insult = m.efid == 648;
        magic_aggro(m, result, is_insult);
    }
        break;
    case 652:
        magic_gaze(m, result);
        break;
    case 1133:
    {
        magic_surround_in_flames(m, result);
        result.turn_passed = false;
    }
        //return 0;
        break;
    case 651:
        magic_loot(m, result);
        break;
    case 464:
        magic_fall_down(m, result);
        break;
    case 463:
        magic_four_dimensional_pocket(m, result);
        break;
    }
}


void magic_add_buff(const magic_data& m, magic_result& result)
{
    if (the_buff_db[p]->type == buff_data::type_t::buff)
    {
        animeload(11, m.tc);
    }
    else if (the_buff_db[p]->type == buff_data::type_t::hex)
    {
        play_animation(6, m.damage.element);
    }
    if (m.efid == 625 || m.efid == 446)
    {
        if ((m.tc == 0 && m.cc == 0) || m.cc == gdata_mount)
        {
            if (gdata_mount != 0)
            {
                result.selected_target = gdata_mount;
            }
        }
    }
    addbuff(result.selected_target, p, m.efp, calc_buff_duration(p, m.efp));
    if (m.efid == 447)
    {
        if (m.efstatus == curse_state_t::blessed)
        {
            cdata[result.selected_target].birth_year += rnd(3) + 1;
            if (cdata[result.selected_target].birth_year + 12 > gdata_year)
            {
                cdata[result.selected_target].birth_year = gdata_year - 12;
            }
            if (is_in_fov(result.selected_target))
            {
                txtef(2);
                txt(lang(
                         name(result.selected_target) + u8"の老化は遅くなった。"s,
                         name(result.selected_target) + your(result.selected_target)
                         + u8" aging process slows down."s));
            }
        }
    }
    if (m.efid == 446)
    {
        if (is_cursed(m.efstatus))
        {
            cdata[result.selected_target].birth_year -= rnd(3) + 1;
            if (is_in_fov(result.selected_target))
            {
                txtef(8);
                txt(lang(
                         name(result.selected_target) + u8"の老化は速くなった。"s,
                         name(result.selected_target) + your(result.selected_target)
                         + u8" aging process speeds up."s));
            }
        }
    }
    if (m.efid == 458)
    {
        if (result.selected_target == 0)
        {
            // No need to pass result.selected_target, it only effects PC <-> NPC
            incognitobegin();
        }
    }
}


void magic_apply_rapidmagic(magic_data& m)
{
    m.efp = m.efp / 2 + 1;
    m.damage.dice_x = m.damage.dice_x / 2 + 1;
    m.damage.dice_y = m.damage.dice_y / 2 + 1;
    m.damage.damage_bonus = m.damage.damage_bonus / 2 + 1;
}

void magic_melee(const magic_data& m, magic_result& result)
{
    play_animation(18, m.damage.element);

    // TODO Temporary until globals are removed.
    cc = m.cc;
    tc = m.tc;
    dice1 = m.damage.dice_x;
    dice2 = m.damage.dice_y;
    bonus = m.damage.damage_bonus;
    //ele = m.damage.element;
    //elep = m.damage.element_power;
    //try_to_melee_attack(ele, elep);
    try_to_melee_attack();
}

void magic_bolt(const magic_data& m, magic_result& result)
{
    int stat = get_route(cdata[m.cc].position.x, cdata[m.cc].position.y, m.tlocx, m.tlocy);
    if (stat == 0)
    {
        return;
    }

    play_animation(0, m.damage.element, m.efid);
    dx = cdata[m.cc].position.x;
    dy = cdata[m.cc].position.y;
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
        if (dist(dx, dy, cdata[m.cc].position.x, cdata[m.cc].position.y)
            > the_ability_db[m.efid]->sdataref3 % 1000 + 1)
        {
            break;
        }
        if (dx == cdata[m.cc].position.x
            && dy == cdata[m.cc].position.y)
        {
            continue;
        }
        if (m.damage.element == element_t::burning)
        {
            mapitem_fire(dx, dy);
        }
        if (m.damage.element == element_t::icy)
        {
            mapitem_cold(dx, dy);
        }
        if (map(dx, dy, 1) != 0)
        {
            result.selected_target = map(dx, dy, 1) - 1;
            if (m.cc != result.selected_target)
            {
                if (gdata_mount != 0)
                {
                    if (gdata_mount == m.cc)
                    {
                        if (result.selected_target == 0)
                        {
                            continue;
                        }
                    }
                }
                dmg = roll(m.damage);
                int stat = calcmagiccontrol(m.cc, result.selected_target);
                if (stat == 1)
                {
                    continue;
                }
                if (is_in_fov(result.selected_target))
                {
                    if (result.selected_target >= 16)
                    {
                        gdata(809) = 2;
                        txt3rd = 1;
                        txt(lang(
                                 u8"ボルトは"s + name(result.selected_target)
                                 + u8"に命中し"s,
                                 u8"The bolt hits "s + name(result.selected_target)
                                 + u8" and"s));
                    }
                    else
                    {
                        txt(lang(
                                 u8"ボルトが"s + name(result.selected_target)
                                 + u8"に命中した。"s,
                                 u8"The bolt hits "s + name(result.selected_target)
                                 + u8"."s));
                    }
                }
                dmghp(result.selected_target, dmg, m.cc, m.damage.element, m.damage.element_power);
            }
        }
    }
}

void magic_aoe(const magic_data& m, magic_result& result)
{
    int chainbomb = 0;
    elona_vector1<int> chainbomblist;
    int chara_hit = 0;

    // Triggering a bomb causes cc to switch to the bomb character.
    // It also causes damage, tlocx, tlocy, ele and elep to change to that of the bomb character.
    int current_cc = m.cc;
    int current_tlocx = m.tlocx;
    int current_tlocy = m.tlocy;
    skill_damage current_damage = m.damage;

    ccbk = m.cc;
    if (m.efid == 644)
    {
        stxt(
             current_cc,
             lang(
                  name(current_cc) + u8"は爆発した。"s,
                  name(current_cc) + u8" explode"s + _s(current_cc) + u8"."s));
    }
    while (true)
    {
        cdata[current_cc].will_explode_soon() = false;
        range_ = the_ability_db[m.efid]->sdataref3 % 1000 + 1;
        if (debug::voldemort && current_cc == 0)
        {
            range_ *= 2;
        }
        if (m.efid == 644)
        {
            range_ = 2;
        }
        if (m.efid != 404 && m.efid != 637)
        {
            aniref = range_;
            anix = current_tlocx;
            aniy = current_tlocy;
            play_animation(2, current_damage.element);
        }
        for (int cnt = 0, cnt_end = (range_ * 2 + 1); cnt < cnt_end; ++cnt)
        {
            dy = current_tlocy - range_ + cnt;
            if (dy < 0 || dy >= mdata(1))
            {
                continue;
            }
            for (int cnt = 0, cnt_end = (range_ * 2 + 1); cnt < cnt_end; ++cnt)
            {
                dx = current_tlocx - range_ + cnt;
                if (dx < 0 || dx >= mdata(0))
                {
                    continue;
                }
                if (dist(current_tlocx, current_tlocy, dx, dy) > range_)
                {
                    continue;
                }
                if (fov_los(current_tlocx, current_tlocy, dx, dy) == 0)
                {
                    continue;
                }
                if (map(dx, dy, 1) == 0)
                {
                    continue;
                }
                chara_hit = map(dx, dy, 1) - 1;
                if (m.efid == 404)
                {
                    result.succeeded = false;
                    if (current_cc == 0 || cdata[current_cc].relationship >= 0)
                    {
                        if (cdata[chara_hit].relationship >= 0)
                        {
                            result.succeeded = true;
                        }
                    }
                    else if (cdata[chara_hit].relationship <= -1)
                    {
                        result.succeeded = true;
                    }
                    if (result.succeeded)
                    {
                        play_animation(11, current_damage.element);
                        if (is_in_fov(chara_hit))
                        {
                            txt(lang(
                                     name(tc) + u8"は回復した。"s,
                                     name(tc) + u8" "s + is(chara_hit)
                                     + u8" healed."s));
                        }
                        magic_do_heal(m);
                    }
                    continue;
                }
                if (m.efid == 637)
                {
                    result.succeeded = false;
                    if (current_cc == 0 || cdata[current_cc].relationship >= 0)
                    {
                        if (cdata[chara_hit].relationship >= 0)
                        {
                            result.succeeded = true;
                        }
                    }
                    else if (cdata[chara_hit].relationship <= -1)
                    {
                        result.succeeded = true;
                    }
                    if (result.succeeded)
                    {
                        play_animation(11, current_damage.element);
                        txt(lang(
                                 name(chara_hit) + u8"の狂気は消え去った。"s,
                                 name(chara_hit) + u8" "s + is(chara_hit)
                                 + u8" completely sane again."s));
                        healsan(chara_hit, m.efp / 10);
                        healcon(chara_hit, 11, 9999);
                    }
                    continue;
                }
                if (dx == cdata[current_cc].position.x
                    && dy == cdata[current_cc].position.y)
                {
                    continue;
                }
                if (gdata_mount != 0)
                {
                    if (gdata_mount == current_cc)
                    {
                        if (chara_hit == 0)
                        {
                            continue;
                        }
                    }
                }
                if (current_damage.element == element_t::burning)
                {
                    mapitem_fire(dx, dy);
                }
                if (current_damage.element == element_t::icy)
                {
                    mapitem_cold(dx, dy);
                }
                if (current_cc != chara_hit)
                {
                    dmg = roll(current_damage) * 100
                        / (75 + dist(current_tlocx, current_tlocy, dx, dy) * 25);
                    int stat = calcmagiccontrol(current_cc, chara_hit);
                    if (stat == 1)
                    {
                        continue;
                    }
                    if (m.efid == 644)
                    {
                        if (is_in_fov(tc))
                        {
                            if (chara_hit >= 16)
                            {
                                gdata(809) = 2;
                                txt3rd = 1;
                                txt(lang(
                                         u8"爆風は"s + name(chara_hit)
                                         + u8"に命中し"s,
                                         u8"The explosion hits "s + name(chara_hit)
                                         + u8" and"s));
                            }
                            else
                            {
                                txt(lang(
                                         u8"爆風が"s + name(chara_hit)
                                         + u8"に命中した。"s,
                                         u8"The explosion hits "s + name(chara_hit)
                                         + u8"."s));
                            }
                        }
                        if (cdata[chara_hit].explodes())
                        {
                            chainbomblist(chainbomb) = chara_hit;
                            ++chainbomb;
                            continue;
                        }
                    }
                    else if (is_in_fov(chara_hit))
                    {
                        if (chara_hit >= 16)
                        {
                            gdata(809) = 2;
                            txt3rd = 1;
                            txt(lang(
                                     u8"ボールは"s + name(chara_hit)
                                     + u8"に命中し"s,
                                     u8"The ball hits "s + name(chara_hit)
                                     + u8" and"s));
                        }
                        else
                        {
                            txt(lang(
                                     u8"ボールが"s + name(chara_hit)
                                     + u8"に命中した。"s,
                                     u8"The Ball hits "s + name(chara_hit)
                                     + u8"."s));
                        }
                    }
                    dmghp(chara_hit, dmg, current_cc, current_damage.element, current_damage.element_power);
                }
            }
        }
        if (m.efid == 644)
        {
            dmghp(current_cc, 99999, -16);
        }

        if (chainbomb > 0)
        {
            bool chain_triggered = false;
            while (true)
            {
                --chainbomb;
                if (chainbomb < 0)
                    break;
                current_cc = chainbomblist(chainbomb);
                current_tlocx = cdata[current_cc].position.x;
                current_tlocy = cdata[current_cc].position.y;
                if (cdata[current_cc].state == 1)
                {
                    // TODO do efid/efp change also? it seems like they should...
                    const auto damage =
                        calc_skill_damage(m.efid, current_cc, m.efp);
                    current_damage = *damage;
                    stxt(
                         current_cc,
                         lang(
                              name(current_cc) + u8"は誘爆した。"s,
                              name(current_cc) + u8" explode"s + _s(current_cc)
                              + u8"."s));
                    chain_triggered = true;
                    break;
                }
            }

            if (!chain_triggered)
            {
                break;
            }
        }
    }
    // TODO remove?
    cc = ccbk;
}

void magic_arrow(const magic_data& m, magic_result& result)
{
    play_animation(1, m.damage.element);
    dmg = roll(m.damage.dice_y, m.damage.dice_x, m.damage.damage_bonus);
    if (is_in_fov(m.tc))
    {
        if (m.tc >= 16)
        {
            gdata(809) = 2;
            txt3rd = 1;
            txt(lang(
                     u8"矢は"s + name(m.tc) + u8"に命中し"s,
                     u8"The arrow hits "s + name(m.tc) + u8" and"s));
        }
        else
        {
            txt(lang(
                     u8"矢が"s + name(m.tc) + u8"に命中した。"s,
                     u8"The arrow hits "s + name(m.tc) + u8"."s));
        }
    }
    dmghp(m.tc, dmg, m.cc, m.damage.element, m.damage.element_power);
}

void magic_summon(const magic_data& m, magic_result& result, summon_t type)
{
    if (m.cc == 0)
    {
        if (gdata_other_character_count + 100 >= ELONA_MAX_OTHER_CHARACTERS)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            result.obvious = false;
            return;
        }
    }
    p = 3;
    int adjusted_power;
    adjusted_power = (m.efp / 25 + m.efp * m.efp / 10000 + cdata[m.cc].level) / 2;
    if (adjusted_power < 1)
    {
        adjusted_power = 1;
    }
    switch(type)
    {
    case summon_t::pawn:
        adjusted_power = 15 + rnd(8);
        break;
    case summon_t::cat:
        adjusted_power = 2 + rnd(18);
        break;
    case summon_t::fire:
        adjusted_power = 15 + rnd(15);
        break;
    case summon_t::yeek:
        adjusted_power = 5 + rnd(12);
        break;
    case summon_t::other:
        p = 10;
        break;
    }
    for (int cnt = 0, cnt_end = (1 + rnd(p)); cnt < cnt_end; ++cnt)
    {
        flt(calcobjlv(adjusted_power), 2);
        dbid = 0;
        switch(type)
        {
        case summon_t::wild:
            fltn(u8"wild"s);
            break;
        case summon_t::fire:
            fltn(u8"fire"s);
            break;
        case summon_t::pawn:
            fltn(u8"pawn"s);
            break;
        case summon_t::cat:
            fltn(u8"cat"s);
            break;
        case summon_t::yeek:
            fltn(u8"yeek"s);
            break;
        case summon_t::other:
            dbid = 176;
            break;
        }
        characreate(
            -1, dbid, cdata[m.tc].position.x, cdata[m.tc].position.y);
        if (type != summon_t::other)
        {
            if (cdata[rc].id == cdata[m.cc].id)
            {
                chara_vanquish(rc);
                --cnt;
                continue;
            }
        }
    }
    if (is_in_fov(m.cc))
    {
        txt(lang(
                u8"魔法でモンスターが召喚された。"s,
                u8"Several monsters come out from a portal."s));
    }
}

void magic_teleport(const magic_data& m, magic_result& result, teleport_t type)
{
    int tcprev = 0;
    int telex = 0;
    int teley = 0;

    tcprev = result.selected_target;
    if (gdata_mount != 0)
    {
        if (gdata_mount == result.selected_target)
        {
            return;
        }
    }
    if (type == teleport_t::self)
    {
        result.selected_target = m.cc;
    }
    if (type == teleport_t::toward)
    {
        telex = cdata[result.selected_target].position.x;
        teley = cdata[result.selected_target].position.y;
        result.selected_target = m.cc;
    }
    if (type == teleport_t::drawn)
    {
        telex = cdata[m.cc].position.x;
        teley = cdata[m.cc].position.y;
    }
    if (type == teleport_t::other || type == teleport_t::thief)
    {
        if (map(tlocx, tlocy, 1) == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            result.obvious = false;
            return;
        }
        result.selected_target = map(tlocx, tlocy, 1) - 1;
    }
    if (gdata_current_map == 40 || mdata(6) == 1
        || gdata_current_map == 37 || gdata_current_map == 41)
    {
        if (is_in_fov(result.selected_target))
        {
            txt(lang(
                    u8"魔法の力がテレポートを防いだ。"s,
                    u8"Magical field prevents teleportation."s));
        }
        return;
    }
    if (type != teleport_t::toward && encfind(m.tc, 22) != -1)
    {
        if (is_in_fov(result.selected_target))
        {
            txt(lang(
                    u8"魔法の力がテレポートを防いだ。"s,
                    u8"Magical field prevents teleportation."s));
        }
        return;
    }
    if (type == teleport_t::thief)
    {
        if (result.selected_target == m.cc)
        {
            if (is_in_fov(result.selected_target))
            {
                txt(lang(
                        u8"魔法の力がテレポートを防いだ。"s,
                        u8"Magical field prevents teleportation."s));
            }
            return;
        }
        p = rnd(cdata[result.selected_target].gold / 10 + 1);
        if (rnd(sdata(13, result.selected_target)) > rnd(sdata(12, m.cc) * 4)
            || cdata[result.selected_target].is_protected_from_thieves() == 1)
        {
            txt(lang(
                    name(result.selected_target) + u8"は自分の財布を守った。"s,
                    name(result.selected_target) + u8" guard"s + _s(result.selected_target) + u8" "s + his(result.selected_target)
                    + u8" wallet from a thief."s));
            p = 0;
        }
        if (p != 0)
        {
            snd(12);
            cdata[result.selected_target].gold -= p;
            txt(lang(
                    name(m.cc) + u8"は"s + name(result.selected_target) + u8"から"s + p
                    + u8"枚の金貨を奪った。"s,
                    name(m.cc) + u8" steal"s + _s(m.cc) + u8" "s + p
                    + u8" gold pieces from "s + name(result.selected_target) + u8"."s));
            cdata[m.cc].gold += p;
        }
        result.selected_target = m.cc;
        if (gdata_mount != 0)
        {
            if (gdata_mount == result.selected_target)
            {
                return;
            }
        }
    }
    if (is_in_fov(result.selected_target))
    {
        snd(72);
    }
    tx = cdata[result.selected_target].position.x;
    ty = cdata[result.selected_target].position.y;
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        if (type == teleport_t::self_short || type == teleport_t::dimensional_move)
        {
            p(0) = -1;
            p(1) = 1;
            cdata[result.selected_target].next_position.x = cdata[result.selected_target].position.x
                + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
            cdata[result.selected_target].next_position.y = cdata[result.selected_target].position.y
                + (3 - cnt / 70 + rnd(5)) * p(rnd(2));
        }
        else if (type == teleport_t::toward)
        {
            cdata[result.selected_target].next_position.x =
                telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
            cdata[result.selected_target].next_position.y =
                teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
        }
        else if (type == teleport_t::drawn)
        {
            cdata[result.selected_target].next_position.x =
                telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
            cdata[result.selected_target].next_position.y =
                teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
        }
        else
        {
            cdata[result.selected_target].next_position.x = rnd(mdata(0) - 2) + 1;
            cdata[result.selected_target].next_position.y = rnd(mdata(1) - 2) + 1;
        }
        cell_check(
            cdata[result.selected_target].next_position.x, cdata[result.selected_target].next_position.y);
        if (cellaccess == 1)
        {
            if (type == teleport_t::toward)
            {
                if (is_in_fov(m.cc))
                {
                    txt(lang(
                            name(m.cc) + u8"は"s + cdatan(0, tcprev)
                            + u8"の元に移動した。"s,
                            name(m.cc) + u8" teleport"s + _s(m.cc)
                            + u8" toward "s + cdatan(0, tcprev)
                            + u8"."s));
                }
            }
            else if (type == teleport_t::drawn)
            {
                if (is_in_fov(m.cc))
                {
                    txt(lang(
                            name(result.selected_target) + u8"は引き寄せられた。"s,
                            name(result.selected_target) + u8" "s + is(result.selected_target) + u8" drawn."s));
                }
            }
            else if (is_in_fov(m.cc))
            {
                if (type == teleport_t::thief)
                {
                    txt(lang(
                            u8"泥棒は笑って逃げた。"s,
                            u8"A thief escapes laughing."s));
                }
                else
                {
                    txt(lang(
                            name(result.selected_target) + u8"は突然消えた。"s,
                            u8"Suddenly, "s + name(result.selected_target) + u8" disappear"s
                            + _s(result.selected_target) + u8"."s));
                }
            }
            rowactend(m.cc);

            // TODO de-globalize, m.cc is const here
            int ccprev = cc;
            cc = result.selected_target;
            activate_trap();
            cc = ccprev;

            if (result.selected_target == 0)
            {
                update_screen();
            }
            break;
        }
    }
    result.selected_target = tcprev;
}

void magic_breath(const magic_data& m, magic_result& result)
{
    int stat = get_route(cdata[m.cc].position.x, cdata[m.cc].position.y, m.tlocx, m.tlocy);
    if (stat == 0)
    {
        return;
    }
    std::string valn;
    if (m.damage.element != element_t::none)
    {
        valn = i18n::_(u8"ability", std::to_string(static_cast<int>(m.damage.element)), u8"name")
            + lang(u8"の"s, u8" breath"s);
    }
    else
    {
        valn = lang(""s, u8"breath"s);
    }
    if (is_in_fov(m.cc))
    {
        txt(lang(
                 name(m.cc) + u8"は"s + valn + u8"ブレスを吐いた。"s,
                 name(m.cc) + u8" bellow"s + _s(m.cc) + u8" "s + valn
                 + u8" from "s + his(m.cc) + u8" mouth."s));
    }
    dx = cdata[m.cc].position.x;
    dy = cdata[m.cc].position.y;
    breath_list(m.efid);
    play_animation(3, m.damage.element);
    for (int cnt = 0, cnt_end = (maxbreath); cnt < cnt_end; ++cnt)
    {
        dx = breathlist(0, cnt);
        dy = breathlist(1, cnt);
        if (fov_los(
                    cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy)
            == 0)
        {
            continue;
        }
        if (dx == cdata[m.cc].position.x
            && dy == cdata[m.cc].position.y)
        {
            continue;
        }
        if (gdata_mount != 0)
        {
            if (gdata_mount == m.cc)
            {
                if (result.selected_target == 0)
                {
                    continue;
                }
            }
        }
        if (m.damage.element == element_t::burning)
        {
            mapitem_fire(dx, dy);
        }
        if (m.damage.element == element_t::icy)
        {
            mapitem_cold(dx, dy);
        }
        if (map(dx, dy, 1) != 0)
        {
            result.selected_target = map(dx, dy, 1) - 1;
            if (m.cc != result.selected_target)
            {
                dmg = roll(m.damage);
                if (is_in_fov(result.selected_target))
                {
                    if (result.selected_target >= 16)
                    {
                        gdata(809) = 2;
                        txt3rd = 1;
                        txt(lang(
                                 u8"ブレスは"s + name(result.selected_target)
                                 + u8"に命中し"s,
                                 u8"The breath hits "s + name(result.selected_target)
                                 + u8" and"s));
                    }
                    else
                    {
                        txt(lang(
                                 u8"ブレスは"s + name(result.selected_target)
                                 + u8"に命中した。"s,
                                 u8"The breath hits "s + name(result.selected_target)
                                 + u8"."s));
                    }
                }
                dmghp(result.selected_target, dmg, m.cc, m.damage.element, m.damage.element_power);
            }
        }
    }
}

void magic_insanity(const magic_data& m, magic_result& result)
{
    txtef(8);
    if (jp)
    {
        txt(name(m.tc) + u8"は"s + name(m.cc)
            + u8"の腹の亀裂から蛆虫が沸き出るのを見た。"s,
            name(m.tc) + u8"は"s + name(m.cc) + u8"が屍を貪る姿を目撃した。"s,
            name(m.tc) + u8"は"s + name(m.cc) + u8"の恐ろしい瞳に震えた。"s,
            name(m.tc) + u8"は"s + name(m.cc)
            + u8"の触手に絡まる臓物に吐き気を感じた。"s);
    }
    if (en)
    {
        txt(name(m.tc) + u8" see"s + _s(m.tc)
            + u8" maggots breed in the rent stomach of "s + name(m.cc)
            + u8"."s,
            name(m.tc) + u8" see"s + _s(m.tc) + u8" "s + name(m.cc) + u8" chow"s
            + _s(m.cc) + u8" dead bodies."s,
            name(m.tc) + u8" shudder"s + _s(m.tc) + u8" at "s + name(m.cc)
            + your(m.cc) + u8" terrifying eyes."s,
            name(m.tc) + u8" feel"s + _s(m.tc)
            + u8" sick at entrails caught in "s + name(m.cc) + your(m.cc)
            + u8" tentacles."s);
    }
    damage_insanity(m.tc, rnd(roll(m.damage) + 1));
}

void magic_treasure_map(const magic_data& m, magic_result& result)
{
    // TODO deglobalize ci
    if (mdata(6) != 1)
    {
        txt(lang(
                u8"それはグローバルマップで読む必要がある。"s,
                u8"You need to read it while you are in the global map."s));
        return;
    }
    if (is_cursed(m.efstatus))
    {
        if (rnd(5) == 0)
        {
            txt(lang(
                    u8"呪われた地図は触れると崩れ落ちた。"s,
                    u8"The cursed map crumbles as you touch."s));
            --inv[ci].number;
            if (ci >= 5080)
            {
                cell_refresh(inv[ci].position.x, inv[ci].position.y);
            }
            return;
        }
    }
    if (inv[ci].param1 == 0)
    {
        item_separate(ci);
        for (int cnt = 0; cnt < 1000; ++cnt)
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
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                result.succeeded = true;
                int cnt2 = cnt;
                for (int cnt = 0; cnt < 3; ++cnt)
                {
                    p = map(dx + x(cnt2) * cnt, dy + y(cnt2) * cnt, 0);
                    if ((264 <= p && p < 363) || chipm(7, p) & 4)
                    {
                        result.succeeded = false;
                        break;
                    }
                }
                if (result.succeeded)
                {
                    break;
                }
            }
            if (result.succeeded)
            {
                break;
            }
        }
        inv[ci].param1 = dx;
        inv[ci].param2 = dy;
    }
    txt(lang(
            u8"何かの場所を記した地図のようだ…"s,
            u8"There's a mark on the map..."s));
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
    gmode(1, inf_tiles, inf_tiles);
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
            gcopy(2, p % 33 * inf_tiles, p / 33 * inf_tiles);
            if (x == inv[ci].param1)
            {
                if (y == inv[ci].param2)
                {
                    pos(sx, sy);
                    font(40 - en * 2, snail::font_t::style_t::italic);
                    color(255, 20, 20);
                    mes(lang(u8"○"s, u8"O"s));
                    color(0, 0, 0);
                }
            }
        }
    }
    gmode(2);
    pos(wx, wy);
    gcopy(4, 400, 0, ww, wh);
    redraw();
    press();
    snd(71);
}

void magic_love_potion(const magic_data& m, magic_result& result)
{
    if (is_cursed(m.efstatus))
    {
        if (m.tc == 0)
        {
            eatstatus(m.efstatus, m.tc);
        }
        else
        {
            txt(lang(
                     u8"媚薬は呪われていた。"s + name(m.tc) + u8"は"s + name(0)
                     + u8"を軽蔑のまなざしで見つめた。"s,
                     u8"This love potion is cursed. "s + name(m.tc) + u8" look"s
                     + _s(m.tc) + u8" at "s + name(0)
                     + u8" with a contemptuous glance."s));
            modimp(m.tc, -15);
        }
        result.obvious = false;
        return;
    }
    cdata[m.tc].emotion_icon = 317;
    if(m.potion_consume_type) {
        if (*m.potion_consume_type != potion_consume_t::drunk)
        {
            txt(lang(
                     name(m.tc) + u8"は恋の予感がした。"s,
                     name(m.tc) + u8" sense"s + _s(m.tc) + u8" a sigh of love,"s));
            modimp(m.tc, clamp(m.efp / 15, 0, 15));
            dmgcon(m.tc, 7, 100);
            lovemiracle(m.tc);
            return;
        }
    }
    if (m.tc == 0)
    {
        txt(lang(name(m.tc) + u8"は興奮した！"s, u8"You are excited!"s));
    }
    else
    {
        txt(lang(
                 name(m.tc) + u8"は"s + name(0) + u8"を熱いまなざしで見つめた。"s,
                 name(m.tc) + u8" give"s + _s(m.tc) + u8" "s + name(0)
                 + u8" the eye."s));
        lovemiracle(m.tc);
        modimp(m.tc, clamp(m.efp / 4, 0, 25));
    }
    dmgcon(m.tc, 7, 500);
}

void magic_pregnancy(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                 name(m.cc) + u8"は"s + name(m.tc)
                 + u8"の口の中に何かを送り込んだ！"s,
                 name(m.cc) + u8" put"s + _s(m.cc) + u8" something into "s + name(m.tc)
                 + your(m.tc) + u8" body!"s));
    }
    // TODO de-globalize
    get_pregnant();
}

void magic_examine_self(const magic_data& m, magic_result& result)
{
    txt(lang(
             u8"あなたは自分の状態を調べた。"s, u8"You examine yourself."s));
    animeload(10, m.tc);
    label_1964();
}

void magic_milk(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        snd(107);
        if (is_cursed(m.efstatus))
        {
            if (m.tc == 0)
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
                         u8"\"Argh, the milk is cursed!\""s));
            }
        }
        else if (m.tc == 0)
        {
            txt(lang(
                     u8"濃厚で病み付きになりそうな味だ。"s,
                     u8"The taste is very thick, almost addictive."s));
        }
        else
        {
            txtef(9);
            txt(lang(u8"「うまー」"s, u8"\"Yummy!\""s));
        }
    }
    if (m.efstatus == curse_state_t::blessed)
    {
        modheight(m.tc, rnd(5) + 1);
    }
    if (is_cursed(m.efstatus))
    {
        modheight(m.tc, (rnd(5) + 1) * -1);
    }
    cdata[m.tc].nutrition += 1000 * (m.efp / 100);
    if (m.tc == 0)
    {
        // TODO de-globalize
        label_2162();
    }
    eatstatus(m.efstatus, m.tc);
    animeload(15, m.tc);
}

void magic_alcohol(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        if (is_cursed(m.efstatus))
        {
            txtef(9);
            txt(lang(u8"「うぃっ…」"s, u8"*Hic*"s),
                lang(u8"「まずいぜ」"s, u8"\"Ah, bad booze.\""s),
                lang(u8"「げー♪」"s, u8"\"Ugh...\""s),
                lang(
                     u8"「腐ったミルクみたいな味だ」"s,
                     u8"\"Bah, smells like rotten milk.\""s));
        }
        else
        {
            txtef(9);
            txt(lang(u8"「うぃっ！」"s, u8"*Hic*"s),
                lang(u8"「うまいぜ」"s, u8"\"Ah, good booze.\""s),
                lang(u8"「らららー♪」"s, u8"\"La-la-la-la.\""s),
                lang(u8"「ひっく」"s, u8"\"I'm going to heaven.\""s),
                lang(u8"「ふぅ」"s, u8"\"Whew!\""s),
                lang(u8"「たまらないわ」"s, u8"\"I'm revived!\""s),
                lang(u8"「んまっ♪」"s, u8"\"Awesome.\""s));
        }
    }
    dmgcon(m.tc, 8, m.efp);
    eatstatus(m.efstatus, m.tc);
}

void magic_acid(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        if (m.tc == 0)
        {
            txt(lang(u8"ぐわぁぁ！"s, u8"Arrrrg!"s));
        }
        txt(lang(
                 u8"酸が"s + name(m.tc) + u8"を溶かした。"s,
                 u8"The sulfuric acid melts "s + name(m.tc) + u8"."s));
    }
    if (cdata[m.tc].is_pregnant())
    {
        cdata[m.tc].is_pregnant() = false;
        if (is_in_fov(m.tc))
        {
            txt(lang(
                     name(m.tc) + u8"の体内のエイリアンは溶けた。"s,
                     name(m.tc) + your(m.tc) + u8" alien children melt in "s
                     + his(m.tc) + u8" stomach."s));
        }
    }
    dmghp(m.tc, m.efp * efstatusfix(m.efstatus, 500, 400, 100, 50) / 1000, -15, element_t::acid, m.efp);
}

void magic_water(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        if (m.tc == 0)
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
    sickifcursed(m.efstatus, m.tc, 1);
}

void magic_potion_stamina(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(u8"*シュワワ* 刺激的！"s, u8"*quaff* Juicy!"s));
        txt(lang(
                 name(m.tc) + u8"のスタミナが少し回復した。"s,
                 name(m.tc) + u8" restore"s + _s(m.tc) + u8" some stamina."s));
    }
    healsp(m.tc, 25);
    sickifcursed(m.efstatus, m.tc, 1);
}

void magic_potion_greater_stamina(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(u8"*ごくり*"s, u8"*quaff*"s));
        txt(lang(
                 name(m.tc) + u8"のスタミナはかなり回復した。"s,
                 name(m.tc) + u8" greatly restore"s + _s(m.tc) + u8" stamina."s));
    }
    healsp(m.tc, 100);
    sickifcursed(m.efstatus, m.tc, 1);
}

void magic_salt(const magic_data& m, magic_result& result)
{
    if (cdatan(2, m.tc) == u8"snail"s)
    {
        if (is_in_fov(m.tc))
        {
            txtef(3);
            txt(lang(
                     u8"塩だ！"s + name(m.tc) + u8"は溶けはじめた！"s,
                     u8"It's salt! "s + name(m.tc) + u8" start"s + _s(m.tc)
                     + u8" to melt."s));
        }
        if (cdata[m.tc].hp > 10)
        {
            dmghp(m.tc, cdata[m.tc].hp - rnd(10), -15);
        }
        else
        {
            dmghp(m.tc, rnd(20000), -15);
        }
    }
    else if (is_in_fov(m.tc))
    {
        txtef(9);
        txt(lang(u8"「しょっぱ〜」"s, u8"\"Salty!\""s));
    }
}

void magic_dirty_water(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        if (m.tc == 0)
        {
            txt(lang(u8"*ごくっ* まずい！"s, u8"*quaff* Yucky!"s));
        }
        else
        {
            txt(lang(u8" *ごくっ* "s, u8"*quaff*"s));
        }
    }
    sickifcursed(m.efstatus, m.tc, 1);
}

void magic_steal(const magic_data& m, magic_result& result)
{
    if (gdata_executing_immediate_quest_type == 1008
        || gdata_executing_immediate_quest_type == 1010)
    {
        txt(lang(
                 u8"そんなことをしている余裕はない！"s,
                 u8"You have no time for it!"s));
        result.turn_passed = false;
        return;
    }
    if (m.cc == 0)
    {
        if (cdata[0].sp < 50)
        {
            if (cdata[0].sp < rnd(75))
            {
                txt(lang(
                         u8"疲労し過ぎて失敗した！"s,
                         u8"You are too exhausted!"s));
                dmgsp(0, the_ability_db[m.efid]->cost / 2 + 1);
                return;
            }
        }
        dmgsp(
              0,
              rnd(the_ability_db[m.efid]->cost / 2 + 1)
              + the_ability_db[m.efid]->cost / 2 + 1);
    }
    invsubroutine = 1;
    invctrl(0) = 27;
    invctrl(1) = 0;
    snd(100);
    ctrl_inventory();
}

void magic_mount_dismount(const magic_data& m, magic_result& result)
{
    if (m.cc == 0)
    {
        if (cdata[0].sp < 50)
        {
            if (cdata[0].sp < rnd(75))
            {
                txt(lang(
                         u8"疲労し過ぎて失敗した！"s,
                         u8"You are too exhausted!"s));
                dmgsp(0, the_ability_db[m.efid]->cost / 2 + 1);
                return;
            }
        }
        dmgsp(
              0,
              rnd(the_ability_db[m.efid]->cost / 2 + 1)
              + the_ability_db[m.efid]->cost / 2 + 1);
    }
    if (gdata_mount != 0)
    {
        if (m.tc == m.cc)
        {
            int stat =
                cell_findspace(cdata[0].position.x, cdata[0].position.y, 1);
            if (stat == 0)
            {
                txt(lang(
                         u8"降りるスペースがない。"s,
                         u8"There's no place to get off."s));
                return;
            }
            cell_setchara(gdata_mount, rtval, rtval(1));
            txt(lang(
                     name(gdata_mount) + u8"から降りた。"s,
                     u8"You dismount from "s + name(gdata_mount) + u8"."s));
            txtef(9);
            if (jp)
            {
                txt(name(gdata_mount) + u8"「ふぅ」"s,
                    name(gdata_mount) + u8"「乗り心地はよかった？」"s,
                    name(gdata_mount) + u8"「疲れた…」"s,
                    name(gdata_mount) + u8"「またいつでも乗ってね♪」"s);
            }
            if (en)
            {
                txt(name(gdata_mount) + u8" "s + u8"\"Phew.\""s,
                    name(gdata_mount) + u8" "s + u8"\"How was my ride?\""s,
                    name(gdata_mount) + u8" "s + u8"\"Tired...tired...\""s,
                    name(gdata_mount) + u8" "s + u8"\"It was nice.\""s);
            }
            ride_end();
            return;
        }
    }
    if (m.tc >= 16)
    {
        txt(lang(
                 u8"仲間にしか騎乗できない。"s,
                 u8"You can only ride an ally."s));
        return;
    }
    if (cdata[m.tc].is_escorted() == 1
        || cdata[m.tc].is_escorted_in_sub_quest() == 1)
    {
        txt(lang(
                 u8"護衛対象には騎乗できない。"s,
                 u8"You can't ride a client."s));
        return;
    }
    if (m.tc == m.cc)
    {
        if (gdata_mount == 0)
        {
            txt(lang(
                     name(m.cc) + u8"は自分に乗ろうとした。"s,
                     u8"You try to ride yourself."s));
        }
        return;
    }
    if (cdata[m.tc].current_map != 0)
    {
        txt(lang(
                 u8"その仲間はこの場所に滞在中だ。"s,
                 u8"The ally currently stays in this area."s));
        return;
    }
    if (gdata_mount != 0)
    {
        txt(lang(
                 u8"現在"s + name(m.cc) + u8"は"s + name(gdata_mount)
                 + u8"に騎乗している。"s,
                 name(m.cc) + u8" "s + is(m.cc) + u8" currently riding "s
                 + name(gdata_mount) + u8"."s));
    }
    else
    {
        ride_begin(m.tc);
        txtef(9);
        if (jp)
        {
            txt(name(gdata_mount) + u8"「うぐぅ」"s,
                name(gdata_mount) + u8"「ダイエットしてよ…」"s,
                name(gdata_mount) + u8"「いくよ！」"s,
                name(gdata_mount) + u8"「やさしくしてね♪」"s);
        }
        if (en)
        {
            txt(name(gdata_mount) + u8" "s + u8"\"Awww.\""s,
                name(gdata_mount) + u8" "s
                + u8"\"You should go on a diet.\""s,
                name(gdata_mount) + u8" "s + u8"\"Let's roll!\""s,
                name(gdata_mount) + u8" "s + u8"\"Be gentle.\""s);
        }
    }
}

void magic_perform(const magic_data& m, magic_result& result)
{
    if (m.cc != 0)
    {
        result.succeeded = false;
        for (const auto& cnt : items(m.cc))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].skill == 183)
            {
                ci = cnt;
                result.succeeded = true;
                break;
            }
        }
        if (!result.succeeded)
        {
            result.turn_passed = false;
            return;
        }
    }
    if (sdata(183, m.cc) == 0)
    {
        if (is_in_fov(m.cc))
        {
            txt(lang(
                     name(m.cc) + u8"は演奏のやり方を知らない。"s,
                     name(m.cc) + u8" "s + does((cc == 0))
                     + u8"n't know how to play an instrument."s));
            result.turn_passed = false;
            return;
        }
    }
    if (m.cc == 0)
    {
        if (cdata[0].sp < 50)
        {
            if (cdata[0].sp < rnd(75))
            {
                txt(lang(
                         u8"疲労し過ぎて失敗した！"s,
                         u8"You are too exhausted!"s));
                dmgsp(0, the_ability_db[m.efid]->cost / 2 + 1);
                return;
            }
        }
        dmgsp(
              0,
              rnd(the_ability_db[m.efid]->cost / 2 + 1)
              + the_ability_db[m.efid]->cost / 2 + 1);
    }
    // TODO de-globalize
    label_2146();
}

void magic_cook(const magic_data& m, magic_result& result)
{
    if (sdata(184, 0) == 0)
    {
        txt(lang(
                 u8"料理の仕方を知らない。"s, u8"You don't know how to cook."s));
        result.turn_passed = false;
        return;
    }
    cooktool = ci;
    invsubroutine = 1;
    invctrl = 16;
    snd(100);
    {
        int stat = ctrl_inventory();
        if (stat == 0)
        {
            result.turn_passed = false;
            return;
        }
    }
    if (m.cc == 0)
    {
        if (cdata[0].sp < 50)
        {
            if (cdata[0].sp < rnd(75))
            {
                txt(lang(
                         u8"疲労し過ぎて失敗した！"s,
                         u8"You are too exhausted!"s));
                dmgsp(0, the_ability_db[m.efid]->cost / 2 + 1);
                return;
            }
        }
        dmgsp(
              0,
              rnd(the_ability_db[m.efid]->cost / 2 + 1)
              + the_ability_db[m.efid]->cost / 2 + 1);
    }
    // TODO de-globalize
    cook();
}

void magic_fish(const magic_data& m, magic_result& result)
{
    if (sdata(185, 0) == 0)
    {
        txt(lang(
                 u8"釣りの仕方を知らない。"s, u8"You don't know how to fish."s));
        result.turn_passed = false;
        return;
    }
    if (!inv_getspace(0))
    {
        txt(lang(
                 u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
        result.turn_passed = false;
        return;
    }
    if (inv[ci].count == 0)
    {
        txt(lang(
                 u8"釣竿には餌が付いていない。"s,
                 u8"You need a bait to fish."s));
        result.turn_passed = false;
        return;
    }
    result.succeeded = false;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        y = cdata[m.cc].position.y + cnt - 1;
        x = cdata[m.cc].position.x;
        if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
        {
            continue;
        }
        if (chipm(0, map(x, y, 0)) == 3)
        {
            result.succeeded = true;
            break;
        }
    }
    if (!result.succeeded)
    {
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            y = cdata[m.cc].position.y;
            x = cdata[m.cc].position.x + cnt - 1;
            if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
            {
                continue;
            }
            if (chipm(0, map(x, y, 0)) == 3)
            {
                result.succeeded = true;
                break;
            }
        }
    }
    if (!result.succeeded)
    {
        ++msgdup;
        txt(lang(
                 u8"釣りをする場所が見当たらない。"s,
                 u8"This isn't a good place to fish."s));
        update_screen();
        result.turn_passed = false;
        return;
    }
    if (chipm(0, map(cdata[0].position.x, cdata[0].position.y, 0)) == 3)
    {
        txt(lang(
                 u8"水の中からは釣れない。"s,
                 u8"You can't fish while swimming."s));
        update_screen();
        result.turn_passed = false;
        return;
    }
    if (cdata[0].position.x - x > 0)
    {
        cdata[0].direction = 1;
    }
    if (cdata[0].position.x - x < 0)
    {
        cdata[0].direction = 2;
    }
    if (cdata[0].position.y - y > 0)
    {
        cdata[0].direction = 3;
    }
    if (cdata[0].position.y - y < 0)
    {
        cdata[0].direction = 0;
    }
    gdata(35) = cdata[0].direction;
    fishx = x;
    fishy = y;
    addefmap(fishx, fishy, 1, 3);
    if (m.cc == 0)
    {
        if (cdata[0].sp < 50)
        {
            if (cdata[0].sp < rnd(75))
            {
                txt(lang(
                         u8"疲労し過ぎて失敗した！"s,
                         u8"You are too exhausted!"s));
                dmgsp(0, the_ability_db[m.efid]->cost / 2 + 1);
                return;
            }
        }
        dmgsp(
              0,
              rnd(the_ability_db[m.efid]->cost / 2 + 1)
              + the_ability_db[m.efid]->cost / 2 + 1);
    }
    item_separate(ci);
    --inv[ci].count;
    rowactre = 0;
    // TODO de-globalize
    label_2156();
}

void magic_remove_hex(const magic_data& m, magic_result& result, bool is_vanquish)
{
    if (is_cursed(m.efstatus))
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"は悪魔が笑う声を聞いた。"s,
                    name(m.tc) + u8" hear"s + _s(m.tc) + u8" devils laugh."s));
        }
        magic_curse(m, result, false);
        return;
    }
    p = 0;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        i = 16 - cnt - 1;
        if (is_vanquish)
        {
            if (p >= 1)
            {
                break;
            }
        }
        if (the_buff_db[cdata[m.tc].buffs[i].id]->type
            != buff_data::type_t::hex)
        {
            continue;
        }
        if (cdata[m.tc].buffs[i].id == 13)
        {
            continue;
        }
        if (cdata[m.tc].buffs[i].id == 0)
        {
            continue;
        }
        if (rnd(m.efp * 2 + 1) > rnd(cdata[m.tc].buffs[i].power + 1))
        {
            delbuff(m.tc, i);
            ++p;
            --cnt;
            continue;
        }
    }
    addbuff(m.tc, 10, m.efp, 5 + m.efp / 30);
    animeload(11, m.tc);
}

void magic_aura(const magic_data& m, magic_result& result)
{
    txtef(5);
    txt(lang(
             name(m.tc) + u8"は黄金の輝きに包まれた！"s,
             u8"A golden aura wraps "s + name(m.tc) + u8"!"s));
    // TODO de-globalize and move here
    label_2188();
    play_animation(5, m.damage.element);
}

void magic_create_material(const magic_data& m, magic_result& result)
{
    if (m.tc >= 16)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (!is_cursed(m.efstatus))
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
    autosave = 1 * (gdata_current_map != 35);
    for (int cnt = 0,
             cnt_end =
             (rnd(3) + 3 + (m.efstatus == curse_state_t::blessed) * 6);
         cnt < cnt_end;
         ++cnt)
    {
        atxspot = 19;
        if (!is_cursed(m.efstatus))
        {
            p = random_material(m.efp / 10, m.efp / 50);
        }
        else
        {
            p = 0;
        }
        matgetmain(p, 1);
    }
}

void magic_heal(const magic_data& m, magic_result& result, heal_t type)
{
    if (type == heal_t::light)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"の傷はふさがった。"s,
                    name(m.tc) + u8" "s + is(m.tc)
                    + u8" slightly healed."s));
        }
    }
    if (type == heal_t::critical || type == heal_t::healing_touch)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"は回復した。"s,
                    name(m.tc) + u8" "s + is(m.tc) + u8" healed."s));
        }
    }
    if (type == heal_t::cure_of_eris)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"の身体に生命力がみなぎった。"s,
                    name(m.tc) + u8" "s + is(m.tc)
                    + u8" greatly healed."s));
        }
    }
    if (type == heal_t::cure_of_jure)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"は完全に回復した。"s,
                    name(m.tc) + u8" "s + is(m.tc)
                    + u8" completely healed."s));
        }
    }
    magic_do_heal(m);
    if (m.efstatus == curse_state_t::blessed)
    {
        healcon(m.tc, 12, 5 + rnd(5));
    }
    sickifcursed(m.efstatus, m.tc, 3);
    play_animation(5, m.damage.element);
}

// TODO also heals mount because tc is an array...?
void magic_do_heal(const magic_data& m)
{
    elona_vector1<int> to_heal;
    int subloop = 0;
    subloop = 1;
    if (gdata_mount != 0)
    {
        if (m.tc == gdata_mount || m.tc == 0)
        {
            subloop = 2;
            if (m.tc == gdata_mount)
            {
                to_heal(0) = gdata_mount;
                to_heal(1) = 0;
            }
            else
            {
                to_heal(0) = 0;
                to_heal(1) = gdata_mount;
            }
        }
    }
    for (int cnt = 0, cnt_end = (subloop); cnt < cnt_end; ++cnt)
    {
        healhp(to_heal(cnt), roll(m.damage));
        healcon(to_heal(cnt), 6);
        healcon(to_heal(cnt), 1, 50);
        healcon(to_heal(cnt), 5, 50);
        healcon(to_heal(cnt), 7, 30);
        healcon(to_heal(cnt), 9, 20);
        healsan(to_heal(cnt), 1);
    }
}

void magic_special_attack(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.cc))
    {
        if (m.cc == 0)
        {
            txt(lang(
                    name(m.cc) + u8"は"s
                    + i18n::_(
                        u8"ability",
                        std::to_string(m.efid),
                        u8"name")
                    + u8"の"s
                    + i18n::_(
                        u8"ui",
                        u8"cast_style",
                        u8"_"s
                        + cdata[m.cc].special_attack_type),
                    name(m.cc) + u8" cast "s
                    + i18n::_(
                        u8"ability",
                        std::to_string(m.efid),
                        u8"name")
                    + u8"."s));
        }
        else
        {
            txt(lang(
                    name(m.cc) + u8"は"s
                    + i18n::_(
                        u8"ui",
                        u8"cast_style",
                        u8"_"s
                        + cdata[m.cc].special_attack_type),
                    name(m.cc) + ""s
                    + i18n::_(
                        u8"ui",
                        u8"cast_style",
                        u8"_"s
                        + cdata[m.cc]
                        .special_attack_type)));
        }
    }
}

void magic_suck_blood(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.cc))
    {
        if (m.tc >= 16)
        {
            gdata(809) = 2;
            txt(lang(
                    aln(m.cc) + name(m.tc) + u8"の血を吸い"s,
                    name(m.cc) + u8" suck"s + _s(m.cc) + u8" "s
                    + name(m.tc) + your(m.tc) + u8" blood and"s));
        }
        else
        {
            txt(lang(
                    name(m.cc) + u8"に血を吸われた。"s,
                    name(m.cc) + u8" suck"s + _s(m.cc) + u8" "s
                    + name(m.tc) + your(m.tc) + u8" blood."s));
        }
    }
}

void magic_touch(const magic_data& m, magic_result& result)
{
    if (m.tc >= 16)
    {
        gdata(809) = 2;
        txt(lang(
                aln(m.cc) + name(m.tc) + u8"を"s + elename(m)
                + _melee(2, cdata[m.cc].melee_attack_type)
                + u8"で"s
                + _melee(0, cdata[m.cc].melee_attack_type),
                name(m.cc) + u8" touch"s + _s(m.cc) + u8" "s + name(m.tc)
                + u8" with "s + his(m.cc) + u8" "s + elename(m)
                + u8" "s
                + _melee(2, cdata[m.cc].melee_attack_type)
                + u8" and"s));
    }
    else
    {
        txt(lang(
                name(m.tc) + u8"は"s + name(m.cc) + u8"に"s
                + elename(m)
                + _melee(2, cdata[m.cc].melee_attack_type)
                + u8"で"s
                + _melee(1, cdata[m.cc].melee_attack_type),
                name(m.cc) + u8" touch"s + _s(m.cc) + u8" "s + name(m.tc)
                + u8" with "s + his(m.cc) + u8" "s + elename(m)
                + u8" "s
                + _melee(2, cdata[m.cc].melee_attack_type)
                + u8"."s));
    }
}

void magic_disassembly(const magic_data& m, magic_result& result)
{
    txt(lang(
            u8"「余分な機能は削除してしまえ」"s, u8"\"Delete.\""s));
    cdata[m.tc].hp = cdata[m.tc].max_hp / 12 + 1;
}

void magic_touch_of_fear(const magic_data& m, magic_result& result)
{
    dmghp(m.tc, roll(m.damage), m.cc, m.damage.element, m.damage.element_power);
    dmgcon(m.tc, 6, m.damage.element_power);
}

void magic_touch_of_sleep(const magic_data& m, magic_result& result)
{
    dmghp(m.tc, roll(m.damage), m.cc, m.damage.element, m.damage.element_power);
    dmgcon(m.tc, 2, m.damage.element_power);
}

void magic_hunger(const magic_data& m, magic_result& result)
{
    dmghp(m.tc, roll(m.damage), m.cc, m.damage.element, m.damage.element_power);
    cdata[m.tc].nutrition -= 800;
    if (is_in_fov(m.tc))
    {
        txtef(8);
        txt(lang(
                 name(m.tc) + u8"はお腹が減った。"s,
                 u8"Suddenly "s + name(m.tc) + u8" feel"s + _s(m.tc)
                 + u8" hungry."s));
    }
    get_hungry(m.tc);
}

void magic_weaken(const magic_data& m, magic_result& result)
{
    dmghp(m.tc, roll(m.damage), m.cc, m.damage.element, m.damage.element_power);
    p = rnd(10);
    if ((cdata[m.tc].quality >= 4 && rnd(4))
        || encfind(m.tc, 60010 + p) != -1)
    {
        p = -1;
    }
    if (p != -1)
    {
        i = sdata.get(10 + p, m.tc).original_level
            - cdata[m.tc].attr_adjs[p];
        if (i > 0)
        {
            i = i * m.efp / 2000 + 1;
            cdata[m.tc].attr_adjs[p] -= i;
        }
        if (is_in_fov(m.tc))
        {
            txtef(8);
            txt(lang(
                     name(m.tc) + u8"は弱くなった。"s,
                     name(m.tc) + u8" "s + is(m.tc) + u8" weakened."s));
        }
        refresh_character(m.tc);
    }
}

void magic_flying(const magic_data& m, magic_result& result)
{
    if (m.cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 6;
    snd(100);
    {
        int stat = ctrl_inventory();
        if (stat == 1)
        {
            autosave = 1 * (gdata_current_map != 35);
            animeload(8, m.cc);
            if (!is_cursed(m.efstatus))
            {
                if (inv[ci].weight > 0)
                {
                    inv[ci].weight = clamp(
                                           inv[ci].weight * (100 - m.efp / 10) / 100,
                                           1,
                                           inv[ci].weight);
                    if (inv[ci].pv > 0)
                    {
                        inv[ci].pv -= inv[ci].pv / 10 + 1
                            + (m.efstatus != curse_state_t::blessed);
                    }
                    if (inv[ci].damage_bonus > 0)
                    {
                        inv[ci].damage_bonus -= inv[ci].damage_bonus / 10
                            + 1 + (m.efstatus != curse_state_t::blessed);
                    }
                }
                txt(lang(
                         ""s + itemname(ci, 1)
                         + u8"は羽が生えたように軽くなった。"s,
                         itemname(ci, 1) + u8" becomes light as a feather."s));
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
                txt(lang(
                         ""s + itemname(ci, 1) + u8"はずしりと重くなった。"s,
                         itemname(ci, 1) + u8" becomes heavy."s));
            }
            refresh_burden_state();
        }
        else
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            result.obvious = false;
        }
    }
    refresh_character(m.cc);
}

void magic_mutate(const magic_data& m, magic_result& result, mutation_t type)
{
    if (m.tc != 0)
    {
        magic_change_creature(m, result);
        return;
    }
    if (type == mutation_t::insane_glance)
    {
        txt(lang(
                name(m.cc) + u8"は"s + name(m.tc)
                + u8"を気の狂いそうな眼差しで見た。"s,
                name(m.cc) + u8" cast"s + _s(m.cc) + u8" an insane glance on "s
                + name(m.tc) + u8"."s));
        if (rnd(3))
        {
            return;
        }
    }
    if (m.tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    if (encfind(m.tc, 33) != -1)
    {
        if (rnd(5))
        {
            txt(lang(
                    u8"あなたは変異を受け付けなかった。"s,
                    u8"You resist the threat of mutation."s));
            return;
        }
    }
    magic_do_mutation(m, result, type);
}

void magic_do_mutation(const magic_data& m, magic_result& result, mutation_t type)
{
    result.succeeded = false;
    p = 1;
    if (m.efid == 1144)
    {
        p = 2 + rnd(3);
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            int tid = rnd(45);
            int stat = get_trait_info(0, tid);
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
            if (is_cursed(m.efstatus))
            {
                if (p == 1)
                {
                    continue;
                }
            }
            else if (p == -1)
            {
                if (m.efstatus == curse_state_t::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        continue;
                    }
                }
                if (m.efid == 1144)
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
            result.succeeded = true;
            break;
        }
    }
    if (!result.succeeded)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
    refresh_character(0);
}

void magic_cure_mutation(const magic_data& m, magic_result& result)
{
    if (m.tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    if (is_cursed(m.efstatus))
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
        }
        magic_do_mutation(m, result, mutation_t::cursed_cure_mutation);
        return;
    }
    result.succeeded = false;
    for (int cnt = 0,
             cnt_end = cnt
             + (1 + (m.efstatus == curse_state_t::blessed)
                + (!is_cursed(m.efstatus)) + rnd(2));
         cnt < cnt_end;
         ++cnt)
    {
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            int tid = rnd(217);
            int stat = get_trait_info(0, tid);
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
            result.succeeded = true;
            break;
        }
    }
    if (!result.succeeded)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
    refresh_character(0);
}

void magic_identify(const magic_data& m, magic_result& result)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl = 13; // identify
    snd(100);
    ctrl_inventory(m.efp);
}

void magic_resurrection(const magic_data& m, magic_result& result)
{
    if (mdata(6) == 1)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (is_cursed(m.efstatus))
    {
        txt(lang(
                u8"冥界から死霊が呼び出された！"s,
                u8"Hoards of undead raise from the hell!"s));
        for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata[0].level), calcfixlv(3));
            fltn(u8"undead"s);
            characreate(-1, 0, cdata[0].position.x, cdata[0].position.y);
        }
        result.obvious = false;
        return;
    }
    allyctrl = 2;
    {
        int stat = label_1980();
        if (stat == -1)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            result.obvious = false;;
            return;
        }
        if (bonus < rnd(100))
        {
            if (is_in_fov(m.cc))
            {
                txt(lang(
                        name(m.cc) + u8"の力は冥界に及ばなかった。"s,
                        name(m.cc) + your(m.cc)
                        + u8" prayer doesn't reach the underworld."s));
            }
            return;
        }
        rc = stat;
    }
    label_1538();
    cxinit = cdata[m.cc].position.x;
    cyinit = cdata[m.cc].position.y;
    place_character();
    cdata[rc].current_map = 0;
    txtef(5);
    txt(cnven(cdatan(0, rc))
        + lang(
            u8"は復活した！"s,
            (u8" "s + have(rc) + u8" been resurrected!"s)));
    txt(lang(u8"「ありがとう！」"s, u8"\"Thanks!\""s));
    animode = 100 + rc;
    play_animation(19, m.damage.element);
    snd(120);
    cdata[rc].emotion_icon = 317;
    if (m.cc == 0)
    {
        modimp(rc, 15);
        if (rc >= 16)
        {
            modify_karma(0, 2);
        }
    }
}

void magic_vanquish_curse(const magic_data& m, magic_result& result)
{
    if (m.efstatus == curse_state_t::none)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"の装備品は白い光に包まれた。"s,
                    name(m.tc) + u8" "s + your(m.tc)
                    + u8" equipment are surrounded by a white aura."s));
        }
    }
    if (m.efstatus == curse_state_t::blessed)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"は聖なる光に包み込まれた。"s,
                    name(m.tc) + u8" "s + is(m.tc)
                    + u8" surrounded by a holy aura."s));
        }
    }
    if (is_cursed(m.efstatus))
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"は悪魔が笑う声を聞いた。"s,
                    name(m.tc) + u8" hear"s + _s(m.tc) + u8" devils laugh."s));
        }
        magic_curse(m, result, false);
        return;
    }
    p(1) = 0;
    p(2) = 0;
    for (const auto& cnt : items(m.tc))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (!is_cursed(inv[cnt].curse_state))
        {
            continue;
        }
        ci = cnt;
        p = 0;
        if (inv[ci].curse_state == curse_state_t::cursed)
        {
            p = rnd(200) + 1;
        }
        if (inv[ci].curse_state == curse_state_t::doomed)
        {
            p = rnd(1000) + 1;
        }
        if (m.efstatus == curse_state_t::blessed)
        {
            p = p / 2 + 1;
        }
        else if (inv[ci].body_part == 0)
        {
            continue;
        }
        if (p != 0)
        {
            if (m.efp >= p)
            {
                ++p(1);
                inv[ci].curse_state = curse_state_t::none;
                item_stack(m.tc, ci, 1);
            }
            else
            {
                ++p(2);
            }
        }
    }
    if (m.efstatus == curse_state_t::blessed)
    {
        if (p(1) != 0)
        {
            if (is_in_fov(m.tc))
            {
                txt(lang(
                        u8"幾つかのアイテムが浄化された。"s,
                        u8"The aura uncurses some "s + his(m.tc) + u8" stuff."s));
            }
        }
    }
    else if (p(1) != 0)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    u8"身に付けている装備の幾つかが浄化された。"s,
                    u8"The aura uncurses some of "s + his(m.tc)
                    + u8" equipment."s));
        }
    }
    if (p(2) != 0)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    u8"幾つかのアイテムは抵抗した。"s,
                    u8"Several items resist the aura and remain cursed."s));
        }
    }
    if (p(1) == 0 && p(2) == 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
    else
    {
        animeload(10, m.tc);
    }
    refresh_character(m.tc);
}

void magic_oracle(const magic_data& m, magic_result& result)
{
    if (m.tc >= 16)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    if (is_cursed(m.efstatus))
    {
        artifactlocation.clear();
        txt(lang(
                u8"何かがあなたの耳元でささやいたが、あなたは聞き取ることができなかった。"s,
                u8"You hear a sepulchral whisper but the voice is too small to distinguish a word."s));
        return;
    }
    if (artifactlocation.empty())
    {
        txt(lang(
                u8"まだ特殊なアイテムは生成されていない。"s,
                u8"No artifacts have been generated yet."s));
    }
    else
    {
        range::for_each(
            artifactlocation, [](const auto& line) { txt(cnven(line)); });
        artifactlocation.clear();
    }
}

void magic_gain_spell(const magic_data& m, magic_result& result)
{
    if (m.tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    result.succeeded = false;
    for (int cnt = 0, cnt_end = (1 + (m.efstatus == curse_state_t::blessed));
         cnt < cnt_end;
         ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 2000; ++cnt)
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
            if (!is_cursed(m.efstatus))
            {
                if (the_ability_db[p])
                {
                    if (cnt2 == 0)
                    {
                        s = lang(u8"突然、"s, u8"Suddenly, "s);
                    }
                    else
                    {
                        s = lang(u8"さらに、"s, u8"Furthermore, "s);
                    }
                    skillgain(0, p, 1, 200);
                    txtef(2);
                    txt(lang(
                            s + name(0) + u8"は"s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8"の魔法の知識を得た。"s,
                            s + u8"you gain knowledge of a spell, "s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8"."s));
                    snd(24);
                    result.succeeded = true;
                    break;
                }
            }
            else
            {
                p = p - 400;
                if (spell(p) > 0)
                {
                    spell(p) = 0;
                    txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
                    txtef(3);
                    txt(lang(
                            u8"突然、"s + name(0) + u8"は"s
                            + i18n::_(
                                u8"ability",
                                std::to_string(p + 400),
                                u8"name")
                            + u8"の魔法の知識を失った。"s,
                            u8"Suddenly, you lose knowledge of a spell, "s
                            + i18n::_(
                                u8"ability",
                                std::to_string(p + 400),
                                u8"name")
                            + u8"."s));
                    snd(117);
                    animeload(14, 0);
                    result.succeeded = true;
                    break;
                }
            }
        }
    }
    if (!result.succeeded)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    autosave = 1 * (gdata_current_map != 35);
}

void magic_descent(const magic_data& m, magic_result& result)
{
    if (m.efstatus == curse_state_t::blessed)
    {
        cdata[m.tc].experience = cdata[m.tc].required_experience;
        r2 = 0;
        gain_level(m.tc);
        if (is_in_fov(m.tc))
        {
            snd(60);
        }
    }
    else
    {
        if (cdata[m.tc].level <= 1)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
            result.obvious = false;
            return;
        }
        --cdata[m.tc].level;
        cdata[m.tc].experience = 0;
        refresh_required_exp(m.tc);
        txtef(8);
        txt(lang(
                name(m.tc) + u8"のレベルが下がった…"s,
                name(m.tc) + u8" lose"s + _s(m.tc) + u8" a level..."s));
    }
    if (is_cursed(m.efstatus))
    {
        txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
        for (int cnt = 10; cnt < 50; ++cnt)
        {
            if (rnd(3) == 0)
            {
                if (cnt <= 17)
                {
                    if (sdata(cnt, m.tc) != 0)
                    {
                        skillexp(cnt, m.tc, -1000);
                    }
                }
            }
        }
        animeload(8, m.tc);
    }
    refresh_character(m.tc);
}

void magic_gain_attribute(const magic_data& m, magic_result& result)
{
    for (int cnt = 0;; ++cnt)
    {
        await();
        p = rnd(300) + 100;
        if (the_ability_db[p])
        {
            if (!is_cursed(m.efstatus))
            {
                if (cnt < efstatusfix(m.efstatus, 0, 0, 100, 2000))
                {
                    if (sdata(p, m.tc) != 0)
                    {
                        continue;
                    }
                }
                skillgain(m.tc, p, 1);
                if (is_in_fov(m.tc))
                {
                    snd(24);
                    txtef(2);
                    txt(lang(
                            ""s + name(m.tc) + u8"は"s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8"の技術を獲得した！"s,
                            name(m.tc) + u8" gain"s + _s(m.tc) + u8" a skill of "s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8"!"s));
                }
                break;
            }
            else
            {
                if (sdata(p, m.tc) == 0)
                {
                    continue;
                }
                if (is_in_fov(m.tc))
                {
                    snd(38);
                    txt(lang(u8"これは呪われている！"s, u8"It's cursed!"s));
                }
                skillexp(p, m.tc, -1000);
                break;
            }
        }
    }
    refresh_character(m.tc);
    autosave = 1 * (gdata_current_map != 35);
}

void magic_faith(const magic_data& m, magic_result& result)
{
    if (tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (cdata[0].god_id.empty())
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (is_cursed(m.efstatus))
    {
        txt(lang(
                u8"あなたの神はあなたの信仰に疑問を抱いた。"s,
                u8"Your god doubts your faith."s));
        snd(117);
        animeload(14, 0);
        skillexp(181, 0, -1000);
        return;
    }
    if (cdata[0].god_id.empty())
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
    else
    {
        txtef(2);
        txt(lang(
                u8"あなたは"s + i18n::_(u8"god", cdata[0].god_id, u8"name")
                + u8"の暖かい眼差しを感じた。"s,
                u8"You feel as if "s
                + i18n::_(u8"god", cdata[0].god_id, u8"name")
                + u8" is watching you."s));
        if (m.efstatus == curse_state_t::blessed)
        {
            txt(lang(
                    u8"空から三つ葉のクローバーがふってきた。"s,
                    u8"A three-leaved falls from the sky."s));
        }
        animode = 100 + tc;
        play_animation(19, m.damage.element);
        snd(120);
        cdata[0].praying_point += 500;
        modpiety(75);
        skillexp(
            181,
            0,
            1000 + (m.efstatus == curse_state_t::blessed) * 750,
            6,
            1000);
    }
    refresh_character(tc);
}

void magic_growth(const magic_data& m, magic_result& result)
{
    for (int cnt = 0, cnt_end = (1 + (m.efstatus == curse_state_t::blessed));
         cnt < cnt_end;
         ++cnt)
    {
        int cnt2 = cnt;
        while (1)
        {
            await();
            p = rnd(300) + 100;
            if (the_ability_db[p])
            {
                if (sdata.get(p, m.tc).original_level == 0)
                {
                    continue;
                }
                modify_potential(
                    m.tc, p, m.efp * efstatusfix(m.efstatus, -4, -2, 5, 5) / 100);
                if (cnt2 == 0)
                {
                    s = lang(""s, u8"The "s);
                }
                else
                {
                    s = lang(u8"さらに"s, u8"Furthermore, the "s);
                }
                if (!is_cursed(m.efstatus))
                {
                    if (is_in_fov(m.tc))
                    {
                        snd(24);
                        txtef(2);
                        txt(lang(
                                s + ""s + name(m.tc) + u8"の"s
                                + i18n::_(
                                    u8"ability",
                                    std::to_string(p),
                                    u8"name")
                                + u8"の技術の潜在能力が上昇した。"s,
                                s + u8"potential of "s + name(m.tc) + your(m.tc)
                                + u8" "s
                                + i18n::_(
                                    u8"ability",
                                    std::to_string(p),
                                    u8"name")
                                + u8" skill increases."s));
                    }
                }
                else if (is_in_fov(m.tc))
                {
                    snd(117);
                    txtef(3);
                    txt(lang(
                            ""s + name(m.tc) + u8"の"s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8"の技術の潜在能力が減少した。"s,
                            u8"The potential of "s + name(m.tc) + your(m.tc)
                            + u8" "s
                            + i18n::_(
                                u8"ability", std::to_string(p), u8"name")
                            + u8" skill decreases."s));
                }
                break;
            }
        }
    }
    refresh_character(m.tc);
    autosave = 1 * (gdata_current_map != 35);
}

void magic_failed_altar_takeover(const magic_data& m, magic_result& result)
{
    i = rnd(10) + 10;
    skillexp(i, tc, efstatusfix(m.efstatus, -2000, -2000, -1000, -250));
    play_animation(6, m.damage.element);
    refresh_character(tc);
}

void magic_hermes_blood(const magic_data& m, magic_result& result)
{
    txt(lang(
            name(tc) + u8"の血は沸きあがるように熱くなった。"s,
            name(tc) + your(tc) + u8" blood burns and a new strength fills "s
            + his(tc) + u8" body!"s));
    skillexp(18, tc, efstatusfix(m.efstatus, -4000, -1000, 8000, 12000));
    if (m.efstatus == curse_state_t::blessed)
    {
        modify_potential(tc, 18, 15);
        txtef(2);
        txt(lang(u8"あつつ！"s, u8"It really burns!"s));
    }
    refresh_character(tc);
}

void magic_gain_potential(const magic_data& m, magic_result& result)
{
    if (m.efstatus == curse_state_t::blessed)
    {
        for (int cnt = 10; cnt < 18; ++cnt)
        {
            modify_potential(
                tc, cnt, rnd(sdata.get(cnt, tc).potential / 20 + 3) + 1);
        }
        txt(lang(
                name(tc) + u8"の全ての能力の潜在能力が上昇した。"s,
                name(tc) + your(tc)
                + u8" potential of every attribute expands."s));
        animode = 100 + tc;
        play_animation(19, m.damage.element);
        snd(61);
    }
    else
    {
        i = rnd(8) + 10;
        const auto valn = i18n::_(u8"ability", std::to_string(i), u8"name");
        if (m.efstatus == curse_state_t::none)
        {
            txt(lang(
                    name(tc) + u8"の"s + valn + u8"の潜在能力が上昇した。"s,
                    name(tc) + your(tc) + u8" potential of "s + valn
                    + u8" expands."s));
            modify_potential(
                tc, i, rnd(sdata.get(i, tc).potential / 10 + 10) + 1);
            snd(24);
        }
        else
        {
            txt(lang(
                    name(tc) + u8"の"s + valn + u8"の潜在能力が減少した。"s,
                    name(tc) + your(tc) + u8" potential of "s + valn
                    + u8" decreases."s));
            modify_potential(
                tc,
                i,
                (rnd(sdata.get(i, tc).potential / 10 + 10) + 1) * -1);
            snd(117);
        }
    }
    autosave = 1 * (gdata_current_map != 35);
}

void magic_vanquish(const magic_data& m, magic_result& result)
{
    if (tc < 57)
    {
        return;
    }
    if (cdata[tc].quality >= 4)
    {
        return;
    }
    txt(lang(
            name(tc) + u8"は消え去った。"s,
            name(tc) + u8" vanish"s + _s(tc) + u8"."s));
    chara_vanquish(tc);
}

void magic_mapping(const magic_data& m, magic_result& result, bool is_sense_object)
{
    if (tc >= 16)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    p = 1;
    if (is_sense_object)
    {
        p = 2;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                p = dist(cdata[tc].position.x, cdata[tc].position.y, x, y);
                if (is_cursed(m.efstatus))
                {
                    if (is_sense_object)
                    {
                        map(x, y, 5) = 0;
                    }
                    else
                    {
                        map(x, y, 2) = tile_default;
                    }
                    continue;
                }
                if (p < 7 || rnd(m.efp + 1) > rnd(p * 8 + 1)
                    || m.efstatus == curse_state_t::blessed)
                {
                    if (is_sense_object)
                    {
                        if (map(x, y, 6) != 0 || map(x, y, 5) != 0)
                        {
                            map(x, y, 2) = map(x, y, 0);
                        }
                    }
                    else
                    {
                        map(x, y, 2) = map(x, y, 0);
                    }
                }
            }
        }
    }
    if (is_cursed(m.efstatus))
    {
        txt(lang(
                u8"あれ…？あなたは軽い記憶障害を受けた。"s,
                u8"Hmm? You suffer minor memory defect."s));
    }
    else
    {
        if (is_sense_object)
        {
            txt(lang(
                    name(tc) + u8"周囲の物質を感知した。"s,
                    name(tc) + u8" sense"s + _s(tc) + u8" nearby objects."s));
        }
        else
        {
            txt(lang(
                    name(tc) + u8"は周囲の地形を察知した。"s,
                    name(tc) + u8" sense"s + _s(tc) + u8" nearby locations."s));
        }
    }
    animeload(10, tc);
    update_minimap();
    update_screen();
}

void magic_vorpal(const magic_data& m, magic_result& result)
{
    if (cdata[m.tc].hp > cdata[m.tc].max_hp / 8)
    {
        return;
    }
    if (is_in_fov(m.tc))
    {
        snd(105);
        txtef(3);
        txt(lang(u8" *ブシュッ* "s, u8"*Gash*"s));
        if (m.tc >= 16)
        {
            gdata(809) = 2;
            txt3rd = 1;
            txt(lang(
                    name(m.cc) + u8"は"s + name(m.tc) + u8"の首をちょんぎり"s,
                    name(m.cc) + u8" cut"s + _s(m.cc) + u8" "s + name(m.tc) + your(m.tc)
                    + u8" head and"s));
        }
        else
        {
            txt(lang(
                    name(m.cc) + u8"は"s + name(m.tc) + u8"の首をちょんぎった。"s,
                    name(m.cc) + u8" cut"s + _s(m.cc) + u8" "s + name(m.tc) + your(m.tc)
                    + u8" head."s));
        }
    }
    dmghp(m.tc, cdata[m.tc].max_hp, m.cc, element_t::vorpal);
}

void magic_restore(const magic_data& m, magic_result& result, bool is_restore_body)
{
    if (is_restore_body)
    {
        if (is_in_fov(tc))
        {
            if (is_cursed(m.efstatus))
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
            if (m.efstatus == curse_state_t::blessed)
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
    else
    {
        if (is_in_fov(tc))
        {
            if (is_cursed(m.efstatus))
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
            if (m.efstatus == curse_state_t::blessed)
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
    for (int cnt = 0;; ++cnt)
    {
        if (p(cnt) == -1)
        {
            break;
        }
        const auto attr = p(cnt) - 10;
        if (is_cursed(m.efstatus))
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
        if (m.efstatus == curse_state_t::blessed)
        {
            cdata[tc].attr_adjs[attr] =
                sdata.get(p(cnt), tc).original_level / 10 + 5;
        }
    }
    refresh_character(tc);
}

void magic_wish(const magic_data& m, magic_result& result)
{
    what_do_you_wish_for();
    screenupdate = -1;
    label_1416();
}

void magic_escape(const magic_data& m, magic_result& result)
{
    if (tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (gdata_is_returning_or_escaping != 0)
    {
        txt(lang(
                u8"脱出を中止した。"s,
                u8"The air around you gradually loses power."s));
        gdata_is_returning_or_escaping = 0;
    }
    else
    {
        int stat = label_2080();
        if (stat == 1)
        {
            txt(lang(
                    u8"依頼請負中の帰還は法律で禁止されている。それでも帰還する？"s,
                    u8"Returning while taking a quest if forbidden. Are you sure you want to return?"s));
            ELONA_YES_NO_PROMPT();
            rtval = show_prompt(promptx, prompty, 160);
            if (rtval != 0)
            {
                return;
            }
        }
        txt(lang(
                u8"周囲の大気がざわめきだした。"s,
                u8"The air around you becomes charged."s));
        if (adata(16, gdata_current_map) == 8)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    txt(lang(
                            u8"このままダンジョンを出ると、この階のクエストは達成できない…"s,
                            u8"The lord of the dungeon might disappear if you escape now."s));
                }
            }
        }
        gdata_destination_map = gdata(850);
        gdata_destination_dungeon_level = 1;
        if (is_cursed(m.efstatus))
        {
            if (rnd(3) == 0)
            {
                gdata_destination_map = 41;
                gdata_destination_dungeon_level = 1;
            }
        }
        gdata_is_returning_or_escaping = 5 + rnd(10);
    }
}

void magic_return(const magic_data& m, magic_result& result)
{
    if (tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (gdata_is_returning_or_escaping != 0)
    {
        txt(lang(
                u8"帰還を中止した。"s,
                u8"The air around you gradually loses power."s));
        gdata_is_returning_or_escaping = 0;
    }
    else
    {
        label_2081();
        if (is_cursed(m.efstatus))
        {
            if (rnd(3) == 0)
            {
                gdata_destination_map = 41;
                gdata_destination_dungeon_level = 1;
            }
        }
    }
}

void magic_restore_mana(const magic_data& m, magic_result& result)
{
    healmp(m.tc, m.efp / 2 + rnd((m.efp / 2 + 1)));
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"のマナが回復した。"s,
                name(m.tc) + your(m.tc) + u8" mana is restored."s));
        play_animation(5, m.damage.element);
    }
}

void magic_absorb_mana(const magic_data& m, magic_result& result)
{
    healmp(m.tc, roll(m.damage));
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"は周囲からマナを吸い取った。"s,
                name(m.tc) + u8" absorb"s + _s(m.tc) + u8" mana from the air."s));
        play_animation(5, m.damage.element);
    }
}

void magic_poison(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"は毒を浴びた！"s,
                name(m.tc) + u8" "s + is(m.tc) + u8" hit by poison!"s));
    }
    if (cdata[m.tc].is_pregnant())
    {
        cdata[m.tc].is_pregnant() = false;
        if (is_in_fov(m.tc))
        {
            txt(lang(
                    name(m.tc) + u8"の体内のエイリアンは溶けた。"s,
                    name(m.tc) + your(m.tc) + u8" alien children melt in "s
                    + his(m.tc) + u8" stomach."s));
        }
    }
    dmgcon(m.tc, 1, m.efp);
}

void magic_dye(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"は墨を浴びた！"s,
                u8"Ink squirts into "s + name(m.tc) + your(m.tc) + u8" face!"s));
    }
    dmgcon(m.tc, 4, m.efp);
}

void magic_confusion(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"はひどい頭痛におそわれた！"s,
                u8"A foul stench floods "s + name(m.tc) + your(m.tc)
                + u8" nostrils!"s));
    }
    dmgcon(m.tc, 5, m.efp);
}

void magic_potion_numbness(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"は痺れた！"s,
                name(m.tc) + u8" get"s + _s(m.tc) + u8" numbness!"s));
    }
    dmgcon(m.tc, 3, m.efp);
}

void magic_juice(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                name(m.tc) + u8"は甘い液体を浴びた！"s,
                u8"Strange sweet liquid splashes onto "s + name(m.tc) + u8"!"s));
    }
    dmgcon(m.tc, 2, m.efp);
}

void magic_curse(const magic_data& m, magic_result& result, bool is_attack)
{
    if (is_attack)
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                     name(m.cc) + u8"は"s + name(m.tc)
                     + u8"を指差して呪いの言葉を呟いた。"s,
                     name(m.cc) + u8" point"s + _s(m.cc) + u8" "s + name(m.tc)
                     + u8" and mutter"s + _s(m.cc) + u8" a curse."s));
        }
    }
    p = 75 + sdata(19, m.tc);
    if (encfind(m.tc, 43) != -1)
    {
        p += encfind(m.tc, 43) / 2;
    }
    if (rnd(p) > m.efp / 2 + (is_cursed(m.efstatus)) * 100)
    {
        return;
    }
    if (m.tc < 16)
    {
        if (rnd(3))
        {
            if (trait(42))
            {
                txt(lang(
                         u8"あなたは祈祷を捧げ呪いのつぶやきを無効にした。"s,
                         u8"Your prayer nullifies the curse."s));
                return;
            }
        }
    }
    i = 0;
    for (int cnt = 100; cnt < 130; ++cnt)
    {
        if (cdata_body_part(m.tc, cnt) % 10000 == 0)
        {
            continue;
        }
        p(i) = cdata_body_part(m.tc, cnt) % 10000 - 1;
        if (inv[p(i)].curse_state == curse_state_t::blessed)
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
            p = get_random_inv(m.tc);
            if (inv[p].number == 0)
            {
                continue;
            }
            if (inv[p].curse_state == curse_state_t::blessed)
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
        if (inv[i].curse_state == curse_state_t::cursed)
        {
            inv[i].curse_state = curse_state_t::doomed;
        }
        else
        {
            inv[i].curse_state = curse_state_t::cursed;
        }
        if (is_in_fov(m.tc))
        {
            txt(lang(
                     name(m.tc) + u8"の"s + valn + u8"は黒く輝いた。"s,
                     name(m.tc) + your(m.tc) + u8" "s + valn + u8" glows black."s));
        }
        refresh_character(m.tc);
        snd(117);
        animeload(14, m.tc);
        item_stack(m.tc, i, 1);
    }
    else
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
}

void magic_weaken_resistance(const magic_data& m, magic_result& result)
{
    result.succeeded = false;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p = rnd(11) + 50;
        if (sdata.get(p, tc).original_level >= 150)
        {
            ++f;
            resistmod(tc, p, 50 * -1);
            if (f >= m.efp / 100)
            {
                break;
            }
        }
    }
    if (!result.succeeded)
    {
        txt(lang(u8"何も起こらなかったようだ。"s, u8"Nothing happens."s));
        result.obvious = false;
    }
    else
    {
        snd(38);
    }
    refresh_character(tc);
}

void magic_ally(const magic_data& m, magic_result& result, ally_t type)
{
    if (cc != 0 && cc < 16)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    flt(cdata[0].level / 2 + 5, 3);
    p = 0;
    if (rnd(3) == 0)
    {
        fltn(u8"man"s);
    }
    if (type == ally_t::younger_cat_sister)
    {
        txt(lang(
                 u8"なんと、あなたには生き別れた血の繋がっていないぬこの妹がいた！"s,
                 u8"How...! You suddenly get a younger cat sister!"s));
        p = 210;
    }
    if (type == ally_t::younger_sister)
    {
        txt(lang(
                 u8"なんと、あなたには生き別れた血の繋がっていない妹がいた！"s,
                 u8"How...! You suddenly get a younger sister!"s));
        p = 176;
    }
    if (type == ally_t::young_lady)
    {
        txt(lang(
                 u8"お嬢さんが空から降ってきた！"s,
                 u8"A young lady falls from the sky."s));
        p = 211;
    }
    novoidlv = 1;
    characreate(56, p, -3, 0);
    rc = 56;
    new_ally_joins();
}

void magic_domination(const magic_data& m, magic_result& result)
{
    int adjusted_power = m.efp;
    if (cc != 0 || tc == 0 || cdata[tc].relationship == 10)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (gdata_current_map == 6 || gdata_current_map == 40
        || gdata_current_map == 42)
    {
        result.obvious = false;
        txt(lang(
                 u8"この場所では効果がない。"s,
                 u8"The effect doesn't work in this area."s));
        return;
    }
    result.succeeded = true;
    {
        int stat = inv_find(663, cc);
        if (stat != -1)
        {
            adjusted_power = adjusted_power * 3 / 2;
        }
    }
    if (rnd(adjusted_power / 15 + 5) < cdata[tc].level)
    {
        result.succeeded = false;
    }
    if (cdata[tc].quality >= 4 || cdata[tc].character_role != 0
        || cdata[tc].is_lord_of_dungeon() == 1)
    {
        f = -1;
    }
    if (result.succeeded)
    {
        rc = tc;
        new_ally_joins();
        check_quest();
    }
    else if (!result.succeeded)
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
}

void magic_place_ground_effect(const magic_data& m, magic_result& result, ground_effect_t type)
{
    if (type == ground_effect_t::web)
    {
        p(0) = 3;
        p(1) = 2 + rnd((m.efp / 50 + 1));
        txt(lang(
                 u8"蜘蛛の巣が辺りを覆った。"s,
                 u8"The ground is covered with thick webbing."s));
    }
    if (type == ground_effect_t::fog)
    {
        txt(lang(
                 u8"辺りを濃い霧が覆った。"s,
                 u8"The air is wrapped in a dense fog."s));
        p(0) = 3;
        p(1) = 2 + rnd((m.efp / 50 + 1));
    }
    if (type == ground_effect_t::acid)
    {
        txt(lang(
                 u8"酸の水溜りが発生した。"s, u8"Acid puddles are generated."s));
        p(0) = 2;
        p(1) = 2 + rnd((m.efp / 50 + 1));
    }
    if (type == ground_effect_t::fire)
    {
        txt(lang(
                 u8"火柱が発生した。"s,
                 u8"Walls of fire come out from the ground."s));
        p(0) = 2;
        p(1) = 2 + rnd((m.efp / 50 + 1));
    }
    if (type == ground_effect_t::ether)
    {
        txt(lang(u8"エーテルの霧が発生した。"s, u8"Ether mist spreads."s));
        p(0) = 2;
        p(1) = 1 + rnd((m.efp / 100 + 2));
    }
    snd(68);
    for (int cnt = 0, cnt_end = (p(1)); cnt < cnt_end; ++cnt)
    {
        x = rnd(p) + tlocx - rnd(p);
        y = rnd(p) + tlocy - rnd(p);
        result.succeeded = true;
        if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
        {
            result.succeeded = false;
        }
        else if (chipm(7, map(x, y, 0)) & 4)
        {
            result.succeeded = false;
        }
        if (dist(tlocx, tlocy, x, y) >= p)
        {
            result.succeeded = false;
        }
        if (!result.succeeded)
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
        if (type == ground_effect_t::ether)
        {
            addmef(x, y, 4, 20, rnd(4) + 2, m.efp, cc);
        }
        if (type == ground_effect_t::acid)
        {
            addmef(x, y, 3, 19, rnd(10) + 5, m.efp, cc);
        }
        if (type == ground_effect_t::fire)
        {
            addmef(x, y, 5, 24, rnd(10) + 5, m.efp, cc);
            mapitem_fire(x, y);
        }
        if (type == ground_effect_t::web)
        {
            addmef(x, y, 1, 11, -1, m.efp * 2);
        }
        if (type == ground_effect_t::fog)
        {
            addmef(x, y, 2, 30, 8 + rnd((15 + m.efp / 25)), m.efp);
        }
    }
}

void magic_create_artifact(const magic_data& m, magic_result& result)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 0;
    snd(100);
    ctrl_inventory();
    if (inv[ci].quality < 4 || inv[ci].quality == 6)
    {
        txt(lang(u8"それは無理だ。"s, u8"It's impossible."s));
        result.obvious = false;
        return;
    }
    txt(lang(
             u8"アーティファクトの新しい銘は？"s,
             u8"What do you want to name this artifact?"s));
    {
        int stat = select_alias(3);
        if (stat == 0)
        {
            result.obvious = false;
            randomize();
            return;
        }
        p = stat;
    }
    inv[ci].subname = list(1, p) + 40000;
    randomize();
    txt(lang(
             u8"それは"s + listn(0, p) + u8"という銘になった。"s,
             u8"It's now called "s + listn(0, p) + u8"."s));
}

// TODO fix efcibk
void magic_superior_material(const magic_data& m, magic_result& result)
{
    int efcibk = 0;
    efcibk = ci;

    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 7;
    snd(100);
    {
        int stat = ctrl_inventory();
        f = stat;
    }
    if (inv[ci].quality >= 4 || ibit(10, ci) == 1)
    {
        txt(lang(
                 u8"そのアイテムに改良の余地はない。"s,
                 u8"This item leaves no room for improvement."s));
        fixmaterial = 0;
        objfix = 0;
        return;
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
        encadd(
               ci,
               randomenc(randomenclv(egolv)),
               randomencp() + (fixlv == 5) * 100 + (ibit(15, ci) == 1) * 100,
               20 - (fixlv == 5) * 10 - (ibit(15, ci) == 1) * 20);
    }
    randomize();
    txt(lang(
             u8"それは"s + itemname(ci, 1) + u8"になった。"s,
             u8"It becomes "s + itemname(ci, 1) + u8"."s));
    if (equip != 0)
    {
        cdata_body_part(cc, equip) =
            cdata_body_part(cc, equip) / 10000 * 10000 + ci + 1;
        inv[ci].body_part = equip;
    }
    refresh_character(cc);
    fixmaterial = 0;
    objfix = 0;
    ci = efcibk;
    --inv[ci].number;
    cell_refresh(inv[ci].position.x, inv[ci].position.y);
    autosave = 1 * (gdata_current_map != 35);

    ci = efcibk;
}

void magic_change_material(const magic_data& m, magic_result& result, bool is_material_kit)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 0;
    snd(100);
    {
        int stat = ctrl_inventory();
        f = stat;
    }
    if (inv[ci].quality == 5 || ibit(10, ci) == 1)
    {
        if (!is_material_kit)
        {
            result.succeeded = false;
        }
    }
    equip = inv[ci].body_part;
    if (result.succeeded)
    {
        if (inv[ci].quality == 6)
        {
            if (m.efp < 350)
            {
                txt(lang(
                         u8"アーティファクトの再生成にはパワーが足りない。"s,
                         u8"More magic power is needed to reconstruct an artifact."s));
                return;
            }
            animeload(8, cc);
            txt(lang(
                     name(cc) + u8"の"s + itemname(ci, 1)
                     + u8"は再生成された。"s,
                     name(cc) + your(cc) + u8" "s + itemname(ci, 1, 1)
                     + u8" is reconstructed."s));
            --inv[ci].number;
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            flt();
            itemcreate(0, inv[ci].id, -1, -1, 0);
        }
        else
        {
            animeload(8, cc);
            if (m.efp <= 50)
            {
                if (rnd(3) == 0)
                {
                    fixmaterial = 35;
                }
            }
            s = itemname(ci, 1, 1);
            objlv = m.efp / 10;
            objfix = m.efp / 100;
            randomize();
            change_item_material();
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
        result.obvious = false;
    }
    if (equip != 0)
    {
        cdata_body_part(cc, equip) =
            cdata_body_part(cc, equip) / 10000 * 10000 + ci + 1;
        inv[ci].body_part = equip;
    }
    refresh_character(cc);
    fixmaterial = 0;
    objfix = 0;
}

void magic_deed_of_inheritance(const magic_data& m, magic_result& result)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    snd(24);
    p = rnd((m.efp + 1)) / 100 + 1;
    gdata_rights_to_succeed_to += p;
    txtef(5);
    txt(lang(
             u8"あなたは遺産相続人として認められた(+"s + p + u8")"s,
             u8"You claim the right of succession. (+"s + p + u8")"s));
    txt(lang(
             u8"今やあなたは"s + gdata_rights_to_succeed_to
             + u8"個の遺産を相続できる。"s,
             u8"You can now inherit "s + gdata_rights_to_succeed_to
             + u8" items."s));
}

void magic_enchant(const magic_data& m, magic_result& result, bool is_armor)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    invsubroutine = 1;
    if (is_armor)
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
        int stat = ctrl_inventory();
        if (stat == 1)
        {
            if (inv[ci].enhancement < m.efp / 100)
            {
                snd(24);
                txt(lang(
                         itemname(ci) + u8"は黄金の光に包まれた。"s,
                         itemname(ci) + u8" "s + is2(inv[ci].number)
                         + u8" surrounded by a golden aura."s));
                ++inv[ci].enhancement;
            }
            else
            {
                txt(lang(
                         itemname(ci) + u8"は抵抗した。"s,
                         itemname(ci) + u8" resist"s + _s2(inv[ci].number)
                         + u8"."s));
            }
            refresh_character(cc);
        }
        else
        {
            result.obvious = false;
        }
    }
}

void magic_recharge(const magic_data& m, magic_result& result, bool is_fill_charge)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    if (is_fill_charge)
    {
        if (gdata_charge_power < 10)
        {
            txt(lang(
                     u8"充填するには最低でも魔力の貯蓄が10必要だ。"s,
                     u8"You need at least 10 recharge powers to recharge items."s));
            return;
        }
        gdata_charge_power -= 10;
        txt(lang(
                 u8"魔力の貯蓄を10消費した(残り"s + gdata_charge_power + u8")"s,
                 u8"You spend 10 recharge powers. (Total:"s + gdata_charge_power
                 + u8")"s));
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 3;
    snd(100);
    {
        int stat = ctrl_inventory();
        if (stat == 1)
        {
            dbid = inv[ci].id;
            access_item_db(item_db_t::charge_level);
            if (ichargelevel < 1 || inv[ci].id == 290 || inv[ci].id == 480
                || inv[ci].id == 289 || inv[ci].id == 732
                || (inv[ci].id == 687 && inv[ci].param2 != 0))
            {
                txt(lang(
                         u8"それは充填ができないようだ。"s,
                         u8"You can't recharge this item."s));
                return;
            }
            result.succeeded = true;
            if (inv[ci].count > ichargelevel)
            {
                // TODO is this equivalent?
                //f = -1;
                result.succeeded = false;
            }
            if (f == -1)
            {
                txt(lang(
                         itemname(ci) + u8"はこれ以上充填できないようだ。"s,
                         itemname(ci) + u8" cannot be recharged anymore."s));
                return;
            }
            if (rnd(m.efp / 25 + 1) == 0)
            {
                result.succeeded = false;
            }
            if (the_item_db[inv[ci].id]->category == 54000)
            {
                if (rnd(4) == 0)
                {
                    result.succeeded = false;
                }
            }
            if (rnd(ichargelevel * ichargelevel + 1) == 0)
            {
                result.succeeded = false;
            }
            if (result.succeeded)
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
                txt(lang(
                         itemname(ci) + u8"は充填された(+"s + p + u8")"s,
                         itemname(ci) + u8" "s + is2(inv[ci].number)
                         + u8" recharged by +"s + p + u8"."s));
                inv[ci].count += p;
                animeload(8, cc);
            }
            else
            {
                if (rnd(4) == 0)
                {
                    txt(lang(
                             itemname(ci) + u8"は破裂した。"s,
                             itemname(ci) + u8" explode"s + _s2(inv[ci].number)
                             + u8"."s));
                    --inv[ci].number;
                    refresh_burden_state();
                    return;
                }
                txt(lang(
                         itemname(ci) + u8"への充填は失敗した。"s,
                         u8"You fail to recharge "s + itemname(ci) + u8"."s));
            }
        }
        else
        {
            result.obvious = false;
        }
    }
}

void magic_draw_charge(const magic_data& m, magic_result& result)
{
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 5;
    snd(100);
    {
        int stat = ctrl_inventory();
        if (stat == 1)
        {
            dbid = inv[ci].id;
            access_item_db(item_db_t::charge_level);
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
            txt(lang(
                     itemname(ci) + u8"を破壊して"s + p
                     + u8"の魔力を抽出した(計"s + gdata_charge_power
                     + u8")"s,
                     u8"You destroy "s + itemname(ci) + u8" and extract "s + p
                     + u8" recharge powers. (Total:"s + gdata_charge_power
                     + u8")"s));
            inv[ci].number = 0;
            refresh_burden_state();
        }
    }
}

void magic_change_creature(const magic_data& m, magic_result& result)
{
    if (tc == 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    result.succeeded = true;
    if (m.efp / 10 + 10 < cdata[tc].level)
    {
        result.succeeded = false;
    }
    if (cdata[tc].quality >= 4 || cdata[tc].character_role != 0
        || cdata[tc].is_escorted() == 1
        || cdata[tc].is_lord_of_dungeon() == 1)
    {
        f = -1;
    }
    if (tc < 57)
    {
        result.succeeded = false;
    }
    if (result.succeeded)
    {
        animeload(8, tc);
        txt(lang(
                 name(tc) + u8"は変化した。"s,
                 name(tc) + u8" change"s + _s(tc) + u8"."s));
        flt(calcobjlv(cdata[tc].level + 3), 2);
        characreate(56, 0, -3, 0);
        relocate_chara(56, tc, 1);
        cdata[tc].enemy_id = cc;
        cdata[tc].is_quest_target() = false;
        check_quest();
    }
    else if (!result.succeeded)
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
}

void magic_alchemy(const magic_data& m, magic_result& result)
{
    int fltbk = 0;
    int valuebk = 0;
    if (cc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
        return;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 4;
    snd(100);
    {
        int stat = ctrl_inventory();
        f = stat;
    }
    if (f)
    {
        if (inv[ci].quality > 4 || ibit(5, ci) == 1)
        {
            result.succeeded = false;
        }
    }
    if (result.succeeded)
    {
        autosave = 1 * (gdata_current_map != 35);
        animeload(8, cc);
        fltbk = the_item_db[inv[ci].id]->category;
        valuebk = calcitemvalue(ci, 0);
        inv[ci].number = 0;
        for (int cnt = 0;; ++cnt)
        {
            await();
            flt(calcobjlv(m.efp / 10) + 5, calcfixlv(3));
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
                inv[ci].number = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        txt(lang(
                 u8"それは"s + itemname(ci, 1) + u8"に変容した。"s,
                 u8"It is metamorphosed into "s + itemname(ci, 1) + u8"."s));
        refresh_burden_state();
    }
    else
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        result.obvious = false;
    }
}

void magic_wall_creation(const magic_data& m, magic_result& result, bool create_door)
{
    x = tlocx;
    y = tlocy;
    result.succeeded = true;
    if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1))
    {
        result.succeeded = false;
    }
    else
    {
        if (chipm(7, map(x, y, 0)) & 4)
        {
            if (homemapmode == 0)
            {
                if (!create_door)
                {
                    result.succeeded = false;
                }
                else if (chipm(0, map(x, y, 0)) == 3)
                {
                    result.succeeded = false;
                }
            }
        }
        if (map(x, y, 1) != 0 || map(x, y, 6) != 0)
        {
            result.succeeded = false;
        }
    }
    if (result.succeeded)
    {
        if (create_door)
        {
            snd(65);
            if (chipm(0, map(x, y, 0)) == 6)
            {
                txt(lang(
                         u8"この壁は魔法を受け付けないようだ。"s,
                         u8"These walls seem to resist your magic."s));
                return;
            }
            txt(lang(u8"扉が出現した。"s, u8"A door appears."s));
            cell_featset(x, y, tile_doorclosed, 21, rnd(m.efp / 10 + 1));
            if (chipm(7, map(x, y, 0)) & 4)
            {
                map(x, y, 0) = tile_tunnel;
            }
        }
        else
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
    }
    else
    {
        if (homemapmode == 0)
        {
            txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        }
        result.obvious = false;
    }
}

void magic_swarm(const magic_data& m, magic_result& result)
{
    txtef(4);
    txt(lang(u8"スウォーム！"s, u8"Swarm!"s));
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[m.cc].state != 1)
        {
            continue;
        }
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (m.cc == cnt)
        {
            continue;
        }
        if (cnt <= 16)
        {
            continue;
        }
        result.selected_target = cnt;
        dx = cdata[result.selected_target].position.x;
        dy = cdata[result.selected_target].position.y;
        if (dist(cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy)
            > the_ability_db[631]->sdataref3 % 1000 + 1)
        {
            continue;
        }
        if (fov_los(cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy)
            == 0)
        {
            continue;
        }
        play_animation(9, m.damage.element);

        // TODO de-globalize
        cc = m.cc;
        tc = result.selected_target;
        dice1 = m.damage.dice_x;
        dice2 = m.damage.dice_y;
        bonus = m.damage.damage_bonus;
        //ele = m.damage.element;
        //elep = m.damage.element_power;
        //try_to_melee_attack(ele, elep);
        try_to_melee_attack();
    }
}

void magic_drop_item(const magic_data& m, magic_result& result)
{
    if (mdata(6) == 1)
    {
        return;
    }
    if (map(cdata[m.cc].position.x, cdata[m.cc].position.y, 6) != 0)
    {
        return;
    }
    cell_featset(cdata[m.cc].position.x, cdata[m.cc].position.y, 0, 14, 7, m.cc);
    if (is_in_fov(m.cc))
    {
        txt(lang(
                 name(m.cc) + u8"は何かを投下した。"s,
                 name(m.cc) + u8" drop"s + _s(m.cc)
                 + u8" something on the ground."s));
    }
}

void magic_gravity(const magic_data& m, magic_result& result)
{
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (m.cc == cnt)
        {
            continue;
        }
        if (cdata[cnt].is_immune_to_mine())
        {
            continue;
        }
        result.selected_target = cnt;
        dx = cdata[result.selected_target].position.x;
        dy = cdata[result.selected_target].position.y;
        if (dist(cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy) > 4)
        {
            continue;
        }
        if (is_in_fov(result.selected_target))
        {
            txt(lang(
                     name(result.selected_target) + u8"は重力を感じた。"s,
                     name(result.selected_target) + u8" feel"s + _s(result.selected_target) + u8" gravity."s));
        }
        cdata[result.selected_target].gravity += 100 + rnd(100);
    }
}

void magic_ehekatl(const magic_data& m, magic_result& result)
{
    txtef(4);
    txt(lang(u8"うみみゃぁ！"s, u8"Mewmewmew!"s));
    animode = 0;
    play_animation(19, m.damage.element);
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[m.cc].state != 1)
        {
            continue;
        }
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (m.cc == cnt)
        {
            continue;
        }
        result.selected_target = cnt;
        dmghp(result.selected_target, 9999999, m.cc);
    }
}

void magic_meteorite(const magic_data& m, magic_result& result)
{
    txtef(4);
    txt(lang(
             u8"隕石が落ちてきた！"s,
             u8"Innumerable meteorites fall all over the area!"s));
    play_animation(22, m.damage.element);
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        dy = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
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
                result.selected_target = map(dx, dy, 1) - 1;
                dmg = sdata(16, m.cc) * m.efp / 10;
                dmghp(result.selected_target, dmg, m.cc, element_t::burning, 1000);
            }
        }
    }
}

void magic_cheer(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.cc))
    {
        txt(lang(
                 name(m.cc) + u8"は仲間を鼓舞した。"s,
                 name(m.cc) + u8" cheer"s + _s(m.cc) + u8"."s));
    }
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (m.cc == cnt)
        {
            continue;
        }
        if (m.cc < 16)
        {
            if (cnt >= 16)
            {
                continue;
            }
            else if (cdata[m.cc].relationship != cdata[result.selected_target].relationship)
            {
                continue;
            }
        }
        result.selected_target = cnt;
        dx = cdata[result.selected_target].position.x;
        dy = cdata[result.selected_target].position.y;
        if (dist(cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy)
            > the_ability_db[656]->sdataref3 % 1000 + 1)
        {
            continue;
        }
        if (fov_los(cdata[m.cc].position.x, cdata[m.cc].position.y, dx, dy)
            == 0)
        {
            continue;
        }
        if (is_in_fov(result.selected_target))
        {
            txtef(4);
            txt(lang(
                     name(result.selected_target) + u8"は興奮した！"s,
                     name(result.selected_target) + u8" "s + is(result.selected_target) + u8" excited!"s));
        }
        addbuff(result.selected_target, 5, sdata(17, m.cc) * 5 + 50, 15);
        addbuff(result.selected_target, 7, sdata(17, m.cc) * 5 + 100, 60);
        addbuff(result.selected_target, 18, 1500, 30);
    }
}

void magic_cure_corruption(const magic_data& m, magic_result& result)
{
    if (m.tc != 0)
    {
        txt(lang(u8"何もおきない… "s, u8"Nothing happens..."s));
        return;
    }
    snd(64);
    if (!is_cursed(m.efstatus))
    {
        txtef(2);
        txt(lang(
                 u8"エーテルの抗体があなたの体内に行き渡った。"s,
                 u8"Your Ether Disease is cured greatly."s));
        modcorrupt(m.efp * -10);
    }
    else
    {
        txtef(8);
        txt(lang(
                 u8"エーテルの病菌があなたの体内に行き渡った。"s,
                 u8" The Ether Disease spreads around your body."s));
        modcorrupt(200);
    }
}

void magic_corrupt_player(const magic_data& m, magic_result& result)
{
    if (m.tc != 0)
    {
        return;
    }
    txtef(8);
    txt(lang(
             name(m.cc) + u8"に睨まれ、あなたはエーテルに侵食された。"s,
             name(m.cc) + u8" gazes at you. Your Ether Disease deteriorates."s));
    modcorrupt(100);
}


void magic_aggro(const magic_data& m, magic_result& result, bool is_insult)
{
    if (is_insult)
    {
        magic_insult(m, result);
    }
    dmgcon(m.tc, 7, 200);
}

void magic_insult(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                 name(m.cc) + u8"は"s + name(m.tc) + u8"を罵倒した。"s,
                 name(m.cc) + u8" insult"s + _s(m.cc) + u8" "s + name(m.tc)
                 + u8"."s));
        txtef(9);
        if (jp)
        {
            if (cdata[m.cc].sex == 0)
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

void magic_gaze(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                 name(m.cc) + u8"は"s + name(m.tc) + u8"を睨み付けた。"s,
                 name(m.cc) + u8" gaze"s + _s(m.cc) + u8" at "s + name(m.tc)
                 + u8"."s));
    }
    dmgmp(m.tc, rnd(20) + 1);
}

void magic_surround_in_flames(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                 name(m.tc) + u8"は炎に包まれた。"s,
                 name(m.tc) + u8" "s + is(m.tc) + u8" surrounded by flames."s));
    }
    addmef(
           cdata[m.tc].position.x,
           cdata[m.tc].position.y,
           5,
           24,
           rnd(15) + 25,
           m.efp,
           m.cc);
    mapitem_fire(cdata[m.tc].position.x, cdata[m.tc].position.y);
}

void magic_loot(const magic_data& m, magic_result& result)
{
    if (is_in_fov(m.tc))
    {
        txt(lang(
                 name(m.cc) + u8"は"s + name(m.tc) + u8"のバックパックを漁った。"s,
                 name(m.cc) + u8" loot"s + _s(m.cc) + u8" "s + name(m.tc) + your(m.tc)
                 + u8" backpack."s));
    }
    p = -1;
    for (const auto& cnt : items(m.tc))
    {
        if (inv[cnt].number == 0)
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
        for (const auto& cnt : items(m.tc))
        {
            if (inv[cnt].number == 0)
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
        return;
    }
    ci = p;
    if (ibit(6, ci))
    {
        if (is_in_fov(m.tc))
        {
            txt(lang(
                     name(m.cc) + u8"は"s + itemname(ci, 1)
                     + u8"の異臭に気付き手をひっこめた。"s,
                     name(m.cc) + u8" notice"s + _s(m.cc) + u8" unusual odor from "s
                     + itemname(ci, 1) + u8" and step"s + _s(m.cc)
                     + u8" back."s));
        }
        return;
    }
    rowact_item(ci);
    if (is_in_fov(m.tc))
    {
        snd(18);
        txt(lang(
                 name(m.cc) + u8"は"s + itemname(ci, 1) + u8"を食べた！"s,
                 name(m.cc) + u8" eat"s + _s(m.cc) + u8" "s + itemname(ci, 1)
                 + u8"!"s));
    }
    healhp(m.cc, cdata[m.cc].max_hp / 3);
    // TODO de-globalize
    label_2161();
    refresh_burden_state();
}

void magic_fall_down(const magic_data& m, magic_result& result)
{
    animeload(10, m.tc);
    for (int cnt = 0,
             cnt_end = cnt + (clamp(4 + rnd((m.efp / 50 + 1)), 1, 15));
         cnt < cnt_end;
         ++cnt)
    {
        snd(64);
        flt(calcobjlv(m.efp / 10), calcfixlv(3));
        dbid = 0;
        dbid = 54;
        p = 400 + rnd(m.efp);
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
        itemcreate(-1, dbid, cdata[m.cc].position.x, cdata[m.cc].position.y, p);
        txt(lang(
                 itemname(ci) + u8"が降ってきた！"s,
                 itemname(ci) + u8" fall"s + _s2(inv[ci].number) + u8" down!"s));
        await(100);
        redraw();
    }
}

void magic_four_dimensional_pocket(const magic_data& m, magic_result& result)
{
    snd(72);
    txt(lang(
             u8"あなたは四次元のポケットを召喚した。"s,
             u8"You summon 4 dimensional pocket."s));
    invfile = 8;
    ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
    if (fs::exists(
                   filesystem::dir::tmp() / (u8"shop"s + invfile + u8".s2")))
    {
        ctrl_file(file_operation2_t::_3, u8"shop"s + invfile + u8".s2");
    }
    else
    {
        for (const auto& cnt : items(-1))
        {
            inv[cnt].number = 0;
        }
    }
    shoptrade = 0;
    menucycle = 1;
    invsubroutine = 1;
    invctrl(0) = 22;
    invctrl(1) = 5;
    invcontainer = clamp(m.efp / 10 + 10, 10, 300);
    mode = 6;
    snd(100);
    ctrl_inventory(m.efp);
    invcontainer = 0;
    ctrl_file(file_operation2_t::_4, u8"shop"s + invfile + u8".s2");
    ctrl_file(file_operation2_t::_3, u8"shoptmp.s2");
    mode = 0;
}

std::string elename(const magic_data& m)
{
    if (m.efid == 614)
    {
        return lang(u8"飢えた"s, u8"starving"s);
    }
    if (m.efid == 613)
    {
        return lang(u8"腐った"s, u8"rotten"s);
    }
    if (m.efid == 617)
    {
        return lang(u8"恐ろしい"s, u8"fearful"s);
    }
    if (m.efid == 618)
    {
        return lang(u8"柔らかい"s, u8"silky"s);
    }

    switch(m.damage.element)
    {
    case element_t::burning:
        return lang(u8"燃える"s, u8"burning"s);
    case element_t::icy:
        return lang(u8"冷たい"s, u8"icy"s);
    case element_t::electric:
        return lang(u8"放電する"s, u8"electric"s);
    case element_t::psychic:
        return lang(u8"霊的な"s, u8"psychic"s);
    case element_t::numb:
        return lang(u8"痺れる"s, u8"numb"s);
    case element_t::shivering:
        return lang(u8"震える"s, u8"shivering"s);
    case element_t::poisonous:
        return lang(u8"毒の"s, u8"poisonous"s);
    case element_t::infernal:
        return lang(u8"地獄の"s, u8"infernal"s);
    case element_t::chaotic:
        return lang(u8"混沌の"s, u8"chaotic"s);
    case element_t::gloomy:
        return lang(u8"暗黒の"s, u8"gloomy"s);
    case element_t::cut:
        return lang(u8"出血の"s, u8"cut"s);
    case element_t::ether:
        return lang(u8"エーテルの"s, u8"ether"s);
    }

    return u8"?"s;
}


} // namespace elona
