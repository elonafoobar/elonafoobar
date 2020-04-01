#include "attack.hpp"

#include "../snail/application.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int attackitem = 0;
int extraattack = 0;

} // namespace



int tglocx = 0;
int tglocy = 0;
int cansee = 0;



// see input.cpp
extern int kdx;
extern int kdy;



void build_target_list()
{
    listmax = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() != Character::State::alive)
            {
                continue;
            }
            if (is_in_fov(cnt) == 0)
            {
                continue;
            }
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                if (cnt.relationship == 10)
                {
                    if (cnt.index == 0)
                    {
                        continue;
                    }
                }
            }
            x = cnt.position.x;
            y = cnt.position.y;
            if (x == cdata[cc].position.x && y == cdata[cc].position.y)
            {
                continue;
            }
            if (fov_los(cdata[cc].position.x, cdata[cc].position.y, x, y) == 0)
            {
                continue;
            }
            if (cnt.is_invisible() == 1)
            {
                if (cdata[cc].can_see_invisible() == 0)
                {
                    if (cnt.wet == 0)
                    {
                        continue;
                    }
                }
            }
            list(0, listmax) = cnt.index;
            list(1, listmax) = x;
            list(2, listmax) = y;
            ++listmax;
            if (listmax >= 499)
            {
                break;
            }
        }
        if (listmax != 0)
        {
            break;
        }
    }
    while (1)
    {
        if (listmax < 2)
        {
            break;
        }
        i = 1;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            p = dist(
                cdata[cc].position.x,
                cdata[cc].position.y,
                list(1, cnt),
                list(2, cnt));
            p(1) = dist(
                cdata[cc].position.x,
                cdata[cc].position.y,
                list(1, cnt + 1),
                list(2, cnt + 1));
            if (p(1) < p)
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                p(2) = list(2, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(2, cnt) = list(2, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                list(2, cnt + 1) = p(2);
                i = 0;
                break;
            }
        }
        if (i == 1)
        {
            break;
        }
    }
}



int can_do_ranged_attack()
{
    cw = -1;
    ammo = -1;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            ammo = cdata[cc].body_parts[cnt] % 10000 - 1;
        }
    }
    if (cw == -1)
    {
        cw = 0;
        return -1;
    }
    if (ammo == -1)
    {
        if (inv[cw].skill != 111)
        {
            cw = 0;
            return -2;
        }
    }
    if (ammo != -1)
    {
        if (inv[cw].skill != inv[ammo].skill)
        {
            return -3;
        }
    }
    attackskill = inv[cw].skill;
    return 1;
}



