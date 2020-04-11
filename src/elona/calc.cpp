#include "calc.hpp"

#include "ability.hpp"
#include "area.hpp"
#include "buff.hpp"
#include "character.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace
{

std::vector<int> furniture_random_colors = {
    0,
    4,
    2,
    5,
    6,
};



std::vector<int> item_random_colors = {
    0,
    2,
    4,
    5,
    6,
    3,
};



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



optional<SkillDamage> calc_skill_damage(int skill, int cc, int power)
{
    int x = sdata(the_ability_db[skill]->related_basic_attribute, cc);

    switch (skill)
    {
    case 412: return SkillDamage{0, 1, x * power * 5 / 100, 0, 0};
    case 461:
        return SkillDamage{
            0, 1, clamp((x * 5 + power) / 20 + 40, 40, 100), 0, 0};
    case 411: return SkillDamage{0, 1, x * power * 10 / 100, 0, 0};
    case 400:
        return SkillDamage{1 + x / 30, power / 40 + 5 + 1, power / 30, 0, 0};
    case 401:
        return SkillDamage{2 + x / 26, power / 25 + 5 + 1, power / 15, 0, 0};
    case 405:
        return SkillDamage{2 + x / 22, power / 18 + 5 + 1, power / 10, 0, 0};
    case 402:
        return SkillDamage{3 + x / 15, power / 12 + 5 + 1, power / 6, 0, 0};
    case 403:
        return SkillDamage{5 + x / 10, power / 7 + 5 + 1, power / 2, 0, 0};
    case 406: return SkillDamage{0, 1, x * 5 + power * 2, 0, 0};
    case 407: return SkillDamage{0, 1, x * 5 + power * 3 / 2, 0, 0};
    case 623:
        return SkillDamage{
            1 + x / 10, cdata[cc].piety_point / 70 + 1 + 1, 0, 0, 0};
    case 624:
        return SkillDamage{
            1 + x / 20, cdata[cc].piety_point / 140 + 1 + 1, 0, 0, 0};
    case 414:
        return SkillDamage{power / 125 + 2 + x / 50,
                           power / 60 + 9 + 1,
                           0,
                           60,
                           100 + power / 4};
    case 459:
        return SkillDamage{power / 100 + 3 + x / 25,
                           power / 40 + 12 + 1,
                           0,
                           60,
                           100 + power / 4};
    case 418:
        return SkillDamage{power / 80 + 1 + x / 18,
                           power / 25 + 8 + 1,
                           0,
                           53,
                           200 + power / 3};
    case 415:
        return SkillDamage{power / 70 + 1 + x / 18,
                           power / 25 + 8 + 1,
                           0,
                           56,
                           200 + power / 3};
    case 417:
        return SkillDamage{power / 70 + 1 + x / 18,
                           power / 25 + 8 + 1,
                           0,
                           59,
                           200 + power / 3};
    case 416:
        return SkillDamage{power / 70 + 1 + x / 18,
                           power / 25 + 8 + 1,
                           0,
                           58,
                           200 + power / 3};
    case 419:
        return SkillDamage{power / 50 + 1 + x / 20,
                           power / 26 + 4 + 1,
                           0,
                           51,
                           180 + power / 4};
    case 420:
        return SkillDamage{power / 50 + 1 + x / 20,
                           power / 26 + 4 + 1,
                           0,
                           50,
                           180 + power / 4};
    case 421:
        return SkillDamage{power / 50 + 1 + x / 20,
                           power / 26 + 4 + 1,
                           0,
                           52,
                           180 + power / 4};
    case 422:
        return SkillDamage{power / 50 + 1 + x / 20,
                           power / 25 + 4 + 1,
                           0,
                           53,
                           180 + power / 4};
    case 423:
        return SkillDamage{power / 50 + 1 + x / 20,
                           power / 25 + 4 + 1,
                           0,
                           54,
                           180 + power / 4};
    case 431:
        return SkillDamage{power / 100 + 1 + x / 20,
                           power / 15 + 2 + 1,
                           0,
                           51,
                           150 + power / 5};
    case 432:
        return SkillDamage{power / 100 + 1 + x / 20,
                           power / 15 + 2 + 1,
                           0,
                           50,
                           150 + power / 5};
    case 433:
        return SkillDamage{power / 80 + 1 + x / 20,
                           power / 12 + 2 + 1,
                           0,
                           59,
                           150 + power / 5};
    case 434:
        return SkillDamage{power / 80 + 1 + x / 20,
                           power / 12 + 2 + 1,
                           0,
                           57,
                           150 + power / 5};
    case 460:
        return SkillDamage{
            power / 100 + 1 + x / 25, power / 18 + 2 + 1, 0, 60, 100};
    case 404:
        return SkillDamage{x / 20 + 3, power / 15 + 5 + 1, power / 10, 0, 0};
    case 644: return SkillDamage{1 + x / 25, 15 + x / 5 + 1, 1, 0, 0};
    case 601: return SkillDamage{1 + x / 15, 7, x / 4, 56, 200};
    case 612: return SkillDamage{1 + x / 20, 7, x / 15, 0, 0};
    case 602: return SkillDamage{1 + x / 15, 8, x / 8, 50, 100};
    case 603: return SkillDamage{1 + x / 15, 8, x / 8, 51, 100};
    case 604: return SkillDamage{1 + x / 15, 8, x / 8, 52, 100};
    case 605: return SkillDamage{1 + x / 15, 8, x / 8, 53, 100};
    case 606: return SkillDamage{1 + x / 15, 8, x / 8, 59, 100};
    case 608: return SkillDamage{1 + x / 15, 8, x / 8, 56, 100};
    case 610: return SkillDamage{1 + x / 15, 8, x / 8, 55, 100};
    case 607: return SkillDamage{1 + x / 15, 8, x / 8, 57, 100};
    case 609: return SkillDamage{1 + x / 15, 8, x / 8, 58, 100};
    case 611: return SkillDamage{1 + x / 15, 8, x / 8, 54, 100};
    case 613: return SkillDamage{1 + x / 10, 4, 1, 0, 0};
    case 614: return SkillDamage{1 + x / 10, 4, 1, 0, 0};
    case 617: return SkillDamage{1 + x / 10, 4, 0, 0, 100 + x * 2};
    case 618: return SkillDamage{1 + x / 10, 4, 0, 0, 100 + x * 3};
    case 615: return SkillDamage{1 + x / 10, 5, 0, 55, x * 4 + 20};
    case 616: return SkillDamage{1 + x / 10, 5, 0, 58, x * 4 + 20};
    case 636: return SkillDamage{1 + x / 20, 11, 1, 0, 0};
    case 655:
        return SkillDamage{
            power / 80 + 1, power / 8 + 2 + 1, 0, 57, 150 + power / 2};
    default: return none;
    }
}



int calcobjlv(int base)
{
    int ret = base <= 0 ? game_data.current_dungeon_level : base;
    if (game_data.current_map == mdata_t::MapId::shelter_)
    {
        ret = 1;
    }
    for (int i = 1; i < 4; ++i)
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



Quality calcfixlv(Quality base_quality)
{
    int ret = static_cast<int>(
        base_quality == Quality::none ? Quality::good : base_quality);
    for (int i = 1; i < 4; ++i)
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
    return static_cast<Quality>(clamp(
        ret, static_cast<int>(Quality::bad), static_cast<int>(Quality::godly)));
}



int calcfame(int cc, int base)
{
    int ret = base * 100 /
        (100 + cdata[cc].fame / 100 * (cdata[cc].fame / 100) / 2500);
    if (ret < 5)
    {
        ret = rnd(5) + 1;
    }
    return ret;
}



int decfame(int cc, int base)
{
    int ret = cdata[cc].fame / base + 5;
    ret = ret + rnd_capped(ret / 2) - rnd_capped(ret / 2);
    cdata[cc].fame -= ret;
    if (cdata[cc].fame < 0)
    {
        cdata[cc].fame = 0;
    }
    return ret;
}



int calcshopreform()
{
    return map_data.max_item_count * 100 + 1000;
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
    int n = game_data.date.year - cdata[cc].birth_year;
    return n >= 0 ? std::to_string(n) : i18n::s.get("core.chara.age_unknown");
}



int calcexpalive(int level)
{
    return level * 100;
}



int calc_evasion(int cc)
{
    return sdata(13, cc) / 3 + sdata(173, cc) + cdata[cc].dv + 25;
}



int calc_accuracy(
    optional_ref<Item> weapon,
    optional_ref<Item> ammo,
    bool consider_distance)
{
    critical = 0;
    int accuracy;

    if (attackskill == 106)
    {
        accuracy =
            sdata(12, cc) / 5 + sdata(10, cc) / 2 + sdata(attackskill, cc) + 50;
        if (cdata[cc].combat_style.shield())
        {
            accuracy = accuracy * 100 / 130;
        }
        accuracy +=
            sdata(12, cc) / 5 + sdata(10, cc) / 10 + cdata[cc].hit_bonus;
    }
    else
    {
        accuracy = sdata(12, cc) / 4 + sdata(weapon->skill, cc) / 3 +
            sdata(attackskill, cc) + 50;
        accuracy += cdata[cc].hit_bonus + weapon->hit_bonus;
        if (ammo)
        {
            accuracy += ammo->hit_bonus;
        }
    }

    if (attackskill != 106)
    {
        if (attackrange)
        {
            if (consider_distance)
            {
                rangedist = clamp(
                    dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y) -
                        1,
                    0,
                    9);
                const auto effective_range =
                    calc_effective_range(itemid2int(weapon->id));
                accuracy = accuracy * effective_range[rangedist] / 100;
            }
        }
        else
        {
            if (cdata[cc].combat_style.two_hand())
            {
                accuracy += 25;
                if (weapon->weight >= 4000)
                {
                    accuracy += sdata(167, cc);
                }
            }
            else if (cdata[cc].combat_style.dual_wield())
            {
                if (attacknum == 1)
                {
                    if (weapon->weight >= 4000)
                    {
                        accuracy -= (weapon->weight - 4000 + 400) /
                            (10 + sdata(166, cc) / 5);
                    }
                }
                else if (weapon->weight > 1500)
                {
                    accuracy -= (weapon->weight - 1500 + 100) /
                        (10 + sdata(166, cc) / 5);
                }
            }
        }
    }

    if (game_data.mount != 0)
    {
        if (cc == 0)
        {
            accuracy =
                accuracy * 100 / clamp((150 - sdata(301, cc) / 2), 115, 150);
            if (attackskill != 106 && attackrange == 0 &&
                weapon->weight >= 4000)
            {
                accuracy -=
                    (weapon->weight - 4000 + 400) / (10 + sdata(301, cc) / 5);
            }
        }
        if (cc == game_data.mount)
        {
            accuracy =
                accuracy * 100 / clamp((150 - sdata(10, cc) / 2), 115, 150);
            if (attackskill != 106 && attackrange == 0 &&
                weapon->weight >= 4000)
            {
                accuracy -=
                    (weapon->weight - 4000 + 400) / (10 + sdata(10, cc) / 10);
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



int calcattackhit(optional_ref<Item> weapon, optional_ref<Item> ammo)
{
    int tohit = calc_accuracy(weapon, ammo, true);
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
        if (tohit < sdata(187, tc) * 10 && tohit > 0)
        {
            int evaderef = evasion * 100 / clamp(tohit, 1, tohit);
            if (evaderef > 300)
            {
                if (rnd_capped(sdata(187, tc) + 250) > 100)
                {
                    return -2;
                }
            }
            if (evaderef > 200)
            {
                if (rnd_capped(sdata(187, tc) + 250) > 150)
                {
                    return -2;
                }
            }
            if (evaderef > 150)
            {
                if (rnd_capped(sdata(187, tc) + 250) > 200)
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
    if (rnd_capped(tohit) > rnd_capped(evasion * 3 / 2))
    {
        return 1;
    }
    return -1;
}



int calcattackdmg(
    optional_ref<Item> weapon,
    optional_ref<Item> ammo,
    AttackDamageCalculationMode mode)
{
    int damagepierce = 0;
    int damagenormal = 0;
    int pierce;
    if (attackskill == 106)
    {
        dmgfix =
            sdata(10, cc) / 8 + sdata(106, cc) / 8 + cdata[cc].damage_bonus;
        dice1 = 2;
        dice2 = sdata(106, cc) / 8 + 5;
        dmgmulti = 0.5 +
            double(
                (sdata(10, cc) + sdata(attackskill, cc) / 5 +
                 sdata(152, cc) * 2)) /
                40;
        pierce = clamp(sdata(attackskill, cc) / 5, 5, 50);
    }
    else
    {
        dmgfix = cdata[cc].damage_bonus + weapon->damage_bonus +
            weapon->enhancement + (weapon->curse_state == CurseState::blessed);
        dice1 = weapon->dice_x;
        dice2 = weapon->dice_y;
        if (ammo)
        {
            dmgfix += ammo->damage_bonus + ammo->dice_x * ammo->dice_y / 2;
            dmgmulti = 0.5 +
                double(
                    (sdata(13, cc) + sdata(weapon->skill, cc) / 5 +
                     sdata(attackskill, cc) / 5 + sdata(189, cc) * 3 / 2)) /
                    40;
        }
        else
        {
            dmgmulti = 0.6 +
                double(
                    (sdata(10, cc) + sdata(weapon->skill, cc) / 5 +
                     sdata(attackskill, cc) / 5 + sdata(152, cc) * 2)) /
                    45;
        }
        pierce = calc_rate_to_pierce(itemid2int(weapon->id));
    }
    if (attackrange)
    {
        if (mode == AttackDamageCalculationMode::actual_damage)
        {
            const auto effective_range =
                calc_effective_range(itemid2int(weapon->id));
            dmgmulti = dmgmulti * effective_range[rangedist] / 100;
        }
    }
    else if (cdata[cc].combat_style.two_hand())
    {
        if (weapon->weight >= 4000)
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
            dmgfix += 5 + cdata.player().level * 2 / 3;
        }
    }
    if (mode == AttackDamageCalculationMode::raw_damage)
    {
        return damage;
    }
    const auto prot = calc_attack_protection(cdata[tc]);
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
        else if (ammo)
        {
            dmgmulti =
                dmgmulti * clamp(ammo->weight / 100 + 100, 100, 150) / 100;
        }
        else
        {
            dmgmulti =
                dmgmulti * clamp(weapon->weight / 200 + 100, 100, 150) / 100;
        }
    }
    damage = damage * dmgmulti / 100;
    orgdmg = damage;
    if (prot.rate > 0)
    {
        damage = damage * 100 / (100 + prot.rate);
    }
    if (attackrange == 0)
    {
        if (cdata[cc].rate_to_pierce > rnd(100))
        {
            pierce = 100;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.damage.vorpal.melee"),
                    Message::color{ColorIndex::orange});
            }
        }
    }
    else
    {
        if (ammoproc == 2)
        {
            pierce = 60;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.damage.vorpal.ranged"),
                    Message::color{ColorIndex::orange});
            }
        }
        if (ammoprocbk == 0)
        {
            damage /= 2;
        }
        if (ammoprocbk == 5)
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
    if (prot.rate > 0)
    {
        damagenormal -= roll(prot.dice_x, prot.dice_y, 0);
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
        damage = damage * 100 /
            clamp((100 + cdata[tc].decrease_physical_damage), 25, 1000);
    }
    if (damage < 0)
    {
        damage = 0;
    }
    return damage;
}



CalcAttackProtectionResult calc_attack_protection(const Character& chara)
{
    const auto rate = chara.pv + sdata(chara_armor_class(chara), chara.index) +
        sdata(12, chara.index) / 10;
    if (rate <= 0)
    {
        return {0, 1, 1};
    }

    const auto rate2 = rate / 4;
    auto dice_x = rate2 / 10 + 1;
    if (dice_x < 0)
    {
        dice_x = 1;
    }
    const auto dice_y = rate2 / dice_x + 2;
    return {rate, dice_x, dice_y};
}



int calcmedalvalue(const Item& item)
{
    switch (item.id)
    {
    case ItemId::diablo: return 65;
    case ItemId::artifact_seed: return 15;
    case ItemId::scroll_of_growth: return 5;
    case ItemId::scroll_of_faith: return 8;
    case ItemId::rod_of_domination: return 20;
    case ItemId::scroll_of_superior_material: return 7;
    case ItemId::little_sisters_diary: return 12;
    case ItemId::bottle_of_water: return 3;
    case ItemId::potion_of_cure_corruption: return 10;
    case ItemId::presidents_chair: return 20;
    case ItemId::bill: return 5;
    case ItemId::tax_masters_tax_box: return 18;
    case ItemId::cat_sisters_diary: return 85;
    case ItemId::girls_diary: return 25;
    case ItemId::shrine_gate: return 11;
    case ItemId::bottle_of_hermes_blood: return 30;
    case ItemId::sages_helm: return 55;
    case ItemId::license_of_the_void_explorer: return 72;
    case ItemId::garoks_hammer: return 94;
    default: return 1;
    }
}



int calcitemvalue(const Item& item, int calc_mode)
{
    const auto category = the_item_db[itemid2int(item.id)]->category;
    int ret = 0;
    if (item.identify_state == IdentifyState::unidentified)
    {
        if (calc_mode == 2)
        {
            ret = item.value * 4 / 10;
        }
        else
        {
            ret = cdata.player().level / 5 *
                    ((game_data.random_seed + item.index * 31) %
                         cdata.player().level +
                     4) +
                10;
        }
    }
    else if (!is_equipment(category))
    {
        ret = item.value;
    }
    else
    {
        switch (item.identify_state)
        {
        case IdentifyState::unidentified: break;
        case IdentifyState::partly: ret = item.value * 2 / 10; break;
        case IdentifyState::almost: ret = item.value * 5 / 10; break;
        case IdentifyState::completely: ret = item.value; break;
        }
    }
    if (item.identify_state == IdentifyState::completely)
    {
        switch (item.curse_state)
        {
        case CurseState::doomed: ret = ret / 5; break;
        case CurseState::cursed: ret = ret / 2; break;
        case CurseState::none: break;
        case CurseState::blessed: ret = ret * 120 / 100; break;
        }
    }
    if (category == ItemCategory::food)
    {
        if (item.param2 > 0)
        {
            ret = ret * item.param2 * item.param2 / 10;
        }
    }
    if (item.id == ItemId::cargo_travelers_food)
    {
        if (calc_mode == 0)
        {
            ret += clamp(
                cdata.player().fame / 40 +
                    ret * (cdata.player().fame / 80) / 100,
                0,
                800);
        }
    }
    if (item.weight < 0)
    {
        if (mode == 6)
        {
            if (category == ItemCategory::cargo)
            {
                ret = ret * trate(item.param1) / 100;
                if (calc_mode == 1)
                {
                    ret = ret * 65 / 100;
                }
                return ret;
            }
        }
    }
    if (item.has_charge())
    {
        item_db_get_charge_level(item, itemid2int(item.id));
        if (item.count < 0)
        {
            ret = ret / 10;
        }
        else if (category == ItemCategory::spellbook)
        {
            ret = ret / 5 + ret * item.count / (ichargelevel * 2 + 1);
        }
        else
        {
            ret = ret / 2 + ret * item.count / (ichargelevel * 3 + 1);
        }
    }
    if (category == ItemCategory::chest)
    {
        if (item.param1 == 0)
        {
            ret = ret / 100 + 1;
        }
    }
    if (calc_mode == 0)
    {
        int max = ret / 2;
        ret = ret * 100 / (100 + sdata(156, 0));
        if (game_data.guild.belongs_to_mages_guild != 0)
        {
            if (category == ItemCategory::spellbook)
            {
                ret = ret * 80 / 100;
            }
        }
        if (ret <= max)
        {
            ret = max;
        }
    }
    if (calc_mode == 1)
    {
        int max = sdata(156, 0) * 250 + 5000;
        if (ret / 3 < max)
        {
            max = ret / 3;
        }
        ret = ret * (100 + sdata(156, 0) * 5) / 1000;
        if (is_equipment(category))
        {
            ret /= 20;
        }
        if (item.is_stolen())
        {
            if (game_data.guild.belongs_to_thieves_guild == 0)
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
    if (calc_mode == 2)
    {
        ret = ret / 5;
        if (is_equipment(category))
        {
            ret /= 3;
        }
        if (ret > 15000)
        {
            ret = 15000;
        }
        if (item.is_stolen())
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
    int rank = clamp(cdata[tc].shop_rank, 1, 200);
    int ret = rank * rank * 15 + 200;
    if (ret > 500'000)
    {
        ret = 500'000;
    }
    return ret * 100 / (100 + sdata(160, 0) * 10) + 200;
}



int calcguiltvalue()
{
    return -(cdata.player().karma + 30) *
        (cdata.player().fame / 2 + cdata.player().level * 200);
}



int calchireadv(int adventurer)
{
    return 250 + cdata[adventurer].level * cdata[adventurer].level * 30;
}



int calchirecost(int cc)
{
    switch (cdata[cc].role)
    {
    case Role::maid: return 450;
    case Role::trainer: return 250;
    case Role::bartender: return 350;
    case Role::healer: return 500;
    case Role::appraiser: return 750;
    case Role::informer: return 250;
    case Role::guard: return 50;
    case Role::blackmarket_vendor: return 4000;
    case Role::guest_wandering_vendor: return 0;
    default:
        if (is_shopkeeper(cdata[cc].role))
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
    int gold = rnd(100) + rnd_capped(cdata[cc].level * 50 + 1);
    if (is_shopkeeper(cdata[cc].role))
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
    for (auto&& cnt : cdata.others())
    {
        if (cnt.role == Role::none)
            continue;
        if (cnt.state() != Character::State::alive)
            continue;
        cost += calchirecost(cnt.index);
    }
    cost = cost *
        clamp(100 - clamp(cdata.player().karma / 2, 0, 50) - 7 * trait(38) -
                  (cdata.player().karma >= 20) * 5,
              25,
              200) /
        100;
    game_data.cost_to_hire = cost;
}



int calccostbuilding()
{
    int cost = game_data.home_scale * game_data.home_scale * 200;

    for (int cnt = 300; cnt < 450; ++cnt)
    {
        switch (static_cast<mdata_t::MapId>(area_data[cnt].id))
        {
        case mdata_t::MapId::museum: cost += 1500; break;
        case mdata_t::MapId::ranch: cost += 1000; break;
        case mdata_t::MapId::crop: cost += 750; break;
        case mdata_t::MapId::shop: cost += 5000; break;
        case mdata_t::MapId::storage_house: cost += 750; break;
        default: break;
        }
    }

    return cost *
        clamp(100 - clamp(cdata.player().karma / 2, 0, 50) - 7 * trait(38) -
                  (cdata.player().karma >= 20) * 5,
              25,
              200) /
        100;
}



int calccosttax()
{
    int cost{};
    cost += cdata.player().gold / 1000;
    cost += cdata.player().fame;
    cost += cdata.player().level * 200;
    return cost *
        clamp(100 - clamp(cdata.player().karma / 2, 0, 50) - 7 * trait(38) -
                  (cdata.player().karma >= 20) * 5,
              25,
              200) /
        100;
}



int calcmealvalue()
{
    return 140;
}



int calccostreload(int owner, bool do_reload)
{
    int cost{};

    for (auto&& item : inv.for_chara(cdata[owner]))
    {
        if (item.number() == 0)
            continue;
        if (the_item_db[itemid2int(item.id)]->category != ItemCategory::ammo)
            continue;

        for (auto&& enc : item.enchantments)
        {
            if (enc.id == 0)
                break;

            if (enc.id / 10000 == 9)
            {
                int type = enc.id % 10000;
                int current = enc.power % 1000;
                int max = enc.power / 1000;
                cost += (max - current) * (50 + type * type * 10);
                if (do_reload)
                {
                    enc.power = max * 1000 + max;
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
    return (game_data.current_cart_limit - game_data.initial_cart_limit) /
        10000 +
        1;
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
        for (const auto& item : inv.pc())
        {
            if (item.number() == 0)
            {
                continue;
            }
            if (item.identify_state != IdentifyState::completely)
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

    return game_data.guild.belongs_to_fighters_guild ? cost / 2 : cost;
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

    int platinum = 15 + 3 * game_data.number_of_learned_skills_by_trainer;
    return discount ? platinum * 2 / 3 : platinum;
}



int calcresurrectvalue(int pet)
{
    return cdata[pet].state() != Character::State::pet_dead
        ? 100
        : cdata[pet].level * cdata[pet].level * 15;
}



int calcslavevalue(int pet)
{
    int value = sdata(10, pet) * sdata(11, pet) +
        cdata[pet].level * cdata[pet].level + 1000;
    if (value > 50'000)
    {
        value = 50'000;
    }
    if (cdata[pet].splits() || cdata[pet].splits2())
    {
        value = 10;
    }
    return value;
}



int calcrestorecost()
{
    return game_data.guild.belongs_to_fighters_guild ? 250 : 500;
}



int calcinitgold(int owner)
{
    if (owner < 0)
    {
        return rnd_capped(
                   game_data.current_dungeon_level * 25 *
                       (game_data.current_map != mdata_t::MapId::shelter_) +
                   10) +
            1;
    }

    switch (charaid2int(cdata[owner].id))
    {
    case 183: return 5000 + rnd(11000);
    case 184: return 2000 + rnd(5000);
    case 185: return 1000 + rnd(3000);
    default: return rnd_capped(cdata[owner].level * 25 + 10) + 1;
    }
}



int calcspellpower(int id, int cc)
{
    if (id >= 600)
    {
        if (the_ability_db[id]->related_basic_attribute != 0)
        {
            return sdata(the_ability_db[id]->related_basic_attribute, cc) * 6 +
                10;
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
        if (game_data.mount == cc)
        {
            return 95 - clamp(30 - sdata(301, 0) / 2, 0, 30);
        }
        else
        {
            return 95;
        }
    }

    int penalty = 4;

    int armor_skill = chara_armor_class(cdata[cc]);
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
    if (game_data.mount != 0)
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

    int percentage = 90 + sdata(id, cc) -
        the_ability_db[id]->difficulty * penalty / (5 + sdata(172, cc) * 4);
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
    if (cdata[cc].combat_style.dual_wield())
    {
        percentage -= 6;
    }
    if (cdata[cc].combat_style.shield())
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
        if (id == 413 || id == 461 || id == 457 || id == 438 || id == 409 ||
            id == 408 || id == 410 || id == 466)
        {
            return the_ability_db[id]->cost;
        }
        else
        {
            return the_ability_db[id]->cost * (100 + sdata(id, cc) * 3) / 100 +
                sdata(id, cc) / 8;
        }
    }
    else
    {
        return the_ability_db[id]->cost * (50 + cdata[cc].level * 3) / 100;
    }
}



int calcspellcoststock(int id, int cc)
{
    if (debug::voldemort)
        return 1;

    int cost = the_ability_db[id]->cost * 200 / (sdata(id, cc) * 3 + 100);
    if (cost < the_ability_db[id]->cost / 5)
    {
        cost = the_ability_db[id]->cost / 5;
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
    int score = cdata.player().level * cdata.player().level +
        game_data.deepest_dungeon_level * game_data.deepest_dungeon_level +
        game_data.kill_count;
    if (game_data.death_count > 1)
    {
        score = score / 10 + 1;
    }
    if (game_data.wizard)
    {
        score = 0;
    }
    return score;
}



void calcpartyscore()
{
    int score = 0;
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (cnt.impression >= 53)
        {
            score += cnt.level + 5;
        }
        if (cnt.impression < 50)
        {
            score -= 20;
        }
    }
    if (score > quest_data.immediate().extra_info_2)
    {
        txt(u8"(+"s + (score - quest_data.immediate().extra_info_2) + u8") "s,
            Message::color{ColorIndex::blue});
    }
    if (score < quest_data.immediate().extra_info_2)
    {
        txt(u8"("s + (score - quest_data.immediate().extra_info_2) + u8") "s,
            Message::color{ColorIndex::red});
    }
    quest_data.immediate().extra_info_2 = score;
}



void calcpartyscore2()
{
    int score{};
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (cnt.impression >= 53 && cnt.quality >= Quality::miracle)
        {
            score += 20 + cnt.level / 2;
            txt(i18n::s.get("core.quest.party.is_satisfied", cnt));
        }
    }
    if (score != 0)
    {
        txt(i18n::s.get("core.quest.party.total_bonus", score));
    }
    quest_data.immediate().extra_info_2 =
        quest_data.immediate().extra_info_2 * (100 + score) / 100;
}


int generate_color(ColorIndex index, int id)
{
    int color = static_cast<int>(index);
    if (index == ColorIndex::random_furniture)
    {
        color = choice(furniture_random_colors);
    }
    if (index == ColorIndex::random_seeded)
    {
        // The choice can't be completely random - it has to be the
        // same as all other items of this type. So, base it off the
        // random seed of the current save data.
        const auto index =
            (id + game_data.random_seed) % item_random_colors.size();
        color = item_random_colors.at(index);
    }
    if (index == ColorIndex::random_any)
    {
        color = rnd(21);
    }

    // Only accept the first 21 color indices, as the ones after that are
    // used for random generation.
    return color % 21;
}



int calc_potential_on_gain(int potential)
{
    return static_cast<int>(potential * 1.1) + 1;
}

int calc_potential_on_loss(int potential)
{
    return static_cast<int>(potential * 0.9);
}

int calc_initial_skill_base_potential(
    int skill_id,
    int original_level,
    int initial_level)
{
    int potential{};

    // Excludes resistance and attributes.
    bool is_skill_or_spell = skill_id >= 100;

    if (is_skill_or_spell)
    {
        potential = initial_level * 5;
        if (original_level == 0)
        {
            potential += 100;
        }
        else
        {
            potential += 50;
        }
    }
    else
    {
        potential = initial_level * 20;
        if (potential > 400)
        {
            potential = 400;
        }
    }

    return potential;
}

int calc_initial_skill_level_speed(int initial_level, int chara_level)
{
    return initial_level * (100 + chara_level * 2) / 100;
}

int calc_initial_skill_level(int initial_level, int chara_level, int potential)
{
    return potential * potential * chara_level / 45000 + initial_level +
        chara_level / 3;
}

int calc_initial_skill_decayed_potential(int chara_level, int potential)
{
    if (chara_level <= 1)
    {
        return potential;
    }

    return std::exp(std::log(0.9) * chara_level) * potential;
}

int calc_initial_resistance_level(
    const Character& chara,
    int initial_level,
    int element_id)
{
    if (chara.index == 0)
    {
        return 100;
    }

    int level = chara.level * 4 + 96;
    if (level > 300)
    {
        level = 300;
    }
    if (initial_level != 0)
    {
        if (initial_level < 100 || initial_level >= 500)
        {
            level = initial_level;
        }
        else
        {
            level += initial_level;
        }
    }
    if (element_id == 60 && level < 500)
    {
        level = 100;
    }

    return level;
}

int calc_skill_related_attribute_exp(int experience, int divisor)
{
    return experience / (2 + divisor);
}

int calc_base_skill_exp_gained(
    int base_experience,
    int potential,
    int skill_level)
{
    return base_experience * potential / (100 + skill_level * 15);
}

int calc_boosted_skill_exp_gained(int experience, int buff_amount)
{
    if (buff_amount <= 0)
    {
        return experience;
    }

    return experience * (100 + buff_amount) / 100;
}

int calc_chara_exp_from_skill_exp(
    const Character& chara,
    int skill_exp,
    int divisor)
{
    return rnd_capped(
               int(double(chara.required_experience) * skill_exp / 1000 /
                   (chara.level + divisor)) +
               1) +
        rnd(2);
}

int calc_exp_gain_negotiation_gold_threshold(int current_level)
{
    return (current_level + 10) * (current_level + 10);
}

int calc_exp_gain_negotiation(int coefficient, int current_level)
{
    return clamp(
        coefficient * coefficient / (current_level * 5 + 10), 10, 1000);
}

int calc_exp_gain_detection(int dungeon_level)
{
    return dungeon_level * 2 + 20;
}

int calc_spell_exp_gain(int spell_id)
{
    return the_ability_db[spell_id]->cost * 4 + 20;
}

int calc_exp_gain_casting(int spell_id)
{
    return the_ability_db[spell_id]->cost + 10;
}

int calc_exp_gain_mana_capacity(const Character& chara)
{
    return std::abs(chara.mp) * 200 / (chara.max_mp + 1);
}

int calc_exp_gain_healing(const Character& chara)
{
    if (chara.hp != chara.max_hp)
    {
        if (sdata(154, chara.index) < sdata(11, chara.index))
        {
            return 5 + sdata(154, chara.index) / 5;
        }
    }

    return 0;
}

int calc_exp_gain_meditation(const Character& chara)
{
    if (chara.mp != chara.max_mp)
    {
        if (sdata(155, chara.index) < sdata(16, chara.index))
        {
            return 5 + sdata(155, chara.index) / 5;
        }
    }

    return 0;
}

int calc_exp_gain_stealth()
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (rnd(20))
        {
            return 0;
        }
    }

    return 2;
}

int calc_exp_gain_weight_lifting(const Character& chara)
{
    if (chara.inventory_weight_type == 0)
    {
        return 0;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (rnd(20))
        {
            return 0;
        }
    }

    return 4;
}

int calc_exp_gain_memorization(int spell_id)
{
    return 10 + the_ability_db[spell_id]->difficulty / 5;
}

int calc_exp_gain_crafting(int mat_amount)
{
    return 50 + mat_amount * 20;
}

} // namespace elona
