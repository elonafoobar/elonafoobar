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



namespace elona
{

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



void status_ailment_damage(
    Character& chara,
    StatusAilment status_ailment,
    int power)
{
    if (power <= 0)
        return;

    int turn{};

    switch (status_ailment)
    {
    case StatusAilment::blinded:
        if (chara.is_immune_to_blindness())
            return;
        if (chara.quality > Quality::great && rnd(chara.level / 2 + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::darkness);
        turn = power / 6;
        if (turn <= 0)
            return;
        if (chara.blind == 0)
        {
            chara.blind = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.blinded.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.blind += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::confused:
        if (chara.is_immune_to_confusion())
            return;
        if (buff_has(chara, "core.hero"))
            return;
        if (chara.quality > Quality::great && rnd(chara.level / 2 + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::mind);
        turn = power / 7;
        if (turn <= 0)
            return;
        if (chara.confused == 0)
        {
            chara.confused = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.confused.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.confused += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::paralyzed:
        if (chara.is_immune_to_paralyzation())
            return;
        if (chara.quality > Quality::great && rnd(chara.level + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::nerve);
        turn = power / 10;
        if (turn <= 0)
            return;
        if (chara.paralyzed == 0)
        {
            chara.paralyzed = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.paralyzed.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.paralyzed += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::poisoned:
        if (chara.is_immune_to_poison())
            return;
        if (chara.quality > Quality::great && rnd(chara.level / 3 + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::poison);
        turn = power / 5;
        if (turn <= 0)
            return;
        if (chara.poisoned == 0)
        {
            chara.poisoned = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.poisoned.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.poisoned += turn / 3 + 3;
        }
        chara.activity.finish();
        return;
    case StatusAilment::sleep:
        if (chara.is_immune_to_sleep())
            return;
        if (chara.quality > Quality::great && rnd(chara.level / 5 + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::nerve);
        turn = power / 4;
        if (turn <= 0)
            return;
        if (chara.sleep == 0)
        {
            chara.sleep = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.sleep.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.sleep += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::fear:
        if (chara.is_immune_to_fear())
            return;
        if (buff_has(chara, "core.holy_shield"))
            return;
        if (buff_has(chara, "core.hero"))
            return;
        if (chara.quality > Quality::great && rnd(chara.level / 5 + 1))
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::mind);
        turn = power / 7;
        if (turn <= 0)
            return;
        if (chara.fear == 0)
        {
            chara.fear = turn;
        }
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.status_ailment.message.fear.apply", chara));
        }
        return;
    case StatusAilment::dimmed:
        if (chara.quality > Quality::great && rnd(chara.level / 3 + 1))
            return;
        if (cdatan(2, chara.index) == u8"golem"s)
            return;
        power = calc_power_decreased_by_resistance(
            chara.index, power, Element::sound);
        turn = power / 8;
        if (turn <= 0)
            return;
        if (chara.dimmed == 0)
        {
            chara.dimmed = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.dimmed.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.dimmed += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::bleeding:
        if (chara.quality > Quality::great)
        {
            power /= 2;
        }
        turn = power / 25;
        if (turn <= 0)
            return;
        if (chara.bleeding == 0)
        {
            chara.bleeding = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.bleeding.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.bleeding += turn;
        }
        chara.activity.finish();
        return;
    case StatusAilment::drunk:
        turn = power / 10;
        if (turn <= 0)
            return;
        if (chara.drunk == 0)
        {
            chara.drunk = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                    "core.status_ailment.message.drunk.apply", chara));
            }
        }
        else
        {
            chara.drunk += turn;
        }
        return;
    case StatusAilment::insane:
        turn = power / 8;
        if (turn <= 0)
            return;
        if (chara.insane == 0)
        {
            chara.insane = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.insane.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.insane += turn / 3 + 1;
        }
        chara.activity.finish();
        return;
    case StatusAilment::sick:
        turn = power / 10;
        if (turn <= 0)
            return;
        if (chara.sick == 0)
        {
            chara.sick = turn;
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                        "core.status_ailment.message.sick.apply", chara),
                    Message::color{ColorIndex::purple});
            }
        }
        else
        {
            chara.sick += turn / 10 + 1;
        }
        return;
    default:
        throw std::runtime_error{u8"Unknown status ailment: "s +
                                 int(status_ailment)};
    }
}



void status_ailment_heal(
    Character& chara,
    StatusAilment status_ailment,
    int power)
{
    switch (status_ailment)
    {
    case StatusAilment::fear:
        if (chara.fear > 0)
        {
            if (power == 0)
            {
                chara.fear = 0;
            }
            else
            {
                chara.fear -= power;
            }
            if (chara.fear <= 0)
            {
                chara.fear = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.fear.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::blinded:
        if (chara.blind > 0)
        {
            if (power == 0)
            {
                chara.blind = 0;
            }
            else
            {
                chara.blind -= power;
            }
            if (chara.blind <= 0)
            {
                chara.blind = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.blinded.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::confused:
        if (chara.confused > 0)
        {
            if (power == 0)
            {
                chara.confused = 0;
            }
            else
            {
                chara.confused -= power;
            }
            if (chara.confused <= 0)
            {
                chara.confused = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.confused.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::paralyzed:
        if (chara.paralyzed > 0)
        {
            if (power == 0)
            {
                chara.paralyzed = 0;
            }
            else
            {
                chara.paralyzed -= power;
            }
            if (chara.paralyzed <= 0)
            {
                chara.paralyzed = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.paralyzed.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::poisoned:
        if (chara.poisoned > 0)
        {
            if (power == 0)
            {
                chara.poisoned = 0;
            }
            else
            {
                chara.poisoned -= power;
            }
            if (chara.poisoned <= 0)
            {
                chara.poisoned = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.poisoned.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::sleep:
        if (chara.sleep > 0)
        {
            if (power == 0)
            {
                chara.sleep = 0;
            }
            else
            {
                chara.sleep -= power;
            }
            if (chara.sleep <= 0)
            {
                chara.sleep = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.sleep.heal", chara));
                }
            }
            return;
        }
        break;
    case StatusAilment::dimmed:
        if (chara.dimmed > 0)
        {
            if (power == 0)
            {
                chara.dimmed = 0;
            }
            else
            {
                chara.dimmed -= power;
            }
            if (chara.dimmed <= 0)
            {
                chara.dimmed = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.dimmed.heal", chara));
                }
            }
        }
        break;
    case StatusAilment::bleeding:
        if (chara.bleeding > 0)
        {
            if (power == 0)
            {
                chara.bleeding = 0;
            }
            else
            {
                chara.bleeding -= power;
            }
            if (chara.bleeding <= 0)
            {
                chara.bleeding = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.bleeding.heal", chara));
                }
            }
        }
        break;
    case StatusAilment::drunk:
        if (chara.drunk > 0)
        {
            if (power == 0)
            {
                chara.drunk = 0;
            }
            else
            {
                chara.drunk -= power;
            }
            if (chara.drunk <= 0)
            {
                chara.drunk = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.drunk.heal", chara));
                }
            }
        }
        break;
    case StatusAilment::insane:
        if (chara.insane > 0)
        {
            if (power == 0)
            {
                chara.insane = 0;
            }
            else
            {
                chara.insane -= power;
            }
            if (chara.insane <= 0)
            {
                chara.insane = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.insane.heal", chara));
                }
            }
        }
        break;
    case StatusAilment::sick:
        if (chara.sick > 0)
        {
            if (power == 0)
            {
                chara.sick = 0;
            }
            else
            {
                chara.sick -= power;
            }
            if (chara.sick <= 0)
            {
                chara.sick = 0;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get(
                        "core.status_ailment.message.sick.heal", chara));
                }
            }
        }
        break;
    default:
        throw std::runtime_error{u8"Unknown status ailment: "s +
                                 int(status_ailment)};
    }
}

} // namespace elona