bool do_physical_attack_internal()
{
    int attackdmg;

    if (cdata[cc].state() != Character::State::alive)
    {
        return false;
    }
    if (cdata[tc].state() != Character::State::alive)
    {
        return false;
    }
    if (cdata[cc].fear != 0)
    {
        txt(i18n::s.get("core.damage.is_frightened", cdata[cc]),
            Message::only_once{true});
        return false;
    }
    if (cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .mef_index_plus_one != 0)
    {
        bool return_now = mef_proc_from_physical_attack(tc);
        if (return_now)
        {
            return false;
        }
    }
    if (attackrange == 1)
    {
        RangedAttackAnimation(
            cdata[cc].position,
            cdata[tc].position,
            static_cast<RangedAttackAnimation::Type>(attackskill),
            the_item_db[itemid2int(inv[cw].id)]->subcategory,
            inv[cw].image % 1000,
            inv[cw].image / 1000)
            .play();
    }

    const auto expmodifer = 1 + cdata[tc].is_hung_on_sand_bag() * 15 +
        cdata[tc].splits() + cdata[tc].splits2() +
        (game_data.current_map == mdata_t::MapId::show_house);
    int hit = calcattackhit();
    i = 0;
    if (hit == 1)
    {
        if (critical)
        {
            if (cc == 0)
            {
                txt(i18n::s.get("core.damage.critical_hit"),
                    Message::color{ColorIndex::red});
            }
        }
        dmg = calcattackdmg(AttackDamageCalculationMode::actual_damage);
        attackdmg = dmg;
        if (cc == 0)
        {
            if (g_config.attack_animation())
            {
                int damage_percent = dmg * 100 / cdata[tc].max_hp;
                MeleeAttackAnimation(
                    cdata[tc].position,
                    cdata[tc].breaks_into_debris(),
                    attackskill,
                    damage_percent,
                    critical)
                    .play();
            }
        }
        if (attackskill != 106)
        {
            if (inv[cw].quality >= Quality::miracle)
            {
                if (inv[cw].quality == Quality::special)
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(itemid2int(inv[cw].id));
                }
                else if (inv[cw].subname >= 40000)
                {
                    randomize(inv[cw].subname - 40000);
                    s(1) = random_title(RandomTitleType::weapon);
                    randomize();
                }
                else
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(itemid2int(inv[cw].id));
                }
                if (inv[cw].quality == Quality::godly)
                {
                    s(1) = i18n::s.get("core.item.godly_paren", s(1));
                }
                else
                {
                    s(1) = i18n::s.get("core.item.miracle_paren", s(1));
                }
                if (is_in_fov(cdata[cc]))
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get(
                                "core.damage.wields_proudly", cdata[cc], s(1)),
                            Message::color{ColorIndex::cyan});
                    }
                }
                i = 1;
            }
        }
        if (attackskill == 106)
        {
            if (cdata[cc].element_of_unarmed_attack != 0)
            {
                ele = cdata[cc].element_of_unarmed_attack / 100000;
                elep = cdata[cc].element_of_unarmed_attack % 100000;
            }
        }
        if (is_in_fov(cdata[tc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (attackskill == 106)
            {
                if (tc >= 16)
                {
                    game_data.proc_damage_events_flag = 2;
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed_and",
                        cdata[cc],
                        _melee(0, cdata[cc].melee_attack_type),
                        cdata[tc]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed",
                        cdata[cc],
                        _melee(1, cdata[cc].melee_attack_type),
                        cdata[tc]));
                }
            }
            else
            {
                optional<std::string> weapon_name = none;
                if (attackskill == 111)
                {
                    // Special case for thrown weapons.
                    weapon_name = itemname(cw, 1, 1);
                }
                else
                {
                    weapon_name = i18n::s.get_enum_property_optional(
                        "core.damage.weapon", "name", attackskill);
                }
                if (weapon_name)
                {
                    if (tc >= 16)
                    {
                        game_data.proc_damage_events_flag = 2;
                        if (attackskill == 111)
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_throwing",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc],
                                *weapon_name));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_and",
                                cdata[cc],
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                cdata[tc]));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.damage.weapon.attacks_with",
                            cdata[cc],
                            i18n::s.get_enum_property(
                                "core.damage.weapon", "verb", attackskill),
                            cdata[tc],
                            *weapon_name));
                    }
                }
            }
        }
        damage_hp(cdata[tc], dmg, cc, ele, elep);
        if (critical)
        {
            chara_gain_skill_exp(cdata[cc], 186, 60 / expmodifer, 2);
            critical = 0;
        }
        if (rtdmg > cdata[tc].max_hp / 20 || rtdmg > sdata(154, tc) ||
            rnd(5) == 0)
        {
            chara_gain_skill_exp(
                cdata[cc],
                attackskill,
                clamp(
                    (sdata(173, tc) * 2 - sdata(attackskill, cc) + 1), 5, 50) /
                    expmodifer,
                0,
                4);
            if (attackrange == 0)
            {
                chara_gain_skill_exp(cdata[cc], 152, 20 / expmodifer, 0, 4);
                if (cdata[cc].combat_style.two_hand())
                {
                    chara_gain_skill_exp(cdata[cc], 167, 20 / expmodifer, 0, 4);
                }
                if (cdata[cc].combat_style.dual_wield())
                {
                    chara_gain_skill_exp(cdata[cc], 166, 20 / expmodifer, 0, 4);
                }
            }
            else if (attackskill == 111)
            {
                chara_gain_skill_exp(cdata[cc], 152, 10 / expmodifer, 0, 4);
            }
            else
            {
                chara_gain_skill_exp(cdata[cc], 189, 25 / expmodifer, 0, 4);
            }
            if (cc == 0)
            {
                if (game_data.mount != 0)
                {
                    chara_gain_skill_exp(
                        cdata.player(), 301, 30 / expmodifer, 0, 5);
                }
            }
            if (cdata[tc].state() == Character::State::alive)
            {
                chara_gain_skill_exp(
                    cdata[tc],
                    chara_armor_class(cdata[tc]),
                    clamp((250 * rtdmg / cdata[tc].max_hp + 1), 3, 100) /
                        expmodifer,
                    0,
                    5);
                if (cdata[tc].combat_style.shield())
                {
                    chara_gain_skill_exp(cdata[tc], 168, 40 / expmodifer, 0, 4);
                }
            }
        }
        if (attackskill != 106)
        {
            proc_weapon_enchantments();
        }
        if (cdata[tc].cut_counterattack > 0)
        {
            if (attackrange == 0)
            {
                damage_hp(
                    cdata[cc],
                    attackdmg * cdata[tc].cut_counterattack / 100 + 1,
                    tc,
                    61,
                    100);
            }
        }
        if (cdata[tc].damage_reaction_info != 0)
        {
            p = cdata[tc].damage_reaction_info % 1000;
            ccbk = cc;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (attackrange == 0)
                {
                    if (p == 61)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.thorns",
                                    cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            cdata[cc],
                            clamp(attackdmg / 10, 1, cdata[tc].max_hp / 10),
                            tc,
                            p,
                            cdata[tc].damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 62)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.ether_thorns",
                                    cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            cdata[cc],
                            clamp(attackdmg / 10, 1, cdata[tc].max_hp / 10),
                            tc,
                            p,
                            cdata[tc].damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 63)
                    {
                        if (attackskill != 106)
                        {
                            if (rnd(5) == 0)
                            {
                                item_acid(cdata[cc], cw);
                            }
                        }
                    }
                }
                if (attackdmg > cdata[tc].max_hp / 10)
                {
                    cc = tc;
                    tlocx = cdata[cc].position.x;
                    tlocy = cdata[cc].position.y;
                    if (p == 63)
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.acids"),
                                Message::color{ColorIndex::purple});
                        }
                        efid = 455;
                        efp = cdata[tc].damage_reaction_info / 1000;
                        magic();
                        break;
                    }
                }
            }
            cc = ccbk;
        }
    }
    else
    {
        if (cc == 0)
        {
            snd("core.miss");
        }
        if (sdata(attackskill, cc) > sdata(173, tc) || rnd(5) == 0)
        {
            p = clamp(
                    (sdata(attackskill, cc) - sdata(173, tc) / 2 + 1), 1, 20) /
                expmodifer;
            chara_gain_skill_exp(cdata[tc], 173, p, 0, 4);
            chara_gain_skill_exp(cdata[tc], 187, p, 0, 4);
        }
    }
    if (hit == -1)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get("core.damage.miss.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.damage.miss.other", cdata[cc], cdata[tc]));
            }
            add_damage_popup(u8"miss", tc, {191, 191, 191});
        }
    }
    if (hit == -2)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (tc < 16)
            {
                txt(i18n::s.get(
                    "core.damage.evade.ally", cdata[cc], cdata[tc]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.damage.evade.other", cdata[cc], cdata[tc]));
            }
            add_damage_popup(u8"evade!!", tc, {191, 191, 191});
        }
    }
    rowact_check(cdata[tc]);
    if (attackskill != 106)
    {
        if (cdata[tc].state() != Character::State::alive)
        {
            cw = attackitem;
            if (inv[cw].is_alive())
            {
                if (inv[cw].param2 < calcexpalive(inv[cw].param1))
                {
                    inv[cw].param2 +=
                        rnd_capped(cdata[tc].level / inv[cw].param1 + 1);
                    if (inv[cw].param2 >= calcexpalive(inv[cw].param1))
                    {
                        snd("core.ding3");
                        txt(i18n::s.get(
                                "core.misc.living_weapon_taste_blood", inv[cw]),
                            Message::color{ColorIndex::green});
                    }
                }
            }
        }
    }
    ele = 0;
    if (extraattack == 0)
    {
        if (attackrange)
        {
            if (rnd(100) < cdata[cc].extra_shot)
            {
                ammoproc = -1;
                ++extraattack;
                return true;
            }
        }
        else if (rnd(100) < cdata[cc].extra_attack)
        {
            ++extraattack;
            return true;
        }
    }

    return false;
}



