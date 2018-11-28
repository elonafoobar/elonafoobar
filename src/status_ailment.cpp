#include "status_ailment.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "buff.hpp"
#include "character.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "map.hpp"
#include "message.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace
{


int calc_power_decreased_by_resistance(int cc, int power, Element element)
{
    const auto resistance_level = sdata(int(element), cc) / 50;
    power =
        (rnd(power / 2 + 1) + power / 2) * 100 / (50 + resistance_level * 50);

    if (resistance_level >= 3 && power < 40)
    {
        return 0;
    }
    else
    {
        return power;
    }
}


} // namespace



namespace elona
{



void dmgcon(int cc, StatusAilment status_ailment, int power)
{
    if (power <= 0)
        return;

    int turn{};

    switch (status_ailment)
    {
    case StatusAilment::blinded:
        if (cdata[cc].is_immune_to_blindness())
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 2 + 1))
            return;
        power =
            calc_power_decreased_by_resistance(cc, power, Element::darkness);
        turn = power / 6;
        if (turn <= 0)
            return;
        if (cdata[cc].blind == 0)
        {
            cdata[cc].blind = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.blinded.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].blind += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::confused:
        if (cdata[cc].is_immune_to_confusion())
            return;
        if (buff_has(cdata[cc], 7))
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 2 + 1))
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::mind);
        turn = power / 7;
        if (turn <= 0)
            return;
        if (cdata[cc].confused == 0)
        {
            cdata[cc].confused = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.confused.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].confused += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::paralyzed:
        if (cdata[cc].is_immune_to_paralyzation())
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level + 1))
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::nerve);
        turn = power / 10;
        if (turn <= 0)
            return;
        if (cdata[cc].paralyzed == 0)
        {
            cdata[cc].paralyzed = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.paralyzed.apply",
                        cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].paralyzed += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::poisoned:
        if (cdata[cc].is_immune_to_poison())
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 3 + 1))
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::poison);
        turn = power / 5;
        if (turn <= 0)
            return;
        if (cdata[cc].poisoned == 0)
        {
            cdata[cc].poisoned = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.poisoned.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].poisoned += turn / 3 + 3;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::sleep:
        if (cdata[cc].is_immune_to_sleep())
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 5 + 1))
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::nerve);
        turn = power / 4;
        if (turn <= 0)
            return;
        if (cdata[cc].sleep == 0)
        {
            cdata[cc].sleep = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.sleep.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].sleep += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::fear:
        if (cdata[cc].is_immune_to_fear())
            return;
        if (buff_has(cdata[cc], 1))
            return;
        if (buff_has(cdata[cc], 7))
            return;
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 5 + 1))
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::mind);
        turn = power / 7;
        if (turn <= 0)
            return;
        if (cdata[cc].fear == 0)
        {
            cdata[cc].fear = turn;
        }
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.status_ailment.fear.apply", cdata[cc]));
        }
        return;
    case StatusAilment::dimmed:
        if (cdata[cc].quality > Quality::great && rnd(cdata[cc].level / 3 + 1))
            return;
        if (cdatan(2, cc) == u8"golem"s)
            return;
        power = calc_power_decreased_by_resistance(cc, power, Element::sound);
        turn = power / 8;
        if (turn <= 0)
            return;
        if (cdata[cc].dimmed == 0)
        {
            cdata[cc].dimmed = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.dimmed.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].dimmed += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::bleeding:
        if (cdata[cc].quality > Quality::great)
        {
            power /= 2;
        }
        turn = power / 25;
        if (turn <= 0)
            return;
        if (cdata[cc].bleeding == 0)
        {
            cdata[cc].bleeding = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.bleeding.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].bleeding += turn;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::drunk:
        turn = power / 10;
        if (turn <= 0)
            return;
        if (cdata[cc].drunk == 0)
        {
            cdata[cc].drunk = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.locale.status_ailment.drunk.apply", cdata[cc]));
            }
        }
        else
        {
            cdata[cc].drunk += turn;
        }
        return;
    case StatusAilment::insane:
        turn = power / 8;
        if (turn <= 0)
            return;
        if (cdata[cc].insane == 0)
        {
            cdata[cc].insane = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.insane.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].insane += turn / 3 + 1;
        }
        cdata[cc].continuous_action.finish();
        return;
    case StatusAilment::sick:
        turn = power / 10;
        if (turn <= 0)
            return;
        if (cdata[cc].sick == 0)
        {
            cdata[cc].sick = turn;
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                        "core.locale.status_ailment.sick.apply", cdata[cc]),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            cdata[cc].sick += turn / 10 + 1;
        }
        return;
    default:
        throw std::runtime_error{u8"Unknown status ailment: "s +
                                 int(status_ailment)};
    }
}



