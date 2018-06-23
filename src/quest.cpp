#include "quest.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "dmgheal.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "mef.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

enum class turn_result_t;

int rewardfix = 0;

int quest_is_return_forbidden()
{
    f = 0;
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        p = gdata(160 + cnt);
        if (qdata(8, p) == 1)
        {
            if (qdata(3, p) == 1007 || qdata(3, p) == 1002)
            {
                f = 1;
                break;
            }
        }
    }
    return f;
}

void quest_place_target()
{
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 1)
        {
            cdata[cnt].is_quest_target() = true;
            cdata[cnt].relationship = -3;
        }
    }
    return;
}



int quest_targets_remaining()
{
    int f_at_m119 = 0;
    f_at_m119 = 0;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 1)
        {
            if (cdata[cnt].is_quest_target() == 1)
            {
                ++f_at_m119;
            }
        }
    }
    return f_at_m119;
}



void quest_check()
{
    int p_at_m119 = 0;
    if (gdata_current_map == 5)
    {
        if (gdata_current_dungeon_level == 3)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_putit_attacks < 2)
                {
                    gdata_putit_attacks = 2;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
        if (gdata_current_dungeon_level == 4)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_thieves_hideout < 2)
                {
                    gdata_thieves_hideout = 2;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
        if (gdata_current_dungeon_level == 5)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_nightmare < 3)
                {
                    gdata_nightmare = 3;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
    }
    if (gdata_current_map == 12)
    {
        if (gdata_current_dungeon_level == 3)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_cat_house < 2)
                {
                    gdata_cat_house = 2;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
        if (gdata_current_dungeon_level == 4)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_defense_line < 3)
                {
                    gdata_defense_line = 3;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
    }
    if (gdata_current_map == 36)
    {
        if (gdata_current_dungeon_level == 20)
        {
            if (quest_targets_remaining() == 0)
            {
                if (gdata_sewer_sweeping < 2)
                {
                    gdata_sewer_sweeping = 2;
                    snd(44);
                    txtef(2);
                    txt(i18n::s.get("core.locale.quest.journal_updated"));
                }
            }
        }
    }
    if (gdata_executing_immediate_quest_type == 0)
    {
        return;
    }
    if (gdata(73) != 3)
    {
        if (gdata(71) == 1)
        {
            p_at_m119 = 0;
            for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                 cnt < ELONA_MAX_CHARACTERS;
                 ++cnt)
            {
                if (cdata[cnt].state == 1)
                {
                    ++p_at_m119;
                }
            }
            if (p_at_m119 == 0)
            {
                event_add(8);
            }
            else
            {
                txtef(4);
                txt(i18n::s.get("core.locale.quest.hunt.remaining", p_at_m119));
            }
        }
        if (gdata_executing_immediate_quest_type == 1008)
        {
            if (chara_find(qdata(12, gdata_executing_immediate_quest)) == 0)
            {
                event_add(8);
            }
        }
    }
    return;
}