void do_physical_attack()
{
    while (do_physical_attack_internal())
        ;
}



void do_ranged_attack()
{
    int ammox = 0;
    int ammoy = 0;
    attackrange = 1;
    attacknum = 0;
    ele = 0;
    ammoproc = -1;
    ammoprocbk = -1;
    ammox = cdata[tc].position.x;
    ammoy = cdata[tc].position.y;
    attackitem = cw;
    if (ammo != -1)
    {
        if (inv[ammo].count != -1)
        {
            if (inv[ammo].enchantments[inv[ammo].count].power % 1000 <= 0)
            {
                txt(i18n::s.get("core.action.ranged.load_normal_ammo"));
                inv[ammo].count = -1;
            }
            else
            {
                ammoproc = inv[ammo].enchantments[inv[ammo].count].id % 10000;
                if (cc == 0)
                {
                    if (cdata.player().sp < 50)
                    {
                        if (cdata.player().sp < rnd(75))
                        {
                            txt(i18n::s.get("core.magic.common.too_exhausted"));
                            damage_sp(
                                cdata.player(),
                                encammoref(2, ammoproc) / 2 + 1);
                            ammoproc = -1;
                            return;
                        }
                    }
                    damage_sp(cdata.player(), rnd(encammoref(2, ammoproc) + 1));
                }
                --inv[ammo].enchantments[inv[ammo].count].power;
            }
        }
    }
    if (ammoproc == 0)
    {
        ammoprocbk = ammoproc;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            can_do_ranged_attack();
            ele = 0;
            extraattack = 0;
            do_physical_attack();
            if (cdata[tc].state() != Character::State::alive)
            {
                int stat = find_enemy_target();
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    tc = cdata[cc].enemy_id;
                }
            }
        }
    }
    else if (ammoproc == 5)
    {
        ammoprocbk = ammoproc;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            can_do_ranged_attack();
            ele = 0;
            build_target_list();
            if (listmax == 0)
            {
                break;
            }
            tc = list(0, rnd(listmax));
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                if (cdata[tc].relationship >= 0)
                {
                    if (cnt != 0)
                    {
                        cnt = cnt + (rnd(5) == 0) - 1;
                        continue;
                    }
                }
            }
            else if (cdata[tc].relationship == -3)
            {
                cnt = cnt + (rnd(5) == 0) - 1;
                continue;
            }
            extraattack = 0;
            do_physical_attack();
        }
    }
    else
    {
        extraattack = 0;
        do_physical_attack();
    }
    if (ammoproc == 1)
    {
        tlocx = ammox;
        tlocy = ammoy;
        efid = 460;
        efp = sdata(attackskill, cc) * 8 + 10;
        magic();
    }
    ammoproc = -1;
    ammoprocbk = -1;
}



