#include "element.hpp"

#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "data/types/type_skill.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "message.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "variables.hpp"



namespace elona
{



int randomele()
{
    int p_at_m45 = 0;
    int i_at_m45 = 0;
    p_at_m45 = rnd(11) + 50;
    if (p_at_m45 != 1)
    {
        for (int cnt = 0, cnt_end = (the_skill_db[p_at_m45]->difficulty);
             cnt < cnt_end;
             ++cnt)
        {
            i_at_m45 = rnd(11) + 50;
            if (the_skill_db[i_at_m45]->difficulty <
                the_skill_db[p_at_m45]->difficulty)
            {
                if (rnd(2) == 0)
                {
                    p_at_m45 = i_at_m45;
                }
            }
        }
    }
    return p_at_m45;
}



std::string elename(int ele)
{
    if (efid == 614)
    {
        return i18n::s.get("core.element.name.starving");
    }
    if (efid == 613)
    {
        return i18n::s.get("core.element.name.rotten");
    }
    if (efid == 617)
    {
        return i18n::s.get("core.element.name.fearful");
    }
    if (efid == 618)
    {
        return i18n::s.get("core.element.name.silky");
    }
    if (auto text = i18n::s.get_enum_optional("core.element.name", ele))
    {
        return *text;
    }
    return "?"s;
}



int element_color_id(int element_id)
{
    switch (element_id)
    {
    case 50: return 3;
    case 51: return 12;
    case 52: return 5;
    case 59: return 8;
    case 53: return 4;
    case 58: return 9;
    case 57: return 11;
    case 54: return 10;
    case 55: return 2;
    case 56: return 7;
    case 63: return 2;
    }

    return 0;
}



void chara_gain_registance(Character& chara, int element, int delta)
{
    if (delta >= 50)
    {
        txt(i18n::s.get_enum("core.element.resist.gain", element, chara),
            Message::color{ColorIndex::green});
    }
    else if (delta <= -50)
    {
        txt(i18n::s.get_enum("core.element.resist.lose", element, chara),
            Message::color{ColorIndex::purple});
    }

    chara.skills().set_base_level(
        *the_skill_db.get_id_from_integer(element),
        clamp(
            chara.skills().base_level(
                *the_skill_db.get_id_from_integer(element)) +
                delta,
            50,
            200));
    snd("core.atk_elec");
    animeload(15, chara);

    chara_refresh(chara);
}



void txteledmg(
    int type,
    optional_ref<const Character> attacker,
    const Character& target,
    int element)
{
    if (type == 0 && is_in_fov(target))
    {
        auto text =
            i18n::s.get_enum_optional("core.element.damage"s, element, target);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get("core.element.damage.default", target));
        }
    }
    else if (type == 1)
    {
        if (attacker)
        {
            auto text = i18n::s.get_enum_property_optional(
                "core.death_by.element"s,
                "active.by_chara",
                element,
                target,
                *attacker);
            if (text)
            {
                txt(*text);
            }
            else
            {
                txt(i18n::s.get(
                    "core.death_by.element.default.active.by_chara",
                    target,
                    *attacker));
            }
        }
        else
        {
            auto text = i18n::s.get_enum_property_optional(
                "core.death_by.element"s, "active.by_spell", element, target);
            if (text)
            {
                txt(*text);
            }
            else
            {
                txt(i18n::s.get(
                    "core.death_by.element.default.active.by_spell", target));
            }
        }
    }
    else if (type == 2)
    {
        auto text = i18n::s.get_enum_property_optional(
            "core.death_by.element"s, "passive", element, target);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get("core.death_by.element.default.passive", target));
        }
    }
}



} // namespace elona
