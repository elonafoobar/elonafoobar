#include "quest.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "dmgheal.hpp"
#include "event.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "message.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

QuestData quest_data;

#define QDATA_PACK(x, ident) legacy_qdata(x, quest_id) = ident;
#define QDATA_UNPACK(x, ident) ident = legacy_qdata(x, quest_id);

#define SERIALIZE_ALL() \
    SERIALIZE(0, client_chara_index); \
    SERIALIZE(1, originating_map_id); \
    SERIALIZE(2, deadline_hours); \
    SERIALIZE(3, id); \
    SERIALIZE(4, escort_difficulty); \
    SERIALIZE(5, difficulty); \
    SERIALIZE(6, reward_gold); \
    SERIALIZE(7, reward_item_id); \
    SERIALIZE(8, progress); \
    SERIALIZE(9, deadline_days); \
    SERIALIZE(10, target_chara_index); \
    SERIALIZE(11, target_item_id); \
    SERIALIZE(12, extra_info_1); \
    SERIALIZE(13, extra_info_2); \
    SERIALIZE(14, client_chara_type); \
    SERIALIZE(15, delivery_has_package_flag);


#define SERIALIZE QDATA_PACK
void Quest::pack_to(elona_vector2<int>& legacy_qdata, int quest_id)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE


#define SERIALIZE QDATA_UNPACK
void Quest::unpack_from(elona_vector2<int>& legacy_qdata, int quest_id)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE



void Quest::clear()
{
    *this = {};
}



Quest& QuestData::immediate()
{
    assert(game_data.executing_immediate_quest != 0);

    return quest_data[game_data.executing_immediate_quest];
}



void QuestData::clear()
{
    for (auto&& quest : quests)
    {
        quest.clear();
    }
}



void QuestData::pack_to(elona_vector2<int>& legacy_qdata)
{
    assert(legacy_qdata.j_size() == quests.size());

    int i{};
    for (auto&& quest : quests)
    {
        quest.pack_to(legacy_qdata, i);
        ++i;
    }
}



void QuestData::unpack_from(elona_vector2<int>& legacy_qdata)
{
    assert(legacy_qdata.j_size() == quests.size());

    int i{};
    for (auto&& quest : quests)
    {
        quest.unpack_from(legacy_qdata, i);
        ++i;
    }
}



enum class TurnResult;

int rewardfix = 0;

int quest_is_return_forbidden()
{
    f = 0;
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        p = game_data.taken_quests.at(cnt);
        if (quest_data[p].progress == 1)
        {
            if (quest_data[p].id == 1007 || quest_data[p].id == 1002)
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
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::alive)
        {
            cnt.is_quest_target() = true;
            cnt.relationship = -3;
        }
    }
}



int quest_targets_remaining()
{
    int f_at_m119 = 0;
    f_at_m119 = 0;
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::alive)
        {
            if (cnt.is_quest_target() == 1)
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
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        if (game_data.current_dungeon_level == 3)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.putit_attacks < 2)
                {
                    game_data.quest_flags.putit_attacks = 2;
                    quest_update_journal_msg();
                }
            }
        }
        if (game_data.current_dungeon_level == 4)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.thieves_hideout < 2)
                {
                    game_data.quest_flags.thieves_hideout = 2;
                    quest_update_journal_msg();
                }
            }
        }
        if (game_data.current_dungeon_level == 5)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.nightmare < 3)
                {
                    game_data.quest_flags.nightmare = 3;
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        if (game_data.current_dungeon_level == 3)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.cat_house < 2)
                {
                    game_data.quest_flags.cat_house = 2;
                    quest_update_journal_msg();
                }
            }
        }
        if (game_data.current_dungeon_level == 4)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.defense_line < 3)
                {
                    game_data.quest_flags.defense_line = 3;
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        if (game_data.current_dungeon_level == 20)
        {
            if (quest_targets_remaining() == 0)
            {
                if (game_data.quest_flags.sewer_sweeping < 2)
                {
                    game_data.quest_flags.sewer_sweeping = 2;
                    quest_update_journal_msg();
                }
            }
        }
    }
    if (game_data.executing_immediate_quest_type == 0)
    {
        return;
    }
    if (game_data.executing_immediate_quest_status != 3)
    {
        if (game_data.executing_immediate_quest_show_hunt_remain == 1)
        {
            p_at_m119 = 0;
            for (auto&& cnt : cdata.others())
            {
                if (cnt.state() == Character::State::alive)
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
                Message::instance().txtef(ColorIndex::blue);
                txt(i18n::s.get("core.locale.quest.hunt.remaining", p_at_m119));
            }
        }
        if (game_data.executing_immediate_quest_type == 1008)
        {
            if (chara_find(quest_data.immediate().extra_info_1) == 0)
            {
                event_add(8);
            }
        }
    }
}


