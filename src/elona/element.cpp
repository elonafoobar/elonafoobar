#include "element.hpp"

#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "message.hpp"
#include "random.hpp"
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
        for (int cnt = 0, cnt_end = (the_ability_db[p_at_m45]->difficulty);
             cnt < cnt_end;
             ++cnt)
        {
            i_at_m45 = rnd(11) + 50;
            if (the_ability_db[i_at_m45]->difficulty <
                the_ability_db[p_at_m45]->difficulty)
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
    return u8"?"s;
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



void resistmod(int cc, int element, int delta)
{
    if (delta >= 50)
    {
        if (auto text = i18n::s.get_enum_optional(
                "core.element.resist.gain", element, cdata[cc]))
        {
            txt(*text, Message::color{ColorIndex::green});
        }
        else
        {
            assert(false);
        }
    }
    else if (delta <= 50 * -1)
    {
        if (auto text = i18n::s.get_enum_optional(
                "core.element.resist.lose", element, cdata[cc]))
        {
            txt(*text, Message::color{ColorIndex::purple});
        }
        else
        {
            assert(false);
        }
    }

    sdata.get(element, cc).original_level =
        clamp(sdata.get(element, cc).original_level + delta, 50, 200);
    snd("core.atk_elec");
    animeload(15, cc);

    chara_refresh(cc);
}



void txteledmg(int type, int attacker, int target, int element)
{
    if (type == 0 && is_in_fov(cdata[target]))
    {
        auto text = i18n::s.get_enum_optional(
            "core.element.damage"s, element, cdata[target]);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get("core.element.damage.default", cdata[target]));
        }
    }
    else if (type == 1)
    {
        auto text = i18n::s.get_enum_property_optional(
            "core.death_by.element"s,
            "active",
            element,
            cdata[target],
            cdata[attacker]);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get(
                "core.death_by.element.default.active",
                cdata[target],
                cdata[attacker]));
        }
    }
    else if (type == 2)
    {
        auto text = i18n::s.get_enum_property_optional(
            "core.death_by.element"s,
            "passive",
            element,
            cdata[target],
            cdata[attacker]);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get(
                "core.death_by.element.default.passive",
                cdata[target],
                cdata[attacker]));
        }
    }
}



} // namespace elona