void try_to_melee_attack()
{
    if (cc != 0)
    {
        if (cdata[tc].damage_reaction_info)
        {
            if (distance < 6)
            {
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y))
                {
                    int stat = can_do_ranged_attack();
                    if (stat == 1)
                    {
                        do_ranged_attack();
                    }
                }
            }
            p = cdata[tc].damage_reaction_info % 1000;
            if (p == 61)
            {
                if (cdata[cc].hp < cdata[cc].max_hp / 2)
                {
                    return;
                }
            }
        }
    }
    attacknum = 0;
    attackrange = 0;
    attackskill = 106;
    ammo = -1;
    ele = 0;
    if (cdata[cc].combat_style.shield())
    {
        if (clamp(int(std::sqrt(sdata(168, cc)) - 3), 1, 5) +
                cdata[cc].has_power_bash() * 5 >
            rnd(100))
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.melee.shield_bash", cdata[cc], cdata[tc]));
            }
            damage_hp(cdata[tc], rnd_capped(sdata(168, cc)) + 1, cc);
            status_ailment_damage(
                cdata[tc],
                StatusAilment::dimmed,
                50 + int(std::sqrt(sdata(168, cc))) * 15);
            cdata[tc].paralyzed += rnd(3);
        }
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 10)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            continue;
        }
        cw = cdata[cc].body_parts[cnt] % 10000 - 1;
        attackitem = cw;
        if (inv[cw].dice_x > 0)
        {
            attackskill = inv[cw].skill;
            ++attacknum;
            extraattack = 0;
            do_physical_attack();
        }
    }
    if (attackskill == 106)
    {
        extraattack = 0;
        do_physical_attack();
    }
}



