#include "element.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
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
        for (int cnt = 0, cnt_end = (the_ability_db[p_at_m45]->sdataref4);
             cnt < cnt_end;
             ++cnt)
        {
            i_at_m45 = rnd(11) + 50;
            if (the_ability_db[i_at_m45]->sdataref4
                < the_ability_db[p_at_m45]->sdataref4)
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
        return i18n::s.get("core.locale.element.name.starving");
    }
    if (efid == 613)
    {
        return i18n::s.get("core.locale.element.name.rotten");
    }
    if (efid == 617)
    {
        return i18n::s.get("core.locale.element.name.fearful");
    }
    if (efid == 618)
    {
        return i18n::s.get("core.locale.element.name.silky");
    }
    if (auto text = i18n::s.get_enum_optional("core.locale.element.name", ele))
    {
        return *text;
    }
    return u8"?"s;
}



int eleinfo(int prm_754, int prm_755)
{
    if (prm_754 == 50)
    {
        if (prm_755 == 0)
        {
            return 3;
        }
        else
        {
            return 108;
        }
    }
    if (prm_754 == 51)
    {
        if (prm_755 == 0)
        {
            return 12;
        }
        else
        {
            return 106;
        }
    }
    if (prm_754 == 52)
    {
        if (prm_755 == 0)
        {
            return 5;
        }
        else
        {
            return 107;
        }
    }
    if (prm_754 == 59)
    {
        if (prm_755 == 0)
        {
            return 8;
        }
        else
        {
            return 114;
        }
    }
    if (prm_754 == 53)
    {
        if (prm_755 == 0)
        {
            return 4;
        }
        else
        {
            return 115;
        }
    }
    if (prm_754 == 58)
    {
        if (prm_755 == 0)
        {
            return 9;
        }
        else
        {
            return 111;
        }
    }
    if (prm_754 == 57)
    {
        if (prm_755 == 0)
        {
            return 11;
        }
        else
        {
            return 112;
        }
    }
    if (prm_754 == 54)
    {
        if (prm_755 == 0)
        {
            return 10;
        }
        else
        {
            return 113;
        }
    }
    if (prm_754 == 55)
    {
        if (prm_755 == 0)
        {
            return 2;
        }
        else
        {
            return 110;
        }
    }
    if (prm_754 == 56)
    {
        if (prm_755 == 0)
        {
            return 7;
        }
        else
        {
            return 109;
        }
    }
    if (prm_754 == 63)
    {
        if (prm_755 == 0)
        {
            return 2;
        }
        else
        {
            return 110;
        }
    }
    return 0;
}



void resistmod(int cc, int element, int delta)
{
    if (delta >= 50)
    {
        txtef(2);
        if (auto text = i18n::s.get_enum_optional(
                "core.locale.element.resist.gain", element, cdata[cc]))
        {
            txt(*text);
        }
        else
        {
            assert(false);
        }
    }
    else if (delta <= 50 * -1)
    {
        txtef(8);
        if (auto text = i18n::s.get_enum_optional(
                "core.locale.element.resist.lose", element, cdata[cc]))
        {
            txt(*text);
        }
        else
        {
            assert(false);
        }
    }

    sdata.get(element, cc).original_level =
        clamp(sdata.get(element, cc).original_level + delta, 50, 200);
    snd(107);
    animeload(15, cc);

    chara_refresh(cc);
}



void txteledmg(int type, int attacker, int target, int element)
{
    if (type == 0 && is_in_fov(cdata[target]))
    {
        auto text = i18n::s.get_enum_optional(
            "core.locale.element.damage"s, element, cdata[target]);
        if (text)
        {
            txt(*text);
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.element.damage.default", cdata[target]));
        }
    }
    else if (type == 1)
    {
        auto text = i18n::s.get_enum_property_opt(
            "core.locale.death_by.element"s,
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
                "core.locale.death_by.element.default.active",
                cdata[target],
                cdata[attacker]));
        }
    }
    else if (type == 2)
    {
        auto text = i18n::s.get_enum_property_opt(
            "core.locale.death_by.element"s,
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
                "core.locale.death_by.element.default.passive",
                cdata[target],
                cdata[attacker]));
        }
    }
}



} // namespace elona