void healcon(int prm_827, int prm_828, int prm_829)
{
    if (prm_828 == 6)
    {
        if (cdata[prm_827].fear > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].fear = 0;
            }
            else
            {
                cdata[prm_827].fear -= prm_829;
            }
            if (cdata[prm_827].fear <= 0)
            {
                cdata[prm_827].fear = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.fear.heal", cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 4)
    {
        if (cdata[prm_827].blind > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].blind = 0;
            }
            else
            {
                cdata[prm_827].blind -= prm_829;
            }
            if (cdata[prm_827].blind <= 0)
            {
                cdata[prm_827].blind = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.blinded.heal", cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 5)
    {
        if (cdata[prm_827].confused > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].confused = 0;
            }
            else
            {
                cdata[prm_827].confused -= prm_829;
            }
            if (cdata[prm_827].confused <= 0)
            {
                cdata[prm_827].confused = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.confused.heal", cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 3)
    {
        if (cdata[prm_827].paralyzed > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].paralyzed = 0;
            }
            else
            {
                cdata[prm_827].paralyzed -= prm_829;
            }
            if (cdata[prm_827].paralyzed <= 0)
            {
                cdata[prm_827].paralyzed = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.paralyzed.heal",
                        cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 1)
    {
        if (cdata[prm_827].poisoned > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].poisoned = 0;
            }
            else
            {
                cdata[prm_827].poisoned -= prm_829;
            }
            if (cdata[prm_827].poisoned <= 0)
            {
                cdata[prm_827].poisoned = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.poisoned.heal", cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 2)
    {
        if (cdata[prm_827].sleep > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].sleep = 0;
            }
            else
            {
                cdata[prm_827].sleep -= prm_829;
            }
            if (cdata[prm_827].sleep <= 0)
            {
                cdata[prm_827].sleep = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.sleep.heal", cdata[cc]));
                }
            }
            return;
        }
    }
    if (prm_828 == 7)
    {
        if (cdata[prm_827].dimmed > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].dimmed = 0;
            }
            else
            {
                cdata[prm_827].dimmed -= prm_829;
            }
            if (cdata[prm_827].dimmed <= 0)
            {
                cdata[prm_827].dimmed = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.dimmed.heal", cdata[cc]));
                }
            }
        }
    }
    if (prm_828 == 9)
    {
        if (cdata[prm_827].bleeding > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].bleeding = 0;
            }
            else
            {
                cdata[prm_827].bleeding -= prm_829;
            }
            if (cdata[prm_827].bleeding <= 0)
            {
                cdata[prm_827].bleeding = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.bleeding.heal", cdata[cc]));
                }
            }
        }
    }
    if (prm_828 == 8)
    {
        if (cdata[prm_827].drunk > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].drunk = 0;
            }
            else
            {
                cdata[prm_827].drunk -= prm_829;
            }
            if (cdata[prm_827].drunk <= 0)
            {
                cdata[prm_827].drunk = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.drunk.heal", cdata[cc]));
                }
            }
        }
    }
    if (prm_828 == 11)
    {
        if (cdata[prm_827].insane > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].insane = 0;
            }
            else
            {
                cdata[prm_827].insane -= prm_829;
            }
            if (cdata[prm_827].insane <= 0)
            {
                cdata[prm_827].insane = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.insane.heal", cdata[cc]));
                }
            }
        }
    }
    if (prm_828 == 12)
    {
        if (cdata[prm_827].sick > 0)
        {
            if (prm_829 == 0)
            {
                cdata[prm_827].sick = 0;
            }
            else
            {
                cdata[prm_827].sick -= prm_829;
            }
            if (cdata[prm_827].sick <= 0)
            {
                cdata[prm_827].sick = 0;
                if (is_in_fov(cdata[prm_827]))
                {
                    txt(i18n::s.get(
                        "core.locale.status_ailment.sick.heal", cdata[cc]));
                }
            }
        }
    }
}



} // namespace elona