void quest_set_data(int val0)
{
    randomize(quest_data[rq].client_chara_index + 1);
    s(6) = "";
    s(5) = i18n::s.get(
        "core.locale.quest.info.gold_pieces", quest_data[rq].reward_gold);
    if (quest_data[rq].reward_item_id != 0)
    {
        if (quest_data[rq].reward_item_id < 10000)
        {
            s(5) += i18n::s.get("core.locale.quest.info.and")
                + i18n::_(
                        u8"ui",
                        u8"reward",
                        u8"_"s + quest_data[rq].reward_item_id);
        }
        else
        {
            s(5) += i18n::s.get("core.locale.quest.info.and")
                + fltname(quest_data[rq].reward_item_id);
        }
    }
    if (quest_data[rq].deadline_days == -1)
    {
        nquestdate = i18n::s.get("core.locale.quest.info.no_deadline");
    }
    else
    {
        nquestdate = i18n::s.get(
            "core.locale.quest.info.days", quest_data[rq].deadline_days);
    }
    if (quest_data[rq].id == 1006)
    {
        s = u8"%HARVEST"s;
        parse_quest_board_text(val0);
        s(10) = ""s + cnvweight(quest_data[rq].extra_info_1);
        s(11) = mapname(quest_data[rq].originating_map_id);
        s(4) = i18n::s.get("core.locale.quest.info.harvest.text", s(10));
        if (game_data.executing_immediate_quest == rq)
        {
            s(4) += i18n::s.get(
                "core.locale.quest.info.now",
                cnvweight(quest_data[rq].extra_info_2));
        }
        s(6) = s(4);
    }
    if (quest_data[rq].id == 1009)
    {
        s = u8"%PARTY"s;
        parse_quest_board_text(val0);
        s(10) = i18n::s.get(
            "core.locale.quest.info.party.points", quest_data[rq].extra_info_1);
        s(11) = mapname(quest_data[rq].originating_map_id);
        s(4) = i18n::s.get("core.locale.quest.info.party.text", s(10));
        if (game_data.executing_immediate_quest == rq)
        {
            s(4) += i18n::s.get(
                "core.locale.quest.info.now", quest_data[rq].extra_info_2);
        }
        s(6) = s(4);
    }
    if (quest_data[rq].id == 1007)
    {
        s = u8"%ESCORT,"s + quest_data[rq].escort_difficulty;
        parse_quest_board_text(val0);
        s(11) = ""s + mapname(quest_data[rq].extra_info_1);
        s(4) = i18n::s.get("core.locale.quest.info.escort.text", s(11));
        s(6) = s(4);
    }
    if (quest_data[rq].id == 1001)
    {
        s = u8"%HUNT"s;
        parse_quest_board_text(val0);
        s(4) = i18n::s.get("core.locale.quest.info.hunt.text");
        s(6) = s(4);
    }
    if (quest_data[rq].id == 1004)
    {
        s = u8"%SUPPLY"s;
        parse_quest_board_text(val0);
        s(4) = cnvarticle(cnvitemname(quest_data[rq].target_item_id));
        s(6) = i18n::s.get("core.locale.quest.info.supply.text", s(4));
    }
    if (quest_data[rq].id == 1002)
    {
        s = u8"%DELIVER,"s + quest_data[rq].extra_info_1;
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(quest_data[rq].target_item_id));
        s(11) = ""s
            + mapname(quest_data[quest_data[rq].target_chara_index]
                          .originating_map_id);
        s(12) = ""s + qname(quest_data[rq].target_chara_index);
        if (iorgweight(quest_data[rq].target_item_id) > 50000)
        {
            s(10) += i18n::s.get("core.locale.quest.info.heavy");
        }
        s(4) = i18n::s.get(
            "core.locale.quest.info.deliver.text", s(10), s(11), s(12));
        s(6) = s(4);
    }
    if (quest_data[rq].id == 1003)
    {
        s = u8"%COOK,"s + quest_data[rq].extra_info_1;
        if (rnd(6) == 0)
        {
            s = u8"%COOK,GENERAL"s;
        }
        parse_quest_board_text(val0);
        s(4) = cnvarticle(foodname(
            quest_data[rq].extra_info_1, ""s, quest_data[rq].extra_info_2));
        s(6) = i18n::s.get("core.locale.quest.info.supply.text", s(4));
    }
    if (quest_data[rq].id == 1008)
    {
        s = u8"%CONQUER"s;
        parse_quest_board_text(val0);
        s(4) = chara_refstr(quest_data[rq].extra_info_1, 2);
        if (quest_data[rq].extra_info_1 == 343)
        {
            s(4) =
                i18n::s.get("core.locale.quest.info.conquer.unknown_monster");
        }
        s(10) = ""s + quest_data[rq].difficulty * 10 / 6;
        s(6) = i18n::s.get("core.locale.quest.info.conquer.text", s(4));
    }
    if (quest_data[rq].id == 1010)
    {
        s = u8"%HUNTEX"s;
        parse_quest_board_text(val0);
        s(4) = chara_refstr(quest_data[rq].extra_info_1, 2);
        s(10) = ""s + quest_data[rq].difficulty * 3 / 2;
        s(6) = i18n::s.get("core.locale.quest.info.huntex.text");
    }
    if (quest_data[rq].id == 1011)
    {
        s = u8"%COLLECT"s;
        parse_quest_board_text(val0);
        s(10) = cnvarticle(cnvitemname(quest_data[rq].target_item_id));
        s(11) = ""s + mapname(quest_data[rq].originating_map_id);
        if (game_data.current_map == quest_data[rq].originating_map_id
            && game_data.current_dungeon_level == 1)
        {
            s(12) = ""s + cdatan(0, quest_data[rq].target_chara_index);
        }
        else
        {
            s(12) = i18n::s.get("core.locale.quest.info.collect.target", s(11));
        }
        if (iorgweight(quest_data[rq].target_item_id) > 50000)
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
                   "core.locale.quest.giver.have_something_to_ask", cdata[tc])
            + buff;
        if (quest_data[rq].deadline_days != -1)
        {
            buff += i18n::s.get(
                "core.locale.quest.giver.days_to_perform",
                quest_data[rq].deadline_days,
                cdata[tc]);
        }
        buff += i18n::s.get("core.locale.quest.giver.how_about_it", cdata[tc]);
    }
    if (val0 == 2)
    {
        if (quest_data[rq].progress == 3)
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
            + mapname(quest_data[rq].originating_map_id) + u8"\n"s;
        buff += i18n::s.get("core.locale.quest.journal.deadline");
        if (quest_data[rq].deadline_days != -1)
        {
            buff += i18n::s.get("core.locale.quest.journal.remaining");
        }
        buff += nquestdate + u8"\n"s;
        s(5) = i18n::s.get("core.locale.quest.journal.reward") + s(5);
        talk_conv(s(5), 40 - en * 10);
        buff += s(5) + u8"\n"s;
        s(4) = i18n::s.get("core.locale.quest.journal.detail");
        if (quest_data[rq].progress == 3)
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
            "core.locale.quest.giver.complete.done_well", cdata[tc]);
        if (elona::stoi(s(5)) != 0)
        {
            txt(i18n::s.get(
                "core.locale.quest.giver.complete.take_reward",
                s(5),
                cdata[tc]));
        }
        if (quest_data[rq].id == 1006)
        {
            if (quest_data[rq].extra_info_1 * 125 / 100
                < quest_data[rq].extra_info_2)
            {
                buff += i18n::s.get(
                    "core.locale.quest.giver.complete.extra_coins", cdata[tc]);
            }
        }
        if (quest_data[rq].id == 1009)
        {
            if (quest_data[rq].extra_info_1 * 150 / 100
                < quest_data[rq].extra_info_2)
            {
                buff += i18n::s.get(
                    "core.locale.quest.giver.complete.music_tickets",
                    cdata[tc]);
            }
        }
    }
    randomize();
}



