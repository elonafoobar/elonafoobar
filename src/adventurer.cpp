#include "adventurer.hpp"
#include <string>
#include "ability.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "db_item.hpp"
#include "equipment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

int i_at_m145 = 0;

void create_all_adventurers()
{
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        rc = cnt;
        create_adventurer();
    }
    return;
}



void create_adventurer()
{
    flt(0, 4);
    initlv = rnd(60 + cdata[0].level) + 1;
    p(0) = 75;
    p(1) = 41;
    p(2) = 160;
    novoidlv = 1;
    chara_create(rc, p(rnd(3)), -1, -1);
    cdata[rc].relationship = 0;
    cdata[rc].original_relationship = 0;
    cdata[rc]._156 = 100;
    cdata[rc].set_state(character::state_t::adventurer_in_other_map);
    cdata[rc].image = rnd(33) * 2 + 1 + cdata[rc].sex;
    cdatan(0, rc) = randomname();
    cdatan(1, rc) = random_title();
    cdata[rc].character_role = 13;
    p = rnd(450);
    if (adata(16, p) == mdata_t::map_id_t::none
        || adata(16, p) == mdata_t::map_id_t::your_home
        || adata(0, p) == mdata_t::map_type_t::temporary)
    {
        p = 4;
    }
    if (rnd(4) == 0)
    {
        p = 5;
    }
    if (rnd(4) == 0)
    {
        p = 11;
    }
    if (rnd(6) == 0)
    {
        p = 12;
    }
    cdata[rc].current_map = p;
    cdata[rc].current_dungeon_level = 1;
    cdata[rc].fame = cdata[rc].level * cdata[rc].level * 30
        + rnd((cdata[rc].level * 200 + 100)) + rnd(500);
    return;
}


int advfavoriteskill(int prm_868)
{
    randomize(prm_868);
    rtval = 0;
    i_at_m145 = 0;
    while (1)
    {
        rtval(i_at_m145) = rnd(300) + 100;
        if (!the_ability_db[rtval(i_at_m145)])
        {
            continue;
        }
        ++i_at_m145;
        if (i_at_m145 >= 2)
        {
            break;
        }
    }
    randomize();
    return i_at_m145;
}



int advfavoritestat(int prm_869)
{
    randomize(prm_869);
    i_at_m145 = rnd(8) + 10;
    randomize();
    return i_at_m145;
}

void addnews2(const std::string& prm_401, int prm_402)
{
    std::string n_at_m36;
    n_at_m36 = prm_401;
    if (prm_402)
    {
        txtef(13);
        txt(u8"[News] "s + n_at_m36);
    }
    talk_conv(n_at_m36, 38 - en * 5);
    newsbuff += n_at_m36 + u8"\n"s;
    return;
}



void addnewstopic(const std::string& prm_403, const std::string& prm_404)
{
    addnews2(
        prm_403 + u8" "s + gdata_year + u8"/"s + gdata_month + u8"/"s
        + gdata_day + u8" h"s + gdata_hour + ""s + u8" "s + prm_404);
    return;
}



void addnews(int news_type, int adventurer, int fame, const std::string& valn)
{
    switch (news_type)
    {
    case 0: addnews2(valn); break;
    case 1:
        addnewstopic(u8"@01"s, i18n::s.get("core.locale.news.discovery.title"));
        addnews2(
            i18n::s.get(
                "core.locale.news.discovery.text",
                cdatan(1, adventurer),
                valn,
                mapname(cdata[adventurer].current_map)),
            1);
        break;
    case 2:
        addnewstopic(u8"@02"s, i18n::s.get("core.locale.news.growth.title"));
        addnews2(
            i18n::s.get(
                "core.locale.news.growth.text",
                cdatan(1, adventurer),
                cdata[adventurer].level),
            1);
        break;
    case 3:
        addnewstopic(u8"@02"s, i18n::s.get("core.locale.news.recovery.title"));
        addnews2(
            i18n::s.get(
                "core.locale.news.recovery.text", cdatan(1, adventurer)),
            1);
        break;
    case 4:
        addnewstopic(
            u8"@03"s, i18n::s.get("core.locale.news.accomplishment.title"));
        addnews2(
            i18n::s.get(
                "core.locale.news.accomplishment.text",
                cdatan(1, adventurer),
                fame),
            1);
        break;
    case 5:
        addnewstopic(
            u8"@04"s, i18n::s.get("core.locale.news.retirement.title"));
        addnews2(
            i18n::s.get(
                "core.locale.news.retirement.text", cdatan(1, adventurer)),
            1);
        break;
    }
    newsbuff += u8"\n"s;
}