void proc_weapon_enchantments()
{
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        cw = attackitem;
        if (inv[cw].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[cw].enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd_capped(inv[cw].enchantments[cnt].power / 50 + 1) + 1;
            heal_sp(cdata[cc], p);
            damage_sp(cdata[tc], p / 2);
            continue;
        }
        if (enc == 38)
        {
            p = rnd_capped(inv[cw].enchantments[cnt].power / 25 + 1) + 1;
            heal_mp(cdata[cc], p / 5);
            if (cdata[tc].state() != Character::State::alive)
            {
                continue;
            }
            damage_mp(cdata[tc], p);
            continue;
        }
        if (enc == 37)
        {
            if (rnd(66) == 0)
            {
                event_add(18, cc);
            }
            continue;
        }
        if (enc == 40)
        {
            if (game_data.left_turns_of_timestop == 0)
            {
                if (rnd(25) == 0)
                {
                    txt(i18n::s.get("core.action.time_stop.begins", cdata[cc]),
                        Message::color{ColorIndex::cyan});
                    game_data.left_turns_of_timestop =
                        inv[cw].enchantments[cnt].power / 100 + 1 + 1;
                }
                continue;
            }
        }
        if (enc == 57)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/dragon/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 61)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/god/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        if (enc == 58)
        {
            s = chara_db_get_filter(cdata[tc].id);
            if (strutil::contains(s(0), u8"/undead/"))
            {
                game_data.proc_damage_events_flag = 1;
                damage_hp(cdata[tc], orgdmg / 2, cc);
            }
            continue;
        }
        i = enc / 10000;
        if (i != 0)
        {
            enc = enc % 10000;
            if (i == 7)
            {
                if (orgdmg <= 1)
                {
                    continue;
                }
                ele = enc;
                if (cdata[tc].state() != Character::State::alive)
                {
                    continue;
                }
                game_data.proc_damage_events_flag = 1;
                damage_hp(
                    cdata[tc],
                    rnd_capped(
                        orgdmg * (100 + inv[cw].enchantments[cnt].power) /
                            1000 +
                        1) +
                        5,
                    cc,
                    ele,
                    inv[cw].enchantments[cnt].power / 2 + 100);
                continue;
            }
            if (i == 8)
            {
                if (cdata[tc].state() != Character::State::alive)
                {
                    continue;
                }
                if (enc >= 26)
                {
                    continue;
                }
                tcbk = tc;
                p = encprocref(1, enc);
                if (p == 3000 || p == 10000)
                {
                    tc = cc;
                }
                p = encprocref(5, enc);
                enc = encprocref(0, enc);
                tlocx = cdata[tc].position.x;
                tlocy = cdata[tc].position.y;
                if (rnd(100) < p)
                {
                    efid = enc;
                    efp = inv[cw].enchantments[cnt].power +
                        sdata(attackskill, cc) * 10;
                    magic();
                }
                tc = tcbk;
                continue;
            }
            continue;
        }
    }
    if (ammoproc == 4)
    {
        txt(i18n::s.get("core.action.time_stop.begins", cdata[cc]),
            Message::color{ColorIndex::cyan});
        game_data.left_turns_of_timestop = 4;
    }
    if (ammoproc == 3)
    {
        if (cdata[tc].state() == Character::State::alive)
        {
            game_data.proc_damage_events_flag = 1;
            damage_hp(
                cdata[tc],
                orgdmg * 2 / 3,
                cc,
                rnd(11) + 50,
                sdata(attackskill, cc) * 10 + 100);
        }
    }
}