void quest_on_map_initialize()
{
    for (auto&& cnt : cdata.others())
    {
        if (cnt.state() == Character::State::empty)
        {
            continue;
        }
        if (cnt.character_role == 0)
        {
            continue;
        }
        if (cnt.quality == Quality::special)
        {
            continue;
        }
        if (cnt.character_role == 3)
        {
            continue;
        }
        i = -1;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (quest_data[cnt].client_chara_index == 0)
            {
                i = cnt;
                break;
            }
        }
        int cnt2 = cnt.index;
        for (int cnt = 0; cnt < 500; ++cnt)
        {
            if (quest_data[cnt].client_chara_index == cnt2)
            {
                if (quest_data[cnt].originating_map_id == game_data.current_map)
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
        quest_data[i].client_chara_index = cnt.index;
        quest_data[i].originating_map_id = game_data.current_map;
        qname(i) = cdatan(0, cnt.index);
        cnt.related_quest_id = i + 1;
        game_data.number_of_existing_quests = i + 1;
    }
}



void quest_refresh_list()
{
    for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].client_chara_index == 0)
        {
            continue;
        }
        if (quest_data[cnt].originating_map_id != game_data.current_map)
        {
            continue;
        }
        rc = quest_data[cnt].client_chara_index;
        if (quest_data[cnt].progress == 0)
        {
            if (quest_data[cnt].deadline_hours < game_data.date.hours())
            {
                rq = cnt;
                quest_generate();
                quest_gen_scale_by_level();
            }
        }
    }
}

void quest_update_journal_msg()
{
    snd("core.write1");
    Message::instance().txtef(ColorIndex::green);
    txt(i18n::s.get("core.locale.quest.journal_updated"));
}

