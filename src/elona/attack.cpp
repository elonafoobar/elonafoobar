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
#include "game.hpp"
#include "globals.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "lua_env/interface.hpp"
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

int extraattack = 0;

} // namespace



int tglocx = 0;
int tglocy = 0;
int cansee = 0;



// see input.cpp
extern int kdx;
extern int kdy;



void build_target_list(const Character& attacker)
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
            if (attacker.is_player() || attacker.relationship >= 0)
            {
                if (cnt.relationship == 10)
                {
                    if (cnt.is_player())
                    {
                        continue;
                    }
                }
            }
            x = cnt.position.x;
            y = cnt.position.y;
            if (x == attacker.position.x && y == attacker.position.y)
            {
                continue;
            }
            if (!fov_los(attacker.position, {x, y}))
            {
                continue;
            }
            if (cnt.is_invisible() == 1)
            {
                if (attacker.can_see_invisible() == 0)
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
            p = dist(attacker.position, list(1, cnt), list(2, cnt));
            p(1) = dist(attacker.position, list(1, cnt + 1), list(2, cnt + 1));
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



CanDoRangedAttackResult can_do_ranged_attack(const Character& chara)
{
    OptionalItemRef weapon;
    OptionalItemRef ammo;
    for (const auto& body_part : chara.body_parts)
    {
        if (!body_part.is_equip())
        {
            continue;
        }
        if (body_part.id == "core.shoot")
        {
            weapon = body_part.equipment();
        }
        else if (body_part.id == "core.ammo")
        {
            ammo = body_part.equipment();
        }
    }
    if (!weapon)
    {
        return {-1, nullptr, nullptr};
    }
    if (!ammo)
    {
        if (weapon->skill != 111)
        {
            return {-2, nullptr, nullptr};
        }
    }
    if (ammo)
    {
        if (weapon->skill != ammo->skill)
        {
            return {-3, nullptr, nullptr};
        }
    }
    attackskill = weapon->skill;
    return {1, weapon, ammo};
}



bool do_physical_attack_internal(
    Character& attacker,
    Character& target,
    const OptionalItemRef& weapon,
    const OptionalItemRef& ammo)
{
    int attackdmg;

    if (attacker.state() != Character::State::alive)
    {
        return false;
    }
    if (target.state() != Character::State::alive)
    {
        return false;
    }
    if (attacker.fear != 0)
    {
        txt(i18n::s.get("core.damage.is_frightened", attacker),
            Message::only_once{true});
        return false;
    }
    if (cell_data.at(target.position.x, target.position.y).mef_index_plus_one !=
        0)
    {
        bool return_now = mef_proc_from_physical_attack(attacker, target);
        if (return_now)
        {
            return false;
        }
    }
    if (attackrange == 1)
    {
        RangedAttackAnimation(
            attacker.position,
            target.position,
            static_cast<RangedAttackAnimation::Type>(attackskill),
            the_item_db[weapon->id]->subcategory,
            weapon->image,
            weapon->tint)
            .play();
    }

    const auto expmodifer = 1 + target.is_hung_on_sand_bag() * 15 +
        target.splits() + target.splits2() +
        (game()->current_map == mdata_t::MapId::show_house);
    int hit = calcattackhit(attacker, target, weapon, ammo);
    i = 0;
    if (hit == 1)
    {
        if (critical)
        {
            if (attacker.is_player())
            {
                txt(i18n::s.get("core.damage.critical_hit"),
                    Message::color{ColorIndex::red});
            }
        }
        dmg = calcattackdmg(
            attacker,
            target,
            weapon,
            ammo,
            AttackDamageCalculationMode::actual_damage);
        attackdmg = dmg;
        if (attacker.is_player())
        {
            if (g_config.attack_animation())
            {
                int damage_percent = dmg * 100 / target.max_hp;
                MeleeAttackAnimation(
                    target.position,
                    target.breaks_into_debris(),
                    attackskill,
                    damage_percent,
                    critical)
                    .play();
            }
        }
        if (attackskill != 106)
        {
            if (weapon->quality >= Quality::miracle)
            {
                if (weapon->quality == Quality::special)
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(the_item_db[weapon->id]->integer_id);
                }
                else if (weapon->subname >= 40000)
                {
                    randomize(weapon->subname - 40000);
                    s(1) = random_title(RandomTitleType::weapon);
                    randomize();
                }
                else
                {
                    s(1) = i18n::s.get("core.misc.wields_proudly.the") +
                        iknownnameref(the_item_db[weapon->id]->integer_id);
                }
                if (weapon->quality == Quality::godly)
                {
                    s(1) = i18n::s.get("core.item.godly_paren", s(1));
                }
                else
                {
                    s(1) = i18n::s.get("core.item.miracle_paren", s(1));
                }
                if (is_in_fov(attacker))
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get(
                                "core.damage.wields_proudly", attacker, s(1)),
                            Message::color{ColorIndex::cyan});
                    }
                }
                i = 1;
            }
        }
        if (attackskill == 106)
        {
            if (attacker.element_of_unarmed_attack != 0)
            {
                ele = attacker.element_of_unarmed_attack / 100000;
                elep = attacker.element_of_unarmed_attack % 100000;
            }
        }
        if (is_in_fov(target))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (attackskill == 106)
            {
                if (!target.is_player_or_ally())
                {
                    g_proc_damage_events_flag = 2;
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed_and",
                        attacker,
                        _melee(0, attacker.melee_attack_type),
                        target));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.damage.weapon.attacks_unarmed",
                        attacker,
                        _melee(1, attacker.melee_attack_type),
                        target));
                }
            }
            else
            {
                optional<std::string> weapon_name = none;
                if (attackskill == 111)
                {
                    // Special case for thrown weapons.
                    weapon_name = itemname(weapon.unwrap(), 1, false);
                }
                else
                {
                    weapon_name = i18n::s.get_enum_property_optional(
                        "core.damage.weapon", "name", attackskill);
                }
                if (weapon_name)
                {
                    if (!target.is_player_or_ally())
                    {
                        g_proc_damage_events_flag = 2;
                        if (attackskill == 111)
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_throwing",
                                attacker,
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                target,
                                *weapon_name));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.damage.weapon.attacks_and",
                                attacker,
                                i18n::s.get_enum_property(
                                    "core.damage.weapon",
                                    "verb_and",
                                    attackskill),
                                target));
                        }
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.damage.weapon.attacks_with",
                            attacker,
                            i18n::s.get_enum_property(
                                "core.damage.weapon", "verb", attackskill),
                            target,
                            *weapon_name));
                    }
                }
            }
        }
        damage_hp(target, dmg, attacker.index, ele, elep);
        if (critical)
        {
            chara_gain_skill_exp(attacker, 186, 60 / expmodifer, 2);
            critical = 0;
        }
        if (rtdmg > target.max_hp / 20 || rtdmg > target.get_skill(154).level ||
            rnd(5) == 0)
        {
            chara_gain_skill_exp(
                attacker,
                attackskill,
                clamp(
                    (target.get_skill(173).level * 2 -
                     attacker.get_skill(attackskill).level + 1),
                    5,
                    50) /
                    expmodifer,
                0,
                4);
            if (attackrange == 0)
            {
                chara_gain_skill_exp(attacker, 152, 20 / expmodifer, 0, 4);
                if (attacker.combat_style.two_hand())
                {
                    chara_gain_skill_exp(attacker, 167, 20 / expmodifer, 0, 4);
                }
                if (attacker.combat_style.dual_wield())
                {
                    chara_gain_skill_exp(attacker, 166, 20 / expmodifer, 0, 4);
                }
            }
            else if (attackskill == 111)
            {
                chara_gain_skill_exp(attacker, 152, 10 / expmodifer, 0, 4);
            }
            else
            {
                chara_gain_skill_exp(attacker, 189, 25 / expmodifer, 0, 4);
            }
            if (attacker.is_player())
            {
                if (game()->mount != 0)
                {
                    chara_gain_skill_exp(
                        cdata.player(), 301, 30 / expmodifer, 0, 5);
                }
            }
            if (target.state() == Character::State::alive)
            {
                chara_gain_skill_exp(
                    target,
                    chara_armor_class(target),
                    clamp((250 * rtdmg / target.max_hp + 1), 3, 100) /
                        expmodifer,
                    0,
                    5);
                if (target.combat_style.shield())
                {
                    chara_gain_skill_exp(target, 168, 40 / expmodifer, 0, 4);
                }
            }
        }
        if (attackskill != 106)
        {
            proc_weapon_enchantments(attacker, target, weapon.unwrap());
        }
        if (target.cut_counterattack > 0)
        {
            if (attackrange == 0)
            {
                damage_hp(
                    attacker,
                    attackdmg * target.cut_counterattack / 100 + 1,
                    target.index,
                    61,
                    100);
            }
        }
        if (target.damage_reaction_info != 0)
        {
            p = target.damage_reaction_info % 1000;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (attackrange == 0)
                {
                    if (p == 61)
                    {
                        if (is_in_fov(attacker))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.thorns",
                                    attacker),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            attacker,
                            clamp(attackdmg / 10, 1, target.max_hp / 10),
                            target.index,
                            p,
                            target.damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 62)
                    {
                        if (is_in_fov(attacker))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.ether_thorns",
                                    attacker),
                                Message::color{ColorIndex::purple});
                        }
                        damage_hp(
                            attacker,
                            clamp(attackdmg / 10, 1, target.max_hp / 10),
                            target.index,
                            p,
                            target.damage_reaction_info / 1000);
                        break;
                    }
                    if (p == 63)
                    {
                        if (attackskill != 106)
                        {
                            if (rnd(5) == 0)
                            {
                                item_acid(attacker, weapon);
                            }
                        }
                    }
                }
                if (attackdmg > target.max_hp / 10)
                {
                    tlocx = target.position.x;
                    tlocy = target.position.y;
                    if (p == 63)
                    {
                        if (is_in_fov(target))
                        {
                            txt(i18n::s.get(
                                    "core.damage.reactive_attack.acids"),
                                Message::color{ColorIndex::purple});
                        }
                        efid = 455;
                        efp = target.damage_reaction_info / 1000;
                        magic(target, target);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        if (attacker.is_player())
        {
            snd("core.miss");
        }
        if (attacker.get_skill(attackskill).level >
                target.get_skill(173).level ||
            rnd(5) == 0)
        {
            p = clamp(
                    (attacker.get_skill(attackskill).level -
                     target.get_skill(173).level / 2 + 1),
                    1,
                    20) /
                expmodifer;
            chara_gain_skill_exp(target, 173, p, 0, 4);
            chara_gain_skill_exp(target, 187, p, 0, 4);
        }
    }
    if (hit == -1)
    {
        if (is_in_fov(attacker))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (target.is_player_or_ally())
            {
                txt(i18n::s.get("core.damage.miss.ally", attacker, target));
            }
            else
            {
                txt(i18n::s.get("core.damage.miss.other", attacker, target));
            }
            add_damage_popup(u8"miss", target.index, {191, 191, 191});
        }
    }
    if (hit == -2)
    {
        if (is_in_fov(attacker))
        {
            if (extraattack)
            {
                txt(i18n::s.get("core.damage.furthermore"));
                Message::instance().continue_sentence();
            }
            if (target.is_player_or_ally())
            {
                txt(i18n::s.get("core.damage.evade.ally", attacker, target));
            }
            else
            {
                txt(i18n::s.get("core.damage.evade.other", attacker, target));
            }
            add_damage_popup(u8"evade!!", target.index, {191, 191, 191});
        }
    }
    rowact_check(target);
    if (attackskill != 106)
    {
        if (target.state() != Character::State::alive)
        {
            if (weapon->is_alive)
            {
                if (weapon->param2 < calcexpalive(weapon->param1))
                {
                    weapon->param2 +=
                        rnd_capped(target.level / weapon->param1 + 1);
                    if (weapon->param2 >= calcexpalive(weapon->param1))
                    {
                        snd("core.ding3");
                        txt(i18n::s.get(
                                "core.misc.living_weapon_taste_blood",
                                weapon.unwrap()),
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
            if (rnd(100) < attacker.extra_shot)
            {
                ammoproc = -1;
                ++extraattack;
                return true;
            }
        }
        else if (rnd(100) < attacker.extra_attack)
        {
            ++extraattack;
            return true;
        }
    }

    return false;
}



void do_physical_attack(
    Character& attacker,
    Character& target,
    const OptionalItemRef& weapon,
    const OptionalItemRef& ammo)
{
    while (do_physical_attack_internal(attacker, target, weapon, ammo))
        ;
}



void do_ranged_attack(
    Character& attacker,
    Character& target,
    const OptionalItemRef& weapon,
    const OptionalItemRef& ammo)
{
    int ammox = 0;
    int ammoy = 0;
    attackrange = 1;
    attacknum = 0;
    ele = 0;
    ammoproc = -1;
    ammoprocbk = -1;
    ammox = target.position.x;
    ammoy = target.position.y;
    if (ammo)
    {
        if (ammo->charges != -1)
        {
            if (ammo->enchantments[ammo->charges].power % 1000 <= 0)
            {
                txt(i18n::s.get("core.action.ranged.load_normal_ammo"));
                ammo->charges = -1;
            }
            else
            {
                ammoproc = ammo->enchantments[ammo->charges].id % 10000;
                if (attacker.is_player())
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
                --ammo->enchantments[ammo->charges].power;
            }
        }
    }
    if (ammoproc == 0)
    {
        ammoprocbk = ammoproc;
        auto rapidshot_target = std::ref(target);
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            const auto result = can_do_ranged_attack(attacker);
            const auto& weapon = result.weapon;
            const auto& ammo = result.ammo;
            ele = 0;
            extraattack = 0;
            do_physical_attack(attacker, rapidshot_target.get(), weapon, ammo);
            if (rapidshot_target.get().state() != Character::State::alive)
            {
                int stat = find_enemy_target(attacker);
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    rapidshot_target = std::ref(cdata[attacker.enemy_id]);
                }
            }
        }
    }
    else if (ammoproc == 5)
    {
        ammoprocbk = ammoproc;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            const auto result = can_do_ranged_attack(attacker);
            const auto& weapon = result.weapon;
            const auto& ammo = result.ammo;
            ele = 0;
            build_target_list(attacker);
            if (listmax == 0)
            {
                break;
            }
            const auto shot_target = list(0, rnd(listmax));
            if (attacker.is_player() || attacker.relationship >= 0)
            {
                if (cdata[shot_target].relationship >= 0)
                {
                    if (cnt != 0)
                    {
                        cnt = cnt + (rnd(5) == 0) - 1;
                        continue;
                    }
                }
            }
            else if (cdata[shot_target].relationship == -3)
            {
                cnt = cnt + (rnd(5) == 0) - 1;
                continue;
            }
            extraattack = 0;
            do_physical_attack(attacker, cdata[shot_target], weapon, ammo);
        }
    }
    else
    {
        extraattack = 0;
        do_physical_attack(attacker, target, weapon, ammo);
    }
    if (ammoproc == 1)
    {
        tlocx = ammox;
        tlocy = ammoy;
        efid = 460;
        efp = attacker.get_skill(attackskill).level * 8 + 10;
        magic(cdata.player(), target);
    }
    ammoproc = -1;
    ammoprocbk = -1;
}