void quest_set_data(int val0)
{
    randomize(qdata(0, rq) + 1);
    s(6) = "";
    s(5) = i18n::s.get("core.locale.quest.info.gold_pieces", qdata(6, rq));
    if (qdata(7, rq) != 0)
    {
        if (qdata(7, rq) < 10000)
        {
            s(5) += i18n::s.get("core.locale.quest.info.and")
                + i18n::_(u8"ui", u8"reward", u8"_"s + qdata(7, rq));
        }
        else
        {
            s(5) += i18n::s.get("core.locale.quest.info.and")
                + fltname(qdata(7, rq));
        }
    }
    if (qdata(9, rq) == -1)
    {
        nquestdate = i18n::s.get("core.locale.quest.info.no_deadline");
    }
    else
    {
        nquestdate = i18n::s.get("core.locale.quest.info.days", qdata(9, rq));
    }
    if (qdata(3, rq) == 1006)
    {
        s = u8"%HARVEST"s;
        parse_quest_board_text(val0);
        s(10) = ""s + cnvweight(qdata(12, rq));
        s(11) = mapname(qdata(1, rq));
        s(4) = i18n::s.get("core.locale.quest.info.harvest.text", s(10));
        if (gdata_executing_immediate_quest == rq)
        {
            s(4) += i18n::s.get(
                "core.locale.quest.info.now", cnvweight(qdata(13, rq)));
        }
        s(6) = s(4);
    }
    if (qdata(3, rq) == 1009)
    {
        s = u8"%PARTY"s;
        parse_quest_board_text(val0);
        s(10) =
            i18n::s.get("core.locale.quest.info.party.points", qdata(12, rq));
        s(11) = mapname(qdata(1, rq));
        s(4) = i18n::s.get("core.locale.quest.info.party.text", s(10));
        if (gdata_executing_immediate_quest == rq)
        {
            s(4) += i18n::s.get("core.locale.quest.info.now", qdata(13, rq));
        }
        s(6) = s(4);
    }
    if (qdata(3, rq) == 1007)
    {
        s = u8"%ESCORT,"s + qdata(4, rq);
        parse_quest_board_text(val0);
        s(11) = ""s + mapname(qdata(12, rq));
        s(4) = i18n::s.get("core.locale.quest.info.escort.text", s(11));
        s(6) = s(4);
    }
    if (qdata(3, rq) == 1001)
    {
        s = u8"%HUNT"s;
        parse_quest_board_text(val0);
        s(4) = i18n::s.get("core.locale.quest.info.hunt.text");
        s(6) = s(4);
    }
    if (qdata(3, rq) == 1004)
    {
        s = u8"%SUPPLY"s;
        parse_quest_board_text(val0);
        s(4) = cnvarticle(cnvitemname(qdata(11, rq)));
        s(6) = i18n::s.get("core.locale.quest.info.supply.text", s(4));
    }
    if (qdata(3, rq) == 1002)
    {
        s = u8"%DELIVER,"s + qdata(12, rq);
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(qdata(11, rq)));
        s(11) = ""s + mapname(qdata(1, qdata(10, rq)));
        s(12) = ""s + qname(qdata(10, rq));
        if (iorgweight(qdata(11, rq)) > 50000)
        {
            s(10) += i18n::s.get("core.locale.quest.info.heavy");
        }
        s(4) = i18n::s.get(
            "core.locale.quest.info.deliver.text", s(10), s(11), s(12));
        s(6) = s(4);
    }
    if (qdata(3, rq) == 1003)
    {
        s = u8"%COOK,"s + qdata(12, rq);
        if (rnd(6) == 0)
        {
            s = u8"%COOK,GENERAL"s;
        }
        parse_quest_board_text(val0);
        s(4) = cnvarticle(foodname(qdata(12, rq), ""s, qdata(13, rq)));
        s(6) = i18n::s.get("core.locale.quest.info.supply.text", s(4));
    }
    if (qdata(3, rq) == 1008)
    {
        s = u8"%CONQUER"s;
        parse_quest_board_text(val0);
        s(4) = chara_refstr(qdata(12, rq), 2);
        if (qdata(12, rq) == 343)
        {
            s(4) =
                i18n::s.get("core.locale.quest.info.conquer.unknown_monster");
        }
        s(10) = ""s + qdata(5, rq) * 10 / 6;
        s(6) = i18n::s.get("core.locale.quest.info.conquer.text", s(4));
    }
    if (qdata(3, rq) == 1010)
    {
        s = u8"%HUNTEX"s;
        parse_quest_board_text(val0);
        s(4) = chara_refstr(qdata(12, rq), 2);
        s(10) = ""s + qdata(5, rq) * 3 / 2;
        s(6) = i18n::s.get("core.locale.quest.info.hunt.text");
    }
    if (qdata(3, rq) == 1011)
    {
        s = u8"%COLLECT"s;
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(qdata(11, rq)));
        s(11) = ""s + mapname(qdata(1, rq));
        if (gdata_current_map == qdata(1, rq)
            && gdata_current_dungeon_level == 1)
        {
            s(12) = ""s + cdatan(0, qdata(10, rq));
        }
        else
        {
            s(12) = i18n::s.get("core.locale.quest.info.collect.target", s(11));
        }
        if (iorgweight(qdata(11, rq)) > 50000)
        {
            s(10) += i18n::s.get("core.locale.quest.info.heavy");
        }
        s(4) = i18n::s.get("core.locale.quest.info.collect.text", s(10), s(12));
        s(6) = s(4);
    }
    text_replace_tags_in_quest_text();
    if (val0 == 1)
    {
        buff = i18n::s.get(
                   "core.locale.quest.giver.have_something_to_ask", cdata[cc])
            + buff;
        if (qdata(9, rq) != -1)
        {
            buff += i18n::s.get(
                "core.locale.quest.giver.days_to_perform",
                qdata(9, rq),
                cdata[cc]);
        }
        buff += i18n::s.get("core.locale.quest.giver.how_about_it", cdata[cc]);
    }
    if (val0 == 2)
    {
        if (qdata(8, rq) == 3)
        {
            buff += u8"@QC["s
                + i18n::s.get("core.locale.quest.journal.complete") + u8"]"s
                + s(3) + u8"\n"s;
        }
        else
        {
            buff += u8"@QL["s + i18n::s.get("core.locale.quest.journal.job")
                + u8"] "s + s(3) + u8"\n"s;
        }
        buff += i18n::s.get("core.locale.quest.journal.client") + qname(rq)
            + u8"\n"s;
        buff += i18n::s.get("core.locale.quest.journal.location")
            + mapname(qdata(1, rq)) + u8"\n"s;
        buff += i18n::s.get("core.locale.quest.journal.deadline");
        if (qdata(9, rq) != -1)
        {
            buff += i18n::s.get("core.locale.quest.journal.remaining");
        }
        buff += nquestdate + u8"\n"s;
        s(5) = i18n::s.get("core.locale.quest.journal.reward") + s(5);
        talk_conv(s(5), 40 - en * 10);
        buff += s(5) + u8"\n"s;
        s(4) = i18n::s.get("core.locale.quest.journal.detail");
        if (qdata(8, rq) == 3)
        {
            s(4) +=
                i18n::s.get("core.locale.quest.journal.report_to_the_client");
        }
        else
        {
            s(4) += s(6);
        }
        talk_conv(s(4), 40 - en * 10);
        buff += s(4) + u8"\n"s;
    }
    if (val0 == 3)
    {
        buff = i18n::s.get(
            "core.locale.quest.giver.complete.done_well", cdata[cc]);
        if (elona::stoi(s(5)) != 0)
        {
            txt(i18n::s.get(
                "core.locale.quest.giver.complete.take_reward",
                s(5),
                cdata[cc]));
        }
        if (qdata(3, rq) == 1006)
        {
            if (qdata(12, rq) * 125 / 100 < qdata(13, rq))
            {
                buff += i18n::s.get(
                    "core.locale.quest.giver.complete.extra_coins", cdata[cc]);
            }
        }
        if (qdata(3, rq) == 1009)
        {
            if (qdata(12, rq) * 150 / 100 < qdata(13, rq))
            {
                buff += i18n::s.get(
                    "core.locale.quest.giver.complete.music_tickets",
                    cdata[cc]);
            }
        }
    }
    randomize();
    return;
}