int quest_generate()
{
    quest_data[rq].id = 0;
    quest_data[rq].client_chara_type = 0;
    quest_data[rq].progress = 0;
    quest_data[rq].deadline_hours = (rnd(3) + 1) * 24 + game_data.date.hours();
    quest_data[rq].reward_item_id = 0;
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
            if (n == quest_data[rq].client_chara_index)
            {
                continue;
            }
            if (cdata[n].state() != Character::State::alive)
            {
                continue;
            }
            if (cdata[n].relationship != 0
                || (cdata[n].character_role != 4
                    && cdata[n].character_role != 14))
            {
                continue;
            }
            flt(40, Quality::good);
            flttypemajor = choice(fsetcollect);
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
            quest_data[rq].target_chara_index = i;
            quest_data[rq].target_item_id = i(1);
            quest_data[rq].originating_map_id = game_data.current_map;
            rewardfix = 60;
            quest_data[rq].reward_item_id = 5;
            quest_data[rq].id = 1011;
            quest_data[rq].client_chara_type = 3;
            quest_data[rq].escort_difficulty = 0;
            quest_data[rq].deadline_days = rnd(3) + 2;
            quest_data[rq].difficulty = cdata[i].level / 3;
        }
        return 0;
    }
    if (cdata.player().fame >= 30000)
    {
        if (rnd(13) == 0)
        {
            quest_data[rq].difficulty = rnd(cdata.player().level + 10)
                + rnd((cdata.player().fame / 2500 + 1));
            quest_data[rq].difficulty =
                roundmargin(quest_data[rq].difficulty, cdata.player().level);
            minlevel = clamp(quest_data[rq].difficulty / 7, 5, 30);
            for (int cnt = 0; cnt < 50; ++cnt)
            {
                flt(quest_data[rq].difficulty, Quality::good);
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
            quest_data[rq].extra_info_1 = cdata.tmp().id;
            quest_data[rq].deadline_hours =
                (rnd(6) + 2) * 24 + game_data.date.hours();
            quest_data[rq].reward_item_id = 0;
            quest_data[rq].id = 1010;
            quest_data[rq].client_chara_type = 1;
            quest_data[rq].escort_difficulty = 0;
            quest_data[rq].reward_item_id = 5;
            quest_data[rq].deadline_days = -1;
            rewardfix = 140;
            return 0;
        }
    }
    if (cdata.player().fame >= 50000)
    {
        if (rnd(20) == 0)
        {
            quest_data[rq].difficulty = rnd(cdata.player().level + 10)
                + rnd((cdata.player().fame / 2500 + 1));
            quest_data[rq].difficulty =
                roundmargin(quest_data[rq].difficulty, cdata.player().level);
            minlevel = clamp(quest_data[rq].difficulty / 4, 5, 30);
            for (int cnt = 0; cnt < 50; ++cnt)
            {
                flt(quest_data[rq].difficulty, Quality::good);
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
            quest_data[rq].extra_info_1 = cdata.tmp().id;
            quest_data[rq].deadline_hours =
                (rnd(6) + 2) * 24 + game_data.date.hours();
            quest_data[rq].reward_item_id = 0;
            quest_data[rq].id = 1008;
            quest_data[rq].client_chara_type = 8;
            quest_data[rq].escort_difficulty = 0;
            quest_data[rq].reward_item_id = 1;
            quest_data[rq].deadline_days = -1;
            rewardfix = 175;
            return 0;
        }
    }
    if (rnd(11) == 0)
    {
        quest_data[rq].deadline_hours =
            (rnd(6) + 2) * 24 + game_data.date.hours();
        quest_data[rq].id = 1007;
        quest_data[rq].client_chara_type = 6;
        quest_data[rq].escort_difficulty = rnd(3);
        quest_data[rq].target_chara_index = 0;
        quest_data[rq].reward_item_id = 5;
        while (1)
        {
            quest_data[rq].extra_info_1 = choice(asettown);
            if (quest_data[rq].extra_info_1 != game_data.current_map)
            {
                break;
            }
        }
        p = quest_data[rq].extra_info_1;
        if (quest_data[rq].escort_difficulty == 0)
        {
            rewardfix = 140
                + dist(
                      area_data[game_data.current_map].position.x,
                      area_data[game_data.current_map].position.y,
                      area_data[p].position.x,
                      area_data[p].position.y)
                    * 2;
            quest_data[rq].deadline_days = rnd(8) + 6;
            quest_data[rq].difficulty = clamp(
                rnd(cdata.player().level + 10)
                    + rnd((cdata.player().fame / 500 + 1)) + 1,
                1,
                80);
        }
        if (quest_data[rq].escort_difficulty == 1)
        {
            rewardfix = 130
                + dist(
                      area_data[game_data.current_map].position.x,
                      area_data[game_data.current_map].position.y,
                      area_data[p].position.x,
                      area_data[p].position.y)
                    * 2;
            quest_data[rq].deadline_days = rnd(5) + 2;
            quest_data[rq].difficulty = clamp(rewardfix / 10 + 1, 1, 40);
        }
        if (quest_data[rq].escort_difficulty == 2)
        {
            rewardfix = 80
                + dist(
                      area_data[game_data.current_map].position.x,
                      area_data[game_data.current_map].position.y,
                      area_data[p].position.x,
                      area_data[p].position.y)
                    * 2;
            quest_data[rq].deadline_days = rnd(8) + 6;
            quest_data[rq].difficulty = clamp(rewardfix / 20 + 1, 1, 40);
        }
        if (quest_data[rq].extra_info_1 == 33
            || game_data.current_map == mdata_t::MapId::noyel)
        {
            rewardfix = rewardfix * 180 / 100;
        }
        return 0;
    }
    if (rnd(23) == 0
        || (game_data.current_map == mdata_t::MapId::palmia && rnd(8) == 0))
    {
        quest_data[rq].difficulty = clamp(
            rnd(sdata(183, 0) + 10),
            int(1.5 * std::sqrt(sdata(183, 0))) + 1,
            cdata.player().fame / 1000 + 10);
        quest_data[rq].deadline_hours =
            (rnd(6) + 2) * 24 + game_data.date.hours();
        quest_data[rq].reward_item_id = 0;
        quest_data[rq].id = 1009;
        quest_data[rq].client_chara_type = 7;
        quest_data[rq].escort_difficulty = 0;
        quest_data[rq].reward_item_id = 0;
        quest_data[rq].extra_info_1 = quest_data[rq].difficulty * 10 + rnd(50);
        quest_data[rq].extra_info_2 = 0;
        quest_data[rq].deadline_days = -1;
        rewardfix = 0;
        return 0;
    }
    if (rnd(30) == 0
        || (game_data.current_map == mdata_t::MapId::yowyn && rnd(2) == 0))
    {
        quest_data[rq].difficulty = clamp(
            rnd(cdata.player().level + 5) + rnd((cdata.player().fame / 800 + 1))
                + 1,
            1,
            50);
        quest_data[rq].deadline_hours =
            (rnd(6) + 2) * 24 + game_data.date.hours();
        quest_data[rq].id = 1006;
        quest_data[rq].client_chara_type = 5;
        quest_data[rq].escort_difficulty = 0;
        quest_data[rq].reward_item_id = 5;
        quest_data[rq].deadline_days = -1;
        quest_data[rq].extra_info_1 = 15000 + quest_data[rq].difficulty * 2500;
        quest_data[rq].extra_info_2 = 0;
        rewardfix = 60 + quest_data[rq].difficulty * 2;
        return 0;
    }
    if (rnd(8) == 0)
    {
        quest_data[rq].difficulty = clamp(
            rnd(cdata.player().level + 10)
                + rnd((cdata.player().fame / 500 + 1)) + 1,
            1,
            80);
        quest_data[rq].difficulty =
            roundmargin(quest_data[rq].difficulty, cdata.player().level);
        quest_data[rq].deadline_hours =
            (rnd(6) + 2) * 24 + game_data.date.hours();
        quest_data[rq].reward_item_id = 0;
        quest_data[rq].id = 1001;
        quest_data[rq].client_chara_type = 1;
        quest_data[rq].escort_difficulty = 0;
        quest_data[rq].reward_item_id = 1;
        quest_data[rq].deadline_days = -1;
        rewardfix = 135;
        return 0;
    }
    if (rnd(6) == 0)
    {
        i = -1;
        for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            p = rnd(game_data.number_of_existing_quests);
            for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
                 cnt < cnt_end;
                 ++cnt)
            {
                if (quest_data[cnt].id == 1002)
                {
                    if (quest_data[cnt].target_chara_index == p)
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
            if (quest_data[p].client_chara_index != 0)
            {
                if (quest_data[p].originating_map_id != game_data.current_map
                    || 0)
                {
                    i = p;
                    break;
                }
            }
        }
        if (i != -1)
        {
            p = quest_data[i].originating_map_id;
            rewardfix = 70
                + dist(
                      area_data[game_data.current_map].position.x,
                      area_data[game_data.current_map].position.y,
                      area_data[p].position.x,
                      area_data[p].position.y)
                    * 2;
            if (p == 33 || game_data.current_map == mdata_t::MapId::noyel)
            {
                rewardfix = rewardfix * 175 / 100;
            }
            quest_data[rq].target_chara_index = i;
            flt();
            dbmode = 1;
            flttypemajor = choice(fsetdeliver);
            get_random_item_id();
            quest_data[rq].extra_info_1 = flttypemajor;
            quest_data[rq].reward_item_id = 5;
            if (flttypemajor == 54000)
            {
                quest_data[rq].reward_item_id = 2;
            }
            if (flttypemajor == 77000)
            {
                quest_data[rq].reward_item_id = 3;
            }
            if (flttypemajor == 64000)
            {
                quest_data[rq].reward_item_id = 77000;
            }
            if (flttypemajor == 60000)
            {
                quest_data[rq].reward_item_id = 60000;
            }
            quest_data[rq].target_item_id = dbid;
            quest_data[rq].id = 1002;
            quest_data[rq].client_chara_type = 2;
            quest_data[rq].escort_difficulty = 0;
            quest_data[rq].deadline_days = rnd(12) + 3;
            quest_data[rq].difficulty = clamp(rewardfix / 20 + 1, 1, 25);
        }
        return 0;
    }
    if (rnd(6) == 0)
    {
        quest_data[rq].id = 1003;
        quest_data[rq].client_chara_type = 3;
        quest_data[rq].deadline_days = rnd(6) + 2;
        quest_data[rq].reward_item_id = 5;
        quest_data[rq].extra_info_1 = rnd(8) + 1;
        if (quest_data[rq].extra_info_1 == 4)
        {
            quest_data[rq].reward_item_id = 52000;
        }
        if (quest_data[rq].extra_info_1 == 6)
        {
            quest_data[rq].reward_item_id = 25000;
        }
        if (quest_data[rq].extra_info_1 == 1)
        {
            quest_data[rq].reward_item_id = 25000;
        }
        if (quest_data[rq].extra_info_1 == 5)
        {
            quest_data[rq].reward_item_id = 52000;
        }
        if (quest_data[rq].extra_info_1 == 7)
        {
            quest_data[rq].reward_item_id = 77000;
        }
        if (quest_data[rq].extra_info_1 == 2)
        {
            quest_data[rq].reward_item_id = 56000;
        }
        if (quest_data[rq].extra_info_1 == 3)
        {
            quest_data[rq].reward_item_id = 53000;
        }
        quest_data[rq].extra_info_2 = rnd(7) + 3;
        quest_data[rq].difficulty = quest_data[rq].extra_info_2 * 3;
        rewardfix = 60 + quest_data[rq].difficulty;
        return 0;
    }
    if (rnd(5) == 0)
    {
        quest_data[rq].id = 1004;
        quest_data[rq].client_chara_type = 3;
        quest_data[rq].deadline_days = rnd(6) + 2;
        flt();
        dbmode = 1;
        flttypemajor = choice(fsetsupply);
        get_random_item_id();
        quest_data[rq].reward_item_id = 5;
        quest_data[rq].target_item_id = dbid;
        quest_data[rq].difficulty =
            clamp(rnd(cdata.player().level + 5) + 1, 1, 30);
        rewardfix = 65 + quest_data[rq].difficulty;
        return 0;
    }
    return 1;
}

void quest_gen_scale_by_level()
{
    quest_data[rq].reward_gold =
        ((quest_data[rq].difficulty + 3) * 100
         + rnd((quest_data[rq].difficulty * 30 + 200)) + 400)
        * rewardfix / 100;
    quest_data[rq].reward_gold = quest_data[rq].reward_gold * 100
        / (100 + quest_data[rq].difficulty * 2 / 3);
    if (quest_data[rq].client_chara_type == 3
        || quest_data[rq].client_chara_type == 2)
    {
        return;
    }
    if (cdata.player().level >= quest_data[rq].difficulty)
    {
        quest_data[rq].reward_gold = quest_data[rq].reward_gold * 100
            / (100 + (cdata.player().level - quest_data[rq].difficulty) * 10);
    }
    else
    {
        quest_data[rq].reward_gold = quest_data[rq].reward_gold
            * (100
               + clamp(
                     (quest_data[rq].difficulty - cdata.player().level) / 5
                         * 25,
                     0,
                     200))
            / 100;
    }
}

void quest_check_all_for_failed()
{
    for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].id == 0)
        {
            continue;
        }
        if (quest_data[cnt].progress != 1)
        {
            continue;
        }
        if (quest_data[cnt].deadline_days < 0)
        {
            continue;
        }
        rq = cnt;
        --quest_data[rq].deadline_days;
        if (quest_data[rq].deadline_days == 0)
        {
            quest_failed(quest_data[rq].id);
        }
    }
}