void try_to_melee_attack(Character& attacker, Character& target)
{
    if (!attacker.is_player())
    {
        if (target.damage_reaction_info)
        {
            if (distance < 6)
            {
                if (fov_los(attacker.position, target.position))
                {
                    const auto result = can_do_ranged_attack(attacker);
                    if (result.type == 1)
                    {
                        do_ranged_attack(
                            attacker, target, result.weapon, result.ammo);
                    }
                }
            }
            p = target.damage_reaction_info % 1000;
            if (p == 61)
            {
                if (attacker.hp < attacker.max_hp / 2)
                {
                    return;
                }
            }
        }
    }
    attacknum = 0;
    attackrange = 0;
    attackskill = 106;
    ele = 0;
    if (attacker.combat_style.shield())
    {
        if (clamp(int(std::sqrt(attacker.get_skill(168).level) - 3), 1, 5) +
                attacker.has_power_bash() * 5 >
            rnd(100))
        {
            if (is_in_fov(attacker))
            {
                txt(i18n::s.get(
                    "core.action.melee.shield_bash", attacker, target));
            }
            damage_hp(
                target,
                rnd_capped(attacker.get_skill(168).level) + 1,
                attacker.index);
            status_ailment_damage(
                target,
                StatusAilment::dimmed,
                50 + int(std::sqrt(attacker.get_skill(168).level)) * 15);
            target.paralyzed += rnd(3);
        }
    }
    for (const auto& body_part : attacker.body_parts)
    {
        if (!body_part.is_equip())
        {
            continue;
        }
        if (body_part.id == "core.shoot" || body_part.id == "core.ammo")
        {
            continue;
        }
        const auto weapon = body_part.equipment().unwrap();
        if (weapon->dice.rolls > 0)
        {
            attackskill = weapon->skill;
            ++attacknum;
            extraattack = 0;
            do_physical_attack(attacker, target, weapon, nullptr);
        }
    }
    if (attackskill == 106)
    {
        extraattack = 0;
        do_physical_attack(attacker, target, nullptr, nullptr);
    }
}