void quest_on_map_initialize()
{
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 0)
        {
            continue;
        }
        if (cdata[cnt].character_role == 0)
        {
            continue;
        }
        if (cdata[cnt].quality == 6)
        {
            continue;
        }
        if (cdata[cnt].character_role == 3)
        {
            continue;
        }
        i = -1;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (qdata(0, cnt) == 0)
            {
                i = cnt;
                break;
            }
        }
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (qdata(0, cnt) == cnt2)
            {
                if (qdata(1, cnt) == gdata_current_map)
                {
                    i = -1;
                    break;
                }
            }
        }
        if (i == -1)
        {
            break;
        }
        qdata(0, i) = cnt;
        qdata(1, i) = gdata_current_map;
        qname(i) = cdatan(0, cnt);
        cdata[cnt].related_quest_id = i + 1;
        gdata_number_of_existing_quests = i + 1;
    }
    return;
}



void quest_refresh_list()
{
    for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (qdata(0, cnt) == 0)
        {
            continue;
        }
        if (qdata(1, cnt) != gdata_current_map)
        {
            continue;
        }
        rc = qdata(0, cnt);
        if (qdata(8, cnt) == 0)
        {
            if (qdata(2, cnt) < gdata_hour + gdata_day * 24
                    + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
            {
                rq = cnt;
                quest_generate();
                quest_gen_scale_by_level();
            }
        }
    }
}