int find_enemy_target(bool silent)
{
    if (cdata[cdata[cc].enemy_id].state() != Character::State::alive)
    {
        cdata[cc].enemy_id = 0;
    }
    else if (is_in_fov(cdata[cdata[cc].enemy_id]) == 0)
    {
        cdata[cc].enemy_id = 0;
    }
    if (cdata[cc].enemy_id == 0)
    {
        build_target_list();
        if (listmax != 0)
        {
            f = 0;
            if (cc == 0 || cdata[cc].relationship >= 0)
            {
                p(0) = -3;
                p(1) = -1;
                p(2) = 0;
            }
            else
            {
                p(0) = 10;
                p(1) = 0;
                p(2) = 0;
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                int cnt2 = cnt;
                for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
                {
                    if (cdata[list(0, cnt)].relationship <= p(cnt2))
                    {
                        cdata[cc].enemy_id = list(0, cnt);
                        f = 1;
                        break;
                    }
                }
                if (f == 1)
                {
                    break;
                }
            }
        }
    }
    if (cdata[cc].enemy_id == 0 || cdata[cc].blind != 0)
    {
        if (cc == 0 && !silent)
        {
            txt(i18n::s.get("core.action.ranged.no_target"));
            update_screen();
        }
        return 0;
    }
    if (cdata[cc].enemy_id < 0)
    {
        cdata[cc].enemy_id = 0;
    }
    return 1;
}



int prompt_really_attack()
{
    s = txttargetlevel(cc, tc);
    txt(s);
    txt(i18n::s.get("core.action.really_attack", cdata[tc]));
    if (yes_no())
    {
        update_screen();
        return 1;
    }
    else
    {
        update_screen();
        return 0;
    }
}