void label_2662()
{
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        rc = cnt;
        cc = rc;
        if (cdata[rc].period_of_contract != 0)
        {
            if (cdata[rc].period_of_contract < gdata_hour + gdata_day * 24
                    + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
            {
                cdata[rc].period_of_contract = 0;
                cdata[rc].is_contracting() = false;
                cdata[rc].relationship = 0;
                txt(i18n::s.get(
                    "core.locale.chara.contract_expired", cdata[rc]));
            }
        }
        if (cdata[rc].current_map != gdata_current_map)
        {
            if (cdata[rc].state() == character::state_t::adventurer_empty)
            {
                create_adventurer();
                continue;
            }
            if (cdata[rc].state() == character::state_t::adventurer_dead)
            {
                if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12
                    >= cdata[rc].time_to_revive)
                {
                    if (rnd(3) == 0)
                    {
                        addnews(5, rc);
                        cdata[rc].set_state(character::state_t::empty);
                        create_adventurer();
                    }
                    else
                    {
                        addnews(3, rc);
                        cdata[rc].set_state(
                            character::state_t::adventurer_in_other_map);
                    }
                    continue;
                }
            }
        }
        if ((cdata[rc].current_map != gdata_current_map
             || mdata_map_type == mdata_t::map_type_t::world_map)
            && rnd(60) == 0)
        {
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                if (rnd(4) == 0)
                {
                    p = rnd(50) + 450;
                }
                else
                {
                    p = rnd(300);
                }
                if (adata(16, p) == mdata_t::map_id_t::none || p == 7
                    || adata(0, p) == mdata_t::map_type_t::temporary || p == 9)
                {
                    p = 4;
                }
                if (cnt < 5)
                {
                    if (adata(0, p) != mdata_t::map_type_t::town)
                    {
                        continue;
                    }
                }
                break;
            }
            cdata[rc].current_map = p;
            cdata[rc].current_dungeon_level = 1;
        }
        if (cdata[rc].current_map == gdata_current_map)
        {
            continue;
        }
        if (rnd(200) == 0)
        {
            if (adata(0, cdata[rc].current_map) != mdata_t::map_type_t::town)
            {
                label_2664();
            }
        }
        if (rnd(10) == 0)
        {
            cdata[rc].experience += cdata[rc].level * cdata[rc].level * 2;
        }
        if (rnd(20) == 0)
        {
            cdata[rc].fame += rnd(cdata[rc].level * cdata[rc].level / 40 + 5)
                - rnd((cdata[rc].level * cdata[rc].level / 50 + 5));
        }
        if (rnd(2000) == 0)
        {
            cdata[rc].experience += clamp(cdata[rc].level, 1, 1000)
                * clamp(cdata[rc].level, 1, 1000) * 100;
            int fame = rnd(cdata[rc].level * cdata[rc].level / 20 + 10) + 10;
            cdata[rc].fame += fame;
            addnews(4, rc, fame);
            label_2664();
        }
        if (cdata[rc].experience >= cdata[rc].required_experience)
        {
            r2 = 0;
            gain_level(cdata[rc]);
        }
    }
    notesel(newsbuff);
    if (noteinfo() > 195)
    {
        for (int cnt = 0, cnt_end = (noteinfo() - 195); cnt < cnt_end; ++cnt)
        {
            notedel(0);
        }
    }
    return;
}


int label_2664()
{
    f = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        ci = get_random_inv(rc);
        if (inv[ci].number() == 0)
        {
            f = 1;
            break;
        }
        if (inv[ci].body_part != 0)
        {
            continue;
        }
        if (inv[ci].number() != 0)
        {
            if (cdata[rc].item_which_will_be_used == ci)
            {
                cdata[rc].item_which_will_be_used = 0;
            }
            inv[ci].remove();
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        return 0;
    }
    flt(cdata[rc].level, 4);
    if (rnd(3) == 0)
    {
        flttypemajor = choice(fsetwear);
    }
    else
    {
        flttypemajor = choice(fsetitem);
    }
    int stat = itemcreate(rc, 0, -1, -1, 0);
    if (stat == 0)
    {
        return 0;
    }
    inv[ci].identification_state =
        identification_state_t::completely_identified;
    if (inv[ci].quality >= 4)
    {
        if (the_item_db[inv[ci].id]->category < 50000)
        {
            addnews(1, rc, 0, itemname(ci));
        }
    }
    wear_most_valuable_equipment();
    return 0;
}



} // namespace elona