int quest_generate()
{
    qdata(3, rq) = 0;
    qdata(14, rq) = 0;
    qdata(8, rq) = 0;
    qdata(2, rq) = (rnd(3) + 1) * 24
        + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
           + gdata_year * 24 * 30 * 12);
    qdata(7, rq) = 0;
    if (rnd(3) == 0)
    {
        return 0;
    }
    if (rnd(14) == 0)
    {
        i = -1;
        for (int cnt = 0; cnt < 300; ++cnt)
        {
            int n =
                rnd(ELONA_MAX_OTHER_CHARACTERS) + ELONA_MAX_PARTY_CHARACTERS;
            if (n == qdata(0, rq))
            {
                continue;
            }
            if (cdata[n].state != 1)
            {
                continue;
            }
            if (cdata[n].relationship != 0
                || (cdata[n].character_role != 4
                    && cdata[n].character_role != 14))
            {
                continue;
            }
            flt(40, 2);
            flttypemajor = fsetcollect(rnd(length(fsetcollect)));
            int stat = itemcreate(n, 0, -1, -1, 0);
            if (stat != 0)
            {
                inv[ci].count = rq;
                i(0) = n;
                i(1) = inv[ci].id;
                ibitmod(12, ci, 1);
                break;
            }
            else
            {
                i = -1;
                break;
            }
        }
        if (i != -1)
        {
            qdata(10, rq) = i;
            qdata(11, rq) = i(1);
            qdata(1, rq) = gdata_current_map;
            rewardfix = 60;
            qdata(7, rq) = 5;
            qdata(3, rq) = 1011;
            qdata(14, rq) = 3;
            qdata(4, rq) = 0;
            qdata(9, rq) = rnd(3) + 2;
            qdata(5, rq) = cdata[i].level / 3;
        }
        return 0;
    }
    if (cdata[0].fame >= 30000)
    {
        if (rnd(13) == 0)
        {
            qdata(5, rq) =
                rnd(cdata[0].level + 10) + rnd((cdata[0].fame / 2500 + 1));
            qdata(5, rq) = roundmargin(qdata(5, rq), cdata[0].level);
            minlevel = clamp(qdata(5, rq) / 7, 5, 30);
            for (int cnt = 0; cnt < 50; ++cnt)
            {
                flt(qdata(5, rq), 2);
                chara_create(56, 0, -3, 0);
                if (cmshade)
                {
                    continue;
                }
                if (cdata[rc].level < minlevel)
                {
                    continue;
                }
                break;
            }
            qdata(12, rq) = cdata[56].id;
            qdata(2, rq) = (rnd(6) + 2) * 24
                + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                   + gdata_year * 24 * 30 * 12);
            qdata(7, rq) = 0;
            qdata(3, rq) = 1010;
            qdata(14, rq) = 1;
            qdata(4, rq) = 0;
            qdata(7, rq) = 5;
            qdata(9, rq) = -1;
            rewardfix = 140;
            return 0;
        }
    }
    if (cdata[0].fame >= 50000)
    {
        if (rnd(20) == 0)
        {
            qdata(5, rq) =
                rnd(cdata[0].level + 10) + rnd((cdata[0].fame / 2500 + 1));
            qdata(5, rq) = roundmargin(qdata(5, rq), cdata[0].level);
            minlevel = clamp(qdata(5, rq) / 4, 5, 30);
            for (int cnt = 0; cnt < 50; ++cnt)
            {
                flt(qdata(5, rq), 2);
                chara_create(56, 0, -3, 0);
                if (cmshade)
                {
                    continue;
                }
                if (cdata[rc].level < minlevel)
                {
                    continue;
                }
                break;
            }
            qdata(12, rq) = cdata[56].id;
            qdata(2, rq) = (rnd(6) + 2) * 24
                + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                   + gdata_year * 24 * 30 * 12);
            qdata(7, rq) = 0;
            qdata(3, rq) = 1008;
            qdata(14, rq) = 8;
            qdata(4, rq) = 0;
            qdata(7, rq) = 1;
            qdata(9, rq) = -1;
            rewardfix = 175;
            return 0;
        }
    }
    if (rnd(11) == 0)
    {
        qdata(2, rq) = (rnd(6) + 2) * 24
            + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
               + gdata_year * 24 * 30 * 12);
        qdata(3, rq) = 1007;
        qdata(14, rq) = 6;
        qdata(4, rq) = rnd(3);
        qdata(10, rq) = 0;
        qdata(7, rq) = 5;
        while (1)
        {
            qdata(12, rq) = asettown(rnd(length(asettown)));
            if (qdata(12, rq) != gdata_current_map)
            {
                break;
            }
        }
        p = qdata(12, rq);
        if (qdata(4, rq) == 0)
        {
            rewardfix = 140
                + dist(
                      adata(1, gdata_current_map),
                      adata(2, gdata_current_map),
                      adata(1, p),
                      adata(2, p))
                    * 2;
            qdata(9, rq) = rnd(8) + 6;
            qdata(5, rq) = clamp(
                rnd(cdata[0].level + 10) + rnd((cdata[0].fame / 500 + 1)) + 1,
                1,
                80);
        }
        if (qdata(4, rq) == 1)
        {
            rewardfix = 130
                + dist(
                      adata(1, gdata_current_map),
                      adata(2, gdata_current_map),
                      adata(1, p),
                      adata(2, p))
                    * 2;
            qdata(9, rq) = rnd(5) + 2;
            qdata(5, rq) = clamp(rewardfix / 10 + 1, 1, 40);
        }
        if (qdata(4, rq) == 2)
        {
            rewardfix = 80
                + dist(
                      adata(1, gdata_current_map),
                      adata(2, gdata_current_map),
                      adata(1, p),
                      adata(2, p))
                    * 2;
            qdata(9, rq) = rnd(8) + 6;
            qdata(5, rq) = clamp(rewardfix / 20 + 1, 1, 40);
        }
        if (qdata(12, rq) == 33 || gdata_current_map == 33)
        {
            rewardfix = rewardfix * 180 / 100;
        }
        return 0;
    }
    if (rnd(23) == 0 || (gdata_current_map == 15 && rnd(8) == 0))
    {
        qdata(5, rq) = clamp(
            rnd(sdata(183, 0) + 10),
            int(1.5 * std::sqrt(sdata(183, 0))) + 1,
            cdata[0].fame / 1000 + 10);
        qdata(2, rq) = (rnd(6) + 2) * 24
            + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
               + gdata_year * 24 * 30 * 12);
        qdata(7, rq) = 0;
        qdata(3, rq) = 1009;
        qdata(14, rq) = 7;
        qdata(4, rq) = 0;
        qdata(7, rq) = 0;
        qdata(12, rq) = qdata(5, rq) * 10 + rnd(50);
        qdata(13, rq) = 0;
        qdata(9, rq) = -1;
        rewardfix = 0;
        return 0;
    }
    if (rnd(30) == 0 || (gdata_current_map == 12 && rnd(2) == 0))
    {
        qdata(5, rq) = clamp(
            rnd(cdata[0].level + 5) + rnd((cdata[0].fame / 800 + 1)) + 1,
            1,
            50);
        qdata(2, rq) = (rnd(6) + 2) * 24
            + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
               + gdata_year * 24 * 30 * 12);
        qdata(3, rq) = 1006;
        qdata(14, rq) = 5;
        qdata(4, rq) = 0;
        qdata(7, rq) = 5;
        qdata(9, rq) = -1;
        qdata(12, rq) = 15000 + qdata(5, rq) * 2500;
        qdata(13, rq) = 0;
        rewardfix = 60 + qdata(5, rq) * 2;
        return 0;
    }
    if (rnd(8) == 0)
    {
        qdata(5, rq) = clamp(
            rnd(cdata[0].level + 10) + rnd((cdata[0].fame / 500 + 1)) + 1,
            1,
            80);
        qdata(5, rq) = roundmargin(qdata(5, rq), cdata[0].level);
        qdata(2, rq) = (rnd(6) + 2) * 24
            + (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
               + gdata_year * 24 * 30 * 12);
        qdata(7, rq) = 0;
        qdata(3, rq) = 1001;
        qdata(14, rq) = 1;
        qdata(4, rq) = 0;
        qdata(7, rq) = 1;
        qdata(9, rq) = -1;
        rewardfix = 135;
        return 0;
    }
    if (rnd(6) == 0)
    {
        i = -1;
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            p = rnd(gdata_number_of_existing_quests);
            for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
                 cnt < cnt_end;
                 ++cnt)
            {
                if (qdata(3, cnt) == 1002)
                {
                    if (qdata(10, cnt) == p)
                    {
                        p = -1;
                        break;
                    }
                }
            }
            if (p == -1)
            {
                continue;
            }
            if (qdata(0, p) != 0)
            {
                if (qdata(1, p) != gdata_current_map || 0)
                {
                    i = p;
                    break;
                }
            }
        }
        if (i != -1)
        {
            p = qdata(1, i);
            rewardfix = 70
                + dist(
                      adata(1, gdata_current_map),
                      adata(2, gdata_current_map),
                      adata(1, p),
                      adata(2, p))
                    * 2;
            if (p == 33 || gdata_current_map == 33)
            {
                rewardfix = rewardfix * 175 / 100;
            }
            qdata(10, rq) = i;
            flt();
            dbmode = 1;
            flttypemajor = fsetdeliver(rnd(length(fsetdeliver)));
            get_random_item_id();
            qdata(12, rq) = flttypemajor;
            qdata(7, rq) = 5;
            if (flttypemajor == 54000)
            {
                qdata(7, rq) = 2;
            }
            if (flttypemajor == 77000)
            {
                qdata(7, rq) = 3;
            }
            if (flttypemajor == 64000)
            {
                qdata(7, rq) = 77000;
            }
            if (flttypemajor == 60000)
            {
                qdata(7, rq) = 60000;
            }
            qdata(11, rq) = dbid;
            qdata(3, rq) = 1002;
            qdata(14, rq) = 2;
            qdata(4, rq) = 0;
            qdata(9, rq) = rnd(12) + 3;
            qdata(5, rq) = clamp(rewardfix / 20 + 1, 1, 25);
        }
        return 0;
    }
    if (rnd(6) == 0)
    {
        qdata(3, rq) = 1003;
        qdata(14, rq) = 3;
        qdata(9, rq) = rnd(6) + 2;
        qdata(7, rq) = 5;
        qdata(12, rq) = rnd(8) + 1;
        if (qdata(12, rq) == 4)
        {
            qdata(7, rq) = 52000;
        }
        if (qdata(12, rq) == 6)
        {
            qdata(7, rq) = 25000;
        }
        if (qdata(12, rq) == 1)
        {
            qdata(7, rq) = 25000;
        }
        if (qdata(12, rq) == 5)
        {
            qdata(7, rq) = 52000;
        }
        if (qdata(12, rq) == 7)
        {
            qdata(7, rq) = 77000;
        }
        if (qdata(12, rq) == 2)
        {
            qdata(7, rq) = 56000;
        }
        if (qdata(12, rq) == 3)
        {
            qdata(7, rq) = 53000;
        }
        qdata(13, rq) = rnd(7) + 3;
        qdata(5, rq) = qdata(13, rq) * 3;
        rewardfix = 60 + qdata(5, rq);
        return 0;
    }
    if (rnd(5) == 0)
    {
        qdata(3, rq) = 1004;
        qdata(14, rq) = 3;
        qdata(9, rq) = rnd(6) + 2;
        flt();
        dbmode = 1;
        flttypemajor = fsetsupply(rnd(length(fsetsupply)));
        get_random_item_id();
        qdata(7, rq) = 5;
        qdata(11, rq) = dbid;
        qdata(5, rq) = clamp(rnd(cdata[0].level + 5) + 1, 1, 30);
        rewardfix = 65 + qdata(5, rq);
        return 0;
    }
    return 1;
}