int target_position(bool target_chara)
{
    if (tlocinitx != 0 || tlocinity != 0)
    {
        tlocx = tlocinitx;
        tlocy = tlocinity;
    }
    else
    {
        tlocx = cdata[cc].position.x;
        tlocy = cdata[cc].position.y;
    }

    scposval = 1;

    if (target_chara)
    {
        if (cdata.player().enemy_id == 0)
        {
            find_enemy_target();
        }
        build_target_list();
        if (listmax == 0)
        {
            txt(i18n::s.get("core.misc.no_target_around"));
        }
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            if (list(0, cnt) == 0)
            {
                continue;
            }
            if (list(0, cnt) == cdata.player().enemy_id)
            {
                tlocx = cdata[list(0, cnt)].position.x;
                tlocy = cdata[list(0, cnt)].position.y;
                break;
            }
        }
    }

    while (1)
    {
        screenupdate = -1;
        update_screen();
        dx = (tlocx - scx) * inf_tiles + inf_screenx;
        dy = (tlocy - scy) * inf_tiles + inf_screeny;
        if (dy + inf_tiles <= windowh - inf_verh)
        {
            snail::Application::instance().get_renderer().set_blend_mode(
                snail::BlendMode::blend);
            snail::Application::instance().get_renderer().set_draw_color(
                {127, 127, 255, 50});
            snail::Application::instance().get_renderer().fill_rect(
                dx,
                dy * (dy > 0),
                inf_tiles -
                    (dx + inf_tiles > windoww) * (dx + inf_tiles - windoww),
                inf_tiles + (dy < 0) * inf_screeny -
                    (dy + inf_tiles > windowh - inf_verh) *
                        (dy + inf_tiles - windowh + inf_verh));
        }
        rc = -1;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one <= 1)
            {
                break;
            }
            rc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
            if (is_in_fov(cdata[rc]) == 0)
            {
                break;
            }
            if (fov_los(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[rc].position.x,
                    cdata[rc].position.y) == 0)
            {
                break;
            }
            if ((cdata[rc].is_invisible() == 0 ||
                 cdata.player().can_see_invisible() || cdata[rc].wet) == 0)
            {
                break;
            }
            get_route(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[rc].position.x,
                cdata[rc].position.y);
            dx = (tlocx - scx) * inf_tiles + inf_screenx;
            dy = (tlocy - scy) * inf_tiles + inf_screeny;
            if (maxroute != 0)
            {
                dx = cdata[cc].position.x;
                dy = cdata[cc].position.y;
                for (int cnt = 0; cnt < 100; ++cnt)
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
                    sx = (dx - scx) * inf_tiles + inf_screenx;
                    sy = (dy - scy) * inf_tiles + inf_screeny;
                    if (sy + inf_tiles <= windowh - inf_verh)
                    {
                        snail::Application::instance()
                            .get_renderer()
                            .set_blend_mode(snail::BlendMode::blend);
                        snail::Application::instance()
                            .get_renderer()
                            .set_draw_color({255, 255, 255, 25});
                        snail::Application::instance().get_renderer().fill_rect(
                            sx,
                            sy * (sy > 0),
                            inf_tiles -
                                (sx + inf_tiles > windoww) *
                                    (sx + inf_tiles - windoww),
                            inf_tiles + (sy < 0) * inf_screeny -
                                (sy + inf_tiles > windowh - inf_verh) *
                                    (sy + inf_tiles - windowh + inf_verh));
                    }
                }
            }
        }
        txttargetnpc(tlocx, tlocy);
        redraw();
        auto action = key_check();
        if (key_direction(action) == 1)
        {
            x = tlocx + kdx;
            y = tlocy + kdy;
            if (x >= 0 && y >= 0 && x < map_data.width && y < map_data.height)
            {
                tlocx += kdx;
                tlocy += kdy;
            }
        }
        if (findlocmode == 1)
        {
            if (rc == -1)
            {
                i = 0;
            }
            else
            {
                i = rc;
            }
            f = 0;
            p = 0;
            for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
            {
                if (cdata[list(0, cnt)].position.x == cdata[i].position.x)
                {
                    if (cdata[list(0, cnt)].position.y == cdata[i].position.y)
                    {
                        p = cnt;
                        break;
                    }
                }
            }
            if (action == "next_page")
            {
                ++p;
                f = 1;
                if (p >= listmax)
                {
                    p = 0;
                }
            }
            if (action == "previous_page")
            {
                --p;
                f = 1;
                if (p < 0)
                {
                    p = listmax - 1;
                    if (p < 0)
                    {
                        p = 0;
                    }
                }
            }
            i = list(0, p);
            if (f)
            {
                snd("core.cursor1");
                tlocx = cdata[list(0, p)].position.x;
                tlocy = cdata[list(0, p)].position.y;
            }
        }
        if (action == "enter")
        {
            if (findlocmode == 1)
            {
                if (cansee == 0 || chip_data.for_cell(tlocx, tlocy).effect & 4)
                {
                    txt(i18n::s.get(
                        "core.action.which_direction.cannot_see_location"));
                    continue;
                }
                snd("core.ok1");
                if (rc > 0)
                {
                    cdata.player().enemy_id = rc;
                    txt(i18n::s.get("core.action.look.target", cdata[rc]));
                }
                else
                {
                    tgloc = 1;
                    tglocx = tlocx;
                    tglocy = tlocy;
                    txt(i18n::s.get("core.action.look.target_ground"));
                }
            }
            else
            {
                snd("core.cursor1");
            }
            scposval = 0;
            if (tlocinitx == 0 && tlocinity == 0)
            {
                update_screen();
            }
            tlocinitx = 0;
            tlocinity = 0;
            return cansee;
        }
        if (action == "cancel")
        {
            tlocinitx = 0;
            tlocinity = 0;
            scposval = 0;
            update_screen();
            return -1;
        }
    }
}

} // namespace elona