void quest_enter_map()
{
    if (game_data.executing_immediate_quest_type == 1009)
    {
        Message::instance().txtef(ColorIndex::cyan);
        txt(i18n::s.get(
            "core.locale.map.quest.on_enter.party",
            game_data.left_minutes_of_executing_quest,
            quest_data.immediate().extra_info_1));
    }
    if (game_data.executing_immediate_quest_type == 1006)
    {
        if (quest_data.immediate().extra_info_1 <= 0)
        {
            quest_data.immediate().extra_info_1 = 15000;
            quest_data.immediate().reward_gold = 400;
        }
        Message::instance().txtef(ColorIndex::cyan);
        txt(i18n::s.get(
            "core.locale.map.quest.on_enter.harvest",
            cnvweight(quest_data.immediate().extra_info_1),
            game_data.left_minutes_of_executing_quest));
    }
    if (game_data.executing_immediate_quest_type == 1008)
    {
        Message::instance().txtef(ColorIndex::cyan);
        txt(i18n::s.get(
            "core.locale.map.quest.on_enter.conquer",
            chara_refstr(quest_data.immediate().extra_info_1, 2),
            game_data.left_minutes_of_executing_quest));
    }
}



void quest_exit_map()
{
    if (game_data.executing_immediate_quest_type == 1006)
    {
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].own_state == 4)
            {
                inv[cnt].remove();
            }
        }
        refresh_burden_state();
    }
    if (game_data.executing_immediate_quest_status != 3)
    {
        if (game_data.executing_immediate_quest_type >= 1000)
        {
            rq = game_data.executing_immediate_quest;
        }
        if (game_data.executing_immediate_quest_type == 1007)
        {
            if (quest_data[rq].progress == 0)
            {
                game_data.executing_immediate_quest_type = 0;
                game_data.executing_immediate_quest_show_hunt_remain = 0;
                game_data.executing_immediate_quest = 0;
                game_data.executing_immediate_quest_status = 0;
                return;
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.quest.escort.you_left_your_client"));
            }
        }
        quest_failed(game_data.executing_immediate_quest_type);
        msg_halt();
    }
    game_data.executing_immediate_quest_type = 0;
    game_data.executing_immediate_quest_show_hunt_remain = 0;
    game_data.executing_immediate_quest = 0;
    game_data.executing_immediate_quest_status = 0;
}