void quest_gen_scale_by_level()
{
    qdata(6, rq) =
        ((qdata(5, rq) + 3) * 100 + rnd((qdata(5, rq) * 30 + 200)) + 400)
        * rewardfix / 100;
    qdata(6, rq) = qdata(6, rq) * 100 / (100 + qdata(5, rq) * 2 / 3);
    if (qdata(14, rq) == 3 || qdata(14, rq) == 2)
    {
        return;
    }
    if (cdata[0].level >= qdata(5, rq))
    {
        qdata(6, rq) =
            qdata(6, rq) * 100 / (100 + (cdata[0].level - qdata(5, rq)) * 10);
    }
    else
    {
        qdata(6, rq) = qdata(6, rq)
            * (100 + clamp((qdata(5, rq) - cdata[0].level) / 5 * 25, 0, 200))
            / 100;
    }
    return;
}

void quest_check_all_for_failed()
{
    for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (qdata(3, cnt) == 0)
        {
            continue;
        }
        if (qdata(8, cnt) != 1)
        {
            continue;
        }
        if (qdata(9, cnt) < 0)
        {
            continue;
        }
        rq = cnt;
        --qdata(9, rq);
        if (qdata(9, rq) == 0)
        {
            quest_failed(qdata(3, rq));
        }
    }
    return;
}



