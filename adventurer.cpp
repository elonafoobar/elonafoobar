#include "adventurer.hpp"
#include <string>
#include "ability.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "equipment.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
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
    cdata[rc].state = 3;
    cdata[rc].image = rnd(33) * 2 + 1 + cdata[rc].sex;
    cdatan(0, rc) = randomname();
    cdatan(1, rc) = random_title();
    cdata[rc].character_role = 13;
    p = rnd(450);
    if (adata(16, p) == 0 || adata(16, p) == 7 || adata(0, p) == 7)
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
        addnewstopic(u8"@01"s, lang(u8"アイテム発見"s, u8"Discovery"s));
        addnews2(
            lang(
                cdatan(1, adventurer) + u8"は"s
                    + mapname(cdata[adventurer].current_map) + u8"にて"s + valn
                    + u8"を入手した。"s,
                cdatan(1, adventurer) + u8" has discovered "s + valn + u8" in "s
                    + mapname(cdata[adventurer].current_map) + u8"."s),
            1);
        break;
    case 2:
        addnewstopic(u8"@02"s, lang(u8"新たなる力"s, u8"Growth"s));
        addnews2(
            lang(
                cdatan(1, adventurer) + u8"は経験をつみ、レベル"s
                    + cdata[adventurer].level + u8"になった。"s,
                cdatan(1, adventurer)
                    + u8" has gained experience and achieved level "s
                    + cdata[adventurer].level + u8"."s),
            1);
        break;
    case 3:
        addnewstopic(
            u8"@02"s, lang(u8"怪我からの復帰"s, u8"Recovery from injury"s));
        addnews2(
            lang(
                cdatan(1, adventurer) + u8"は怪我から回復した。"s,
                cdatan(1, adventurer) + u8" has fully recovered from injury."s),
            1);
        break;
    case 4:
        addnewstopic(u8"@03"s, lang(u8"クエストの達成"s, u8"Accomplishment"s));
        addnews2(
            lang(
                cdatan(1, adventurer) + u8"はクエストを達成し、"s + fame
                    + u8"の名声を手にした。"s,
                cdatan(1, adventurer) + u8" has finished a quest and gained "s
                    + fame + u8" fame."s),
            1);
        break;
    case 5:
        addnewstopic(u8"@04"s, lang(u8"引退"s, u8"Retirement"s));
        addnews2(
            lang(
                cdatan(1, adventurer)
                    + u8"は自分の力の限界を悟り、ノースティリスから去っていった。"s,
                cdatan(1, adventurer)
                    + u8" realizes the limitations and leaves North Tyris."s),
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
                txt(lang(
                    cdatan(0, rc) + u8"との契約期間が切れた。"s,
                    u8"The period of contract with "s + cdatan(0, rc)
                        + u8" has been expired."s));
            }
        }
        if (cdata[rc].current_map == gdata_current_map)
        {
            continue;
        }
        if (cdata[rc].state == 5)
        {
            create_adventurer();
            continue;
        }
        if (cdata[rc].state == 4)
        {
            if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                    + gdata_year * 24 * 30 * 12
                >= cdata[rc].time_to_revive)
            {
                if (rnd(3) == 0)
                {
                    addnews(5, rc);
                    cdata[rc].state = 0;
                    create_adventurer();
                }
                else
                {
                    addnews(3, rc);
                    cdata[rc].state = 3;
                }
                continue;
            }
        }
        if (rnd(60) == 0)
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
                if (adata(16, p) == 0 || p == 7 || adata(0, p) == 7 || p == 9)
                {
                    p = 4;
                }
                if (cnt < 5)
                {
                    if (adata(0, p) != 3)
                    {
                        continue;
                    }
                }
                break;
            }
            cdata[rc].current_map = p;
            cdata[rc].current_dungeon_level = 1;
        }
        if (rnd(200) == 0)
        {
            if (adata(0, cdata[rc].current_map) != 3)
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
            cdata[rc].experience +=
                cdata[rc].level * cdata[rc].level * cdata[rc].level * 5;
            int fame = rnd(cdata[rc].level * cdata[rc].level / 20 + 10) + 10;
            cdata[rc].fame += fame;
            addnews(4, rc, fame);
            label_2664();
        }
        if (cdata[rc].experience >= cdata[rc].required_experience)
        {
            r2 = 0;
            gain_level(rc);
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
        if (inv[ci].number == 0)
        {
            f = 1;
            break;
        }
        if (inv[ci].body_part != 0)
        {
            continue;
        }
        if (inv[ci].number != 0)
        {
            if (cdata[rc].item_which_will_be_used == ci)
            {
                cdata[rc].item_which_will_be_used = 0;
            }
            inv[ci].number = 0;
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
        flttypemajor = fsetwear(rnd(length(fsetwear)));
    }
    else
    {
        flttypemajor = fsetitem(rnd(length(fsetitem)));
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