TurnResult quest_pc_died_during_immediate_quest()
{
    rc = 0;
    revive_player();
    chara_gain_skill_exp(cdata.player(), 17, -500);
    chara_gain_skill_exp(cdata.player(), 15, -500);
    levelexitby = 4;
    game_data.current_dungeon_level = 0;
    return TurnResult::exit_map;
}



void quest_failed(int val0)
{
    if (val0 == 1)
    {
        area_data[game_data.previous_map2].winning_streak_in_arena = 0;
        txt(i18n::s.get("core.locale.quest.you_were_defeated"));
        modrank(0, -100);
    }
    if (val0 >= 1000)
    {
        txt(i18n::s.get("core.locale.quest.failed_taken_from", qname(rq)));
        if (quest_data[rq].id == 1002)
        {
            --quest_data[quest_data[rq].target_chara_index]
                  .delivery_has_package_flag;
            Message::instance().txtef(ColorIndex::purple);
            txt(i18n::s.get(
                "core.locale.quest.deliver.you_commit_a_serious_crime"));
            modify_karma(cdata.player(), -20);
        }
        if (quest_data[rq].id == 1007)
        {
            Message::instance().txtef(ColorIndex::purple);
            txt(i18n::s.get("core.locale.quest.escort.you_failed_to_protect"));
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (cnt != 0)
                {
                    if (cdata[cnt].is_escorted() == 1)
                    {
                        if (quest_data[rq].extra_info_2 == cdata[cnt].id)
                        {
                            tc = cnt;
                            cdata[cnt].is_escorted() = false;
                            if (cdata[tc].state() == Character::State::alive)
                            {
                                if (quest_data[rq].escort_difficulty == 0)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "assassin");
                                    p = -11;
                                }
                                if (quest_data[rq].escort_difficulty == 1)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "poison");
                                    p = -4;
                                }
                                if (quest_data[rq].escort_difficulty == 2)
                                {
                                    s = i18n::s.get(
                                        "core.locale.quest.escort.failed."
                                        "deadline",
                                        cdata[tc]);
                                    mef_add(
                                        cdata.player().position.x,
                                        cdata.player().position.y,
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
                                Message::instance().txtef(ColorIndex::cyan);
                                txt(s);
                                damage_hp(cdata[tc], 999999, p);
                            }
                            cdata[tc].set_state(Character::State::empty);
                            break;
                        }
                    }
                }
            }
            modify_karma(cdata.player(), -10);
        }
        quest_data[rq].id = 0;
        quest_data[rq].progress = 0;
    }
    int stat = decfame(0, 40);
    p = stat;
    Message::instance().txtef(ColorIndex::red);
    txt(i18n::s.get("core.locale.quest.lose_fame", p(0)));
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
    snd("core.cheer");
    if (petarenawin == 1)
    {
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get("core.locale.quest.arena.your_team_is_victorious"));
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get(
            "core.locale.quest.gain_fame",
            game_data.executing_immediate_quest_fame_gained));
        cdata.player().fame += game_data.executing_immediate_quest_fame_gained;
        modrank(1, 100, 2);
        ++area_data[game_data.previous_map2].winning_streak_in_pet_arena;
        if (area_data[game_data.previous_map2].winning_streak_in_pet_arena % 20
            == 0)
        {
            matgetmain(41, 1);
        }
        else if (
            area_data[game_data.previous_map2].winning_streak_in_pet_arena % 5
            == 0)
        {
            matgetmain(40, 1);
        }
    }
    else
    {
        Message::instance().txtef(ColorIndex::purple);
        txt(i18n::s.get("core.locale.quest.arena.your_team_is_defeated"));
        area_data[game_data.previous_map2].winning_streak_in_pet_arena = 0;
        modrank(1, -100);
        int stat = decfame(0, 60);
        p = stat;
        if (arenaop == 0)
        {
            Message::instance().txtef(ColorIndex::red);
            txt(i18n::s.get("core.locale.quest.lose_fame", p(0)));
        }
    }
}