void quest_exit_map()
{
    if (gdata_executing_immediate_quest_type == 1006)
    {
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].own_state == 4)
            {
                item_remove(inv[cnt]);
            }
        }
        refresh_burden_state();
    }
    if (gdata(73) != 3)
    {
        if (gdata_executing_immediate_quest_type >= 1000)
        {
            rq = gdata_executing_immediate_quest;
        }
        if (gdata_executing_immediate_quest_type == 1007)
        {
            if (qdata(8, rq) == 0)
            {
                gdata_executing_immediate_quest_type = 0;
                gdata(71) = 0;
                gdata_executing_immediate_quest = 0;
                gdata(73) = 0;
                return;
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.quest.escort.you_left_your_client"));
            }
        }
        quest_failed(gdata_executing_immediate_quest_type);
        msg_halt();
    }
    gdata_executing_immediate_quest_type = 0;
    gdata(71) = 0;
    gdata_executing_immediate_quest = 0;
    gdata(73) = 0;
    return;
}



turn_result_t quest_pc_died_during_immediate_quest()
{
    rc = 0;
    label_1540();
    skillexp(17, 0, -500);
    skillexp(15, 0, -500);
    levelexitby = 4;
    gdata_current_dungeon_level = 0;
    return turn_result_t::exit_map;
}