void proc_weapon_enchantments(
    Character& attacker,
    Character& target,
    const ItemRef& weapon)
{
    for (const auto& enc : weapon->enchantments)
    {
        int enc_id = enc.id;
        if (enc_id == 36)
        {
            p = rnd_capped(enc.power / 50 + 1) + 1;
            heal_sp(attacker, p);
            damage_sp(target, p / 2);
            continue;
        }
        if (enc_id == 38)
        {
            p = rnd_capped(enc.power / 25 + 1) + 1;
            heal_mp(attacker, p / 5);
            if (target.state() != Character::State::alive)
            {
                continue;
            }
            damage_mp(target, p);
            continue;
        }
        if (enc_id == 37)
        {
            if (rnd(66) == 0)
            {
                deferred_event_add(DeferredEvent{
                    "core.ragnarok",
                    0,
                    lua::create_table("core.chara", attacker.index)});
            }
            continue;
        }
        if (enc_id == 40)
        {
            if (game()->left_turns_of_timestop == 0)
            {
                if (rnd(25) == 0)
                {
                    txt(i18n::s.get("core.action.time_stop.begins", attacker),
                        Message::color{ColorIndex::cyan});
                    game()->left_turns_of_timestop = enc.power / 100 + 1 + 1;
                }
                continue;
            }
        }
        if (enc_id == 57)
        {
            s = chara_db_get_filter(target.id);
            if (strutil::contains(s(0), u8"/dragon/"))
            {
                g_proc_damage_events_flag = 1;
                damage_hp(target, orgdmg / 2, attacker.index);
            }
            continue;
        }
        if (enc_id == 61)
        {
            s = chara_db_get_filter(target.id);
            if (strutil::contains(s(0), u8"/god/"))
            {
                g_proc_damage_events_flag = 1;
                damage_hp(target, orgdmg / 2, attacker.index);
            }
            continue;
        }
        if (enc_id == 58)
        {
            s = chara_db_get_filter(target.id);
            if (strutil::contains(s(0), u8"/undead/"))
            {
                g_proc_damage_events_flag = 1;
                damage_hp(target, orgdmg / 2, attacker.index);
            }
            continue;
        }
        i = enc_id / 10000;
        if (i != 0)
        {
            enc_id = enc_id % 10000;
            if (i == 7)
            {
                if (orgdmg <= 1)
                {
                    continue;
                }
                ele = enc_id;
                if (target.state() != Character::State::alive)
                {
                    continue;
                }
                g_proc_damage_events_flag = 1;
                damage_hp(
                    target,
                    rnd_capped(orgdmg * (100 + enc.power) / 1000 + 1) + 5,
                    attacker.index,
                    ele,
                    enc.power / 2 + 100);
                continue;
            }
            if (i == 8)
            {
                if (target.state() != Character::State::alive)
                {
                    continue;
                }
                if (enc_id >= 26)
                {
                    continue;
                }
                p = encprocref(1, enc_id);
                auto invoke_target = target.index;
                if (p == 3000 || p == 10000)
                {
                    invoke_target = attacker.index;
                }
                p = encprocref(5, enc_id);
                enc_id = encprocref(0, enc_id);
                tlocx = cdata[invoke_target].position.x;
                tlocy = cdata[invoke_target].position.y;
                if (rnd(100) < p)
                {
                    efid = enc_id;
                    efp =
                        enc.power + attacker.get_skill(attackskill).level * 10;
                    magic(attacker, cdata[invoke_target]);
                }
                continue;
            }
            continue;
        }
    }
    if (ammoproc == 4)
    {
        txt(i18n::s.get("core.action.time_stop.begins", attacker),
            Message::color{ColorIndex::cyan});
        game()->left_turns_of_timestop = 4;
    }
    if (ammoproc == 3)
    {
        if (target.state() == Character::State::alive)
        {
            g_proc_damage_events_flag = 1;
            damage_hp(
                target,
                orgdmg * 2 / 3,
                attacker.index,
                rnd(11) + 50,
                attacker.get_skill(attackskill).level * 10 + 100);
        }
    }
}