void quest_all_targets_killed()
{
    musicloop = 1;
    play_music("core.mcFanfare");
    game_data.executing_immediate_quest_status = 3;
    if (game_data.executing_immediate_quest_type == 1)
    {
        snd("core.cheer");
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get("core.locale.quest.arena.you_are_victorious"));
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get(
            "core.locale.quest.gain_fame",
            game_data.executing_immediate_quest_fame_gained));
        modrank(0, 100, 2);
        cdata.player().fame += game_data.executing_immediate_quest_fame_gained;
        txt(i18n::s.get("core.locale.quest.arena.stairs_appear"));
        map_placeupstairs(map_data.width / 2, map_data.height / 2);
        ++area_data[game_data.previous_map2].winning_streak_in_arena;
        if (area_data[game_data.previous_map2].winning_streak_in_arena % 20
            == 0)
        {
            matgetmain(41, 1);
        }
        else if (
            area_data[game_data.previous_map2].winning_streak_in_arena % 5 == 0)
        {
            matgetmain(40, 1);
        }
    }
    if (game_data.executing_immediate_quest_type == 1001
        || game_data.executing_immediate_quest_type == 1010)
    {
        quest_data.immediate().progress = 3;
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get("core.locale.quest.hunt.complete"));
    }
    if (game_data.executing_immediate_quest_type == 1007)
    {
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get("core.locale.quest.hunt.complete"));
    }
    if (game_data.executing_immediate_quest_type == 1008)
    {
        game_data.left_minutes_of_executing_quest = 0;
        quest_data.immediate().progress = 3;
        Message::instance().txtef(ColorIndex::green);
        txt(i18n::s.get("core.locale.quest.conquer.complete"));
    }
}