void quest_failed(int val0)
{
    if (val0 == 1)
    {
        adata(22, gdata_previous_map2) = 0;
        txt(i18n::s.get("core.locale.quest.you_were_defeated"));
        modrank(0, -100);
    }
    if (val0 >= 1000)
    {
        txt(i18n::s.get("core.locale.quest.failed_taken_from", qname(rq)));
        if (qdata(3, rq) == 1002)
        {
            --qdata(15, qdata(10, rq));
            txtef(8);
            txt(i18n::s.get(
                "core.locale.quest.deliver.you_commit_a_serious_crime"));
            modify_karma(0, -20);
        }
        if (qdata(3, rq) == 1007)
        {
            txtef(8);
            txt(i18n::s.get("core.locale.quest.escort.you_failed_to_protect"));
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (cnt != 0)
                {
                    if (cdata[cnt].is_escorted() == 1)
                    {
                        if (qdata(13, rq) == cdata[cnt].id)
                        {
                            tc = cnt;
                            cdata[cnt].is_escorted() = false;
                            if (cdata[tc].state == 1)
                            {
                                if (qdata(4, rq) == 0)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "assassin");
                                    p = -11;
                                }
                                if (qdata(4, rq) == 1)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "poison");
                                    p = -4;
                                }
                                if (qdata(4, rq) == 2)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "deadline",
                                        cdata[tc]);
                                    mef_add(
                                        cdata[0].position.x,
                                        cdata[0].position.y,
                                        5,
                                        24,
                                        rnd(15) + 25,
                                        efp,
                                        0);
                                    mapitem_fire(
                                        cdata[tc].position.x,
                                        cdata[tc].position.y);
                                    p = -9;
                                }
                                txtef(9);
                                txt(s);
                                dmghp(tc, 999999, p);
                            }
                            cdata[tc].state = 0;
                            break;
                        }
                    }
                }
            }
            modify_karma(0, -10);
        }
        qdata(3, rq) = 0;
        qdata(8, rq) = 0;
    }
    int stat = decfame(0, 40);
    p = stat;
    txtef(3);
    txt(i18n::s.get("core.locale.quest.lose_fame", p(0)));
    return;
}



void quest_team_victorious()
{
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (followerin(cnt) == 0)
        {
            continue;
        }
        if (cdata[cnt].hp < cdata[cnt].max_hp / 2)
        {
            cdata[cnt].hp = cdata[cnt].max_hp / 2;
        }
    }
    snd(69);
    if (petarenawin == 1)
    {
        txtef(2);
        txt(i18n::s.get("core.locale.quest.arena.your_team_is_victorious"));
        txtef(2);
        txt(i18n::s.get("core.locale.quest.gain_fame", gdata(74)));
        cdata[0].fame += gdata(74);
        modrank(1, 100, 2);
        ++adata(23, gdata_previous_map2);
        if (adata(23, gdata_previous_map2) % 20 == 0)
        {
            matgetmain(41, 1);
        }
        else if (adata(23, gdata_previous_map2) % 5 == 0)
        {
            matgetmain(40, 1);
        }
    }
    else
    {
        txtef(8);
        txt(i18n::s.get("core.locale.quest.arena.your_team_is_defeated"));
        adata(23, gdata_previous_map2) = 0;
        modrank(1, -100);
        int stat = decfame(0, 60);
        p = stat;
        if (arenaop == 0)
        {
            txtef(3);
            txt(i18n::s.get("core.locale.quest.lose_fame", p(0)));
        }
    }
    return;
}



