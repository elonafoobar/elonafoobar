#include "character_status.hpp"
#include "ability.hpp"
#include "adventurer.hpp"
#include "character.hpp"
#include "config.hpp"
#include "fov.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "variables.hpp"

namespace elona
{

void modcorrupt(int prm_815)
{
    int org_at_m134 = 0;
    int p_at_m134 = 0;
    int mod_at_m134 = 0;
    int cnt2_at_m134 = 0;
    int i_at_m134 = 0;
    org_at_m134 = gdata_ether_disease_stage / 1000;
    p_at_m134 = prm_815 + (prm_815 > 0) * gdata_ether_disease_speed;
    if (trait(168))
    {
        if (prm_815 > 0)
        {
            p_at_m134 = p_at_m134 * 100 / 150;
        }
    }
    gdata_ether_disease_stage += p_at_m134;
    if (gdata_ether_disease_stage < 0)
    {
        gdata_ether_disease_stage = 0;
    }
    mod_at_m134 = gdata_ether_disease_stage / 1000 - org_at_m134;
    if (mod_at_m134 > 0)
    {
        if (org_at_m134 == 0)
        {
            txtef(8);
            txt(i18n::s.get("core.locale.chara.corruption.symptom"));
            if (config::instance().extrahelp)
            {
                if (gdata(215) == 0)
                {
                    if (mode == 0)
                    {
                        if (cdata[0].continuous_action_turn == 0)
                        {
                            gdata(215) = 1;
                            ghelp = 15;
                            show_ex_help();
                        }
                    }
                }
            }
        }
        if (org_at_m134 + mod_at_m134 >= 20)
        {
            p_at_m134 = 20 - org_at_m134;
        }
        else
        {
            p_at_m134 = mod_at_m134;
        }
        for (int cnt = 0, cnt_end = (p_at_m134); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            if (org_at_m134 + cnt2_at_m134 > 20)
            {
                break;
            }
            for (int cnt = 0; cnt < 100000; ++cnt)
            {
                int tid = rnd(17) + 200;
                int stat = trait_get_info(0, tid);
                if (stat == 0 || traitref != 3)
                {
                    continue;
                }
                if (trait(tid) <= traitref(1))
                {
                    continue;
                }
                --trait(tid);
                i_at_m134 = 700 + org_at_m134 + cnt2_at_m134;
                gdata(i_at_m134) = tid;
                txtef(8);
                txt(i18n::s.get("core.locale.chara.corruption.add"));
                txtef(3);
                txt(traitrefn(1));
                if (tid == 203)
                {
                    body = 9;
                    lost_body_part(0);
                }
                if (tid == 205)
                {
                    body = 3;
                    lost_body_part(0);
                }
                if (tid == 206)
                {
                    body = 2;
                    lost_body_part(0);
                }
                break;
            }
        }
        animeload(8, 0);
        chara_refresh(0);
        return;
    }
    if (mod_at_m134 < 0)
    {
        if (org_at_m134 + mod_at_m134 < 0)
        {
            p_at_m134 = org_at_m134;
        }
        else
        {
            p_at_m134 = std::abs(mod_at_m134);
        }
        if (p_at_m134 < 0)
        {
            p_at_m134 = 0;
        }
        for (int cnt = 0, cnt_end = (p_at_m134); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            for (int cnt = 0; cnt < 100000; ++cnt)
            {
                int tid = rnd(17) + 200;
                if (cnt == 0)
                {
                    i_at_m134 = 700 + org_at_m134 - cnt2_at_m134 - 1;
                    if (gdata(i_at_m134) != 0)
                    {
                        tid = gdata(i_at_m134);
                    }
                }
                int stat = trait_get_info(0, tid);
                if (stat == 0 || traitref != 3)
                {
                    continue;
                }
                if (trait(tid) >= 0)
                {
                    continue;
                }
                ++trait(tid);
                txtef(2);
                txt(i18n::s.get("core.locale.chara.corruption.remove"));
                txtef(2);
                txt(traitrefn(0));
                break;
            }
        }
        animeload(10, 0);
        chara_refresh(0);
        return;
    }
    return;
}



void modweight(int cc, int delta, bool force)
{
    int min = cdata[cc].height * cdata[cc].height * 18 / 25000;
    int max = cdata[cc].height * cdata[cc].height * 24 / 10000;

    if (cdata[cc].weight < min)
    {
        cdata[cc].weight = min;
        return;
    }
    if (!force && delta > 0)
    {
        if (cdata[cc].weight > max)
        {
            return;
        }
    }

    cdata[cc].weight =
        cdata[cc].weight * (100 + delta) / 100 + (delta > 0) - (delta < 0);

    if (cdata[cc].weight <= 0)
    {
        cdata[cc].weight = 1;
    }
    if (is_in_fov(cc))
    {
        if (delta >= 3)
        {
            txt(i18n::s.get("core.locale.chara.weight.gain", cdata[cc]));
        }
        if (delta <= -3)
        {
            txt(i18n::s.get("core.locale.chara.weight.lose", cdata[cc]));
        }
    }
}



void modheight(int cc, int delta)
{
    cdata[cc].height =
        cdata[cc].height * (100 + delta) / 100 + (delta > 0) - (delta < 0);
    if (cdata[cc].height <= 1)
    {
        cdata[cc].height = 1;
    }
    if (is_in_fov(cc))
    {
        if (delta > 0)
        {
            txt(i18n::s.get("core.locale.chara.height.gain", cdata[cc]));
        }
        if (delta < 0)
        {
            txt(i18n::s.get("core.locale.chara.height.lose", cdata[cc]));
        }
    }
}

void gain_level(int cc)
{
    cdata[cc].experience -= cdata[cc].required_experience;
    if (cdata[cc].experience < 0)
    {
        cdata[cc].experience = 0;
    }
    ++cdata[cc].level;
    if (cdata[cc].character_role != 13)
    {
        if (r2 == 0)
        {
            txtef(2);
            if (cc == 0)
            {
                txt(i18n::s.get("core.locale.chara.gain_level.self",
                                cdata[cc],
                                cdata[cc].level));
            }
            else
            {
                txt(i18n::s.get("core.locale.chara.gain_level.other", cdata[cc]));
            }
        }
    }
    else
    {
        addnews(2, cc);
    }
    p = 5 * (100 + sdata.get(14, cc).original_level * 10)
            / (300 + cdata[cc].level * 15)
        + 1;
    if (cc == 0)
    {
        if (cdata[cc].level % 5 == 0)
        {
            if (cdata[cc].max_level < cdata[cc].level)
            {
                if (cdata[cc].level <= 50)
                {
                    ++gdata_acquirable_feat_count;
                }
            }
        }
        gain_special_action();
        p += trait(154);
    }
    cdata[cc].skill_bonus += p;
    cdata[cc].total_skill_bonus += p;
    if (cdatan(2, cc) == u8"mutant"s || (cc == 0 && trait(0) == 1))
    {
        if (cdata[cc].level < 37)
        {
            if (cdata[cc].level % 3 == 0)
            {
                if (cdata[cc].max_level < cdata[cc].level)
                {
                    gain_new_body_part(cc);
                }
            }
        }
    }
    if (cdata[cc].max_level < cdata[cc].level)
    {
        cdata[cc].max_level = cdata[cc].level;
    }
    if (cc >= 16)
    {
        grow_primary_skills(cc);
    }
    update_required_experience(cc);
    chara_refresh(cc);
}



void grow_primary_skills(int cc)
{
    for (int cnt = 10; cnt < 20; ++cnt)
    {
        sdata.get(cnt, cc).original_level += rnd(3);
        if (sdata.get(cnt, cc).original_level > 2000)
        {
            sdata.get(cnt, cc).original_level = 2000;
        }
    }
    for (int cnt = 0, cnt_end = (mainskill.size()); cnt < cnt_end; ++cnt)
    {
        sdata.get(mainskill(cnt), cc).original_level += rnd(3);
        if (sdata.get(mainskill(cnt), cc).original_level > 2000)
        {
            sdata.get(mainskill(cnt), cc).original_level = 2000;
        }
    }
}



void update_required_experience(int cc)
{
    cdata[cc].required_experience = clamp(cdata[cc].level, 1, 200)
            * (clamp(cdata[cc].level, 1, 200) + 1)
            * (clamp(cdata[cc].level, 1, 200) + 2)
            * (clamp(cdata[cc].level, 1, 200) + 3)
        + 3000;
    if (cdata[cc].required_experience > 100000000
        || cdata[cc].required_experience < 0)
    {
        cdata[cc].required_experience = 100000000;
    }
}



} // namespace elona