void quest_complete()
{
    snd("core.complete1");
    p = quest_data[rq].reward_gold;
    if (quest_data[rq].id == 1006)
    {
        if (quest_data[rq].extra_info_1 != 0)
        {
            if (quest_data[rq].extra_info_1 * 125 / 100
                < quest_data[rq].extra_info_2)
            {
                p = clamp(
                    p
                        * static_cast<int>(
                              static_cast<double>(quest_data[rq].extra_info_2)
                              / quest_data[rq].extra_info_1),
                    p(0),
                    p * 3);
            }
        }
    }
    if (p != 0)
    {
        flt();
        itemcreate(
            -1, 54, cdata.player().position.x, cdata.player().position.y, p);
    }
    if (quest_data[rq].id == 1002)
    {
        p = rnd(2) + 1;
    }
    else
    {
        p = 1;
    }
    if (quest_data[rq].id == 1008 || quest_data[rq].id == 1010)
    {
        p = 2 + (rnd(100) < rnd(cdata.player().fame / 5000 + 1));
    }
    flt();
    itemcreate(-1, 55, cdata.player().position.x, cdata.player().position.y, p);
    if (quest_data[rq].id == 1009)
    {
        if (quest_data[rq].extra_info_1 * 150 / 100
            < quest_data[rq].extra_info_2)
        {
            flt();
            itemcreate(
                -1,
                724,
                cdata.player().position.x,
                cdata.player().position.y,
                1 + quest_data[rq].extra_info_2 / 10);
        }
    }
    if (quest_data[rq].reward_item_id != 0)
    {
        p = rnd(rnd(4) + 1) + 1;
        if (quest_data[rq].id == 1008 || quest_data[rq].id == 1010)
        {
            p += 2;
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            fixlv = Quality::good;
            if (rnd(2))
            {
                fixlv = Quality::great;
                if (rnd(12) == 0)
                {
                    fixlv = Quality::miracle;
                }
            }
            flt((quest_data[rq].difficulty + cdata.player().level) / 2 + 1,
                calcfixlv(fixlv));
            if (quest_data[rq].reward_item_id < 10000)
            {
                if (quest_data[rq].reward_item_id == 1)
                {
                    flttypemajor = choice(fsetwear);
                }
                if (quest_data[rq].reward_item_id == 2)
                {
                    flttypemajor = choice(fsetmagic);
                }
                if (quest_data[rq].reward_item_id == 3)
                {
                    flttypemajor = choice(fsetarmor);
                }
                if (quest_data[rq].reward_item_id == 4)
                {
                    flttypemajor = choice(fsetweapon);
                }
                if (quest_data[rq].reward_item_id == 5)
                {
                    flttypemajor = choice(fsetrewardsupply);
                }
            }
            else
            {
                flttypemajor = quest_data[rq].reward_item_id;
            }
            itemcreate(
                -1, 0, cdata.player().position.x, cdata.player().position.y, 0);
        }
    }
    modify_karma(cdata.player(), 1);
    game_data.executing_immediate_quest_fame_gained =
        calcfame(0, quest_data[rq].difficulty * 3 + 10);
    Message::instance().txtef(ColorIndex::green);
    txt(i18n::s.get("core.locale.quest.completed_taken_from", qname(rq)));
    Message::instance().txtef(ColorIndex::green);
    txt(i18n::s.get(
        "core.locale.quest.gain_fame",
        game_data.executing_immediate_quest_fame_gained));
    cdata.player().fame += game_data.executing_immediate_quest_fame_gained;
    txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
    if (quest_data[rq].id == 1002)
    {
        --quest_data[quest_data[rq].target_chara_index]
              .delivery_has_package_flag;
    }
    quest_data[rq].id = 0;
    quest_data[rq].progress = 0;
    autosave = 1 * (game_data.current_map != mdata_t::MapId::show_house);
}

} // namespace elona