void quest_all_targets_killed()
{
    musicloop = 1;
    play_music(74);
    gdata(73) = 3;
    if (gdata_executing_immediate_quest_type == 1)
    {
        snd(69);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.arena.you_are_victorious"));
        txtef(2);
        txt(i18n::s.get("core.locale.quest.gain_fame", gdata(74)));
        modrank(0, 100, 2);
        cdata[0].fame += gdata(74);
        txt(i18n::s.get("core.locale.quest.arena.stairs_appear"));
        map_placeupstairs(mdata(0) / 2, mdata(1) / 2);
        ++adata(22, gdata_previous_map2);
        if (adata(22, gdata_previous_map2) % 20 == 0)
        {
            matgetmain(41, 1);
        }
        else if (adata(22, gdata_previous_map2) % 5 == 0)
        {
            matgetmain(40, 1);
        }
    }
    if (gdata_executing_immediate_quest_type == 1001
        || gdata_executing_immediate_quest_type == 1010)
    {
        qdata(8, gdata_executing_immediate_quest) = 3;
        txtef(2);
        txt(i18n::s.get("core.locale.quest.hunt.complete"));
    }
    if (gdata_executing_immediate_quest_type == 1007)
    {
        txtef(2);
        txt(i18n::s.get("core.locale.quest.hunt.complete"));
    }
    if (gdata_executing_immediate_quest_type == 1008)
    {
        gdata_left_minutes_of_executing_quest = 0;
        qdata(8, gdata_executing_immediate_quest) = 3;
        txtef(2);
        txt(i18n::s.get("core.locale.quest.conquer.complete"));
    }
    return;
}

void quest_complete()
{
    snd(51);
    p = qdata(6, rq);
    if (qdata(3, rq) == 1006)
    {
        if (qdata(12, rq) != 0)
        {
            if (qdata(12, rq) * 125 / 100 < qdata(13, rq))
            {
                p = clamp(p * qdata(13, rq) / qdata(12, rq), p(0), p * 3);
            }
        }
    }
    if (p != 0)
    {
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y, p);
    }
    if (qdata(3, rq) == 1002)
    {
        p = rnd(2) + 1;
    }
    else
    {
        p = 1;
    }
    if (qdata(3, rq) == 1008 || qdata(3, rq) == 1010)
    {
        p = 2 + (rnd(100) < rnd(cdata[0].fame / 5000 + 1));
    }
    flt();
    itemcreate(-1, 55, cdata[0].position.x, cdata[0].position.y, p);
    if (qdata(3, rq) == 1009)
    {
        if (qdata(12, rq) * 150 / 100 < qdata(13, rq))
        {
            flt();
            itemcreate(
                -1,
                724,
                cdata[0].position.x,
                cdata[0].position.y,
                1 + qdata(13, rq) / 10);
        }
    }
    if (qdata(7, rq) != 0)
    {
        p = rnd(rnd(4) + 1) + 1;
        if (qdata(3, rq) == 1008 || qdata(3, rq) == 1010)
        {
            p += 2;
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            fixlv = 2;
            if (rnd(2))
            {
                fixlv = 3;
                if (rnd(12) == 0)
                {
                    fixlv = 4;
                }
            }
            flt((qdata(5, rq) + cdata[0].level) / 2 + 1, calcfixlv(fixlv));
            if (qdata(7, rq) < 10000)
            {
                if (qdata(7, rq) == 1)
                {
                    flttypemajor = fsetwear(rnd(length(fsetwear)));
                }
                if (qdata(7, rq) == 2)
                {
                    flttypemajor = fsetmagic(rnd(length(fsetmagic)));
                }
                if (qdata(7, rq) == 3)
                {
                    flttypemajor = fsetarmor(rnd(length(fsetarmor)));
                }
                if (qdata(7, rq) == 4)
                {
                    flttypemajor = fsetweapon(rnd(length(fsetweapon)));
                }
                if (qdata(7, rq) == 5)
                {
                    flttypemajor =
                        fsetrewardsupply(rnd(length(fsetrewardsupply)));
                }
            }
            else
            {
                flttypemajor = qdata(7, rq);
            }
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        }
    }
    modify_karma(0, 1);
    gdata(74) = calcfame(0, qdata(5, rq) * 3 + 10);
    txtef(2);
    txt(i18n::s.get("core.locale.quest.completed_taken_from", qname(rq)));
    txtef(2);
    txt(i18n::s.get("core.locale.quest.gain_fame", gdata(74)));
    cdata[0].fame += gdata(74);
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    if (qdata(3, rq) == 1002)
    {
        --qdata(15, qdata(10, rq));
    }
    qdata(3, rq) = 0;
    qdata(8, rq) = 0;
    autosave = 1 * (gdata_current_map != 35);
    return;
}

} // namespace elona