int find_enemy_target(Character& chara, bool silent)
{
    if (cdata[chara.enemy_id].state() != Character::State::alive)
    {
        chara.enemy_id = 0;
    }
    else if (is_in_fov(cdata[chara.enemy_id]) == 0)
    {
        chara.enemy_id = 0;
    }
    if (chara.enemy_id == 0)
    {
        build_target_list(chara);
        if (listmax != 0)
        {
            f = 0;
            if (chara.is_player() || chara.relationship >= 0)
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
                        chara.enemy_id = list(0, cnt);
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
    if (chara.enemy_id == 0 || chara.blind != 0)
    {
        if (chara.is_player() && !silent)
        {
            txt(i18n::s.get("core.action.ranged.no_target"));
            update_screen();
        }
        return 0;
    }
    if (chara.enemy_id < 0)
    {
        chara.enemy_id = 0;
    }
    return 1;
}



int prompt_really_attack(const Character& target)
{
    s = txttargetlevel(cdata.player(), target);
    txt(s);
    txt(i18n::s.get("core.action.really_attack", target));
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



int target_position(bool target_cell)
{
    if (tlocinitx != 0 || tlocinity != 0)
    {
        tlocx = tlocinitx;
        tlocy = tlocinity;
    }
    else
    {
        tlocx = cdata.player().position.x;
        tlocy = cdata.player().position.y;
    }

    scposval = 1;

    if (!target_cell)
    {
        if (cdata.player().enemy_id == 0)
        {
            find_enemy_target(cdata.player());
        }
        build_target_list(cdata.player());
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

        optional_ref<Character> target_chara;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one <= 1)
            {
                break;
            }
            target_chara =
                cdata[cell_data.at(tlocx, tlocy).chara_index_plus_one - 1];
            if (is_in_fov(*target_chara) == 0)
            {
                break;
            }
            if (!fov_los(cdata.player().position, target_chara->position))
            {
                break;
            }
            if ((target_chara->is_invisible() == 0 ||
                 cdata.player().can_see_invisible() || target_chara->wet) == 0)
            {
                break;
            }
            get_route(
                cdata.player().position.x,
                cdata.player().position.y,
                target_chara->position.x,
                target_chara->position.y);
            dx = (tlocx - scx) * inf_tiles + inf_screenx;
            dy = (tlocy - scy) * inf_tiles + inf_screeny;
            if (maxroute != 0)
            {
                dx = cdata.player().position.x;
                dy = cdata.player().position.y;
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
            if (target_chara)
            {
                i = target_chara->index;
            }
            else
            {
                i = 0;
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
                if (target_chara)
                {
                    cdata.player().enemy_id = target_chara->index;
                    txt(i18n::s.get("core.action.look.target", *target_chara));
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
